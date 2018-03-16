#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
//��Ʒ�ṹ��
struct good
{
	long int code;  //��Ʒ���
    char name [20];  //��Ʒ����
    int count;  //��Ʒ����
    int sell;  //��Ʒ����
    double price;  //��Ʒ�۸�
    double discount;  //��Ʒ�ۿ�
    int yy,mm,dd;  //��Ʒ������
    char madein[10];  //��Ʒ����
    struct good *next;  //ָ��ڵ�
};
typedef struct good GOD;

//��Ա�ṹ��
struct vip
{
	int code;  //��Ա���
    char clas[10];  //��Ա�ȼ�
    char name[12];  //��Ա����
    char sex[5];  //��Ա�Ա�
    char tel[12];  //��Ա�绰
    char birthday[9];  //��Ա����
    int times;  //��Ա���Ѵ���
	double jifen;  //��Ա����
    struct vip *next;  //ָ��ڵ�
};
typedef struct vip VIP ;

//���ﳵ�ṹ��
struct cart
{
	int num;  //��Ա���
	char clas[10];  //��Ա�ȼ�
	char vip[12];  //��Ա����
	int code;  //��Ʒ���
	char good[20];  //��Ʒ����
    double price;  //��Ʒ�۸�
    double discount;  //��Ʒ�ۿ�
	int count;  //��Ʒ����
	struct cart *next;  //ָ��ڵ�
};
typedef struct cart CART;




//����������
void denglu(char zhanghao[],char mima[]);

void good_save(GOD *head);  //������Ϣ���ı�
void vip_save(VIP *head);
void cart_save(CART *head);

GOD *good_read();  //��ȡ�ı�
VIP *vip_read();
CART *cart_read();

void ch_swap(char t1[],char t2[]);  //�����ַ���
void in_swap(int *t1,int *t2);  //���α�������
void db_swap(double *t1,double *t2);  //��ɢ��������


void shopstuff_enter();  // 1����Ա��¼��������������

CART* cart_add(VIP *head1,GOD *head2);
CART* cart_printf(GOD *head2);
double cart_calculate(CART *pt);
void cart_view(CART *head);

void manage_menu();  // 2->����Ա��¼ ����Ա�˵�

void good_manage();  // 2.1-->��Ʒ����˵�
GOD *good_add(GOD *head);  // 2.1.1��Ʒ��Ϣ¼��
GOD *good_change(GOD *head);  //2.1.2��Ʒ��Ϣ�޸�
void good_printf(GOD* head);   //2.1.3��Ʒ��Ϣ��ʾ
void good_search(GOD *head);  // 2.1.4��Ʒ��Ϣ����
GOD *good_delet(GOD *head);  // 2.1.5��Ʒ��Ϣɾ��
void good_sort(GOD *head);    //2.1.6��Ʒ��Ϣ����鿴

void vip_manage();  // 2.2-->��Ա����˵�
VIP *vip_add(VIP *head);  // 2.2.1ӪҵԱ��Ϣ¼��
VIP *vip_change(VIP *head);  // 2.2.2ӪҵԱ��Ϣ�޸�
void vip_inquire(VIP *head);  // 2.2.3ӪҵԱ��Ϣ�鿴
  void vip_display(VIP * head);  //2.2.3.1��ʾ���л�Ա��Ϣ
  void vip_search(VIP* head);  //2.2.3.2����ָ����Ա��Ϣ
  void vip_sort(VIP* head);  //2.2.3.3���������Ա��Ϣ
  void vip_statistic(VIP* head);  //2.2.3.4����ͳ�ƻ�Ա��Ϣ
  void vip_clas(VIP *head);  //2.2.3.4.1����Ա�ȼ�ͳ��
VIP *vip_delet(VIP *head);  // 2.2.4ӪҵԱ��Ϣɾ��

/**************************************************************
void smart_manage();  // 2.3-->���ܹ���
void good_overview();  // 2.3.1��Ʒ״̬����
void vip_overview();  // 2.3.2��Ա״̬����
void good_warning();  // 2.3.3��Ʒ��������
void vip_warning();  //2.3.4��Ա��������
***********************************************************/



