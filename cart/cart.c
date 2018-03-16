/************************************************
*函数名：shopstuff_enter（营业员界面）
*功能：创建购物车 开始读取会员以及商品信息
*返回值：NULL
*************************************************/
void shopstuff_enter()
{
	int num;
	CART *head;
	VIP *head1;
	GOD *head2;
	while(1)
	{
	system("cls");
	printf("\n\n================欢迎光临================\n\n");
	printf("1.会员卡购物\n\n");
	printf("2.无会员卡购物\n\n");
	printf("3.查看出售记录\n\n");
	printf("4.退出登录\n\n");
	printf("===============================================\n\n");
	printf("请输入你的选择：");
	scanf("%d",&num);
	switch (num)
	{
	case 1:
		head1=vip_read();
		head2=good_read();
		if(head1 == NULL || head2 == NULL)
		{
			printf("读取会员商品信息失败");
			getch();
		}
		else
			head=cart_add(head1,head2);
		break;
	case 2:
		head2=good_read();
		if(head2 == NULL)
		{
			printf("读取会员商品信息失败");
			getch();
		}
		else
			head=cart_printf(head2);
		break;
	case 3:
		head=cart_read();
		if(head==NULL)
		{
			printf("文本读取失败");
			getch();
		}
		else
			cart_view(head);
		break;
	case 4:
		return;
	default:printf("选择错误，请重新输入");break;
	}
	}
}




/************************************************
*函数名：cart_read（读取商品信息文件）
*功能：读取文件中的信息并将其放入单链表中，并且最后返回一个头指针
*返回值：GOD *（结构体指针）
*************************************************/
CART *cart_read()        //读取商品信息文件
{
	FILE *fp;	//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    CART *t1,*t2,*head=NULL;
    if((fp=fopen("cart.txt","r"))==NULL)      //判断文件是否存在
    {   printf("打开文件失败！没有该文件\n\n");
 		printf("请按任意键返回主菜单\n");
        getch();
		return 0;
     }
	rewind(fp);	  //这个函数是把一个文件的位置指针从新移至开头，不然的话会出现一个组数据丢失
    t1=(CART *) malloc(sizeof(CART));	//申请动态空间
    head=t2=t1;	//把t1赋给头结点
	 while(!feof(fp))	//feof函数的功能是判断文件是不是结束，如果结束了，返回非零值，否则返回0，
    {   if(fread(t1,sizeof(CART),1,fp)!=1)	//fread函数返回读出数据项的个数
            break;  //如果没有读取内容，则结束
	    t1->next=(CART *)malloc(sizeof(CART));	//在申请动态空间的同时，把t1的next指向下一个结点
        t2=t1;     //t2是真正的尾节点
		t1=t1->next;	//t1向后移一个结点
    }
    t2->next=NULL;
	fclose(fp);		//关闭文件
return head;	//返回头指针
}


