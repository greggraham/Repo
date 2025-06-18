// created with Github Copilot
// connect a potentiometer to A0 and a button to pin 2.

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Controls
#define POT_PIN A0
#define BUTTON_PIN 2

// Player
#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 4
int playerX;

// Bullet
#define BULLET_WIDTH 2
#define BULLET_HEIGHT 4
int bulletX = -1, bulletY = -1;
bool bulletActive = false;

// Invaders
#define INVADER_ROWS 2
#define INVADER_COLS 8
#define INVADER_WIDTH 8
#define INVADER_HEIGHT 6
int invaders[INVADER_ROWS][INVADER_COLS]; // 1 = alive, 0 = dead
int invaderX = 10, invaderY = 10;
int invaderDir = 1; // 1 = right, -1 = left

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  // Initialize invaders
  for (int r = 0; r < INVADER_ROWS; r++)
    for (int c = 0; c < INVADER_COLS; c++)
      invaders[r][c] = 1;
}

void loop() {
  // Player movement
  playerX = map(analogRead(POT_PIN), 0, 1023, 0, SCREEN_WIDTH - PLAYER_WIDTH);

  // Shooting
  static bool lastButton = HIGH;
  bool button = digitalRead(BUTTON_PIN);
  if (button == LOW && lastButton == HIGH && !bulletActive) {
    bulletX = playerX + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
    bulletY = SCREEN_HEIGHT - PLAYER_HEIGHT - BULLET_HEIGHT;
    bulletActive = true;
  }
  lastButton = button;

  // Move bullet
  if (bulletActive) {
    bulletY -= 4;
    if (bulletY < 0) bulletActive = false;
  }

  // Move invaders
  static unsigned long lastMove = 0;
  if (millis() - lastMove > 300) {
    invaderX += invaderDir * 4;
    // Change direction at screen edge
    if (invaderX <= 0 || invaderX + INVADER_COLS * (INVADER_WIDTH + 2) >= SCREEN_WIDTH) {
      invaderDir = -invaderDir;
      invaderY += 8;
    }
    lastMove = millis();
  }

  // Bullet collision with invaders
  if (bulletActive) {
    for (int r = 0; r < INVADER_ROWS; r++) {
      for (int c = 0; c < INVADER_COLS; c++) {
        if (invaders[r][c]) {
          int ix = invaderX + c * (INVADER_WIDTH + 2);
          int iy = invaderY + r * (INVADER_HEIGHT + 2);
          if (bulletX + BULLET_WIDTH > ix && bulletX < ix + INVADER_WIDTH &&
              bulletY + BULLET_HEIGHT > iy && bulletY < iy + INVADER_HEIGHT) {
            invaders[r][c] = 0;
            bulletActive = false;
          }
        }
      }
    }
  }

  // Draw everything
  display.clearDisplay();
  // Draw player
  display.fillRect(playerX, SCREEN_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT, SSD1306_WHITE);
  // Draw bullet
  if (bulletActive)
    display.fillRect(bulletX, bulletY, BULLET_WIDTH, BULLET_HEIGHT, SSD1306_WHITE);
  // Draw invaders
  for (int r = 0; r < INVADER_ROWS; r++) {
    for (int c = 0; c < INVADER_COLS; c++) {
      if (invaders[r][c]) {
        int ix = invaderX + c * (INVADER_WIDTH + 2);
        int iy = invaderY + r * (INVADER_HEIGHT + 2);
        display.drawRect(ix, iy, INVADER_WIDTH, INVADER_HEIGHT, SSD1306_WHITE);
      }
    }
  }
  display.display();

  delay(20);
}