#include <M5Cardputer.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* CLAUDE_API_KEY = "YOUR_ANTHROPIC_API_KEY";
const char* ELEVENLABS_API_KEY = "YOUR_ELEVENLABS_API_KEY";
const char* ELEVENLABS_VOICE_ID = "zNsotODqUhvbJ5wMG7Ei";

// ==================== TURQUOISE COSMIC PALETTE ====================
// Using M5GFX color565(r, g, b) format
#define WD_BG_DEEP    0x0945   // #0a2a2a - main background
#define WD_BG_CARD    0x00E3   // #071f1f - card backgrounds
#define WD_BG_BAR     0x09C7   // #0f3a3a - bar backgrounds
#define WD_ACCENT     0x5E54   // #5dcaa5 - primary accent
#define WD_ACCENT_LT  0x9F19   // #9fe1cb - light accent
#define WD_ACCENT_DIM 0x1CEE   // #1d9e75 - dim accent
#define WD_TEXT        0xE7BD   // #e1f5ee - primary text
#define WD_TEXT_SEC    0x5E54   // #5dcaa5 - secondary text
#define WD_STAT_SPD   0x85DF   // #85b7eb - speed
#define WD_STAT_WIT   0x9F19   // #9fe1cb - wit
#define WD_STAT_PWR   0xF4B2   // #f09595 - power
#define WD_STAT_STL   0xFE4F   // #fac775 - stealth
#define WD_STAT_SRV   0x9E2C   // #97c459 - survival
#define WD_RARITY     0xEF07   // #ef9f27 - rarity stars
#define WD_YELLOW     0xFEA0   // yellow for speaking indicator
#define WD_RED        0xF800   // red for errors

String inputText = "";
String currentNarration = "";
String question1 = "";
String question2 = "";
String lastEntryJson = "";
String lastAnswer = "";
String lastQuestion = "";

bool isLoading = false;
bool viewingEntry = false;
bool viewingQuestions = false;
bool viewingAnswer = false;

// Animal database
const char* animalDB[] = {
    "Axolotl", "Albatross", "Anaconda", "Armadillo", "Arctic Fox",
    "Bengal Tiger", "Blue Whale", "Bald Eagle", "Black Mamba", "Blobfish",
    "Cheetah", "Chameleon", "Capybara", "Chimpanzee", "Clownfish",
    "Dolphin", "Dragonfly", "Dumbo Octopus",
    "Elephant", "Electric Eel", "Emperor Penguin", "Eagle Owl",
    "Flamingo", "Fox", "Frog",
    "Golden Retriever", "Gorilla", "Great White Shark", "Gecko",
    "Hummingbird", "Honey Badger", "Hammerhead Shark",
    "Iguana", "Ibex",
    "Jellyfish", "Jaguar",
    "Komodo Dragon", "Koala", "King Cobra",
    "Lion", "Lemur", "Lynx",
    "Mantis Shrimp", "Moose", "Manta Ray",
    "Narwhal", "Nautilus",
    "Octopus", "Orangutan", "Osprey", "Otter",
    "Pangolin", "Platypus", "Panda", "Peregrine Falcon", "Pufferfish",
    "Quokka", "Quetzal",
    "Red Panda", "Rhinoceros", "Rattlesnake",
    "Snow Leopard", "Sloth", "Seahorse", "Scorpion", "Stingray",
    "Tardigrade", "Tarantula", "Toucan", "Tortoise",
    "Unicornfish",
    "Vulture", "Viper",
    "Wolf", "Wolverine", "Whale Shark", "Wombat",
    "Xenopus",
    "Yak",
    "Zebra"
};
const int animalCount = sizeof(animalDB) / sizeof(animalDB[0]);

int browseOffset = 0;
int browseSelect = 0;
String browseFilter = "";
bool browsing = false;

// ==================== SCREEN FUNCTIONS ====================

void drawSplash() {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);

    // Stars
    M5Cardputer.Display.drawPixel(20, 8, WD_ACCENT_LT);
    M5Cardputer.Display.drawPixel(180, 15, WD_ACCENT);
    M5Cardputer.Display.drawPixel(100, 5, WD_TEXT);
    M5Cardputer.Display.drawPixel(200, 25, WD_ACCENT_DIM);
    M5Cardputer.Display.drawPixel(50, 20, WD_ACCENT_LT);

    M5Cardputer.Display.setTextColor(WD_ACCENT_DIM);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(80, 15);
    M5Cardputer.Display.println("T H E");

    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    M5Cardputer.Display.setTextSize(3);
    M5Cardputer.Display.setCursor(20, 30);
    M5Cardputer.Display.println("WILDDEX");

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(30, 70);
    M5Cardputer.Display.println("Creature encyclopedia");

    M5Cardputer.Display.setTextColor(WD_ACCENT_DIM);
    M5Cardputer.Display.setCursor(40, 100);
    M5Cardputer.Display.println("Connecting to WiFi...");
}

