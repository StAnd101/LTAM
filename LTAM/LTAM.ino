//---------------CONNECTION OF CONTROLL BODIES---------------
//---------------Led Lenta
#define LED1_NUM 60    // number of LEDs
#define LED1_PIN 5    // pin lentu

#define LED2_NUM 32    // number of LEDs
#define LED2_PIN 4    // pin lentu

#define LED3_NUM 71    // number of LEDs
#define LED3_PIN 3    // pin lentu

//---------------Enkoder
#define EN1_PIN 5          //pin encoder 1
#define EN2_PIN 6         //pin encoder 2
#define EN3_PIN 7        //pin encoder 3

//---------------Buttons
#define BT1_PIN 9          //pin button 1
#define BT2_PIN 8         //pin button 2
#define BT3_PIN 7        //pin button 3

//---------------Reshumu
#define BT1_KOL_RESHUMOV 6          //number of modes for button 1
#define BT2_KOL_RESHUMOV 3         //number of modes for button 2
#define BT3_KOL_RESHUMOV 0        //number of modes for button 3


//---------------GLOBAL VARIABLES--------------------------------
//---------------Enkoder
int en1_yarkost = 0;            // brightness of the tape for для LED_1
int en2_yarkost = 0;           // brightness of the tape for LED_2
int en3_yarkost = 0;          // brightness of the tape for LED_3

//---------------Buttons
int bt1_value = 1;              // режим для LED_1
int bt2_value = 1;             // режим для LED_2
int bt3_value = 1;            // режим для LED_3

bool flag1 = false;
bool flag2 = false;
bool flag3 = false;

//---------------SETTINGS---------------
//---------------Obshie Nastroiki
#define CURRENT_LIMIT 1700       // current limit in milliamps
#define KOL_LENT 2              // quantity FastLED lent

#define FOR_i(from, to) for(int i = (from); i < (to); i++)
//---------------FireTrick
#define ORDER_GRB               // color order ORDER_GRB / ORDER_RGB / ORDER_BRG
#define COLOR_DEBTH 3          // color depth: 1, 2, 3 (в байтах)

int led1_firetick_counter = 0;        // variable for fireTick

//---------------Raduga
byte counter;                       //container for rainbow

//---------------color_bounce
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR
int led1_bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
int led2_bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
int led1_idex = 0;                //-LED INDEX (0 to LED_COUNT-1)
int led2_idex = 0;                //-LED INDEX (0 to LED_COUNT-1)

//---------------led1_flame
int BOTTOM_INDEX = 0;        // countdown LED
int TOP_INDEX = int(LED1_NUM / 2);
int EVENODD = LED1_NUM % 2;

//---------------led1_random_march
int isat = 0;                //-SATURATION (0-255)
int ledsX[LED1_NUM][3];

//---------------Background
unsigned long off_timer;
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;        // Ada code word for communication
boolean led2_state = true;                                // tape status flag


//---------------БИБЛИОТЕКИ---------------
//---------------FastLED
#include <FastLED.h>
CRGB fast_led[KOL_LENT][100];                              // creating an array of tapes [number of tapes] [number of LEDs (xs for what)]

//---------------microLED
#include <microLED.h>
LEDdata micro_led1[LED1_NUM];                              // tape buffer of type LEDdata (size depends on COLOR_DEBTH)
microLED strip (micro_led1, LED1_NUM, LED1_PIN);          // object tape


void setup() {
  FastLED.addLeds<WS2811, LED1_PIN, GRB>(fast_led[0], LED1_NUM);          // object tape 0
  FastLED.addLeds<WS2812, LED2_PIN, GRB>(fast_led[1], LED2_NUM);         // object tape 1
  FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT); 
  Serial.begin(115200);
  Serial.print("Ada\n");                                                // Contact computer
  pinMode(BT1_PIN, INPUT_PULLUP);
  pinMode(BT2_PIN, INPUT_PULLUP);
  pinMode(BT3_PIN, INPUT_PULLUP);
}

void loop() {
  void_button();
  void_encoder();

}
