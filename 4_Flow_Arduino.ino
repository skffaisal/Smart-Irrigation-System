#define PULSE_PIN D1  //gpio1
#define PULSE_PIN1 D2  //gpio2
#define PULSE_PIN2 D3  //gpio3
#define PULSE_PIN3 D4  //gpio4
#define LED_PIN D7    //gpio13

volatile long pulseCount=0;
volatile long pulseCount1=0;
volatile long pulseCount2=0;
volatile long pulseCount3=0;
float calibrationFactor = 4.5;
float calibrationFactor1 = 4.5;
float calibrationFactor2 = 4.5;
float calibrationFactor3 = 4.5;
float flowRate;
float flowRate1;
float flowRate2;
float flowRate3;
unsigned int flowMilliLitres;
unsigned int flowMilliLitres1;
unsigned int flowMilliLitres2;
unsigned int flowMilliLitres3;
unsigned long totalMilliLitres;
unsigned long totalMilliLitres1;
unsigned long totalMilliLitres2;
unsigned long totalMilliLitres3;
float totalLitres;
float totalLitres1;
float totalLitres2;
float totalLitres3;
unsigned long oldTime;
unsigned long oldTime1;
unsigned long oldTime2;
unsigned long oldTime3;
void ICACHE_RAM_ATTR pulseCounter()
{
  pulseCount++;
}

void ICACHE_RAM_ATTR pulseCounter1()
{
  pulseCount1++;
}
void ICACHE_RAM_ATTR pulseCounter2()
{
  pulseCount2++;
}
void ICACHE_RAM_ATTR pulseCounter3()
{
  pulseCount3++;
}
void setup()
{
  Serial.begin(9600);

  pulseCount        = 0;
  pulseCount1        = 0;
  pulseCount2        = 0;
  pulseCount3        = 0;
  flowRate          = 0.0;
  flowRate1          = 0.0;
  flowRate2          = 0.0;
  flowRate3          = 0.0;
  flowMilliLitres   = 0;
  flowMilliLitres1   = 0;
  flowMilliLitres2   = 0;
  flowMilliLitres3   = 0;
  totalMilliLitres  = 0;
  totalMilliLitres1  = 0;
  totalMilliLitres2  = 0;
  totalMilliLitres3  = 0;
  oldTime           = 0; 
  oldTime1           = 0;
  oldTime2           = 0;  
  oldTime3           = 0;  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // We have an active-low LED attached
  pinMode(PULSE_PIN, INPUT);
  attachInterrupt(PULSE_PIN, pulseCounter, FALLING);
  pinMode(PULSE_PIN1, INPUT);
  attachInterrupt(PULSE_PIN1, pulseCounter, FALLING);
  pinMode(PULSE_PIN2, INPUT);
  attachInterrupt(PULSE_PIN2, pulseCounter, FALLING);  
  pinMode(PULSE_PIN3, INPUT);
  attachInterrupt(PULSE_PIN3, pulseCounter, FALLING);  
}

void loop()
{
   if((millis() - oldTime) > 1000)    // Only process counters once per second
  {
    detachInterrupt(PULSE_PIN);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;     
    totalLitres = totalMilliLitres * 0.001;
    unsigned int frac;   
    Serial.print("flowrate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min");
    Serial.print("  Current Liquid Flowing: ");             // Output separator
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");
    Serial.print("  Output Liquid Quantity: ");             // Output separator
    Serial.print(totalLitres);
    Serial.println("L");
    //Serial.print(totalMilliLitres);
    //Serial.println("mL");

    pulseCount = 0;

    attachInterrupt(PULSE_PIN, pulseCounter, FALLING);
  }
   if((millis() - oldTime1) > 1000)    // Only process counters once per second
  {
    detachInterrupt(PULSE_PIN1);
    flowRate1 = ((1000.0 / (millis() - oldTime1)) * pulseCount1) / calibrationFactor1;
    oldTime1 = millis();
    flowMilliLitres1 = (flowRate1 / 60) * 1000;
    totalMilliLitres1 += flowMilliLitres1;     
    totalLitres1 = totalMilliLitres1 * 0.001;
    unsigned int frac1;   
    Serial.print("flowrate1: ");
    Serial.print(int(flowRate1));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    frac1 = (flowRate1 - int(flowRate1)) * 10;
    Serial.print(frac1, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min1");
    Serial.print("  Current Liquid Flowing1: ");             // Output separator
    Serial.print(flowMilliLitres1);
    Serial.print("mL/Sec1");
    Serial.print("  Output Liquid Quantity1: ");             // Output separator
    Serial.print(totalLitres1);
    Serial.println("L1");
    //Serial.print(totalMilliLitres);
    //Serial.println("mL");

    pulseCount1 = 0;

    attachInterrupt(PULSE_PIN1, pulseCounter1, FALLING);
  }
   if((millis() - oldTime2) > 1000)    // Only process counters once per second
  {
    detachInterrupt(PULSE_PIN2);
    flowRate2 = ((1000.0 / (millis() - oldTime2)) * pulseCount2) / calibrationFactor2;
    oldTime2 = millis();
    flowMilliLitres2 = (flowRate2 / 60) * 1000;
    totalMilliLitres2 += flowMilliLitres2;     
    totalLitres2 = totalMilliLitres2 * 0.001;
    unsigned int frac2;   
    Serial.print("flowrate2: ");
    Serial.print(int(flowRate2));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    frac2 = (flowRate2 - int(flowRate2)) * 10;
    Serial.print(frac2, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min2");
    Serial.print("  Current Liquid Flowing2: ");             // Output separator
    Serial.print(flowMilliLitres2);
    Serial.print("mL/Sec2");
    Serial.print("  Output Liquid Quantity2: ");             // Output separator
    Serial.print(totalLitres2);
    Serial.println("L2");
    //Serial.print(totalMilliLitres);
    //Serial.println("mL");

    pulseCount2 = 0;

    attachInterrupt(PULSE_PIN2, pulseCounter2, FALLING);
  }
   if((millis() - oldTime3) > 1000)    // Only process counters once per second
  {
    detachInterrupt(PULSE_PIN3);
    flowRate3 = ((1000.0 / (millis() - oldTime3)) * pulseCount3) / calibrationFactor3;
    oldTime3 = millis();
    flowMilliLitres3 = (flowRate3 / 60) * 1000;
    totalMilliLitres3 += flowMilliLitres3;     
    totalLitres3 = totalMilliLitres3 * 0.001;
    unsigned int frac3;   
    Serial.print("flowrate3: ");
    Serial.print(int(flowRate3));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    frac3 = (flowRate3 - int(flowRate3)) * 10;
    Serial.print(frac3, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min3");
    Serial.print("  Current Liquid Flowing3: ");             // Output separator
    Serial.print(flowMilliLitres3);
    Serial.print("mL/Sec3");
    Serial.print("  Output Liquid Quantity3: ");             // Output separator
    Serial.print(totalLitres3);
    Serial.println("L3");
    //Serial.print(totalMilliLitres);
    //Serial.println("mL");

    pulseCount3 = 0;

    attachInterrupt(PULSE_PIN3, pulseCounter3, FALLING);
  }  
}
