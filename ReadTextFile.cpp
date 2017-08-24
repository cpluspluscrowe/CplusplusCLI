#include "ReadTextFile.h"


ReadTextFile::ReadTextFile()
{
}
List<String^>^ ReadTextFile::GetFacilities()
{
	String^ path = "C:\\Users\\CCrowe\\Documents\\Visual Studio 2013\\Projects\\List Drawing and Parents\\Debug\\Facility_Names.txt";
	System::IO::StreamReader^ file = gcnew System::IO::StreamReader(path);
	List<String^>^ facilities = gcnew List<String^>();
	String^ line;
	while ((line = file->ReadLine()) != nullptr)
	{
		facilities->Add(line);
	}
	file->Close();
	return facilities;
}