void drawInput() {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);

    // Stars
    M5Cardputer.Display.drawPixel(15, 3, WD_ACCENT_LT);
    M5Cardputer.Display.drawPixel(220, 8, WD_ACCENT);
    M5Cardputer.Display.drawPixel(190, 3, WD_TEXT);

    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(10, 5);
    M5Cardputer.Display.println("WILDDEX");
    M5Cardputer.Display.drawLine(0, 25, 240, 25, WD_ACCENT_DIM);

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(10, 35);
    M5Cardputer.Display.println("ENTER SPECIES NAME:");

    M5Cardputer.Display.setTextColor(WD_TEXT);
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(10, 55);
    M5Cardputer.Display.print(inputText);
    M5Cardputer.Display.print("_");

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(10, 110);
    M5Cardputer.Display.println("[ENTER]Search [R]Random [B]Browse");
    M5Cardputer.Display.setTextColor(WD_ACCENT_DIM);
    M5Cardputer.Display.setCursor(10, 122);
    M5Cardputer.Display.println("Spelling mistakes? No worries!");
}

void drawLoading() {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(10, 30);
    M5Cardputer.Display.println("Exploring the wild...");
    M5Cardputer.Display.setCursor(10, 50);
    M5Cardputer.Display.print("Tracking: ");

    // Scan bar animation
    for (int i = 0; i < 3; i++) {
        M5Cardputer.Display.fillRect(10, 70 + (i * 12), 220 - (i * 40), 6, WD_BG_BAR);
        M5Cardputer.Display.fillRect(10, 70 + (i * 12), (220 - (i * 40)) * (3 - i) / 3, 6, WD_ACCENT);
    }

    M5Cardputer.Speaker.tone(784, 80);
    delay(100);
    M5Cardputer.Speaker.tone(659, 80);
    delay(100);
    M5Cardputer.Speaker.tone(523, 80);
    delay(100);
    M5Cardputer.Speaker.tone(392, 80);
}

void showEntryControls() {
    M5Cardputer.Display.fillRect(0, 125, 240, 10, WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 127);
    if (lastAnswer.length() > 0) {
        M5Cardputer.Display.println("[Q]? [A]Talk [C]QR [R]Ans [DEL]");
    } else {
        M5Cardputer.Display.println("[Q]? [A]Speak [C]QR Code [DEL]");
    }
}

void showAnswerControls() {
    M5Cardputer.Display.fillRect(0, 125, 240, 10, WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 127);
    M5Cardputer.Display.println("[R]Entry [ENTER]New [DEL]Back");
}

void showQuestions() {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 5);
    M5Cardputer.Display.println("EXPLORE MORE:");
    M5Cardputer.Display.drawLine(0, 16, 240, 16, WD_ACCENT_DIM);

    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    M5Cardputer.Display.setCursor(5, 25);
    M5Cardputer.Display.print("[1] ");
    M5Cardputer.Display.setTextColor(WD_TEXT);

    int x = 29;
    int y = 25;
    for (unsigned int i = 0; i < question1.length(); i++) {
        if (x > 235) { x = 5; y += 10; }
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(question1[i]);
        x += 6;
    }

    y += 20;
    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    M5Cardputer.Display.setCursor(5, y);
    M5Cardputer.Display.print("[2] ");
    M5Cardputer.Display.setTextColor(WD_TEXT);

    x = 29;
    for (unsigned int i = 0; i < question2.length(); i++) {
        if (x > 235) { x = 5; y += 10; }
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(question2[i]);
        x += 6;
    }

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(5, 120);
    M5Cardputer.Display.println("[1][2] Answer  [DEL] Back");
}

// ==================== BROWSE ====================

int countMatches() {
    int count = 0;
    for (int i = 0; i < animalCount; i++) {
        String name = String(animalDB[i]);
        name.toUpperCase();
        String filterUpper = browseFilter;
        filterUpper.toUpperCase();
        if (filterUpper.length() == 0 || name.startsWith(filterUpper)) {
            count++;
        }
    }
    return count;
}

String getSelectedAnimal() {
    int matchIndex = 0;
    for (int i = 0; i < animalCount; i++) {
        String name = String(animalDB[i]);
        String upper = name;
        upper.toUpperCase();
        String filterUpper = browseFilter;
        filterUpper.toUpperCase();
        if (filterUpper.length() == 0 || upper.startsWith(filterUpper)) {
            if (matchIndex == browseOffset + browseSelect) {
                return name;
            }
            matchIndex++;
        }
    }
    return "";
}

