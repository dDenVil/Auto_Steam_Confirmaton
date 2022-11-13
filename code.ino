#include "Mouse.h"

const int button1 = 2;
const int button2 = 3;
const int led = 4;
boolean trg1=0;
boolean trg2=0;
//boolean trg3=0;
boolean currentButton1=0;
boolean lastButton1=0;
boolean currentButton2=0;
boolean lastButton2=0;
int cycleDelay=100; // loop timeout 

//________________________________________________________________________
int kk=4; // coef of chars for steam app
int orderDelay=50; // timeout between oders / it can jump if too small delay (min 50)
signed char stX=24; //calibrating start of X axis *k (-128...127)
signed char stY=80; // calibrating start of Y axis *k (-128...127)
signed char step=88; // step from one order to another *k * k
int scroll=8; // amount to scroll 4 orders
int ordersnum=4; // amount of orders on screen
//________________________________________________________________________
int k=4; // coef of chars for cs
int csDelay=100; // delay beetwen scrolls
signed char csX=32;  // set to 1st in a row item *k (-128...127)
signed char csY=34;  // set to 1st in a row item *k (-128...127)
signed char stepCS=25;  //step from one item to another *k   (-128...127)
int scrollCS=9; // sroll of 1 row                (1-10)
int itemnum=8; // amount of items in a row
int rownum=4;  //amount of rows
signed char rowstep=88; //(-128...127)
//________________________________________________________________________

void setup() {
  Serial.available();
  Serial.begin(115200);  
  Mouse.begin();
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {

  settings(csDelay);
  update();
  if (currentButton1 == LOW && trg1==0 && lastButton1 == HIGH)  {     // Checking button 1 and starting after releasing it               
  if (Mouse.isPressed(MOUSE_LEFT)) {
     Mouse.release(MOUSE_LEFT);
   } 
    Serial.println("Start Steam APP");   
    trg1=1;                     
    Serial.println("Calibrating...");
      for (int i=0; i <10; i++) {    // moving pointer to top left corner
       Mouse.move(-125,-125 , 0);
       delay(10);
      }

      for (int i=0; i <kk; i++) {    // moving pointer to start point
        Mouse.move(stX,stY , 0);
        delay(orderDelay);
      }
  }
    if (currentButton1 == HIGH && trg1==1)  {  //process

        for (int i=0; i <ordersnum-1; i++) {
            digitalWrite(led,HIGH);
            Mouse.press(MOUSE_LEFT);
            delay(10);
            Mouse.release(MOUSE_LEFT);
            digitalWrite(led,LOW);
            for (int i=0; i <kk; i++) {
              Mouse.move(0, step, 0); 
              delay(orderDelay);
            } 
          delay(orderDelay);
          
        }
      Mouse.press(MOUSE_LEFT);
      delay(10);
      Mouse.release(MOUSE_LEFT);
      Mouse.move(0,0 ,-scroll);       //scrolling down
          
      for (int i=0; i <(ordersnum-1)*kk; i++) {    // returning to start point
            Mouse.move(0, -step, 0); 
            delay(orderDelay);
      } 
  }
   update();
   if (currentButton1 == LOW && trg1==1 && lastButton1 == HIGH)  {
     Serial.println("Stop Steam");
     trg1=0;
    }
//---------------------------------------------------------------------------------------------------

  if (currentButton2 == LOW && trg2==0 && lastButton2 == HIGH)   // CS        
  {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
    Serial.println("Start CS:GO Stash");   
    trg2=1;                     
    Serial.println("Calibrating...");
      for (int i=0; i <10; i++) {    // moving pointer to top left corner
       Mouse.move(-125,-125 , 0);
       delay(10);
      }
      for (int i=0; i <k; i++) {    // moving pointer to start point
        Mouse.move(csX,csY , 0);
        //delay(csDelay);
        delay(10);
      }
      delay(csDelay);
   }
    if (currentButton2 == HIGH && trg2==1)  {  //process CS
      Mouse.move(0,-rowstep, 0);  
      delay(10);
      for (int i=0; i <rownum; i++) {   //loop for every 4 rows
        Mouse.move(0,rowstep, 0);  
        delay(10);
        for (int i=0; i <itemnum-1; i++) {
          digitalWrite(led,HIGH);
          Mouse.press(MOUSE_LEFT);
          delay(10);
          Mouse.release(MOUSE_LEFT);
          for (int i=0; i <k; i++) Mouse.move(stepCS,0, 0); //step
          digitalWrite(led,LOW);
        }
        Mouse.press(MOUSE_LEFT);
        delay(10);
        Mouse.release(MOUSE_LEFT);
        for (int i=0; i <(itemnum-1)*k; i++)  Mouse.move(-stepCS, 0, 0);  // returning to start point  
        if(digitalRead(button2)==LOW) return; // stop process
     }
     for (int i=0; i <rownum-1; i++) Mouse.move(0,-rowstep, 0);  // returning mouse to 1st row 
     Mouse.move(0,0 ,-scrollCS);       //scrolling down
     delay(csDelay);
    }
    update();
    if (currentButton2 == LOW && trg2==1 && lastButton2 == HIGH)  {
     Serial.println("Stop CS");
     trg2=0;
    }
    lastButton1=currentButton1;
    lastButton2=currentButton2;
    delay(cycleDelay); //for stability maybe baby
}
//-------------------------------------------------------------------- 
boolean debounce (boolean last, int butt){
  boolean current = digitalRead(butt);
    if (last != current) {
    delay(3);
    current=digitalRead(butt);
    return current;
    }
}
void update(void) {
  currentButton1=debounce(lastButton1, button1);
  currentButton2=debounce(lastButton2, button2);
}
int settings (int data) {
       if (Serial.available() > 0) {
     int dat = Serial.parseInt();
      if (dat!=0) {
        data=dat;         // choose your variable for setting up
        Serial.println(data);
      }
    }
}
