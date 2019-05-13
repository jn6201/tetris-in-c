#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include<time.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define TIMER_BLINK500  1     /*500ms¶¨Ê±Æ÷ÊÂ¼þ±êÖ¾ºÅ*/
#define TIMER_BLINK1000 2     /*1000ms¶¨Ê±Æ÷Ê±¼ä±êÖ¾ºÅ*/
#define xiangsu 0.2


void KeyboardEventProcess(int key, int event);
void TimerEventProcess(int timerID);/*¶¨Ê±Æ÷ÏûÏ¢»Øµ÷º¯Êý*/

void BlockMove(int direction);
void FillaBlock(int x,int y,int color);
void DrawBlock(int a,int b,int x,int y){
switch(a){
	case 0: SetPenColor("Blue");
			drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
			drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			break;
	case 1: SetPenColor("Yellow");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
					}
	case 2: SetPenColor("Red");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						break;
					}

		}
}
void DrawMap(){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			DrawBox(1+i*xiangsu,1+j*xiangsu,xiangsu,xiangsu);
		}
	}
}

void BlockInit(){
	srand((int)time(0)); 
	int t=int(rand())%7;
	DrawBlock(t,0,4,19);
}

void MAINGAME(){
	registerKeyboardEvent(KeyboardEventProcess);/*×¢²á¼üÅÌÏûÏ¢»Øµ÷º¯Êý*/
	registerTimerEvent(TimerEventProcess);/*×¢²á¶¨Ê±Æ÷ÏûÏ¢»Øµ÷º¯Êý*/
	startTimer(TIMER_BLINK500, mseconds500);/*500ms¶¨Ê±Æ÷´¥·¢*/
    startTimer(TIMER_BLINK1000, mseconds1000);/*1000ms¶¨Ê±Æ÷´¥·¢*/
} 

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI»ñÈ¡¼üÅÌ
		switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_SPACE:/*Ðý×ª*/

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
			     case VK_P://ÔÝÍ£// 
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
	display(); // Ë¢ÐÂÏÔÊ¾
}

void TimerEventProcess(int timerID)
{
      bool erasemode;

	  switch (timerID) {
	    case TIMER_BLINK500: /*500ms¹â±êÉÁË¸¶¨Ê±Æ÷*/
	      erasemode = GetEraseMode();
		  SetEraseMode(isDisplayCircle);
          DrawCenteredCircle(ccx, ccy, radius);
	      SetEraseMode(erasemode);
		  isDisplayCircle = !isDisplayCircle;
		  break;
	    case TIMER_BLINK1000: /*1000ms¹â±êÉÁË¸¶¨Ê±Æ÷*/
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
	// ÇåÆÁ
	DisplayClear();

#if defined(DEMO_MENU)
	// »æÖÆºÍ´¦Àí²Ëµ¥
	drawMenu();
#endif

#if defined(DEMO_ROTATE)
	// Ðý×ªµÄÈý½ÇÐÎ
	drawRotateTriangle();
#endif
			
#if defined(DEMO_BUTTON)
	// °´Å¥
	drawButtons();
#endif

#if defined(DEMO_EDITBOX)
	// ±à¼­ÎÄ±¾×Ö·û´®
	drawEditText();
#endif
}

