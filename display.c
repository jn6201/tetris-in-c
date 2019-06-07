#include "main.h"
extern int block[12][22];
extern double winwidth, winheight,FontSize;
extern int isgame,score,ms;
extern char FooterStr[30];
extern char DiffcultyStr[10];
extern enum gstates mainstate;
extern int block[12][22];
extern int newblock;
extern int start;
extern struct person persons[100];
int num=0; 

#if defined(DEMO_MENU)
// 菜单演示程序
void drawMenu()
{
	SetPointSize(FontSize);
	static char * menuListFile[] = {"File",  
		"Start | Ctrl-O", 
		"Show ranking | Ctrl-R",
		"Save | Ctrl-S",
		"Exit | Ctrl-E"};
	static char * menuListTool[] = {"Tool",
		"Pause | Ctrl-P",
		"Speed-up | Ctrl-F",
		"Speed-down | Ctrl-D"};
	static char * menuListOthers[] = {"Others",
		"Help | Ctrl-H",
		"About | Ctrl-A"};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListOthers[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListTool[3])*1.2;
	double xindent = winheight/20; // 缩进
	int    selection;
	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection>0 ) selectedLabel = menuListFile[selection];
	if( selection==1 ) MAINGAME();  //开始游戏 
	if( selection==2 ) mainstate=showBoard; //显示排行榜 
	if( selection==3 ) MemoryArchiving();     //保存游戏 
	if( selection==4 ) exit(-1); // choose to exit
	
	// Tool 菜单
	menuListTool[1] =(isgame!=1)? "Start | Ctrl-P":"Pause | Ctrl-P";
	selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
	if( selection>0 ) selectedLabel = menuListTool[selection];
	if( selection==1 ){ if(isgame==1)  pause();  //暂停游戏 
						else if(isgame==2)   carryon();//恢复游戏 
						else if(isgame==0)   MAINGAME();//开始游戏 
						} 
	if( selection==2 ){ //加速 
		if(mainstate==Playing) faster();
		sprintf(FooterStr,"Diffculty changed to %s!",DiffcultyStr); //修改提示栏 
	}
	if( selection==3 ){ //减速 
		if(mainstate==Playing) 	slower();
		sprintf(FooterStr,"Diffculty changed to %s!",DiffcultyStr); //修改提示栏 
	}
	
	// Others 菜单
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListOthers,sizeof(menuListOthers)/sizeof(menuListOthers[0]));
	if( selection>0 ) selectedLabel = menuListOthers[selection];
	if( selection==1 ) mainstate=showHelp;    //显示操作按键介绍 
	if( selection==2 ) mainstate=showAbout;   //关于 
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
//		int i,j;
//		for(i=0;i<12;i++)
//		for(j=0;j<22;j++)
//		    memset(block[i][j], 0, sizeof(block[i][j]));
			MAINGAME();
		}
		
	if( button(GenUIID(0), x, y-3*h, w*2, h*2, "读取存档") )  //读取存档按钮 
		{	
		    
			ReadArchiving(); 
		}
		
	if( button(GenUIID(0), x, y-6*h, w*2, h*2, "排行榜") )  //排行榜按钮 
		{	
		   mainstate=showBoard;
		}
		
	if( button(GenUIID(0), x, y-9*h, w*2, h*2, "退出") )  //退出游戏 
		{	
			exit(-1);
		}
}
#endif

