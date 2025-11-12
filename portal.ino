#define DNS_PORT 53
IPAddress AP_IP(192,168,4,1);

void setupAP() {
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255,255,255,0));
  WiFi.softAP(settings.ap_ssid.c_str(), settings.ap_pass.c_str());
  pinMode(settings.pin, OUTPUT);
  digitalWrite(settings.pin, LOW);
  Serial.println("AP started: " + settings.ap_ssid);
}

void setupCaptiveDNS(DNSServer &dns) {
  dns.start(DNS_PORT, "*", AP_IP);
}

void registerPortalRoutes() {
  server.on("/", HTTP_GET, []() {
    String u, p;
    if (!getAuth(u, p)) { server.sendHeader("Location", "/login"); server.send(302); return; }
    server.send(200, "text/html; charset=UTF-8", mainPage(u, digitalRead(settings.pin)));
  });

  server.on("/toggle", HTTP_POST, []() {
    String u, p;
    if (!getAuth(u, p)) { server.send(403, "text/plain", "Přístup odepřen"); return; }
    digitalWrite(settings.pin, !digitalRead(settings.pin));
    server.sendHeader("Location", "/");
    server.send(302);
  });

  // Captive portal redirect
  server.on("/generate_204", [](){ server.sendHeader("Location", String("http://") + AP_IP.toString()); server.send(302); });
}
