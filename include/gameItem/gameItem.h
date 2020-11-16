#include <gtkmm.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../dialogItem/dialogItemType.h"

#ifndef GAMEITEM_GAMEITEM_H_
#define GAMEITEM_GAMEITEM_H_

using namespace std;

class GameItem : public Gtk::ListBoxRow {
 private:
    Gtk::Label label;
    Gtk::Image image;
    Gtk::EventBox eventBox;
    Gtk::Box box;

 public:
    typedef struct {
        string appID;
        string name;
    } Game;

    typedef struct {
        string name;
        vector<pair<string, string>> settings;
        ItemType itemType;
    } GameSetting;

    GameItem(Game game,
             Gtk::Window *window,
             string steamID,
             bool(onClick)(GdkEventButton *, Game, Gtk::Window *, string)) {
        Gtk::manage(this);
        label.set_label(game.name.c_str());
        eventBox.add(box);
        box.pack_start(label, Gtk::PACK_START, 5);
        eventBox.signal_button_press_event().connect(
          sigc::bind<GameItem::Game, Gtk::Window *, string>(
            sigc::ptr_fun(onClick), game, window, steamID));
        add(eventBox);
    }
};
#endif  // GAMEITEM_GAMEITEM_H_
