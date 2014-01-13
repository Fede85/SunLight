#include <SunLight.h>

SunLight mySun; // Declaration of the object

// Setting the longitude of your location
// Will be used to estimate the average Noon
float myLongitude = 9.10;

// Setting the latitude of your location
float myLatitude = 45.58;

// The current settings are for the north of Milan

// If you want to anticipate the sunrise and postpone the sunset.
// Permits data beetween 0 and 60 and the unit of measurement is minutes
uint8_t twilight_minutes = 0;

// The date on which you want to calculate astronomical events
uint8_t day = 25;
uint8_t month = 2;
uint16_t year = 11;

// The array where will be saved variables of sunrise and sunset
// with the following form:
// timeArray[ Rise_hours, Rise_minutes, Set_hours, Set_minutes ]
// if you want you can use specially created index:
// SUNRISE_H SUNRISE_M SUNSET_H SUNSET_M
uint8_t timeArray[4];

void setup()
{
  Serial.begin(57600);
}

void loop()
{
  // This functions are used to set your geographical coordinates of your location
  mySun.setPosition(myLatitude, myLongitude);
  
  // This is the function that allows you to calculate sunrise and sunset
  boolean check = mySun.computeSR(timeArray, twilight_minutes, day, month, year);
  //return true if all the data entered are correct

  if( check == true )
  {
    // Print on Serial monitor the Sunrise time
    Serial.print("Sunrise: ");
    Serial.print(timeArray[SUNRISE_H], DEC);
    Serial.print("h ");
    Serial.print(timeArray[SUNRISE_M], DEC);
    Serial.println("m ");

    // Print on Serial monitor the Sunset time
    Serial.print("Sunset: ");
    Serial.print(timeArray[SUNSET_H], DEC);
    Serial.print("h ");
    Serial.print(timeArray[SUNSET_M], DEC);
    Serial.println("m ");
  }
  else
    // Some parameter is incorrect and the function can not perform the calculation
    Serial.println("Something wrong in function computeSR...please check your input parameteer");

  delay(1000);
}




