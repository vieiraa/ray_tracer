#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "ray.h"
#include "intersection_record.h"

class Primitive
{
public:
#if __cplusplus < 201103L
    typedef Primitive* PrimitiveUniquePtr;
#else
    typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;
#endif

    Primitive( void );

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;
};

#endif /* PRIMITIVE_H_ */

