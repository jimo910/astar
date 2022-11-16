#include "path.h"

using namespace std;


class mapping{
	
	public:
	 void sMapping();
	 void right(char p);
	 void left(char p);
	 void forward(char p);
	 void backward(char p);
	vectorBox <vectorBox <node* > > vectorToBox();
	vectorBox<node *> landmark(){
		return landmarks;
	}
	void print_mapping();
	 void checkLocation();
	 void addBorders();
	private:
	vector < vector <node* > > field;
	int totalX, totalY;
	vectorBox<node *> landmarks;
	node* currentPosition;
};




void mapping::sMapping(){
	 vector< node *> start; 	
     node* hello = new node(0,0,'p');
     this->currentPosition= hello;
	 start.push_back(hello);
	 field.push_back(start);
	 this->totalX = 1;
	 this->totalY=1;
	 int count = 0;
	 while(count<5){
	 	char D;
	 	cin>> D;
	 	if(D=='f'){
	 		this->forward('p');
	 	//	cout<<"out";
		 }else if(D=='r'){
		 	this->right('p');
		 }else if(D=='l'){
		 	this->left('p');
		 }else if(D=='b'){
		 	this->backward('p');
		 }else{
		 	cout<<"Map is done"<<D<<"\n";
		 	this->addBorders();
		 	return;
		 	
		 }
	
	 
}

}

void mapping::right(char p){
	 node* parent;	
	parent=  this->currentPosition;
	 cout<<"hmm";
	int y = parent->y;
	int x = parent->x;
	cout<< "x is " << x  <<"y is" <<y <<"\n";
	size_t i, j;
	if(y+1==this->totalY){
		for(int i=0; i<totalX; i++){
    		for(int j=totalY; j<=totalY; j++){
    			 node* hello = new node(i,j,p);
        		field[i].push_back(hello);    
    }
}
		totalY= totalY+1;
}
	
 		currentPosition = field[x][y+1];
	this->checkLocation();	
}

void mapping::left(char p){
	node* parent;
	parent=  this->currentPosition;
	int y = parent->y;
	int x = parent->x;
	cout<< "x is " << x  <<"y is" <<y <<"\n";
	size_t i, j;
	if(y==0){
		for(i=0; i<totalX; i++){
			for(j=0; j<totalY; j++){
				field[i][j]->y =  field[i][j]->y+1;
		}
	}	
	for(i=0; i<totalX; i++){
				 node* hello = new node(i,y,p);
			field[i].insert(field[i].begin(), hello);
		
	}

	currentPosition = field[x][y];
	this->totalY= this->totalY +1;	
}else{

	currentPosition = field[x][y-1];

}
	this->checkLocation();
}

void mapping::forward(char p){
	 node* parent;
	parent=  this->currentPosition;
	int y = parent->y;
	int x = parent->x;
	cout<< " forward x is " << x  <<"y is" <<y <<"\n";
	size_t i, j;
	if(x==0){
		for(int i =0; i<totalX; i++){
			for(j=0; j<totalY; j++){
				field[i][j]->x =  field[i][j]->x+1;
				
		}	
	}
	
	vector< node* > command;
	for(j=0; j<totalY; j++){
	 	 node* hello = new node(x,j,p);	
				 command.push_back(hello);		 
	} 
	
	field.insert( field.begin(), command);
	currentPosition = field[x][y];
	this->totalX = this->totalX+1;
	
}else{
		currentPosition = field[x-1][y];
}
	this->checkLocation();
}

void mapping::backward(char p){
	node* parent;
	parent=  this->currentPosition;
	int y = parent->y;
	int x = parent->x;
	cout<< "x is " << x  <<"y is" <<y <<"\n";
	size_t i, j;
	
	if(x+1 ==this->totalX){
		vector <node*> move;
		for(j=0; j<totalY; j++){
	 		 node* hello = new node(x+1,j,p);	
				 move.push_back(hello);
				
	} 
	field.push_back(move);
		this->totalX = this->totalX+1;
	}	

	currentPosition = field[x+1][y];
	this->checkLocation();
}

void mapping::print_mapping(){
		size_t i , j ;
	for( int i =0; i<this->totalX; i++){
		for(j=0; j<this->totalY; j++){
			cout << field[i][j]->nodeStatus <<"\t";	
		}
		cout<<"\n";
	}
}

vectorBox <vectorBox <node* > > mapping::vectorToBox(){
	vectorBox <vectorBox <node* > > BOX;
	size_t i,j;
	for( i =0; i<this->totalX; i++){
		 vectorBox <node* > box;
		for(j=0; j<this->totalY; j++){
			node* hello = field[i][j];
			box.push_back(hello);
					
		}
		BOX.push_back(box);
	}
	return BOX;
}  

void mapping::checkLocation(){	
	char ch;
	cout<< "enter p or b";
	cin>>ch;
	if(ch=='m'){
		currentPosition->nodeStatus = 'p';	
		landmarks.push_back(currentPosition);	
	}else{
		currentPosition->nodeStatus= ch;
	}
	cout <<"\n";
}

void mapping ::addBorders(){
this->currentPosition = field[0][0];
this->forward('x');
this->currentPosition = field[0][0];
this->left('x');
this->currentPosition = field[this->totalX-1][this->totalY-1];
this->right('x');
this->currentPosition = field[this->totalX-1][this->totalY-1];
this->backward('x');
}
