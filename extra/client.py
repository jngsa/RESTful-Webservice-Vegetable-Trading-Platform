import requests
import time

BASE_URL = "http://localhost:8000"

def create_konto(benutzername, passwort):
    """Erstellt ein neues Konto mit eingegebenem Benutzernamen & Passwort"""
    try:
        response = requests.post(f"{BASE_URL}/create_konto/", params={"benutzername": benutzername, "passwort": passwort})
        response.raise_for_status()  # Wirft eine Ausnahme bei einem Fehler-Statuscode
        return response.json()
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Erstellen des Kontos: {e} xxx")
    
def login(benutzername, passwort):
    """Loggt ein Nutzer*in mit eingegebenem Benutzernamen & Passwort ein"""
    try:
        response = requests.post(f"{BASE_URL}/login/", params={"benutzername": benutzername, "passwort": passwort})
        response.raise_for_status()  # Wirft eine Ausnahme bei einem Fehler-Statuscode
        return response.json()
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        if response.status_code == 401:
            raise Exception("Falsches Passwort.")
        
        elif response.status_code == 404:
            raise Exception("Konto existiert nicht.")
        
        else:
            raise Exception(f"xxx Fehler beim Einloggen. : {e} xxx")

def start():
    """die Bank initialisieren, falls noch nicht"""
    try:
        response = requests.post(f"{BASE_URL}/start/")
        response.raise_for_status()  # Wirft eine Ausnahme bei einem Fehler-Statuscode
        return response.json()
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Initialisieren der Bank: {e} xxx")

def mein_konto(benutzername):
    """Gibt Infos über das Konto vom Server zurück"""
    try:
        response = requests.get(f"{BASE_URL}/mein_konto/", params={"benutzername" : benutzername})
        return response.json()
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Empfangen der Infos des Kontos vom Server: {e} xxx")

def get_bank_waren():
    """Gibt alle verkäuflichen Waren von der Bank zurück mit aktuellem Preis"""
    try:
        response = requests.get(f"{BASE_URL}/bank_waren/")
        return response.json()
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Empfangen der Infos des Kontos vom Server: {e} xxx")
    
def kaufen(benutzername, ware_name, units):
    """Kauft eingegebene Ware"""
    try:
        response = requests.post(f"{BASE_URL}/kaufen/", params={"benutzername" : benutzername, "ware_name" : ware_name, "units" : units})
        response.raise_for_status()  # Wirft eine Ausnahme bei einem Fehler-Statuscode
        return response.json()
    
    except requests.exceptions.HTTPError as http_err:   # wenn der Server spezifischen Error zurückgibt
        if response.status_code == 400:
            print(f"Fehler: {response.json()['detail']}")
        else:
            print(f"HTTP error occurred: {http_err}")

    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Kaufen: {e} xxx")
    
def verkaufen(benutzername, ware_name, units):
    """Verkauft eingegebene Ware"""
    try:
        response = requests.post(f"{BASE_URL}/verkaufen/", params={"benutzername" : benutzername, "ware_name" : ware_name, "units" : units})
        response.raise_for_status()  # Wirft eine Ausnahme bei einem Fehler-Statuscode
        return response.json()
    
    except requests.exceptions.HTTPError as http_err:   # wenn der Server spezifischen Error zurückgibt
        if response.status_code == 400:
            print(f"Fehler: {response.json()['detail']}")
        else:
            print(f"HTTP error occurred: {http_err}")

    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Verkaufen: {e} xxx")


# ------------------------------------------------
def main():
    start()


if __name__ == "__main__":
    client()
