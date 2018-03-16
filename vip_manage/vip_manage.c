
/************************************************
*函数名： void vip_manage()
*功能：显示会员管理菜单
*返回值：NULL
*************************************************/
void vip_manage()
{
    VIP* head=NULL;
int choice;
while(1)
{   
	system("cls");
    printf("========营业员管理=====\n\n");
    printf("1.会员录入\n\n");
    printf("2.会员信息修改\n\n");
    printf("3.会员信息查看\n\n");
    printf("4.会员信息删除\n\n");
    printf("5.返回上一级\n\n");
    printf("=========================\n\n");
	printf("请输入你的选择（1-5）：");
	scanf("%d",&choice);
	getchar();
	switch(choice)
	{
	case 1 :head=vip_add(head);break;
	case 2 :head=vip_read();
       if(head!=NULL)
         head=vip_change(head);
       break;
	case 3 :head=vip_read();
       if(head!=NULL)
         vip_inquire(head);
       break;
	case 4 :head=vip_read();
		if(head!=NULL)
			head=vip_delet(head);
		break;
	default :printf("\n输入错误，请重新输入\n");return;
	}
}
}



/************************************************
*函数名：vip_save（保存）
*功能：将链表（数据）保存在文件
*返回值：NULL
*************************************************/
void vip_save(VIP *head)								
{
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件		
    VIP *t;			//定义一个指针，从头到尾遍历一遍单链表，向文件中写入
    if ((fp=fopen("vip.txt","w"))==NULL)		//打开文件来写入
    {
        printf("打开文件失败！\n");
        getch();     //输入任意键进入下一步
        exit(0);		//退出
    }
    t=head;			//把头指针赋给t，让它从头开始
    while(t!=NULL)	//只要t指针不为空，即等于链表没有结束
    {
       fwrite(t,sizeof(VIP),1,fp);	//把链表写入文件中
       t=t->next;	//指针后移
    }
    fclose(fp);		//把文件关闭
    printf("\n文件保存成功\n");
	printf("\n请按任意键返回主菜单\n");
	getch();	
}






/************************************************
*函数名：vip_read（读取通讯录文件）
*功能：读取文件中的信息并将其放入单链表中，并且最后返回一个头指针
*返回值：VIP *（结构体指针）
*************************************************/
VIP * vip_read()
{
    FILE *fp;	//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    VIP *t1,*t2,*head=NULL;
   
    if((fp=fopen("vip.txt","r"))==NULL)      //判断文件是否存在
    {
        printf("打开文件失败！没有该文件\n\n");
 		printf("请按任意键返回主菜单\n");
        getch();
		return 0;
     }
	rewind(fp);	  //这个函数是把一个文件的位置指针从新移至开头，不然的话会出现一个组数据丢失
    t1=(VIP *) malloc(sizeof(VIP));	//申请动态空间
    head=t2=t1;	//把t1赋给头结点
	
    while(!feof(fp))	//feof函数的功能是判断这个文件是不是结束了，如果结束了，返回一个非零值，否则返回一个0，
    {
        if(fread(t1,sizeof(VIP),1,fp)!=1)	//fread函数返回读出数据项的个数
           break;  //如果没有读取内容，则结束
	
        t1->next=(VIP *)malloc(sizeof(VIP));	//把在申请动态空间的同时，把t1的next指向下一个结点
        t2=t1;     //t2是真正的尾节点
		t1=t1->next;	//t1向后移一个结点
    }
    t2->next=NULL;	
	fclose(fp);		//关闭文件
    return head;	//返回一个头指针，因为在没有创建一个单链表和文件的时候，就是靠这个头指针进行一系列的操作的
}




