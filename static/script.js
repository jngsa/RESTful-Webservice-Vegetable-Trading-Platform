$(document).ready(function() {
    // Funktion zum Einloggen/Registrieren
    $(".konto-button").click(function() {
        var benutzername = prompt("Benutzername:");
        var passwort = prompt("Passwort:");
        
        $.ajax({
            url: "http://127.0.0.1:8000/login/",
            method: "POST",
            data: JSON.stringify({
                benutzername: benutzername,
                passwort: passwort
            }),
            contentType: "application/json",
            success: function(response) {
                alert(response.message);
                // Hier können Sie weitere Aktionen nach erfolgreichem Login durchführen
            },
            error: function(xhr, status, error) {
                alert("Fehler beim Login: " + xhr.responseJSON.detail);
            }
        });
    });

    // Funktion zum Kaufen
    $(".buy-button").click(function() {
        var ware_name = prompt("Welche Ware möchten Sie kaufen?");
        var units = prompt("Wie viele Einheiten?");
        
        $.ajax({
            url: "http://127.0.0.1:8000/kaufen/",
            method: "POST",
            data: JSON.stringify({
                benutzername: "AKTUELLER_BENUTZERNAME", // Dies müssen Sie anpassen
                ware_name: ware_name,
                units: parseInt(units)
            }),
            contentType: "application/json",
            success: function(response) {
                alert(response.message);
            },
            error: function(xhr, status, error) {
                alert("Fehler beim Kauf: " + xhr.responseJSON.detail);
            }
        });
    });

    // Funktion zum Abrufen und Anzeigen von Waren
    function getAndDisplayWaren() {
        $.ajax({
            url: "http://127.0.0.1:8000/bank_waren/",
            method: "GET",
            success: function(response) {
                var warenListe = "";
                for (var ware in response.stocks) {
                    warenListe += ware + ": " + response.stocks[ware].price + " EUR, " + response.stocks[ware].units + " Einheiten<br>";
                }
                $(".graph-container").html(warenListe);
            },
            error: function(xhr, status, error) {
                alert("Fehler beim Abrufen der Waren: " + error);
            }
        });
    }

    // Waren beim Laden der Seite anzeigen
    getAndDisplayWaren();
});