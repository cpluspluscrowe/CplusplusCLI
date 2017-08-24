#include "JcmsDrawing.h"
#include "Facility.h"
#include "ConstructionActivity.h"

JcmsDrawing::JcmsDrawing(String^ number, String^ description)
{
	this->Number = number;
	this->Description = description;
}
JcmsDrawing::~JcmsDrawing(){
	this->!JcmsDrawing();
}
JcmsDrawing::!JcmsDrawing(){
	
}
void JcmsDrawing::SetId(String^ id){
	this->Id = id;
}
void JcmsDrawing::SetNumber(String^ number){
	this->Number = number;
}
void JcmsDrawing::SetDescription(String^ description){
	this->Description = description;
}
String^ JcmsDrawing::GetId(){
	return this->Id;
}
String^ JcmsDrawing::GetNumber(){
	return this->Number;
}
String^ JcmsDrawing::GetDescription(){
	return this->Description;
}
int JcmsDrawing::CompareTo(Object^ other){
	return String::Compare(this->Number, ((JcmsDrawing^)other)->Number);
}
void JcmsDrawing::AddFacilityDrawing(JcmsDrawing^ drawing,Facility^ facility){
	if (JcmsDrawing::FacilitiesContainingDrawing->ContainsKey(drawing)){
		SortedSet<Facility^>^ facilitySet;
		JcmsDrawing::FacilitiesContainingDrawing->TryGetValue(drawing, facilitySet);
		facilitySet->Add(facility);
	}
	else{
		SortedSet<Facility^>^ facilitySet = gcnew SortedSet<Facility^>();
		facilitySet->Add(facility);
		JcmsDrawing::FacilitiesContainingDrawing->Add(drawing, facilitySet);
	}
}
SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ JcmsDrawing::GetFacilitiesContainingDrawing(){
	return JcmsDrawing::FacilitiesContainingDrawing;
}
void JcmsDrawing::AddSupportFileDrawing(JcmsDrawing^ drawing, Facility^ facility){
	if (JcmsDrawing::FacilitiesContainingSupportFile->ContainsKey(drawing)){
		SortedSet<Facility^>^ facilitySet;
		JcmsDrawing::FacilitiesContainingSupportFile->TryGetValue(drawing, facilitySet);
		facilitySet->Add(facility);
	}
	else{
		SortedSet<Facility^>^ facilitySet = gcnew SortedSet<Facility^>();
		facilitySet->Add(facility);
		JcmsDrawing::FacilitiesContainingSupportFile->Add(drawing, facilitySet);
	}
}
SortedDictionary<JcmsDrawing^, SortedSet<Facility^>^>^ JcmsDrawing::GetSupportFiles(){
	return JcmsDrawing::FacilitiesContainingSupportFile;
}
void JcmsDrawing::AddCaDrawing(JcmsDrawing^ drawing, ConstructionActivity^ ca){
	if (JcmsDrawing::CaContainingDrawing->ContainsKey(drawing)){
		SortedSet<ConstructionActivity^>^ caSet;
		JcmsDrawing::CaContainingDrawing->TryGetValue(drawing, caSet);
		caSet->Add(ca);
	}
	else{
		SortedSet<ConstructionActivity^>^ caSet = gcnew SortedSet<ConstructionActivity^>();
		caSet->Add(ca);
		JcmsDrawing::CaContainingDrawing->Add(drawing, caSet);
	}
}
SortedDictionary<JcmsDrawing^, SortedSet<ConstructionActivity^>^>^ JcmsDrawing::GetCaFiles(){
	return JcmsDrawing::CaContainingDrawing;
}