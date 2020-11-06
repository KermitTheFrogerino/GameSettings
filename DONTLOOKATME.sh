#!/bin/bash
# sudo pip install PyVDF;
printf '\E[H\E[3J'
clear
g++ -o gameSettings.out main.cpp \
    -std=c++20 \
    $(pkg-config gtkmm-3.0 --cflags json-glib-1.0 --libs) \
    -lcurl -ljson-glib-1.0
./gameSettings.out
# sleep 0.5
# i3-msg "[id=$(xdotool getactivewindow)] floating enable"
