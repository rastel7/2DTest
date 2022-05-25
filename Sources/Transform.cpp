#include"Transform.h"

Transform::Transform() {
	
}

template<class T>
Transform::Transform(T x, T y):m_position(float(x),float(y)) {
	
}
