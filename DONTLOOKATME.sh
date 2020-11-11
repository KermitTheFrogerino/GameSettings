#!/bin/bash
# sudo pip install PyVDF;
printf '\033[2J\033[3J\033[1;1H'
clear
gcc -o gameSettings.out main.cpp \
    -std=c++20 -lstdc++ \
    $(pkg-config gtkmm-3.0 --cflags --libs)
./gameSettings.out
# sleep 0.5
# i3-msg "[id=$(xdotool getactivewindow)] floating enable"
