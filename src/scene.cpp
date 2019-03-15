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
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                
                std::cerr << "id = " << primitive_id << "\n";
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
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
    Sphere *s = new Sphere(glm::vec3(-2, 0.25f, 3.0f), 1);
    s->material_ = new Diffuse(glm::vec3(0, 0, 0), glm::vec3(40, 40, 40));
    Fast_Triangle *t1 = new Fast_Triangle(glm::vec3(0,1,0), glm::vec3(-1, 1, 0), glm::vec3(0.5f, 0, 0));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t1));
    /*TriangleMesh *light = new TriangleMesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/sphere.obj");
    for (auto tr : light->getTriangles()) {
        tr->material_->emitted_ = glm::vec3(15, 15, 15);
        tr->material_->reflected_ = glm::vec3(0,0,0);
        primitives_.push_back(Primitive::PrimitiveUniquePtr(tr));
        }*/
    /*
    TriangleMesh *mesh = new TriangleMesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/cat.obj");
    auto triangles = mesh->getTriangles();
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(mesh));

    for (auto tr : triangles) {
	primitives_.push_back(Primitive::PrimitiveUniquePtr(tr));
        }*/
}
