const BASE_URL = "http://localhost:8000";

// Erstellt ein neues Konto
async function createKonto(benutzername, passwort) {
    try {
        const response = await fetch(`${BASE_URL}/create_konto/?benutzername=${encodeURIComponent(benutzername)}&passwort=${encodeURIComponent(passwort)}`, {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
        });

        const data = await response.json();
        if (!response.ok) {
            throw new Error(data.message || data.detail || `Fehler beim Erstellen des Kontos: ${response.statusText}`);
        }

        localStorage.setItem('benutzername', data.benutzername);
        window.location.href = 'index.html';
        
        if (typeof getInventar === 'function') {
            await getInventar();
        }
        
        return data;
    } catch (error) {
        console.error("Fehler beim Erstellen des Kontos:", error);
        document.getElementById("register-error").textContent = error.message;
    }
}

// Loggt einen Benutzer ein
async function login(benutzername, passwort) {
    try {
        const response = await fetch(`${BASE_URL}/login/?benutzername=${encodeURIComponent(benutzername)}&passwort=${encodeURIComponent(passwort)}`, {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
        });

        const data = await response.json();
        if (!response.ok) {
            throw new Error(data.message || data.detail || `Fehler beim Einloggen: ${response.statusText}`);
        }

        localStorage.setItem('benutzername', data.benutzername);
        window.location.href = 'index.html';
        
        if (typeof getInventar === 'function') {
            await getInventar();
        }
        
        return data;
    } catch (error) {
        console.error("Fehler beim Einloggen:", error);
        document.getElementById("login-error").textContent = error.message;
    }
}

// Event-Listener für das Login-Formular
document.querySelector(".login-form").addEventListener("submit", async (event) => {
    event.preventDefault();
    const benutzername = event.target.elements[0].value;
    const passwort = event.target.elements[1].value;
    await login(benutzername, passwort);
});

// Event-Listener für das Registrierungsformular
document.querySelector(".register-form").addEventListener("submit", async (event) => {
    event.preventDefault();
    const benutzername = event.target.elements[0].value;
    const passwort = event.target.elements[1].value;
    await createKonto(benutzername, passwort);
});