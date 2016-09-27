#include "drawing.h"
#include <sstream>
using namespace std;
/*
 * Function to put out a message on error exits.
 */

XInfo xInfo;
extern int fps;
vector<Block> boardBlocks;
vector<Ball> balls;
Paddle paddle(0,0,0);
Score playerScore(0);
extern bool finish;

void error( string str ) {
    cerr << str << endl;
    exit(0);
}


void initSplashScreen(int begin){
	string text = "BREAKOUT";
	string text2 = "By: Yi Chao Peter Liang (ycpliang)";
	string text3 = "20433663";
	string text4 = "START";
	string text5 = "EXIT";
	if(begin == 0 || begin == 2){
		std::stringstream ss;
		ss.str("");
		ss << playerScore.getScore();
		if(begin == 2){
			text = "YOU WON!!!";
		}else{
			text  = "GAMEOVER";
		}
		text3 = "FINAL SCORE: " + ss.str();
		text4 = "RESTART";
 		text5 = "QUIT";	
	}
	string text6 = "Extra Feature: GREEN(1 pts), RED(2 pts), YELLOW(3 pts), PINK(4 pts) Blocks is destroyed in 1 hit," ;
	string text7 = "PURPLE(5 pts) is 2 hits, CYAN(6 pts) is 3 hits, and GREY(7 pts) need 4 hits, ";
	string text8 = "hitting the paddle increase score by one point. Paddle bounce based on sin function.";
	string text9 = "<- left arrow key and -> right arrow key to move the paddle.";
	string text10 = "fully destroy grey blocks will award you with an duplicate ball on the field";

	XFillRectangle(xInfo.display, xInfo.pixmap,  xInfo.gc[BLACK], 0, 0, xInfo.width, xInfo.height);

	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (30), 30, text6.c_str(), text6.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (30), 50, text7.c_str(), text7.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (30), 70, text8.c_str(), text8.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (30), 90, text9.c_str(), text9.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (30), 110, text10.c_str(), text10.length() );

	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[5],
                  (xInfo.width/2 - 40), xInfo.height/3, text.c_str(), text.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[7],
                  (xInfo.width/2 - 100), (xInfo.height/3 + 40), text2.c_str(), text2.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  (xInfo.width/2 - 50), (xInfo.height/3 + 80), text3.c_str(), text3.length() );

	XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[GREEN], (xInfo.width/2 - 80), xInfo.height/2, 180, 60);
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[9],
                  (xInfo.width/2 - 10), (xInfo.height/2 + 35), text4.c_str(), text4.length() );
	
	XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[RED], (xInfo.width/2 - 80), xInfo.height/2 + 100, 180, 60);
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[9],
                  (xInfo.width/2 - 10), (xInfo.height/2 + 135), text5.c_str(), text5.length() );

	XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[BLACK], 
		0, 0, xInfo.width, xInfo.height,
		0, 0);
	XFlush(xInfo.display);
	
}

void Block::paint(XInfo & xInfo){ 
	XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[color], x, y, xSize, ySize);
	XDrawRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[BLACK], x, y, xSize, ySize);
}

void Ball::paint(XInfo & xInfo){ 
	XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc[GREEN],(int)x,(int)y, size * 2, size * 2, 0, 360 * 64);
}

void Paddle::paint(XInfo & xInfo){ 
	XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc[PADDLE], x + 5, y, x + length - 5, y);
}

void Score::paint(XInfo & xInfo){
	std::string pScore;
	std::string cFPS;
	std::stringstream ss;
	ss << score;
	pScore = ss.str();
	ss.str("");
	ss << fps;
	cFPS = ss.str();
	std::string text = "Score: " + pScore;
	std::string text2 = "FPS: " + cFPS;
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  25, 25, text.c_str(), text.length() );
	XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc[8],
                  25, 45, text2.c_str(), text2.length() );

}

/*
 * Create a window
 */
