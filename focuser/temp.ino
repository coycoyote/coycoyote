void initializeSensors() {
  int chk = DHT.read22(TEMP_SENSOR_PIN); 
  if(chk == DHTLIB_OK) {
    sensorType = 3;
  }
  if(sensorType == 0) {
    sensors.begin(); 
    boolean sensorConnected = sensors.getAddress(insideThermometer, 0);
    if(sensorConnected) {
      sensors.setResolution(insideThermometer, 10);
      sensors.setWaitForConversion(false);
      sensorType=1;
    }
  }
  if(sensorType > 0) tempCycleEvent = timer.after(2000, requestTemp);
}

void requestTemp() {
  if(stepper.distanceToGo() != 0) {
    // dont measure during move
    tempCycleEvent = timer.after(TEMP_CYCLE, requestTemp);
    return;
  }
  if(sensorType == 1) {
    sensors.requestTemperaturesByAddress(insideThermometer); // Send the command to get temperature. For 10 bit res it takes 188ms
  }
  tempCycleEvent = timer.after(188, readTemp);
}

void readTemp() {
  currentTemp = currentHum = currentDewpoint = 0.0;
  if(sensorType == 1) {
    currentTemp = sensors.getTempC(insideThermometer);
  }
  if(sensorType == 3) {
    DHT.read22(TEMP_SENSOR_PIN);
    currentTemp = DHT.temperature;
    currentHum = DHT.humidity;
    currentDewpoint = dewPoint(currentTemp, currentHum);
  }  

  tempCycleEvent = timer.after(TEMP_CYCLE, requestTemp);
}

void calculateHeaterPWM() {
  heaterPWM = map(constrain(currentHum, 50, 100), 50, 100, 0, 100);
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
	RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558 - T);
}

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
	return Td;
}
