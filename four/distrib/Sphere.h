#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere(){ 
		tcenter = (Vector3f::ZERO);
		tradius = (1.f);

	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material),
		tcenter(center), 
		tradius(radius)
		{
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		//tmin: etäisyys kamerasta?
		Vector3f origin = r.getOrigin();
		Vector3f direction = r.getDirection();

		//etäisyys ympyrän keskipisteestä = radius
		//at^2+bt+c=0
		//a = 1
		float b = 2 * (Vector3f::dot(direction, origin)) - Vector3f::dot(direction, tcenter);
		float c = Vector3f::dot(origin, origin) - tradius * tradius;
		float dtemp = (b * b) - (4 * c);
		float t1 = (-b + std::sqrt(dtemp)) / 2;
		float t2 = (-b - std::sqrt(dtemp)) / 2;
		float t;
		if (dtemp < 0) return false;
		else if (dtemp == 0) {
			t = -b / 2;
			if (t >= tmin && t < h.getT())
			{
				Vector3f point = r.pointAtParameter(t);
				Vector3f normal = (point - tcenter).normalized();
				h.set(t, this->getMaterial(), normal);
			}
		}
		else {
			if (t1 >= tmin && t2 >= tmin) {
				t = std::_Min_value(t1, t2);
			}
			else if (t1 >= tmin) t = t1;
			else if (t2 >= tmin) t = t2;
			else return false;
			if (t > h.getT()) {
				Vector3f point = r.pointAtParameter(t);
				Vector3f normal = (point - tcenter).normalized();
				h.set(t, this->getMaterial(), normal);
			}
			else return false;
		}
		return true;
	}

private:
	Vector3f tcenter;
	float tradius;
protected:
	

};


#endif
