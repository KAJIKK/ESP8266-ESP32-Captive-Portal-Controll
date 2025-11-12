bool parseCookie(const String &cookie, String &user, String &pass) {
  user = pass = "";
  int u = cookie.indexOf("user=");
  int p = cookie.indexOf("pass=");
  if (u == -1 || p == -1) return false;
  user = cookie.substring(u + 5, cookie.indexOf(';', u + 5));
  pass = cookie.substring(p + 5, cookie.indexOf(';', p + 5));
  if (user.endsWith("\r") || user.endsWith("\n")) user.trim();
  if (pass.endsWith("\r") || pass.endsWith("\n")) pass.trim();
  return true;
}

bool checkCredentials(const String &u, const String &p) {
  for (auto &a : accounts)
    if (a.username == u && a.password == p) return true;
  return false;
}

bool isAdmin(const String &u) {
  return (u == "admin");
}

bool getAuth(String &u, String &p) {
  String cookie = server.header("Cookie");
  return parseCookie(cookie, u, p) && checkCredentials(u, p);
}

// --- ROUTES ---
void registerAuthRoutes() {
  server.on("/login", HTTP_GET, []() {
    server.send(200, "text/html; charset=UTF-8", loginPage());
  });

  server.on("/login", HTTP_POST, []() {
    String u = server.arg("user");
    String p = server.arg("pass");
    if (checkCredentials(u, p)) {
      // Set cookies (stateless auth)
      String setCookie = "user=" + u + "; Path=/";
      server.sendHeader("Set-Cookie", setCookie);
      String setCookie2 = "pass=" + p + "; Path=/";
      server.sendHeader("Set-Cookie", setCookie2);
      server.sendHeader("Location", String("http://192.168.4.1"), true);
      server.send(302, "text/plain", "");
    } else server.send(403, "text/html; charset=UTF-8", "<h3>Neplatné uživatelské údaje</h3>");
  });

  server.on("/logout", HTTP_GET, []() {
    server.send(200, "text/html; charset=UTF-8", "<script>document.cookie='user=;Max-Age=0;path=/';"
                                  "document.cookie='pass=;Max-Age=0;path=/';"
                                  "window.location='/login'</script>");
  });
}
