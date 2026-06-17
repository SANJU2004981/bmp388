#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h> // Correct header file

// Standard sea level pressure for altitude calculation
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp; // Correct class

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); 

  Serial.println("BMP3XX Initialization...");

  // Initialize I2C. If your board uses a different I2C bus, 
  // you may need to define Wire pins (e.g., Wire.setPins(SDA, SCL);) before this.
  if (!bmp.begin_I2C(0x77)) {
    Serial.println("Could not find a valid BMP388 sensor at 0x77!");
    Serial.println("Check your wiring: SDA -> D14, SCL -> D15");
    while (1) delay(10);
  }

  // Set up oversampling and filter
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  Serial.println("BMP388 Initialized Successfully!");
}

void loop() {
  // Always call performReading() to update sensor data
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude: ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println("------------------------------------");
  
  delay(1000); 
}
