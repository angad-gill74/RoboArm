#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 
#define SERVOMAX  580 
#define NUM_SERVOS 6

// 0 = Base, 1-4 = Arm, 5 = Gripper
const int servoChannels[NUM_SERVOS] = {0, 1, 2, 3, 4, 5}; 

const int servoSpeeds[NUM_SERVOS]   = {10, 10, 10, 5, 5, 3}; 

unsigned long lastMoveTime[NUM_SERVOS];
int currentPulse[NUM_SERVOS];

// Selection for Arm
int selectedArmServo = 1; // Servo 1 by default
unsigned long lastButtonPress = 0;

void setup() {
  Serial.begin(115200);
  Dabble.begin("ESP32_Arm_6DOF"); 

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
   
  int startPos = map(90, 0, 180, SERVOMIN, SERVOMAX);

  for(int i=0; i<NUM_SERVOS; i++) {
    currentPulse[i] = startPos;
    pwm.setPWM(servoChannels[i], 0, currentPulse[i]);
    lastMoveTime[i] = 0;
    
    delay(500); 
    
    Serial.print("Servo "); Serial.print(i); Serial.println(" Ready.");
  }
  
  Serial.println("System Ready. Controlling Servo 1.");
}

void loop() {
  Dabble.processInput(); 
  unsigned long currentMillis = millis();

  // Base control (SERVO 0): D-Pad Left/Right
  if (currentMillis - lastMoveTime[0] >= servoSpeeds[0]) {
    if (GamePad.isRightPressed()) {
      currentPulse[0]++; 
      if (currentPulse[0] > SERVOMAX) currentPulse[0] = SERVOMAX;
      pwm.setPWM(servoChannels[0], 0, currentPulse[0]);
      lastMoveTime[0] = currentMillis;
    }
    else if (GamePad.isLeftPressed()) {
      currentPulse[0]--; 
      if (currentPulse[0] < SERVOMIN) currentPulse[0] = SERVOMIN;
      pwm.setPWM(servoChannels[0], 0, currentPulse[0]);
      lastMoveTime[0] = currentMillis;
    }
  }

  // Gripper control (SERVO 5): Square / Cross
  if (currentMillis - lastMoveTime[5] >= servoSpeeds[5]) {
    if (GamePad.isSquarePressed()) {
      currentPulse[5]++; 
      if (currentPulse[5] > SERVOMAX) currentPulse[5] = SERVOMAX;
      pwm.setPWM(servoChannels[5], 0, currentPulse[5]);
      lastMoveTime[5] = currentMillis;
    }
    else if (GamePad.isCrossPressed()) {
      currentPulse[5]--; 
      if (currentPulse[5] < SERVOMIN) currentPulse[5] = SERVOMIN;
      pwm.setPWM(servoChannels[5], 0, currentPulse[5]);
      lastMoveTime[5] = currentMillis;
    }
  }

  // Arm selection (Cycle servos 1-4): Triangle (+) / Circle (-)
  if (currentMillis - lastButtonPress > 250) {
    if (GamePad.isTrianglePressed()) {
      selectedArmServo++;
      if (selectedArmServo > 4) selectedArmServo = 1;
      
      Serial.print("Selected Servo: "); Serial.println(selectedArmServo);
      lastButtonPress = currentMillis;
    }
    else if (GamePad.isCirclePressed()) {
      selectedArmServo--;
      if (selectedArmServo < 1) selectedArmServo = 4;
      
      Serial.print("Selected Servo: "); Serial.println(selectedArmServo);
      lastButtonPress = currentMillis;
    }
  }

  // Arm control (Servo 1-4): D-Pad Up / Down
  int i = selectedArmServo;
  
  if (currentMillis - lastMoveTime[i] >= servoSpeeds[i]) {
    if (GamePad.isUpPressed()) {
      currentPulse[i]++; 
      if (currentPulse[i] > SERVOMAX) currentPulse[i] = SERVOMAX;
      pwm.setPWM(servoChannels[i], 0, currentPulse[i]);
      lastMoveTime[i] = currentMillis;
    }
    else if (GamePad.isDownPressed()) {
      currentPulse[i]--; 
      if (currentPulse[i] < SERVOMIN) currentPulse[i] = SERVOMIN;
      pwm.setPWM(servoChannels[i], 0, currentPulse[i]);
      lastMoveTime[i] = currentMillis;
    }
  }
}