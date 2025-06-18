// created with Github Copilot
// connect a potentiometers to A0 and A1.

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Paddle settings
#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 16
#define PADDLE_MARGIN 2

// Ball settings
#define BALL_SIZE 4

// Potentiometer pins
#define P1_POT A0
#define P2_POT A1

// Game variables
int p1Y = 0, p2Y = 0;
int ballX = SCREEN_WIDTH / 2, ballY = SCREEN_HEIGHT / 2;
int ballVX = 2, ballVY = 2;
int p1Score = 0, p2Score = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  randomSeed(analogRead(A2));
}

void loop() {
  // Read potentiometers and map to paddle positions
  p1Y = map(analogRead(P1_POT), 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  p2Y = map(analogRead(P2_POT), 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);

  // Move ball
  ballX += ballVX;
  ballY += ballVY;

  // Ball collision with top/bottom
  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZE) {
    ballVY = -ballVY;
  }

  // Ball collision with paddles
  // Left paddle
  if (ballX <= PADDLE_MARGIN + PADDLE_WIDTH &&
      ballY + BALL_SIZE >= p1Y && ballY <= p1Y + PADDLE_HEIGHT) {
    ballVX = -ballVX;
    ballX = PADDLE_MARGIN + PADDLE_WIDTH; // Prevent sticking
  }
  // Right paddle
  if (ballX + BALL_SIZE >= SCREEN_WIDTH - PADDLE_MARGIN - PADDLE_WIDTH &&
      ballY + BALL_SIZE >= p2Y && ballY <= p2Y + PADDLE_HEIGHT) {
    ballVX = -ballVX;
    ballX = SCREEN_WIDTH - PADDLE_MARGIN - PADDLE_WIDTH - BALL_SIZE; // Prevent sticking
  }

  // Score check
  if (ballX < 0) {
    p2Score++;
    resetBall();
  }
  if (ballX > SCREEN_WIDTH - BALL_SIZE) {
    p1Score++;
    resetBall();
  }

  // Draw everything
  display.clearDisplay();
  // Draw paddles
  display.fillRect(PADDLE_MARGIN, p1Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  display.fillRect(SCREEN_WIDTH - PADDLE_MARGIN - PADDLE_WIDTH, p2Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  // Draw ball
  display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, SSD1306_WHITE);
  // Draw center line
  for (int i = 0; i < SCREEN_HEIGHT; i += 8) {
    display.drawFastVLine(SCREEN_WIDTH / 2, i, 4, SSD1306_WHITE);
  }
  // Draw scores
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 0);
  display.print(p1Score);
  display.setCursor(SCREEN_WIDTH - 40, 0);
  display.print(p2Score);

  display.display();
  delay(20);
}

void resetBall() {
  ballX = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
  ballY = random(0, SCREEN_HEIGHT - BALL_SIZE);
  ballVX = (random(0, 2) == 0) ? 2 : -2;
  ballVY = (random(0, 2) == 0) ? 2 : -2;
}