/*
 * SmartMatrix Clock
 * Version 0.2.1
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

SmartMatrix matrix;

int brightness = 60;

void setup()  {
    // set the Time library to use Teensy 3.1's RTC to keep time
    setSyncProvider(getTeensy3Time);

    matrix.begin();
    matrix.setBrightness(brightness*(255/100));
}

void loop() {
//      Teensy3Clock.set(t); // set the RTC
//      setTime(t);

    digitalClockDisplay();
    delay(100);
}

void digitalClockDisplay() {
  // digital clock display of the time
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year());

    matrix.fillScreen({0x00, 0x00, 0x00});

    matrix.setFont(font5x7);

    int t = 0;
    char time[] = "00:00A";

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

    if (isPM()) {
        time[5] = 'P';
    } else {
        time[5] = 'A';
    }

    if (time[0] == ' ') {
        matrix.drawString(4, 1, {0xff, 0xff, 0}, &time[1]);
    } else {
        matrix.drawString(1, 1, {0xff, 0xff, 0}, time);
    }

    matrix.swapBuffers(true);
}

time_t getTeensy3Time()
{
    return Teensy3Clock.get();
}
