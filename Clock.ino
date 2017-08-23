/*
 * SmartMatrix Clock
 * Version 0.6.0
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

#include <Time.h>
#include <SmartMatrix_32x32.h>
#include "ColorCycle.h"

SmartMatrix matrix;
ColorCycle timeColor(2);
ColorCycle dateColor(2);

int brightness = 60;
const rgb24 backgroundColor = {0, 0, 0};

char const *months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

void setup()  {
    // set the Time library to use Teensy 3.1's RTC to keep time
    setSyncProvider(getTeensy3Time);

    matrix.begin();
    matrix.setBrightness(brightness*(255/100));
}

void loop() {
    digitalClockDisplay();
    delay(100);
}

void copyMonth(char const *source, char *target)
{
   while(*source)
   {
      *target = *source;
      source++;
      target++;
   }
}

void digitalClockDisplay() {

	rgb24 currentTimeColor = timeColor.nextColor();
	rgb24 currentDateColor = dateColor.nextColor();

    matrix.fillScreen(backgroundColor);

    matrix.setFont(gohufont11b);

    int t = 0;
    char time[] = "00:00";

    t = hourFormat12();
    time[0] = '0' + t / 10;
    if (time[0] == '0') time[0] = ' ';
    time[1] = '0' + t % 10;

    t = minute();
    time[3] = '0' + t / 10;
    time[4] = '0' + t % 10;

    if (second()%2 != 0) {
        time[2] = ' ';
    }

    if (time[0] == ' ') {
        matrix.drawString(5, 5, currentTimeColor, &time[1]);
    } else {
        matrix.drawString(1, 5, currentTimeColor, time);
    }

    matrix.setFont(font5x7);

    char date[] = "Jan 01";

    copyMonth(months[month()-1], date);

    t = day();
    date[4] = '0' + t / 10;
    date[5] = '0' + t % 10;

    matrix.drawString(1, 19, currentDateColor, date);

    matrix.swapBuffers(false);
}

time_t getTeensy3Time() {
    return Teensy3Clock.get();
}

//TODO: Set time and date
//TODO: 12/24 Hour time
