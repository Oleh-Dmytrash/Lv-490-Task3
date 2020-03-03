#include "DirectoryFilesParser.h"

string DirectoryFilesParser::ParseFiles(string directory_path)
{
    auto start_timer = chrono::high_resolution_clock::now();

    DirectoryReader reader(directory_path);
    reader.ReadDirectory();

    vector<thread> threads;

    for (int i = 0; i < reader.GetFileCount(); ++i)
    {
        m_parsers.emplace_back(new CodeParser());
        threads.emplace_back(thread(&CodeParser::Parse, m_parsers[i], reader.GetPath(i)));
    }

    for (auto& current_thread : threads)
    {
        current_thread.join();
    }

    string parse_info;
    for (auto parser : m_parsers)
    {
        parse_info.append(parser->GetResult());
    }

    auto stop_timer = chrono::high_resolution_clock::now();

    auto time_of_execution1 = chrono::duration_cast<chrono::microseconds>(stop_timer - start_timer);
    auto time_of_execution2 = chrono::duration_cast<chrono::milliseconds>(stop_timer - start_timer);    

    parse_info.append("Parsed files count: \t" + to_string(reader.GetFileCount()) + '\n');
    parse_info.append("Time of execution: \t" + to_string(time_of_execution1.count()) + " micoseconds\n");
    parse_info.append("Time of execution: \t" + to_string(time_of_execution2.count()) + " milliseconds\n");

    return parse_info;
}
