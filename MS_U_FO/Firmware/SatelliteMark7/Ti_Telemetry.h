// (c) Tivole

/*
  Telemtry format:
  1. DS18B20    =>  [ Temperature 1 ]     (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  2. DS18B20    =>  [ Temperature 2 ]     (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  3. DS18B20    =>  [ Temperature 3 ]     (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  4. DS18B20    =>  [ Temperature 4 ]     (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]

  5. BH1750     =>  [ Light intensity 1 ] (Lux)         <unsigned int>    {XXXXX}   = [ 5 Bytes ]
  6. BH1750     =>  [ Light intensity 2 ] (Lux)         <unsigned int>    {XXXXX}   = [ 5 Bytes ]

  7. Pocket Geiger => [ Radiation ]       (CPM or uR/hr)  <unsigned int>  {XXXX}    = [ 4 Bytes ]

  8. MQ7       =>  [ CO concentration ]  (PPM)         <unsigned int>    {XXXX}    = [ 4 Bytes ]
  9. MG811     =>  [ CO2 concentration ] (PPM)         <unsigned int>    {XXXX}    = [ 4 Bytes ]
  10. MQ131     =>  [ O3 concentration ]  (PPM)         <unsigned int>    {XXXX}    = [ 4 Bytes ]

  11. UVM30A    => [ UV index ]           (a number)    <unsigned int>    {XX}      = [ 2 Bytes ]

  12. BME280    => [ Temperature 5 ]      (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  13. BME680    => [ Temperature 6 ]      (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  14. MLX90614  => [ Temperature 7 ]      (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]
  15. MLX90614  => [ Tempreature 8 ]      (Celsius)     <double>          {XXX.X}   = [ 5 Bytes ]

  16. MS5607    => [ Pressure 1 ]         (Pascal)      <double>          {XXXXX}   = [ 5 Bytes ]
  17. BME280    => [ Pressure 2 ]         (Pascal)      <double>          {XXXXX}   = [ 5 Bytes ]
  18. BME680    => [ Pressure 3 ]         (Pascal)      <double>          {XXXXX}   = [ 5 Bytes ]

  19. BME280    => [ Humidity 1 ]         (%)           <double>          {XXX}     = [ 3 Bytes ]
  20. BME680    => [ Humidity 2 ]         (%)           <double>          {XXX}     = [ 3 Bytes ]

  21. LSM303DLHC&L3GD20 => [ ACC {x} ]    (g)           <double>          {XX.XXX}  = [ 6 Bytes ]
  22. LSM303DLHC&L3GD20 => [ ACC {y} ]    (g)           <double>          {XX.XXX}  = [ 6 Bytes ]
  23. LSM303DLHC&L3GD20 => [ ACC {z} ]    (g)           <double>          {XX.XXX}  = [ 6 Bytes ]

  24. LSM303DLHC&L3GD20 => [ GYR {x} ]    (deg/s)       <double>          {XX.XXX}  = [ 6 Bytes ]
  25. LSM303DLHC&L3GD20 => [ GYR {y} ]    (deg/s)       <double>          {XX.XXX}  = [ 6 Bytes ]
  26. LSM303DLHC&L3GD20 => [ GYR {z} ]    (deg/s)       <double>          {XX.XXX}  = [ 6 Bytes ]

  27. LSM303DLHC&L3GD20 => [ MAG {x} ]    (Tesla)       <double>          {XX.XXX}  = [ 6 Bytes ]
  28. LSM303DLHC&L3GD20 => [ MAG {y} ]    (Tesla)       <double>          {XX.XXX}  = [ 6 Bytes ]
  29. LSM303DLHC&L3GD20 => [ MAG {z} ]    (Tesla)       <double>          {XX.XXX}  = [ 6 Bytes ]

  30. Longtitude        => [ GPS_long ]   ()            <double>          {XX.XXXX} = [ 7 Bytes ]
  31. Latitude          => [ GPS_lat ]    ()            <double>          {XX.XXXX} = [ 7 Bytes ]

  32. BME680            => [ Gas Resistance ] (KOhms)   <double>          {XXXX.X}  = [ 6 Bytes ]

 */

#define LINE_LENGTH 60

