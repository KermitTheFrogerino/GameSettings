#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.h"
#include "dialogItemType.h"

using namespace std;

#ifndef DIALOGITEM_DIALOGINPUTITEM_H_
#define DIALOGITEM_DIALOGINPUTITEM_H_

class DialogInputItem : public Gtk::ListBoxRow {
 private:
    Gtk::Box box;
    Gtk::Label label;
    Gtk::Entry entry;

    int const margin = 8;

 public:
    // Switch Item
    explicit DialogInputItem(string title) {
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

    string getEntryText() { return entry.get_text(); }

    void setEntryText(const string text) { entry.set_text(text); }

    void insertEntryText(const string text, int textLength, int position) {
        entry.insert_text(text, textLength, position);
    }
};
#endif  // DIALOGITEM_DIALOGINPUTITEM_H_