void drawBrowse() {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 3);
    M5Cardputer.Display.print("BROWSE: ");
    M5Cardputer.Display.setTextColor(WD_TEXT);
    M5Cardputer.Display.print(browseFilter);
    M5Cardputer.Display.print("_");
    M5Cardputer.Display.drawLine(0, 14, 240, 14, WD_ACCENT_DIM);

    int shown = 0;
    int matchIndex = 0;
    for (int i = 0; i < animalCount; i++) {
        String name = String(animalDB[i]);
        String upper = name;
        upper.toUpperCase();
        String filterUpper = browseFilter;
        filterUpper.toUpperCase();

        if (filterUpper.length() == 0 || upper.startsWith(filterUpper)) {
            if (matchIndex >= browseOffset && shown < 10) {
                int y = 18 + (shown * 11);

                if (matchIndex == browseOffset + browseSelect) {
                    M5Cardputer.Display.fillRect(0, y - 1, 240, 11, WD_ACCENT);
                    M5Cardputer.Display.setTextColor(WD_BG_DEEP);
                } else {
                    M5Cardputer.Display.setTextColor(WD_TEXT);
                }

                M5Cardputer.Display.setCursor(5, y);
                M5Cardputer.Display.print(matchIndex == browseOffset + browseSelect ? "> " : "  ");
                M5Cardputer.Display.print(name);
                shown++;
            }
            matchIndex++;
        }
    }

    if (shown == 0) {
        M5Cardputer.Display.setTextColor(WD_RARITY);
        M5Cardputer.Display.setCursor(5, 50);
        M5Cardputer.Display.println("No matches found!");
    }

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(5, 127);
    M5Cardputer.Display.println("[W/S]Scroll [ENTER]Select [DEL]Back");
}

// ==================== ENTRY DISPLAY ====================

void drawEntryHeader(JsonDocument& doc) {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);

    // Header bar
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 3);
    M5Cardputer.Display.printf("WILDDEX #%03d", doc["entryNumber"].as<int>());

    // Rarity stars
    M5Cardputer.Display.setCursor(160, 3);
    int rarity = doc["rarity"].as<int>();
    for (int i = 0; i < 5; i++) {
        M5Cardputer.Display.setTextColor(i < rarity ? WD_RARITY : WD_BG_BAR);
        M5Cardputer.Display.print("*");
    }

    M5Cardputer.Display.drawLine(0, 14, 240, 14, WD_ACCENT_DIM);

    // Animal name
    M5Cardputer.Display.setTextColor(WD_TEXT);
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(5, 18);
    String name = doc["commonName"].as<String>();
    if (name.length() > 14) name = name.substring(0, 13) + ".";
    M5Cardputer.Display.println(name);

    // Family and size
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(5, 38);
    M5Cardputer.Display.printf("%s", doc["family"].as<const char*>());
    M5Cardputer.Display.setCursor(120, 38);
    M5Cardputer.Display.printf("%s", doc["sizeRange"].as<const char*>());

    // Classification and weight
    M5Cardputer.Display.setTextColor(WD_TEXT_SEC);
    M5Cardputer.Display.setCursor(5, 48);
    String classif = doc["classification"].as<String>();
    if (classif.length() > 18) classif = classif.substring(0, 17) + ".";
    M5Cardputer.Display.print(classif);
    M5Cardputer.Display.setCursor(120, 48);
    M5Cardputer.Display.printf("%s", doc["weightRange"].as<const char*>());

    M5Cardputer.Display.drawLine(0, 58, 240, 58, WD_ACCENT_DIM);

    // Stat bars
    int statY = 62;
    int barX = 30;
    int barMaxW = 90;

    const char* statNames[] = {"SPD", "WIT", "PWR", "STL", "SRV"};
    const char* statKeys[] = {"speed", "wit", "power", "stealth", "survival"};
    uint16_t statColors[] = {WD_STAT_SPD, WD_STAT_WIT, WD_STAT_PWR, WD_STAT_STL, WD_STAT_SRV};

    for (int s = 0; s < 5; s++) {
        int val = doc[statKeys[s]].as<int>();

        M5Cardputer.Display.setTextColor(WD_ACCENT);
        M5Cardputer.Display.setCursor(5, statY);
        M5Cardputer.Display.print(statNames[s]);

        // Bar background
        M5Cardputer.Display.fillRect(barX, statY, barMaxW, 7, WD_BG_BAR);

        // Bar fill
        int fillW = (val * barMaxW) / 10;
        M5Cardputer.Display.fillRect(barX, statY, fillW, 7, statColors[s]);

        // Value
        M5Cardputer.Display.setTextColor(WD_TEXT);
        M5Cardputer.Display.setCursor(barX + barMaxW + 5, statY);
        M5Cardputer.Display.printf("%d", val);

        statY += 9;
    }

    M5Cardputer.Display.drawLine(0, statY + 2, 240, statY + 2, WD_ACCENT_DIM);
}