/***********************************************
*函数名：vip_add（增加）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值：ID *（结构体链表头节点指针）
***********************************************/
VIP* vip_add(VIP *head)
{	
	int k=0,i=0,total=0;
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    VIP *p1,*p2,*tail,*p3,*pa;	
    char saveflag;			//是否保存标志
   	
    if ((fp=fopen("vip.txt","r"))==NULL)		//如果文件不存在就创建
    {
        head=p1=tail=NULL;
		while(1)				//这个循环可以实现多次添加会员
		{
		   p1= (VIP*)malloc(sizeof(VIP));	//给p1分配一个动态存储空间
		   p1->next=NULL;
      bb1: printf("请输入编号(当你不想录入时，在编号处输入0，结束录入):\n");
		   fflush(stdin);
		   scanf("%d",&p1->code);    //输入编号
          if(p1->code==0)	//判断输入的是否为0号，是则结束函数
		  {
            if(total==0)				//当记录人数为0时不创建会员文件
            {
             printf("你输入了0条记录，单链表没有创建...\n");
             free(p1);					//释放p1空间
             return (head);			//把head返回
            }
            else
            {
                break;					//跳出while循环
            }
		  }
		  fflush(stdin);
          printf("请输入会员姓名、性别、电话、生日、消费次数、积分： \n");
          scanf("%s%s%s%s%d%lf",p1->name,p1->sex,p1->tel,p1->birthday,&p1->times,&p1->jifen);
		  p1->name[11]=0;
		  p1->sex[4]=0;
		  p1->tel[11]=0;
		  p1->birthday[8]=0;		 
		  p3=head;		//让p3从头开始遍历
		  while(p3!=NULL)		//当p3不为空时
		  {
				if(p1->code==p3->code)
				{
					free(p1);
					printf("你重复输入了。\n");
					goto bb1;
				}
				p3=p3->next;
			}
		     //使得每个字段都能有效结束
		  fflush(stdin);
		  printf("请输入会员等级(普通会员-1、黄金会员-2、钻石会员-3):\n");
		  scanf("%d",&k);
		  switch(k)
		  {
		  case 1:strcpy(p1->clas,"普通会员");break;
		  case 2:strcpy(p1->clas,"黄金会员");break;
	      case 3:strcpy(p1->clas,"钻石会员");break;
		  default:printf("输入错误！请重新选择");getch;
		  }
		  p1->clas[9]=0;

		  printf("\n\n编号：%d\n",p1->code);
		  printf("会员等级：%s\n",p1->clas);
		  printf("姓名：%s\n",p1->name);
		  printf("性别：%s\n",p1->sex);
		  printf("电话：%s\n",p1->tel);
		  printf("生日：%s\n",p1->birthday);
		  printf("消费次数：%d\n",p1->times);
		  printf("会员积分：%f\n\n",p1->jifen);


	      if(head==NULL)			//这是第一次进来的时候，head为空
		  {
            head=p1;				//head和p2都为p1
            tail=p1;
		  }
          else
          {	
            tail->next=p1;		//第二次以后的执行命令，目的就是p2向后移，而head的位置不变
            tail=p1;
          }
          
        total++;				//录入一个人后，总数就加1
		}
		tail->next=NULL;						//尾指针域赋值为NULL
		free(p1);
		printf("\n新建会员成功\n ");
		getchar();		//这个getchar是吸收回车键的
		vip_save(head);	//将新创建的联系人链表保存到通讯录文件中
	}
	else  //如果文件已存在，则添加会员
	{
	head=vip_read();
    p1=p2=head;			//先让它们都等于头指针
    system("cls");	//清屏
    while(p1->next!=NULL)	//把p1移到尾节点
        p1=p1->next;

bb2:pa=(VIP*)malloc(sizeof(VIP));	//申请动态存储空间
	printf("请输入添加会员的编号:\n");
	fflush(stdin);
    scanf("%d",&pa->code);	
	
	p2=head;		//让p2从头开始遍历
	while(p2!=NULL)		//当p2不为空时
	{
		if(pa->code==p2->code)
		{
			free(pa);
			printf("编号重复输入了。\n");
			goto bb2;
		}
		p2=p2->next;
	}

    printf("请输入会员姓名、性别、电话、生日、消费次数、积分：\n");
	fflush(stdin);
    scanf("%s%s%s%s%d%lf",pa->name,pa->sex,pa->tel,pa->birthday,&pa->times,&pa->jifen);
	pa->name[11]=0;
	pa->sex[4]=0;
	pa->tel[11]=0;
	pa->birthday[8]=0;

	printf("请输入会员等级(普通会员-1、黄金会员-2、钻石会员-3):\n");
	scanf("%d",&k);
	switch(k)
	{
		case 1:strcpy(pa->clas,"普通会员");break;
		case 2:strcpy(pa->clas,"黄金会员");break;
	    case 3:strcpy(pa->clas,"钻石会员");break;
		default:printf("输入错误！请重新选择");getch();
	}
	pa->clas[9]=0;

	printf("\n\n编号：%d\n",pa->code);
	printf("会员等级：%s\n",pa->clas);
    printf("姓名：%s\n",pa->name);
	printf("性别：%s\n",pa->sex);
	printf("电话：%s\n",pa->tel);
	printf("生日：%s\n",pa->birthday);
	printf("消费次数：%d\n",pa->times);
	printf("会员积分：%f\n",pa->jifen);

	p1->next=pa;		//尾节点p1的next添加pa
	pa->next=NULL;
	printf("新添加会员成功,是否存盘?(Y/N)\n");
	fflush(stdin);
	scanf("%c",&saveflag);		//存盘？Y or N
	if(saveflag=='y'||saveflag=='Y')	//当输入y Y的时候
		vip_save(head);		//调用保存函数
	else
	{
		printf("请按任意键返回主菜单\n");
		getch();	
	}
	free(pa);	
  	}		
    return head;		//返回头指针	
}






