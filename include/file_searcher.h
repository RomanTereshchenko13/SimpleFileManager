#ifndef FILE_SEARCHER_H
#define FILE_SEARCHER_H

#include"file_system.h"

class file_searcher 
{
public:
    file_searcher() = default;
    file_searcher(std::shared_ptr<file_system> fs) : file_system_ptr(fs)  {}
    void start_search(std::string_view file_name);

    file_searcher(const file_searcher& other) = delete;
    file_searcher& operator=(const file_searcher& other) = delete;

private:
    std::mutex mx;
    std::atomic<bool> found;
    std::vector<std::thread> m_threads;
    std::queue<fs::path> task_queue;
    std::shared_ptr<file_system> file_system_ptr;
    unsigned max_threads = std::thread::hardware_concurrency();

private:
    bool search_file(const fs::path& path, std::string_view file_name);
    void worker_thread(std::string_view file_name);
};

#endif // FILE_SEARCHER_H