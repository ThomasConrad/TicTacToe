int step = 22;
int dir = 23;
int time = 0;
int period = 3;
bool tick = true;
bool dir_ = true;

void setup()
{
  pinMode(step, OUTPUT);
  pinMode(dir, OUTPUT);
}

void loop()
{

  if (dir_ == true) {
    digitalWrite(dir, HIGH);
  }
  else {
    digitalWrite(dir, LOW);
  }


  if (millis() - time >= period / 2) {
    if (tick) {
      digitalWrite(step, HIGH);
    }
    else if (!tick) {
      digitalWrite(step, LOW);
    }
    tick != tick;
    time = millis();
  }



}

