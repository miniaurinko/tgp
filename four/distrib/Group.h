#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

  Group(){

  }
	
  Group( int num_objects ){

  }

  ~Group(){
   
  }

  virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
	  bool ok = false;
	  for (int i = 0; i < objects.size(); i++) {
		  if (objects[i]->intersect(r, h, tmin) == true) ok = true;
		}
	  return ok;
   }
	
  void addObject( int index , Object3D* obj ){
	  objects.push_back(obj);
  }

  int getGroupSize(){ 
	  objects.size();
  }

 private:
	 vector<Object3D*> objects;
};

#endif
	
