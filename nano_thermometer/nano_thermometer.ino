#include <IIC_without_ACK.h>
#include "oledfont.c"

#define OLED_SDA 8
#define OLED_SCL 9

IIC_without_ACK display(OLED_SDA, OLED_SCL);

int data[128];

void setup(){
  display.Initial();
  delay(10);
  display.Fill_Screen(0x00);
  analogReference(INTERNAL);
  display.Char_F8x16(0,0,"Nano");  
  display.Char_F8x16(0,2,"thermometer");  
  display.Char_F8x16(0,4,"by DS");
  delay(250);
  display.Fill_Screen(0x00);  
  for (int i=0;i<128;i++){data[i]=0;}
}

void loop(){
  for (int i=1;i<128;i++){
    data[i-1]=data[i];
  }

  float ftempC=0;
  for (int i=0;i<256;i++){
    ftempC += 1000* 1.1*analogRead(7)*10/1024 -200;
  }
  ftempC/=2560;
  int tempC = ftempC;
  data[127]=tempC;
  if (data[127]>360) data[127]=360;
  if (data[127]<130) data[127]=130;
  
  char cha[25];
  sprintf(cha, "T=%i.%i'C", tempC/10, tempC%10);

  
  for (int l=0;l<6;l++){
    display.IIC_SetPos(0,2+l);  
    display.Begin_IIC_Data();
    for (int i=0;i<127;i++){
      int v = (360-data[i])/5;
      char u;
      if (v>=(l+1)*8) { u=8; }
      else if (v<(l-0)*8) { u=0; }
      else { u = v%(l*8); u%=8; }
      char w = 256-pow(2.0, u);
      display.Write_IIC_Byte(w);
    }
    display.IIC_Stop();  
  }
  
  display.Char_F8x16(0,0,cha);

  delay(0);//delay of plot redraw =approx 380ms
}
