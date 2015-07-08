#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>

#include "ProtoMath.h"
#include "ProtoCore.h"
#include "ProtoUtility.h"

#include "ProtoVector3.h"
#include "ProtoDimension3.h"
#include "ProtoTuple4.h"
#include "ProtoMatrix3.h"
#include "ProtoMatrix4.h"

#include "ProtoColor4.h"

#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace blw {
	class BrittGeom3 {
	public:
		friend std::ostream& operator <<(std::ostream& out, const BrittGeom3& geom);

		enum RenderMode {
			bPOINTS,
			bWIREFRAME,
			bSURFACE
		};

		BrittGeom3();

		virtual ~BrittGeom3();

	protected:


	private:


	};
}

#endif