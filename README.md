poorwm
======

PoorWM is a hostile fullscreen window manager for X11.

This project begins after finding TinyWM by Nick Welch
(http://incise.org/tinywm.html), whose 50 lines of code
were quickly studied, then modified to remove excess
features and implement window switching.


Features
========
- Fullscreen windows
- Window switching by pressing Alt+Tab
- No window borders
- No maximize / minimize / close user interaction
- No window dragging / moving 
- No visual hints of any kind
- Small enough code base


Building poorwm
===============
- make
- sudo make install


Known bugs
==========
- New windows are not immediately forced to fullscreen, but
  will behave themselves after reaching them via Alt+Tabbing.
