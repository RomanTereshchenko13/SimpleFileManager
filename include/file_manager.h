#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

#include"file_system.h"

using std::string, std::cout, std::endl, std::cin;

class file_manager
{
public:
	file_manager() = default;
	file_manager(std::shared_ptr<file_system> file_system_ptr)
		: m_file_system_ptr(file_system_ptr) {}

	void read_from_file(std::string& command);
	void write_to_file(std::string& command);
	void create_file(std::string&  command);
	void make_dir(std::string& command);	// creates new directory
	void remove_dir(const std::string&  command); // remove directory if empty
	void remove(const std::string& command); // remove directory or path
	void move(string& command);	// renames or moves to another location directory or file
	void copy(string& command);	// copy directory or file
	void list();	// shows list of files/directories

private:
	fs::path m_file_path;
	std::shared_ptr<file_system> m_file_system_ptr;
};


#endif // FILE_MANAGER_H_
