#include<bits/stdc++.h>
#include"DSJ_词法分析.h"
using namespace std;
const int maxvartablep=500;
char token[20],token1[40];
char yuyi_in[300];//词法分析文件名
char yuyi_out[300];
FILE *fin,*fout;
int program();
int declaration_list();
int declaration_stat();
int statement_list();
int statement();
int if_stat();
int while_stat();
int for_stat();
int read_stat();
int write_stat();
int compound_stat();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int term();
int factor();
int fun_declaration();//
int fun_body();//
int main_declaration();//
int call_stat();//
int name_def(char* name);
struct{
	char name[8];
	int address;
} vartable[maxvartablep];
int vartablep=0,labelp=0,datap=0;

int name_def(char* name){

	int i,es=0;
	if(vartablep>=maxvartablep) return 21;
	for(i=vartablep-1;i==0;i--){
		if(strcmp(vartable[i].name,name)==0){
			es=22;
			break;
		}
	}
	if(es>0) return es;
	strcpy(vartable[vartablep].name,name);
	vartable[vartablep].address=datap;
	datap++;
	vartablep++;
	return es;
}
int lookup(char* name,int* paddress){
    int i,es=0;
    for(i=0;i<vartablep;i++){
        if(strcmp(vartable[i].name,name)==0){
            *paddress=vartable[i].address;
            return es;
        }
    }
    return es=23;
}
int TESTparse(){
	int es=0;
	strcpy(yuyi_in,cifa_out);
	if((fin=fopen(yuyi_in,"r"))==NULL){
		printf("打开%s文件错误\n",yuyi_in);
		es=10;
	}
	strcpy(yuyi_out,"out_yuyi_");
	strcat(yuyi_out,cifa_in);
	if((fout=fopen(yuyi_out,"w"))==NULL){
		printf("打开yuyi_out文件错误\n");
		es=10;
	}
	if(es==0) es=program();
	printf("=====语法分析结果：======\n");
	switch(es){
		case 0:printf("语法分析成功\n");break;
		case 10:cout<<"打开输入文件失败"<<endl;break;
		case 1:cout<<"缺少{!"<<endl;break;
		case 2:cout<<"缺少}!"<<endl;break;
		case 3:cout<<"缺少标识符!"<<endl;break;
		case 4:cout<<"缺少分号!"<<endl;break;
		case 5:cout<<"缺少(!" <<endl;break;
		case 6:cout<<"缺少)!"<<endl;break;
		case 7:cout<<"缺少操作数!"<<endl;break;
		case 9:cout<<"缺少main函数"<<endl;break;
		case 11:cout<<"非法声明,缺少fun/main"<<endl;break;
		case 21:cout<<"符号表溢出"<<endl;break;
		case 22:cout<<"重复定义"<<endl;break;
		case 23:cout<<"变量未声明"<<endl;break;
		default: cout<<es<<endl;
	}
	return es;
}

