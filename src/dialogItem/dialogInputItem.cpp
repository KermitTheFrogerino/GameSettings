#include "dialogInputItem.hpp"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.hpp"
#include "dialogItemType.hpp"

using namespace std;

// Switch Item
DialogInputItem::DialogInputItem(string title) {
    Gtk::manage(this);

    label.set_label(title);
    label.set_halign(Gtk::ALIGN_START);
    add(box);
    box.set_margin_bottom(margin);
    box.set_margin_top(margin);
    box.set_margin_start(margin);
    box.set_margin_end(margin);
    box.pack_start(label);
    box.pack_end(entry);
}

string DialogInputItem::getEntryText() { return entry.get_text(); }

void DialogInputItem::setEntryText(const string text) { entry.set_text(text); }

void DialogInputItem::insertEntryText(const string text, int textLength, int position) {
    entry.insert_text(text, textLength, position);
}
