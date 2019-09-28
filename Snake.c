#include <ncurses.h>
#define SPEED 200
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

typedef struct spart {
    int x;
    int y;
} snakeypart;
enum direction { UP, DOWN, RIGHT, LEFT };
WINDOW *snakeys_world;//定义贪吃蛇窗口
int snake_length = 3;


void Initialization(void);//初始化函数
void WaitGame(void);
void Game(void);
void GameOver(void);
void CreateSnake(void);


int main(){
	
	Initialization();
	WaitGame();
	Game();
	GameOver();
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
    timeout(SPEED);//设置运动间隔时间
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
 	char ch;
 	int offsetx = (COLS - WORLD_WIDTH) / 2;
    int offsety = (LINES - WORLD_HEIGHT) / 2;
    int i = 1,n = 0; 
    while ((ch = getch()) != 'b'&&(ch = getch()) != 'B') {
    	wclear(snakeys_world);
    	mvprintw(offsety+WORLD_HEIGHT/2-5,offsetx+16, "PieceOfCakeSnake");
 	 	mvprintw(offsety+WORLD_HEIGHT/2-1,offsetx+i, "Please enter 'B' to start");
 	 	mvprintw(1,offsetx+WORLD_HEIGHT/2+10, "Score: %d",i);
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
 	//mvwaddch(snakeys_world, snakey[i].y, snakey[i].x, '#');//在指定位置输出
 	box(snakeys_world,0,0);
 	wrefresh(snakeys_world);
}
/*
 *	函数作用:游戏中
 *	函数参数:无
 *	函数返回值:无/
 */
void Game(void){
	CreateSnake();
}
void GameOver(void){
	delwin(snakeys_world);
    endwin();
}