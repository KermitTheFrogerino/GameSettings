#!/bin/bash
# sudo pip install PyVDF;
clear
g++ -o gameSettings.out main.cpp \
    $(pkg-config gtkmm-3.0 --cflags json-glib-1.0 --libs) \
    -lcurl -ljson-glib-1.0
./gameSettings.out
# sleep 0.5
# i3-msg "[id=$(xdotool getactivewindow)] floating enable"
