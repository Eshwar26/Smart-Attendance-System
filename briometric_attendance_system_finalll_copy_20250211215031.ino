// #include <Arduino.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>

// // Pin Definitions for I2C LCD
// #define I2C_SDA D2        // GPIO4 - LCD SDA connection
// #define I2C_SCL D1        // GPIO5 - LCD SCL connection

// // Pin Definitions for AS608/AS-68ML Fingerprint Sensor
// #define FINGERPRINT_RX D6  // GPIO12 - Connect to Yellow wire (RX)
// #define FINGERPRINT_TX D5  // GPIO14 - Connect to White wire (TX)

// // Initialize devices
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// SoftwareSerial mySerial(FINGERPRINT_TX, FINGERPRINT_RX);
// Adafruit_Fingerprint finger(&mySerial);

// char choice = '0';
// uint8_t lastId = 0;  // Track the last used ID

// // Helper function to print both to Serial and LCD
// void displayMessage(const char *line1, const char *line2) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(line1);
//     lcd.setCursor(0, 1);
//     lcd.print(line2);
//     Serial.print("LCD Display - Line 1: ");
//     Serial.println(line1);
//     Serial.print("LCD Display - Line 2: ");
//     Serial.println(line2);
// }

// // Fingerprint enrollment
// boolean getFingerprintEnroll() {
//     uint8_t id = lastId + 1;  // Increment ID for new fingerprint
//     Serial.print("Enrolling ID: ");
//     Serial.println(id);
    
//     // First fingerprint capture
//     displayMessage("Place finger", "on sensor");
//     while (finger.getImage() != FINGERPRINT_OK) {
//         displayMessage("Waiting...", "Place finger");
//         delay(500);
//     }

//     // Convert first image to template
//     if (finger.image2Tz(1) != FINGERPRINT_OK) {
//         displayMessage("Template Err", "Try again");
//         return false;
//     }

//     displayMessage("Remove finger", "please");
//     delay(2000);
//     while (finger.getImage() != FINGERPRINT_NOFINGER) delay(100);

//     // Second fingerprint capture
//     displayMessage("Place same", "finger again");
//     while (finger.getImage() != FINGERPRINT_OK) {
//         displayMessage("Waiting...", "Place same finger");
//         delay(500);
//     }

//     // Convert second image to template
//     if (finger.image2Tz(2) != FINGERPRINT_OK) {
//         displayMessage("Template Err", "Try again");
//         return false;
//     }

//     // Create and store model
//     if (finger.createModel() != FINGERPRINT_OK) {
//         displayMessage("Model Error", "Try again");
//         return false;
//     }
//     if (finger.storeModel(id) != FINGERPRINT_OK) {
//         displayMessage("Store Error", "Try again");
//         return false;
//     }

//     lastId = id;  // Update last used ID
//     displayMessage("Enroll Success!", ("ID: " + String(id)).c_str());
//     delay(2000);
//     return true;
// }

// // Fingerprint verification
// void getFingerprintID() {
//     uint8_t p = finger.getImage();
//     if (p != FINGERPRINT_OK) {
//         displayMessage("No Finger", "Detected");
//         return;
//     }

//     // Convert image to template and search
//     if (finger.image2Tz() != FINGERPRINT_OK) {
//         displayMessage("Image Error", "Try Again");
//         return;
//     }

//     p = finger.fingerFastSearch();
//     if (p == FINGERPRINT_OK) {
//         displayMessage("Hello, ID", String(finger.fingerID).c_str());
//         Serial.print("Found ID: ");
//         Serial.println(finger.fingerID);
//     } else {
//         displayMessage("No Match", "Found");
//         Serial.println("No match found.");
//     }
//     delay(2000);
// }

// void setup() {
//     Serial.begin(115200);
//     Wire.begin(I2C_SDA, I2C_SCL);
//     lcd.init();
//     lcd.backlight();
//     displayMessage("System", "Starting...");

//     mySerial.begin(57600);
//     if (!finger.verifyPassword()) {
//         displayMessage("Sensor Error", "Check wiring");
//         while (1) delay(1000);
//     }

//     displayMessage("1:Enroll", "2:Verify");
// }

// void loop() {
//     if (Serial.available()) {
//         choice = Serial.read();

//         switch (choice) {
//             case '1':
//                 if (getFingerprintEnroll()) {
//                     Serial.println("Enrollment successful.");
//                 } else {
//                     Serial.println("Enrollment failed.");
//                 }
//                 displayMessage("1:Enroll", "2:Verify");
//                 break;

//             case '2':
//                 displayMessage("Verify Mode", "Place Finger");
//                 getFingerprintID();
//                 displayMessage("1:Enroll", "2:Verify");
//                 break;

//             default:
//                 displayMessage("Invalid Input", "Try 1 or 2");
//                 delay(2000);
//                 displayMessage("1:Enroll", "2:Verify");
//                 break;
//         }
//     }
// }















// #include <Arduino.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>

// // Pin Definitions for I2C LCD
// #define I2C_SDA D2        // GPIO4 - LCD SDA connection
// #define I2C_SCL D1        // GPIO5 - LCD SCL connection

// // Pin Definitions for AS608/AS-68ML Fingerprint Sensor
// #define FINGERPRINT_RX D6  // GPIO12 - Connect to Yellow wire (RX)
// #define FINGERPRINT_TX D5  // GPIO14 - Connect to White wire (TX)

// // Initialize devices
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// SoftwareSerial mySerial(FINGERPRINT_TX, FINGERPRINT_RX);
// Adafruit_Fingerprint finger(&mySerial);

// // Maximum number of fingerprint slots
// #define MAX_FINGERPRINTS 128

// // Names array to store names associated with each ID
// String fingerprintNames[MAX_FINGERPRINTS];

// char choice = '0';

// // Helper function to print both to Serial and LCD
// void displayMessage(const char *line1, const char *line2) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(line1);
//     lcd.setCursor(0, 1);
//     lcd.print(line2);
//     Serial.println(String("LCD: ") + line1 + " | " + line2);
// }

// // Function to enroll a fingerprint with an assigned name
// boolean getFingerprintEnroll() {
//     uint8_t id;
//     Serial.println("Enter ID to assign:");
//     while (!Serial.available()); // Wait for user input
//     id = Serial.parseInt();
//     if (id >= MAX_FINGERPRINTS) {
//         Serial.println("Invalid ID. Must be less than 128.");
//         displayMessage("Invalid ID", "Try again");
//         return false;
//     }

//     Serial.println("Enter name for ID:");
//     while (!Serial.available()); // Wait for user input
//     fingerprintNames[id] = Serial.readStringUntil('\n');
//     fingerprintNames[id].trim(); // Remove extra spaces/newlines

//     displayMessage("Place finger", "on sensor");
//     Serial.println("Waiting for valid finger press...");

