#define ThiE true
#define GPSE true
//=============================================================================
#include <LTask.h>
#include <LDateTime.h>
#if GPSE
#include <LGPS.h>
#endif
#include "log_lv1.h"
#include <LBattery.h>
#if ThiE
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h>
#endif
#include "sps30.h"
#include "BlueDot_BME280.h"
#include "DFRobot_OzoneSensor.h"
//=============================================================================
#if ThiE
#define WIFI_AP "UCES_Concesionarios"
#define WIFI_PASSWORD "Cafeterias2023*.*"
//#define WIFI_AP "WIFI-ITM"
//#define WIFI_PASSWORD ""
#define WIFI_AUTH LWIFI_WPA 
#define TOKEN "3blrjWlaJahUkEnWYkr3"
#endif
//=============================================================================
#define SP30_COMMS SERIALPORT1
#define TX_PIN 8
#define RX_PIN 8
#define DEBUG 0                                                                 //0 : No messages, 1 : Request sending and receiving, 2 : Request sending and receiving + show protocol errors
#define SPS30_ACINT -1                                                          //0 = Disable Auto Clean, -1 = Do not change current setting
#define SPS30_CLNOW  0                                                          //Perform a clean NOW, 1 = yes, 0 = NO
//#define LED_ADV 13                                                              //LED Linkit One
#define BLOWER1 5                                                               //Blower
#define BLOWER2 6                                                               //Blower
#define COLLECT_NUMBER   20                                                     //Collect number, the collection range is 1-100
#define Ozone_IICAddress OZONE_ADDRESS_3
//==============================================================================
const uint32_t  READ_DELAYS = 600000;
const uint32_t  READ_DELAYB = 60000;
static uint32_t msDelayS    = millis();
static uint32_t msDelayB    = millis();
//==============================================================================
BlueDot_BME280      bme;
DFRobot_OzoneSensor z27;
//==============================================================================
#if GPSE
gpsSentenceInfoStruct gpsInfo;
#endif
//==============================================================================
#if ThiE
char thingsboardServer[] = "thingsboard.cloud";
LWiFiClient wifiClient;
PubSubClient client( wifiClient );
#endif
unsigned long lastSend;
//==============================================================================
SPS30 sps30;
bool SPS30B;                                                                    //Begin out
bool SPS30P;                                                                    //Probe out
bool SPS30R;                                                                    //Reset out
bool SPS30S;                                                                    //Serial Number out
bool SPS30I;                                                                    //Start out
bool SPS30C;                                                                    //Clean out
bool SPS30E;                                                                    //Execute clean out
bool SPS30T;                                                                    //Set clean interval out
bool SPS30V;                                                                    //Get values out
bool BM280E;                                                                    //BME280 enable
bool ZE27OE;                                                                    //ZE27O3 enable
char SPS30_SN[32];                                                              //Serial Number buffer
uint32_t SPS30_CLIN = 345600;                                                   //Clean interval [Seconds]
const char* SPS30_INI_FN  = "SPS30_INI_FN.txt";
const char* SPS30_NPR_FN  = "SPS30_NPR_FN.txt";
const char* SPS30_MCR_FN  = "SPS30_MCR_FN.txt";
const char* SPS30_PCZ_FN  = "SPS30_PCZ_FN.txt";
const char* BM280_INI_FN  = "BM280_INI_FN.txt";
const char* BM280_THP_FN  = "BM280_THP_FN.txt";
const char* ZE27O_INI_FN  = "ZE27O_INI_FN.txt";
const char* ZE27O_OZN_FN  = "ZE27O_OZN_FN.txt";
#if GPSE
const char* GPSCD_UTC_FN  = "GPSCD_UTC_FN.txt";
const char* GPSCD_COO_FN  = "GPSCD_COO_FN.txt";
const char* GPSCD_EXT_FN  = "GPSCD_EXT_FN.txt";
#endif
const char* BATTY_LEV_FN  = "BATTY_LEV_FN.txt";
const char* BATTY_ISC_FN  = "BATTY_ISC_FN.txt";
//==============================================================================
bool pre = true;                                                                //Print enable
bool lof = true;                                                                //Log file enable
//==============================================================================
void setup() {
  //Serial.begin(9600);
  
//------------------------------------------------------------------------------
  #if GPSE
  LGPS.powerOn();
  //Serial.println("GPS started.");
  #endif
  //LGPS.powerOff();
//------------------------------------------------------------------------------
  #if ThiE
  
  client.setServer( thingsboardServer, 1883 );
  lastSend = 0;
  #endif
  //============================================================================
  pinMode(BLOWER1, OUTPUT);
  pinMode(BLOWER2, OUTPUT);
  digitalWrite(BLOWER1, LOW);
  digitalWrite(BLOWER2, LOW);
  #if GPSE
  log_SD_begin();
  LTask.begin();
  #endif
//------------------------------------------------------------------------------
  sps30.EnableDebugging(DEBUG);
  sps30.SetSerialPin(RX_PIN, TX_PIN);
//  sps30.wakeup();
  SPS30B = sps30.begin(SP30_COMMS);
  sps30.wakeup();
  if(SPS30B) log_ER("SPS3", "INI", "Begin", SPS30_INI_FN, pre, lof);
  SPS30P = sps30.probe();
  if(SPS30P) log_ER("SPS3", "INI", "Probe", SPS30_INI_FN, pre, lof);
  SPS30R = sps30.reset();
  if(SPS30R) log_ER("SPS3", "INI", "Reset", SPS30_INI_FN, pre, lof);
//------------------------------------------------------------------------------
  SPS30S = sps30.GetSerialNumber(SPS30_SN, 32);
  if(SPS30S==0) log_ST("SPS3", "INI", "SE/NU", SPS30_SN, SPS30_INI_FN, pre, lof);
  SPS30T = sps30.SetAutoCleanInt(SPS30_CLIN);
  if(SPS30T==0) log_EX("SPS3", "INI", "SetCI", SPS30_INI_FN, pre, lof);
  SPS30C = sps30.GetAutoCleanInt(&SPS30_CLIN);
  if(SPS30C==0) log_1I("SPS3", "CLI", SPS30_CLIN, SPS30_INI_FN, pre, lof);
  if(SPS30_CLNOW) SPS30E = sps30.clean();
  if(SPS30E) log_EX("SPS3", "INI", "Clean", SPS30_INI_FN, pre, lof);
//------------------------------------------------------------------------------
  SPS30I = sps30.start();
  if(SPS30I) log_ER("SPS3", "INI", "Start", SPS30_INI_FN, pre, lof);
//------------------------------------------------------------------------------
//Configuración de parametros BME680
  bme.parameter.communication         = 0;
  bme.parameter.I2CAddress            = 0x77;
  bme.parameter.sensorMode            = 0b11;
  bme.parameter.IIRfilter             = 0b100;
  bme.parameter.humidOversampling     = 0b101;
  bme.parameter.tempOversampling      = 0b101; 
  bme.parameter.pressOversampling     = 0b101; 
  bme.parameter.pressureSeaLevel      = 1013.25;
  bme.parameter.tempOutsideCelsius    = 15;
  bme.parameter.tempOutsideFahrenheit = 59;
  //Inicializar Sensor BME680
  if (bme.init() == 0x60) BM280E = true;
  if (BM280E) log_ER("B280", "INI", "Begin", BM280_INI_FN, pre, lof);
//------------------------------------------------------------------------------
//Inicializar Sensor ZE27O3
  ZE27OE = z27.begin(Ozone_IICAddress);
  if (ZE27OE) log_ER("ZE27", "INI", "Begin", ZE27O_INI_FN, pre, lof);
  z27.setModes(MEASURE_MODE_PASSIVE);
//------------------------------------------------------------------------------
 #if ThiE
   LWiFi.begin();
  client.setServer( thingsboardServer, 1883 );
  lastSend = 0;
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) ;
  //Serial.println("WiFi attached!");
  
