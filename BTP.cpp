#include <iostream>
using namespace std;

struct node{
	int key;
	node* left;
	node* right;
};

node* root=NULL;
void enqueue(int a);
int dequeue();
bool isEmpty();

void insert(node* to,node* n){
	if(n){
		if(n->key<to->key) 
			if(to->left!=NULL)
				insert(to->left,n);
			else
				to->left=n;
		if(n->key>to->key) 
			if(to->right!=NULL)
				insert(to->right,n);
			else
				to->right=n;
	}	 	 
}

void insert(int value){
	
	node* temp = new node;
	temp->right=NULL;
	temp->left=NULL;
	temp->key=value;
	if(root==NULL)
		root=temp;
	else
		insert(root,temp);
}

void basicDisplay(node* b){
	if(b){
		cout<<b->key<<" ";
		basicDisplay(b->right);
		basicDisplay(b->left);
	}
}


int count(node* p){
	if(p==NULL){
		return 0;
	}else{
		return 1+count(p->left)+count(p->right);
	}
}

int max(int a, int b){return a>b?a:b;}

int hight(node* tree){
	if(tree==NULL){
		return 0;
	}else{
		return 1+max(hight(tree->right),hight(tree->left));
	}
}

void disp(node* p,int h){
	for(int i=0;i<h/2;i++){
		cout<<" ";
	}	 
	cout<<p->key;
}
int leaf(node* l);
void printer(node* nd){
	if(nd==NULL)
		return;
	else{
		enqueue(nd);		
		while(isEmpty()){
			nd=dequeue();			
			int h=max(leaf(nd),hight(nd)*2);
			disp(nd,h);
			cout<<endl;
			enqueue(nd->left);
			enqueue(nd->right);
		}
	}

}

int leaf(node* l){
	if(l==NULL)
		return 1;
	else{
		return leaf(l->left)+leaf(l->right);
	}
}



int main(){
	insert(9);
	insert(49);
	insert(23);
	insert(13);
    insert(03);
	insert(53);
	insert(6);
    insert(7);
	cout<<"preorder:";basicDisplay(root);
	cout<<endl<<"all:"<<count(root)<<endl<<"leaf:"<<leaf(root)<<endl<<"hight:"<<hight(root);
	cout<<endl<<"---------------------------------"<<endl;
	printer(root);
	
	
	//testing the queue
	enqueue(2);enqueue(54);enqueue(6);
	while(!isEmpty()){
		cout<<dequeue()<<" ";
	}
}


///implementing queue
struct point{
	int val;
	point* next;
	point* prev;
};

point* parent=NULL;

bool isEmpty(){

	return (parent==NULL);
}

void enqueue(int a){
	point* p = new point;
	p->val=a;
	p->next=p;
	p->prev=p;
	if(parent==NULL){
		parent=p;
	}else{
		p->next=parent;
		p->prev=parent->prev;
		parent->prev=p;
		parent=p;
	}
}

int dequeue(){
	if(parent!=NULL){
		if(parent->next==parent){
			int temp = parent->val;
			parent=NULL;
			return temp;
		}else{
			int temp = (parent->prev)->val;
			parent->prev=parent->prev->prev;
			parent->prev->next=parent;
			return temp;
		}	 
	}
	return -1;
}

