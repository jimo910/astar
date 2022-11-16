#include<iostream>
#include <cmath>
#include <vector>
using namespace std;

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
		node* next;
		 node* parent;
		 float globalValue;
		 float localValue;
		 char nodeStatus; // a passage or a blockage
		 char checkers; // visited or unvisited.
		 int x;
		 int y;
		 int indexs;
		 int count;

	};
	
	
template <class T>
class nodeBox {
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
class vectorBox{
public:
   vectorBox() {
		 head = tail = 0;
		 count =0;
		// this->y = x;
   }

 int isEmpty() {
 return head == 0;
 }
 void push_back(T);
 void insert(T);
 T index(int);
 int size();
 int count;	
 int x;
 int y;
 void changedx(int x);
 nodeBox<T> * returnHead(){
 	return head;
 }
nodeBox<T> * returntail(){
 	return tail;
 }
 private:
 	nodeBox<T>* head;  nodeBox<T> *tail;
};

template <class T>
void vectorBox<T>::insert(T el) {
 head = new nodeBox<T>(el,head);
 if (tail == 0){
 	tail = head;
}
count = count+1;
}

template <class T> 
void vectorBox<T>::push_back(T el) {
 	if (tail != 0) { 
 		tail->next = new nodeBox<T>(el);
 		tail = tail->next;
 }
 else head = tail = new nodeBox<T>(el);
 	count = count+1;
}

template <class T>
int vectorBox<T>::size(){
	return count;
}
template <class T>
 T vectorBox<T>::index(int j){
 	size_t i;
 	nodeBox<T>* start;
	T returnw;
	start = head;
 	for(i=0; i<this->size(); i++){
 		if(j==i){
 			returnw= start->info;
 			
		 }
		 start= start->next;
	 }
	 return returnw;
 }

template <class T> 
 void vectorBox<T>::changedx(int x){
 	size_t i;
 	for(i=0; i<this->size(); i++){
 		T hello = index(i);
 		hello->x = i;
	}
 }
 
 template<class T>
vectorBox< T > addvectorBox( vectorBox<T> x, vectorBox<T> y){
	vectorBox<T> path;
	vector<node *> vectorPath;
	size_t j;
	
	for(j=0; j<x.size(); j++){
			node* hello = x.index(j);
			vectorPath.push_back(hello);
					
	}
	for(j=0; j<x.size(); j++){
		node* hello = y.index(j);
		vectorPath.push_back(hello);
					
		}
	for(j=0; j<vectorPath.size(); j++){
		node* hello = vectorPath[j];
		path.push_back(hello);
				
		}
	return path;
	
}
 
 
