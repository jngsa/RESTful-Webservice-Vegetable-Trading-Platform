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

def client():
    """Hauptfunktion des Clients"""
    print("Wilkommen beim Handelplatz!")

    # Login/Anmelden-Seite loop
    while True:
        print("-------------- Login/Anmelden-Seite ----------------")
        print("1 - Einloggen")                      # input, ob man einloggt oder ein neues Konto erstellt
        print("2 - neues Konto erstellen")
        print(" ")
        choice = (input("Wähle eine Option 1 / 2 : ")).strip()  # strip() entfernt Leerzeichen vom String
        print(" ")

        # Einloggen
        if choice == "1":
            print("------------------- Einloggen -------------------")
            benutzername = (input("Gibt deinen Benutzernamen ein : ")).strip()

            while not (benutzername and benutzername.strip()):     # falls der eingegebene Benutzername kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                benutzername = (input("Bitte gibt deinen Namen nochmal ein : ")).strip()
            
            passwort = (input("Gibt dein Passwort ein : ")).strip()

            while not (passwort and passwort.strip()):             # falls das eingegebene Passwort kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                passwort = (input("Bitte gibt dein Passwort nochmal ein : ")).strip()
            
            try:
                konto_info = login(benutzername, passwort)         # Schickt Login-Information am Server
                print(" ")
                print(konto_info["message"])

                if konto_info["message"] == "Einloggen erfolgreich. Wilkommen zurück!":
                    break                                           # wenn das Einloggen erfolgreich ist, wird diese Loop beendet

            except Exception as e:
                print(f"xxx Fehler : {e} xxx")
            
            print(" ")

        # neues Konto erstellen
        elif choice == "2":
            print("------------- neues Konto erstellen -------------")
            benutzername = (input("Gibt deinen Benutzernamen ein : ")).strip()

            while not (benutzername and benutzername.strip()):     # falls der eingegebene Benutzername kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                benutzername = (input("Bitte gibt deinen Namen nochmal ein : ")).strip()

            passwort = (input("Gibt dein Passwort ein : ")).strip()

            while not (passwort and passwort.strip()):             # falls das eingegebene Passwort kein Zeichen enthält (empty string)
                print("xxx Du hast nichts eingegeben! xxx")
                passwort = (input("Bitte gibt dein Passwort nochmal ein : ")).strip()

            try:
                konto_info = create_konto(benutzername, passwort)  # Schickt Anmelden-Info am Server

                if not konto_info or "benutzername" not in konto_info:  # falls der Server nichts zurückgibt
                    raise Exception ("xxx Ungültige Antwort vom Server: Fehler beim Anmelden. xxx")   

                if konto_info["message"] == "Dieser Benutzername ist belegt.":  # falls der gewählte Benutzername schon belegt ist
                    raise Exception ("xxx Der eingegebene Benutzername ist belegt. Wählt einen anderen! xxx")    

                else:
                    print(" ")
                    print(f"✓✓✓ Konto erstellt. Dein Benutzername : {benutzername} ✓✓✓")
                    print("✓✓✓ Du kannst sich jetzt einloggen. ✓✓✓")

            except Exception as e:
                print(f"xxx Fehler : {e} xxx")
            
            print(" ")
        
        else:   # falls der eingegebene Input anders als 1 oder 2 ist
            print("Ungültige Option. Bitte wähle 1 oder 2.")
            print(" ")


    # Webservice-Loop
    while True:
        try:
            bank_info = start()             # die Bank initialisieren (falls noch nicht)
            print("")
            print(bank_info["message"])     # Schickt Status-Update von der Bank am Client
            print("")

        except Exception as e:
                print(f"xxx Fehler : {e} xxx")
        
        # Konsole-UI
        print("------------------- Startseite -------------------")
        print("1 - verfügbare Handelsgüter der Bank sehen & kaufen")
        print("2 - meine Handelsgüter verkaufen")
        print("3 - Infos über mein Konto")
        print("4 - Logout")
        print("")

        wahl = (input("Wähle eine Option 1 / 2 / 3 / 4 : ")).strip()

        # Kaufseite (von der Bank)
        if wahl == "1":
            try: 
                bank_response = get_bank_waren()        # fordert alle verkäuflichen Waren von der Bank an
                bank_waren = bank_response["stocks"]    # bank_waren ist ein Dict mit Namen der Ware als key & ein Base-Model als value
                                                        # Base-Model enthält Namen, Preis und Anzahl der verfügbaren Ware
                
                # Konsole-UI
                print("------------------- Kaufseite -------------------")

                # alle Waren in bank_waren werden ausgedruckt
                for name, ware_von_bank in bank_waren.items():
                    print("X-----------------------------------X")
                    print(f"Ware    : {name}")
                    print(f"Preis   : {round(ware_von_bank['price'], 2)} POOSE-Bucks")      # Preis wird bis zu 2 Dezimalstellen aufgerundet
                    
                    if ware_von_bank['units'] != 0:
                        print(f"Units   : {ware_von_bank['units']}")
                    
                    else:   # falls die Ware ausverkauft ist
                        print("Units   : AUSVERKAUFT") 
                    
                    print("X-----------------------------------X")
                    print(" ")
                
                print("ACHTUNG: Wenn du seit langem diese Seite nicht aktualisiert hat, werden die aktuellen Preise aller Waren höchstwahrscheinlich unterschiedlich von den gezeigten Preisen.")
                print("Gibt 0 ein, wenn du nichts kaufen möchtest.")
                ware_name = ((input("Gibt den Namen von der Ware ein, die du kaufen möchtest : ")).strip()).capitalize()    # capitalize() schreibt der erste Buchstabe des Inputs groß

                # Wenn 0 eingegeben wird, verlässt der/die Nutzer*in die Kaufseite 
                if ware_name != "0":
                    while ware_name not in bank_waren:      # falls eingegebener Name von Ware existiert nicht
                        print(f"{ware_name} existiert nicht.")
                        ware_name = ((input("Gibt den Namen von der Ware ein, die du kaufen möchtest : ")).strip()).capitalize
                    
                    while bank_waren[ware_name]['units'] == 0:  # falls eingegebene Ware ausverkauft ist
                        print(f"{ware_name} ist leider ausverkauft.")
                        ware_name = ((input("Gibt den Namen von der Ware ein, die du kaufen möchtest : ")).strip()).capitalize

                    units = (input(f"Wie viele {ware_name} möchtest du kaufen? Gibt eine Anzahl davon ein : ")).strip()

                    while units.isdigit() == False:         # falls Zeichen statt Zahlen als Units eingegeben werden
                        print("Gibt bitte NUR Zahlen ein!")
                        units = (input(f"Wie viele {ware_name} möchtest du kaufen? Gibt eine Anzahl davon ein : ")).strip()
                    
                    while int(units) <= 0 or int(units) > bank_waren[ware_name]["units"]:     # falls eingegebene Anzahl zu viel / wenig ist
                        print("Zu viele oder zu wenig Units eingegeben.")
                        units = (input(f"Wie viele {ware_name} möchtest du kaufen? Gibt eine Anzahl davon ein : ")).strip()

                    mein_konto_info = mein_konto(benutzername)  # Holt Konto-Info vom Server ab

                    kauf_info = kaufen(benutzername, ware_name, units)      # Schickt Kaufantrag am Server
                    print(" ")
                    print(kauf_info["message"])

                    bank_response = get_bank_waren()                # Holt Waren von der Bank nochmal ab, um aktuellste Preise zu erhalten
                    aktuelle_bank_waren = bank_response["stocks"]   # die Preise werden aktualisiert und man kauft etwas gleichzeitig => aktuellste Preise werden von Guthaben abgezogen 

                    # Konsole-UI
                    print(" ")
                    print("------------------- Kaufdetailsseite -------------------")
                    print("~ Kaufdetails ~")
                    print(f"gewählte Ware   : {ware_name}")
                    print(f"Units gekauft   : {units}")
                    print(f"Preis pro Ware  : {round((aktuelle_bank_waren[ware_name])['price'], 2)} POOSE-Bucks")
                    print(f"Gesamtpreis     : {round((int(units))*((aktuelle_bank_waren[ware_name])['price']), 2)} POOSE-Bucks")
                    print(" ")
                    print(f"aktuelle Guthaben       : {round(mein_konto_info['guthaben'], 2)} POOSE-Bucks")
                    print(f"Guthaben nach dem Kauf  : {round(mein_konto_info['guthaben'] - (int(units))*((aktuelle_bank_waren[ware_name])['price']), 2)} POOSE-Bucks")
                    print(" ")

                    print("")
                    exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

                    while exit != "":
                        exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

            except Exception as e:
                print(f"Fehler: {e}")

            print("")
            print("Warte kurz ... ")
            time.sleep(4)   # kurze Wartezeit zwischen Seiten
            
        # Verkaufseite (vom eigenen Inventar)
        elif wahl == "2":
            try:
                mein_konto_info = mein_konto(benutzername)      # Holt Konto-Info vom Server ab
                bank_response = get_bank_waren()                # Holt Waren von der Bank ab
                bank_waren = bank_response["stocks"]    
                
                # Konsole-UI
                print("------------------- Verkaufseite -------------------")
                print("Meine Hauptgüter ; ")
                print(" ")

                if mein_konto_info["isEmpty"]:  # falls keine Waren dem/r Nutzer*in gehören
                    print("Noch keine Waren!")

                else:
                    myInventar = mein_konto_info["inventar"]    # myInventar ist ein Dict mit Namen der Ware als key & ein Base-Model als value
                                                                # Base-Model enthält Namen, Preis und Anzahl der verfügbaren Ware

                    # alle Waren werden ausgedruckt
                    for name, myWare in myInventar.items():
                        print(f"Ware              : {name}")
                        print(f"gekaufter Preis   : {round((myInventar[name])['price'], 2)} POOSE-Bucks")
                        print(f"aktueller Preis   : {round((bank_waren[name])['price'], 2)} POOSE-Bucks")        # aktueller Preis einer Ware wird von der Bank abgeholt
                        print(f"Units             : {myWare['units']}")
                        print(" ")
                
                    print("ACHTUNG: Wenn du seit langem diese Seite nicht aktualisiert hat, werden die Preise aller Waren höchstwahrscheinlich unterschiedlich von den gezeigten Preisen.")
                    print("Gibt 0 ein, wenn du nichts verkaufen möchtest.")
                    ware_name = ((input("Gibt den Namen von der Ware ein, die du verkaufen möchtest : ")).strip()).capitalize()

                    # Wenn 0 eingegeben wird, verlässt der/die Nutzer*in die Verkaufseite 
                    if ware_name != "0":
                        while ware_name not in myInventar:      # falls eingegebener Name von Ware existiert nicht
                            print(f"{ware_name} existiert nicht.")
                            ware_name = ((input("Gibt den Namen von der Ware ein, die du verkaufen möchtest : ")).strip()).capitalize()

                        units = (input(f"Wie viele {ware_name} möchtest du verkaufen? Gibt eine Anzahl davon ein : ")).strip()

                        while units.isdigit() == False:         # falls Zeichen statt Zahlen eingegeben werden
                            print("Gibt bitte NUR Zahlen ein!")
                            units = (input(f"Wie viele {ware_name} möchtest du verkaufen? Gibt eine Anzahl davon ein : ")).strip()
                        
                        while int(units) <= 0 or int(units) > (myInventar[ware_name])["units"]:     # falls eingegebene Anzahl zu viel / wenig ist
                            print("Zu viele oder zu wenig Units eingegeben.")
                            units = (input(f"Wie viele {ware_name} möchtest du verkaufen? Gibt eine Anzahl davon ein : ")).strip()

                        verkauf_info = verkaufen(benutzername, ware_name, units)    # Schickt Verkaufantrag am Server
                        print(verkauf_info["message"])

                        bank_response = get_bank_waren()                # Holt Waren von der Bank nochmal ab, um aktuellste Preise zu erhalten
                        aktuelle_bank_waren = bank_response["stocks"]   # die Preise werden aktualisiert und man verkauft etwas gleichzeitig => aktuellste Preis + Guthaben 

                        # Konsole-UI
                        print(" ")
                        print("------------------- Verkaufdetailsseite -------------------")
                        print("~ Verkaufdetails ~")
                        print(f"gewählte Ware               : {ware_name}")
                        print(f"Units zu verkaufen          : {units}")
                        print(f"gekaufter Preis pro Ware    : {round((myInventar[ware_name])['price'], 2)} POOSE-Bucks")
                        print(f"aktueller Preis pro Ware    : {round((aktuelle_bank_waren[ware_name])['price'], 2)} POOSE-Bucks")
                        print("")
                        print(f"aktueller Gesamtpreis       : {round((int(units))*((aktuelle_bank_waren[ware_name])['price']), 2)} POOSE-Bucks")
                        print(f"Gewinn / Verlust            : {round((int(units))*(((aktuelle_bank_waren[ware_name])['price']) - (myInventar[ware_name])['price']), 0)} POOSE-Bucks")
                        print(" ")
                        print(f"aktuelle Guthaben           : {round(mein_konto_info['guthaben'], 2)} POOSE-Bucks")
                        print(f"Guthaben nach dem Verkauf   : {round(mein_konto_info['guthaben'] + (int(units))*((aktuelle_bank_waren[ware_name])['price']), 2)} POOSE-Bucks")
                        print(" ")

                        print("")
                        exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

                        while exit != "":
                            exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

            except Exception as e:
                print(f"Fehler : {e}")
            
            print("")
            print("Warte kurz ... ")
            time.sleep(4)   # kurze Wartezeit zwischen Seiten

        # Konto-Info-Seite
        elif wahl == "3":
            try:
                mein_konto_info = mein_konto(benutzername)      # Holt Konto-Info vom Server ab
                bank_response = get_bank_waren()                # Holt Waren von der Bank ab
                bank_waren = bank_response["stocks"]

                # Konsole-UI
                print("------------------- Konto-Info -------------------")
                print(f"Benutzername        : {konto_info['benutzername']}")
                print(f"POOSE-Bucks         : {round(mein_konto_info['guthaben'], 2)} POOSE-Bucks")    # Guthaben wird zu einer Ganzzahl aufgerundet

                print("Meine Waren ; ")
                print(" ")

                if mein_konto_info["isEmpty"]:      # falls keine Waren dem/r Nutzer*in gehören
                    print("Noch keine Waren!")

                else:
                    myInventar = mein_konto_info["inventar"]    # gleicher Code-Abschnitt wie oben

                    for name, myWare in myInventar.items():
                        print(f"Ware              : {name}")
                        print(f"gekaufter Preis   : {round((myInventar[name])['price'], 2)} POOSE-Bucks")
                        print(f"aktueller Preis   : {round((bank_waren[name])['price'], 2)} POOSE-Bucks")        # aktueller Preis einer Ware wird von der Bank abgeholt
                        print(f"Units             : {myWare['units']}")
                        print(" ")
            
                print("")
                print("ACHTUNG: Wenn du seit langem diese Seite nicht aktualisiert hat, werden die aktuellen Preise aller Waren höchstwahrscheinlich unterschiedlich von den gezeigten Preisen.")
                exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

                while exit != "":
                    exit = input("Druckt 'Enter', wenn du diese Seite verlassen möchtest. ")

            except Exception as e:
                print(f"Fehler: {e}")

            print("")
            print("Warte kurz ... ")
            time.sleep(4)

        # Logout - Ende des Programms
        elif wahl == "4":   
            print(" ")
            print("Ciao!")
            break

        else:   # falls der eingegebene Input anders als 1, 2, 3 oder 4 ist
            print("Ungültige Option. Bitte wähle 1, 2, 3 oder 4.")


if __name__ == "__main__":
    client()
