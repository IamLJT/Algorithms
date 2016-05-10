#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
typedef struct node
{
	int data;
	struct node *next;
}node;
node *create(int n)
{
	node *p=NULL,*head;
	head=(node *)malloc(sizeof(node));
	p=head;
	node *s;
	int i=1;
	if(0!=n)
	{
		while(i<=n)
		{
			s=(node *)malloc(sizeof(node));
			s->data=rand()%100+1;	//初始化
			//s->data=i;
			p->next=s;
			p=s;					//p为指向尾部的临时节点
			i++;
		}
		s->next=head->next;
	}
	free(head);
	return s->next;
}
int main()
{
	int n,k;
	//int n=4,m=3;
	cout<<"总人数：";
	cin>>n;
	cout<<"这"<<n<<"个数为：";
	node *p=create(n);
	node *temp=p,*temp0;
	while(temp!=p->next)
	{
		cout<<p->data<<"-";
		p=p->next;
	}
	cout<<p->data;
	p=p->next;
	//free(temp);
	cout<<"\n开始上限值：";
	cin>>k;
	cout<<"\n依次离开的人为：";
	//m%=n;
	while(p!=p->next)
	{
		k%=n;
		if(k==0)k=n;
		for(int i=1;i<k-1;i++)
		{
			p=p->next;
		}
		if(k!=1)
		{
			k=p->next->data;
			temp=p->next;
			p->next=temp->next;
			free(temp);
		}
		else
		{
			k=p->data;//因为k=1不在上述循环中
			p->next=temp0->next;
			free(temp0);
		}
		cout<<k<<"->";
		
		
		temp0=p;
		p=p->next;
		n--;
		/*for(int i=1;i<m-1;i++)
			p=p->next;
		cout<<p->next->data<<"->";
		p->next=p->next->next;
		p=p->next;*/
	}
	free(temp0);
	cout<<p->data<<endl;
	system("pause");
	return 0;
}