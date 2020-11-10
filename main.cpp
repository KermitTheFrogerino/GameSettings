#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <sstream>
#include <string>
#include "include/dialog/dialog.h"
#include "include/gameItem/gameItem.h"
#include "include/jsonParser/jsonParser.h"
#include "include/simpleFunctions/simpleFunctions.h"
#include "include/vdfParser/vdfParser2.h"

Glib::RefPtr<Gtk::Application> app;
Glib::RefPtr<Gtk::Builder> mainBuilder;
Glib::RefPtr<Gtk::Builder> dialogBuilder;
Gtk::Window *window;
Gtk::ListBox *listBox;

void buildList() {
    mainBuilder->get_widget("listBox", listBox);
    vector<string> pathList = SimpleFunctions::getDrives();
    // For each steam drive dir
    for (string item : pathList) {
        char const *path = item.c_str();
        DIR *folder = opendir(path);
        if (folder == NULL) {
            puts("Unable to read directory");
            exit(1);
        }
        // Each game appmanifest file
        while (dirent *entry = readdir(folder)) {
            if (!strstr(entry->d_name, "appmanifest_")) continue;
            GameItem::Game game =
              SimpleFunctions::getGame(SimpleFunctions::surroundChar(path, "/", entry->d_name));
            if (SimpleFunctions::stringInList(game.name, {"Proton", "Steam"})) continue;
            listBox->append(*new GameItem(
              game,
              window,
              [](GdkEventButton *event, GameItem::Game game, Gtk::Window *window) -> bool {
                  return Dialog(dialogBuilder, game, window).show();
              }));
        }
        closedir(folder);
    }
}

int main(int argc, char **argv) {
    app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    mainBuilder = Gtk::Builder::create_from_file("glade/mainUI.glade");
    dialogBuilder = Gtk::Builder::create_from_file("glade/dialog.glade");

    mainBuilder->get_widget("window", window);

    string path = "UserLocalConfigStore/Software/Valve/Steam/Apps/70/LaunchOptions";
    VdfParser2 parser = VdfParser2("test.vdf");
    auto str = parser.readFile(path);
    cout << str << endl;
    parser.write(path, "yeet %command%");

    // buildList();
    // window->show_all();
    // return app->run(*window);
    return 0;
}
