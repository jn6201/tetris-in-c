#include"main.h"
int ifgame=0;
// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("Tetris");
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();

	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
            

	// 打开控制台，方便输出变量信息，便于调试
	// InitConsole(); 

}

#if defined(DEMO_MENU)
// 菜单演示程序
void drawMenu()
{ 
	static char * menuListFile[] = {"File",  
		"Start | Ctrl-O", 
		"Show ranking | Ctrl-R",
		"Save | Ctrl-S",
		"Exit | Ctrl-E"};
	static char * menuListTool[] = {"Tool",
		"Pause | Ctrl-P",
		"Speed-up | Ctrl->",
		"Speed-down | Ctrl-<"};
	static char * menuListHelp[] = {"Help",
		"Help | Ctrl-H",
		"About"};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListTool[3])*1.2;
	double xindent = winheight/20; // 缩进
	int    selection;
	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection>0 ) selectedLabel = menuListFile[selection];
//	if( selection==1 ) Start_game();  //开始游戏 
//	if( selection==2 ) ShowRanking(); //显示排行榜 
//	if( selection==3 ) Save_game();     //保存游戏 
	if( selection==4 ) exit(-1); // choose to exit
	
	// Tool 菜单
//	menuListTool[1] =(g_gamestate!=Playing)? "Start  | Ctrl-P":"Pause  | Ctrl-P";
	selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
	if( selection>0 ) selectedLabel = menuListTool[selection];
	if( selection==1 ){ if(ifgame==1)  Pause_game();  //暂停游戏 
						else if(ifgame==2)   Resume_game();//恢复游戏 
						else if(ifgame==0)   Start_game();//开始游戏 
						} 
	if( selection==2 )  
	if( selection==3 )  
	
	// Help 菜单
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection>0 ) selectedLabel = menuListHelp[selection];
//	if( selection==1 ) ShowHelp();    //显示操作按键介绍 
//	if( selection==2 ) ShowAbout();   //关于 
	}
#endif // #if defined(DEMO_MENU)

#if defined(DEMO_BUTTON)
// 按钮演示程序
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double x = winwidth/3.5;  
	double y = winheight/2+3*h; 
	double w = winwidth/5; // 控件宽度
	
	if( button(GenUIID(0), x, y, w*2, h*2, "新游戏") )   //新游戏按钮 
		{	
			MAINGAME();
		}
		
	if( button(GenUIID(0), x, y-3*h, w*2, h*2, "读取存档") )  //读取存档按钮 
		{	
//			ReadArchiving(); 
		}
		
	if( button(GenUIID(0), x, y-6*h, w*2, h*2, "排行榜") )  //排行榜按钮 
		{	
			ranking_list();
		}
		
	if( button(GenUIID(0), x, y-9*h, w*2, h*2, "退出") )  //退出游戏 
		{	
			exit(-1);
		}
}
#endif

void display()
{
	// 清屏
	DisplayClear();
	// 绘制和处理菜单
	drawMenu();
	// 按钮
	drawButtons();
	// 将绘制的结果put到屏幕上
	//UpdateDisplay();
} 
