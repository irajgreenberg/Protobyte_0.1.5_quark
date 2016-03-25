#include "ProtoPlasm.h"
#include "ProtoController.h"

int main(int argc, char const** argv) {
		ijg::ProtoPlasm p(1000, 600, "ProtoController", new ProtoController());
		return EXIT_SUCCESS;
}