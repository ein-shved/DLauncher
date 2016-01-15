/**
 *  The xlib implementation.
 */

#ifndef _XLIB_HPP_
#define _XLIB_HPP_

#include "window.hpp"
#include <X11/Xlib.h>
#include <unordered_set>

namespace DLauncher {

class XWindow : public DLauncher::Window {
public:
    XWindow (::Display *display, XWindow *parent,
             const Rectangle &rect);
    ~XWindow();
    virtual int draw(const Rectangle &rect);
    virtual int draw(const Point &p);
    virtual int draw (bool hide = false);
    virtual int hide(bool hide = true);
    virtual Rectangle rect() const;
    virtual int text(const std::string &text);
    virtual int fill(const Color &color);
    virtual Color color() const;
    virtual bool visible() const;
    virtual bool same(const Window *other);
    ::Window window();

protected:
    XWindow(::Display *display, ::Window window);

private:
    ::Display *m_display;
    int m_default_screen;
    ::Window m_win;
};

class XRootWindow : public XWindow {
public:
    XRootWindow(::Display *display);
    virtual int draw(const Rectangle &rect);
    virtual int draw(const Point &p);
    virtual int draw (bool hide = false);
    virtual int hide(bool hide = true);
    virtual int text(const std::string &text);
    virtual int fill(const Color &color);
    virtual bool visible() const;
};

class XWindowFactory : public DLauncher::WindowFactory {
public:
    XWindowFactory (const char *display_name = NULL);
    ~XWindowFactory ();
    virtual DLauncher::Window *create(DLauncher::Window *parent,
                                      const Rectangle &rect);
    virtual DLauncher::Window *create(DLauncher::Window *base);
    virtual int set_main_window(DLauncher::Window *window);
    virtual DLauncher::Window *get_root();
    void event_loop();

private:
    Display *m_display;
    XWindow *m_main;
};
}

#endif /* xlib.hpp */
