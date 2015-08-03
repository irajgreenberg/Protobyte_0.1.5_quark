#ifndef __PROTORATIO3_H__
#define __PROTORATIO3_H__

#include <iostream>
#include "ProtoTuple3.h"
#include "ProtoRatio2.h"

namespace ijg {

	class ProtoRatio3;
	typedef ProtoRatio3 Ratio3;

	class ProtoRatio3 : private ProtoTuple3i {
	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoRatio3& rat);

		ProtoRatio3();
		ProtoRatio3(int elem0, int elem1, int elem2, int sampleSize = 1);

		int getElem0() const;
		int getElem1() const;
		int getElem2() const;
		int getSampleSize() const;
		float getUnit() const;
		float getElemSample0() const;
		float getElemSample1() const;
		float getElemSample2() const;

		void setElem0(int value);
		void setElem1(int value);
		void setElem2(int value);
		void setSampleSize(int size);

	private:
		float unit;

		int sampleSize;
		float elemSample0, elemSample1, elemSample2;

		//possible "sub-ratios"
		//ProtoRatio2 ratio0, ratio1, ratio2;

		void setUnit();
		void calculateElemSamples();
	};
	inline int ProtoRatio3::getElem0() const {
		return elem0;
	}

	inline int ProtoRatio3::getElem1() const {
		return elem1;
	}

	inline int ProtoRatio3::getElem2() const {
		return elem2;
	}

	inline int ProtoRatio3::getSampleSize() const {
		return sampleSize;
	}

	inline float ProtoRatio3::getUnit() const {
		return unit;
	}

	inline float ProtoRatio3::getElemSample0() const {
		return elemSample0;
	}

	inline float ProtoRatio3::getElemSample1() const {
		return elemSample1;
	}

	inline float ProtoRatio3::getElemSample2() const {
		return elemSample2;
	}

	inline void ProtoRatio3::setElem0(int value) {
		elem0 = value;
		setUnit();
		calculateElemSamples();
	}

	inline void ProtoRatio3::setElem1(int value) {
		elem1 = value;
		setUnit();
		calculateElemSamples();
	}

	inline void ProtoRatio3::setElem2(int value) {
		elem2 = value;
		setUnit();
		calculateElemSamples();
	}

	inline void ProtoRatio3::setSampleSize(int size) {
		sampleSize = size;
		calculateElemSamples();
	}
}

#endif //__PROTORATIO3_H__