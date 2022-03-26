#include <microDS3231.h>
#include <GyverOLED.h>

MicroDS3231 rtc;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
float lambda = 7275.386666666667  //Долгота Санкт-Петербурга в секундах

void setup() {
  oled.init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
float timeUr(int dayNum){
  float beta = 360*(dayNum - 81)/365;
  return 7.53*cos(beta) + 1.5*sin(beta) - 9.87*sin(2*beta);
}
float istTime(float UTC, float lambda, int dayNum){
  return UTC + lambda + timeUr(dayNum);
}

remya operator+(const vremya &t1, long int  &k)
{
   vremya c;
  //ПРосто представим переменную t1 в виде большого-большого количества секунд
  long int temp= t1.n* 3600+ t1.m* 60+ t1.g;
 
 
  //Теперь сложим имеющееся время и прибавляемое
  temp+= k;
  
  //А теперь просто переведём temp (большое-большое количество секунд) в часы, минуты и секунда
  c.n= ((temp/3600)%24); //Это вот столько часов
 
  //Теперь по минутам
  c.m= temp%3600/60;
  
  //И по секундам
  c.g= temp%60;
 
  cout<<c.n<<" "<<c.m<<" "<<c.g<<endl;
  return c;
};
