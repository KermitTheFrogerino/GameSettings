#include "dialog.hpp"
#include <gtkmm.h>
#include <algorithm>
#include <any>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../dialogItem/dialogInputItem.hpp"
#include "../dialogItem/dialogItem.hpp"
#include "../dialogItem/dialogItemType.hpp"
#include "../gameItem/gameItem.hpp"
#include "../globalVariables.hpp"
#include "../func/func.hpp"

using namespace std;

void Dialog::build() {
    dialog->set_titlebar(headerBar);
    headerBar.set_subtitle(game.name);
    headerBar.set_title("Set Launch Options");
    headerBar.set_show_close_button();
    headerBar.show();
    checkOptions(Func::readGameOptions(game.appID, "143352235"));
}

void Dialog::checkOptions(string launchOptions) {
    auto split = Func::stringSplitByString(launchOptions, "%command%");
    vector<string> prefix =
      Func::stringSplitByChar(split.size() >= 2 ? split[0] : "", ' ');

    vector<string> validSettings;
    for (GameItem::GameSetting setting : GlobalVariables.itemsList) {
        DialogItem *dialogItem = NULL;
        if (find(prefix.begin(), prefix.end(), setting.settings[0].second) != prefix.end()) {
            validSettings.push_back(setting.settings[0].second);
            dialogItem = new DialogItem(setting, true);
        }
        if (dialogItem == NULL) dialogItem = new DialogItem(setting);
        listRows.push_back(dialogItem);
        listBox->append(*dialogItem);
    }
    setPrefix(prefix, validSettings);
    setSuffix(split.size() >= 2 ? split[1] : "");
    listBox->show_all_children();
}

void Dialog::setPrefix(vector<string> prefix, vector<string> validSettings) {
    string prefixOtherCommands = "";
    for (auto command : prefix) {
        if (find(validSettings.begin(), validSettings.end(), command) == validSettings.end()) {
            prefixOtherCommands += " " + command;
        }
    }
    prefixDialogInput->setEntryText(
      Func::removeCharRFromStart(prefixOtherCommands, ' '));
    listBox->append(*prefixDialogInput);
}

void Dialog::setSuffix(string suffix) {
    suffixDialogInput->setEntryText(Func::removeCharRFromStart(suffix, ' '));
    listBox->append(*suffixDialogInput);
}

void Dialog::save() {
    cout << "Save" << endl;
    for (auto item : listRows) {
        bool state = item->getSwitchState();
        cout << state << endl;
    }
    cout << prefixDialogInput->getEntryText() << endl;
    cout << suffixDialogInput->getEntryText() << endl;
}

Dialog::Dialog(Glib::RefPtr<Gtk::Builder> dialogBuilder,
       GameItem::Game game,
       Gtk::Window *parent,
       string steamID) {
    this->steamID = steamID;
    this->game = game;
    this->window = parent;
    dialogBuilder->get_widget("dialog", dialog);
    dialogBuilder->get_widget("dialogListBox", listBox);
}

bool Dialog::show() {
    try {
        build();
        dialog->set_transient_for(*window);
        if (dialog->run() == Gtk::RESPONSE_APPLY) {
            save();
        } else {
            cout << endl << "close" << endl;
        }
        for (Gtk::Widget *item : listBox->get_children()) {
            listBox->remove(*item);
        }
        dialog->close();
        return true;
    } catch (const std::exception &ex) {
        cout << ex.what() << endl;
        return false;
    }
}
