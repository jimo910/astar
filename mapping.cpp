#include  "mapping.h"
#include <fstream>
#include <iostream>
using namespace std;


void mapping::isFile(){ 
		fstream MyFile("filename.txt");// the filename to check if it exist.
		if(MyFile){
				this->file_dey =1;
				cout <<"FILE EXIST";

		}else{
			cout <<"file doesnot exist";
			this->file_dey=0;
		}
}

void mapping::sMapping(){
	isFile(); // to check if  map already exist
	int  i,j;
	cout<<file_dey <<"\n";
if(this->file_dey==1) { // checking if a map was made.
				cout<<"FILE EXIST";
				ifstream MyFile("filename.txt"); //create a map of the environment.
				ifstream MyLandmarks("landmark.txt"); // storing the landmarks
 				int x; // x-coordinate
 				int y; // y-coordinate
				string passage; // checking the node-status.
				string Eaex="x";
				string pis  ="p"; 
				MyFile>>x >>y>>passage;
				this->totalX = x;
				this->totalY =y;
				vector< node*> box, empty;
				int count=0;
					 while(MyFile>>x >> y >> passage){ //reading from file(map) till it ends.
							int  i = 0;
							node*  hj ;

							if(passage==Eaex){ 
									hj= new node(x,y ,'x');		 //instantiating a node that is at the boundary
							}else if(passage==pis){
									hj= new node(x,y, 'p');	  //instantiating a node that is a passage
							}else{
								hj= new node(x,y ,'b');	   //instantiating a node that is a blockage.
		}
				box.push_back(hj);  // insert the node into a box. 
				count=count+1; // increment the number of rows moved.
				if(y==this->totalY-1){ // checking if the map has reached the boundary on x-axis.
					field.push_back(box); // insert the vector<node *> box into  vector<vector<node*> field.
			 		box =empty;
			   	    count=0;
					cout<<"\n";
			}
	 }

			this->print_mapping();
			int xland;
			int yland;
			int  no;
			char pass = 'p';
//MyLandmarks>>xland >> yland >> no;
			while(MyLandmarks>>xland>> yland >> no){
					node * hj =  new node (xland,yland,pass);
					this->landmarks.push_back(hj);
			}


		cout<<"DONE";
		return;
}else{ // file doesnot exist.
	//cout<<"file doesn't exist";
				this->file_dey =1;
				vector< node *> start; 	
				node* hello = new node(0,0,'p'); // robot current position.(starting position)
				this->currentPosition= hello;
				start.push_back(hello);
				field.push_back(start);
				this->totalX = 1;
				this->totalY=1;
				while(true){
							char D;
							cin>> D;  // prompt keyboard interrupt
							if(D=='f'){ // if 'f' is pressed , move the robot forward
								this->forward('p');
							//	cout<<"out";
							}else if(D=='r'){  // if 'r' is pressed , move the robot to the right
								this->right('p');
							}else if(D=='l'){ // if 'l' is pressed , move the robot to the left.
								this->left('p');
							}else if(D=='b'){ // if 'b' is pressed , move the robot backward
								this->backward('p');
							}else{ // another character presssed will ends the map
								cout<<"Map is done"<<D<<"\n";
								this->addBorders(); // demarcate the borders so robot do not move beyond.
								return;
								
					}
				
				
			}

}

}

void mapping::right(char p){
	node* parent;	
	parent=  this->currentPosition; // localize the robot(get it current position)
	int y = parent->y;
	int x = parent->x;
	//cout<< "x is " << x  <<"y is" <<y <<"\n";

	if(y+1==this->totalY){  // check if the robot has reached extreme point of it current map.
		for(int i=0; i<totalX; i++){ // create a node down each row .
    		for(int j=totalY; j<=totalY; j++){
    			 node* hello = new node(i,j,p); // asumes the nodeStatus has passage.
        		field[i].push_back(hello);    
    }
}
		totalY= totalY+1; // increase the number of column.
}
	
 		currentPosition = field[x][y+1]; // change the currentPosition.
	this->checkLocation();	
}


void mapping::left(char p){
	node* parent;
	parent=  this->currentPosition; // localize the robot(get it current position)
	int y = parent->y;
	int x = parent->x;
	if(y==0){ // check if the robot has reached extreme point of it  current map.
		for(int i=0; i<totalX; i++){ 
			for(int j=0; j<totalY; j++){  // shifting all rows to the right
				field[i][j]->y =  field[i][j]->y+1;
			}
		}	
		for(int i=0; i<totalX; i++){ // create a node down each row .
				 node* hello = new node(i,y,p);
				field[i].insert(field[i].begin(), hello); // asumes the nodeStatus has passage.
		}
		currentPosition = field[x][y];
		this->totalY= this->totalY +1;	 //increase the number of column.
	}else{

		currentPosition = field[x][y-1]; // change the currentPosition.

	}
	this->checkLocation();
}

