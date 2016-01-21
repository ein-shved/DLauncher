#include "xlib.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace DLauncher;

XWindowFactory::XKeyHandler::XKeyHandler (DLauncher::Launcher &launcher,
                                          ::Display *display,
                                          ::Window win)
    : m_launcher(launcher)
{
    XIM xim = XOpenIM(display, NULL, NULL, NULL);
	m_xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
	                  XNClientWindow, win, XNFocusWindow, win, NULL);
}

void XWindowFactory::XKeyHandler::operator()(XKeyEvent *ev)
{
	char buf[32];
	int len;
	KeySym ksym = NoSymbol;
	Status status;

	len = XmbLookupString(m_xic, ev, buf, sizeof buf, &ksym, &status);

	if(status == XBufferOverflow)
		return;
	if(ev->state & ControlMask) {
        if(control_mask(ev, ksym)) {
            return;
        }
    } else if(ev->state & Mod1Mask) {
        if(mod_1_mask(ev, ksym)) {
            return;
        }
    }
    process(ev, ksym);
    return;
}
bool XWindowFactory::XKeyHandler::control_mask(XKeyEvent *ev, KeySym &ksym)
{
    return false;
}
bool XWindowFactory::XKeyHandler::mod_1_mask(XKeyEvent *ev, KeySym &ksym)
{
    return false;
}
bool XWindowFactory::XKeyHandler::process(XKeyEvent *ev, KeySym &ksym)
{
    return false;
}
