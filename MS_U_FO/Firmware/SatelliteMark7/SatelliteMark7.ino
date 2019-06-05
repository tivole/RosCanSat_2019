// (c) Tivole

// Libraries
#include "Ti_Telemetry.h"
#include "Ti_UV_index.h"
#include "Ti_MQ7.h"
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "Adafruit_BME680.h"
#include <Adafruit_MLX90614.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BH1750FVI.h>
#include <SPI.h>
#include <SD.h>


// Defined PINS
#define UVM30A_PIN 0 // A0
#define DS18B20_ONE_WIRE_BUS_PIN 2 // D2
#define DS18B20_TEMPERATURE_PRECISION 9 // 9 Bit per device
#define BH1750_ADDRESSPIN_1 12
#define BH1750_ADDRESSPIN_2 13
#define MQ7_PIN 1 // A1

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


// File for SD card
File myFile;


void setup() {
  Serial.begin(9600);

  bool isOk = true;

  MQ7_Ro = Calibrate_MQ7(MQ7_PIN);

  DS18B20_Sensors.begin();
  BH1750_LightSensor1.begin();
  BH1750_LightSensor2.begin();

  if (!SD.begin(4))                                           isOk = false;
  if (DS18B20_Sensors.getDeviceCount() != 4)                  isOk = false;
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_1, 0))  isOk = false;
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_2, 1))  isOk = false;
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_3, 2))  isOk = false;
  if (!DS18B20_Sensors.getAddress(DS18B20_Temperature_4, 3))  isOk = false;
  if (!BME280.begin())                                        isOk = false;
  if (!BME680.begin())                                        isOk = false;
  if (!MLX90614.begin())                                      isOk = false;

  myFile = SD.open("test55.txt", FILE_WRITE);

  if(!myFile)                                                 isOk = false;


  // Set the resolution to 9 bit per device
  DS18B20_Sensors.setResolution(DS18B20_Temperature_1, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_2, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_3, DS18B20_TEMPERATURE_PRECISION);
  DS18B20_Sensors.setResolution(DS18B20_Temperature_4, DS18B20_TEMPERATURE_PRECISION);

  Initialize_BME680();

  if(!isOk) {
    Serial.println("\n(!) There is some problem!\n");
    while(1);
  }else {
    Serial.println("\nEverything is OK!\n");
  }
}


void loop() {
  Collect_All_Data();

  Telemetry.Ti_Print();
  Serial.println();

  String tel = Telemetry.Get_Telemetry();
  writeIntoSD(tel);
  
  delay(2000);
}

void writeIntoSD(String tel) {
  myFile.print(tel);
  myFile.flush();
}

bool Collect_All_Data() {
  bool status = true;
  if (! BME680.performReading()) status = false;
  DS18B20_Sensors.requestTemperatures();

  Telemetry.Temperature_1     = DS18B20_Sensors.getTempC(DS18B20_Temperature_1);
  Telemetry.Temperature_2     = DS18B20_Sensors.getTempC(DS18B20_Temperature_2);
  Telemetry.Temperature_3     = DS18B20_Sensors.getTempC(DS18B20_Temperature_3);
  Telemetry.Temperature_4     = DS18B20_Sensors.getTempC(DS18B20_Temperature_4);

  Telemetry.Light_intensity_1 = BH1750_LightSensor1.GetLightIntensity();
  Telemetry.Light_intensity_2 = BH1750_LightSensor2.GetLightIntensity();

  Telemetry.CO_concentration  = Read_MQ7_CO_Concentration(MQ7_PIN, MQ7_Ro);

  Telemetry.UV_index          = Read_UV_index(UVM30A_PIN);

  Telemetry.Temperature_5     = BME280.readTemperature();
  Telemetry.Temperature_6     = BME680.temperature;
  Telemetry.Temperature_7     = MLX90614.readAmbientTempC();
  Telemetry.Temperature_8     = MLX90614.readObjectTempC();

  Telemetry.Pressure_2        = BME280.readPressure();
  Telemetry.Pressure_3        = BME680.pressure;

  Telemetry.Humidity_1        = BME280.readHumidity();
  Telemetry.Humidity_2        = BME680.humidity;

  Telemetry.Gas_Resistance    = (BME680.gas_resistance) / 1000.0;

  return status;
}

void Initialize_BME680() {
  // Set up oversampling and filter initialization
  BME680.setTemperatureOversampling(BME680_OS_8X);
  BME680.setHumidityOversampling(BME680_OS_2X);
  BME680.setPressureOversampling(BME680_OS_4X);
  BME680.setIIRFilterSize(BME680_FILTER_SIZE_3);
  BME680.setGasHeater(320, 150); // 320*C for 150 ms
}
