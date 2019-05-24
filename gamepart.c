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
int block[12][22];//初始化为0代表空白，，1，2，3，4，5，6，7，代表不同颜色
int newblock;//用于存储下一个方块的a类型
int indexx,indexy;//储存当前指示格
int indexa,indexb;//储存当前指示类型


void KeyboardEventProcess(int key, int event);
void TimerEventProcess(int timerID);/*¶¨Ê±Æ÷ÏûÏ¢»Øµ÷º¯Êý*/
void prefunction(){
	for(int i=0;i<12;i++){
		for(int j=0;j<22;j++){
			if(i==0||i==11||j==0||j==21)block[i][j]=-10;
		}
	}
}

void BlockMove(int direction){
	switch(direction){
		case -1:if(isblock(indexa,indexb,indexx-1,indexy)==1){
			indexx--;
			clean();
			drawblock(indexa,indexb,indexx,indexy);
		}break;
		case 1:if(isblock(indexa,indexb,indexx+1,indexy)==1){
			indexx++;
			clean();
			drawblock(indexa,indexb,indexx,indexy);
		}break; 
		case 0: if(isblock(indexa,indexb,indexx,indexy-1)==1){
			indexy--;
			clean();
			drawblock(indexa,indexb,indexx,indexy);
		}break;
	}
}
int isblock(int a,int b,int x,int y){
	if(block[x][y]!=0)return 0;
	switch(a){
		case 1: if(block[x][y-1]!=0||block[x-1][y]!=0||block[x-1][y-1]!=0)return 0;
				break;
		case 2: switch(b){
			case 0:case 2: if(block[x][y+1]!=0||block[x+1][y]!=0||block[x+1][y-1]!=0)return 0;
				break;
			case 1:case 3: if(block[x][y-1]!=0||block[x-1][y-1]!=0||block[x+1][y]!=0)return 0;
				break;
		}break;
		case 3: switch(b){
			case 0:case 2: if(block[x-1][y]!=0||block[x][y+1]!=0||block[x-1][y-1]!=0)return 0;
				break;
			case 1:case 3: if(block[x-1][y]!=0||block[x][y-1]!=0||block[x+1][y-1]!=0)return 0;
				break;
		}break;
		case 4: switch(b){
			case 0:case 2: if(block[x][y+1]!=0||block[x][y-1]!=0||block[x][y-2]!=0)return 0;
				break;
			case 1:case 3: if(block[x+1][y]!=0||block[x-1][y]!=0||block[x-2][y]!=0)return 0;
				break;
		}break;
		case 5: switch(b){
			case 0: if(block[x-1][y]!=0||block[x+1][y]!=0||block[x+2][y]!=0)return 0;
				break;
			case 1: if(block[x][y-1]!=0||block[x-1][y]!=0||block[x][y-2]!=0)return 0;
				break;
			case 2: if(block[x][y-1]!=0||block[x-1][y-1]!=0||block[x-2][y-1]!=0)return 0;
				break;
			case 3: if(block[x][y+1]!=0||block[x][y-1]!=0||block[x+1][y-1]!=0)return 0;
				break;
		}
		case 6: switch(b){
			case 0: if(block[x+1][y]!=0||block[x-1][y]!=0||block[x-1][y+1]!=0)return 0;
				break;
			case 1: if(block[x][y-1]!=0||block[x][y+1]!=0||block[x+1][y+1]!=0)return 0;
				break;
			case 2: if(block[x-1][y]!=0||block[x+1][y]!=0||block[x+1][y+1]!=0)return 0;
				break;
			case 3: if(block[x][y+1]!=0||block[x][y-1]!=0||block[x-1][y-1]!=0)return 0;
				break;
		}break;
		case 7: switch(b){
			case 0: if(block[x-1][y]!=0||block[x+1][y]!=0||block[x][y+1]!=0)return 0;
				break;
			case 1: if(block[x+1][y]!=0||block[x][y+1]!=0||block[x][y-1]!=0)return 0;
				break;
			case 2: if(block[x][y-1]!=0||block[x+1][y]!=0||block[x-1][y]!=0)return 0;
				break;
			case 3: if(block[x-1][y]!=0||block[x][y+1]!=0||block[x][y-1]!=0)return 0;
				break;
		}break;
	}
	return 1;
}
void clean(){
	for(int i=0;i<12;i++){
		for(int j=0;j<22;j++){
			if(block[i][j]>0)block[i][j]=0;
		}
	}
}
void drawblock(int a,int b,int x,int y){//前提是isblock=1
	switch(a){
		case 1: block[x][y-1]=block[x-1][y]=block[x-1][y-1]=block[x][y]=1;
				break;
		case 2: switch(b){
			case 0: block[x][y+1]=block[x+1][y]=block[x+1][y-1]=block[x][y]=2;
				break;
			case 1: block[x][y-1]=block[x-1][y-1]=block[x+1][y]=block[x][y]=2;
				break;
		}break;
		case 3: switch(b){
			case 0: block[x-1][y]=block[x][y+1]=block[x-1][y-1]=block[x][y]=3;
				break;
			case 1: block[x-1][y]=block[x][y-1]=block[x+1][y-1]=block[x][y]=3;
				break;
		}break;
		case 4: switch(b){
			case 0: block[x][y+1]=block[x][y-1]=block[x][y-2]=block[x][y]=4;
				break;
			case 1: block[x+1][y]=block[x-1][y]=block[x-2][y]=block[x][y]=4;
				break;
		}break;
		case 5: switch(b){
			case 0: block[x-1][y]=block[x+1][y]=block[x+2][y]=block[x][y]=5;
				break;
			case 1: block[x][y-1]=block[x-1][y]=block[x][y-2]=block[x][y]=5;
				break;
			case 2: block[x][y-1]=block[x-1][y-1]=block[x-2][y-1]=block[x][y]=5;
				break;
			case 3: block[x][y+1]=block[x][y-1]=block[x+1][y-1]=block[x][y]=5;
				break;
		}break;
		case 6: switch(b){
			case 0: block[x+1][y]=block[x-1][y]=block[x-1][y+1]=block[x][y]=6;
				break;
			case 1: block[x][y-1]=block[x][y+1]=block[x+1][y+1]=block[x][y]=6;
				break;
			case 2: block[x-1][y]=block[x+1][y]=block[x+1][y+1]=block[x][y]=6;
				break;
			case 3: block[x][y+1]=block[x][y-1]=block[x-1][y-1]=block[x][y]=6;
				break;
		}break;
		case 7: switch(b){
			case 0: block[x-1][y]=block[x+1][y]=block[x][y+1]=block[x][y]=7;
				break;
			case 1: block[x+1][y]=block[x][y+1]=block[x][y-1]=block[x][y]=7;
				break;
			case 2: block[x][y-1]=block[x+1][y]=block[x-1][y]=block[x][y]=7;
				break;
			case 3: block[x-1][y]=block[x][y+1]=block[x][y-1]=block[x][y]=7;
				break;
		}break;
	}

}