class Ti_Telemetry {
 public:
  double Temperature_1 = 0.0, Temperature_2 = 0.0, Temperature_3 = 0.0, Temperature_4 = 0.0, Temperature_5 = 0.0, Temperature_6 = 0.0, Temperature_7 = 0.0, Temperature_8 = 0.0, Humidity_1 = 0.0, Humidity_2 = 0.0, Pressure_1 = 0.0, Pressure_2 = 0.0, Pressure_3 = 0.0, ACC_x = 0.0, ACC_y = 0.0, ACC_z = 0.0, GYR_x = 0.0, GYR_y = 0.0, GYR_z = 0.0, MAG_x = 0.0, MAG_y = 0.0, MAG_z = 0.0, GPS_long = 0.0, GPS_lat = 0.0, Gas_Resistance = 0.0;
  unsigned int Light_intensity_1 = 0, Light_intensity_2 = 0, UV_index = 0, Radiation = 0, CO_concentration = 0, CO2_concentration = 0, O3_concentration = 0;

  void Ti_Print();
  String Get_Telemetry();
};

String Ti_Telemetry::Get_Telemetry() {
  String Telemetry = "";
  Telemetry += String(Temperature_1, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_2, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_3, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_4, 1);
  Telemetry += ",";
  Telemetry += String(Light_intensity_1);
  Telemetry += ",";
  Telemetry += String(Light_intensity_2);
  Telemetry += ",";
  Telemetry += String(Radiation);
  Telemetry += ",";
  Telemetry += String(CO_concentration);
  Telemetry += ",";
  Telemetry += String(CO2_concentration);
  Telemetry += ",";
  Telemetry += String(O3_concentration);
  Telemetry += ",";
  Telemetry += String(UV_index);
  Telemetry += ",";
  Telemetry += String(Temperature_5, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_6, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_7, 1);
  Telemetry += ",";
  Telemetry += String(Temperature_8, 1);
  Telemetry += ",";
  Telemetry += String(Pressure_1, 1);
  Telemetry += ",";
  Telemetry += String(Pressure_2, 1);
  Telemetry += ",";
  Telemetry += String(Pressure_3, 1);
  Telemetry += ",";
  Telemetry += String(Humidity_1, 1);
  Telemetry += ",";
  Telemetry += String(Humidity_2, 1);
  Telemetry += ",";
  Telemetry += String(ACC_x, 3);
  Telemetry += ",";
  Telemetry += String(ACC_y, 3);
  Telemetry += ",";
  Telemetry += String(ACC_z, 3);
  Telemetry += ",";
  Telemetry += String(GYR_x, 3);
  Telemetry += ",";
  Telemetry += String(GYR_y, 3);
  Telemetry += ",";
  Telemetry += String(GYR_z, 3);
  Telemetry += ",";
  Telemetry += String(MAG_x, 3);
  Telemetry += ",";
  Telemetry += String(MAG_y, 3);
  Telemetry += ",";
  Telemetry += String(MAG_z, 3);
  Telemetry += ",";
  Telemetry += String(GPS_long, 4);
  Telemetry += ",";
  Telemetry += String(GPS_lat, 4);
  Telemetry += ",";
  Telemetry += String(Gas_Resistance, 1);
  Telemetry += "\n";

  return Telemetry;
}

