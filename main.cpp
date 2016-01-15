#include "launcher.hpp"
#include "xlib.hpp"

#include <unistd.h>

using namespace DLauncher;
using namespace std;

int main ()
{
    XWindowFactory factory;
    Launcher l(factory);
    l.launch();
    factory.event_loop();
}
