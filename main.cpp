
#include "ProjectAnalyser.h"
int main()
{
	string file_path = "1.h";
	std::ifstream f(file_path);
	std::string res((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
	f.close();
	cout << res<<endl;
	//ProjectAnalyser a(path);
	//a.process(20);
	//a.create_file();
	Parser a(res, file_path);
	cout << a.info();
	system("pause");
}