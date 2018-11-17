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

	Serial.begin(9600);
	Serial.println("Initalized");

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

void Four7Seg::_writeAllDigits() {
	_writeDigit(_digitPins[0], _values[0]);
	_writeDigit(_digitPins[1], _values[1]);
	_writeDigit(_digitPins[2], _values[2]);
	_writeDigit(_digitPins[3], _values[3]);
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

void Four7Seg::write(int value) {
	_setValues(value);
	_writeAllDigits();
}

// int Four7Seg::_getDigitInFloat(int digit, float value, int significantDigits) {
// 	pow(10, 4 - significantDigits - 1)
// }

void Four7Seg::_setValues(float value, int significantDigits) {
	// Serial.println("set values");
	if (value >= pow(10, 4 - significantDigits)) { // too many digits? too few?
		memcpy(_values, _error, sizeof(_values)); // set values to error
		return; //bail
	}
	// round away any extra sig digits	
	float roundedValue = round(value * pow(10, significantDigits)) / pow(10, significantDigits);
	String stringValue;
	stringValue = String(roundedValue);


	int decimalIndex = stringValue.indexOf(".");
	int valueLength = stringValue.length() + (decimalIndex != -1 ? -1 : 0); // strip the decimal out of the length ... for some reason
	// Serial.println(valueLength);
	int i = 3; // which digit we're on
	while (i > (valueLength - 1)) { // is it blank?
		_values[i] = _blank;
		i--;
	}
	// Serial.println(i);

	// Serial.println(stringValue);
	int stringPosition = stringValue.length();
	while (i > -1) {
		if (stringValue.charAt(stringPosition) != '.') {
			int digitValue = stringValue.charAt(stringPosition) - '0';
			_values[i] = _numbers[digitValue];
			i--;
		} else {
			_values[i + 1] += 1; // add the decimal to the previous digit
		}
		stringPosition--;
	}

}

void Four7Seg::_setValues(float value) {
	// Serial.println("write digits");
	_setValues(value, 2);
	_writeAllDigits();
}

void Four7Seg::write(float value) {
	// Serial.println("write");
	_setValues(value);
	_writeAllDigits();
}






