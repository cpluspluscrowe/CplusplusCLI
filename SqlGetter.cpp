#include "SqlGetter.h"


SqlGetter::SqlGetter()
{
}
SqlGetter::~SqlGetter()
{
}
void SqlGetter::SetupFacilities(){
	std::string path = R"(C:\Users\CCrowe\Documents\Visual Studio 2013\Projects\List Drawing then Parents\Debug\Facility_Names.txt)";
	std::ifstream file(path);
	std::string facility;
	for (std::string line; std::getline(file, line);)
	{
		if (!line.empty()){
			this->facilities.push_back(gcnew String(line.c_str()));
		}
	}
}