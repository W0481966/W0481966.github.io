/*
 * Web Server
 * A simple web server
 * Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 1, 177);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(80);
String readString;

// Declare Pin 8 as an LED because thats what we will be connecting the LED to.You could use any other pin and would then have to change the pin number.
int led = 8;

void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("LED Controller Test 1.0");
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 100) {
          readString += c;
          Serial.write(c);

          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();

            client.println("<html>");
            client.println("<head>");
            client.println("    <title>Home Automation</title>");
            client.println("</head>");

            client.println("<body>");
            client.println("<h1>Home Automation</h1>");
            client.println("<hr>");

            client.println("<a href=\"/?lighton\"\">Turn On Light</a>");
            client.println("<a href=\"/?lightoff\"\">Turn Off Light</a>");

            client.println("</body>");
            client.println("</html>");

            delay(1);
            client.stop();

            if (readString.indexOf("?lighton") > 0) {
              digitalWrite(8, HIGH);
              Serial.println("Led On");
            } else if (readString.indexOf("?lightoff") >0) {
              digitalWrite(8, LOW);
              Serial.println("Led Off");
            }
            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disonnected");
          }
        }
      }
    }
  }
}