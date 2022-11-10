

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>


#include <dht11.h>


#define POWER_PIN  17 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN 34 // ESP32 pin GIOP34 (ADC6) connected to sensor's signal pin


#define AOUT_PIN 36 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor
#define THRESHOLD 1500 // CHANGE YOUR THRESHOLD HERE


#define SENSOR_PIN 19 // ESP32 pin GIOP19 connected to one wire DS18B20 sensor's DQ pin


#define LIGHT_SENSOR_PIN 39 // ESP32 pin GIOP39 (ADC3)


OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit

int value = 0; // variable to store the sensor value

int DHT11Temp = 0;
int DHT11Hum = 0;
const int DHT11pin = 23;

dht11 DHT;                  //Note:DHT on behalf of the temperature and humidity from first sensor


void setup() {
 
  DS18B20.begin();    // initialize the sensor
  lcd.init();         // initialize the lcd
  lcd.backlight();    // open the backlight

  lcd.setCursor(2, 0); // start to print at the first row
  lcd.print("WELCOME TO");    // print the temperature in Celsius
  lcd.setCursor(3, 1); // start to print at the first row
  lcd.print("THORIUM");    // print the temperature in Celsius
  delay(5000);
    lcd.clear();


      Serial.begin(9600);

  pinMode(DHT11pin, INPUT); 

      
  pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
}

void loop() {
  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0);  // read temperature in Celsius
  tempF = tempC * 9 / 5 + 32; // convert Celsius to Fahrenheit




   digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("The water sensor value: ");
  Serial.println(value);

  delay(1000);



  
  DHT.read(DHT11pin);
  DHT11Temp = DHT.temperature;
  DHT11Hum = DHT.humidity;




 int value = analogRead(AOUT_PIN); // read the analog value from sensor

  if (value < THRESHOLD)
    Serial.print("The soil is DRY (");
  else
    Serial.print("The soil is WET (");

  Serial.print(value);
  Serial.println(")");


  delay(500);



  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 40) {
    Serial.println(" => Dark");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
  } else {
    Serial.println(" => Very bright");
  }

  delay(500);
/*
 lcd.clear();
  lcd.setCursor(0, 0);  // display position
  lcd.print(tempC);     // display the temperature in Celsius
  lcd.print((char)223); // display ° character
  lcd.print("C");
  lcd.setCursor(0, 1);  // display position
  lcd.print(tempF);     // display the temperature in Fahrenheit
  lcd.print((char)223); // display ° character
  lcd.print("F");

  delay(500);
  */

   lcd.setCursor(0, 0); // start to print at the first row
  lcd.print("tempC");    // print the temperature in Celsius
  lcd.setCursor(0, 1); // start to print at the first row
  lcd.print(tempC);    // print the temperature in Celsius

  lcd.setCursor(8, 0); // start to print at the first row
  lcd.print("tempF");    // print the temperature in Celsius
  lcd.setCursor(8, 1);
  lcd.print(tempF);
 
  
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0); // start to print at the first row
  lcd.print("DHTtemp");    // print the temperature in Celsius
  lcd.setCursor(0, 1); // start to print at the first row
  lcd.print(DHT11Temp);    // print the temperature in Celsius  


  lcd.setCursor(8, 0); // start to print at the first row
  lcd.print("DHThum");    // print the temperature in Celsius
  lcd.setCursor(8, 1);
  lcd.print(DHT11Hum);
  
  delay(2000);
  lcd.clear();  
}