void typewriterText(String text, int startY) {
    int x = 5;
    int y = startY;
    int charWidth = 6;
    int lineHeight = 10;
    int maxX = 235;
    int maxY = 125;

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(WD_TEXT);

    for (unsigned int i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c == ' ' && x > 5) {
            int wordEnd = text.indexOf(' ', i + 1);
            if (wordEnd == -1) wordEnd = text.length();
            int wordLen = wordEnd - (i + 1);
            if (x + (wordLen + 1) * charWidth > maxX) {
                x = 5;
                y += lineHeight;
            }
        }

        if (y + lineHeight > maxY) {
            M5Cardputer.Display.scroll(0, -lineHeight);
            M5Cardputer.Display.fillRect(0, maxY - lineHeight, 240, lineHeight, WD_BG_DEEP);
            y -= lineHeight;
        }

        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(c);
        x += charWidth;

        if (x > maxX) {
            x = 5;
            y += lineHeight;
        }

        if (i % 3 == 0) {
            M5Cardputer.Speaker.tone(1760, 15);
        }

        delay(30);
        M5Cardputer.update();
    }
}

void redrawEntry() {
    if (lastEntryJson.length() == 0) return;

    JsonDocument entryDoc;
    deserializeJson(entryDoc, lastEntryJson);
    drawEntryHeader(entryDoc);

    String desc = entryDoc["description"].as<String>();
    int x = 5;
    int y = 110;
    int charWidth = 6;
    int maxX = 235;

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(WD_TEXT);

    for (unsigned int i = 0; i < desc.length(); i++) {
        char c = desc[i];
        if (c == ' ' && x > 5) {
            int wordEnd = desc.indexOf(' ', i + 1);
            if (wordEnd == -1) wordEnd = desc.length();
            int wordLen = wordEnd - (i + 1);
            if (x + (wordLen + 1) * charWidth > maxX) {
                x = 5;
                y += 10;
            }
        }
        if (y > 120) break;
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(c);
        x += charWidth;
        if (x > maxX) { x = 5; y += 10; }
    }

    showEntryControls();
    viewingEntry = true;
    viewingAnswer = false;
    viewingQuestions = false;
}

void redrawAnswer() {
    if (lastAnswer.length() == 0) return;

    M5Cardputer.Display.fillScreen(WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 5);
    M5Cardputer.Display.println("QUESTION:");
    M5Cardputer.Display.drawLine(0, 16, 240, 16, WD_ACCENT_DIM);

    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    int x = 5;
    int y = 22;
    for (unsigned int i = 0; i < lastQuestion.length(); i++) {
        if (x > 235) { x = 5; y += 10; }
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(lastQuestion[i]);
        x += 6;
    }

    y += 15;
    M5Cardputer.Display.drawLine(0, y, 240, y, WD_ACCENT_DIM);
    y += 5;

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(5, y);
    M5Cardputer.Display.println("ANSWER:");
    y += 12;

    M5Cardputer.Display.setTextColor(WD_TEXT);
    x = 5;
    for (unsigned int i = 0; i < lastAnswer.length(); i++) {
        if (x > 235) { x = 5; y += 10; }
        if (y > 120) break;
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(lastAnswer[i]);
        x += 6;
    }

    showAnswerControls();
    viewingAnswer = true;
    viewingEntry = false;
}

void showQRCode() {
    if (lastEntryJson.length() == 0) return;

    JsonDocument doc;
    deserializeJson(doc, lastEntryJson);
    String name = doc["commonName"].as<String>();

    String slug = name;
    slug.toLowerCase();
    slug.replace(" ", "-");
    slug.replace("(", "");
    slug.replace(")", "");

    String url = "https://wilddex.app/creature/" + slug;

    M5Cardputer.Display.fillScreen(WD_BG_DEEP);

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 3);
    M5Cardputer.Display.println("SCAN TO EXPLORE:");
    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    M5Cardputer.Display.setCursor(5, 15);
    M5Cardputer.Display.println(name);

    // Use M5GFX built-in QR code
    M5Cardputer.Display.qrcode(url.c_str(), 70, 28, 92, 6);

    M5Cardputer.Display.setTextColor(WD_ACCENT_DIM);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 122);
    M5Cardputer.Display.println("wilddex.app");

    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(160, 122);
    M5Cardputer.Display.println("[DEL] Back");
}
// ==================== VOICE ====================

