#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#include <iostream>
#include <vector>
#include <memory>

//#include "ProtoMath.h"
#include "ProtoVector3.h"
#include "ProtoDimension3.h"

#include "ProtoVertex3.h"
#include "ProtoTuple3.h"
#include "ProtoFace3.h"


#include "ProtoColor4.h"

namespace ijg {
	class BrittGeom3 {
	public:
		BrittGeom3();
		~BrittGeom3();

		void setPosition(const Vec3f& newPosition);
		//void setPositionX(float newPosX);
		//void setPositionY(float newPosY);
		//void setPositionZ(float newPosZ);
		void setSize(const Dim3f& newSize);
		void setRotation(const Vec3f& newRotation);

	protected:
		std::vector<ProtoVertex3> vertices;
		std::vector<ProtoTuple3<int>> indexes;

		Vec3f position, rotation;
		Dim3f size;
		std::vector<Col4f> color;


	private:



	};
}
#endif