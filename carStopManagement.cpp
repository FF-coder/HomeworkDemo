#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <windows.h>
#define spacenum 5 
//spacenum ������ͣ����λ:n 

typedef struct
{
	char num[10];//���ƺ� 
	int inSecond;//����ͣ����ͣ��������    �������ͣ���� 
	int outSecond;//�뿪ͣ����ͣ�������� 
	char intime[20];//����ʱ�� �ַ���     ��ʽ���ַ��� �����ӡͣ��ʱ�� 
    char outtime[20];//�뿪ʱ��  �ַ��� 
}Car,*carData;//�� 
//����ջ 1ͣ������ 2��ʱ���� 
typedef struct
{
	
	Car car[spacenum];  
	int top;//ջ�� 
	
}Stack;//ParkinglotStack ͣ�����ڵĳ� ˳��ջ �� TempStack:�洢 Ų��ͣ�������м�ĳ�����ʱ ��Ҫ��ʱ�����ĳ� ;
//�������
typedef struct Node{
    Car carWaiting;
    struct Node * next;
}QueueNode;//��ʽ������ж��нڵ� 
typedef struct{
    QueueNode *front;//ͷָ��
    QueueNode *rear;//��βָ��
}SidewalkQueue;//�������
void InitStack(Stack *s);
void Push(Stack *s,Car car);
//void Pop(Stack *s,Car *car);//Car Pop(Stack *s);
void Pop(Stack *s,Car *car);
int isTop(Stack *s,char carNum[10]) ;//���ݳ��ƺ����жϳ���λ���Ƿ�Ϊջ�� 
int isFull(Stack *s);
void printStack(Stack *s);//��ӡ��ʱջ��Ԫ��  ʵʱ���� 

void feesCalculate(Car theCar);//����ͣ���ѵĺ���  //ÿ��Сʱ��ȡ2Ԫ  2/30min
void printNewst(Stack *NewPStack,SidewalkQueue *NewSidewalk);//��ӡͣ�����ͱ����������� 

QueueNode * initSidewalkQueue(SidewalkQueue *sq);//��ʼ���������
int traverseQueue(SidewalkQueue *sq);//�������������� 
int isEmpty(SidewalkQueue *s);//�жϱ�������Ƿ�Ϊ�� 
void EnterQueue(SidewalkQueue *s,Car car);//1-1-1 ͣ��������ʱ �������н��������ж�β
void outQueue(SidewalkQueue *s,Car *car); //��ͣ�����п�λʱ���ñ�����е����������� ����ͣ���� 

void Select_MainMenu(Stack *P,Stack *T,SidewalkQueue *side)  ;//���˵� 

void PushToParkinglot(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk) ; //1����ͣ��

void CarLeave(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk);//2�뿪ͣ����

