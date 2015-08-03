#ifndef __PROTORATIO_H__
#define __PROTORATIO_H__


#include <iostream>
#include "ProtoTuple2.h"

namespace ijg {

	class ProtoRatio2 : private ProtoTuple2i {
	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoRatio2& rat);

		ProtoRatio2();
		ProtoRatio2(int elem0, int elem1, int sampleSize = 1);

		int getElem0() const;
		int getElem1() const;
		int getSampleSize() const;
		float getUnit() const;
		float getElemSample0() const;
		float getElemSample1() const;

		void setElem0(int value);
		void setElem1(int value);
		void setSampleSize(int size);

	private:
		int sampleSize;
		float unit;

		float elemSample0, elemSample1;
		
		void setUnit();
		void calculateElemSamples();

	};

	inline int ProtoRatio2::getElem0() const {
		return elem0;
	}
	
	inline int ProtoRatio2::getElem1() const {
		return elem1;
	}

	inline int ProtoRatio2::getSampleSize() const {
		return sampleSize;
	}
	
	inline float ProtoRatio2::getUnit() const {
		return unit;
	}

	inline float ProtoRatio2::getElemSample0() const {
		return elemSample0;
	}

	inline float ProtoRatio2::getElemSample1() const {
		return elemSample1;
	}

	inline void ProtoRatio2::setElem0(int value) {
		elem0 = value;
		setUnit();
	}

	inline void ProtoRatio2::setElem1(int value) {
		elem1 = value;
		setUnit();
	}

	inline void ProtoRatio2::setSampleSize(int size) {
		sampleSize = size;
		calculateElemSamples();
	}
}

#endif //__PROTORATIO_H__