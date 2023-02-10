#!/bin/bash

### This displays single-digit prime numbers on a 7-segment display.
### We number the segments from 1 to 7, starting from the top and
### going clockwise around the outside. The middle segment is #7.

set -e

SEGMENT_PINS="1 2 3 4 5 6 25"
DIR=/sys/class/gpio
PREFIX=$DIR/gpio

# Takes two params.
#   1. A segment number, from 1 to 7
#   2. A value. 0 for off, 1 for on
setSegment() {
	pin=$(echo $SEGMENT_PINS | cut -d ' ' -f $1)
	echo $2 > $PREFIX$pin/value
}

# Takes 7 params, which represent the values of the 7 segments.
# 0 for off, 1 for on
setSegments() {
	setSegment 1 $1
	setSegment 2 $2
	setSegment 3 $3
	setSegment 4 $4
	setSegment 5 $5
	setSegment 6 $6
	setSegment 7 $7
}

show0() {
	setSegments 1 1 1 1 1 1 0
}

show1() {
	setSegments 0 1 1 0 0 0 0
}

show2() {
	setSegments 1 1 0 1 1 0 1
}

show3() {
	setSegments 1 1 1 1 0 0 1
}

show4() {
	setSegments 0 1 1 0 0 1 1
}

show5() {
	setSegments 1 0 1 1 0 1 1
}

show6() {
	setSegments 1 0 1 1 1 1 1
}

show7() {
	setSegments 1 1 1 0 0 0 0
}

show8() {
	setSegments 1 1 1 1 1 1 1
}

show9() {
	setSegments 1 1 1 1 0 1 1
}

blank() {
	setSegments 0 0 0 0 0 0 0
}

# Initialize
for pin in $SEGMENT_PINS; do
	if [ ! -e $PREFIX$pin ]; then
		echo $pin > $DIR/export
		sleep 1
	fi

	echo out > $PREFIX$pin/direction
	echo 0 > $PREFIX$pin/value
done

trap blank EXIT

while /bin/true; do
	for num in 2 3 5 7; do
		show$num
		sleep 1
	done
	blank
	sleep 1
done
