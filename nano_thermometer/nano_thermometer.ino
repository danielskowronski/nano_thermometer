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
  
  double ftempC=0;
  for (int i=0;i<100;i++){
    ftempC += (1000* 1.1*analogRead(7)*10)/1024;
  }
  ftempC/=1000;
  int tempC = ftempC - 20; //LM35 without resistor: 2..150'C
  data[127]=tempC;
  if (data[127]>360) data[127]=360;
  if (data[127]<130) data[127]=130;
  
  unsigned long long m=millis();
  char v,w;
  for (int l=5;l>=0;l--){
    display.IIC_SetPos(0,2+l);  
    display.Begin_IIC_Data();
    int i=0; for (int m=0;m<=128;m++) for (;i<m && i<127;i++){ //redraw optimization
      v = (360-data[i])/5;
      if (v>=(l+1)*8) { v=8; /*empty*/}
      else if (v<l*8) { v=0; /*full*/}
      else { v%=(l*8); v%=8; }
      w = 255>>v<<v; //w = v*zeros from left, rest are ones
      display.Write_IIC_Byte(w);
    }
    display.IIC_Stop();  
  }
  m = millis()-m;

  char cha[25];
  sprintf(cha, "T=%i.%i'C", tempC/10, tempC%10);
  display.Char_F8x16(0,0,cha);
  sprintf(cha, "%ims", m);
  display.Char_F8x16(72,0,cha);

  delay(0);//delay of plot redraw =approx 380ms
}