#include<bits/stdc++.h>
#include"DSJ_词法分析.h"
using namespace std;
char token[20],token1[40];
char yufa_in[300];//词法分析文件名
char yufa_out[300];
FILE *fin,*fout;
set<string>se;
struct node{
	string st;
	vector<node*>son;
	int cnt; 
	node* addSon(string s){
		node* Son=new node();
		Son->st=s;
		son.push_back(Son);
		return Son;
	}
} *Root; 
int program();
int declaration_list(node* fa);
int declaration_stat(node* fa);
int statement_list(node* fa);
int statement(node* fa);
int if_stat(node* fa);
int while_stat(node* fa);
int for_stat(node* fa);
int read_stat(node* fa);
int write_stat(node* fa);
int compound_stat(node* fa);
int expression_stat(node* fa);
int expression(node* fa);
int bool_expr(node* fa);
int additive_expr(node* fa);
int term(node* fa);
int factor(node* fa);
int fun_declaration(node* fa);//
int fun_body(node* fa);//
int main_declaration(node* fa);//
int call_stat(node* fa);//
void out(node* p){
	p->addSon(token1);
}
void shift(int x){
	for(int i=0;i<x;i++) fprintf(fout," ");
}
void line(int x){
	for(int i=0;i<x;i++) fprintf(fout,"-");
} 
//fseek(fin,fileadd,0);
void tree_out(node* p,int ppre){
	int fp,pre=0;
	int x=p->cnt;//下面叶子节点个数 
	shift(x*8+ppre*16);
	fprintf(fout,"%s\n",p->st.c_str());
	int len=p->st.length();
	shift(x*8+len/2);
	fprintf(fout,"|\n");
	int nc=p->son.size();
	if(nc==0) return;
	shift(p->son[0]->cnt*8);
	fprintf(fout,"|\n");
	fp=ftell(fout);
	
	for(int i=0;i<nc;i++){
		if(i>0) pre+=p->son[i-1]->cnt;
		tree_out(p->son[i],pre);
		fseek(fout,fp,0);
		if(i+1<nc) line((p->son[i]->cnt+p->son[i+1]->cnt)*8);
		fprintf(fout,"|");
		fp=ftell(fout);
	}
	return ;
}

int tree_cnt(node *p){
	int nc=p->son.size();
	if(nc==0) return 1;
	int sum=0;
	for(int i=0;i<nc;i++){
		sum+=tree_cnt(p->son[i]);
	}
	p->cnt=sum;
	return sum;
}
int TESTparse(){
	int es=0;
//	scanf("%s",fileName);
//	fileName="out.txt";
	strcpy(yufa_in,cifa_out);
	if((fin=fopen(yufa_in,"r"))==NULL){
		printf("打开%s文件错误\n",yufa_in);
		es=10;
	}
	strcpy(yufa_out,"out_yufa_");
	strcat(yufa_out,cifa_in);
	if((fout=fopen(yufa_out,"w"))==NULL){
		printf("打开yufa_out文件错误\n");
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
		case 8:cout<<"重复定义！"<<endl;break; 
		case 9:cout<<"缺少main函数"<<endl;break;
		case 11:cout<<"非法声明,缺少fun/main"<<endl;break;
		case 12:cout<<"使用未声明变量！"<<endl;break; 
		default: cout<<es<<endl; 
	}
	return es;
}

