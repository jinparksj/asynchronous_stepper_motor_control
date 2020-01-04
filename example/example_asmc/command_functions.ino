void Command(String string_input) {
  Serial.print(">> Command : "); Serial.println(string_input);
  String motorID = string_input.substring(0, 1);
  String running_command = string_input.substring(1);
  char runtype = running_command[0];
  String runvalue = running_command.substring(1);
  Serial.print("Sender : "); Serial.println(senderID);
  Serial.print("Running Command: "); Serial.println(running_command);

  isWorking = true;

  switch (motorID[0]) {
    case '1':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        isT4Working = true;
        isT5Working = true;
        ALLHOME();
        isT1Working = false;
        isT3Working = false;
        isT4Working = false;
        isT5Working = false;
      }
      break;
    case 'X':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        XHOME();
        isT1Working = false;
        isT3Working = false;
      }
      else if (runtype == 'R') {
        isT1Working = true;
        isT3Working = true;
        XYRUN(runvalue.toFloat(), currentY);
        isT1Working = false;
        isT3Working = false;
      }
      break;
    case 'Y':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        YHOME();
        isT1Working = false;
        isT3Working = false;
      }
      else if (runtype == 'R') {
        isT1Working = true;
        isT3Working = true;
        XYRUN(currentX, runvalue.toFloat());
        isT1Working = false;
        isT3Working = false;
      }
      break;
    case 'Z':
      if (runtype == 'H') {
        isT4Working = true;
        Z1HOME();
      }
      else if (runtype == 'R') {
        isT4Working = true;
        Z1RUN(runvalue.toFloat());
      }
      break;
    case 'T':
      if (runtype == 'H') {
        isPumpWorking = false;
        isT5Working = true;
        Z2HOME();
      }
      else if (runtype == 'R') {
        isPumpWorking = false;
        isT5Working = true;
        Z2RUN(runvalue.toFloat());
      }
      break;
    case 'P':
      if (runtype == 'H') {
        isT5Working = true;
        PHOME();
        isT5Working = false;
      }
      else if (runtype == 'R') {
        isT5Working = true;
        PRUN(runvalue.toFloat());
        isT5Working = false;
      }
      else if (runtype == 'C') {
        char speed_mode = runvalue[0];
        if (speed_mode == 'L') {
          LowSpeedMode("P");
        }
        else if (speed_mode == 'H') {
          HighSpeedMode("P");
        }
        else if (speed_mode == 'D') { //Dispense Speed
          LowSpeedMode("P");
        }
      }
      break;
  }
}

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
