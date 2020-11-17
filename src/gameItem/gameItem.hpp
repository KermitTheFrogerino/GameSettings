#include <gtkmm.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../dialogItem/dialogItemType.hpp"

#ifndef SRC_GAMEITEM_GAMEITEM_HPP_
#define SRC_GAMEITEM_GAMEITEM_HPP_

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
             bool(onClick)(GdkEventButton *, Game, Gtk::Window *, string));
};
#endif  // SRC_GAMEITEM_GAMEITEM_HPP_
