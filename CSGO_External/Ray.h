#ifndef RAY_H 
#define RAY_H 
#include "Vector.h"

class Ray {

public:
	Vector origin, direction, directionInverse;

	Ray(Vector _origin, Vector _direction);

	bool Trace(Vector leftBottom, Vector rightTop, float &distance);

};

#endif  