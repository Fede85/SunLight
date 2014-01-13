/*
  Sunlight.h - Library for compute the approssimate Sunrise and Sunset time.
  Created by Federico Vanzati (f.vanzati@gmail.com), January 3, 2011
  Relased into public domain.
*/

#ifndef SunLight_h
#define SunLight_h

extern "C" {
#include <Math.h>
}

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define DEGREE_TURN 360.0 
#define DAYS_YEAR 365.0 
#define DEG_RAD 57.2958 // Conversion degree to radiant
#define GMT_0 13.0 // Local Greenwich Mean Time, it's the basis for these calculation
#define DEG_MERIDIUM 15.0 // Every 15° we pass one meridium and the mean time change of 1 hr
#define INPUT_ERROR 0  // If error occurred in input data 
#define INPUT_VALID 1 // If the function recived the correct parameter
#define DOY_ERROR 400 // If the calcDOY function recived invalid parameters input

#define SUNRISE_H 0  // Sunrise array index for hours
#define SUNRISE_M 1  // Sunrise array index for minutes
#define SUNSET_H 2   // Sunset array index for hours
#define SUNSET_M 3   // Sunset array index for minutes

class SunLight {
public:
  SunLight();
  boolean computeSR(uint8_t *, uint8_t &, uint8_t, uint8_t, uint16_t);
  uint16_t calcDOY(uint8_t, uint8_t, uint16_t);
  float calcMezzoDiMedio (void);
  float conv_sessagesimali(uint8_t , uint8_t);
  void setPosition(float, float);
  
  uint16_t dayOfYear;
  float alba, tramonto;

private:
  float omega;
  float lat, lon; 
  };

#endif
