int getTime();

void setup() {
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(getTime());
  delay(500);
}

int getTime(){
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(5);
  digitalWrite(12, LOW);

  return pulseIn(13, HIGH);
}
