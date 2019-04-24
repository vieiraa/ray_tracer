#include <glm/glm.hpp>
#include "ray.h"

class AABB {

public:
    AABB(void);

    AABB(const glm::vec3 &p1, const glm::vec3 &p2);

    glm::vec3 diagonal() const;

    double getArea();

    double getVolume();

    bool intersect(const Ray &ray) const;

    glm::vec3 pMin;
    glm::vec3 pMax;
    glm::vec3 centoid;
};
