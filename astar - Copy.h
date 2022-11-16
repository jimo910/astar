
#include<vector>
//#include<queue>
#include<cmath>
#include<iostream>
using namespace std;
 template<class T>
 class nodes{
 	public:
	nodes() {
		 next = 0;
		 }
 	nodes(T el, nodes *ptr = 0) {
 		info = el; next = ptr;
 	}
 	T info;
		nodes *next;
 };


template <class T>
class queue{
public:
	
 queue() {
 	head = tail = 0;
   }
   

 bool empty() {
 return head == 0;
 }
 
void push( T el) {
 if (tail != 0) { // if list not empty;
 tail->next = new  nodes<T>(el);
 tail = tail->next;
 }
 else head = tail = new nodes<T>(el);
 
}

 void pop() {
 T el = head->info;
 nodes<T> *tmp = head;
 if (head == tail){ // if only one node in the list;
 	head = tail = 0;}
 else {
 head = head->next;
 }
 delete tmp;
}

T front(){
	return head->info;
}


 bool isInList(T) const;

private:
	nodes<T> *head, *tail;
};









/*class myComparator
{
public:
    // operator  it takes in two argument cell.
	int operator() (const node* p1, node* p2)
	{
		return p1->localValue > p2->localValue;
	}
};*/
class astar{
	public:
		void populate(); // to populate vector field so we can know if the vector is a passage or a blockage.
		float distance( struct node *a,  struct node *b); // to know the distnace between two node.
		void aStarAlgorithm(int sX, int sY, int tX, int tY);
		void drawPath();
		void pusher( int sX, int sY); // to know the postition of the node and get it neighbour.
		void pushNode( struct node* &parent , struct node* &pos); //it pushes the node that meet the requirement to priority queue
	queue < node* > shortestinQueue;


	private:
//	vector< vector<node*> > field;
  vector< vector <node* > > field;
	struct node* targeted;
	struct node* starter;
	int success;

};

	struct node{
		 node* parent;
		 float globalValue;
		 float localValue;
		 char nodeStatus; // a passage or a blockage
		 char checkers; // visited or unvisited.
		 int x;
		 int y;
		
	};

void astar::populate(){
char ch;
size_t i, j;

 for(i=0; i<6; i++){
  vector<node* > hello;
	for(j=0;j<6; j++){
		if(i==0 || i==5 || j==0  || j==5){
			char ch= 'x';
			struct node *hj = new node;
		 	hj->globalValue = hj->localValue= INFINITY;
		 	hj->x = i;
		 	hj->y=j;
		 	hj->nodeStatus=ch;
		 	hj->checkers='v';
	    	hello.push_back(hj);

		}else{
	//	cout<< "enter a value :" ;
	//	cin>>'p';
	//	cout<<"\n";
		 struct node *hj = new node;
		 hj->globalValue = hj->localValue= INFINITY;
		 hj->x = i;
		 hj->y=j;
		 hj->nodeStatus= 'p';
		 hj->checkers='u';
		hello.push_back(hj);
	}
	}
	field.push_back(hello);
}

}


void astar::drawPath(){
struct node * checkers =  this->targeted;
	while(checkers!=this->starter){
		int x = checkers->x;
		int y = checkers->y;
		cout<<"x is" << x <<"\t y is" << y <<"\n";
		checkers = checkers->parent;

	}
}

void astar::aStarAlgorithm(int sX, int sY, int tX, int tY){
	 node* start = this->starter= field[sX][sY];
	 node* target= field[tX][tY];
	this->targeted = target;
	field[sX][sY]->localValue=0;
	field[sX][sY]->globalValue= this->distance(start, target) + field[sX][sY]->localValue;
	this->pusher(sX, sY);
	while((this->shortestinQueue.empty())==false){
		struct node*  top = this->shortestinQueue.front();
		cout<< "the x :"<<top->x  <<"\t the y:" << top->y <<"\n";
		this->shortestinQueue.pop();

		 if(top->x==tX && top->y ==tY){
		 	this->success= 1;
		 	break;
		 }else{
		 	this->pusher(top->x, top->y);
		 }
	}

	if(this->success==1){
		cout<<"shortest distance found" <<"\n";
		this->drawPath();
	}else{
		cout<<"no possible solution"<<"\n";
	}


}

float astar::distance(struct node *a, struct node *b ){
	int xto =  abs(a->x - b->x);
	int yto = abs(a->y - b->y);
	float heur = sqrtf((xto *xto) + (yto*yto));
}

void astar::pusher(int sX, int sY){

			this->pushNode(field[sX][sY], field[sX][sY+1]);
			this->pushNode(field[sX][sY], field[sX+1][sY]);
			this->pushNode(field[sX][sY], field[sX-1][sY]);
			this->pushNode(field[sX][sY], field[sX][sY-1]);
	}


void astar::pushNode( struct node* &parent, struct node* &pos){
	char status = pos->nodeStatus;
	char checker = pos->checkers;
	float parentLocalValue = parent->localValue;
	float distance = this->distance(parent, pos);
	float posLocal = pos->localValue;
	float iff = parentLocalValue + distance;
	if(iff<posLocal){
		pos->parent = parent;
		pos->localValue = iff;
		pos->globalValue = this->distance(targeted, pos) + pos->localValue;
	if(status=='p' && checker=='u'){
		this->shortestinQueue.push(pos);
		cout<< "presented" <<"\n";
	}

}
}