int main()
{
	 system("color 3f");
	 system("title  ͣ��������ϵͳ") ;
//	 //����ջ
    //ParkinglotStack ͣ�����ڵĳ� ˳��ջ 
	Stack *ParkinglotStack=(Stack*)malloc(sizeof(Stack));
	//TempStack:�洢 Ų��ͣ�������м�ĳ�����ʱ ��Ҫ��ʱ�����ĳ� ;
	Stack *TempStack=(Stack*)malloc(sizeof(Stack));
	InitStack(ParkinglotStack);
	InitStack(TempStack);
	printf("\n%d",TempStack->top);
    Car car0,car1,car2;
	int insec=1673421370;
	char timestr1[20]="2023-1-11 15:16:10";
	car0.inSecond=insec;
	strcpy(car0.num,"��A10011");car0.inSecond=insec;
	strcpy(car0.intime,timestr1);
	Push(ParkinglotStack,car0);
   car1.inSecond=insec;
	strcpy(car1.num,"��B20022");car1.inSecond=insec+1;
	strcpy(car1.intime,"2023-1-11 15:16:11");
    Push(ParkinglotStack,car1);
    
      car2.inSecond=insec;
	strcpy(car2.num,"��C30033");car2.inSecond=insec+2;
	strcpy(car2.intime,"2023-1-11 15:16:12");
    Push(ParkinglotStack,car2);
  

//����
  SidewalkQueue *sidewalkQueue= (SidewalkQueue*)malloc(sizeof(SidewalkQueue));
  //SidewalkQueue *sidewalkQueue=initSidewalkQueue(sidewalkQueue);//��ʼ���������
   sidewalkQueue->front=sidewalkQueue->rear=initSidewalkQueue(sidewalkQueue);//��ʼ���������
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
    if(s->top==spacenum-1)return;//���� 
    else
    {
    	++(s->top);
    	s->car[s->top]=car;
	 } 
    
} 
void Pop(Stack *s,Car *car)
{
	if(s->top==-1)return;//	printf("�Ѿ�Ϊ��~");
	else
	{
		*car=s->car[s->top];
	    (s->top)--;
	}
}
int isTop(Stack *s,char carNum[10]) //���ݳ��ƺ����жϳ���λ���Ƿ�Ϊջ��  //1 0 2:�����޳�
{
	if(s->top==-1)
	{
		printf("\nͣ���������޳���Ŷ~\n");
		return 2;
	}
	else
	{
		if(strcmp(s->car[s->top].num,carNum)==0)//�жϳ��ƺ��Ƿ�ƥ��ջ������ ==0��ƥ�� ����ƥ�� 
		{
			return 1;//�ó�����ջ�� ����Ų�� ֱ�ӳ�ͣ���� 
		} 
		else
		{
			int exist=0;//���費���ڴ˳� 
			for(int g=0;g<=s->top;g++)
			{
				if(strcmp( carNum,s->car[g].num)==0)
				{
				     exist=1;//���ڴ˳� 
				     break;
			    }
			}
			if(exist==0)//ͣ�������޴˳�  -1
			     return -1; 
		    else	return 0;//0 �ó�����ջ�� ��ҪŲǰ��ĳ���ų�ͣ���� 
		}
	}
	
}
int isFull(Stack *s)//�ж�ջ�Ƿ����� 
{
	if(s->top==spacenum-1)return 1;
	else return 0;
}
void printStack(Stack *s)//��ӡ��ʱջ��Ԫ��  ʵʱ���� 
{
	if(s->top==-1)printf("\nû�г�����\n");
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
     //ÿ��Сʱ��ȡ2Ԫ  2/30min
     
     double totalMinute=totalSecond/60.0;
     printf("\t�ܼ�ͣ��ʱ��Ϊ��%.4lf����\n",totalMinute);
     double fees=totalMinute*2.0/30.0;
     printf("\n\tͣ���ѣ�%.4lfԪ(ÿ��Сʱ�շ�2Ԫ)\n",fees);
}
void printNewst(Stack *NewPStack,SidewalkQueue *NewSidewalk)
{
	   if(isFull(NewPStack)) printf("\nͣ����:\n\t����״̬:����");
	   else printf("\nͣ����:\n\t����״̬:δ��");
		printf("\n\t��������%d\n\t��λ����%d\n\t�ӱ���������Ϊ:",NewPStack->top+1,spacenum-(NewPStack->top+1));
		printStack(NewPStack);//��ӡ��ʱջ��Ԫ��  ʵʱ����
		printf("\n���:");
		if(isEmpty(NewSidewalk))//��� �� 
		{
		    printf("\n\t�Ⱥ�������0\n\n");
		}
		else
		{
         	printf("\n\t�������Ⱥ�˳������Ϊ:");
         	int QueueNum=traverseQueue(NewSidewalk); 
			printf("\t���еȺ�������%d\n\n",QueueNum);
		}
}

QueueNode * initSidewalkQueue(SidewalkQueue *sq)//��ʼ��������� 
{

	QueueNode *h=(QueueNode*)malloc(sizeof(QueueNode)); //��ͷ��� 
	h->next=NULL;
//	SidewalkQueue *h=(SidewalkQueue *)malloc(sizeof(SidewalkQueue)); //��ͷ���
//	sq->front=sq->rear=h;
//	sq->front->next=NULL;
	return h;
}

int traverseQueue(SidewalkQueue *sq)//�������������� �����ܳ����� 
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


