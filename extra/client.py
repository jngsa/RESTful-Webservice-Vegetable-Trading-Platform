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
    
    except requests.exceptions.RequestException as e:   # wenn der Server Error zurückgibt
        raise Exception (f"xxx Fehler beim Kaufen: {e} xxx")


# ------------------------------------------------

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
            try: 
                bank_response = get_bank_waren()
                bank_waren = bank_response["stocks"]
                
                print("------------------- Kaufseite -------------------")

                for name, ware_von_bank in bank_waren.items():
                    print("X-----------------------------------X")
                    print(f"Ware    : {name}")
                    print(f"Preis   : {round(ware_von_bank['price'], 0)} POOSE-Coins")      # Preis wird zu einer Ganzzahl aufgerundet
                    print(f"Units   : {ware_von_bank['units']}")
                    print("X-----------------------------------X")
                    print(" ")
                
                ware_name = input("Gibt den Namen von der Ware ein, die du kaufen möchtest : ")

                while ware_name not in bank_waren:      # falls eingegebener Name von Ware existiert nicht
                    print(f"{ware_name} existiert nicht.")
                    ware_name = input("Gibt den Namen von der Ware ein, die du kaufen möchtest : ")

                units = input(f"Wie viele {ware_name} möchtest du kaufen? Gibt eine Anzahl davon ein : ")

                while units.isdigit() == False:         # falls Zeichen statt Zahlen eingegeben werden
                    print("Gibt bitte NUR Zahlen ein!")
                    units = input(f"Wie viele {ware_name} möchtest du kaufen? Gibt eine Anzahl davon ein : ")

                kauf_info = kaufen(benutzername, ware_name, units)
                print(kauf_info["message"])

            except Exception as e:
                print(f"Fehler: {e}")

            time.sleep(10)
            

        elif wahl == "2":
            break # temporary placeholder

        elif wahl == "3":
            try:
                mein_konto_info = mein_konto(benutzername)

                print("------------------- Konto-Info -------------------")
                print(f"Benutzername        : {konto_info['benutzername']}")
                print(f"POOSE-Coins         : {round(mein_konto_info['guthaben'], 0)}")     # Guthaben wird zu einer Ganzzahl aufgerundet

                print("Meine Waren ; ")
                print(" ")

                if mein_konto_info["isEmpty"]:
                    print("Noch keine Waren!")

                else:
                    myInventar = mein_konto_info["inventar"]

                    for name, myWare in myInventar.items():
                        print(f"Ware    : {name}")
                        print(f"Preis   : {round(myWare['price'], 0)} POOSE-Coins")        # Preis wird zu einer Ganzzahl aufgerundet
                        print(f"Units   : {myWare['units']}")
                        print(" ")

            except Exception as e:
                print(f"Fehler: {e}")

            time.sleep(5)

        elif wahl == "4":
            break

        else:
            print("Ungültige Option. Bitte wähle 1, 2, 3 oder 4.")


        

        









if __name__ == "__main__":
    client()
