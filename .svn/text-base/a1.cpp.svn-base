/*
 * NAME: 
 * USERID: 
 *
 * Fall 2015 CS349 Assignment 1:  An implementation of Breakout in C/C++ and Xlib.
 * 
 * 
 *
 * Commands to compile and run:
 *
 *  g++ -o a1 a1.cpp -L/usr/X11R6/lib -lX11 -lstdc++
 *  ./a1
 *
 * Note: the -L option and -lstdc++ may not be needed on some machines.
 */

#include "drawing.h"
using namespace std;

int fps = 30;
const int BufferSize = 10;
extern XInfo xInfo;
bool finish;
bool oneHit = false;
int color = 0;
 	
bool handleKeyPress(int key, char text[BufferSize], int time){
	(void)time;
	if(key == 65361){
		paddleMoveLeft();
	}else if(key == 65363){
		paddleMoveRight();
	}else if(key == 113){
		return true;		
	}
	return false;
}


void handleResize( XEvent &event, bool splash) {
        XConfigureEvent xce = event.xconfigure;
        if (xce.width != xInfo.width || xce.height != xInfo.height) {
		int prevWidth = xInfo.width;
		int prevHeight = xInfo.height;
		XFreePixmap(xInfo.display, xInfo.pixmap);
		int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
		xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, xce.width, xce.height, depth);
                xInfo.width = xce.width;
                xInfo.height = xce.height;
		if(!splash){
    			initBlock(NUMBEROFBLOCKS, false, color, oneHit);
			initPaddle();	
			updateBall(prevWidth, prevHeight);
		}
        }
}

bool checkInput(){
	XEvent event; // save the event here
 	KeySym key;
 	bool ret = false;
	char text[BufferSize];
	for(int i = 0; i < 60; i++){
        if(XPending(xInfo.display) > 0){
	//cout << XPending(xInfo.display) << endl;
	XNextEvent(xInfo.display, &event ); // wait for next event
        switch( event.type ) {
                case MotionNotify: // mouse movement
                     //   cout << event.xmotion.x << ","
                       //          << event.xmotion.y << endl;
                     //   cout << event.xmotion.x << endl;
                       //          << event.xmotion.y << endl;
	             handleMotion(event.xmotion.x); 
		     break;
                case ConfigureNotify: // any keypress
                        handleResize(event, false);
                        break;
                case KeyPress: // any keypress
			 XLookupString( (XKeyEvent *)&event, text, BufferSize, &key, 0);
                        ret = handleKeyPress(key, text, event.xkey.time);
		//	exit(0);
                        break; 
		//default:
		//	usleep(1000000/FPS);
		}
	}else{
		usleep(1000000/(fps * 60));
	}
	}
	return ret;
}
	
int action(){
// XEvent event; // save the event here
// KeySym key;
// char text[BufferSize];
 while(!finish ) {  // event loop until 'exit'
	if(checkInput()) return 2;
	handleAnimation();
   	if(repaint())   return 1;
	}
return 0;
 //}
}

/*
int action(){
 XEvent event; // save the event here
 KeySym key;
 char text[BufferSize];
	int c;
 while( true ) {  // event loop until 'exit'
       if(XPending(xInfo.display) > 0){
	XNextEvent(xInfo.display, &event ); // wait for next event
        switch( event.type ) {
                case MotionNotify: // mouse movement
                     //   cout << event.xmotion.x << ","
                       //          << event.xmotion.y << endl;
	                handleMotion(event.xmotion.x); 
                        break;
                case KeyPress: // any keypress
			c = XLookupString( (XKeyEvent *)&event, text, BufferSize, &key, 0);
                        handleKeyPress(key, text, event.xkey.time);
		//	exit(0);
                        break;
                case ConfigureNotify: // any keypress
                        handleResize(xInfo, event);
                        break;
		default:
			handleAnimation();
         		usleep(1000000/FPS);
	 	  	repaint();
		//	break;
	}
//	usleep(1000000/FPS);
//	checkInput();
//	handleAnimation();
  // 	repaint();
        }
 }
}*/


bool actionSplash(int begin){
 XEvent event; // save the event here
 KeySym key;
 char text[BufferSize];
int x = xInfo.width/2 - 80;
int y = xInfo.height/2;
int xSize = 180;
int ySize = 60;
bool end;
 while( true ) {  // event loop until 'exit'
        if(XPending(xInfo.display) > 0){
 	XNextEvent(xInfo.display, &event ); // wait for next event
        switch( event.type ) {
                case ButtonPress: // mouse movement
		        if(event.xbutton.x > x && event.xbutton.x < x + xSize && event.xbutton.y > y + 100 && event.xbutton.y < y + 100 + ySize){
				return false;
			}
		        if(event.xbutton.x > x && event.xbutton.x < x + xSize && event.xbutton.y > y && event.xbutton.y < y + ySize){
				return true;
			}
			break;
                case ConfigureNotify: // any keypress
                        handleResize(event, true);
                        break;
		default:
    			initSplashScreen(begin);
	}
	}
 }
}



int main (int argc, char* argv[] ) {
    srand(time(0));
    int speed = 4;
    switch(argc){
	case 5: color = atoi(argv[4]);
	case 4: if(atoi(argv[3]) > 0) oneHit = true;  
   	case 3: speed = atoi(argv[2]);
	case 2: fps = atoi(argv[1]);
    }
    if(color > 7){
	cout << "color doesn't exist " << endl;
	return 0;
    }
    initX(argc, argv);
    initBoard();
    bool exit = actionSplash(1);
    int exitType = 0;
    int splashType = 0;
    do{
    finish = false; 
    splashType = 0;
   if(exit){
   	initBlock(NUMBEROFBLOCKS, true, color, oneHit);
    	initBall(speed);
    	initPaddle();
    	exitType = action();
	if(exitType == 1){
		splashType = 2;
	}
    }
    }while(exit = actionSplash(splashType));
    XCloseDisplay(xInfo.display);
}
