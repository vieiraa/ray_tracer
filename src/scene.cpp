#include "scene.h"
#include "diffuse.h"
#include <stdlib.h>

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

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

    return intersection_result;
}

/*
void Scene::load() {
    for (int i = 0; i < 3; i++) {
        glm::vec3 v1(drand48() * 10, drand48() * 10, drand48() * 10);
	glm::vec3 v2(drand48() * 10, drand48() * 10, drand48() * 10);
	glm::vec3 v3(drand48() * 10, drand48() * 10, drand48() * 10);

        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Fast_Triangle(v1, v2, v3)));
    }
    }*/

void Scene::load() {

	//scene objects
	/*Sphere *s1 = new Sphere(glm::vec3(-1.5f, 0, -2.5f), 0.75f);
	s1->material_ = std::make_shared<Diffuse>(glm::vec3(175.0f, 238.0f, 238.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	primitives_.push_back(Primitive::PrimitiveUniquePtr(s1));

    Sphere *s2 = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.75f);
    s2->material_ = std::make_shared<Diffuse>(glm::vec3(153.0f, 50.0f, 204.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s2));

    Sphere *s3 = new Sphere(glm::vec3(1.5f, 0, -2.5f), 0.75f);
    s3->material_ = std::make_shared<Diffuse>(glm::vec3(250.0f, 128.0f, 114.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s3));
	
	//Lights
    Sphere *s4 = new Sphere(glm::vec3(0.0f, 4.0f, 1.0f), 1.5f);
    s4->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s4));

    Sphere *s5 = new Sphere(glm::vec3(0.0f, 4.0f, -0.75f), 1.5f);
    s5->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s5));

    Sphere *s6 = new Sphere(glm::vec3(0.0f, 4.0f, -2.5f), 1.5f);
    s6->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s6));

    Sphere *s7 = new Sphere(glm::vec3(0.0f, 4.0f, -4.25f), 1.5f);
    s7->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s7));
	*/
    TriangleMesh mesh("C:\\Users\\lucca\\Documents\\GitHub\\ray_tracer\\3d_models\\cat.obj");

    for (auto &t : mesh.getTriangles()) {
        primitives_.push_back(Primitive::PrimitiveUniquePtr(t.release()));
    }
}
