#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernet.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "ca13a9c0-9808-11ed-b193-d9789b2af62b";
char password[] = "b73e5ae6edcdb8741b88a1488fa5e508e393a9ab";
char clientID[] = "92da7730-98ef-11ed-8d53-d7cd1025126a";

// Temperature
// Pin for sensor
#define TEMP A0
// Channel for sending data to Cayenne
#define TEMP_CHANNEL 6

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID);
}

void loop() {
	Cayenne.loop();
  // CAYENNE_OUT wasn't working, even for this one-liner
  Cayenne.celsiusWrite(TEMP_CHANNEL, analogRead(TEMP));
}

CAYENNE_OUT(0) {
	CAYENNE_LOG("Send data for Virtual Channel 0");
	// This command writes the device's uptime in seconds to the Virtual Channel. 
	Cayenne.virtualWrite(0, millis() / 1000);
}