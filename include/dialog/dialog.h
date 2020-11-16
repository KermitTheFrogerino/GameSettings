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
#include "../dialogItem/dialogInputItem.h"
#include "../dialogItem/dialogItem.h"
#include "../dialogItem/dialogItemType.h"
#include "../gameItem/gameItem.h"
#include "../globalVariables.h"
#include "../simpleFunctions/simpleFunctions.h"

using namespace std;

#ifndef INCLUDE_DIALOG_DIALOG_H_
#define INCLUDE_DIALOG_DIALOG_H_

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

    void build() {
        dialog->set_titlebar(headerBar);
        headerBar.set_subtitle(game.name);
        headerBar.set_title("Set Launch Options");
        headerBar.set_show_close_button();
        headerBar.show();
        checkOptions(SimpleFunctions::readGameOptions(game.appID, "143352235"));
    }

    void checkOptions(string launchOptions) {
        auto split = SimpleFunctions::stringSplitByString(launchOptions, "%command%");
        vector<string> prefix =
          SimpleFunctions::stringSplitByChar(split.size() >= 2 ? split[0] : "", ' ');

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

    void setPrefix(vector<string> prefix, vector<string> validSettings) {
        string prefixOtherCommands = "";
        for (auto command : prefix) {
            if (find(validSettings.begin(), validSettings.end(), command) == validSettings.end()) {
                prefixOtherCommands += " " + command;
            }
        }
        prefixDialogInput->setEntryText(
          SimpleFunctions::removeCharRFromStart(prefixOtherCommands, ' '));
        listBox->append(*prefixDialogInput);
    }

    void setSuffix(string suffix) {
        suffixDialogInput->setEntryText(SimpleFunctions::removeCharRFromStart(suffix, ' '));
        listBox->append(*suffixDialogInput);
    }

    void save() {
        cout << "Save" << endl;
        for (auto item : listRows) {
            bool state = item->getSwitchState();
            cout << state << endl;
        }
        cout << prefixDialogInput->getEntryText() << endl;
        cout << suffixDialogInput->getEntryText() << endl;
    }

 public:
    Dialog(Glib::RefPtr<Gtk::Builder> dialogBuilder,
           GameItem::Game game,
           Gtk::Window *parent,
           string steamID) {
        this->steamID = steamID;
        this->game = game;
        this->window = parent;
        dialogBuilder->get_widget("dialog", dialog);
        dialogBuilder->get_widget("dialogListBox", listBox);
    }

    bool show() {
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
};

#endif  // INCLUDE_DIALOG_DIALOG_H_
