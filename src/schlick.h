#pragma once

#include "ray.h"

float schlick(const glm::vec3 &r_dir, const glm::vec3 &normal, float ni, float nt) {
    float R0 = (ni - nt) / (ni + nt);
    R0 *= R0;

    float cos1 = -glm::dot(normal, r_dir);

    if (ni > nt) {
        float n = ni / nt;
        float cos2 = 1.0f - n * n * (1.0f - cos1 * cos1);

        if (cos2 < 0.0f)     // TIR
            return 1.0f;
    }

    float aux = 1-cos1;

    return R0 + (1.0f - R0) * aux * aux * aux * aux * aux;
}
