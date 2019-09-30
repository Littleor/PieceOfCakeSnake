#include <ncurses.h>
#include <stdlib.h>
#include <time.h> 
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

typedef struct spart {
    int x;
    int y;
} snakeypart;

enum direction { UP, DOWN, RIGHT, LEFT };//
WINDOW *snakeys_world;//定义贪吃蛇窗口
int SnakeLength = 5;//蛇的长度,初为4
int Score = 0;//成绩分数
snakeypart snakey[120];//设置蛇儿的坐标地址--没有使用链表
snakeypart food;
snakeypart tem;
int direction = RIGHT;//蛇的方向
int ch;//获取输入内容
int speed = 400;


void Initialization(void);//初始化函数
void WaitGame(void);
void Game(void);
void GameOver(void);
void CreateSnake(void);
bool RandomFood(void);


int main(){
	
	Initialization();
	WaitGame();
	Game();
 	return 0;
}
/*
 *	函数作用:初始化屏幕
 *	函数参数:无
 *	函数返回值:无/
 */
void Initialization(void){
   	initscr();//初始化屏幕
    noecho();//设置没有回显
    cbreak();//禁止行缓冲区
    timeout(speed);//设置运动间隔时间
    keypad(stdscr, TRUE);//识别用户的功能键，即F1、F2等这些键，代码中可以获得用户的这些按键
	int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
	snakeys_world = newwin(WORLD_HEIGHT, WORLD_WIDTH,offsety,offsetx);//创建窗口--newwin(高,宽,离上顶的高度,离左边的距离)
	
 	 	
}
/*
 *	函数作用:等待开始游戏界面
 *	函数参数:无
 *	函数返回值:无/
 */
void WaitGame(void){
 	int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
    int i = 1,n = 0; 
    while ((ch = getch()) != 'b') {
    	wclear(snakeys_world);
    	mvprintw(offsety+WORLD_HEIGHT/2-5,offsetx+16, "PieceOfCakeSnake");
 	 	mvprintw(offsety+WORLD_HEIGHT/2-1,offsetx+i, "Please enter 'B' to start");
 	 	mvprintw(1,offsetx+WORLD_HEIGHT/2+10, "Score: %d",Score);
 	 	mvprintw(WORLD_HEIGHT-3,offsetx+5, "Copyright © Littleor ALL right reserverd");
 	 	
 	 	box(snakeys_world, 0 , 0);
 	 	wrefresh(snakeys_world);
 	 	if(offsetx+i<WORLD_WIDTH-12&&n%2==0){
 	 		i++;
 	 	}
 	 	else if(i>1&&n%2!=0){
 	 		i--;
 	 	}
 	 	else if(offsetx+i>=WORLD_WIDTH/2||i<=1){
 	 		n++;
 	 	}
 	 	else{
 	 	}
 	}
}

/*
 *	函数作用:创建一条蛇
 *	函数参数:无
 *	函数返回值:无/
 */

void CreateSnake(void){
	int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
    wclear(snakeys_world);
    for(int i = 0;i < SnakeLength;i++){
    	snakey[i].x = offsetx+10-i;
    	snakey[i].y = offsety;
    }
 	mvwaddch(snakeys_world, snakey[0].y, snakey[0].x, '0');//在指定位置输出蛇头
 	for(int i = 1;i < SnakeLength;i++){
    mvwaddch(snakeys_world, snakey[i].y, snakey[i].x, '#');//在指定位置输出蛇身
 	}
 	mvprintw(1,offsetx+WORLD_HEIGHT/2+10, "Score: %d",Score);
 	box(snakeys_world,0,0);
 	wrefresh(snakeys_world);
}
/*
 *	函数作用:生成食物
 *	函数参数:无
 *	函数返回值:bool
 */
bool RandomFood(void){
	srand(time(NULL)); 
	int food_y = (rand() % (WORLD_HEIGHT-1));
	int food_x = (rand() % (WORLD_WIDTH-1));
	int n = 0;
	for(int i = 0;i<SnakeLength;i++ ){
		if(snakey[i].x == food_x && snakey[i].y == food_y){
			return false;
		}
		else if(food_y == 0 ||food_x == 0){
			return false;
		}
	}
	
		food.y = food_y;
		food.x = food_x;
		return true;
	
}
/*
 *	函数作用:切换蛇的方向
 *	函数参数:无
 *	函数返回值:无
 */
 void GetDir(void){

 	if(ch != ERR) {
            switch(ch) {
                case KEY_UP:
                    direction = (direction == DOWN)?DOWN:UP;
                    break;
                case KEY_DOWN:
                    direction = (direction == UP)?UP:DOWN;
                    break;
                case KEY_RIGHT:
                    direction = (direction == LEFT)?LEFT:RIGHT;
                    break;
                case KEY_LEFT:
                    direction = (direction == RIGHT)?RIGHT:LEFT;
                    break;
                default:
                    break;
            }
 
        }
 }
