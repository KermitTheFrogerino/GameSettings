#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include "include/dialog/dialog.h"
#include "include/gameItem/gameItem.h"
#include "include/jsonParser/jsonParser.h"
#include "include/simpleFunctions/simpleFunctions.h"

Glib::RefPtr<Gtk::Application> app;
Glib::RefPtr<Gtk::Builder> mainBuilder;
Glib::RefPtr<Gtk::Builder> dialogBuilder;
Gtk::Window *window;
Gtk::ListBox *listBox;

vector<string> blacklist = {"Proton", "Steam"};

void buildList() {
    mainBuilder->get_widget("listBox", listBox);

    vector<string> pathList = SimpleFunctions::getDrives();
    // For each steam drive dir
    for (size_t i = 0; i < pathList.size(); i++) {
        char const *path = pathList[i].c_str();
        DIR *folder = opendir(path);
        if (folder == NULL) {
            puts("Unable to read directory");
            exit(1);
        }
        struct dirent *entry;
        // Each game appmanifest file
        while ((entry = readdir(folder))) {
            if (!strstr(entry->d_name, reinterpret_cast<char const *>("appmanifest_"))) continue;
            GameItem::Game game = SimpleFunctions::getGame(SimpleFunctions::surroundChar(
              const_cast<char *>(path), const_cast<char *>(reinterpret_cast<char const *>("/")),
              entry->d_name));
            if (SimpleFunctions::ifStrMatchList(game.name, blacklist)) continue;
            listBox->append(*new GameItem(
              game, window,
              [](GdkEventButton *event, GameItem::Game game, Gtk::Window *window) -> bool {
                  Dialog(dialogBuilder, game, window).show();
                  return true;
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
    buildList();
    window->show_all();
    return app->run(*window);
}
