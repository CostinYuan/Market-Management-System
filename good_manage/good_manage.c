void good_manage()
{
    GOD *head=NULL;
	int choice;
while(1)
{   system("cls");
    printf("\n\n");
    printf("========商品管理=====\n");
    printf("1.商品信息录入\n");
    printf("2.商品信息修改\n");
    printf("3.商品全部信息显示\n");
    printf("4.商品信息查找\n");
    printf("5.商品信息删除\n");
	printf("6.商品信息排序查看\n");
    printf("7.返回上一级\n");
    printf("=========================\n\n");
printf("请输入你的选择（1-7）：");
scanf("%d",&choice);
getchar();
switch(choice)
{
case 1 :head=good_add(head);break;
case 2 :head=good_read();
       if(head==NULL)
		   printf("\n请先选择1.录入商品信息\n");
	   else
		   head=good_change(head);
       break;
case 3 :head=good_read(head);
        if(head==NULL)
		   printf("\n请先选择1.录入商品信息\n");
	    else
		   good_printf(head);
        break;
case 4 :head=good_read(head);
       if(head==NULL)
		   printf("\n请先选择1  创建链表\n");
	   else
		   good_search(head);
       break;
case 5 :head=good_read(head);
        if(head==NULL)
		    printf("\n请先选择1  创建链表\n");
	    else
            head=good_delet(head);
        break;
case 6 :head=good_read(head);
	    if(head==NULL)
		    printf("\n请先选择1  创建链表\n");
	    else
            good_sort(head);
        break;
case 7 :return;
default:printf("\n输入错误，请重新输入\n");
              getch();
  }
}
}





