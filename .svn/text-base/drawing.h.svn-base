#ifndef __DRAWING_H__
#define __DRAWING_H__
#include <cstdlib>
#include <iostream>
#include <list>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define BLACK 		0
#define GREEN 		1
#define RED   		2
#define YELLOW          3
#define PINK		4
#define PURPLE		5
#define CYAN		6
#define GREY		7
#define PADDLE		8
#define BORDER 5
#define PI  3.14159265
#define NUMBEROFBLOCKS 72


struct XInfo {
    Display* 	display;
    int		 screen;
    Window	 window;
    std::vector<GC> gc;
    Pixmap pixmap;
    int width;
    int height;
};



class Displayable{
	public:
		virtual void paint(XInfo & xInfo) = 0;
};


class Score: public Displayable {
	int score;
	public:
		Score(int score ) : score(score) {}
		virtual void paint(XInfo & xInfo);
		bool add(int x) {
			score += x;
		}
		int getScore(){
			return score;
		}	
		void setZero(){
			score = 0;
		}
};


class Block: public Displayable{
 int x,y;
 int xSize, ySize;
 int color;
 int type;
 bool oneHit;
 bool active1;
 public:
	virtual void paint(XInfo & xInfo);
 	Block(int x, int y, int xSize, int ySize, int color, int type, bool oneHit, bool active):
		x(x), y(y), xSize(xSize), ySize(ySize), color(color), type(type), oneHit (oneHit), active1(active){}
	bool checkActive(){
		return active1;
	}
	int getX(){
		return x;
	}
	int getY(){
		return y;	
	}
	int getXSize(){
		return xSize;
	}
	int getYSize(){
		return ySize;
	}
	bool hit(Score & playerScore){
		playerScore.add(color);
		if(color < 5 || oneHit){
			active1 = false;
			if(type == 7){
				return true;
			}
		}else{
	//		type -= 1;
			color -= 1;
		}
		return false;
	}
	void changeProp(int x, int y, int xSize, int ySize){
		this->x = x;	
		this->y = y;
		this->xSize = xSize;
		this->ySize = ySize;
	}
};


