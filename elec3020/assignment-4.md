## Raspberry Pi VM

![VM screenshot](/assets/elec3020/assignment-4/vm.png)

## Dialog

![Dialog screenshot](/assets/elec3020/assignment-4/dialog.png)

```python
{% include elec3020/assignment-4/dialog.py %}
```

## Controlling GPIO through a shell script

[Watch video](/assets/elec3020/assignment-4/7segment.mp4)

My project is simple: I display all single-digit prime numbers in sequence on a 7-segment display.

Note that [the traffic light tutorial](https://simonprickett.dev/controlling-raspberry-pi-gpio-pins-from-bash-scripts-traffic-lights/) is incorrect - you don't need root to manipulate /sys/class/gpio, it's sufficient to be in the `gpio` group. The pi user already was, and I don't think that was my doing.

### Circuit diagram

I used an Arduino instead of a Pi because my circuit diagramming app doesn't provide a Pi. Pin 13 in the diagram ended up being pin 25 on the Pi.

![Circuit diagram](/assets/elec3020/assignment-4/circuit.png)

```bash
{% include elec3020/assignment-4/7segment.sh %}
```
