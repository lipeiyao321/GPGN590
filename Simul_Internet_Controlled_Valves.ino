#include <SPI.h>
#include <Ethernet.h>
// MAC address for shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetServer server(80); // Using port 80
int eightChanRelayIN1 = 11;   //variable for relay channel 11 drive pin
int eightChanRelayIN2 = 10;   //variable for relay channel 10 drive pin
int eightChanRelayIN3 = 9;   //variable for relay channel 9 drive pin
int eightChanRelayIN4 = 8;   //variable for relay channel 8 drive pin
//int eightChanRelayIN5 = 7;   //variable for relay channel 7 drive pin
//int eightChanRelayIN6 = 6;   //variable for relay channel 6 drive pin
//int eightChanRelayIN7 = 5;   //variable for relay channel 5 drive pin
//int eightChanRelayIN8 = 4;   //variable for relay channel 4 drive pin

void setup() 
{
pinMode(eightChanRelayIN1, OUTPUT); //set the relay drive pin for channel 11 to be an output
pinMode(eightChanRelayIN2, OUTPUT); //set the relay drive pin for channel 10 to be an output
pinMode(eightChanRelayIN3, OUTPUT); //set the relay drive pin for channel 9 to be an output
pinMode(eightChanRelayIN4, OUTPUT); //set the relay drive pin for channel 8 to be an output
//pinMode(eightChanRelayIN5, OUTPUT); //set the relay drive pin for channel 7 to be an output
//pinMode(eightChanRelayIN6, OUTPUT); //set the relay drive pin for channel 6 to be an output
//pinMode(eightChanRelayIN7, OUTPUT); //set the relay drive pin for channel 5 to be an output
//pinMode(eightChanRelayIN8, OUTPUT); //set the relay drive pin for channel 4 to be an output
Ethernet.begin(mac); // Start the Ethernet shield
server.begin();
Serial.begin(9600); // Start serial communication
Serial.println("Server address:"); // Print server address
// (Arduino shield)
Serial.println(Ethernet.localIP());
}

void loop() {
EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    String buffer = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Read from the Ethernet shield
        buffer += c; // Add character to string buffer
        // Client sent request, now waiting for response
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK"); // HTTP response
          client.println("Content-Type: text/html");
          client.println(); // HTML code
          client.print("<center><br><h1>Valves Operator</h1><br><br><br><FORM>");
          client.print("<P> <INPUT type=\"submit\" name=\"status1\"value=\"ON\">");
          client.print("<P> <INPUT type=\"submit\" name=\"status1\"value=\"OFF\">");
//          client.print("<P> <INPUT type=\"submit\" name=\"status2\"value=\"2ON\">");
//          client.print("<P> <INPUT type=\"submit\" name=\"status2\"value=\"2OFF\">");
//          client.print("<P> <INPUT type=\"submit\" name=\"status3\"value=\"3ON\">");
//          client.print("<P> <INPUT type=\"submit\" name=\"status3\"value=\"3OFF\">");
          client.print("</FORM></center>");
        break;
        }
        if (c == '\n') {
        currentLineIsBlank = true;
        buffer = "";
        }
        else if (c == '\r') { // Command from webpage
        
        // Did the on button get pressed
        if (buffer.indexOf("GET /?status1=ON") >= 0)
          digitalWrite(eightChanRelayIN1, LOW);

        
        // Did the off button get pressed
        if (buffer.indexOf("GET /?status1=OFF") >= 0)
          digitalWrite(eightChanRelayIN1, HIGH); 
           
//        if (buffer.indexOf("GET /?status2=2ON") >= 0)
//          digitalWrite(eightChanRelayIN2, LOW);

//        
//        // Did the off button get pressed
//        if (buffer.indexOf("GET /?status3=2OFF") >= 0)
//          digitalWrite(eightChanRelayIN2, HIGH); 
//
//        if (buffer.indexOf("GET /?status3=3ON") >= 0)
//          digitalWrite(eightChanRelayIN3, LOW);
//
//        
//        // Did the off button get pressed
//        if (buffer.indexOf("GET /?status2=3OFF") >= 0)
//          digitalWrite(eightChanRelayIN3, HIGH); 
        }
        else {
        currentLineIsBlank = false;
        }
      }
    }
  client.stop(); // End server
  }
}
