from fastapi import FastAPI, HTTPException
from typing import Dict
from pydantic import BaseModel
import uvicorn
import os
import konto
import bank
import ware

app = FastAPI()

konto_liste: Dict[str, Konto] = {} # Verzeichnis aller existierenden Kontos

@app.post("/create_konto/")
def create_konto(benutzername : str, passwort : str):
    """Erstellt ein neues Konto mit eingegebenem Benutzernamen & Passwort"""
    konto = Konto(benutzername, passwort)
    konto_liste[benutzername] = konto
    return {
        "message" : "Das Konto wurde erfolgreich erstellt.",
        "benutzername" : benutzername
    }








if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)

