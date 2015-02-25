/* Keyboard example with debug channel, for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 #include <string.h>
#include "usb_keyboard_debug.h"
#include "print.h"
#include "config.h"

typedef enum { false, true } bool;

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

#define DELAY_TIME 5

// uint8_t number_keys[10]=
// 	{KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9};

// uint8_t rows[11] = {
// 	PIN0, PIN1, PIN2, PIN3, PIN7, PIN0, PIN1, PIN2, PIN0, PIN1, PIN4
// };

// uint8_t row_ports[11] = {
// 	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0d, 0x0d, 0x0d, 0x0f, 0x0f, 0x0f
// };


/*
	COLUMNS = 8
	ROWS = 11
	NKEYS = COLUMNS * ROWS */
#define NKEYS 88

#define COLUMNS 8

uint8_t cols[COLUMNS] = {
	PIN5, PIN6, PIN7, PIN6, PIN5, PIN4, PIN7, PIN6
};

uint8_t col_ports[COLUMNS] = {
	0x0f, 0x0f, 0x0f, 0x0b, 0x0b, 0x0b, 0x0d, 0x0d
};

#define ROWS 11

uint8_t rows[ROWS] = {
	PIN0, PIN1, PIN2, PIN3, PIN7, PIN0, PIN1, PIN2, PIN0, PIN1, PIN4
};

uint8_t row_ports[ROWS] = {
	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0d, 0x0d, 0x0d, 0x0f, 0x0f, 0x0f
};

/* pressed  keeps track of which keys that are pressed
   queue    contains the keys that are sent in the HID packet
   mod_keys is the bit pattern corresponding to pressed modifier keys
   mode is the current macro mode */
bool pressed[NKEYS];
uint8_t queue[7] = {255,255,255,255,255,255,255};
uint8_t mod_keys = 0;


/* prototypes */
inline void key_press(uint8_t key_id);
inline void key_release(uint8_t key_id);
inline void send(void);
void read_rows(int c);
void init(void);

void read_rows(int c) {
	for(int r = 0; r < ROWS; r++) {
		// phex(r);

		uint8_t row_port = row_ports[r];
		uint8_t row = rows[r];

		uint8_t volatile *r_port = NULL;;
		// uint8_t volatile r_port;
		// uint8_t volatile *r_port_ptr = &r_port;

		switch(row_port) {
			case 0x0b:
				r_port = &PINB;
				// print("PINB = ");
				break;
			case 0x0d:
				r_port = &PIND;
				// print("PIND = ");
				break;
			case 0x0f:
				r_port = &PINF;
				// print("PINF = ");
				break;
		}

		uint8_t key_id = r + c * ROWS;

		if (*r_port & (1 << row)) {
			phex(r);
			print(" on ");
			phex(r + c * ROWS);
			print(" ");
			phex(c);
			print("\n");

			// uint8_t key_id = r + c * ROWS;

		    int map = switch_map[key_id];

			if (map == NO_KEY)
				continue;

			if(!pressed[key_id]) {
				key_press(key_id);
			}

			// phex(key_id);
			// print(" ");
			// phex(switch_map[r + c * ROWS]);
			// print(" [");
			// 	phex(key_map[switch_map[key_id]]);
			// // phex(switch_pos_map[switch_map[r + c * ROWS]]);
			// print("] ");

			// print(" (");
			// phex(keys[switch_pos_map[switch_map[r + c * ROWS]]]);
			// print(")");
			// print("\n");
		} else if (pressed[key_id]) {
		    int map = switch_map[key_id];

			if (map == NO_KEY)
				continue;

			key_release(key_id);
		}
	}
}

