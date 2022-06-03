#pragma once
#include"Hittable.h"

#include<memory>
#include<vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
	std::vector<std::shared_ptr<Hittable>> objects;
	HittableList() {};
	HittableList(shared_ptr<Hittable> object)
	{
		Add(object);
	}
	void Clear()
	{
		objects.clear();
	}

	void Add(shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

};


