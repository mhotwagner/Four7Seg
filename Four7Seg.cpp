#include <Arduino.h>
#include <Four7Seg.h>

Four7Seg::Four7Seg(
	int dataPin,
	int latchPin,
	int clockPin,
	int digitPins[])
{
	_dataPin = dataPin;
	_latchPin = latchPin;
	_clockPin = clockPin;
	_digitPins[0] = digitPins[0];
	_digitPins[1] = digitPins[1];
	_digitPins[2] = digitPins[2];
	_digitPins[3] = digitPins[3];
	// memcpy(_digitPins, digitPins, sizeof(_digitPins));

	pinMode(_dataPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	for (int i = 0; i < 4; i++) pinMode(_digitPins[i], OUTPUT);

}


void Four7Seg::_resetAllDigits() {
	for (int i = 0; i < 4; i++) digitalWrite(_digitPins[i], _digitOffState);
}


void Four7Seg::_writeDigit(int digitPin, int value) {

	_resetAllDigits();
	digitalWrite(digitPin, _digitOnState);
	digitalWrite(_latchPin, LOW);
	shiftOut(_dataPin, _clockPin, LSBFIRST, value);
	digitalWrite(_latchPin, HIGH);
	delay(_postWriteDelay);
}

void Four7Seg::_writeDigit(int pin) {

	_resetAllDigits();
	digitalWrite(_digitPins[pin], _digitOnState);
	digitalWrite(_latchPin, LOW);
	shiftOut(_dataPin, _clockPin, LSBFIRST, _values[pin]);
	digitalWrite(_latchPin, HIGH);
	delay(_postWriteDelay);
}


void Four7Seg::_setValues(int value) {
	if (value / 1000 > 9) { // do we have too many digits?
		memcpy(_values, _error, sizeof(_values)); // set values to error
		return; //bail
	}
	_values[3] = _numbers[value / 1000]; // most significant digit first
	_values[2] = _numbers[(value % 1000) / 100];
	_values[1] = _numbers[(value % 100) / 10];
	_values[0] = _numbers[(value % 10)];

	// lop off leading zeroes
	int i = 3;
	while (_values[i] == _numbers[0] && i > 0) {
		_values[i] = _blank;
		i--;
	}
}


void Four7Seg::swapDigitState() {
	if (_digitOffState == LOW) {
		_digitOffState = HIGH;
		_digitOnState = LOW;
	} else {
		_digitOffState = LOW;
		_digitOnState = HIGH;
	}
}

void Four7Seg::write(int value) {
	_setValues(value);
	_writeDigit(_digitPins[0], _values[0]);
	_writeDigit(_digitPins[1], _values[1]);
	_writeDigit(_digitPins[2], _values[2]);
	_writeDigit(_digitPins[3], _values[3]);
}