/***********************************************
*函数名：cart_add（会员卡增加）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值：CART *（结构体链表头节点指针）
***********************************************/
CART* cart_add(VIP *head1,GOD *head2)
{
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
	CART *head,*p1,*tail,*pt;  //p1存储一条购物信息 pt存储一次购物信息
	VIP  *pv1;
	GOD *pg1;
    int saveflag,mm,nn;		//保存标志

    if ((fp=fopen("cart.txt","r"))==NULL)		//如果文件不存在就创建
    {

		p1= (CART*)malloc(sizeof(CART));	//给p1分配一个动态存储空间
		head=tail=pt=p1;
		p1->next=NULL;

		system("cls");
   cc1: printf("\n请输入会员编号:\n");
		fflush(stdin);
		scanf("%d",&p1->num);    //输入会员编号
		mm=0;  //初始化
		pv1=head1;
		while(pv1!=NULL)  //开始检索会员文档
		{
			if(p1->num==pv1->code)  //找到该会员
			{
				strcpy(p1->vip,pv1->name);  //复制会员姓名
				strcpy(p1->clas,pv1->clas);  //复制会员等级
				printf("\n会员编号：%d\t",pv1->code);
				printf("会员等级：%s\t",pv1->clas);
				printf("会员姓名：%s\n",pv1->name);
				mm=1;
				break;
			}
			pv1=pv1->next;
		}
		if(mm!=1)  //没找到该会员
		{
			printf("该会员未注册，请重新输入!");
			getch();
			goto cc1;  //返回输入会员编号
		}  //搜索会员结束

		//可循环商品输入
   cc2: printf("\n请输入购买商品的编号：");
		scanf("%d",&p1->code);
		nn=0;  //初始化
		pg1=head2;
		while(pg1!=NULL)  //开始搜索商品
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //复制商品名称
				p1->price=pg1->price;  //复制商品单价
				p1->discount=pg1->discount;  //复制商品折扣
				printf("\n编号：%d\t",p1->code);
				printf("名称：%s\t",p1->good);
				printf("单价：%.2f\t",p1->price);
				printf("折扣：%.2f\t",p1->discount);

				printf("数量：");
				scanf("%d",&p1->count);  //输入商品数量
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n库存不足！请重新输入！");
					getch();
					goto cc2;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //搜索商品结束
		if(nn!=1)
		{
			printf("\n该商品不存在，请重新输入");
			getch();
			goto cc2;
		}
		//一个节点创建完成
		//询问是否继续添加商品
		saveflag=0;
		printf("\n确认并继续输入1，结束请输入0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			tail=p1;
			tail->next=NULL; //收尾
			pv1->jifen+=cart_calculate(pt);  //结算本次消费总额，获得积分
			pv1->times++;
			cart_save(head);
			vip_save(head1);
			good_save(head2);
			pt=p1; //记录最后一条消费记录的位置
			free(p1);
			free(pv1);
			free(pg1);
		}
		else
		{
			tail->next=p1;
			tail=p1;

			p1= (CART*)malloc(sizeof(CART));
			if(p1==NULL)
			{
				printf("\nError!\n");
				return;
			}
			p1->num=pv1->code;  //复制会员编号
			strcpy(p1->vip,pv1->name);  //复制会员姓名
			strcpy(p1->clas,pv1->clas);  //复制会员等级
			goto cc2;
		}
	}

	//文本已存在
	else
	{
		head=cart_read();
		tail=head;
		while(tail->next!=NULL)
		{
			tail=tail->next;
		}
		p1=pt=tail;  //从上一次最后一个位置的下一个开始记录,将记录指针指向该次购物的第一条
		p1=(CART*)malloc(sizeof(CART));
		system("cls");
   cc3: printf("\n请输入会员编号:\n");
		fflush(stdin);
		scanf("%d",&p1->num);    //输入会员编号
		mm=0;  //初始化
		pv1=head1;
		while(pv1!=NULL)  //开始检索会员文档
		{
			if(p1->num==pv1->code)  //找到该会员
			{
				strcpy(p1->vip,pv1->name);  //复制会员姓名
				strcpy(p1->clas,pv1->clas);  //复制会员等级
				printf("\n会员编号：%d\t",pv1->code);
				printf("会员等级：%s\t",pv1->clas);
				printf("会员姓名：%s\n",pv1->name);
				mm=1;
				break;
			}
			pv1=pv1->next;
		}
		if(mm!=1)  //没找到该会员
		{
			printf("该会员未注册，请重新输入!");
			getch();
			goto cc3;  //返回输入会员编号
		}  //搜索会员结束

		//可循环商品输入
   cc4: printf("\n请输入购买商品的编号：");
		scanf("%d",&p1->code);
		nn=0;  //初始化
		pg1=head2;
		while(pg1!=NULL)  //开始搜索商品
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //复制商品名称
				p1->price=pg1->price;  //复制商品单价
				p1->discount=pg1->discount;  //复制商品折扣
				printf("\n编号：%d\t",p1->code);
				printf("名称：%s\t",p1->good);
				printf("单价：%.2f\t",p1->price);
				printf("折扣：%.2f\t",p1->discount);

				printf("数量：");
				scanf("%d",&p1->count);  //输入商品数量
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n库存不足！请重新输入！");
					getch();
					goto cc4;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //搜索商品结束
		if(nn!=1)
		{
			printf("\n该商品不存在，请重新输入");
			getch();
			goto cc4;
		}
		//一个节点创建完成
		//询问是否继续添加商品
		printf("\n确认并继续添加请按1，结束请输入0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			p1->next=NULL; //收尾
			pv1->jifen+=cart_calculate(pt);  //结算本次消费总额，获得积分
			pv1->times++;
			cart_save(head);
			vip_save(head1);
			good_save(head2);
			pt=p1; //记录最后一条消费记录的位置
			free(p1);
			free(pv1);
			free(pg1);
		}
		else
		{
			tail->next=p1;
			tail=p1;
			p1= (CART*)malloc(sizeof(CART));
			p1->num=pv1->code;  //复制会员编号
			strcpy(p1->vip,pv1->name);  //复制会员姓名
			strcpy(p1->clas,pv1->clas);  //复制会员等级
			goto cc4;
		}
	}
	return head;
}







