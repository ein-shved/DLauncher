/**
 *  Base class of launcher.
 */

#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include <window.hpp>
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
    void focus(Window *window, bool loose);
    void launch();
    void exec(const std::string &cmd);
    void exec();
    Rectangle calc_main_space();

    const std::string &input() const;
    void input (const std::string &string);
    void complete ();

    const std::string &config (const std::string &param);
    int iconfig(const std::string &param, int def = 0);

private:
    static const Config generate_default_config();

private:
    WindowFactory &m_factory;
    Window *m_root;
    Window *m_main;
    Config m_config;

    std::string m_text;

    static Config s_default_config;
};

}

#endif /* launcher.hpp */
