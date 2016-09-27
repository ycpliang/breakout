name: Yi Chao Peter Liang
userId: ycpliang
student #: 20433663

program files : a1.cpp drawing.h drawing.cpp MakeFile
'make' to build and './a1' to execute

key and mouse input
<- left arrow key and -> right arrow key to move the paddle 'qq' key to quit when in game.
move left and right on mouse to control paddle.

command-line input
the program accepts 0, 1, 2, 3, 4 number of parameters.
sample : ./a1 30 6 1 5
./a1 
30(frames per second) 
6(speed of the ball) 
1(whether or not all balls need only one hit to destroy (0 = Normal mode) 1 or greater = One hit Destroy ) 
5(normally each line of block has a random color, 5 ensures 
all blocks are Purple (0 = Random, 1 = Green, 2 = Red, 3 = yellow, 4 = pink, 5 = Purple, 6 = Cyan, 7 = Grey)

Extra Features
1. Blocks are assigned life at the beginning of the game. Green, red, yellow, pink only require one hit to be destroyed.
Purple need two hits to be destroyed; after one hit, it will become a pink block and will still appear on board.
Cyan need three hits (Cyan -> Purple -> Pink), and Grey needs 4 hits (Grey -> Cyan -> Purple -> Pink).

2. When You fully eliminate a Grey Block, as in (Grey -> Cyan -> Purple -> Pink -> Nothing), you are awarded with an extra
ball. As this is hard to test a hack is implemented and can be actived at the beginning of the game.
./a1 30 5 1 7
this will guarentee that all blocks are grey and it only takes one hit to fully destroy grey blocks, and thus awarding
duplicate balls.

3.When the ball bounces on the paddle, depending on where you bounce on the paddle it will go at a different angle.
This is calculated based on an sin function, and the xVelocity and yVelocity adjusted accordingly.
The radian that can be generated is (-1.2 < arcsin(x/length) < -0.3 and  0.3 < arcsin(x/length) < 1.2 ) 
which ranges from -108 degrees to - 30 degrees and 30 degrees to 108 degrees.
Hitting directly in the center will generate the most perpendicular(to the paddle) angle. 
Hitting on the most left will make the ball go at the most negative angle.
Hitting on the most right will make the ball go at the most positive angle. 

Scoring
hitting the paddle awards you 1 point and hitting the block will award you with 1 = Green, 2 = Red, 3 = yellow, 
4 = pink, 5 = Purple, 6 = Cyan, 7 = Grey.

ENJOY :)
