#include <DistanceSensor.h>
#include <LiquidCrystal_I2C.h>

constexpr int TrigPin = 12;
constexpr int EchoPin = 11;
int RED = 7;
int GREEN = 6;
int BLUE = 5;

DistanceSensor<TrigPin, EchoPin> sensor;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{ lcd.init();
  lcd.backlight();
  sensor.begin();
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("ultrasonic ruler");
  delay(2500);
}

void loop()
{

  int result = sensor.tick();
  if (result == sensor.NREADY) {
    return;
  }
  else if (result == sensor.ERR)
  {
    Serial.println("error occured");
    return;
  }

  if (result<=15){
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,HIGH);
  }

  else{
    digitalWrite(RED,LOW);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,LOW);
  }
  if (result>820){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NIL");
  }
  else {
  Serial.print(result);
  Serial.print("\n");
  lcd.setCursor(0,0);
  lcd.print(result);
  lcd.print("cm");
  delay(200);
  lcd.clear();
  }
}
