/*
	For7Seg.h - An 4-digit 7-segment LED library for Arduino
	For controlling a 4-digit 7-segment LED with a single
	74HC595 shift register
	Created by Michael Hotwagner, 2018
*/
#ifndef Four7Seg_h
#define Four7Seg_h

#include <Arduino.h>

class Four7Seg
{
	public:
		Four7Seg(int dataPin, int clockPin, int latchPin, int digitPins[]);

		void swapDigitState();

		void write(int value);

	private:
		uint8_t _digitOffState = LOW;
		uint8_t _digitOnState = HIGH;
		int _postWriteDelay = 1;

		int _dataPin, _clockPin, _latchPin;
		int _digitPins[4];

		int _values[4];

		int _numbers[10] = { 252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };
		int _blank = 0;
		int _error[4] = { 10, 10, 158, _blank };

		void _resetAllDigits();

		void _writeDigit(int digitPin, int value);
		void _writeDigit(int pin);

		void _setValues(int value);
};

#endif