//     uint8_t p = -1;
//     while (p != FINGERPRINT_OK) {
//         p = finger.getImage();
//         switch (p) {
//             case FINGERPRINT_OK:
//                 Serial.println("Image taken");
//                 break;
//             case FINGERPRINT_NOFINGER:
//                 Serial.println("Waiting for finger...");
//                 break;
//             case FINGERPRINT_PACKETRECIEVEERR:
//                 displayMessage("Comm Error", "Try again");
//                 return false;
//             case FINGERPRINT_IMAGEFAIL:
//                 displayMessage("Image Error", "Try again");
//                 return false;
//         }
//         delay(100);
//     }

//     if (finger.image2Tz(1) != FINGERPRINT_OK) {
//         displayMessage("Convert Err", "Try again");
//         return false;
//     }

//     displayMessage("Remove finger", "please");
//     delay(2000);
//     while (finger.getImage() != FINGERPRINT_NOFINGER) delay(100);

//     displayMessage("Place same", "finger again");
//     Serial.println("Place the same finger again...");

//     while (finger.getImage() != FINGERPRINT_OK) delay(100);

//     if (finger.image2Tz(2) != FINGERPRINT_OK) {
//         displayMessage("Convert Err", "Try again");
//         return false;
//     }

//     if (finger.createModel() != FINGERPRINT_OK) {
//         displayMessage("Match Fail", "Try again");
//         return false;
//     }

//     if (finger.storeModel(id) != FINGERPRINT_OK) {
//         displayMessage("Store Error", "Try again");
//         return false;
//     }

//     Serial.println("Enrollment completed successfully!");
//     displayMessage("Success!", fingerprintNames[id].c_str());
//     delay(2000);
//     return true;
// }

// // Function to verify a fingerprint and display its name
// boolean getFingerprintVerify() {
//     displayMessage("Place finger", "for verify");

//     uint8_t retryCount = 0;
//     const uint8_t maxRetries = 50;
//     while (retryCount < maxRetries) {
//         uint8_t p = finger.getImage();
//         if (p == FINGERPRINT_OK) break;
//         if (p == FINGERPRINT_NOFINGER) retryCount++;
//         delay(100);
//     }

//     if (retryCount >= maxRetries) {
//         displayMessage("Timeout", "Finger not found");
//         return false;
//     }

//     if (finger.image2Tz() != FINGERPRINT_OK) {
//         displayMessage("Convert Error", "Try again");
//         return false;
//     }

//     if (finger.fingerSearch() == FINGERPRINT_OK) {
//         String name = fingerprintNames[finger.fingerID];
//         if (name.length() == 0) name = "Unknown";
//         Serial.print("Fingerprint found! ID: ");
//         Serial.print(finger.fingerID);
//         Serial.print(", Name: ");
//         Serial.println(name);
//         displayMessage("Hello", name.c_str());
//         return true;
//     } else {
//         displayMessage("Not Found", "Try again");
//         return false;
//     }
// }

// void setup() {
//     Serial.begin(115200);
//     Serial.println("Fingerprint Sensor Test");

//     Wire.begin(I2C_SDA, I2C_SCL);
//     lcd.init();
//     lcd.backlight();
//     displayMessage("System", "Starting...");

//     mySerial.begin(57600);
//     if (!finger.verifyPassword()) {
//         displayMessage("No Sensor", "Check Wiring");
//         while (1) delay(1000);
//     }

//     displayMessage("1:Enroll", "2:Verify");
// }

// void loop() {
//     if (Serial.available()) {
//         choice = Serial.read();

//         switch (choice) {
//             case '1':
//                 Serial.println("Enrollment mode...");
//                 if (getFingerprintEnroll()) {
//                     Serial.println("Enrollment successful!");
//                 } else {
//                     Serial.println("Enrollment failed!");
//                 }
//                 break;

//             case '2':
//                 Serial.println("Verification mode...");
//                 if (getFingerprintVerify()) {
//                     Serial.println("Verification successful!");
//                 } else {
//                     Serial.println("Verification failed!");
//                 }
//                 break;

//             default:
//                 displayMessage("1:Enroll", "2:Verify");
//                 break;
//         }
//     }
// }





























// #include <Arduino.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>

// // Pin Definitions
// #define I2C_SDA D2
// #define I2C_SCL D1
// #define FINGERPRINT_RX D6
// #define FINGERPRINT_TX D5

// // Initialize components
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// SoftwareSerial mySerial(FINGERPRINT_TX, FINGERPRINT_RX);
// Adafruit_Fingerprint finger(&mySerial);

// #define MAX_FINGERPRINTS 128
// String fingerprintNames[MAX_FINGERPRINTS];

// // Helper to display messages on LCD
// void displayMessage(const char *line1, const char *line2) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(line1);
//     lcd.setCursor(0, 1);
//     lcd.print(line2);
//     Serial.print("LCD: ");
//     Serial.println(line1);
//     Serial.println(line2);
// }

// // Function to handle enrollment
// boolean enrollFingerprint(uint8_t id, const String &name) {
//     if (id > MAX_FINGERPRINTS) {
//         displayMessage("ID too large!", "Max is 128");
//         return false;
//     }
//     fingerprintNames[id] = name;

//     displayMessage("Place finger", "on sensor...");
//     while (finger.getImage() != FINGERPRINT_OK) {
//         delay(100);
//     }

//     if (finger.image2Tz(1) != FINGERPRINT_OK) {
//         displayMessage("Error", "Try again");
//         return false;
//     }

//     displayMessage("Remove finger", "please...");
//     delay(2000);
//     while (finger.getImage() != FINGERPRINT_NOFINGER) {
//         delay(100);
//     }

//     displayMessage("Place same", "finger again...");
//     while (finger.getImage() != FINGERPRINT_OK) {
//         delay(100);
//     }

//     if (finger.image2Tz(2) != FINGERPRINT_OK) {
//         displayMessage("Error", "Try again");
//         return false;
//     }

//     if (finger.createModel() != FINGERPRINT_OK) {
//         displayMessage("Match failed", "Try again");
//         return false;
//     }

//     if (finger.storeModel(id) != FINGERPRINT_OK) {
//         displayMessage("Store failed", "Try again");
//         return false;
//     }

//     displayMessage("Enroll Success", ("ID: " + String(id)).c_str());
//     return true;
// }

// // Function to handle verification
// void verifyFingerprint() {
//     displayMessage("Place finger", "to verify...");
//     while (finger.getImage() != FINGERPRINT_OK) {
//         delay(500);
//     }

//     if (finger.image2Tz() != FINGERPRINT_OK) {
//         displayMessage("Image Error", "Try again");
//         return;
//     }

//     if (finger.fingerFastSearch() != FINGERPRINT_OK) {
//         displayMessage("No match", "Try again");
//         return;
//     }

