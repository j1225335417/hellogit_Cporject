#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct student)
#define FORMAT "%7d %13s %13s %7d %15s\n"
#define DATA stu[i].s_num,stu[i].name,stu[i].sex,stu[i].age,stu[i].remarks
struct student{		// ����ѧ���Ľṹ�� 
	int s_num;
	char name[15];
	char sex[2];
	int age;
	char remarks[40];
};
struct student stu[35];  // ����һ���ṹ��������ѧ����Ϣ 
void menu();  // �˵�����
void input(); // ��Ϣ¼�뺯��
void show();  // ��Ϣ��ʾ����
void del();  // ��Ϣɾ������ 
void change();  // ��Ϣ�޸ĺ���
void search();   // ��Ϣ��ѯ����
void exit_();   // �˳�����ĺ���
void changePassword(); // �޸�����ĺ��� 
//��ѯ���ܵ��������� 
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
  	printf("\t\t*---------<�༶��������ϵͳ>--------*\n");
  	printf("\t\t*                                   *\n");
    printf("\t\t*         ���Ƿ�������(y/n)         *\n");
  	printf("\t\t*                                   *\n");
  	printf("\t\t*-----------------------------------*\n\n");
  	printf("\t\t����:");
	scanf("%c",&y);
	if(y == 'y' || y == 'Y'){
		printf("\t\t��������");
		scanf("%d",&password);
		pass = fopen("password.txt","a+");  // ��һ���ļ������� 
		fread(&pa,sizeof(pa),1,pass);
		if(password == pa){    // ��֤���� 
			menu();
			scanf("%d",&n);/*����ѡ���ܵı��*/
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
			    getch();  // ������һ��ֵ 
			    menu();/*ִ���깦���ٴ���ʾ�˵�����*/
			    scanf("%d",&n);
			}
		}
		else
		{
			printf("\t\t��֤����ʧ��"); 
		}
	}
	else{
		printf("\t\t��������4λ��������:");
		scanf("%d",&password);
		if((pass = fopen("password.txt","a+"))==NULL)/*��ָ���ļ�*/
		{ 
			printf("can not open\n");
			return 0;
		}
		else{
				if(fwrite(&password,sizeof(password),1,pass)==1);
				printf("��������½"); 
		}
	}
	
	return 0; 
}
void menu(){
	system("cls");
  	printf("\n\n\n\n\n");
  	printf("\t\t*---------- <�༶��������ϵͳ>---------*\n");
  	printf("\t\t*             0. �˳�����              *\n");
  	printf("\t\t*             1. ¼����Ϣ              *\n");
  	printf("\t\t*             2. ��ѯ��Ϣ              *\n");
  	printf("\t\t*             3. ɾ����Ϣ              *\n");
  	printf("\t\t*             4. �޸�����              *\n");
  	printf("\t\t*             5. �޸���Ϣ              *\n");
  	printf("\t\t*             6. �����Ϣ              *\n");
  	printf("\t\t*--------------------------------------*\n\n");
  	printf("\t\t��������ѡ��Ĺ��ܴ���(0-6):");
}
void exit_(){
	printf("�˳�ϵͳ�ɹ�");
	system("TASKKILL C��Ŀ.exe");
}

void changePassword(){
	FILE *fp;/*�����ļ�ָ��*/
	int newPassword;
	if((fp=fopen("password.txt","wb"))==NULL)/*��ָ���ļ�*/
	{ 
		printf("can not open\n");
		return;
	}
	printf("\t\t�������µ�����:");
	scanf("%d",&newPassword);
	if(fwrite(&newPassword,sizeof(int),1,fp) !=1){
		printf("\t\t�޸�ʧ��");
		getch();
		fclose(fp);
		return;
	}
	printf("\t\t�޸ĳɹ�");
	fclose(fp);
}

