int led1 = 10;

void setup()
{
    pinMode(led1, OUTPUT);
}

void loop()
{
    digitalWrite(led1, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    delay(100);
}