#include "aabbBound.h"
#include "ray.h"
#include <algorithm>    // std::min

aabbBound::aabbBound(void) {};

aabbBound::aabbBound(const glm::vec3 &p1, const glm::vec3 &p2) {
	pMin = glm::vec3{ std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z) };
	pMax = glm::vec3{ std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z) };

};

glm::vec3 aabbBound::diagonal() const {
	return pMax - pMin;

}

double aabbBound::getArea() {
	glm::vec3 d = diagonal();
	return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);

}

double aabbBound::getVolume() {
	glm::vec3 d = diagonal();
	return d.x * d.y * d.z;

}

bool aabbBound::intersect(const Ray &ray) const {
	// An Efficient and Robust Ray–Box Intersection Algorithm,
	// Peter Shirley
	
	float txmin;
	float txmax;
	float tymin;
	float tymax;
	float tzmin;
	float tzmax;
	float divx;
	float divy;
	float divz;

	divx = 1.0f / ray.direction_.x;
	if (divx >= 0.0f)
	{
		txmin = (pMin.x - ray.origin_.x) * divx;
		txmax = (pMax.x - ray.origin_.x) * divx;
	}
	else
	{
		txmin = (pMax.x - ray.origin_.x) * divx;
		txmax = (pMin.x - ray.origin_.x) * divx;
	}

	divy = 1.0f / ray.direction_.y;
	if (divy >= 0.0f)
	{
		tymin = (pMin.y - ray.origin_.y) * divy;
		tymax = (pMax.y - ray.origin_.y) * divy;
	}
	else
	{
		tymin = (pMax.y - ray.origin_.y) * divy;
		tymax = (pMin.y - ray.origin_.y) * divy;
	}

	if ((txmin > tymax) || (tymin > txmax))
		return false;

	if (tymin > txmin)
		txmin = tymin;

	if (tymax < txmax)
		txmax = tymax;

	divz = 1.0f / ray.direction_.z;
	if (divz >= 0.0f)
	{
		tzmin = (pMin.z - ray.origin_.z) * divz;
		tzmax = (pMax.z - ray.origin_.z) * divz;
	}
	else
	{
		tzmin = (pMax.z - ray.origin_.z) * divz;
		tzmax = (pMin.z - ray.origin_.z) * divz;
	}

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;

	if (tzmin > txmin)
		txmin = tzmin;

	if (tzmax < txmax)
		txmax = tzmax;

	return true;//tmax > 0.00001f;
};