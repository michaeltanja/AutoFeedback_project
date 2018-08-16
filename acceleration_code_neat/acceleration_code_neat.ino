//for reference to velocity integral:
//https://arduino.stackexchange.com/questions/9436/integrating-an-analog-signal-using-arduino-uno-smd

#include <Wire.h>

int m; //mass of the accelerometer assembly and the arduino attached

//mechanics
long accelX, accelY, accelZ;       //acceleration
float gForceX, gForceY,gForceZ;    //gforce
float linaccelX;                   //linear acceleration in m/s^2
float ivel;                        //initial velocity
float nvel;                        //new velocity

//time
float dt;                          //difference in time
unsigned long period = 1000;
unsigned long old_time;
unsigned long new_time;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  //omitted the PLX-DAQ lines that write to excel
 
  setupMPU();

}

void loop() {
  //maybe place a time stamp loop? or 2?
  timestamp1();
  recordAccelRegisters();
  printData();
  delay(period);                              //time delay in milliseconds
 
}

void setupMPU(){
  Wire.beginTransmission(0b1101000);      //writing straight to I2C
  Wire.write(0x6B);                       //MPU6050 power module, sleep mode upon power
  Wire.write(0b00000000);                 //MPU6050 power module commands, sleep mode disabled
  Wire.endTransmission();                 //end transmission
  Wire.beginTransmission(0b1101000);      //calling up the I2C again
  Wire.write(0x1B);                       //repitition module
  Wire.write(0x00000000);                 //commands the module to repeat the process?
  Wire.endTransmission();                 //end transmission
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();

  
}
/*This timestamp is meant for me to record the time that the data was taekn
  My hope is that the code will record this time stamp and use the next time stamp recorded
  in the next loop iteration and find the difference to find deltatime*/
void timestamp1(){
  new_time = millis();
}

void recordAccelRegisters(){

 
  
  Wire.beginTransmission(0b1101000);       //writes directly to the I2C
  Wire.write(0x3B);                        //accelerometer address, commands to begin data transmission
  Wire.endTransmission();                  //end transmission
  Wire.requestFrom(0b1101000,6);           //request data
  while(Wire.available() < 6);             //


  accelX = Wire.read()<<8|Wire.read();
  accelY = Wire.read()<<8|Wire.read();
  accelZ = Wire.read()<<8|Wire.read();     //gathers data from the acceleration registers

 
  processAccelData();                      //runs function stated in the void loop


  
}
/*second time stamp, not sure if this is required, since the deltatime should be taken as 
 * the difference in time since the data was last recoded, not the time it takes to 
 * run the calculation code
 */



void processAccelData(){
  
  gForceX = (accelX / 16384.0) + (-1.59738); //should be about 0 with no movement
  gForceY = (accelY / 16384.0) + (-0.26);    //should be about 0 with no movement
  gForceZ = (accelZ / 16834.0) + (0.22);     //should be about 1 with no movement, gravity of earth
  
// integration attempt

  
  linaccelX = 9.81 * gForceX;                //1 G = 9.81 m/s^2 or 32ft/s^2


dt = (new_time - old_time)/1000;
old_time = new_time;

  //Serial.println(dt); // this indicated that this function sees the time stamp

  nvel += (linaccelX * dt) + ivel;
  nvel += ivel;                         //compiling error, maybe find a way to get the arduino
  // to take the average of the last 5 data points of velocity
  
 // nvel += (linaccelX * (now - last_time_sampled))+ivel;
 // nvel += ivel;
 // last_time_sampled = now;
  

}



void printData(){

     Serial.print("The difference in time for the data taken is ");
     Serial.print(dt);    //this works, now place this in the acceleration loop
     Serial.println("'s");
     Serial.println(" ");
     Serial.print("The acceleration is ");
     Serial.print(linaccelX);
     Serial.println("m/s^2");
     Serial.println(" ");
     Serial.print("G-force calibration: ");
     Serial.println(gForceX);
     Serial.println(" ");
     Serial.print("Velocity is ");
     Serial.println(nvel);
     Serial.println(" ");
     Serial.println(" ");

   
}

