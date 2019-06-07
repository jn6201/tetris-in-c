#include "main.h"
extern enum gstates mainstate;
extern double winwidth, winheight;
extern int block[12][22],score,newblock;
bool MemoryArchiving(){
		FILE *fp;
		char string[32];
		int i,j;
	  if((fp=fopen("./archiving.txt","w"))==NULL){

       return 0;
	  }
	 pause();
	  for(i=0;i<12;i++){
	  	for(j=0;j<22;j++){	  	  

           fprintf(fp,"%d\n ",block[i][j]);
		  }
	  }

     fprintf(fp,"%d\n ",score);
     fprintf(fp,"%d\n",newblock);
	 fclose(fp);
	 return 1;
}
void ReadArchiving(){
	FILE *fp;
	char string[32];
	int i,j;
//	pause();
	double fH = GetFontHeight();
    double h = fH*2; // 控件高度
    double x = winwidth/2;
	double y = winheight/2+3*h;
	if((fp=fopen("./archiving.txt","r"))==NULL){

        printf("\n open file Fail,close!");
		getchar();
		exit(1);
	  }
	  for(i=0;i<12;i++)
	  for(j=0;j<22;j++){
	  	fscanf(fp,"%d",&block[i][j]);
	  }
	  fscanf(fp,"%d",&score);
	  fscanf(fp,"%d",&newblock);
	  
	  fclose(fp);
	 mainstate=Normalstate;
	  
}
