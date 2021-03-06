#ifndef TUI_FM_DIRLIST_MENU
#define TUI_FM_DIRLIST_MENU

#include "tui_fm_menu.hpp"
#include "current_dir.hpp"

using namespace cppurses;

class fm_dirlist_menu : public fm_menu {
	public:
		fm_dirlist_menu();

		sig::Signal<void()>& selected_file_changed{fm_menu::selected_item_changed};
		sig::Signal<void()>& esc_pressed{fm_menu::esc_pressed};
		sig::Signal<void()> d_pressed;
		sig::Signal<void()> backspace_pressed;
		sig::Signal<void()> h_pressed;
		sig::Signal<void()> insert_rfile;
		sig::Signal<void()> insert_dir;
		sig::Signal<void()> rename_selected;
		sig::Signal<void()> run_file;
		sig::Signal<void()> terminal;
		sig::Signal<void()> undo;
		sig::Signal<void()> redo;
		sig::Signal<void()> check_items;

		Label& title{this->make_child<Label>("Directory listing")};
		Blank_height& blank_after_title{this->make_child<Blank_height>(1)};
		std::size_t menu_height() const override;

	protected:
		bool paint_event() override;

		bool key_press_event(Key key, char symbol) override;

		bool mouse_press_event(Mouse_button button,
				Point global,
				Point local,
				std::uint8_t device_id) override;

		bool mouse_press_event_filter(Event_handler* receiver,
				Mouse_button button,
				Point global,
				Point local,
				std::uint8_t device_id) override;

	private: 
		std::size_t height_without_menu_items{this->children().size()};
};

#endif  // TUI_FM_MENU
