#include "ProtoRatio3.h"

namespace ijg {
	std::ostream& operator<<(std::ostream& out, const ProtoRatio3& rat) {
		out << "elem0: " << rat.elem0 << ", " 
			<< "elem1: " << rat.elem1 << ", "
			<< "elem2: " << rat.elem2 << ", "
			<< "unit: " << rat.unit << std::endl
			<< "sample size: " << rat.sampleSize << ", "
			<< "elem0 sample: " << rat.elemSample0 << ", "
			<< "elem1 sample: " << rat.elemSample1 << ", "
			<< "elem2 sample: " << rat.elemSample2;
		return out;
	}
}

using namespace ijg;

ProtoRatio3::ProtoRatio3() :
ProtoTuple3i(), sampleSize(1) {
	elem0 = 1;
	elem1 = 1;
	elem2 = 1;
	setUnit();
	calculateElemSamples();
}

ProtoRatio3::ProtoRatio3(int elem0, int elem1, int elem2, int sampleSize) :
ProtoTuple3i(elem0, elem1, elem2), sampleSize(sampleSize) {
	setUnit();
	calculateElemSamples();
}

void ProtoRatio3::setUnit() {
	int total = elem0 + elem1 + elem2;
	unit = (1.00 / total);
}

void ProtoRatio3::calculateElemSamples() {
	elemSample0 = (unit * sampleSize * elem0);
	elemSample1 = (unit * sampleSize * elem1);
	elemSample2 = (unit * sampleSize * elem2);
}