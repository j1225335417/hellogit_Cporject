#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct student)
#define FORMAT "%7d %13s %13s %7d %15s\n"
#define DATA stu[i].s_num,stu[i].name,stu[i].sex,stu[i].age,stu[i].remarks
struct student{		// 定义学生的结构体 
	int s_num;
	char name[15];
	char sex[2];
	int age;
	char remarks[40];
};
struct student stu[35];  // 定义一个结构体数组存放学生信息 
void menu();  // 菜单函数
void input(); // 信息录入函数
void show();  // 信息显示函数
void del();  // 信息删除函数 
void change();  // 信息修改函数
void search();   // 信息查询函数
void exit_();   // 退出程序的函数
void changePassword(); // 修改密码的函数 
//查询功能的下属函数 
void num_sh(int num);  
void name_sh(char name[]);
void sex_sh(char sex[]);
void age_sh(int age);
int main()
{
	int n;
	char y;
	int password;
	int pa;
	FILE *pass;
	system("cls");
  	printf("\n\n\n\n\n");
  	printf("\t\t*---------<班级档案管理系统>--------*\n");
  	printf("\t\t*                                   *\n");
    printf("\t\t*         你是否有密码(y/n)         *\n");
  	printf("\t\t*                                   *\n");
  	printf("\t\t*-----------------------------------*\n\n");
  	printf("\t\t输入:");
	scanf("%c",&y);
	if(y == 'y' || y == 'Y'){
		printf("\t\t输入密码");
		scanf("%d",&password);
		pass = fopen("password.txt","a+");  // 打开一个文件存密码 
		fread(&pa,sizeof(pa),1,pass);
		if(password == pa){    // 验证密码 
			menu();
			scanf("%d",&n);/*输入选择功能的编号*/
			while(n)
			{ 
				switch(n)
			    { 
			       case 0: exit_();break;
				   case 1: input();break;
			       case 2: search();break;
			       case 3: del();break;
			       case 4: changePassword();break;
			       case 5: change();break;
			       case 6: show();break;
			       default:break;
			    }
			    getch();  // 待输入一个值 
			    menu();/*执行完功能再次显示菜单界面*/
			    scanf("%d",&n);
			}
		}
		else
		{
			printf("\t\t验证密码失败"); 
		}
	}
	else{
		printf("\t\t请先设置4位数的密码:");
		scanf("%d",&password);
		if((pass = fopen("password.txt","a+"))==NULL)/*打开指定文件*/
		{ 
			printf("can not open\n");
			return 0;
		}
		else{
				if(fwrite(&password,sizeof(password),1,pass)==1);
				printf("请重启登陆"); 
		}
	}
	
	return 0; 
}
void menu(){
	system("cls");
  	printf("\n\n\n\n\n");
  	printf("\t\t*---------- <班级档案管理系统>---------*\n");
  	printf("\t\t*             0. 退出程序              *\n");
  	printf("\t\t*             1. 录入信息              *\n");
  	printf("\t\t*             2. 查询信息              *\n");
  	printf("\t\t*             3. 删除信息              *\n");
  	printf("\t\t*             4. 修改密码              *\n");
  	printf("\t\t*             5. 修改信息              *\n");
  	printf("\t\t*             6. 输出信息              *\n");
  	printf("\t\t*--------------------------------------*\n\n");
  	printf("\t\t输入你想选择的功能代码(0-6):");
}
void exit_(){
	printf("退出系统成功");
	system("TASKKILL C项目.exe");
}

void changePassword(){
	FILE *fp;/*定义文件指针*/
	int newPassword;
	if((fp=fopen("password.txt","wb"))==NULL)/*打开指定文件*/
	{ 
		printf("can not open\n");
		return;
	}
	printf("\t\t请输入新的密码:");
	scanf("%d",&newPassword);
	if(fwrite(&newPassword,sizeof(int),1,fp) !=1){
		printf("\t\t修改失败");
		getch();
		fclose(fp);
		return;
	}
	printf("\t\t修改成功");
	fclose(fp);
}

