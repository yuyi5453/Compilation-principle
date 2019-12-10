#include<bits/stdc++.h>
int TESTmachine(){
	int es=0,i=0,k=0,codecount,stack[1000],stacktop=0;
	int data[1000];
	char Codein[300],code[1000][20];
	int label[100]={0};
	char lno[4];
	FILE* fin;
	printf("输入文件名：");
	scanf("%s",Codein);
	strcat(Codein,".txt");
	char s[300]="out_yuyi_";
	strcat(s,Codein);strcpy(Codein,s);
	if((fin=fopen(Codein,"r"))==NULL){
		printf("打开%s文件出错\n",Codein);
		es=10;
		return 10;
	}
	codecount=0;
	i=fscanf(fin,"%s",&code[codecount]);
	while(!feof(fin)){
		i=strlen(code[codecount])-1;
		if(code[codecount][i]==':'){
			i=i-5;
			strncpy(lno,&code[codecount][5],i);
			lno[i]='\0';
			label[atoi(lno)]=codecount;
//			printf("label[%d]=%d\n",atoi(lno),label[atoi(lno)]);
			code[codecount][0]=':';
			code[codecount][1]='\0';
			strcat(code[codecount],lno);
			k++;
		}
		codecount++;
		i=fscanf(fin,"%s",&code[codecount]);
	}
	fclose(fin);
//	for(i=0;i<codecount;i++) printf("code[%d]  %s\n",i,code[i]);
	for(i=0;i<codecount;i++){
		int l;
		l=strlen(code[i]);
		
		if((l>1)&&(code[i][1]=='A')){
			strncpy(lno,&code[i][5],l-5);
			lno[l-5]='\0';
			itoa(label[atoi(lno)],code[i],10);
		}
	}	
//	for(i=0;i<codecount;i++) printf("code[%d]  %s\n",i,code[i]);
	i=0;
	while(i<codecount){
//		printf("code %d   %s\n",i,code[i]);
		if(strcmp(code[i],"LOAD")==0){
			i++;
			stack[stacktop]=data[atoi(code[i])];
			stacktop++;
		}
		if(strcmp(code[i],"LOADI")==0){
			i++;
			stack[stacktop++]=atoi(code[i]);	
		}
		if(strcmp(code[i],"STO")==0){
			i++;
			data[atoi(code[i])]=stack[stacktop-1];
		}
		if(strcmp(code[i],"POP")==0){
			stacktop--;
		}
		if(strcmp(code[i],"ADD")==0){
			stack[stacktop-2]=stack[stacktop-2]+stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"SUB")==0){
			stack[stacktop-2]=stack[stacktop-2]-stack[stacktop-1];
			stacktop--;	
		}
		if(strcmp(code[i],"MULT")==0){
			stack[stacktop-2]=stack[stacktop-2]*stack[stacktop-1];
			stacktop--;	
		}
		if(strcmp(code[i],"DIV")==0){
			stack[stacktop-2]=stack[stacktop-2]/stack[stacktop-1];
			stacktop--;	
		}
		if(strcmp(code[i],"BR")==0){
			i++;
			i=atoi(code[i]);
		}
		if(strcmp(code[i],"BRF")==0){
			i++;
			if(stack[stacktop-1]==0) i=atoi(code[i]);
			stacktop--;
		}
		if(strcmp(code[i],"EQ")==0){
			stack[stacktop-2]=stack[stacktop-2]==stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"NOTEQ")==0){
			stack[stacktop-2]=stack[stacktop-2]!=stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"GT")==0){
			stack[stacktop-2]=stack[stacktop-2]>stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"LES")==0){
			stack[stacktop-2]=stack[stacktop-2]<stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"GE")==0){
			stack[stacktop-2]=stack[stacktop-2]>=stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"LE")==0){
			stack[stacktop-2]=stack[stacktop-2]<=stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"AND")==0){
			stack[stacktop-2]=stack[stacktop-2]&&stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"OR")==0){
			stack[stacktop-2]=stack[stacktop-2]||stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"NOT")==0){
			stack[stacktop-1]=!stack[stacktop-1];
			stacktop--;
		}
		if(strcmp(code[i],"IN")==0){
			printf("输入:");
			scanf("%d",&stack[stacktop]);
			stacktop++; 
		}
		if(strcmp(code[i],"OUT")==0){
			printf("程序输出##%d\n",stack[stacktop-1]);
			stacktop--;
		}
		if(strcmp(code[i],"STOP")==0){
			break;
		}
		i++;
	}
	return es;
} 

int main()
{
	int es=TESTmachine();
	return 0;
}
