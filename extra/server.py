from fastapi import FastAPI, HTTPException
from typing import Dict
from pydantic import BaseModel
import uvicorn
import os
import konto
import bank
import ware

app = FastAPI()

konto_liste: Dict[str, konto.Konto] = {} # Verzeichnis aller existierenden Kontos
bank_existenz = []

class meineWare(BaseModel):
    """Modell für Handelsgut/Ware"""
    ware_name: str
    price: float
    units: int

@app.post("/create_konto/")
def create_konto(benutzername : str, passwort : str):
    """Erstellt ein neues Konto mit eingegebenem Benutzernamen & Passwort"""
    neues_konto = konto.Konto(benutzername, passwort)
    konto_liste[benutzername] = neues_konto
    return {
        "message" : "✓✓✓ Das Konto wurde erfolgreich erstellt. ✓✓✓",
        "benutzername" : benutzername
    }

@app.post("/login/")
def login(benutzername : str, passwort : str):
    """Loggt ein Nutzer*in mit eingegebenem Benutzernamen & Passwort ein"""
    if benutzername in konto_liste:
        aktuelles_konto = konto_liste[benutzername]
        if aktuelles_konto.getPasswort() == passwort:
            return {
                "message" : "✓✓✓ Einloggen erfolgreich. Wilkommen zurück! ✓✓✓",
                "benutzername" : benutzername
            }
        
        else:
            raise HTTPException(status_code=401, detail="xxx Falsches Passwort. xxx")
    
    else:
        raise HTTPException(status_code=404, detail="xxx Das Konto mit diesem Benutzername existiert nicht. xxx")

@app.post("/start/")
def start():
    """die Bank initialisieren, falls noch nicht"""
    if len(bank_existenz) == 0:
        aktuelle_bank = bank.Bank()
        bank_existenz.append(aktuelle_bank)

        return {
        "message" : "✓✓✓ die Bank wurde erfolgreich initialisiert ✓✓✓",
        }
    
    else:
        aktuelle_bank = bank_existenz[0]

        return {
            "message" : "✓✓✓ die Bank funktioniert gerade ✓✓✓",
        }

@app.get("/mein_konto/")
def mein_konto(benutzername : str):
    """Gibt Infos über das Konto zurück"""

    if benutzername not in konto_liste:
        raise HTTPException(status_code=404, detail="Konto nicht gefunden")
    
    aktuelles_konto = konto_liste[benutzername]

    inventar = aktuelles_konto.getInventar()
    myInventar: Dict[str, meineWare] = {}       # Verzeichnis aller besitzten Waren

    for name, aktuelle_ware in inventar:
        data = {
            "ware_name" : name,
            "price" : aktuelle_ware.getPrice(),
            "units" : aktuelle_ware.getUnits()
        }

        ware_instanz = meineWare(**data)
        myInventar[name] = ware_instanz         # Ware zum Inventar hinzufügen

    return {
        "guthaben" : aktuelles_konto.getGuthaben(),
        "inventar" : myInventar
    }


if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)

