/************************************************
*��������shopstuff_enter��ӪҵԱ���棩
*���ܣ��������ﳵ ��ʼ��ȡ��Ա�Լ���Ʒ��Ϣ
*����ֵ��NULL
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
	printf("\n\n================��ӭ����================\n\n");
	printf("1.��Ա������\n\n");
	printf("2.�޻�Ա������\n\n");
	printf("3.�鿴���ۼ�¼\n\n");
	printf("4.�˳���¼\n\n");
	printf("===============================================\n\n");
	printf("���������ѡ��");
	scanf("%d",&num);
	switch (num)
	{
	case 1:
		head1=vip_read();
		head2=good_read();
		if(head1 == NULL || head2 == NULL)
		{
			printf("��ȡ��Ա��Ʒ��Ϣʧ��");
			getch();
		}
		else
			head=cart_add(head1,head2);
		break;
	case 2:
		head2=good_read();
		if(head2 == NULL)
		{
			printf("��ȡ��Ա��Ʒ��Ϣʧ��");
			getch();
		}
		else
			head=cart_printf(head2);
		break;
	case 3:
		head=cart_read();
		if(head==NULL)
		{
			printf("�ı���ȡʧ��");
			getch();
		}
		else
			cart_view(head);
		break;
	case 4:
		return;
	default:printf("ѡ���������������");break;
	}
	}
}




/************************************************
*��������cart_read����ȡ��Ʒ��Ϣ�ļ���
*���ܣ���ȡ�ļ��е���Ϣ��������뵥�����У�������󷵻�һ��ͷָ��
*����ֵ��GOD *���ṹ��ָ�룩
*************************************************/
CART *cart_read()        //��ȡ��Ʒ��Ϣ�ļ�
{
	FILE *fp;	//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
    CART *t1,*t2,*head=NULL;
    if((fp=fopen("cart.txt","r"))==NULL)      //�ж��ļ��Ƿ����
    {   printf("���ļ�ʧ�ܣ�û�и��ļ�\n\n");
 		printf("�밴������������˵�\n");
        getch();
		return 0;
     }
	rewind(fp);	  //��������ǰ�һ���ļ���λ��ָ�����������ͷ����Ȼ�Ļ������һ�������ݶ�ʧ
    t1=(CART *) malloc(sizeof(CART));	//���붯̬�ռ�
    head=t2=t1;	//��t1����ͷ���
	 while(!feof(fp))	//feof�����Ĺ������ж��ļ��ǲ��ǽ�������������ˣ����ط���ֵ�����򷵻�0��
    {   if(fread(t1,sizeof(CART),1,fp)!=1)	//fread�������ض���������ĸ���
            break;  //���û�ж�ȡ���ݣ������
	    t1->next=(CART *)malloc(sizeof(CART));	//�����붯̬�ռ��ͬʱ����t1��nextָ����һ�����
        t2=t1;     //t2��������β�ڵ�
		t1=t1->next;	//t1�����һ�����
    }
    t2->next=NULL;
	fclose(fp);		//�ر��ļ�
return head;	//����ͷָ��
}


