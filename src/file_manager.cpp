#include"pch.h"
#include"color.h"
#include"file_manager.h"

//creates directory in a current path
void file_manager::make_dir(std::string& command) 
{
	try
	{
		if (fs::create_directory(m_file_system_ptr->get_current_path() / command))
			std::cout << "Directory " << COLOR::Green << command << COLOR::Reset << " created\n";
		else 
			std::cout << "Directory " << COLOR::Yellow << command << COLOR::Reset << " already exist\n";
	}
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << COLOR::Red << ex.what() << COLOR::Reset << std::endl;
    }
}

//removes directory in a cyrrent path if it is empty
void file_manager::remove_dir(const string& command) 
{
	fs::path path(m_file_system_ptr->get_current_path() / command);
	if (fs::is_directory(path)) 
	{
		try 
		{
			fs::remove(path);
			std::cout << "Directory " << COLOR::Green << command << COLOR::Reset << " removed\n";
		}
		catch (const fs::filesystem_error& ex) 
		{
        std::cerr << COLOR::Red << ex.what() << COLOR::Reset << std::endl;
		}
	}
	else std::cout << "Can`t find directory with name " << COLOR::Yellow << command << COLOR::Reset << std::endl;
}

//remove file or directory
void file_manager::remove(const std::string& command) 
{
	if (fs::remove_all(m_file_system_ptr->get_current_path() / command)) 
	{
		std::cout << COLOR::Green << command << COLOR::Reset << " removed\n";
	}
	else 
		std::cout << "Can`t find directory with name " << COLOR::Yellow << command << COLOR::Reset << std::endl;
}

//move to different directory or rename
void file_manager::move(string& command) 
{
	std::vector<string> paths;
	std::string s;
	const char delim = ' ';
	std::stringstream ss(command);

	while (getline(ss, s, delim))
		paths.push_back(s);

	if (paths.size() == 2) 
	{
		try
		{
			fs::rename(m_file_system_ptr->get_current_path() / paths[0], m_file_system_ptr->get_current_path() / paths[1]);
			std::cout << COLOR::Green << paths[0] << COLOR::Reset << " moved to: " << COLOR::Green << paths[1] << COLOR::Reset << std::endl;
		}
		catch(const fs::filesystem_error& ex)
		{
			std::cerr << COLOR::Red << ex.what() << COLOR::Reset << std::endl;
		}
	}
	else 
		std::cout << COLOR::Red << "Please enter second name or path\n" << COLOR::Reset;
}

void file_manager::copy(string& command) 
{
	std::vector<string> paths;
	string s;
	const char delim = ' ';
	std::stringstream ss(command);
	while (getline(ss, s, delim))
		paths.push_back(s);
	if (paths.size() == 2) {
		fs::copy(m_file_system_ptr->get_current_path() / paths[0], m_file_system_ptr->get_current_path() / paths[1]);
		std::cout << COLOR::Green << paths[0] << COLOR::Reset << " copied to: " << COLOR::Green << paths[1] << COLOR::Reset << std::endl;
	}
	else
		std::cout << COLOR::Red << "Please enter second name or path\n" << COLOR::Reset;
}

void file_manager::list()
{
	std::cout << "\nDirectory content: " << std::endl;
	for (fs::directory_entry dir : fs::directory_iterator(m_file_system_ptr->get_current_path(), fs::directory_options::skip_permission_denied))
		std::cout << dir.path() << std::endl;
}

void file_manager::create_file(std::string& command)
{
	fs::path path(m_file_system_ptr->get_current_path() / command);
	if (fs::exists(path))
		std::cout << "File " << COLOR::Yellow << command << COLOR::Reset << " already exists\n";
	else 
	{
		try
		{
			std::ofstream file(path);
			std::cout << "File " << COLOR::Green << command << COLOR::Reset << " created\n";
			file.close();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

//read file content line by line
void file_manager::read_from_file(std::string& command) 
{
	m_file_path = m_file_system_ptr->get_current_path() / command;

	std::ifstream file(m_file_path, std::ios::in);

	if (!file.is_open())
	{
		std::cerr << "Failed to open " << COLOR::Red << m_file_path << COLOR::Reset << std::endl;
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
		std::cerr << "Failed to open " << COLOR::Red << m_file_path << COLOR::Reset << std::endl;
		return;
	}

	std::cout << "Please write your text (type 'exit' to finish): \n";

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