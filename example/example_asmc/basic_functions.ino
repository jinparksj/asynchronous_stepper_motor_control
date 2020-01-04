void InitializeMotors() {
  MOTOR_A.InitializeMotors();
  delay(delay_motor);
  MOTOR_B.InitializeMotors();
  delay(delay_motor);
  MOTOR_Z1.InitializeMotors();
  delay(delay_motor);
  MOTOR_Z2.InitializeMotors();
  delay(delay_motor);
  MOTOR_P.InitializeMotors();
  delay(delay_motor);
}

void ConvertXYtoAB(float moving_distance_x, float moving_distance_y) {
  /*
     HBOT CASE 1
      - A = (x - y) / 2;
      - B = (- x - y) / 2;
     HBOT CASE 2
      - A = (X + Y) / 2;
      - B = (X - Y) / 2;
      HBOT CASE 3
      - A = (X - Y) / 2;
      - B = (X + Y) / 2;
  */
  moving_distance_A = (moving_distance_x - moving_distance_y) / 2;
  moving_distance_B = (moving_distance_x + moving_distance_y) / 2;
}

void GoTo1(float x, float y, float z1) {
  XYRUN(x, y);
  Z1RUN(z1);
}

void GoTo2(float x, float y, float z2) {
  XYRUN(x, y);
  Z2RUN(z2);
}

void ALLHOME() {
  Serial.println("All Home");
  Z1HOME();
  Z2HOME();

  bool isAtHomeA = MOTOR_A.CheckAtHome();
  bool isAtHomeB = MOTOR_B.CheckAtHome();

  if ((isAtHomeA == true) && (isAtHomeB == true)) {
    //Out of edge, when it is at home, others just go next
    XYRUN(XY_HOME_SPACE, XY_HOME_SPACE);
    //Y homing
    YHOME();
    //X homing
    XHOME();
  }

  if (isAtHomeB == false) {
    YHOME();
  }

  if (isAtHomeA == false) {
    XHOME();
  }


  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;

  Z1HOME();
  PHOME();
  delay(100);
  Z1HOME();
  YHOME();
  XHOME();

  currentP = 0;
  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;
  currentZ1 = 0;
  currentZ2 = 0;
}

void XHOME() {
  //X homing
  isAtHomeX = false;
  MOTOR_A.Home();
  MOTOR_B.SupportHome();
  while (!isAtHomeX) {
    Serial.print("X");
    delay(belt_motor_delay);
  }
  currentX = 0;
  isAtHomeX = false;

}

void YHOME() {
  //Y homing
  isAtHomeY = false;
  MOTOR_A.SupportHome(30000);
  MOTOR_B.Home();
  while (!isAtHomeY) {
    Serial.print("Y");
    delay(belt_motor_delay);
  }
  currentY = 0;
  isAtHomeY = false;
}

void XYHOME() {
  bool isAtHomeA = MOTOR_A.CheckAtHome();
  bool isAtHomeB = MOTOR_B.CheckAtHome();

  if (isAtHomeB == false) {
    YHOME();
  }

  if (isAtHomeA == false) {
    XHOME();
  }

  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;
}


void XYRUN(float targetX, float targetY) {
  moving_distance_X = targetX - currentX;
  moving_distance_Y = targetY - currentY;

  ConvertXYtoAB(moving_distance_X, moving_distance_Y);
  //  Serial.print("A1 : "); Serial.println(currentA);
  //  Serial.print("B1 : "); Serial.println(currentB);
  //  Serial.print("X1 : "); Serial.println(currentX);
  //  Serial.print("Y1 : "); Serial.println(currentY);
  currentA += moving_distance_A;
  currentB += moving_distance_B;
  currentX = targetX;
  currentY = targetY;

  //  Serial.print("A2 : "); Serial.println(currentA);
  //  Serial.print("B2 : "); Serial.println(currentB);
  //  Serial.print("X2 : "); Serial.println(currentX);
  //  Serial.print("Y2 : "); Serial.println(currentY);

  isDoneRunA = false;
  isDoneRunB = false;
  MOTOR_A.Run(currentA);
  MOTOR_B.Run(currentB);

  while (!isDoneRunA) {
    Serial.print("A");
    delay(belt_motor_delay);
  }
  while (!isDoneRunB) {
    Serial.print("B");
    delay(belt_motor_delay);
  }
  isDoneRunA = false;
  isDoneRunB = false;
}

