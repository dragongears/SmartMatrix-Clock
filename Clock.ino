/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 *
 */

#include <Time.h>
#include <SmartMatrix_32x32.h>

SmartMatrix matrix;

int brightness = 60;

void setup()  {
  // set the Time library to use Teensy 3.0's RTC to keep time
  setSyncProvider(getTeensy3Time);

  matrix.begin();
  matrix.setBrightness(brightness*(255/100));
}

void loop() {
//  if (Serial.available()) {
//    time_t t = processSyncMessage();
//    if (t != 0) {
//      Teensy3Clock.set(t); // set the RTC
//      setTime(t);
//    }
//  }
  digitalClockDisplay();
  delay(1000);
}

void digitalClockDisplay() {
  // digital clock display of the time
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.print(" ");
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year());
//  Serial.println();

    matrix.fillScreen({0x00, 0x00, 0x00});

    matrix.setFont(font3x5);

    int t = 0;
    char time[] = "00:00:00 AM";

    t = hourFormat12();
    time[0] = '0' + t / 10;
    time[1] = '0' + t % 10;

    t = minute();
    time[3] = '0' + t / 10;
    time[4] = '0' + t % 10;

    t = second();
    time[6] = '0' + t / 10;
    time[7] = '0' + t % 10;

    if (isPM()) {
      time[9] = 'P';
    } else {
      time[9] = 'A';
    }

    matrix.drawString(1, 16, {0xff, 0xff, 0}, time);

    matrix.swapBuffers(true);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}
