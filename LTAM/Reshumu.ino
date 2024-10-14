//---------------RESHUMU--------------------------------
//---------------led1
void led1_fireTick() {
  static uint32_t prevTime;
  // move the flame
  if (millis() - prevTime > 20) {
    prevTime = millis();
    int thisPos = 0, lastPos = 0;
    FOR_i(0, LED1_NUM) {
      micro_led1[i] = led1_getFireColor((inoise8(i * 5, led1_firetick_counter)));        // step of fire   15(instead of 5)
    }
    led1_firetick_counter += 20;
    strip.setBrightness(en1_yarkost);
    strip.show();
  }
}
void led1_raduga(){
    for (int i = 0; i < LED1_NUM; i++ ) {         // from 0 to first third
    fast_led[0][i] = CHSV(counter + i * 2, 255, 255);  // HSV. Increase HUE (color)
    // умножение i уменьшает шаг радуги
  }
  counter++;        // counter varies from 0 to 255 (byte data type)
  FastLED[0].showLeds(en1_yarkost);
}
void led1_color_bounceFADE() {
  if (led1_bouncedirection == 0) {
    led1_idex = led1_idex + 1;
    if (led1_idex == LED1_NUM) {
      led1_bouncedirection = 1;
      led1_idex = led1_idex - 1;
    }
  }
  if (led1_bouncedirection == 1) {
    led1_idex = led1_idex - 1;
    if (led1_idex == 0) {
      led1_bouncedirection = 0;
    }
  }
  int iL1 = led1_color_bounceFADE_adjacent_cw(led1_idex);
  int iL2 = led1_color_bounceFADE_adjacent_cw(iL1);
  int iL3 = led1_color_bounceFADE_adjacent_cw(iL2);
  int iR1 = led1_color_bounceFADE_adjacent_ccw(led1_idex);
  int iR2 = led1_color_bounceFADE_adjacent_ccw(iR1);
  int iR3 = led1_color_bounceFADE_adjacent_ccw(iR2);
  for (int i = 0; i < LED1_NUM; i++ ) {
    if (i == led1_idex) {
      fast_led[0][i] = CHSV(thishue, thissat, 255);
    }
    else if (i == iL1) {
      fast_led[0][i] = CHSV(thishue, thissat, 150);
    }
    else if (i == iL2) {
      fast_led[0][i] = CHSV(thishue, thissat, 80);
    }
    else if (i == iL3) {
      fast_led[0][i] = CHSV(thishue, thissat, 20);
    }
    else if (i == iR1) {
      fast_led[0][i] = CHSV(thishue, thissat, 150);
    }
    else if (i == iR2) {
      fast_led[0][i] = CHSV(thishue, thissat, 80);
    }
    else if (i == iR3) {
      fast_led[0][i] = CHSV(thishue, thissat, 20);
    }
    else {
      fast_led[0][i] = CHSV(0, 0, 0);
    }
  }
  delay(30);
  FastLED[0].showLeds(en1_yarkost);
}
void led1_pulse_one_color_all_rev() {
  if (led1_bouncedirection == 0) {
    isat++;
    if (isat >= 255) {
      led1_bouncedirection = 1;
    }
  }
  if (led1_bouncedirection == 1) {
    isat = isat - 1;
    if (isat <= 1) {
      led1_bouncedirection = 0;
    }
  }
  for (int led1_idex = 0 ; led1_idex < LED1_NUM; led1_idex++ ) {
    fast_led[0][led1_idex] = CHSV(thishue, isat, 255);
  }
  FastLED[0].showLeds(en1_yarkost);
}
void led1_random_march() {                   //-m14-RANDOM MARCH CCW
  led1_copy_led_array();
  int iCCW;
  fast_led[0][0] = CHSV(random(0, 255), 255, 255);
  for (int led1_idex = 1; led1_idex < LED1_NUM ; led1_idex++ ) {
    iCCW = led1_adjacent_ccw(led1_idex);
    fast_led[0][led1_idex].r = ledsX[iCCW][0];
    fast_led[0][led1_idex].g = ledsX[iCCW][1];
    fast_led[0][led1_idex].b = ledsX[iCCW][2];
  }
  delay(30);
  FastLED[0].showLeds(en1_yarkost);
}
void led1_flame() {                                    //-m22-FLAMEISH EFFECT
  int idelay = random(0, 35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= TOP_INDEX; i++ ) {
    ihue = ihue + hinc;
    fast_led[0][i] = CHSV(ihue, thissat, 255);
    int ih = horizontal_index(i);
    fast_led[0][ih] = CHSV(ihue, thissat, 255);
    fast_led[0][TOP_INDEX].r = 255; fast_led[0][TOP_INDEX].g = 255; fast_led[0][TOP_INDEX].b = 255;
    delay(30);
    FastLED[0].showLeds(en1_yarkost);
  }
}
void led1_ems_lightsSTROBE() {                  //-m26-EMERGENCY LIGHTS (STROBE LEFT/RIGHT)
  int thishue = 0;
  int thathue = (thishue + 160) % 255;
  for (int x = 0 ; x < 5; x++ ) {
    for (int i = 0 ; i < TOP_INDEX; i++ ) {
      fast_led[0][i] = CHSV(thishue, thissat, 255);
    }
      delay(30);
  FastLED[0].showLeds(en1_yarkost);
    one_color_all(0, 0, 0);
      delay(30);
  FastLED[0].showLeds(en1_yarkost);
  }
  for (int x = 0 ; x < 5; x++ ) {
    for (int i = TOP_INDEX ; i < LED1_NUM; i++ ) {
      fast_led[0][i] = CHSV(thathue, thissat, 255);
    }
      delay(50);
  FastLED[0].showLeds(en1_yarkost);
    one_color_all(0, 0, 0);
      delay(50);
  FastLED[0].showLeds(en1_yarkost);
  }
}


