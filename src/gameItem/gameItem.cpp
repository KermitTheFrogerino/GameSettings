#include "gameItem.hpp"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../dialogItem/dialogItemType.hpp"

using namespace std;

GameItem::GameItem(Game game,
                   Gtk::Window *window,
                   string steamID,
                   bool(onClick)(GdkEventButton *, Game, Gtk::Window *, string)) {
    Gtk::manage(this);
    label.set_label(game.name.c_str());
    eventBox.add(box);
    box.pack_start(label, Gtk::PACK_START, 5);
    eventBox.signal_button_press_event().connect(sigc::bind<GameItem::Game, Gtk::Window *, string>(
      sigc::ptr_fun(onClick), game, window, steamID));
    add(eventBox);
}
