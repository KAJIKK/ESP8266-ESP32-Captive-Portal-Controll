# 🚪 ESP8266 Captive Portal with User System, Admin Panel & OTA Updates

A modern **ESP8266-based WiFi Access Point** that serves a **captive portal** with user authentication, admin controls, pin control, and **OTA (Over-The-Air)** firmware updates — all wrapped in a clean mobile-friendly dark UI.

---

## ✨ Features

### 🔐 User Management
- Built-in **admin account** (`admin / admin`) created on first boot.
- Admin can **create and delete users** directly from the web interface.
- User accounts are stored in flash memory and **persist across reboots**.
- Each user can **change their own password** securely via the `/changepass` page.

### 🌐 Captive Portal Access Point
- The ESP8266 creates a standalone WiFi network (default SSID `ESP-Captive-Portal`).
- Any connected device is redirected to a login page automatically.
- After logging in, users see the main control panel.

### ⚙️ Admin Panel
- Dedicated **admin-only** pages:
  - `/users` → Manage user accounts.
  - `/settings` → Change AP name, password, and system configuration.
  - `/restart` → Manually reboot the device.
- Automatic OTA password synchronization with the admin password.
- `/debug` page shows cookies, account JSON, and other useful runtime info (LEAKS PASSWORD, KEEP DISABLED!!!).

### 🖲️ GPIO Control
- Main portal page has a large toggle button that controls **D4 (GPIO2)**.
- Real-time pin state feedback with a clear on/off indicator.

### 🛠️ OTA Updates
- Full **ArduinoOTA** integration.
- OTA password automatically matches the current admin password.
- Works even when connected directly to the ESP’s AP — no internet needed.
- Update directly from the Arduino IDE via **Network Port** or IP (e.g. `192.168.4.1`).

### 🧠 Persistent Configuration
- All settings (users, AP SSID/password) stored in flash memory.
- Automatically reloaded at startup.

### 🎨 Responsive Dark Mode UI
- Optimized for **mobile** and **desktop**.
- Large touch-friendly buttons.
- Red “danger” buttons for destructive actions.
- UTF-8 emoji icons (with fallback entities for reliability).

---

## 📦 Requirements

- **Hardware:** ESP8266 (e.g. NodeMCU, Wemos D1 Mini)
- **Libraries:**
  - `ESP8266WiFi.h`
  - `ESP8266WebServer.h`
  - `DNSServer.h`
  - `ArduinoJson.h`
  - `ArduinoOTA.h`
  - `LittleFS.h` (for flash storage)

Tested on ESP8266EX with 4MB flash.

---

## 🚀 Setup & Usage

1. **Clone or download** this repository into your Arduino projects folder.
2. Open the `.ino` in the Arduino IDE.
3. Select the correct board (**NodeMCU 1.0 / ESP8266**) and COM port.
4. **Upload the code via serial** for the first time.
5. After boot:
   - The ESP creates an AP named `ESP-Captive-Portal`.
   - Connect with your phone or laptop (password defaults to blank).
   - You’ll be redirected to the captive login page (if not go to http://192.168.4.1).
6. Login with:
   - Username: admin
   - Password: admin
7. Explore:
- Toggle the GPIO pin.
- Change passwords.
- Create new users.
- Access `/settings` to rename the AP or restart the ESP.
8. For OTA updates:
- Connect your PC to the ESP’s AP.
- In Arduino IDE → **Port** → choose `Network Port: ESP-Captive-Portal at 192.168.4.1`.
- Upload as usual.

---



## 🔧 Project Structure

    /ESP_CaptivePortal/
    ├── main.ino # Main setup & loop
    ├── auth.ino # Cookie auth
    ├── ui.ino # You would never guess what this file does
    ├── users.ino # User management (admin-only)
    ├── settings.ino # System settings + restart endpoint (admin-only)
    ├── storage.ino
    ├── portal.ino # Captive portal logic
    ├── ota.ino # ArduinoOTA setup & restart logic
    └── debug.ino # Debug info and cookie inspector




---

## 🔒 Security Notes
- This system uses cookies for authentication (username + password in plain text).
- Designed for **local AP use** (not for Internet-facing deployment).
- OTA uploads are protected with the **same password as the admin account**.
- To enhance security, you can easily:
  - Enable HTTPS with an external proxy.
  - Add hashing for stored passwords (MD5 or SHA256).

---

## ❤️ Credits & Inspiration
Inspired by community ESP8266 captive portal projects, merged with a custom authentication and OTA management system written from scratch.

---

## 📸 Screenshots (Optional)
<img width="461" height="436" alt="Snímek obrazovky z 2025-11-13 00-09-12" src="https://github.com/user-attachments/assets/143d7f55-cbb7-4039-ac89-86b02dac29e0" /><img width="463" height="645" alt="Snímek obrazovky z 2025-11-13 00-07-10" src="https://github.com/user-attachments/assets/ea483cb6-4987-4619-9627-3a1ba9c2171a" />
<img width="462" height="769" alt="Snímek obrazovky z 2025-11-13 00-08-59" src="https://github.com/user-attachments/assets/7300b9ed-e67e-4d7e-9f64-8a49d5fb9e20" /><img width="464" height="930" alt="Snímek obrazovky z 2025-11-13 00-08-33" src="https://github.com/user-attachments/assets/5ea244d7-d263-4d72-9b15-eb6b96868cf5" />

---

## 🧰 Future Improvements
- Password hashing for enhanced security
- Built-in file manager for web content
- Configurable GPIO mapping
- OTA status display on web UI
- English UI

---

## 📄 License
This project is open source and released under the **AGPLv3 License**.

---

> ✨ _A simple but powerful captive portal and control system for your ESP8266. Ideal for IoT garage control, local WiFi access, and secure multi-user setups._