void BlockInit(){
	srand((int)time(0)); 
	int t=int(rand())%7+1;
	newblock=t;
}
void blockicy(){
	for(int i=0;i<11;i++){
		for(int j=0;j<21;j++){
			if(block[i][j]>0)block[i][j]=-block[i][j];
		}
	}
}
void blcokdecline(){
int falg=1,i,j,m,n;
for(j=1;j<21;j++){
	falg=1;
	for(i=1;i<11;i++)if(block[i][j]==0)flag=0;
	if(flag==1){
		for(m=j;m<21;m++){
			for(n=1;n<11;n++){
				block[n][m]=block[n][m+1];
			}
			}
		}
	}
}
void finaldraw(){
	DisplayClear();
	for(int i=0;i<12;i++){
		for(int j=0;j<22;j++){
			switch (block[i][j]){
				case -10:SetPenColor('Black');break;
				case -1:SetPenColor('Blue');break;
				case 1:SetPenColor('Blue');break;
				case -2:SetPenColor('Green');break;
				case 2:SetPenColor('Green');break;
				case -3:SetPenColor('Red');break;
				case 3:SetPenColor('Red');break;
				case -4:SetPenColor('Orange');break;
				case 4:SetPenColor('Orange');break;
				case -5:SetPenColor('Yellow');break;
				case 5:SetPenColor('Yellow');break;
				case -6:SetPenColor('Brown');break;
				case 6:SetPenColor('Brown');break;
				case -7:SetPenColor('Cyan');break;
				case 7:SetPenColor('Cyan');break;
				case 0:SetPenColor('White');break;
				
			}
			drawRectangle(i*xiangsu+1,j*xiangsu+1,xiangsu,xiangsu,1);
		}
	}
}
void display(){
	DisplayClear();
	if(isblock(indexa,indexb,indexx,indexy)==1){
		clean();
		drawblock(indexa,indexb,indexx,indexy);
	}
	if(isblock(indexa,indexb,index))
}
void MAINGAME(){
	prefunction();
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
			     case VK_SPACE:
			 		indexb=(indexb+1)%4;
			 		if(isblock(indexa,indexb,indexx,indexy)==1){
			 			clean();
			 			drawblock(indexa,indexb,indexx,indexy);
			 			DisplayClear();
			 			finaldraw();
			 		}
                     break;
			     case VK_DOWN:

                     break;
			     case VK_LEFT:
			         indexx--;
			         display();
                     break;
			     case VK_RIGHT:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccx += deltax;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
                 default:break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}

void TimerEventProcess(int timerID)
{
      
	  
}





/*void DrawBlock(int a,int b,int x,int y){
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
			break;
	case 2: SetPenColor("Red");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
					}
	case 3: SetPenColor("Green");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-2)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						break;
					}
			break;
	case 4: SetPenColor("Brown");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 2: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-2)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 3: drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;			
					}
		break;
		case 5: SetPenColor("Orange");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 2: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-2)*xiangsu,(y1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 3: drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x)*xiangsu,(y)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x)*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						break;			
					}
		break;
		case 6: SetPenColor("Cyan");
			switch(b): {
				case 0:	drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 1: drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 2: drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-2)*xiangsu,(y)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				case 3: drawRectangle((x)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x)*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						break;			
					}
		break;					
		}
}
void DrawMap(){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			DrawBox(1+i*xiangsu,1+j*xiangsu,xiangsu,xiangsu);
		}
	}
}*/
