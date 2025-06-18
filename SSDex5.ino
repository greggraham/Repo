// created with Github Copilot
// connect a potentiometer to A0

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PADDLE_WIDTH 24
#define PADDLE_HEIGHT 4
#define PADDLE_Y (SCREEN_HEIGHT - 8)
#define BALL_SIZE 4
#define BRICK_ROWS 3
#define BRICK_COLS 8
#define BRICK_WIDTH 15
#define BRICK_HEIGHT 6

int paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
int ballX = SCREEN_WIDTH / 2;
int ballY = SCREEN_HEIGHT / 2;
int ballDX = 2;
int ballDY = -2;

bool bricks[BRICK_ROWS][BRICK_COLS];

void resetBricks() {
  for (int r = 0; r < BRICK_ROWS; r++)
    for (int c = 0; c < BRICK_COLS; c++)
      bricks[r][c] = true;
}

void setup() {
  pinMode(A0, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  ballX = random(10, SCREEN_WIDTH - 10);
  resetBricks();
}

void loop() {
  // Paddle control
  int pot = analogRead(A0);
  paddleX = map(pot, 0, 1023, 0, SCREEN_WIDTH - PADDLE_WIDTH);

  // Ball movement
  ballX += ballDX;
  ballY += ballDY;

  // Wall collision
  if (ballX <= 0 || ballX >= SCREEN_WIDTH - BALL_SIZE) ballDX = -ballDX;
  if (ballY <= 0) ballDY = -ballDY;

  // Paddle collision
  if (ballY + BALL_SIZE >= PADDLE_Y && ballY + BALL_SIZE <= PADDLE_Y + PADDLE_HEIGHT &&
      ballX + BALL_SIZE >= paddleX && ballX <= paddleX + PADDLE_WIDTH) {
    ballDY = -ballDY;
    ballY = PADDLE_Y - BALL_SIZE; // Prevent sticking
  }

  // Brick collision
  for (int r = 0; r < BRICK_ROWS; r++) {
    for (int c = 0; c < BRICK_COLS; c++) {
      if (bricks[r][c]) {
        int bx = c * BRICK_WIDTH;
        int by = r * BRICK_HEIGHT + 8;
        if (ballX + BALL_SIZE > bx && ballX < bx + BRICK_WIDTH &&
            ballY + BALL_SIZE > by && ballY < by + BRICK_HEIGHT) {
          bricks[r][c] = false;
          ballDY = -ballDY;
        }
      }
    }
  }

  // Missed ball
  if (ballY > SCREEN_HEIGHT) {
    ballX = random(10, SCREEN_WIDTH - 10);
    ballY = SCREEN_HEIGHT / 2;
    if (random(2) == 0) {
      ballDX = 2;
    } else {
      ballDX = -2;
    }
    ballDY = -2;
    resetBricks();
  }

  // Draw everything
  display.clearDisplay();
  // Draw bricks
  for (int r = 0; r < BRICK_ROWS; r++)
    for (int c = 0; c < BRICK_COLS; c++)
      if (bricks[r][c])
        display.fillRect(c * BRICK_WIDTH, r * BRICK_HEIGHT + 8, BRICK_WIDTH - 2, BRICK_HEIGHT - 2, SSD1306_WHITE);
  // Draw paddle
  display.fillRect(paddleX, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  // Draw ball
  display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, SSD1306_WHITE);

  display.display();
  delay(15); // change this number to change speed
}