/***********************************************
*��������cart_add����Ա�����ӣ�
*���ܣ�����Ƿ����ļ������򴴽�һ�������������ݷ����������棬����������ݣ�һ����Ҫ���棬�͵���save�����������ļ���
*����ֵ��CART *���ṹ������ͷ�ڵ�ָ�룩
***********************************************/
CART* cart_add(VIP *head1,GOD *head2)
{
	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
	CART *head,*p1,*tail,*pt;  //p1�洢һ��������Ϣ pt�洢һ�ι�����Ϣ
	VIP  *pv1;
	GOD *pg1;
    int saveflag,mm,nn;		//�����־

    if ((fp=fopen("cart.txt","r"))==NULL)		//����ļ������ھʹ���
    {

		p1= (CART*)malloc(sizeof(CART));	//��p1����һ����̬�洢�ռ�
		head=tail=pt=p1;
		p1->next=NULL;

		system("cls");
   cc1: printf("\n�������Ա���:\n");
		fflush(stdin);
		scanf("%d",&p1->num);    //�����Ա���
		mm=0;  //��ʼ��
		pv1=head1;
		while(pv1!=NULL)  //��ʼ������Ա�ĵ�
		{
			if(p1->num==pv1->code)  //�ҵ��û�Ա
			{
				strcpy(p1->vip,pv1->name);  //���ƻ�Ա����
				strcpy(p1->clas,pv1->clas);  //���ƻ�Ա�ȼ�
				printf("\n��Ա��ţ�%d\t",pv1->code);
				printf("��Ա�ȼ���%s\t",pv1->clas);
				printf("��Ա������%s\n",pv1->name);
				mm=1;
				break;
			}
			pv1=pv1->next;
		}
		if(mm!=1)  //û�ҵ��û�Ա
		{
			printf("�û�Աδע�ᣬ����������!");
			getch();
			goto cc1;  //���������Ա���
		}  //������Ա����

		//��ѭ����Ʒ����
   cc2: printf("\n�����빺����Ʒ�ı�ţ�");
		scanf("%d",&p1->code);
		nn=0;  //��ʼ��
		pg1=head2;
		while(pg1!=NULL)  //��ʼ������Ʒ
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //������Ʒ����
				p1->price=pg1->price;  //������Ʒ����
				p1->discount=pg1->discount;  //������Ʒ�ۿ�
				printf("\n��ţ�%d\t",p1->code);
				printf("���ƣ�%s\t",p1->good);
				printf("���ۣ�%.2f\t",p1->price);
				printf("�ۿۣ�%.2f\t",p1->discount);

				printf("������");
				scanf("%d",&p1->count);  //������Ʒ����
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n��治�㣡���������룡");
					getch();
					goto cc2;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //������Ʒ����
		if(nn!=1)
		{
			printf("\n����Ʒ�����ڣ�����������");
			getch();
			goto cc2;
		}
		//һ���ڵ㴴�����
		//ѯ���Ƿ���������Ʒ
		saveflag=0;
		printf("\nȷ�ϲ���������1������������0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			tail=p1;
			tail->next=NULL; //��β
			pv1->jifen+=cart_calculate(pt);  //���㱾�������ܶ��û���
			pv1->times++;
			cart_save(head);
			vip_save(head1);
			good_save(head2);
			pt=p1; //��¼���һ�����Ѽ�¼��λ��
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
			p1->num=pv1->code;  //���ƻ�Ա���
			strcpy(p1->vip,pv1->name);  //���ƻ�Ա����
			strcpy(p1->clas,pv1->clas);  //���ƻ�Ա�ȼ�
			goto cc2;
		}
	}

	//�ı��Ѵ���
	else
	{
		head=cart_read();
		tail=head;
		while(tail->next!=NULL)
		{
			tail=tail->next;
		}
		p1=pt=tail;  //����һ�����һ��λ�õ���һ����ʼ��¼,����¼ָ��ָ��ôι���ĵ�һ��
		p1=(CART*)malloc(sizeof(CART));
		system("cls");
   cc3: printf("\n�������Ա���:\n");
		fflush(stdin);
		scanf("%d",&p1->num);    //�����Ա���
		mm=0;  //��ʼ��
		pv1=head1;
		while(pv1!=NULL)  //��ʼ������Ա�ĵ�
		{
			if(p1->num==pv1->code)  //�ҵ��û�Ա
			{
				strcpy(p1->vip,pv1->name);  //���ƻ�Ա����
				strcpy(p1->clas,pv1->clas);  //���ƻ�Ա�ȼ�
				printf("\n��Ա��ţ�%d\t",pv1->code);
				printf("��Ա�ȼ���%s\t",pv1->clas);
				printf("��Ա������%s\n",pv1->name);
				mm=1;
				break;
			}
			pv1=pv1->next;
		}
		if(mm!=1)  //û�ҵ��û�Ա
		{
			printf("�û�Աδע�ᣬ����������!");
			getch();
			goto cc3;  //���������Ա���
		}  //������Ա����

		//��ѭ����Ʒ����
   cc4: printf("\n�����빺����Ʒ�ı�ţ�");
		scanf("%d",&p1->code);
		nn=0;  //��ʼ��
		pg1=head2;
		while(pg1!=NULL)  //��ʼ������Ʒ
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //������Ʒ����
				p1->price=pg1->price;  //������Ʒ����
				p1->discount=pg1->discount;  //������Ʒ�ۿ�
				printf("\n��ţ�%d\t",p1->code);
				printf("���ƣ�%s\t",p1->good);
				printf("���ۣ�%.2f\t",p1->price);
				printf("�ۿۣ�%.2f\t",p1->discount);

				printf("������");
				scanf("%d",&p1->count);  //������Ʒ����
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n��治�㣡���������룡");
					getch();
					goto cc4;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //������Ʒ����
		if(nn!=1)
		{
			printf("\n����Ʒ�����ڣ�����������");
			getch();
			goto cc4;
		}
		//һ���ڵ㴴�����
		//ѯ���Ƿ���������Ʒ
		printf("\nȷ�ϲ���������밴1������������0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			p1->next=NULL; //��β
			pv1->jifen+=cart_calculate(pt);  //���㱾�������ܶ��û���
			pv1->times++;
			cart_save(head);
			vip_save(head1);
			good_save(head2);
			pt=p1; //��¼���һ�����Ѽ�¼��λ��
			free(p1);
			free(pv1);
			free(pg1);
		}
		else
		{
			tail->next=p1;
			tail=p1;
			p1= (CART*)malloc(sizeof(CART));
			p1->num=pv1->code;  //���ƻ�Ա���
			strcpy(p1->vip,pv1->name);  //���ƻ�Ա����
			strcpy(p1->clas,pv1->clas);  //���ƻ�Ա�ȼ�
			goto cc4;
		}
	}
	return head;
}