inline void key_press(uint8_t key_id) {
  uint8_t i;
  pressed[key_id] = true;

  int map = switch_map[key_id];
  int key = key_map[map];

  switch(key) {
  	case KEY_LEFTCONTROL:
  	print("l ctrl\n");
	  	mod_keys |= KEY_LEFT_CTRL; break;
  	case KEY_LEFTSHIFT:
  	print("l shift\n");
  		mod_keys |= KEY_LEFT_SHIFT; break;
	case KEY_LEFTALT:
	print("l alt\n");
		mod_keys |= KEY_LEFT_ALT; break;
	case KEY_LEFTGUI:
	print("l gui\n");
		mod_keys |= KEY_LEFT_GUI; break;
	case KEY_RIGHTCONTROL:
	print("r ctrl\n");
		mod_keys |= KEY_RIGHT_CTRL; break;
	case KEY_RIGHTSHIFT:
	print("r shift\n");
		mod_keys |= KEY_RIGHT_SHIFT; break;
	case KEY_RIGHTALT:
	print("r alt\n");
		mod_keys |= KEY_RIGHT_ALT; break;
	case KEY_RIGHTGUI:
	print("r gui\n");
		mod_keys |= KEY_RIGHT_GUI; break;
	default:

		print("normal key: ");
		phex(key);
		print("\n");

		for(i=5; i>0; i--) queue[i] = queue[i-1];
		queue[0] = key;
  }

  send();
}

inline void key_release(uint8_t key_id) {
  uint8_t i;
  pressed[key_id] = false;

  int map = switch_map[key_id];
  int key = key_map[map];

  switch(key) {
  	case KEY_LEFTCONTROL:
	  	mod_keys &= ~KEY_LEFT_CTRL; break;
  	case KEY_LEFTSHIFT:
  		mod_keys &= ~KEY_LEFT_SHIFT; break;
	case KEY_LEFTALT:
		mod_keys &= ~KEY_LEFT_ALT; break;
	case KEY_LEFTGUI:
		mod_keys &= ~KEY_LEFT_GUI; break;
	case KEY_RIGHTCONTROL:
		mod_keys &= ~KEY_RIGHT_CTRL; break;
	case KEY_RIGHTSHIFT:
		mod_keys &= ~KEY_RIGHT_SHIFT; break;
	case KEY_RIGHTALT:
		mod_keys &= ~KEY_RIGHT_ALT; break;
	case KEY_RIGHTGUI:
		mod_keys &= ~KEY_RIGHT_GUI; break;
	default:

		print("release key: ");
		phex(key);
		print("\n");

	    for(i=0; i<6; i++) if(queue[i]==key) break;
	    for(; i<6; i++) queue[i] = queue[i+1];
  }

  send();
}

inline void send(void) {
  // return;
  uint8_t i;
  for(i=0; i<6; i++)
    keyboard_keys[i] = queue[i]<255? queue[i]: 0;
  keyboard_modifier_keys = mod_keys;
  usb_keyboard_send();
}


// void convert_key_to_ansi_char(int key) {
// 	switch(key) {
//   	case KEY_LEFTCONTROL:
//   		char *k = "KEY_LEFT_CTRL";
//   		for(int i = 0; i < strlen(k); i++;) {
//   			keyboard_keys[0] = k[i];
// 		  	usb_keyboard_send();
//   		}
// 	  	break;
//   	case KEY_LEFTSHIFT:
// 	  	// usb_keyboard_send();
// 	  	break;
// 	case KEY_LEFTALT:
// 		// usb_keyboard_send();
// 	  	break;
// 	case KEY_LEFTGUI:
// 		// usb_keyboard_send();
// 	  	break;
// 	case KEY_RIGHTCONTROL:
// 		// usb_keyboard_send();
// 	  	break;
// 	case KEY_RIGHTSHIFT:
// 		// usb_keyboard_send();
// 	  	break;
// 	case KEY_RIGHTALT:
// 		// usb_keyboard_send();
// 	  	break;
// 	case KEY_RIGHTGUI:
// 		// usb_keyboard_send();
// 	  	break;
//   }
// }

