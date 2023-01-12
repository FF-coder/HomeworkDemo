#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <windows.h>
#define spacenum 5 
//spacenum ：共有停车场位:n 

typedef struct
{
	char num[10];//车牌号 
	int inSecond;//进入停车场停车区的秒    方便计算停车费 
	int outSecond;//离开停车场停车区的秒 
	char intime[20];//进入时间 字符串     格式化字符串 方便打印停车时间 
    char outtime[20];//离开时间  字符串 
}Car,*carData;//车 
//两个栈 1停车场内 2暂时出场 
typedef struct
{
	
	Car car[spacenum];  
	int top;//栈顶 
	
}Stack;//ParkinglotStack 停车场内的车 顺序栈 或 TempStack:存储 挪动停车场内中间的车出场时 需要暂时出场的车 ;
//便道队列
typedef struct Node{
    Car carWaiting;
    struct Node * next;
}QueueNode;//链式便道队列队列节点 
typedef struct{
    QueueNode *front;//头指针
    QueueNode *rear;//队尾指针
}SidewalkQueue;//便道队列
void InitStack(Stack *s);
void Push(Stack *s,Car car);
//void Pop(Stack *s,Car *car);//Car Pop(Stack *s);
void Pop(Stack *s,Car *car);
int isTop(Stack *s,char carNum[10]) ;//根据车牌号找判断车的位置是否为栈顶 
int isFull(Stack *s);
void printStack(Stack *s);//打印此时栈内元素  实时更新 

void feesCalculate(Car theCar);//计算停车费的函数  //每半小时收取2元  2/30min
void printNewst(Stack *NewPStack,SidewalkQueue *NewSidewalk);//打印停车场和便道内最新情况 

QueueNode * initSidewalkQueue(SidewalkQueue *sq);//初始化便道队列
int traverseQueue(SidewalkQueue *sq);//遍历便道队列输出 
int isEmpty(SidewalkQueue *s);//判断便道队列是否为空 
void EnterQueue(SidewalkQueue *s,Car car);//1-1-1 停车场已满时 将车排列进入便道队列队尾
void outQueue(SidewalkQueue *s,Car *car); //当停车场有空位时，让便道队列的首辆车出队 进入停车场 

void Select_MainMenu(Stack *P,Stack *T,SidewalkQueue *side)  ;//主菜单 

void PushToParkinglot(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk) ; //1安排停车

void CarLeave(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk);//2离开停车场