//     uint8_t id = finger.fingerID;
//     if (fingerprintNames[id] != "") {
//         displayMessage("Hello,", fingerprintNames[id].c_str());
//     } else {
//         displayMessage("Hello,", ("ID: " + String(id)).c_str());
//     }

//     delay(3000);
// }

// // Setup and main menu
// void setup() {
//     Serial.begin(115200);
//     Wire.begin(I2C_SDA, I2C_SCL);
//     lcd.init();
//     lcd.backlight();
//     displayMessage("System", "Starting...");

//     mySerial.begin(57600);
//     if (!finger.verifyPassword()) {
//         displayMessage("Sensor Error", "Check wiring");
//         while (1) delay(1000);
//     }

//     displayMessage("1: Enroll", "2: Verify");
// }

// void loop() {
//     if (Serial.available()) {
//         char option = Serial.read();
//         if (option == '1') {
//             Serial.println("Enter ID:");
//             while (!Serial.available());
//             uint8_t id = Serial.parseInt();

//             Serial.println("Enter Name:");
//             while (!Serial.available());
//             String name = Serial.readStringUntil('\n');
//             name.trim(); // Remove extra spaces or newline

//             if (enrollFingerprint(id, name)) {
//                 Serial.println("Enroll Success!");
//             } else {
//                 Serial.println("Enroll Failed!");
//             }
//         } else if (option == '2') {
//             verifyFingerprint();
//         } else {
//             displayMessage("Invalid Option", "Try 1 or 2");
//         }

//         displayMessage("1: Enroll", "2: Verify");
//     }
// }









// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ArduinoJson.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <Adafruit_Fingerprint.h>
// #include <SoftwareSerial.h>

// // Pin Definitions
// #define FINGERPRINT_TX D6
// #define FINGERPRINT_RX D5
// #define LCD_SDA D2
// #define LCD_SCL D1

// // Initialize components
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// SoftwareSerial fingerSerial(FINGERPRINT_RX, FINGERPRINT_TX);
// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);
// ESP8266WebServer server(80);

// // WiFi credentials
// const char* ssid = "I1927";
// const char* password = "12345678";

// // System states
// enum Mode {
//     ATTENDANCE = 0,
//     ENROLL = 1
// };

// Mode currentMode = ATTENDANCE;

// // Data storage
// struct UserData {
//     String name;
//     String rollNo;
//     bool isActive;
//     unsigned long lastVerified;
// } users[127];

// // HTML and JavaScript content stored in PROGMEM
// const char index_html[] PROGMEM = R"=====(
// <!DOCTYPE html>
// <html lang="en">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>Biometric System</title>
//     <link href="https://cdnjs.cloudflare.com/ajax/libs/tailwindcss/2.2.19/tailwind.min.css" rel="stylesheet">
//     <style>
//         .mode-card { transition: transform 0.2s; }
//         .mode-card:hover { transform: translateY(-5px); }
//     </style>
// </head>
// <body class="bg-gray-100 min-h-screen">
//     <div class="container mx-auto px-4 py-8">
//         <header class="text-center mb-12">
//             <h1 class="text-4xl font-bold text-gray-800 mb-2">Biometric System</h1>
//             <p class="text-gray-600">Select mode to continue</p>
//         </header>
//         <div class="grid md:grid-cols-2 gap-8 max-w-4xl mx-auto">
//             <div class="mode-card bg-white rounded-lg shadow-lg p-6 cursor-pointer" onclick="setMode('enroll')">
//                 <h2 class="text-xl font-semibold text-gray-800 mb-2">Enrollment Mode</h2>
//                 <p class="text-gray-600">Register new users in the system</p>
//             </div>
//             <div class="mode-card bg-white rounded-lg shadow-lg p-6 cursor-pointer" onclick="setMode('attendance')">
//                 <h2 class="text-xl font-semibold text-gray-800 mb-2">Attendance Mode</h2>
//                 <p class="text-gray-600">Verify and mark attendance</p>
//             </div>
//         </div>
//     </div>
//     <script>
//         function setMode(mode) {
//             fetch('/setmode?mode=' + mode)
//                 .then(response => response.text())
//                 .then(data => alert(data));
//         }
//     </script>
// </body>
// </html>
// )=====";

// // Function declarations
// void displayMessage(const String& line1, const String& line2 = "");
// void handleRoot();
// void handleSetMode();
// void handleEnroll();
// void handleStatus();
// uint8_t enrollFingerprint(uint8_t id);
// int getFingerprintID();
// int getFirstFreeID();

// // Global variables for verification status
// bool newVerification = false;
// String lastVerifiedName = "";

// void setup() {
//     Serial.begin(115200);

//     // Initialize I2C for LCD
//     Wire.begin(LCD_SDA, LCD_SCL);
//     lcd.init();
//     lcd.backlight();

//     displayMessage("Starting...");

//     // Initialize fingerprint sensor
//     fingerSerial.begin(57600);
//     if (!finger.verifyPassword()) {
//         displayMessage("Sensor Error!");
//         while (1);
//     }

//     // Connect to WiFi
//     WiFi.begin(ssid, password);
//     displayMessage("WiFi Connecting");

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//     }

//     // Setup web server routes
//     server.on("/", HTTP_GET, handleRoot);
//     server.on("/setmode", HTTP_GET, handleSetMode);
//     server.on("/enroll", HTTP_POST, handleEnroll);
//     server.on("/status", HTTP_GET, handleStatus);
//     server.begin();

//     displayMessage("System Ready", WiFi.localIP().toString());
// }

// void loop() {
//     server.handleClient();

//     if (currentMode == ATTENDANCE) {
//         int fingerprintID = getFingerprintID();
//         if (fingerprintID > 0 && users[fingerprintID].isActive) {
//             lastVerifiedName = users[fingerprintID].name;
//             newVerification = true;
//             displayMessage("Hello", lastVerifiedName);
//             delay(2000);
//             displayMessage("Attendance Mode", "Place finger...");
//         }
//     }
// }

// void handleRoot() {
//     server.send(200, "text/html", index_html);
// }

// void handleSetMode() {
//     String mode = server.arg("mode");
//     if (mode == "attendance") {
//         currentMode = ATTENDANCE;
//         displayMessage("Attendance Mode", "Place finger...");
//     } else if (mode == "enroll") {
//         currentMode = ENROLL;
//         displayMessage("Enroll Mode", "Use web form...");
//     }
//     server.send(200, "text/plain", "Mode set to " + mode);
// }

// void handleEnroll() {
//     if (currentMode != ENROLL) {
//         server.send(400, "text/plain", "System not in enrollment mode");
//         return;
//     }

//     StaticJsonDocument<200> doc;
//     DeserializationError error = deserializeJson(doc, server.arg("plain"));
//     if (error) {
//         server.send(400, "text/plain", "Invalid JSON");
//         return;
//     }

//     String name = doc["name"];
//     String rollNo = doc["rollNo"];

