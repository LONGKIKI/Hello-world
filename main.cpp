#include<stdio.h>
#include<malloc.h>
#include<iostream>

using namespace std;

typedef struct Polynode
{
 float coef;   //系数
 int exp;   //指数
 struct Polynode *next;
}*Poly,Polynode; //Poly为结点指针类型

void Insert(Poly p,Poly head)
{
 if(p->coef==0) //系数为0时释放结点
  free(p);
 else
 {
  Poly q1,q2;
  q1=head;
  q2=head->next;
  while(q2&&p->exp<q2->exp)
  {   //后移查找插入位置
   q1=q2;
   q2=q2->next;
  }
  if(q2&&p->exp==q2->exp)
  {     //将指数相同的相合并
   q2->coef+=p->coef;
   free(p);
   if(!q2->coef)  //系数为0时释放结点
   {
    q1->next=q2->next;
    free(q2);
   }
  }
  else
  {
   p->next=q2;
   q1->next=p;
  }
 }
}//Insert

Poly CreateList(Poly head,int m)
{   //建立一个头指针为head、项数为m的一元多项式
 int i;
 Poly p;
 Polynode *q;
 p=head=(Poly)malloc(sizeof(struct Polynode));
 head->next=NULL;
 for(i=0;i<m;i++)
 {
  p=(Poly)malloc(sizeof(struct Polynode));//建立新结点以接收数据
  cout<<"请输入第"<<i+1<<"项的系数与指数: ";
  cin>>p->coef>>p->exp;
  Insert(p,head);   //调用Insert函数插入结点
 }
    q=head->next;
 while(q!=NULL)
 {
  cout<<"系数："<<q->coef<<"\t"<<"指数 : "<<q->exp<<endl;
  q=q->next;
 }
 return head;
}//CreatePoly

void DestroyList(Poly p)
{   //销毁多项式p
 Poly q1,q2;
 if(p->next!=NULL)
 {
  q1=p->next;
  q2=q1->next;
  while(q1->next)
  {
   free(q1);
   q1=q2;//指针后移
   q2=q2->next;
  }
 }

}

int OutputList(Poly P)
{  //输出多项式
 Poly q=P->next;
 int flag=1;//项数计数器
 if(!q)
 { //若多项式为空，输出0
  cout<<" 0 "<<endl;
  return(0);
 }
 while (q)
 {
  if(q->coef>0&&flag!=1) //系数大于0且不是第一项
   cout<<"+";
  if(q->coef!=1&&q->coef!=-1)//系数非1或-1的普通情况
  {
   cout<<q->coef;
   if(q->exp==1)
    cout<<"X";
   else if(q->exp)
    cout<<"X^"<<q->exp;
  }
  else
  {
   if(q->coef==1)
   {
    if(!q->exp)
     cout<<"1";
    else if(q->exp==1)
     cout<<"X";
    else if(q->exp)
     cout<<"X^"<<q->exp;
   }
   if(q->coef==-1)
   {
    if(!q->exp) cout<<"-1";
    else if(q->exp==1) cout<<"-X";
    else cout<<"-X^"<<q->exp;
   }
  }
  q=q->next;
  flag++;
 }//while
 cout<<endl;
 return(0);
}//OutputPoly

int compare(Poly a,Poly b)
{
 if(a&&b)
 {
  if(!b||a->exp>b->exp) return 1;
  else if(!a||a->exp<b->exp) return -1;
  else return 0;
 }
 else if(!a&&b) return -1;//a多项式已空，但b多项式非空
 else return 1;//b多项式已空，但a多项式非空
}//compare

