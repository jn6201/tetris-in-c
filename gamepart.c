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

#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#define TIMER_BLINK1000 2     /*1000ms定时器时间标志号*/


void KeyboardEventProcess(int key, int event);
void TimerEventProcess(int timerID);/*定时器消息回调函数*/

void MAINGAME(){
	registerKeyboardEvent(KeyboardEventProcess);/*注册键盘消息回调函数*/
	registerTimerEvent(TimerEventProcess);/*注册定时器消息回调函数*/
	startTimer(TIMER_BLINK500, mseconds500);/*500ms定时器触发*/
    startTimer(TIMER_BLINK1000, mseconds1000);/*1000ms定时器触发*/
} 

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
		switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_SPACE:/*旋转*/

                     break;
			     case VK_DOWN:

                     break;
			     case VK_LEFT:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccx -= deltax;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_RIGHT:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccx += deltax;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_P://暂停// 
  					 SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
		 	         SetPenSize(GetPenSize()+1);
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 break;

                     break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
	display(); // 刷新显示
}

void TimerEventProcess(int timerID)
{
      bool erasemode;

	  switch (timerID) {
	    case TIMER_BLINK500: /*500ms光标闪烁定时器*/
	      erasemode = GetEraseMode();
		  SetEraseMode(isDisplayCircle);
          DrawCenteredCircle(ccx, ccy, radius);
	      SetEraseMode(erasemode);
		  isDisplayCircle = !isDisplayCircle;
		  break;
	    case TIMER_BLINK1000: /*1000ms光标闪烁定时器*/
	      erasemode = GetEraseMode();
		  SetEraseMode(isDisplayCircle2);
          DrawCenteredCircle(ccx, ccy, radius*2);
	      SetEraseMode(erasemode);
		  isDisplayCircle2 = !isDisplayCircle2;
		  break;
	    default:
		  break;
	  }
}

void display()
{
	// 清屏
	DisplayClear();

#if defined(DEMO_MENU)
	// 绘制和处理菜单
	drawMenu();
#endif

#if defined(DEMO_ROTATE)
	// 旋转的三角形
	drawRotateTriangle();
#endif
			
#if defined(DEMO_BUTTON)
	// 按钮
	drawButtons();
#endif

#if defined(DEMO_EDITBOX)
	// 编辑文本字符串
	drawEditText();
#endif
}
