const int res = 52;
void setup() {
  // put your setup code here, to run once:
  pinMode(res,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(res,HIGH);
    delay(1000);
    digitalWrite(res,LOW);
    delay(1000);

}
