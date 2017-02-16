#include <iostream>
using namespace std;

struct node{
	int key;
	node* left;
	node* right;
};

struct point{
	node* val;
	point* next;
	point* prev;
};

void enqueue(node* a);
node* dequeue();
bool isEmpty();
int levelOf(node*,node*);
bool isInTree(node*,node*);


node* root=NULL;
point* parent;


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
		int lastLevel=0;
		int currentNodeLevel;
		while(!isEmpty()){
			nd=dequeue();			
			int h=max(leaf(nd),hight(nd)*2);
			disp(nd,h);
			currentNodeLevel=levelOf(nd,root);
			if(currentNodeLevel!=lastLevel){
				cout<<endl;
				lastLevel=currentNodeLevel;
			}
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

int levelOf(node* val,node* from){
	if(val==from){
		return 0;
	}else{
		if(isInTree(val,from->left))
			return 1+levelOf(val,from->left);
		else if(isInTree(val,from->right))
			return 1+levelOf(val,from->right);
		else
			return -1;
	}
}

bool isInTree(node* val, node* in){
	if(in!=NULL){
		if(val->key==in->key)
			return true;
		else if(val->key>in->key)
			return isInTree(val,in->left);
		else 
			return isInTree(val,in->right);
	}
	return false;
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
}


///implementing queue


bool isEmpty(){
	return parent==NULL;
}

void enqueue(node* n){
	point* p = new point;
	p->val=n;
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

node* dequeue(){
	if(parent!=NULL){
		if(parent->next==parent){
			point* temp = parent;
			parent=NULL;
			return temp->val;
		}else{
			point* temp = (parent->prev);
			parent->prev=parent->prev->prev;
			parent->prev->next=parent;
			return temp->val;
		}	 
	}
	return NULL;
}