/***********************************************
*��������cart_save�����棩
*���ܣ�����Ƿ����ļ������򴴽�һ�������������ݷ����������棬����������ݣ�һ����Ҫ���棬�͵���save�����������ļ���
*����ֵ��void
***********************************************/
void cart_save(CART *head)
{
	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
    CART *t;			//����һ��ָ�룬��ͷ��β����һ�鵥�������ļ���д��
    if ((fp=fopen("cart.txt","w"))==NULL)		//���ļ���д��
    {
        printf("���ļ�ʧ�ܣ�\n");
        getch();     //���������������һ��
        exit(0);		//�˳�
    }
    t=head;			//��ͷָ�븳��t��������ͷ��ʼ
    while(t!=NULL)	//ֻҪtָ�벻Ϊ�գ�����������û�н���
    {
       fwrite(t,sizeof(CART),1,fp);	//������д���ļ���
       t=t->next;	//ָ�����
    }
    fclose(fp);		//���ļ��ر�
    printf("\n�ļ�����ɹ�\n");
	printf("\n�밴������������˵�\n");
	getch();
}



/***********************************************
*��������cart_caluculate�����㣩
*���ܣ�����Ƿ����ļ������򴴽�һ�������������ݷ����������棬����������ݣ�һ����Ҫ���棬�͵���save�����������ļ���
*����ֵ:total���ṹ������ͷ�ڵ�ָ�룩
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
	printf("\n\n�ܼƣ�%.2f\n",sum);
	return sum;
}




/***********************************************
*��������cart_printf���޻�Ա�����ӣ�
*���ܣ�����Ƿ����ļ������򴴽�һ�������������ݷ����������棬����������ݣ�һ����Ҫ���棬�͵���save�����������ļ���
*����ֵ��CART *���ṹ������ͷ�ڵ�ָ�룩
***********************************************/
CART* cart_printf(GOD *head2)
{
	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
	CART *head,*p1,*tail,*pt;  //p1�洢һ��������Ϣ pt�洢һ�ι�����Ϣ
	GOD *pg1;
    int saveflag,nn;		//�����־

    if ((fp=fopen("cart.txt","r"))==NULL)		//����ļ������ھʹ���
    {

		p1= (CART*)malloc(sizeof(CART));	//��p1����һ����̬�洢�ռ�
		head=tail=pt=p1;
		p1->next=NULL;

		system("cls");

		p1->num=0;
		strcpy(p1->vip,"null");  //���ƻ�Ա����
		strcpy(p1->clas,"null");  //���ƻ�Ա�ȼ�

		//��ѭ����Ʒ����
   dd1: printf("\n�����빺����Ʒ�ı�ţ�");
		scanf("%d",&p1->code);
		nn=0;  //��ʼ��
		pg1=head2;
		while(pg1!=NULL)  //��ʼ������Ʒ
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //������Ʒ����
				p1->price=pg1->price;  //������Ʒ����
				p1->discount=pg1->discount;  //������Ʒ�ۿ�
				printf("\n��ţ�%d\t",p1->code);
				printf("���ƣ�%s\t",p1->good);
				printf("���ۣ�%.2f\t",p1->price);
				printf("�ۿۣ�%.2f\t",p1->discount);

				printf("������");
				scanf("%d",&p1->count);  //������Ʒ����
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n��治�㣡���������룡");
					getch();
					goto dd1;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //������Ʒ����
		if(nn!=1)
		{
			printf("\n����Ʒ�����ڣ�����������");
			getch();
			goto dd1;
		}
		//һ���ڵ㴴�����
		//ѯ���Ƿ���������Ʒ
		saveflag=0;
		printf("\nȷ�ϲ���������1������������0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			tail->next=p1;
			tail=p1;
			tail->next=NULL; //��β
			cart_calculate(pt);  //���㱾�������ܶ��û���
			cart_save(head);
			good_save(head2);
			pt=p1; //��¼���һ�����Ѽ�¼��λ��
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
			p1->num=0;  //���ƻ�Ա���
			strcpy(p1->vip,"null");  //���ƻ�Ա����
			strcpy(p1->clas,"null");  //���ƻ�Ա�ȼ�
			goto dd1;
		}
	}

	//�ı��Ѵ���
	else
	{
		head=cart_read();
		while(head->next!=NULL)
		{
			head=head->next;
		}
		p1=pt=head;  //����һ�����һ��λ�õ���һ����ʼ��¼,����¼ָ��ָ��ôι���ĵ�һ��
		/*pt=p1;  */
		system("cls");
		p1->num=0;
		strcpy(p1->vip,"null");  //���ƻ�Ա����
		strcpy(p1->clas,"null");  //���ƻ�Ա�ȼ�

		//��ѭ����Ʒ����
   dd2: printf("\n�����빺����Ʒ�ı�ţ�");
		scanf("%d",&p1->code);
		nn=0;  //��ʼ��
		pg1=head2;
		while(pg1!=NULL)  //��ʼ������Ʒ
		{
			if(p1->code==pg1->code)
			{
				strcpy(p1->good,pg1->name);  //������Ʒ����
				p1->price=pg1->price;  //������Ʒ����
				p1->discount=pg1->discount;  //������Ʒ�ۿ�
				printf("\n��ţ�%d\t",p1->code);
				printf("���ƣ�%s\t",p1->good);
				printf("���ۣ�%.2f\t",p1->price);
				printf("�ۿۣ�%.2f\t",p1->discount);

				printf("������");
				scanf("%d",&p1->count);  //������Ʒ����
				if (pg1->count > p1->count)
				{
					pg1->count-=p1->count;
					pg1->sell+=p1->count;
				}
				else
				{
					printf("\n��治�㣡���������룡");
					getch();
					goto dd2;
				}
				nn=1;
			}
			pg1=pg1->next;
		}  //������Ʒ����
		if(nn!=1)
		{
			printf("\n����Ʒ�����ڣ�����������");
			getch();
			goto dd2;
		}
		//һ���ڵ㴴�����
		//ѯ���Ƿ���������Ʒ
		printf("\nȷ�ϲ���������밴1������������0");
		scanf("%d",&saveflag);
		if(saveflag==0)
		{
			head->next=p1;
			p1->next=NULL; //��β
			cart_calculate(pt);  //���㱾�������ܶ��û���
			cart_save(head);
			good_save(head2);
			pt=p1; //��¼���һ�����Ѽ�¼��λ��
			free(p1);
			free(pg1);
		}
		else
		{
			head->next=p1;
			head=p1;
			p1= (CART*)malloc(sizeof(CART));
			p1->num=0;  //���ƻ�Ա���
			strcpy(p1->vip,"null");  //���ƻ�Ա����
			strcpy(p1->clas,"null");  //���ƻ�Ա�ȼ�
			goto dd2;
		}
	}
	return head;
}

/***********************************************
*��������cart_view�����棩
*���ܣ�����Ƿ����ļ������򴴽�һ�������������ݷ����������棬����������ݣ�һ����Ҫ���棬�͵���save�����������ļ���
*����ֵ��void
***********************************************/

void cart_view(CART *head)
{
	CART *p1;
	p1=head;
	system("cls");
	printf("\n\n===��Ա���===�ȼ�===����===��Ʒ���======����=====����=====�ۿ�=====����==\n");
	while(p1!=NULL)
	{
		printf("     %d     %s  %s     %d       %s   %.2f   %.2f   %.d\n",p1->num,p1->clas,p1->vip,p1->code,p1->good,p1->price,p1->discount,p1->count);
		p1=p1->next;
	}
	printf("\n\n�����������");
	getch();
}
