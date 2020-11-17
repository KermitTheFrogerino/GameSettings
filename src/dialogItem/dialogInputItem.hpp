#include <gtkmm.h>
#include <iostream>
#include <string>
#include "../gameItem/gameItem.hpp"
#include "dialogItemType.hpp"

using namespace std;

#ifndef SRC_DIALOGITEM_DIALOGINPUTITEM_HPP_
#define SRC_DIALOGITEM_DIALOGINPUTITEM_HPP_

class DialogInputItem : public Gtk::ListBoxRow {
 private:
    Gtk::Box box;
    Gtk::Label label;
    Gtk::Entry entry;

    int const margin = 8;

 public:
    // Switch Item
    explicit DialogInputItem(string title);

    string getEntryText();

    void setEntryText(const string text);

    void insertEntryText(const string text, int textLength, int position);
};
#endif  // SRC_DIALOGITEM_DIALOGINPUTITEM_HPP_
