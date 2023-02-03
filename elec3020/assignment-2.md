## Leveraging Cloud Computing for IoT

[View PDF](/assets/elec3020/assignment-2/cert.pdf)

## Cloud project

### Video

[Watch video](/assets/elec3020/assignment-2/demo.mp4)

### Synopsis

The idea behind this project was to put a thermometer in one location and a display in another location
to show the temperature. The end result might be something
[like this](https://media.gettyimages.com/photos/street-thermometer-displays-a-39-degree-celsius-temperature-before-picture-id95723578).

The devices would communicate through the cloud, which would allow them to be completely decoupled - you could display
any thermometer without updating the display, and you could have a thermometer feed any number of displays without
updating the thermometer. Since Cayenne is incapable of copy values from one device to another, and NasserCorp is too
cheap to spring for a real cloud solution, we're going to pay a monkey peanuts to sit at the Cayenne dashboard and
update the display when the temperature changes.

### Diagram

Here's a diagram of my circuits. The small device on the left represents the ESP32, since there was no more appropriate
image available. Changing the temperature on cue is not easy, so for demonstration purposes, the
thermometer has been replaced by a photoresistor.

![Circuit Diagram](/assets/elec3020/assignment-2/circuit.png)


### Source code

#### Arduino Uno with thermometer.
```cpp
{% include elec3020/assignment-2/arduino.ino %}
```

#### ESP32 with I2C 1602 LCD display
```cpp
{% include elec3020/assignment-2/esp32.ino %}
```
