#include"main.h"

#define TIMER  1     
#define xiangsu 0.2
extern int num;
extern char FooterStr[30];
extern enum gstates mainstate;

int block[12][22];//初始化为0代表空白，，1，2，3，4，5，6，7，代表不同颜色
int newblock;//用于存储下一个方块的a类型
int indexx,indexy;//储存当前指示格
int indexa,indexb;//储存当前指示类型
int ms;//储存时间间隔
int score;//
int isgame=0;//0表示结束，1表示进行中，2表示暂停 
int fuzhu=0;//这是一个辅助判断消除的变量，用于blockdecline中连续消除第一行的情况 

void prefunction(){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<22;j++){
			if(i==0||i==11||j==0||j==21)block[i][j]=-10;
		}
	}
}

int isblock(int a,int b,int x,int y){
	if(block[x][y]<0)return 0;
	switch(a){
		case 1: if(block[x][y-1]<0||block[x-1][y]<0||block[x-1][y-1]<0)return 0;
				break;
		case 2: switch(b){
			case 0:case 2: if(block[x][y+1]<0||block[x+1][y]<0||block[x+1][y-1]<0)return 0;
				break;
			case 1:case 3: if(block[x][y-1]<0||block[x-1][y-1]<0||block[x+1][y]<0)return 0;
				break;
		}break;
		case 3: switch(b){
			case 0:case 2: if(block[x-1][y]<0||block[x][y+1]<0||block[x-1][y-1]<0)return 0;
				break;
			case 1:case 3: if(block[x-1][y]<0||block[x][y-1]<0||block[x+1][y-1]<0)return 0;
				break;
		}break;
		case 4: switch(b){
			case 0:case 2: if(block[x][y+1]<0||block[x][y-1]<0||block[x][y-2]<0)return 0;
				break;
			case 1:case 3: if(block[x+1][y]<0||block[x-1][y]<0||block[x-2][y]<0)return 0;
				break;
		}break;
		case 5: switch(b){
			case 0: if(block[x+1][y]<0||block[x-1][y]<0||block[x-1][y-1]<0)return 0;
				break;
			case 1: if(block[x][y-1]<0||block[x][y+1]<0||block[x-1][y+1]<0)return 0;
				break;
			case 2: if(block[x+1][y]<0||block[x+1][y+1]<0||block[x-1][y]<0)return 0;
				break;
			case 3: if(block[x][y-1]<0||block[x+1][y-1]<0||block[x][y+1]<0)return 0;
				break;
		}break;
		case 6: switch(b){
			case 0: if(block[x+1][y]<0||block[x-1][y]<0||block[x-1][y+1]<0)return 0;
				break;
			case 1: if(block[x][y-1]<0||block[x][y+1]<0||block[x+1][y+1]<0)return 0;
				break;
			case 2: if(block[x-1][y]<0||block[x+1][y]<0||block[x+1][y-1]<0)return 0;
				break;
			case 3: if(block[x][y+1]<0||block[x][y-1]<0||block[x-1][y-1]<0)return 0;
				break;
		}break;
		case 7: switch(b){
			case 0: if(block[x-1][y]<0||block[x+1][y]<0||block[x][y+1]<0)return 0;
				break;
			case 1: if(block[x+1][y]<0||block[x][y+1]<0||block[x][y-1]<0)return 0;
				break;
			case 2: if(block[x][y-1]<0||block[x+1][y]<0||block[x-1][y]<0)return 0;
				break;
			case 3: if(block[x-1][y]<0||block[x][y+1]<0||block[x][y-1]<0)return 0;
				break;
		}break;
	}
	return 1;
}

void clean(){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<22;j++){
			if(block[i][j]>0)block[i][j]=0;
		}
	}
}

