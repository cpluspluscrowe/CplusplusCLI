#include "Facility.h"
Facility::Facility(String^ number)
{
	this->number = number;
	this->facilityDrawings = gcnew SortedSet<JcmsDrawing^>();
	this->facilitySupportFiles = gcnew SortedSet<JcmsDrawing^>();
	this->constructionActivities = gcnew SortedSet<ConstructionActivity^>();
	this->conn = gcnew SqlConnection("Server=OME-CND6435DR5;Database=JCMS_Local_41;Integrated Security = true");
}
SqlCommand^ Facility::SetupFacilitySupportFilesSql(){
	String^ sql = R"(DECLARE @ele_id nvarchar(50);
		DECLARE @type nvarchar(50);
		DECLARE @subtype nvarchar(50);
		DECLARE @facility nvarchar(100);
		DECLARE @facility_id int;
		SET @facility = @number;
		set @facility_id = (select element_id from element where Element_Nbr = @number);

		SET @subtype = (SELECT Element_Type from Element where Element_Nbr = @facility);
		SELECT DISTINCT File_Nbr, File_Descr from JCMS_File WHERE File_Id in (SELECT File_Id FROM JCMS_File_Owner WHERE File_Owner_Id = @facility_id AND File_Owner_Obj_Type = @subtype) AND File_Class = 'SUPPORT' ORDER BY File_Nbr ASC ;
		)";
	SqlCommand^ cmd = gcnew SqlCommand(sql, this->conn);
	cmd->Parameters->AddWithValue("@number", this->number);
	return cmd;
}
void Facility::PopulateSupportFiles(){
	SqlCommand^ cmd = this->SetupFacilitySupportFilesSql();
	SqlDataReader^ reader = cmd->ExecuteReader();
	while (reader->Read()){
		array<Object^>^ colNames = gcnew array<Object^>(3);
		reader->GetValues(colNames);
		JcmsDrawing^ drawing = gcnew JcmsDrawing(colNames[0]->ToString(), colNames[1]->ToString());
		this->facilitySupportFiles->Add(drawing);
	}
	reader->Close();
}

SqlCommand^ Facility::SetupFacilityDrawingsSql(){
	String^ sql = R"(DECLARE @ele_id nvarchar(50);
                DECLARE @type nvarchar(50);
                DECLARE @facility nvarchar(100);
                SET @facility = @number;
                SET @ele_id = (SELECT Element_Id from Element WHERE Element_Nbr = @facility);
                SET @type = (SELECT Element_Type from Element where Element_Nbr = @facility);
                SELECT DISTINCT File_Nbr, File_Descr from JCMS_File WHERE File_Id in 
                    (SELECT File_Id FROM JCMS_File_Owner WHERE File_Owner_Id = @ele_id  AND File_Owner_Obj_Type = @type) 
                    AND File_Class = 'DRAWING' ORDER BY File_Nbr ASC ;)";
	SqlCommand^ cmd = gcnew SqlCommand(sql, this->conn);
	cmd->Parameters->AddWithValue("@number", this->number);
	return cmd;
}

void Facility::PopulateFacilityDrawings(){
	SqlCommand^ cmd = this->SetupFacilityDrawingsSql();
	SqlDataReader^ reader = cmd->ExecuteReader();
	while (reader->Read()){
		array<Object^>^ colNames = gcnew array<Object^>(2);
		reader->GetValues(colNames);
		JcmsDrawing^ drawing = gcnew JcmsDrawing(colNames[0]->ToString(), colNames[1]->ToString());
		this->facilityDrawings->Add(drawing);
	}
	reader->Close();
}

SortedSet<JcmsDrawing^>^ Facility::GetFacilityDrawings(){
	this->conn->Open();
	this->PopulateFacilityDrawings();
	this->conn->Close();
	return this->facilityDrawings;
}
SortedSet<JcmsDrawing^>^ Facility::GetFacilitySupportFiles(){
	this->conn->Open();
	this->PopulateSupportFiles();
	this->conn->Close();
	return this->facilitySupportFiles;
}

Facility::~Facility(){
}
int Facility::CompareTo(Object^ other){
	return String::Compare(this->number, ((Facility^)other)->number);
}

SortedSet<ConstructionActivity^>^ Facility::GetConstructionActivities(){
	this->conn->Open();
	this->PopulateConstructionActivities();
	this->conn->Close();
	return this->constructionActivities;
}

SqlCommand^ Facility::SetupConstructionActivitySql(){
	String^ sql = R"(DECLARE @ele_id nvarchar(50);
		DECLARE @ele_name nvarchar(100);
		DECLARE @ele_descr nvarchar(100);
		DECLARE @FetchStatus int
		DECLARE CA_cursor CURSOR  
			FOR select Element_Id, Element_Nbr, Element_Descr FROM Element WHERE Element_Id in 
			(SELECT Element_Id FROM Element_Hierarchy WHERE Parent_Element_Id In 
			(SELECT Element_Id FROM Element WHERE Element_Nbr = @facilityNumber)) ORDER BY Element_Nbr ASC;

		OPEN CA_cursor  
		FETCH NEXT FROM CA_cursor INTO @ele_id, @ele_name,@ele_descr
		WHILE @@FETCH_STATUS = 0
			BEGIN
				SELECT @ele_name, @ele_descr
				FETCH NEXT FROM CA_cursor INTO @ele_id, @ele_name, @ele_descr
			END
		CLOSE CA_cursor;
		DEALLOCATE CA_cursor;
		)";
	SqlCommand^ cmd = gcnew SqlCommand(sql, this->conn);
	cmd->Parameters->AddWithValue("@facilityNumber", this->number);
	return cmd;
}

void Facility::PopulateConstructionActivities(){
	SqlCommand^ cmd = this->SetupConstructionActivitySql();
	SqlDataReader^ reader = cmd->ExecuteReader();
	while (reader->Read()){
		array<Object^>^ colNames = gcnew array<Object^>(2);
		reader->GetValues(colNames);
		ConstructionActivity^ ca = gcnew ConstructionActivity(colNames[0]->ToString(), colNames[1]->ToString());
		this->constructionActivities->Add(ca);
	}
	reader->Close();
}
String^ Facility::GetNumber(){
	return this->number;
}