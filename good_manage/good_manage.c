void good_manage()
{
    GOD *head=NULL;
	int choice;
while(1)
{   system("cls");
    printf("\n\n");
    printf("========��Ʒ����=====\n");
    printf("1.��Ʒ��Ϣ¼��\n");
    printf("2.��Ʒ��Ϣ�޸�\n");
    printf("3.��Ʒȫ����Ϣ��ʾ\n");
    printf("4.��Ʒ��Ϣ����\n");
    printf("5.��Ʒ��Ϣɾ��\n");
	printf("6.��Ʒ��Ϣ����鿴\n");
    printf("7.������һ��\n");
    printf("=========================\n\n");
printf("���������ѡ��1-7����");
scanf("%d",&choice);
getchar();
switch(choice)
{
case 1 :head=good_add(head);break;
case 2 :head=good_read();
       if(head==NULL)
		   printf("\n����ѡ��1.¼����Ʒ��Ϣ\n");
	   else
		   head=good_change(head);
       break;
case 3 :head=good_read(head);
        if(head==NULL)
		   printf("\n����ѡ��1.¼����Ʒ��Ϣ\n");
	    else
		   good_printf(head);
        break;
case 4 :head=good_read(head);
       if(head==NULL)
		   printf("\n����ѡ��1  ��������\n");
	   else
		   good_search(head);
       break;
case 5 :head=good_read(head);
        if(head==NULL)
		    printf("\n����ѡ��1  ��������\n");
	    else
            head=good_delet(head);
        break;
case 6 :head=good_read(head);
	    if(head==NULL)
		    printf("\n����ѡ��1  ��������\n");
	    else
            good_sort(head);
        break;
case 7 :return;
default:printf("\n�����������������\n");
              getch();
  }
}
}





GOD *good_add(GOD *head)  // 2.1.1��Ʒ��Ϣ¼��
{	int k=0,i=0,total=0;
	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
    GOD *p1,*tail,*p3,*p2,*pa;	//pa����������ӵ���Ϣ��
    char saveflag;			//����ַ����������Ƿ񱣴�
   	
    if ((fp=fopen("good.txt","r"))==NULL)		//����ļ������ھʹ���
    {
        head=p1=tail=NULL;
		while(1)				//���ѭ������ʵ�ֶ�������Ʒ��Ϣ
		{
		   p1= (GOD*)malloc(sizeof(GOD));	//��p1����һ����̬�洢�ռ�
		   p1->next=NULL;
      bb1: printf("\n��������(���㲻��¼��ʱ���ڱ�Ŵ�����0������¼��):\n");
		   fflush(stdin);
		   scanf("%d",&p1->code);			//������
          if(p1->code==0)	//�ж�������Ƿ�Ϊ0�ţ���������
		  {
            if(total==0)				//����¼����Ϊ0ʱ��������Ʒ��Ϣ�ļ�
            {
             printf("��������0����¼��������û�д���...\n");
             free(p1);					//�ͷ�p1�ռ�
             return (head);			//��head����
            }
            else
            {
                break;					//����whileѭ��
            }
		  }
		  fflush(stdin);
          printf("������������Ϣ(�����ƣ��������������۸��ۿۣ�������(������)����������):\n");
          scanf("%s%d%d%lf%lf%d%d%d%s",p1->name,&p1->count,&p1->sell,&p1->price,&p1->discount,&p1->yy,&p1->mm,&p1->dd,p1->madein);
		  p1->name[19]=0;
		  p1->madein[9]=0;

		  p3=head;		//��p3��ͷ��ʼ����
		  while(p3!=NULL)		//��p3��Ϊ��ʱ
		  {		if(p1->code==p3->code)
				{	free(p1);
					printf("���ظ������ˡ�\n");
					goto bb1;
				}
				p3=p3->next;
		  }
	      if(head==NULL)			//���ǵ�һ�ν�����ʱ��headΪ��
		  {
            head=p1;				//head��p2��Ϊp1
            tail=p1;
		  }
          else
          {	
            tail->next=p1;		//���ǵڶ����Ժ��ִ�����Ŀ�ľ���p2����ƣ���head��λ�ò���
            tail=p1;
          }
         total++;				//����¼��һ���˺������ͼ�1
		}
		tail->next=NULL;				//βָ����ֵΪNULL			
		free(p1);
		printf("\n�½���Ʒ��Ϣ�ļ��ɹ�������%d����Ʒ\n ",total);
		good_save(head);	//���´�������Ʒ�����浽GOD�ļ���
	}
	
	
	else 
	{
		head=good_read();
	    p1=p2=head;			//�������Ƕ�����ͷָ��
		system("cls");	//����
		while(p1->next!=NULL)	//��p1�Ƶ�β�ڵ�
        p1=p1->next;
bb2:pa=(GOD*)malloc(sizeof(GOD));	//���붯̬�洢�ռ�
	printf("����������˵ı��:\n");
	fflush(stdin);
    scanf("%d",&pa->code);
	while(p2!=NULL)		//��p2��Ϊ��ʱ
	{	if(pa->code==p2->code)
		{	free(pa);
			printf("���ظ������ˡ�\n");
			goto bb2;
		}
		p2=p2->next;
	}
	p1->next=pa;		//β�ڵ�p1��next���pa
	pa->next=NULL;
    printf("\n������������Ϣ(�����ƣ��������������۸��ۿۣ�������(������)����������)�� \n");    		  
	fflush(stdin);
    scanf("%s%d%d%lf%lf%d%d%d%s",pa->name,&pa->count,&pa->sell,&pa->price,&pa->discount,&pa->yy,&pa->mm,&pa->dd,pa->madein);
    p1->name[19]=0;
    p1->madein[9]=0;
	printf("�������Ʒ��Ϣ�ɹ�,�Ƿ����?(Y/N)\n");
	fflush(stdin);
	scanf("%c",&saveflag);		//���룬���Y or N
	if(saveflag=='y'||saveflag=='Y')	//�������ǵ�ʱ��
		good_save(head);		//���ñ��溯��
	else
	{	printf("�밴������������˵�\n");
		getch();	
	}
	free(pa);
	} 
	return(head);
}



