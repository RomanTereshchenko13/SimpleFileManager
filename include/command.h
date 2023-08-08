#ifndef COMMAND_H_
#define COMMAND_H_

#include"file_searcher.h"
#include"file_manager.h"

class command
{
public:
	command() {}
	virtual ~command() {}
	virtual void execute(std::string command) = 0;
};

/*FileSystem Commands*/
class set_path_command : public command
{
public:
	set_path_command(std::shared_ptr<file_system> fs)
		:file_system_ptr{ fs } {}

	void execute(std::string command) override {
		file_system_ptr->set_current_path(command);
	}

private:
	std::shared_ptr<file_system> file_system_ptr;
}; 


class help_command : public command
{
public:
	help_command(std::shared_ptr <file_system> fs)
		:file_system_ptr{ fs } {}

	void execute(std::string command) override {
		file_system_ptr->help();
	}
private:
	std::shared_ptr <file_system> file_system_ptr;
};

/*FileManager Commands*/
class list_command : public command
{
public:
	list_command() = default;
	list_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->list();
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class makedir_command : public command
{
public:
	makedir_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{dm} {}

	void execute(std::string command) override {
		dirManagerPtr->make_dir(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class removedir_command : public command
{
public:
	removedir_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->remove_dir(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class remove_command : public command
{
public:
	remove_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->remove(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class move_command : public command
{
public:
	move_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->move(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class copy_command : public command
{
public:
	copy_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->copy(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class create_command : public command
{
public:
	create_command(std::shared_ptr<file_manager> dm)
		:dirManagerPtr{ dm } {}

	void execute(std::string command) override {
		dirManagerPtr->create_file(command);
	}

private:
	std::shared_ptr<file_manager> dirManagerPtr;
};

class read_command : public command
{
public:
	read_command(std::shared_ptr<file_manager> fm)
		:fileManagerPtr{ fm } {}

	void execute(std::string command) override {
		fileManagerPtr->read_from_file(command);
	}

private:
	std::shared_ptr<file_manager> fileManagerPtr;
};

class write_command : public command
{
public:
	write_command(std::shared_ptr<file_manager> fm)
		:fileManagerPtr{ fm } {}

	void execute(std::string command) override {
		fileManagerPtr->write_to_file(command);
	}

private:
	std::shared_ptr<file_manager> fileManagerPtr;
};

class search_command : public command
{
public:
	search_command(std::shared_ptr <file_searcher> fs)
		:file_searcher_ptr{ fs } {}

	void execute(std::string command) override {
		file_searcher_ptr->start_search(command);
	}
private:
	std::shared_ptr <file_searcher> file_searcher_ptr;
};

#endif //COMMAND_H_