
#include "window.hpp"

#include <stdexcept>
#include <sstream>

using namespace DLauncher;
using namespace std;

Point::Point(int in_x, int in_y)
        : x(in_x)
        , y(in_y)
{};
Point::Point (const Point &other)
    : x(other.x)
    , y(other.y)
{}
Point & Point::operator = (int p)
{
    x = y = p;
    return *this;
}

Rectangle::Rectangle (int x, int y, int in_height, int in_width)
    : p(x, y)
    , height(in_height)
    , width(in_width)
{}
Rectangle::Rectangle(const Rectangle &other)
    : p(other.p)
    , height(other.height)
    , width(other.width)
{}
Rectangle & Rectangle::operator = (int l)
{
    height = width = l;
    return *this;
}
Rectangle &Rectangle::operator = (const Point &other)
{
    p = other;
}
Rectangle Rectangle::operator + (int l) const {
    Rectangle res(*this);
    res.height += l;
    res.width += l;
    return res;
}

Color::Color (int in_r, int in_g, int in_b, int in_a)
        : a(in_a)
        , r(in_r)
        , g(in_g)
        , b(in_b)
{}
Color::Color (int c)
    : a ((c >> 24) & 0xff)
    , r ((c >> 16) & 0xff)
    , g ((c >>  8) & 0xff)
    , b ((c >>  0) & 0xff)
{}
Color::Color (const std::string &str)
{
    int c;
    int r,g,b,a;
#define STR_TO_COLOR(col)       \
    if (str == #col) {          \
        *this = col();          \
        return;                 \
    } else
    STR_TO_COLOR(black)
    STR_TO_COLOR(red)
    STR_TO_COLOR(green)
    STR_TO_COLOR(blue)
    STR_TO_COLOR(white)

    if (sscanf(str.c_str(),"%3d:%3d:%3d:%3d",a,r,g,b) == 4) {
        set(r,g,b,a);
    } else
    if (sscanf(str.c_str(),"%3d:%3d:%3d",r,g,b) == 4) {
        set(r,g,b);
    } else
    if(stringstream(str) >> c) {
        *this = c;
        return;
    } else {
        throw runtime_error("Can not convert string to color");
    }
#undef STR_TO_COLOR
}
const Color &Color::black(){
    static Color result(0,0,0);
    return result;
}
const Color &Color::red(){
    static Color result(255,0,0);
    return result;
}
const Color &Color::green(){
    static Color result(0,255,0);
    return result;
}
const Color &Color::blue(){
    static Color result(0,0,255);
    return result;
}
const Color &Color::white(){
    static Color result(255,255,255);
    return result;
}
Color & Color::operator = (int c)
{
    *this = Color(c);
}
void Color::set(int r, int g, int b, int a)
{
    *this = Color(r,g,b,a);
}
Window::~Window()
{}
WindowFactory::~WindowFactory()
{}