void input(){
	int i,m=0;/*m�Ǽ�¼������*/
	char ch[2];  
	FILE *fp;/*�����ļ�ָ��*/
	if((fp=fopen("data.txt","a+"))==NULL)/*��ָ���ļ�*/
	{ 
		printf("can not open\n");
		return;
	}
	while(!feof(fp))
	{
		if(fread(&stu[m] ,LEN,1,fp)==1)
		m++;/*ͳ�Ƶ�ǰ��¼����*/
	}
	fclose(fp);
	if(m==0)
		printf("No record!\n");
	else
	{
		system("cls");
	    show();/*����show��������ʾԭ����Ϣ*/
	}
	if((fp=fopen("data.txt","wb"))==NULL){
		printf("can not open\n");
		return;
	}
	for(i=0;i<m;i++){
		fwrite(&stu[i] ,LEN,1,fp);/*��ָ���Ĵ����ļ�д����Ϣ*/
	}

    printf("������(y/n)��ʼ�����:");
    scanf("%s",ch);
	while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ҫ¼������Ϣ*/
	{
	    printf("ѧ��:");
		scanf("%d",&stu[m].s_num);/*����ѧ��ѧ��*/
	    for(i=0;i<m;i++)
		    if(stu[i].s_num==stu[m].s_num){
			    printf("ѧ���ظ�!");
			    getch();
			    fclose(fp);
			    return;
		    }
		
	        printf("����:");
		 	scanf("%s",stu[m].name);/*����ѧ������*/
	    	printf("�Ա�:");
	     	scanf("%s",&stu[m].sex);/*����ѧ���Ա�*/
	     	printf("����:");
		 	scanf("%d",&stu[m].age);/*����ѧ������*/
		 	printf("��ע:");
		 	scanf("%s",&stu[m].remarks); // ���뱸ע 
	     	if(fwrite(&stu[m],LEN,1,fp)!=1)/*����¼�����Ϣд��ָ���Ĵ����ļ�*/
	     	{
			 	printf("can not save!");
				getch();
		 	}
	     	else
		 	{
			 	printf("%s saved!\n",stu[m].name);
			 	m++;
		 	}
	     	printf("�Ƿ����?(y/n):");/*ѯ���Ƿ����*/
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
   printf("ѧ��              ����           �Ա�     ����         ��ע\t\n");
   for(i=0;i<m;i++){ 
	   printf(FORMAT,DATA);/*����Ϣ��ָ����ʽ��ӡ*/
   }
}

void change(){
	int pword,num,pw;
	int i,j,m=0;
	int t; 
	FILE *fp,*p,*password;
	password = fopen("password.txt","a+");
	fread(&pw,sizeof(int),1,password);
	printf("\t\t������������룺");
	scanf("%d",&pword);
	if(pword == pw){
		printf("\t\t������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
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
				printf("\t\t����:");
	 			scanf("%s",stu[i].name);/*����ѧ������*/
    			printf("\t\t�Ա�:");
     			scanf("%s",&stu[i].sex);/*����ѧ���Ա�*/
     			printf("\t\t����:");
	 			scanf("%d",&stu[i].age);/*����ѧ������*/
	 			printf("\t\t��ע:");
	 			scanf("%s",&stu[i].remarks); // ���ı�ע 
	 			if((fp=fopen("data.txt","wb"))==NULL)
     			{ 
				 	printf("can not open\n");
					return;
				}
				for(j=0;j<m;j++){
					if(fwrite(&stu[j],LEN,1,fp)!=1)/*����¼�����Ϣд��ָ���Ĵ����ļ�*/
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
		 			printf("%s �޸ĳɹ�!\n",stu[i].name);
				 }
				 else{
				 	printf("�޸�ʧ��!\n");
					getch();
				 }
	 			fclose(fp);
				return ;
			} 
		}
	}
	else{
		printf("����������");
		getch();
		return;
	}
}

