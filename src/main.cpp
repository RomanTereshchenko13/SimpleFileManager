#include"pch.h"
#include "command.h"
#include"color.h"

using system_ptr = std::shared_ptr<file_system>;
using manager_ptr = std::shared_ptr<file_manager>;
using searcher_ptr = std::shared_ptr<file_searcher>;
using command_ptr = std::unique_ptr<command>;
using commands_map = std::unordered_map<std::string_view, command_ptr>;  

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//commands initialization
commands_map initialize_commands(system_ptr& system, manager_ptr& manager, searcher_ptr& searcher)
{
    commands_map commands;
    commands["mkdir"] = std::make_unique<makedir_command>(manager);
    commands["rmdir"] = std::make_unique<removedir_command>(manager);
    commands["rm"] = std::make_unique<remove_command>(manager);
    commands["mv"] = std::make_unique<move_command>(manager);
    commands["cp"] = std::make_unique<copy_command>(manager);
    commands["cd"] = std::make_unique<set_path_command>(system);
    commands["ls"] = std::make_unique<list_command>(manager);
    commands["touch"] = std::make_unique<create_command>(manager);
    commands["read"] = std::make_unique<read_command>(manager);
    commands["write"] = std::make_unique<write_command>(manager);
    commands["help"] = std::make_unique<help_command>(system);
    commands["find"] = std::make_unique<search_command>(searcher);

    return commands;
}

//main loop of the application
void run_file_manager(const commands_map& commands, const system_ptr& file_system_ptr) {
    std::string command_name;
    do
    {
        cout << COLOR::Yellow << file_system_ptr->get_current_path().string() << "> " << COLOR::Reset;
        getline(std::cin, command_name);
        auto it = commands.find(command_name.substr(0, command_name.find(' ')));
        if (it != commands.end()) {
            it->second->execute(command_name.substr(command_name.find(' ') + 1));
        }
        else if(command_name == "Q" || command_name == "q") 
        {
            std::cout << "Bye!\n";
        }
        else 
        {
            cout << "Invalid command." << endl;
        }
    } while (command_name != "Q" && command_name != "q");
}

int main()
{
    std::cout << "Welcome to My File Manager!\n";
    std::cout << "Enter a " << COLOR::Yellow << "command "<< COLOR::Reset << "to begin. Type " 
    << COLOR::Green << "'help' " << COLOR::Reset << "to see a list of available commands.\n";

    system_ptr file_system_ptr = std::make_shared<file_system>();
    manager_ptr file_manager_ptr = std::make_shared<file_manager>(file_system_ptr);
    searcher_ptr file_searcher_ptr = std::make_shared <file_searcher>(file_system_ptr);

    commands_map commands = initialize_commands(file_system_ptr, file_manager_ptr, file_searcher_ptr);
    run_file_manager(commands, file_system_ptr);

    return 0;
}