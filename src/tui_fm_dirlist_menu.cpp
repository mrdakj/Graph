#include "../include/tui_fm_dirlist_menu.hpp"

Fm_dirlist_menu::Fm_dirlist_menu()
{
	this->title.set_alignment(Alignment::Center);
    	this->title.brush.add_attributes(Attribute::Bold);
    	this->blank_after_title.background_tile = L'─';
}

bool Fm_dirlist_menu::paint_event() {
	return Fm_menu::paint_event();
}

bool Fm_dirlist_menu::key_press_event(Key key, char symbol) {

   	if (key == Key::h) {
		h_pressed();
	} else if (key == Key::Backspace) {
		backspace_pressed();
	} else if (key == Key::d) {
		d_pressed();
	} else if (key == Key::q) {
		insert_rfile();
	} else if (key == Key::w) {
		insert_dir();
	} else if (key == Key::r) {
		rename_selected();
	} else if (key == Key::e) {
		run_file();
	} else if (key == Key::t) {
		terminal();
	} else if (key == Key::u) {
		undo();
	} else if (key == Key::p) {
		redo();
	} else if (key == Key::j) {
		if (selected_index_ >= items_.size()-1)
			items_end_boundary();

	} else if (key == Key::k) {
		if (selected_index_ <= 0)
			items_begin_boundary();
	}

	return	Fm_menu::key_press_event(key, symbol);
}

bool Fm_dirlist_menu::mouse_press_event(Mouse_button button,
                             Point global,
                             Point local,
                             std::uint8_t device_id) {
	return Fm_menu::mouse_move_event(button, global, local, device_id);
}

bool Fm_dirlist_menu::mouse_press_event_filter(Event_handler* receiver,
                                    Mouse_button button,
                                    Point global,
                                    Point local,
                                    std::uint8_t device_id) {
	return Fm_menu::mouse_press_event_filter(receiver, button, global, local, device_id);
}
