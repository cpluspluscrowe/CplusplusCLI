using namespace System;
using namespace System::Data::SqlClient;
using namespace System::Text;
using namespace System::Collections::Generic;
#include "JcmsDrawing.h"
#include "ConstructionActivity.h"
#pragma once
public ref class Facility : public IComparable
{
public:
	Facility(String^ number);
	~Facility();
	SortedSet<JcmsDrawing^>^ GetFacilityDrawings();
	SortedSet<JcmsDrawing^>^ GetFacilitySupportFiles();
	SortedSet<ConstructionActivity^>^ GetConstructionActivities();
	virtual int CompareTo(Object^ other);
	String^ GetNumber();
private:

	void PopulateSupportFiles();
	SqlCommand^ SetupFacilitySupportFilesSql();
	void PopulateFacilityDrawings();
	SqlCommand^ SetupFacilityDrawingsSql();
	String^ number;
	SortedSet<JcmsDrawing^>^ facilityDrawings;
	SortedSet<JcmsDrawing^>^ facilitySupportFiles;
	SortedSet<ConstructionActivity^>^ constructionActivities;
	void PopulateConstructionActivities();
	SqlCommand^ SetupConstructionActivitySql();
	SqlConnection^ conn;
};