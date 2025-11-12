#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>


ESP8266WebServer server(80);
DNSServer dnsServer;

// global data shared across files
struct Account {
  String username;
  String password;
};
struct Settings {
  String ap_ssid;
  String ap_pass;
  int pin;
};
std::vector<Account> accounts;
Settings settings;

void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  loadAccounts();
  loadSettings();

  setupAP();
  setupCaptiveDNS(dnsServer);

  setupOTA();

  const char* headerKeys[] = { "Cookie" };
  size_t headerKeysCount = sizeof(headerKeys) / sizeof(char*);
  server.collectHeaders(headerKeys, headerKeysCount);


  registerAuthRoutes();
  registerUserRoutes();
  registerSettingsRoutes();
  registerPortalRoutes();
  //registerDebugRoute(); //#################### LEAKS PASSWORDS!!!!! #########################

  server.begin();
  Serial.println("Server started");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  handleOTA();
}