void mapping::forward(char p){
	node* parent;
	parent=  this->currentPosition; // localize the robot(get it current position)
	int y = parent->y;
	int x = parent->x;
	if(x==0){ // check if the robot has reached extreme point of it current  map.
		for(int i =0; i<totalX; i++){ // shifting each columns backwards.
			for(int j=0; j<totalY; j++){
				field[i][j]->x =  field[i][j]->x+1;
				
		}	
	}
	
	vector< node* > command;
	for(int j=0; j<totalY; j++){ // create a node  across each column .
	 	 node* hello = new node(x,j,p);	 // asumes the nodeStatus has passage.
				 command.push_back(hello);		 
	} 
	
	field.insert( field.begin(), command); // insert a 
	currentPosition = field[x][y];
	this->totalX = this->totalX+1; //increase the number of rows.
	
}else{
		currentPosition = field[x-1][y]; // change the current position.
}
	this->checkLocation();
}

void mapping::backward(char p){
	node* parent;
	parent=  this->currentPosition; // localize the robot(get it current position)
	int y = parent->y;
	int x = parent->x;
	//cout<< "x is " << x  <<"y is" <<y <<"\n";
	int  j;
	
	if(x+1 ==this->totalX){ // check if the robot has reached extreme point of it current  map.
		vector <node*> move;
		for(j=0; j<totalY; j++){ // create a node across  each columns .
	 		 node* hello = new node(x+1,j,p);	 // assumes nodeStaus is passage.
				 move.push_back(hello);
				
	} 
	field.push_back(move);
		this->totalX = this->totalX+1; // increase the number of columns.
	}	

	currentPosition = field[x+1][y]; // change the current position.

	this->checkLocation();
}


void mapping::print_mapping(){ // printing out the mapped areas.
		
	for( int i =0; i<this->totalX; i++){
		for(int j=0; j<this->totalY; j++){
			cout << field[i][j]->nodeStatus <<"\t";	
		}
		cout<<"\n";
	}
}



vectorBox <vectorBox <node* > > mapping::vectorToBox(){
		 vectorBox <vectorBox <node* > > BOX;	
	 	ofstream MyFile("filename.txt");// open a file name "filename.txt"
		int  i,j;
		//cout<< this->totalX << " "<< this->totalY << '\n';
		MyFile<< this->totalX << " "<< this->totalY << 'S' <<'\n';	// write to the file : the total number of rows, columns and 's' indicating it as starting
		for( i =0; i< this->totalX; i++){
			 	vectorBox <node* > box;
		 		//cout<<"still working1";	
				for(j=0; j< this->totalY; j++){
						//cout<<"still working21";	
						node* hello = field[i][j];
						MyFile << i <<" " << j <<" " << hello->nodeStatus <<'\n'; // write each node (x-coordinate y-coordinate ) and it status to file.
						box.push_back(hello); 
				
				}
				BOX.push_back(box);
	}

	
	MyFile.close(); // close the file pointer.
	this->save_Landmarks(); 
	return BOX;
}  




void mapping::checkLocation(){	
	char ch;
	cout<< "enter p or b";
	cin>>ch; // prompting to get if node is a passage, blockage or landmark.
	if(ch=='m'){ // check if node is landmark
		currentPosition->nodeStatus = 'p';	 // set it status to passage.
		landmarks.push_back(currentPosition);	// add it to landmark list.
	}else{
		currentPosition->nodeStatus= ch; 
	}
	cout <<"\n";
}

void mapping ::addBorders(){
this->currentPosition = field[0][0]; 
this->forward('x'); // to add 'x'  to the first row of each column. it indicate demarcation
this->currentPosition = field[0][0];
this->left('x'); // to add 'x'  to the first column of each row. it indicate demarcation
this->currentPosition = field[this->totalX-1][this->totalY-1];
this->right('x'); // to add 'x'  to the last column of each row. it indicate demarcation
this->currentPosition = field[this->totalX-1][this->totalY-1];
this->backward('x'); // to add 'x'  to the last t row of each column. it indicate demarcation
}


void  mapping::save_Landmarks(){

	fstream landmarkFile ("landmark.txt");

	if(landmarkFile){ // to check if the landmarK FIle exist
			/*int i; int j;
		cout<<"\n";
		for(i=0; i<this->landmarks.size(); i++ ){
				int x  = landmarks.index(i)->x;
				int y = landmarks.index(i)->y;
				cout<< x <<" " << y   << "  " << i << '\n';
			}
			cout << "\nwahalaaa";
		return;*/
		
	}else{ // if it doesnot.
			ofstream landmarkFile ("landmark.txt");
		//	cout << "we move Nothing spoil";
			int i =0;
			cout<< this->landmarks.size();
			for(i=0; i<this->landmarks.size(); i++ ){  //loop throught the landmark list.
				int x  = landmarks.index(i)->x;
				int y = landmarks.index(i)->y;
				landmarkFile<< x <<" " << y   << "  " << i << '\n'; // write the x-coordinate , y-coordinate and  the landmark's index to file 
 
			}
		
	}
	landmarkFile.close();
}
