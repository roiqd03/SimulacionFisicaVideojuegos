#pragma once
#include "../../RenderUtils.hpp"

class BoundingBox
{
private:
	Vector3 _min;
	Vector3 _max;
public:
	BoundingBox() : _min(), _max() {}
	BoundingBox(Vector3 minimum, Vector3 maximum) : _min(minimum), _max(maximum) {}
	inline BoundingBox(Vector3 dimensions){
		Vector3 d = dimensions / 2;
		_min = { -d.x, -d.y, -d.z };
		_max = { d.x, d.y, d.z };
	}
	inline bool contains(Vector3 point) {
		return point.x >= _min.x && point.x <= _max.x &&
			point.y >= _min.y && point.y <= _max.y &&
			point.z >= _min.z && point.z <= _max.z;
	}
	inline void translate(Vector3 movement) {
		_min += movement;
		_max += movement;
	}
};

