// (c) Tivole

// Libraries
#include "Ti_Telemetry.h"
#include "Ti_UV_index.h"
#include "Ti_MQ7.h"
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "Adafruit_BME680.h"
#include "MPU9250.h"
#include <Adafruit_MLX90614.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BH1750FVI.h>
#include <SPI.h>
#include <SD.h>


// Defined PINS
#define UVM30A_PIN A0 // A0
#define DS18B20_ONE_WIRE_BUS_PIN 2 // D2
#define DS18B20_TEMPERATURE_PRECISION 9 // 9 Bit per device
#define BH1750_ADDRESSPIN_1 12 // D12
#define BH1750_ADDRESSPIN_2 13 // D13
#define MQ7_PIN A1 // A1
#define LED_PIN 3 // D3
#define BUZZER_PIN 5 // D5
#define MG811_PIN A2 // A2
#define MQ131_PIN A3 // A3


// Our telemetry global class
Ti_Telemetry Telemetry;


// BME280, BME680, MLX90614
Adafruit_BME280 BME280; // I2C
Adafruit_BME680 BME680; // I2C
Adafruit_MLX90614 MLX90614 = Adafruit_MLX90614(); // I2C


// DS18B20 Thermometer
OneWire oneWire(DS18B20_ONE_WIRE_BUS_PIN); // OneWire
DallasTemperature DS18B20_Sensors(&oneWire);
DeviceAddress DS18B20_Temperature_1, DS18B20_Temperature_2, DS18B20_Temperature_3, DS18B20_Temperature_4;


// BH1750 Light intensity sensor
BH1750FVI::eDeviceAddress_t BH1750_DEVICEADDRESS_1 = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceAddress_t BH1750_DEVICEADDRESS_2 = BH1750FVI::k_DevAddress_L;
BH1750FVI::eDeviceMode_t BH1750_DEVICEMODE = BH1750FVI::k_DevModeContHighRes;
BH1750FVI BH1750_LightSensor1(BH1750_ADDRESSPIN_1, BH1750_DEVICEADDRESS_1, BH1750_DEVICEMODE);
BH1750FVI BH1750_LightSensor2(BH1750_ADDRESSPIN_2, BH1750_DEVICEADDRESS_2, BH1750_DEVICEMODE);


// MQ7 Resistance
float MQ7_Ro = 10;


// MPU9250 Accelerometer, Gyroscope, Magnetometer
MPU9250 MPU9250_IMU(Wire, 0x68); // I2C


// File for SD card
File myFile;


// Time counter
unsigned int Time = 0;

void setup() {
  Serial.begin(9600);

  bool isOk = true;

  MQ7_Ro = Calibrate_MQ7(MQ7_PIN);

  DS18B20_Sensors.begin();
  BH1750_LightSensor1.begin();
  BH1750_LightSensor2.begin();

  if (!SD.begin(4))                                           { Serial.println("Problem is HERE 1"); isOk = false; }
  if (DS18B20_Sensors.getDeviceCount() != 4)                  { Serial.println("Problem is HERE 2"); isOk = false; }
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_1, 0))  { Serial.println("Problem is HERE 3"); isOk = false; }
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_2, 1))  { Serial.println("Problem is HERE 4"); isOk = false; }
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_3, 2))  { Serial.println("Problem is HERE 5"); isOk = false; }
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_4, 3))  { Serial.println("Problem is HERE 6"); isOk = false; }
  if (!BME280.begin())                                        { Serial.println("Problem is HERE 7"); isOk = false; }
  if (!BME680.begin())                                        { Serial.println("Problem is HERE 8"); isOk = false; }
  if (!MLX90614.begin())                                      { Serial.println("Problem is HERE 9"); isOk = false; }
  if (MPU9250_IMU.begin() < 0)                                { Serial.println("Problem is HERE 10"); isOk = false; }

  myFile = SD.open("test55.txt", FILE_WRITE);

  if(!myFile)                                                 isOk = false;


  // Set the resolution to 9 bit per device
  DS18B20_Sensors.setResolution(DS18B20_Temperature_1, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_2, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_3, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_4, DS18B20_TEMPERATURE_PRECISION);

  Initialize_BME680();

  // LED and BUZZER PINS config
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  if(!isOk) {
    Serial.println("\n(!) There is some problem!\n");
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    digitalWrite(LED_PIN, LOW);
    while(1);
  }else {
    Serial.println("\nEverything is OK!\n");

    // Switch ON LED
    digitalWrite(LED_PIN, HIGH);

    // BUZZER signal
    Buzzer_Signal();
    delay(500);
  }
}


