#include <immer/vector.hpp>
#include <immer/algorithm.hpp>
#include <algorithm>
#include <iostream>
#include "file.hpp"
#include "current_dir.hpp"
#include "tui_file_manager.hpp"
#include <cppurses/cppurses.hpp>


int main()
{
	current_dir d(fs::absolute(""));
	
	// test iterators
	// for (auto&& i : d) {
	// 	std::cout << i.name() << std::endl;
	// }

	// test transform
	// auto x = transform(d,[](auto&& d)  { return d.size()+3; }, &file::size);
	// for (auto&& f : x) {
	// 	std::cout << f << std::endl;
	// }

	file_manager_tui fm(d);	

	cppurses::System sys;
	sys.set_head(&fm);

	return sys.run();
}
