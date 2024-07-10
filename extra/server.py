from fastapi import FastAPI, HTTPException
from typing import Dict
from pydantic import BaseModel
import uvicorn
import os
import time
import threading
import konto
import bank
import ware

app = FastAPI()

from fastapi.middleware.cors import CORSMiddleware

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Erlaubt alle Ursprünge
    allow_credentials=True,
    allow_methods=["*"],  # Erlaubt alle Methoden
    allow_headers=["*"],  # Erlaubt alle Header
)

konto_liste: Dict[str, konto.Konto] = {} # Verzeichnis aller existierenden Kontos
bank_existenz = []  # enthält die aktuelle Bank

class meineWare(BaseModel):
    """Modell für Handelsgut/Ware"""
    ware_name: str
    price: float
    units: int

# -------------------------------------------------------------------------------
# Preis-Aktualisieren (jede 30 Sekunden)

def update_prices():
    while True:
        if len(bank_existenz) == 0:
            aktuelle_bank = bank.Bank()             # die Bank initialisieren
            bank_existenz.append(aktuelle_bank)     # diese Bank in bank_existenz einfügen
        
        else:
            aktuelle_bank = bank_existenz[0]
        
        time.sleep(30)
        aktuelle_bank.updatePrices()
        print("STATUS UPDATE: Preise von Waren aktualisiert.")

# Preis-Aktualisieren im Hintergrund ausführen
def start_background_tasks():
    thread = threading.Thread(target=update_prices, daemon=True)
    thread.start()

@app.on_event("startup")
async def startup_event():
    start_background_tasks()

# -------------------------------------------------------------------------------

@app.post("/create_konto/")
def create_konto(benutzername : str, passwort : str):
    """Erstellt ein neues Konto mit eingegebenem Benutzernamen & Passwort"""
    
    if benutzername in konto_liste:     # falls andere(r) Nutzer*in mit dem Benutzernamen schon angemeldet hat
        return {
            "message" : "Dieser Benutzername ist belegt.",
            "benutzername" : ""
        }

    neues_konto = konto.Konto(benutzername, passwort)   # ein Konto erstellen
    konto_liste[benutzername] = neues_konto             # fügt dieses Konto in konto_liste ein
    return {
        "message" : "Das Konto wurde erfolgreich erstellt. ",
        "benutzername" : benutzername
    }

@app.post("/login/")
def login(benutzername : str, passwort : str):
    """Loggt ein Nutzer*in mit eingegebenem Benutzernamen & Passwort ein"""

    # prüft, ob das Konto mit diesem Benutzernamen schon existiert
    if benutzername in konto_liste:
        aktuelles_konto = konto_liste[benutzername]
        if aktuelles_konto.getPasswort() == passwort:   # Einloggen mit dem Passwort authentifizieren
            return {
                "message" : "Einloggen erfolgreich. Wilkommen zurück!",
                "benutzername" : benutzername
            }
        
        else:
            raise HTTPException(status_code=401, detail="xxx Falsches Passwort. xxx")
    
    else:
        raise HTTPException(status_code=404, detail="xxx Das Konto mit diesem Benutzername existiert nicht. xxx")

@app.post("/start/")
def start():
    """die Bank initialisieren, falls noch nicht"""

    if len(bank_existenz) == 0:                 # falls die Bank noch nicht initialisiert wird
        aktuelle_bank = bank.Bank()             # die Bank initialisieren
        bank_existenz.append(aktuelle_bank)     # diese Bank in bank_existenz einfügen

        return {
        "message" : "STATUS UPDATE: Die Bank wurde erfolgreich initialisiert.",
        }
    
    else:
        aktuelle_bank = bank_existenz[0]        # falls die Bank schon initialisiert wurde, tut nichts

        return {
            "message" : "STATUS UPDATE: Die Bank funktioniert gerade.",
        }

