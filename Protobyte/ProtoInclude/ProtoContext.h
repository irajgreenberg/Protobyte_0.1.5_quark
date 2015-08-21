/*!  \brief  ProtoContext.h: encapsulates static tranformation matrix/functions
ProtoContext.h
Protobyte Library

Copyright (c) 2015 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained in any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef __PROTO_CONTEXT_H__
#define __PROTO_CONTEXT_H__

#include <iostream>
#include <memory>



namespace ijg {

	class ProtoContext {

	private:
		ProtoContext() {}
		static std::unique_ptr<ProtoContext> ctx;

	public:
		static const ProtoContext& getContext();
	};
}

#endif // __PROTO_CONTEXT_H__