//     int id = getFirstFreeID();
//     if (id < 0) {
//         server.send(400, "text/plain", "Database full");
//         return;
//     }

//     displayMessage("Place finger", "to enroll");

//     if (enrollFingerprint(id)) {
//         users[id].name = name;
//         users[id].rollNo = rollNo;
//         users[id].isActive = true;
//         server.send(200, "text/plain", "Enrollment successful");
//     } else {
//         server.send(400, "text/plain", "Enrollment failed");
//     }
// }

// void handleStatus() {
//     StaticJsonDocument<200> doc;
//     doc["verified"] = newVerification;
//     doc["name"] = lastVerifiedName;

//     String response;
//     serializeJson(doc, response);

//     newVerification = false;  // Reset the flag
//     server.send(200, "application/json", response);
// }

// void displayMessage(const String& line1, const String& line2) {
//     lcd.clear();
//     lcd.print(line1);
//     if (line2.length() > 0) {
//         lcd.setCursor(0, 1);
//         lcd.print(line2);
//     }
// }

// uint8_t enrollFingerprint(uint8_t id) {
//     int p = -1;
//     displayMessage("Place finger");

//     while (p != FINGERPRINT_OK) {
//         p = finger.getImage();
//         delay(50);
//     }

//     p = finger.image2Tz(1);
//     if (p != FINGERPRINT_OK) return p;

//     displayMessage("Remove finger");
//     delay(2000);

//     displayMessage("Place again");
//     p = 0;
//     while (p != FINGERPRINT_OK) {
//         p = finger.getImage();
//         delay(50);
//     }

//     p = finger.image2Tz(2);
//     if (p != FINGERPRINT_OK) return p;

//     p = finger.createModel();
//     if (p != FINGERPRINT_OK) return p;

//     p = finger.storeModel(id);
//     if (p != FINGERPRINT_OK) return p;

//     return true;
// }

// int getFingerprintID() {
//     uint8_t p = finger.getImage();
//     if (p != FINGERPRINT_OK) return -1;

//     p = finger.image2Tz();
//     if (p != FINGERPRINT_OK) return -1;

//     p = finger.fingerFastSearch();
//     if (p != FINGERPRINT_OK) return -1;

//     return finger.fingerID;
// }

// int getFirstFreeID() {
//     for (int i = 1; i < 127; i++) {
//         if (!users[i].isActive) return i;
//     }
//     return -1;
// }













// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h> // For ESP8266
// #include <SoftwareSerial.h>
// #include <EEPROM.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ArduinoJson.h>

// // Constants
// const int MAX_USERS = 50;

// // WiFi credentials
// const char* ssid = "I1927";
// const char* password = "12345678";

// // Initialize web server
// ESP8266WebServer server(80);

// // Initialize fingerprint sensor
// SoftwareSerial mySerial(D6, D5); // RX, TX
// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// // Initialize LCD (0x27 is the default I2C address, adjust if needed)
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// // Structure to store user data
// struct User {
//   char name[20];
//   int rollNumber;
//   bool isPresent;
//   unsigned long lastMarked;
// };

// // Global variables
// bool enrollmentMode = false;
// bool waitingForFinger = false;
// String userName = "";
// int userRoll = 0;
// String lcdLine1 = "";
// String lcdLine2 = "";
// String systemStatus = "";

// // Function prototypes
// void handleRoot();
// void handleMode();
// void handleEnroll();
// void handleStatus();
// void handleUsers();
// void updateLCD(String line1, String line2);
// String getUserList();
// int getFingerprintID();
// void enrollUser();
// void checkAttendance();
// String formatTime(unsigned long timestamp);

// // HTML page definition (same as before)
// const char MAIN_page[] PROGMEM = R"=====(
// [Previous HTML content remains exactly the same]
// )=====";

// void setup() {
//   Serial.begin(9600);
  
//   // Initialize LCD
//   // Wire.begin(D2, D1);
//   // lcd.begin();
//   // lcd.backlight();
//   // lcd.print("Initializing...");
//   // In setup() function, replace the LCD initialization part with:

//   // Initialize LCD
//   Wire.begin(D2, D1);  // SDA, SCL
//   lcd.begin(16, 2);    // Initialize LCD with 16 columns and 2 rows
//   lcd.init();          // Required for ESP8266
//   lcd.backlight();
//   lcd.print("Initializing...");




//   // Initialize fingerprint sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Error!");
//     while (1);
//   }
  
//   // Initialize EEPROM
//   EEPROM.begin(512);
  
//   // Connect to WiFi
//   WiFi.begin(ssid, password);
//   lcd.clear();
//   lcd.print("Connecting WiFi");
  
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     lcd.print(".");
//   }
  
//   // Setup web server routes
//   server.on("/", HTTP_GET, handleRoot);
//   server.on("/mode", HTTP_GET, handleMode);
//   server.on("/enroll", HTTP_POST, handleEnroll);
//   server.on("/status", HTTP_GET, handleStatus);
//   server.on("/users", HTTP_GET, handleUsers);
  
//   server.begin();
  
//   updateLCD("System Ready", "IP: " + WiFi.localIP().toString());
// }

// void loop() {
//   server.handleClient();
  
//   if (waitingForFinger) {
//     if (enrollmentMode) {
//       enrollUser();
//     } else {
//       checkAttendance();
//     }
//   }
// }

// void handleRoot() {
//   server.send(200, "text/html", MAIN_page);
// }

// void handleMode() {
//   String mode = server.arg("set");
//   enrollmentMode = (mode == "enroll");
//   waitingForFinger = false;
  
//   updateLCD(enrollmentMode ? "Enrollment Mode" : "Attendance Mode", "");
  
//   server.send(200, "text/plain", "Switched to " + mode + " mode");
// }

// void handleUsers() {
//   String userList = getUserList();
//   server.send(200, "application/json", userList);
// }

// String getUserList() {
//   StaticJsonDocument<1024> doc;
//   JsonArray users = doc.createNestedArray("users");
  
//   for (int i = 0; i < MAX_USERS; i++) {
//     User user;
//     EEPROM.get(sizeof(User) * i, user);
//     if (user.name[0] != 0) {
//       JsonObject userObj = users.createNestedObject();
//       userObj["name"] = user.name;
//       userObj["roll"] = user.rollNumber;
//       userObj["isPresent"] = user.isPresent;
//       if (user.lastMarked > 0) {
//         userObj["lastMarked"] = formatTime(user.lastMarked);
//       }
//     }
//   }
  
//   String response;
//   serializeJson(doc, response);
//   return response;
// }

// void handleEnroll() {
//   if (!enrollmentMode) {
//     server.send(200, "text/plain", "Please switch to enrollment mode first");
//     return;
//   }
  
//   userName = server.arg("name");
//   userRoll = server.arg("roll").toInt();
//   waitingForFinger = true;
  
//   updateLCD("Place finger", "");
  