/************************************************
*函数名：vip_change（修改）
*功能：修改会员信息
*返回值：VIP *（结构体指针）
*************************************************/
VIP* vip_change(VIP* head)
{
    VIP *p1;			
    char saveflag;	
    int k=0,n;
	int flag=0;		//修改标志
    system("cls");		//清屏
	p1=head;		
    printf("请输入要修改的会员编号：\n");	
    scanf("%d",&n);		
    while(p1!=NULL)		//这个while语句的作用是在遍历整个单链表
	{
	   if(p1->code==n)	//判断你输入的名字是不是和通讯录中的相同
	   {
			flag=1;			//当存在一样的名字时，
			printf("\n你要修改的电话记录为:\n");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
    		printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
		printf("\n请输入修改后的信息（除会员编号和等级）:\n");
			fflush(stdin);
            scanf("%s%s%s%s%d%lf",p1->name,p1->sex,p1->tel,p1->birthday,&p1->times,&p1->jifen);
			p1->name[11]=0;
		    p1->sex[4]=0;
		    p1->tel[11]=0;
		    p1->birthday[8]=0;
			printf("\n\n姓名：%s\n",p1->name);
		    printf("性别：%s\n",p1->sex);
		    printf("电话：%s\n",p1->tel);
		    printf("生日：%s\n",p1->birthday);
		    printf("消费次数：%d\n",p1->times);
			printf("会员积分：%f\n\n",p1->jifen);


            printf("请输入会员等级(普通会员-1、黄金会员-2、钻石会员-3):\n");
	        scanf("%d",&k);
	        switch(k)
			{
		       case 1:strcpy(p1->clas,"普通会员");break;
		       case 2:strcpy(p1->clas,"黄金会员");break;
	           case 3:strcpy(p1->clas,"钻石会员");break;
		       default:printf("输入错误！请重新选择");getch();
			}
	        p1->clas[9]=0;
			
			printf("\n\n编号：%d\n",p1->code);
			printf("会员等级：%s\n",p1->clas);
			printf("姓名：%s\n",p1->name);
			printf("性别：%s\n",p1->sex);
			printf("电话：%s\n",p1->tel);
			printf("生日：%s\n",p1->birthday);
			printf("消费次数：%d\n",p1->times);
			printf("会员积分：%f\n\n",p1->jifen);

			printf("该会员信息已修改成功\n");
			printf("通讯人已经新建成功,是否进行保存? (Y/N)\n");
			fflush(stdin);
			scanf("%c",&saveflag);
			if(saveflag=='y'||saveflag=='Y')	//当输入是的时候
				vip_save(head);			//调用保存函数
			else
			{
				printf("请按任意键返回主菜单\n");
				getch();	
			}
			break;
	   }	  
	   p1=p1->next;  //p1指针向后移
	}
    if(flag==0)	//没有这个名字的人，返回主菜单
	{
        printf("\n没有找到要修改的会员编号，请按任意键返回主菜单!\n");
		getch();	//按下任意键就进入下一条语句的函数
    }
	return(head);    
}



