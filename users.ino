void registerUserRoutes() {
  // List all users
  server.on("/users", HTTP_GET, []() {
    String u, p;
    if (!getAuth(u, p) || !isAdmin(u)) {
      server.send(403, "text/html; charset=UTF-8", "<h3>Přístup odepřen</h3>");
      return;
    }
    server.send(200, "text/html; charset=UTF-8", usersPage());
  });

  // Add user
  server.on("/users/add", HTTP_POST, []() {
    String u, p;
    if (!getAuth(u, p) || !isAdmin(u)) {
      server.send(403, "text/plain", "Přístup odepřen");
      return;
    }

    String newUser = server.arg("newuser");
    String newPass = server.arg("newpass");

    if (newUser.length() == 0 || newPass.length() == 0) {
      server.send(400, "text/html; charset=UTF-8", "<script>alert('Udaje nemůžou být prázdné');window.location='/users';</script>");
      return;
    }

    for (auto &a : accounts) {
      if (a.username == newUser) {
        server.send(400, "text/html; charset=UTF-8", "<script>alert('Uživatel již existuje');window.location='/users';</script>");
        return;
      }
    }

    accounts.push_back({ newUser, newPass });
    saveAccounts();
    server.sendHeader("Location", "/users");
    server.send(302);
  });

  // Delete user
  server.on("/users/delete", HTTP_POST, []() {
    String u, p;
    if (!getAuth(u, p) || !isAdmin(u)) {
      server.send(403, "text/plain", "Přístup odepřen");
      return;
    }

    String del = server.arg("deluser");
    if (del == "admin") {
      server.send(400, "text/html; charset=UTF-8", "<script>alert('Nelze smazat admina');window.location='/users';</script>");
      return;
    }

    for (int i = 0; i < accounts.size(); i++) {
      if (accounts[i].username == del) {
        accounts.erase(accounts.begin() + i);
        saveAccounts();
        break;
      }
    }
    server.sendHeader("Location", "/users");
    server.send(302);
  });

  // ==== Change Password Page ====
  server.on("/changepass", HTTP_GET, []() {
    String user, pass;
    if (!getAuth(user, pass)) {
      server.sendHeader("Location", "/login");
      server.send(302, "text/plain", "");
      return;
    }

    String html = "<!doctype html><html><head>"
                  "<meta charset='UTF-8'>"
                  "<meta name='viewport' content='width=device-width,initial-scale=1'>";
    html += styleCSS();
    html += "</head><body><div class='card'>";
    html += "<h2>Změnit heslo</h2>";
    html += "<form method='POST' action='/changepass'>";
    html += "<label>Uživatelské jméno:</label><br>";
    html += "<input type='text' name='user' value='" + user + "' readonly><br>";
    html += "<label>Nové heslo:</label><br>";
    html += "<input type='password' placeholder='Nové heslo' name='newpass' required><br>";
    html += "<button type='submit' class='button primary'>Změnit</button>";
    html += "<a class='back-btn' href='/'> &larr; Zpět</a></div></body></html>";
    html += "</form></div></body></html>";

    server.send(200, "text/html; charset=UTF-8", html);
  });

  // Change password (self or admin changes another user)
  server.on("/changepass", HTTP_POST, []() {
    String u, p;
    if (!getAuth(u, p)) {
      server.send(403, "text/plain", "Přístup odepřen");
      return;
    }

    String target = server.arg("user");
    String newpass = server.arg("newpass");

    if (!isAdmin(u) && target != u) {
      server.send(403, "text/plain; charset=UTF-8", "Můžete měnit pouze svoje heslo");
      return;
    }

    for (auto &a : accounts) {
      if (a.username == target) {
        a.password = newpass;
        saveAccounts();
        server.send(200, "text/html; charset=UTF-8", "<script>alert('Heslo změněno');window.location='/'</script>");
        if (isAdmin(u)) {
          setOTApassword();
        }
        return;
      }
    }
    server.send(404, "text/html; charset=UTF-8", "<h3>Uživatel neexistuje</h3>");
  });
}

String usersPage() {
  String h = "<!doctype html><html><head>"
             "<meta charset='UTF-8'>"
             "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += styleCSS();
  h += "</head><body><div class='card'><h2>Správa Uživatelů</h2>";

  h += "<table style='width:100%;text-align:left;margin-bottom:10px'>";
  for (auto &a : accounts) {
    h += "<tr><td>" + a.username + "</td><td>";
    if (a.username != "admin")
      h += "<form method='POST' action='/users/delete' style='display:inline'>"
           "<input type='hidden' name='deluser' value='"
           + a.username + "'>"
                          "<button class='delete-btn' type='submit'>Smazat</button></form>";
    else
      h += "<span style='color:#888;font-style: italic'>Admina nelze smazat</span>";
    h += "</td></tr>";
  }
  h += "</table>";

  // Add new user
  h += "<h3>Přidat Uživatele</h3>"
       "<form method='POST' action='/users/add'>"
       "<input name='newuser' placeholder='Nový uživatel' required><br>"
       "<input name='newpass' placeholder='Heslo' type='password' required><br>"
       "<button type='submit'>Přidat</button>"
       "</form>";

  // Change password
  h += "<h3>Změnit heslo uživatele</h3>"
       "<form method='POST' action='/changepass'>"
       "<input name='target' placeholder='Uživatelké jméno' required><br>"
       "<input name='newpw' placeholder='Nové heslo' type='password' required><br>"
       "<button type='submit'>Změnit</button>"
       "</form>";

  h += "<a class='back-btn' href='/'> &larr; Zpět</a></div></body></html>";
  return h;
}
