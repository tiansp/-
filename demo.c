

//  book manggement system

//  �����Ա��������

// ���ڣ�2020.6.12


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAX 1000

typedef struct
{
	char isbn[10];
	char bkname[20];		/*����*/
	char author[10];		    /*����*/
	char press[20];		    /*������*/
	float price; 			/*����*/
	int num;				/*����(��λ����)*/
} BOOK;

void ReadData();
void searchfor();
void sort();

int bknum=3;
BOOK bk[MAX]= {{"001","���ֵ��Ӽ���","��־��","�ߵȽ���",58,10},{"002","c++","andrei","yufik",99,40},{"003","python","����","��������ѧ",85,10}};

void WriteData()//�鱾����
{
	FILE *fp;
	if ((fp=fopen("bookdata.txt","w"))==NULL)
	{
		printf("Can not open the file!\n");
		return;
	}
	fwrite(&bknum,sizeof(int),1,fp);
	fwrite(&bk,sizeof(BOOK),bknum,fp);


	rewind(fp);
	fclose(fp);
}

void ReadData()//�鱾����
{
	FILE *fp;
	if((fp=fopen("bookdata.txt","r"))==NULL)
	{
		printf("\n\n��������������ļ������ڣ��봴����(bookdata.txt)");
	}
	fread(&bknum,sizeof(int),1,fp);
	fread(&bk,sizeof(BOOK),bknum,fp);
	rewind(fp);
	fclose(fp);
}

void booklist()//�б�
{
	int i,j;
	j=bknum;
	sort();
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "���","����","����","������","�۸�","����");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i=0; i<j; i++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
		       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	printf("\n\t\t��������������˵�! ");
	getch();
}
void print()
{
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "���","����","����","������","�۸�","����");
	printf("\t\t----------------------------------------------------------------------------\n");
}
void print2()
{
	int i,j;
	j=bknum;
	sort();
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "���","����","����","������","�۸�","����");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i=0; i<j; i++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
		       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
}
void booksale()
{
	int re,a,i,b,n;
	re=bknum;
	float amount=0;
	char need[20];
	system("cls");
	print2();
	do
	{

		printf("\n\n\t\t����������Ҫ����������:");
		scanf("%s",need);
		for ( i=0; i<re; i++)
			if(strcmp(bk[i].bkname,need)==0)
			{
				if(bk[i].num==0)printf("�����治��,����ϵ����Ա����!");
				else
				{
					system("cls");
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					printf("\n\t\t ���Ƿ�������Ҫ�������,����ȷ��(1)����(0):");
					scanf("%d",&a);
					if(!a)break;
					printf("\n\n\n\t\t��������Ҫ���������:");
					scanf("%d",&n);
					if(n>bk[i].num)printf("\n\t\t��治��,��ʣ%d��!!!",bk[i].num);
					else bk[i].num-=n;
					amount+=bk[i].price * n;
					printf("\n\t\t������������(1),��������(0):");
					scanf("%d",&b);
				}
			}


	}
	while(b);
	if (i==bknum)printf("\n\t\t�������Ȿ�飬���������룡");
	{
		booksale();
		getch();
	}

	printf("\n\t\t�ܹ���Ҫ֧��%.2fԪ!!!",amount);
	printf("\n\t\t��������������˵�! ");
	getch();
}