#if defined(DEMO_TOOLS)
// 工具按钮演示程序
void drawTools()
{
	double fH = GetPointSize();
	double h = winwidth/15;
	double x = winwidth/1.8;
	double y = winheight/4;
	double w = winwidth/15;
	double dx= winwidth/15;

	//开始按键，效果同菜单开始 
	if(button(GenUIID(0), x, y, w, h, "")) {
		if(isgame!=1) {
			if(isgame==2)  carryon();
//			else if(g_gamestate!=Cleaning)Start_game();
		}
	}

	//绘制开始图形 
	SetPenColor("Black");
	SetPenSize(3);
	MovePen(x+w/6,y+w/6);
	DrawLine(0,w*2.0/3);
	DrawLine(w*2.0/3,-w/3);
	DrawLine(-w*2.0/3,-w/3);
	SetPenSize(0);
	
	//暂停按键，效果同菜单暂停
	if(button(GenUIID(0), x+dx, y, w, h, "")) {
		if(isgame==1) pause();
	}
	//绘制暂停图形 
	SetPenColor("Black");
	SetPenSize(10);
	MovePen(x+dx+w/3,y+w/6);
	DrawLine(0,w*2.0/3);
	MovePen(x+dx+w-w/3,y+w/6);
	DrawLine(0,w*2.0/3);
	SetPenSize(0);
	
	//停止按键，效果同停止暂停
	if(button(GenUIID(0), x+2*dx, y, w, h, "")) {
//		if(g_gamestate==Playing||g_gamestate==Paused||g_gamestate==GameEnd) Stop_game();
         MemoryArchiving();
            mainstate=Welcome;
	}
	//绘制停止图形 
	SetPenColor("Black");
	SetPenSize(22);
	MovePen(x+2*dx+w/3,y+w/3);
	DrawLine(0,w/3);
	DrawLine(w/3,0);
	DrawLine(0,-w/3);
	DrawLine(-w/3,0);
	SetPenSize(0);
	
	//减速按键
	if(button(GenUIID(0), x, y-dx, w, h, "")) {
		if(mainstate==Playing) {
			slower();
		}
		sprintf(FooterStr,"Diffculty changed to %s!",DiffcultyStr); //修改提示栏 
	}
	
	//绘制减速图形 
	SetPenColor("Black");
	SetPenSize(3);
	MovePen(x+w-w/3,y-dx+w/6);
	DrawLine(0,w*2.0/3);
	DrawLine(-w/2,-w/3);
	DrawLine(w/2,-w/3);
	MovePen(x+w-w/6,y-dx+w/6);
	DrawLine(0,w*2.0/3);
	DrawLine(-w/2,-w/3);
	DrawLine(w/2,-w/3);
	SetPenSize(0);
	
	//加速按键
	if(button(GenUIID(0), x+2*dx, y-dx, w, h, "")) {
		if(mainstate==Playing) {
			faster();
		}
		sprintf(FooterStr,"Diffculty changed to %s!",DiffcultyStr); //修改提示栏 
	}
	//绘制加速图形 
	SetPenColor("Black");
	SetPenSize(3);
	MovePen(x+2*dx+w/3,y-dx+w/6);
	DrawLine(0,w*2.0/3);
	DrawLine(+w/2,-w/3);
	DrawLine(-w/2,-w/3);
	MovePen(x+2*dx+w/6,y-dx+w/6);
	DrawLine(0,w*2.0/3);
	DrawLine(+w/2,-w/3);
	DrawLine(-w/2,-w/3);
	SetPenSize(0);
	
	//绘制下一个图形 
	SetPenColor("White");
	drawRectangle(x/1.25,y*2.58,w*1.5, w*1.5, TRUE);
	SetPenColor("Black");
	SetPenSize(3);
	drawLabel(x/1.24, y*3, "Next :"); //绘制 "Next"
	MovePen(x/1.25,y*2.58);
	DrawLine(w*1.5,0);
	DrawLine(0,w*1.5);
	DrawLine(-w*1.5,0);
	DrawLine(0,-w*1.5); 
	
	
	//绘制分数栏 
	SetPointSize(fH*3);
	char scoretext[10];
	itoa(score*100,scoretext,10);
	drawLabel( x*1.2, y*3, "Score :");
	drawLabel( x*1.2, y*2.7, scoretext);
	
	switch(ms) { //根据速度修改难度文字 
			case 250:
				strcpy(DiffcultyStr,"INSANE");
				break;
			case 300:
				strcpy(DiffcultyStr,"HARD");
				break;
			case 350:
				strcpy(DiffcultyStr,"NORMAL");
				break;
			case 400:
				strcpy(DiffcultyStr,"EASY");
				break;
		}
	
	//绘制难度
	SetPointSize(fH*3);
	drawLabel( x*1.2, y*2.3,"Diffculty:");
	if(ms==400) SetPenColor("Green");
	if(ms==350) SetPenColor("Cyan");
	if(ms==300) SetPenColor("Orange");
	if(ms==250) SetPenColor("Red");
	drawLabel( x*1.2, y*2.0, DiffcultyStr);
	
	//绘制退出按钮
	SetPointSize(fH);
	if( button(GenUIID(0), winwidth/1.2, winheight/10,GetFontHeight()*3,GetFontHeight()*1.5, "退出") )   //退出按钮 
		{
			exit(0);
            
            
		}
}
#endif

//绘制底部状态栏
void DrawFooter() {
	double Font_Height = GetFontHeight();
	double Start_x = Font_Height/3.0; //左对齐起点
	double Footer_Height = Font_Height*1.5; //底栏高度
	SetPenSize(1);
	SetPenColor("LightGray");
	drawRectangle(0, 0, winwidth, Footer_Height, TRUE);
	SetPenColor("Black");
	drawLabel(Start_x, Font_Height*0.45, FooterStr);	 
}

	
void display()
{
	// 清屏
	DisplayClear();
	SetPenColor("Cream");
	drawRectangle(0, 0, winwidth, winheight, TRUE);
	// 绘制和处理菜单
	drawMenu();
	//绘制底栏 
	DrawFooter();
	// 按钮
    if(mainstate==Welcome) drawButtons();
	// 将绘制的结果put到屏幕上
	//UpdateDisplay();
	if(mainstate==Playing){
			
		drawTools();
		finaldraw(); 	
	}
	if(mainstate==Normalstate){
			drawTools();
		finaldraw(); 
		
   	    Start_game();
	}
//	if(mainstate==Normalstate){
//		startdraw;
//	}
	if(mainstate==showAbout) ShowAbout();
	if(mainstate==showHelp) ShowHelp();
	if(mainstate==changeUser)
	{	
		memoryscore();
		num++;
	}
	if(mainstate==showBoard) ranking_list();	
} 
