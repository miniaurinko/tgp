#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f center; 
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){
		t_center = center;
		t_dir = direction.normalized();
		t_up = up;
		t_angle = angle;
	}

	virtual Ray generateRay( const Vector2f& point){
		//return Ray(Vector3f(1,0,0),Vector3f(1,0,0));
		// r = (x*u + fov*y*v + D*w)
		float D = 1/(tan(t_angle / 2));
		Vector3f r = point.x()*Vector3f::cross(t_dir, t_up) + point.y()*t_up + D * t_dir;
		r.normalize();
		return Ray(t_center, r);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
	Vector3f t_up;
	Vector3f t_center;
	Vector3f t_dir;
	float t_angle;
};

#endif //CAMERA_H