void search(){
	int case_,num,age;
	char name[15];
	char sex[2];
	printf("\t\t ��ѡ���ѯ��ʽ\n");
	printf("\t\t 1:ѧ�Ų�ѯ\n");
	printf("\t\t 2:������ѯ\n");
	printf("\t\t 3:�Ա��ѯ\n");
	printf("\t\t 4:�����ѯ\n");
	printf("\t\t�������Ӧ�ĺ��룺");
	scanf("%d",&case_);
	switch(case_)
	{
		case 1: 
			printf("\t\t������ѧ��:");
			scanf("%d",&num);
			num_sh(num);
			break;
		case 2:
			printf("\t\t����������:");
			scanf("%s",name);
			name_sh(name);
			break;
		case 3:
			printf("\t\t�������Ա�:");
			scanf("%s",sex);
			sex_sh(sex);
			break;
		case 4:
			printf("\t\t����������:");
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
		printf("û��ѧ����Ϣ��¼!\n");
		return;
	}
  	show();
	printf("��������Ҫɾ��ѧ����ѧ��:");
	scanf("%d",&snum);
	for(i=0;i<m;i++)
	{
		if(snum==stu[i].s_num)
		{    
			printf("�ҵ�ɾ����Ϣ��ȷ����?(y/n)");
			scanf("%s",ch);
			if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ҫ����ɾ��*/
			{ 
				for(j=i;j<m;j++){ 
					stu[j]=stu[j+1];/*����һ����¼�Ƶ�ǰһ����¼��λ��*/
				} 
				m--;/*��¼���ܸ�����1*/
			} 
			if((fp=fopen("data.txt","wb"))==NULL)
			{ 
				printf("can not open\n");
				return;
			}
			for(j=0;j<m;j++){  /*�����ĺ�ļ�¼����д��ָ���Ĵ����ļ���*/
				if(fwrite(&stu[j] ,LEN,1,fp)!=1)
				{ 	
					printf("can not save!\n");
					getch();
				}
			} 
			fclose(fp);
			printf("ɾ���ɹ�!\n");
			return;
		}
	}
	printf("û���ҵ�Ҫɾ������Ϣ��\n");
}
//ֻ�Ǽ�����ѯ�ĺ��� 
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
	    printf("\t\tû�м�¼!\n");
		return;
	}
  	for(i=0;i<m;i++)
    if(num==stu[i].s_num)/*���������ѧ���Ƿ��ڼ�¼��*/
    { 
	   	printf("ѧ��              ����           �Ա�     ����         ��ע\t\n");
	    printf(FORMAT,DATA);/*�����ҳ��Ľ����ָ����ʽ���*/
		break;
    }   
  	if(i==m) 
	  printf("û�����ѧ���������ѧ�Ų���!\n");/*δ�ҵ�Ҫ���ҵ���Ϣ*/
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
	    printf("û�м�¼!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(strcmp(name,stu[i].name)==0)/*��������������Ƿ��ڼ�¼��*/
    { 
	    printf("ѧ��              ����           �Ա�     ����         ��ע\t\n");
	    printf(FORMAT,DATA);/*�����ҳ��Ľ����ָ����ʽ���*/
	    j=1;
    }   
  	if(j!=1) 
	  printf("û�����ѧ���������ѧ�Ų���!\n");/*δ�ҵ�Ҫ���ҵ���Ϣ*/
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
	    printf("û�м�¼!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(strcmp(sex,stu[i].sex)==0)/*����������Ա��Ƿ��ڼ�¼��*/
    { 
	   	printf("ѧ��              ����           �Ա�     ����         ��ע\t\n");
	    printf(FORMAT,DATA);/*�����ҳ��Ľ����ָ����ʽ���*/
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
	    printf("û�м�¼!\n");
		return;
	}
	for(i=0;i<m;i++)
	if(age == stu[i].age)/*��������������Ƿ��ڼ�¼��*/
    { 
	   	printf("ѧ��              ����           �Ա�     ����         ��ע\t\n");
	    printf(FORMAT,DATA);/*�����ҳ��Ľ����ָ����ʽ���*/
	    j=1;
    }   
    if(j!=1)
	  printf("�������������ܲ������߼�!\n");/*δ�ҵ�Ҫ���ҵ���Ϣ*/
}

