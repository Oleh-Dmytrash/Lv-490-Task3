#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include<fstream>
#include"FilesHandler.h"
using namespace std;
using namespace filesystem;







int main()
{
	FilesHandler a("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST");
	string str=a.ParseFiles();
	cout << str << endl;


	return 0;
}