int main()
{
	 system("color 3f");
	 system("title  停车场管理系统") ;
//	 //车辆栈
    //ParkinglotStack 停车场内的车 顺序栈 
	Stack *ParkinglotStack=(Stack*)malloc(sizeof(Stack));
	//TempStack:存储 挪动停车场内中间的车出场时 需要暂时出场的车 ;
	Stack *TempStack=(Stack*)malloc(sizeof(Stack));
	InitStack(ParkinglotStack);
	InitStack(TempStack);
	printf("\n%d",TempStack->top);
    Car car0,car1,car2;
	int insec=1673421370;
	char timestr1[20]="2023-1-11 15:16:10";
	car0.inSecond=insec;
	strcpy(car0.num,"沪A10011");car0.inSecond=insec;
	strcpy(car0.intime,timestr1);
	Push(ParkinglotStack,car0);
   car1.inSecond=insec;
	strcpy(car1.num,"陕B20022");car1.inSecond=insec+1;
	strcpy(car1.intime,"2023-1-11 15:16:11");
    Push(ParkinglotStack,car1);
    
      car2.inSecond=insec;
	strcpy(car2.num,"粤C30033");car2.inSecond=insec+2;
	strcpy(car2.intime,"2023-1-11 15:16:12");
    Push(ParkinglotStack,car2);
  

//队列
  SidewalkQueue *sidewalkQueue= (SidewalkQueue*)malloc(sizeof(SidewalkQueue));
  //SidewalkQueue *sidewalkQueue=initSidewalkQueue(sidewalkQueue);//初始化便道队列
   sidewalkQueue->front=sidewalkQueue->rear=initSidewalkQueue(sidewalkQueue);//初始化便道队列
   sidewalkQueue->front->next=NULL;sidewalkQueue->rear->next=NULL;
//QueueNode

    Select_MainMenu(ParkinglotStack,TempStack,sidewalkQueue) ;
    

    return 0;
}
void InitStack(Stack *s)
{
    s->top=-1;
}
void Push(Stack *s,Car car)
{
    if(s->top==spacenum-1)return;//已满 
    else
    {
    	++(s->top);
    	s->car[s->top]=car;
	 } 
    
} 
void Pop(Stack *s,Car *car)
{
	if(s->top==-1)return;//	printf("已经为空~");
	else
	{
		*car=s->car[s->top];
	    (s->top)--;
	}
}
int isTop(Stack *s,char carNum[10]) //根据车牌号找判断车的位置是否为栈顶  //1 0 2:内已无车
{
	if(s->top==-1)
	{
		printf("\n停车场内已无车辆哦~\n");
		return 2;
	}
	else
	{
		if(strcmp(s->car[s->top].num,carNum)==0)//判断车牌号是否匹配栈顶车辆 ==0则匹配 否则不匹配 
		{
			return 1;//该车就在栈顶 不用挪车 直接出停车场 
		} 
		else
		{
			int exist=0;//假设不存在此车 
			for(int g=0;g<=s->top;g++)
			{
				if(strcmp( carNum,s->car[g].num)==0)
				{
				     exist=1;//存在此车 
				     break;
			    }
			}
			if(exist==0)//停车场内无此车  -1
			     return -1; 
		    else	return 0;//0 该车不在栈顶 需要挪前面的车后才出停车场 
		}
	}
	
}
int isFull(Stack *s)//判断栈是否已满 
{
	if(s->top==spacenum-1)return 1;
	else return 0;
}
void printStack(Stack *s)//打印此时栈内元素  实时更新 
{
	if(s->top==-1)printf("\n没有车辆！\n");
	else
	{
		for(int i=0;i<=s->top;++i)
		{
			printf("%s ",s->car[i]);
		}
	}
	printf("\n\n");
}
void feesCalculate(Car theCar)
{
     int totalSecond=theCar.outSecond-theCar.inSecond;
     //每半小时收取2元  2/30min
     
     double totalMinute=totalSecond/60.0;
     printf("\t总计停车时长为：%.4lf分钟\n",totalMinute);
     double fees=totalMinute*2.0/30.0;
     printf("\n\t停车费：%.4lf元(每半小时收费2元)\n",fees);
}
void printNewst(Stack *NewPStack,SidewalkQueue *NewSidewalk)
{
	   if(isFull(NewPStack)) printf("\n停车场:\n\t场内状态:已满");
	   else printf("\n停车场:\n\t场内状态:未满");
		printf("\n\t车辆数：%d\n\t空位数：%d\n\t从北到南排列为:",NewPStack->top+1,spacenum-(NewPStack->top+1));
		printStack(NewPStack);//打印此时栈内元素  实时更新
		printf("\n便道:");
		if(isEmpty(NewSidewalk))//便道 空 
		{
		    printf("\n\t等候车辆数：0\n\n");
		}
		else
		{
         	printf("\n\t车辆按先后顺序排列为:");
         	int QueueNum=traverseQueue(NewSidewalk); 
			printf("\t共有等候车辆数：%d\n\n",QueueNum);
		}
}

QueueNode * initSidewalkQueue(SidewalkQueue *sq)//初始化便道队列 
{

	QueueNode *h=(QueueNode*)malloc(sizeof(QueueNode)); //带头结点 
	h->next=NULL;
//	SidewalkQueue *h=(SidewalkQueue *)malloc(sizeof(SidewalkQueue)); //带头结点
//	sq->front=sq->rear=h;
//	sq->front->next=NULL;
	return h;
}

int traverseQueue(SidewalkQueue *sq)//遍历便道队列输出 返回总车辆数 
{
	Car iCar;
	QueueNode *t;
	int count=0;
	if(sq->front==sq->rear)return count;
	else
	{	
	       t=sq->front->next;
	       while(t!=NULL)
           {	
	              strcpy(iCar.num,t->carWaiting.num);
				  ++count; 
	              printf("%s ",iCar.num);
	              t=t->next;
	       }
	       printf("\n\n");
	       free(t);
	       return count;
	}
}


