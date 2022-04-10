#include <GyverOLED.h>
#include <Arduino.h>

#define OLED_RESET 4
#define sizeTrend 30
int in1[sizeTrend];
int in2[sizeTrend];
GyverOLED<SSH1106_128x64> oled;

int convert(int y, int mn, int mx, byte yTrend, byte heightTrend, int *in ){
  int ny=y;
  ny=map(ny,mn,mx,heightTrend-1+yTrend,yTrend);
  //ny=map(ny,mn,mx,yTrend,heightTrend-1+yTrend);
  return ny;
}

void setup(){
  oled.init();
  oled.clear();
  oled.setScale(1);
  oled.update();
}
void loop(){
  oled.clear();
  drawTrend(95,30,0,0,5,in1);
  drawTrend(30,30,0,33,0,in2);
  drawTrend(34,24,60,37,5,in1);
  oled.update();
  delay(200);
}
void drawTrend(int widthTrend, int heightTrend, int xTrend, byte yTrend, byte cn, int *in){
   //добавляем новое значение
  in[sizeTrend-1]=analogRead(cn);
  byte oldX=0;
  byte oldY=0+yTrend;
  int mn=1000;
  int mx=0;
  double k=0.0;
  //сдвигаем график
  for  (byte x=0;x<(sizeTrend-1);x++){
    in[x]=in[x+1];
  }

  //поиск мин и макс
  for (byte i=0;i<sizeTrend;i++){
    if (in[i]>mx){
      mx=in[i];
    }
    if (in[i]<mn){
      mn=in[i];
    }
  }
  if(mn==mx){
    mx=mn+1;
    mn=mn-1;
  }
  //формирование буфера вывода
  for(byte x=0;x<sizeTrend-1;x++){
    byte y=convert(in[x],mn,mx,yTrend,heightTrend,in);
    byte nxt_x=map(x,0,sizeTrend-1,0,widthTrend);
    //отрисовка тренда
    oled.line(xTrend+oldX, oldY, xTrend+nxt_x, y);
    oldX=nxt_x;
    oldY=y;

    //отрисовка рамки
    oled.rect(xTrend, yTrend, widthTrend, heightTrend);

  } 
  //вывод минимума и максимума
  oled.setCursor(xTrend+widthTrend+3,yTrend);
  oled.println(mx);
  oled.setCursor(xTrend+widthTrend+3,yTrend+heightTrend-8);
  oled.println(mn);
  oled.setCursor(xTrend+widthTrend+3,yTrend+(heightTrend/2)-4);
  oled.println(in[sizeTrend-1]); //текущее
  oldX=0;
  oldY=convert(in[0],mn,mx,yTrend,heightTrend,in);
}