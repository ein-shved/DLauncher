/**
 *  The interface of window.
 */

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>

namespace DLauncher {

struct Point {
    int x, y;

    Point (int x = 0, int y = 0);
    Point (const Point &other);
    Point & operator = (int p);
};
struct Rectangle {
    Point p;
    unsigned int height, width;

    Rectangle (int x = 0, int y = 0,
               int height = 0,
               int width = 0);
    Rectangle(const Rectangle &other);
    Rectangle &operator = (int l);
    Rectangle &operator = (const Point &other); /* Move to */
    Rectangle operator + (int l) const;
};

struct Color {
    int a : 8, r : 8, g : 8, b : 8;
    Color (int r, int g, int b, int a = 0);
    Color (int c = 0);
    Color (const std::string &str);

    static const Color &black();
    static const Color &red();
    static const Color &green();
    static const Color &blue();
    static const Color &white();

    Color & operator = (int c);
    operator int () const {
        return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) +
                ((b & 0xff) << 0);
    };
    void set (int r, int g, int b, int a = 0);
};

class Window {
public:
    virtual ~Window();
    virtual int draw(const Rectangle &rect) = 0;
    virtual int draw(const Point &p) = 0; /* Move to */
    virtual int draw (bool hide = false) = 0;
    virtual int hide(bool hide = true) = 0;
    virtual Rectangle rect() const = 0;
    virtual int text(const std::string &text) = 0;
    virtual int fill(const Color &color) = 0;
    virtual Color color() const = 0;
    virtual bool visible() const = 0;
    virtual bool same(const Window *other) = 0;
};

class WindowFactory {
public:
    virtual ~WindowFactory();
    virtual Window *create(Window *parent, const Rectangle &rect) = 0;
    virtual Window *create(Window *base) = 0;
    virtual Window *get_root() = 0;
    virtual int set_main_window(Window *window) = 0;
};

}

#endif /* window.hpp */
