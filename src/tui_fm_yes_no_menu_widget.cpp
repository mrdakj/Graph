#include "tui_fm_yes_no_menu_widget.hpp"

fm_yes_no_menu_widget::fm_yes_no_menu_widget(std::string question, sig::Slot<void()> yes_slot, sig::Slot<void()> no_slot)  
{
	blank_after_question_second.background_tile = L'─';
	enable_border(*this);

	this->question.set_text(question);
	options_menu.add_item("Yes").connect(yes_slot);
	options_menu.add_item("No").connect(no_slot);
	options_menu.esc_pressed.connect(no_slot);
}

fm_yes_no_menu_widget::fm_yes_no_menu_widget()  
{
	blank_after_question_second.background_tile = L'─';
	enable_border(*this);
}

void fm_yes_no_menu_widget::grab_focus()
{
	Focus::set_focus_to(&options_menu);
}

void fm_yes_no_menu_widget::add_yes_no_slots(sig::Slot<void()> yes_slot, sig::Slot<void()> no_slot)
{
	options_menu.remove_item(0);
	options_menu.remove_item(0);
	options_menu.add_item("Yes").connect(yes_slot);
	options_menu.add_item("No").connect(no_slot);
	options_menu.esc_pressed.connect(no_slot);
}

void fm_yes_no_menu_widget::add_yes_no_slots(std::string question, sig::Slot<void()> yes_slot, sig::Slot<void()> no_slot)
{
	this->question.set_text(question);
	add_yes_no_slots(yes_slot, no_slot);
}
