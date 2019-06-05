// (c) Tivole

#define         RL_VALUE                     (5)
#define         RO_CLEAN_AIR_FACTOR          (9.83)
#define         CALIBARAION_SAMPLE_TIMES     (50)
#define         CALIBRATION_SAMPLE_INTERVAL  (500)
#define         READ_SAMPLE_INTERVAL         (50)
#define         READ_SAMPLE_TIMES            (5)
#define         GAS_CO                       (1)

float           COCurve[3]  =  {2.3,0.72,-0.34};



float MQResistanceCalculation(int raw_adc) {
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQCalibration(int mq_pin) {
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;
  val = val/RO_CLEAN_AIR_FACTOR;

  return val;
}

float MQRead(int mq_pin) {
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;
}

int  MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

int MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
}



float Calibrate_MQ7(int MQ7_PIN) {
  float Ro = MQCalibration(MQ7_PIN);
  return Ro;
}

unsigned int Read_MQ7_CO_Concentration(int MQ7_PIN, float Ro) {
  return MQGetGasPercentage(MQRead(MQ7_PIN)/Ro, GAS_CO);
}