int program(){
	Root=new node();
	Root->st="<programe>";
//	shift(p);
//	fprintf(fout,"<program>\n");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"function")&&strcmp(token,"main")){
		return es=11;
	}
	while(strcmp(token,"function")==0){
		
		es=fun_declaration(Root);
		if(es>0) return es;
	}
	if(strcmp(token,"main")){
		return es=9;
	}
	es=main_declaration(Root);
	if(es>0) return es;
	
	return es;
}
int fun_declaration(node* fa){
	node* p=fa->addSon("<fun_declaration>");
	out(p);
//	cur->addSon(token1);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=5;
	out(p);
//	cur->addSon(token1);
	
	es=fun_body(p);
	if(es>0) return es;
	
	return es;
}
int main_declaration(node* fa){
	node* p=fa->addSon("<main_declaration>");
	out(p);
//	cur->addSon(token1);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
//	cur->addSon(token1);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	out(p);
//	cur->addSon(token1);
	es=fun_body(p);
	if(es>0) return es;
	fscanf(fin,"%s %s\n",token,token1);
	
	return es;
	
}
int fun_body(node* fa){
	node* p=fa->addSon("fun_body");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"{")) return es=1;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	es=declaration_list(p);
	if(es>0) return es;
	es=statement_list(p);
	if(es>0) return es;
	if(strcmp(token,"}")) return es=2;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	se.clear();//清空一个识别完成的函数体内的变量 
	return es;
}
int declaration_list(node* fa){
	node* p=fa->addSon("declaration_list");
	int es=0;
	while(strcmp(token,"int")==0){
		es=declaration_stat(p);
		if(es>0) return es;
	}
	return es;
}
int declaration_stat(node* fa){
	node* p=fa->addSon("<declaration_stat>");
	int es=0;
	out(p);
	
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	
	if(strcmp(token,"ID")) return es=3;
	if(se.count(token1)) return es=8;
	se.insert(token1);
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es; 
}
int statement_list(node* fa){
	node* p=fa->addSon("<state_ment>");
	int es=0;
	while(strcmp(token,"}")){
		es=statement(p);
		if(es>0) return es;
	}
	return es;
}
int statement(node* fa){
	node* p=fa->addSon("<statement>");
	int es=0;
	if(es==0&&strcmp(token,"if")==0) es=if_stat(p);
	if(es==0&&strcmp(token,"while")==0) es=while_stat(p);
	if(es==0&&strcmp(token,"for")==0) es=for_stat(p);
	if(es==0&&strcmp(token,"read")==0) es=read_stat(p);
	if(es==0&&strcmp(token,"write")==0) es=write_stat(p);
	if(es==0&&strcmp(token,"{")==0) es=compound_stat(p);
	if(es==0&&strcmp(token,"call")==0) es=call_stat(p);
	if(es==0&&(strcmp(token,"ID")==0||strcmp(token,"NUM")==0||strcmp(token,"(")==0)) es=expression_stat(p);
	
	return es;
}
int if_stat(node* fa){
	node* p=fa->addSon("<if_stat>");
	int es=0;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	if(es>0) return es;

	if(strcmp(token,"else")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=statement(p);
		return es;
	}
	return es;
}
int while_stat(node* fa){
	node* p=fa->addSon("<while_stat>");
	int es=0;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	out(p);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	out(p);
	if(strcmp(token,")")) return es=6;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	return es;
}
int for_stat(node* fa){
	node* p=fa->addSon("<for_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	out(p);
	if(strcmp(token,"(")) return es=5;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1); 
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement(p);
	return es;
}
int write_stat(node* fa){
	node* p=fa->addSon("<write_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=expression(p);
	if(es>0) return es;
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es;
}
int read_stat(node* fa){
	node* p=fa->addSon("<read_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	if(strcmp(token,";")) return es=4;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	return es;
}
int compound_stat(node* fa){
	node* p=fa->addSon("<compound_stat>");
	out(p);
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
//	printf("%s %s\n",token,token1);
	es=statement_list(p);
	return es;
}
int expression_stat(node* fa){
	node* p=fa->addSon("<expression_stat>");
	out(p);
	int es=0;
	if(strcmp(token,";")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		return es;
	}
	es=expression(p);
	if(es>0) return es;
	if(es==0&&strcmp(token,";")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		return es;
	}
	else{
		return es=4;
	}
}
int call_stat(node* fa){
	node* p=fa->addSon("<call_stat>");
	int es=0;
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"ID")) return es=3;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,"(")) return es=5;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	if(strcmp(token,")")) return es=6;
	out(p);
	fscanf(fin,"%s %s\n",token,token1);
	
	return es; 
}
int expression(node* fa){
	node* p=fa->addSon("<expression>");
	int es=0,fileadd;
	char token2[20],token3[40];
	if(strcmp(token,"ID")==0){
		if(!se.count(token1)) return es=12;
		fileadd=ftell(fin);
		fscanf(fin,"%s %s\n",token2,token3);
//		printf("%s %s\n",token2,token3);...
		if(strcmp(token2,"=")==0){
			out(p);
//			shift(p+1);
//			fprintf(fout,"%s\n",token2);
			p->addSon(token2);
			
			fscanf(fin,"%s %s\n",token,token1);
			es=bool_expr(p);
			if(es>0) return es;
		}
		else{
			fseek(fin,fileadd,0);
			es=bool_expr(p);
			if(es>0) return es;
		}
	}
	else es=bool_expr(p+1);
	return es;
}
int bool_expr(node* fa){
	node* p=fa->addSon("<bool_expr>");
	int es=0;
	es=additive_expr(p);
	if(es>0) return es;
	if(strcmp(token,">")==0||strcmp(token,">=")==0||strcmp(token,"<")==0||strcmp(token,"<=")==0||strcmp(token,"==")==0||strcmp(token,"!=")==0){
			out(p);
			fscanf(fin,"%s %s\n",token,token1);
//			printf("%s %s\n",token,token1);
			es=additive_expr(p);
			if(es>0) return es;
	}
	return es;
}
int additive_expr(node* fa){
	node* p=fa->addSon("<additive_expr>");
	int es=0;
	es=term(p);
	if(es>0) return es;
	while(strcmp(token,"+")==0||strcmp(token,"-")==0){
		out(p);
		fscanf(fin,"%s %s",token,token1);
//		printf("%s %s\n",token,token1);
		es=term(p);
		if(es>0) return es;
	}
	return es;
}
int term(node*fa){
	node* p=fa->addSon("<term>");
	int es=0;
	es=factor(p);
	if(es>0) return es;
	while(strcmp(token,"*")==0||strcmp(token,"/")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=factor(p);
		if(es>0) return es;
	}
	return es;
}
int factor(node* fa){
	node* p=fa->addSon("<factor>");
	int es=0;

	if(strcmp(token,"(")==0){
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
		es=expression(p);
		if(es>0) return es;
		if(strcmp(token,")")) return es=6;
		out(p);
		fscanf(fin,"%s %s\n",token,token1);
//		printf("%s %s\n",token,token1);
	}
	else{
		
		if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0){
			out(p);
			fscanf(fin,"%s %s\n",token,token1);
//			printf("%s %s\n",token,token1);
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
	
	if(es==0&&flag){
		tree_cnt(Root);
		tree_out(Root,0);
	}
	fclose(fin);
	fclose(fout);
	return 0;
 }
