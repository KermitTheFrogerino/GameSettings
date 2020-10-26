#include <gtkmm.h>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <vector>
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
      {"Esync", DialogItem::ItemType::two},
      {"MangoHud", DialogItem::ItemType::two},
      {"Gamemode", DialogItem::ItemType::two},
      {"Driver", DialogItem::ItemType::multiple},
      {"Fsync", DialogItem::ItemType::two},
      {"WineDebug", DialogItem::ItemType::two},
      {"Log", DialogItem::ItemType::two},
    };

    void build() {
        dialog->set_titlebar(headerBar);
        headerBar.set_subtitle(game.name);
        headerBar.set_title("Set Launch Options");
        headerBar.set_show_close_button();
        headerBar.show();
        for (auto it : itemsList) {
            listBox->append(*new DialogItem(DialogItem::DialogModel(it.first, it.second)));
        }
        listBox->show_all_children();
    }

    void save() { cout << "Save" << endl; }

 public:
    Dialog(Glib::RefPtr<Gtk::Builder> dialogBuilder, GameItem::Game game, Gtk::Window *parent) {
        this->game = game;
        this->window = parent;
        dialogBuilder->get_widget("dialog", dialog);
        dialogBuilder->get_widget("dialogListBox", listBox);
    }

    bool show() {
        try {
            build();
            dialog->set_transient_for(*window);
            if (dialog->run() == Gtk::RESPONSE_APPLY) save();
            for (Gtk::Widget *item : listBox->get_children()) {
                listBox->remove(*item);
            }
            dialog->close();
            return true;
        } catch (const std::exception & ex) {
            cout << ex.what() << endl;
            return false;
        }
    }
};

#endif  // DIALOG_DIALOG_H_
