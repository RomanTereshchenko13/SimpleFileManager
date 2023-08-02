#include"pch.h"
#include"file_system.h"

void file_system::help() {
	std::cout << "Avaliable commands: \n"
		<< "\033[33mls\033[0m\t\t\t\t\t\t" << "List files and directories in current directory;\n"
		<< "\033[33mcd\033[0m <directory>\t\t\t\t\t" << "Set current directory;\n"
		<< "\033[33mmkdir\033[0m <directory>\t\t\t\t" << "Creates new direcory;\n"
		<< "\033[33mrmdir\033[0m <directory>\t\t\t\t" << "Removes directory if it not empty;\n"
		<< "\033[33mrm\033[0m <directory/file>\t\t\t\t" << "Removes file or directory;\n"
		<< "\033[33mmv\033[0m <directory/file> <new directory/file>\t" << "Renames or moves directory/file;\n"
		<< "\033[33mcp\033[0m <directory/file> <new directory/file>\t" << "Copies files or directories;\n"
		<< "\033[33mtouch\033[0m <file>\t\t\t\t\t" << "Creates new;\n"
		<< "\033[33mread\033[0m <file>\t\t\t\t\t" << "Reads text from file;\n"
		<< "\033[33mwrite\033[0m <file>\t\t\t\t\t" << "Writes text into file;\n"
		<< "\033[33msearch\033[0m <file>\t\t\t\t\t" << "Searches all files with set name in current directory;\n"
		<< "\033[33mQ\033[0m\t\t\t\t\t\t" << "\033[31mEXIT\033[0m\n";

}

void file_system::set_current_path(const std::string& command) {
	try {
		fs::current_path(command);
	}
	catch (fs::filesystem_error const& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		std::cout << command << " is not valid path" << std::endl;
	}
	m_current_path = fs::current_path();
}

const fs::path& file_system::get_current_path() const {
	return m_current_path;
}