void led1_rgb_propeller() {                           //-m27-RGB PROPELLER
  led1_idex++;
  int ghue = (thishue + 80) % 255;
  int bhue = (thishue + 160) % 255;
  int N3  = int(LED1_NUM / 3);
  int N6  = int(LED1_NUM / 6);
  int N12 = int(LED1_NUM / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (led1_idex + i + LED1_NUM - N12) % LED1_NUM;
    int j1 = (j0 + N3) % LED1_NUM;
    int j2 = (j1 + N3) % LED1_NUM;
    fast_led[0][j0] = CHSV(thishue, thissat, 255);
    fast_led[0][j1] = CHSV(ghue, thissat, 255);
    fast_led[0][j2] = CHSV(bhue, thissat, 255);
  }
  delay(30);
  FastLED[0].showLeds(en1_yarkost);
}


//---------------led2
void led2_background() {

  if (!led2_state) led2_state = true;
  off_timer = millis();  

  for (i = 0; i < sizeof prefix; ++i) {
waitLoop: while (!Serial.available()) led2_background_connection();;
    if (prefix[i] == Serial.read()) continue;
    i = 0;
    goto waitLoop;
  }

  while (!Serial.available()) led2_background_connection();;
  hi = Serial.read();
  while (!Serial.available()) led2_background_connection();;
  lo = Serial.read();
  while (!Serial.available()) led2_background_connection();;
  chk = Serial.read();
  if (chk != (hi ^ lo ^ 0x55))
  {
    i = 0;
    goto waitLoop;
  }

  memset(fast_led[1], 0, LED2_NUM * sizeof(struct CRGB));
  for (int i = 0; i < LED2_NUM; i++) {
    byte r, g, b;
    // читаем данные для каждого цвета
    while (!Serial.available()) led2_background_connection();
    r = Serial.read();
    while (!Serial.available()) led2_background_connection();
    g = Serial.read();
    while (!Serial.available()) led2_background_connection();
    b = Serial.read();
    fast_led[1][i].r = r;
    fast_led[1][i].g = g;
    fast_led[1][i].b = b;
  }
  FastLED[1].showLeds(en2_yarkost);
}
void led2_white(){
  fill_solid(fast_led[1], LED2_NUM, CRGB::FloralWhite);
  FastLED[1].showLeds(en2_yarkost);
  }
void led2_color_bounce() {
  if (led2_bouncedirection == 0) {
    led2_idex = led2_idex + 1;
    if (led2_idex == LED2_NUM) {
      led2_bouncedirection = 1;
      led2_idex = led2_idex - 1;
    }
  }
  if (led2_bouncedirection == 1) {
    led2_idex = led2_idex - 1;
    if (led2_idex == 0) {
      led2_bouncedirection = 0;
    }
  }
  for (int i = 0; i < LED2_NUM; i++ ) {
    if (i == led2_idex) {
      fast_led[1][i] = CHSV(thishue, thissat, 255);
    }
    else {
      fast_led[1][i] = CHSV(0, 0, 0);
    }
  }
  delay(30);
  FastLED[1].showLeds(en2_yarkost);
}


//---------------DOP K RESHUMAM--------------------------------
LEDdata led1_getFireColor(int val) {
  // the larger val, the more the color shifts, saturation drops and brightness increases
  return mHSV(
           0 + map(val, 0, 255, 0, 15),                           // H       initial fire color (0 red, 80 green, 140 lightning, 190 pink) (instead of HUE_START (0)) cast by hue 21 (instead of 4 variable (15))
           constrain(map(val, 0, 255, 255, 245), 0, 255),        // S        MAX_SAT = 255, MIN_SAT = 245            saturation
           constrain(map(val, 0, 255, 1, 255), 0, 255)         // V         MIN_BRIGHT = 70, MAX_BRIGHT = 255       fire brightness
         );

}
//---------------led1_color_bounceFADE
int led1_color_bounceFADE_adjacent_cw(int i) {
  int r;
  if (i < LED1_NUM - 1) {
    r = i + 1;
  }
  else {
    r = 0;
  }
  return r;
}
int led1_color_bounceFADE_adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = LED1_NUM - 1;
  }
  return r;
}
//---------------led1_random_march
void led1_copy_led_array() {
  for (int i = 0; i < LED1_NUM; i++ ) {
    ledsX[i][0] = fast_led[0][i].r;
    ledsX[i][1] = fast_led[0][i].g;
    ledsX[i][2] = fast_led[0][i].b;
  }
}
int led1_adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = LED1_NUM - 1;
  }
  return r;
}
//---------------led1_flame
int horizontal_index(int i) {
  //-ONLY WORKS WITH INDEX < TOPINDEX
  if (i == BOTTOM_INDEX) {
    return BOTTOM_INDEX;
  }
  if (i == TOP_INDEX && EVENODD == 1) {
    return TOP_INDEX + 1;
  }
  if (i == TOP_INDEX && EVENODD == 0) {
    return TOP_INDEX;
  }
  return LED1_NUM - i;
}
//---------------led1_ems_lightsSTROBE
void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED1_NUM; i++ ) {
    fast_led[0][i].setRGB( cred, cgrn, cblu);
  }
}

//---------------led2
void led2_background_connection() {
  if (led2_state) {
    if (millis() - off_timer > (1000000 * 1000)) {                     //10000 * 1000    --->  100000 * 1000
      bt2_value = 2;
      led2_state = false;
      fill_solid(fast_led[1], LED2_NUM, CRGB::Black);
      FastLED[1].showLeds(en2_yarkost);
    }
  }
}
