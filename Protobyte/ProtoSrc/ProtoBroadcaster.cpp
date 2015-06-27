#include "ProtoBroadcaster.h"

using namespace ijg;

ProtoBaseApp* ProtoBroadcaster::baseApp;

//cstr
ProtoBroadcaster::ProtoBroadcaster(ProtoBaseApp* baseApp) {
	ProtoBroadcaster::baseApp = baseApp;
}

void ProtoBroadcaster::setBaseApp(ProtoBaseApp* baseApp) {
	ProtoBroadcaster::baseApp = baseApp;
}


// non-member function returns main context

	ProtoBaseApp* ProtoBroadcaster::getBaseApp(){
		return ProtoBroadcaster::baseApp;
	}
