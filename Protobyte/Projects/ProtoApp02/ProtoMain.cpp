#include "ProtoPlasm.h"
#include "ProtoApp.h"

int main(int argc, char const** argv) {
		ijg::ProtoPlasm p(1200, 800, "ProtoApp", new ProtoApp());
		return EXIT_SUCCESS;
}