
#include"mapping.h"


class motionPlanner{
	
	public:
		 vectorBox< char > get_vector(){
		 	 return motions;
		 }
		 
		  // get the  char vector 
		// vectorBox<node *> changed_nodes();
		 void set_vector(vectorBox <node *> s);
		 void planMotion();
		 
	private:
		vectorBox <node *> path;
		vectorBox<node *> changedNode;
		vectorBox <char> motions;
		int checkers;
		int increment;
			
};

void motionPlanner::set_vector(vectorBox <node *> s){	
	checkers= 0;
	this->path = s;
}

void motionPlanner :: planMotion(){	

	node* currentNode = path.index(0);
	node* nextNode = path.index(1);
	if(currentNode->x == nextNode->x){
		this->checkers= 0;
		if(currentNode->y > nextNode->y){
			increment = 0;
		}else{
			increment =1;
		}
	}else{
		this->checkers = 1;
		if(currentNode->y > nextNode->y){
			increment =0;
			}else{
				increment = 1;
			}
		}
	
	
	motions.push_back('f');
	size_t i;
	for(i=1; i<path.size()-2; i++){
		node* currentNode = path.index(i);
		node* nextNode = path.index(i+1);
		if(this->checkers == 0 && increment == 0){
			if(currentNode->x==nextNode->x){
				motions.push_back('f');
			}else{
				checkers=1;
				if(currentNode->x > nextNode->x){
					increment = 0;
					motions.push_back('r');
				}
				else{
					increment =1;
					motions.push_back('l');
				}
			}
		}
	else if(this->checkers == 0 && increment == 1){
			if(currentNode->x==nextNode->x){
				motions.push_back('f');
			}else{
				checkers=1;
				if(currentNode->x > nextNode->x){
					increment = 0;
					motions.push_back('l');
				}else{
					increment =1;
					motions.push_back('r');
				}
			}
		}
	else if(this->checkers == 1 && increment == 0){
			if(currentNode->y==nextNode->y){
				motions.push_back('f');
			}else{
				checkers=0;
				if(currentNode->y > nextNode->y){
					increment = 0;
					motions.push_back('l');
				}else{
					increment =1;
					motions.push_back('r');
				}
			}
		}
	
else{
			if(currentNode->y==nextNode->y){
				motions.push_back('f');
			}else{
				checkers=0;
				if(currentNode->y > nextNode->y){
					increment = 0;
					motions.push_back('r');
				}else{
					increment =1;
					motions.push_back('l');
				}
			}
		}
	
}

motions.push_back('f');	 
}



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
 	count = 0;
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
count =count +1;
}

int length(){
	return count;
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
 count = count-1;
}


 T index(int j){
 	size_t i;
 	nodes<T>* start = head;
 	for(i=0; i<this->length(); i++){
 		if(j==i){
 			return start->info;
 			
		 }
		 start= start->next;
	 }
 }

T front(){
	return head->info;
}


 bool isInList(T) const;

private:
	nodes<T> *head, *tail;
	int count;
};







class astar{
	public:
		void populate(); // to populate vectorBox field so we can know if the vectorBox is a passage or a blockage.
		float distance( int xpar, int ypar, int xpos, int ypos); // to know the distnace between two node.
		vectorBox<node* > astarAlgorithm(int sX, int sY, int tX, int tY);
		vectorBox <node* > drawPath(int sX, int sY, int tX, int Ty);
		void pusher( int sX, int sY); // to know the postition of the node and get it neighbour.
		void pushNode(node* parent ,  node* pos);
		void print_node(vectorBox <node*> hss);
		void print_node (vectorBox <char > hmm);
		void printVectorBox( vectorBox<node*> rasp);
		void asmapping();
		void changeKaraktaUsed();
		void changeParentNode();
		vectorBox<node*>  pathPlanner(int sX, int sY, int tx, int tY);
		queue < node* > shortestinQueue;
		vectorBox<node* > landmark;
		queue <node * >landmarkPointer;
		queue<node* > entered; 
		friend class motionPlannig;
		
 private:

	 vectorBox< vectorBox<node*> > field;
	 vectorBox< vectorBox<node*> > controlField;
 	  vectorBox <vectorBox< vectorBox<node*> > > landmarks;
 	 node* targeted;
	 node* starter;
	 int success;
	 int mappingCount;
	 char karakta;

};

void astar:: printVectorBox( vectorBox<node*> rasp){
	node* start ;//= rasp->head;
	size_t i;
	for(i=0; i<6; i++){
		start = rasp.index(i);
		//cout<< start <<"\t";
		//start = start->next;
	}
	cout<<"\n";
}

