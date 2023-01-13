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

byte button = 2;

void setup() {
  pinMode(button, INPUT);

  Serial.begin(9600);
  while (!Serial);

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
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
            client.println("Refresh: 1");
            client.println();

            client.println("<html>");
            client.println("<head>");
            client.println("    <title>Home Automation</title>");
            client.println("    <style>");
            client.println("        h1 {");
            client.println("            text-align: center;");
            client.println("            font-size: 1in");
            client.println("        }");
            client.println();
            client.println("        em {");
            // client.println("            font-style: normal;");
            client.println("            color: blue;");
            client.println("            text-decoration: underline;");
            client.println("        }");
            client.println("    </style>");
            client.println("</head>");

            client.println("<body>");

            if (digitalRead(button)) {
              client.println("<h1>I'm feeling <em>down</em></h1>");
            } else {
              client.println("<h1>I'm <em>up</em> to no good</h1>");
            }

            client.println("</body>");
            client.println("</html>");

            delay(1);
            client.stop();

            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disconnected");
          }
        }
      }
    }
  }
}