void loop() {
  Collect_All_Data();

  Telemetry.Ti_Print();
  Serial.println();

  String tel = Telemetry.Get_Telemetry();
  writeIntoSD(tel);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  delay(1900);
  Time += 2;

}

void writeIntoSD(String tel) {
  myFile.print(tel);
  myFile.flush();
}

bool Collect_All_Data() {

  // Reading data from sensors
  bool status = true;
  if (! BME680.performReading()) status = false;
  DS18B20_Sensors.requestTemperatures();
  MPU9250_IMU.readSensor();


  // Collecting all data
  Telemetry.Time              = Time;

  Telemetry.Temperature_1     = DS18B20_Sensors.getTempC(DS18B20_Temperature_1);
  Telemetry.Temperature_2     = DS18B20_Sensors.getTempC(DS18B20_Temperature_2);
  Telemetry.Temperature_3     = DS18B20_Sensors.getTempC(DS18B20_Temperature_3);
  Telemetry.Temperature_4     = DS18B20_Sensors.getTempC(DS18B20_Temperature_4);

  Telemetry.Light_intensity_1 = BH1750_LightSensor1.GetLightIntensity();
  Telemetry.Light_intensity_2 = BH1750_LightSensor2.GetLightIntensity();

  Telemetry.CO_concentration  = Read_MQ7_CO_Concentration(MQ7_PIN, MQ7_Ro);
  Telemetry.CO2_concentration = analogRead(MG811_PIN);
  Telemetry.O3_concentration  = analogRead(MQ131_PIN);

  Telemetry.UV_index          = Read_UV_index(UVM30A_PIN);

  Telemetry.Temperature_5     = BME280.readTemperature();
  Telemetry.Temperature_6     = BME680.temperature;
  Telemetry.Temperature_7     = MLX90614.readAmbientTempC();
  Telemetry.Temperature_8     = MLX90614.readObjectTempC();

  Telemetry.Pressure_2        = BME280.readPressure();
  Telemetry.Pressure_3        = BME680.pressure;

  Telemetry.Humidity_1        = BME280.readHumidity();
  Telemetry.Humidity_2        = BME680.humidity;

  Telemetry.ACC_x             = MPU9250_IMU.getAccelX_mss();
  Telemetry.ACC_y             = MPU9250_IMU.getAccelY_mss();
  Telemetry.ACC_z             = MPU9250_IMU.getAccelZ_mss();
  Telemetry.GYR_x             = MPU9250_IMU.getGyroX_rads();
  Telemetry.GYR_y             = MPU9250_IMU.getGyroY_rads();
  Telemetry.GYR_z             = MPU9250_IMU.getGyroZ_rads();
  Telemetry.MAG_x             = MPU9250_IMU.getMagX_uT();
  Telemetry.MAG_y             = MPU9250_IMU.getMagY_uT();
  Telemetry.MAG_z             = MPU9250_IMU.getMagZ_uT();

  Telemetry.Gas_Resistance    = (BME680.gas_resistance) / 1000.0;

  return status;
}

void Buzzer_Signal() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(250);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(250);
  digitalWrite(BUZZER_PIN, LOW);
}

void Initialize_BME680() {
  // Set up oversampling and filter initialization
  BME680.setTemperatureOversampling(BME680_OS_8X);
  BME680.setHumidityOversampling(BME680_OS_2X);
  BME680.setPressureOversampling(BME680_OS_4X);
  BME680.setIIRFilterSize(BME680_FILTER_SIZE_3);
  BME680.setGasHeater(320, 150); // 320*C for 150 ms
}
