# About

DLauncher was inspired by [dmenu](http://tools.suckless.org/dmenu/) and
consider to replace it as launcher for me.
There are several shortcomings in dmenu, I wish to resolve here:
* Sometimes dmenu takes too much time to start (sometimes to a minute) even on
  very powerful machine.
  This will be resolved by running DLauncher as a daemon.
* The completion of dmenu complete only the first word of command. Here
  DLauncher will use the readline library.
* I didn't manage to make dmenu to remember the history in a good manner. The
  readline will help me here too.
* dmenu supports only X. For a years I dreamed to switch to wayland, but
  different things always blocks me. But now I fill - I'm ready.

# Architecture

I contributes sometimes to dwm, but I can't fully accept (or maybe understand)
the suckless philosophy.
So it DLauncher is not suckless, but I hope it will be simple, laconic and
powerful.
I started it as a hobby and it won't pretend to be widespread or even usable,
so do not judge strict. The main aim for me is to try the wayland from the
client part.

DLaunchers written on C++. The main part is a launcher class itself.
It is responsible for a base logic.
The other one is a Window interface, the mission of which is to encapsulate the
graphics protocol details.
And the Xlib implementation of Window interface and Wayland (in future).

# Compiling

Run ``autoreconf`` to generate configure script, then configure project with
it, and ``make``.

# Running

Just run ``dlauncher`` binary.

# dlauncher

I found more others projects with the same name, but there is
[one](https://github.com/xinhaoyuan/dlauncher)
with the same aims. I think, I will use it if my won't be succeed.
