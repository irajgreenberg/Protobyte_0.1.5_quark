#ifndef TEST_SHAPE_H
#define	TEST_SHAPE_H

#include <iostream>
#include "TestGeom.h"

namespace ijg {

	class TestShape : public TestGeom {
	public:
		friend std::ostream& operator<<(std::ostream& out, const TestShape& block);

		/*!
		* Default Constructor */
		TestShape();
		/*!
		* Constructor */
		TestShape(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const ProtoColor4<float>& col4);
		/*!
		* Constructor */
		TestShape(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		TestShape(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<Col4f>& cols4);
		/*!
		* Constructor */
		TestShape(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));


		void calcVerts();

		void calcInds();


	};
}

#endif

