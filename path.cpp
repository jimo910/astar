 
 #include "path.h"
 #include <iostream>
using namespace std;

// insert a new element  T at the front of the container
template <class T>
void vectorBox<T>::insert(T el) {
 head = new nodeBox<T>(el,head); // point the new (head->next) pointer to the current head
 if (tail == 0){ // to check if there  is no element in the container.
 	tail = head;
}
count = count+1; // increment the  number of element.
}
// to insert a new element T at the back of the container.
template <class T> 
void vectorBox<T>::push_back(T el) {
 	if (tail != 0) {  // checking if the  container is not empty.
 		tail->next = new nodeBox<T>(el); // point the tail->next to the new element.
 		tail = tail->next; // declare tail to be equal to the new element.
 }
 else head = tail = new nodeBox<T>(el);
 	count = count+1; // to increment the number of element T in the container.
}
// it returns the number of element in the container.
template <class T>
int vectorBox<T>::size(){
	return count;
}

// it returns the element at index J.
template <class T>
 T vectorBox<T>::index(int j){
 	int i;
 	nodeBox<T>* start; //a pointer to  object of class nodeBox.
	T returnw; //an element of type T
	start = head; // assign head to the variable start.
 	for(i=0; i<this->size(); i++){ // loop through the element in the container.
 		if(j==i){ // check if the parameter index j is equal to i.
 			returnw= start->info; // get the object stored in the nodeBox info.
 			break; // bre
		 }
		 start= start->next; // point to the next NodeBox  element in the container.
	 }
	 return returnw;
 }

/*template <class T> 
 void vectorBox<T>::changedx(int x){
 	size_t i;
 	for(i=0; i<this->size(); i++){
 		T hello = index(i);
 		hello->x = i;
	}
 }*/
 


 template<class T>
vectorBox<T> vectorBox< T >::addvectorBox( vectorBox<T> x, vectorBox<T> y){
	vectorBox<T> path; //  variable vectorBox. =>path
	vector<T> vectorPath; // variable std::vector  => vectorPath.
	int j;// variable int j.
	for(j=0; j<x.size(); j++){ // insert all element in vectorBox<T> x into vector vectorPath
			node* hello = x.index(j);
			vectorPath.push_back(hello);
					
	}
	for(j=0; j<x.size(); j++){ //inserting all elements in  vectorBox<T> y into vector vectorPath.
		node* hello = y.index(j);
		vectorPath.push_back(hello);
					
		} 
		int xyz = vectorPath.size();

	for(j=0; j<xyz; j++){ // inserting all element in vector vectorPath to vectorBox  path
		node* hello = vectorPath[j];
		path.push_back(hello);
				
		}
	return path; // return vectorBox path.
	
}

/*template <class T>
vectorBox<T> operator+=(vectorBox<T> hel){
		vectorBox<T> hello  ;
		return hello;
}*/
 