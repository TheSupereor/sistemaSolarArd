#include <Stepper.h>
#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

const int stepsPerRevolution = 200;  
Stepper earthMotor(stepsPerRevolution, 8, 10, 9, 11);  
Stepper SunMotor(stepsPerRevolution, 4, 6, 5, 7);  

const int echoPinEarth = 2;  
const int trigPinEarth = 3;  

const int echoPinSun = 4;   
const int trigPinSun = 5;   

void setup() {
  Serial.begin(9600);

  pinMode(trigPinEarth, OUTPUT);
  pinMode(echoPinEarth, INPUT);
  pinMode(trigPinSun, OUTPUT);
  pinMode(echoPinSun, INPUT);

  earthMotor.setSpeed(10);  // velocidade 
  SunMotor.setSpeed(10);  // velocidade 
  initializeLS();
}

void loop() {
  rotatePlanetEarth(360);
  if (detectObject(trigPinEarth, echoPinEarth)) {
    Serial.println("Objeto próximo à Terra!");
    // planetMotor.stop();
  }

  // Rotação da Lua
  rotatePlanetSun(30);
  if (detectObject(trigPinSun, echoPinSun)) {
    Serial.println("Objeto próximo à Lua!");
    // planetMotor.stop();
  }

  int distancia = getDistanceMM();
  delay(1000);  
}

void rotatePlanetEarth(int rotationDegrees) {
  Serial.print("Rotacionando " + planetName + " por " + String(rotationDegrees) + " graus... ");
  earthMotor.step(rotationDegrees * stepsPerRevolution / 360);
  Serial.println("Concluído.");
}

void rotatePlanetSun(int rotationDegrees) {
  Serial.print("Rotacionando " + planetName + " por " + String(rotationDegrees) + " graus... ");
  SunMotor.step(rotationDegrees * stepsPerRevolution / 360);
  Serial.println("Concluído.");
}

bool detectObject(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  if (distance < 20) { 
    return true;        // Objeto detectado
  } else {
    return false;       // Nenhum objeto detectado
  }
}

void initializeSensor(){
  while (!Serial) delay(10);

  Serial.println(F("Adafruit VL53L1X sensor demo"));

  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());
}

int getDistanceMM(){
  int16_t distance;

  if (vl53.dataReady()) {
    distance = vl53.distance();
    if (distance == -1) {
      Serial.print(F("Couldn't get distance: "));
      Serial.println(vl53.vl_status);
      return;
    }
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(" mm");

    vl53.clearInterrupt();
    return distance;
  }
}
