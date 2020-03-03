#include "DirectoryReader.h"

void DirectoryReader::ReadDirectory()
{
	filesystem::path path = m_directory_path;
	if (m_directory_path == "") return;

	if (!filesystem::is_directory(m_directory_path)) return;

	const regex cpp_files("\\.(?:c|cpp|h|hpp)");

	for (const auto& entry : filesystem::directory_iterator(m_directory_path))
	{		
		const string extension = entry.path().extension().string();
		if (filesystem::is_regular_file(entry) && regex_match(extension, cpp_files))
		{
			m_directory_files_path.push_back(string(entry.path().string()));
		}
	}
}

void DirectoryReader::ReadDirectory(string directory_path)
{
	if (filesystem::is_directory(directory_path))
	{
		m_directory_path = directory_path;
	}
	else
	{
		return;
	}

	const std::regex cpp_files("\\.(?:c|cpp|h|hpp)");

	for (const auto& entry : filesystem::directory_iterator(m_directory_path))
	{
		const string extension = entry.path().extension().string();
		if (filesystem::is_regular_file(entry) && regex_match(extension, cpp_files))
		{
			m_directory_files_path.push_back(string(entry.path().string()));
		}
	}
}

int DirectoryReader::GetFileCount()
{
	return m_directory_files_path.size();
}

string DirectoryReader::GetPath(int file_number)
{
	if ((signed)file_number > (signed)(m_directory_files_path.size() - 1))
	{
		return nullptr;
	}
	else
	{
		return m_directory_files_path[file_number];
	}
}
