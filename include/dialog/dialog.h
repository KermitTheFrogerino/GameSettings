#include <gtkmm.h>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include "../dialogItem/dialogItem.h"
#include "../gameItem/gameItem.h"

using namespace std;

#ifndef DIALOG_DIALOG_H_
#define DIALOG_DIALOG_H_

class Dialog {
 private:
    Glib::RefPtr<Gtk::Builder> dialogBuilder;
    Gtk::Dialog *dialog;
    Gtk::Window *window;
    GameItem::Game game;
    Gtk::ListBox *listBox;
    Gtk::HeaderBar headerBar = Gtk::HeaderBar();
    map<string, DialogItem::ItemType> itemsList = {
      {"Esync", DialogItem::ItemType::two},    {"MangoHud", DialogItem::ItemType::two},
      {"Gamemode", DialogItem::ItemType::two}, {"Driver", DialogItem::ItemType::multiple},
      {"Fsync", DialogItem::ItemType::two},    {"WineDebug", DialogItem::ItemType::two},
      {"Log", DialogItem::ItemType::two},
    };

    void build() {
        headerBar.set_subtitle(game.name);
        headerBar.set_title("Set Launch Options");
        headerBar.set_show_close_button();
        headerBar.show();
        for (auto it = itemsList.begin(); it != itemsList.end(); ++it) {
            listBox->append(*new DialogItem(DialogItem::DialogModel(it->first, it->second)));
        }
        listBox->show_all_children();
    }

 public:
    Dialog(Glib::RefPtr<Gtk::Builder> dialogBuilder, GameItem::Game game, Gtk::Window *parent) {
        this->game = game;
        this->window = parent;
        dialogBuilder->get_widget("dialog", dialog);
        dialog->set_titlebar(headerBar);
        dialogBuilder->get_widget("dialogListBox", listBox);
    }

    void show() {
        build();
        dialog->set_transient_for(*window);
        int result = dialog->run();
        if (result == Gtk::RESPONSE_DELETE_EVENT) {
            dialog->close();
        }
    }
};

#endif  // DIALOG_DIALOG_H_
