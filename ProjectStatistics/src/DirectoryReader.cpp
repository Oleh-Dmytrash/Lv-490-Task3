#include "DirectoryReader.h"

std::map<std::string, std::string> DirectoryReader::GetCppFilesInFolder(std::string path_to_folder)
{
	std::map<std::string, std::string> files_in_directory;

	const std::regex cpp_files("\\.(?:cpp|c|h|hpp)");
	if (!std::filesystem::is_directory(path_to_folder))
	{
		throw std::runtime_error("The path specified is not a directory");
	}
	std::filesystem::directory_iterator folder(path_to_folder);
	for (auto& entry : folder)
	{
		if (std::regex_match(entry.path().extension().string(), cpp_files))
		{
			std::ifstream file(entry.path());
			if (file.is_open())
			{
				std::string file_text((std::istreambuf_iterator<char>(file)),
					std::istreambuf_iterator<char>());

				files_in_directory.emplace(std::make_pair(entry.path().string(), file_text));
			}
		}
	}
	return files_in_directory;
}