int program(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"function")&&strcmp(token,"main")){
		return es=11;
	}
	while(strcmp(token,"function")==0){

		es=fun_declaration();
		if(es>0) return es;
	}
	if(strcmp(token,"main")){
		return es=9;
	}
	es=main_declaration();
	fprintf(fout,"  STOP\n");
	if(es>0) return es;
	for(int i=0;i<vartablep;i++){
		printf("	%s	%d\n",vartable[i].name,vartable[i].address);
	} 
	return es;
}
int fun_declaration(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	es=name_def(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=5;
	es=fun_body();
	if(es>0) return es;

	return es;
}
int main_declaration(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	es=fun_body();
	if(es>0) return es;
	fscanf(fin,"%s %s\n",token,token1);

	return es;

}
int fun_body(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"{")) return es=1;
	fscanf(fin,"%s %s\n",token,token1);
	es=declaration_list();
	if(es>0) return es;
	es=statement_list();
	if(es>0) return es;
	if(strcmp(token,"}")) return es=2;
	fscanf(fin,"%s %s\n",token,token1);
	return es;
}
int declaration_list(){
	int es=0;
	while(strcmp(token,"int")==0){
		es=declaration_stat();
		if(es>0) return es;
	}
	return es;
}
int declaration_stat(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	es=name_def(token1);
	if(es>0) return es;
	fscanf(fin,"%s %s\n",token,token1);

	if(strcmp(token,";")) return es=4;
	fscanf(fin,"%s %s\n",token,token1);
	return es;
}
int statement_list(){
	int es=0;
	while(strcmp(token,"}")){
		es=statement();
		if(es>0) return es;
	}
	return es;
}
int statement(){
	int es=0;
	if(es==0&&strcmp(token,"if")==0) es=if_stat();
	if(es==0&&strcmp(token,"while")==0) es=while_stat();
	if(es==0&&strcmp(token,"for")==0) es=for_stat();
	if(es==0&&strcmp(token,"read")==0) es=read_stat();
	if(es==0&&strcmp(token,"write")==0) es=write_stat();
	if(es==0&&strcmp(token,"{")==0) es=compound_stat();
	if(es==0&&strcmp(token,"call")==0) es=call_stat();
	if(es==0&&(strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0)) es=expression_stat();

	return es;
}
int if_stat(){
	int es=0,label1,label2;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	label1=labelp++;
	fprintf(fout,"		BRF LABEL%d\n",label1);
	fscanf(fin,"%s %s\n",token,token1);
	es=statement();
	if(es>0) return es;
	label2=labelp++;
	fprintf(fout,"		BR LABEL%d\n",label2);
	fprintf(fout,"LABEL%d:\n",label1);
	if(strcmp(token,"else")==0){
		fscanf(fin,"%s %s\n",token,token1);
		es=statement();
		if(es>0) return es;
	}
	fprintf(fout,"LABEL%d:\n",label2);
	return es;
}
int while_stat(){
	int es=0,label1,label2;
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);
	fscanf(fin,"%s %s\n",token,token1);

	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	label2=labelp++;
	fprintf(fout,"		BRF LABEL%d\n",label2);
	fscanf(fin,"%s %s\n",token,token1);
	es=statement();
	if(es>0)    return es;
	fprintf(fout,"		BR LABEL%d\n",label1);
	fprintf(fout,"LABEL%d:\n",label2);
	return es;
}
int for_stat(){
	int es=0,label1,label2,label3,label4;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	fprintf(fout,"		POP\n");
	if(strcmp(token,";")) return es=4;
	label1=labelp++;
	fprintf(fout,"LABEL%d:\n",label1);
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	label2=labelp++;
	fprintf(fout,"		BRF LABEL%d\n",label2);
	label3=labelp++;
	fprintf(fout,"		BR LABEL%d\n",label3);
	if(strcmp(token,";")) return es=4;
	label4=labelp++;
	fprintf(fout,"LABEL%d:\n",label4);
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	fprintf(fout,"		POP\n");
	fprintf(fout,"		BR LABEL%d\n",label1);
	if(strcmp(token,")")) return es=6;
	fprintf(fout,"LABEL%d:\n",label3);
	fscanf(fin,"%s %s\n",token,token1);
	es=statement();
	if(es>0)    return es;
	fprintf(fout,"		BR LABEL%d\n",label4);
	fprintf(fout,"LABEL%d:\n",label2);
	return es;
}
int write_stat(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	es=expression();
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	fprintf(fout,"  OUT\n");
	fscanf(fin,"%s %s\n",token,token1);
	return es;
}
int read_stat(){
	int address;
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	es=lookup(token1,&address);
	if(es>0) return es;
	fprintf(fout,"  IN  \n");
	fprintf(fout,"  STO %d\n",address);
	fprintf(fout,"  POP\n");

	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,";")) return es=4;
	fscanf(fin,"%s %s\n",token,token1);
	return es;
}
int compound_stat(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	es=statement_list();
	if(strcmp(token,"}")) return es=2;
	fscanf(fin,"%s %s\n",token,token1);
	return es;
}
int expression_stat(){
	int es=0;
	if(strcmp(token,";")==0){
		fscanf(fin,"%s %s\n",token,token1);
		return es;
	}
	es=expression();
	if(es>0) return es;
	fprintf(fout,"  POP\n");
	if(es==0&&strcmp(token,";")==0){
		fscanf(fin,"%s %s\n",token,token1);
		return es;
	}
	else{
		return es=4;
	}
}
int call_stat(){
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	
	fscanf(fin,"%s %s\n",token,token1);

	return es;
}
int expression(){
	int es=0,fileadd;
	char token2[20],token3[40];
	if(strcmp(token,"ID")==0){
		fileadd=ftell(fin);
		fscanf(fin,"%s %s\n",token2,token3);
		if(strcmp(token2,"=")==0){
            int address;
            es=lookup(token1,&address);
            if(es>0) return es;
			fscanf(fin,"%s %s\n",token,token1);
			es=bool_expr();
			if(es>0) return es;
			fprintf(fout,"  STO   %d\n",address);
		}
		else{
			fseek(fin,fileadd,0);
			es=bool_expr();
			if(es>0) return es;
		}
	}
	else es=bool_expr();
	return es;
}
int bool_expr(){
	int es=0;
	es=additive_expr();
	if(es>0) return es;
	if(strcmp(token,">")==0||strcmp(token,">=")==0||strcmp(token,"<")==0||strcmp(token,"<=")==0||strcmp(token,"==")==0||strcmp(token,"!=")==0){
			char token2[20];
			strcpy(token2,token);
			fscanf(fin,"%s %s\n",token,token1);
			es=additive_expr();
			if(es>0) return es;
			if(strcmp(token2,">")==0)fprintf(fout," GT\n");
			if(strcmp(token2,">=")==0)fprintf(fout," GE\n");
			if(strcmp(token2,"<")==0)fprintf(fout," LES\n");
			if(strcmp(token2,"<=")==0)fprintf(fout," LE\n");
			if(strcmp(token2,"==")==0)fprintf(fout," EQ\n");
			if(strcmp(token2,"!=")==0)fprintf(fout," NOTEQ\n");
	}
	return es;
}
int additive_expr(){
	int es=0;
	es=term();
	if(es>0) return es;
	while(strcmp(token,"+")==0||strcmp(token,"-")==0){
		char token2[20];
		strcpy(token2,token); 
		fscanf(fin,"%s %s",token,token1);
//		printf("%s %s\n",token,token1);
		es=term();
		if(es>0) return es;
		if(strcmp(token2,"+")==0) fprintf(fout,"	ADD\n");
		if(strcmp(token2,"0")==0) fprintf(fout,"	SUB\n");
	}
	return es;
}
int term(){
	int es=0;
	es=factor();
	if(es>0) return es;
	while(strcmp(token,"*")==0||strcmp(token,"/")==0){
		char token2[20];
		strcpy(token2,token);
		fscanf(fin,"%s %s\n",token,token1);
		es=factor();
		if(es>0) return es;
		if(strcmp(token2,"*")==0) fprintf(fout,"	MULT\n");
		if(strcmp(token2,"/")==0) fprintf(fout,"	DIV\n");
	}
	return es;
}
int factor(){
	int es=0;

	if(strcmp(token,"(")==0){
		fscanf(fin,"%s %s\n",token,token1);
		es=expression();
		if(es>0) return es;
		if(strcmp(token,")")) return es=6;
		fscanf(fin,"%s %s\n",token,token1);
	}
	else{

		if(strcmp(token,"ID")==0){
			int address;
			es=lookup(token1,&address);
			if(es>0) return es;
			fprintf(fout,"		LOAD %d\n",address);
			fscanf(fin,"%s %s\n",token,token1);
			return es;
		}
		if(strcmp(token,"NUM")==0){
			fprintf(fout,"		LOADI %s\n",token1);
			fscanf(fin,"%s %s\n",&token,&token1);
			return es;
		}
		else{
			es=7;
			return es;
		}
	}
	return es;
}

int main()
{
	if(!init()){cout<<"词法分析错误"<<endl;return 0;}
	int flag=scan();
	if(flag) cout<<"词法分析成功"<<endl;
	else cout<<"词法分析失败"<<endl;

	int es=0;
	if(flag)  es=TESTparse();
	if(es==0&&flag){
		printf("语法分析成功\n");
	}
	else if(flag&&es) printf("语法分析失败\n");
	fclose(fin);
	fclose(fout);
	return 0;
 }

