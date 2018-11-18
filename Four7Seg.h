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
		void write(float value);
		void write(String value);

	private:
		// common anode v cathode hadnling
		uint8_t _digitOffState = LOW;
		uint8_t _digitOnState = HIGH;
		int _postWriteDelay = 1; // we need a tiny delay to ensure each value actually display

		int _dataPin, _clockPin, _latchPin;
		int _digitPins[4];

		// values read left to right, exactly as they'll display
		// "hi" = ["", "", h", "i"]
		// 916 = [0, 9, 1, 6]
		int _values[4];

		int _numbers[10] = { 252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };
		int _blank = 0; 
		int _error[4] = { 10, 10, 158, _blank };

		// caching
		int _STRING = 1;
		int _FLOAT = 2;
		int _INT = 3;
		int _LAST_TYPE;
		String _LAST_STRING;
		float _LAST_FLOAT;
		int _LAST_INT;

		void _resetAllDigits();

		void _writeDigit(int digitPin, int value);
		void _writeDigit(int pin);
		void _writeAllDigits();

		// int _getDigitInFloat(int digit, float value, int significantDigits);
		void _setValuesFromString(String value);

		void _setValues(int value);
		void _setValues(float value);
		void _setValues(float value, int significantDigits);
		void _setValues(String value);

		uint8_t _characters[128] = {
			0b11111100, // 0   "0"          AAA
			0b01100000, // 1   "1"         F   B
			0b11011010, // 2   "2"         F   B
			0b11110010, // 3   "3"          GGG
			0b01100110, // 4   "4"         E   C
			0b10110110, // 5   "5"         E   C
			0b10111110, // 6   "6"          DDD
			0b11100000, // 7   "7"
			0b11111110, // 8   "8"
			0b11110110, // 9   "9"
			0b11101110, // 10  "A"
			0b00111110, // 11  "b"
			0b10011100, // 12  "C"
			0b01111010, // 13  "d"
			0b10011110, // 14  "E"
			0b10001110, // 15  "F"
			0b00000000, // 16  NO DISPLAY
			0b00000000, // 17  NO DISPLAY
			0b00000000, // 18  NO DISPLAY
			0b00000000, // 19  NO DISPLAY
			0b00000000, // 20  NO DISPLAY
			0b00000000, // 21  NO DISPLAY
			0b00000000, // 22  NO DISPLAY
			0b00000000, // 23  NO DISPLAY
			0b00000000, // 24  NO DISPLAY
			0b00000000, // 25  NO DISPLAY
			0b00000000, // 26  NO DISPLAY
			0b00000000, // 27  NO DISPLAY
			0b00000000, // 28  NO DISPLAY
			0b00000000, // 29  NO DISPLAY
			0b00000000, // 30  NO DISPLAY
			0b00000000, // 31  NO DISPLAY
			0b00000000, // 32  ' '
			0b00000000, // 33  '!'  NO DISPLAY
			0b01000100, // 34  '"'
			0b00000000, // 35  '#'  NO DISPLAY
			0b00000000, // 36  '$'  NO DISPLAY
			0b00000000, // 37  '%'  NO DISPLAY
			0b00000000, // 38  '&'  NO DISPLAY
			0b01000000, // 39  '''
			0b10011100, // 40  '('
			0b11110000, // 41  ')'
			0b00000000, // 42  '*'  NO DISPLAY
			0b00000000, // 43  '+'  NO DISPLAY
			0b00001000, // 44  ','
			0b00000010, // 45  '-'
			0b00000000, // 46  '.'  NO DISPLAY
			0b00000000, // 47  '/'  NO DISPLAY
			0b11111100, // 48  '0'
			0b01100000, // 49  '1'
			0b11011010, // 50  '2'
			0b11110010, // 51  '3'
			0b01100110, // 52  '4'
			0b10110110, // 53  '5'
			0b10111110, // 54  '6'
			0b11100000, // 55  '7'
			0b11111110, // 56  '8'
			0b11110110, // 57  '9'
			0b00000000, // 58  ':'  NO DISPLAY
			0b00000000, // 59  ';'  NO DISPLAY
			0b00000000, // 60  '<'  NO DISPLAY
			0b00000000, // 61  '='  NO DISPLAY
			0b00000000, // 62  '>'  NO DISPLAY
			0b00000000, // 63  '?'  NO DISPLAY
			0b00000000, // 64  '@'  NO DISPLAY
			0b11101110, // 65  'A'
			0b00111110, // 66  'b'
			0b10011100, // 67  'C'
			0b01111010, // 68  'd'
			0b10011110, // 69  'E'
			0b10001110, // 70  'F'
			0b10111100, // 71  'G'
			0b01101110, // 72  'H'
			0b01100000, // 73  'I'
			0b01110000, // 74  'J'
			0b00000000, // 75  'K'  NO DISPLAY
			0b00011100, // 76  'L'
			0b00000000, // 77  'M'  NO DISPLAY
			0b00101010, // 78  'n'
			0b11111100, // 79  'O'
			0b11001110, // 80  'P'
			0b11100110, // 81  'q'
			0b00001010, // 82  'r'
			0b10110110, // 83  'S'
			0b00011110, // 84  't'
			0b01111100, // 85  'U'
			0b00000000, // 86  'V'  NO DISPLAY
			0b00000000, // 87  'W'  NO DISPLAY
			0b00000000, // 88  'X'  NO DISPLAY
			0b01110110, // 89  'y'
			0b00000000, // 90  'Z'  NO DISPLAY
			0b10011100, // 91  '['
			0b00000000, // 92  '\'  NO DISPLAY
			0b11110000, // 93  ']'
			0b00000000, // 94  '^'  NO DISPLAY
			0b00010000, // 95  '_'
			0b00000100, // 96  '`'
			0b11101110, // 97  'a' SAME AS CAP
			0b00111110, // 98  'b' SAME AS CAP
			0b00011010, // 99  'c'
			0b01111010, // 100 'd' SAME AS CAP
			0b11011110, // 101 'e'
			0b10001110, // 102 'F' SAME AS CAP
			0b10111100, // 103 'G' SAME AS CAP
			0b00101110, // 104 'h'
			0b00100000, // 105 'i'
			0b01110000, // 106 'j' SAME AS CAP
			0b00000000, // 107 'k'  NO DISPLAY
			0b01100000, // 108 'l'
			0b00000000, // 109 'm'  NO DISPLAY
			0b00101010, // 110 'n' SAME AS CAP
			0b00111010, // 111 'o'
			0b11001110, // 112 'p' SAME AS CAP
			0b11100110, // 113 'q' SAME AS CAP
			0b00001010, // 114 'r' SAME AS CAP
			0b10110110, // 115 'S' SAME AS CAP
			0b00011110, // 116 't' SAME AS CAP
			0b00111000, // 117 'u'
			0b00000000, // 118 'b'  NO DISPLAY
			0b00000000, // 119 'w'  NO DISPLAY
			0b00000000, // 120 'x'  NO DISPLAY
			0b00000000, // 121 'y'  NO DISPLAY
			0b00000000, // 122 'z'  NO DISPLAY
			0b00000000, // 123 '0b'  NO DISPLAY
			0b00000000, // 124 '|'  NO DISPLAY
			0b00000000, // 125 ','  NO DISPLAY
			0b00000000, // 126 '~'  NO DISPLAY
			0b00000000 // 127 'DEL'  NO DISPLAY
		};
};

#endif