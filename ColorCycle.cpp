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
ColorCycle::ColorCycle (uint8_t step) {

	step_ = step;

	// Initialize color and delta
	for(int i = 0; i < 3; i++) {
		color_[i] = 255;
		delta_[i] = 0;
	}

}

// Get the next color step in the cycle
rgb24 ColorCycle::nextColor() {

	uint8_t done = 0;

	// Change the RGB colors that haven't reached max or min brightness
	for(int i = 0; i < 3; i++) {
		if (delta_[i] == 0) {
			done++;
		} else {
			color_[i] += delta_[i];
			// Stop changing if <= 0
			if (color_[i] <= 0) {
				color_[i] = 0;
				delta_[i] = 0;
			// Stop changing if >= 255
			} else if (color_[i] >= 255) {
				color_[i] = 255;
				delta_[i] = 0;
			}
		}
	}

	// If all the colors have reached their new colors and are no longer changing
	if (done == 3) {
		// Pick a random RGB color (other than black)
		uint8_t random_color = (rand() % 6) + 1;
		for(int i=0; i < 3; i++) {
			if (((random_color >> i) & 0x01) * 255 >= color_[i]) {
				delta_[i] = step_;
			} else {
				delta_[i] = -step_;
			}
		}
	}

	return {(uint8_t)color_[0], (uint8_t)color_[1], (uint8_t)color_[2]};
}
