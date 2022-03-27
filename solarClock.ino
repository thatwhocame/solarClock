#include <microDS3231.h>
#include <GyverOLED.h>
#include <Arduino.h>

MicroDS3231 rtc;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
float lambda = 7275.386666666667;  //Долгота Санкт-Петербурга в секундах

void setup() {
  rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  oled.init();
  Serial.begin(9600);
}

void loop() {
  int UTC = timeTOsec(rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
  int dayNum = dayCounter(rtc.getDay(), rtc.getMonth(), rtc.getYear());
  istTime(UTC, lambda, dayNum);
}

float timeUr(int dayNum){
  float beta = 360*(dayNum - 81)/365;
  return 7.53*cos(beta) + 1.5*sin(beta) - 9.87*sin(2*beta);
}

float istTime(float UTC, float lambda, int dayNum){
  return UTC + lambda + timeUr(dayNum);
}

int timeTOsec(int hours, int minutes, int seconds){
  return hours*3600 + minutes*60 + seconds;
}
int* timeTOhour(int seconds){
  int time[3];
  time[0] = (seconds/3600)%24;
  time[1] = seconds%3600/60;
  time[2] = seconds%60;
  return time;
}

int dayCounter(int Day, int Month, int Year)
{
    int N(0), i(0), Mounthes[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while(i != Month-1)
        {
            N += Mounthes[i];
            i++;
        };
    if ((( Year%4 == 0 && Year%100 != 0 ) || Year%400 == 0) && Month > 2 ) N++;
    return N + Day;
}

  //ПРосто представим переменную t1 в виде большого-большого количества секунд
  //long int temp= t1.n* 3600+ t1.m* 60+ t1.g;
 
  //Теперь сложим имеющееся время и прибавляемое
  //temp+= k;
  
  //А теперь просто переведём temp (большое-большое количество секунд) в часы, минуты и секунда
  //c.n= ((temp/3600)%24); //Это вот столько часов
 
  //Теперь по минутам
  //c.m= temp%3600/60;
  
  //И по секундам
  //c.g= temp%60;