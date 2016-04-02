#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct {         //定义顺序表结构
int *elem;               //存储数组初始地址
int length;         //当前长度
int listsize;     //最大容量
}SqList;

int InitList(SqList *L) //初始化新的顺序表
{
          L->elem = (int *)malloc(MAX*sizeof(int));
          if(!L->elem)                                 //分配内存失败
              exit(0);
          L->length = 0;                 //初始化长度为0
          L->listsize = MAX;         //最大容量
          return 1;                     //构造成功返回1
}
void Creatlist(SqList *L)   //手动输入生成顺序表
{
     int i,n=0,s;
    printf("请输入所输入数组长度:\n");
    scanf("%d",&s);
      for(i = 0; i < s; i++ ) //由用户输入数据生成顺序表
         {
             scanf("%d",&n);
             L->elem[i] = n;
         }
     L->length = i;
     printf("输入成功！\n");   //返回当前长度
}

void SortList(SqList *L) //用冒泡排序对输入表进行排序
{
    int i,j,k=0;
    for(i = 0; i < L->length ;i++)
        for(j = i;j < L->length ;j++)
    if(L->elem[i] > L->elem[j])   //升序排列，交换元素
       {
          k = L->elem[i];
          L->elem[i] = L->elem[j];
           L->elem[j] = k;
       }
}

void TailInsert(SqList *L)//实现在表尾插入元素
{
    int num;
    char ch;
    do{
    printf("请输入要插入表末的元素：\n");
    scanf("%d",&num);
    getchar();
    L->elem[L->length]=num;//把num添加到表尾
    (L->length)++; //表长加1
    printf("是否继续插入？（Y/N）\n");//输入y继续插入
    scanf("%c",&ch);
    getchar();
    }while(ch=='y'||ch=='Y');
}
int DeleteElem(SqList *L,int i)//实现删除索引值为i的元素
{
    int j;
    if(i<1||i>L->length)//判断i是否有效
        printf("参数输入错误 索引值出错\n");

    for(j=i;j<L->length-1;j++)//在索引值为i元素后的元素都往前一位
        L->elem[j]=L->elem[j+1];
    L->length--;//表长减一
    return L->elem[i];//返回所删除元素
}



int PrintElem(SqList *L,int i)//实现打印索引值为i的元素
{
    if(i<1||i>L->length)//判断i是否有效
        printf("参数输入错误 索引值出错\n");
        else
    printf("索引值为%d的元素是%d\n",i,L->elem[i]);
    return L->elem[i];
}
int PrintLength(SqList *L)//实现打印表长
{

    printf("求表长函数测试：\n");
    printf("%d\n",L->length);
    return L->length;
}
void PrintList(SqList *L)   //实现输出顺序表
{
   int i;
   for(i=0;i<L->length;i++)
      printf("%d   ",L->elem[i]);
   printf("\n");
}
void Merge(SqList *La,SqList *Lb,SqList *Lc)//实现合并La与Lb到Lc
{

    int *pa,*pb,*pc,*pa_last,*pb_last;
    pa=La->elem;
    pb=Lb->elem;
    /*printf("*pa:%d\n",*pa);
    printf("*pb:%d\n",*pb);*/
    Lc->length=Lc->listsize=La->length+Lb->length;//把Lc的长度设置为La的长度与Lb的长度之和
    pc=Lc->elem=(int *)malloc(Lc->listsize*sizeof(int));//分配内存到数组并初始化pc指向数组初始地址
    if(!Lc->elem) exit(0);//分配失败就退出
    pa_last=La->elem+(La->length-1);//设置La表尾
    pb_last=Lb->elem+(Lb->length-1);//设置Lb表尾
    /*printf("*pa_last:%d\n",*pa_last);
    printf("*pb_last:%d\n",*pb_last);*/
    while(pa<=pa_last&&pb<=pb_last)//pa与pb都没有越界时进行循环
    {
      /*  printf("当前*pa:%d\n",*pa);
        printf("当前*pb:%d\n",*pb);*/
        if(*pa<= *pb) *pc++=*pa++;//La的元素小雨Lb的元素则把La元素放到Lc中，然后pa和pc指向下一个元素
        else *pc++=*pb++;}//否则就将Lb元素进行相同操作
        while(pa<=pa_last)*pc++=*pa++;//把剩下的元素插入
        while(pb<=pb_last)*pc++=*pb++;

}
/*void Union(SqList *La,SqList *Lb)//算法2.1
{
		int i,e;
		for(i=0;i<Lb->length;i++)
		{
			e=Lb->elem[i];//提取表b中元素赋给e
			if(LocateElem(La,e)==-1)//若在表a找不到元素e
				Insert(La,La->length,e);//按照算法2.1是把表b中表a没有的元素插到表a最后

			}

	}*/

	/*void MergeList(SqList *La,SqList *Lb,SqList *Lc)    // 算法2.2
{
     int i=0,j=0,k=0;//初始索引值为0
      Lc->listsize = Lc->length = La->length + Lb->length ;   //C表的实际长度
       Lc->elem = (int *)malloc(Lc->length*sizeof(int));
          if(!Lc->elem)   exit(0);//内存分配不足
   while(i < La->length && j < Lb->length )    //合并
         {
              if(La->elem[i] <= Lb->elem[j])//表a i元素小于等于表b j元素时
                Lc->elem[k++] = La->elem[i++];//表a i元素插入表c后自增到下一个元素
              else
                 Lc->elem[k++] = Lb->elem[j++];
         }
   while(i < (La->length))    //若a表剩余则直接并归
           Lc->elem[k++] = La->elem[i++];

    while(j < (Lb->length) )    //若b表剩余也直接并归
             Lc->elem[k++] = Lb->elem[j++];

}*/
void Insert (SqList *L,int i , int e)//插入元素e
	{
		int j;
		if(i<1||i>L->length+1)//判断i是否有效
			printf("插入失败");
			for(j=L->length;j>i;j--)//在索引值为i后面的元素都往后推一个
			L->elem[j]=L->elem[j-1];

			L->elem[i] =e;
			L->length++;

		}

		int LocateElem(SqList *L,int e)//在表中查找元素
		{
			int i;
			for(i=0;i<L->length;i++)
			if(L->elem[i]==e)
				{
				    return i;//若能找到返回索引值
                    break;
			}
			return -1;//若找不到则返回-1
			}
