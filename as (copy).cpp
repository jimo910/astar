#include "astar.h"
int main(){
	astar Astar;
	Astar.populate();
	Astar.asmapping();	
 cout<<"\n\n\n";
  vectorBox <node *> path =Astar.pathPlanner(2,1,3,2);
  motionPlanner gmotion;
  gmotion.set_vector(path);
  gmotion.planMotion();
  cout<<"sgsgs";
  Astar.print_node(path);
  cout<<"\n";
  Astar.print_node(gmotion.get_vector());
  cout<<"achievement";
}
  

 