GOD *good_add(GOD *head)  // 2.1.1商品信息录入
{	int k=0,i=0,total=0;
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    GOD *p1,*tail,*p3,*p2,*pa;	//pa是用来放添加的信息的
    char saveflag;			//这个字符用来接收是否保存
   	
    if ((fp=fopen("good.txt","r"))==NULL)		//如果文件不存在就创建
    {
        head=p1=tail=NULL;
		while(1)				//这个循环可以实现多次添加商品信息
		{
		   p1= (GOD*)malloc(sizeof(GOD));	//给p1分配一个动态存储空间
		   p1->next=NULL;
      bb1: printf("\n请输入编号(当你不想录入时，在编号处输入0，结束录入):\n");
		   fflush(stdin);
		   scanf("%d",&p1->code);			//输入编号
          if(p1->code==0)	//判断输入的是否为0号，结束函数
		  {
            if(total==0)				//当记录人数为0时不创建商品信息文件
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
          printf("请输入其他信息(按名称，余量，销量，价格，折扣，保质期(年月日)，产地输入):\n");
          scanf("%s%d%d%lf%lf%d%d%d%s",p1->name,&p1->count,&p1->sell,&p1->price,&p1->discount,&p1->yy,&p1->mm,&p1->dd,p1->madein);
		  p1->name[19]=0;
		  p1->madein[9]=0;

		  p3=head;		//让p3从头开始遍历
		  while(p3!=NULL)		//当p3不为空时
		  {		if(p1->code==p3->code)
				{	free(p1);
					printf("你重复输入了。\n");
					goto bb1;
				}
				p3=p3->next;
		  }
	      if(head==NULL)			//这是第一次进来的时候，head为空
		  {
            head=p1;				//head和p2都为p1
            tail=p1;
		  }
          else
          {	
            tail->next=p1;		//这是第二次以后的执行命令，目的就是p2向后移，而head的位置不变
            tail=p1;
          }
         total++;				//这是录入一个人后，总数就加1
		}
		tail->next=NULL;				//尾指针域赋值为NULL			
		free(p1);
		printf("\n新建商品信息文件成功，共有%d种商品\n ",total);
		good_save(head);	//将新创建的商品链表保存到GOD文件中
	}
	
	
	else 
	{
		head=good_read();
	    p1=p2=head;			//先让它们都等于头指针
		system("cls");	//清屏
		while(p1->next!=NULL)	//把p1移到尾节点
        p1=p1->next;
bb2:pa=(GOD*)malloc(sizeof(GOD));	//申请动态存储空间
	printf("请输入添加人的编号:\n");
	fflush(stdin);
    scanf("%d",&pa->code);
	while(p2!=NULL)		//当p2不为空时
	{	if(pa->code==p2->code)
		{	free(pa);
			printf("你重复输入了。\n");
			goto bb2;
		}
		p2=p2->next;
	}
	p1->next=pa;		//尾节点p1的next添加pa
	pa->next=NULL;
    printf("\n请输入其他信息(按名称，余量，销量，价格，折扣，保质期(年月日)，产地输入)： \n");    		  
	fflush(stdin);
    scanf("%s%d%d%lf%lf%d%d%d%s",pa->name,&pa->count,&pa->sell,&pa->price,&pa->discount,&pa->yy,&pa->mm,&pa->dd,pa->madein);
    p1->name[19]=0;
    p1->madein[9]=0;
	printf("新添加商品信息成功,是否存盘?(Y/N)\n");
	fflush(stdin);
	scanf("%c",&saveflag);		//输入，存放Y or N
	if(saveflag=='y'||saveflag=='Y')	//当输入是的时候
		good_save(head);		//调用保存函数
	else
	{	printf("请按任意键返回主菜单\n");
		getch();	
	}
	free(pa);
	} 
	return(head);
}



/************************************************
*函数名：good_save(GOD *head)	//保存文件
*功能：将链表（数据）保存在文件
*返回值：NULL
*************************************************/
void good_save(GOD *head)	//保存文件							
{
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件		
    GOD* t ;			//定义一个指针，从头到尾遍历一遍单链表，向文件中写入
    if ((fp=fopen("good.txt","w"))==NULL)		//打开文件来写入
    {
        printf("打开文件失败！\n");
        getch();     //输入任意键进入下一步
        exit(0);		//退出
    }
    t=head;			//把头指针赋给t，让它从头开始
    while(t!=NULL)	//只要t指针不为空，即等于链表没有结束
    {
       fwrite(t,sizeof(GOD),1,fp);	//把链表写入文件中
       t=t->next;	//指针后移
    }
    fclose(fp);		//把文件关闭
    printf("\n保存成功\n");
	getch();	
}


/************************************************
*函数名：good_read（读取商品信息文件）
*功能：读取文件中的信息并将其放入单链表中，并且最后返回一个头指针
*返回值：GOD *（结构体指针）
*************************************************/
GOD *good_read(GOD *head)        //读取商品信息文件 
{    FILE *fp;	//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    GOD *t1,*t2,*h=NULL;
    if((fp=fopen("good.txt","r"))==NULL)      //判断文件是否存在
    {   printf("打开文件失败！没有该文件\n\n");
 		printf("请按任意键返回主菜单\n");
        getch();
		return 0;
     }
	rewind(fp);	  //这个函数是把一个文件的位置指针从新移至开头，不然的话会出现一个组数据丢失
    t1=(GOD *) malloc(sizeof(GOD));	//申请动态空间
    head=t2=t1;	//把t1赋给头结点
	 while(!feof(fp))	//feof函数的功能是判断文件是不是结束，如果结束了，返回非零值，否则返回0，
    {   if(fread(t1,sizeof(GOD),1,fp)!=1)	//fread函数返回读出数据项的个数
            break;  //如果没有读取内容，则结束
	    t1->next=(GOD *)malloc(sizeof(GOD));	//在申请动态空间的同时，把t1的next指向下一个结点
        t2=t1;     //t2是真正的尾节点
		t1=t1->next;	//t1向后移一个结点
    }
    t2->next=NULL;	
	fclose(fp);		//关闭文件
return head;	//返回头指针
}


/************************************************
*函数名：void good_printf()  // 1.1显示商品信息
*功能：显示商品信息
*返回值：无返回值
*************************************************/
void good_printf(GOD *head)  // 1.1显示商品信息
{
	GOD *p1=head;
	int i=0;
	printf("\n编号   名称   余量   销量   价格  折扣  保质期(年月日)   产地\n\n");
    while(p1!=NULL)
	{
		printf("%d      %s      %d      %d      %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		i++;
	}
	printf("\n\n商品信息成功显示\n");
	printf("\n共有%d件商品\n",i);
	getch();
}

/************************************************
*函数名：GOD *good_change();  //2.1.2商品信息修改
*功能：修改人物信息
*返回值：GOD *（结构体指针）
*************************************************/
GOD* good_change(GOD* head)
{   
    GOD *p1;			
    char saveflag;	
	int t;         //存放待修改人的编号
	int flag=0;		//修改标志
    system("cls");		//清屏
	p1=head;		
    printf("请输入要修改的商品编号：\n");	
    scanf("%d",&t);		
    while(p1!=NULL)		//这个while语句的作用是在遍历整个单链表
	{   
	if(p1->code==t)	//判断是不是你输入的编号是不是与商品信息文件中的相同
	   {		
	   flag=1;			//当存在一样的编号时，
		printf("\n你要修改的商品信息为:\n");
		printf("\n编号     名称    余量   销量   价格  折扣  保质期(年月日)   产地\n\n");
		printf("%d         %s       %d      %d      %.2lf      %.2lf   %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n请输入修改后的信息:\n");
		fflush(stdin);
		scanf("%d%s%d%lf%lf%d%d%d%s",&p1->code,p1->name,&p1->count,&p1->price,&p1->discount,&p1->yy,&p1->mm,&p1->dd,p1->madein);
		printf("该商品信息已修改成功\n");
		printf("已经新建成功,是否进行保存? (Y/N)\n");
		fflush(stdin);
		scanf("%c",&saveflag);
		if(saveflag=='y'||saveflag=='Y')	//当输入是的时候
			good_save(head);			//调用保存函数
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
        printf("\n没有找到要修改的通讯名单，请按任意键返回主菜单!\n");
		getch();	//按下任意键就进入下一条语句的函数
    }
	return(head);    
}

/************************************************
*函数名：Search（查找）
*功能：可以通过姓名查询,也可以通过类型查询
*返回值：NULL
*************************************************/
void good_search(GOD* head)
{	int num;	//子菜单选择
	int count=0;
	GOD * p1;
	int i;  //i用来存放编号
	int flag;	//flag是用来判断是否找到，
	char c[20],searchflag='y';	//c是来存放名称
	while(1)
	{	    
		p1=head;
		system("cls");		//清屏
		printf("\n**************查找子菜单*******************\n");
		printf("\n\t 1.按名称\n");
		printf("\n\t 2.按编号\n");
		printf("\n\t 3.返回商品管理菜单\n");
		printf("\n*******************************************\n");
		fflush(stdin);
		num=4;
		scanf("%d",&num);	//选择你想要查询的方式	
		switch(num)		
		{
		case 1:	count=0;
				flag=0;		//初始化为0
				printf("\n请输入待查找的名称: \n");
				scanf("%s",c);	
				p1=head;					
				while(p1!=NULL)		
				{  if(strcmp(p1->name,c)==0)	
				   {  count++;
					  if(count==1)
						  printf("\n编号     名称    余量   销量   价格  折扣  保质期(年月日)   产地\n\n");
					  printf("%d       %s       %d      %d      %.2lf       %.2lf    %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
					   flag=1;		//flag赋值为1，表示已经查到了数据了					   
				   }
				   p1=p1->next;		//p1指针向后移
				}
				if(flag==0)		//表示为没有找到相关数据
					printf("\n未能找到符合条件的记录\n");
				else
					printf("\n\n\########找到了%d个名称为\"%s\"商品!###########\n\n",count,c);
				fflush(stdin);
				getch();
			break;
		case 2:	count=0;
				flag=0;		//初始化为0
				printf("\n请输入待查找的编号: \n");
				scanf("%d",&i);	
				p1=head;					
				while(p1!=NULL)		
				{  if(p1->code ==i)	
				   {  count++;
					  if(count==1)
						  printf("\n编号     名称    余量   销量   价格  折扣  保质期(年月日)   产地\n\n");
					  printf("%d       %s       %d      %d      %.2lf       %.2lf   %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
					   flag=1;		//flag赋值为1，表示已经查到了数据了					   
				   }
				   p1=p1->next;		//p1指针向后移
				}
				if(flag==0)		//表示为没有找到相关数据
					printf("\n未能找到符合条件的记录\n");
				else
					printf("\n\n\######找到了%d个编号为\"%d\"商品!#####\n\n",count,i);
				fflush(stdin);
				getch();
			break;	
		case 3:return;
		default :printf("你输入错了，请你输入任意键返回查找子菜单\n");
			     getch();
		}
	}
}

/************************************************
*函数名： Delete（删除）
*功能：通过查找姓名来实现删除通讯记录
*返回值：ID *（结构体指针）
*************************************************/
GOD *good_delet(GOD *head)  // 2.1.4商品信息删除
{
GOD *p1,*p2;		//p1是用来遍历整一个单链表定位要删除的结点，p2是用来定位p1的前结点的    char  saveflag='n', temp;		//saveflag是否保存，temp是否删除
	int c;	
	char temp,saveflag; 
    p1=p2=head;		//把head赋给p1,p2  	
    printf("\n请输入要删除的编号:\n");
    scanf("%d",&c);
	getchar();
	while(p1!=NULL)		//while语句的作用是在遍历整个单链表
	{
	   if(p1->code==c)	//判断是否存在用户输入的编号 
	   { 	
		   if(p1->next==NULL)
		   {
			   printf("\n这是最后一个商品信息，无法删除。\n");
			   printf("\n按任意键返回\n");
			   getch();
			   return;
		   }
		    printf("你要删除的商品为:\n");
			printf("\n编号    名称    余量   销量    价格  折扣  保质期(年月日)   产地\n\n");
			printf("%d         %s       %d      %d      %.2lf        %.2lf    %d-%d-%d    %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
			printf("请确定是否要删除该记录？Y/N?\n");
			fflush(stdin);
			scanf("%c",&temp);		//确定要删除吗？			
			if(temp=='y'||temp=='Y')	//当输入是的时候
			 {
			   if(p1==head)		//判断是不是在头结点
				   head=p1->next;	//把头结点去掉
			   else
                p2->next=p1->next;	//删除p1结点（p2的next域指向p1的下个结点）
			   printf("该商品信息已删除成功,是否存盘?Y/N?\n");
			   fflush(stdin);
			   scanf("%c",&saveflag);		//确定要保存吗？
			   if(saveflag=='y'||saveflag=='Y')	//当输入是的时候
				  good_save(head);			//调用保存函数
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
	}
	if((p1->next)==NULL&&p1->code!=c)
	{
			printf("没有找到要删除的商品信息，请检查你要删除的商品是否正确\n");
			printf("请按任意键返回主菜单\n");
			getch();			
	}
	return(head);		//return一个已经完成修改的链表头指针   
}


/************************************************
*函数名： good_sort   //2.1.6商品排序查看
*功能：按照类型排序通讯记录
*返回值：GOD *（结构体指针）
*************************************************/
void good_sort(GOD *head)    //2.1.6商品排序查看
{
	GOD  *p1,*p2;
	int c,sum=0;
	while(1)
	{
		p2=NULL;
		system("cls");
		p1=head;
		sum=0;
	printf("\n**************查看子菜单*******************\n");
	printf("\n\t 1.按编号查看\n");
	printf("\n\t 2.按名称查看\n");
	printf("\n\t 3.按销售数量查看\n");
	printf("\n\t 4.返回商品管理菜单\n");
	printf("\n*******************************************\n");
	fflush(stdin);
	scanf("%d",&c);
	switch(c)
	{
case 1:
	while( head != p2)
	{
		p1 = head;
		while( p1->next!= p2 )
		{  
			if( p1->code>p1->next->code)
			{
				in_swap(&p1->code,&p1->next->code);          //交换数据
				in_swap(&p1->count,&p1->next->count);    
				in_swap(&p1->sell,&p1->next->sell);  
				db_swap(&p1->price,&p1->next->price );
				db_swap(&p1->discount ,&p1->next->discount);
				in_swap(&p1->yy,&p1->next->yy);
				in_swap(&p1->mm,&p1->next->mm);
				in_swap(&p1->dd,&p1->next->dd);
				ch_swap(p1->madein,p1->next->madein);
				ch_swap(p1->name,p1->next->name);
            }		
			p1 = p1->next;
        }
	    p2= p1;
    }
    printf("商品信息已按照 编号 排序成功");
    printf("\n编号   名称     余量   销量    价格  折扣  保质期(年月日)   产地\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d   %d   %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n商品信息成功显示\n");
	printf("\n共有%d件商品\n",sum);
	getch(); 
	break;
case 2:
	while( head != p2)
	{
		p1 = head;
		while( p1->next!= p2 )
		{  
			if(strcmp(p1->name,p1->next->name)>0)
			{
				in_swap(&p1->code,&p1->next->code);          //交换数据
				in_swap(&p1->count,&p1->next->count); 
				in_swap(&p1->sell,&p1->next->sell);  
				db_swap(&p1->price,&p1->next->price );
				db_swap(&p1->discount ,&p1->next->discount);
				in_swap(&p1->yy,&p1->next->yy);
				in_swap(&p1->mm,&p1->next->mm);
				in_swap(&p1->dd,&p1->next->dd);
				ch_swap(p1->madein,p1->next->madein);
				ch_swap(p1->name,p1->next->name);
            }		
			p1 = p1->next;
        }
	   p2= p1;
    }
	printf("商品信息已按照 名称 排序成功\n");
    printf("\n编号   名称    余量   销量   价格  折扣  保质期(年月日)   产地\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d  %d  %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n商品信息成功显示\n");
	printf("\n共有%d件商品\n",sum);
	getch();
	 break;
case 3:
	while( head != p2)
	{
		p1 = head;
		while( p1->next!= p2 )
		{  
			if(p1->sell>p1->next->sell)
			{
				in_swap(&p1->code,&p1->next->code);          //交换数据
				in_swap(&p1->count,&p1->next->count); 
				in_swap(&p1->sell,&p1->next->sell);  
				db_swap(&p1->price,&p1->next->price );
				db_swap(&p1->discount ,&p1->next->discount);
				in_swap(&p1->yy,&p1->next->yy);
				in_swap(&p1->mm,&p1->next->mm);
				in_swap(&p1->dd,&p1->next->dd);
				ch_swap(p1->madein,p1->next->madein);
				ch_swap(p1->name,p1->next->name);
            }		
			p1 = p1->next;
        }
	   p2= p1;
    }
	printf("商品信息已按照 销量 排序成功\n");
    printf("\n编号   名称    余量   销量   价格  折扣  保质期(年月日)   产地\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d  %d  %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n商品信息成功显示\n");
	printf("\n共有%d件商品\n",sum);
	printf("下次购进商品可多购卖出数量最多的商品！\n");
	getch(); 
	 break;
case 4:return;
default:printf("\n输入错误，请重新输入\n");
     getch();
}
}
}
