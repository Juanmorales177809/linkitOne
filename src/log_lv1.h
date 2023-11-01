#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>
//==============================================================================
#define Drv LFlash          // use Internal 10M Flash
//#define Drv LSD                                                                 // Use SD card
//==============================================================================
void log_SD_begin()
{
  pinMode(10, OUTPUT);
  Drv.begin();
}
//==============================================================================
void log_TI(const char* type, const char* origen, int hour, int minute, int second, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %02d:%02d:%02d", millis(), rtc, type, origen, hour, minute, second);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,80);
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_2V(const char* type, const char* var1, const char* var2, double val1, double val2, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %011.4f %s: %011.4f", millis(), rtc, type, var1, val1, var2, val2);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,80);
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_ER(const char* type, const char* origen, const char* fun, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %s OK", millis(), rtc, type, origen, fun);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_EX(const char* type, const char* origen, const char* fun, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %s executed", millis(), rtc, type, origen, fun);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_ST(const char* type, const char* origen, const char* fun, const char* msg, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %s %s", millis(), rtc, type, origen, fun, msg);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_1I(const char* type, const char* fun, int val, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %08d", millis(), rtc, type, fun, val);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,80);
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_1F(const char* type, const char* fun, float v1, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %08.2f", millis(), rtc, type, fun, v1);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_4F(const char* type, const char* fun, float v1, float v2, float v3, float v4, const char* fileN, bool printT, bool saveD)
{
  char buff[80];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %08.2f %08.2f %08.2f %08.2f", millis(), rtc, type, fun, v1, v2, v3, v4);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
void log_5F(const char* type, const char* fun, float v1, float v2, float v3, float v4, float v5, const char* fileN, bool printT, bool saveD)
{
  char buff[90];
  unsigned int rtc;
  LDateTime.getRtc(&rtc);
  LFile dataFile = Drv.open(fileN, FILE_WRITE);
  if(printT || saveD) sprintf(buff, "[%012d][%012d][%s] %s: %08.2f %08.2f %08.2f %08.2f %08.2f", millis(), rtc, type, fun, v1, v2, v3, v4, v5);
  if(printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.println(buff);
  memset(buff,0,sizeof(buff));
//  if(dataFile && printT)  sprintf(buff, "[%012d][%012d][%s] Save OK/EN", millis(), rtc, type);
//  if(dataFile && printT)  Serial.println(buff);
  if(!dataFile && printT) sprintf(buff, "[%012d][%012d][%s] Save ER/DI", millis(), rtc, type);
  if(!dataFile && printT) Serial.println(buff);
  if(dataFile && saveD) dataFile.close();
}
//==============================================================================
