#include <Wire.h>

#define ADDR 0x33
int counter = 0;

void setup() {
  Wire.begin(); //Join I2C protocol
  Serial.begin(9600);
}

void loop() {

  //Byte instructions for the tests (array)
  unsigned int instructions[2] = {0x1f, 0x2f}; // Any of the two algorithms can be tested on any of the four antenna and combinations of antennas so 4!*2 possibilities. 
  //You can add values but refer to the manual to determine the byte to pass.

  //Write
  Wire.beginTransmission(ADDR); // begin on the transmission on the port with address 0x33 as per the manual and is 51 in decimal.
  Wire.write(instructions[counter]);
  Wire.endTransmission(); //stop the transmission
  //Read
  Wire.requestFrom(ADDR, 4); //requestest from the slave port (the antenna at address 0x33) and pass 4 bytes
  unsigned int answer = Wire.read();
  Serial.print("The answer is " + answer);
  counter++;
  if (counter == (sizeof(instructions)/sizeof(int)))
    exit(0);
}

