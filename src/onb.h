#pragma once

#include <glm/glm.hpp>

class ONB {
    glm::mat3x3 matrix_;
    glm::vec3 u_;
    glm::vec3 v_;
    glm::vec3 w_;

public:
    ONB();

    void setFromV(const glm::vec3 &v);
    void setFromUW(const glm::vec3 &u,
                   const glm::vec3 &w);

    glm::mat3x3 getBasisMatrix() const;

private:
    void setBasisMatrix();
};
