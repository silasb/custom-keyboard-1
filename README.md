Custom Keyboard 1
=================

This is my repo for my reversed engineered keyboard.

# Building

	make clean && make
	./teensy -mmcu=atmega32u4 -w -v keyboard.hex
	# Hit reset on Teensy to flash firmware

# Debugging

I've leave `usb_keyboard_debug` so I can debug easily with [HID Listen](http://www.pjrc.com/teensy/hid_listen.html).

	./hid_listen/hid_listen

# TODO

- [ ] Clean up code and remove junk
- [ ] Bring dependencies into repository