/*
 *	函数作用:移动蛇头
 *	函数参数:无
 *	函数返回值:无
 */
void MoveHead(void){
	
	switch (direction) {
    	//控制头部的移动方向
        case UP:
            (snakey[0].y - 1 == 0) ? snakey[0].y = WORLD_HEIGHT - 2 : snakey[0].y--;
            break;
        case DOWN:
            (snakey[0].y + 1 == WORLD_HEIGHT - 1 )? snakey[0].y = 1 : snakey[0].y++;
            break;
        case RIGHT:
            (snakey[0].x + 1 == WORLD_WIDTH - 1 )? snakey[0].x = 1 : snakey[0].x++;
            break;
        case LEFT:
            (snakey[0].x - 1 == 0 )? snakey[0].x = WORLD_WIDTH - 2 : snakey[0].x--;
            break;
        default:
            break;
    }
    for(int i = 1;i<SnakeLength;i++){
    	if(snakey[0].x == snakey[i].x && snakey[0].y == snakey[i].y){
    		GameOver();
    	}
    }
    if(snakey[0].y == food.y && snakey[0].x == food.x){
    	snakey[SnakeLength].x = tem.x;
    	snakey[SnakeLength].y = tem.y;
    	SnakeLength++;
    	Score++;
    	speed = speed - Score;
    	if(speed <= 50){
    		speed = 50;
    	}
    	while(!RandomFood());
    	timeout(speed);//设置运动间隔时间
    }
    mvwaddch(snakeys_world,food.y,food.x,'x');//在指定位置输出食物
 	mvwaddch(snakeys_world, snakey[0].y, snakey[0].x, '0');//在指定位置输出蛇头	
}
/*
 *	函数作用:移动蛇身
 *	函数参数:无
 *	函数返回值:无
 */
void Move(void){
	tem.y =snakey[SnakeLength-1].y;
	tem.x =snakey[SnakeLength-1].x;
	for(int i=SnakeLength-1;i>0;i--){
		snakey[i].x = snakey[i-1].x;
		snakey[i].y = snakey[i-1].y;
		mvwaddch(snakeys_world, snakey[i].y, snakey[i].x, '#');//在指定位置输出蛇身
	}
}
/*
 *	函数作用:游戏中
 *	函数参数:无
 *	函数返回值:无
 */
void Game(void){
	int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
	CreateSnake();
	while(!RandomFood());
	while ((ch = getch()) != 'x') {
		wclear(snakeys_world);
		GetDir();//获取蛇的方向
		Move();//移动蛇身
		MoveHead();//修改蛇头位置
 	 	mvprintw(1,offsetx+WORLD_HEIGHT/2+10, "Score: %d ",Score);
 	 	box(snakeys_world, 0 , 0);
 	 	wrefresh(snakeys_world);
	}


}

void GameOver(void){
		int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
    int i = 1,n = 0; 
    while ((ch = getch()) != 'q') {
    	wclear(snakeys_world);
    	mvprintw(offsety+WORLD_HEIGHT/2-5,offsetx+WORLD_WIDTH/2-5, "GameOver");
    	mvprintw(offsety+WORLD_HEIGHT/2-4,offsetx+WORLD_WIDTH/2-8, "YourScore is %d",Score);
 	 	mvprintw(offsety+WORLD_HEIGHT/2-1,offsetx+i, "Please enter 'q' to quit");
 	 	mvprintw(WORLD_HEIGHT-3,offsetx+5, "Copyright © Littleor ALL right reserverd");
 	 	box(snakeys_world, 0 , 0);
 	 	wrefresh(snakeys_world);
 	 	if(offsetx+i<WORLD_WIDTH-12&&n%2==0){
 	 		i++;
 	 	}
 	 	else if(i>1&&n%2!=0){
 	 		i--;
 	 	}
 	 	else if(offsetx+i>=WORLD_WIDTH/2||i<=1){
 	 		n++;
 	 	}
 	 	else{
 	 	}
 	}
	delwin(snakeys_world);
    endwin();
}