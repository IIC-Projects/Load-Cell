#include <SPI.h>
//#include <nRF24L01.h>
#include <HX711.h>
//#include <RF24.h>
//RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

#define DOUT 3
#define CLK 2

HX711 scale;
const int chipSelect = 4;
String dataString = "";
float calibration_factor = 1205386; //prev_value 20230.09
float z = calibration_factor;

void setup()
{

    ////  radio.begin();
    //  radio.openWritingPipe(address);
    //  radio.setPALevel(RF24_PA_MAX);
    //  radio.stopListening();

    Serial.begin(9600);
    Serial.println("HX711 calibration sketch");

    scale.begin(DOUT, CLK);
    scale.set_scale();
    scale.tare(); //Reset the scale to 0

    long zero_factor = scale.read_average(); //Get a baseline reading
    Serial.print("Zero factor: ");           //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
    Serial.println(zero_factor);
}
void loop()
{

    float y;
    String z;
    scale.set_scale(calibration_factor); //Adjust to this calibration factor

    // Serial.print("Reading: ");
    y = (scale.get_units());

    if (Serial.available())
    {
        char temp = Serial.read();
        if (temp == '+' || temp == 'a')
            calibration_factor += 500;
        else if (temp == '-' || temp == 'z')
            calibration_factor -= 500;

        else if (temp == '+' || temp == 's')
            calibration_factor += 1000;
        else if (temp == '-' || temp == 'x')
            calibration_factor -= 1000;
    }
    //z = String(y);
    Serial.print(y);
    Serial.print(",");
    //Serial.print(" kgs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
    //Serial.print(" calibration_factor: ");
    Serial.println(calibration_factor);
    Serial.println();

    //const char text[] = "hello"

    //  radio.write(&y, sizeof(y));
    //  delay(100);
}