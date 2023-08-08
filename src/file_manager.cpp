#include"pch.h"
#include"file_manager.h"

void file_manager::make_dir(std::string& command) {
	try
	{
		if (fs::create_directory(m_file_system_ptr->get_current_path() / command))
			cout << "Directory " << command << " created" << endl;
		else cout << "Directory " << command << " already exist" << endl;
	}
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << "Error occurred: " << ex.what() << std::endl;
    }
}

void file_manager::remove_dir(const string& command) {
	fs::path path(m_file_system_ptr->get_current_path() / command);
	if (fs::is_directory(path)) {
		try {
			fs::remove(path);
			cout << "Directory " << command << " removed" << endl;
		}
		catch (fs::filesystem_error) {
			cout << "Sorry, directory " << command << " can`t be removed. It`s not empty" << endl;
		}
	}
	else cout << "Can`t find directory with name " << command << endl;
}

void file_manager::remove(const std::string& command) {
	fs::path path(m_file_system_ptr->get_current_path() / command);
	if (fs::remove_all(path)) {
		if (fs::is_directory(path))
			cout << "Directory " << command << " removed" << endl;
		else cout << "File " << command << " removed" << endl;
	}
	else cout << "Can`t find directory with name" << command << endl;
}

//move to different directory or rename
void file_manager::move(string& command) {

	std::vector<string> paths;

	std::string s;
	const char delim = ' ';
	std::stringstream ss(command);

	while (getline(ss, s, delim))
		paths.push_back(s);

	if (paths.size() == 2) {

		fs::rename(m_file_system_ptr->get_current_path() / paths[0], m_file_system_ptr->get_current_path() / paths[1]);
	}
 
	else cout << "Please enter second name or path" << endl;
}

void file_manager::copy(string& command) {
	std::vector<string> paths;
	string temp = command;
	string s;
	const char delim = ' ';
	std::stringstream ss(temp);
	while (getline(ss, s, delim))
		paths.push_back(s);
	if (paths.size() == 2) {
		fs::copy(m_file_system_ptr->get_current_path() / paths[0], m_file_system_ptr->get_current_path() / paths[1]);
		cout << "Directory/File: " << paths[0] << " copied" << endl;
	}
	else cout << "Please enter second path" << endl;
}

void file_manager::list()
{
	cout << "\nDirectory content: " << endl;
	for (fs::directory_entry dir : fs::directory_iterator(m_file_system_ptr->get_current_path(), fs::directory_options::skip_permission_denied))
		cout << dir.path() << endl;
}

void file_manager::create_file(std::string& command)
{
	fs::path path(m_file_system_ptr->get_current_path() / command);
	if (fs::exists(path))
		cout << "File " << command << " already exists" << endl;
	else {
		std::ofstream file(command);
		file.close();
	}
}

//read file content line by line
void file_manager::read_from_file(std::string& command) 
{
	m_file_path = m_file_system_ptr->get_current_path() / command;

	std::ifstream file(m_file_path, std::ios::in);

	if (!file.is_open())
	{
		std::cerr << "Failed to open " << m_file_path << std::endl;
	}

	std::string line;

	while(std::getline(file, line))
	{
		std::cout << line << std::endl;
	}

	file.close();

}

//create file and write to it. if file already exist appends new content to already existed
void file_manager::write_to_file(std::string& command) 
{
	m_file_path = m_file_system_ptr->get_current_path() / command;

	std::ofstream file(m_file_path, std::ios::out | std::ios::app);

	if (!file.is_open())
	{
		std::cerr << "Failed to open " << m_file_path << std::endl;
		return;
	}

	cout << "Please write your text (type 'exit' to finish): " << endl;

	std::string input;
	while(true) 
	{
		std::getline(std::cin, input);

		if(input == "exit")
			break;

		file << input << std::endl;
	} 

	file.close();
}