//   server.send(200, "text/plain", "Please place finger on sensor");
// }

// void handleStatus() {
//   StaticJsonDocument<1024> doc;
//   doc["lcd1"] = lcdLine1;
//   doc["lcd2"] = lcdLine2;
//   doc["status"] = systemStatus;
  
//   JsonArray users = doc.createNestedArray("users");
  
//   for (int i = 0; i < MAX_USERS; i++) {
//     User user;
//     EEPROM.get(sizeof(User) * i, user);
//     if (user.name[0] != 0) {
//       JsonObject userObj = users.createNestedObject();
//       userObj["name"] = user.name;
//       userObj["roll"] = user.rollNumber;
//       userObj["isPresent"] = user.isPresent;
//       if (user.lastMarked > 0) {
//         userObj["lastMarked"] = formatTime(user.lastMarked);
//       }
//     }
//   }
  
//   String response;
//   serializeJson(doc, response);
//   server.send(200, "application/json", response);
// }

// void updateLCD(String line1, String line2) {
//   lcdLine1 = line1;
//   lcdLine2 = line2;
//   lcd.clear();
//   lcd.print(line1);
//   lcd.setCursor(0, 1);
//   lcd.print(line2);
// }

// int getFingerprintID() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return -1;
  
//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return -1;
  
//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) return -1;
  
//   return FINGERPRINT_OK;
// }

// void enrollUser() {
//   int fingerID = getFingerprintID();
  
//   if (fingerID == FINGERPRINT_OK) {
//     User newUser;
//     userName.toCharArray(newUser.name, 20);
//     newUser.rollNumber = userRoll;
//     newUser.isPresent = false;
//     newUser.lastMarked = 0;
    
//     int addr = sizeof(User) * (finger.fingerID - 1);
//     EEPROM.put(addr, newUser);
//     EEPROM.commit();
    
//     updateLCD("User enrolled!", userName);
//     systemStatus = "Successfully enrolled " + userName;
//     waitingForFinger = false;
//     delay(2000);
//     updateLCD(enrollmentMode ? "Enrollment Mode" : "Attendance Mode", "");
//   }
// }

// void checkAttendance() {
//   int fingerID = getFingerprintID();
  
//   if (fingerID == FINGERPRINT_OK) {
//     User user;
//     int addr = sizeof(User) * (finger.fingerID - 1);
//     EEPROM.get(addr, user);
    
//     user.isPresent = true;
//     user.lastMarked = millis();
//     EEPROM.put(addr, user);
//     EEPROM.commit();
    
//     updateLCD("Hello " + String(user.name), "Attendance marked");
//     systemStatus = "Marked attendance for " + String(user.name);
//     waitingForFinger = false;
//     delay(2000);
//     updateLCD(enrollmentMode ? "Enrollment Mode" : "Attendance Mode", "");
//   }
// }

// String formatTime(unsigned long timestamp) {
//   unsigned long seconds = timestamp / 1000;
//   unsigned long minutes = seconds / 60;
//   unsigned long hours = minutes / 60;
//   minutes %= 60;
//   seconds %= 60;
  
//   char timeStr[9];
//   sprintf(timeStr, "%02lu:%02lu:%02lu", hours, minutes, seconds);
//   return String(timeStr);
// }











// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins
// SoftwareSerial mySerial(D6, D5); // TX, RX
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127];
// bool enrollMode = false;

// void setup() {
//   Serial.begin(9600);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.begin(16, 2);
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     if (Serial.parseInt() == 1) {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");

//   Serial.println("Enter name:");
//   while (!Serial.available()) delay(10);
//   String name = Serial.readStringUntil('\n');
//   name.trim();

//   Serial.println("Enter roll number:");
//   while (!Serial.available()) delay(10);
//   int roll = Serial.parseInt();

//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID();
//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Place finger");
//     lcd.setCursor(0, 1);
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");

//     while (!getFingerprintEnroll(id)) {
//       delay(500); // Wait longer before retrying
//     }
//     delay(2000);
//   }

//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete!");
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//       case FINGERPRINT_OK:
//         break;
//       case FINGERPRINT_NOFINGER:
//         return false;
//       default:
//         return false;
//     }
//   }

//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) return false;

//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) return false;

//   return true;
// }

// uint8_t getFreeID() {
//   uint8_t count = 1;
//   while (count < 128) {
//     if (!users[count].name[0]) return count;
//     count++;
//   }
//   return 1;
// }














// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins (TX to RX and RX to TX)
// SoftwareSerial mySerial(D5, D6); // TX, RX (swapped pins)
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127] = {};
// bool enrollMode = false;

// void setup() {
//   Serial.begin(9600);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     int input = Serial.parseInt();
//     if (input == 1) {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");

//   Serial.println("Enter name:");
//   while (!Serial.available()) delay(10);
//   String name = Serial.readStringUntil('\n');
//   name.trim();

//   Serial.println("Enter roll number:");
//   while (!Serial.available()) delay(10);
//   int roll = Serial.parseInt();

//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID();
//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Place finger");
//     lcd.setCursor(0, 1);
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");

//     while (!getFingerprintEnroll(id)) {
//       delay(500); // Wait longer before retrying
//     }
//     delay(2000);
//   }

//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete!");
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//       case FINGERPRINT_OK:
//         break;
//       case FINGERPRINT_NOFINGER:
//         return false;
//       default:
//         return false;
//     }
//   }

//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) return false;

//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) return false;

//   return true;
// }

// uint8_t getFreeID() {
//   uint8_t count = 1;
//   while (count < 128) {
//     if (!users[count].name[0]) return count;
//     count++;
//   }
//   return 1;
// }













// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins (TX to RX and RX to TX)
// SoftwareSerial mySerial(D5, D6); // TX, RX (swapped pins)
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127] = {};
// bool enrollMode = false;

// void setup() {
//   Serial.begin(115200); // Set the baud rate to 115200 for Serial Monitor

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Uncomment to set RTC time manually
//   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// rtc.adjust(DateTime(2025, 1, 22, 20, 28, 45));


//   // Initialize Fingerprint Sensor
//   finger.begin(57600); // Fingerprint sensor at 57600 baud rate
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     int input = Serial.parseInt();
//     if (input == 1) {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");

//   Serial.println("Enter name:");
//   while (!Serial.available()) delay(10);
//   String name = Serial.readStringUntil('\n');
//   name.trim();

//   Serial.println("Enter roll number:");
//   while (!Serial.available()) delay(10);
//   int roll = Serial.parseInt();

//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID();
//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Place finger");
//     lcd.setCursor(0, 1);
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");

//     while (!getFingerprintEnroll(id)) {
//       delay(500); // Wait longer before retrying
//     }
//     delay(2000);
//   }

//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete!");
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//       case FINGERPRINT_OK:
//         break;
//       case FINGERPRINT_NOFINGER:
//         return false;
//       default:
//         return false;
//     }
//   }

