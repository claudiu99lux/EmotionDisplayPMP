#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include "SPI.h"
#include <Adafruit_ILI9341.h>
#include<SoftwareSerial.h>

#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12

#define DEG2RAD 0.0174532925

SoftwareSerial BT(51, 50);  //RX = 51; TX = 50
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
char selectedAnimation = '0';

void setup() {
  BT.begin(9600);
  tft.begin();
  tft.setRotation(1);
  waitingScreen();
}

void loop(void) {
  if (BT.available())  //verificam daca vin date de la telefon
  {
    selectedAnimation = BT.read();    //citim datele si le convertim in int
    if(selectedAnimation == '1')
      smile();
    else if(selectedAnimation == '2')
      frown();
    else if(selectedAnimation == '3')
      wink();
    else if(selectedAnimation == '4')
      christmas();
    else
      waitingScreen();
  }
}

void smile(){
  tft.fillScreen(ILI9341_YELLOW);
  //Coordonate ochi
  int x1 = 102;
  int y = 195;
  int x2 = 218;
  int raza = 28;
  
  drawEyesAndGlasses(x1, x2, y, raza);
 
  while(selectedAnimation == '1' && !BT.available()){
    //Coordonate gura
    int x_centru_gura = tft.width()/2;
    int y_centru_gura = tft.height()/2 + 10;
    int nr_seg_gura = 40; // 40*3 = 120 grade
    int grosime = 22; // grosime 45 arata ok
    int rx = 150;
    int ry = 120;
    int unghi_start = 300;
    // desenam gura
    drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx-grosime, ry-grosime, grosime/1.5, ILI9341_WHITE);
    drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx, ry, grosime, ILI9341_BLACK);
    
    delay(1000);
    // stergem gura (de fapt desenam culoarea background peste, nu putem sterge altfel)
    drawArcElipsa(160, 130, 300, 40, rx, ry, grosime*2, ILI9341_YELLOW);
  }
}

void frown(){
  tft.fillScreen(ILI9341_YELLOW);
  //Coordonate ochi
  int x1 = 102;
  int y = 195;
  int x2 = 218;
  int raza = 28;
  //desenam ochii
  drawEyesAndGlasses(x1, x2, y, raza);
 
  while(selectedAnimation == '2' && !BT.available()){
    //Coordonate gura
    int x_centru_gura = tft.width()/2;
    int y_centru_gura = 0;
    int nr_seg_gura = 40; // 40*3 = 120 grade
    int grosime = 22; // grosime 45 arata ok
    int rx = 140;
    int ry = 100;
    int unghi_start = 120;
    // desenam gura
    drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx, ry, grosime/1.5, ILI9341_WHITE);
    drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx-grosime/1.5, ry-grosime/1.5, grosime, ILI9341_BLACK);
    
    delay(1000);
    // stergem gura (de fapt desenam culoarea background peste, nu putem sterge altfel)
    drawArcElipsa(x_centru_gura, y_centru_gura, 120, 40, rx*1.05, ry, grosime*2, ILI9341_YELLOW);
  }
}

void wink(){
  tft.fillScreen(ILI9341_YELLOW);
  //Coordonate ochi
  int x1 = 102;
  int y = 195;
  int x2 = 218;
  int raza = 28;
  
  drawEyesAndGlasses(x1, x2, y, raza);
  
  //Coordonate gura
  int x_centru_gura = tft.width()/2;
  int y_centru_gura = tft.height()/2 + 10;
  int nr_seg_gura = 40; // 40*3 = 120 grade
  int grosime = 22; // grosime 45 arata ok
  int rx = 150;
  int ry = 120;
  int unghi_start = 300;
  // desenam gura
  drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx-grosime, ry-grosime, grosime/1.5, ILI9341_WHITE);
  drawArcElipsa(x_centru_gura, y_centru_gura, unghi_start, nr_seg_gura, rx, ry, grosime, ILI9341_BLACK);
  // facem ochiul stang sa clipeasca
  while(selectedAnimation == '3' && !BT.available()){
    delay(1500);
    // forma U
    drawArcElipsa(x2, y-10, 270, 60, raza, raza, 0.25*raza, ILI9341_BLACK);
    //inchidem ochiul deasupra
    tft.fillCircle(x2, y, raza+2, ILI9341_YELLOW);
    //inchidem ochiul sub U
    drawArcElipsa(x2, y-10, 270, 60, 1.5*raza, 1.5*raza, 0.5*raza, ILI9341_YELLOW);
    delay(1500);
    //desenam ochiul din nou de jos in sus
    //sub U
    drawArcElipsa(x2, y-10, 285, 50, raza, raza+5, 0.2*raza, ILI9341_WHITE);
    //ochi
    for(int i=2; i>=0; i--)
      tft.fillCircle(x2, y-10*i, raza, ILI9341_WHITE);
    // pupila
    for(int i=4; i>=0; i--)
      tft.fillCircle(x2, y-5*i, raza/2, ILI9341_BLACK);
  }
}

