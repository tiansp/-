

//  book manggement system

//  完成人员：田仕鹏

// 日期：2020.6.12


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAX 1000

typedef struct
{
	char isbn[10];
	char bkname[20];		/*书名*/
	char author[10];		    /*作者*/
	char press[20];		    /*出版社*/
	float price; 			/*单价*/
	int num;				/*数量(单位：册)*/
} BOOK;

void ReadData();
void searchfor();
void sort();

int bknum=3;
BOOK bk[MAX]= {{"001","数字电子技术","杨志忠","高等教育",58,10},{"002","c++","andrei","yufik",99,40},{"003","python","嵩天","北京理工大学",85,10}};

void WriteData()//书本数据
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

void ReadData()//书本数据
{
	FILE *fp;
	if((fp=fopen("bookdata.txt","r"))==NULL)
	{
		printf("\n\n—————库存文件不存在！请创建！(bookdata.txt)");
	}
	fread(&bknum,sizeof(int),1,fp);
	fread(&bk,sizeof(BOOK),bknum,fp);
	rewind(fp);
	fclose(fp);
}

void booklist()//列表
{
	int i,j;
	j=bknum;
	sort();
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "书号","书名","作者","出版社","价格","数量");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i=0; i<j; i++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
		       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	printf("\n\t\t按任意键返回主菜单! ");
	getch();
}
void print()
{
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "书号","书名","作者","出版社","价格","数量");
	printf("\t\t----------------------------------------------------------------------------\n");
}
void print2()
{
	int i,j;
	j=bknum;
	sort();
	printf("\n\n\t\t----------------------------------------------------------------------------\n");
	printf("\t\t%-10s%-20s%-10s%-20s%-10s%-5s\n",
	       "书号","书名","作者","出版社","价格","数量");
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

		printf("\n\n\t\t请输入您想要买的书的名称:");
		scanf("%s",need);
		for ( i=0; i<re; i++)
			if(strcmp(bk[i].bkname,need)==0)
			{
				if(bk[i].num==0)printf("本书库存不足,请联系管理员补充!");
				else
				{
					system("cls");
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					printf("\n\t\t 这是否是您需要购买的书,是请确认(1)不是(0):");
					scanf("%d",&a);
					if(!a)break;
					printf("\n\n\n\t\t请输入您要购买的数量:");
					scanf("%d",&n);
					if(n>bk[i].num)printf("\n\t\t库存不足,仅剩%d本!!!",bk[i].num);
					else bk[i].num-=n;
					amount+=bk[i].price * n;
					printf("\n\t\t继续购买输入(1),结账输入(0):");
					scanf("%d",&b);
				}
			}


	}
	while(b);
	if (i==bknum)printf("\n\t\t不存在这本书，请重新输入！");
	{
		booksale();
		getch();
	}

	printf("\n\t\t总共需要支付%.2f元!!!",amount);
	printf("\n\t\t按任意键返回主菜单! ");
	getch();
}

