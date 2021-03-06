Minetest Mapper C++
===================

A port of minetestmapper.py to C++ from https://github.com/celeron55/minetest/tree/master/util

Requirements
------------

* libgd
* sqlite3
* xxd binary

Compilation
-----------

::

    git clone git://github.com/mireq/minetest-mapper-cpp.git minetest-mapper-cpp
    cd minetest-mapper-cpp/
    cmake .
    make

Usage
-----

Binary `minetest_mapper` has two mandatory paremeters, `-i` (input world path)
and `-o` (output image path).

::

    ./minetest_mapper -i /home/user/.minetest/worlds/my_world/ -o /home/user/map.png


Parameters
^^^^^^^^^^

bgcolor:
    Background color of image, `--bgcolor #ffffff`

scalecolor:
    Color of scale, `--scalecolor #000000`

playercolor:
    Color of player indicators, `--playercolor #ff0000`

origincolor:
    Color of origin indicator, `--origincolor #ff0000`

drawscale:
    Draw tick marks, `--drawscale`

drawplayers:
    Draw player indicators, `--drawplayers`

draworigin:
    Draw origin indicator, `--draworigin`

geometry:
    Limit area to specific geometry, `--geometry -800:-800+1600+1600`

Customization of colors.txt
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Default `colors.txt` is included in binary. Color definitions can be redefined
using external `colors.txt` file.