int main()
{
    char ch;      //读取字符用于判断程序的结束或继续
    SqList la,lb,lc;
    int i,e,o,example,temp,tem;
while(o!=0)
{//构造好菜单
    printf("(1)初始化顺序表\n");
    printf("(2)表尾插入元素\n");
    printf("(3)求表长的函数\n");
    printf("(4)输出位置i的元素\n");
    printf("(5)第i位置前插入元素\n");
    printf("(6)删除位置i的元素\n");
    printf("(7)输出顺序表\n");
    printf("(8)合并顺序表La和Lb到Lc\n");
    printf("(0)退出\n");

  scanf("%d",&o);
  switch(o)//用switch语句测试菜单中各项的功能
  {
  case 1:
    if(InitList(&la))
    {
        printf("初始化La成功\n");
        printf("La:\n");
           Creatlist(&la);
           SortList( &la);
    }
    if(InitList(&lb))      //生成b表
       {
        printf("初始化Lb成功\n");
        printf("Lb:\n");
        Creatlist( &lb);
        SortList( &lb);
       }
       getchar();

       break;
  case 2:
    printf("在La末尾插入元素：\n");
    TailInsert(&la);
    getchar();

    break;
  case 3:
    printf("La表长：");
     PrintLength(&la);
     printf("Lb表长：");
     PrintLength(&lb);
     getchar();

    break;
  case 4:
      printf("打印索引值为多少的元素：\n");
      scanf("%d",&temp);
    PrintElem(&la,temp);
    getchar();

    break;
  case 5:
      printf("请输入需要插入元素的索引值：\n");
      scanf("%d",&temp);
      printf("请输入需要插入的元素：\n");
       scanf("%d",&tem);
    Insert(&la,temp,tem);
    getchar();

    break;
  case 6:
    printf("删除La索引值为多少的元素:\n");
    scanf("%d",&temp);
    DeleteElem(&la,temp);
    getchar();

    break;
  case 7:
    printf("输出线性表La:\n");
    PrintList(&la);
    printf("输出线性表Lb:\n");
    PrintList(&lb);
    getchar();
    break;
  case 8:
    printf("测试合并函数算法2.7\n");
    Merge(&la,&lb,&lc);
    printf("合并后Lc：\n");
    PrintList(&lc);
    getchar();
    break;

  case 9:
    printf("查找元素:\n");
    scanf("%d",&example);
    if(LocateElem(&lc,example)==-1)
        printf("找不到啊\n");
    else
    printf("找到的索引值为：%d",LocateElem(&lc,example));
 case 0:
    break;
 default:
    printf("输入有误！\n");
  }

    //system("cls"); //清除屏幕

}
return 0 ;
}
