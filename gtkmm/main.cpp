#include <gtkmm.h>

//using gtk
int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Main kit(argc, argv);

    builder =  Gtk::Builder::create_from_file("GridTest.glade");

    Gtk::Window * window = 0;

    builder->get_widget("mainWindow", window);

    Gtk::Main::run(*window);

    return 0;
}
