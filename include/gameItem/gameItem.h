#include <gtkmm.h>
#include <iostream>
#include <string>

#ifndef GAMEITEM_GAMEITEM_H_
#define GAMEITEM_GAMEITEM_H_

class GameItem : public Gtk::ListBoxRow {
 private:
    Gtk::Label label;
    Gtk::Image image;
    Gtk::EventBox eventBox;
    Gtk::Box box;

 public:
    typedef struct {
        std::string appID;
        std::string name;
    } Game;

    GameItem(Game game, Gtk::Window *window, bool(onClick)(GdkEventButton *, Game, Gtk::Window *)) {
        Gtk::manage(this);
        label.set_label(game.name.c_str());
        eventBox.add(box);
        box.pack_start(label, Gtk::PACK_START, 5);
        auto func = sigc::bind<GameItem::Game, Gtk::Window *>(sigc::ptr_fun(onClick), game, window);
        eventBox.signal_button_press_event().connect(func);
        add(eventBox);
    }
};
#endif  // GAMEITEM_GAMEITEM_H_
