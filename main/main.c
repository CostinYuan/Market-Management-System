#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//商品结构体
struct good
{
	long int code;  //商品编号
    char name [20];  //商品名称
    int count;  //商品余量
    int sell;  //商品销量
    double price;  //商品价格
    double discount;  //商品折扣
    int yy,mm,dd;  //商品保质期
    char madein[10];  //商品产地
    struct good *next;  //指针节点
};
typedef struct good GOD;

//会员结构体
struct vip
{
	int code;  //会员编号
    char clas[10];  //会员等级
    char name[12];  //会员姓名
    char sex[5];  //会员性别
    char tel[12];  //会员电话
    char birthday[9];  //会员生日
    int times;  //会员消费次数
	double jifen;  //会员积分
    struct vip *next;  //指针节点
};
typedef struct vip VIP ;

//购物车结构体
struct cart
{
	int num;  //会员编号
	char clas[10];  //会员等级
	char vip[12];  //会员姓名
	int code;  //商品编号
	char good[20];  //商品名称
    double price;  //商品价格
    double discount;  //商品折扣
	int count;  //商品数量
	struct cart *next;  //指针节点
};
typedef struct cart CART;




//各函数声明
void denglu(char zhanghao[],char mima[]);

void good_save(GOD *head);  //保存信息至文本
void vip_save(VIP *head);
void cart_save(CART *head);

GOD *good_read();  //读取文本
VIP *vip_read();
CART *cart_read();

void ch_swap(char t1[],char t2[]);  //交换字符串
void in_swap(int *t1,int *t2);  //整形变量交换
void db_swap(double *t1,double *t2);  //离散变量交换


void shopstuff_enter();  // 1收银员登录，进入收银界面

CART* cart_add(VIP *head1,GOD *head2);
CART* cart_printf(GOD *head2);
double cart_calculate(CART *pt);
void cart_view(CART *head);

void manage_menu();  // 2->管理员登录 管理员菜单

void good_manage();  // 2.1-->商品管理菜单
GOD *good_add(GOD *head);  // 2.1.1商品信息录入
GOD *good_change(GOD *head);  //2.1.2商品信息修改
void good_printf(GOD* head);   //2.1.3商品信息显示
void good_search(GOD *head);  // 2.1.4商品信息查找
GOD *good_delet(GOD *head);  // 2.1.5商品信息删除
void good_sort(GOD *head);    //2.1.6商品信息排序查看

void vip_manage();  // 2.2-->会员管理菜单
VIP *vip_add(VIP *head);  // 2.2.1营业员信息录入
VIP *vip_change(VIP *head);  // 2.2.2营业员信息修改
void vip_inquire(VIP *head);  // 2.2.3营业员信息查看
  void vip_display(VIP * head);  //2.2.3.1显示所有会员信息
  void vip_search(VIP* head);  //2.2.3.2搜索指定会员信息
  void vip_sort(VIP* head);  //2.2.3.3分类排序会员信息
  void vip_statistic(VIP* head);  //2.2.3.4分类统计会员信息
  void vip_clas(VIP *head);  //2.2.3.4.1按会员等级统计
VIP *vip_delet(VIP *head);  // 2.2.4营业员信息删除

/**************************************************************
void smart_manage();  // 2.3-->智能管理
void good_overview();  // 2.3.1商品状态总览
void vip_overview();  // 2.3.2会员状态总览
void good_warning();  // 2.3.3商品问题提醒
void vip_warning();  //2.3.4会员生日提醒
***********************************************************/



#include"C:\Documents and Settings\Administrator\桌面\20170417b\good_manage\good_manage.c"
#include"C:\Documents and Settings\Administrator\桌面\20170417b\vip_manage\vip_manage.c"
#include"C:\Documents and Settings\Administrator\桌面\20170417b\cart\cart.c"


/************************************************
*函数名： main(主函数)
*功能：显示主菜单
*返回值：NULL
*************************************************/
void main()
{
	int choice;
	char  zhanghao[80]={0},mima[20]={0};
	GOD *head=NULL;
zhu:while(1)
	{
		system("cls");
		printf("\n========中商超市管理系统=====\n\n");
		printf("1.营业员登陆\n\n");
		printf("2.管理员登陆\n\n");
		printf("3.退出管理系统\n\n");
		printf("=========================\n\n");
		printf("请输入你的选择（1-3）：");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
		case 1 :/*denglu(zhanghao,mima);
			if(strcmp(zhanghao,"shopassistant")==0&&strcmp(mima,"123456")==0)*/
			{
				head=good_read();  //读取商品文件子函数
				if(head!=NULL);
				shopstuff_enter();  //进入营业员子函数
			}
			/*else
			{
				printf("\n\t营业员帐号或者密码错误\n\n");getch();
				goto zhu;
			}*/
			break;
		case 2 :/*denglu(zhanghao,mima);
			if(strcmp(zhanghao,"administor")==0&&strcmp(mima,"123456")==0)*/
			{
				manage_menu(); //进入管理菜单子函数
			}
			/*else
			{
				printf("\n\t营业员帐号或者密码错误\n\n");
				getch();
				goto zhu;
			}*/
			break;
		case 3 :exit(0);break;  //退出
		default :printf("\n输入错误，请重新输入！\n");
			getch();
		}
	}
}


/************************************************
*函数名： manage_menu()
*功能：显示管理员菜单
*返回值：NULL
*************************************************/
void manage_menu()
{
int choice;
while(1)
{   system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\n========欢迎使用中商商品管理系统=======\n\n");
    printf("1.商品管理\n\n");
    printf("2.会员管理\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("3.智能管理（建设中）\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("4.退出登录\n\n");
    printf("=========================================\n\n");
printf("请输入你的选择（1-4）：");
scanf("%d",&choice);
getchar();
switch(choice)
        {
         case 1 :good_manage();break;  //进入商品管理子菜单子函数
         case 2 :vip_manage();break;  //进入会员管理菜单子函数
         /*case 3 :smart_manage();break;  //进入智能管理菜单子函数*/
         case 4 :return;  //退出登录 返回主函数
         default :printf("\n 输入错误，请重新输入！");getch();
        }
     }
}


/************************************************
*函数名:denglu
*功能：显示管理员菜单
*返回值：NULL
*************************************************/
void denglu(char zhanghao[],char mima[])
{

	printf("\n请输入你的帐号：");
	fflush(stdin);
	gets(zhanghao);
	printf("请输入你的密码：");
	fflush(stdin);
	gets(mima);
}


/************************************************
*函数名： ch_swap（交换）
*功能：交换结点内数据
*返回值：无
*************************************************/
void ch_swap(char t1[],char t2[])   //交换char型数据
{
	char t[20]={0};
	strcpy(t,t1);
	strcpy(t1,t2);
	strcpy(t2,t);
}


/************************************************
*函数名： in_swap（交换）
*功能：交换结点内数据
*返回值：无
*************************************************/
void in_swap(int *t1,int *t2)   //交换int型数据
{
	int t=*t1;
	*t1=*t2;
	*t2=t;
}


/************************************************
*函数名： db_swap（交换）
*功能：交换结点内数据
*返回值：无
*************************************************/
void db_swap(double *t1,double *t2)   //交换int型数据
{
	double t=*t1;
	*t1=*t2;
	*t2=t;
}