int main(void)
{


	// set for 16 MHz clock
	CPU_PRESCALE(0);

	// Configure all port B and port D pins as inputs with pullup resistors.
	// See the "Using I/O Pins" page for details.
	// http://www.pjrc.com/teensy/pins.html
	// DDRD = 0x00;
	// DDRB = 0x00;
	// PORTB = 0xFF;
	// PORTD = 0xFF;

	// set diode directions
	// since we set explicit outputs, then all other pins are inputs
	DDRF = 0xF0; // f4-f7 output
	DDRB = 0x70; // d4-d6;
	DDRD = 0xC0; // d7, d6
	// DDRF = 0x00;
	// DDRF |= (1 << PIN5);
	// DDRB = 0x00;

	// set all ports to low
	PORTF = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;

	// use pull up resistors for inputs
	// PORTB |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN7);  
	// PORTD |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2);
	// PORTF |= (1 << PIN0) | (1 << PIN1) | (1 << PIN4);

	// PORTB |= (1 << PIN1);

	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;

	// Wait an extra second for the PC's operating system to load drivers
	// and do whatever it does to actually be ready for input
	_delay_ms(1000);

	// Configure timer 0 to generate a timer overflow interrupt every
	// 256*1024 clock cycles, or approx 61 Hz when using 16 MHz clock
	// This demonstrates how to use interrupts to implement a simple
	// inactivity timeout.
	// TCCR0A = 0x00;
	// TCCR0B = 0x05;
	// TIMSK0 = (1<<TOIE0); 

	print("Begin keyboard example program\n"); 
	print("All Port B or Port D pins are inputs with pullup resistors.\n");
	print("Any connection to ground on Port B or D pins will result in\n");
	print("keystrokes sent to the PC (and debug messages here).\n");

	while(1) {
		_delay_ms(DELAY_TIME);

		// int c = 1;
		for(int c = 0; c < COLUMNS; c++)
		{
			uint8_t col_port = col_ports[c];
			uint8_t column = cols[c];

			uint8_t volatile *c_port = NULL;

			switch(col_port) {
				case 0x0b:
					c_port = &PORTB; 
					break;
				case 0x0d:
					c_port = &PORTD;
					break;
				case 0x0f:
					c_port = &PORTF;
					break;
			}

			// col_port[c] |= cols[c]

			// phex(c);
			// print("\n");

			// phex (column);
		// 	// print("\n");

			*c_port |= (1 << column);

			_delay_us(1);

			// _delay_ms(2);

			read_rows(c);

			*c_port &= ~(1 << column);
		}
	}

	// while (1) {
	// 	// read all port B and port D pins
	// 	b = PINB;
	// 	d = PIND;
	// 	// check if any pins are low, but were high previously
	// 	mask = 1;
	// 	reset_idle = 0;
	// 	for (i=0; i<8; i++) {
	// 		if (((b & mask) == 0) && (b_prev & mask) != 0) {
	// 			usb_keyboard_press(KEY_B, KEY_SHIFT);
	// 			usb_keyboard_press(number_keys[i], 0);
	// 			print("Port B, bit ");
	// 			phex(i);
	// 			print("\n");
	// 			reset_idle = 1;
	// 		}
	// 		if (((d & mask) == 0) && (d_prev & mask) != 0) {
	// 			usb_keyboard_press(KEY_D, KEY_SHIFT);
	// 			usb_keyboard_press(number_keys[i], 0);
	// 			print("Port D, bit ");
	// 			phex(i);
	// 			print("\n");
	// 			reset_idle = 1;
	// 		}
	// 		mask = mask << 1;
	// 	}
	// 	// if any keypresses were detected, reset the idle counter
	// 	if (reset_idle) {
	// 		// variables shared with interrupt routines must be
	// 		// accessed carefully so the interrupt routine doesn't
	// 		// try to use the variable in the middle of our access
	// 		cli();
	// 		idle_count = 0;
	// 		sei();
	// 	}
	// 	// now the current pins will be the previous, and
	// 	// wait a short delay so we're not highly sensitive
	// 	// to mechanical "bounce".
	// 	b_prev = b;
	// 	d_prev = d;
	// 	_delay_ms(2);
	// }
}

// This interrupt routine is run approx 61 times per second.
// A very simple inactivity timeout is implemented, where we
// will send a space character and print a message to the
// hid_listen debug message window.
// ISR(TIMER0_OVF_vect)
// {
// 	idle_count++;
// 	if (idle_count > 61 * 8) {
// 		idle_count = 0;
// 		print("Timer Event :)\n");
// 		// usb_keyboard_press(KEY_SPACE, 0); 
// 	}
// }

void init() {
	// init pressed array
	for(int i=0; i<NKEYS; i++) pressed[i] = false;
}

