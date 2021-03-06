#include <ASMC.h>
#include <avr/wdt.h>
#include "globals.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  while (!Serial && (millis() < 4000));
  InitializeMotors();
}

void loop() {
  // put your main code here, to run repeatedly:
  isWorking = isT1Working || isT2Working || isT3Working || isT4Working || isT5Working || isCooperating;
  if (!isWorking) {
    if (Serial.available() > 0) {
      input_USB = Serial.readStringUntil('/');
      Serial.println(input_USB);
      Command(input_USB);
      input_USB = "";
    }
  }
  delay(100);
}

ISR(TIMER1_COMPA_vect)
{
  ResponseMotorA = MOTOR_A.isrPulse_TIMER1();
  if (digitalRead(MOTOR_A._STLFLT) == 1) {
    count_recovery++;
    total_count_recovery++;
    direction_recovery_z1 *= -1;
    direction_recovery_z2 *= -1;
    Serial.print("count_recovery : "); Serial.println(count_recovery);
    MOTOR_A.SetAtHome();
    MOTOR_B.SetAtHome();
    MOTOR_A.ResetMotors();
    MOTOR_B.ResetMotors();
    currentX = 0;
    currentY = 0;
    currentZ1 = 0;
    currentZ2 = 0;
    currentA = 0;
    currentB = 0;
    currentP = 0;
    ResponseMotorB = 0;
    InitializeMotors();
    RECOVERY_XYZTP();
    if (input_USB != "") {
      Serial.println(input_USB);
      Command(input_USB);
      input_USB = "";
    }
    count_recovery = 0;
  }
  if (ResponseMotorA == 1) {
    MOTOR_B.SetAtHome();
    ResponseMotorA = 0;
    isAtHomeX = true;
    isT1Working = false;
  }
  else if (ResponseMotorA == 10) {
    isDoneRunA = true;
    ResponseMotorA = 0;
    isT1Working = false;
  }
}

ISR(TIMER3_COMPA_vect)
{
  ResponseMotorB = MOTOR_B.isrPulse_TIMER3();
  if (digitalRead(MOTOR_B._STLFLT) == 1) {
    count_recovery++;
    total_count_recovery++;
    direction_recovery_z1 *= -1;
    direction_recovery_z2 *= -1;
    Serial.print("count_recovery : "); Serial.println(count_recovery);
    MOTOR_A.SetAtHome();
    MOTOR_B.SetAtHome();
    MOTOR_A.ResetMotors();
    MOTOR_B.ResetMotors();
    currentX = 0;
    currentY = 0;
    currentZ1 = 0;
    currentZ2 = 0;
    currentA = 0;
    currentB = 0;
    currentP = 0;
    ResponseMotorB = 0;
    InitializeMotors();
    RECOVERY_XYZTP();
    if (input_USB != "") {
      Serial.println(input_USB);
      Command(input_USB);
      input_USB = "";
    }
    count_recovery = 0;
  }
  if (ResponseMotorB == 2) {
    MOTOR_A.SetAtHome();
    ResponseMotorB = 0;
    isAtHomeY = true;
    isT3Working = false;
  }
  else if (ResponseMotorB == 20) {
    isDoneRunB = true;
    ResponseMotorB = 0;
    isT3Working = false;
  }
}

ISR(TIMER4_COMPA_vect)
{
  ResponseMotorZ1 = MOTOR_Z1.isrPulse_TIMER4();
  if (digitalRead(MOTOR_Z1._STLFLT) == 1) {
    count_recovery++;
    total_count_recovery++;
    direction_recovery_z1 *= -1;
    direction_recovery_z2 *= -1;
    Serial.print("count_recovery : "); Serial.println(count_recovery);
    MOTOR_Z1.SetAtHome();
    MOTOR_Z1.ResetMotors();
    currentX = 0;
    currentY = 0;
    currentZ1 = 0;
    currentZ2 = 0;
    currentA = 0;
    currentB = 0;
    currentP = 0;
    ResponseMotorZ1 = 0;
    InitializeMotors();
    RECOVERY_XYZTP();
    if (input_USB != "") {
      Serial.println(input_USB);
      Command(input_USB);
      input_USB = "";
    }
    count_recovery = 0;
  }
  if (ResponseMotorZ1 == 3) {
    ResponseMotorZ1 = 0;
    isAtHomeZ1 = true;
    isT4Working = false;
  }
  else if (ResponseMotorZ1 == 30) {
    isDoneRunZ1 = true;
    ResponseMotorZ1 = 0;
    isT4Working = false;
  }
}

ISR(TIMER5_COMPA_vect)
{
  if (isPumpWorking) {
    ResponseMotorP = MOTOR_P.isrPulse_TIMER5();
    if (ResponseMotorP == 40) {
      ResponseMotorP = 0;
      isAtHomeP = true;
      isDoneRunP = true;
      isT5Working = false;
    }
  }
  else {
    ResponseMotorZ2 = MOTOR_Z2.isrPulse_TIMER5();
    if (digitalRead(MOTOR_Z2._STLFLT) == 1) {
      count_recovery++;
      total_count_recovery++;
      direction_recovery_z1 *= -1;
      direction_recovery_z2 *= -1;
      Serial.print("count_recovery : "); Serial.println(count_recovery);
      MOTOR_Z2.SetAtHome();
      MOTOR_Z2.ResetMotors();
      currentX = 0;
      currentY = 0;
      currentZ1 = 0;
      currentZ2 = 0;
      currentA = 0;
      currentB = 0;
      currentP = 0;
      ResponseMotorZ2 = 0;
      InitializeMotors();
      RECOVERY_XYZTP();
      if (input_USB != "") {
        Serial.println(input_USB);
        Command(input_USB);
        input_USB = "";
      }
      count_recovery = 0;
    }
    if (ResponseMotorZ2 == 4) {
      ResponseMotorZ2 = 0;
      isAtHomeZ2 = true;
      isT5Working = false;
    }
    else if (ResponseMotorZ2 == 40) {
      isDoneRunZ2 = true;
      ResponseMotorZ2 = 0;
      isT5Working = false;
    }
  }
  if (count_recovery == 10) {
    Serial.println("STOP");
    while (true);
  }
  if (total_count_recovery == 30) {
    Serial.println("STOP");
    while (true);
  }
}
