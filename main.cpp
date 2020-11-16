#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "include/dialog/dialog.h"
#include "include/gameItem/gameItem.h"
#include "include/simpleFunctions/simpleFunctions.h"
#include "include/vdfParser/vdfParser.h"

Glib::RefPtr<Gtk::Builder> mainBuilder;
Glib::RefPtr<Gtk::Builder> dialogBuilder;
Gtk::Window *window;
Gtk::ListBox *listBox;

void buildList(string steamID) {
    mainBuilder->get_widget("listBox", listBox);
    vector<string> pathList = SimpleFunctions::getDrives();
    // For each steam drive dir
    for (string path : pathList) {
        DIR *folder = opendir(path.c_str());
        if (folder == NULL) {
            puts("Unable to read directory");
            exit(1);
        }
        // Each game appmanifest file
        while (dirent *entry = readdir(folder)) {
            if (!strstr(entry->d_name, "appmanifest_")) continue;
            GameItem::Game game = SimpleFunctions::getGame(path + "/" + entry->d_name);
            if (SimpleFunctions::stringInList(game.name, GlobalVariables.gameBList, true)) continue;
            listBox->append(*new GameItem(
              game,
              window,
              steamID,
              [](GdkEventButton *event, GameItem::Game game, Gtk::Window *window, string steamID)
                -> bool { return Dialog(dialogBuilder, game, window, steamID).show(); }));
        }
        closedir(folder);
    }
}

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    mainBuilder = Gtk::Builder::create_from_file("glade/mainUI.glade");
    dialogBuilder = Gtk::Builder::create_from_file("glade/dialog.glade");

    mainBuilder->get_widget("window", window);

    string steamID = SimpleFunctions::getSteamUserID();

    buildList(steamID);
    window->show_all();
    return app->run(*window);
}