void input(){
	int i,m=0;/*m是记录的条数*/
	char ch[2];  
	FILE *fp;/*定义文件指针*/
	if((fp=fopen("data.txt","a+"))==NULL)/*打开指定文件*/
	{ 
		printf("can not open\n");
		return;
	}
	while(!feof(fp))
	{
		if(fread(&stu[m] ,LEN,1,fp)==1)
		m++;/*统计当前记录条数*/
	}
	fclose(fp);
	if(m==0)
		printf("No record!\n");
	else
	{
		system("cls");
	    show();/*调用show函数，显示原有信息*/
	}
	if((fp=fopen("data.txt","wb"))==NULL){
		printf("can not open\n");
		return;
	}
	for(i=0;i<m;i++){
		fwrite(&stu[i] ,LEN,1,fp);/*向指定的磁盘文件写入信息*/
	}

    printf("请输入(y/n)开始或结束:");
    scanf("%s",ch);
	while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否要录入新信息*/
	{
	    printf("学号:");
		scanf("%d",&stu[m].s_num);/*输入学生学号*/
	    for(i=0;i<m;i++)
		    if(stu[i].s_num==stu[m].s_num){
			    printf("学号重复!");
			    getch();
			    fclose(fp);
			    return;
		    }
		
	        printf("姓名:");
		 	scanf("%s",stu[m].name);/*输入学生姓名*/
	    	printf("性别:");
	     	scanf("%s",&stu[m].sex);/*输入学生性别*/
	     	printf("年龄:");
		 	scanf("%d",&stu[m].age);/*输入学生年龄*/
		 	printf("备注:");
		 	scanf("%s",&stu[m].remarks); // 输入备注 
	     	if(fwrite(&stu[m],LEN,1,fp)!=1)/*将新录入的信息写入指定的磁盘文件*/
	     	{
			 	printf("can not save!");
				getch();
		 	}
	     	else
		 	{
			 	printf("%s saved!\n",stu[m].name);
			 	m++;
		 	}
	     	printf("是否继续?(y/n):");/*询问是否继续*/
	     	scanf("%s",ch);
	}
	fclose(fp);
}
void show(){
   FILE *fp;
   int i,m=0;
   fp=fopen("data.txt","rb");
   while(!feof(fp)){
   		if(fread(&stu[m] ,LEN,1,fp)==1) 
   		m++;
   }  
   fclose(fp);
   printf("学号              姓名           性别     年龄         备注\t\n");
   for(i=0;i<m;i++){ 
	   printf(FORMAT,DATA);/*将信息按指定格式打印*/
   }
}

void change(){
	int pword,num,pw;
	int i,j,m=0;
	int t; 
	FILE *fp,*p,*password;
	password = fopen("password.txt","a+");
	fread(&pw,sizeof(int),1,password);
	printf("\t\t请输入你的密码：");
	scanf("%d",&pword);
	if(pword == pw){
		printf("\t\t输入你要修改的学生学号：");
		scanf("%d",&num);
		fp=fopen("data.txt","r+");
		if(fp == NULL){
			printf("can not open!");
		}
		else{
			while(!feof(fp)){
	        	if(fread(&stu[m],LEN,1,fp)==1)
	        		m++;
    		}
		}
		for(i=0;i<m;i++){
			if(stu[i].s_num == num){
				printf("\t\t姓名:");
	 			scanf("%s",stu[i].name);/*更改学生姓名*/
    			printf("\t\t性别:");
     			scanf("%s",&stu[i].sex);/*更改学生性别*/
     			printf("\t\t年龄:");
	 			scanf("%d",&stu[i].age);/*更改学生年龄*/
	 			printf("\t\t备注:");
	 			scanf("%s",&stu[i].remarks); // 更改备注 
	 			if((fp=fopen("data.txt","wb"))==NULL)
     			{ 
				 	printf("can not open\n");
					return;
				}
				for(j=0;j<m;j++){
					if(fwrite(&stu[j],LEN,1,fp)!=1)/*将新录入的信息写入指定的磁盘文件*/
	     			{
	     				printf("can not open"); 
			 			return;
		 			}
	     			else
		 			{
		 				t=1;
		 			}
		 		}
		 		if(t==1){
		 			printf("%s 修改成功!\n",stu[i].name);
				 }
				 else{
				 	printf("修改失败!\n");
					getch();
				 }
	 			fclose(fp);
				return ;
			} 
		}
	}
	else{
		printf("你的密码错误！");
		getch();
		return;
	}
}

void search(){
	int case_,num,age;
	char name[15];
	char sex[2];
	printf("\t\t 请选择查询方式\n");
	printf("\t\t 1:学号查询\n");
	printf("\t\t 2:姓名查询\n");
	printf("\t\t 3:性别查询\n");
	printf("\t\t 4:年龄查询\n");
	printf("\t\t请输入对应的号码：");
	scanf("%d",&case_);
	switch(case_)
	{
		case 1: 
			printf("\t\t请输入学号:");
			scanf("%d",&num);
			num_sh(num);
			break;
		case 2:
			printf("\t\t请输入名字:");
			scanf("%s",name);
			name_sh(name);
			break;
		case 3:
			printf("\t\t请输入性别:");
			scanf("%s",sex);
			sex_sh(sex);
			break;
		case 4:
			printf("\t\t请输入年龄:");
			scanf("%d",&age);
			age_sh(age);
			break;
	}
}

