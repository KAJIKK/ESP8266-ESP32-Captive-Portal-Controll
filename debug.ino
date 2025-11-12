//#################### LEAKS PASSWORDS!!!!! #########################

void registerDebugRoute() {
  server.on("/debug", HTTP_GET, []() {
    String cookie = server.header("Cookie");
    String u, p;
    parseCookie(cookie, u, p);
    String html = "<html><body><pre>";
    html += "Raw Cookie: " + cookie + "\n";
    html += "Parsed user: " + u + "\n";
    html += "Parsed pass: " + p + "\n";
    html += "Auth valid: " + String(checkCredentials(u, p) ? "YES" : "NO") + "\n\n";
    html += "Accounts:\n";
    for (auto &a : accounts) html += a.username + ":" + a.password + "\n";
    html += "</pre><a href='/'>Back</a></body></html>";
    server.send(200, "text/html", html);
  });
}
