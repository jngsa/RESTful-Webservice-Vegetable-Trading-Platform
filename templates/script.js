const BASE_URL = "http://localhost:8000";
let ware = null;
let benutzername = localStorage.getItem('benutzername');

// Überprüft, ob der Benutzer eingeloggt ist
function isLoggedIn() {
    return localStorage.getItem('benutzername') !== null;
}

// Ruft die verfügbaren Waren von der Bank ab und zeigt sie an
async function getWaren() {
    try {
        const response = await fetch(`${BASE_URL}/bank_waren/`);
        if (!response.ok) {
            throw new Error(`Fehler beim Empfangen der Waren vom Server: ${response.statusText}`);
        }

        const data = await response.json();
        const stocks = data.stocks;

        const stocksAnzeige = document.getElementById("stocks-anzeige");
        stocksAnzeige.innerHTML = "";

        for (const wareName in stocks) {
            const wareElement = document.createElement("li");
            wareElement.textContent = `${wareName}: ${stocks[wareName].units} verfügbar`;
            stocksAnzeige.appendChild(wareElement);
        }
    } catch (error) {
        console.error("Fehler beim Empfangen der Waren vom Server:", error);
    }
}

// Setzt die ausgewählte Ware
function setWare(selectedWare) {
    ware = selectedWare;
}

// Sucht nach einer Ware und zeigt deren Details an
async function suchen() {
    const suchInput = document.querySelector(".such-input");
    const suchWert = suchInput.value.trim();

    try {
        const response = await fetch(`${BASE_URL}/bank_waren/`);
        if (!response.ok) {
            throw new Error(`Fehler beim Empfangen der Waren vom Server: ${response.statusText}`);
        }

        const data = await response.json();
        const stocks = data.stocks;

        if (suchWert in stocks) {
            setWare(suchWert);
            document.querySelector(".price-value").textContent = stocks[suchWert].price;
            document.querySelector(".units-value").textContent = stocks[suchWert].units;
        } else {
            setWare(null);
            document.querySelector(".price-value").textContent = "0";
            document.querySelector(".units-value").textContent = "0";
        }
    } catch (error) {
        console.error("Fehler beim Suchen der Ware:", error);
    }
}

// Ruft das Inventar des Benutzers ab und zeigt es an
async function getInventar() {
    const inventarAnzeige = document.getElementById("inventar-anzeige");
    const loginMessage = document.getElementById("login-message");

    if (isLoggedIn()) {
        loginMessage.style.display = "none";
        inventarAnzeige.style.display = "block";

        try {
            const response = await fetch(`${BASE_URL}/mein_konto/?benutzername=${benutzername}`);
            if (!response.ok) {
                throw new Error(`Fehler beim Empfangen des Inventars vom Server: ${response.statusText}`);
            }

            const data = await response.json();
            const inventar = data.inventar;

            inventarAnzeige.innerHTML = "";

            for (const wareName in inventar) {
                const wareElement = document.createElement("li");
                wareElement.textContent = `${wareName}: ${inventar[wareName].units} Stück (Letzter Kaufpreis: ${inventar[wareName].price}€)`;
                inventarAnzeige.appendChild(wareElement);
            }
        } catch (error) {
            console.error("Fehler beim Empfangen des Inventars vom Server:", error);
        }
    } else {
        loginMessage.style.display = "block";
        inventarAnzeige.style.display = "none";
    }
}

// Kauft eine Ware
async function kaufen_func() {
    const menge = parseInt(document.querySelector(".buy-amount").value);

    if (ware) {
        try {
            const response = await fetch(`${BASE_URL}/kaufen/`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({ benutzername, ware_name: ware, units: menge }),
            });

            if (response.status === 400) {
                const errorData = await response.json();
                console.error("Fehler beim Kaufen:", errorData.detail);
            } else if (!response.ok) {
                throw new Error(`Fehler beim Kaufen: ${response.statusText}`);
            }

            const data = await response.json();
            console.log(data.message);

            document.querySelector(".buy-amount").value = "1";
            getWaren();
            suchen();
        } catch (error) {
            console.error("Fehler beim Kaufen:", error);
        }
    } else {
        console.error("Keine Ware ausgewählt.");
    }
}

// Verkauft eine Ware
async function verkaufen_func() {
    const menge = parseInt(document.querySelector(".sell-amount").value);

    if (ware) {
        try {
            const response = await fetch(`${BASE_URL}/verkaufen/`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({ benutzername, ware_name: ware, units: menge }),
            });

            if (response.status === 400) {
                const errorData = await response.json();
                console.error("Fehler beim Verkaufen:", errorData.detail);
            } else if (!response.ok) {
                throw new Error(`Fehler beim Verkaufen: ${response.statusText}`);
            }

            const data = await response.json();
            console.log(data.message);

            document.querySelector(".sell-amount").value = "1";
            getWaren();
            suchen();
        } catch (error) {
            console.error("Fehler beim Verkaufen:", error);
        }
    } else {
        console.error("Keine Ware ausgewählt.");
    }
}

// Event-Listener für die Suchleiste
document.querySelector(".such-input").addEventListener("keypress", function (event) {
    if (event.key === "Enter") {
        suchen();
    }
});

// Event-Listener für den Kaufen-Button
document.querySelector(".buy-button").addEventListener("click", kaufen_func);

// Event-Listener für den Verkaufen-Button
document.querySelector(".sell-button").addEventListener("click", verkaufen_func);

// Event-Listener für Änderungen des Login-Status
window.addEventListener('storage', function (event) {
    if (event.key === 'benutzername') {
        benutzername = localStorage.getItem('benutzername');
        getWaren();
    }
});

// Initiale Anzeige der Waren
getWaren();