void Ti_Telemetry::Ti_Print() {
  int i;
  String Telemetry = "";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 1 */
  Telemetry += "1. ";
  Telemetry += "Temperature_1\t= ";
  Telemetry += String(Temperature_1, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 2 */
  Telemetry += "2. ";
  Telemetry += "Temperature_2\t= ";
  Telemetry += String(Temperature_2, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 3 */
  Telemetry += "3. ";
  Telemetry += "Temperature_3\t= ";
  Telemetry += String(Temperature_3, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 4 */
  Telemetry += "4. ";
  Telemetry += "Temperature_4\t= ";
  Telemetry += String(Temperature_4, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Light intensity 1 */
  Telemetry += "5. ";
  Telemetry += "Light_intensity_1\t= ";
  Telemetry += String(Light_intensity_1);
  Telemetry += " lux\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Light intensity 2 */
  Telemetry += "6. ";
  Telemetry += "Light_intensity_2\t= ";
  Telemetry += String(Light_intensity_2);
  Telemetry += " lux\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Radiation */
  Telemetry += "7. ";
  Telemetry += "Radiation\t\t= ";
  Telemetry += String(Radiation);
  Telemetry += " cpm\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* CO */
  Telemetry += "8. ";
  Telemetry += "CO_concentration\t= ";
  Telemetry += String(CO_concentration);
  Telemetry += " ppm\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* CO2 */
  Telemetry += "9. ";
  Telemetry += "CO2_concentration\t= ";
  Telemetry += String(CO2_concentration);
  Telemetry += " ppm\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* O3 */
  Telemetry += "10. ";
  Telemetry += "O3_concentration\t= ";
  Telemetry += String(O3_concentration);
  Telemetry += " ppm\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* UV index */
  Telemetry += "11. ";
  Telemetry += "UV_index\t\t= ";
  Telemetry += String(UV_index);
  Telemetry += "\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 5 */
  Telemetry += "12. ";
  Telemetry += "Temperature_5\t= ";
  Telemetry += String(Temperature_5, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 6 */
  Telemetry += "13. ";
  Telemetry += "Temperature_6\t= ";
  Telemetry += String(Temperature_6, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 7 */
  Telemetry += "14. ";
  Telemetry += "Temperature_7\t= ";
  Telemetry += String(Temperature_7, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Temperature 8 */
  Telemetry += "15. ";
  Telemetry += "Temperature_8\t= ";
  Telemetry += String(Temperature_8, 1);
  Telemetry += " *C\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Pressure 1 */
  Telemetry += "16. ";
  Telemetry += "Pressure_1\t\t= ";
  Telemetry += String(Pressure_1, 1);
  Telemetry += " Pa\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Pressure 2 */
  Telemetry += "17. ";
  Telemetry += "Pressure_2\t\t= ";
  Telemetry += String(Pressure_2, 1);
  Telemetry += " Pa\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Pressure 3 */
  Telemetry += "18. ";
  Telemetry += "Pressure_3\t\t= ";
  Telemetry += String(Pressure_3, 1);
  Telemetry += " Pa\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Humidity 1 */
  Telemetry += "19. ";
  Telemetry += "Humidity_1\t\t= ";
  Telemetry += String(Humidity_1, 1);
  Telemetry += " %\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Humidity 2 */
  Telemetry += "20. ";
  Telemetry += "Humidity_2\t\t= ";
  Telemetry += String(Humidity_2, 1);
  Telemetry += " %\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Accelerometer */
  Telemetry += "21.";
  Telemetry += " Accelerometer\t=";
  Telemetry += " { (";
  Telemetry += String(ACC_x);
  Telemetry += "), (";
  Telemetry += String(ACC_y);
  Telemetry += "), (";
  Telemetry += String(ACC_z);
  Telemetry += ") } g\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Gyroscope */
  Telemetry += "24.";
  Telemetry += " Gyroscope\t\t=";
  Telemetry += " { (";
  Telemetry += String(GYR_x);
  Telemetry += "), (";
  Telemetry += String(GYR_y);
  Telemetry += "), (";
  Telemetry += String(GYR_z);
  Telemetry += ") } deg/s\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Magnetometer */
  Telemetry += "27.";
  Telemetry += " Magnetometer\t=";
  Telemetry += " { (";
  Telemetry += String(MAG_x);
  Telemetry += "), (";
  Telemetry += String(MAG_y);
  Telemetry += "), (";
  Telemetry += String(MAG_z);
  Telemetry += ") } Tesla\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* GPS longtitude */
  Telemetry += "30. ";
  Telemetry += "GPS_long\t\t= ";
  Telemetry += String(GPS_long, 4);
  Telemetry += "\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* GPS latitude */
  Telemetry += "31. ";
  Telemetry += "GPS_lat\t\t= ";
  Telemetry += String(GPS_lat, 4);
  Telemetry += "\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  /* Gas Resistance */
  Telemetry += "32. ";
  Telemetry += "Gas_Resistance\t= ";
  Telemetry += String(Gas_Resistance, 1);
  Telemetry += " KOmhs\n";
  for(i = 0; i < LINE_LENGTH; i++) Telemetry += "-";
  Telemetry += "\n";

  Serial.print(Telemetry);
}
