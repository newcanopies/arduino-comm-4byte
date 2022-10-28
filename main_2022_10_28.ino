#include <Wire.h>
#include <math.h>


#define ADDR 0x33
int counter = 0;
int counter2 = 0;

void setup() {
  Wire.begin(); //Join I2C protocol
  Serial.begin(9600);
}


void decodeAnswer(unsigned int a[])
{
  
  Serial.println("Begin Decode\n");
  int byte[8] = {0,0,0,0,0,0,0,0};
  unsigned int byte1, byte2, byte4, byte3 = 0x00;
  byte1 = a[0];
  byte2 = a[1];
  byte3 = a[2];
  byte4 = a[3];

  for(int i = 0; byte1 > 0; i++)
  {
    byte[i] = byte1%2;
    byte1 = byte1/2;
    delay(1000);
  }
  
  Serial.print("The first byte is:");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);
  Serial.println();
  for(int i =0; i < 8; i++)
    byte[i] = 0;
  
    
  for(int i = 0; byte2 > 0; i++)
  {
    byte[i] = byte2%2;
    byte2 = byte2/2;
    delay(1000);
  }
  Serial.print("The second byte is: ");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);
  Serial.println();
  for(int i =0; i < 8; i++)
    byte[i] = 0;
   
  for(int i = 0; byte4 > 0; i++)
  {
    byte[i] = byte4%2;
    byte4 = byte4/2;
    delay(1000);
  }
 
  Serial.print("The time elapsed for the test is: ");
  Serial.print(byte3);
  Serial.println(" seconds.");
  Serial.print("The fourth byte is: ");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);
  Serial.println();
  Serial.println("End decode"); 
  delay(7000);
}


void loop() {

  //Byte instructions for the tests (array)
  unsigned int instructions[11] = {0x4, 0x1f, 0x2f, 0x11,0x21,0x12,0x22,0x14,0x24,0x18,0x28}; // Any of the two algorithms can be tested on any of the four antenna and combinations of antennas so 4!*2 possibilities. 
  //You can add values but refer to the manual to determine the byte to pass.
  //0x1f, 0x2f,0x11,0x21,0x12,0x22,0x14,0x24,0x18,0x28
  
  unsigned int answers[4] = {0x00, 0x00, 0x00, 0x00};

  //Write
  Wire.beginTransmission(ADDR); // begin on the transmission on the port with address 0x33 as per the manual and is 51 in decimal.
  Wire.write(instructions[counter]);
  delay(30000); // delay to allow for buffer to clear for print I believe (L)
  Wire.write(0x00);
  Wire.endTransmission(); //stop the transmission
  Wire.requestFrom(ADDR, 4); //requestest from the slave port (the antenna at address 0x33) and pass 4 bytes
  
  while(Wire.available())
  {
    answers[counter2] = Wire.read();
    counter2++;
  }
  Serial.println();

  decodeAnswer(answers);
  

  counter2 = 0;
  counter++;
  Serial.println(counter);
  
  if (counter == 11)
  {
    Serial.print("Program Finished");
    Wire.beginTransmission(ADDR); // begin on the transmission on the port with address 0x33 as per the manual and is 51 in decimal.
    Wire.write(0x00);
    Wire.endTransmission(); //stop the transmission
    delay(1000);
    exit(0);
  }
    
}