class Ball: public Displayable{
 double x,y;
 double xVelocity, yVelocity;
 bool active1;
 int size;
 public:
	virtual void paint(XInfo & xInfo);
 	Ball(int x, int y, int xVelocity, int yVelocity, int active, int size): x(x), y(y), xVelocity(xVelocity), yVelocity(yVelocity), active1(active), size(size/2){}
	bool checkActive(){
		return active1;
	}
	bool checkValid(){
		return (x > 0);
	}
	int moveNumber(){
		return std::max(xVelocity,yVelocity);
	}
	bool move(){
//		int maxChange = std::max(xVelocity,yVelocity);
//		x += xVelocity/maxChange;
		x += xVelocity;
		y -= yVelocity;
//		y -= yVelocity/maxChange;
		
	}
	int checkHit(std::vector <Block> & boardBlocks, Score & playerScore){
		int maxChange = std::max(abs(xVelocity), abs(yVelocity));
		double tryX = x;
		double tryY = y;
		int ret = 0;
		int xValue = -1;
		int yValue = -1;
		int bx;
		int by;
		int bxSize;
		int bySize;
		for(int i = 0; i <= maxChange; i++){
			tryX += xVelocity/maxChange;
			tryY -= yVelocity/maxChange;
		  	for(int i2 = 0; i2 < boardBlocks.size(); i2++){
				bx = boardBlocks[i2].getX();
				by = boardBlocks[i2].getY();
				bxSize = boardBlocks[i2].getXSize();
				bySize = boardBlocks[i2].getYSize();
                		if(boardBlocks[i2].checkActive()){
					if(tryX + size >= bx && tryX <= bx + bxSize && ((tryY - 1 <= by + bySize && tryY + 1 >= by + bySize) || (tryY + size + 1 >= by && tryY + size - 1 <= by))){
						ret = 1;
						if(boardBlocks[i2].hit(playerScore))ret = 2;
						yVelocity = -yVelocity;
						y = (int)tryY - yVelocity;
						x = (int)tryX + xVelocity;
					}else if(((tryX + size + 1 >= bx && tryX + size - 1 <= bx ) || (tryX - 1 <= bx + bxSize && tryX + 1 >= bx + bxSize)) && tryY <= by + bySize && tryY + size >= by){
						ret = 1;
						if(boardBlocks[i2].hit(playerScore)) ret = 2;
						xVelocity = -xVelocity;
						x = (int)tryX + xVelocity;
						y = (int)tryY - yVelocity;
					}
					if(ret == 1){
						break;
					}	
				}
			}

			if(ret == 1){
				break;
			}
		}
		return ret;
	}
	bool checkBound(int maxX, int maxY){
		if(x + size <= BORDER && y+size < maxY - BORDER){
			xVelocity = -xVelocity;
			return true;
	//	}else if(y + size > maxY - BORDER){ //for testing
	//		yVelocity = -yVelocity;
	//		return true;
		}else if(x + size >= maxX - BORDER && y+size < maxY){
		//	std::cout << "true" << std::endl;
			xVelocity = -xVelocity;
			return true;
		}else if(y - size <= BORDER){
			yVelocity = -yVelocity;
			return true;
		}else if(y + size >= maxY){
			active1 = false;
			return false;
		}else{
			return true;
		}
	}
	/*bool paddleCollision(int paddleX, int paddleY, int length){
		if(x + size >= paddleX && x - size <= paddleX + length && y >= paddleY){
	//		y = paddleY;
			yVelocity = -yVelocity;
			return true;
		}
	}*/
	bool paddleCollision(int paddleX, int paddleY, int length){
				
		if(x + size >= paddleX && x - size <= paddleX + length && y >= paddleY){
			if(x + size < paddleX){
				x = paddleX;
			}
			double rad = asin((1.8 * (x + size - paddleX)/length - 0.9));
			if((x + size - paddleX) / length >= 1){
					rad = asin((1.8 * (x - size - paddleX)/length - 0.9));
			}
	//		if(rad < 0.2 && rad > -0.2){
				if(rad > 0){
					rad += 0.3;
				}else{
					rad -= 0.3;
				}
	//		}
			double speed = sqrt((xVelocity * xVelocity + yVelocity * yVelocity));		
			xVelocity = speed * sin(rad);
			y = paddleY;
			yVelocity = speed * cos(rad);	
			return true;
		}
	}
	bool renewBallPos(int prevWidth, int prevHeight, int newWidth, int newHeight){
		x = x * newWidth / prevWidth;
		y = y * newHeight / prevHeight;
		xVelocity = xVelocity * newWidth / prevWidth;
		yVelocity = yVelocity * newHeight / prevHeight;
	}
	double getX(){
		return x;
	}
	double getY(){
		return y;
	}
	double getXvelocity(){
		return xVelocity;
	}
	double getYvelocity(){
		return yVelocity;
	}
};

class Paddle: public Displayable {
 int x;
 int y;
 int length;
 int speed;
 public:
	virtual void paint(XInfo & xInfo);
	Paddle(int x, int y, int length): x(x),y(y), length(length), speed(0){}
	int getX(){
		return x;
	}
	int getY(){
		return y - BORDER - BORDER;
	}
	int getLength(){
		return length;
	}
	void moveLeft(){
		if(x > 1){
			if(speed > 0) speed = 0;
			if(speed > -50) speed -= 1;
			x -= (-speed / 10 + 1);
		}
	}
	void moveRight(XInfo & xInfo){
		if(x + length < xInfo.width){
			if(speed < 0) speed = 0;
			if(speed < 50) speed += 1;	
			x += speed / 10 + 1;
		}
	}
};

void drawBlock(Block& block);
void handleAnimation();
void initBlock(int number, bool, int, bool);
void initBall(int speed);
void initPaddle();
void initX(int argc, char* argv[]);
void initBoard();
bool repaint();
void paddleMoveLeft();
void paddleMoveRight();
void handleMotion(int x);
int moveNumber();
void handleResize( XEvent &event);
void updateBall(int prevWidth, int prevHeight);
void initSplashScreen(int);
#endif
