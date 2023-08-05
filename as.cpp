
#include "astar.cpp"  // include the astar class libraries
#include <iostream>
using namespace std;

int main(){
	astar Astar;  // creating an instance of class astar.
	Astar.populate(); // astar populate to get the prestored mapped loaded on the algorithm.
	Astar.asmapping(); // generating a path that link each landmark to   all other one.
  vectorBox <node *> path =Astar.pathPlanner(2,1,3,2);  // generating a path from landmark 0 to landmarks 1. '2' as the fourth parameters shows path between two landmarks.
  motionPlanner gmotion(path,   Astar);  // creating an instance of class motionPlanner. it takes the path to plan motion for, and the object to which the path is gotten.
  cout<<"sgsgs\n";
  Astar.print_node(path); 
  cout<<"\n"; 
  Astar.print_node(gmotion.get_vector());
  cout<<"achievement";
}
  //needs improvement
  // 1. map remain the same after each robot movement. 
  


 


