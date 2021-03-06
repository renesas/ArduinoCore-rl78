/*
  Listfiles
 
 This example shows how print out the files in a 
 directory on a SD card 
 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald
 
 This example code is in the public domain.
 	 
 */
#include <SD.h>

File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial2.begin(9600);
   while (!Serial2) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial2.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial2.println("initialization failed!");
    return;
  }
  Serial2.println("initialization done.");

  root = SD.open("/");
  
  printDirectory(root, 0);
  
  Serial2.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial2.print('\t');
     }
     Serial2.print(entry.name());
     if (entry.isDirectory()) {
       Serial2.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial2.print("\t\t");
       Serial2.println(entry.size(), DEC);
     }
     entry.close();
   }
}



