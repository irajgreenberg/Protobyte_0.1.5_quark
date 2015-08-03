#ifndef __PROTORATIO_H__
#define __PROTORATIO_H__


#include <iostream>
#include "ProtoTuple2.h"

namespace ijg {

	class ProtoRatio2 : private ProtoTuple2i {
	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoRatio2& rat);

		ProtoRatio2();
		ProtoRatio2(int elem0, int elem1);

		int getElem0() const;
		int getElem1() const;
		float getUnit() const;

		void setElem0(int value);
		void setElem1(int value);

	private:
		enum UnitType {
			TOTAL,
			FRACTION
		};

		float unit;
		
		void setUnit(UnitType type = TOTAL);

	};

	inline int ProtoRatio2::getElem0() const {
		return elem0;
	}
	
	inline int ProtoRatio2::getElem1() const {
		return elem1;
	}

	inline float ProtoRatio2::getUnit() const {
		return unit;
	}

	inline void ProtoRatio2::setElem0(int value) {
		elem0 = value;
		setUnit();
	}

	inline void ProtoRatio2::setElem1(int value) {
		elem1 = value;
		setUnit();
	}
}

#endif //__PROTORATIO_H__