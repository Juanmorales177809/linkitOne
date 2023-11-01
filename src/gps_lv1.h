//==============================================================================
/*Refer to http://www.gpsinformation.org/dale/nmea.htm#GGA
  Sample data: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
  Where:
  GGA           Global Positioning System Fix Data
  123519        Fix taken at 12:35:19 UTC                                       [1]
  4807.038,N    Latitude 48 deg 07.038' N                                       [2-3]
  01131.000,E   Longitude 11 deg 31.000' E                                      [4-5]
  1             Fix quality:                                                    [6] 
                0 = invalid                                        
                1 = GPS fix (SPS)
                2 = DGPS fix
                3 = PPS fix
                4 = Real Time Kinematic
                5 = Float RTK
                6 = estimated (dead reckoning) (2.3 feature)
                7 = Manual input mode
                8 = Simulation mode
  08           Number of satellites being tracked                             [7]
  0.9          Horizontal dilution of position                                [8]
  545.4,M      Altitude, Meters, above mean sea level                         [9]
  46.9,M       Height of geoid (mean sea level) above WGS84                   [11]
                       ellipsoid
      (empty field) time in seconds since last DGPS update
      (empty field) DGPS station ID number
   *  *47          the checksum data, always begins with *
*/


//==============================================================================
static unsigned char getComma(unsigned char num, const char *str)
{
  unsigned char i, j = 0;
  int len = strlen(str);
  for (i = 0; i < len; i ++)
  {
    if (str[i] == ',')
      j++;
    if (j == num)
      return i + 1;
  }
  return 0;
}
//==============================================================================
static double getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atof(buf);
  return rev;
}
//==============================================================================
static double getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atoi(buf);
  return rev;
}
//==============================================================================
int getOriLon(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  if(buf[0]=='W')
    return 1;
  return -1;
}
//==============================================================================
int getOriLat(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  if(buf[0]=='N')
    return 1;
  return -1;
}
//==============================================================================
void parseGPGGA(const char* GPGGAstr)
{
  char buff[256];
 
  double latitude;
  double longitude;
  int tmp, hour, minute, second, num ;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    hour     = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute   = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second   = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');

//    sprintf(buff, "UTC timer %2d-%2d-%2d", hour, minute, second);
//    Serial.println(buff);

    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp]);
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp]);
//    sprintf(buff, "latitude = %10.4f, longitude = %10.4f", latitude, longitude);
//    Serial.println(buff);

    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
//    sprintf(buff, "satellites number = %d", num);
//    Serial.println(buff);
  }
  else
  {
    char buff[80];
    unsigned int rtc;
    LDateTime.getRtc(&rtc);
    sprintf(buff, "[%012d][%012d][GPSD] Not get data", millis(), rtc);
  }
}
//==============================================================================
int *GPS_TI(const char* GPGGAstr)                                               
{
  int tmp, hour, minute, second;
  static int r[3] = {-1,-1,-1};
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    r[0]  = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');         //Hour
    r[1]  = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');         //Minute
    r[2]  = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');         //Second
  }
else
    return r;
  return r;
  }
//==============================================================================  
double *GPS_LL(const char* GPGGAstr)                                               
{ 
  double latitude, longitude;
  int  tmp, NS, WE;
  static double r[2] = {0, 0};
  if (GPGGAstr[0] == '$')
  {   
//------------------------------------------------------------------------------
    tmp  = getComma(2, GPGGAstr);
    r[0] = getDoubleNumber(&GPGGAstr[tmp]);                                     //Latitude
    tmp  = getComma(3, GPGGAstr);
    NS   = getOriLat(&GPGGAstr[tmp]);
    r[0] = NS*r[0];
//------------------------------------------------------------------------------   
    tmp  = getComma(4, GPGGAstr);
    r[1] = getDoubleNumber(&GPGGAstr[tmp]);                                     //Longitude
    WE   = getOriLon(&GPGGAstr[tmp]);
    r[1] = WE*r[1];
  }
else
    return r;
  return r;
  }
//==============================================================================
int GPS_FQ(const char* GPGGAstr)                                               
{
  int tmp, fq;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(6, GPGGAstr);
    fq  = getIntNumber(&GPGGAstr[tmp]);
  }
else
    return -1;
  return fq;
  }
//==============================================================================
int GPS_NS(const char* GPGGAstr)                                               
{
  int tmp;
  double ns;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(7, GPGGAstr);
    ns  = getIntNumber(&GPGGAstr[tmp]);
  }
else
    return -1;
  return ns;
  }
  
//==============================================================================
double GPS_DP(const char* GPGGAstr)                                               
{
  int tmp;
  double dp;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(8, GPGGAstr);
    dp  = getDoubleNumber(&GPGGAstr[tmp]);
  }
else
    return -1;
  return dp;
  }
//==============================================================================
double GPS_HE(const char* GPGGAstr)                                               
{
  int tmp;
  double he;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(9, GPGGAstr);
    he  = getDoubleNumber(&GPGGAstr[tmp]);
  }
else
    return -1;
  return he;
  }
//==============================================================================
double GPS_HG(const char* GPGGAstr)                                               
{
  int tmp;
  double hg;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(11, GPGGAstr);
    hg  = getDoubleNumber(&GPGGAstr[tmp]);
  }
else
    return -1;
  return hg;
  }
//==============================================================================
float sexa2dec(float GPS_LLa)
  {
  //GPS_LLa1 = 614.7676;
  float tmp0 = (int)(GPS_LLa/100);
  float tmp1 = (GPS_LLa-(int)GPS_LLa)/36;
  float tmp2 = (int)(((GPS_LLa/100)-(int)(float)GPS_LLa/100)*100)/60.0;
  return(tmp0+tmp2+tmp1);
  }
//==============================================================================
  

float sexa2dec2(float GPS_LLa)
  {
  float tmp0 = GPS_LLa/100;
  float tmp1 = ((float)(tmp0-(int)tmp0)*100)/60;  
  return((int)tmp0+tmp1);
  }

    

  
