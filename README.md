# LCD Game with Arduino

This is a simple Arduino game using an LCD display, where a player controls a character that jumps to avoid obstacles. The game keeps track of the player's score and ends when the character collides with an obstacle.

## Features
- **Character and Obstacle Display:** Uses custom characters for the player and obstacles.
- **Score Counter:** Displays the current score in the top-right corner.
- **Game Over Screen:** Shows when the character collides with an obstacle.
- **Buzzer Sounds:** Provides sound feedback for actions and game events.

## Hardware Requirements
- Arduino
- LCD Display with I2C (16x2)
- Push Button
- Buzzer
- Resistor (for button if not using `INPUT_PULLUP`)

## Circuit Setup
1. Connect the LCD display to the Arduino using I2C.
2. Connect a push button to pin `2` and set it as `INPUT_PULLUP`.
3. Connect a buzzer to pin `4` for sound feedback.

## Code Explanation

1. **Libraries and Setup:**
   - Includes `LiquidCrystal_I2C` and `Wire` libraries for LCD communication.
   - Initializes the LCD with address `0x27` and screen size `16x2`.
   
2. **Character Customization:**
   - Defines custom characters (skull and tower) to display the player and obstacles on the screen.

3. **Gameplay Logic:**
   - The player can make the character jump by pressing the button.
   - The game ends if the character collides with any obstacle, and the LCD displays a "Game Over" message with the final score.
   - Each time the character successfully reaches the right side of the screen without colliding, the score increments.

4. **Sound Effects:**
   - Buzzer sounds provide feedback for actions (jumping, scoring, game over).

## How to Play
1. Press the button connected to pin `2` to make the character jump.
2. Avoid colliding with obstacles represented as towers on the LCD.
3. When the game ends, the character's score will be displayed.

## Code Overview

```cpp
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Declare LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables for game control
int pos = 0;
int y = 1;
const int buttonPin = 2;
const int buzzerPin = 4;
bool gameOver = false;
int score = 0;

// Custom characters
byte Tengkorak[8] = { ... };
byte Menara[8] = { ... };

// Setup LCD, characters, and pins
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, Tengkorak);
  lcd.createChar(1, Menara);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

// Main game loop
void loop() {
  if (gameOver) return;
  
  // Display towers
  lcd.clear();
  ...

  // Check for jump and handle collision
  if (digitalRead(buttonPin) == LOW) {
    ...
  }

  // Move character and increase score
  pos++;
  ...
}
```

## Dependencies
- `LiquidCrystal_I2C.h`
- `Wire.h`

## License
This project is open-source under the MIT License.
