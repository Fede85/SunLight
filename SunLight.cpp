/*
  Sunlight.cpp - Library for compute the approssimate Sunrise and Sunset time.
  Created by Federico Vanzati (f.vanzati@gmail.com), January 3, 2011
  Relased into public domain.
*/

#include "SunLight.h"

SunLight::SunLight(){
  omega = DEGREE_TURN / DAYS_YEAR; 
  omega = omega / DEG_RAD; 
  lat = 45.58; 
  lon = 9.19;
}

//This function once received as input parameters the date
//returns the number of days of the year ... from 0 to 365!
//D_ay O_f Y_ear

uint16_t SunLight::calcDOY(uint8_t _day , uint8_t _month, uint16_t _year)
{ 
  if( _day <= 0 || _day > 31 ) return DOY_ERROR;
  if( _month <= 0 || _month > 12) return DOY_ERROR;
  uint16_t n1 = floor(275 * _month /9);
  uint16_t n2 = floor((_month + 9) / 12);
  uint16_t n3 = (1 + floor((_year - 4 * floor(_year / 4) + 2) / 3));
  return (n1 - (n2 * n3) + _day - 30);
}

//The function computeSR will calculate the the sunrise and sunset times 
//if you pass a date as a parameter.
//Consider the array as the output of the function, will contains the values of calculation expressed in hours and minutes

boolean SunLight::computeSR( uint8_t alba_tramonto[], uint8_t & twilight, uint8_t _d, uint8_t _m, uint16_t _y )
{
  dayOfYear = calcDOY(_d, _m, _y);
  if(dayOfYear == DOY_ERROR) return INPUT_ERROR;
  float t = (float)dayOfYear + 284.0; 

  float mezzo_di_medio = calcMezzoDiMedio();
  if( mezzo_di_medio == INPUT_ERROR )
    return INPUT_ERROR;

  else
  {
    float dec = 23.45 * sin(omega * t); //declinazione del sole
    float E1 = sin(2.0 * omega * (dayOfYear - 81.0));
    float E2 = sin(omega * (dayOfYear - 1.0));
    float E = -9.87 * E1 + 7.67 * E2; //equazione del tempo

    float mezzo_di = mezzo_di_medio + E/100.0;

    float T = 12 * (1 + (dec * tan(lat / DEG_RAD) / 90.0));

    float twilight_hr;
    if( twilight >= 0 && twilight <= 60 )
    {
      twilight_hr = conv_sessagesimali( 0, twilight);
    }
    else
    {
      twilight_hr = 0;
      return INPUT_ERROR;
    }

    float mezzoT = T / 2.0;
    alba = mezzo_di - (mezzoT) - twilight_hr;
    tramonto = mezzo_di + (mezzoT) + twilight_hr;

    alba_tramonto[SUNRISE_H] = (int)floor(alba);
    alba_tramonto[SUNRISE_M] = (int)floor((alba - alba_tramonto[SUNRISE_H]) * 60.0);

    alba_tramonto[SUNSET_H] = (int)floor(tramonto);
    alba_tramonto[SUNSET_M] = (int)floor((tramonto - alba_tramonto[SUNSET_H]) * 60.0);

    return INPUT_VALID;
  }
}


float SunLight::conv_sessagesimali( uint8_t ore, uint8_t minuti ){
  if( ore < 0 && ore > 60 )
    return INPUT_ERROR;
  else if ( minuti < 0 && minuti > 60 )
    return INPUT_ERROR;
  else {
    float min_dec = minuti / 60.0;
    return ore + min_dec;
  }
}


// This function converts longitude, expressed in degree and minutes first,
// in a time variable that expresses the avverage noon in Greenwich Mean Time.
// If is entered invalid data, the function return an error.

float SunLight::calcMezzoDiMedio ()
{
  float mediumNoon;
  if( lon <= -180.0 || lon >= 180.0 )
    return INPUT_ERROR;
  else{
    float scostamento = lon / DEG_MERIDIUM;
    float mediumNoon = GMT_0 - scostamento;
    return mediumNoon;
  }
}

void SunLight::setPosition ( float latitude, float longitude)
{
  lat = latitude;
  lon = longitude;
}