void astar::populate(){
	
/*	mappingCount =0;
	char ch;
size_t i, j;
for(i=0; i<30; i++){

	 vectorBox< node*> rasp;
	 cout<<"resume";
 for(j=0; j<30; j++){
	if((i==0 || i==29) || (j==0 || j==29)){
		node* hello = new node(i,j);
		hello->nodeStatus ='x';
		rasp.push_back(hello);	
	}
	else if((i==1 && j==2) || (i==3 && j==4) || (i==4 && j==4) || (i==3 && j==2)|| (i==3 && j==1)){
		node* hello = new node(i,j);
		hello->nodeStatus ='p';
		rasp.push_back(hello);
		landmark.push_back(hello);
	//	landmarkPointer.push(hello);	
		
	}else{	
 	 node* hello = new node(i,j);
 	 rasp.push_back(hello);
 	 cout<<"hello\n";
	  }
 }
 
	int x = field.size();
	//rasp.changedx(x);
	field.push_back(rasp);
	controlField.push_back(rasp);
// cout<<"hellle";
}
//this->controlField = field;*/

mapping gmapping;
 gmapping.sMapping();
// gmapping.print_mapping();
 field = gmapping.vectorToBox();
 this->landmark = gmapping.landmark();
}




void astar::print_node( vectorBox<node *> hmm){

	//vectorBox<node*> hmm = landmarks.index(x).index(x);
	int count =0;
	size_t j=0;
	cout<<hmm.size();
	cout<<"\n";
		for(j=0; j<hmm.size(); j++){
			if(count==10){
				cout<<"\n";
				count = 0;
			}
			cout<< hmm.index(j)->x << "," << hmm.index(j)->y <<" ";
			count = count+1;
		}

}

void astar::print_node( vectorBox<char > hmm){
	int count =0;
	size_t j=0;
	cout<<"\n";
		for(j=0; j<hmm.size(); j++){
			if(count==10){
				cout<<"\n";
				count = 0;
			}
			cout<< hmm.index(j);
			count = count+1;
		}

}

vectorBox <node* > astar::drawPath(int sX, int sY, int tX, int tY){
	 node* targets= field.index(sX).index(sY);//[sX][sY];
	 node* checkers= field.index(tX).index(tY);
	 node * prev;
 	 vectorBox<node* > landmarkers;
	 while(checkers!=targets){
		int x = checkers->x;
		int y = checkers->y;  
		cout<<"x is" <<x;
		cout<<"\n y is"<<y<<"\n";
	landmarkers.push_back(checkers);
	checkers = checkers->parent;

	}
	this->changeParentNode();
	return landmarkers;
}

void astar::changeKaraktaUsed(){
	if(karakta=='u'){
		karakta = 'v';
	}else if(karakta=='v'){
		karakta= 't';
	}else{
		karakta='u';
	}

}

vectorBox<node* > astar::astarAlgorithm(int sX, int sY, int tX, int tY){
	changeKaraktaUsed();
	mappingCount = mappingCount+1;
	vectorBox <node* > help ; 
	node* start = this->starter= field.index(sX).index(sY);//[sX][sY];
	 node* target= field.index(tX).index(tY);
	this->targeted = target;
	field.index(sX).index(sY)->localValue=0;
	field.index(sX).index(sY)->globalValue= this->distance(sX, sY, tX, tY) + field.index(sX).index(sY)->localValue;
	this->pusher(sX, sY);
	while((this->shortestinQueue.empty())==false){
		 node*  top = this->shortestinQueue.front();
		 //cout<<"otilo";
	//	cout <<top->x  <<" "<< top->y <<"\n";
		this->shortestinQueue.pop();
	
		 if(top->x==tX && top->y ==tY){
		 	this->success= 1;
		 	help= this->drawPath(sX,sY, tX, tY);
		 	//cout<<"ogbeniiii";
		 //	cout<<"na me problem";
		 	break;
		 }else{
		
		 	this->pusher(top->x, top->y);
		 }
	}

	if(this->success==1){
		cout<<"shortest distance found" <<"\n";
	//	this->drawPath();
	}else{
		cout<<"no possible solution"<<"\n";
	}

return help;

}

void astar::asmapping(){
	vectorBox<node *> landrover=landmark;
	vectorBox < vectorBox < node* > > landmarkmap;
	size_t i,j;
	
	for(i=0; i<landrover.size(); i++){
		for( j=0; j<landrover.size(); j++){
			if(i==j){
				vectorBox <node *> dhl;
				landmarkmap.push_back(dhl);
				continue;
			}
			node* land1 = landrover.index(i);
			node* land2 = landrover.index(j);
			int x1 = land1->x;
			int y1 = land1->y;
			int x2= land2->x;
			int y2= land2->y;
		//	cout<<"x1 is" << x1 <<"y is" <<y1 <<"x2 is" << x2 <<"y2 is" <<y2;
			 vectorBox<node *> hello = this->astarAlgorithm(x2, y2, x1,y1);
		//	 cout<<"\n\n";
		//	 this->print_node(hello);
			landmarkmap.push_back(hello);
		//	cout<<"\n\n\n";
		
	}
	this->landmarks.push_back(landmarkmap);
//	 vectorBox <node*>  hemmd = landmarks.index(1).index(0);
//	 print_node(hemmd);
 }/*
 
 
vectorBox <node*> hello= mappingAlgorithm(1,2,3,4);
vectorBox <node*> hellos =mappingAlgorithm(3,2,3,4);
vectorBox <node*> hellor=mappingAlgorithm(3,4,4,4);
	landmarks.push_back(hello);
	landmarks.push_back(hellos);
	landmarks.push_back(hellor);*/
//	print_node(landmarks.index(2).index(1));
}

