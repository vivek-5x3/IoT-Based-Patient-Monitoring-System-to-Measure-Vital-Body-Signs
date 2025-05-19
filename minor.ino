#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> // Change the library to Adafruit_SH110X.h
#include <MAX30100_PulseOximeter.h>
#include <Adafruit_MLX90614.h>
// Define pin for ECG
#define ECG_PIN A0
// Define screen dimensions and I2C address
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
// Initialize display
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Initialize pulse oximeter
PulseOximeter pox;
// Initialize MLX90614 temperature sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup() {
// Start serial communication
Serial.begin(115200);
// Initialize display
if(!display.begin(SCREEN_ADDRESS)) { // Change here to initialize with SCREEN_ADDRESS
Serial.println(F("SH110X allocation failed"));
for(;;); // Loop forever if display initialization fails

}
display.display();
delay(2000);
display.clearDisplay();
// Initialize MLX90614 sensor
Serial.println("MLX90614 test");
mlx.begin();
// Initialize pulse oximeter
pox.begin();
pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}
void loop() {
// Read temperature from MLX90614
float temperature = mlx.readObjectTempC();
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.println(" °C");
// Read heart rate from pulse oximeter
int heartRate = pox.getHeartRate();
Serial.print("Heart rate: ");
Serial.print(heartRate);
Serial.println(" bpm");
// Read blood oxygen level from pulse oximeter
int oxygen = pox.getSpO2();
Serial.print("Blood oxygen: ");
Serial.print(oxygen);
Serial.println(" %");
// Read ECG value from analog pin
int ecgValue = analogRead(ECG_PIN);
Serial.print("ECG Value: ");
Serial.println(ecgValue);
// Display data on the screen
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(SH110X_WHITE); // Change SSD1306_WHITE to SH110X_WHITE
display.setCursor(0, 0);
display.print("Temp: ");
display.print(temperature);
display.println(" C");
display.print("HR: ");
display.print(heartRate);
display.println(" bpm");
display.print("SpO2: ");
display.print(oxygen);
display.println(" %");
display.print("ECG: ");
display.println(ecgValue);
display.display();
// Wait for 1 second before updating the data
delay(1000);
}