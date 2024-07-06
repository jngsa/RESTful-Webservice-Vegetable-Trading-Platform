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
            raise Exception("xxx Falsches Passwort. xxx")
        
        elif response.status_code == 404:
            raise Exception("xxx Konto existiert nicht. xxx")
        
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


def client():
    """Hauptfunktion des Clients"""
    print("Wilkommen beim Handelplatz!")

    while True:
        print("-------------- Login/Anmelden-Seite ----------------")
        print("1 - Einloggen")                  # input, ob man einloggt oder ein neues Konto erstellt
        print("2 - neues Konto erstellen")

        choice = input("Wähle eine Option 1 / 2 : ")

        # Einloggen
        if choice == "1":
            print("------------------- Einloggen -------------------")
            benutzername = input("Gibt deinen Benutzernamen ein : ")

            while not (benutzername and benutzername.strip()):     # falls der eingegebene Benutzername kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                benutzername = input("Bitte gibt deinen Namen nochmal ein : ")
            
            passwort = input("Gibt dein Passwort ein : ")

            while not (passwort and passwort.strip()):     # falls das eingegebene Passwort kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                passwort = input("Bitte gibt dein Passwort nochmal ein : ")
            
            try:
                konto_info = login(benutzername, passwort)
                print(konto_info["message"])

                if konto_info["message"] == "✓✓✓ Einloggen erfolgreich. Wilkommen zurück! ✓✓✓":
                    break

            except Exception as e:
                print(f"xxx Fehler : {e} xxx")

        # neues Konto erstellen
        elif choice == "2":
            print("------------- neues Konto erstellen -------------")
            benutzername = input("Gibt deinen Benutzernamen ein : ")

            while not (benutzername and benutzername.strip()):     # falls der eingegebene Benutzername kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                benutzername = input("Bitte gibt deinen Namen nochmal ein : ")

            passwort = input("Gibt dein Passwort ein : ")

            while not (passwort and passwort.strip()):     # falls das eingegebene Passwort kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                passwort = input("Bitte gibt dein Passwort nochmal ein : ")

            try:
                konto_info = create_konto(benutzername, passwort)

                if not konto_info or "benutzername" not in konto_info:
                    raise Exception ("xxx Ungültige Antwort vom Server: Benutzername nicht gefunden. xxx")       

                print(f"✓✓✓ Konto erstellt. Dein Benutzername : {benutzername} ✓✓✓")
                print("✓✓✓ Du kannst sich jetzt einloggen. ✓✓✓")

            except Exception as e:
                print(f"xxx Fehler : {e} xxx")
        
        else:
            print("Ungültige Option. Bitte wähle 1 oder 2.")


    while True:
        try:
            bank_info = start()
            print(bank_info["message"])

        except Exception as e:
                print(f"xxx Fehler : {e} xxx")
        
        print("------------------- Startseite -------------------")
        print("1 - verfügbare Handelsgüter der Bank sehen & kaufen")
        print("2 - meine Handelsgüter verkaufen")
        print("3 - Infos über mein Konto")
        print("4 - Logout")

        wahl = input("Wähle eine Option 1 / 2 / 3 : ")

        if wahl == "1":
            break # temporary placeholder

        elif wahl == "2":
            break # temporary placeholder

        elif wahl == "3":
            mein_konto_info = mein_konto(konto_info["benutzername"])

            print("------------------- Konto-Info -------------------")
            print(f"Benutzername        : {konto_info['benutzername']}")
            print(f"Aktuelle Guthaben   : {mein_konto_info['guthaben']}")

            print("Meine Waren ; ")
            print(" ")
            myInventar = mein_konto_info["inventar"]

            for name, myWare in myInventar.items():
                print(f"Ware    : {name}")
                print(f"Preis   : {myWare['price']}")
                print(f"Units   : {myWare['units']}")
                print(" ")

            time.sleep(5)

        elif wahl == "4":
            break

        else:
            print("Ungültige Option. Bitte wähle 1, 2, 3 oder 4.")


        

        









if __name__ == "__main__":
    client()
