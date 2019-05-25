void KeyboardEventProcess(int key, int event);
void TimerEventProcess(int timerID);
void prefunction();//预处理，每次刷新时第一步注册黑色边框
void BlockMove(int direction);//把当前活动方块移动一格
int isblock(int a,int b,int x,int y);//判断xy中心位置能否放下 一个ab型方块
void clean();//清除当前活动方块
void drawblock(int a,int b,int x,int y);//在xy中心位置绘制一个ab型方块
void BlockInit();//随机生成下一个方块的a型
void blockicy();//冻结当前活动方块
void blcokdecline();//消灭满的行
void finaldraw();//将数组形式最终编程图案
int block[12][22];//初始化为0代表空白，，1，2，3，4，5，6，7，代表不同颜色
int newblock;//用于存储下一个方块的a类型
int indexx,indexy;//储存当前指示格
int indexa,indexb;//储存当前指示类型
int ms;//储存时间间隔
int score;//

