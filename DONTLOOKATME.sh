#!/bin/bash
# sudo pip install PyVDF;
printf '\E[H\E[3J'
clear
gcc -o gameSettings.out main.cpp \
    -std=c++20 -lstdc++ \
    $(pkg-config gtkmm-3.0 --cflags --libs)
./gameSettings.out
# sleep 0.5
# i3-msg "[id=$(xdotool getactivewindow)] floating enable"
