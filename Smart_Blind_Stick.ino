#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER 7
#define VIBRATION 6
#define WATER_SENSOR A0

long duration;
int distance;
int waterValue;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(VIBRATION, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Ultrasonic Sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Water Sensor
  waterValue = analogRead(WATER_SENSOR);

  bool objectDetected = (distance > 0 && distance < 50);
  bool waterDetected = (waterValue > 300);

  Serial.print("Distance: ");
  Serial.print(distance);

  Serial.print("  Water: ");
  Serial.println(waterValue);

  // BOTH OBJECT AND WATER
  if (objectDetected && waterDetected) {

    digitalWrite(VIBRATION, HIGH);

    tone(BUZZER, 1200);
    delay(200);

    noTone(BUZZER);
    delay(100);

    tone(BUZZER, 1800);
    delay(200);

    noTone(BUZZER);
    delay(100);
  }

  // OBJECT ONLY
  else if (objectDetected) {

    digitalWrite(VIBRATION, HIGH);

    tone(BUZZER, 1500);   // Loud continuous sound
    delay(300);
  }

  // WATER ONLY
  else if (waterDetected) {

    digitalWrite(VIBRATION, LOW);

    tone(BUZZER, 800);
    delay(100);

    noTone(BUZZER);
    delay(100);

    tone(BUZZER, 800);
    delay(100);

    noTone(BUZZER);
    delay(200);
  }

  // NOTHING DETECTED
  else {

    noTone(BUZZER);
    digitalWrite(VIBRATION, LOW);
  }
}