void speakEntry() {
    if (currentNarration.length() == 0) return;

    if (WiFi.status() != WL_CONNECTED) {
        M5Cardputer.Display.fillRect(0, 125, 240, 10, WD_BG_DEEP);
        M5Cardputer.Display.setTextColor(WD_RED);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setCursor(5, 127);
        M5Cardputer.Display.println("No WiFi for voice!");
        delay(2000);
        showEntryControls();
        return;
    }

    M5Cardputer.Display.fillRect(0, 125, 240, 10, WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_YELLOW);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 127);
    M5Cardputer.Display.println("Charles is speaking...");

    WiFiClientSecure ttsClient;
    ttsClient.setInsecure();

    if (!ttsClient.connect("api.elevenlabs.io", 443)) {
        showEntryControls();
        return;
    }

    JsonDocument ttsDoc;
    ttsDoc["text"] = currentNarration;
    ttsDoc["model_id"] = "eleven_multilingual_v2";
    String ttsBody;
    serializeJson(ttsDoc, ttsBody);

    String path = String("/v1/text-to-speech/") + ELEVENLABS_VOICE_ID + "?output_format=pcm_8000";

    ttsClient.println("POST " + path + " HTTP/1.1");
    ttsClient.println("Host: api.elevenlabs.io");
    ttsClient.println("Content-Type: application/json");
    ttsClient.print("xi-api-key: ");
    ttsClient.println(ELEVENLABS_API_KEY);
    ttsClient.print("Content-Length: ");
    ttsClient.println(ttsBody.length());
    ttsClient.println("Connection: close");
    ttsClient.println();
    ttsClient.println(ttsBody);

    unsigned long timeout = millis();
    while (!ttsClient.available()) {
        if (millis() - timeout > 30000) { ttsClient.stop(); showEntryControls(); return; }
        delay(500);
    }

    String ttsStatus = ttsClient.readStringUntil('\n');
    while (ttsClient.available()) {
        String line = ttsClient.readStringUntil('\n');
        line.trim();
        if (line.length() == 0) break;
    }

    size_t maxBuffer = 50 * 1024;
    uint8_t* audioBuffer = (uint8_t*)malloc(maxBuffer);
    size_t audioSize = 0;

    if (audioBuffer) {
        unsigned long lastData = millis();
        while (millis() - lastData < 5000) {
            if (ttsClient.available()) {
                int bytesRead = ttsClient.read(audioBuffer + audioSize, maxBuffer - audioSize);
                if (bytesRead > 0) { audioSize += bytesRead; lastData = millis(); if (audioSize >= maxBuffer) break; }
            }
            delay(1);
        }
        if (audioSize > 100) {
            M5Cardputer.Speaker.playRaw((const int16_t*)audioBuffer, audioSize / 2, 8000, false, 1, 0);
            while (M5Cardputer.Speaker.isPlaying()) { delay(100); M5Cardputer.update(); }
        }
        free(audioBuffer);
    }

    ttsClient.stop();
    showEntryControls();
}

// ==================== ASK QUESTION ====================