void bookin()
{
	char bookno[10],bookname[20],author[10];
	int price,num,flag=0,i;
	do
	{
		printf("\n\t\t��%d���飡",bknum+1);
		printf("\n\n\n\t\t����000�����ϼ�\n");
		printf("\n\t\t���������:");
		scanf("%s",bookno);
		if(strcmp(bookno,"000")==0)break;
		for(i=0; i<bknum; i++)
		{
			if(strcmp(bookno,bk[i].isbn)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("\n\t\t�������������:");
			scanf("%d",&num);
			bk[i].num+=num;
			system("cls");
			bookin();
			break;
		}
		if(flag==0)
		{
			bknum++;
			strcpy(bk[bknum-1].isbn,bookno);
			printf("\n\t\t����������:");
			scanf("\n");
			gets(bk[bknum-1].bkname);
			printf("\n\t\t����������:");
			scanf("\n");
			gets(bk[bknum-1].author);
			printf("\n\t\t�����������:");
			scanf("\n");
			gets(bk[bknum-1].press);
			printf("\n\t\t������۸�:");
			scanf("%f",&bk[bknum-1].price);
			printf("\n\t\t����������:");
			scanf("%d",&bk[bknum-1].num);
			system("cls");
			bookin();
			break;
		}
	}
	while(1);
	WriteData();
}
void update()//�޸�
{
	int i,choice,jj=0;
	char xxx[10];
	print2();
	printf("\n\n\n��������Ҫ�޸ĵ�ͼ��ı��");
	scanf("%s",xxx);
	printf("\n%s",xxx);
	for(i=0; i<bknum; i++)
	{
		if(strcmp(xxx,bk[i].isbn)==0)
		{
			system("cls");
			print();
			printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );



			printf("\n\n\n\t\t********����������Ҫ�޸ĵ�����********\n\n");
			printf("                1. ���\n\n");
			printf("                2. ����\n\n");
			printf("                3. ����\n\n");
			printf("                4. ������\n\n");
			printf("                5. �۸�\n\n");
			printf("                6. ����\n\n");
			printf("                0. exit\n\n");
			printf("\t\t****************************************\n\n");
			printf("                 ��ѡ��0-6��:");
			scanf("%d",&choice);
			system("cls");
			printf("\n\n\t\t");

			switch(choice)
			{
				case 1:
				{
					printf("\n\t\t��������ĵ��±��:");
					scanf("%s",&bk[i].isbn);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 2:
				{
					printf("\n\t\t��������ĵ�������:");
					scanf("%s",&bk[i].bkname);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 3:
				{
					printf("\n\t\t��������ĵ�������:");
					scanf("%s",&bk[i].author);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 4:
				{
					printf("\n\t\t��������ĵ��³�����:");
					scanf("%s",&bk[i].press);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 5:
				{
					printf("\n\t\t��������ĵ��¼۸�:");
					scanf("%f",&bk[i].price);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 6:
				{
					printf("\n\t\t��������ĵ�������:");
					scanf("%d",&bk[i].num);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 0:
					break;
			}

		}
	}

	printf("\n\t\t��������������˵�! ");
	getch();

}

void del()//ɾ��
{
	char Stuname2[20];
	int i,j,a=0;

	while(1)
	{
		print2();
		printf("\n\n\n\t\t������ͼ������(0�˳�)��");
		scanf("%s",Stuname2);
		if(strcmp(Stuname2,"0")==0)
		{
			break;
		}

		printf("\n");
		for(i=0; i<bknum; i++)
			if(strcmp(bk[i].bkname,Stuname2)==0)
				for(j=i; j<bknum-1; j++)
				{
					strcpy(bk[j].isbn,bk[j+1].isbn);
					strcpy(bk[j].bkname,bk[j+1].bkname);
					strcpy(bk[j].author,bk[j+1].author);
					strcpy(bk[j].press,bk[j+1].press);
					bk[j].price=bk[j+1].price;
					bk[j].num=bk[j+1].num;
				}
		bknum--;
		system("cls");
		print2();
		printf("\n\t\tɾ���ɹ�\n");
		printf("\n\t\t����ɾ������(1),�˳�����(0):");
		scanf("%d",&a);
		if(!a)break;
		system("cls");

	}
	if (i==bknum)
	{
		printf("\n\t\t���޴��飡");
		printf("\n\t\t���������밴1���˳�0��");
		int io;
		scanf("%d",&io);
		if(io)
		{
			system("cls");
			del();
		}

	}
	printf("\n\t\t��������������˵�! ");
	getch();
}

void pquantitydis()//����
{

	printf(" \n\n\n\n\n\n\t\t\t\t**********************************\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*     ��ӭ�������������ϵͳ   *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t**********************************\n");
	printf("\n\n\t\t\t\t��������������˵���");
	getch();
}
int FindEdit()//������Ҳ˵�
{
	printf("\n\n");
	printf("\t   ************************************************************\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      �����Խ������²���:                                 *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ����Ų��� �밴 1                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ���������� �밴 2                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      �����߲��� �밴 3                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ����������� �밴 4                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ������ ���� �밴 5                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      �� 0 �����˵�!                                      *\n");
	printf("\t   ************************************************************\n\n");
	printf("\t   ������:");
	int a;
	scanf("%d",&a);
	return a;
}
int sortEdit()//������Ҳ˵�
{
	printf("\n\n");
	printf("\t   ************************************************************\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      �����Խ������²���:                                 *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ��������� �밴 1                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ������������� �밴 2                               *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      ���۸����� �밴 3                                   *\n");
	printf("\t   *                                                          *\n");
//	printf("\t   *      ����������� �밴 4                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      �� 0 �����˵�!                                      *\n");
	printf("\t   ************************************************************\n\n");
	printf("\t   ������:");
	int a;
	scanf("%d",&a);
	return a;
}
void sort()
{
	int i,j;
	char t[10];
	for(i=0; i<bknum-1; i++)
		for (j=i+1; j<bknum; j++)
			if(strcmp(bk[i].isbn,bk[j].isbn)>0)
				strcpy(t,bk[i].isbn),strcpy(bk[i].isbn,bk[j].isbn),strcpy(bk[j].isbn,t);
}

void sort_price()
{
	int i,j;
	int t;
	char jis[MAX];
	BOOK bkk= {0};
	BOOK bkm[MAX];
	memcpy(&bkm,&bk,sizeof(bk));
	for(i=0; i<bknum-1; i++)
		for (j=i+1; j<bknum; j++)
			if(bkm[i].price>bkm[j].price)
				bkk=bkm[i],bkm[i]=bkm[j],bkm[j]=bkk;
	int i_1,j_1;
	j_1=bknum;
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "���","����","����","������","�۸�","����");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i_1=0; i_1<j_1; i_1++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bkm[i_1].isbn,bkm[i_1].bkname,
		       bkm[i_1].author, bkm[i_1].press,bkm[i_1].price,bkm[i_1].num );
	printf("\n\t\t��������������˵�! ");
	getch();

}
void sort_num()
{
	int i,j;
	int t;
	char jis[MAX];
	BOOK bkk= {0};
	BOOK bkm[MAX];
	memcpy(&bkm,&bk,sizeof(bk));
	for(i=0; i<bknum-1; i++)
		for (j=i+1; j<bknum; j++)
			if(bkm[i].num>bkm[j].num)
				bkk=bkm[i],bkm[i]=bkm[j],bkm[j]=bkk;
	int i_1,j_1;
	j_1=bknum;
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "���","����","����","������","�۸�","����");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i_1=0; i_1<j_1; i_1++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bkm[i_1].isbn,bkm[i_1].bkname,
		       bkm[i_1].author, bkm[i_1].press,bkm[i_1].price,bkm[i_1].num );
	printf("\n\t\t��������������˵�! ");
	getch();

}
void sort_main()
{
	int a;
	a=sortEdit();
	system("cls");
	switch(a)
	{
		case 1:
		{
			sort();
			print2();
			printf("\n\t\t��������������˵�! ");
			getch();
			break;
		}
		case 2:
			sort_num();
			break;
		case 3:
			sort_price();
			break;
		case 0:
			break;
	}
}
void menu()//���˵�
{
	int choice;
	float amount;
	if(bknum==0)
	{
		printf("����¼����������Ϣ�����س�����롪��������\n");
		getch();
	}

	do
	{
		system("cls");
		printf("\n\n\n                         ********ͼ����Ϣ����ϵͳ********\n\n");
		printf("                                1. ����ͼ����Ϣ\n\n");
		printf("                                2. ��ӡͼ����Ϣ\n\n");
		printf("                                3. ��ѯͼ����Ϣ\n\n");
		printf("                                4. �޸�ͼ����Ϣ\n\n");
		printf("                                5. ɾ��ͼ����Ϣ\n\n");
		printf("                                6. ͼ������\n\n");
		printf("                                7. ����\n\n");
		printf("                                0. �˳�ϵͳ");
		printf("\n\n\n                          ********************************\n\n");
		printf("                                ��ѡ��0-6��:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				system("cls");
				bookin();
				WriteData();
				break;/*����ͼ����Ϣ*/
			case 2:
				system("cls");
				booklist();
				break;/*��ӡͼ����Ϣ*/
			case 3:
				system("cls");
				searchfor();
				break;/*��ѯͼ����Ϣ*/
			case 4:
				system("cls");
				update();
				WriteData();
				break;/*�޸�ͼ����Ϣ*/
			case 5:
				system("cls");
				del();
				WriteData();
				break;/*ɾ��ͼ����Ϣ*/
			case 6:
				system("cls");
				booksale();

				WriteData();
				break;
			case 7:
				system("cls");
				sort_main();
				break;
			case 0:
				break;
		}
	}
	while(choice!=0);

}

//����Ų���
int FindByNum()
{
	system("cls");
	int num=bknum;
	if (num == 0)
	{
		printf("\n\n\t\t���ݿ�����û��ͼ����Ϣ�������ͼ����Ϣ\n\n\t\t\t   ");
		getch();
		return;
	}
	int i;
	int flag=0;
	char biao[20]= {0};
	char sex[10];
	printf("\n\n\t\t������Ҫ���ҵ���ţ�");
	scanf("%s", sex);

	for (i = 0; i < num; i++)
		if (strcmp(bk[i].isbn,sex) == 0)
		{
			printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}
//����������
int FindByName()
{
	system("cls");
	int i;
	int flag=0;
	int num=bknum;
	char biao[20]= {0};
	char name[20];
	if (num == 0)
	{
		printf("\n\n\t\t���ݿ�����û��ͼ����Ϣ�������ͼ����Ϣ\n\n\t\t\t   ");
		getch();
		return;
	}
	printf("\n\n\t\t��������Ҫ���ҵ�ͼ���������");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].bkname)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}
//�����߲���
int FindByAuthor()
{
	system("cls");
	int i;
	int flag=0;
	int num=bknum;
	if (num == 0)
	{
		printf("\n\n\t\t���ݿ�����û��ͼ����Ϣ�������ͼ����Ϣ\n\n\t\t\t   ");
		getch();
		return;
	}
	char biao[20];
	char name[20];
	printf("\n\n\t\t��������Ҫ���ҵ�ͼ������ߣ�");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].author)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}
