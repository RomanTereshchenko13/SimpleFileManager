#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

class file_system
{
public:
	file_system() : m_current_path{fs::current_path().root_directory()} {}
	void help();
	void set_current_path(const std::string& command);
	const fs::path& get_current_path() const ;
private:
	fs::path m_current_path;
};

#endif //FILE_SYSTEM_H