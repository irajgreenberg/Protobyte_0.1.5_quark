#include "ProtoRatio2.h"

namespace ijg {
	std::ostream& operator<<(std::ostream& out, const ProtoRatio2& rat) {
		out << "elem0: " << rat.elem0 << ", " << "elem1: " << rat.elem1 
			<< ", " << "unit: " << rat.unit << std::endl;
		return out;
	}
}

using namespace ijg;

ProtoRatio2::ProtoRatio2() :
ProtoTuple2() {
	elem0 = 1;
	elem1 = 1;
	setUnit();
}

ProtoRatio2::ProtoRatio2(int elem0, int elem1):
ProtoTuple2i(elem0, elem1) {
	setUnit();
}

void ProtoRatio2::setUnit(UnitType type) {
	int total = 0;
	switch (type)
	{
	case ijg::ProtoRatio2::TOTAL:
		total = elem0 + elem1;
		unit = (1.00 / total);
		break;
	case ijg::ProtoRatio2::FRACTION:
		unit = 1.00;
		break;
	default:
		unit = 1.00;
		break;
	}
}