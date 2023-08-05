#include "path.cpp"
class mapping{
	
	public:
	 void sMapping();
	 // simulating the robot moving right
	 void right(char p);
	 // simulating the robot moving left 
	 void left(char p); 
	 //simulating the robot moving forward.
	 void forward(char p); 
	// simulating the robot moving backward.
	 void backward(char p); 
	 vectorBox <vectorBox <node* > > vectorToBox();
	 vectorBox<node *> landmark(){
		return landmarks;
	}
	// to print status of each node.
	void print_mapping();
	// to localize the robot.
	 void checkLocation();
	 // to demarcate the boundaries.
	 void addBorders();
	 // to save node marked as landmark  to file.
	 void save_Landmarks();
	  void isFile();
	private:
	vector < vector <node* > > field;
	int totalX, totalY;
	vectorBox<node *> landmarks;
	node* currentPosition;
	int file_dey ;
// to check if the map exist 

	
};

