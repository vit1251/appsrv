#!/bin/bash

. ~/.profile

meson setup builddir
meson compile -C builddir
