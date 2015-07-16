#ifndef __TestBlock__Protobyte__
#define	__TestBlock__Protobyte__

#include <iostream>
#include "TestGeom3.h"

namespace ijg {

	class TestBlock : public TestGeom3 {
	public:
		friend std::ostream& operator<<(std::ostream& out, const TestBlock& TestBlock);

		/*!
		* Default Constructor */
		TestBlock();
		/*!
		* Constructor */
		TestBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const ProtoColor4<float>& col4);
		/*!
		* Constructor */
		TestBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		TestBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<Col4f>& cols4);
		/*!
		* Constructor */
		TestBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));



		/*!
		* Declared pure virtual in GeomBase base class
		* and must be implemented in all derived classes.
		*
		* Generates all vertices.*/
		void calcVerts();


		/*!
		* Declared pure virtual in GeomBase base class
		* and must be implemented in all derived classes:
		*
		* Generates indices to group vertices to triangle faces.*/
		void calcInds();
	};
}

#endif