class Sonar
{
  public:
    void pin(int pin);
    int ping();
  private:
    int _pin;
    int duration;
};

void Sonar::pin(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

int Sonar::ping()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pin, LOW);

  pinMode(_pin, INPUT);
  duration = int(pulseIn(_pin, HIGH));

  return duration;
}