#include <Wire.h>
#include <math.h>

#define ADDR 0x33
int counter = 0;
int counter2 = 0;

void setup() {
  Wire.begin(); //Join I2C protocol
  Serial.begin(9600);
}

/*
void decodeAnswer(unsigned int a[])
{
  int temp = a[0];
  int answerBits[32];
  for(int i = 0; temp > 0; i++)
    {
      answerBits[i] = temp%2;
      temp = temp/2;
    }

  for(int i = 0; temp > 0; i++)
  {
    Serial.print(answerBits[i]);
  }

}
*/

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
  
  for(int i = 0; i < sizeof(answers)/sizeof(int); i++)
  {
    Serial.print(answers[i]);
  }

  counter2 = 0;
  counter++;
  if (counter == (sizeof(instructions)/sizeof(int)))
    exit(0);
}

