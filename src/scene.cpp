#include "scene.h"
#include "diffuse.h"
#include "perfect_reflector.h"
#include "smooth_dielectric.h"
#include "cook_torrance.h"

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
    intersection_result = bvh_->intersect(ray, intersection_record, num_intersections, num_intersections_test);
#endif

    return intersection_result;
}

void Scene::load() {

    //scene objects


    /*Sphere *s1 = new Sphere(glm::vec3(-0.8f, -1.1f, 0.5), 0.7f);
    s1->material_ = std::make_shared<SmoothDielectric>(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s1));

    Sphere *s2 = new Sphere(glm::vec3(0.8f, -1.1f, -0.3), 0.7f);
    s2->material_ = std::make_shared<PerfectReflector>();
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s2));

    Sphere *s3 = new Sphere(glm::vec3(0.0f, -0.75, 2.0f), 0.7f);
    s3->material_ = std::make_shared<CookTorrance>(glm::vec3(250.0f, 128.0f, 114.0f)/255.0f, 1.0f);
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s3));*/

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
    Sphere *s7 = new Sphere(glm::vec3(5.0f, -5.0f, -3.0f), 2.0f);
    s7->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(15.0f, 15.0f, 15.0f));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s7));

    //TriangleMesh mesh("C:\\Users\\lucca\\Documents\\GitHub\\ray_tracer\\3d_models\\scene.obj", glm::vec3 (0.4f,0.4f,0.4f ));

    Mesh mesh("C:\\Users\\lucca\\Documents\\GitHub\\ray_tracer\\3d_models\\project_objects\\scene_real.obj");
    //Mesh mesh("/home/jordy/Documentos/cg/trabalho 2/ray_tracer/3d_models/project_objects/scene_real.obj");


    for (auto &m : mesh.getMeshes()) {
        for (auto &t : m.getTriangles()) {
            if (m.name_.find("Glass") != std::string::npos)
                t->material_ = std::make_shared<SmoothDielectric>(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0));

            else if (m.name_.find("Lamp") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(17.0f, 17.0f, 17.0f));

            else if (m.name_.find("GlasSol") != std::string::npos)
                t->material_ = std::make_shared<SmoothDielectric>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)*20.0f);

            else if (m.name_.find("LuzAmarela") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(240.0f/255, 230.0f/255, 140.0f/255)*120.0f);

            else if (m.name_.find("Metal1") != std::string::npos)
                t->material_ = std::make_shared<CookTorrance>(glm::vec3(160.0f, 82.0f, 45.0f)/255.0f, 0.2);

            else if (m.name_.find("Metal2") != std::string::npos)
                t->material_ = std::make_shared<CookTorrance>(glm::vec3(192.0f, 192.0f, 192.0f) / 255.0f, 0.3);

            else if (m.name_.find("MetalBranco") != std::string::npos)
                t->material_ = std::make_shared<CookTorrance>(glm::vec3(255.0f, 250.0f, 250.0f) / 255.0f, 0.3);

            else if (m.name_.find("CadeiraVermelha") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0.0f,0.0f,0.0f));

            else if (m.name_.find("Marrom") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(205.0f, 133.0f, 63.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));

            else if (m.name_.find("PernaBeje") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(222.0f,184.0f,135.0f),glm::vec3(0.0f, 0.0f, 0.0f));

            else if (m.name_.find("BrancoPorta") != std::string::npos)
                t->material_ = std::make_shared<Diffuse>(glm::vec3(255.0f, 250.0f, 250.0f)/255.0f, glm::vec3(0.0f, 0.0f, 0.0f));

            else
                t->material_ = std::make_shared<Diffuse>(glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0, 0, 0));

            primitives_.push_back(Primitive::PrimitiveUniquePtr(t));
        }
    }
}