/************************************************
*函数名：vip_inquire（会员信息查询系统菜单）
*功能：会员信息查询系统菜单
*返回值：VIP *（结构体指针）
*************************************************/
void vip_inquire(VIP *head)
{
	int i;
	while(1)
	{
		system("cls");
		printf("========会员信息查询系统=========\n\n");
		printf("1.显示所有会员信息\n\n");
		printf("2.搜索指定会员信息\n\n");
		printf("3.分类排序会员信息\n\n");
		printf("4.分类统计会员信息\n\n");
		printf("5.返回上一级\n\n");
		printf("=================================\n\n");
		printf("请输入你想查询的类型：");
		fflush(stdin);
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			head=vip_read();
			if(head!=NULL)
				vip_display(head);
			break;
		case 2:
			head=vip_read();
			if(head!=NULL)
				vip_search(head);
			break;
		case 3:
			head=vip_read();
			if(head!=NULL)
				vip_sort(head);
			break;
		case 4:
			head=vip_read();
			if(head!=NULL)
				vip_statistic(head);
			break;
		case 5:return;
		default:printf("输入错误，请重新输入");
			return;
		}
	}
}





/************************************************
*函数名： vip_display（显示所有会员信息）
*功能：显示所有会员信息信息
*返回值：无返回值
*************************************************/
void vip_display(VIP * head)
{
	VIP *p1=head;
	printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
    while(p1!=NULL)
	{
		printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
		printf("\n");
		p1=p1->next;
	}
	printf("\n\n会员信息成功显示\n");
	printf("\n请按任意键返回主菜单\n");
	getch();

}


/************************************************
*函数名： vip_search（搜索指定会员信息）
*功能：搜索指定会员信息信息
*返回值：无返回值
*************************************************/
void vip_search(VIP* head)
{
	int num;	//子菜单选择
	VIP* p;		
	int flag;	//flag是用来判断是否找到
	int c;
	char t[12];	//c是来存放姓名或者类型，
	while(1)
	{
		system("cls");
		printf("\n**************查找子菜单*******************\n\n");
		printf("1.按编号\n\n");
		printf("2.按电话\n\n");
		printf("3.返回主菜单\n\n");
		printf("*******************************************\n\n");
		fflush(stdin);
		num=4;
		scanf("%d",&num);	//选择你想要查询的方式	
		switch(num)	
		{
		case 1:	
				flag=0;		//初始化为0
				printf("\n请输入待查找的编号: \n");
				scanf("%d",&c);	
				p=head;					
				while(p!=NULL)		
				{
				   if(p->code==c)	
				   {  
					   printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
					   printf("%d      %s      %s       %s    %s     %s     %d    %.2f\n",p->code,p->clas,p->name,p->sex,p->tel,p->birthday,p->times,p->jifen);
					   flag=1;		//flag赋值为1，表示为已经查到了数据了					   
				   }
				   p=p->next;		//p1指针向后移
				}
				if(flag==0)		//表示没有找到相关数据
				{
					printf("\n未能找到符合条件的记录\n");
				}
				printf("\n搜索完成，按任意键返回\n");
				getch();
			break;
		case 2:	
				flag=0;		//初始化为0
				printf("\n请输入待查找的电话: \n");
				scanf("%s",t);	
				p=head;					
				while(p!=NULL)		
				{
				   if(strcmp(p->tel,t)==0)	
				   {  
					   printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
					   printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p->code,p->clas,p->name,p->sex,p->tel,p->birthday,p->times,p->jifen);
					   flag=1;		//flag赋值为1，表示为已经查到了数据了					   
				   }
				   p=p->next;		//p1指针向后移
				}
				if(flag==0)		//表示没有找到相关数据
				{
					printf("\n未能找到符合条件的记录\n");
				}
				printf("\n搜索完成，按任意键返回\n");
				getch();
			break;	
		case 3:return;
		default :printf("你输入错了，请你输入任意键返回查找子菜单...\n");
			     getch();
		}
	}
}





