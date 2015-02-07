/*
 * ColorCycle Class - Cycle through RGB colors for SmartMatrix
 *
 * Copyright (c) 2014 Art Dahm (art@dahm.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ColorCycle.h"

// Constructor
ColorCycle::ColorCycle () {

	// Initialize color
	for(int i = 0; i < RGB_COUNT; i++) {
		color[i] = newColor[i] = 255;
	}

}

// Get the next color step in the cycle
rgb24 ColorCycle::nextColor() {

	uint8_t done = 0;

	for(int i=0; i < RGB_COUNT; i++) {
		// If this PWM has reached its new color increment done
		if (color[i] == newColor[i]) {
			done++;
		// Move PWM towards its new color
		} else if (color[i] < newColor[i]) {
			color[i] += 1;
		} else if (color[i] > newColor[i]) {
			color[i] -= 1;
		}
	}

	// If all the PWMs have reached their new colors
	if (done == RGB_COUNT) {
		// Pick a random RGB color (other than black)
		uint8_t randomColor = (rand() % 6) + 1;
		// Set red, green, and blue components to maximum brightness
		for(int i=0; i < RGB_COUNT; i++) {
			newColor[i] = ((randomColor >> i) & 0x01) * 255;
		}
	}

	return {color[0], color[1], color[2]};
}