#endif
  //-----------------------------------------------------------------------------
}

void loop() {
  #if ThiE
  LWifiStatus ws = LWiFi.status();
  boolean status = wifi_status(ws);
  if (!status) {
    //Serial.println("Connecting to AP ...");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
      delay(500);
    }
    //Serial.println("Connected to AP");
  }
 
  if ( !client.connected() ) {
    reconnect();
    //Serial.println("Reconnect...");
    
  }
  #endif
  
  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    getAndSendData();
    lastSend = millis();
  }
#if ThiE
  client.loop();
#endif
}
void getAndSendData()
{
   //-------------------------------------------------------------------------
  //Serial.println("Inicializando Sensores...");
  struct sps_values val;
  float SPS30_MCR[4];
  float SPS30_NPR[4];
  float SPS30_PSZ;
  //-------------------------------------------------------------------------
  float BM280_THP[4];
  //-------------------------------------------------------------------------
  int16_t ZE27O_OZN;
  //-------------------------------------------------------------------------
  #if GPSE
  int     *GPS_TIa;
  double  *GPS_LLa;
  int     GPS_FQi, GPS_NSi;
  double  GPS_DPd, GPS_HEi, GPS_HGi;
  #endif
  //-------------------------------------------------------------------------
  int     BATTY_LEV[2];
  bool    blowerOn = false;
//------------------------------------------------------------------------------
  #if GPSE
  LGPS.getData(&gpsInfo);
  //Serial.println((char*)gpsInfo.GPGGA);
  #endif
//------------------------------------------------------------------------------
  if(millis() - msDelayS<READ_DELAYS) return;
  msDelayS = millis();
  blowerOn = true;
//------------------------------------------------------------------------------ 
  if(blowerOn) digitalWrite(BLOWER1, HIGH);
  if(blowerOn) digitalWrite(BLOWER2, HIGH);
  delay(READ_DELAYB);
  blowerOn = false;
  digitalWrite(BLOWER1, LOW);
  digitalWrite(BLOWER2, LOW);
//------------------------------------------------------------------------------
  //Inizializar SPS30 
  
  sps30.wakeup();
  //Serial.println("Inizializar...");
  delay(7000);
//------------------------------------------------------------------------------
//Obtener valores de SPS30
  SPS30V = sps30.GetValues(&val);                                               //Get values from SPS30
  if(SPS30V==0) log_ER("SPS3", "LEC", "Value", SPS30_INI_FN, 0, 0);             //Print and save disable
//------------------------------------------------------------------------------
// Mass Concentration P1.0 P2.5 P4.0 P10
  if(SPS30V == 0) SPS30_MCR[0] = val.MassPM1;                                   //Mass Concentration P1.0
  if(SPS30V == 0) SPS30_MCR[1] = val.MassPM2;                                   //Mass Concentration P2.5
  if(SPS30V == 0) SPS30_MCR[2] = val.MassPM4;                                   //Mass Concentration P4.0
  if(SPS30V == 0) SPS30_MCR[3] = val.MassPM10;                                  //Mass Concentration P10
  if(SPS30V==0) log_4F("SPS3", "MCR", SPS30_MCR[0], SPS30_MCR[1], SPS30_MCR[2], SPS30_MCR[3], SPS30_MCR_FN, pre, lof);
//------------------------------------------------------------------------------
// Number concentration P0.5 P1.0 P2.5 P4.0 P10
  if(SPS30V == 0) SPS30_NPR[0] = val.NumPM0;                                    //Number concentration P0.5
  if(SPS30V == 0) SPS30_NPR[1] = val.NumPM1;                                    //Number concentration P1.0
  if(SPS30V == 0) SPS30_NPR[2] = val.NumPM2;                                    //Number concentration P2.5
  if(SPS30V == 0) SPS30_NPR[3] = val.NumPM4;                                    //Number concentration P4.0
  if(SPS30V == 0) SPS30_NPR[4] = val.NumPM10;                                   //Number concentration P10
  if(SPS30V==0) log_5F("SPS3", "NPR", SPS30_NPR[0], SPS30_NPR[1], SPS30_NPR[2], SPS30_NPR[3], SPS30_NPR[4], SPS30_NPR_FN, pre, lof);//Print Number concentration P0.5 P1.0 P2.5 P4.0 P10
  //Serial.print("Este es");
  //Serial.println(SPS30_NPR[0]);
//------------------------------------------------------------------------------
// Typical particle size
  SPS30_PSZ = val.PartSize;//Typical particle size
  if(SPS30V==0) log_1F("SPS3", "TPS", SPS30_PSZ, SPS30_PCZ_FN, pre, lof);        //Print Typical particle size
//------------------------------------------------------------------------------
  if(BM280E) BM280_THP[0] = bme.readTempC();                                      //Read Temperature
  if(BM280E) BM280_THP[1] = bme.readHumidity();                                   //Read Humidity
  if(BM280E) BM280_THP[2] = bme.readPressure();                                   //Read Pressure
  if(BM280E) BM280_THP[3] = bme.readAltitudeMeter();                              //Read Altitude
  if(BM280E) log_4F("B280", "THP", BM280_THP[0], BM280_THP[1], BM280_THP[2], BM280_THP[3], BM280_THP_FN, pre, lof);//Print Temperature, Humidity, Pressure
//------------------------------------------------------------------------------
  ZE27O_OZN = z27.readOzoneData(COLLECT_NUMBER);                                   //Read Ozone data
  if(ZE27OE) log_1I("ZE27", "OZN", ZE27O_OZN, ZE27O_OZN_FN, pre, lof);             //Print Ozone data
//------------------------------------------------------------------------------
  #if GPSE
  char latitude[20];
  char lat_direction[1];
  char longitude[20];
  char lon_direction[1];
  char buf[20];
  char time[30];
  const char* p = (char*)gpsInfo.GPGGA;

  p = nextToken(p, 0); // GGA
  p = nextToken(p, time); // Time
  p = nextToken(p, latitude); // Latitude
  p = nextToken(p, lat_direction); // N or S?
  p = nextToken(p, longitude); // Longitude
  p = nextToken(p, lon_direction); // E or W?
  p = nextToken(p, buf); // fix quality

  const int coord_size = 8;
  char lat_fixed[coord_size], lon_fixed[coord_size];
  convertCoords(latitude, longitude, lat_direction, lon_direction, lat_fixed, lon_fixed, coord_size);
  #endif
//------------------------------------------------------------------------------
  // Obtain battery level
  String batteryLevel = String(LBattery.level());
  String batteryCharging = LBattery.isCharging() == 1 ? "true" : "false";

  log_1I("BATT", "LEV", BATTY_LEV[0], BATTY_LEV_FN, pre, lof);                     //Print Battery level
  log_1I("BATT", "ISC", BATTY_LEV[1], BATTY_ISC_FN, pre, lof);                     //Print Battery is charging
//------------------------------------------------------------------------------
//C.R.P.C. LAT: 000614.7676 LON: -07534.9319                                    //Sexagesimal
//C.R.P.C. LAT: 000624.6560 LON: -07558.2067                                    //Decimal
//C.R.P.C. LAT: 6.246124  LON: -75.582289                                             
//  Serial.println(sexa2dec(GPS_LLa[0]),4);
 
//  send_GPS("CES_01",sexa2dec2(GPS_LLa[0]), sexa2dec2(GPS_LLa[1]), 1);
//  delay(2000);

//------------------------------------------------------------------------------
//Crear una cadena JSON que contiene los datos 
#if GPSE
  String payload = "{";
  payload += "\"latitude\":"; payload += lat_fixed; payload += ", ";
  payload += "\"longitude\":"; payload += lon_fixed; payload += ", ";
  payload += "\"batteryLevel\":"; payload += batteryLevel;  payload += ", ";
  payload += "\"batteryCharging\":"; payload += batteryCharging;
  payload += "}";
  //Serial.println(payload);
#endif
  //------------------------------------------------------------------------------
  //Crear una cadena JSON que contenga los datos obtenidos en el sensor sps30
  String sensirion = "{";
  sensirion += "\"MassPM1\":"; sensirion += float(SPS30_MCR[0]); sensirion += ", ";
  sensirion += "\"MassPM2\":"; sensirion += float(SPS30_MCR[1]); sensirion += ", ";
  sensirion += "\"MassPM4\":"; sensirion += float(SPS30_MCR[2]); sensirion += ", ";
  sensirion += "\"MassPM10\":"; sensirion += float(SPS30_MCR[3]); sensirion += ", ";
  sensirion += "\"PartSize\":"; sensirion += float(SPS30_PSZ);
  sensirion += "}";
   //Serial.println(sensirion);
  String sensirion1 = "{";
  sensirion1 += "\"NumPM0\":"; sensirion1 += float(SPS30_NPR[0]); sensirion1 += ", ";
  sensirion1 += "\"NumPM1\":"; sensirion1 += float(SPS30_NPR[1]); sensirion1 += ", ";
  sensirion1 += "\"NumPM2\":"; sensirion1 += float(SPS30_NPR[2]); sensirion1 += ", ";
  sensirion1 += "\"NumPM4\":"; sensirion1 += float(SPS30_NPR[3]); sensirion1 += ", ";
  sensirion1 += "\"NumPM10\":"; sensirion1 += float(SPS30_NPR[4]); sensirion1 += ", "; 
  sensirion1 += "}";
  //Serial.println(sensirion1);
 
  //------------------------------------------------------------------------------
  //Crear una cadena JSON que contenga los datos obtenidos en el sensor bme280
  String bme280 = "{";
  bme280 += "\"Temperature\":"; bme280 += BM280_THP[0]; bme280 += ", ";
  bme280 += "\"Humidity\":"; bme280 += BM280_THP[1]; bme280 += ", ";
  bme280 += "\"Pressure\":"; bme280 += BM280_THP[2]; bme280 += ", ";
  bme280 += "\"Altitude\":"; bme280 += BM280_THP[3];
  bme280 += "}";
 
  //Serial.println(bme280);

  //------------------------------------------------------------------------------
  //Crear una cadena JSON que contenga los datos obtenidos en el sensor ze27o3
  String ze27o3 = "{";
  ze27o3 += "\"Ozone\":"; ze27o3 += ZE27O_OZN;
  ze27o3 += "}";
  //Serial.println(ze27o3);
  //------------------------------------------------------------------------------
  //Se convierte la cadena JSON payload en un arreglo de caracteres llamado attributes utilizando toCharArray()
  char attributes_gps[100];
  payload.toCharArray( attributes_gps, 100 );
  char attributes_sensirion[100];
  sensirion.toCharArray( attributes_sensirion, 100 );
  char attributes_sensirion1[100];
  sensirion1.toCharArray(attributes_sensirion1,100);
  char attributes_bme280[100];
  bme280.toCharArray( attributes_bme280, 100 );
  char attributes_ze27o3[100];
  ze27o3.toCharArray( attributes_ze27o3, 100 );
  //------------------------------------------------------------------------------  
  //Enviar los datos a thingsboard
  
    client.publish( "v1/devices/me/attributes", attributes_gps );
    delay(2000);
    client.publish( "v1/devices/me/telemetry", attributes_bme280 );
    delay(2000);
    client.publish( "v1/devices/me/telemetry", attributes_sensirion );
    delay(2000);
    client.publish( "v1/devices/me/telemetry", attributes_sensirion1 );
    delay(2000);
    client.publish( "v1/devices/me/telemetry", attributes_ze27o3 );
    delay(2000);
    
   
  //------------------------------------------------------------------------------
  

  // Prepare a JSON payload string
  // String payload = "{";
  // payload += "\"latitude\":"; payload += lat_fixed; payload += ", ";
  // payload += "\"longitude\":"; payload += lon_fixed; payload += ", ";
  // payload += "\"batteryLevel\":"; payload += batteryLevel;  payload += ", ";
  // payload += "\"batteryCharging\":"; payload += batteryCharging;
  // payload += "}";


  // send_3F("CES_01", "tem", "hum", "pre", BM280_THP[0],  BM280_THP[1], BM280_THP[2], 1);
  // delay(2000);
  // send_3F("CES_01", "bat", "ozn", "psz", BATTY_LEV[0],  ZE27O_OZN   , SPS30_PSZ,    1);
  // delay(2000);
  // send_3F("CES_01", "mc1", "mc2", "mc3", SPS30_MCR[0],  SPS30_MCR[1], SPS30_MCR[3], 1);
  // delay(2000);

  sps30.sleep();
  //Serial.flush();
 
  
}
void convertCoords(const char* latitude, const char* longitude, const char* lat_direction,
                   const char* lon_direction, char* lat_return, char* lon_return, int buff_length)
{
  char lat_deg[3];

  // extract the first 2 chars to get the latitudinal degrees
  strncpy(lat_deg, latitude, 2);

  // null terminate
  lat_deg[2] = 0;

  char lon_deg[4];

  // extract first 3 chars to get the longitudinal degrees
  strncpy(lon_deg, longitude, 3);

  // null terminate
  lon_deg[3] = 0;

  // convert to integer from char array
  int lat_deg_int = arrayToInt(lat_deg);
  int lon_deg_int = arrayToInt(lon_deg);

  // must now take remainder/60
  // this is to convert from degrees-mins-secs to decimal degrees
  // so the coordinates are "google mappable"

  // convert the entire degrees-mins-secs coordinates into a float - this is for easier manipulation later
  float latitude_float = arrayToFloat(latitude);
  float longitude_float = arrayToFloat(longitude);

  // remove the degrees part of the coordinates - so we are left with only minutes-seconds part of the coordinates
  latitude_float = latitude_float - (lat_deg_int * 100);
  longitude_float = longitude_float - (lon_deg_int * 100);

  // convert minutes-seconds to decimal
  latitude_float /= 60;
  longitude_float /= 60;

  // add back on the degrees part, so it is decimal degrees
  latitude_float += lat_deg_int;
  longitude_float += lon_deg_int;

  if (strcmp (lat_direction, "S") == 0) {
    latitude_float *= -1;
  }

  if (strcmp (lon_direction, "W") == 0) {
    longitude_float *= -1;
  }

  // format the coordinates nicey - no more than 6 decimal places
  snprintf(lat_return, buff_length, "%2.6f", latitude_float);
  snprintf(lon_return, buff_length, "%3.6f", longitude_float);
}
const char *nextToken(const char* src, char* buf)
{
  int i = 0;
  while (src[i] != 0 && src[i] != ',')
    i++;
  if (buf)
  {
    strncpy(buf, src, i);
    buf[i] = 0;
  }
  if (src[i])
    i++;
  return src + i;
}
float arrayToFloat(const char* char_array)
{
  float temp;
  sscanf(char_array, "%f", &temp);
  return temp;
}
int arrayToInt(const char* char_array)
{
  int temp;
  sscanf(char_array, "%d", &temp);
  return temp;
}
void InitLWiFi()
{
  #if ThiE
  LWiFi.begin();
  // Keep retrying until connected to AP
  // Serial.println("Connecting to AP ...");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
    delay(500);
  
  }
  #endif
  // Serial.println("Connected to AP");
}
#if ThiE
void reconnect() {
  // Loop until we're reconnected
  
  while (!client.connected()) {
    // Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("LinkIt One Device", TOKEN, NULL) ) {
      // Serial.println( "[DONE]" );
    } else {
      // Serial.print( "[FAILED] [ rc = " );
      // Serial.print( client.state() );
      // Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      
      delay( 5000 );
    }
  }
}

boolean wifi_status(LWifiStatus ws) {
  switch (ws) {
    case LWIFI_STATUS_DISABLED:
      return false;
      break;
    case LWIFI_STATUS_DISCONNECTED:
      return false;
      break;
    case LWIFI_STATUS_CONNECTED:
      return true;
      break;
  }
  return false;
}
#endif
