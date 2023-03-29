const short M1 = 2, M2 = 3, M3 = 4, M4 = 5, M5 = 6;  // Stepper Motor Select pins
const short dir1 = 7, step1 = 8;                     //Stepper Motor 1 Driver Pins
const short dir2 = 9, step2 = 10;                    //Stepper Motor 1 Driver Pins
const short LED = 13;                                // For the camera's LED
const int step_delay = 1500;                         //in microseconds
const int step_count = 50;                           //Sets the number of Step Counts for 90 degree rotation
const int move_delay = 475;                          //in MilliSeconds
short clockWise = 1;  
short ena = 1;                               // for setting the refference for clockwise direction
void setup() {
  for (short i = 2; i < 10; i++)
    pinMode(i, OUTPUT);
  // for (short i = 2; i < 10; i++)
  //   digitalWrite(i, LOW);
  Serial.begin(115200);
}
  

void turn(short selected_pin, short direction, short number_of_times) {
  digitalWrite(selected_pin, HIGH);
  if (selected_pin == 2 || selected_pin == 3 || selected_pin == 5) {
    digitalWrite(dir1, direction);
    for (short j = 0; j < step_count * number_of_times; j++) {
      digitalWrite(step1, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(step1, LOW);
      delayMicroseconds(step_delay);
    }
  } else if (selected_pin == 4 || selected_pin == 6) {
    digitalWrite(dir2, direction);
    for (short j = 0; j < step_count * number_of_times; j++) {
      digitalWrite(step2, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(step2, LOW);
      delayMicroseconds(step_delay);
    }
  }
  delayMicroseconds(step_delay);
  digitalWrite(selected_pin, LOW);
}

void turn2(short selected_pin1, short selected_pin2, short direction1, short direction2, short number_of_times) {
  digitalWrite(selected_pin1, HIGH);
  digitalWrite(selected_pin2, HIGH);
  if (selected_pin1 == 3 || selected_pin1 == 5) {
    digitalWrite(dir1, direction1);
    digitalWrite(dir1, direction2);
    for (short j = 0; j < step_count * number_of_times; j++) {
      digitalWrite(step1, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(step1, LOW);
      delayMicroseconds(step_delay);
    }
  }
  if (selected_pin1 == 4 || selected_pin1 == 6) {
    digitalWrite(dir2, direction1);
    digitalWrite(dir2, direction2);
    for (short j = 0; j < step_count * number_of_times; j++) {
      digitalWrite(step2, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(step2, LOW);
      delayMicroseconds(step_delay);
    }
  }
  digitalWrite(selected_pin1, LOW);
  digitalWrite(selected_pin2, LOW);
}

void loop() {
  if (Serial.available()) {
    digitalWrite(ena,0);
    String data = Serial.readStringUntil('\n');
    //String data = "SC4C4A2A4C3C3A4C1A3C5C5C1C2A1A2C3A1A3C4A1A4A2A1C2C1C3A1A3C5A1A5A5C1C5C1C3A1A3A1C4A1A4A1A3C1C3C1C3A1A3A1A5C1C5C5A1A5A1A2C1C2A1C5A1A5A1A2C1C2C5C1C1A5A1C5A1A5C1C5C1C1A5A1C5A1A5C1C1C2A1A3C1A2A1C3C1A4C1C5A1C4C1A5A1A4C1C5A1C4C1A5A1C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C5C1C1A5A1C5A1A5A4C1C1C4C1A4C1C4C5C1C1A5A1C5A1A5A4C1C1C4C1A4C1C4C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C4C1C1A4A1C4A1A4A5C1C1C5C1A5C1C5E";
    for (int i = 0; i < data.length(); i++) {
      if (data[i] == 'S') {
        Serial.println("Solving Started");
        continue;
      } else if (data[i] == 'E') {
        Serial.println("Solving Done");
        break;
      } else if (data[i] == 'A') {  //AntiClock Wise Once
        short selected_pin = data.charAt(i + 1) - '0' + 1;
        turn(selected_pin, !clockWise, 1);
        delay(move_delay);
      } else if (data[i] == 'C') {  //Clock Wise Once
        short selected_pin = data.charAt(i + 1) - '0' + 1;
        turn(selected_pin, clockWise, 1);
        delay(move_delay);
      } else if (data[i] == 'D') {  //AntiClock Wise Twice
        short selected_pin = data.charAt(i + 1) - '0' + 1;
        turn(selected_pin, !clockWise, 2);
        delay(move_delay);
      } else if (data[i] == 'E') {  //Clock Wise Twice
        short selected_pin = data.charAt(i + 1) - '0' + 1;
        turn(selected_pin, clockWise, 2);
        delay(move_delay);

      } else if (data[i] == 'T') {  //Parallel Solving
        short selected_pin_1, selected_pin_2, direction1, direction2;
        if (data[i + 1] == 'A' || data[i + 1] == 'D') {  //AntiClock Wise Once
          selected_pin_1 = data.charAt(i + 2) - '0' + 1;
          direction1 = !clockWise;
        } else if (data[i + 1] == 'C' || data[i + 1] == 'E') {  //Clock Wise Once
          selected_pin_1 = data.charAt(i + 2) - '0' + 1;
        }
        if (data[i + 3] == 'A' || data[i + 3] == 'D') {  //AntiClock Wise Once
          selected_pin_2 = data.charAt(i + 4) - '0' + 1;
          direction1 = !clockWise;
        } else if (data[i + 3] == 'C' || data[i + 3] == 'E') {  //Clock Wise Once
          selected_pin_2 = data.charAt(i + 4) - '0' + 1;
          direction2 = clockWise;
        }
        turn2(selected_pin_1, selected_pin_2, direction1, direction2, 1);
        delay(move_delay);
        i += 4;
      }
    }
    digitalWrite(ena,1);
  } else {
    digitalWrite(ena,1); 
  }
}
// String ->  "SC4C4A2A4C3C3A4C1A3C5C5C1C2A1A2C3A1A3C4A1A4A2A1C2C1C3A1A3C5A1A5A5C1C5C1C3A1A3A1C4A1A4A1A3C1C3C1C3A1A3A1A5C1C5C5A1A5A1A2C1C2A1C5A1A5A1A2C1C2C5C1C1A5A1C5A1A5C1C5C1C1A5A1C5A1A5C1C1C2A1A3C1A2A1C3C1A4C1C5A1C4C1A5A1A4C1C5A1C4C1A5A1C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C5C1C1A5A1C5A1A5A4C1C1C4C1A4C1C4C5C1C1A5A1C5A1A5A4C1C1C4C1A4C1C4C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C2C1C1A2A1C2A1A2A3C1C1C3C1A3C1C3C4C1C1A4A1C4A1A4A5C1C1C5C1A5C1C5E"
