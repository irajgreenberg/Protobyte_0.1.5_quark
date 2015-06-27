/*!  \brief  ProtoBroadcaster.h: Broadcasts ProtoBaseApp
ProtoBroadcaster.h
Protobyte Library v02

Created by Ira on 6/27/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTO_BROADCASTER_H
#define PROTO_BROADCASTER_H

#include "ProtobaseApp.h"


namespace ijg {
	
	class ProtoBroadcaster {

	public:
		static ProtoBaseApp* baseApp;
		
		
		//cstr
		ProtoBroadcaster(ProtoBaseApp* baseApp);
			
		void setBaseApp(ProtoBaseApp* baseApp);
		static ProtoBaseApp* getBaseApp();

	};

}

#endif //PROTO_BROADCASTER_H