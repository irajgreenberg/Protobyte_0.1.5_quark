#ifndef __TestBlock__Protobyte__
#define	__TestBlock__Protobyte__

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {

	class TestBlock : public ProtoGeom3 {
	public:
		friend std::ostream& operator<<(std::ostream& out, const TestBlock& TestBlock);

		TestBlock();

		//default constructor place holder
		TestBlock(std::string name);

		TestBlock(const ProtoColor4f& col4);

		TestBlock(const std::vector<Col4f> col4s);

		TestBlock(const std::string& diffuseMapImage, const Vec2f& textureScale);

		TestBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size);

		TestBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
			const ProtoColor4<float>& col4);

		TestBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<Col4f>& cols4);

		void calcVerts();
		void calcInds();

		void setColorAt(int position, const ProtoColor4f& newColor);
		ProtoColor4f getColorAt(int position) const;
	};

	inline void TestBlock::setColorAt(int position, const ProtoColor4f& newColor) {
		int max = col4s.size() - 1;
		if (position < 0) {
			position = 0;
		}
		else if (position > max) {
			position = max;
		}
		col4s[position] = newColor;
	}

	inline ProtoColor4f TestBlock::getColorAt(int position) const {
		int max = col4s.size() - 1;
		if (position < 0) {
			position = 0;
		}
		else if (position > max) {
			position = max;
		}
		return col4s[position];
	}

}

#endif