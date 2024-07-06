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
        raise Exception (f"Fehler beim Erstellen des Kontos: {e}")



def client():
    """Hauptfunktion des Clients"""
    print("Wilkommen beim Handelplatz!")

    while True:
        print("1 - Einloggen")                  # input, ob man einloggt oder ein neues Konto erstellt
        print("2 - neues Konto erstellen")

        choice = input("Wähle eine Option 1 / 2 : ")

        if choice == "1":
            break # temporary placeholder
        
        elif choice == "2":
            benutzername = input("Gibt deinen Benutzernamen ein : ")

            while not (benutzername and benutzername.strip()):     # falls der eingegebene Benutzername kein Zeichen enthält (empty string)
                print("Du hast nichts eingegeben!")
                benutzername = input("Bitte gibt deinen Namen nochmal ein : ")

            passwort = input("Gibt dein Passwort ein : ")

            while not (passwort and passwort.strip()):     # falls das eingegebene Passwort kein Zeichen enthält (empty string)
                print("Du hast nichts eingegeben!")
                passwort = input("Bitte gibt dein Passwort nochmal ein : ")

            try:
                konto_info = create_konto(benutzername, passwort)

                if not konto_info or "benutzername" not in konto_info:
                    raise Exception ("Ungültige Antwort vom Server: Benutzername nicht gefunden.")       

                print(f"Konto erstellt. Dein Benutzername : {benutzername}")

            except Exception as e:
                print(f"Fehler : {e}")











if __name__ == "__main__":
    client()
