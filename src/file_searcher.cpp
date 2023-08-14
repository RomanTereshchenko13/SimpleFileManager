#include"pch.h"
#include"color.h"
#include "file_searcher.h"

void file_searcher::start_search(std::string_view file_name)
{
    m_threads.clear();
    found = false;
    fs::path path = file_system_ptr->get_current_path();
    for (const auto & entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
	{
		if (entry.is_directory())
		{
             task_queue.push(entry.path());
		}
		else if (entry.is_regular_file() && entry.path().filename() == file_name)
		{   
            found = true;
            std::cout << "Full path to the file: " << COLOR::Green << entry.path().string() << COLOR::Reset << std::endl;
			return; 
		}
	}

    for (unsigned i = 0; i < max_threads; ++i)
    {
        m_threads.emplace_back(std::thread(&file_searcher::worker_thread, this, file_name));
    }

    
    for(auto& thread : m_threads)
    {
        thread.join();
    }

    if(!found)
        std::cout << "Can`t find file: " << COLOR::Red << file_name << COLOR::Reset << std::endl;
}

bool file_searcher::search_file(const fs::path& path, std::string_view file_name)
{
    for(const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
    {
        if(entry.is_regular_file() && entry.path().filename() == file_name)
        {
            {
                found = true;
            }
            
            std::cout << "Full path to the file: " << COLOR::Green << entry.path().string() << COLOR::Reset << std::endl;
        }
        if(found) return true;
    }

    return false;
}

void file_searcher::worker_thread(std::string_view file_name)
{
    while (!found)
    {
        fs::path path;
        {
            std::scoped_lock lock(mx);
            if (!task_queue.empty())
            {
                path = task_queue.front();
                task_queue.pop();
            }
            else
            {
                return;
            }
        }
        try
        {
            search_file(path, file_name);
        }
        catch (const fs::filesystem_error& ex)
        {
            std::cerr << COLOR::Red << ex.what() << COLOR::Reset << std::endl;
        }

        if (found) return;
    }
}
