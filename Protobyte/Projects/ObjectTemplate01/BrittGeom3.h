#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#include <iostream>
#include <vector>
#include <memory>

#include "ProtoVector3.h"
#include "ProtoDimension3.h"

#include "ProtoVertex3.h"
#include "ProtoTuple3.h"
#include "ProtoFace3.h"


#include "ProtoColor4.h"

namespace ijg {
	class BrittGeom3 {
		
		friend class ProtoVerex3;
		
	public:
		BrittGeom3();
		~BrittGeom3();

	protected:
		void init();

		void clearVectors();

		virtual void calcVerts() = 0;
		virtual void calcInds() = 0;


		std::vector<ProtoVertex3> vertices;
		std::vector<ProtoTuple3<int>> indexes;

		std::vector<Col4f> color;


	private:
		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		void initializeGLEW();
		void initializeOpenGL();

	};
}
#endif