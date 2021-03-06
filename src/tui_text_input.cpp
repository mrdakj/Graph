#include "tui_fm_text_input.hpp"


bool fm_text_input_widget::Text_input::key_press_event(Key key, char symbol)
{
	/* Extend key press-es here */
	if (key == Key::Escape) {
		editing_canceled();
	}

	/* Do the standard procedure of Line edit */
	return Line_edit::key_press_event(key, symbol);
}


bool fm_text_input_widget::Text_input::focus_in_event() 
{
	/* Bypass focus_in of text input 
	 * wich clears the placeholder */

	return Textbox::focus_in_event();
}

bool fm_text_input_widget::Text_input::focus_out_event() 
{
	editing_canceled();
	return Line_edit::focus_out_event();
}

fm_text_input_widget::Text_input::Text_input(const Glyph_string& initial_text) : Line_edit(initial_text) {}


fm_text_input_widget::fm_text_input_widget(const Glyph_string &title, const Glyph_string &info_message, const Glyph_string &initial_text) : 
	title(make_child<Label>(title)), info_message(make_child<Label>(info_message)), text_input(make_child<Text_input>(initial_text)),
	editing_finished(text_input.editing_finished), editing_canceled(text_input.editing_canceled)
{
	Focus::set_focus_to(&text_input);

	this->title.set_alignment(Alignment::Center);
	this->title.brush.add_attributes(Attribute::Bold);
	this->title_blank.background_tile = L'─';
	enable_border(*this);
}

void fm_text_input_widget::grab_focus()
{
	text_input.clear();
	Focus::set_focus_to(&text_input);
}


void fm_text_input_widget::change_title(const std::string& new_title)
{
	title.contents() = new_title;
}

void fm_text_input_widget::change_info_message(const std::string& message)
{
	info_message.contents() = message;
}
