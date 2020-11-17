#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.hpp"
#include "dialogItemType.hpp"

using namespace std;

#ifndef SRC_DIALOGITEM_DIALOGITEM_HPP_
#define SRC_DIALOGITEM_DIALOGITEM_HPP_

class DialogItem : public Gtk::ListBoxRow {
 private:
    Gtk::Box box;
    Gtk::Label label;
    Gtk::Switch switchWidget;
    GameItem::GameSetting gameSettings;

    int const margin = 8;

 public:
    // Switch Item
    explicit DialogItem(GameItem::GameSetting gameSettings, bool enabled = false);

    bool getSwitchState();
};
#endif  // SRC_DIALOGITEM_DIALOGITEM_HPP_
