#include "ProtoPlasm.h"
#include "ProtoController.h"

int main(int argc, char const** argv) {
		ijg::ProtoPlasm p(500, 500, "ProtoController", new ProtoController());
		return EXIT_SUCCESS;
}