void bookin()
{
	char bookno[10],bookname[20],author[10];
	int price,num,flag=0,i;
	do
	{
		printf("\n\t\t第%d本书！",bknum+1);
		printf("\n\n\n\t\t输入000返回上级\n");
		printf("\n\t\t请输入书号:");
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
			printf("\n\t\t请重新输入书号:");
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
			printf("\n\t\t请输入书名:");
			scanf("\n");
			gets(bk[bknum-1].bkname);
			printf("\n\t\t请输入作者:");
			scanf("\n");
			gets(bk[bknum-1].author);
			printf("\n\t\t请输入出版社:");
			scanf("\n");
			gets(bk[bknum-1].press);
			printf("\n\t\t请输入价格:");
			scanf("%f",&bk[bknum-1].price);
			printf("\n\t\t请输入数量:");
			scanf("%d",&bk[bknum-1].num);
			system("cls");
			bookin();
			break;
		}
	}
	while(1);
	WriteData();
}
void update()//修改
{
	int i,choice,jj=0;
	char xxx[10];
	print2();
	printf("\n\n\n请输入您要修改的图书的编号");
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



			printf("\n\n\n\t\t********请输入您想要修改的数据********\n\n");
			printf("                1. 编号\n\n");
			printf("                2. 书名\n\n");
			printf("                3. 作者\n\n");
			printf("                4. 出版社\n\n");
			printf("                5. 价格\n\n");
			printf("                6. 数量\n\n");
			printf("                0. exit\n\n");
			printf("\t\t****************************************\n\n");
			printf("                 请选择（0-6）:");
			scanf("%d",&choice);
			system("cls");
			printf("\n\n\t\t");

			switch(choice)
			{
				case 1:
				{
					printf("\n\t\t请输入你改的新编号:");
					scanf("%s",&bk[i].isbn);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 2:
				{
					printf("\n\t\t请输入你改的新书名:");
					scanf("%s",&bk[i].bkname);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 3:
				{
					printf("\n\t\t请输入你改的新作者:");
					scanf("%s",&bk[i].author);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 4:
				{
					printf("\n\t\t请输入你改的新出版社:");
					scanf("%s",&bk[i].press);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 5:
				{
					printf("\n\t\t请输入你改的新价格:");
					scanf("%f",&bk[i].price);
					print();
					printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bk[i].isbn,bk[i].bkname,
					       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
					break;
				}
				case 6:
				{
					printf("\n\t\t请输入你改的新数量:");
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

	printf("\n\t\t按任意键返回主菜单! ");
	getch();

}

void del()//删除
{
	char Stuname2[20];
	int i,j,a=0;

	while(1)
	{
		print2();
		printf("\n\n\n\t\t请输入图书书名(0退出)：");
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
		printf("\n\t\t删除成功\n");
		printf("\n\t\t继续删除输入(1),退出输入(0):");
		scanf("%d",&a);
		if(!a)break;
		system("cls");

	}
	if (i==bknum)
	{
		printf("\n\t\t查无此书！");
		printf("\n\t\t重新输入请按1；退出0：");
		int io;
		scanf("%d",&io);
		if(io)
		{
			system("cls");
			del();
		}

	}
	printf("\n\t\t按任意键返回主菜单! ");
	getch();
}

void pquantitydis()//界面
{

	printf(" \n\n\n\n\n\n\t\t\t\t**********************************\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*     欢迎进入简易书店管理系统   *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t*                                *\n");
	printf(" \t\t\t\t**********************************\n");
	printf("\n\n\t\t\t\t按任意键进入主菜单！");
	getch();
}
int FindEdit()//输出查找菜单
{
	printf("\n\n");
	printf("\t   ************************************************************\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      您可以进行以下操作:                                 *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按书号查找 请按 1                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按书名查找 请按 2                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按作者查找 请按 3                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按出版社查找 请按 4                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      多条件 查找 请按 5                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按 0 回主菜单!                                      *\n");
	printf("\t   ************************************************************\n\n");
	printf("\t   请输入:");
	int a;
	scanf("%d",&a);
	return a;
}
int sortEdit()//输出查找菜单
{
	printf("\n\n");
	printf("\t   ************************************************************\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      您可以进行以下操作:                                 *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按书号排序 请按 1                                   *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按库存数量排序 请按 2                               *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按价格排序 请按 3                                   *\n");
	printf("\t   *                                                          *\n");
//	printf("\t   *      按出版社查找 请按 4                                  *\n");
	printf("\t   *                                                          *\n");
	printf("\t   *      按 0 回主菜单!                                      *\n");
	printf("\t   ************************************************************\n\n");
	printf("\t   请输入:");
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
	       "书号","书名","作者","出版社","价格","数量");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i_1=0; i_1<j_1; i_1++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bkm[i_1].isbn,bkm[i_1].bkname,
		       bkm[i_1].author, bkm[i_1].press,bkm[i_1].price,bkm[i_1].num );
	printf("\n\t\t按任意键返回主菜单! ");
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
	       "书号","书名","作者","出版社","价格","数量");
	printf("\t\t----------------------------------------------------------------------------\n");
	for (i_1=0; i_1<j_1; i_1++)
		printf("\t\t%-10s%-20s%-10s%-20s%-10.2f%-5d\n",bkm[i_1].isbn,bkm[i_1].bkname,
		       bkm[i_1].author, bkm[i_1].press,bkm[i_1].price,bkm[i_1].num );
	printf("\n\t\t按任意键返回主菜单! ");
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
			printf("\n\t\t按任意键返回主菜单! ");
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
void menu()//主菜单
{
	int choice;
	float amount;
	if(bknum==0)
	{
		printf("首先录入基本库存信息！按回车后进入—————\n");
		getch();
	}

	do
	{
		system("cls");
		printf("\n\n\n                         ********图书信息管理系统********\n\n");
		printf("                                1. 创建图书信息\n\n");
		printf("                                2. 打印图书信息\n\n");
		printf("                                3. 查询图书信息\n\n");
		printf("                                4. 修改图书信息\n\n");
		printf("                                5. 删除图书信息\n\n");
		printf("                                6. 图书销售\n\n");
		printf("                                7. 排序\n\n");
		printf("                                0. 退出系统");
		printf("\n\n\n                          ********************************\n\n");
		printf("                                请选择（0-6）:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				system("cls");
				bookin();
				WriteData();
				break;/*创建图书信息*/
			case 2:
				system("cls");
				booklist();
				break;/*打印图书信息*/
			case 3:
				system("cls");
				searchfor();
				break;/*查询图书信息*/
			case 4:
				system("cls");
				update();
				WriteData();
				break;/*修改图书信息*/
			case 5:
				system("cls");
				del();
				WriteData();
				break;/*删除图书信息*/
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

//按书号查找
int FindByNum()
{
	system("cls");
	int num=bknum;
	if (num == 0)
	{
		printf("\n\n\t\t数据库中暂没有图书信息，请添加图书信息\n\n\t\t\t   ");
		getch();
		return;
	}
	int i;
	int flag=0;
	char biao[20]= {0};
	char sex[10];
	printf("\n\n\t\t请输入要查找的书号：");
	scanf("%s", sex);

	for (i = 0; i < num; i++)
		if (strcmp(bk[i].isbn,sex) == 0)
		{
			printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}
//按书名查找
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
		printf("\n\n\t\t数据库中暂没有图书信息，请添加图书信息\n\n\t\t\t   ");
		getch();
		return;
	}
	printf("\n\n\t\t请输入您要查找的图书的书名：");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].bkname)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
			       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
			flag=i;
		}
	return flag;
}
//按作者查找
int FindByAuthor()
{
	system("cls");
	int i;
	int flag=0;
	int num=bknum;
	if (num == 0)
	{
		printf("\n\n\t\t数据库中暂没有图书信息，请添加图书信息\n\n\t\t\t   ");
		getch();
		return;
	}
	char biao[20];
	char name[20];
	printf("\n\n\t\t请输入您要查找的图书的作者：");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].author)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
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
		printf("\n\n\t\t数据库中暂没有图书信息，请添加图书信息\n\n\t\t\t   ");
		getch();
		return;
	}
	char biao[20];
	char name[20];
	printf("\n\n\t\t请输入您要查找的图书的出版社：");
	scanf("%s",&name);
	for(i=0; i<num; i++)
		if(strcmp(name,bk[i].press)==0)
			biao[i]=1;

	for (i = 0; i < 20; i++)
		if (biao[i] == 1)
		{
			printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
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
	printf("\n\n\t\t请输入要查找的书名：");
	scanf("%s", sex_1);

	char biao_2[20]= {0};
	char sex_2[20];
	printf("\n\n\t\t请输入要查找的作者：");
	scanf("%s", sex_2);

	char biao_3[20]= {0};
	char sex_3[20];
	printf("\n\n\t\t请输入要查找的出版社：");
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
				printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a1 && a2 )
	{
		for(i=0; i<20; i++)
			if(biao_1[i]==1)
				printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a1 && a3)
	{
		for(i=0; i<20; i++)
			if(biao_1[i]==1)
				printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );
	}
	else if(a2 && a3)
	{
		for(i=0; i<20; i++)
			if(biao_2[i]==1)
				printf("\n\t\t编号:%-8s书名:%-10s作者:%-10s出版社:%-10s价格:%-8.2f数量:%-4d\n",bk[i].isbn,bk[i].bkname,
				       bk[i].author, bk[i].press,bk[i].price,bk[i].num );}
	else printf("\n\t\t不存在条件都成立的书籍！");




}
void searchfor()//搜索
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
				printf("\n\n\t\t继续(1),退出(0):");
				scanf("%d",&b);
				break;
			case 2:
				c=FindByName();
				printf("\n\n\t\t继续(1),退出(0):");
				scanf("%d",&b);
				break;
			case 3:
				c=FindByAuthor();
				printf("\n\n\t\t继续(1),退出(0):");
				scanf("%d",&b);
				break;
			case 4:
				c=FindByPress();
				printf("\n\n\t\t继续(1),退出(0):");
				scanf("%d",&b);
				break;
			case 5:
				search_fix();
				printf("\n\n\t\t继续(1),退出(0):");
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
//按书名,编号,出版社,作者查找
//模糊查找

}

int main()
{
	system("color 0B");
	ReadData();
	pquantitydis();
	menu();

}
























