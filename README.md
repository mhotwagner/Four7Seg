## Four7Seg
An Arduino library for controlling a SH5461as 4-digit 7-segment led module with a single 74HC595 shift register


## Quickstart

```cpp
#include <Four7Seg.h>

// Controls for the led module
int digitPins[] = { D4, D3, D2, D1 };  // It's in order by digit, from left to right

// Pins for controlling the shift register
int dataPin = 5;
int latchPin = 6;
int clockPin = 7;

Four7Seg disp(dataPin, latchPin, clockPin, digitPins);

void setup() {
  /* So, you control which digit(s) in the led are active
  by turning on or off the "digit pins".  By the spec, off
  should be digitalWrite(somePin, LOW), and on should be
  HIGH.  On my module, this is backwards.  I have no idea
  if the modules come in two different flavors, or if I
  just have a faulty one, but this was my solution. */
  disp.swapDigitState();
}

void loop() {
  // This will write until n is greater than 4 digits
  // (9999+1), and then it will write print an error message.
  disp.write(n);
  n += 1;
}
```