void askQuestion(String question) {
    M5Cardputer.Display.fillScreen(WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(5, 5);
    M5Cardputer.Display.println("QUESTION:");
    M5Cardputer.Display.drawLine(0, 16, 240, 16, WD_ACCENT_DIM);

    M5Cardputer.Display.setTextColor(WD_ACCENT_LT);
    int x = 5;
    int y = 22;
    for (unsigned int i = 0; i < question.length(); i++) {
        if (x > 235) { x = 5; y += 10; }
        M5Cardputer.Display.setCursor(x, y);
        M5Cardputer.Display.print(question[i]);
        x += 6;
    }

    y += 15;
    M5Cardputer.Display.drawLine(0, y, 240, y, WD_ACCENT_DIM);
    y += 5;

    M5Cardputer.Display.setTextColor(WD_RARITY);
    M5Cardputer.Display.setCursor(5, y);
    M5Cardputer.Display.println("Thinking...");

    M5Cardputer.Speaker.tone(523, 80);
    delay(100);
    M5Cardputer.Speaker.tone(659, 80);

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
        int wa = 0;
        while (WiFi.status() != WL_CONNECTED && wa < 20) { delay(1000); wa++; }
        if (WiFi.status() != WL_CONNECTED) {
            M5Cardputer.Display.setTextColor(WD_RED);
            M5Cardputer.Display.setCursor(5, y);
            M5Cardputer.Display.println("No WiFi!            ");
            viewingAnswer = true;
            return;
        }
    }

    JsonDocument requestDoc;
    requestDoc["model"] = "claude-sonnet-4-20250514";
    requestDoc["max_tokens"] = 300;

    String prompt = "Answer this animal question in 2-3 short sentences, ";
    prompt += "in a warm David Attenborough narration style: " + question;

    JsonArray messages = requestDoc["messages"].to<JsonArray>();
    JsonObject msg = messages.add<JsonObject>();
    msg["role"] = "user";
    msg["content"] = prompt;

    String body;
    serializeJson(requestDoc, body);

    WiFiClientSecure client;
    client.setInsecure();

    bool connected = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
        if (client.connect("api.anthropic.com", 443)) { connected = true; break; }
        delay(3000);
    }

    if (!connected) {
        M5Cardputer.Display.setTextColor(WD_RED);
        M5Cardputer.Display.setCursor(5, y);
        M5Cardputer.Display.println("Connection failed!  ");
        viewingAnswer = true;
        return;
    }

    client.println("POST /v1/messages HTTP/1.1");
    client.println("Host: api.anthropic.com");
    client.println("Content-Type: application/json");
    client.print("x-api-key: ");
    client.println(CLAUDE_API_KEY);
    client.println("anthropic-version: 2023-06-01");
    client.print("Content-Length: ");
    client.println(body.length());
    client.println("Connection: close");
    client.println();
    client.println(body);

    unsigned long timeout = millis();
    while (!client.available()) {
        if (millis() - timeout > 15000) { client.stop(); M5Cardputer.Display.setTextColor(WD_RED); M5Cardputer.Display.setCursor(5, y); M5Cardputer.Display.println("Timeout!            "); viewingAnswer = true; return; }
        delay(100);
    }

    while (client.available()) { String line = client.readStringUntil('\n'); if (line == "\r") break; }

    String response = "";
    while (client.connected() || client.available()) {
        if (client.available()) {
            String chunkSizeLine = client.readStringUntil('\n');
            chunkSizeLine.trim();
            int chunkSize = strtol(chunkSizeLine.c_str(), NULL, 16);
            if (chunkSize == 0) break;
            for (int i = 0; i < chunkSize; i++) {
                unsigned long t = millis();
                while (!client.available()) { if (millis() - t > 5000) break; delay(10); }
                if (client.available()) response += (char)client.read();
            }
            client.readStringUntil('\n');
        }
        delay(10);
    }
    client.stop();

    JsonDocument responseDoc;
    deserializeJson(responseDoc, response);
    String answer = responseDoc["content"][0]["text"].as<String>();

    M5Cardputer.Display.fillRect(0, y, 240, 135 - y, WD_BG_DEEP);
    M5Cardputer.Display.setTextColor(WD_ACCENT);
    M5Cardputer.Display.setCursor(5, y);
    M5Cardputer.Display.println("ANSWER:");
    y += 12;

    typewriterText(answer, y);

    lastAnswer = answer;
    lastQuestion = question;

    delay(200);
    showAnswerControls();
    viewingAnswer = true;
}

// ==================== FETCH ANIMAL ====================

