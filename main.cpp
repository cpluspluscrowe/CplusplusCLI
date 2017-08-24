#include "Facility.h"
#include "ReadTextFile.h"
using namespace ExcelApplicationWrapper;
namespace ew = ExcelApplicationWrapper; 
using namespace Microsoft::Office::Interop::Excel;
namespace Excel = Microsoft::Office::Interop::Excel;

void ExportSupportFilesToExcel(ew::Workbook^ wb){
	ew::Worksheet^ ws = wb->Sheets["JCMS 4.1 Support Files"];
	int cnt = 3;
	for each(auto kv in JcmsDrawing::GetSupportFiles()){
		ws->Range("A" + cnt.ToString())->SetValue(kv.Key->GetNumber());
		ws->Range("B" + cnt.ToString())->SetValue(kv.Key->GetDescription());
		cnt += 1;
		for each(auto d in kv.Value){
			ws->Range("C" + cnt.ToString())->SetValue(d->GetNumber());
			ws->Range("D" + cnt.ToString())->SetValue("Support");
			cnt += 1;
		}
	}
}
void ExportFacilityDrawingsToExcel(ew::Workbook^ wb){
	int cnt = 3;
	ew::Worksheet^ ws = wb->Sheets["JCMS 4.1 Facility Drawings"];
	for each(auto kv in JcmsDrawing::GetFacilitiesContainingDrawing()){
		ws->Range("A" + cnt.ToString())->SetValue(kv.Key->GetNumber());
		ws->Range("B" + cnt.ToString())->SetValue(kv.Key->GetDescription());
		cnt += 1;
		for each(auto d in kv.Value){
			ws->Range("C" + cnt.ToString())->SetValue(d->GetNumber());
			ws->Range("D" + cnt.ToString())->SetValue("Facility");
			cnt += 1;
		}
	}
}
void ExportCaDrawingsToExcel(ew::Workbook^ wb){
	int cnt = 3;
	ew::Worksheet^ ws = wb->Sheets["JCMS 4.1 Ca Drawings"];
	for each(auto kv in JcmsDrawing::GetCaFiles()){
		ws->Range("A" + cnt.ToString())->SetValue(kv.Key->GetNumber());
		ws->Range("B" + cnt.ToString())->SetValue(kv.Key->GetDescription());
		cnt += 1;
		for each(auto d in kv.Value){
			for each(auto f in d->GetParentFacilities()){//assume all CA have facilities
				ws->Range("C" + cnt.ToString())->SetValue(f->GetNumber());
				ws->Range("D" + cnt.ToString())->SetValue(d->GetNumber());
				ws->Range("E" + cnt.ToString())->SetValue(d->GetDescription());
				cnt += 1;
			}
		}
	}
}
ew::ExcelApplication^ GetXl(){
	ew::ExcelApplication^ xlApp = gcnew ExcelApplication();
	Excel::Application^ xl = xlApp->GetWrappedExcelApplication();
	xl->Visible = true;
	return xlApp;
}
ew::Workbook^ GetWorkbook(ew::ExcelApplication^ xlApp){
	//ew::ExcelApplication^ xlApp = gcnew ExcelApplication();
	//Excel::Application^ xl = xlApp->GetWrappedExcelApplication();
	//xl->Visible = true;
	ew::Workbook^ wb = xlApp->Workbooks->Open("C:\\Users\\CCrowe\\Documents\\AFCS Folder\\New Draw CA List.xlsm");
	return wb;
}
void StoreResultsWithinExcel(){
	ew::ExcelApplication^ xl = GetXl();
	ew::Workbook^ wb = GetWorkbook(xl);
	ExportSupportFilesToExcel(wb);
	wb->Close(true);
	xl->GetWrappedExcelApplication()->Quit();

	xl = GetXl();
	wb = GetWorkbook(xl);
	ExportCaDrawingsToExcel(wb);
	wb->Close(true);
	xl->GetWrappedExcelApplication()->Quit();

	xl = GetXl();
	wb = GetWorkbook(xl);
	ExportFacilityDrawingsToExcel(wb);
	wb->Close(true);
	xl->GetWrappedExcelApplication()->Quit();
}

void FillJcmsStaticSupportFiles(Facility^ facility){

		for each(auto drawing in facility->GetFacilitySupportFiles()){
			JcmsDrawing^ draw = gcnew JcmsDrawing(drawing->GetNumber(), drawing->GetDescription());
			JcmsDrawing::AddSupportFileDrawing(draw, facility);
		}
}
void FillJcmsStaticFacilityDrawings(Facility^ facility){
		for each(JcmsDrawing^ drawing in facility->GetFacilityDrawings()){
			JcmsDrawing^ draw = gcnew JcmsDrawing(drawing->GetNumber(), drawing->GetDescription());
			JcmsDrawing::AddFacilityDrawing(draw, facility);
		}
	}
void FillJcmsStaticCaDrawings(Facility^ facility){
	for each(auto ca in facility->GetConstructionActivities()){
		for each(auto drawing in ca->GetDrawings()){
			JcmsDrawing^ draw = gcnew JcmsDrawing(drawing->GetNumber(), drawing->GetDescription());
			JcmsDrawing::AddCaDrawing(draw, ca);
		}
	}
}
void fillStaticFiles(){
	List<String^>^ facilities = ReadTextFile::GetFacilities();
	for each(auto facilityText in facilities){
		Facility^ facility = gcnew Facility(facilityText);
		FillJcmsStaticSupportFiles(facility);
		FillJcmsStaticFacilityDrawings(facility);
		FillJcmsStaticCaDrawings(facility);
	}
}

int main(){

	fillStaticFiles();
	StoreResultsWithinExcel();
}