#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../../tm4c123gh6pm.h"

#include "../../MCAL/UART/UART.h"
#include "../../MCAL/GPIO/GPIO.h"

#include "GPS.h"



f32 atof2(u8 *str) {
    f32 result = 0.0;
    f32 fraction = 0.0;
    u32 divisor = 10;
    s32 sign = 1;
    u32 decimal_seen = 0;

    // Handle leading whitespace
    while (*str == ' ') {
        str++;
    }

    // Handle optional sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Process digits
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            if (decimal_seen) {
                fraction += (*str - '0') / (f32)divisor;
                divisor *= 10;
            } else {
                result = result * 10 + (*str - '0');
            }
        } else if (*str == '.') {
            decimal_seen = 1;
        } else {
            break; // Stop parsing on encountering non-numeric character
        }
        str++;
    }

    result += fraction;
    return result * sign;
}

f32 get_lat(u8 *fix, u8 len){
u8 i ;
u8 j=0;
u8 k=0;
static f32 lat_1;	
static u8 lat[10];
for(i=0; i<len; i++){
    if (fix[i] == comma){
    j++;
    }
    if(j == 1 && fix[i] == 'V'){
      break;  
     }
       if(j == 2 && fix[i]!= comma){
       lat[k]=fix[i];
       k++;
       }
       if(j == 3){
        lat[k]= '\0';
      if(fix[i] == 'S'){
        lat_1= -1 * atof2(lat);
        break;
      }
      else if(fix[i] == 'N'){
        lat_1= atof2(lat);
        break;
      }
    }
  }
     return lat_1;
}

f32 get_long(u8 *fix, u8 len){
u8 i=0;
u8 j=0;
u8 k=0;
static f32 lon_1 ;
static u8 lon[10];
for(i=0; i<len; i++){
    if (fix[i] == comma){
    j++;
    }
    if(j == 1 && fix[i] == 'V'){
      break;  
     }
       if(j == 4 && fix[i]!= comma){
       lon[k]=fix[i];
       k++;
       }
       if(j == 5){
        lon[k]= '\0';
      if(fix[i] == 'W'){
        lon_1= -1 * atof2(lon);
        break;
      }
      else if(fix[i] == 'E'){
        lon_1= atof2(lon);
        break;
      }
    }
  }
  return lon_1;
}

f32 ToDegreesAndMinutes(f32 decimalDegrees) {
    u32 degrees = (u32)decimalDegrees; // Extract integer part as degrees
    f32 fractionalPart = decimalDegrees - degrees; // Extract fractional part
    f32 minutes = fractionalPart * 60.0; // Convert fractional part to minutes
    return ((degrees * 100) + minutes); // Combine degrees and minutes in format
}

f32 ToDegree (f32 angle) {
int degree = (int) angle / 100 ;
float minutes = angle - (float) degree*100; 
return (degree+ (minutes/60));
}

f32 ToRadians(f32 degrees) {
    return degrees * (pi / 180.0);
}

f32 get_distance(f32 lat1, f32 lon1, f32 lat2, f32 lon2) {            //Printing integer or decimal?
    // Convert latitude and longitude from degrees to radians
    f32 dlat;
    f32 dlon;
	  f32 a;
	  f32 c;
	  f32 distance;
	  lat1 = ToRadians(ToDegree(lat1));
    lon1 = ToRadians(ToDegree(lon1));
    lat2 = ToRadians(ToDegree(lat2));
    lon2 = ToRadians(ToDegree(lon2));
    
    // Haversine formula
    dlat = lat2 - lat1;
    dlon = lon2 - lon1;
    a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = RADIUS_OF_EARTH * c;
    
    return (f32) distance ;
}

void subs(f32 *lat1, f32 *lon1, f32 *lat2, f32 *lon2){
  *lat1= *lat2;
  *lon1= *lon2;
}