float astar::distance( int xpar,  int ypar, int xpos, int ypos){
	int xto =  abs(xpar - xpos);
	int yto = abs(ypar - ypos);
	float heur = sqrtf((xto *xto) + (yto*yto));
	return heur;
}

void astar::pusher(int sX, int sY){
		
		
			this->pushNode(field.index(sX).index(sY), field.index(sX+1).index(sY));
			this->pushNode(field.index(sX).index(sY),field.index(sX-1).index(sY));
			this->pushNode(field.index(sX).index(sY), field.index(sX).index(sY-1));
			this->pushNode(field.index(sX).index(sY), field.index(sX).index(sY+1) );
}


void astar::pushNode(  node* parent, node* pos){
	this->entered.push(pos);
	char status = pos->nodeStatus;
	char checker = pos->checkers;
int xpar = parent->x; int xpos= pos->x;
int ypar=parent->y; int ypos= pos->y;
	float parentLocalValue = parent->localValue;
	float distance = this->distance(xpar,ypar, xpos, ypos);
	float posLocal = pos->localValue;
	float iff = parentLocalValue + distance;
	int nodeCount = pos->count;	
		if(iff<posLocal){
			pos->parent = parent;
			pos->localValue = iff;
			pos->globalValue = this->distance(xpar, ypar, xpos, ypos) + pos->localValue;
	
	if(status=='p' && nodeCount!=mappingCount){
		this->shortestinQueue.push(pos);
		pos->checkers= karakta;
		pos->count= this->mappingCount;
	//	cout<< "presented" <<"\n";
	}
	//cout<< parent->x <<" " <<parent->y <<" " <<pos->x <<" " <<pos->y;
	//cout<<"\n";
}

}
void astar::changeParentNode(){
	while((this->entered.empty())==false){
		node* fronts = entered.front();
		fronts->globalValue = INFINITY;
		fronts->localValue= INFINITY;
		fronts->parent =0;
		entered.pop();
	}
}

vectorBox <node*> astar::pathPlanner(int sX, int sY, int tx, int iflands){
	//iflands  is 2  sX is a landmark, sY is Landmarks.
	// iflands is 0, sX is a landmarks and sY, and tx are coordinate
	// iflands is 1, tx is landmarks and sX and sY are coordinate.
	int nodeStarterDistance;
	node* nearestStarter;
	int queueNumb;
		node* landmarkNoder = landmark.index(sX);
		size_t i;
		if(iflands!=2){	
		for(i=0; i<landmark.size(); i++){
			node* landmarkNode = landmark.index(i);
			int landmarkX = landmarkNode->x;
			int landmarkY= landmarkNode->y;
			int checkstarter= this->distance(landmarkX, landmarkY, sY, tx);
			if(checkstarter<nodeStarterDistance || i==0){
				nearestStarter = landmarkNode;
				nodeStarterDistance= checkstarter;
				queueNumb =i;
			}		
		}
		
		if(nearestStarter==landmarkNoder){
			int landX = landmarkNoder->x;
			int landY = landmarkNoder->y;
				vectorBox<node *> path ;
			if(iflands ==0){
				path = this->astarAlgorithm(landX, landY, sY, tx);
			}else{
				path = this->astarAlgorithm(sY, tx, landX, landY);
			}
		
			return path;
		}else{
			int landX = nearestStarter->x;
			int landY = nearestStarter->y;
			if(iflands==0){
				vectorBox<node *> pathh = this->astarAlgorithm(landX, landY, sY, tx);
				vectorBox <node *> landPath = landmarks.index(sX).index(queueNumb);
				vectorBox <node *> path =  addvectorBox(landPath, pathh);
				return path;
			
		}else{
				vectorBox<node *> pathh = this->astarAlgorithm( sY, tx,landX, landY);
				vectorBox <node *> landPath = landmarks.index(queueNumb).index(sX);
				vectorBox <node *> path =  addvectorBox(pathh, landPath);
				return path;
				//path
		}
		
		}
	}
	else{
		vectorBox<node* > path = landmarks.index(sX).index(sY);
		cout<<"dhd";
		return path;
	}
}







