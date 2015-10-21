
#include <LTask.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

#define Drv LFlash          // use Internal 10M Flash
// #define Drv LSD           // use SD card

LFile myFile;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial1.begin(115200);

    while(!Serial1.available());         // input any thing to start

    Serial1.print("Initializing Storage card...\r\n");

    LTask.begin();
    Drv.begin();

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = Drv.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) 
    {
        Serial1.print("Writing to test.txt...\r\n");
        //myFile.println("testing 1, 2, 3.");
        // close the file:
        myFile.close();
        Serial1.println("done.\r\n");
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial1.println("error opening test.txt\r\n");
    }
    /*
    // re-open the file for reading:
    myFile = Drv.open("test.txt");
    if (myFile) 
    {
        Serial1.println("test.txt:");
        myFile.seek(0);
        // read from the file until there's nothing else in it:
        while (myFile.available()) 
        {            
            Serial1.write(myFile.read());
        }
        // close the file:
        myFile.close();
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial1.println("error opening test.txt");
    }
    */
}

void loop()
{
    // nothing happens after setup
}