int isEmpty(SidewalkQueue *s)//�жϱ�������Ƿ�Ϊ�� 
{
	if(s->front==s->rear)return 1;//Ϊ��
	else return 0;//���зǿ� 
}
void EnterQueue(SidewalkQueue *s,Car car)//1-1-1 ͣ��������ʱ �������н��������ж�β
{
	//β�巨˼�� 
	QueueNode *q=(QueueNode*)malloc(sizeof(QueueNode));
	q->carWaiting=car;
	q->next=NULL;
	s->rear->next=q;
	s->rear=q;//��Ϊ�µĶ�β 
//	free(q);
}
void outQueue(SidewalkQueue *s,Car *car) //��ͣ�����п�λʱ���ñ�����е����������� 
{
	if(s->front==s->rear){
		printf("\n��ʱ�����û�г���Ŷ��\n");
		return;
	}
	QueueNode *c=s->front->next;//���������ڵĽ�� 
	*car=c->carWaiting;//����������Ϣ
	s->front->next=s->front->next->next;//c->next; //ͷ����nextָ����һ����
	if(s->rear==c)//���ԭ���ı�������ﱾ����ֻ��һ���� ��ó����к����Ϊ��  
	{
		s->rear=s->front;//��֤��һ��������isEmpty 
	}
	free(c); 
}
//���˵� 
void Select_MainMenu(Stack *P,Stack *T,SidewalkQueue *side) 
{	
	
	char nMainchoose[50];//����������ַ����������� 
	while(1)//�˵�ѭ�� 
	{
		system("CLS"); //***ϵͳ��Ļ��� ***
		//����˵������� 
		printf("\n\n\t\t ------------ ��ӭ����ͣ��������ϵͳ  ------------\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     1.ͣ��                      |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     2.�����볡                  |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                     3.�˳�ϵͳ                  |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t|                                                 |\n");
		printf("\t\t  ----------------------------------------------- \n");
			printf("\t\t\t\t����������ѡ��:");
			scanf("%s",nMainchoose);//�����û���������ֿ�����ж�		
		int choice=atoi(nMainchoose);	//��������ַ���ת��Ϊ����		
		switch(choice)
		{
			case 1: 
			        PushToParkinglot(P,T,side) ;//1.ͣ�� 
			        system("pause");
					break;
		    case 2: 
		            CarLeave(P,T,side); //2.�����볡
					system("pause");break;
		    case 3:
                printf("��л��ʹ�ñ�ϵͳ����ӭ���´�������\n"); //3.�˳�ϵͳ 
				system("pause");
				//break; 
				return ;
		
			default:printf("\n\t\t   ѡ����������ѡ��\n");	
			        system("pause");
		}
	}//while(1)�������� 
}//Select_MainMenu�������� 


