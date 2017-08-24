using namespace System;
using namespace System::Data::SqlClient;
#include <string>
#include <vector>
#include <fstream>
#include <cliext/vector>

#pragma once
public ref class SqlGetter
{
public:
	SqlGetter();
	~SqlGetter();
	void SetupFacilities();
private:
	SqlConnection^ conn;
	cliext::vector<String^> facilities;
};