/************************************************
*函数名： vip_sort（分类排序会员信息）
*功能：分类排序会员信息
*返回值：无返回值
*************************************************/
void vip_sort(VIP* head)
{
	int num;	//子菜单选择
	VIP *p1,*p2;		
	while(1)
	{
		p2=NULL;
		system("cls");
		p1=head;
		printf("\n**************排序子菜单*******************\n\n");
		printf("1.按编号排序（从低到高）\n\n");
		printf("2.按消费次数排序（从高到低）\n\n");
		printf("3.按会员积分排序（从高到低）\n\n");
		printf("3.返回主菜单\n\n");
		printf("*******************************************\n\n");

		fflush(stdin);
		scanf("%d",&num);	//选择你想要查询的方式	
		switch(num)	
		{
		case 1:		
			while( head != p2)
			{
				p1 = head;
				while( p1->next!= p2 )
				{  
					if( p1->code > p1->next->code)
					{
						ch_swap(p1->clas,p1->next->clas);
						ch_swap(p1->name,p1->next->name);
						ch_swap(p1->sex,p1->next->sex);
						ch_swap(p1->tel,p1->next->tel);
						ch_swap(p1->birthday,p1->next->birthday);
						in_swap(&p1->code,&p1->next->code);
						in_swap(&p1->times,&p1->next->times);
						db_swap(&p1->jifen,&p1->next->jifen);
					}		
					p1 = p1->next;
				}
				p2= p1;
			}
			system("cls");
			printf("通讯录已按照 编号 排序成功");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			while(p1!=NULL)
			{
				printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
				printf("\n");
				p1=p1->next;
			}
			printf("\n\n排序完成，按任意键返回\n");
			getch();
			break;
		case 2:	
			while( head != p2)
			{
				p1 = head;
				while( p1->next!= p2 )
				{  
					if( p1->times > p1->next->times)
					{
						ch_swap(p1->clas,p1->next->clas);
						ch_swap(p1->name,p1->next->name);
						ch_swap(p1->sex,p1->next->sex);
						ch_swap(p1->tel,p1->next->tel);
						ch_swap(p1->birthday,p1->next->birthday);
						in_swap(&p1->code,&p1->next->code);
						in_swap(&p1->times,&p1->next->times);
						db_swap(&p1->jifen,&p1->next->jifen);
					}		
					p1 = p1->next;
				}
				p2= p1;
			}
			system("cls");
			printf("通讯录已按照 消费次数 排序成功");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			while(p1!=NULL)
			{
				printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
				printf("\n");
				p1=p1->next;
			}
			printf("\n\n排序完成，按任意键返回\n");
			getch();
			break;	
		case 3:
			while( head != p2)
			{
				p1 = head;
				while( p1->next!= p2 )
				{  
					if( p1->jifen > p1->next->jifen)
					{
						ch_swap(p1->clas,p1->next->clas);
						ch_swap(p1->name,p1->next->name);
						ch_swap(p1->sex,p1->next->sex);
						ch_swap(p1->tel,p1->next->tel);
						ch_swap(p1->birthday,p1->next->birthday);
						in_swap(&p1->code,&p1->next->code);
						in_swap(&p1->times,&p1->next->times);
						db_swap(&p1->jifen,&p2->next->jifen);
					}		
					p1 = p1->next;
				}
				p2= p1;
			}
			system("cls");
			printf("通讯录已按照 消费次数 排序成功");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			while(p1!=NULL)
			{
				printf("%d      %s      %s       %s    %s     %s     %d    %.2f",
					p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
				printf("\n");
				p1=p1->next;
			}
			printf("\n\n排序完成，按任意键返回\n");
			getch();
			break;	

		case 4:return;
		default :printf("你输入错了，请你输入任意键返回排序子菜单...\n");
			     getch();
		}
	}
}





/************************************************
*函数名： vip_statistic（分类统计会员信息）
*功能：分类统计会员信息
*返回值：void（无返回值）
*************************************************/
void vip_statistic(VIP* head)
{
	int num;	//子菜单选择
	VIP *p1,*p2;		
	int total;
	p2=NULL;
	while(1)
	{
		system("cls");
		p1=head;
		printf("\n**************统计子菜单*******************\n\n");
		printf("1.统计会员人数\n\n");
		printf("2.统计会员等级\n\n");
		printf("3.返回主菜单\n\n");
		printf("*******************************************\n\n");
		fflush(stdin);
		scanf("%d",&num);	//选择你想要查询的方式	
		switch(num)	
		{
		case 1:
			total=0;
			while(head!=p2)
			{
				p1=head;
				while( p1->next!= p2 )
				{  
					if(p1->code> p1->next->code)
					{
						ch_swap(p1->clas,p1->next->clas);
						ch_swap(p1->name,p1->next->name);
						ch_swap(p1->sex,p1->next->sex);
						ch_swap(p1->tel,p1->next->tel);
						ch_swap(p1->birthday,p1->next->birthday);
						in_swap(&p1->code,&p1->next->code);
						in_swap(&p1->times,&p1->next->times);
						db_swap(&p1->jifen,&p1->next->jifen);
					}
					p1=p1->next;
				}
				p2=p1;
			}
			system("cls");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			while(p1!=NULL)
			{
				printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
				total++;
				printf("\n");
				p1=p1->next;
			}
			printf("\n\n共有会员人数%d人，详细信息如上\n\n",total);
			printf("统计完成，按任意键返回");
			getch();
			break;
		case 2:
			if(head!=0)
				vip_clas(head);
		case 3:
			return;
		default:
			printf("\n输入错误，按任意键返回统计菜单\n");
			getch();
		}
	}
}
			
			
			






/************************************************
*函数名： vip_clas（按照会员等级统计）
*功能：通过选择会员等级统计并显示会员信息
*返回值：void(无返回值) 
*************************************************/
void vip_clas(VIP *head)
{
	VIP *p1;		
	int num,total;
	while(1)
	{
		system("cls");
		p1=head;
		printf("\n**************会员等级选择*******************\n\n");
		printf("1.普通会员\n\n");
		printf("2.黄金会员\n\n");
		printf("3.钻石会员\n\n");
		printf("4.返回上一级\n\n");
		printf("*******************************************\n\n");
		fflush(stdin);
		scanf("%d",&num);	//选择你想要查询的方式	
		switch(num)
		{
		case 1:
			total=0;
			p1=head;
			while( p1!= NULL )
			{  
				if(strcmp(p1->clas,"普通会员")==0)
					total++;
				p1 = p1->next;
			}
			system("cls");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			p1=head;
			while(p1!=NULL)
			{
				if(strcmp(p1->clas,"普通会员")==0)
				{
					printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
					printf("\n");
				}
				p1=p1->next;
			}
			printf("\n共有普通会员人数%d人，详细信息如上\n",total);
			printf("\n统计完成，按任意键返回\n");
			getch();
			break;
		case 2:
			total=0;
			p1 = head;
			while( p1!=NULL )
			{  
				if(strcmp(p1->clas,"黄金会员")==0)
					total++;
				p1=p1->next;
			}
			system("cls");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			p1=head;
			while(p1!=NULL)
			{
				if(strcmp(p1->clas,"黄金会员")==0)
				{
					printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
					printf("\n");
				}
				p1=p1->next;
			}
			printf("\n\n共有黄金会员人数%d人，详细信息如上\n\n",total);
			printf("统计完成，按任意键返回");
			getch();
			break;
		case 3:
			total=0;
			p1 = head;
			while( p1!= NULL )
			{  
				if(strcmp(p1->clas,"钻石会员")==0)
					total++;
				p1=p1->next;
			}
			system("cls");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			p1=head;
			while(p1!=NULL)
			{
				if(strcmp(p1->clas,"钻石会员")==0)
				{
					printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
					printf("\n");
				}
				p1=p1->next;
			}
			printf("共有钻石会员人数%d人，详细信息如上",total);
			printf("统计完成，按任意键返回");
			getch();
			break;
		case 4:return;
		default:
			printf("\n输入错误，按任意键返回选择菜单\n");
			getch();
		}
	}
}






/************************************************
*函数名： vip_delet（删除）
*功能：通过查找编号来实现删除会员记录
*返回值：VIP *（结构体指针）
*************************************************/
VIP* vip_delet(VIP *head)
{
    VIP *p1,*p2;		//p1是用来遍历整一个单链表定位要删除的结点，p2是用来定位p1的前结点的
    char saveflag='n', temp;		//saveflag是否保存，temp是否删除
	int k;				//存放k输入的编号		
    p1=p2=head;		//把head赋给p1,p2,p3    
	system("cls");
    printf("\n请输入要删除的编号:\n");
    scanf("%d",&k);
	getchar();
	while(p1!=NULL)		//这个while语句的作用是在遍历整个单链表时，当遇到一样的名字时把i赋值，引导下面的工作
	{
	   if(p1->code==k)	//判断是不是你输入的编号是不是和文本中的相等
	   {
			printf("你要删除的会员为:\n");
			printf("\n编号===会员等级====姓名====性别=======电话=========生日=======消费次数===积分===\n\n");
			printf("%d      %s      %s       %s    %s     %s     %d    %.2f",p1->code,p1->clas,p1->name,p1->sex,p1->tel,p1->birthday,p1->times,p1->jifen);
			printf("请确定是否要删除该记录？Y/N?\n");
			fflush(stdin);
			scanf("%c",&temp);		//确定要删除吗？			
			if(temp=='y'||temp=='Y')	//当输入是的时候
			 {
			   if(p1==head)		//判断是不是在头结点
				   head=p1->next;	//把头结点去掉
			   else
                p2->next=p1->next;	//删除p1结点（p2的next域指向p1的下个结点）
			   printf("该会员已删除成功,是否存盘?Y/N?\n");
			   fflush(stdin);
			   scanf("%c",&saveflag);		//确定要保存吗？
			   if(saveflag=='y'||saveflag=='Y')	//当输入是的时候
				  vip_save(head);			//调用保存函数
			   else
				{
					printf("请按任意键返回主菜单\n");
					getch();	
				}
			}
			else
			{
				printf("请按任意键返回主菜单\n");
				getch();	
			}
	   break;
	   }
	   p2=p1;
	   p1=p1->next;  //p1指针向后移
	   if((p1->next)==NULL)
	   {
		   printf("没有找到要删除的会员，请检查你要删除的会员编号是否正确\n");
		   printf("按任意键返回重新输入\n");
		   getch();
		   break;	//按下任意键就进入下一条语句的函数			
	   }
	}
	return(head);		//return一个已经完成修改的链表头指针   
}



