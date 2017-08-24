#include "ConstructionActivity.h"
#include "Facility.h"

ConstructionActivity::ConstructionActivity(String^ number, String^ description)
{
	this->number = number;
	this->description = description;
	this->conn = gcnew SqlConnection("Server=OME-CND6435DR5;Database=JCMS_Local_41;Integrated Security = true");
	this->drawings = gcnew SortedSet<JcmsDrawing^>();
	this->facilities = gcnew SortedSet<Facility^>();
}

int ConstructionActivity::CompareTo(Object^ other){
	return String::Compare(this->number, ((ConstructionActivity^)other)->number);
}

SqlCommand^ ConstructionActivity::SetupDrawingSql(){
	String^ sql = R"(DECLARE @ele_id nvarchar(50);
		DECLARE @ele_name nvarchar(100);
		DECLARE @ele_descr nvarchar(100);
		DECLARE @type nvarchar(50);
		DECLARE @subtype nvarchar(50);
		DECLARE @FetchStatus int
		SET @ele_name = @number;
		SET @ele_id = (select element_id from element where element_nbr = @ele_name);
		SET @ele_descr = (select Element_Descr from element where element_nbr = @ele_name);

		SET @subtype = (SELECT Element_Type from Element where Element_Nbr = @ele_name);
		SELECT DISTINCT File_Nbr, File_Descr from JCMS_File WHERE File_Id in (SELECT File_Id FROM JCMS_File_Owner WHERE File_Owner_Id = @ele_id AND File_Owner_Obj_Type = @subtype) AND File_Class = 'DRAWING' ORDER BY File_Nbr ASC ;
		)";
	SqlCommand^ cmd = gcnew SqlCommand(sql, this->conn);
	cmd->Parameters->AddWithValue("@number", this->number);
	return cmd;
}

void ConstructionActivity::PopulateDrawings(){
	SqlCommand^ cmd = this->SetupDrawingSql();
	SqlDataReader^ reader = cmd->ExecuteReader();
	while (reader->Read()){
		array<Object^>^ colNames = gcnew array<Object^>(2);
		reader->GetValues(colNames);
		JcmsDrawing^ drawing = gcnew JcmsDrawing(colNames[0]->ToString(), colNames[1]->ToString());
		this->drawings->Add(drawing);
	}
	reader->Close();
}

SortedSet<JcmsDrawing^>^ ConstructionActivity::GetDrawings(){
	this->conn->Open();
	this->PopulateDrawings();
	this->conn->Close();
	return this->drawings;
}
String^ ConstructionActivity::GetNumber(){
	return this->number;
}
String^ ConstructionActivity::GetDescription(){
	return this->description;
}
SqlCommand^ ConstructionActivity::SetupFacilities(){
	String^ sql = R"(
		select element_nbr from element where element_id in (
		select Parent_Element_Id from Element_Hierarchy where Element_Id in (
		select element_id from element where element_nbr = @caNumber));
		)";
	
	SqlCommand^ cmd = gcnew SqlCommand(sql, this->conn);
	cmd->Parameters->AddWithValue("@caNumber", this->number);
	return cmd;
}
void ConstructionActivity::PopulateFacilities(){
	SqlCommand^ cmd = this->SetupFacilities();
	SqlDataReader^ reader = cmd->ExecuteReader();
	while (reader->Read()){
		array<Object^>^ colNames = gcnew array<Object^>(2);
		reader->GetValues(colNames);
		Facility^ facility = gcnew Facility(colNames[0]->ToString());
		this->facilities->Add(facility);
	}
	reader->Close();
}

SortedSet<Facility^>^ ConstructionActivity::GetParentFacilities(){
	this->conn->Open();
	this->PopulateFacilities();
	this->conn->Close();
	return this->facilities;
}