void del(){
	FILE *fp;
	int snum,i,j,m=0;
	char ch[2];
	if((fp=fopen("data.txt","r+"))==NULL)
	{
		printf("can not open\n");
		return;
	}
	while( !feof(fp) )  
		if(fread(&stu[m],LEN,1,fp)==1) m++;
		fclose(fp);
	if(m==0) 
	{
		printf("没有学生信息记录!\n");
		return;
	}
  	show();
	printf("请输入你要删除学生的学号:");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
	{
		if(snum==stu[i].s_num)
		{    
			printf("找到删除信息，确定吗?(y/n)");
			scanf("%s",ch);
			if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否要进行删除*/
			{ 
				for(j=i;j<m;j++){ 
					stu[j]=stu[j+1];/*将后一个记录移到前一个记录的位置*/
				} 
				m--;/*记录的总个数减1*/
			} 
			if((fp=fopen("data.txt","wb"))==NULL)
			{ 
				printf("can not open\n");
				return;
			}
			for(j=0;j<m;j++){  /*将更改后的记录重新写入指定的磁盘文件中*/
				if(fwrite(&stu[j] ,LEN,1,fp)!=1)
				{ 	
					printf("can not save!\n");
					getch();
				}
			} 
			fclose(fp);
			printf("删除成功!\n");
			return;
		}
	}
	printf("没有找到要删除的信息！\n");
}
//只是几个查询的函数 
void num_sh(int num){
    FILE *fp;
    int i,m=0;
    if((fp=fopen("data.txt","rb"))==NULL){ 
		printf("can not open\n");
		return;
	}
    while(!feof(fp)){
		if(fread(&stu[m],LEN,1,fp)==1) 
		m++;
	}
  	fclose(fp);
  	if(m==0) {
	    printf("\t\t没有记录!\n");
		return;
	}
  	for(i=0;i<m;i++)
    if(num==stu[i].s_num)/*查找输入的学号是否在记录中*/
    { 
	   	printf("学号              姓名           性别     年龄         备注\t\n");
	    printf(FORMAT,DATA);/*将查找出的结果按指定格式输出*/
		break;
    }   
  	if(i==m) 
	  printf("没有这个学生或者你的学号不对!\n");/*未找到要查找的信息*/
}

void name_sh(char name[]){
	FILE *fp;
    int i,j=0,m=0;
    if((fp=fopen("data.txt","rb"))==NULL){ 
		printf("can not open\n");
		return;
	}
    while(!feof(fp)){
		if(fread(&stu[m],LEN,1,fp)==1) 
		m++;
	}
  	fclose(fp);
  	if(m==0) {
	    printf("没有记录!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(strcmp(name,stu[i].name)==0)/*查找输入的姓名是否在记录中*/
    { 
	    printf("学号              姓名           性别     年龄         备注\t\n");
	    printf(FORMAT,DATA);/*将查找出的结果按指定格式输出*/
	    j=1;
    }   
  	if(j!=1) 
	  printf("没有这个学生或者你的学号不对!\n");/*未找到要查找的信息*/
}
void sex_sh(char sex[]){
	FILE *fp;
    int i,m=0;
    if((fp=fopen("data.txt","rb"))==NULL){ 
		printf("can not open\n");
		return;
	}
    while(!feof(fp)){
		if(fread(&stu[m],LEN,1,fp)==1) 
		m++;
	}
  	fclose(fp);
  	if(m==0) {
	    printf("没有记录!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(strcmp(sex,stu[i].sex)==0)/*查找输入的性别是否在记录中*/
    { 
	   	printf("学号              姓名           性别     年龄         备注\t\n");
	    printf(FORMAT,DATA);/*将查找出的结果按指定格式输出*/
    }   
}
void age_sh(int age){
	FILE *fp;
    int i,j=0,m=0;
    if((fp=fopen("data.txt","rb"))==NULL){ 
		printf("can not open\n");
		return;
	}
    while(!feof(fp)){
		if(fread(&stu[m],LEN,1,fp)==1) 
		m++;
	}
  	fclose(fp);
  	if(m==0) {
	    printf("没有记录!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(age == stu[i].age)/*查找输入的年龄是否在记录中*/
    { 
	   	printf("学号              姓名           性别     年龄         备注\t\n");
	    printf(FORMAT,DATA);/*将查找出的结果按指定格式输出*/
	    j=1;
    }   
    if(j!=1)
	  printf("你输入的年龄可能不符合逻辑!\n");/*未找到要查找的信息*/
}

