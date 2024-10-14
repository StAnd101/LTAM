void void_button() {
  //CLICK HANDLER
  bool btnState1 = digitalRead(BT1_PIN);
  if (btnState1 && !flag1) {          // click handler
    flag1 = true;
  } else if (!btnState1 && flag1) {  // release handler
    bt1_value++;
    flag1 = false;
  }

  bool btnState2 = digitalRead(BT2_PIN);
  if (btnState2 && !flag2) {          // click handler
    flag2 = true;
  } else if (!btnState2 && flag2) {  // release handler
    bt2_value++;
    flag2 = false;
  }

  bool btnState3 = digitalRead(BT3_PIN);
  if (btnState3 && !flag3) {          // click handler
    flag3 = true;
  } else if (!btnState3 && flag3) {  // release handler
    bt3_value++;
    flag3 = false;
  }

  ////MODE HANDLER FOR LENTA
  if (bt1_value > BT1_KOL_RESHUMOV) {
    bt1_value = 1;
  } else if (bt1_value < 0) {
    bt1_value = BT1_KOL_RESHUMOV;
  }
  if (bt2_value > BT2_KOL_RESHUMOV) {
    bt2_value = 1;
  } else if (bt2_value < 0) {
    bt2_value = BT2_KOL_RESHUMOV;
  }
  if (bt3_value > BT3_KOL_RESHUMOV) {
    bt3_value = 1;
  } else if (bt3_value < 0) {
    bt3_value = BT3_KOL_RESHUMOV;
  }
  void_reshumu();
}
void void_encoder(){
  en1_yarkost = map(analogRead(EN1_PIN), 0, 1000, 10, 250);
  en2_yarkost = map(analogRead(EN2_PIN), 0, 1000, 10, 250);
  en3_yarkost = map(analogRead(EN3_PIN), 0, 1000, 10, 250);
}
void void_reshumu() {
  switch (bt1_value) {
    case  1: led1_raduga(); break;
    case  2: led1_fireTick(); break;
    case  3: led1_color_bounceFADE(); break;
    case  4: led1_pulse_one_color_all_rev(); break;
    case  5: led1_random_march(); break;
    case  6: led1_rgb_propeller(); break;
    case  7: led1_flame(); break;
    case  8: led1_ems_lightsSTROBE(); break;
    case  9: ; break;
    case  10: ; break;
    case  11: ; break;
    case  12: ; break;
    case  13: ; break;
  }
  switch (bt2_value) {
    case  1: led2_white(); break;
    case  2: led2_color_bounce(); break;
    case  3: led2_background();; break;
    case  4: ; break;
    case  5: ; break;
  }
  switch (bt3_value) {
    case  1: ; break;
    case  2: ; break;
    case  3: ; break;
    case  4: ; break;
    case  5: ; break;
  }
}