void fetchAnimal(String animal) {
    isLoading = true;
    drawLoading();

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
        int wa = 0;
        while (WiFi.status() != WL_CONNECTED && wa < 20) { delay(1000); wa++; }
        if (WiFi.status() != WL_CONNECTED) {
            M5Cardputer.Display.fillScreen(WD_BG_DEEP);
            M5Cardputer.Display.setTextColor(WD_RED);
            M5Cardputer.Display.setCursor(10, 50);
            M5Cardputer.Display.println("No WiFi!");
            isLoading = false;
            viewingEntry = true;
            return;
        }
    }

    JsonDocument requestDoc;
    requestDoc["model"] = "claude-sonnet-4-20250514";
    requestDoc["max_tokens"] = 500;

    String prompt = "Generate a WildDex entry for: " + animal + ". ";
    prompt += "If the name is misspelled, figure out what animal they mean. ";
    prompt += "Respond ONLY with valid JSON, no markdown, no code fences. ";
    prompt += "Use this exact structure: ";
    prompt += "{entryNumber: number, commonName: string, ";
    prompt += "classification: string, family: string, ";
    prompt += "sizeRange: string, weightRange: string, ";
    prompt += "rarity: 1-5, ";
    prompt += "speed: 1-10, wit: 1-10, power: 1-10, ";
    prompt += "stealth: 1-10, survival: 1-10, ";
    prompt += "description: 2 short sentences in David Attenborough style, ";
    prompt += "narrationScript: 1 sentence only, max 15 words, warm David Attenborough style, ";
    prompt += "questions: array of 2 strings, fun follow-up questions about this animal}";

    JsonArray messages = requestDoc["messages"].to<JsonArray>();
    JsonObject msg = messages.add<JsonObject>();
    msg["role"] = "user";
    msg["content"] = prompt;

    String body;
    serializeJson(requestDoc, body);

    Serial.println("=== CLAUDE REQUEST ===");

    WiFiClientSecure client;
    client.setInsecure();

    bool connected = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
        Serial.printf("Connecting... attempt %d\n", attempt);
        if (client.connect("api.anthropic.com", 443)) { connected = true; break; }
        delay(3000);
    }

    if (!connected) {
        M5Cardputer.Display.fillScreen(WD_BG_DEEP);
        M5Cardputer.Display.setTextColor(WD_RED);
        M5Cardputer.Display.setCursor(10, 50);
        M5Cardputer.Display.println("Connection failed!");
        M5Cardputer.Display.setTextColor(WD_ACCENT);
        M5Cardputer.Display.setCursor(10, 65);
        M5Cardputer.Display.println("Press DEL to go back");
        isLoading = false;
        viewingEntry = true;
        return;
    }

    client.println("POST /v1/messages HTTP/1.1");
    client.println("Host: api.anthropic.com");
    client.println("Content-Type: application/json");
    client.print("x-api-key: ");
    client.println(CLAUDE_API_KEY);
    client.println("anthropic-version: 2023-06-01");
    client.print("Content-Length: ");
    client.println(body.length());
    client.println("Connection: close");
    client.println();
    client.println(body);

    unsigned long timeout = millis();
    while (!client.available()) {
        if (millis() - timeout > 15000) {
            M5Cardputer.Display.fillScreen(WD_BG_DEEP);
            M5Cardputer.Display.setTextColor(WD_RED);
            M5Cardputer.Display.setCursor(10, 50);
            M5Cardputer.Display.println("Timeout!");
            client.stop();
            isLoading = false;
            viewingEntry = true;
            return;
        }
        delay(100);
    }

    while (client.available()) { String line = client.readStringUntil('\n'); if (line == "\r") break; }

    String response = "";
    while (client.connected() || client.available()) {
        if (client.available()) {
            String chunkSizeLine = client.readStringUntil('\n');
            chunkSizeLine.trim();
            int chunkSize = strtol(chunkSizeLine.c_str(), NULL, 16);
            if (chunkSize == 0) break;
            for (int i = 0; i < chunkSize; i++) {
                unsigned long t = millis();
                while (!client.available()) { if (millis() - t > 5000) break; delay(10); }
                if (client.available()) response += (char)client.read();
            }
            client.readStringUntil('\n');
        }
        delay(10);
    }
    client.stop();

    JsonDocument responseDoc;
    deserializeJson(responseDoc, response);
    String content = responseDoc["content"][0]["text"].as<String>();
    content.replace("```json", "");
    content.replace("```", "");
    content.trim();

    Serial.println("Entry: " + content);
    lastEntryJson = content;

    JsonDocument entryDoc;
    DeserializationError error = deserializeJson(entryDoc, content);

    if (error) {
        M5Cardputer.Display.fillScreen(WD_BG_DEEP);
        M5Cardputer.Display.setTextColor(WD_RED);
        M5Cardputer.Display.setCursor(10, 50);
        M5Cardputer.Display.println("Parse error!");
        M5Cardputer.Display.setTextColor(WD_ACCENT);
        M5Cardputer.Display.setCursor(10, 65);
        M5Cardputer.Display.println("Press DEL to go back");
        isLoading = false;
        viewingEntry = true;
        return;
    }

    if (entryDoc.containsKey("narrationScript")) {
        currentNarration = entryDoc["narrationScript"].as<String>();
    } else {
        currentNarration = entryDoc["description"].as<String>();
    }

    if (entryDoc.containsKey("questions")) {
        question1 = entryDoc["questions"][0].as<String>();
        question2 = entryDoc["questions"][1].as<String>();
    } else {
        question1 = "";
        question2 = "";
    }

    lastAnswer = "";
    lastQuestion = "";

    drawEntryHeader(entryDoc);

    // Discovery jingle
    M5Cardputer.Speaker.tone(523, 100);
    delay(120);
    M5Cardputer.Speaker.tone(659, 100);
    delay(120);
    M5Cardputer.Speaker.tone(784, 100);
    delay(120);
    M5Cardputer.Speaker.tone(1047, 300);
    delay(500);

    String desc = entryDoc["description"].as<String>();
    typewriterText(desc, 110);

    delay(200);
    showEntryControls();
    viewingEntry = true;
    isLoading = false;
}

// ==================== SETUP & LOOP ====================

void setup() {
    Serial.begin(115200);
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Speaker.setVolume(255);

    // Boot jingle
    M5Cardputer.Speaker.tone(523, 100);
    delay(150);
    M5Cardputer.Speaker.tone(659, 100);
    delay(150);
    M5Cardputer.Speaker.tone(784, 300);
    delay(200);

    drawSplash();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        attempts++;
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
    } else {
        Serial.println("\nWiFi FAILED");
    }

    drawInput();
}

