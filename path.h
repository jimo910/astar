#include<iostream>
#include <cmath>
#include <vector>
using namespace std;

// it is class of an object that has attribute(x-coord, y-coordinate , nodestatus)
class node{ 
		public:
		node(int xt, int yt, char p){
			next= 0;
			globalValue = localValue= INFINITY;
			nodeStatus= p;
			checkers='p';
			this->y = yt;
			this->x = xt;
			count =0;
		} 
		node* next; //it points to the node next to it in a container
		 node* parent; // it points to the previous node on the path to the targeted node.
		 float globalValue; // globalValue is  the distance between the starting-node and the targeted node.
		 float localValue; // local value is the distance  between this node and the targeted node.
		 char nodeStatus; // a passage or a blockage
		 char checkers; // visited or unvisited.
		 int x; // the x-coordinate of the node
		 int y; // the y-coordinate of the node.
		 int indexs; // it returns the  number of node object instantiated before this node.
		 int count;

	};
	



	
template <class T>

class nodeBox {  //  a class to make working with node object easier.
public:
 nodeBox() {
 	next = 0;
 }
	nodeBox(T el, nodeBox *ptr = 0) {
	 info = el; next = ptr;
 }
   T info;
   nodeBox *next;
};


template <class T>
	class vectorBox{ // a class object for storing and indexing Element.		
		public:
 			vectorBox() { // vectorbox constructor.
			head = tail = 0;
			count =0;
		// this->y = x;
   }

 		int isEmpty() { //  function to check if the vectorBox is empty
 				return head == 0;
 			}
 		void push_back(T); // to insert a new element T at the back of container.
	    void insert(T); // to insert  a new element T at the front of container
 		T index(int); // it returns the element  T at the parameter 
 		int size(); // it returms the number of element in the box
	    int count;	// it use to increment the number of element in the container.
		vectorBox<T> &operator+=( vectorBox<T>);
  		int x;
 		int y;
	 vectorBox< T > addvectorBox( vectorBox<T> x, vectorBox<T> y);
 	//	void changedx(int x);
		 nodeBox<T> * returnHead(){  // it return the  first element.
 			return head;
 		}
		nodeBox<T> * returntail(){ // it returns the last element.
 				return tail;
 }
 	private:
 				nodeBox<T>* head=0;  nodeBox<T> *tail=0; // th
};





