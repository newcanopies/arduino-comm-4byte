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
  
  Serial.print("\nBegin Decode\n");
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
  }
  
  Serial.print("The first byte is: ");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);

  for(int i = 0; byte2 > 0; i++)
  {
    byte[i] = byte2%2;
    byte2 = byte2/2;
  }
  
  Serial.print("\nThe second byte is: ");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);
  
  for(int i = 0; byte4 > 0; i++)
  {
    byte[i] = byte4%2;
    byte4 = byte4/2;
  }
 
  Serial.print("\nThe time elapsed for the test is: ");
  Serial.print(byte3);
  Serial.print(" seconds.\n");
  Serial.print("The fourth byte is: ");
  for(int i = sizeof(byte)/sizeof(int) - 1; i >= 0; i--)
    Serial.print(byte[i]);
  Serial.print("\nEnd decode\n");
}


void loop() {

  //Byte instructions for the tests (array)
  unsigned int instructions[2] = {0x1f, 0x2f}; // Any of the two algorithms can be tested on any of the four antenna and combinations of antennas so 4!*2 possibilities. 
  //You can add values but refer to the manual to determine the byte to pass.
  
  unsigned int answers[4] = {0x00, 0x00, 0x00, 0x00};


  //Write
  Wire.beginTransmission(ADDR); // begin on the transmission on the port with address 0x33 as per the manual and is 51 in decimal.
  Wire.write(instructions[counter]);
  Wire.endTransmission(); //stop the transmission
  //Read
  Wire.requestFrom(ADDR, 4); //requestest from the slave port (the antenna at address 0x33) and pass 4 bytes
  
  while(Wire.available())
  {
    answers[counter2] = Wire.read();
    counter2++;
  }

  decodeAnswer(answers);
  

  counter2 = 0;
  counter++;
  if (counter == (sizeof(instructions)/sizeof(int)))
    exit(0);
}
