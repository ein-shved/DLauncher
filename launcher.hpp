/**
 *  Base class of launcher.
 */

#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include <window.hpp>
#include <libinput.h>
#include <iterator>
#include <map>

namespace DLauncher {

class Launcher {
public:
    typedef std::map<std::string, std::string> Config;
public:
    Launcher (WindowFactory &factory, const Config &config = Config());
    ~Launcher();
    void configure(const Config &config);
    void key(const struct libinput_event_keyboard &event);
    void focus(Window *window, bool loose);
    void launch();
    void exec(std::iterator<std::input_iterator_tag, std::string> cmd);
    Rectangle calc_main_space();

private:
    const std::string &config (const std::string &param);
    int iconfig(const std::string &param, int def = 0);
    static const Config generate_default_config();

private:
    WindowFactory &m_factory;
    Window *m_root;
    Window *m_main;
    Config m_config;

    static Config s_default_config;
};

}

#endif /* launcher.hpp */
