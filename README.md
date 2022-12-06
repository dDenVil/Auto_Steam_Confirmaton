# Automatic Steam Confirmation &amp; CS:GO Stasher on Arduino 
Hey there :wave: This is my 1st project on GitHub       
So this device will be useful for the ones who is cs:go investor or trader
## Problem
From time to time I am diving into the investing of cs:go skins and stickers. And 
I'm fed up with putting items to stash, taking them out and confirmation of market listening.   
   
![Steam App](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/app_cs.jpg?raw=true)
## Here's what I came up with
![Device](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/device.jpg?raw=true) Device in small box with 2 buttons and 1 led. It has adapter for phone. It is can put or take from CS:GO stash 1000 items in 20 seconds (
[GIF](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/ScreenCS.gif)
). Just press right button. If you want in can do it 5x faster. And press left button to confirm market listening in Steam App (
[GIF](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/ScreenApp.gif)
).


## Other ways to solve it
**For steam app confirmation we can use [SDA](https://github.com/Jessecar96/SteamDesktopAuthenticator):**     
- [X] Easy and instant confirmation from PC;   
- [X] You can connect multiple accounts 
- [ ] No possibility to use the phone for confirmation;     
- [ ] Every time you have to open SDA & enter encryption key even if you want to confirm 1 order.     

**To simplify stashing we can use [Mouse Recorder](https://www.robot-soft.com/mouse-keyboard-recorder.html):**     
- [X] Easy to install and use;     
- [ ] Hard to setup for cs:go stashing;   
- [ ] Slow even if you choose fast repeating.

**To put items on market we will use:** 
* Chrome extension [SIH](https://chrome.google.com/webstore/detail/steam-inventory-helper/cmeakgjggjdlcpncigglobpjbkabhmjl?hl=uk) 
* Steam feature [MultiSell](https://steamcommunity.com/market/multisell?appid=730&contextid=2&items%5B%5D=Sticker%20%7C%20North%20%28Gold%29%20%7C%202020%20RMR). That is much faster for listening indentical items, like stickers This [link](https://multisellgenerator.com/) will help you. 

# Let's get started
+ For this project we need Arduino Pro Micro!!! It has ATmega32U4 microcontroller that can interpret mouse or keyboard *(P.S. I bought it 4 years ago for 1$, now I wouldn't but it)*. By adding library #include "Mouse.h" we will be able to move mouse on PC and phone.    
+ [Schematics](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/sheme.jpg?raw=true)  is easy. To 2nd and 3rd I/O we connect to GND through buttons. And LED to 4th I/O and GND through 220 Ohms resistor.
+ Choose correct board and Port (Tools->Board-> Arduino AVR-> Arduino Micro)
+ Upload [code.ino](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/code.ino)
+ Adjust shift and step parameters for Steam App and CS:GO stash
```c
int kk=4; // coef of chars for steam app
int orderDelay=50; // timeout between oders / it can jump if too small delay (min 50)
signed char stX=24; //calibrating start of X axis *k (-128...127)
signed char stY=80; // calibrating start of Y axis *k (-128...127)
signed char step=88; // step from one order to another *k * k
int scroll=8; // amount to scroll 4 orders`
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
```
After uploading of the code you have to adjust few parameters:    
*(Change delays to 1000ms during adjustments , it will make your life easier)*
+ For steam app
    + stX  - to set the pointer on the 1st icon
    + stY  - to set the pointer on the 1st icon
    + step - step beetwen icons
    + scroll - scroll of 4 icons
+ For cs: go stash
    + csX - to set the pointer on the 1st icon
    + csY - to set the pointer on the 1st icon
    + stepCS - step beetwen icons on X-axis
    + scrollCS - scroll to update all icons
    + rowstep - step beetween icons on Y-axis       
    
    
Function `settings(stepCS)` will help you to change chosen parameter on terminal (COM-port).

         
![GIF](https://github.com/dDenVil/Auto_Steam_Confirmaton/blob/main/Readme_assets/gifs.gif?raw=true)    