void christmas(){
  tft.fillScreen(ILI9341_BLACK);
  //in matrici stocam coordonatele triunghiurilor
  int x[6][3];
  int y[6][3];
  int w = tft.width();
  int h = tft.height();
  
  for (int etaj = 0; etaj < 6; etaj++) {
    x[etaj][0] = w/2;
    y[etaj][0] = (etaj+1) * h/8 + h/8; // adunam la final un h/8 pentru ca acesta este varful de sus al triunghiului
    x[etaj][1] = w/2 - (6-etaj) * w/16;
    y[etaj][1] = (etaj+1) * h/8;
    x[etaj][2] = w/2 + (6-etaj) * w/16;;
    y[etaj][2] = (etaj+1) * h/8;
  }

  tft.fillRect(w/2-w/16, 0, w/8, h/8, ILI9341_DARKGREY); // latimea e w/8, setam x ca mijloc minus x/16 ca sa fie centrata tulpina

  for (int etaj = 0; etaj < 6; etaj++) {
    tft.fillTriangle(x[etaj][0], y[etaj][0], x[etaj][1], y[etaj][1], x[etaj][2], y[etaj][2], ILI9341_DARKGREEN);
  }

  while (selectedAnimation == '4' && !BT.available()) {
    for (int layer = 0; layer < 6; layer++) {
      for (int corner = 0; corner < 3; corner++) {
        tft.fillCircle(x[layer][corner], y[layer][corner], w/40, rainbow(random(128)));
        delay(10);
      }
    }
    //adaugam o lumina si deasupra tulpinii
    tft.fillCircle(x[0][0], y[0][1], w/40, rainbow(random(128)));
  }
}

void waitingScreen(){
  tft.fillScreen(ILI9341_LIGHTGREY);
  tft.fillRoundRect(30, 30, 260, 180, 10, ILI9341_OLIVE);
  tft.fillCircle(160, 120, 50, ILI9341_MAROON);
  tft.fillCircle(160, 120, 30, ILI9341_BLUE);
}

unsigned int rainbow(int valoare)
{
  // valoare intre 0-127
  // vom returna o valoare pe 16 biti care reprezinta culoarea
  // aceasta metoda de generare culori am realizat-o combinand informatiile despre culori gasite pe forumurile arduino

  byte red = 0; //red reprezinta cei mai semnificativi 5 biti
  byte green = 0; //green reprezinta urmatorii 6 biti
  byte blue = 0; //blue reprezinta cei mai putin semnificativi 5 biti

  byte quadrant = valoare / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (valoare % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (valoare % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = valoare % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (valoare % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}


void drawEyesAndGlasses(int x1, int x2, int y, int raza){
  // ochi
  for(int i=0; i<3; i++){
    tft.fillCircle(x1, y-10*i, raza, ILI9341_WHITE);
    tft.fillCircle(x2, y-10*i, raza, ILI9341_WHITE);
  }
  
  // pupile
  for(int i=0; i<5; i++){
    tft.fillCircle(x1, y-5*i, raza/2, ILI9341_BLACK);
    tft.fillCircle(x2, y-5*i, raza/2, ILI9341_BLACK);
  }
  
  // lentile ochelari
  for(int i=43; i<=48; i++){
    tft.drawCircle(x1, y-10, i, ILI9341_BLACK);  
    tft.drawCircle(x2, y-10, i, ILI9341_BLACK);
  }

  //legatura intre lentile
  for(int i=-3; i<=3; i++)
    tft.drawLine(x1+43, y-10+i, x2-43, y-10+i, ILI9341_BLACK);
}

int drawArcElipsa(int x, int y, int unghi_start, int nr_segmente, int rx, int ry, int w, unsigned int culoare)
{
  // x,y = coordonatele centrului elipsei
  // unghi_start = 0 - 359, unghiul de la care se incepe desenarea (fata de axa oY, deci oY este 0)
  // nr_segmente = numarul de segmente desenate. Un segment are 3 grade, deci pentru 120 grade vor fi 40 segmente, pentru 360 grade vor fi 120 segmente
  // rx = raza pe axa x
  // yx = raza pe axa y
  // w  = grosime
  byte seg = 3; // un segment are 3 grade
  byte inc = 3; // desenam un segment la fiecare 3 grade pentru un arc continuu, putem modifica pentru arc punctat

  for (int i=unghi_start; i<unghi_start+seg*nr_segmente; i=i+inc) {
    // calculam coordonatele de start pentru segmentul curent
    float sx = cos((i - 90) * DEG2RAD);
    float sy = sin((i - 90) * DEG2RAD);
    int x0 = sx * (rx - w) + x;
    int y0 = sy * (ry - w) + y;
    int x1 = sx * rx + x;
    int y1 = sy * ry + y;

    // calculam coordonatele finale pentru segmentul curent
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    // desenam cele doua triunghiuri care compun segmentul
    tft.fillTriangle(x0, y0, x1, y1, x2, y2, culoare);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, culoare);
  }
}