void drawblock(int a,int b,int x,int y){//前提是isblock=1
	switch(a){
		case 1: block[x][y-1]=block[x-1][y]=block[x-1][y-1]=block[x][y]=1;
				break;
		case 2: switch(b){
			case 0:case 2: block[x][y+1]=block[x+1][y]=block[x+1][y-1]=block[x][y]=2;
				break;
			case 1:case 3: block[x][y-1]=block[x-1][y-1]=block[x+1][y]=block[x][y]=2;
				break;
		}break;
		case 3: switch(b){
			case 0:case 2: block[x-1][y]=block[x][y+1]=block[x-1][y-1]=block[x][y]=3;
				break;
			case 1:case 3: block[x-1][y]=block[x][y-1]=block[x+1][y-1]=block[x][y]=3;
				break;
		}break;
		case 4: switch(b){
			case 0:case 2: block[x][y+1]=block[x][y-1]=block[x][y-2]=block[x][y]=4;
				break;
			case 1:case 3: block[x+1][y]=block[x-1][y]=block[x-2][y]=block[x][y]=4;
				break;
		}break;
		case 5: switch(b){
			case 0: block[x+1][y]=block[x-1][y]=block[x-1][y-1]=block[x][y]=5;
				break;
			case 1: block[x][y-1]=block[x][y+1]=block[x-1][y+1]=block[x][y]=5;
				break;
			case 2: block[x+1][y]=block[x+1][y+1]=block[x-1][y]=block[x][y]=5;
				break;
			case 3: block[x][y+1]=block[x][y-1]=block[x+1][y-1]=block[x][y]=5;
				break;
		}break;
		case 6: switch(b){
			case 0: block[x+1][y]=block[x-1][y]=block[x-1][y+1]=block[x][y]=6;
				break;
			case 1: block[x][y-1]=block[x][y+1]=block[x+1][y+1]=block[x][y]=6;
				break;
			case 2: block[x-1][y]=block[x+1][y]=block[x+1][y-1]=block[x][y]=6;
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

int BlockInit(){
	srand((int)time(0)); 
	int t;
	t=((int)rand())%7+1;
	return t;
}

void blockicy(){
	int i,j;
	for(i=0;i<11;i++){
		for(j=0;j<21;j++){
			if(block[i][j]>0)block[i][j]=-block[i][j];
		}
	}
}

void blockdecline(){
int flag,i,j,m,n;
for(j=1;j<21;j++){
	flag=1;
	if(fuzhu==1)j=j-1;
	for(i=1;i<11;i++)if(block[i][j]==0){
		flag=0;
		fuzhu=0;
	}
	if(flag==1){
		score++;
		for(m=j;m<20;m++){
			for(n=1;n<11;n++){
				block[n][m]=block[n][m+1];
			}
			if(j>1)j=j-1;
			fuzhu=0;
			if(j==1)fuzhu=1;
			}
		}
	}
}

void finaldraw(){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<22;j++){
			switch (block[i][j]){
				case -10:SetPenColor("Black");break;
				case -1:SetPenColor("Blue");break;
				case 1:SetPenColor("Blue");break;
				case -2:SetPenColor("Green");break;
				case 2:SetPenColor("Green");break;
				case -3:SetPenColor("Red");break;
				case 3:SetPenColor("Red");break;
				case -4:SetPenColor("Orange");break;
				case 4:SetPenColor("Orange");break;
				case -5:SetPenColor("Yellow");break;
				case 5:SetPenColor("Yellow");break;
				case -6:SetPenColor("Brown");break;
				case 6:SetPenColor("Brown");break;
				case -7:SetPenColor("Cyan");break;
				case 7:SetPenColor("Cyan");break;
				case 0:SetPenColor("White");break;
				
			}
			drawRectangle(i*xiangsu+1,j*xiangsu+1,xiangsu,xiangsu,1);
		}
	}
	int x=25,y=25;//画旁边的待命方块
	switch(newblock){
	case 1: SetPenColor("Blue");
			drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
			drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			break;
	case 2: SetPenColor("Green");
			drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
			drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
			break;
				
	case 3: SetPenColor("Red");
			drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				
	case 4: SetPenColor("Orange");
			drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y-2)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle(x*xiangsu,(y+1)*xiangsu,xiangsu,xiangsu,1);
						break;
				
	case 5: SetPenColor("Yellow");
			drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						break;
				
		case 6: SetPenColor("Brown");
			drawRectangle(x*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;
				
		case 7: SetPenColor("Cyan");
				drawRectangle(x*xiangsu,y*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x-1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						drawRectangle((x+1)*xiangsu,(y-1)*xiangsu,xiangsu,xiangsu,1);
						break;							
		}
}

void MAINGAME(){
	score=0;
	isgame=1;
	mainstate=Playing; 
	strcpy(FooterStr, "Game start!");
	prefunction();
	indexx=6;
	indexy=19;
	newblock=BlockInit();
	drawblock(BlockInit(),0,indexx,indexy);
	ms=350;//最初速度
	startTimer(TIMER, ms);
} 

void Start_game(){
	isgame=1;
	mainstate=Playing; 
    ms=350;//最初速度
	startTimer(TIMER, ms);
}

void KeyboardEventProcess1(int key, int event)
{
	switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_SPACE:
			 		if(isblock(indexa,(indexb+1)%4,indexx,indexy)==1){
			 			clean();
			 			indexb=(indexb+1)%4;
			 			drawblock(indexa,indexb,indexx,indexy);
			 			display();
			 		}
                     break;
			     case VK_DOWN:
					 if(isblock(indexa,indexb,indexx,indexy-1)==1){
			         	clean();
			         	indexy--;
			         	drawblock(indexa,indexb,indexx,indexy);
			         	display();
			         }
                     break;
			     case VK_LEFT:
			         if(isblock(indexa,indexb,indexx-1,indexy)==1){
			         	clean();
			         	indexx--;
			         	drawblock(indexa,indexb,indexx,indexy);
			         	display();
			         }
                     break;
			     case VK_RIGHT:
			         if(isblock(indexa,indexb,indexx+1,indexy)==1){
			         	clean();
			         	indexx++;
			         	drawblock(indexa,indexb,indexx,indexy);
			         	display();
			         }
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
    if(isgame==1){
	switch(timerID){
    	case TIMER:
    	if(isblock(indexa,indexb,indexx,indexy-1)==1){
    		indexy=indexy-1;
    		clean();
    		drawblock(indexa,indexb,indexx,indexy);
    		display();
    	}
    	else{
    		blockicy();
    		blockdecline();
    		indexa=newblock;
    		indexb=0;
    		newblock=BlockInit();
    		indexx=6;
    		indexy=19;
    		if(isblock(indexa,indexb,indexx,indexy)==1){
    			drawblock(indexa,indexb,indexx,indexy);
    			display();
    		}
    		else{//开启游戏结束流程
    		cancelTimer(TIMER);
			mainstate=changeUser;
    		}
    	}

    } 
  }
}

void pause(){
	if(isgame==1){
		isgame=2;
		strcpy(FooterStr, "Pause");
	}
}

void carryon(){
	if(isgame==2){
		isgame=1;
		strcpy(FooterStr, "Carry on!");
		mainstate=Playing; 
	}
}

void faster(){
	cancelTimer(TIMER);
    if(ms>250)ms=ms-50;
    startTimer(TIMER, ms);
	}
	
void slower(){
	cancelTimer(TIMER);
    if(ms<400)ms=ms+50;
    startTimer(TIMER, ms);
}