/************************************************
*��������good_save(GOD *head)	//�����ļ�
*���ܣ����������ݣ��������ļ�
*����ֵ��NULL
*************************************************/
void good_save(GOD *head)	//�����ļ�							
{
	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�		
    GOD* t ;			//����һ��ָ�룬��ͷ��β����һ�鵥�������ļ���д��
    if ((fp=fopen("good.txt","w"))==NULL)		//���ļ���д��
    {
        printf("���ļ�ʧ�ܣ�\n");
        getch();     //���������������һ��
        exit(0);		//�˳�
    }
    t=head;			//��ͷָ�븳��t��������ͷ��ʼ
    while(t!=NULL)	//ֻҪtָ�벻Ϊ�գ�����������û�н���
    {
       fwrite(t,sizeof(GOD),1,fp);	//������д���ļ���
       t=t->next;	//ָ�����
    }
    fclose(fp);		//���ļ��ر�
    printf("\n����ɹ�\n");
	getch();	
}


/************************************************
*��������good_read����ȡ��Ʒ��Ϣ�ļ���
*���ܣ���ȡ�ļ��е���Ϣ��������뵥�����У�������󷵻�һ��ͷָ��
*����ֵ��GOD *���ṹ��ָ�룩
*************************************************/
GOD *good_read(GOD *head)        //��ȡ��Ʒ��Ϣ�ļ� 
{    FILE *fp;	//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
    GOD *t1,*t2,*h=NULL;
    if((fp=fopen("good.txt","r"))==NULL)      //�ж��ļ��Ƿ����
    {   printf("���ļ�ʧ�ܣ�û�и��ļ�\n\n");
 		printf("�밴������������˵�\n");
        getch();
		return 0;
     }
	rewind(fp);	  //��������ǰ�һ���ļ���λ��ָ�����������ͷ����Ȼ�Ļ������һ�������ݶ�ʧ
    t1=(GOD *) malloc(sizeof(GOD));	//���붯̬�ռ�
    head=t2=t1;	//��t1����ͷ���
	 while(!feof(fp))	//feof�����Ĺ������ж��ļ��ǲ��ǽ�������������ˣ����ط���ֵ�����򷵻�0��
    {   if(fread(t1,sizeof(GOD),1,fp)!=1)	//fread�������ض���������ĸ���
            break;  //���û�ж�ȡ���ݣ������
	    t1->next=(GOD *)malloc(sizeof(GOD));	//�����붯̬�ռ��ͬʱ����t1��nextָ����һ�����
        t2=t1;     //t2��������β�ڵ�
		t1=t1->next;	//t1�����һ�����
    }
    t2->next=NULL;	
	fclose(fp);		//�ر��ļ�
return head;	//����ͷָ��
}


