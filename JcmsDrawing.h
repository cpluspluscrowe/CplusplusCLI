using namespace System;
using namespace System::Collections::Generic;
#include <cliext\map>
#include <string>

ref class ConstructionActivity;
ref class Facility;

#pragma once
public ref class JcmsDrawing : public IComparable ///Purpose: Any functions with Drawings
{
public:
	JcmsDrawing(String^ number,String^ description);
	~JcmsDrawing();
	!JcmsDrawing();
	void SetId(String^ id);
	void SetNumber(String^ number);
	void SetDescription(String^ description);
	String^ GetId();
	String^ GetNumber();
	String^ GetDescription();
	virtual int CompareTo(Object^ other);
	static SortedDictionary<String^, String^> DrawingMap;

	static void AddFacilityDrawing(JcmsDrawing^ drawing, Facility^ facility);
	static SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ GetFacilitiesContainingDrawing();

	static void AddSupportFileDrawing(JcmsDrawing^ drawing, Facility^ facility);
	static SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ GetSupportFiles();

	static void AddCaDrawing(JcmsDrawing^ drawing, ConstructionActivity^ ca);
	static SortedDictionary<JcmsDrawing^, SortedSet<ConstructionActivity^>^>^ GetCaFiles();
private:
	static SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ FacilitiesContainingDrawing = gcnew SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>();
	static SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ FacilitiesContainingSupportFile = gcnew SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>();
	static SortedDictionary<JcmsDrawing^, SortedSet<ConstructionActivity^>^>^ CaContainingDrawing = gcnew SortedDictionary<JcmsDrawing^, SortedSet<ConstructionActivity^>^>();

	String^ Id;
	String^ Number;
	String^ Description;
};
