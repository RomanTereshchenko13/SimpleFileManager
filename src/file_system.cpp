#include"pch.h"
#include"file_system.h"
#include"color.h"

//helping method
void file_system::help() {
	std::cout << "Avaliable commands: \n"
		<< COLOR::Yellow << "ls" << COLOR::Reset << "\t\t\t\t\t\t" << "List files and directories in current directory;\n"
		<< COLOR::Yellow << "cd" << COLOR::Reset << " <directory>\t\t\t\t\t" << "Set current directory;\n"
		<< COLOR::Yellow << "mkdir" << COLOR::Reset << " <directory>\t\t\t\t" << "Creates new direcory;\n"
		<< COLOR::Yellow << "rmdir" << COLOR::Reset << " <directory>\t\t\t\t" << "Removes directory if it not empty;\n"
		<< COLOR::Yellow << "rm" << COLOR::Reset << " <directory/file>\t\t\t\t" << "Removes file or directory;\n"
		<< COLOR::Yellow << "mv" << COLOR::Reset << " <directory/file> <new directory/file>\t" << "Renames or moves directory/file;\n"
		<< COLOR::Yellow << "cp" << COLOR::Reset << " <directory/file> <new directory/file>\t" << "Copies files or directories;\n"
		<< COLOR::Yellow << "touch" << COLOR::Reset << " <file>\t\t\t\t\t" << "Creates new;\n"
		<< COLOR::Yellow << "read" << COLOR::Reset  << " <file>\t\t\t\t\t" << "Reads text from file;\n"
		<< COLOR::Yellow << "write" << COLOR::Reset << " <file>\t\t\t\t\t" << "Writes text into file;\n"
		<< COLOR::Yellow << "search" << COLOR::Reset << " <file>\t\t\t\t\t" << "Searches all files with set name in current directory;\n"
		<< COLOR::Yellow << "Q" << COLOR::Reset << "\t\t\t\t\t\t" << COLOR::Red << "EXIT\n" << COLOR::Reset;
}

//Setting new working directory when "cd" command used
void file_system::set_current_path(const std::string& command) {
	try {
		fs::current_path(command);
		m_current_path = fs::current_path();
	}
	catch (fs::filesystem_error const& ex) {
		std::cerr << ex.what() << std::endl;
	}

}

//Gets working directory
const fs::path& file_system::get_current_path() const {
	return m_current_path;
}