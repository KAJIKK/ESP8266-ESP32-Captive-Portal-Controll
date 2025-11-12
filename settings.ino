void registerSettingsRoutes() {
  // Display settings page
  server.on("/settings", HTTP_GET, []() {
    String u, p;
    if (!getAuth(u, p) || !isAdmin(u)) {
      server.send(403, "text/html; charset=UTF-8", "<h3>Přístup odepřen</h3>");
      return;
    }
    server.send(200, "text/html; charset=UTF-8", settingsPage());
  });

  // Save settings
  server.on("/settings", HTTP_POST, []() {
    String u, p;
    if (!getAuth(u, p) || !isAdmin(u)) {
      server.send(403, "text/html; charset=UTF-8", "<h3>Přístup odepřen</h3>");
      return;
    }

    settings.ap_ssid = server.arg("ap_ssid");
    settings.ap_pass = server.arg("ap_pass");
    settings.pin = server.arg("pin").toInt();
    saveSettings();

    // Auto-reboot after short delay
    server.send(200, "text/html; charset=UTF-8",
                "<script>"
                "alert('Settings saved. ESP will reboot to apply changes.');"
                "setTimeout(function(){ window.location='/'; }, 2000);"
                "</script>");

    Serial.println("Rebooting ESP to apply new settings...");
    delay(2000);  // allow browser to process
    ESP.restart();
  });

  // Admin-only manual restart endpoint
  server.on("/restart", HTTP_POST, []() {
    String user, pass;
    // getAuth() parses cookie and verifies credentials; it returns true only if credentials are valid
    if (!getAuth(user, pass) || !isAdmin(user)) {
      // not authenticated or not admin
      server.send(403, "text/html; charset=UTF-8", "<!doctype html><html><body><h3>Přístup odepřen</h3><p>Pouze pro admina.</p></body></html>");
      return;
    }

    // Authenticated admin — respond to browser first so it sees the message
    server.send(200, "text/html; charset=UTF-8",
                "<!doctype html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'></head>"
                "<body style='font-family:sans-serif;text-align:center;padding:20px;'><h3>Restartování...</h3>"
                "<p>Zařízení se restartuje</p></body></html>");

    // Small delay to let the HTTP response go out
    delay(750);

    // Restart device
    ESP.restart();
  });
}

String settingsPage() {
  String h = "<!doctype html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += styleCSS();
  h += "</head><body><div class='card'><h2>Nastavení</h2>";
  h += "<form method='POST' action='/settings'>"
       "AP SSID:<br><input name='ap_ssid' value='"
       + settings.ap_ssid + "' required><br>"
                            "Heslo k AP:<br><input name='ap_pass' value='"
       + settings.ap_pass + "'><br>"
                            "Pin relátka (GPIO):<br><input name='pin' type='number' value='"
       + String(settings.pin) + "' required><br>"
                                "<button type='submit'>Uložit</button></form>";
  h += "<a class='back-btn' href='/'> &larr; Zpět</a></div></body></html>";
  h += "<form action='/restart' method='POST' style='margin-top:20px;'>";
  h += "<button type='submit' class='button danger'>🔁 Manuální restart</button>";
  h += "</form>";

  return h;
}
