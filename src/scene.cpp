#include "scene.h"
#include "diffuse.h"
#include "perfect_reflector.h"
#include "smooth_dielectric.h"
#include "cook_torrance.h"

Scene::Scene() {}

Scene::~Scene() {}

bool Scene::intersect(const Ray &ray,
                      IntersectionRecord &intersection_record) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

#if 0
    // Loops over the list of primitives, testing the intersection of each primitive against the given ray
    //std::size_t primitive_id = 0;
    for (size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ ) {
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) ) {
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }
        }
    }
#else
    unsigned num_intersections;
    unsigned num_intersections_test;
    intersection_result = acc_->intersect(ray, intersection_record, num_intersections, num_intersections_test);
#endif

    return intersection_result;
}

void Scene::load() {
    //Lights
    /*
      Sphere *s4 = new Sphere(glm::vec3(0.0f, 4.0f, 1.0f), 1.5f);
      s4->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
      primitives_.push_back(Primitive::PrimitiveUniquePtr(s4));

      Sphere *s5 = new Sphere(glm::vec3(0.0f, 4.0f, -0.75f), 1.5f);
      s5->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
      primitives_.push_back(Primitive::PrimitiveUniquePtr(s5));*/

    Sphere *s6 = new Sphere(glm::vec3(0.0f, 4.0f, -2.5f), 1.5f);
    s6->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s6));

    Mesh mesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/scene.obj");
    Mesh cat("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/cat.obj");

    for (auto &m : mesh.getMeshes()) {
        for (auto &t : m.getTriangles()) {
            t->material_ = std::make_shared<Diffuse>(glm::vec3(0.8f), glm::vec3(0.0f));
            primitives_.push_back(Primitive::PrimitiveUniquePtr(t));
        }
    }

    for (auto &m : cat.getMeshes()) {
        for (auto &t : m.getTriangles()) {
            t->material_ = std::make_shared<Diffuse>(glm::vec3(0.5f), glm::vec3(0.0f));
            primitives_.push_back(Primitive::PrimitiveUniquePtr(t));
        }
    }
}