int FindByPress()
{
	system("cls");
	int i;
	int flag;
	int num=bknum;
	if (num == 0)
	{
		printf("\n\n\t\t���ݿ�����û��ͼ����Ϣ�������ͼ����Ϣ\n\n\t\t\t   ");
		getch();
		return;
	}
	char biao[20];
	char name[20];
	printf("\n\n\t\t��������Ҫ���ҵ�ͼ��ĳ����磺");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].press)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}


void search_fix()
{
	int a1=0,a2=0,a3=0;
	int i;
	int j;

	system("cls");

	char biao_1[20]= {0};
	char sex_1[20];
	printf("\n\n\t\t������Ҫ���ҵ�������");
	scanf("%s", sex_1);

	char biao_2[20]= {0};
	char sex_2[20];
	printf("\n\n\t\t������Ҫ���ҵ����ߣ�");
	scanf("%s", sex_2);

	char biao_3[20]= {0};
	char sex_3[20];
	printf("\n\n\t\t������Ҫ���ҵĳ����磺");
	scanf("%s", sex_3);

	for (i = 0; i < bknum; i++)

	{
		if (strstr(bk[i].bkname,sex_1)!=NULL)
		{
			
					biao_1[i]=1;
					a1=1;
		}


		if (strstr(bk[i].author,sex_2)!=NULL)
		{
			
					biao_2[i]=1;
					a2=1;
		}
		
		if (strstr(bk[i].press,sex_3)!=NULL)
		{
			
					biao_3[i]=1;
					a3=1;
		}
	}

	if(a1 && a2 && a3)
	{
		for(i=0; i<20; i++)
			if(biao_1[i]==1)
				printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a1 && a2 )
	{
		for(i=0; i<20; i++)
			if(biao_1[i]==1)
				printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a1 && a3)
	{
		for(i=0; i<20; i++)
			if(biao_1[i]==1)
				printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a2 && a3)
	{
		for(i=0; i<20; i++)
			if(biao_2[i]==1)
				printf("\n\t\t���:%-8s����:%-10s����:%-10s������:%-10s�۸�:%-8.2f����:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );}
	else printf("\n\t\t�������������������鼮��");




}
void searchfor()//����
{
	int a=FindEdit();
	int b=1;
	int c;
	while(b)
	{

		switch(a)
		{
			case 1:
				c=FindByNum();
				printf("\n\n\t\t����(1),�˳�(0):");
				scanf("%d",&b);
				break;
			case 2:
				c=FindByName();
				printf("\n\n\t\t����(1),�˳�(0):");
				scanf("%d",&b);
				break;
			case 3:
				c=FindByAuthor();
				printf("\n\n\t\t����(1),�˳�(0):");
				scanf("%d",&b);
				break;
			case 4:
				c=FindByPress();
				printf("\n\n\t\t����(1),�˳�(0):");
				scanf("%d",&b);
				break;
			case 5:
				search_fix();
				printf("\n\n\t\t����(1),�˳�(0):");
				scanf("%d",&b);
				break;
			case 0:
				b=0;
				break;
			default:
				b=0;
				break;
		}

	}
//������,���,������,���߲���
//ģ������

}

int main()
{
	system("color 0B");
	ReadData();
	pquantitydis();
	menu();

}
























