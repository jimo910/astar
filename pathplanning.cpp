 #include "mapping.h"
vectorBox<node *>  vectorNode();
vectorBox<node *>  vectorBoxNode();



int main(){
	

 mapping gmapping;
 gmapping.sMapping();
 gmapping.print_mapping();
 vectorBox < vectorBox <node* > > sure = gmapping.vectorToBox();
 
 

}

/*vectorBox<node *>  vectorNode(){

	vector<node*> v;
	vectorBox <node *> hello;
	size_t i;
	for(i=0; i<36000000; i++){
		node* hellos = new node(0,i);
	   v.push_back(hellos);
	}
	for(i=0; i<36000000; i++){
		node * hellos = v[i];
		hello.push_back(hellos);
	}
		
	return hello;
}

vectorBox<node *>  vectorBoxNode(){
	size_t i;
	vectorBox <node *> hello;
	for(i=0; i<36000000; i++){
		node* hell =  new node(0,i);
		hello.push_back(hell);	
	}
	return hello;
}

*/


