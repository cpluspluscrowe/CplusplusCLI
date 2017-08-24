#include "JcmsDrawing.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data::SqlClient;
using namespace System::Diagnostics;

ref class Facility;

#pragma once
public ref class ConstructionActivity : public IComparable
{
public:
	ConstructionActivity(String^ number, String^ description);
	virtual int CompareTo(Object^ other);
	SortedSet<JcmsDrawing^>^ GetDrawings();
	String^ GetNumber();
	String^ GetDescription();
	SortedSet<Facility^>^ GetParentFacilities();
private:
	SqlCommand^ SetupFacilities();
	void PopulateFacilities();
	SqlCommand^ SetupDrawingSql();
	void PopulateDrawings();
	SortedSet<JcmsDrawing^>^ drawings;
	SortedSet<Facility^>^ facilities;
	String^ number;
	String^ description;
	SqlConnection^ conn;
};

