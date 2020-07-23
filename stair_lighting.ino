
#include <Tlc5940.h>
#include <Timers.h>

const int BUTTON1 = 6;
const int BUTTON2 = 8;

int zapaloneDol = 0;
int zapaloneGora = 0;

Timer timer;

void setup()
{
  Serial.begin(9600);
  Tlc.init(0);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}

void loop()
{
  zapalanieOdGory();
  zapalanieOdDolu();
  sciemnianieOdDolu();
  sciemnianieOdGory();
}

void zapalanieOdDolu(){
  if(zapaloneDol == 0){
    if (digitalRead(BUTTON1) == LOW) {
      timer.begin(20000);
      for (int i=0; i <= 14; i++){
        for (int j = 0; j <= 4000; j = j + 25){
          Tlc.set(i, j);
          Tlc.update();
          delay(1);
        }
        delay(1);
        Tlc.update(); 
      }
      zapaloneDol = 1;
    }
  }
  if(timer.available()){
    for (int i=0; i <= 14; i++){
      Tlc.set(i, 0);
      Tlc.update();
      delay(40);
    }
   zapaloneDol = 0;
  }
}

void sciemnianieOdDolu(){
  Serial.print(zapaloneDol);
  if(zapaloneDol == 1){
    if(digitalRead(BUTTON2) == LOW) {
      timer.time(STOP);
       for (int i=0; i <= 14; i++){
        for (int j = 4000; j >= 0; j = j - 25){
          Tlc.set(i, j);
          Tlc.update();
          delay(1);
        }
       delay(1);
       Tlc.update(); 
      }
     zapaloneDol = 0;
    }
  }
}

void zapalanieOdGory(){
  if(zapaloneGora == 0){
    if (digitalRead(BUTTON2) == LOW) {
      timer.begin(20000);
      for (int i=14; i >= 0; i--){
        for (int j = 0; j <= 4000; j = j + 25){
          Tlc.set(i, j);
          Tlc.update();
          delay(1);
        }
        delay(50);
        Tlc.update(); 
      }
     zapaloneGora = 1;
    }
  }
  if(timer.available()){
    for (int i=14; i >= 0; i--){
      Tlc.set(i, 0);
      Tlc.update();
      delay(30);
    }
   zapaloneGora = 0;
  }
}

void sciemnianieOdGory(){
  if(zapaloneGora == 1){
    if(digitalRead(BUTTON1) == LOW) {
      timer.time(STOP);
       for (int i=14; i >= 0; i--){
        for (int j = 4000; j >= 0; j = j - 25){
          Tlc.set(i, j);
          Tlc.update();
          delay(1);
        }
        delay(50);
        Tlc.update(); 
       }
      zapaloneGora = 0;
    }
  }
}