void initX(int argc, char* argv[]) {

    XSizeHints hints;
    /*
    * Display opening uses the DISPLAY	environment variable.
    * It can go wrong if DISPLAY isn't set, or you don't have permission.
    */
    xInfo.display = XOpenDisplay( "" );
    if ( !xInfo.display )	{
        error( "Can't open display." );
    }

    /*
    * Find out some things about the display you're using.
    */
    xInfo.screen = DefaultScreen( xInfo.display ); // macro to get default screen index

    unsigned long white, black;
    white = XWhitePixel( xInfo.display, xInfo.screen ); 
    black = XBlackPixel( xInfo.display, xInfo.screen );

	hints.x = 10;
        hints.y = 10;
        hints.width = 1000;
        hints.height = 700;
        hints.flags = PPosition | PSize;

    xInfo.window = XCreateSimpleWindow(
       xInfo.display,				// display where window appears
       DefaultRootWindow( xInfo.display ), // window's parent in window tree
       hints.x, hints.y,			           // upper left corner location
       hints.width, hints.height,	               // size of the window
       BORDER,						     // width of window's border
       black,						// window border colour
       black );			    // window background colour
   
    // extra window properties like a window title
    XSetStandardProperties(
        xInfo.display,		// display containing the window
        xInfo.window,		// window whose properties are set
        "BreakOut Liang",	// window's title
        "BO",				// icon's title
        None,				// pixmap for the icon
        argv, argc,			// applications command line args
        None );			// size hints for the window

 	xInfo.height = hints.height;	
	xInfo.width = hints.width;
    	
	int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
	xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, xInfo.width, xInfo.height, depth);
	/*
     * Put the window on the screen.*/
    	XSelectInput(xInfo.display, xInfo.window,
        PointerMotionMask | KeyPressMask | ButtonPressMask | ButtonMotionMask | StructureNotifyMask); // select events
    	XSetWindowBackgroundPixmap(xInfo.display, xInfo.window, None);
    
    XSetWindowBackgroundPixmap(xInfo.display, xInfo.window, None);
    XMapRaised( xInfo.display, xInfo.window );

    XFlush(xInfo.display);
    //sleep(2);	// let server get set up before sending drawing commands
                // this is a hack until we get to events
}

void initBall(int speed){
    while(!balls.empty()){
	balls.pop_back();
    }
    int x,y,size;
    x = xInfo.width / 2;
    y = xInfo.height - xInfo.height/50 - 15;
    size = 10;
    int xVeloc, yVeloc;
    xVeloc = sqrt(speed * speed / 2);
    yVeloc = sqrt(speed * speed /2 );
    Ball tempBall(x,y,xVeloc,yVeloc,true,size);
    balls.push_back(tempBall);
}

void initPaddle(){
   int x;
   int y = xInfo.height - xInfo.height/50;
   int length;
   length = xInfo.width / 17;
   x = xInfo.width / 2 - length/2;
   paddle = Paddle(x,y,length);	
   playerScore.setZero();
}

void initBlock(int number, bool newBlocks, int oneColor, bool oneHit){
    while(!boardBlocks.empty()){
	boardBlocks.pop_back();
    }
    int x, y, xSize, ySize, color, type, active;
    int width = xInfo.width;
    int height = xInfo.height;
    int space = xInfo.width / 20; 
    int xSizeB = (width - space * 2)/12; 
    int yspace = xInfo.height / 10;
    int ySizeB = (height/2 - yspace * 2)/6;
    int random1 = rand() % 7 + 1;
    if(oneColor != 0) random1 = oneColor;
    for(int i = 0; i < number; i++){
	if(i % 12 == 0 && oneColor == 0) random1 = rand() % 7 + 1;
	x = space + (i % 12) * xSizeB;
	y = yspace + i/12 * ySizeB;
 	xSize = xSizeB;
	ySize = ySizeB;
	if(newBlocks){
		color = random1;
		type = color;
		active = true;
    		Block temp(x,y,xSize,ySize,color,type,oneHit,active);
		boardBlocks.push_back(temp);
	}else{
		boardBlocks[i].changeProp(x, y, xSize, ySize);
	}
    	//	boardBlocks[i].paint(xInfo);
    }
    //XFlush(xInfo.display);
}

