#ifndef __BrittCube__Protobyte__
#define __BrittCube__Protobyte__

#include <iostream>
#include "BrittGeom3.h"

namespace ijg {

	class BrittCube : public BrittGeom3 {

	public:
		BrittCube();

		void calcVerts();
		void calcInds();

	};

}

#endif