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
void save();  // ��Ϣ���溯��
void del();  // ��Ϣɾ������ 
void change(int pw);  // ��Ϣ�޸ĺ���
void search();   // ��Ϣ��ѯ����
void exit_();   // �˳�����ĺ���
//��ѯ���ܵ��������� 
void num_sh(int num);  
void name_sh(char name[]);
void sex_sh(char sex[]);
void age_sh(int age);
int main()
{
	int n;
	int password;
	printf("��������4λ��������:");
	scanf("%d",&password);
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
	       case 4: save();break;
	       case 5: change(password);break;
	       case 6: menu();break;
	       case 7: show();break;
	       default:break;
	    }
	    getch();  // ������һ��ֵ 
	    menu();/*ִ���깦���ٴ���ʾ�˵�����*/
	    scanf("%d",&n);
	}
	return 0; 
}
void menu(){
	system("cls");
  	printf("\n\n\n\n\n");
  	printf("\t\t|--------------<�༶��������ϵͳ>---------|\n");
  	printf("\t\t|             0. �˳�����                 |\n");
  	printf("\t\t|             1. ¼����Ϣ                 |\n");
  	printf("\t\t|             2. ��ѯ                     |\n");
  	printf("\t\t|             3. ɾ��                     |\n");
  	printf("\t\t|             4. ����                     |\n");
  	printf("\t\t|             5. �޸�                     |\n");
  	printf("\t\t|             6. �˵�                     |\n");
  	printf("\t\t|             7. ���                     |\n");
  	printf("\t\t|-----------------------------------------|\n\n");
  	printf("\t\t��������ѡ��Ĺ��ܴ���(0-7):");
}
void exit_(){
	printf("�˳�ϵͳ�ɹ�");
	system("TASKKILL C��Ŀ.exe");
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
void change(int pw){
	int pword,num;
	int i,j,m=0;
	int t; 
	FILE *fp,*p;
	printf("������������룺");
	scanf("%d",&pword);
	if(pword == pw){
		printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
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
				printf("����:");
	 			scanf("%s",stu[i].name);/*����ѧ������*/
    			printf("�Ա�:");
     			scanf("%s",&stu[i].sex);/*����ѧ���Ա�*/
     			printf("����:");
	 			scanf("%d",&stu[i].age);/*����ѧ������*/
	 			printf("��ע:");
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
void save(){
	printf("����ɹ���");
}
void search(){
	int case_,num,age;
	char name[15];
	char sex[2];
	printf("\t��ѡ���ѯ��ʽ\n");
	printf("\t 1:ѧ�Ų�ѯ\n");
	printf("\t 2:������ѯ\n");
	printf("\t 3:�Ա��ѯ\n");
	printf("\t 4:�����ѯ\n");
	printf("�������Ӧ�ĺ��룺");
	scanf("%d",&case_);
	switch(case_)
	{
		case 1: 
			printf("������ѧ��:");
			scanf("%d",&num);
			num_sh(num);
			break;
		case 2:
			printf("����������:");
			scanf("%s",name);
			name_sh(name);
			break;
		case 3:
			printf("�������Ա�:");
			scanf("%s",sex);
			sex_sh(sex);
			break;
		case 4:
			printf("����������:");
			scanf("%d",&age);
			age_sh(age);
			break;
	}
}
void del(){
	int i,j,num;
	int m=0,k=0,t=0;
	FILE *fp;
	printf("��������Ҫɾ��ѧ����ѧ�ţ�");
	scanf("%d",&num);
	fp = fopen("data.txt","a+");
	if(fp == NULL){
		printf("can not open!");
	}
	else{
		while(!feof(fp)){
	        if(fread(&stu[m],LEN,1,fp)==1)
	        	m++;
    	}
	}
	if(m==0){
		printf("û��ѧ����Ϣ");
		return;
	}
	for(i=0;i<m;i++){
		if(stu[i].s_num == num){
			for(j=i;j<m;j++){
				k=1;
				stu[j] = stu[j+1];
			}
			if((fp=fopen("data.txt","wb"))==NULL){ 
				printf("can not open\n");
				return;
			}
			for(j=0;j<m;j++){
				if(fwrite(&stu[j],LEN,1,fp)!=1)/*����¼�����Ϣд��ָ���Ĵ����ļ�*/
	     		{
	     			printf("can not open"); 
	     			return;
		 		}
	     		else{
	     			t=1;
		 		}
	  	    }
	  	    if(t==1){
	  	    	printf("ɾ���ɹ���");
			}
			else{
				printf("ɾ��ʧ��!\n");
				getch();
			}
	 		fclose(fp);
			return ;
		}
	}
	if(k==0){
		printf("�������ѧ�Ų����ڣ�");
		return;
	}
}
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
	    printf("û�м�¼!\n");
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
