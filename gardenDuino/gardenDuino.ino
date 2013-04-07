// reading amount of liquid that has flowed through a Water Flow Sensor from Seeedstudio.com
// Code adapted from example provided at http://www.seeedstudio.com/wiki/G1/2_Water_Flow_sensor
// altered by Kent and github user markfinn
 
 //264 pulses per liter
 //about 62 pulses per cup?
 //3950 pulses is a little under 4 gallons?
#define MAX_COUNT 124 //volume of water to dispense in instances in "counts" or "pulses"
#define MAX_CUTOFF_COUNT 3950 //keep some water in the cistern
//variables volatile because of their association with the interrupt
volatile int pulseCount; //measuring the rising edges of the signal
volatile int cutoffPulseCount;
int hallsensor = 2;    //The pin location of the sensor
int solenoid = 5;    //The pin location of the solenoid control
 
void rpm ()     //This is the function that the interupt calls 
{ 
  pulseCount++;  //This function measures the rising and falling edge of the hall effect sensors signal

  if (pulseCount >= cutoffPulseCount)
    pinMode(solenoid, LOW);
} 
// The setup() method runs once, when the sketch starts
void setup() //
{ 
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  pulseCount = 0;
  cutoffPulseCount = 0;
  pinMode(solenoid, LOW);
  sei();      //Enables interrupts
} 
// the loop() method runs over and over again,
// as long as the Arduino has power
void loop ()    
{
  
  if(soilDry() && (cutoffPulseCount < MAX_CUTOFF_COUNT))
  {
    StartWateringCycle(124);
    delay(360000); //delay one hour
  }
  
  delay(1000);
}//loop

//should quantity just be MAX_COUNT?
void StartWateringCycle(int quantity)
{
  cli();  //disable interrupts
  cutoffPulseCount = pulseCount + quantity; 
  sei();      //Enables interrupts
  pinMode(solenoid, HIGH); //should this be first line in the function?
}//StartWateringCycle

boolean soilDry()
{
  
  
  
}//soilDry

