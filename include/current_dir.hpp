#ifndef CURRENT_DIR_HPP
#define CURRENT_DIR_HPP 

#include <immer/vector.hpp>
#include <immer/algorithm.hpp>
#include <range/v3/all.hpp>
#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include "file.hpp"

namespace fs = std::experimental::filesystem;

class Current_dir {
private:

	fs::path path;
	immer::vector<File> data;

	void rename_on_system(const std::string& file_name, const std::string& new_file_name) const;
	int file_search(const std::string& file_name) const;

public:
	Current_dir(const std::string& path, immer::vector<File> data);
	Current_dir(const std::string& path);

	immer::vector<File> ls() const;

	Current_dir cd(const std::string& dir) const;
	Current_dir rename(const std::string& file_name, const std::string& new_file_name) const &;

	Current_dir rename(const std::string& file_name, const std::string& new_file_name) &&;


	const fs::path& get_path() const;
};

#endif /* CURRENT_DIR_HPP */
