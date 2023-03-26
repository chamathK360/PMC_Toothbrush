#include "Wire.h"

#include "I2Cdev.h"
#include "TCA6424A.h"

TCA6424A tca;

#define SOLO_01 PI_6
#define SOLO_02 PH_9
#define SOLO_03 PJ_9
#define SOLO_04 PE_2
#define SOLO_05 PI_3
#define SOLO_06 PI_2
#define SOLO_07 PD_3
#define SOLO_08 PA_14

#define step_resouloustion 400

bool init_ok = false;

void setup() {

  pinMode(SOLO_01, OUTPUT);
  pinMode(SOLO_02, OUTPUT);
  pinMode(SOLO_03, OUTPUT);
  pinMode(SOLO_04, OUTPUT);
  pinMode(SOLO_05, OUTPUT);
  pinMode(SOLO_06, OUTPUT);
  pinMode(SOLO_07, OUTPUT);
  pinMode(SOLO_08, OUTPUT);

  Wire.begin();
  tca.initialize();

  if (tca.testConnection()) {
    // set bank 0 to outputs
    tca.setBankDirection(0, TCA6424A_OUTPUT);  //TCA6424A_INPUT
    tca.setBankDirection(1, TCA6424A_OUTPUT);
    tca.setBankDirection(2, TCA6424A_OUTPUT);
    tca.setBankDirection(3, TCA6424A_OUTPUT);
    tca.setBankDirection(4, TCA6424A_OUTPUT);
    tca.setBankDirection(5, TCA6424A_OUTPUT);
    tca.setBankDirection(6, TCA6424A_OUTPUT);
    tca.setBankDirection(7, TCA6424A_OUTPUT);
    tca.setBankDirection(8, TCA6424A_OUTPUT);
    tca.setBankDirection(9, TCA6424A_OUTPUT);
    tca.setBankDirection(10, TCA6424A_OUTPUT);
    tca.setBankDirection(11, TCA6424A_OUTPUT);
    tca.setBankDirection(12, TCA6424A_OUTPUT);
    tca.setBankDirection(13, TCA6424A_OUTPUT);
    tca.setBankDirection(14, TCA6424A_OUTPUT);
    tca.setBankDirection(15, TCA6424A_OUTPUT);
    tca.setBankDirection(16, TCA6424A_OUTPUT);
    tca.setBankDirection(17, TCA6424A_OUTPUT);
    tca.setBankDirection(18, TCA6424A_OUTPUT);
    tca.setBankDirection(TCA6424A_P11, TCA6424A_INPUT);
    tca.setPinDirection(TCA6424A_P13, TCA6424A_OUTPUT);
    init_ok = true;
  }
}

void loop() {

  SOLO_ACTUATE(SOLO_01, 3000);  //refarance solonid (type your name)
  stepper_move_01(60, 10);
  stepper_move_02(90, 10);
}

void SOLO_ACTUATE(byte name, unsigned int time) {
  digitalWrite(name, HIGH);
  delay(time);
  digitalWrite(name, LOW);
}

void stepper_move_01(int angle, unsigned int speed) {
  angle = angle * step_resouloustion / 360;
  //digitalWrite(dir, HIGH);
  tca.writePin(TCA6424A_P03, HIGH);
  for (int i = 0; i <= round(angle); i++) {
    tca.writePin(TCA6424A_P00, HIGH);
    //digitalWrite(step, HIGH);
    delay(speed);
    tca.writePin(TCA6424A_P00, LOW);
    //digitalWrite(step, LOW);
    delay(speed);
  }
}


void stepper_move_02(int angle, unsigned int speed) {
  angle = angle * step_resouloustion / 360;
  tca.writePin(TCA6424A_P01, HIGH);
  //digitalWrite(dir1, HIGH);
  for (int i = 0; i <= round(angle); i++) {
    tca.writePin(TCA6424A_P02, HIGH);
    //digitalWrite(step1, HIGH);
    delay(speed);
    tca.writePin(TCA6424A_P02, LOW);
    //digitalWrite(step1, LOW);
    delay(speed);
  }
}