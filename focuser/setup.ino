// Initialization routine
void setup() 
{
  initializeSerial();
  initializeBuzzer();
  initializeProperties();
  initializeButtons();
  initializeSensors();
  initializeStepper();
  buzz(50, 2);
}
