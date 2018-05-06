#include "../include/tui_file_manager.hpp"

using namespace cppurses;


/* Change directory slot */
sig::Slot<void()> chdir(File_manager_tui& fm, const std::string& dirpath)
{
    //sig::Slot<void()> slot{[&pb] { pb.clicked(); }};
    //slot.track(pb.destroyed);
    //return slot;

    sig::Slot<void()> slot{[&fm, dirpath] {
	    fm.set_directory(fm.curdir.cd(fs::absolute(dirpath)));
	    // exit(EXIT_FAILURE);
    }};

    slot.track(fm.destroyed);

    return slot;
}

sig::Slot<void()> delete_file(File_manager_tui& fm)
{
    sig::Slot<void()> slot{[&fm] {
	    std::string file_name = fm.flisting.get_selected_item_name();
	    fm.set_directory(fm.curdir.delete_file(fm.curdir.find_by_fname(file_name)));
		std::size_t index = fm.flisting.selected_index_;
		if (index != 0)
			index--;
		fm.flisting.select_item(index);
    }};

    slot.track(fm.destroyed);

    return slot;
}

sig::Slot<void()> insert_rfile(File_manager_tui& fm, const std::string& name)
{
    sig::Slot<void()> slot{[&fm, name] {
	    fm.set_directory(fm.curdir.insert_file(File(name, 'r')));
		int index = fm.curdir.get_index_by_name(name);
		if (index != -1)
			fm.flisting.select_item(index);
    }};

    slot.track(fm.destroyed);


    return slot;
}

sig::Slot<void()> insert_dir(File_manager_tui& fm, const std::string& name)
{
    sig::Slot<void()> slot{[&fm, name] {
	    fm.set_directory(fm.curdir.insert_file(File(name, 'd')));
		int index = fm.curdir.get_index_by_name(name);
		if (index != -1)
			fm.flisting.select_item(index);
    }};

    slot.track(fm.destroyed);

    return slot;
}

sig::Slot<void()> change_file(File_manager_tui& fm)
{
    sig::Slot<void()> slot{[&fm] 
    {
	    std::string file_name = fm.flisting.get_selected_item_name();
	    fm.file_info.set_file(fm.curdir.find_by_fname(file_name));
    }};

    slot.track(fm.flisting.destroyed);

    return slot;
}
 
File_manager_tui::File_manager_tui(Current_dir& curdir) : curdir(curdir)
{
	init(curdir);
}


void File_manager_tui::init(const Current_dir& curdir)
{
	set_background(*this, Color::Black);
	//hlLabel.set_alignment(Alignment::Center);
	set_background(current_dir_path, Color::White);
	set_foreground(current_dir_path, Color::Black);

	Focus::set_focus_to(&flisting);
	enable_border(flisting);


	current_dir_path.brush.add_attributes(Attribute::Bold);
	set_directory(curdir);
}

void File_manager_tui::set_directory(const Current_dir& new_curdir)
{

	// Pokupljenja stara velicina
	size_t old_size = flisting.size();
	curdir = new_curdir;

	/* Postavljanje inicijalnog fajla na finfo */
	if (curdir.dirs.size() > 0) 
		file_info.set_file(curdir.dirs[0]);
	else if (curdir.regular_files.size() > 0) 
		file_info.set_file(curdir.regular_files[0]);	
	else 
		file_info.set_file("Empty directory", "", "");

	immer::for_each(curdir.dirs, [this](auto&& f) { 
		flisting.add_item(f.get_name()).connect(chdir(*this, this->curdir.path / f.get_name()));
	});

	immer::for_each(curdir.regular_files, [this](auto&& f) { 
		flisting.add_item(f.get_name());
	});

	// TODO -> Ovako je uradjeno jer mora prvo da se 
	// dodaju novi elementi, eleminisati nekako petlju
	// je l moze prvo da se uklone pa onda da se dodaju?
	for (std::size_t i = 0; i < old_size; i++)
	       flisting.remove_item(0);	


	flisting.select_item(0);
	flisting.selected_file_changed.connect(change_file(*this));	

	flisting.esc_pressed.disconnect_all_slots();
	flisting.esc_pressed.connect(chdir(*this, fs::absolute(curdir.get_path().parent_path())));

	flisting.d_pressed.disconnect_all_slots();
	flisting.d_pressed.connect(delete_file(*this));


	flisting.insert_rfile.disconnect_all_slots();
	flisting.insert_rfile.connect(insert_rfile(*this, "unititled"));

	flisting.insert_dir.disconnect_all_slots();
	flisting.insert_dir.connect(insert_dir(*this, "untitled_dir"));

	this->current_dir_path.set_text("  Dir: " + curdir.get_path().string());
}