//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) return false;

//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) return false;

//   return true;
// }

// uint8_t getFreeID() {
//   uint8_t count = 1;
//   while (count < 128) {
//     if (!users[count].name[0]) return count;
//     count++;
//   }
//   return 1;
// }









//  #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins
// SoftwareSerial mySerial(D5, D6); // RX, TX
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127];
// bool enrollMode = false;

// void setup() {
//   Serial.begin(115200);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.begin(16, 2);
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n'); // Removed `.trim()`
//     input.trim(); // Use `trim()` separately
//     if (input == "1") {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");
//   delay(2000);

//   // Get Name
//   Serial.println("Enter name:");
//   lcd.clear();
//   lcd.print("Enter Name");
//   while (!Serial.available());
//   String name = Serial.readStringUntil('\n'); // Removed `.trim()`
//   name.trim(); // Use `trim()` separately
//   Serial.println("Name: " + name);

//   // Get Roll Number
//   Serial.println("Enter roll number:");
//   lcd.clear();
//   lcd.print("Enter Roll No");
//   while (!Serial.available());
//   int roll = Serial.parseInt();
//   Serial.println("Roll Number: " + String(roll));

//   // Begin Enrollment
//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID();
//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");
//     Serial.println("Waiting for finger...");

//     while (!getFingerprintEnroll(id)) {
//       lcd.setCursor(0, 1);
//       lcd.print("Try Again");
//       delay(1000);
//     }
//     delay(2000);
//   }

//   // Save User Data
//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete!");
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//       case FINGERPRINT_OK:
//         break;
//       case FINGERPRINT_NOFINGER:
//         return false;
//       default:
//         return false;
//     }
//   }

//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) return false;

//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) return false;

//   return true;
// }

// uint8_t getFreeID() {
//   uint8_t count = 1;
//   while (count < 128) {
//     if (!users[count].name[0]) return count;
//     count++;
//   }
//   return 1;
// }



















// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins
// SoftwareSerial mySerial(D5, D6); // TX, RX
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127];
// bool enrollMode = false;

// void setup() {
//   Serial.begin(115200);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.begin(16, 2);
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     int mode = Serial.parseInt();
//     if (mode == 1) {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");
//   delay(2000);

//   // Flush serial input to avoid skipping prompts
//   flushInput();

//   // Get Name
//   Serial.println("Enter name:");
//   lcd.clear();
//   lcd.print("Enter Name:");
//   while (!Serial.available());
//   String name = Serial.readStringUntil('\n');
//   name.trim();
//   if (name.length() == 0) {
//     lcd.clear();
//     lcd.print("Invalid Name");
//     Serial.println("Invalid Name! Restart enrollment.");
//     delay(2000);
//     return;
//   }
//   Serial.println("Name: " + name);

//   // Flush serial input before next prompt
//   flushInput();

//   // Get Roll Number
//   Serial.println("Enter roll number:");
//   lcd.clear();
//   lcd.print("Enter Roll No:");
//   while (!Serial.available());
//   int roll = Serial.parseInt();
//   if (roll <= 0) {
//     lcd.clear();
//     lcd.print("Invalid Roll No");
//     Serial.println("Invalid Roll Number! Restart enrollment.");
//     delay(2000);
//     return;
//   }
//   Serial.println("Roll Number: " + String(roll));

//   // Begin Enrollment
//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID(); // Get a free ID for this user
//   Serial.println("Enrolling user with ID: " + String(id));

//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");
//     Serial.println("Waiting for finger... Step " + String(i) + " of 5");

//     int result = getFingerprintEnroll(id);
//     if (result) {
//       lcd.clear();
//       lcd.print("Step ");
//       lcd.print(i);
//       lcd.print(" Success!");
//       delay(2000);
//     } else {
//       lcd.clear();
//       lcd.print("Failed! Retry");
//       Serial.println("Failed to capture fingerprint. Try again.");
//       delay(2000);
//       i--; // Retry the same step
//     }
//   }

//   // Save User Data
//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete for ID: " + String(id));
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;

//   // Capture a fingerprint image
//   Serial.println("Place your finger...");
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     if (p == FINGERPRINT_NOFINGER) return false;
//     if (p == FINGERPRINT_PACKETRECIEVEERR || p == FINGERPRINT_IMAGEFAIL) return false;
//   }
//   Serial.println("Fingerprint image taken.");

//   // Convert the image
//   p = finger.image2Tz(1);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Image conversion failed.");
//     return false;
//   }

//   // Store the fingerprint
//   p = finger.createModel();
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Model creation failed.");
//     return false;
//   }

//   p = finger.storeModel(id);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Model storage failed.");
//     return false;
//   }

//   Serial.println("Fingerprint enrolled successfully.");
//   return true;
// }

// uint8_t getFreeID() {
//   for (uint8_t i = 1; i < 127; i++) {
//     if (!users[i].name[0]) return i;
//   }
//   return 1; // Default to 1 if all IDs are taken
// }

// void flushInput() {
//   while (Serial.available()) Serial.read();
// }








// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>

// // Fingerprint Sensor Pins
// SoftwareSerial mySerial(D5, D6); // TX, RX
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// struct User {
//   char name[20];
//   int rollNo;
// };

// User users[127];
// bool enrollMode = false;

// void setup() {
//   Serial.begin(115200);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.begin(16, 2);
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   lcd.print("Ready!");
//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     int mode = Serial.parseInt();
//     if (mode == 1) {
//       enrollMode = true;
//       enrollUser();
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");
//   delay(2000);

//   // Flush serial input to avoid skipping prompts
//   flushInput();

//   // Get Name
//   Serial.println("Enter name:");
//   lcd.clear();
//   lcd.print("Enter Name:");
//   while (!Serial.available());
//   String name = Serial.readStringUntil('\n');
//   name.trim();
//   if (name.length() == 0) {
//     lcd.clear();
//     lcd.print("Invalid Name");
//     Serial.println("Invalid Name! Restart enrollment.");
//     delay(2000);
//     return;
//   }
//   Serial.println("Name: " + name);

//   // Flush serial input before next prompt
//   flushInput();

//   // Get Roll Number
//   Serial.println("Enter roll number:");
//   lcd.clear();
//   lcd.print("Enter Roll No:");
//   while (!Serial.available());
//   int roll = Serial.parseInt();
//   if (roll <= 0) {
//     lcd.clear();
//     lcd.print("Invalid Roll No");
//     Serial.println("Invalid Roll Number! Restart enrollment.");
//     delay(2000);
//     return;
//   }
//   Serial.println("Roll Number: " + String(roll));

//   // Begin Enrollment
//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID(); // Get a free ID for this user
//   Serial.println("Enrolling user with ID: " + String(id));

//   for (int i = 1; i <= 3; i++) { // Three steps for enrollment
//     lcd.clear();
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 3");
//     Serial.println("Waiting for finger... Step " + String(i) + " of 3");

