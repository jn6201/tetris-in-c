#include"main.h"
// 用户主程序入口
// 仅初始化执行一次

extern int isgame;
int start=0;
double winwidth, winheight;   // 窗口尺寸
double FontSize;  //原始字体大小
enum gstates mainstate = Welcome;
char FooterStr[30];
char DiffcultyStr[10];
struct person persons[100];
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	if(isgame==1&&(key==VK_SPACE||key==VK_DOWN||key==VK_LEFT||key==VK_RIGHT))
		KeyboardEventProcess1(key,event);
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}

static void DefineColors() { //定义颜色
	DefineColor("LightGray", 240/255.0, 240/255.0, 240/255.0);
	DefineColor("Orange", 255/255.0, 165/255.0, 0/255.0);
	DefineColor("Cream", 249/255.0, 236/255.0, 200/255.0);
	DefineColor("Melange", 210/255.0, 140/255.0, 100/255.0);
	DefineColor("LightBlue", 150/255.0, 200/255.0, 255/255.0);
}

void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("Tetris");
    InitGraphics();

	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    FontSize = GetPointSize(); //获取原始字体大小
	mainstate = Welcome;
	// 注册时间响应函数
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess); 
	DefineColors(); //定义颜色 
	setMenuColors("LightGray", "Black", "Blue", "White", TRUE); //设置菜单样式
	setButtonColors("LightBlue", "Black", "Orange", "Black", TRUE); //设置按钮样式
	setTextBoxColors("Orange", "Black", "Melange", "Black", TRUE); //设置文本框样式

	
	strcpy(FooterStr, "Welcome to Tetris!"); //初始化底栏文字
	strcpy(DiffcultyStr, "NORMAL"); //初始化难度文字
	display();
	// 打开控制台，方便输出变量信息，便于调试
	// InitConsole(); 
    int i;
	for( i=0;i<100;i++){
			memset(persons[i].name,0,20*sizeof(char));	
}
}