Poly AddPoly(Poly pa,Poly pb)
{//求解并建立和多项式a+b，返回其头指针
 Poly qa=pa->next;
 Poly qb=pb->next;
 Poly headc,hc,qc;
 hc=(Poly)malloc(sizeof(struct Polynode));//建立头结点
 hc->next=NULL;
 headc=hc;
 while(qa||qb){
  qc=(Poly)malloc(sizeof(struct Polynode));
  switch(compare(qa,qb))
  {
  case 1:
   {
    qc->coef=qa->coef;
    qc->exp=qa->exp;
    qa=qa->next;
    break;
   }
  case 0:
   {
    qc->coef=qa->coef+qb->coef;
    qc->exp=qa->exp;
    qa=qa->next;
    qb=qb->next;
    break;
   }
  case -1:
   {
    qc->coef=qb->coef;
    qc->exp=qb->exp;
    qb=qb->next;
    break;
   }
  }//switch
  if(qc->coef!=0)
  {
   qc->next=hc->next;
   hc->next=qc;
   hc=qc;
  }
  else free(qc);//当相加系数为0时，释放该结点
 }//while
 return headc;
}//AddPoly

Poly SubtractPoly(Poly pa,Poly pb)
{//求解并建立和多项式a-b，返回其头指针
 Poly qa=pa->next;
 Poly qb=pb->next;
 Poly headc,hc,qc;
 hc=(Poly)malloc(sizeof(struct Polynode));//建立头结点
 hc->next=NULL;
 headc=hc;
 while(qa||qb)
 {
  qc=(Poly)malloc(sizeof(struct Polynode));
  switch(compare(qa,qb))
  {
  case 1:
   {
    qc->coef=qa->coef;
    qc->exp=qa->exp;
    qa=qa->next;
    break;
   }
  case 0:
   {
    qc->coef=qa->coef-qb->coef;
    qc->exp=qa->exp;
    qa=qa->next;
    qb=qb->next;
    break;
   }
  case -1:
   {
    qc->coef=-qb->coef;
    qc->exp=qb->exp;
    qb=qb->next;
    break;
   }
  }//switch
  if(qc->coef!=0)
  {
   qc->next=hc->next;
   hc->next=qc;
   hc=qc;
  }
  else free(qc);//当相减系数为0时，释放该结点
 }//while
 return headc;
}//AddPoly

Poly MultiplyPoly(Poly pa,Poly pb)
{//求解并建立积多项式a*b，返回其头指针
 Poly hf,pf;
 Poly qa=pa->next;
 Poly qb=pb->next;
 hf=(Poly)malloc(sizeof(struct Polynode));//建立头结点
 hf->next=NULL;
 for(qa=pa->next;qa;qa=qa->next)
 {
  for(qb=pb->next;qb;qb=qb->next)
  {
   pf=(Poly)malloc(sizeof(struct Polynode));
   pf->coef=qa->coef*qb->coef;
   pf->exp=qa->exp+qb->exp;
   Insert(pf,hf);//调用Insert函数以合并指数相同的项
  }
 }
 return hf;
}//MultiplyPoly

void DevicePoly(Poly pa,Poly pb)
{//求解并建立商多项式a/b，返回其头指针
 Poly hf,pf,temp1,temp2;
 Poly qa=pa->next;
 Poly qb=pb->next;
 hf=(Poly)malloc(sizeof(struct Polynode));//建立头结点,存储商
 hf->next=NULL;
 pf=(Poly)malloc(sizeof(struct Polynode));//建立头结点，存储余数
 pf->next=NULL;
 temp1=(Poly)malloc(sizeof(struct Polynode));
 temp1->next=NULL;
 temp2=(Poly)malloc(sizeof(struct Polynode));
 temp2->next=NULL;
 temp1=AddPoly(temp1,pa);
 while(qa!=NULL&&qa->exp>=qb->exp)
 {
  temp2->next=(Poly)malloc(sizeof(struct Polynode));
  temp2->next->coef=(qa->coef)/(qb->coef);
  temp2->next->exp=(qa->exp)-(qb->exp);
  Insert(temp2->next,hf);
  pa=SubtractPoly(pa,MultiplyPoly(pb,temp2));
  qa=pa->next;
  temp2->next=NULL;
 }
 pf=SubtractPoly(temp1,MultiplyPoly(hf,pb));
 cout<<"商是：";
 OutputList(hf);
 cout<<"余数是：";
 OutputList(pf);
}//DevicePoly