//     if (!captureAndStoreFingerprint(i)) {
//       lcd.clear();
//       lcd.print("Failed! Retry");
//       Serial.println("Failed to capture fingerprint. Try again.");
//       delay(2000);
//       i--; // Retry the same step
//     } else {
//       lcd.clear();
//       lcd.print("Step ");
//       lcd.print(i);
//       lcd.print(" Success!");
//       delay(2000);
//     }
//   }

//   // Save User Data
//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete for ID: " + String(id));
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool captureAndStoreFingerprint(int step) {
//   int p = -1;

//   // Step 1: Get the fingerprint image
//   Serial.println("Place your finger...");
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     if (p == FINGERPRINT_NOFINGER) {
//       return false; // No finger detected
//     } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//       Serial.println("Communication error with fingerprint sensor.");
//       return false;
//     } else if (p == FINGERPRINT_IMAGEFAIL) {
//       Serial.println("Imaging error. Try again.");
//       return false;
//     }
//   }
//   Serial.println("Fingerprint image taken.");

//   // Step 2: Convert the image to a template
//   p = finger.image2Tz(step);
//   if (p != FINGERPRINT_OK) {
//     Serial.println("Failed to convert image to template. Error: " + String(p));
//     return false;
//   }
//   Serial.println("Fingerprint template created.");

//   // Final step: Store the template
//   if (step == 3) { // Final step
//     p = finger.createModel();
//     if (p != FINGERPRINT_OK) {
//       Serial.println("Failed to create model. Error: " + String(p));
//       return false;
//     }
//     p = finger.storeModel(getFreeID());
//     if (p != FINGERPRINT_OK) {
//       Serial.println("Failed to store model. Error: " + String(p));
//       return false;
//     }
//     Serial.println("Fingerprint successfully stored.");
//   }

//   return true;
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// uint8_t getFreeID() {
//   for (uint8_t i = 1; i < 127; i++) {
//     if (!users[i].name[0]) return i;
//   }
//   return 1; // Default to 1 if all IDs are taken
// }

// void flushInput() {
//   while (Serial.available()) Serial.read();
// }























































#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <RTClib.h>

// Fingerprint Sensor Pins
SoftwareSerial mySerial(D5, D6); // TX, RX
Adafruit_Fingerprint finger(&mySerial);

// LCD and RTC
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

struct User {
  char name[20];
  int rollNo;
};

User users[127];
bool enrollMode = false;

void setup() {
  Serial.begin(115200);

  // Initialize I2C for RTC and LCD
  Wire.begin(D2, D1); // SDA, SCL
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();

  lcd.print("Starting...");
  delay(2000);
  lcd.clear();

  // RTC detectionnnnn
  if (!rtc.begin()) {
    lcd.print("RTC Failed!");
    while (1);
  }


   rtc.adjust(DateTime(2025, 1, 23, 9, 31, 0));

  // Fingerprint Sensor detectionnnnn
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    lcd.print("Sensor Failed!");
    while (1);
  }

  lcd.print("Ready!");
  delay(2000);
  lcd.clear();
  lcd.print("Attendance Mode");
}

void loop() {
  if (Serial.available()) {
    int mode = Serial.parseInt();
    if (mode == 1) {
      enrollMode = true;
      enrollUser();
    } else if (mode == 2) {
      enrollMode = false;
      lcd.clear();
      lcd.print("Attendance Mode");
    }
  }

  if (!enrollMode) {
    getFingerprintAttendance();
  }
}

void enrollUser() {
  lcd.clear();
  lcd.print("Enrollment Mode");
  delay(2000);

  // Flush serial input to avoid skipping prompts
  flushInput();

  // Get Name
  Serial.println("Enter name:");
  lcd.clear();
  lcd.print("Enter Name:");
  while (!Serial.available());
  String name = Serial.readStringUntil('\n');
  name.trim();
  if (name.length() == 0) {
    lcd.clear();
    lcd.print("Invalid Name");
    Serial.println("Invalid Name! Restart enrollment.");
    delay(2000);
    return;
  }
  Serial.println("Name: " + name);

  // Flush serial input before next prompt
  flushInput();

  // Get Roll Number
  Serial.println("Enter roll number:");
  lcd.clear();
  lcd.print("Enter Roll No:");
  while (!Serial.available());
  int roll = Serial.parseInt();
  if (roll <= 0) {
    lcd.clear();
    lcd.print("Invalid Roll No");
    Serial.println("Invalid Roll Number! Restart enrollment.");
    delay(2000);
    return;
  }
  Serial.println("Roll Number: " + String(roll));

  // Begin Enrollment
  lcd.clear();
  lcd.print("Place finger");
  lcd.setCursor(0, 1);
  lcd.print("multiple times");

  int id = getFreeID(); // Get a free ID for this user
  Serial.println("Enrolling user with ID: " + String(id));

  for (int i = 1; i <= 3; i++) { // Three steps for enrollment
    lcd.clear();
    lcd.print("Step ");
    lcd.print(i);
    lcd.print(" of 3");
    Serial.println("Waiting for finger... Step " + String(i) + " of 3");

    while (!captureAndStoreFingerprint(i)) {
      lcd.clear();
      lcd.print("Failed! Retry");
      lcd.setCursor(0, 1);
      lcd.print("Step ");
      lcd.print(i);
      delay(2000); // Delay before retrying
    }

    lcd.clear();
    lcd.print("Step ");
    lcd.print(i);
    lcd.print(" Success!");
    delay(2000);
  }

  // Save User Data
  name.toCharArray(users[id].name, 20);
  users[id].rollNo = roll;

  lcd.clear();
  lcd.print("Enrollment Done!");
  Serial.println("Enrollment complete for ID: " + String(id));
  delay(2000);

  enrollMode = false;
  lcd.clear();
  lcd.print("Attendance Mode");
}

bool captureAndStoreFingerprint(int step) {
  int p = -1;

  // Wait for user to place finger
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if (p == FINGERPRINT_NOFINGER) {
      continue; // Keep waiting for the finger
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error with fingerprint sensor.");
      return false;
    } else if (p == FINGERPRINT_IMAGEFAIL) {
      Serial.println("Imaging error. Try again.");
      return false;
    }
  }
  Serial.println("Fingerprint image taken.");

  // Step 2: Convert the image to a template
  p = finger.image2Tz(step);
  if (p != FINGERPRINT_OK) {
    Serial.println("Failed to convert image to template. Error: " + String(p));
    return false;
  }
  Serial.println("Fingerprint template created.");

  // Final step: Store the template
  if (step == 3) { // Final step
    p = finger.createModel();
    if (p != FINGERPRINT_OK) {
      Serial.println("Failed to create model. Error: " + String(p));
      return false;
    }
    p = finger.storeModel(getFreeID());
    if (p != FINGERPRINT_OK) {
      Serial.println("Failed to store model. Error: " + String(p));
      return false;
    }
    Serial.println("Fingerprint successfully stored.");
  }

  return true;
}