void Z1HOME() {
  //LIFT Z1
  isAtHomeZ1 = false;
  MOTOR_Z1.Home();
  while (!isAtHomeZ1) {
    Serial.print("Z1");
    delay(belt_motor_delay);
  }
  currentZ1 = 0;
  isAtHomeZ1 = false;
}

void Z2HOME() {
  //LIFT Z2
  isPumpWorking = false;
  isAtHomeZ2 = false;
  Z2RUN(15);
  MOTOR_Z2.Home();
  while (!isAtHomeZ2) {
    Serial.print("Z2");
    delay(belt_motor_delay);
  }
  currentZ2 = 0;
  isAtHomeZ2 = false;
  Z2RUN(-13);
}

void PHOME() {
  isPumpWorking = true;
  isAtHomeP = false;
  MOTOR_P.PumpHome(pump_home_position);
  while (!isAtHomeP)  {
    Serial.print("P");
    delay(pump_motor_delay);
  }
  currentP = 0;
  isAtHomeP = false;
}


void Z1RUN(float target_position) {
  currentZ1 = target_position;
  isDoneRunZ1 = false;
  MOTOR_Z1.Run(target_position);
  while (!isDoneRunZ1) {
    Serial.print("Z1");
    delay(belt_motor_delay);
  }
  isDoneRunZ1 = false;
}

void Z2RUN(float target_position) {
  isPumpWorking = false;
  currentZ2 = target_position;
  isDoneRunZ2 = false;
  MOTOR_Z2.Run(target_position);
  while (!isDoneRunZ2) {
    Serial.print("Z2");
    delay(belt_motor_delay);
  }
  isDoneRunZ2 = false;
}

void PRUN(float target_position) {
  isPumpWorking = true;
  currentP = target_position;
  isDoneRunP = false;
  MOTOR_P.Run(target_position);
  while (!isDoneRunP) {
    delay(pump_motor_delay);
    Serial.print("P");
  }
  isDoneRunP = false;
}

void DRAW(float draw_volume) { // old bsimax script: (-)
  Serial.print("DRAW : "); Serial.print(currentP); Serial.print(" / "); Serial.println(draw_volume);
  float target_volume = currentP + draw_volume;
  PRUN(target_volume);
  delay(500);
}

void DISPENSE(float dispense_volume) {
  Serial.print("DISPENSE : "); Serial.print(currentP); Serial.print(" / "); Serial.println(dispense_volume);
  float target_volume = currentP - dispense_volume;
  PRUN(target_volume);
  delay(500);
}


void SpeedChange(String motor_id, unsigned int maximum_speed, unsigned minimum_speed) {
  if (motor_id == "A") {
    MOTOR_A.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(maximum_speed, minimum_speed);
  }
  delay(delay_motor);
}

void HighSpeedMode(String motor_id) {
  //HighSpeedMode("Z");
  if (motor_id == "A") {
    MOTOR_A.Begin(high_max_speed_AB, high_min_speed_AB);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(high_max_speed_AB, high_min_speed_AB);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(high_max_speed_Z1, high_min_speed_Z1);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(high_max_speed_Z2, high_min_speed_Z2);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(high_max_speed_P, high_min_speed_P);
  }
  delay(delay_motor);
}

void LowSpeedMode(String motor_id) {
  //LowSpeedMode("Z");
  if (motor_id == "A") {
    MOTOR_A.Begin(low_max_speed_AB, low_min_speed_AB);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(low_max_speed_AB, low_min_speed_AB);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(low_max_speed_Z1, low_min_speed_Z1);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(low_max_speed_Z2, low_min_speed_Z2);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(low_max_speed_P, low_min_speed_P);
  }
  delay(delay_motor);
}
