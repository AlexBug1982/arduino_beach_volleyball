//#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"       // Fastled library to control the LEDs
#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "modules/BluePlayerClass.h"
#include "modules/RedPlayerClass.h"
#include "modules/PlayerClass.h"
#include "modules/BallClass.h"

// How many leds are connected?
#define NUM_LEDS 162 //18 * 9 grid

// Create the array of retro arcade characters and store it in Flash memory
const long PLAY_FIELD[] PROGMEM =
{
0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xb4864d,
0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d, 0xb4864d
};

#define FIELD_LENGTH 18
#define FIELD_HEIGHT 9

// Define the Data Pin
#define DATA_PIN 6  // Connected to the data pin of the first LED strip

BluePlayer player_blue_one = BluePlayer(4,4);
BluePlayer player_blue_two = BluePlayer(6,5);
RedPlayer player_red_one = RedPlayer(12,4);
RedPlayer player_red_two = RedPlayer(11,2);

Ball ball = Ball(FIELD_LENGTH, FIELD_HEIGHT);

Player players[4];

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);//Initialization of Serial Port
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // Init of the Fastled library
  FastLED.setBrightness(15);

  unsigned long time = micros();
  randomSeed(time);

  players[0] = player_blue_one;
  player_blue_one.setTeamPlayer(&player_blue_two);
  players[1] = player_blue_two;
  player_blue_two.setTeamPlayer(&player_blue_one);
  players[2] = player_red_one;
  player_red_one.setTeamPlayer(&player_red_two);
  players[3] = player_red_two;
  player_red_two.setTeamPlayer(&player_red_one);

  delay(1000);
  defineStartTeam();
  delay(1000);

}

void loop() {
  FastLED.clear();
  for(byte ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    CRGB ledColor = pgm_read_dword(&(PLAY_FIELD[ledIndex]));
    for (byte playerIndex = 0; playerIndex < 4; playerIndex++) {
      Player player = players[playerIndex];
      byte pX = player.getX();
      byte pY = player.getY();
      byte playerLedPos = getLEDpos(pX, pY);
      if (ledIndex == playerLedPos)
      {
        ledColor = player.getColor();
        continue;
      }
    }

    ball.fly();
    byte bX = ball.getCurrent().getX();
    byte bY = ball.getCurrent().getX();
    byte ballLedPos = getLEDpos(bX, bY);
    if (ledIndex == ballLedPos)
    {
      ledColor = ball.getColor();
    }

    leds[ledIndex] = ledColor;
  }
  for (byte pMoveIndex = 0; pMoveIndex < 4; pMoveIndex++) {
    Player playerToMove = players[pMoveIndex];
    playerToMove.move();
    players[pMoveIndex] = playerToMove;
  }
  FastLED.show();
  delay(500);
}

void defineStartTeam() {
  byte r = byte(random(2));
  if (r == 0 ) { 
    //blue
    ball.setStart(0, 6);
    ball.setRandomDestination(true);
  } else {
    //red
    ball.setStart(17, 2);
    ball.setRandomDestination(false);
  }
}

/* 
  Calculates the distance between two x and y objects
*/
double distance(byte* coordA, byte* coordB) {
  byte x1 = coordA[0];
  byte y1 = coordA[1];
  byte x2 = coordB[0];
  byte y2 = coordB[1];
  double distance = sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
  return distance;
}

/* 
  Calcualtes the serial LED Strip id based on x and y coordinates for a serpentine raster
  x = 0 and y = 0 is top left 

  serial ids:
     y0 y1 y2 y3
  x0 0  1  3  4
  x1 8  7  6  5
  x2 9  10 11 12
*/
byte getLEDpos(byte x, byte y){
  byte pos;
  if(y & 0x1) { // is y odd
    pos = y * FIELD_LENGTH + (FIELD_LENGTH -1 - x) ;
  } else { // y is even
    pos = y * FIELD_LENGTH + x;
  }
  return pos;
}