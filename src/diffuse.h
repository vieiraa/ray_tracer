#pragma once

#include "material.h"
#include <glm/glm.hpp>

class Diffuse : public Material
{
    public:
        Diffuse(glm::vec3 r, glm::vec3 e);
        virtual ~Diffuse();

        glm::vec3 fr();

    protected:

    private:
};