//1����ͣ��
void PushToParkinglot(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk) 
{
	system("CLS");
	printf("\n\n\t\t ------------ ������[ͣ������]ģ��  ------------\n");
	printf("\n��ǰͣ�����ͱ��������£�\n");
	printNewst(PStack,sidewalk);//��ӡ����״̬   
	Car thisCar;
	printf("\n������˳��ĳ��ƺ�==>");	
	char inputCarNum[10];
	scanf("%s",&inputCarNum);
	int repeat=0;//�жϳ��ƺ��Ƿ����ظ�  1:�ظ�  �� 0���� 
	for(int b=0;b<=PStack->top;++b)
	{
		if(strcmp(inputCarNum,PStack->car[b].num)==0)
		{
			repeat=1;//���ظ� 
			break;
		}
	}
	
		   
	if(repeat==1)//���ظ�
	{
	    	printf("\n������󣺳��ƺ�%s��ͣ�����ڵĳ��ظ���Ŷ�����鳵�ƺ�Ŷ��\n",inputCarNum);
        	printf("\n������ѡ�==> �������복�ƺ� : 1  ;  �������˵� :�����ַ������س����⣩\n");
         	char cc[30];
			printf("��ѡ��==>");scanf("%s",cc);
			if(strcmp(cc,"1")==0) 	PushToParkinglot(PStack,TStack,sidewalk) ;//�������복�ƺ� 
            else return;	//�������˵�
	}
	else //���ƺ����ظ� ���� 
	{
		strcpy(thisCar.num,inputCarNum);
         //1-1 �жϳ���ջ�Ƿ�����
              //1-1-1 �� ����  �����������н��������ж�β  EnterQueue���� 
              //1-1-2 �� δ�� ���Խ�������ֱ�ӽ�ջpush��ջParkinglotStack
    int Full=isFull(PStack);
	if(isFull(PStack))
	{
		printf("\n�ܱ�ǸŶ����ϵͳ��⣬ͣ������λ�����������ڱ���ŶӵȺ�Ŷ��\n");
		printf("\n���ڰ��Ŵ˳��������Ⱥ�...\n");
		Sleep(1000);
    	EnterQueue(sidewalk,thisCar);//1-1-1 �� ����  �����������н��������ж�β
		printf("������%s���ѽ������ȴ���\n",thisCar.num);
		printf("\nͣ������������������£�\n");
		printNewst(PStack,sidewalk);//��ӡͣ������������״̬ �� 
	}
	else
	{
		printf("\nͣ���������п�λ�����ڰ��Ŵ˳�����ͣ����...\n");
		Sleep(1000);
	    int sec = time((time_t *)NULL);
		thisCar.inSecond=sec;//�� ������������շ� 
	    time_t timep; time(&timep);
        struct tm *p;p = gmtime(&timep);
        snprintf(thisCar.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	   //��ӡ�ó������ƺţ�ͣ���Ǹ�λ�� �볡ʱ�� ��ʾͣ����ʱ��ʼ printf("\n");
	   Push(PStack,thisCar);	//1-1-1 �� δ�� ���Խ�������ֱ�ӽ�ջpush��ջParkinglotStack
	   printf("\n����%s:\n\t�ѽ���ͣ��������ʼͣ����ʱ��\n\t�볡ʱ��:%s\n\tͣ��:��%d����λ���ӱ����ϼ�����\n",thisCar.num,thisCar.intime,(PStack->top)+1);

        printNewst(PStack,sidewalk);//��ӡͣ��������״̬ 
	}	
	
	}
	
}
//2�뿪ͣ����
void CarLeave(Stack *PStack,Stack *TStack,SidewalkQueue *sidewalk)
{
	system("CLS");
	printf("\n\n\t\t ------------ ������[���뿪ͣ����]��ģ��  ------------\n");
	printf("\n��ǰͣ�����ͱ��������£�\n");
	printNewst(PStack,sidewalk);//��ӡ����״̬  
//	�ж�
//1ջ�� ��ӡ�볡ʱ�� ת�շѼ��㺯��
// 0�м� ��ӡ��ʱ����Ԫ�� �� �����ɹ���ʾ ����ʱ�� 
//   Ȼ�����ݳ����İ�ԭ�򷵻�stackTempȫ�� pop��  ParkinglotStack
	Car thisCar;Car carTemp1;
    char inputNum[10];
	printf("\n������Ҫ�뿪�ĳ����ĳ��ƺ�==>");	
	scanf("%s",&inputNum);
    int TopFlag=isTop(PStack, inputNum); //���ݳ��ƺ����жϳ���λ���Ƿ�Ϊջ��   //TopFlag:1 or 0 or -1  or 2 
    if(TopFlag==2) //ͣ����Ϊ�� 
	{
		printf("\n���ڷ������˵�...\n");Sleep(900);
    	return;
	}
	else if(TopFlag==-1)//�޴˳� �����ƺ����� 
	{
	    	printf("\nͣ������û�г���%sŶ�����鳵�ƺ��Ƿ�������ȷŶ��\n",inputNum);
        	printf("\n������ѡ�==> �������복�ƺ� : 1  ;  �������˵� :�����ַ������س����⣩\n");
         	char cc[30];
			printf("��ѡ��==>");scanf("%s",cc);
			if(strcmp(cc,"1")==0) 	CarLeave(PStack,TStack,sidewalk);//�������복�ƺ� 
            else return;	//�������˵�
	}
	
	else if(TopFlag==1) //1�˳���ջ�� ��ӡ�볡ʱ�� ת�շѼ��㺯��
	{
    	printf("\n���ڰ��Ŵ˳��뿪ͣ����...\n");Sleep(1000);
     	Pop(PStack,&thisCar);//ֱ�ӳ��� ��ջ 
        time_t timep;time(&timep);
        struct tm *p;p = gmtime(&timep);
        snprintf(thisCar.outtime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec); 
        int sec = time((time_t *)NULL);	thisCar.outSecond=sec;//�� ������������շ� 
        printf("\n����%s:\n\t���뿪ͣ������\n\t�볡ʱ��:%s\n\t��ǰ�볡ʱ��:%s\n",thisCar.num,thisCar.outtime,thisCar.intime);
        feesCalculate(thisCar); //�շ���� 
        printf("\n��ͣ����������һ����λ��");
		printf("\nͣ����:\n\t����״̬:δ��\n\t��������%d\n\t��λ����%d",PStack->top+1,spacenum-(PStack->top+1));
		printf("\n\t�ӱ���������Ϊ:");
		printStack(PStack);//��ӡ��ʱջ��Ԫ��  ʵʱ����
		    //�����жϱ�����Ƿ��г������зǿգ������� �����ͣ����  
		
	    if(isEmpty(sidewalk)==0)//����г� ���Ž���ͣ���� 
	    {
	    	
		    outQueue(sidewalk,&carTemp1);//�����������������
			printf("\n�����г��볡����һ����λ,���ڰ��ű�������е�һ������%s����ͣ����...\n",carTemp1.num);Sleep(1000);
			int sec = time((time_t *)NULL);carTemp1.inSecond=sec;
	        time_t timep;time(&timep);
            struct tm *p; p = gmtime(&timep);snprintf(carTemp1.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	        Push(PStack,carTemp1) ;//��ͣ����
	       printf("\n����%s:\n\t�ѽ���ͣ��������ʼͣ����ʱ��\n\t�볡ʱ��:%s\n\tͣ��:��%d����λ���ӱ����ϼ�����\n",carTemp1.num,carTemp1.intime,(PStack->top)+1);
	       printf("\nͣ������Ϣ����Ϊ���£�\n");
		   printNewst(PStack,sidewalk);//��ӡ����״̬  
		}
		else
		{
			printf("\n�����\n\t�Ⱥ�������0\n\n");
		} 
		
	}
	else// 0��Ϊ�м䳵�� ��ҪŲ�� ��ӡ��ʱ����Ԫ�� �� �����ɹ���ʾ ����ʱ�� 
	{
		Car leaveTempCar,TrueLeaveCar,carTemp;
        //Ų�������ݳ����İ�ԭ�򷵻�stackTempȫ�� pop��  ParkinglotStack
		printf("\n���ڸó�������λ����λ�ã���Ҫ�������ĳ���ʱ����,���ڰ���Ų��...\n");Sleep(500);
		printf("\nŲ��˳��Ϊ��");
		int k;
        for(k=PStack->top;k>=0;--k)
        {
        	 if(strcmp(inputNum,PStack->car[k].num)==0)
        	 {
        	 	printf("\n������%s�������뿪ͣ����...",PStack->car[k].num); Sleep(800);
        	 	break;
			 }
        	 Pop(PStack,&leaveTempCar);
			 Push(TStack,leaveTempCar);//������ʱջ 
        	 printf("%s ",leaveTempCar.num);
		}
            printf("\n\n");
			Pop(PStack,&TrueLeaveCar);//Ŀ�공���볡
			time_t timep;time(&timep);
            struct tm *p;p = gmtime(&timep);
            snprintf(TrueLeaveCar.outtime, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec); 
             int sec = time((time_t *)NULL);TrueLeaveCar.outSecond=sec;//�� ������������շ� 
			printf("\n����%s:\n\t���뿪ͣ������\n\t�볡ʱ��:%s\n\t��ǰ�볡ʱ��:%s\n",TrueLeaveCar.num,TrueLeaveCar.outtime,TrueLeaveCar.intime);
            feesCalculate(TrueLeaveCar); //�շ���� 
          	printf("\n��ʱŲ���ĳ���������˳�򷵻�ԭλ��");
            for(int j=TStack->top;j>=0;--j)
			{
			    Pop(TStack,&leaveTempCar);
			    printf("%s ",leaveTempCar.num);
				Push(PStack,leaveTempCar);//����Push��ͣ���� 
			}
			printf("\n��Ų���ĳ���ȫ������ԭλ��\n\n");
			
		//	printNewst(PStack,sidewalk);//��ӡ����״̬ 
			
         	if(isEmpty(sidewalk)==0)//������г� ��Ҫ���Ž���ͣ���� 
	        {
		     	printf("\nͣ�������ڳ���һ����λ�����ڰ��ű�������е�һ��������ͣ����...\n",carTemp.num);Sleep(1000);
		     	outQueue(sidewalk,&carTemp);//�����������������
			    int sec2 = time((time_t *)NULL);carTemp.inSecond=sec;time_t timep;time(&timep);
                struct tm *p2; 	p2 = gmtime(&timep);
                snprintf(carTemp.intime, 20, "%d-%d-%d %d:%d:%d", 1900 + p2->tm_year, 1 + p2->tm_mon, p2->tm_mday, 8 + p2->tm_hour, p2->tm_min, p2->tm_sec);
	             Push(PStack,carTemp) ;//��ͣ����
	            printf("\n\t������%s���ѽ���ͣ��������ʼͣ����ʱ��\n\t�볡ʱ��:%s\n\tͣ��:��%d����λ���ӱ����ϼ�����\n",carTemp.num,carTemp.intime,(PStack->top)+1);
	            printf("\nͣ������Ϣ����Ϊ���£�\n");
		    }
		   else
		   {
		         printf("Ŀǰͣ�����ͱ����������£�\n");
		   }
		   printNewst(PStack,sidewalk);//��ӡ����״̬  
		
		
	}
}
