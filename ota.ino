void setupOTA() {
  ArduinoOTA.setHostname(settings.ap_ssid.c_str());
  setOTApassword();

  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update Starting...");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Update Complete");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();

  Serial.println("OTA Ready");
  Serial.print("Hostname: ");
  Serial.println(ArduinoOTA.getHostname());
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void setOTApassword() {
  // Find admin password dynamically
  String adminPass = "admin";  // fallback default
  for (auto &a : accounts) {
    if (a.username == "admin") {
      adminPass = a.password;
      break;
    }
  }

  ArduinoOTA.setPassword(adminPass.c_str());  // ✅ use .c_str() to convert String → const char*
  Serial.print("OTA Password (same as admin): ");
  Serial.println(adminPass);
}


void handleOTA() {
  ArduinoOTA.handle();
}
