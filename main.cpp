#include<stdio.h>
#include<malloc.h>
#include<iostream>

using namespace std;

typedef struct Polynode
{
 float coef;   //ϵ��
 int exp;   //ָ��
 struct Polynode *next;
}*Poly,Polynode; //PolyΪ���ָ������

void Insert(Poly p,Poly head)
{
 if(p->coef==0) //ϵ��Ϊ0ʱ�ͷŽ��
  free(p);
 else
 {
  Poly q1,q2;
  q1=head;
  q2=head->next;
  while(q2&&p->exp<q2->exp)
  {   //���Ʋ��Ҳ���λ��
   q1=q2;
   q2=q2->next;
  }
  if(q2&&p->exp==q2->exp)
  {     //��ָ����ͬ����ϲ�
   q2->coef+=p->coef;
   free(p);
   if(!q2->coef)  //ϵ��Ϊ0ʱ�ͷŽ��
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
{   //����һ��ͷָ��Ϊhead������Ϊm��һԪ����ʽ
 int i;
 Poly p;
 Polynode *q;
 p=head=(Poly)malloc(sizeof(struct Polynode));
 head->next=NULL;
 for(i=0;i<m;i++)
 {
  p=(Poly)malloc(sizeof(struct Polynode));//�����½���Խ�������
  cout<<"�������"<<i+1<<"���ϵ����ָ��: ";
  cin>>p->coef>>p->exp;
  Insert(p,head);   //����Insert����������
 }
    q=head->next;
 while(q!=NULL)
 {
  cout<<"ϵ����"<<q->coef<<"\t"<<"ָ�� : "<<q->exp<<endl;
  q=q->next;
 }
 return head;
}//CreatePoly

void DestroyList(Poly p)
{   //���ٶ���ʽp
 Poly q1,q2;
 if(p->next!=NULL)
 {
  q1=p->next;
  q2=q1->next;
  while(q1->next)
  {
   free(q1);
   q1=q2;//ָ�����
   q2=q2->next;
  }
 }

}

int OutputList(Poly P)
{  //�������ʽ
 Poly q=P->next;
 int flag=1;//����������
 if(!q)
 { //������ʽΪ�գ����0
  cout<<" 0 "<<endl;
  return(0);
 }
 while (q)
 {
  if(q->coef>0&&flag!=1) //ϵ������0�Ҳ��ǵ�һ��
   cout<<"+";
  if(q->coef!=1&&q->coef!=-1)//ϵ����1��-1����ͨ���
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
 else if(!a&&b) return -1;//a����ʽ�ѿգ���b����ʽ�ǿ�
 else return 1;//b����ʽ�ѿգ���a����ʽ�ǿ�
}//compare

Poly AddPoly(Poly pa,Poly pb)
{//��Ⲣ�����Ͷ���ʽa+b��������ͷָ��
 Poly qa=pa->next;
 Poly qb=pb->next;
 Poly headc,hc,qc;
 hc=(Poly)malloc(sizeof(struct Polynode));//����ͷ���
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
  else free(qc);//�����ϵ��Ϊ0ʱ���ͷŸý��
 }//while
 return headc;
}//AddPoly

Poly SubtractPoly(Poly pa,Poly pb)
{//��Ⲣ�����Ͷ���ʽa-b��������ͷָ��
 Poly qa=pa->next;
 Poly qb=pb->next;
 Poly headc,hc,qc;
 hc=(Poly)malloc(sizeof(struct Polynode));//����ͷ���
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
  else free(qc);//�����ϵ��Ϊ0ʱ���ͷŸý��
 }//while
 return headc;
}//AddPoly

Poly MultiplyPoly(Poly pa,Poly pb)
{//��Ⲣ����������ʽa*b��������ͷָ��
 Poly hf,pf;
 Poly qa=pa->next;
 Poly qb=pb->next;
 hf=(Poly)malloc(sizeof(struct Polynode));//����ͷ���
 hf->next=NULL;
 for(qa=pa->next;qa;qa=qa->next)
 {
  for(qb=pb->next;qb;qb=qb->next)
  {
   pf=(Poly)malloc(sizeof(struct Polynode));
   pf->coef=qa->coef*qb->coef;
   pf->exp=qa->exp+qb->exp;
   Insert(pf,hf);//����Insert�����Ժϲ�ָ����ͬ����
  }
 }
 return hf;
}//MultiplyPoly

void DevicePoly(Poly pa,Poly pb)
{//��Ⲣ�����̶���ʽa/b��������ͷָ��
 Poly hf,pf,temp1,temp2;
 Poly qa=pa->next;
 Poly qb=pb->next;
 hf=(Poly)malloc(sizeof(struct Polynode));//����ͷ���,�洢��
 hf->next=NULL;
 pf=(Poly)malloc(sizeof(struct Polynode));//����ͷ��㣬�洢����
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
 cout<<"���ǣ�";
 OutputList(hf);
 cout<<"�����ǣ�";
 OutputList(pf);
}//DevicePoly

float ValuePoly(Poly head,float x)
{//����xֵ�����㲢���ض���ʽ��ֵ
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
                  }//ָ��С��0�����г���
         else
                  {
                      t*=x;
                      i--;
                  }//ָ������0�����г˷�
  }
  sum+=p->coef*t;
 }
 return sum;
}//ValuePoly

