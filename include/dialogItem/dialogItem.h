#include <gtkmm.h>
#include <iostream>
#include <string>

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
    enum ItemType { two, multiple, input };

    class DialogModel {
     private:
        string title;
        ItemType itemType;

     public:
        DialogModel(string title, ItemType itemType) {
            this->title = title;
            this->itemType = itemType;
        }

        string getTitle() { return title; }

        ItemType getItemType() { return itemType; }
    };

    explicit DialogItem(DialogItem::DialogModel dialogModel) {
        Gtk::manage(this);
        label.set_label(dialogModel.getTitle());
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
