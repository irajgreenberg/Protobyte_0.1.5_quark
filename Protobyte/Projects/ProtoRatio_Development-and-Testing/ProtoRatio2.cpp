#include "ProtoRatio2.h"

namespace ijg {
	std::ostream& operator<<(std::ostream& out, const ProtoRatio2& rat) {
		out << "elem0: " << rat.elem0 << ", " << "elem1: " << rat.elem1
			<< ", " << "unit: " << rat.unit << std::endl
			<< "sample size: " << rat.sampleSize << ", "
			<< "elem0 sample: " << rat.elemSample0 << ", "
			<< "elem1 sample: " << rat.elemSample1;
		return out;
	}
}

using namespace ijg;

ProtoRatio2::ProtoRatio2() :
ProtoTuple2(), sampleSize(1) {
	elem0 = 1;
	elem1 = 1;
	setUnit();
	calculateElemSamples();
}

ProtoRatio2::ProtoRatio2(int elem0, int elem1, int sampleSize):
ProtoTuple2i(elem0, elem1), sampleSize(sampleSize) {
	setUnit();
	calculateElemSamples();
}

void ProtoRatio2::setUnit() {
	int total = elem0 + elem1;
	unit = (1.00 / total);
}

void ProtoRatio2::calculateElemSamples() {
	elemSample0 = (unit * elem0 * sampleSize);
	elemSample1 = (unit * elem1 * sampleSize);
}