Poly Derivative(Poly head)
{//��Ⲣ����a�ĵ���������ʽ����������ͷָ��
 Poly q=head->next,p1,p2,hd;
 hd=p1=(Poly)malloc(sizeof(struct Polynode));//����ͷ���
 hd->next=NULL;
 while(q)
 {
  if(q->exp!=0)
  {               //����ǳ�����ʱ
   p2=(Poly)malloc(sizeof(struct Polynode));
   p2->coef=q->coef*q->exp;
   p2->exp=q->exp-1;
   p2->next=p1->next;//β�巨������
   p1->next=p2;
   p1=p2;
  }
  else if(q->exp==0) //����Ϊ������
   break;
  q=q->next;
 }
 return hd;
}//Dervative

int main()
{
 int m,n,flag=0;
 float x;
 Poly pa=0,pb=0,pc,pd,pe,pf;//�����ʽ��ͷָ�룬pa��pb��ʹ��ǰ����ֵNULL
 cout<<"������a������:" ;
 cin>>m;
 pa=CreateList(pa,m);//��������ʽa
 cout<<"������b������:" ;
 cin>>n;
 pb=CreateList(pb,n);//��������ʽa
 //����˵�
 cout<<"*********************************************************************"<<endl;
 cout<<" 1.�������ʽa��b         2.��������ʽa+b         3.��������ʽa-b"<<endl;
 cout<<"           4.��������ʽa*b         5.��������ʽa/b"<<endl;
 cout<<" 6.�������ʽa��x����ֵ   7.�����ʽa�ĵ�����     8.�˳�����"<<endl;
 cout<<"*********************************************************************"<<endl;
 for(;;flag=0)
 {
  cout<<"ִ�в���Ϊ:" ;
  cin>>flag;
  if(flag==1)
  {
   cout<<"����ʽaΪ��";
   OutputList(pa);
   cout<<"����ʽbΪ��";
   OutputList(pb);
   continue;
  }
  if(flag==2)
  {
   pc=AddPoly(pa,pb);
   cout<<"����ʽa+bΪ��";
   OutputList(pc);
   DestroyList(pc);
   continue;
  }
  if(flag==3)
  {
   pd=SubtractPoly(pa,pb);
   cout<<"����ʽa-bΪ��";
   OutputList(pd);
   DestroyList(pd);
   continue;
  }
  if(flag==4)
  {
   pe=MultiplyPoly(pa,pb);
   cout<<"����ʽa*bΪ��";
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
   cout<<"������x��ֵ��x=";
   cin>>x;
   cout<<"����ʽa��ֵΪ:"<<ValuePoly(pa,x)<<endl;
   continue;
  }
  if(flag==7)
  {
   pf=Derivative(pa);
   cout<<"����ʽa�ĵ�����Ϊ��";
   OutputList(pf);
   DestroyList(pf);
   continue;
  }
  if(flag==8)
   break;
  if(flag<1||flag>8)
   cout<<"�������!!!������ѡ��!!";
  continue;
 }
 DestroyList(pa);
 DestroyList(pb);
 return 0;
}
