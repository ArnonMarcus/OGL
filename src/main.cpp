#include "ogl/rnd/window_.h"
#include <cstdlib>

int main(void)
{
    ogl::rnd::Window window("Me", 1000, 1000);
    window.start();

	exit(EXIT_SUCCESS);
}