void loop() {
    M5Cardputer.update();

    if (isLoading) return;

    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

        // === BROWSING ===
        if (browsing) {
            for (auto i : status.word) {
                if (i == 'w' || i == 'W') {
                    if (browseSelect > 0) browseSelect--;
                    else if (browseOffset > 0) browseOffset--;
                    M5Cardputer.Speaker.tone(1760, 15);
                    drawBrowse();
                    return;
                }
                if (i == 's' || i == 'S') {
                    int matches = countMatches();
                    if (browseOffset + browseSelect < matches - 1) {
                        if (browseSelect < 9) browseSelect++;
                        else browseOffset++;
                    }
                    M5Cardputer.Speaker.tone(1760, 15);
                    drawBrowse();
                    return;
                }
                if (i != 'w' && i != 'W' && i != 's' && i != 'S') {
                    browseFilter += i;
                    browseFilter.toUpperCase();
                    browseOffset = 0;
                    browseSelect = 0;
                    M5Cardputer.Speaker.tone(1760, 30);
                    drawBrowse();
                    return;
                }
            }
            if (status.enter) {
                String selected = getSelectedAnimal();
                if (selected.length() > 0) {
                    browsing = false;
                    inputText = selected;
                    fetchAnimal(selected);
                }
                return;
            }
            if (status.del) {
                if (browseFilter.length() > 0) {
                    browseFilter.remove(browseFilter.length() - 1);
                    browseOffset = 0;
                    browseSelect = 0;
                    drawBrowse();
                } else {
                    browsing = false;
                    inputText = "";
                    drawInput();
                }
            }
            return;
        }

        // === VIEWING ANSWER ===
        if (viewingAnswer) {
            if (status.del) redrawEntry();
            if (status.enter) { viewingAnswer = false; inputText = ""; drawInput(); return; }
            for (auto i : status.word) {
                if (i == 'r' || i == 'R') { redrawEntry(); return; }
            }
            return;
        }

        // === VIEWING QUESTIONS ===
        if (viewingQuestions) {
            for (auto i : status.word) {
                if (i == '1' && question1.length() > 0) { viewingQuestions = false; askQuestion(question1); return; }
                if (i == '2' && question2.length() > 0) { viewingQuestions = false; askQuestion(question2); return; }
            }
            if (status.del) { viewingQuestions = false; redrawEntry(); }
            return;
        }

        // === VIEWING ENTRY ===
        if (viewingEntry) {
            for (auto i : status.word) {
                if (i == 'a' || i == 'A') { speakEntry(); return; }
                if (i == 'q' || i == 'Q') { if (question1.length() > 0) { viewingQuestions = true; showQuestions(); } return; }
                if (i == 'c' || i == 'C') { showQRCode(); return; }
                if (i == 'r' || i == 'R') { if (lastAnswer.length() > 0) redrawAnswer(); return; }
            }
            if (status.enter) { viewingEntry = false; inputText = ""; drawInput(); return; }
            if (status.del) {
                viewingEntry = false;
                inputText = "";
                currentNarration = "";
                question1 = "";
                question2 = "";
                lastEntryJson = "";
                lastAnswer = "";
                lastQuestion = "";
                drawInput();
            }
            return;
        }

        // === INPUT SCREEN ===
        if (inputText.length() == 0) {
            for (auto i : status.word) {
                if (i == 'r' || i == 'R') {
                    M5Cardputer.Speaker.tone(262, 60); delay(70);
                    M5Cardputer.Speaker.tone(330, 60); delay(70);
                    M5Cardputer.Speaker.tone(392, 60); delay(70);
                    M5Cardputer.Speaker.tone(523, 60); delay(70);
                    M5Cardputer.Speaker.tone(659, 60); delay(70);
                    M5Cardputer.Speaker.tone(784, 120);
                    inputText = "RANDOM";
                    fetchAnimal("Pick a random interesting wild animal and generate its entry");
                    return;
                }
                if (i == 'b' || i == 'B') {
                    browsing = true;
                    browseFilter = "";
                    browseOffset = 0;
                    browseSelect = 0;
                    drawBrowse();
                    return;
                }
            }
        }

        if (status.enter && inputText.length() > 0) { fetchAnimal(inputText); return; }

        if (status.del && inputText.length() > 0) {
            M5Cardputer.Speaker.tone(1760, 30);
            inputText.remove(inputText.length() - 1);
            drawInput();
            return;
        }

        for (auto i : status.word) {
            M5Cardputer.Speaker.tone(1760, 30);
            inputText += i;
            inputText.toUpperCase();
        }

        drawInput();
    }
}
