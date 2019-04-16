#include "primitive.h"

class bvh {

public:
	
	struct bvhNode {

		~bvhNode(void) {
			if(left_) {
				delete left_;
				left_ = nullptr;
			}

			if (right_) {
				delete right_;
				right_ = nullptr;

			}
		}

		bvhNode *left_ = nullptr;
		bvhNode *right_ = nullptr;
		aabbBound bound_;
		std::size_t firstPrimitive;
		std::size_t totalPrimitives;
	};

	struct bvhPrimitiveInfo {
		aabbBound bounds_;
		std::size_t primitiveId_;
		glm::vec3 centroid_;
	
		aabbBound leftBound_;
		aabbBound rightBound_;

	};

	bvh(cons std::vector< Primitive::PrimitiveUniquePtr > &primitives);





};