#include <systemc>

#include "top.hpp"

int sc_main(int argc, char *argv[])
{
	Top top("top");
	sc_core::sc_start();

	return 0;
}
