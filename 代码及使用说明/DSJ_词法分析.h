#include<bits/stdc++.h>
#define keyNum 11
using namespace std;
char keyWord[keyNum][10]={"call","do","else","for","function","if","int","main","read","while","write"};
char singleWord[]="+-*();,{}";//纯单分界符
char doubleWord[]=">=<!";
FILE *Fin,*Fout;//文件指针 
char cifa_in[300];//输入文件名
char cifa_out[300];
int init();//初始化
int scan();//输入
int isSaved(char *s){//是否为保留字 (二分) 
	int l=0,r=keyNum;
	while(l<r){
		int mid=(l+r)/2;
		if(strcasecmp(s,keyWord[mid])==0) return 1;
		if(strcasecmp(s,keyWord[mid])>0) l=mid+1;
		else r=mid;
	}
	return 0;
}

int init(){
	cout<<"输入文件名称:"<<endl;
	cin>>cifa_in; 
	strcat(cifa_in,".txt");
	if((Fin=fopen(cifa_in,"r"))==NULL){
		cout<<"打开输入文件出错"<<endl;
		return 0;
	}
	strcpy(cifa_out,"out_cifa_");
	strcat(cifa_out,cifa_in);
	if((Fout=fopen(cifa_out,"w"))==NULL){
		cout<<"创建词法输出文件出错"<<endl;
		return 0;
	}
	return 1;
}

int scan(){
	char ch,buff[40];
	int es=1,j;
	int cnt=1;//用于记录当前行号 
	ch=getc(Fin);
	while(ch!=EOF){
		while(ch==' '||ch=='\t'||ch=='\n'){
			if(ch=='\n') cnt++;
			ch=getc(Fin);
		} 
		if(ch==EOF) break;
		if(isalpha(ch)){//如果是标识符 
			buff[0]=ch;j=1;
			ch=getc(Fin);
			while(isalnum(ch)){
				buff[j++]=ch;
				ch=getc(Fin);
			}
			buff[j]='\0';
			if(isSaved(buff)) fprintf(Fout,"%s\t%s\n",buff,buff);
			else  fprintf(Fout,"%s\t%s\n","ID",buff);
		}
		else if(isdigit(ch)){//如果是数字 
			buff[0]=ch;ch=getc(Fin);j=1;
			while(isdigit(ch)){
				buff[j++]=ch;
				ch=getc(Fin);
			}
			buff[j]='\0';
			fprintf(Fout,"%s\t%s\n","NUM",buff);
		}
		else if(strchr(singleWord,ch)>0){//单分界符 
			buff[0]=ch;buff[1]='\0';
			ch=getc(Fin);
			fprintf(Fout,"%s\t%s\n",buff,buff);
		}
		
		else if(strchr(doubleWord,ch)>0){//双 
			 buff[0]=ch; ch=getc(Fin);
			 if(ch=='='){
			 	buff[1]=ch;buff[2]='\0';
			 	ch=getc(Fin);
			 }
			 else buff[1]='\0';
			 
			 fprintf(Fout,"%s\t%s\n",buff,buff);
		}
		else if(ch=='/'){
			ch=getc(Fin);
			if(ch=='*'){
				char ch1;
				ch1=getc(Fin);
				do{
					ch=ch1;ch1=getc(Fin);
				}while((ch!='*'||ch1!='/')&&ch1!=EOF);
				
				ch=getc(Fin);
			}
			else{	
				buff[0]='/';buff[1]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
			}
		}
		else if(ch=='&'){
			buff[0]=ch;
			ch=getc(Fin);
			if(ch=='&'){
				buff[1]=ch;buff[2]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
				ch=getc(Fin);
			}
			else{
				buff[1]='\0';
				ch=getc(Fin);
				es=0;
				fprintf(Fout,"%s\t%d\t%s\n","ERROR at line",cnt,buff);
			} 
		}
		else if(ch=='|'){
			buff[0]=ch;
			ch=getc(Fin);
			if(ch=='|'){
				buff[1]=ch;buff[2]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
				ch=getc(Fin);
			}
			else{
				buff[1]='\0';
				ch=getc(Fin);
				es=0;
				fprintf(Fout,"%s\t%d\t%s\n","ERROR at line ",cnt,buff);
			} 
		}
		else{
			buff[0]=ch;buff[1]='\0';
			ch=getc(Fin);
			es=0;
			fprintf(Fout,"%s\t%d\t%s\n","ERROR at line ",cnt,buff);
		}
	}
	fclose(Fin);
	fclose(Fout);
	return es;
}