#include"C:\Documents and Settings\Administrator\����\20170417b\good_manage\good_manage.c"
#include"C:\Documents and Settings\Administrator\����\20170417b\vip_manage\vip_manage.c"
#include"C:\Documents and Settings\Administrator\����\20170417b\cart\cart.c"


/************************************************
*�������� main(������)
*���ܣ���ʾ���˵�
*����ֵ��NULL
*************************************************/
void main()
{
	int choice;
	char  zhanghao[80]={0},mima[20]={0};
	GOD *head=NULL;
zhu:while(1)
	{
		system("cls");
		printf("\n========���̳��й���ϵͳ=====\n\n");
		printf("1.ӪҵԱ��½\n\n");
		printf("2.����Ա��½\n\n");
		printf("3.�˳�����ϵͳ\n\n");
		printf("=========================\n\n");
		printf("���������ѡ��1-3����");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
		case 1 :/*denglu(zhanghao,mima);
			if(strcmp(zhanghao,"shopassistant")==0&&strcmp(mima,"123456")==0)*/
			{
				head=good_read();  //��ȡ��Ʒ�ļ��Ӻ���
				if(head!=NULL);
				shopstuff_enter();  //����ӪҵԱ�Ӻ���
			}
			/*else
			{
				printf("\n\tӪҵԱ�ʺŻ����������\n\n");getch();
				goto zhu;
			}*/
			break;
		case 2 :/*denglu(zhanghao,mima);
			if(strcmp(zhanghao,"administor")==0&&strcmp(mima,"123456")==0)*/
			{
				manage_menu(); //�������˵��Ӻ���
			}
			/*else
			{
				printf("\n\tӪҵԱ�ʺŻ����������\n\n");
				getch();
				goto zhu;
			}*/
			break;
		case 3 :exit(0);break;  //�˳�
		default :printf("\n����������������룡\n");
			getch();
		}
	}
}


/************************************************
*�������� manage_menu()
*���ܣ���ʾ����Ա�˵�
*����ֵ��NULL
*************************************************/
void manage_menu()
{
int choice;
while(1)
{   system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\n========��ӭʹ��������Ʒ����ϵͳ=======\n\n");
    printf("1.��Ʒ����\n\n");
    printf("2.��Ա����\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("3.���ܹ��������У�\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("4.�˳���¼\n\n");
    printf("=========================================\n\n");
printf("���������ѡ��1-4����");
scanf("%d",&choice);
getchar();
switch(choice)
        {
         case 1 :good_manage();break;  //������Ʒ�����Ӳ˵��Ӻ���
         case 2 :vip_manage();break;  //�����Ա����˵��Ӻ���
         /*case 3 :smart_manage();break;  //�������ܹ���˵��Ӻ���*/
         case 4 :return;  //�˳���¼ ����������
         default :printf("\n ����������������룡");getch();
        }
     }
}


/************************************************
*������:denglu
*���ܣ���ʾ����Ա�˵�
*����ֵ��NULL
*************************************************/
void denglu(char zhanghao[],char mima[])
{

	printf("\n����������ʺţ�");
	fflush(stdin);
	gets(zhanghao);
	printf("������������룺");
	fflush(stdin);
	gets(mima);
}


/************************************************
*�������� ch_swap��������
*���ܣ��������������
*����ֵ����
*************************************************/
void ch_swap(char t1[],char t2[])   //����char������
{
	char t[20]={0};
	strcpy(t,t1);
	strcpy(t1,t2);
	strcpy(t2,t);
}


/************************************************
*�������� in_swap��������
*���ܣ��������������
*����ֵ����
*************************************************/
void in_swap(int *t1,int *t2)   //����int������
{
	int t=*t1;
	*t1=*t2;
	*t2=t;
}


/************************************************
*�������� db_swap��������
*���ܣ��������������
*����ֵ����
*************************************************/
void db_swap(double *t1,double *t2)   //����int������
{
	double t=*t1;
	*t1=*t2;
	*t2=t;
}

