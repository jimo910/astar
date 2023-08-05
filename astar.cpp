#include "astar.h"
#include <iostream>
using namespace std;

void astar::populate(){
mapping gmapping; // Creating an instance of  the mapping class
 gmapping.sMapping(); // generate a new map or load the existing map .
// gmapping.print_mapping();
 field = gmapping.vectorToBox();  //return  the generated map to the algorithm to process.
 this->landmark = gmapping.landmark(); // returns the landmark to the algorithm.
}




void astar::print_node( vectorBox<node *> hmm){

	//vectorBox<node*> hmm = landmarks.index(x).index(x);
	int count =0;
	int j=0;
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
	int  j=0;
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



// it return the shortest distance between the point and  the targeted point, or return a point if the targeted point cannot be accessed.
vectorBox<node* > astar::astarAlgorithm(int sX, int sY, int tX, int tY){
	mappingCount = mappingCount+1;
	vectorBox <node* > help ; 
	 this->starter= field.index(sX).index(sY);//[sX][sY]; it denotes the robot current Position.
	 node* target= field.index(tX).index(tY);   // It denotes the robot targeted Position(Destination).
	this->targeted = target;
	field.index(sX).index(sY)->localValue=0;
	field.index(sX).index(sY)->globalValue= this->distance(sX, sY, tX, tY) + field.index(sX).index(sY)->localValue;
	this->pusher(sX, sY);
	while((this->shortestinQueue.empty())==false){
		 node*  top = this->shortestinQueue.front();
		 //cout<<"otilo";
	//	cout <<top->x  <<" "<< top->y <<"\n";
		this->shortestinQueue.pop();
	
		 if(top->x==tX && top->y ==tY){  //  check if the tagreted node has been reached.
		 	this->success= 1;
		 	help= this->drawPath(sX,sY, tX, tY); // it returns the path from the starting-point to the destination-point.
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

// is used to generate  a path between a landmarks and all other landmarks.
void astar::asmapping(){  
	vectorBox<node *> landrover=landmark;
	vectorBox < vectorBox < node* > > landmarkmap;
	int i,j;
	
	for(i=0; i<landrover.size(); i++){ // 
		for( j=0; j<landrover.size(); j++){
			if(i==j){ // Condition for neglecting generating a path between the same node/
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
			 vectorBox<node *> hello = this->astarAlgorithm(x2, y2, x1,y1); // used to generate  path between point(x2,y2)   and point (x1, y1). both point are landmarks.
		//	 cout<<"\n\n";
		//	 this->print_node(hello);
			landmarkmap.push_back(hello);
		//	cout<<"\n\n\n";
		
	}
	this->landmarks.push_back(landmarkmap);

 }
}


// for generating the heuristic distance between two point/.
float astar::distance( int xpar,  int ypar, int xpos, int ypos){
	int xto =  abs(xpar - xpos);
	int yto = abs(ypar - ypos);
	float heur = sqrtf((xto *xto) + (yto*yto));
	return heur;
}

// it is used to populate all the neigbouring point of a point being considered by the algorithm to a function which check if the point meet some condition
void astar::pusher(int sX, int sY){
			this->pushNode(field.index(sX).index(sY), field.index(sX+1).index(sY)); // right neighbouring point
			this->pushNode(field.index(sX).index(sY),field.index(sX-1).index(sY)); // left neigbouring point
			this->pushNode(field.index(sX).index(sY), field.index(sX).index(sY-1)); // // bottom neighbouring point
			this->pushNode(field.index(sX).index(sY), field.index(sX).index(sY+1) ); // top neigbouring point
}


// it compares the current node and the neigbouring node's location. to check which is closer to the point. and also check if the neigbouring hasnot been checked b4 or being a blockage.
void astar::pushNode(  node* parent, node* pos){  
	this->entered.push(pos);
	char status = pos->nodeStatus;
int xpar = parent->x; int xpos= pos->x;
int ypar=parent->y; int ypos= pos->y;
	float parentLocalValue = parent->localValue; // getting the localvalue of the parent Node
	float distance = this->distance(xpar,ypar, xpos, ypos); // getting the distance between the parent node and current node. 
	float posLocal = pos->localValue; // getting the localValue of the Position.
	float iff = parentLocalValue + distance; 
	int nodeCount = pos->count;	
		if(iff<posLocal){ //  a condition to check if  the parent is closer to the destination or the current node position is.
			pos->parent = parent;
			pos->localValue = iff;
			pos->globalValue = this->distance(xpar, ypar, xpos, ypos) + pos->localValue;
	
	if(status=='p' && nodeCount!=mappingCount){ // condition to check if the node is a passage and the node has not been checked before.
		this->shortestinQueue.push(pos); // keep the node in view
		pos->count= this->mappingCount;  // mark this node position as checked so it wont be rechecked.
	}
	
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


//to generate path from a landmarks  to another point on the field and vice  versa
vectorBox <node*> astar::pathPlanner(int sX, int sY, int tX, int iflands){ //
	//iflands  is 2  sX is a landmark, sY is Landmarks.
	// iflands is 0, sX is a landmarks and    sY and tx are coordinate of targeted/Destination  node
	// iflands is 1, tx is landmarks and sX and sY are coordinate of  the starting node.
	int nodeStarterDistance=0;
	node* nearestLandmark; //  a node to compute the nearest landmarks to the starting node or targeted node.
	int queueNumb;
	int checkstarter;
	node* landmarkNoder;
		
		int i;
		if(iflands!=2){	 // if path is not between a landmark and a landmark.
		if(iflands==0){
		landmarkNoder = landmark.index(sX); } // to get the node on Landmark(sX)
		else{
			 landmarkNoder= landmark.index(tX);  // to get the node on Landmarks(tX)
		}
	
		for(i=0; i<landmark.size(); i++){ // To loop through all the landmarks and checked for the one closer to the point.
			node* landmarkNode = landmark.index(i);
			int landmarkX = landmarkNode->x;
			int landmarkY= landmarkNode->y;
			if(iflands ==0){
		    checkstarter= this->distance(landmarkX, landmarkY, sY, tX);} // getting the distance between the landmarks and the starting/targeted point.
			else{ checkstarter= this->distance(landmarkX, landmarkY, sX, sY); } 
			if(checkstarter<nodeStarterDistance || i==0){
				nearestLandmark = landmarkNode;
				nodeStarterDistance= checkstarter;
				queueNumb =i;
			}		
		}
		
		if(nearestLandmark==landmarkNoder){ // the nearest landmark to the point  is the targeted/starting landmarks.
			int landX = landmarkNoder->x;
			int landY = landmarkNoder->y;
				vectorBox<node *> path ;

			if(iflands ==0){
				// the nearest landmark to the point  is the targeted/staring lamdmarks,get  the shortest path between them.
				path = this->astarAlgorithm(landX, landY, sY, tX);  
			}else{
				path = this->astarAlgorithm(sX, sY, landX, landY);
			}
		
			return path;
		}else{ // the nearest landmark to the point  is not the targeted/starting landmarks.

			int landX = nearestLandmark->x;
			int landY = nearestLandmark->y;
			if(iflands==0){
				vectorBox<node *> pathh = this->astarAlgorithm(landX, landY, sY, tX); //get the path between the nearest landmarks and the targeted point. 
				vectorBox <node *> landPath = landmarks.index(sX).index(queueNumb);// get the path between the starting landmarks and the landmark nearest to the targeted point
				vectorBox <node *> addition;
				vectorBox <node *> path =  addition.addvectorBox(landPath, pathh);
				return path;
			
		}else{
				vectorBox<node *> pathh = this->astarAlgorithm( sX, sY, landX, landY); //get the path between the nearest landmarks and the  starting  point. 
				vectorBox <node *> landPath = landmarks.index(queueNumb).index(tX);// get the path between the targeted landmarks and the landmark nearest to the starting point
				vectorBox <node *> addition;
				vectorBox <node *> path =  addition.addvectorBox(pathh, landPath);
				return path;
				
		}  
		
		}
	}
	else{
		vectorBox<node* > path = landmarks.index(sX).index(sY); // getting path between two landmarks.
		cout<<"dhd";
		return path;
	}
}


	motionPlanner::motionPlanner(vectorBox<node*> path, astar &get){
					objAstar= get; // initiating  Astar object objAstar from parameter get.
					this->set_vector(path); // this is to assign the attribute path to parameter path.
					this->planMotion(); //

					if(isplanned==true){ // to check if the destination has been reached.
						cout<<"ok\n";
						return;
					}else{
							cout<<"olslsk\n";
						while (this-> isplanned==false && this->isastar !=false){ 
							control_failed_plan(); // generate a new path from the failedNode to the targeted node. 
							this->set_vector(this->newPath);
							this->planMotion(); // the motion is checked again.
						}
						return;
					}
			
		 }
void motionPlanner::control_failed_plan(){
	cout <<"\n control failed plan \n";
	int sX = this->Failednode->x; // it get the x-coordinate of the node where the blockage happens.
	int sY = this->Failednode->y; // it get the y-coordinate of the node where the blockage happens.
	int tX = this->target->x; //it get the x-coordinate of the targeted node 
	int tY = this->target->y; //it get the y-coordinate of the targeted node 

	cout<<sX << sY << tX << tY <<endl ;
	newPath = objAstar.astarAlgorithm(sX, sY, tX, tY); //generate a  path between the failedNode and the targeted node.
	if(objAstar.success==1){ 
			isastar = true; 
	}else{
		isastar = false;
	}
}



void motionPlanner::set_vector(vectorBox <node *> s){	
	checkers= 0; // 
	this->path = s; // assignn the parameter to the  class attribute path.  
	int length = s.size(); //get the length of s.
	target =  s.index(length-1); // get the last node of the path i.e the target node.
}

int motionPlanner :: planMotion(){	

	node* currentNode = path.index(0);
	node* nextNode = path.index(1); // int nextX = nextNode->x; int nextY= nextNode->y;
	char p;
	cin >> p;

	if(p==nextNode->nodeStatus){ // to check if the current position is a passage.
	if(currentNode->x == nextNode->x){ // checking the x-coordinate of (current and next node) to update checkers.
		this->checkers= 0;
		if(currentNode->y > nextNode->y){ // checking the y-coordinate of (current and next node) to  check if it increasing or not, then update increment.
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
	}else{ // this else statement take care of situation where the planned path (passage) is now a blockage.
		cout<<"\n failed\n";
    	objAstar.field.index(nextNode->x).index(nextNode->y)->nodeStatus= p;
		this->Failednode = currentNode;
		this->isplanned= false;
		return 0 ;
	}
	
	motions.push_back('f');
	int i;
	for(i=1; i<path.size()-2; i++){ // to lo0p through the path which motion is to be planned.
		
		node* currentNode = path.index(i);
		node* nextNode = path.index(i+1);
		char s;
		cin>>s;  // to get the current state of Node{either it  still a passage or it blocked}.

	if(s==nextNode->nodeStatus){ // run the statement if it is a passage, else the path planned has failed.
		if(this->checkers == 0 && increment == 0){  
			if(currentNode->x==nextNode->x){ // move forward when the x-value are the same.
				motions.push_back('f');
			}else{
				checkers=1; // change the valuue of checekers to denote y-coordinate has  equal, and x-coordinate changing.
				if(currentNode->x > nextNode->x){ // move right if the current x-coordinate is greater than the next node x-coordinate
					increment = 0;
					motions.push_back('r'); // move right if the current x-coordinate is greater than the next node x-coordinate
				}
				else{
					increment =1;
					motions.push_back('l');
				}
			}
		}
	else if(this->checkers == 0 && increment == 1){
			if(currentNode->x==nextNode->x){ // move forward when the x-value are the same.
				motions.push_back('f');
			}else{
				checkers=1;
				if(currentNode->x > nextNode->x){  // move left if the current x-coordinate is greater than the next node x-coordinate && increment is 1.
					increment = 0;
					motions.push_back('l');
				}else{ // move right if the current x-coordinate is less  than the next node x-coordinate && increment is 1.
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
				if(currentNode->y > nextNode->y){ // move left if the current y-coordinate is greater than the next node y-coordinate && increment is 0.
					increment = 0;
					motions.push_back('l');
				}else{  // move right if the current y-coordinate is less than the next node y-coordinate && increment is 0.
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
				if(currentNode->y > nextNode->y){  // move right if the current y-coordinate is greater than the next node y-coordinate && increment is 1.
					increment = 0;
					motions.push_back('r');
				}else{  // move left if the current y-coordinate is less than the next node y-coordinate && increment is 1.

					increment =1;
					motions.push_back('l');
				}
			}
		}

	}else{ // the path planned has failed(due to blockage of  a node in the path)	
		cout<<"\n failed\n";
		objAstar.field.index(nextNode->x).index(nextNode->y)->nodeStatus= s; // change the nodestatus of the node blocked on the map.
		this->Failednode = currentNode;
		this->isplanned= false; //update your isplanned to ffalse.
		return 0 ;
	}
	
}
	this->isplanned= true;
	motions.push_back('f');	 
	return 1;
}

