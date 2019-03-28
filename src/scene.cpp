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

/*void Scene::load( void )
{
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Naive_Triangle{ glm::vec3{0.25f, 0.5f, -1.0f}, glm::vec3(0.5f, 0, 0), glm::vec3(0, 0, 0)}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Naive_Triangle{ glm::vec3{-0.5f,-0.25f,0}, glm::vec3(-0.5f,-0.75,0), glm::vec3(0.5,-0.5,0)}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Naive_Triangle{ glm::vec3{0.25f,-0.25f,0}, glm::vec3(-0.25f,-0.25, 0), glm::vec3(0,-0.5,-1.0)}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Naive_Triangle{ glm::vec3{-0.25f,0.25f,-4.0f}, glm::vec3(-0.75f,0.25,-4.0), glm::vec3(-0.5,-0.25,-4.0)}));

}*/
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
/*
    Sphere *s1 = new Sphere(glm::vec3(2.75f, 4.0f, -6.75f), 0.25f);
    s1->material_ = new Diffuse(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s1));

    Sphere *s2 = new Sphere(glm::vec3(2.75f, 4.0f, -1.5f), 0.25f);
    s2->material_ = new Diffuse(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s2));
*/
    Sphere *s3 = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.75f);
    s3->material_ = std::make_shared<Diffuse>(glm::vec3(153.0f, 50.0f, 204.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s3));

    Sphere *s4 = new Sphere(glm::vec3(1.5f, 0, -2.5f), 0.75f);
    s4->material_ = std::make_shared<Diffuse>(glm::vec3(250.0f, 128.0f, 114.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s4));

    Sphere *s5 = new Sphere(glm::vec3(0.0f, 4.0f, 1.0f), 1.5f);
    s5->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s5));

    Sphere *s6 = new Sphere(glm::vec3(0.0f, 4.0f, -0.75f), 1.5f);
    s6->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s6));

    Sphere *s7 = new Sphere(glm::vec3(0.0f, 4.0f, -2.5f), 1.5f);
    s7->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s7));

    Sphere *s8 = new Sphere(glm::vec3(0.0f, 4.0f, -4.25f), 1.5f);
    s8->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s8));

    Sphere *s9 = new Sphere(glm::vec3(-1.5f, 0, -2.5f), 0.75f);
    s9->material_ = std::make_shared<Diffuse>(glm::vec3(175.0f, 238.0f, 238.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s9));
    /*TriangleMesh *light = new TriangleMesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/sphere.obj");
    for (auto tr : light->getTriangles()) {
        tr->material_->emitted_ = glm::vec3(15, 15, 15);
        tr->material_->reflected_ = glm::vec3(0,0,0);
        primitives_.push_back(Primitive::PrimitiveUniquePtr(tr));
        }*/

    TriangleMesh mesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/scene.obj");
    primitives_.insert(primitives_.end(), std::make_move_iterator(mesh.getTriangles().begin()), std::make_move_iterator(mesh.getTriangles().end()));
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(mesh));
}
