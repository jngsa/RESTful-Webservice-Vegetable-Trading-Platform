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

@app.post("/create_konto/")
def create_konto(benutzername : str, passwort : str):
    """Erstellt ein neues Konto mit eingegebenem Benutzernamen & Passwort"""
    neues_konto = konto.Konto(benutzername, passwort)
    konto_liste[benutzername] = neues_konto
    return {
        "message" : "Das Konto wurde erfolgreich erstellt.",
        "benutzername" : benutzername
    }

@app.post("/login/")
def login(benutzername : str, passwort : str):
    """Loggt ein Nutzer*in mit eingegebenem Benutzernamen & Passwort ein"""
    if benutzername in konto_liste:
        aktuelles_konto = konto_liste[benutzername]
        if aktuelles_konto.getPasswort() == passwort:
            return {
                "message" : "Einloggen erfolgreich. Wilkommen zurück!",
                "benutzername" : benutzername
            }
        
        else:
            raise HTTPException(status_code=401, detail="Falsches Passwort.")
    
    else:
        raise HTTPException(status_code=404, detail="Das Konto mit diesem Benutzername existiert nicht.")






if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)

