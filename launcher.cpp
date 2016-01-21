/**
 *  Base file of launcher.
 */

#include "launcher.hpp"

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;
using namespace DLauncher;

Launcher::Config Launcher::s_default_config =
    Launcher::generate_default_config();

Launcher::Launcher(WindowFactory &factory, const Config &config)
    : m_factory(factory)
    , m_config(config)
{
    m_root = m_factory.get_root();
    if (m_root == NULL) {
        throw runtime_error("Can not retrieve root window");
    }
    m_main = m_factory.create(m_root);
}

void Launcher::configure(const Config &config)
{
    m_config = config;
}
Launcher::~Launcher()
{
    m_factory.set_main_window(NULL);
    delete m_root;
    delete m_main;
}

void Launcher::focus(Window *window, bool loose)
{
    if (window->same(m_main)) {
        return;
    }
}
void Launcher::launch()
{
    m_factory.set_main_window(m_main);
    m_main->fill(config("color"));
    m_main->draw(calc_main_space());
    m_main->draw();
}
void Launcher::exec(const std::string &cmd)
{
    /* TODO */
}
void Launcher::exec()
{
    exec(m_text);
}
Rectangle Launcher::calc_main_space()
{
    const string &pos = config("pos");
    int height = iconfig("height", 10);
    Rectangle r = m_root->rect();
    Point p;

    if (pos != "bottom") {
        p = Point(0, 0);
    } else {
        p = Point(0, r.height - height);
    }
    r.p = p;
    r.height = height;

    return r;
}

const std::string &Launcher::input() const
{
    return m_text;
}

void Launcher::input (const std::string &string)
{
    m_text = string;
}
void Launcher::complete ()
{
    /* TODO */
}

const std::string &Launcher::config (const std::string &param)
{
    if (m_config.find(param) == m_config.end()) {
        return s_default_config[param];
    } else {
        return m_config[param];
    }
}
int Launcher::iconfig (const std::string &param, int def)
{
    stringstream conf (config(param));
    int result;

    if (!(conf >> result)) {
        return def;
    }
    return result;
}
const Launcher::Config Launcher::generate_default_config()
{
    Config res;
    res["pos"] = "top";
    res["height"] = "10";
    res["color"] = "black";
    res["select"] = "green";

    return res;
}
