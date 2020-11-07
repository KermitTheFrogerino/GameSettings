#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.h"
#include "dialogItemType.h"

using namespace std;

#ifndef DIALOGITEM_DIALOGITEM_H_
#define DIALOGITEM_DIALOGITEM_H_

class DialogItem : public Gtk::ListBoxRow {
 private:
    Gtk::Box box;
    Gtk::EventBox eventBox;
    Gtk::Label label;
    Gtk::Switch switchWidget;

    int const margin = 8;

 public:
    // Switch Item
    explicit DialogItem(GameItem::GameSetting gameSetting, bool enabled = false) {
        Gtk::manage(this);

        switchWidget.set_state(enabled);

        label.set_label(gameSetting.getName());
        label.set_hexpand(true);
        label.set_halign(Gtk::ALIGN_START);
        eventBox.add(box);
        box.set_margin_bottom(margin);
        box.set_margin_top(margin);
        box.set_margin_start(margin);
        box.set_margin_end(margin);
        box.add(label);
        box.add(switchWidget);
        add(eventBox);
    }
};
#endif  // DIALOGITEM_DIALOGITEM_H_
