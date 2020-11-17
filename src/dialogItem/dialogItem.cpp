#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.hpp"
#include "dialogItem.hpp"
#include "dialogItemType.hpp"

using namespace std;

DialogItem::DialogItem(GameItem::GameSetting gameSettings, bool enabled) {
    this->gameSettings = gameSettings;
    Gtk::manage(this);

    switchWidget.set_state(enabled);

    label.set_label(gameSettings.name);
    label.set_hexpand(true);
    label.set_halign(Gtk::ALIGN_START);
    add(box);
    box.set_margin_bottom(margin);
    box.set_margin_top(margin);
    box.set_margin_start(margin);
    box.set_margin_end(margin);
    box.add(label);
    box.add(switchWidget);
}

bool DialogItem::getSwitchState() { return switchWidget.get_state(); }
