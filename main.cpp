
#include "ProjectAnalyser.h"
int main()
{
	string path = "C:\\Users\\Gannusya\\Documents\\TEST2";
	ProjectAnalyser a(path);
	a.process(20);
	a.create_file();
	system("pause");
}