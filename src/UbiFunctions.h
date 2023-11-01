#define HOST "industrial.api.ubidots.com"
#define URL "/api/v1.6/devices/"
#define TOKEN "BBFF-Fg2jAwRbEdCNaawuoDkrbxfbtarOn3"
//==============================================================================
void send_3F(const char* DEVICELABEL, const char* varN1, const char* varN2, const char* varN3, float val1, float val2, float val3, bool printT)
  {
//------------------------------------------------------------------------------   
  char    payload[180];
  char    le[4];
  String  response;
//------------------------------------------------------------------------------
//  LGPRSClient client;
  LWiFiClient client;
//------------------------------------------------------------------------------
  sprintf(payload,"%s", "{");
  sprintf(payload,"%s%s%s%s%s", payload, "\"", varN1, "\"", ":"); 
  sprintf(payload,"%s%f", payload, val1);
  sprintf(payload,"%s%s", payload, ",");
  sprintf(payload,"%s%s%s%s%s", payload, "\"", varN2, "\"", ":");
  sprintf(payload,"%s%f", payload, val2);
  sprintf(payload,"%s%s", payload, ",");
  sprintf(payload,"%s%s%s%s%s", payload, "\"", varN3, "\"", ":");
  sprintf(payload,"%s%f", payload, val3);
  sprintf(payload,"%s%s", payload, "}");
//------------------------------------------------------------------------------
  sprintf(le,"%d", strlen(payload));
//------------------------------------------------------------------------------
//  if(printT) Serial.println(payload);
//------------------------------------------------------------------------------
  if(client.connect(HOST, 80))
    {  
    if(printT) Serial.println("Connected!");
    client.print(F("POST "));
    client.print(URL);
    client.print(DEVICELABEL);
    client.println(F(" HTTP/1.1"));
    client.println(F("User-Agent: LinKit One/1.0"));
    client.print(F("X-Auth-Token: "));
    client.println(TOKEN);
    client.println(F("Connection: close"));
    client.println(F("Content-Type: application/json"));
    client.print(F("Content-Length: "));
    client.println(le);
    client.print(F("Host: "));
    client.println(HOST);
    client.println();   
    client.println(payload);
    client.println();
    } 
  else
    {
    if(printT) Serial.println(F("Connection failed"));
    }
//------------------------------------------------------------------------------
  while(client.connected()) 
    {
    while (client.connected() && !client.available());
    char c = client.read();
    if(printT) Serial.print(c);
    }
  client.stop();
  }
//==============================================================================
void send_GPS(const char* DEVICELABEL, float val1, float val2, bool printT)
  {
//------------------------------------------------------------------------------   
  char    payload[180];
  char    le[4];
  String  response;
//------------------------------------------------------------------------------
  LGPRSClient client;
  //LWiFiClient client;
//------------------------------------------------------------------------------
  sprintf(payload,"%s%f%s%f%s", "{\"position\":{\"lat\":",val1, ",\"lng\":", val2,"}}");
  Serial.println(payload);
//------------------------------------------------------------------------------
  sprintf(le,"%d", strlen(payload));
//------------------------------------------------------------------------------
//  if(printT) Serial.println(payload);
//------------------------------------------------------------------------------
  if(client.connect(HOST, 80))
    {  
    if(printT) Serial.println("Connected!");
    client.print(F("POST "));
    client.print(URL);
    client.print(DEVICELABEL);
    client.println(F(" HTTP/1.1"));
    client.println(F("User-Agent: LinKit One/1.0"));
    client.print(F("X-Auth-Token: "));
    client.println(TOKEN);
    client.println(F("Connection: close"));
    client.println(F("Content-Type: application/json"));
    client.print(F("Content-Length: "));
    client.println(le);
    client.print(F("Host: "));
    client.println(HOST);
    client.println();   
    client.println(payload);
    client.println();
    } 
  else
    {
    if(printT) Serial.println(F("Connection failed"));
    }
//------------------------------------------------------------------------------
  while(client.connected()) 
    {
    while (client.connected() && !client.available());
    char c = client.read();
    if(printT) Serial.print(c);
    }
  client.stop();
  }
//==============================================================================