bool repaint(){
	bool noMore = true;
	//clear
	 XFillRectangle(xInfo.display, xInfo.pixmap,  xInfo.gc[BLACK], 0, 0, xInfo.width, xInfo.height);
	//paint Blocks
	 for(int i = 0; i < boardBlocks.size(); i++){
		if(boardBlocks[i].checkActive()){
			 boardBlocks[i].paint(xInfo);
			noMore = false;
		}
	 }
	//paint paddle
	for(int i = 0; i < balls.size(); i++){
		if(balls[i].checkValid() && balls[i].checkActive()) 
			balls[i].paint(xInfo);
	}
	paddle.paint(xInfo);
	playerScore.paint(xInfo);	
	XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[BLACK], 
		0, 0, xInfo.width, xInfo.height,
		0, 0);

	XFlush(xInfo.display);

	return noMore;

}
void initBoard(){

    Display * display = xInfo.display;
    Window win = xInfo.window;
    GC gc;
    XColor color;
    Colormap colormap;

    gc = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, gc, BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, gc, BlackPixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, gc, FillSolid);
	XSetLineAttributes(xInfo.display, gc,
	                     7, LineSolid, CapRound, JoinMiter);

	xInfo.gc.push_back(gc); 
  
  char green[] = "#00FF00";
  char red[] = "#FF001A";
  char yellow[] = "#FFFF00";
  char pink[] = "#FF0080";
  char purple[] = "#DE00FF";
  char cyan[] = "#00FFF3";
  char grey[] = "#666666";
  char paddle[] = "#FF001A";
  char redDisplay[] ="#FF001A";
  vector <char *> colorCodes;
  colorCodes.push_back(green);
  colorCodes.push_back(red);
  colorCodes.push_back(yellow);
  colorCodes.push_back(pink);
  colorCodes.push_back(purple);
  colorCodes.push_back(cyan);
  colorCodes.push_back(grey);
  colorCodes.push_back(paddle);

  for(int i = 0; i < colorCodes.size(); i++){
  	colormap = DefaultColormap(xInfo.display, 0);
  	XParseColor(xInfo.display, colormap, colorCodes[i], &color);
 	XAllocColor(xInfo.display, colormap, &color);

		gc = XCreateGC(xInfo.display, xInfo.window, 0, 0);      
		XSetForeground(xInfo.display, gc, color.pixel);
       		XSetBackground(xInfo.display, gc, BlackPixel(xInfo.display, xInfo.screen));
        	XSetFillStyle(xInfo.display, gc, FillSolid);
        	XSetLineAttributes(xInfo.display, gc,
                             3, LineSolid, CapButt, JoinRound);
	
	xInfo.gc.push_back(gc); 
  }
  XSetLineAttributes(xInfo.display, xInfo.gc[8], 8, LineSolid, CapRound, JoinRound);
  XFontStruct * font;
  font = XLoadQueryFont (display, "8x16");
  XSetFont (display, xInfo.gc[8], font->fid);

  XFontStruct * font1;
  	font1 = XLoadQueryFont (xInfo.display, "12x24");
  	XSetFont (xInfo.display, xInfo.gc[5], font1->fid);
  	XFontStruct * font2;
  	font2 = XLoadQueryFont (xInfo.display, "8x16");
  	XSetFont (xInfo.display, xInfo.gc[7], font2->fid);

  	colormap = DefaultColormap(xInfo.display, 0);
  	XParseColor(xInfo.display, colormap, redDisplay, &color);
 	XAllocColor(xInfo.display, colormap, &color);

		gc = XCreateGC(xInfo.display, xInfo.window, 0, 0);      
		XSetForeground(xInfo.display, gc, color.pixel);

  	colormap = DefaultColormap(xInfo.display, 0);
  	XParseColor(xInfo.display, colormap, green, &color);
 	XAllocColor(xInfo.display, colormap, &color);
       		XSetBackground(xInfo.display, gc, color.pixel);
        	XSetFillStyle(xInfo.display, gc, FillSolid);
        	XSetLineAttributes(xInfo.display, gc,
                             3, LineSolid, CapButt, JoinRound);
	
	xInfo.gc.push_back(gc); 
  	XFontStruct * font3;
  	font3 = XLoadQueryFont (xInfo.display, "8x16");
  	XSetFont (xInfo.display, xInfo.gc[9], font3->fid);

}


void awardBalls(int i){
    cout << "award ball" << endl;
    double x,y;
    int size;
    double xVeloc, yVeloc;
    x = balls[i].getX();
    y = balls[i].getY();
    size = 10;
    xVeloc = -balls[i].getXvelocity();
    yVeloc = -balls[i].getYvelocity();
    cout << "x: " << x << "y: " << y << "xVeloc: " << xVeloc << "yVeloc: " << yVeloc << endl;
    Ball tempBall(x,y,xVeloc,yVeloc,true,size);
    balls.push_back(tempBall);
    balls[balls.size() - 1].move();

}

void handleAnimation(){
	bool end = false;
	for(int i = 0; i < balls.size(); i++){
		if(balls[i].checkActive()){
			int hit = balls[i].checkHit(boardBlocks, playerScore);
			if(hit == 2){
				awardBalls(i);
			}else if(hit == 0){	
				balls[i].move();
			 	balls[i].paddleCollision(paddle.getX(), paddle.getY(), paddle.getLength());// playerScore.add(1);
				end = !balls[i].checkBound(xInfo.width, xInfo.height);
			}
		}		
	}
//	bool end = true;
	if(end){
		finish = true;
	}else{
		end = true;
		for(int i = 0; i < boardBlocks.size(); i++){
			if(boardBlocks[i].checkActive()){
				end = false;
			}	 
		}
		if(end){
			finish = true;
		}
	}	
}

void paddleMoveLeft(){
    paddle.moveLeft();
}

void paddleMoveRight(){
    paddle.moveRight(xInfo);
}

void handleMotion(int x){
	if(x < paddle.getX()){
		paddle.moveLeft();
	}else if(x > paddle.getX()){
		paddle.moveRight(xInfo);
	}
}


void updateBall(int prevWidth, int prevHeight){
	for(int i = 0; i < balls.size(); i++){
		if(balls[i].checkActive()){
			balls[i].renewBallPos(prevWidth, prevHeight, xInfo.width, xInfo.height);
		}
	}
}

