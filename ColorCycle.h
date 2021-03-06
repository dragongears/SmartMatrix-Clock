/*
 * Header File for ColorCycle Class - Cycle through RGB colors for SmartMatrix
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

#ifndef ColorCycle_h
#define ColorCycle_h

#include "Arduino.h"
#include <stdint.h>
#include <SmartMatrix_32x32.h>

class ColorCycle {
    public:
        // Constructor. The argument passed to the step parameter is the
        // granularity of the color change when nextColor is called.
        ColorCycle (uint8_t step = 1);
        // Steps to the next color in the color cycle and returns it
        rgb24 nextColor();
	private:
		int16_t color_[3];
		int16_t delta_[3];
		uint8_t step_;
};

#endif  /* _ColorCycle_h */