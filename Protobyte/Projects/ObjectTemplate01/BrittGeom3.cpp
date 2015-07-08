#include "BrittGeom3.h"

namespace ijg {
	std::ostream& operator<<(std::ostream& out, const BrittGeom3& geom) {
		out << "Position: " << geom.pos << std::endl
			<< "Rotation: " << geom.rot << std::endl
			<< "Size: " << geom.size << std::endl
			<< "Speed: " << geom.spd << std::endl
			<< "Rotational Speed: " << geom.rotSpd << std::endl;
		return out;
	}
}

using namespace ijg;

BrittGeom3::BrittGeom3():
	pos(Vec3f(0, 0, 0)), rot(Vec3f(0, 0, 0)), size(Dim3f(1, 1, 1)), spd(Vec3f(0, 0, 0)), rotSpd(Vec3f(0, 0, 0)) {
	color.push_back(Col4f(0.2, 0.2, 0.2, 1));
}

BrittGeom3::~BrittGeom3() {

}