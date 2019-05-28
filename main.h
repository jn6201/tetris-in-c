#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"

#define DEMO_MENU
#define DEMO_BUTTON
#define DEMO_ROTATE
#define DEMO_EDITBOX

static double winwidth, winheight;   // 窗口尺寸
static int    show_more_buttons = 0; // 显示更多按钮

// 清屏函数，provided in libgraphics
void DisplayClear(void); 
// 计时器启动函数，provided in libgraphics
void startTimer(int id,int timeinterval);

// 用户的显示函数
void display(void); 

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}

//游戏操作函数 
void Start_game();   //开始游戏 
void ranking_list();//显示排行榜 
void ReadArchiving();//读取存档 
void Save_game();//保存游戏 
void Pause_game();//暂停游戏 
void Resume_game();//恢复游戏 
 
void ShowHelp();//显示帮助 
void ShowHAbout();//显示关于 

void KeyboardEventProcess1(int key, int event);
void TimerEventProcess(int timerID);
void prefunction();//预处理，每次刷新时第一步注册黑色边框
void BlockMove(int direction);//把当前活动方块移动一格
int isblock(int a,int b,int x,int y);//判断xy中心位置能否放下 一个ab型方块
void clean();//清除当前活动方块
void drawblock(int a,int b,int x,int y);//在xy中心位置绘制一个ab型方块
int BlockInit();//随机生成下一个方块的a型
void blockicy();//冻结当前活动方块
void blcokdecline();//消灭满的行
void finaldraw();//将数组形式最终编程图案
void pause();//暂停 
void carryon();//继续 
int block[12][22];//初始化为0代表空白，，1，2，3，4，5，6，7，代表不同颜色
int newblock;//用于存储下一个方块的a类型
int indexx,indexy;//储存当前指示格
int indexa,indexb;//储存当前指示类型
int ms;//储存时间间隔
int score;//
int isgame;//0表示结束，1表示进行中，2表示暂停 
