echo $(pkg-config --cflags-only-I gtkmm-3.0 | sed 's/-I\([^ ]*\)/"\1",\n/g')