void getFingerprintAttendance() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Finger not found!");
    delay(2000);
    lcd.clear();
    lcd.print("Attendance Mode");
    return;
  }

  DateTime now = rtc.now();
  char timeStr[20];
  sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
          now.day(), now.month(), now.year() % 100,
          now.hour(), now.minute(), now.second());

  lcd.clear();
  lcd.print("Hello ");
  lcd.print(users[finger.fingerID].name);
  lcd.setCursor(0, 1);
  lcd.print("Marked!");

  Serial.print("Attendance marked for ");
  Serial.print(users[finger.fingerID].name);
  Serial.print(" at ");
  Serial.println(timeStr);

  delay(2000);
  lcd.clear();
  lcd.print("Attendance Mode");
}

uint8_t getFreeID() {
  for (uint8_t i = 1; i < 127; i++) {
    if (!users[i].name[0]) return i;
  }
  return 1; // Default to 1 if all IDs are taken
}

void flushInput() {
  while (Serial.available()) Serial.read();
}

















// #include <Adafruit_Fingerprint.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <RTClib.h>
// #include <ESP8266WiFi.h> // Correct library for ESP8266
// #include <ESP8266HTTPClient.h>

// // WiFi credentials
// const char* ssid = "I1927";
// const char* password = "12345678";

// // Google Apps Script URL
// const char* googleScriptUrl = "https://script.google.com/macros/s/AKfycbxvTekiofovQj5mgnJDeij6K9DO7lNcf0FclLlUcQuZ9sbZLSZkXDmweA7zo9xHuRD67A/exec";

// // Fingerprint Sensor Pins
// SoftwareSerial mySerial(D5, D6); // TX, RX
// Adafruit_Fingerprint finger(&mySerial);

// // LCD and RTC
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// RTC_DS3231 rtc;

// // User data structure
// struct User {
//   char name[20];
//   int rollNo;
// };
// User users[127];
// bool enrollMode = false;

// void setup() {
//   Serial.begin(9600);

//   // Initialize I2C for RTC and LCD
//   Wire.begin(D2, D1); // SDA, SCL
//   lcd.begin(16, 2);
//   lcd.init();
//   lcd.backlight();

//   lcd.print("Starting...");
//   delay(2000);
//   lcd.clear();

//   // Initialize RTC
//   if (!rtc.begin()) {
//     lcd.print("RTC Failed!");
//     while (1);
//   }

//   // Initialize Fingerprint Sensor
//   finger.begin(57600);
//   if (!finger.verifyPassword()) {
//     lcd.print("Sensor Failed!");
//     while (1);
//   }

//   // Initialize WiFi
//   WiFi.begin(ssid, password);
//   lcd.clear();
//   lcd.print("Connecting WiFi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     lcd.print(".");
//   }
//   lcd.clear();
//   lcd.print("WiFi Connected!");

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void loop() {
//   if (Serial.available()) {
//     int input = Serial.parseInt();
//     if (input == 1) {
//       enrollMode = true;
//       enrollUser();
//     } else if (input == 2) {
//       enrollMode = false;
//       lcd.clear();
//       lcd.print("Attendance Mode");
//     }
//   }

//   if (!enrollMode) {
//     getFingerprintAttendance();
//   }
// }

// void enrollUser() {
//   lcd.clear();
//   lcd.print("Enrollment Mode");

//   // Get name from serial monitor
//   Serial.println("Enter name:");
//   String name = waitForSerialInput();
//   name.trim();

//   // Get roll number from serial monitor
//   Serial.println("Enter roll number:");
//   String rollStr = waitForSerialInput();
//   int roll = rollStr.toInt();

//   lcd.clear();
//   lcd.print("Place finger");
//   lcd.setCursor(0, 1);
//   lcd.print("multiple times");

//   int id = getFreeID();
//   for (int i = 1; i <= 5; i++) {
//     lcd.clear();
//     lcd.print("Place finger");
//     lcd.setCursor(0, 1);
//     lcd.print("Step ");
//     lcd.print(i);
//     lcd.print(" of 5");

//     while (!getFingerprintEnroll(id)) {
//       delay(500); // Wait before retrying
//     }
//     delay(2000);
//   }

//   name.toCharArray(users[id].name, 20);
//   users[id].rollNo = roll;

//   lcd.clear();
//   lcd.print("Enrollment Done!");
//   Serial.println("Enrollment complete!");
//   delay(2000);

//   enrollMode = false;
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// void getFingerprintAttendance() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK) return;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK) {
//     lcd.clear();
//     lcd.print("Finger not found!");
//     delay(2000);
//     lcd.clear();
//     lcd.print("Attendance Mode");
//     return;
//   }

//   DateTime now = rtc.now();
//   char timeStr[20];
//   sprintf(timeStr, "%02d/%02d/%02d %02d:%02d:%02d",
//           now.day(), now.month(), now.year() % 100,
//           now.hour(), now.minute(), now.second());

//   lcd.clear();
//   lcd.print("Hello ");
//   lcd.print(users[finger.fingerID].name);
//   lcd.setCursor(0, 1);
//   lcd.print("Marked!");

//   Serial.print("Attendance marked for ");
//   Serial.print(users[finger.fingerID].name);
//   Serial.print(" at ");
//   Serial.println(timeStr);

//   // Log to Google Sheets
//   logToGoogleSheets(users[finger.fingerID].name, users[finger.fingerID].rollNo, timeStr);

//   delay(2000);
//   lcd.clear();
//   lcd.print("Attendance Mode");
// }

// bool getFingerprintEnroll(uint8_t id) {
//   int p = -1;
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     if (p == FINGERPRINT_NOFINGER) continue;
//     if (p != FINGERPRINT_OK) return false;

//     p = finger.image2Tz(1);
//     if (p != FINGERPRINT_OK) return false;

//     p = finger.storeModel(id);
//     if (p != FINGERPRINT_OK) return false;

//     return true;
//   }
//   return false;
// }

// uint8_t getFreeID() {
//   for (uint8_t i = 1; i < 127; i++) {
//     if (!users[i].name[0]) return i;
//   }
//   return 1;
// }

// String waitForSerialInput() {
//   while (!Serial.available()) {
//     delay(100);
//   }
//   return Serial.readStringUntil('\n');
// }

// void logToGoogleSheets(String name, int rollNo, String timestamp) {
//   if (WiFi.status() == WL_CONNECTED) {
//     WiFiClient client;
//     HTTPClient http;

//     String url = String(googleScriptUrl) + "?name=" + name + "&roll=" + rollNo + "&time=" + timestamp;
//     http.begin(client, url);
//     int httpResponseCode = http.GET();
//     http.end();
//   }
// }
