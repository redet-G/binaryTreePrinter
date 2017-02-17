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
node* root=NULL;
point* parent;
void enqueue(node* a);
node* dequeue();
bool isEmpty();
int levelOf(node*,node*);
bool isInTree(node*,node*);
node* find(node* val, node* in=root);
int isleaf(node* ami);



void insert(node* to,node* n){
	if(n){
		if(n->key<to->key) 
			if(to->left!=NULL)
				insert(to->left,n);
			else
				to->left=n;
		else if(n->key>to->key) 
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
void space(int num){for(int i=0;i<num;i++)cout<<" ";}
int max(int a, int b){return a>b?a:b;}

int hight(node* tree){
	if(tree==NULL){
		return 0;
	}else{
		return 1+max(hight(tree->right),hight(tree->left));
	}
}


int leaf(node* l);
void printer(node* nd){
	if(nd==NULL)
		return;
	else{
		enqueue(nd);		
		int lastLevel=-1;
		int lastSpace=isleaf(root->left);
		int currentSpace;
		int currentNodeLevel;
		int tempSpace;
		node* temp;
		while(!isEmpty()){
			temp=dequeue();			
			currentNodeLevel=levelOf(temp,root);
			currentSpace=isleaf(temp->left);
			if(currentNodeLevel!=lastLevel){
				tempSpace=lastSpace-currentSpace;
				cout<<endl;
				
				for(int i=lastSpace-1,j=1;i>currentSpace;i--,j+=2){
					space(i);cout<<"/";
					space(j);
					cout<<"\\"<<endl;
				}
				space(currentSpace);
				cout<<temp->key;
				space(tempSpace);
				lastLevel=currentNodeLevel;
				lastSpace=currentSpace;
			}else{
				
				space(currentSpace);	
				cout<<temp->key;
				space(tempSpace);
			}
			/*debuging 
			//	cout<<"is empty: "<<isEmpty()<<endl;
			//	cout<<"temp: "<<temp;
				cout<<" ll:"<<lastSpace<<" ";	
				cout<<"cl:"<<currentSpace<<" ";
			/*end debuding*/
			
			if(temp->left!=NULL)
				enqueue(temp->left);
			if(temp->right!=NULL)
				enqueue(temp->right);
		}
		cout<<endl;
	}

}

int leaf(node* l){
	if(l==NULL)
		return 3;
	else{
		return leaf(l->left)+leaf(l->right);
	}
}
int levelOf(node* val,node* from){
	if(val->key==from->key){
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
	return (find(val,in)==NULL)?false:true;
}


node* find(node* val, node* in){
	if(in!=NULL){
		if(val->key==in->key)
			return in;
		else if(val->key>in->key)
			return find(val,in->right);
		else if(val->key<in->key)
			return find(val,in->left);
		else
			return NULL;
	}
	return NULL;
}

int isleaf(node* ami){
	if(ami!=NULL){
		node* me = find(ami);
		if(me!=NULL){
			if(me->right==NULL&&me->left==NULL)
				return 3;//it is a leaf
			if(me->right!=NULL&&me->left==NULL)
				return 2+isleaf(me->right);//not a leaf but is not a complete node
			if(me->right==NULL&&me->left!=NULL)
				return 2+isleaf(me->left);//not a leaf but is not a complete node
			else 
				return 1+isleaf(me->right)+isleaf(me->left);// not a leaf + is it complete node
		}
		
	}
	return 1;
}


int main(){
	insert(5);
	insert(3);
	insert(8);
	insert(2);
	insert(4);
	insert(7);
	insert(9);
	//insert(1);
	//insert(6);
	cout<<"preorder:";basicDisplay(root);
	cout<<endl<<"all:"<<count(root)<<endl<<"leaf:"<<leaf(root)<<endl<<"hight:"<<hight(root)<<endl;
	node* temp = new node;
	temp->key=49;
	cout<<"level of "<<temp->key<<":"<<levelOf(temp,root)<<endl;
	cout<<"spaceCout of root:"<<isleaf(root)<<endl;
	cout<<"---------------------------------"<<endl;
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


