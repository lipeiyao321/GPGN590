#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 153, 35);
EthernetServer server(80);

void setup()
{
  Serial.begin (115200);
  Ethernet.begin(mac, ip);
  server.begin( );
}

void loop( )
{
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  ss.begin(GPSBaud);

  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT,
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);
  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);
  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);
  sensors_event_t event;
  mag.getEvent(&event);

  float lt = gps.location.lat( );
  Serial.println(lt);
  float ln = gps.location.lng( );
  Serial.println(ln);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = -4.78;
  heading += declinationAngle;

  if (heading < 0)
    heading += 2 * PI;

  if (heading > 2 * PI)
    heading -= 2 * PI;

  float headingDegrees = heading * 180 / M_PI;
  float x = event.magnetic.x;
  float y = event.magnetic.y;
  float z = event.magnetic.z;
  EthernetClient client = server.available();
  if (client)
  {
    boolean currentLineIsBlank = true;
    while (client.connected ( ) )
    {
      if (client.available ( ) )
      {
        char character = client.read ( );
        Serial.write(character);
        if (character == '\n' && currentLineIsBlank)
        {
          client.println ("HTTP/1.1 200 OK");
          client.println ("Content-Type: text/html");
          client.println ("Connection: close");
          client.println ("Refresh: 5");
          client.println ( );
          client.println ("<!DOCTYPE HTML>");
          client.println ("<html>");
          client.print ("<Title>Arduino Ethernet Local Webserver </Title>");
          client.print ("<h1>Arduino Ethernet Shield Local Webserver </h1>");
          client.print ("<h4>Latitude: ");
          client.print (lt); client.print(" ");
          client.print ("</h4><h4>Longitude: ");
          client.print (ln); client.print(" ");
          client.print ("</h4><h4><h4>Mag X (T): ");
          client.print (x); client.print(" "); 
          client.print ("</h4><h4><h4><h4>Mag Y (T): ");
          client.print (y); client.print(" ");
          client.print ("</h4><h4><h4><h4><h4>Mag Z (T): ");
          client.print (z); client.print(" ");                  
          client.println ("<br />");
          client.println ("</html>");
          break;
        }

        if ( character == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (character != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1000);
    client.stop();
  }
}
static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len - 1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }

  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i = 0; i < len; ++i)
    Serial.print(i < slen ? str[i] : ' ');
  smartDelay(0);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
