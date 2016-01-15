#include "xlib.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace DLauncher;

XWindow::XWindow (::Display *display,
                  XWindow *parent, const Rectangle &rect)
    : m_display(display)
    , m_default_screen(DefaultScreen(m_display))
    , m_win(XCreateSimpleWindow(display, parent->m_win, rect.p.x, rect.p.y,
                                rect.width, rect.height, 1,
                                BlackPixel(m_display, m_default_screen),
                                WhitePixel(m_display, m_default_screen)))
{}
XWindow::XWindow(::Display *display, ::Window window)
    : m_display(display)
    , m_win(window)
{}
XWindow::~XWindow()
{
    XDestroyWindow(m_display, m_win);
}
int XWindow::draw(const Rectangle &rect)
{
    XMoveResizeWindow(m_display, m_win, rect.p.x, rect.p.y, rect.width,
                      rect.height);
    return 0;
}
int XWindow::draw(const Point &p)
{
    XMoveWindow(m_display, m_win, p.x, p.y);
    return 0;
}
int XWindow::draw(bool hide)
{
    if (!hide) {
        XMapWindow(m_display, m_win);
    }
    return 0;
}
int XWindow::hide(bool hide)
{
    if (hide) {
        XUnmapWindow(m_display, m_win);
    }
    return 0;
}
Rectangle XWindow::rect() const
{
    Rectangle result;
    ::Window w;
    unsigned int b, d;

    XGetGeometry(m_display, m_win, &w, &result.p.x, &result.p.y,
                 &result.width, &result.height, &b, &d);
    return result;
}
int XWindow::text(const std::string &text)
{
    /* TODO */
    return 0;
}
int XWindow::fill(const Color &color)
{
    /* TODO */
    return 0;
}
Color XWindow::color() const
{
    /* TODO */
    return Color();
}
bool XWindow::visible() const
{
    /* TODO */
    return true;
}
bool XWindow::same(const Window *other)
{
    const XWindow *xw = dynamic_cast<const XWindow *>(other);
    if (xw == NULL) return false;
    return m_display == xw->m_display && m_win == xw->m_win;
}
::Window XWindow::window()
{
    return m_win;
}
DLauncher::XRootWindow::XRootWindow(::Display *display)
    : XWindow(display, ::XDefaultRootWindow(display))
{}
int DLauncher::XRootWindow::draw(const Rectangle &rect)
{
    return -1;
}
int DLauncher::XRootWindow::draw(const Point &p)
{
    return -1;
}
int DLauncher::XRootWindow::draw (bool hide)
{
    return -1;
}
int DLauncher::XRootWindow::hide(bool hide)
{
    return -1;
}
int DLauncher::XRootWindow::text(const std::string &text)
{
    return -1;
}
int DLauncher::XRootWindow::fill(const Color &color)
{
    return -1;
}
bool DLauncher::XRootWindow::visible() const
{
    return true;
}

XWindowFactory::XWindowFactory (const char *display_name)
    : m_display(XOpenDisplay(display_name))
    , m_main(NULL)
{
    if (m_display == NULL) {
        throw runtime_error("Can not connect to X display");
    }
}
XWindowFactory::~XWindowFactory ()
{
    XCloseDisplay(m_display);
}
DLauncher::Window *XWindowFactory::create(DLauncher::Window *parent,
                                          const Rectangle &rect)
{
    XWindow *xparent = dynamic_cast<XWindow *>(parent);

    if (xparent == NULL) return NULL;
    return new XWindow(m_display, xparent, rect);
}
DLauncher::Window *XWindowFactory::create(DLauncher::Window *parent)
{
    return create (parent, Rectangle() + 1);
}
int XWindowFactory::set_main_window(DLauncher::Window *window)
{
    if (window == NULL || window == m_main) {
        m_main = NULL;
        return 0;
    }
    m_main = dynamic_cast<XWindow *>(window);
    if (m_main == NULL) return -1;
    XSelectInput(m_display, m_main->window(), ExposureMask | KeyPressMask);
}
DLauncher::Window *XWindowFactory::get_root()
{
    return new DLauncher::XRootWindow(m_display);
}
void XWindowFactory::event_loop()
{
    XEvent e;
    int s = DefaultScreen(m_display);

    while (1) {
        XNextEvent(m_display, &e);
        if (e.type == Expose) {
        }
        if (e.type == KeyPress) {
            cout << "KEY!\n";
            break;
        }
    }
}