/***********************************************
*函数名：cart_save（保存）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值：void
***********************************************/
void cart_save(CART *head)
{
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    CART *t;			//定义一个指针，从头到尾遍历一遍单链表，向文件中写入
    if ((fp=fopen("cart.txt","w"))==NULL)		//打开文件来写入
    {
        printf("打开文件失败！\n");
        getch();     //输入任意键进入下一步
        exit(0);		//退出
    }
    t=head;			//把头指针赋给t，让它从头开始
    while(t!=NULL)	//只要t指针不为空，即等于链表没有结束
    {
       fwrite(t,sizeof(CART),1,fp);	//把链表写入文件中
       t=t->next;	//指针后移
    }
    fclose(fp);		//把文件关闭
    printf("\n文件保存成功\n");
	printf("\n请按任意键返回主菜单\n");
	getch();
}



/***********************************************
*函数名：cart_caluculate（计算）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值:total（结构体链表头节点指针）
***********************************************/
double cart_calculate(CART *p1)
{
	double a,sum=0;
	while(p1!=NULL)
	{
		a=p1->price*p1->discount*p1->count;
		sum+=a;
		p1=p1->next;
	}
	printf("\n\n总计：%.2f\n",sum);
	return sum;
}




/***********************************************
*函数名：cart_printf（无会员卡增加）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值：CART *（结构体链表头节点指针）
***********************************************/
CART* cart_printf(GOD *head2)
{
	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
	CART *head,*p1,*tail,*pt;  //p1存储一条购物信息 pt存储一次购物信息
	GOD *pg1;
    int saveflag,nn;		//保存标志

    if ((fp=fopen("cart.txt","r"))==NULL)		//如果文件不存在就创建
    {

		p1= (CART*)malloc(sizeof(CART));	//给p1分配一个动态存储空间
		head=tail=pt=p1;
		p1->next=NULL;

		system("cls");

		p1->num=0;
		strcpy(p1->vip,"null");  //复制会员姓名
		strcpy(p1->clas,"null");  //复制会员等级

		//可循环商品输入
   dd1: printf("\n请输入购买商品的编号：");
		scanf("%d",&p1->code);
		nn=0;  //初始化
		pg1=head2;
		while(pg1!=NULL)  //开始搜索商品
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //复制商品名称
				p1->price=pg1->price;  //复制商品单价
				p1->discount=pg1->discount;  //复制商品折扣
				printf("\n编号：%d\t",p1->code);
				printf("名称：%s\t",p1->good);
				printf("单价：%.2f\t",p1->price);
				printf("折扣：%.2f\t",p1->discount);

				printf("数量：");
				scanf("%d",&p1->count);  //输入商品数量
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n库存不足！请重新输入！");
					getch();
					goto dd1;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //搜索商品结束
		if(nn!=1)
		{
			printf("\n该商品不存在，请重新输入");
			getch();
			goto dd1;
		}
		//一个节点创建完成
		//询问是否继续添加商品
		saveflag=0;
		printf("\n确认并继续输入1，结束请输入0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			tail=p1;
			tail->next=NULL; //收尾
			cart_calculate(pt);  //结算本次消费总额，获得积分
			cart_save(head);
			good_save(head2);
			pt=p1; //记录最后一条消费记录的位置
			free(p1);
			free(pg1);
		}
		else
		{
			tail->next=p1;
			tail=p1;

			p1= (CART*)malloc(sizeof(CART));
			if(p1==NULL)
			{
				printf("\nError!\n");
				return;
			}
			p1->num=0;  //复制会员编号
			strcpy(p1->vip,"null");  //复制会员姓名
			strcpy(p1->clas,"null");  //复制会员等级
			goto dd1;
		}
	}

	//文本已存在
	else
	{
		head=cart_read();
		while(head->next!=NULL)
		{
			head=head->next;
		}
		p1=pt=head;  //从上一次最后一个位置的下一个开始记录,将记录指针指向该次购物的第一条
		/*pt=p1;  */
		system("cls");
		p1->num=0;
		strcpy(p1->vip,"null");  //复制会员姓名
		strcpy(p1->clas,"null");  //复制会员等级

		//可循环商品输入
   dd2: printf("\n请输入购买商品的编号：");
		scanf("%d",&p1->code);
		nn=0;  //初始化
		pg1=head2;
		while(pg1!=NULL)  //开始搜索商品
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //复制商品名称
				p1->price=pg1->price;  //复制商品单价
				p1->discount=pg1->discount;  //复制商品折扣
				printf("\n编号：%d\t",p1->code);
				printf("名称：%s\t",p1->good);
				printf("单价：%.2f\t",p1->price);
				printf("折扣：%.2f\t",p1->discount);

				printf("数量：");
				scanf("%d",&p1->count);  //输入商品数量
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n库存不足！请重新输入！");
					getch();
					goto dd2;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //搜索商品结束
		if(nn!=1)
		{
			printf("\n该商品不存在，请重新输入");
			getch();
			goto dd2;
		}
		//一个节点创建完成
		//询问是否继续添加商品
		printf("\n确认并继续添加请按1，结束请输入0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			head->next=p1;
			p1->next=NULL; //收尾
			cart_calculate(pt);  //结算本次消费总额，获得积分
			cart_save(head);
			good_save(head2);
			pt=p1; //记录最后一条消费记录的位置
			free(p1);
			free(pg1);
		}
		else
		{
			head->next=p1;
			head=p1;
			p1= (CART*)malloc(sizeof(CART));
			p1->num=0;  //复制会员编号
			strcpy(p1->vip,"null");  //复制会员姓名
			strcpy(p1->clas,"null");  //复制会员等级
			goto dd2;
		}
	}
	return head;
}

/***********************************************
*函数名：cart_view（保存）
*功能：检测是否有文件，否则创建一个单链表，把数据放在链表里面，是则添加数据，一旦需要保存，就调用save函数保存在文件中
*返回值：void
***********************************************/

void cart_view(CART *head)
{
	CART *p1;
	p1=head;
	system("cls");
	printf("\n\n===会员编号===等级===姓名===商品编号======名称=====单价=====折扣=====数量==\n");
	while(p1!=NULL)
	{
		printf("     %d     %s  %s     %d       %s   %.2f   %.2f   %.d\n",p1->num,p1->clas,p1->vip,p1->code,p1->good,p1->price,p1->discount,p1->count);
		p1=p1->next;
	}
	printf("\n\n按任意键返回");
	getch();
}
