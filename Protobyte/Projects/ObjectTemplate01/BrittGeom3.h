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

namespace ijg {
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

		//for getters and setters - should Vec3f attributes be
		//separated into compontents (x, y, z)?

		//GETTERS:
		virtual Vec3f getPos() const;
		virtual Vec3f getRot() const;
		virtual Dim3f getSize() const;
		//should color be returned as vector and single color
		//or just as single color?
		virtual std::vector<ProtoColor4f> getColor() const;
		virtual ProtoColor4f getColorAt(int position) const;
		virtual Vec3f getSpd() const;
		virtual Vec3f getRotSpd() const;

		//SETTERS:
		virtual void setPos(const Vec3f& newPos);
		virtual void setRot(const Vec3f& newRot);
		virtual void setSize(const Dim3f& newSize);
		//vector or single color?
		virtual void setColor(const std::vector<ProtoColor4f>& newColors);
		virtual void setColorAt(int position, const ProtoColor4f& newColor);
		virtual void setSpd(const Vec3f& newSpd);
		virtual void setRotSpd(const Vec3f& newRotSpd);

	protected:
		Vec3f pos, rot;
		Dim3f size;
		//removed single color component - vector only
		std::vector<ProtoColor4f> color;
		//necessary? - move and rotate functions in future?
		Vec3f spd, rotSpd;


	private:


	};
}

#endif