/************************************************
*��������void good_printf()  // 1.1��ʾ��Ʒ��Ϣ
*���ܣ���ʾ��Ʒ��Ϣ
*����ֵ���޷���ֵ
*************************************************/
void good_printf(GOD *head)  // 1.1��ʾ��Ʒ��Ϣ
{
	GOD *p1=head;
	int i=0;
	printf("\n���   ����   ����   ����   �۸�  �ۿ�  ������(������)   ����\n\n");
    while(p1!=NULL)
	{
		printf("%d      %s      %d      %d      %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		i++;
	}
	printf("\n\n��Ʒ��Ϣ�ɹ���ʾ\n");
	printf("\n����%d����Ʒ\n",i);
	getch();
}

/************************************************
*��������GOD *good_change();  //2.1.2��Ʒ��Ϣ�޸�
*���ܣ��޸�������Ϣ
*����ֵ��GOD *���ṹ��ָ�룩
*************************************************/
GOD* good_change(GOD* head)
{   
    GOD *p1;			
    char saveflag;	
	int t;         //��Ŵ��޸��˵ı��
	int flag=0;		//�޸ı�־
    system("cls");		//����
	p1=head;		
    printf("������Ҫ�޸ĵ���Ʒ��ţ�\n");	
    scanf("%d",&t);		
    while(p1!=NULL)		//���while�����������ڱ�������������
	{   
	if(p1->code==t)	//�ж��ǲ���������ı���ǲ�������Ʒ��Ϣ�ļ��е���ͬ
	   {		
	   flag=1;			//������һ���ı��ʱ��
		printf("\n��Ҫ�޸ĵ���Ʒ��ϢΪ:\n");
		printf("\n���     ����    ����   ����   �۸�  �ۿ�  ������(������)   ����\n\n");
		printf("%d         %s       %d      %d      %.2lf      %.2lf   %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n�������޸ĺ����Ϣ:\n");
		fflush(stdin);
		scanf("%d%s%d%lf%lf%d%d%d%s",&p1->code,p1->name,&p1->count,&p1->price,&p1->discount,&p1->yy,&p1->mm,&p1->dd,p1->madein);
		printf("����Ʒ��Ϣ���޸ĳɹ�\n");
		printf("�Ѿ��½��ɹ�,�Ƿ���б���? (Y/N)\n");
		fflush(stdin);
		scanf("%c",&saveflag);
		if(saveflag=='y'||saveflag=='Y')	//�������ǵ�ʱ��
			good_save(head);			//���ñ��溯��
		else
		{
			printf("�밴������������˵�\n");
			getch();	
		}
			break;
	   }	  
	   p1=p1->next;  //p1ָ�������
	}
    if(flag==0)	//û��������ֵ��ˣ��������˵�
	{
        printf("\nû���ҵ�Ҫ�޸ĵ�ͨѶ�������밴������������˵�!\n");
		getch();	//����������ͽ�����һ�����ĺ���
    }
	return(head);    
}

/************************************************
*��������Search�����ң�
*���ܣ�����ͨ��������ѯ,Ҳ����ͨ�����Ͳ�ѯ
*����ֵ��NULL
*************************************************/
void good_search(GOD* head)
{	int num;	//�Ӳ˵�ѡ��
	int count=0;
	GOD * p1;
	int i;  //i������ű��
	int flag;	//flag�������ж��Ƿ��ҵ���
	char c[20],searchflag='y';	//c�����������
	while(1)
	{	    
		p1=head;
		system("cls");		//����
		printf("\n**************�����Ӳ˵�*******************\n");
		printf("\n\t 1.������\n");
		printf("\n\t 2.�����\n");
		printf("\n\t 3.������Ʒ����˵�\n");
		printf("\n*******************************************\n");
		fflush(stdin);
		num=4;
		scanf("%d",&num);	//ѡ������Ҫ��ѯ�ķ�ʽ	
		switch(num)		
		{
		case 1:	count=0;
				flag=0;		//��ʼ��Ϊ0
				printf("\n����������ҵ�����: \n");
				scanf("%s",c);	
				p1=head;					
				while(p1!=NULL)		
				{  if(strcmp(p1->name,c)==0)	
				   {  count++;
					  if(count==1)
						  printf("\n���     ����    ����   ����   �۸�  �ۿ�  ������(������)   ����\n\n");
					  printf("%d       %s       %d      %d      %.2lf       %.2lf    %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
					   flag=1;		//flag��ֵΪ1����ʾ�Ѿ��鵽��������					   
				   }
				   p1=p1->next;		//p1ָ�������
				}
				if(flag==0)		//��ʾΪû���ҵ��������
					printf("\nδ���ҵ����������ļ�¼\n");
				else
					printf("\n\n\########�ҵ���%d������Ϊ\"%s\"��Ʒ!###########\n\n",count,c);
				fflush(stdin);
				getch();
			break;
		case 2:	count=0;
				flag=0;		//��ʼ��Ϊ0
				printf("\n����������ҵı��: \n");
				scanf("%d",&i);	
				p1=head;					
				while(p1!=NULL)		
				{  if(p1->code ==i)	
				   {  count++;
					  if(count==1)
						  printf("\n���     ����    ����   ����   �۸�  �ۿ�  ������(������)   ����\n\n");
					  printf("%d       %s       %d      %d      %.2lf       %.2lf   %d-%d-%d     %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
					   flag=1;		//flag��ֵΪ1����ʾ�Ѿ��鵽��������					   
				   }
				   p1=p1->next;		//p1ָ�������
				}
				if(flag==0)		//��ʾΪû���ҵ��������
					printf("\nδ���ҵ����������ļ�¼\n");
				else
					printf("\n\n\######�ҵ���%d�����Ϊ\"%d\"��Ʒ!#####\n\n",count,i);
				fflush(stdin);
				getch();
			break;	
		case 3:return;
		default :printf("��������ˣ�����������������ز����Ӳ˵�\n");
			     getch();
		}
	}
}

/************************************************
*�������� Delete��ɾ����
*���ܣ�ͨ������������ʵ��ɾ��ͨѶ��¼
*����ֵ��ID *���ṹ��ָ�룩
*************************************************/
GOD *good_delet(GOD *head)  // 2.1.4��Ʒ��Ϣɾ��
{
GOD *p1,*p2;		//p1������������һ��������λҪɾ���Ľ�㣬p2��������λp1��ǰ����    char  saveflag='n', temp;		//saveflag�Ƿ񱣴棬temp�Ƿ�ɾ��
	int c;	
	char temp,saveflag; 
    p1=p2=head;		//��head����p1,p2  	
    printf("\n������Ҫɾ���ı��:\n");
    scanf("%d",&c);
	getchar();
	while(p1!=NULL)		//while�����������ڱ�������������
	{
	   if(p1->code==c)	//�ж��Ƿ�����û�����ı�� 
	   { 	
		   if(p1->next==NULL)
		   {
			   printf("\n�������һ����Ʒ��Ϣ���޷�ɾ����\n");
			   printf("\n�����������\n");
			   getch();
			   return;
		   }
		    printf("��Ҫɾ������ƷΪ:\n");
			printf("\n���    ����    ����   ����    �۸�  �ۿ�  ������(������)   ����\n\n");
			printf("%d         %s       %d      %d      %.2lf        %.2lf    %d-%d-%d    %s",p1->code,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
			printf("��ȷ���Ƿ�Ҫɾ���ü�¼��Y/N?\n");
			fflush(stdin);
			scanf("%c",&temp);		//ȷ��Ҫɾ����			
			if(temp=='y'||temp=='Y')	//�������ǵ�ʱ��
			 {
			   if(p1==head)		//�ж��ǲ�����ͷ���
				   head=p1->next;	//��ͷ���ȥ��
			   else
                p2->next=p1->next;	//ɾ��p1��㣨p2��next��ָ��p1���¸���㣩
			   printf("����Ʒ��Ϣ��ɾ���ɹ�,�Ƿ����?Y/N?\n");
			   fflush(stdin);
			   scanf("%c",&saveflag);		//ȷ��Ҫ������
			   if(saveflag=='y'||saveflag=='Y')	//�������ǵ�ʱ��
				  good_save(head);			//���ñ��溯��
			   else
				{
					printf("�밴������������˵�\n");
					getch();	
				}
			}
			else
			{
				printf("�밴������������˵�\n");
				getch();	
			}
			break;
	   }
	   p2=p1;
	   p1=p1->next;  //p1ָ�������
	}
	if((p1->next)==NULL&&p1->code!=c)
	{
			printf("û���ҵ�Ҫɾ������Ʒ��Ϣ��������Ҫɾ������Ʒ�Ƿ���ȷ\n");
			printf("�밴������������˵�\n");
			getch();			
	}
	return(head);		//returnһ���Ѿ�����޸ĵ�����ͷָ��   
}


/************************************************
*�������� good_sort   //2.1.6��Ʒ����鿴
*���ܣ�������������ͨѶ��¼
*����ֵ��GOD *���ṹ��ָ�룩
*************************************************/
void good_sort(GOD *head)    //2.1.6��Ʒ����鿴
{
	GOD  *p1,*p2;
	int c,sum=0;
	while(1)
	{
		p2=NULL;
		system("cls");
		p1=head;
		sum=0;
	printf("\n**************�鿴�Ӳ˵�*******************\n");
	printf("\n\t 1.����Ų鿴\n");
	printf("\n\t 2.�����Ʋ鿴\n");
	printf("\n\t 3.�����������鿴\n");
	printf("\n\t 4.������Ʒ����˵�\n");
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
				in_swap(&p1->code,&p1->next->code);          //��������
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
    printf("��Ʒ��Ϣ�Ѱ��� ��� ����ɹ�");
    printf("\n���   ����     ����   ����    �۸�  �ۿ�  ������(������)   ����\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d   %d   %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n��Ʒ��Ϣ�ɹ���ʾ\n");
	printf("\n����%d����Ʒ\n",sum);
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
				in_swap(&p1->code,&p1->next->code);          //��������
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
	printf("��Ʒ��Ϣ�Ѱ��� ���� ����ɹ�\n");
    printf("\n���   ����    ����   ����   �۸�  �ۿ�  ������(������)   ����\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d  %d  %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n��Ʒ��Ϣ�ɹ���ʾ\n");
	printf("\n����%d����Ʒ\n",sum);
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
				in_swap(&p1->code,&p1->next->code);          //��������
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
	printf("��Ʒ��Ϣ�Ѱ��� ���� ����ɹ�\n");
    printf("\n���   ����    ����   ����   �۸�  �ۿ�  ������(������)   ����\n");
    while(p1!=NULL)
	{
		printf("%d   %s   %d  %d  %.2lf   %.2lf   %d-%d-%d     %s",p1->code ,p1->name,p1->count,p1->sell,p1->price,p1->discount,p1->yy,p1->mm,p1->dd,p1->madein);
		printf("\n");
		p1=p1->next;
		sum++;
	}
	printf("\n\n��Ʒ��Ϣ�ɹ���ʾ\n");
	printf("\n����%d����Ʒ\n",sum);
	printf("�´ι�����Ʒ�ɶ๺��������������Ʒ��\n");
	getch(); 
	 break;
case 4:return;
default:printf("\n�����������������\n");
     getch();
}
}
}
