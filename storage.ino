void loadAccounts() {
  if (!LittleFS.exists("/accounts.json")) {
    File f = LittleFS.open("/accounts.json", "w");
    f.print("[{\"username\":\"admin\",\"password\":\"admin\"}]");
    f.close();
  }
  File f = LittleFS.open("/accounts.json", "r");
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, f);
  f.close();
  accounts.clear();
  for (JsonObject u : doc.as<JsonArray>()) {
    accounts.push_back({u["username"].as<String>(), u["password"].as<String>()});
  }
}

void saveAccounts() {
  DynamicJsonDocument doc(1024);
  JsonArray arr = doc.to<JsonArray>();
  for (auto &a : accounts) {
    JsonObject o = arr.createNestedObject();
    o["username"] = a.username;
    o["password"] = a.password;
  }
  File f = LittleFS.open("/accounts.json", "w");
  serializeJson(arr, f);
  f.close();
}

void loadSettings() {
  if (!LittleFS.exists("/settings.json")) {
    settings.ap_ssid = "ESP-Captive-Portal";
    settings.ap_pass = "";
    settings.pin = 4;
    saveSettings();
    return;
  }
  File f = LittleFS.open("/settings.json", "r");
  DynamicJsonDocument doc(512);
  deserializeJson(doc, f);
  f.close();
  settings.ap_ssid = doc["ap_ssid"] | "ESP-Captive-Portal";
  settings.ap_pass = doc["ap_pass"] | "";
  settings.pin = doc["pin"] | 4;
}

void saveSettings() {
  DynamicJsonDocument doc(512);
  doc["ap_ssid"] = settings.ap_ssid;
  doc["ap_pass"] = settings.ap_pass;
  doc["pin"] = settings.pin;
  File f = LittleFS.open("/settings.json", "w");
  serializeJson(doc, f);
  f.close();
}
