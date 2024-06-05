#ifndef GPS_H
#define GPS_H

#define RADIUS_OF_EARTH 6371*1000       // Earth's radius
#define pi 3.1414592
#define CHECKSUM 0x2A
#define comma   0x2C



f32 ToDegreesAndMinutes(f32 decimalDegrees);
f32 ToDegree (f32 angle);
f32 ToRadians(f32 degrees) ;
f32 get_distance(f32 lat1, f32 lon1, f32 lat2, f32 lon2);
void subs(f32 *lat1, f32 *lon1, f32 *lat2, f32 *lon2);
f32 atof2(u8 *str);
f32 get_lat(u8 *fix, u8 len );
f32 get_long(u8 *fix, u8 len);







#endif
