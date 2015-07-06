#ifndef __BrittCube__Protobyte__
#define __BrittCube__Protobyte__

#include "BrittGeom3.h"

namespace ijg {
	class BrittCube : public BrittGeom3 {

	public:
		BrittCube();

		void calcVerts();
		void calcInds();

	private:
		//added default color
		Col4f defaultColor = Col4f(0.5, 0.5, 0.5, 1);
	};
}
#endif