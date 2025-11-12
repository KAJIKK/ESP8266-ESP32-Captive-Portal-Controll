String styleCSS() {
  return R"rawliteral(
  <style>
    body {
      background-color: #121212;
      color: #e0e0e0;
      font-family: 'Segoe UI', Roboto, sans-serif;
      text-align: center;
      margin: 0;
      padding: 0;
    }
    .card {
      background: #1e1e1e;
      border-radius: 12px;
      box-shadow: 0 4px 20px rgba(0,0,0,0.4);
      max-width: 360px;
      margin: 40px auto;
      padding: 30px;
    }
button, .back-btn, a.button-link {
  display: block;
  width: 90%;
  max-width: 300px;
  margin: 15px auto;
  padding: 20px 0;
  font-size: 1.4em;
  border-radius: 12px;
  border: none;
  text-align: center;
  text-decoration: none;
  cursor: pointer;
  transition: none; /* remove hover scaling */
}

input {
  width: 90%;
  max-width: 320px;
  padding: 16px 12px;       /* bigger touch area */
  margin: 12px 0;           /* space between inputs */
  font-size: 1.1em;         /* larger, readable text */
  border-radius: 8px;
  border: 1px solid #444;
  background-color: #2a2a2a;
  color: #fff;
  box-sizing: border-box;
}

.button.danger {
  background-color: #b33;
  color: white;
  font-size: 1.1em;
  padding: 16px 24px;
  margin-top: 12px;
  border-radius: 10px;
}

.button.danger:active {
  background-color: #900;
}


.toggle-btn {
  background: #00C853;
  color: #fff;
  font-weight: bold;
}

.toggle-btn.on {
  background: #E53935;
}

button, .toggle-btn {
  box-shadow: 0 4px 10px rgba(0,0,0,0.3);
}

.delete-btn {
  background: #E53935;
  color: white;
  font-size: 1.1em;       /* slightly smaller */
  padding: 12px 0;        /* slightly less tall */
  border-radius: 8px;
  margin: 10px auto;
  width: 80%;             /* narrower than main buttons */
  display: block;
  box-shadow: 0 3px 6px rgba(0,0,0,0.3);
}


.back-btn, a.button-link {
  background: #757575;
  color: white;
  font-size: 1.2em;
}
  </style>
  )rawliteral";
}



String mainPage(const String &user, bool pinState) {
  String h = "<!doctype html><html><head>"
             "<meta charset='UTF-8'>"
             "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += styleCSS();
  h += "</head><body><div class='card'>";
  h += "<h2>Vítej, " + user + "</h2>";
  h += "<p>Garáž je momentálně <strong>" + String(pinState ? "OTEVŘENÁ" : "ZAVŘENÁ") + "</strong></p>";

  // Big toggle button
  h += "<form method='POST' action='/toggle'>";
  h += "<button class='toggle-btn " + String(pinState ? "on" : "") + "'>";
  h += pinState ? "ZAVŘÍT" : "OTEVŘÍT";
  h += "</button></form>";

  // Admin buttons (full-width)
  if (user == "admin") {
    h += "<a class='button-link' href='/users'>👥 Správa Uživatelů</a>";
    h += "<a class='button-link' href='/settings'>⚙️ Nastavení</a>";
  }

  h += "<a href='/changepass' class='button-link'>🔑 Změnit heslo</a>";


  // Logout / back button
  h += "<a class='back-btn' href='/logout'>Odhlásit se</a>";

  h += "<div class='footer'>" + settings.ap_ssid + "</div></div></body></html>";
  return h;
}


String loginPage() {
  String h = "<!doctype html><html><head>"
             "<meta charset='UTF-8'>"
             "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += styleCSS();
  h += "</head><body><div class='card'><h2>" + settings.ap_ssid + "</h2>";
  //if (msg.length()) h += "<p style='color:#E53935'>" + msg + "</p>";
  h += "<form method='POST' action='/login'>";
  h += "<input name='user' placeholder='Uživatelské jméno'><br>";
  h += "<input name='pass' type='password' placeholder='Heslo'><br>";
  h += "<button>Přihlásit se</button></form>";
  h += "</div></body></html>";
  return h;
}
