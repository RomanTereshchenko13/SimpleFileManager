#include"pch.h"
#include "command.h"

int main()
{
    std::cout << "Welcome to My File Manager!\n";
    std::cout << "Enter a \033[33mcommand\033[0m to begin. Type \033[32m'help'\033[0m to see a list of available commands.\n";

    std::shared_ptr<file_system> file_system_ptr = std::make_shared<file_system>();
    std::shared_ptr<file_manager> file_manager_ptr{ std::make_shared<file_manager>(file_system_ptr)};
    std::shared_ptr<file_searcher> file_searcher_ptr = std::make_shared <file_searcher>(file_system_ptr);

    std::unordered_map<std::string_view, std::unique_ptr<command>> commands;
    commands["mkdir"] = std::make_unique<makedir_command>(file_manager_ptr);
    commands["rmdir"] = std::make_unique<removedir_command>(file_manager_ptr);
    commands["rm"] = std::make_unique<remove_command>(file_manager_ptr);
    commands["mv"] = std::make_unique<move_command>(file_manager_ptr);
    commands["cp"] = std::make_unique<copy_command>(file_manager_ptr);
    commands["cd"] = std::make_unique<set_path_command>(file_system_ptr);
    commands["ls"] = std::make_unique<list_command>(file_manager_ptr);
    commands["touch"] = std::make_unique<create_command>(file_manager_ptr);
    commands["read"] = std::make_unique<read_command>(file_manager_ptr);
    commands["write"] = std::make_unique<write_command>(file_manager_ptr);
    commands["help"] = std::make_unique<help_command>(file_system_ptr);
    commands["find"] = std::make_unique<search_command>(file_searcher_ptr);

    std::string command_name;

    do
    {
        cout << "\033[33m" << file_system_ptr->get_current_path().string() << "\033[0m" << "\033[33m>\033[0m ";
        getline(std::cin, command_name);
        auto it = commands.find(command_name.substr(0, command_name.find(' ')));
        if (it != commands.end()) {
            it->second->execute(command_name.substr(command_name.find(' ') + 1));
        }
        else {
            cout << "Invalid command." << endl;
        }
    } while (command_name != "Q" && command_name != "q");


    return 0;
}