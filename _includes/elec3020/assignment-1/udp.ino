#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
unsigned int localPort = 8888;
EthernetUDP Udp;
char packetBuffer[24];

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  pinMode(2, OUTPUT);

  Serial.println("UDP is ready");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("from ");
    IPAddress remote = Udp.remoteIP();

    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) Serial.print(".");
    }
    Serial.print(":");
    Serial.println(Udp.remotePort());

    Udp.read(packetBuffer, packetSize);
    packetBuffer[packetSize] = '\0';
    Serial.print("Contents: ");
    Serial.println(packetBuffer);

    if (!strcmp(packetBuffer, "secret")) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
  }
}