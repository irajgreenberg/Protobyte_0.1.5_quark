#include "ProtoPlasm.h"
#include "ProtoController.h"

int main(int argc, char const** argv) {
		ijg::ProtoPlasm p(600, 600, "ProtoController", new ProtoController());
		return EXIT_SUCCESS;
}