int isEmpty(SidewalkQueue *s)//判断便道队列是否为空 
{
	if(s->front==s->rear)return 1;//为空
	else return 0;//队列非空 
}
void EnterQueue(SidewalkQueue *s,Car car)//1-1-1 停车场已满时 将车排列进入便道队列队尾
{
	//尾插法思想 
	QueueNode *q=(QueueNode*)malloc(sizeof(QueueNode));
	q->carWaiting=car;
	q->next=NULL;
	s->rear->next=q;
	s->rear=q;//作为新的队尾 
//	free(q);
}
void outQueue(SidewalkQueue *s,Car *car) //当停车场有空位时，让便道队列的首辆车出队 
{
	if(s->front==s->rear){
		printf("\n此时便道中没有车辆哦！\n");
		return;
	}
	QueueNode *c=s->front->next;//首辆车所在的结点 
	*car=c->carWaiting;//存首辆车信息
	s->front->next=s->front->next->next;//c->next; //头结点的next指向下一辆车
	if(s->rear==c)//如果原来的便道队列里本来就只有一辆车 则该车出列后队列为空  
	{
		s->rear=s->front;//保证下一次正常判isEmpty 
	}
	free(c); 
}
//主菜单 
void Select_MainMenu(Stack *P,Stack *T,SidewalkQueue *side) 
{	
	
	char nMainchoose[50];//避免非整型字符（串）干扰 
	while(1)//菜单循环 
	{
		system("CLS"); //***系统屏幕清空 ***
		//输出菜单主界面 
		printf("\n\n\t\t ------------ 欢迎来到停车场管理系统  ------------\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     1.停车                      |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     2.汽车离场                  |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     3.退出系统                  |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t  ----------------------------------------------- \n");
			printf("\t\t\t\t请输入您的选择:");
			scanf("%s",nMainchoose);//根据用户输入的数字看如何行动		
		int choice=atoi(nMainchoose);	//将输入的字符串转化为数字		
		switch(choice)
		{
			case 1: 
			        PushToParkinglot(P,T,side) ;//1.停车 
			        system("pause");
					break;
		    case 2: 
		            CarLeave(P,T,side); //2.汽车离场
					system("pause");break;
		    case 3:
                printf("感谢您使用本系统，欢迎您下次再来！\n"); //3.退出系统 
				system("pause");
				//break; 
				return ;
		
			default:printf("\n\t\t   选择有误，请重选！\n");	
			        system("pause");
		}
	}//while(1)函数结束 
}//Select_MainMenu函数结束 


