#include "scene.h"
#include "diffuse.h"
#include "perfect_reflector.h"
#include "smooth_dielectric.h"

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

#if 1
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
    intersection_result = bvh_->intersect(ray, intersection_record, num_intersections, num_intersections_test);
#endif

    return intersection_result;
}

void Scene::load() {

    //scene objects

        
       Sphere *s1 = new Sphere(glm::vec3(-1.0f, -0.9f, -2.95f), 0.8f);
       s1->material_ = std::make_shared<SmoothDielectric>(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s1));
       
       Sphere *s2 = new Sphere(glm::vec3(1.0f, -0.9f, -3.5f), 0.8f);
       s2->material_ = std::make_shared<PerfectReflector>();
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s2));
       /*
       Sphere *s3 = new Sphere(glm::vec3(0.75f, -0.75, -1.0f), 0.27f);
       s3->material_ = std::make_shared<Diffuse>(glm::vec3(250.0f, 128.0f, 114.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s3));
       */ 
       //Lights
       /*
       Sphere *s4 = new Sphere(glm::vec3(0.0f, 4.0f, 1.0f), 1.5f);
       s4->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s4));
        
       Sphere *s5 = new Sphere(glm::vec3(0.0f, 4.0f, -0.75f), 1.5f);
       s5->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s5));
    
       Sphere *s6 = new Sphere(glm::vec3(0.0f, 4.0f, -2.5f), 1.5f);
       s6->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s6));
       */
       Sphere *s7 = new Sphere(glm::vec3(0.0f, 4.0f, -3.0f), 1.75f);
       s7->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.5f, 7.5f, 7.5f));
       primitives_.push_back(Primitive::PrimitiveUniquePtr(s7));
       
    TriangleMesh mesh("C:\\Users\\lucca\\Documents\\GitHub\\ray_tracer\\3d_models\\scene.obj", glm::vec3 (0.4f,0.4f,0.4f ));
    
    //TriangleMesh mesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/scene.obj", glm::vec3(0.4f, 0.4f, 0.4f));
    //TriangleMesh cat("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/cat.obj", glm::vec3(0.8f, 0.8f, 0.8f));

    for (auto &t : mesh.getTriangles()) {
        t->material_ = std::make_shared<Diffuse>(glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0, 0, 0));
        primitives_.push_back(Primitive::PrimitiveUniquePtr(t.release()));
    }

    //for (auto &t : cat.getTriangles()) {
      //  t->material_ = std::make_shared<SmoothDielectric>(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        //primitives_.push_back(Primitive::PrimitiveUniquePtr(t.release()));
    //}
}