@app.get("/mein_konto/")
def mein_konto(benutzername : str):
    """Gibt Infos über das Konto zurück"""

    if benutzername not in konto_liste:
        raise HTTPException(status_code=404, detail="Konto nicht gefunden")
    
    aktuelles_konto = konto_liste[benutzername]     # Holt existierendes Konto vom konto_liste ab

    inventar = aktuelles_konto.getInventar()        # Holt das Inventar des Kontos
    myInventar: Dict[str, meineWare] = {}           # Verzeichnis aller besitzten Waren
    isEmpty = aktuelles_konto.istInventarEmpty()    # prüft, ob Inventar leer ist

    # Wandeln std::unordered_map mit value class Ware in einen Dict mit value Base-Model meineWare um
    # (class Ware kann nicht in json gepackt werden, deshalb ist diese Umwandlung nötig)
    for name, aktuelle_ware in inventar.items():
        data = {
            "ware_name" : name,
            "price" : aktuelle_ware.getPrice(),
            "units" : aktuelle_ware.getUnits()
        }

        ware_instanz = meineWare(**data)        # data als Base-Model speichern
        myInventar[name] = ware_instanz         # Ware zum Inventar hinzufügen

    return {
        "message" : "Infos über Konto erfolgreich zugegriffen",
        "guthaben" : aktuelles_konto.getGuthaben(),
        "inventar" : myInventar,
        "isEmpty" : isEmpty
    }

@app.get("/bank_waren/")
def get_bank_waren():
    """Gibt alle verkäuflichen Waren von der Bank zurück mit aktuellem Preis"""

    if len(bank_existenz) == 0:
        raise HTTPException(status_code=404, detail="Bank noch nicht initialisiert")
    
    aktuelle_bank = bank_existenz[0]        # Holt die Bank ab
    stocks = aktuelle_bank.getStocks()      # stocks enthält ware, die aus dem Namen, Preis und Units besteht  (Stocks -> Ware -> Name, Preis, Units)
    
    # stocks from Source-Datei in ein Dict umwandeln (ähnlicher Grund wie beim Inventar)
    
    bank_stocks: Dict[str, meineWare] = {}

    for güter in stocks:
        data = {
            "ware_name" : güter.getName(),
            "price" : güter.getPrice(),
            "units" : güter.getUnits()
        }

        ware_instanz = meineWare(**data)            # data als Base-Model speichern
        bank_stocks[güter.getName()] = ware_instanz # Ware zum bank_stocks hinzufügen

    return {
        "message" : "Alle Güter von der Bank erfolgreich zugegriffen",
        "stocks" : bank_stocks
    }

@app.post("/kaufen/")
def kaufen(benutzername : str, ware_name : str, units : int):
    """Kauft eingegebene Ware"""

    if benutzername not in konto_liste:
        raise HTTPException(status_code=404, detail="Konto nicht gefunden")
    
    try:
        aktuelles_konto = konto_liste[benutzername]                 # Holt das Konto und die Bank ab
        aktuelle_bank = bank_existenz[0]

        aktuelles_konto.buyWare(aktuelle_bank, ware_name, units)    # Ware(n) von der Bank kaufen
    
    except konto.InvalidArgument as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    return {
            "message" : "Kauf erfolgreich!"
        }

@app.post("/verkaufen/")
def verkaufen(benutzername : str, ware_name : str, units : int):
    """Verkauft eingegebene Ware"""

    if benutzername not in konto_liste:
        raise HTTPException(status_code=404, detail="Konto nicht gefunden")
    
    try:
        aktuelles_konto = konto_liste[benutzername]                 # Holt das Konto und die Bank ab
        aktuelle_bank = bank_existenz[0]

        aktuelles_konto.sellWare(aktuelle_bank, ware_name, units)   # der Bank Ware(n) verkaufen
    
    except konto.InvalidArgument as e:
        raise HTTPException(status_code=400, detail=str(e))
    
    return {
            "message" : "Verkauf erfolgreich!"
        }


if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
    start()

