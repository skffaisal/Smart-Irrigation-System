#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
int sensorPin = A0;
void setup()
{ 
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("turbidity:");
  lcd.print("   ");
  lcd.setCursor(10, 0);
  lcd.print(turbidity);
  delay(100);
  if (turbidity < 25) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    lcd.setCursor(0, 1);
    lcd.print(" CLEAR ");
  }
  if ((turbidity > 25) && (turbidity < 60)) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    lcd.setCursor(0, 1);
    lcd.print(" CLOUDY ");
  }
  if (turbidity > 60) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    lcd.setCursor(0, 1);
    lcd.print(" DIRTY ");
  }
}
