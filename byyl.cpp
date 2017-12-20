#include<bits/stdc++.h>
using namespace std;

int l,cnt,x;
char ch;
int line=0;
char tmp[100];
int i=0;
int flag = 0;
char s[50];
int  E();
int  E1();
int  T();
int  T1();
int  F();

int isDigit(char ch)
{
    if(ch>='0'&&ch<='9')
        return 1;
    else return 0;
}

int isLitter(char ch)
{
    if(ch>='a'&&ch<='z')
        return 1;
    if(ch>='A'&&ch<='Z')
        return 1;
    else return 0;
}
int isZf(char ch)
{
    if(ch == '=' || ch == '>' || ch == '!' || ch == '<' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return 1;
    else return 0;
}

int isKeyword(char tmp[])
{
    if(!strcmp(tmp,"main")|| !strcmp(tmp,"if") || !strcmp(tmp,"else") || !strcmp(tmp,"for") || !strcmp(tmp,"while") || !strcmp(tmp,"int"))
        return 1;
    else return 0;
}

int isBoundary(char ch)
{
  if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==','||ch==';')
    return 1;
  else
    return 0;
}
void get()
{

    while(~scanf("%c",&ch))
    {


      if(ch==' '||ch=='\t')//为空格或是tab
            continue;
         //回车
        else if(ch=='\n')
            line++;
        //是否是界符
        else if(isBoundary(ch))
            {
                s[flag++] += ch;
                printf("(boundary,%c)\n",ch);
            }
        else if(isDigit(ch))//如果是数字
        {
            while(isDigit(ch))
            {
                s[flag++] += ch;
                tmp[i++]=ch;
                scanf("%c",&ch);

            }
            tmp[i]='\0';//加上结束符
            i=0;
            printf("(integer,%s)\n",tmp);
            ungetc(ch,stdin);//将字符退回到输入流中
        }
        else if(isLitter(ch)||ch=='_')
        {
            while(isLitter(ch)||isDigit(ch)||ch=='_')
            {
                s[flag++] += ch;
                tmp[i++]=ch;
                scanf("%c",&ch);

            }
            tmp[i]='\0';
            i=0;
            if(isKeyword(tmp))  //关键字
                printf("(keyword,%s)\n",tmp);
            else            //自定义标识符
                printf("(identifier,%s)\n",tmp);
            ungetc(ch,stdin);
        }
        else if(isZf(ch))//如果是操作符
        {
            while(isZf(ch))
            {
                s[flag++] += ch;
                tmp[i++]=ch;
                scanf("%c",&ch);

            }
            tmp[i]='\0';
            i=0;
            printf("(operator,%s)\n",tmp);
            ungetc(ch,stdin);
        }
        else if(ch == '#')
            {
              s[flag++] += ch;
              break;
            }
        else
          printf("'%c'符号不合法！请重新输入!\n",ch);

}
}
int  E(){
  if(s[x+1] == '=')
    {
      printf("%d E-->i = E\n",cnt++);
      x++;
      return s[x++] == '='&& E();
    }
  else
    {
      printf("%d E-->TE1\n",cnt++ );
      return  T()&& E1();
    }
}
int  E1(){
  if(s[x] == '+'){
      printf("%d E1-->+TE1\n",cnt++);
      x++;
      return  T()&& E1();
  }
  else
      printf("%d E1-->&\n",cnt++);
  return 1;
}
int  T1(){
    if(s[x] == '*'){
        printf("%d T1-->*FT1\n",cnt++);
        x++;
        return  F()&& T1();
    }
    else
        printf("%d T1-->&\n",cnt++);
    return 1;
}
int  T(){
    printf("%d T-->FT1\n",cnt++);
    return  F()&& T1();
}
int  F(){
    if(s[x] == '('){
        printf("%d F-->(E)\n",cnt++);
        x++;
        return  E()&&s[x++] == ')';
       }
    else if(isLitter(s[x])){
        printf("%d F-->i\n",cnt++);
        x++;
        return 1;
    }
    return 0;
}
void BlankSpace (char *s) //过滤掉空格
{
   int i=0;
   char *p=s;
   while(*p)
   {
      if(*p!=' '&& *p != ';')          /*删除空格*/
      {
         s[i]=*p;
         i++;
      }
      p++;
   }
   s[i]='\0';            /*加上结束符*/
}
int main()
{
  printf("请输入文法表达式:\n");//a = b+((b*c)+e)#
  get();
  BlankSpace(s);//过滤空格
  cout<<"*****************************************************"<<endl;
  cout<<"\n                 语法分析结果：\n"<<endl;
  cout<<"*****************************************************"<<endl;
  l = strlen(s) - 1;
  printf("%s\n",s);
  if(E()&&x==l&&s[x]=='#')
    printf("符合语法\n");
  else
    printf("不合规的语法\n");
}
/*
事例
a = b+((b*c)+e)#
a = b+((b*c)+e;#
$$$$$$
main()
{
int a, b;
a=1;
b = a + 1;
}
*/