//1安排停车
void PushToParkinglot(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk) 
{
	system("CLS");
	printf("\n\n\t\t ------------ 这里是[停车安排]模块  ------------\n");
	printf("\n当前停车场和便道情况如下：\n");
	printNewst(PStack,sidewalk);//打印最新状态   
	Car thisCar;
	printf("\n请输入此车的车牌号==>");	
	char inputCarNum[10];
	scanf("%s",&inputCarNum);
	int repeat=0;//判断车牌号是否有重复  1:重复  ； 0：无 
	for(int b=0;b<=PStack->top;++b)
	{
		if(strcmp(inputCarNum,PStack->car[b].num)==0)
		{
			repeat=1;//有重复 
			break;
		}
	}
	
		   
	if(repeat==1)//有重复
	{
	    	printf("\n输入错误：车牌号%s与停车场内的车重复了哦！请检查车牌号哦！\n",inputCarNum);
        	printf("\n（现有选项）==> 重新输入车牌号 : 1  ;  返回主菜单 :其他字符（除回车键外）\n");
         	char cc[30];
			printf("请选择==>");scanf("%s",cc);
			if(strcmp(cc,"1")==0) 	PushToParkinglot(PStack,TStack,sidewalk) ;//重新输入车牌号 
            else return;	//返回主菜单
	}
	else //车牌号无重复 合适 
	{
		strcpy(thisCar.num,inputCarNum);
         //1-1 判断车场栈是否已满
              //1-1-1 是 已满  将输入项排列进入便道队列队尾  EnterQueue（） 
              //1-1-2 否 未满 可以将输入项直接进栈push进栈ParkinglotStack
    int Full=isFull(PStack);
	if(isFull(PStack))
	{
		printf("\n很抱歉哦！经系统检测，停车场车位已满，请先于便道排队等候哦！\n");
		printf("\n正在安排此车进入便道等候...\n");
		Sleep(1000);
    	EnterQueue(sidewalk,thisCar);//1-1-1 是 已满  将输入项排列进入便道队列队尾
		printf("车辆（%s）已进入便道等待！\n",thisCar.num);
		printf("\n停车场与便道最新情况如下：\n");
		printNewst(PStack,sidewalk);//打印停车场与便道最新状态 ； 
	}
	else
	{
		printf("\n停车场内尚有空位，正在安排此车进入停车场...\n");
		Sleep(1000);
	    int sec = time((time_t *)NULL);
		thisCar.inSecond=sec;//秒 方便后续计算收费 
	    time_t timep; time(&timep);
        struct tm *p;p = gmtime(&timep);
        snprintf(thisCar.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	   //打印该车（车牌号）停于那个位置 入场时间 提示停车计时开始 printf("\n");
	   Push(PStack,thisCar);	//1-1-1 否 未满 可以将输入项直接进栈push进栈ParkinglotStack
	   printf("\n车辆%s:\n\t已进入停车场，开始停车计时！\n\t入场时间:%s\n\t停放:第%d个车位（从北到南计数）\n",thisCar.num,thisCar.intime,(PStack->top)+1);

        printNewst(PStack,sidewalk);//打印停车场最新状态 
	}	
	
	}
	
}
//2离开停车场
void CarLeave(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk)
{
	system("CLS");
	printf("\n\n\t\t ------------ 这里是[车离开停车场]的模块  ------------\n");
	printf("\n当前停车场和便道情况如下：\n");
	printNewst(PStack,sidewalk);//打印最新状态  
//	判断
//1栈顶 打印离场时间 转收费计算函数
// 0中间 打印暂时出场元素 和 出场成功提示 出场时间 
//   然后让暂出场的按原序返回stackTemp全部 pop到  ParkinglotStack
	Car thisCar;Car carTemp1;
    char inputNum[10];
	printf("\n请输入要离开的车辆的车牌号==>");	
	scanf("%s",&inputNum);
    int TopFlag=isTop(PStack, inputNum); //根据车牌号找判断车的位置是否为栈顶   //TopFlag:1 or 0 or -1  or 2 
    if(TopFlag==2) //停车场为空 
	{
		printf("\n正在返回主菜单...\n");Sleep(900);
    	return;
	}
	else if(TopFlag==-1)//无此车 （车牌号有误 
	{
	    	printf("\n停车场内没有车辆%s哦！请检查车牌号是否输入正确哦！\n",inputNum);
        	printf("\n（现有选项）==> 重新输入车牌号 : 1  ;  返回主菜单 :其他字符（除回车键外）\n");
         	char cc[30];
			printf("请选择==>");scanf("%s",cc);
			if(strcmp(cc,"1")==0) 	CarLeave(PStack,TStack,sidewalk);//重新输入车牌号 
            else return;	//返回主菜单
	}
	
	else if(TopFlag==1) //1此车在栈顶 打印离场时间 转收费计算函数
	{
    	printf("\n正在安排此车离开停车场...\n");Sleep(1000);
     	Pop(PStack,&thisCar);//直接出场 出栈 
        time_t timep;time(&timep);
        struct tm *p;p = gmtime(&timep);
        snprintf(thisCar.outtime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec); 
        int sec = time((time_t *)NULL);	thisCar.outSecond=sec;//秒 方便后续计算收费 
        printf("\n车辆%s:\n\t已离开停车场！\n\t离场时间:%s\n\t此前入场时间:%s\n",thisCar.num,thisCar.outtime,thisCar.intime);
        feesCalculate(thisCar); //收费情况 
        printf("\n（停车场内增加一个空位）");
		printf("\n停车场:\n\t场内状态:未满\n\t车辆数：%d\n\t空位数：%d",PStack->top+1,spacenum-(PStack->top+1));
		printf("\n\t从北到南排列为:");
		printStack(PStack);//打印此时栈内元素  实时更新
		    //接着判断便道内是否有车（队列非空），若有 则进入停车场  
		
	    if(isEmpty(sidewalk)==0)//便道有车 安排进入停车场 
	    {
	    	
		    outQueue(sidewalk,&carTemp1);//便道队列首辆车出队
			printf("\n由于有车离场增加一个空位,正在安排便道队列中第一辆车：%s进入停车场...\n",carTemp1.num);Sleep(1000);
			int sec = time((time_t *)NULL);carTemp1.inSecond=sec;
	        time_t timep;time(&timep);
            struct tm *p; p = gmtime(&timep);snprintf(carTemp1.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	        Push(PStack,carTemp1) ;//入停车场
	       printf("\n车辆%s:\n\t已进入停车场，开始停车计时！\n\t入场时间:%s\n\t停放:第%d个车位（从北到南计数）\n",carTemp1.num,carTemp1.intime,(PStack->top)+1);
	       printf("\n停车场信息更新为如下：\n");
		   printNewst(PStack,sidewalk);//打印最新状态  
		}
		else
		{
			printf("\n便道：\n\t等候车辆数：0\n\n");
		} 
		
	}
	else// 0：为中间车辆 需要挪车 打印暂时出场元素 和 出场成功提示 出场时间 
	{
		Car leaveTempCar,TrueLeaveCar,carTemp;
        //挪车：让暂出场的按原序返回stackTemp全部 pop到  ParkinglotStack
		printf("\n由于该车不在首位出场位置，需要让其后面的车暂时出场,正在安排挪车...\n");Sleep(500);
		printf("\n挪车顺序为：");
		int k;
        for(k=PStack->top;k>=0;--k)
        {
        	 if(strcmp(inputNum,PStack->car[k].num)==0)
        	 {
        	 	printf("\n车辆（%s）正在离开停车场...",PStack->car[k].num); Sleep(800);
        	 	break;
			 }
        	 Pop(PStack,&leaveTempCar);
			 Push(TStack,leaveTempCar);//存入临时栈 
        	 printf("%s ",leaveTempCar.num);
		}
            printf("\n\n");
			Pop(PStack,&TrueLeaveCar);//目标车辆离场
			time_t timep;time(&timep);
            struct tm *p;p = gmtime(&timep);
            snprintf(TrueLeaveCar.outtime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec); 
             int sec = time((time_t *)NULL);TrueLeaveCar.outSecond=sec;//秒 方便后续计算收费 
			printf("\n车辆%s:\n\t已离开停车场！\n\t离场时间:%s\n\t此前入场时间:%s\n",TrueLeaveCar.num,TrueLeaveCar.outtime,TrueLeaveCar.intime);
            feesCalculate(TrueLeaveCar); //收费情况 
          	printf("\n暂时挪动的车按照以下顺序返回原位：");
            for(int j=TStack->top;j>=0;--j)
			{
			    Pop(TStack,&leaveTempCar);
			    printf("%s ",leaveTempCar.num);
				Push(PStack,leaveTempCar);//依次Push回停车场 
			}
			printf("\n（挪动的车已全部返回原位）\n\n");
			
		//	printNewst(PStack,sidewalk);//打印最新状态 
			
         	if(isEmpty(sidewalk)==0)//若便道有车 需要安排进入停车场 
	        {
		     	printf("\n停车场内腾出了一个空位，正在安排便道队列中第一辆车进入停车场...\n",carTemp.num);Sleep(1000);
		     	outQueue(sidewalk,&carTemp);//便道队列首辆车出队
			    int sec2 = time((time_t *)NULL);carTemp.inSecond=sec;time_t timep;time(&timep);
                struct tm *p2; 	p2 = gmtime(&timep);
                snprintf(carTemp.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p2->tm_year, 1 + p2->tm_mon, p2->tm_mday, 8 + p2->tm_hour, p2->tm_min, p2->tm_sec);
	             Push(PStack,carTemp) ;//入停车场
	            printf("\n\t车辆（%s）已进入停车场，开始停车计时！\n\t入场时间:%s\n\t停放:第%d个车位（从北到南计数）\n",carTemp.num,carTemp.intime,(PStack->top)+1);
	            printf("\n停车场信息更新为如下：\n");
		    }
		   else
		   {
		         printf("目前停车场和便道的情况如下：\n");
		   }
		   printNewst(PStack,sidewalk);//打印最新状态  
		
		
	}
}
