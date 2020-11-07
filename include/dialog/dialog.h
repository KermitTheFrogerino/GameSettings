#include <gtkmm.h>
#include <any>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../dialogItem/dialogItem.h"
#include "../dialogItem/dialogItemType.h"
#include "../gameItem/gameItem.h"
#include "../simpleFunctions/simpleFunctions.h"

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

    vector<GameItem::GameSetting> itemsList = {
      {GameItem::GameSetting("Esync", {{"Esync", "PROTON_NO_ESYNC=1"}})},
      {GameItem::GameSetting("MangoHud", {{"MangoHud", "mangohud"}})},
      {GameItem::GameSetting("Gamemode", {{"Gamemode", "gamemoderun"}})},
      {GameItem::GameSetting(
        "AMD Driver",
        {{
           "Mesa",
           "export "
           "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/radeon_icd.i686.json:/usr/share/"
           "vulkan/icd.d/radeon_icd.x86_64.json",
         },
         {
           "AMDVLK",
           "export "
           "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/amd_icd32.json:/usr/share/vulkan/"
           "icd.d/amd_icd64.json",
         }},
        ItemType::multiple)},
      {GameItem::GameSetting("Fsync", {{"Fsync", "PROTON_NO_FSYNC=1"}})},
      {GameItem::GameSetting("WineDebug", {{"WineDebug", "winedebug=-all"}})},
      {GameItem::GameSetting("Log", {{"Log", "PROTON_LOG=1"}})},
    };

    void build() {
        dialog->set_titlebar(headerBar);
        headerBar.set_subtitle(game.name);
        headerBar.set_title("Set Launch Options");
        headerBar.set_show_close_button();
        headerBar.show();
        checkOptions(SimpleFunctions::readGameOptions(game.appID));
    }

    void checkOptions(string launchOptions) {
        cout << launchOptions << endl;
        for (GameItem::GameSetting setting : itemsList) {
            DialogItem *dialogItem = NULL;
            for (string item : SimpleFunctions::stringSplit(launchOptions, ' ')) {
                if (strcmp(item.c_str(), setting.getSettings()[0].second.c_str()) == 0) {
                    cout << item << endl;
                    dialogItem = new DialogItem(setting, true);
                }
            }
            if (dialogItem == NULL) dialogItem = new DialogItem(setting);
            listBox->append(*dialogItem);
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
        } catch (const std::exception &ex) {
            cout << ex.what() << endl;
            return false;
        }
    }
};

#endif  // DIALOG_DIALOG_H_