float ValuePoly(Poly head,float x)
{//输入x值，计算并返回多项式的值
 Poly p;
 int i;
 float sum=0,t;
 for(p=head->next;p;p=p->next)
 {
  t=1;
  for(i=p->exp;i!=0;)
                {
   if(i<0)
                  {
                      t/=x;
                      i++;
                  }//指数小于0，进行除法
         else
                  {
                      t*=x;
                      i--;
                  }//指数大于0，进行乘法
  }
  sum+=p->coef*t;
 }
 return sum;
}//ValuePoly

Poly Derivative(Poly head)
{//求解并建立a的导函数多项式，并返回其头指针
 Poly q=head->next,p1,p2,hd;
 hd=p1=(Poly)malloc(sizeof(struct Polynode));//建立头结点
 hd->next=NULL;
 while(q)
 {
  if(q->exp!=0)
  {               //该项不是常数项时
   p2=(Poly)malloc(sizeof(struct Polynode));
   p2->coef=q->coef*q->exp;
   p2->exp=q->exp-1;
   p2->next=p1->next;//尾插法插入结点
   p1->next=p2;
   p1=p2;
  }
  else if(q->exp==0) //该项为常数项
   break;
  q=q->next;
 }
 return hd;
}//Dervative

int main()
{
 int m,n,flag=0;
 float x;
 Poly pa=0,pb=0,pc,pd,pe,pf;//定义各式的头指针，pa与pb在使用前付初值NULL
 cout<<"请输入a的项数:" ;
 cin>>m;
 pa=CreateList(pa,m);//建立多项式a
 cout<<"请输入b的项数:" ;
 cin>>n;
 pb=CreateList(pb,n);//建立多项式a
 //输出菜单
 cout<<"*********************************************************************"<<endl;
 cout<<" 1.输出多项式a和b         2.建立多项式a+b         3.建立多项式a-b"<<endl;
 cout<<"           4.建立多项式a*b         5.建立多项式a/b"<<endl;
 cout<<" 6.计算多项式a在x处的值   7.求多项式a的导函数     8.退出程序"<<endl;
 cout<<"*********************************************************************"<<endl;
 for(;;flag=0)
 {
  cout<<"执行操作为:" ;
  cin>>flag;
  if(flag==1)
  {
   cout<<"多项式a为：";
   OutputList(pa);
   cout<<"多项式b为：";
   OutputList(pb);
   continue;
  }
  if(flag==2)
  {
   pc=AddPoly(pa,pb);
   cout<<"多项式a+b为：";
   OutputList(pc);
   DestroyList(pc);
   continue;
  }
  if(flag==3)
  {
   pd=SubtractPoly(pa,pb);
   cout<<"多项式a-b为：";
   OutputList(pd);
   DestroyList(pd);
   continue;
  }
  if(flag==4)
  {
   pe=MultiplyPoly(pa,pb);
   cout<<"多项式a*b为：";
   OutputList(pe);
   DestroyList(pe);
   continue;
  }
  if(flag==5)
  {
   DevicePoly(pa,pb);
   continue;
  }
  if(flag==6)
  {
   cout<<"请输入x的值：x=";
   cin>>x;
   cout<<"多项式a的值为:"<<ValuePoly(pa,x)<<endl;
   continue;
  }
  if(flag==7)
  {
   pf=Derivative(pa);
   cout<<"多项式a的导函数为：";
   OutputList(pf);
   DestroyList(pf);
   continue;
  }
  if(flag==8)
   break;
  if(flag<1||flag>8)
   cout<<"输入错误!!!请重新选择!!";
  continue;
 }
 DestroyList(pa);
 DestroyList(pb);
 return 0;
}
