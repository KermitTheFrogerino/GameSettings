#include <gtkmm.h>
#include <map>
#include <string>
#include <vector>
#include "../dialogItem/dialogInputItem.hpp"
#include "../dialogItem/dialogItem.hpp"
#include "../dialogItem/dialogItemType.hpp"
#include "../gameItem/gameItem.hpp"
#include "../globalVariables.hpp"
#include "../func/func.hpp"

using namespace std;

#ifndef SRC_DIALOG_DIALOG_HPP_
#define SRC_DIALOG_DIALOG_HPP_

class Dialog {
 private:
    string steamID;
    Glib::RefPtr<Gtk::Builder> dialogBuilder;
    Gtk::Dialog *dialog;
    Gtk::Window *window;
    GameItem::Game game;
    Gtk::ListBox *listBox;
    Gtk::HeaderBar headerBar;
    vector<DialogItem *> listRows = {};
    DialogInputItem *prefixDialogInput = new DialogInputItem("Prefix Commands");
    DialogInputItem *suffixDialogInput = new DialogInputItem("Suffix Commands");

    void build();

    void checkOptions(string launchOptions);

    void setPrefix(vector<string> prefix, vector<string> validSettings);

    void setSuffix(string suffix);

    void save();

 public:
    Dialog(Glib::RefPtr<Gtk::Builder> dialogBuilder,
           GameItem::Game game,
           Gtk::Window *parent,
           string steamID);

    bool show();
};

#endif  // SRC_DIALOG_DIALOG_HPP_
