#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


using namespace std;
using namespace ROOT::VecOps; // para definir vectores como  RVec<double>>("vecCol");


vector<vector<double_t> > Response_function_matrix_lin_spec_2023(){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

//~ TFile *E01_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
//~ TFile *E02_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
//~ TFile *E03_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_3_4cmHDPE_VV.root");
//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
//~ TFile *E05_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root");
//~ TFile *E06_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
//~ TFile *E07_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
//~ TFile *E08_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_8_1inchBHDPE_10cmHDPE_VV.root");
//~ TFile *E09_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_9_20cmBHDPE_1.0inch_VV.root");
//~ TFile *E10_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
//~ TFile *E11_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
//~ TFile *E12_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_12_Pb_10cmBHDPEcore_VV.root");
//~ TFile *E13_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_13_1inchBHDPE_15cmGraphite_VV.root");
//~ TFile *E14_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_14_inchBHDPE_15cmHDPE_VV.root");
//~ TFile *E15_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
//~ TFile *E16_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_16_Naked_1inch_VV.root");

TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_3_4cmHDPE_VV.root");
TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root");
TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_8_1inchBHDPE_10cmHDPE_VV.root");
TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_9_20cmBHDPE_1.0inch_VV.root");
TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_12_Pb_10cmBHDPEcore_VV.root");
TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_13_1inchBHDPE_15cmGraphite_VV.root");
TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_14_inchBHDPE_15cmHDPE_VV.root");
TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_16_Naked_1inch_VV.root");

TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE");
TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE");
TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE");
TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE");
TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE");
TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm");
TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm");
TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore");
TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite");
TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE");
TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch");

int binning = h_d01->GetNbinsX();
//~ cout << "Binning en x: " << binning << endl;

vector<double> RF_d01_vec;
vector<double> RF_d02_vec;
vector<double> RF_d03_vec;
vector<double> RF_d04_vec;
vector<double> RF_d05_vec;
vector<double> RF_d06_vec;
vector<double> RF_d07_vec;
vector<double> RF_d08_vec;
vector<double> RF_d09_vec;
vector<double> RF_d10_vec;
vector<double> RF_d11_vec;
vector<double> RF_d12_vec;
vector<double> RF_d13_vec;
vector<double> RF_d14_vec;
vector<double> RF_d15_vec;
vector<double> RF_d16_vec;


for(int i =0; i<binning; i++)
{
	 if(h_d01->GetBinContent(i+1)!=0.0)
		{
			 RF_d01_vec.push_back(h_d01->GetBinContent(i+1));
			 //~ //cout << i << "  " << h_d01->GetBinContent(i+1) << endl;
			 RF_d02_vec.push_back(h_d02->GetBinContent(i+1));
			 RF_d03_vec.push_back(h_d03->GetBinContent(i+1));
			 RF_d04_vec.push_back(h_d04->GetBinContent(i+1));			 
			 RF_d05_vec.push_back(h_d05->GetBinContent(i+1));
			 RF_d06_vec.push_back(h_d06->GetBinContent(i+1));			 
			 RF_d07_vec.push_back(h_d07->GetBinContent(i+1));
			 RF_d08_vec.push_back(h_d08->GetBinContent(i+1));
			 RF_d09_vec.push_back(h_d09->GetBinContent(i+1));
			 RF_d10_vec.push_back(h_d10->GetBinContent(i+1));
			 RF_d11_vec.push_back(h_d11->GetBinContent(i+1));
			 RF_d12_vec.push_back(h_d12->GetBinContent(i+1));
			 RF_d13_vec.push_back(h_d13->GetBinContent(i+1));
			 RF_d14_vec.push_back(h_d14->GetBinContent(i+1));
			 RF_d15_vec.push_back(h_d15->GetBinContent(i+1));
			 RF_d16_vec.push_back(h_d16->GetBinContent(i+1));
	    }
	 else{
		   RF_d01_vec.push_back(1.E-23);
		   RF_d02_vec.push_back(1.E-23);
		   RF_d03_vec.push_back(1.E-23);
		   RF_d04_vec.push_back(1.E-23);
		   RF_d05_vec.push_back(1.E-23);
		   RF_d06_vec.push_back(1.E-23);
		   RF_d07_vec.push_back(1.E-23);
		   RF_d08_vec.push_back(1.E-23);
		   RF_d09_vec.push_back(1.E-23);
		   RF_d10_vec.push_back(1.E-23);
		   RF_d11_vec.push_back(1.E-23);
		   RF_d12_vec.push_back(1.E-23);
		   RF_d13_vec.push_back(1.E-23);
		   RF_d14_vec.push_back(1.E-23);
		   RF_d15_vec.push_back(1.E-23);
		   RF_d16_vec.push_back(1.E-23); 
	     }
}


	 R.push_back(RF_d01_vec); 
	 R.push_back(RF_d02_vec);
	 R.push_back(RF_d03_vec);
	 R.push_back(RF_d04_vec); 
	 R.push_back(RF_d05_vec);
	 R.push_back(RF_d06_vec);	 
	 R.push_back(RF_d07_vec); 
	 R.push_back(RF_d08_vec);
	 R.push_back(RF_d09_vec);
	 R.push_back(RF_d10_vec); 
	 R.push_back(RF_d11_vec);
	 R.push_back(RF_d12_vec);
	 R.push_back(RF_d13_vec); 
	 R.push_back(RF_d14_vec);
	 R.push_back(RF_d15_vec);
	 R.push_back(RF_d16_vec);

E01_file->Close();
E02_file->Close();
E03_file->Close();
E04_file->Close();
E05_file->Close();
E06_file->Close();
E07_file->Close();
E08_file->Close();
E09_file->Close();
E10_file->Close();
E11_file->Close();
E12_file->Close();
E13_file->Close();
E14_file->Close();
E15_file->Close();
E16_file->Close();
delete E01_file;
delete E02_file;
delete E03_file;
delete E04_file;
delete E05_file;
delete E06_file;
delete E07_file;
delete E08_file;
delete E09_file;
delete E10_file;
delete E11_file;
delete E12_file;
delete E13_file;
delete E14_file;
delete E15_file;
delete E16_file;

return R;

}

void RF_CEFNEN_spectrometer_root_file(){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/
		
TFile *E01_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_1_12cmHDPE_VV.root");
TFile *E02_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_2_10cmHDPE_VV.root");
TFile *E03_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_3_4cmHDPE_VV.root");
TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_4_CylinderHDPE_VV.root");
TFile *E05_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root");
TFile *E06_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_6_18cmHDPE_VV.root");
TFile *E07_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_7_20cmHDPE_VV.root");
TFile *E08_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_8_1inchBHDPE_10cmHDPE_VV.root");
TFile *E09_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_9_20cmBHDPE_1.0inch_VV.root");
TFile *E10_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_10_Cylinder_4cm_VV.root");
TFile *E11_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_11_Cylinder_3cm_VV.root");
TFile *E12_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_12_Pb_10cmBHDPEcore_VV.root");
TFile *E13_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_13_1inchBHDPE_15cmGraphite_VV.root");
TFile *E14_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_14_inchBHDPE_15cmHDPE_VV.root");
TFile *E15_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_15_24cmHDPE_VV.root");
TFile *E16_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer/Efi_16_Naked_1inch_VV.root");

TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE");
TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE");
TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE");
TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE");
TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE");
TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm");
TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm");
TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore");
TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite");
TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE");
TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch");

int binning = h_d01->GetNbinsX();
cout << "Binning en x: " << binning << endl;

vector<double> RF_d01_vec;
vector<double> RF_d02_vec;
vector<double> RF_d03_vec;
vector<double> RF_d04_vec;
vector<double> RF_d05_vec;
vector<double> RF_d06_vec;
vector<double> RF_d07_vec;
vector<double> RF_d08_vec;
vector<double> RF_d09_vec;
vector<double> RF_d10_vec;
vector<double> RF_d11_vec;
vector<double> RF_d12_vec;
vector<double> RF_d13_vec;
vector<double> RF_d14_vec;
vector<double> RF_d15_vec;
vector<double> RF_d16_vec;


for(int i =0; i<binning; i++)
{
	 if(h_d01->GetBinContent(i+1)!=0.0)
		{
			 RF_d01_vec.push_back(h_d01->GetBinContent(i+1));
			 //~ cout << i << "  " << h_d01->GetBinContent(i+1) << endl;
			 RF_d02_vec.push_back(h_d02->GetBinContent(i+1));
			 RF_d03_vec.push_back(h_d03->GetBinContent(i+1));
			 RF_d04_vec.push_back(h_d04->GetBinContent(i+1));			 
			 RF_d05_vec.push_back(h_d05->GetBinContent(i+1));
			 RF_d06_vec.push_back(h_d06->GetBinContent(i+1));			 
			 RF_d07_vec.push_back(h_d07->GetBinContent(i+1));
			 RF_d08_vec.push_back(h_d08->GetBinContent(i+1));
			 RF_d09_vec.push_back(h_d09->GetBinContent(i+1));
			 RF_d10_vec.push_back(h_d10->GetBinContent(i+1));
			 RF_d11_vec.push_back(h_d11->GetBinContent(i+1));
			 RF_d12_vec.push_back(h_d12->GetBinContent(i+1));
			 RF_d13_vec.push_back(h_d13->GetBinContent(i+1));
			 RF_d14_vec.push_back(h_d14->GetBinContent(i+1));
			 RF_d15_vec.push_back(h_d15->GetBinContent(i+1));
			 RF_d16_vec.push_back(h_d16->GetBinContent(i+1));
	    }
	 else{
		   RF_d01_vec.push_back(1.E-23);
		   RF_d02_vec.push_back(1.E-23);
		   RF_d03_vec.push_back(1.E-23);
		   RF_d04_vec.push_back(1.E-23);
		   RF_d05_vec.push_back(1.E-23);
		   RF_d06_vec.push_back(1.E-23);
		   RF_d07_vec.push_back(1.E-23);
		   RF_d08_vec.push_back(1.E-23);
		   RF_d09_vec.push_back(1.E-23);
		   RF_d10_vec.push_back(1.E-23);
		   RF_d11_vec.push_back(1.E-23);
		   RF_d12_vec.push_back(1.E-23);
		   RF_d13_vec.push_back(1.E-23);
		   RF_d14_vec.push_back(1.E-23);
		   RF_d15_vec.push_back(1.E-23);
		   RF_d16_vec.push_back(1.E-23); 
	     }
}


//~ auto seed_flux_expacs_csv ="/home/flopez/Dropbox/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
auto E_cut_LCO = seed_rdf.Range(0, 151, 1); // pick an event every 1 entries from 0 to 150 because the last is excluded, that is 151 .


auto df_energy_vec = E_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
auto d_cut_entries = E_cut_LCO.Count().GetValue();
cout << "Entries number of LCO seed : " << d_cut_entries << endl;

ROOT::RDataFrame df_spec(150);

int rowid_e = 0;
int rowid_rf_d01 = 0;
int rowid_rf_d02 = 0;
int rowid_rf_d03 = 0;
int rowid_rf_d04 = 0;
int rowid_rf_d05 = 0;
int rowid_rf_d06 = 0;
int rowid_rf_d07 = 0;
int rowid_rf_d08 = 0;
int rowid_rf_d09 = 0;
int rowid_rf_d10 = 0;
int rowid_rf_d11 = 0;
int rowid_rf_d12 = 0;
int rowid_rf_d13 = 0;
int rowid_rf_d14 = 0;
int rowid_rf_d15 = 0;
int rowid_rf_d16 = 0;

auto df_final = df_spec.Define("energy", [&]() {
						  auto E_elem =  df_energy_vec[rowid_e];
						  rowid_e++;
						  return E_elem;
						})
						.Define("RF_01", [&]() {
						  auto RF_d01_elem =  RF_d01_vec[rowid_rf_d01];
						  rowid_rf_d01++;
						  return RF_d01_elem;
						})
						.Define("RF_02", [&]() {
						  auto RF_d02_elem =  RF_d02_vec[rowid_rf_d02];
						  rowid_rf_d02++;
						  return RF_d02_elem;
						})
						.Define("RF_03", [&]() {
						  auto RF_d03_elem =  RF_d03_vec[rowid_rf_d03];
						  rowid_rf_d03++;
						  return RF_d03_elem;
						})
						.Define("RF_04", [&]() {
						  auto RF_d04_elem =  RF_d04_vec[rowid_rf_d04];
						  rowid_rf_d04++;
						  return RF_d04_elem;
						})
						.Define("RF_05", [&]() {
						  auto RF_d05_elem =  RF_d05_vec[rowid_rf_d05];
						  rowid_rf_d05++;
						  return RF_d05_elem;
						})
						.Define("RF_06", [&]() {
						  auto RF_d06_elem =  RF_d06_vec[rowid_rf_d06];
						  rowid_rf_d06++;
						  return RF_d06_elem;
						})
						.Define("RF_07", [&]() {
						  auto RF_d07_elem =  RF_d07_vec[rowid_rf_d07];
						  rowid_rf_d07++;
						  return RF_d07_elem;
						})
						.Define("RF_08", [&]() {
						  auto RF_d08_elem =  RF_d08_vec[rowid_rf_d08];
						  rowid_rf_d08++;
						  return RF_d08_elem;
						})
						.Define("RF_09", [&]() {
						  auto RF_d09_elem =  RF_d09_vec[rowid_rf_d09];
						  rowid_rf_d09++;
						  return RF_d09_elem;
						})
						.Define("RF_10", [&]() {
						  auto RF_d10_elem =  RF_d10_vec[rowid_rf_d10];
						  rowid_rf_d10++;
						  return RF_d10_elem;
						})
						.Define("RF_11", [&]() {
						  auto RF_d11_elem =  RF_d11_vec[rowid_rf_d11];
						  rowid_rf_d11++;
						  return RF_d11_elem;
						})
						.Define("RF_12", [&]() {
						  auto RF_d12_elem =  RF_d12_vec[rowid_rf_d12];
						  rowid_rf_d12++;
						  return RF_d12_elem;
						})
						.Define("RF_13", [&]() {
						  auto RF_d13_elem =  RF_d13_vec[rowid_rf_d13];
						  rowid_rf_d13++;
						  return RF_d13_elem;
						})
						.Define("RF_14", [&]() {
						  auto RF_d14_elem =  RF_d14_vec[rowid_rf_d14];
						  rowid_rf_d14++;
						  return RF_d14_elem;
						})
						.Define("RF_15", [&]() {
						  auto RF_d15_elem =  RF_d15_vec[rowid_rf_d15];
						  rowid_rf_d15++;
						  return RF_d15_elem;
						})
						.Define("RF_16", [&]() {
						  auto RF_d16_elem =  RF_d16_vec[rowid_rf_d16];
						  rowid_rf_d16++;
						  return RF_d16_elem;
						});

//~ cout << RF_d01_vec.size() << endl;
//~ for (int j=0; j<RF_d01_vec.size();j++)
//~ {
	//~ cout << j << " " << RF_d01_vec[j] << endl;
//~ }

df_final.Snapshot("Response_function_tree","Response_function_CEFNEN.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


}


vector<vector<double_t> > Response_function_matrix_fm()
{
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

/**Generamos archivos .root de cada csv file de funcion respuesta**/
string path_files = "./Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/";
auto response_function_csv_E01 =path_files+"E1_12cmHDPE.csv";
auto response_function_csv_E02 =path_files+"E2_10cmHDPE.csv";
auto response_function_csv_E03 =path_files+"E3_4cmHDPE.csv";
auto response_function_csv_E04 =path_files+"E4_CylinderHDPE.csv";
auto response_function_csv_E05 =path_files+"E5_Cylinder7mmAl_1.8cmBHDPECore.csv";
auto response_function_csv_E06 =path_files+"E6_18cmHDPE.csv";
auto response_function_csv_E07 =path_files+"E7_20cmHDPE.csv";
auto response_function_csv_E08 =path_files+"E8_1inchBHDPE_10cmHDPE.csv";
auto response_function_csv_E09 =path_files+"E9_20cmBHDPE_2.5inch.csv";
auto response_function_csv_E10 =path_files+"E10_Cylinder_4cm.csv";
auto response_function_csv_E11 =path_files+"E11_Cylinder_3cm.csv";
auto response_function_csv_E12 =path_files+"E12_Pb_10cmBHDPEcore.csv";
auto response_function_csv_E13 =path_files+"E13_1inchBHDPE_15cmGraphite.csv";
auto response_function_csv_E14 =path_files+"E14_inchBHDPE_15cmHDPE.csv";
auto response_function_csv_E15 =path_files+"E15_24cmHDPE.csv";
auto response_function_csv_E16 =path_files+"E16_Naked_1inch.csv";

char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"entry",double_type},{"rf_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)

auto RF_rdf_E01 = ROOT::RDF::FromCSV(response_function_csv_E01,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E02 = ROOT::RDF::FromCSV(response_function_csv_E02,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E03 = ROOT::RDF::FromCSV(response_function_csv_E03,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E04 = ROOT::RDF::FromCSV(response_function_csv_E04,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E05 = ROOT::RDF::FromCSV(response_function_csv_E05,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E06 = ROOT::RDF::FromCSV(response_function_csv_E06,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E07 = ROOT::RDF::FromCSV(response_function_csv_E07,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E08 = ROOT::RDF::FromCSV(response_function_csv_E08,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E09 = ROOT::RDF::FromCSV(response_function_csv_E09,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E10 = ROOT::RDF::FromCSV(response_function_csv_E10,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E11 = ROOT::RDF::FromCSV(response_function_csv_E11,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E12 = ROOT::RDF::FromCSV(response_function_csv_E12,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E13 = ROOT::RDF::FromCSV(response_function_csv_E13,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E14 = ROOT::RDF::FromCSV(response_function_csv_E14,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E15 = ROOT::RDF::FromCSV(response_function_csv_E15,true,delimiter,-1, std::move(msdata_map));
auto RF_rdf_E16 = ROOT::RDF::FromCSV(response_function_csv_E16,true,delimiter,-1, std::move(msdata_map));

RF_rdf_E01.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E01.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E02.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E02.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E03.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E03.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E04.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E04.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E05.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E05.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E06.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E06.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E07.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E07.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E08.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E08.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E09.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E09.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E10.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E10.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E11.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E11.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E12.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E12.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E13.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E13.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E14.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E14.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E15.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E15.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
RF_rdf_E16.Snapshot("response_function","/home/flopez/LIN/TESIS_DOC/Analysis/deconv/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/RF_rdf_E16.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


/*Generamos el vector de funcion respuesta*/
auto df_seed_flux_vec_E01 = RF_rdf_E01.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E02 = RF_rdf_E02.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E03 = RF_rdf_E03.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E04 = RF_rdf_E04.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E05 = RF_rdf_E05.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E06 = RF_rdf_E06.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E07 = RF_rdf_E07.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E08 = RF_rdf_E08.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E09 = RF_rdf_E09.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E10 = RF_rdf_E10.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E11 = RF_rdf_E11.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E12 = RF_rdf_E12.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E13 = RF_rdf_E13.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E14 = RF_rdf_E14.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E15 = RF_rdf_E15.Take<double>("rf_value").GetValue();
auto df_seed_flux_vec_E16 = RF_rdf_E16.Take<double>("rf_value").GetValue();

		/*Cargamos las eficiencias absolutas al vector de vectores R*/	
		R.push_back(df_seed_flux_vec_E01);
		R.push_back(df_seed_flux_vec_E02);
		R.push_back(df_seed_flux_vec_E03);
		R.push_back(df_seed_flux_vec_E04);
		R.push_back(df_seed_flux_vec_E05);
		R.push_back(df_seed_flux_vec_E06);
		R.push_back(df_seed_flux_vec_E07);
		R.push_back(df_seed_flux_vec_E08);
		R.push_back(df_seed_flux_vec_E09);
		R.push_back(df_seed_flux_vec_E10);
		R.push_back(df_seed_flux_vec_E11);
		R.push_back(df_seed_flux_vec_E12);
		R.push_back(df_seed_flux_vec_E13);
		R.push_back(df_seed_flux_vec_E14);
		R.push_back(df_seed_flux_vec_E15);
		R.push_back(df_seed_flux_vec_E16);
		
	
/*Las entradas cero de la funcion respuesta las llenamos con 1.E-23  */
		for(auto & v1 : R ) 
			{
				for(auto &v : v1)
					{
						if(v==0.0 ) v=1.E-23;
					}
			}
	
return R;
	
	}

vector<vector<double_t> > neutrons_count_matrix(string campaign, int time){

vector< vector<Double_t>> neutrons_count_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root";
		}
}

if(time==60)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
		}
}

ROOT::RDataFrame df_NC("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

auto df_NC_E01 = df_NC.Take<int>("NEUrate_D01").GetValue();
auto df_NC_E02 = df_NC.Take<int>("NEUrate_D02").GetValue();
auto df_NC_E03 = df_NC.Take<int>("NEUrate_D03").GetValue();
auto df_NC_E04 = df_NC.Take<int>("NEUrate_D04").GetValue();
auto df_NC_E05 = df_NC.Take<int>("NEUrate_D05").GetValue();
auto df_NC_E06 = df_NC.Take<int>("NEUrate_D06").GetValue();
auto df_NC_E07 = df_NC.Take<int>("NEUrate_D07").GetValue();
auto df_NC_E08 = df_NC.Take<int>("NEUrate_D08").GetValue();
auto df_NC_E09 = df_NC.Take<int>("NEUrate_D09").GetValue();
auto df_NC_E10 = df_NC.Take<int>("NEUrate_D10").GetValue();
auto df_NC_E11 = df_NC.Take<int>("NEUrate_D11").GetValue();
auto df_NC_E12 = df_NC.Take<int>("NEUrate_D12").GetValue();
auto df_NC_E13 = df_NC.Take<int>("NEUrate_D13").GetValue();
auto df_NC_E14 = df_NC.Take<int>("NEUrate_D14").GetValue();
auto df_NC_E15 = df_NC.Take<int>("NEUrate_D15").GetValue();
auto df_NC_E16 = df_NC.Take<int>("NEUrate_D16").GetValue();

/****Llenamos la matiz de COUNTING RATES****/
for (int i=0; i<df_NC_E01.size();i++)
	{
        vector<double> row_nc_matrix; /*vector de largo 16: [CR_E01[0],...,CR_E02[0]]*/
       //~ double r;
		//~ if(time==15){r=1.;}
		//~ if(time==60){r=1.;}
			
			row_nc_matrix.push_back((double)df_NC_E01[i]);
			row_nc_matrix.push_back((double)df_NC_E02[i]);
			row_nc_matrix.push_back((double)df_NC_E03[i]);
			row_nc_matrix.push_back((double)df_NC_E04[i]);
			row_nc_matrix.push_back((double)df_NC_E05[i]);
			row_nc_matrix.push_back((double)df_NC_E06[i]);
			row_nc_matrix.push_back((double)df_NC_E07[i]);
			row_nc_matrix.push_back((double)df_NC_E08[i]);
			row_nc_matrix.push_back((double)df_NC_E09[i]);
			row_nc_matrix.push_back((double)df_NC_E10[i]);
			row_nc_matrix.push_back((double)df_NC_E11[i]);
			row_nc_matrix.push_back((double)df_NC_E12[i]);
			row_nc_matrix.push_back((double)df_NC_E13[i]);
			row_nc_matrix.push_back((double)df_NC_E14[i]);
			row_nc_matrix.push_back((double)df_NC_E15[i]);
			row_nc_matrix.push_back((double)df_NC_E16[i]);
									
			neutrons_count_matrix.push_back(row_nc_matrix);
	
	}


/*visualizamos las entradas por fila*/
//~ for (unsigned int row = 0; row < counting_rate_matrix.size(); row++) {
    //~ std::cout << "Row " << row << ": ";
    //~ for (double value : counting_rate_matrix[row]) {
      //~ std::cout << value << " ";
    //~ }
    //~ std::cout << std::endl;
    //~ }

return neutrons_count_matrix;

}

vector<vector<double_t> > E_neutrons_count_matrix(string campaign,int time){

vector< vector<Double_t>> E_neutrons_count_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root";
		}
}

if(time==60)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
		}
}

ROOT::RDataFrame df_NC("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

auto df_NC_E01 = df_NC.Take<int>("NEUrate_D01").GetValue();
auto df_NC_E02 = df_NC.Take<int>("NEUrate_D02").GetValue();
auto df_NC_E03 = df_NC.Take<int>("NEUrate_D03").GetValue();
auto df_NC_E04 = df_NC.Take<int>("NEUrate_D04").GetValue();
auto df_NC_E05 = df_NC.Take<int>("NEUrate_D05").GetValue();
auto df_NC_E06 = df_NC.Take<int>("NEUrate_D06").GetValue();
auto df_NC_E07 = df_NC.Take<int>("NEUrate_D07").GetValue();
auto df_NC_E08 = df_NC.Take<int>("NEUrate_D08").GetValue();
auto df_NC_E09 = df_NC.Take<int>("NEUrate_D09").GetValue();
auto df_NC_E10 = df_NC.Take<int>("NEUrate_D10").GetValue();
auto df_NC_E11 = df_NC.Take<int>("NEUrate_D11").GetValue();
auto df_NC_E12 = df_NC.Take<int>("NEUrate_D12").GetValue();
auto df_NC_E13 = df_NC.Take<int>("NEUrate_D13").GetValue();
auto df_NC_E14 = df_NC.Take<int>("NEUrate_D14").GetValue();
auto df_NC_E15 = df_NC.Take<int>("NEUrate_D15").GetValue();
auto df_NC_E16 = df_NC.Take<int>("NEUrate_D16").GetValue();

/****Llenamos la matiz de COUNTING RATES****/
for (int i=0; i<df_NC_E01.size();i++)
	{
        vector<double> row_nc_matrix; /*vector de largo 16: [CR_E01[0],...,CR_E02[0]]*/
        
			row_nc_matrix.push_back(sqrt((double)df_NC_E01[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E02[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E03[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E04[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E05[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E06[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E07[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E08[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E09[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E10[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E11[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E12[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E13[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E14[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E15[i]));
			row_nc_matrix.push_back(sqrt((double)df_NC_E16[i]));
									
			E_neutrons_count_matrix.push_back(row_nc_matrix);
	
	}
	
return E_neutrons_count_matrix;

}

vector<vector<double_t> > Counting_rate_matrix(string campaign, int time){

vector< vector<Double_t>> counting_rate_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root";
		}
}

if(time==60)
{
	if(campaign=="LCO")
		{
				counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
		}
}

ROOT::RDataFrame df_CR("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

auto df_CR_E01 = df_CR.Take<int>("NEUrate_D01").GetValue();
auto df_CR_E02 = df_CR.Take<int>("NEUrate_D02").GetValue();
auto df_CR_E03 = df_CR.Take<int>("NEUrate_D03").GetValue();
auto df_CR_E04 = df_CR.Take<int>("NEUrate_D04").GetValue();
auto df_CR_E05 = df_CR.Take<int>("NEUrate_D05").GetValue();
auto df_CR_E06 = df_CR.Take<int>("NEUrate_D06").GetValue();
auto df_CR_E07 = df_CR.Take<int>("NEUrate_D07").GetValue();
auto df_CR_E08 = df_CR.Take<int>("NEUrate_D08").GetValue();
auto df_CR_E09 = df_CR.Take<int>("NEUrate_D09").GetValue();
auto df_CR_E10 = df_CR.Take<int>("NEUrate_D10").GetValue();
auto df_CR_E11 = df_CR.Take<int>("NEUrate_D11").GetValue();
auto df_CR_E12 = df_CR.Take<int>("NEUrate_D12").GetValue();
auto df_CR_E13 = df_CR.Take<int>("NEUrate_D13").GetValue();
auto df_CR_E14 = df_CR.Take<int>("NEUrate_D14").GetValue();
auto df_CR_E15 = df_CR.Take<int>("NEUrate_D15").GetValue();
auto df_CR_E16 = df_CR.Take<int>("NEUrate_D16").GetValue();

/****Llenamos la matiz de COUNTING RATES****/
for (int i=0; i<df_CR_E01.size();i++)
	{
        vector<double> row_cr_matrix; /*vector de largo 16: [CR_E01[0],...,CR_E02[0]]*/
       double r;
		if(time==15){r=900;}
		if(time==60){r=3600;}
			
			row_cr_matrix.push_back((double)df_CR_E01[i]/r);
			row_cr_matrix.push_back((double)df_CR_E02[i]/r);
			row_cr_matrix.push_back((double)df_CR_E03[i]/r);
			row_cr_matrix.push_back((double)df_CR_E04[i]/r);
			row_cr_matrix.push_back((double)df_CR_E05[i]/r);
			row_cr_matrix.push_back((double)df_CR_E06[i]/r);
			row_cr_matrix.push_back((double)df_CR_E07[i]/r);
			row_cr_matrix.push_back((double)df_CR_E08[i]/r);
			row_cr_matrix.push_back((double)df_CR_E09[i]/r);
			row_cr_matrix.push_back((double)df_CR_E10[i]/r);
			row_cr_matrix.push_back((double)df_CR_E11[i]/r);
			row_cr_matrix.push_back((double)df_CR_E12[i]/r);
			row_cr_matrix.push_back((double)df_CR_E13[i]/r);
			row_cr_matrix.push_back((double)df_CR_E14[i]/r);
			row_cr_matrix.push_back((double)df_CR_E15[i]/r);
			row_cr_matrix.push_back((double)df_CR_E16[i]/r);
									
			counting_rate_matrix.push_back(row_cr_matrix);
	
	}


/*visualizamos las entradas por fila*/
//~ for (unsigned int row = 0; row < counting_rate_matrix.size(); row++) {
    //~ std::cout << "Row " << row << ": ";
    //~ for (double value : counting_rate_matrix[row]) {
      //~ std::cout << value << " ";
    //~ }
    //~ std::cout << std::endl;
    //~ }

return counting_rate_matrix;

}

vector<Double_t> neutron_count_vector_gauss_MC(string campaign, int event, int crptime){

vector<Double_t> neutron_gauss_vec; // vector con los cr generados aleatoriamente de una distribucion gaussiana
vector<Double_t> N; /*vector de neutrones medidos*/

N = neutrons_count_matrix(campaign,crptime)[event];


for(int i=0;i<N.size();i++)
	{
	  double deltaN = sqrt(N[i]);
	  double neutron_gauss = gRandom->Gaus(N[i],deltaN);
	  neutron_gauss_vec.push_back(neutron_gauss);
	  
	}
//~ for(int i=0;i<N.size();i++)
	//~ {
		//~ cout << " N " << N[i] << setw(15) << setfill(' ') << " N Gauss " << neutron_gauss_vec[i] << endl;
	//~ }
return neutron_gauss_vec;


}

vector<Double_t> Counting_rate_vector_gauss_MC(string campaign, int event, int crptime){

vector<Double_t> N_g; /*vector de neutrones aletarios gaussianos*/
vector<Double_t> CR_g; /*vector de counting rate de neutrones aleatorios gaussianos*/
vector<Double_t> CR; /*vector de counting rate de neutrones medidos*/

N_g = neutron_count_vector_gauss_MC(campaign,event, crptime);
CR = Counting_rate_matrix(campaign,crptime)[event]; //Para comparar


for(int i=0;i<N_g.size();i++)
	{
		double r;
		if(crptime==15){r=900;}
		if(crptime==60){r=3600;}
		CR_g.push_back(N_g[i]/r);
	  
	}
for(int i=0;i<CR_g.size();i++)
	{
		cout << " CR " << CR[i] << setw(15) << setfill(' ') << " CR Gauss " << CR_g[i] << endl;
	}
return CR_g;


}

vector<Double_t> E_neutrons_count_vector_gauss_MC(string campaign, int event, int crptime){

vector<Double_t> N_g; /*vector de neutrones aletarios gaussianos*/
vector<Double_t> E_neutrons_count_vector; /*vector de counting rate de errores de neutrones aleatorios gaussianos*/

N_g = neutron_count_vector_gauss_MC(campaign,event, crptime);


for(int i=0;i<N_g.size();i++)
	{
		double e_neu = sqrt(N_g[i]);
		E_neutrons_count_vector.push_back(e_neu);
	  
	}
for(int i=0;i<N_g.size();i++)
	{
		cout <<  "E_neu_gauss " <<E_neutrons_count_vector[i] << endl;
	}
return E_neutrons_count_vector;


}



double_t Chi_Square(vector<Double_t> C_i,vector<Double_t> dCR, vector<Double_t> CR_rec, double ndet, int crptime)
{
	double_t chi=0;
	double_t partial_sum=0;
	double_t nprom=0;
	double_t variance=0;
		//~ double_t tolerance = 0.1;

	//~ for (int i = 0; i < ndet; i++){ partial_sum = (N_i[i] - N_rec[i])/(N_i[i]*tolerance); chi += partial_sum*partial_sum; }
	 //~ for (int i = 0; i < ndet; i++){ partial_sum = (N_i[i] - N_rec[i])/(sqrt(N_i[i])/900.); chi += partial_sum*partial_sum; }
	//~ double r;
	//~ if(crptime==15){r=1.;}
	//~ if(crptime==60){r=1.;}
	//~ for (int i = 0; i < ndet; i++){
		 //~ partial_sum = (N_i[i] - N_rec[i])/(sqrt(N_i[i]*r)/r);
		 //~ chi += partial_sum*partial_sum;
		 //~ cout << "i " << i << " N_i " << N_i[i] <<  " (sqrt(N*r)/r)N "<< (sqrt(N_i[i]*r)/r)/N_i[i] <<" N_rec " << N_rec[i] << " ci : " << chi << endl;
		 //~ }
	//~ return chi;

	for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i])/(dCR[i]);
		 chi += partial_sum*partial_sum;
		 //~ cout << "Det " << i+1 << " C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		 partial_sum=0;
		 }
	return chi;
	
	
}

double_t Xi_Square(vector<Double_t> C_i, vector<Double_t> CR_rec, double ndet, int crptime)
{
	double_t xi=0;
	double_t partial_sum=0;

	for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i])/C_i[i];
		 xi += partial_sum*partial_sum;
		 //~ cout << "Det " << i+1 << " C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " xi-square sumando : " << partial_sum*partial_sum << endl;
		 partial_sum=0;
		 }
	return xi/((double)ndet);
}

double_t bar_delta(vector<Double_t> C_i, vector<Double_t> CR_rec, double ndet, int crptime)
{
	double_t barDelta=0;
	double_t partial_sum=0;

	for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i]);
		 barDelta += partial_sum;
		 //~ cout << "Det " << i+1 << " C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " bar Delta sumando: " << partial_sum<< endl;
		 partial_sum=0;
		 }
	return barDelta/((double)ndet);
}

double_t STD_cr(vector<Double_t> C_i, vector<Double_t> CR_rec, double ndet, int crptime)
{
	double_t std_cr=0.;
	double_t partial_sum=0.;
	double_t barDelta = bar_delta(C_i, CR_rec, ndet, crptime);
	
	for (int i = 0; i < ndet; i++){
		 partial_sum = (barDelta -(C_i[i] - CR_rec[i]));
		 std_cr += partial_sum*partial_sum;
		 //~ cout << "Det " << i+1 << " C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " STD_cr sumando : " << partial_sum*partial_sum << endl;
		 partial_sum=0.;
		 }
	return sqrt(std_cr*(1./((double)ndet-1.)));
}



vector<Double_t> Recalculate(vector< vector<Double_t>> R, vector<Double_t> Flux, vector<Double_t> dE, double ndet)
{
	ofstream debug_em("debug_em.txt"); // archivo de salida de chi^2
	
	vector<Double_t> N(ndet,0);
	
	for (int i = 0; i < ndet; i++){
		double sum=0;
		for (int j = 0; j < Flux.size(); j++){
			sum += R[i][j]*Flux[j]*dE[j]; //  Flux[j]*dE[j] flujo integral, si es que Flux[j] es un flujo diferencial
		}
		N[i] = sum;
		sum = 0;
	}

	return N;
}

double_t Chi_Square_em2(vector<Double_t> N_i, vector<Double_t> CR_rec, double_t intgl, double ndet)
{
	double_t chi=0;
	double_t partial_sum=0;
	double_t nprom=0;
	double_t variance=0;
	double_t tolerance = 0.1;

	for (int i = 0; i < ndet; i++){ partial_sum = (N_i[i] - CR_rec[i])/(intgl*tolerance); chi += partial_sum*partial_sum; }
	
	return chi;
}

double_t Chi_Square_red(vector<Double_t> C_i, vector<Double_t> dCR, vector<Double_t> CR_rec, double ndet, int crptime)
{
	double_t chi=0;
	double_t partial_sum=0;
	double_t nprom=0;
	double_t variance=0;
	//~ double_t tolerance = 0.1;

	//~ for (int i = 0; i < ndet; i++){ partial_sum = (N_i[i] - N_rec[i])/(N_i[i]*tolerance); chi += partial_sum*partial_sum; }
	//~ double r;
	//~ if(crptime==15){r=900;}
	//~ if(crptime==60){r=3600;}
	//~ for (int i = 0; i < ndet; i++){
		//~ partial_sum = (N_i[i] - N_rec[i])/(sqrt(N_i[i])/r);
		//~ chi += partial_sum*partial_sum;
		//~ }
		for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i])/(dCR[i]);
		 chi += partial_sum*partial_sum;
		 partial_sum=0;
		 }

	/*chi-square reducido: chi-square dividido por el numero de grados de libertad (ndl) del problema, en esta caso el 
	 * numero de detectores*/
	return chi/(double(ndet));
	
}

/*Algoritmo EM con salida grafica*/
void deconv_em(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm){

//~ const int ndet = 16; // numero de detectores //
int ndet = 16; // numero de detectores //


int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> Flux; /*vector de flujo deconvolucionado*/
vector<Double_t> FluxNext; /*vector de flujo de salida por cada iteracion en algoritmo EM*/
vector<Double_t> FluxMin; /* vector del primer flujo deconvolucionado que cumple la condicion chi2 < ndet*/
vector<Double_t> N(ndet,0); /*vector de neutrones medidos*/
vector<Double_t> dN(ndet,0); /*vector de errores de neutrones medidos*/
vector<Double_t> perc_e_N(ndet,0); /*vector de errores porcentuales de neutrones medidos*/
vector<Double_t> CR(ndet,0); /*vector de counting rate de neutrones medidos*/
vector<Double_t> dCR(ndet,0); /*vector de errores de counting rate de neutrones medidos*/ 
vector<Double_t> CR_rec(ndet,0); /*vector de counting rates recalculados*/ 
vector<Double_t> dE; /*Vector de anchos de energia*/
vector< vector<Double_t>> R;   /*matriz de funciones respuesta del espectrometro*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de Energias*/
vector<Double_t> Emid; /*bins*/ /*matriz de Energias*/

ofstream Chi2("chi2.txt"); // archivo de salida de chi2

/****Cargamos el flujo semilla*****/
string str_stream_vwc;
string seed_flux_expacs_csv;

if(vwc_seed<=150)
		{
			// Map: 0->0 (VWC 0%)
			// Map: 1->1 (VWC 0.2%)
			// Map: 150->150 (30%)
			ostringstream stream_vwc;
			stream_vwc << vwc_seed;
			string str_stream_vwc =stream_vwc.str();

			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}

if(vwc_seed>150)
		{
			// Map: 151->32 (VWC 32%)
			// Map: 152->34 (vwc 34%)
			// Map: 185->100 ((vwc 100%)
			int vwc_old_51_seed = (vwc_seed - 135)*2;

			ostringstream stream_vwc_old_51_seed;
			stream_vwc_old_51_seed << vwc_old_51_seed;
			string str_stream_vwc_old_51_seed = stream_vwc_old_51_seed.str();
			str_stream_vwc = str_stream_vwc_old_51_seed;
			
			if(campaign=="LCO")
				{			
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}

char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
cout <<"Generated root file from csv file" << endl;

/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
Seed = df_seed_flux_vec;
cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
binnum = Seed.size()-1;
//~ binnum = 130;
cout << "binnum: Seed.size()-1 : " << binnum << endl;

/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
B = df_binedges_vec;
cout << "B: df_binedges_vec size " << B.size() << endl;

//~ /*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
dE = df_dE_vec;
cout << "dE: df_dE_vec " << B.size() << endl;

auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
E = df_E_vec;
cout << "E: df_E_vec " << B.size() << endl;

/**Inicializamos los vectores**/
for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux.push_back(0) ;
	FluxMin.push_back(0);
} 

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = B.data();

//~ for (int i=0; i<131; i++){
   //~ cout << "i " << i << " edge: " <<  bins[i]<< endl;
//~ }

cout << "bins array size: " << sizeof(*bins) << endl;

TCanvas *canvas_expacs = new TCanvas("Expacs_flux","Expacs_flux");

/*Histograma de flujo inicial*/
auto name_hist_seed = "flux_inicial_expacs_"+str_stream_vwc+"%";
//~ TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), 150, bins);
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
for (int i = 0; i <Seed.size(); i++)
{
	flux_inicial->SetBinContent(i+1,Seed[i]);
}

double_t integral_flux_seed = flux_inicial->Integral();
cout << "integral_flux_seed: " << integral_flux_seed << endl;

gPad->SetLogx();
gStyle->SetOptStat(1001111);
flux_inicial->Draw("HIST");

/**Obtenemos los centros de bin de energia**/
for (int i = 0; i < binnum; i++)
{
	Double_t bin_center = flux_inicial->GetBinCenter(i+1);
	//~ cout << "bin " << i+1 << " bin center " << bin_center << endl;
	Emid.push_back(bin_center);
}

cout << "Emid size " <<  Emid.size() << endl;



/********Flujo semilla diferencial para el algortimo EM*********/
for (int i = 0; i <Seed.size(); i++)
	{
		double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux[i] = Seed[i]/(E_mid); /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}


cout << "Vectors :" << endl;
for(int i=0; i<Seed.size(); i++)
	{
		cout << "i " << i <<  " Seed[i] " << Seed[i] << " Emid[i] " << Emid[i] << " Flux[i]=Seed[i]/(E[i]+(dE[i]/2.))  " << Flux[i] <<  " Flux[i] = Seed[i]/Emid[i] " << Seed[i]/Emid[i] << endl;
    }


/***Llenamos el vector de neutrones y de errores de neutrones medidos****/
N = neutrons_count_matrix(campaign,crptime)[event]; //Tomamos el primer evento para probar
dN = E_neutrons_count_matrix(campaign,crptime)[event]; //Tomamos el primer evento para probar
/***Llenamos el vector de CR de neutrones medidos: N/T ****/
CR = Counting_rate_matrix(campaign,crptime)[event]; //Tomamos el primer evento para probar

cout << "Neutrons vector filled: N[i] & dN[i]" << endl;
//~ /**Visualizamos el vector de CR**/
for (int i = 0; i <N.size(); i++) {  
	
	cout << i <<" N[i] "<< N[i] << " delta N[i] " << dN[i] << endl;
}

cout << "Neutrons percentage error vector filled: dN[i]/N[i]" << endl;
for(int i=0; i<N .size(); i++)
	{
		perc_e_N[i] = dN[i]/N[i];
		cout << "i " << i <<  " dN[i]/N[i] " << perc_e_N[i] << endl;
    }
    
cout << "CR [cps] vector: CR[i]" << " Time " << crptime << " min "  << endl;
for(int i=0; i<CR .size(); i++)
	{
		cout << "i " << i <<  " CR[i] " << CR[i] << endl;
    }
/***Llenamos el vector de dCR***/
cout << " dCR[i] vector "  << endl;  
for(int i=0; i<N .size(); i++)
	{
		dCR[i] = CR[i]*perc_e_N[i];
		cout << "i " << i <<  " dCR[i] " << dCR[i] << endl;
    }



/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/

cout << "Response Function matrix filled: R " << endl;


/****************ACTIVACION/DESACTIVACION DE DETECTORES*************/
vector< vector<Double_t>> R_new;   /*matriz de funciones respuesta del espectrometro redefinida*/
vector<Double_t> N_new;   /*vector de CR redefinido*/
vector<Double_t> perc_e_N_new;
vector<Double_t> CR_new;
vector<Double_t> dCR_new;
vector<string> det_names{"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13","D14","D15","D16"}; /*vector de nombres de detectores activados*/
vector<string> det_names_act;

//~ vector<int> des_vector(ndet,0);
vector<int> act_vector(ndet,1);

//~ vector<int> vec_test{0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1};
//~ vector<int> vec_test{1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1};
//~ vector<int> vec_test{1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1};
vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			R_new.push_back(R[i]);
		}
	else{}
}

//*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;

/*Redefinimos R*/
R = R_new;

perc_e_N.resize(ndet);
CR.resize(ndet);
dCR.resize(ndet);
perc_e_N = perc_e_N_new;
CR = CR_new;
dCR = dCR_new;

/*Redefinimos N*/
N.resize(ndet);
N = N_new;



cout << "Response Function matrix new size:  " <<  R_new.size()  << endl;
cout << "Neutrons vector new size:  " <<  N_new.size()  << endl;

/*******************************************************************/



if (norm==1){
/********Flujo semilla diferencial normalizado************/
for (int i = 0; i < Seed.size(); i++)
	{
		Flux[i] = Flux[i]/integral_flux_seed; //Normalizamos el flujo semilla
		// cout << i << " " << Flux[i] << endl;
	}
}
else {}


TCanvas *canvas_em = new TCanvas("EM","EM");
canvas_em ->Divide(2,1);


/**Visulizacion del flujo semilla**/

/*Condicional de normalizacion*/
string name_hist_seed_norm;
if (norm==1){name_hist_seed_norm = "Flux_inicial_norm_VWC_"+str_stream_vwc+"%";}
else{name_hist_seed_norm = "Flux_inicial_VWC_"+str_stream_vwc+"%";}


TH1D* flux_inicial_norm = new TH1D(name_hist_seed_norm.c_str(),name_hist_seed_norm.c_str(), binnum, bins);

if (flux_type=="diff"){

	for (int i = 0; i < Seed.size(); i++)
		{
			flux_inicial_norm->SetBinContent(i+1,Flux[i]); // representacion diferencial al visualizar
		}
	}

if (flux_type=="Intg"){
	for (int i = 0; i < Seed.size(); i++)
		{
			flux_inicial_norm->SetBinContent(i+1,Flux[i]*(E[i]+(dE[i]/2.))); // representacion flujo per lethargic unit al visualizar
		}
		if (norm==1){
		flux_inicial_norm->Scale(1./flux_inicial_norm->Integral());
	     }
	     else {}
	}


auto flux_inicial_norm_color_th = (TH1D*)flux_inicial_norm->Clone();
flux_inicial_norm_color_th->SetFillColor(kGray);
flux_inicial_norm_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);

auto flux_inicial_norm_color_ep = (TH1D*)flux_inicial_norm->Clone();
flux_inicial_norm_color_ep->SetFillColor(kCyan-9);
flux_inicial_norm_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);

auto flux_inicial_norm_color_fs = (TH1D*)flux_inicial_norm->Clone();
flux_inicial_norm_color_fs->SetFillColor(kGreen-9);
flux_inicial_norm_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);

auto flux_inicial_norm_color_he = (TH1D*)flux_inicial_norm->Clone();
flux_inicial_norm_color_he->SetFillColor(kRed-9);
flux_inicial_norm_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);

canvas_em->cd(1);
gPad->SetLogx();
gStyle->SetOptStat(1001111);
flux_inicial_norm->Draw("HIST");
flux_inicial_norm_color_th->Draw("SAME");
flux_inicial_norm_color_ep->Draw("SAME");
flux_inicial_norm_color_fs->Draw("SAME");
flux_inicial_norm_color_he->Draw("SAME");


/*************************************************************/
/**************Algoritmo de deconvolucion EM******************/
/*************************************************************/

cout << "Inicia Deconvolucion" << endl;
	Double_t Sum_R=0.;
	Double_t Sum_R_Flux=0.;
	Double_t Sum_N_R_Flux=0.;
	
	vector< vector<double_t> > vec_fluxnext; // vector de vectores de flux next o flujos deconvolucionados por paso
	
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	double chi2 = 30.;
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet);
	//~ double_t chi2 = 25;
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet,crptime);
	double_t  chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet,crptime);
	cout << "Chi2 inicial: " << chi2 << endl;
	cout << "Chi2red inicial: "<< chi2_red << endl;
	
	/*contador em*/
	//~ int it = 0;

	//~ Chi2 <<setw(5) << setfill(' ') << it << " "
	Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 <<setw(15) << setfill(' ') << chi2 << " "
				 <<setw(25) << setfill(' ') << chi2_red << endl;
	
	
//~ while (chi2 > ndet)
//~ while(it<steps)
for(int it = 0; it<steps ; it++)
{
	FluxNext = Flux;
	for(Int_t b=0; b<binnum; b++)
		{
			Sum_R=0.;
			for(Int_t r=0; r<ndet; r++)	Sum_R += (R[r][b]);
			
			Sum_N_R_Flux=0.;
			for(Int_t r=0; r<ndet; r++)
				{
					Sum_R_Flux=0.;
						for(Int_t k=0; k<binnum; k++)
							{	
								Sum_R_Flux += (R[r][k] * Flux[k]*dE[k]); //  Flux[k]*dE[k] flujo integral, ya que Flux[k] es un flujo diferencial
							} 
					//~ Sum_N_R_Flux += ((R[r][b]* Flux[b])*N[r])/Sum_R_Flux;
					Sum_N_R_Flux += ((R[r][b]* Flux[b])*CR[r])/Sum_R_Flux;
				}
			FluxNext[b] = Sum_N_R_Flux/Sum_R;
			
		}
	Flux=FluxNext; /*flujo deconvolucionado*/
	
	//Llenamos el vector de vectores de fluxnext
	 for (int i = 0; i < Seed.size(); i++) 
	 {
		FluxMin[i] = Flux[i]; // flujo diferencial
		//~ FluxMin[i] = Flux[i]*dE[i]; //integral
	 }
	
	/*Llenamos el vector de flujos deconvolucionados por paso*/
	vec_fluxnext.push_back(FluxMin);
	
	CR_rec = Recalculate(R, FluxMin, dE, ndet); // CR recalculado
	
	chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
	chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
	
	cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red << endl;
	
	Chi2 <<setw(5) << setfill(' ') << it << " "
		 <<setw(15) << setfill(' ') << chi2 << " "
		 <<setw(25) << setfill(' ') << chi2_red << endl;
}

/*Salida a pantalla de CR de neutrones medidos y recalculados con el flujo deconvolucionado*/

for(int i=0; i<CR_rec.size();i++)
{
 cout<< "Detector:" << det_names_act[i] << setw(13) << setfill(' ') << "CR medido: " << CR[i]  << setw(13) << setfill(' ') <<"CR recal: " << CR_rec[i] << setw(13) << setfill(' ') << " Dif %: " << ((CR[i]-CR_rec[i])/CR[i])*100  << setw(13) << setfill(' ') << "Unc: " <<((sqrt(CR[i])/CR[i])/900)*100<< endl;
}

/****************************************************************************************************/
/****************************************************************************************************/


/****Definimos los histogramas****/


/****Histograma con el flujo deconvolucionado del ultimo paso del algortimto EM****/

TH1D* flux_deconv = new TH1D("Flux_deconv","Flux deconv", binnum, bins);
if (flux_type=="diff"){
	for (int i = 0; i < Seed.size(); i++)
	{
		flux_deconv->SetBinContent(i+1,FluxMin[i]); // representamos el flujo diferencial
	}
}

if (flux_type=="Intg"){
	for (int i = 0; i < Seed.size(); i++)
	{
		flux_deconv->SetBinContent(i+1,FluxMin[i]*(E[i]+(dE[i]/2.))); // representamos el flujo per lethargic unit para visualizar, si es que FluxMin[i] es un flujo diferencial de salida del algoritmo
	}
}

/*Normalizamos para mostrar*/
//~ double integral_deconv_last = flux_deconv->Integral();
//~ flux_deconv->Scale(1./integral_deconv_last );

auto flux_deconv_color_th = (TH1D*)flux_deconv->Clone();
flux_deconv_color_th->SetFillColor(kGray);
flux_deconv_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);

auto flux_deconv_color_ep = (TH1D*)flux_deconv->Clone();
flux_deconv_color_ep->SetFillColor(kCyan-9);
flux_deconv_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);

auto flux_deconv_color_fs = (TH1D*)flux_deconv->Clone();
flux_deconv_color_fs->SetFillColor(kGreen-9);
flux_deconv_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);

auto flux_deconv_color_he = (TH1D*)flux_deconv->Clone();
flux_deconv_color_he->SetFillColor(kRed-9);
flux_deconv_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);


canvas_em->cd(2);
gPad->SetLogx();
gStyle->SetOptStat(1001111);
flux_deconv->Draw("HIST");
flux_deconv_color_th->Draw("SAME");
flux_deconv_color_ep->Draw("SAME");
flux_deconv_color_fs->Draw("SAME");
flux_deconv_color_he->Draw("SAME");



/*****Visuzalizacion de los flujos deconvolucionados por paso del algortimo EM*******/
TCanvas *deconv_steps = new TCanvas("deconv_steps", "Flux Deconv by Step",1920, 1080 ); //generamos un canvas

/*Llenamos un hist por cada paso del algoritmo*/
cout << "# Flujos deconvolucionados: " << vec_fluxnext.size() << endl;

vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_th; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_ep; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_fs; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_he; //vector de histogramas de flujos deconvolucionados

for (int j=0; j < vec_fluxnext.size(); j++)
	{
		TH1D *hist_step = new TH1D(TString::Format("h0_%d", j+1),"Flujo de neutrones deconvolucionado", binnum, bins);
		
		std::ostringstream stream_paso;
		stream_paso << std::fixed;
		stream_paso << std::setprecision(1);
		stream_paso << j;
		std::string paso = stream_paso.str();
		
		vector<double_t> vec_entry  = vec_fluxnext[j];

		if(flux_type=="diff"){
			for (int i = 0; i < Seed.size(); i++)
			 {
				hist_step->SetBinContent(i+1, vec_entry[i]); // representamos el flujo diferencial
			 }
		 }
		 if(flux_type=="Intg"){
			 for (int i = 0; i < Seed.size(); i++)
			 {
				hist_step->SetBinContent(i+1, vec_entry[i]*(E[i]+(dE[i]/2.))); // representamos el flujo per lethargic unit visualizar, si es que FluxMin[i] es un flujo diferencial de salida del algoritmo
			 }	

		}

		/*Coloremos los histogramas deconvolucionados por region de energia*/

		auto hist_step_color_th = (TH1D*)hist_step->Clone();
		hist_step_color_th->SetFillColor(kGray);
		hist_step_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);

		auto hist_step_color_ep = (TH1D*)hist_step->Clone();
		hist_step_color_ep->SetFillColor(kCyan-9);
		hist_step_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);

		auto hist_step_color_fs = (TH1D*)hist_step->Clone();
		hist_step_color_fs->SetFillColor(kGreen-9);
		hist_step_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);

		auto hist_step_color_he = (TH1D*)hist_step->Clone();
		hist_step_color_he->SetFillColor(kRed-9);
		hist_step_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
		
		
		 
		 vec_hist_deconv.push_back(hist_step); // llenamos el vector de histogramas
		 vec_hist_deconv_color_th.push_back(hist_step_color_th); // llenamos el vector de histogramas coloreado
		 vec_hist_deconv_color_ep.push_back(hist_step_color_ep); // llenamos el vector de histogramas coloreado
		 vec_hist_deconv_color_fs.push_back(hist_step_color_fs); // llenamos el vector de histogramas coloreado
		 vec_hist_deconv_color_he.push_back(hist_step_color_he); // llenamos el vector de histogramas coloreado
	}




cout << "Largo vector de histogramas: " << vec_hist_deconv.size() << endl;


int canvas_value = sqrt(steps);
deconv_steps->Divide(canvas_value,canvas_value); 

deconv_steps->cd(1);
gPad->SetLogx();
gStyle->SetOptStat(1001111);
flux_inicial_norm->SetLineColor(kRed);
flux_inicial_norm->Draw("HIST");

// llenamos cada entrada del canvas con un histograma del vector de histogramas
for (int i = 0; i < vec_hist_deconv.size(); i++){
	deconv_steps->cd(i+1);
	gPad->SetLogx();
	gStyle->SetOptStat(1001111);

	/*Normalizamos*/
	double integral_deconv = vec_hist_deconv[i]->Integral();
	//~ vec_hist_deconv[i]->Scale(1./ integral_deconv);
	vec_hist_deconv[i]->Draw("HIST");
	vec_hist_deconv_color_th[i]->Draw("SAME");
	vec_hist_deconv_color_ep[i]->Draw("SAME");
	vec_hist_deconv_color_fs[i]->Draw("SAME");
	vec_hist_deconv_color_he[i]->Draw("SAME");
	} 


gROOT->GetListOfCanvases()->Draw();
}

/*Algoritmo EM que entrega como salida un vector: */
vector<double> deconv_em_output(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm){

//~ const int ndet = 16; // numero de detectores //
int ndet = 16; /*numero de detectores*/
int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> Flux; /*vector de flujo deconvolucionado*/
vector<Double_t> FluxNext; /*vector de flujo de salida por cada iteracion en algoritmo EM*/
vector<Double_t> FluxMin_diff; /* vector del ultimo flujo diff deconvolucionado*/
vector<Double_t> FluxMin_Intg; /* vector del ultimo flujo integral deconvolucionado*/
vector<Double_t> N(ndet,0); /*vector de neutrones medidos*/
vector<Double_t> dN(ndet,0); /*vector de errores de neutrones medidos*/
vector<Double_t> perc_e_N(ndet,0); /*vector de errores porcentuales de neutrones medidos*/
vector<Double_t> CR(ndet,0); /*vector de counting rate de neutrones medidos*/
vector<Double_t> dCR(ndet,0); /*vector de errores de counting rate de neutrones medidos*/ 
vector<Double_t> CR_rec(ndet,0); /*vector de counting rates recalculados*/ 
vector<Double_t> dE; /*Vector de anchos de energia*/
vector< vector<Double_t>> R;   /*matriz de funciones respuesta del espectrometro*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de bordes inferiores de Energias*/
vector<Double_t> Emid; /*bins*/ /*matriz de Energias centrales*/

vector<Double_t> em_vec_output;

ofstream Chi2("Stat_Estimators.txt"); // archivo de salida de Chi2
ofstream debug_em("debug_em.txt"); // archivo de salida de Chi2

/****Cargamos el flujo semilla*****/

string str_stream_vwc;
string seed_flux_expacs_csv;

if(vwc_seed<=150)
		{
			// Map: 0->0 (VWC 0%)
			// Map: 1->1 (VWC 0.2%)
			// Map: 150->150 (30%)
			ostringstream stream_vwc;
			stream_vwc << vwc_seed;
			string str_stream_vwc =stream_vwc.str();

			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}

if(vwc_seed>150)
		{
			// Map: 151->32 (VWC 32%)
			// Map: 152->34 (vwc 34%)
			// Map: 185->100 ((vwc 100%)
			int vwc_old_51_seed = (vwc_seed - 135)*2;

			ostringstream stream_vwc_old_51_seed;
			stream_vwc_old_51_seed << vwc_old_51_seed;
			string str_stream_vwc_old_51_seed = stream_vwc_old_51_seed.str();
			str_stream_vwc = str_stream_vwc_old_51_seed;
			
			if(campaign=="LCO")
				{			
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}
				 
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
//~ seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;

/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
binnum = Seed.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;

/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;

//~ /*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
E = df_E_vec;
//~ cout << "E: df_E_vec " << B.size() << endl;

/**Inicializamos los vectores**/
for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux.push_back(0) ;
	FluxMin_diff.push_back(0);
	FluxMin_Intg.push_back(0);
} 

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = B.data();
//~ TCanvas *canvas_expacs = new TCanvas("Expacs_flux","Expacs_flux");

/*Histograma de flujo inicial*/
auto name_hist_seed = "flux_inicial_expacs_"+str_stream_vwc+"%";
//~ TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), 150, bins);
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
for (int i = 0; i <Seed.size()-1; i++)
{
	flux_inicial->SetBinContent(i+1,Seed[i]);
}

double_t integral_flux_seed = flux_inicial->Integral();

/**Obtenemos los centros de bin de energia**/
for (int i = 0; i < binnum; i++)
{
	Double_t bin_center = flux_inicial->GetBinCenter(i+1);
	//~ cout << "bin " << i+1 << " bin center " << bin_center << endl;
	Emid.push_back(bin_center);
}

//~ cout << "Emid size " <<  Emid.size() << endl;



/********Flujo semilla diferencial para el algortimo EM*********/
for (int i = 0; i <Seed.size(); i++)
	{
		double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux[i] = Seed[i]/(E_mid); /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}


/***Llenamos el vector de neutrones y de errores de neutrones medidos****/
N = neutrons_count_matrix(campaign,crptime)[event-1]; //Tomamos el primer evento para probar
dN = E_neutrons_count_matrix(campaign,crptime)[event-1]; //Tomamos el primer evento para probar
/***Llenamos el vector de CR de neutrones medidos: N/T ****/
CR = Counting_rate_matrix(campaign,crptime)[event-1]; //Tomamos el primer evento para probar

//~ cout << "Neutrons vector filled: N[i] & dN[i]" << endl;
//~ /**Visualizamos el vector de CR**/
//~ for (int i = 0; i <N.size(); i++) {  
	
	//~ cout << i <<" N[i] "<< N[i] << " delta N[i] " << dN[i] << endl;
//~ }

//~ cout << "Neutrons percentage error vector filled: dN[i]/N[i]" << endl;
for(int i=0; i<N.size(); i++)
	{
		perc_e_N[i] = dN[i]/N[i];
		//~ cout << "i " << i <<  " dN[i]/N[i] " << perc_e_N[i] << endl;
    }
    
//~ cout << "CR [cps] vector: CR[i]" << " Time " << crptime << " min "  << endl;
//~ for(int i=0; i<CR.size(); i++)
	//~ {
		//~ cout << "i " << i <<  " CR[i] " << CR[i] << endl;
    //~ }
/***Llenamos el vector de dCR***/
//~ cout << " dCR[i] vector "  << endl;  
for(int i=0; i<N.size(); i++)
	{
		dCR[i] = CR[i]*perc_e_N[i];
		//~ cout << "i " << i <<  " dCR[i] " << dCR[i] << endl;
    }

/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/


//~ cout << "Response Function matrix filled: R " << endl;


/****************ACTIVACION/DESACTIVACION DE DETECTORES*************/

vector< vector<Double_t>> R_new;   /*matriz de funciones respuesta del espectrometro redefinida*/
vector<Double_t> N_new;   /*vector de CR redefinido*/
vector<Double_t> perc_e_N_new;
vector<Double_t> CR_new;
vector<Double_t> dCR_new;

vector<string> det_names{"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13","D14","D15","D16"}; /*vector de nombres de detectores activados*/
vector<string> det_names_act;

//~ vector<int> des_vector(ndet,0);
vector<int> act_vector(ndet,1);


vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};
//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			R_new.push_back(R[i]);
		}
	else{}
}

/**Inspeccionamos la matriz****/
//~ cout << " matrix size: " << R.size() << endl;

//~ for(int i = 0; i<R_new.size();i++){
	//~ cout << " row " << i << " ";
	//~ for (int j=0; j <R_new[0].size(); j++){

		 //~ cout <<  R_new[i][j] << " ";
	//~ }
   //~ cout << endl;
//~ }


/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;

/*Redefinimos R*/
R = R_new;



//~ cout << " matrix size: " << R.size() << endl;
//~ for(int i = 0; i<R.size();i++){
	//~ cout << " row " << i << " ";
	//~ for (int j=0; j <R[0].size(); j++){

		 //~ cout <<  R[i][j] << " ";
	//~ }
   //~ cout << endl;
//~ }
perc_e_N.resize(ndet);
CR.resize(ndet);
dCR.resize(ndet);

perc_e_N = perc_e_N_new;
CR = CR_new;
dCR = dCR_new;


/*Redefinimos N*/
N.resize(ndet);
N = N_new;

//~ cout << " matrix size: " << N.size() << endl;

//~ for(int i = 0; i<N.size();i++){
	//~ cout << " row " << i << " " << N[i] << endl;
//~ }

/*******************************************************************/



if (norm==1){
/********Flujo semilla diferencial normalizado************/
for (int i = 0; i < Seed.size(); i++)
	{
		Flux[i] = Flux[i]/integral_flux_seed; //Normalizamos el flujo semilla
		// cout << i << " " << Flux[i] << endl;
	}
}
else {}



/*************************************************************/
/**************Algoritmo de deconvolucion EM******************/
/*************************************************************/

cout << "Inicia Deconvolucion" << endl;
	Double_t Sum_R=0.;
	Double_t Sum_R_Flux=0.;
	Double_t Sum_N_R_Flux=0.;
	
	vector< vector<double_t> > vec_fluxnext_diff; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	vector< vector<double_t> > vec_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	std::vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
	

	/***Definimos e inicializamos los estimadres estadisticos***/
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	double chi2 = 30.;
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet);
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet,crptime);
	double_t  chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet,crptime);
	double xi2_estimator;
	double barDelta_estimator;
	double STD_cr_estimator;
	
	//~ cout << "Chi2 inicial: " << chi2 << endl;
	//~ cout << "Chi2red inicial: "<< chi2_red << endl;
	
//~ /*contador em*/
int em_it = 0;

	 //~ Chi2 <<setw(5) << setfill(' ') << "it" << " "
		 //~ <<setw(15) << setfill(' ') << "chi2" << " "
		 //~ <<setw(25) << setfill(' ') << "chi2_red"  << " "
		 //~ <<setw(25) << setfill(' ') << "xi2"  << " "
		 //~ <<setw(25) << setfill(' ') << "barDelta"  << " "
		 //~ <<setw(25) << setfill(' ') << "STD_cr" << endl;  

	//~ Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 //~ <<setw(15) << setfill(' ') << chi2 << " "
				 //~ <<setw(25) << setfill(' ') << chi2_red << endl;

if(steps==0)
{				 
	while(chi2>ndet)
	{
		FluxNext = Flux;
		for(Int_t b=0; b<binnum; b++)
			{
				//~ debug_em <<setw(5) << " b " << b << endl;
				Sum_R=0.;
				for(Int_t r=0; r<ndet; r++) {
					Sum_R += (R[r][b]);
					
					//~ debug_em <<setw(5) <<" r " << r << " Sum_R " << Sum_R << endl;
					}
				
				Sum_N_R_Flux=0.;
				for(Int_t r=0; r<ndet; r++)
					{
						Sum_R_Flux=0.;

							//~ debug_em <<setw(5) << " r " << r << endl;
							for(Int_t k=0; k<binnum; k++)
								{	
									Sum_R_Flux += (R[r][k]*Flux[k]*dE[k]); //  Flux[k]*dE[k] flujo integral, ya que Flux[k] es un flujo diferencial
								//~ debug_em <<setw(5) << " k " << k << " Sum_R_Flux " << Sum_R_Flux << endl;
								}
								//~ debug_em <<setw(5) << "Sum_R_Flux total " << Sum_R_Flux << endl;
								
						//~ Sum_N_R_Flux += ((R[r][b]* Flux[b])*N[r])/Sum_R_Flux;
						Sum_N_R_Flux += ((R[r][b]* Flux[b])*CR[r])/Sum_R_Flux;
						//~ debug_em <<setw(5) << " Sum_N_R_Flux : " << Sum_N_R_Flux << endl;
						
					}
				FluxNext[b] = Sum_N_R_Flux/Sum_R;
				//~ debug_em << " FluxNext[b] " << FluxNext[b] << endl;
				
			}
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < Seed.size(); i++) 
		 {
			FluxMin_diff[i] = Flux[i]; // flujo diferencial
			FluxMin_Intg[i] = Flux[i]*dE[i]; //integral
		 }
		//~ TH1D *hist_step_diff = new TH1D(TString::Format("h0_diff_%d", it),"Flujo diferencial de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_diff->SetBinContent(i+1,FluxMin_diff[i]);
				//~ }
		//~ TH1D *hist_step_Intg = new TH1D(TString::Format("h0_Intg_%d", it),"Flujo Integral de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
				//~ }
				
		//~ double_t integral_flux_deconv_diff = hist_step_diff->Integral();
		//~ double_t integral_flux_deconv_Intg = hist_step_Intg->Integral();
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_diff << endl;
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_Intg << endl;
		
		/*Llenamos el vector de flujos deconvolucionados por paso*/
		vec_fluxnext_diff.push_back(FluxMin_diff);
		vec_fluxnext_Intg.push_back(FluxMin_Intg);

		/*Counting rate recalculado*/
		CR_rec = Recalculate(R, FluxMin_diff, dE, ndet); // CR recalculado

		/***Calculamos los estimadores estadisticos***/
		chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		em_it++;
		
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}
}

else
{				 
	for(int it = 0; it<steps ; it++)
	{
		FluxNext = Flux;
		for(Int_t b=0; b<binnum; b++)
			{
				//~ debug_em <<setw(5) << " b " << b << endl;
				Sum_R=0.;
				for(Int_t r=0; r<ndet; r++) {
					Sum_R += (R[r][b]);
					
					//~ debug_em <<setw(5) <<" r " << r << " Sum_R " << Sum_R << endl;
					}
				
				Sum_N_R_Flux=0.;
				for(Int_t r=0; r<ndet; r++)
					{
						Sum_R_Flux=0.;

							//~ debug_em <<setw(5) << " r " << r << endl;
							for(Int_t k=0; k<binnum; k++)
								{	
									Sum_R_Flux += (R[r][k]*Flux[k]*dE[k]); //  Flux[k]*dE[k] flujo integral, ya que Flux[k] es un flujo diferencial
								//~ debug_em <<setw(5) << " k " << k << " Sum_R_Flux " << Sum_R_Flux << endl;
								}
								//~ debug_em <<setw(5) << "Sum_R_Flux total " << Sum_R_Flux << endl;
								
						//~ Sum_N_R_Flux += ((R[r][b]* Flux[b])*N[r])/Sum_R_Flux;
						Sum_N_R_Flux += ((R[r][b]* Flux[b])*CR[r])/Sum_R_Flux;
						//~ debug_em <<setw(5) << " Sum_N_R_Flux : " << Sum_N_R_Flux << endl;
						
					}
				FluxNext[b] = Sum_N_R_Flux/Sum_R;
				//~ debug_em << " FluxNext[b] " << FluxNext[b] << endl;
				
			}
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < Seed.size(); i++) 
		 {
			FluxMin_diff[i] = Flux[i]; // flujo diferencial
			FluxMin_Intg[i] = Flux[i]*dE[i]; //integral
		 }
		//~ TH1D *hist_step_diff = new TH1D(TString::Format("h0_diff_%d", it),"Flujo diferencial de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_diff->SetBinContent(i+1,FluxMin_diff[i]);
				//~ }
		//~ TH1D *hist_step_Intg = new TH1D(TString::Format("h0_Intg_%d", it),"Flujo Integral de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
				//~ }
				
		//~ double_t integral_flux_deconv_diff = hist_step_diff->Integral();
		//~ double_t integral_flux_deconv_Intg = hist_step_Intg->Integral();
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_diff << endl;
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_Intg << endl;
		
		/*Llenamos el vector de flujos deconvolucionados por paso*/
		vec_fluxnext_diff.push_back(FluxMin_diff);
		vec_fluxnext_Intg.push_back(FluxMin_Intg);

		/*Counting rate recalculado*/
		CR_rec = Recalculate(R, FluxMin_diff, dE, ndet); // CR recalculado

		/***Calculamos los estimadores estadisticos***/
		chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		em_it+=it;
		
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}
}

/****************************************************************************************************/
/*********************************Output*************************************************************/
/****************************************************************************************************/

/****SALIDA DEL EM******/

TH1D *hist_deconv_total_Intg = new TH1D(TString::Format("h0_%d", steps),"Flujo de neutrones deconvolucionado", binnum, bins);
for (int i = 0; i <FluxMin_Intg.size(); i++)
		{
			hist_deconv_total_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
		}

double integral_flux_deconv_total_Intg = hist_deconv_total_Intg->Integral(); /*Valor integral total del flujo integral */
//~ cout << "Integral total flux deconv integral: " << integral_flux_deconv_total_Intg << endl;
/*Cambiamos los valores de x ligeramente para que los bines no se solapen, las regiones siguen siendo las mismas*/
double integral_flux_deconv_th = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(0),hist_deconv_total_Intg->FindBin(1.9*1e-07));
//~ cout << "Integral thermal region flux deconv: " << integral_flux_deconv_th << endl;
double integral_flux_deconv_ep = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(2.2*1e-07),hist_deconv_total_Intg->FindBin(0.9*1e-02));
//~ cout << "Integral epithermal region flux deconv: " << integral_flux_deconv_ep << endl;
double integral_flux_deconv_fs = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(1.1*1e-02),hist_deconv_total_Intg->FindBin(0.89*1e+01));
//~ cout << "Integral fast region flux deconv: " << integral_flux_deconv_fs << endl;
double integral_flux_deconv_he = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(1.05*1e+01),hist_deconv_total_Intg->FindBin(7.6*1e+03));
//~ cout << "Integral high energy region flux deconv: " << integral_flux_deconv_he << endl;

//~ /***Llenamos en las dos ultima entradas del vector deconvolucionado, con el chi2 y chi2_red***/
//~ cout << "FluxMin size: " << FluxMin_Intg.size() << endl;
FluxMin_Intg.push_back(ndet);
FluxMin_Intg.push_back(integral_flux_deconv_total_Intg);
FluxMin_Intg.push_back(integral_flux_deconv_th);
FluxMin_Intg.push_back(integral_flux_deconv_ep);
FluxMin_Intg.push_back(integral_flux_deconv_fs);
FluxMin_Intg.push_back(integral_flux_deconv_he);
FluxMin_Intg.push_back(chi2);
FluxMin_Intg.push_back(chi2_red);
FluxMin_Intg.push_back(xi2_estimator);
FluxMin_Intg.push_back(barDelta_estimator);
FluxMin_Intg.push_back(STD_cr_estimator);
FluxMin_Intg.push_back(em_it);


em_vec_output = FluxMin_Intg;
//~ cout << "em_vec_output size: " << em_vec_output.size() << endl;
//~ for (int i=0; i<FluxMin_Intg.size();i++)
	//~ {
		//~ cout <<"i " << i << " FluxMin_Intg[i] "<< FluxMin_Intg[i] << endl;
	//~ }

	
delete flux_inicial;
delete hist_deconv_total_Intg;
return em_vec_output;

}

vector<double> deconv_em_output_MC(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm, int max_steps){

//~ const int ndet = 16; // numero de detectores //
int ndet = 16; /*numero de detectores*/
int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> Flux; /*vector de flujo deconvolucionado*/
vector<Double_t> FluxNext; /*vector de flujo de salida por cada iteracion en algoritmo EM*/
vector<Double_t> FluxMin_diff; /* vector del ultimo flujo diff deconvolucionado*/
vector<Double_t> FluxMin_Intg; /* vector del ultimo flujo integral deconvolucionado*/
vector<Double_t> N(ndet,0); /*vector de neutrones medidos*/
vector<Double_t> dN(ndet,0); /*vector de errores de neutrones medidos*/
vector<Double_t> perc_e_N(ndet,0); /*vector de errores porcentuales de neutrones medidos*/
vector<Double_t> CR(ndet,0); /*vector de counting rate de neutrones medidos*/
vector<Double_t> dCR(ndet,0); /*vector de errores de counting rate de neutrones medidos*/ 
vector<Double_t> CR_rec(ndet,0); /*vector de counting rates recalculados*/ 
vector<Double_t> dE; /*Vector de anchos de energia*/
vector< vector<Double_t>> R;   /*matriz de funciones respuesta del espectrometro*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de bordes inferiores de Energias*/
vector<Double_t> Emid; /*bins*/ /*matriz de Energias centrales*/

vector<Double_t> em_vec_output;

//~ ofstream Chi2("Stat_Estimators.txt"); // archivo de salida de Chi2
//~ ofstream debug_em("debug_em.txt"); // archivo de salida de Chi2

/****Cargamos el flujo semilla*****/

string str_stream_vwc;
string seed_flux_expacs_csv;

if(vwc_seed<=150)
		{
			// Map: 0->0 (VWC 0%)
			// Map: 1->1 (VWC 0.2%)
			// Map: 150->150 (30%)
			ostringstream stream_vwc;
			stream_vwc << vwc_seed;
			string str_stream_vwc =stream_vwc.str();

			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}

if(vwc_seed>150)
		{
			// Map: 151->32 (VWC 32%)
			// Map: 152->34 (vwc 34%)
			// Map: 185->100 ((vwc 100%)
			int vwc_old_51_seed = (vwc_seed - 135)*2;

			ostringstream stream_vwc_old_51_seed;
			stream_vwc_old_51_seed << vwc_old_51_seed;
			string str_stream_vwc_old_51_seed = stream_vwc_old_51_seed.str();
			str_stream_vwc = str_stream_vwc_old_51_seed;
			
			if(campaign=="LCO")
				{			
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
		}
				 
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
//~ seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;

/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
binnum = Seed.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;

/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;

//~ /*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
E = df_E_vec;
//~ cout << "E: df_E_vec " << B.size() << endl;

/**Inicializamos los vectores**/
for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux.push_back(0) ;
	FluxMin_diff.push_back(0);
	FluxMin_Intg.push_back(0);
} 

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = B.data();
//~ TCanvas *canvas_expacs = new TCanvas("Expacs_flux","Expacs_flux");

/*Histograma de flujo inicial*/
auto name_hist_seed = "flux_inicial_expacs_"+str_stream_vwc+"%";
//~ TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), 150, bins);
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
for (int i = 0; i <Seed.size()-1; i++)
{
	flux_inicial->SetBinContent(i+1,Seed[i]);
}

double_t integral_flux_seed = flux_inicial->Integral();

/**Obtenemos los centros de bin de energia**/
for (int i = 0; i < binnum; i++)
{
	Double_t bin_center = flux_inicial->GetBinCenter(i+1);
	//~ cout << "bin " << i+1 << " bin center " << bin_center << endl;
	Emid.push_back(bin_center);
}

//~ cout << "Emid size " <<  Emid.size() << endl;



/********Flujo semilla diferencial para el algortimo EM*********/
for (int i = 0; i <Seed.size(); i++)
	{
		double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux[i] = Seed[i]/(E_mid); /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}


/***Llenamos el vector de neutrones y de errores de neutrones aleatorios gausianos****/
N = neutron_count_vector_gauss_MC(campaign,event-1,crptime); 
for(int i=0;i<N.size();i++)
	{
		double e_neu = sqrt(N[i]);
		dN[i]=e_neu; 
	}
//~ for(int i=0;i<N.size();i++)
	//~ {
		//~ cout <<  "dN_gauss " <<dN[i] << endl;
	//~ }
/***Llenamos el vector de CR de neutrones aleatorios gaussianos: N/T ****/
for(int i=0;i<N.size();i++)
	{
		double r;
		if(crptime==15){r=900;}
		if(crptime==60){r=3600;}
		CR[i]=N[i]/r;
	}
//~ for(int i=0;i<CR.size();i++)
	//~ {
		//~ cout << " CR Gauss " << CR[i] << endl;
	//~ };

//~ cout << "Neutrons percentage error vector filled: dN[i]/N[i]" << endl;
for(int i=0; i<N.size(); i++)
	{
		perc_e_N[i] = dN[i]/N[i];
		//~ cout << "i " << i <<  " dN[i]/N[i] " << perc_e_N[i] << endl;
    }
    
//~ cout << "CR [cps] vector: CR[i]" << " Time " << crptime << " min "  << endl;
//~ for(int i=0; i<CR.size(); i++)
	//~ {
		//~ cout << "i " << i <<  " CR[i] " << CR[i] << endl;
    //~ }
/***Llenamos el vector de dCR***/
//~ cout << " dCR[i] vector "  << endl;  
for(int i=0; i<N.size(); i++)
	{
		dCR[i] = CR[i]*perc_e_N[i];
		//~ cout << "i " << i <<  " dCR[i] " << dCR[i] << endl;
    }

/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/


//~ cout << "Response Function matrix filled: R " << endl;


/****************ACTIVACION/DESACTIVACION DE DETECTORES*************/

vector< vector<Double_t>> R_new;   /*matriz de funciones respuesta del espectrometro redefinida*/
vector<Double_t> N_new;   /*vector de CR redefinido*/
vector<Double_t> perc_e_N_new;
vector<Double_t> CR_new;
vector<Double_t> dCR_new;

vector<string> det_names{"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13","D14","D15","D16"}; /*vector de nombres de detectores activados*/
vector<string> det_names_act;

//~ vector<int> des_vector(ndet,0);
vector<int> act_vector(ndet,1);


vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};
//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			R_new.push_back(R[i]);
		}
	else{}
}

/**Inspeccionamos la matriz****/
//~ cout << " matrix size: " << R.size() << endl;

//~ for(int i = 0; i<R_new.size();i++){
	//~ cout << " row " << i << " ";
	//~ for (int j=0; j <R_new[0].size(); j++){

		 //~ cout <<  R_new[i][j] << " ";
	//~ }
   //~ cout << endl;
//~ }


/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(act_vector[i] == vec_test[i])
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;
cout << "ndet " << ndet << endl;
/*Redefinimos R*/
R = R_new;



//~ cout << " matrix size: " << R.size() << endl;
//~ for(int i = 0; i<R.size();i++){
	//~ cout << " row " << i << " ";
	//~ for (int j=0; j <R[0].size(); j++){

		 //~ cout <<  R[i][j] << " ";
	//~ }
   //~ cout << endl;
//~ }
perc_e_N.resize(ndet);
CR.resize(ndet);
dCR.resize(ndet);

perc_e_N = perc_e_N_new;
CR = CR_new;
dCR = dCR_new;


/*Redefinimos N*/
N.resize(ndet);
N = N_new;

//~ cout << " matrix size: " << N.size() << endl;

//~ for(int i = 0; i<N.size();i++){
	//~ cout << " row " << i << " " << N[i] << endl;
//~ }

/*******************************************************************/



if (norm==1){
/********Flujo semilla diferencial normalizado************/
for (int i = 0; i < Seed.size(); i++)
	{
		Flux[i] = Flux[i]/integral_flux_seed; //Normalizamos el flujo semilla
		// cout << i << " " << Flux[i] << endl;
	}
}
else {}



/*************************************************************/
/**************Algoritmo de deconvolucion EM******************/
/*************************************************************/

cout << "Inicia Deconvolucion" << endl;
	Double_t Sum_R=0.;
	Double_t Sum_R_Flux=0.;
	Double_t Sum_N_R_Flux=0.;
	
	//~ vector< vector<double_t> > vec_fluxnext_diff; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	vector< vector<double> > matrix_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	std::vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
	vector<double> seed_integral_representation(Seed.size());
	for (int i = 0; i<Seed.size(); i++)
	{
		double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		seed_integral_representation[i] = (Seed[i]/E_mid)*dE[i]; /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}
	matrix_fluxnext_Intg.push_back(seed_integral_representation);
	/***Definimos e inicializamos los estimadres estadisticos***/
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	//~ double_t chi2 = Chi_Square(N, N_rec, ndet);
	double chi2 = 30.;
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet);
	//~ double_t  chi2_red = Chi_Square_red(N, N_rec, ndet,crptime);
	double_t  chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet,crptime);
	double xi2_estimator;
	double barDelta_estimator;
	double STD_cr_estimator;
	
	//~ cout << "Chi2 inicial: " << chi2 << endl;
	//~ cout << "Chi2red inicial: "<< chi2_red << endl;
	
//~ /*contador em*/
int em_it = 0;
double diff_criteria = 10.;

	 //~ Chi2 <<setw(5) << setfill(' ') << "it" << " "
		 //~ <<setw(15) << setfill(' ') << "chi2" << " "
		 //~ <<setw(25) << setfill(' ') << "chi2_red"  << " "
		 //~ <<setw(25) << setfill(' ') << "xi2"  << " "
		 //~ <<setw(25) << setfill(' ') << "barDelta"  << " "
		 //~ <<setw(25) << setfill(' ') << "STD_cr" << endl;  

	//~ Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 //~ <<setw(15) << setfill(' ') << chi2 << " "
				 //~ <<setw(25) << setfill(' ') << chi2_red << endl;

if(steps==0)
{				 
	while(diff_criteria>0.01 || chi2>ndet )
	{
		FluxNext = Flux;
		for(Int_t b=0; b<binnum; b++)
			{
				//~ debug_em <<setw(5) << " b " << b << endl;
				Sum_R=0.;
				for(Int_t r=0; r<ndet; r++) {
					Sum_R += (R[r][b]);
					
					//~ debug_em <<setw(5) <<" r " << r << " Sum_R " << Sum_R << endl;
					}
				
				Sum_N_R_Flux=0.;
				for(Int_t r=0; r<ndet; r++)
					{
						Sum_R_Flux=0.;

							//~ debug_em <<setw(5) << " r " << r << endl;
							for(Int_t k=0; k<binnum; k++)
								{	
									Sum_R_Flux += (R[r][k]*Flux[k]*dE[k]); //  Flux[k]*dE[k] flujo integral, ya que Flux[k] es un flujo diferencial
								//~ debug_em <<setw(5) << " k " << k << " Sum_R_Flux " << Sum_R_Flux << endl;
								}
								//~ debug_em <<setw(5) << "Sum_R_Flux total " << Sum_R_Flux << endl;
								
						//~ Sum_N_R_Flux += ((R[r][b]* Flux[b])*N[r])/Sum_R_Flux;
						Sum_N_R_Flux += ((R[r][b]* Flux[b])*CR[r])/Sum_R_Flux;
						//~ debug_em <<setw(5) << " Sum_N_R_Flux : " << Sum_N_R_Flux << endl;
						
					}
				FluxNext[b] = Sum_N_R_Flux/Sum_R;
				//~ debug_em << " FluxNext[b] " << FluxNext[b] << endl;
				
			}
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < Seed.size(); i++) 
		 {
			FluxMin_diff[i] = Flux[i]; // flujo diferencial
			FluxMin_Intg[i] = Flux[i]*dE[i]; //integral
		 }

		
		 
		//~ TH1D *hist_step_diff = new TH1D(TString::Format("h0_diff_%d", it),"Flujo diferencial de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_diff->SetBinContent(i+1,FluxMin_diff[i]);
				//~ }
		//~ TH1D *hist_step_Intg = new TH1D(TString::Format("h0_Intg_%d", it),"Flujo Integral de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
				//~ }
				
		//~ double_t integral_flux_deconv_diff = hist_step_diff->Integral();
		//~ double_t integral_flux_deconv_Intg = hist_step_Intg->Integral();
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_diff << endl;
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_Intg << endl;
		
		/*Llenamos el vector de flujos deconvolucionados por paso*/
		//~ vec_fluxnext_diff.push_back(FluxMin_diff);
		matrix_fluxnext_Intg.push_back(FluxMin_Intg);

							//From std:vector to RVec
		RVec<double> deconv_flux_step_preceding = vector<double>(matrix_fluxnext_Intg[matrix_fluxnext_Intg.size()-2].begin(), matrix_fluxnext_Intg[matrix_fluxnext_Intg.size()-2].end());
		RVec<double> deconv_flux_step_present =  vector<double>(FluxMin_Intg.begin(),FluxMin_Intg.end());
		//~ cout << " deconv_flux_step_preceding " << deconv_flux_step_preceding << endl;
		//~ cout <<  "deconv_flux_step_present " << deconv_flux_step_present << endl;
		TH1D *hist_deconv_flux_step_preceding = new TH1D(TString::Format("h0_%d", em_it),"Flujo de neutrones deconvolucionado", binnum, bins);
		for (int i = 0; i <deconv_flux_step_preceding.size(); i++)
		{
			hist_deconv_flux_step_preceding->SetBinContent(i+1,deconv_flux_step_preceding[i]);
		}

		double integral_deconv_flux_step_preceding  = hist_deconv_flux_step_preceding->Integral(); /*Valor integral total del flujo integral */
		//~ cout << "integral :" << integral_deconv_flux_step_preceding << endl;

		/****Diferencia de flujos consecutivos****/
			RVec<double> diff;
			diff = abs(deconv_flux_step_present-deconv_flux_step_preceding)/integral_deconv_flux_step_preceding;
			//~ cout << " diff vector " << diff << endl;
			    double sum_vec;
				for(int k=0;k<diff.size();k++)
						{
							sum_vec+=diff[k];
						}
				diff_criteria = sum_vec;
				//~ sum_diff_vec.push_back(sum_vec);
			//~ cout << " chi2 " << chi2 << " diff value" << diff_criteria << endl;	

		/*Counting rate recalculado*/
		CR_rec = Recalculate(R, FluxMin_diff, dE, ndet); // CR recalculado

		/***Calculamos los estimadores estadisticos***/
		chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		em_it++;
		cout << "\r " << " em_it " << em_it;
		delete hist_deconv_flux_step_preceding;
		sum_vec=0;
		
		if(em_it>max_steps)
			{
				break;
		    }
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}

}

else
{				 
	for(int it = 0; it<steps ; it++)
	{
		FluxNext = Flux;
		for(Int_t b=0; b<binnum; b++)
			{
				//~ debug_em <<setw(5) << " b " << b << endl;
				Sum_R=0.;
				for(Int_t r=0; r<ndet; r++) {
					Sum_R += (R[r][b]);
					
					//~ debug_em <<setw(5) <<" r " << r << " Sum_R " << Sum_R << endl;
					}
				
				Sum_N_R_Flux=0.;
				for(Int_t r=0; r<ndet; r++)
					{
						Sum_R_Flux=0.;

							//~ debug_em <<setw(5) << " r " << r << endl;
							for(Int_t k=0; k<binnum; k++)
								{	
									Sum_R_Flux += (R[r][k]*Flux[k]*dE[k]); //  Flux[k]*dE[k] flujo integral, ya que Flux[k] es un flujo diferencial
								//~ debug_em <<setw(5) << " k " << k << " Sum_R_Flux " << Sum_R_Flux << endl;
								}
								//~ debug_em <<setw(5) << "Sum_R_Flux total " << Sum_R_Flux << endl;
								
						//~ Sum_N_R_Flux += ((R[r][b]* Flux[b])*N[r])/Sum_R_Flux;
						Sum_N_R_Flux += ((R[r][b]* Flux[b])*CR[r])/Sum_R_Flux;
						//~ debug_em <<setw(5) << " Sum_N_R_Flux : " << Sum_N_R_Flux << endl;
						
					}
				FluxNext[b] = Sum_N_R_Flux/Sum_R;
				//~ debug_em << " FluxNext[b] " << FluxNext[b] << endl;
				
			}
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < Seed.size(); i++) 
		 {
			FluxMin_diff[i] = Flux[i]; // flujo diferencial
			FluxMin_Intg[i] = Flux[i]*dE[i]; //integral
		 }
		//~ TH1D *hist_step_diff = new TH1D(TString::Format("h0_diff_%d", it),"Flujo diferencial de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_diff->SetBinContent(i+1,FluxMin_diff[i]);
				//~ }
		//~ TH1D *hist_step_Intg = new TH1D(TString::Format("h0_Intg_%d", it),"Flujo Integral de neutrones deconvolucionado", binnum, bins);
		//~ for (int i = 0; i <Seed.size(); i++)
				//~ {
					//~ hist_step_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
				//~ }
				
		//~ double_t integral_flux_deconv_diff = hist_step_diff->Integral();
		//~ double_t integral_flux_deconv_Intg = hist_step_Intg->Integral();
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_diff << endl;
		//~ cout << "Integral del flujo deconvolucionado diferencial: " << integral_flux_deconv_Intg << endl;
		
		/*Llenamos el vector de flujos deconvolucionados por paso*/
		//~ vec_fluxnext_diff.push_back(FluxMin_diff);
		//~ vec_fluxnext_Intg.push_back(FluxMin_Intg);

		/*Counting rate recalculado*/
		CR_rec = Recalculate(R, FluxMin_diff, dE, ndet); // CR recalculado

		/***Calculamos los estimadores estadisticos***/
		chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		
		em_it++;
		
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}
}

/****************************************************************************************************/
/*********************************Output*************************************************************/
/****************************************************************************************************/

/****SALIDA DEL EM******/

TH1D *hist_deconv_total_Intg = new TH1D(TString::Format("h0_%d", steps),"Flujo de neutrones deconvolucionado", binnum, bins);
for (int i = 0; i <FluxMin_Intg.size(); i++)
		{
			hist_deconv_total_Intg->SetBinContent(i+1,FluxMin_Intg[i]);
		}

double integral_flux_deconv_total_Intg = hist_deconv_total_Intg->Integral(); /*Valor integral total del flujo integral */
//~ cout << "Integral total flux deconv integral: " << integral_flux_deconv_total_Intg << endl;
/*Cambiamos los valores de x ligeramente para que los bines no se solapen, las regiones siguen siendo las mismas*/
double integral_flux_deconv_th = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(0),hist_deconv_total_Intg->FindBin(1.9*1e-07));
//~ cout << "Integral thermal region flux deconv: " << integral_flux_deconv_th << endl;
double integral_flux_deconv_ep = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(2.2*1e-07),hist_deconv_total_Intg->FindBin(0.9*1e-02));
//~ cout << "Integral epithermal region flux deconv: " << integral_flux_deconv_ep << endl;
double integral_flux_deconv_fs = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(1.1*1e-02),hist_deconv_total_Intg->FindBin(0.89*1e+01));
//~ cout << "Integral fast region flux deconv: " << integral_flux_deconv_fs << endl;
double integral_flux_deconv_he = hist_deconv_total_Intg->Integral(hist_deconv_total_Intg->FindBin(1.05*1e+01),hist_deconv_total_Intg->FindBin(7.6*1e+03));
//~ cout << "Integral high energy region flux deconv: " << integral_flux_deconv_he << endl;

//~ /***Llenamos en las dos ultima entradas del vector deconvolucionado, con el chi2 y chi2_red***/
//~ cout << "FluxMin size: " << FluxMin_Intg.size() << endl;
FluxMin_Intg.push_back(ndet);
FluxMin_Intg.push_back(integral_flux_deconv_total_Intg);
FluxMin_Intg.push_back(integral_flux_deconv_th);
FluxMin_Intg.push_back(integral_flux_deconv_ep);
FluxMin_Intg.push_back(integral_flux_deconv_fs);
FluxMin_Intg.push_back(integral_flux_deconv_he);
FluxMin_Intg.push_back(chi2);
FluxMin_Intg.push_back(chi2_red);
FluxMin_Intg.push_back(xi2_estimator);
FluxMin_Intg.push_back(barDelta_estimator);
FluxMin_Intg.push_back(STD_cr_estimator);
FluxMin_Intg.push_back(em_it);


em_vec_output = FluxMin_Intg;
//~ cout << "em_vec_output size: " << em_vec_output.size() << endl;
//~ for (int i=0; i<FluxMin_Intg.size();i++)
	//~ {
		//~ cout <<"i " << i << " FluxMin_Intg[i] "<< FluxMin_Intg[i] << endl;
	//~ }



	
delete flux_inicial;
delete hist_deconv_total_Intg;
vector<double>().swap(FluxMin_Intg); //liberamos el vector de la memoria
return em_vec_output;

}

void neutron_flux_plots(int vwc_seed){

int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> B; /*bins*/ /*vector de bordes de bins*/
vector<Double_t> dE; /*Vector de anchos de energia*/
vector<Double_t> E; /*matriz de Energias*/

std::ostringstream stream_vwc;
stream_vwc << vwc_seed;
std::string str_stream_vwc =stream_vwc.str();

//~ auto seed_flux_expacs_csv ="/home/flopez/Dropbo./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
cout <<"Generated root file from csv file" << endl;

/*Seleccionamos los datos del flujo semilla para LCO*/
auto seed_ref_cut_LCO = seed_rdf.Range(0, 158, 1); // pick an event every 1 entries from 0 to 150 because the last is excluded, that is 151 .
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
cout << "Entries number of LCO seed : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
Seed = df_seed_flux_vec;
/*Numero de bines*/
binnum = (const int) Seed.size();
//~ binnum = 130;
cout << "Bin num: " << binnum << endl;

/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_rdf.Take<double>("lower_edge_binvalue").GetValue();
B = df_binedges_vec;

//~ /*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_rdf.Take<double>("bin_width").GetValue();
dE = df_dE_vec;

/*Generamos el vector de bordes de bin energias*/
auto df_E_vec = seed_rdf.Take<double>("lower_edge_binvalue").GetValue();
E = df_E_vec;

/**********HISTOGRAMAS********************/
double *bins = B.data();



/**Inicializamos los vectores**/
auto name_hist_seed = "neutron_flux_per_unit_lethargy_VWC_"+str_stream_vwc+"%";
TH1D* neutron_flux_lethargy = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), 157, bins);
for (int i = 0; i < binnum; i++)
{
	neutron_flux_lethargy->SetBinContent(i+1,Seed[i]);
}

TH1D* neutron_flux_diff = new TH1D("Differential Neutron Flux","Differential Neutron Flux", 157, bins);
for (int i = 0; i < binnum; i++)
{
	neutron_flux_diff->SetBinContent(i+1,Seed[i]/E[i]);
}

TH1D* group_plot = new TH1D("Group Plot","Group Plot", 157, bins);
for (int i = 0; i < binnum; i++)
{
	group_plot->SetBinContent(i+1,(Seed[i]/E[i])*dE[i]);
}

TH1D* group_plot_per_energy = new TH1D("Group Plot per Energy","Group Plot per Energy", 157, bins);
for (int i = 0; i < binnum; i++)
{
	group_plot_per_energy->SetBinContent(i+1,(Seed[i]/E[i])*E[i]);
}

double int_group =  group_plot->Integral();
double int_group_per_energy = group_plot_per_energy->Integral();

cout << "Ratio " << int_group_per_energy/int_group << endl;


neutron_flux_diff->SetLineColor(kOrange);
group_plot->SetLineColor(kGreen);
group_plot_per_energy->SetLineColor(kBlue);
neutron_flux_lethargy->SetLineColor(kRed);

group_plot_per_energy->SetLineStyle(8);
neutron_flux_lethargy->SetLineStyle(3);
//~ P15_RP->SetLineColor(kOrange);
//~ P20_RP->SetLineColor(kRed);

neutron_flux_diff->SetLineWidth(4);
group_plot->SetLineWidth(4);
group_plot_per_energy->SetLineWidth(4);
neutron_flux_lethargy->SetLineWidth(4);


TCanvas *canvas_ne = new TCanvas("Neutron Spectrum","Neutron Spectrum");
gPad->SetLogx();
gPad->SetLogy();
neutron_flux_lethargy->GetXaxis()->SetTitle("Energy [MeV]" );
neutron_flux_lethargy->Draw("HIST");
group_plot->Draw("HIST SAME");
neutron_flux_diff->Draw("HIST SAME");
group_plot_per_energy->Draw("HIST SAME");


auto legend = new TLegend(0.744,0.785,0.948,0.949);
legend->SetHeader("Neutron flux spectrum representation","C"); // option "C" allows to center the header
legend->AddEntry(neutron_flux_lethargy,"Expacs Flux","l");
legend->AddEntry(neutron_flux_diff,"Differential Neutron Flux","l");
legend->AddEntry(group_plot,"Group Plot","l");
legend->AddEntry(group_plot_per_energy,"Group Plot per Energy","l");
legend->Draw();
	



}

//~ void TRS_data_csv_to_root(){
	 
//~ auto fileNameCSV ="/home/flopez/LIN/TESIS_DOC/Analysis/IAEA_REPORTS/TRS_403_DATA_Spectra.csv";
//~ auto df = ROOT::RDF::MakeCsvDataFrame(fileNameCSV); 													
//~ df.Snapshot("TRS_403_DATA_Spectra","./TRS_403_DATA_Spectra.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ }

void TRS_plot_spectra(){

TFile *TRS_Spectra_file = new TFile("TRS_403_DATA_Spectra.root");

ROOT::RDataFrame df_TRS_403("TRS_403_DATA_Spectra", TRS_Spectra_file);

/*Generamos un vector de bordes (elow) de energia*/
auto elow_vec = df_TRS_403.Take<double>("Elow").GetValue();
auto eup_vec = df_TRS_403.Take<double>("Eup").GetValue();
int eup_vec_size = eup_vec.size();

/*Generamos un vector de flujos de energia*/
auto cf252_spectrum_vec = df_TRS_403.Take<double>("Cf-252").GetValue();
auto Am241B_spectrum_vec = df_TRS_403.Take<double>("241Am-B").GetValue();

/**Agregamos el ultimo bin de energia a bin edges**/
double eup_last_entry = eup_vec[eup_vec_size-1];
cout << "Last energy of Eup vec: " << eup_last_entry << endl;
cout << "elow_vec size (bin edges): " << elow_vec.size() << endl;
elow_vec.push_back(eup_last_entry);

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = elow_vec.data();
//~ cout << sizeof(bins) << endl;
cout << "elow_vec size (bin edges): " << elow_vec.size() << endl;
int binnum = elow_vec.size() -1;


TH1D* neutron_fluence_cf252 = new TH1D("Neutron Fluence Cf-252","Neutron Fluence Cf-252",binnum , bins);
for (int i = 0; i < binnum; i++)
{
	neutron_fluence_cf252->SetBinContent(i+1,cf252_spectrum_vec[i]);
}

TH1D* neutron_fluence_214AmB = new TH1D("Neutron Fluence 214Am-B","Neutron Fluence 241Am-B",binnum , bins);
for (int i = 0; i < binnum; i++)
{
	neutron_fluence_214AmB ->SetBinContent(i+1,Am241B_spectrum_vec[i]);
}

//~ neutron_fluence_214AmB ->Scale(100);


TCanvas *canvas_spectra = new TCanvas("Neutron Spectrum","Neutron Spectrum");
gPad->SetLogx();
gPad->SetLogy();
neutron_fluence_cf252->GetXaxis()->SetTitle("Energy [MeV]");
neutron_fluence_cf252->GetYaxis()->SetTitle("Fluence per unit log energy [cm^{-1} lethargy^{-1}]");
neutron_fluence_cf252->Draw("HIST");
neutron_fluence_214AmB->Draw("HIST SAME");

auto legend = new TLegend(0.744,0.785,0.948,0.949);
legend->SetHeader("Neutron flux per unit lethargy","C"); // option "C" allows to center the header
legend->AddEntry(neutron_fluence_cf252,"Cf-252","l");
legend->AddEntry(neutron_fluence_214AmB,"241Am-B","l");
legend->Draw();


}

void em_loop_seed(string campaign,int event,int steps,int time_grid){

ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
stream_steps << steps;
stream_event << event; 
stream_timegrid << time_grid;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_em_it;


//~ ROOT::RDataFrame df_seed_loop_i(51);
ROOT::RDataFrame df_seed_loop_i(186);

vector<vector<Double_t> > vec_loop_seed;

/**Iteramos sobre las semillas**/
//186 en total (archivos): 1-151: 151, 32-100 (2 en 2): 35. Entonces 151+35=186
for(int i=0; i<186;i++)
	{
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Starting ... "<< endl;
		vec_loop_seed.push_back(deconv_em_output(campaign,event,steps,i,time_grid,"Intg",0));
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Finished. "<< endl;
		cout << " " << endl;
    }

/*Definimos los bordes de bin de los VWC%*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }
 

/**extraemos la info del numero de detectores*/
auto vec_loop_seed_elem =  vec_loop_seed[0];
vector<int> cut_vec_ndet =  {vec_loop_seed_elem.end() - 12, vec_loop_seed_elem.end()-11};
int ndet = cut_vec_ndet[0];

//~ /**extraemos la info del numero de pasos del metodo EM*/
//~ auto vec_loop_seed_elem_em_it =  vec_loop_seed[0];
//~ vector<int> cut_vec_em_it =  {vec_loop_seed_elem_em_it.end() - 1, vec_loop_seed_elem_em_it.end()};
//~ int em_it_value = cut_vec_em_it[0];

//~ if(steps==0){
	//~ stream_em_it << em_it_value;
	//~ str_stream_steps = stream_em_it.str();
	//~ }
//~ else{}

int rowid_deconv = 0;
int rowid_intg_total = 0;
int rowid_ndet = 0;
int rowid_intg_th = 0;
int rowid_intg_ep = 0;
int rowid_intg_fs = 0;
int rowid_intg_he = 0;
int rowid_Chi2 = 0;
int rowid_Chi2red = 0;
int rowid_xi2 = 0;
int rowid_bardelta = 0;
int rowid_std = 0;
int rowid_bin_seed = 0;
int rowid_em_it = 0;

auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
									  auto vec_loop_seed_element =  vec_loop_seed[rowid_deconv];
									  vector<Double_t> deconv_vec = {vec_loop_seed_element.begin(), vec_loop_seed_element.end() - 12};
									  rowid_deconv++;
									  return deconv_vec;
									})
									.Define("seed_bin_edgeds", [&]() {
									  auto bin_element =  x_vec_seed[rowid_bin_seed];
									  rowid_bin_seed++;
									  return bin_element;
									})
									.Define("ndet", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_ndet];
									  vector<int> cut_vec_ndet = {vec_loop_element.end() - 12, vec_loop_element.end()-11};
									  int ndet = cut_vec_ndet[0];
									  rowid_ndet++;
									  return ndet;
									  })
									.Define("Intg_total", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_total];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_total = cut_vec_intg[0];
									  rowid_intg_total++;
									  return Intg_total;
									  })
									.Define("Intg_th", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_th];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_th = cut_vec_intg[1];
									  rowid_intg_th++;
									  return Intg_th;
									  })
									.Define("Intg_ep", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_ep];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_ep = cut_vec_intg[2];
									  rowid_intg_ep++;
									  return Intg_ep;
									  })
									.Define("Intg_fs", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_fs];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_fs = cut_vec_intg[3];
									  rowid_intg_fs++;
									  return Intg_fs;
									  })
									.Define("Intg_he", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_he];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_he = cut_vec_intg[4];
									  rowid_intg_he++;
									  return Intg_he;
									  })                                                                                           
									.Define("Chi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double Chi2_value = cut_vec[0];
									  rowid_Chi2++;
									  return Chi2_value;
									})
									.Define("Chi2red", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2red];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double Chi2red_value = cut_vec[1];
									  rowid_Chi2red++;
									  return Chi2red_value;
									})
									.Define("xi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_xi2];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double xi2_value = cut_vec[2];
									  rowid_xi2++;
									  return xi2_value;
									})
									.Define("barDelta", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_bardelta];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double bardelta_value = cut_vec[3];
									  rowid_bardelta++;
									  return bardelta_value;
									})
									.Define("std_cr", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_std];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double std_cr_value = cut_vec[4];
									  rowid_std++;
									  return std_cr_value;
									})
									.Define("em_it", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_em_it];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double em_it_value = cut_vec[5];
									  rowid_em_it++;
									  return em_it_value;
									});

ostringstream stream_ndet; 
stream_ndet << ndet;
string str_stream_ndet = stream_ndet.str();

string df_file_name;
if(steps==0)
	{
		df_file_name = "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	}
else{	
		df_file_name = "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	}

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

}


void deconv_em_output_MC_vec2rootfile(vector<double> deconv_em_vec, string campaign,int event,int steps,int time_grid, int ndet, int mc_it){

ostringstream stream_mc_it; 
stream_mc_it<<mc_it;
string str_stream_mc_it = stream_mc_it.str();

ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
stream_steps << steps;
stream_event << event; 
stream_timegrid << time_grid;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_em_it;

ROOT::RDataFrame df_seed_loop_i(1);

//~ vector<Double_t> vec_event_MC_loop = deconv_em_vec;

//~ int rowid_deconv = 0;
//~ int rowid_intg_total = 0;
//~ int rowid_ndet = 0;
//~ int rowid_intg_th = 0;
//~ int rowid_intg_ep = 0;
//~ int rowid_intg_fs = 0;
//~ int rowid_intg_he = 0;
//~ int rowid_Chi2 = 0;
//~ int rowid_Chi2red = 0;
//~ int rowid_xi2 = 0;
//~ int rowid_bardelta = 0;
//~ int rowid_std = 0;
//~ int rowid_bin_seed = 0;
//~ int rowid_em_it = 0;

auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
									  //~ auto deconv_em_vec_element =  deconv_em_vec[rowid_deconv];
									  vector<Double_t> deconv_vec = {deconv_em_vec.begin(),deconv_em_vec.end() - 12};
									  //~ rowid_deconv++;
									  return deconv_vec;
									})
									.Define("ndet", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_ndet];
									  vector<int> cut_vec_ndet = {deconv_em_vec.end() - 12, deconv_em_vec.end()-11};
									  int ndet = cut_vec_ndet[0];
									  //~ rowid_ndet++;
									  return ndet;
									  })
									.Define("Intg_total", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_intg_total];
									  vector<Double_t> cut_vec_intg = {deconv_em_vec.end() - 11, deconv_em_vec.end()-6};
									  double Intg_total = cut_vec_intg[0];
									  //~ rowid_intg_total++;
									  return Intg_total;
									  })
									.Define("Intg_th", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_intg_th];
									  vector<Double_t> cut_vec_intg = {deconv_em_vec.end() - 11, deconv_em_vec.end()-6};
									  double Intg_th = cut_vec_intg[1];
									  //~ rowid_intg_th++;
									  return Intg_th;
									  })
									.Define("Intg_ep", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_intg_ep];
									  vector<Double_t> cut_vec_intg = {deconv_em_vec.end() - 11, deconv_em_vec.end()-6};
									  double Intg_ep = cut_vec_intg[2];
									  //~ rowid_intg_ep++;
									  return Intg_ep;
									  })
									.Define("Intg_fs", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_intg_fs];
									  vector<Double_t> cut_vec_intg = {deconv_em_vec.end() - 11, deconv_em_vec.end()-6};
									  double Intg_fs = cut_vec_intg[3];
									  //~ rowid_intg_fs++;
									  return Intg_fs;
									  })
									.Define("Intg_he", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_intg_he];
									  vector<Double_t> cut_vec_intg = {deconv_em_vec.end() - 11, deconv_em_vec.end()-6};
									  double Intg_he = cut_vec_intg[4];
									  //~ rowid_intg_he++;
									  return Intg_he;
									  })                                                                                           
									.Define("Chi2", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_Chi2];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double Chi2_value = cut_vec[0];
									  //~ rowid_Chi2++;
									  return Chi2_value;
									})
									.Define("Chi2red", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_Chi2red];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double Chi2red_value = cut_vec[1];
									  //~ rowid_Chi2red++;
									  return Chi2red_value;
									})
									.Define("xi2", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_xi2];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double xi2_value = cut_vec[2];
									  //~ rowid_xi2++;
									  return xi2_value;
									})
									.Define("barDelta", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_bardelta];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double bardelta_value = cut_vec[3];
									  //~ rowid_bardelta++;
									  return bardelta_value;
									})
									.Define("std_cr", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_std];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double std_cr_value = cut_vec[4];
									  //~ rowid_std++;
									  return std_cr_value;
									})
									.Define("em_it", [&]() {
									  //~ auto deconv_em_vec =  deconv_em_vec[rowid_em_it];
									  vector<Double_t> cut_vec = {deconv_em_vec.end() - 6, deconv_em_vec.end()};
									  double em_it_value = cut_vec[5];
									  //~ rowid_em_it++;
									  return em_it_value;
									});


ostringstream stream_ndet; 
stream_ndet << ndet;
string str_stream_ndet = stream_ndet.str();

string df_file_name;
if(steps==0)
	{
		df_file_name = "./deconv_data_rootfile/EM_MC_stop/data_em_mc_it/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop"+"_mc_it_"+str_stream_mc_it+".root";
	}
else{	
		df_file_name = "./deconv_data_rootfile/EM_MC/data_em_mc_it/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC"+"_mc_it_"+str_stream_mc_it+".root";
	}

//~ vector<Double_t>().swap(vec_event_MC_loop);

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

}

void em_loop_MC(string campaign,int event,int steps,int time_grid, int bin_seed){

auto start = std::chrono::system_clock::now();

ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
stream_steps << steps;
stream_event << event;
stream_timegrid << time_grid;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_em_it;

vector<vector<Double_t> > vec_event_MC_loop;
int N = 500000; //numero de iteraciones MC
int max_steps = 1000;
ROOT::RDataFrame df_seed_loop_i(N);

/**Iteramos sobre los eventos**/
//~ for(int i=event; i<=event;i++)
	//~ {
		int mc_it =0;
		/*Iteramos el algritmo EM sobre un evento i N veces.*/
		for(int k=1;k<=N;k++)
			{
				cout << "EM unfolding MC " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << bin_seed  << " MC iteration " << k <<  " Starting ... "<< endl;
				vec_event_MC_loop.push_back(deconv_em_output_MC(campaign,event,steps,bin_seed,time_grid,"Intg",0, max_steps));
				cout << " " << endl;
				mc_it++;
			}
    //~ }

/*Definimos los bordes de bin de los VWC%*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }
 

/**extraemos la info del numero de detectores*/
auto vec_event_MC_loop_elem = vec_event_MC_loop[0];
vector<int> cut_vec_ndet =  {vec_event_MC_loop_elem.end()-12, vec_event_MC_loop_elem.end()-11};
int ndet = cut_vec_ndet[0];

//~ /**extraemos la info del numero de pasos del metodo EM*/
//~ auto vec_loop_seed_elem_em_it =  vec_loop_seed[0];
//~ vector<int> cut_vec_em_it =  {vec_loop_seed_elem_em_it.end() - 1, vec_loop_seed_elem_em_it.end()};
//~ int em_it_value = cut_vec_em_it[0];

//~ if(steps==0){
	//~ stream_em_it << em_it_value;
	//~ str_stream_steps = stream_em_it.str();
	//~ }
//~ else{}

int rowid_deconv = 0;
int rowid_intg_total = 0;
int rowid_ndet = 0;
int rowid_intg_th = 0;
int rowid_intg_ep = 0;
int rowid_intg_fs = 0;
int rowid_intg_he = 0;
int rowid_Chi2 = 0;
int rowid_Chi2red = 0;
int rowid_xi2 = 0;
int rowid_bardelta = 0;
int rowid_std = 0;
int rowid_bin_seed = 0;
int rowid_em_it = 0;

auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
									  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
									  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 12};
									  rowid_deconv++;
									  return deconv_vec;
									})
									.Define("ndet", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
									  vector<int> cut_vec_ndet = {vec_loop_element.end() - 12, vec_loop_element.end()-11};
									  int ndet = cut_vec_ndet[0];
									  rowid_ndet++;
									  return ndet;
									  })
									.Define("Intg_total", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_total = cut_vec_intg[0];
									  rowid_intg_total++;
									  return Intg_total;
									  })
									.Define("Intg_th", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_th = cut_vec_intg[1];
									  rowid_intg_th++;
									  return Intg_th;
									  })
									.Define("Intg_ep", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_ep = cut_vec_intg[2];
									  rowid_intg_ep++;
									  return Intg_ep;
									  })
									.Define("Intg_fs", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_fs = cut_vec_intg[3];
									  rowid_intg_fs++;
									  return Intg_fs;
									  })
									.Define("Intg_he", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  double Intg_he = cut_vec_intg[4];
									  rowid_intg_he++;
									  return Intg_he;
									  })                                                                                           
									.Define("Chi2", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double Chi2_value = cut_vec[0];
									  rowid_Chi2++;
									  return Chi2_value;
									})
									.Define("Chi2red", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double Chi2red_value = cut_vec[1];
									  rowid_Chi2red++;
									  return Chi2red_value;
									})
									.Define("xi2", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double xi2_value = cut_vec[2];
									  rowid_xi2++;
									  return xi2_value;
									})
									.Define("barDelta", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double bardelta_value = cut_vec[3];
									  rowid_bardelta++;
									  return bardelta_value;
									})
									.Define("std_cr", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double std_cr_value = cut_vec[4];
									  rowid_std++;
									  return std_cr_value;
									})
									.Define("em_it", [&]() {
									  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  double em_it_value = cut_vec[5];
									  rowid_em_it++;
									  return em_it_value;
									});

ostringstream stream_ndet; 
stream_ndet << ndet;
string str_stream_ndet = stream_ndet.str();

string df_file_name;
if(steps==0)
	{
		df_file_name = "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
	}
else{	
		df_file_name = "./deconv_data_rootfile/EM_MC/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC.root";
	}

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

auto end = std::chrono::system_clock::now();
std::chrono::duration<float,std::ratio<3600>> duration = end - start; //hours
cout <<"Duration: " <<duration.count() << " hr " << endl;

}

//~ void em_mc_seed_picker(){
//~ /*La semilla que cumple el criterio de stop y que tome a menor cantidad de pasos, esto a partir de los datos EM con criterio de stop*/



//~ }

void em_loop_MC_opt(string campaign,int event,int steps,int time_grid, int ndet, int bin_seed, int random_seed){

	auto start = std::chrono::system_clock::now();

	ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
	stream_steps << steps;
	stream_event << event;
	stream_timegrid << time_grid;
	string str_stream_steps = stream_steps.str();
	string str_stream_event = stream_event.str();
	string str_stream_timegrid = stream_timegrid.str();
	string str_stream_em_it;

	ostringstream stream_ndet; 
	stream_ndet << ndet;
	string str_stream_ndet = stream_ndet.str();

	vector<vector<Double_t> > vec_event_MC_loop;
	//~ int N = 500000; //numero de iteraciones MC
	//~ int N = 10; //numero de iteraciones MC
	//~ int max_steps = 1000; //numero de maximo de pasos aceptable en EM
	//~ int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC

	//~ int N = 500000; //numero de iteraciones MC
	//~ int max_steps = 30; //numero de maximo de pasos aceptable en EM
	//~ int max_steps_filter = 15; //numero de maximo de pasos aceptable en EM
	//~ int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC

	int N = 2000000; //numero de iteraciones MC
	int max_steps_em = 19; //numero de maximo de pasos aceptable en EM
	//~ int max_steps_filter = 40; //numero de maximo de pasos aceptable en EM
	int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC


	/**Iteramos sobre los eventos**/
	//~ for(int i=event; i<=event;i++)
		//~ {
			int mc_it = 0;
			int mc_it_rejected =0;
			
			double em_it_value;
			/*Iteramos el algritmo EM sobre un evento i N veces.*/
			int bin_seed_new;
			TRandom3 r;
			for(int k=1;k<=N;k++)
				{
					
					//~ const auto random_number;
					if(random_seed==1)
						{
							/**Randm seed picker**/
							bin_seed_new = r.Integer(186);
							cout << " bin_seed " << bin_seed_new << endl;
						}
					else{bin_seed_new = bin_seed;}

					vector<Double_t> vec_event_MC_loop_element;
					
					cout << "\r " << "EM unfolding MC " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << bin_seed_new  << " MC iteration " << k <<  " Starting ... "<< endl;


					vec_event_MC_loop_element = deconv_em_output_MC(campaign,event,steps,bin_seed_new,time_grid,"Intg",0,max_steps_em);

					vec_event_MC_loop.push_back(vec_event_MC_loop_element);
					//~ vector<Double_t> cut_vec = {vec_event_MC_loop.end() - 6, vec_event_MC_loop.end()};
					//~ double em_it_value = cut_vec[5];
					em_it_value = vec_event_MC_loop_element.back();
					//~ rowid_em_it++;
					//~ if (em_it_value<max_steps_filter)
					if (em_it_value<max_steps_em)
					{
						mc_it++;
						cout << " Accepted " << "iteration " << mc_it << endl;
						//~ deconv_em_output_MC_vec2rootfile(vec_event_MC_loop_element,campaign,event,steps,time_grid,ndet,mc_it);
						cout << " " << endl;
					
						if(mc_it==max_em_mc_it)
							{
								cout << max_em_mc_it << " EM MC iterations complete" << endl;
								break;
								
							}
					}
					else{
							mc_it_rejected++;
							cout << " Rejected" << endl;
							cout << " " << endl;
						}

					vector<Double_t>().swap(vec_event_MC_loop_element);// liberamos el vector de la memoria
				}
				cout << "Accepted "  << mc_it << endl;
				cout << "Rejectec "  << mc_it_rejected << endl;


	ROOT::RDataFrame df_seed_loop_i(mc_it);

	int rowid_deconv = 0;
	int rowid_intg_total = 0;
	int rowid_ndet = 0;
	int rowid_intg_th = 0;
	int rowid_intg_ep = 0;
	int rowid_intg_fs = 0;
	int rowid_intg_he = 0;
	int rowid_Chi2 = 0;
	int rowid_Chi2red = 0;
	int rowid_xi2 = 0;
	int rowid_bardelta = 0;
	int rowid_std = 0;
	int rowid_bin_seed = 0;
	int rowid_em_it = 0;

	auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
										  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
										  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 12};
										  rowid_deconv++;
										  return deconv_vec;
										})
										.Define("ndet", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
										  vector<int> cut_vec_ndet = {vec_loop_element.end() - 12, vec_loop_element.end()-11};
										  int ndet = cut_vec_ndet[0];
										  rowid_ndet++;
										  return ndet;
										  })
										.Define("Intg_total", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
										  double Intg_total = cut_vec_intg[0];
										  rowid_intg_total++;
										  return Intg_total;
										  })
										.Define("Intg_th", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
										  double Intg_th = cut_vec_intg[1];
										  rowid_intg_th++;
										  return Intg_th;
										  })
										.Define("Intg_ep", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
										  double Intg_ep = cut_vec_intg[2];
										  rowid_intg_ep++;
										  return Intg_ep;
										  })
										.Define("Intg_fs", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
										  double Intg_fs = cut_vec_intg[3];
										  rowid_intg_fs++;
										  return Intg_fs;
										  })
										.Define("Intg_he", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
										  double Intg_he = cut_vec_intg[4];
										  rowid_intg_he++;
										  return Intg_he;
										  })                                                                                           
										.Define("Chi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double Chi2_value = cut_vec[0];
										  rowid_Chi2++;
										  return Chi2_value;
										})
										.Define("Chi2red", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double Chi2red_value = cut_vec[1];
										  rowid_Chi2red++;
										  return Chi2red_value;
										})
										.Define("xi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double xi2_value = cut_vec[2];
										  rowid_xi2++;
										  return xi2_value;
										})
										.Define("barDelta", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double bardelta_value = cut_vec[3];
										  rowid_bardelta++;
										  return bardelta_value;
										})
										.Define("std_cr", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double std_cr_value = cut_vec[4];
										  rowid_std++;
										  return std_cr_value;
										})
										.Define("em_it", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
										  double em_it_value = cut_vec[5];
										  rowid_em_it++;
										  return em_it_value;
										});

	//~ ostringstream stream_ndet; 
	//~ stream_ndet << ndet;
	//~ string str_stream_ndet = stream_ndet.str();

	string df_file_name;
	if(steps==0)
		{
			df_file_name = "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
		}
	else{	
			df_file_name = "./deconv_data_rootfile/EM_MC/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC.root";
		}

	df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float,std::ratio<3600>> duration = end - start; //hours
	cout <<"Duration: " <<duration.count() << " hr " << endl;

	}


void em_loop_events_MC_opt(string campaign,int event_inf, int event_sup, int steps,int time_grid, int ndet, int bin_seed, int random_seed)
{
	for(int i=event_inf;i<=event_sup;i++)
		{
				em_loop_MC_opt(campaign,i,steps,time_grid,ndet,bin_seed,random_seed);
		}
}



TH1D* deconv_hist_from_steps_and_seeds_TH1D(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation){

ostringstream stream_steps, stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_steps << steps;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
stream_seed << bin_seed;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_seed = stream_seed.str();
string str_stream_timegrid = stream_timegrid.str();

int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> dE; /*Vector de anchos de energia*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de Energias*/


/**************Energy Bin********************/
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;
/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
binnum = Seed.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;
/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;
//~ /*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
E = df_E_vec;
//~ cout << "E: df_E_vec " << B.size() << endl;
/*******************************************/

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = B.data();

/*Vector de flujo integral deconvolucionado*/
RVec<double> deconv_vec;

string input_complete_file;

if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

auto df_flux_deconv_matrix = df_seed_loop_step.Take<vector<double>>("deconv_vec").GetValue();

//~ cout <<"Branch deconv_vec size: " << df_flux_deconv_matrix.size() << endl;
//~ cout <<"Element from branch deconv_vec size: " <<  df_flux_deconv_matrix[0].size() << endl;
/**Extraemos el vector resultante del metodo EM dado cierta cantidad de pasos "steps" y asociad al numero de semilla "sed"*/
deconv_vec = df_flux_deconv_matrix[bin_seed-1];


/*Generamos el histograma*/

/*VWC%*/
ostringstream stream_vwc ;
auto df_vwc_vec = df_seed_loop_step.Take<double>("seed_bin_edgeds").GetValue();
double vwc_value = df_vwc_vec[bin_seed-1];
stream_vwc << vwc_value;
string str_stream_vwc = stream_vwc.str();



string name_hist_deconv = "Spectrum_"+campaign+"_Event_"+str_stream_event+"_Steps_"+str_stream_steps+"_BinSeed_"+str_stream_seed+"(VWC "+str_stream_vwc+"%)";
TH1D* flux_deconv = new TH1D(name_hist_deconv.c_str(),name_hist_deconv.c_str(), binnum , bins);
for (int i = 0; i <deconv_vec.size(); i++)
	{
		double E_mid;
		
		if(flux_representation=="Integral")
			{
				E_mid = dE[i]; // integral flux
			}
		if(flux_representation=="Lethargy")
			{
				E_mid = E[i]+(dE[i]/2.); // per unit lethargic
			}
		if(flux_representation=="Differential")
			{
				E_mid = 1.; //differential flux
			}

		/*Flux per unit lethargic dado que el flujo de entrada es el flujo integral, esto es, Flujo integral: deconv_vec[i]=Flux[i]*dE[i] */
		flux_deconv->SetBinContent(i+1,(deconv_vec[i]/dE[i])*E_mid); 
	}



flux_deconv->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
flux_deconv->GetXaxis()->SetTitleOffset(1.2);
flux_deconv->GetXaxis()->CenterTitle();
flux_deconv->GetXaxis()->SetTitleSize(0.04);
flux_deconv->SetStats(0);

		if(flux_representation=="Integral")
			{
				flux_deconv->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
				flux_deconv->GetYaxis()->SetTitleOffset(1.4);
			}
		if(flux_representation=="Lethargy")
			{
				flux_deconv->GetYaxis()->SetTitle("#bf{E#times#Phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
				flux_deconv->GetYaxis()->SetTitleOffset(1.7);
			}
		if(flux_representation=="Differential")
			{
				flux_deconv->GetYaxis()->SetTitle("#bf{#Phi(E) [cm^{-2} s^{-1} MeV^{-1}]}");
				flux_deconv->GetYaxis()->SetTitleOffset(1.3);
			}



flux_deconv->GetYaxis()->CenterTitle();
flux_deconv->GetYaxis()->SetTitleSize(0.04);

cout <<"Generated histogram for" << " Max Steps: " << steps << " Bin seed " << bin_seed << " Spectrum representation: " << flux_representation << endl;
return flux_deconv;

}

void deconv_flux_multiplot_by_seed(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation){

ostringstream stream_steps, stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_steps << steps;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
stream_seed << bin_seed;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_seed = stream_seed.str();
string str_stream_timegrid = stream_timegrid.str();

vector<TH1D*> hist_deconv_flux_vec;
vector<TH1D*> vec_hist_deconv_color_th; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_ep; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_fs; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_he; //vector de histogramas de flujos deconvolucionados

/*Llenamos un vector de histogramas por numero de pasos para la misma semilla*/
for(int i = 1; i<=steps;i++){
	hist_deconv_flux_vec.push_back(deconv_hist_from_steps_and_seeds_TH1D(campaign,event,i,timegrid, ndet, bin_seed,flux_representation));
}

for(int i=0;i<hist_deconv_flux_vec.size();i++){
/*Coloremos los histogramas deconvolucionados por region de energia*/
	auto hist_step_color_th = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_th->SetFillColor(kGray);
	hist_step_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);
	
	auto hist_step_color_ep = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_ep->SetFillColor(kCyan-9);
	hist_step_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);
	
	auto hist_step_color_fs = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_fs->SetFillColor(kGreen-9);
	hist_step_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);
	
	auto hist_step_color_he = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_he->SetFillColor(kRed-9);
	hist_step_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
	
	vec_hist_deconv_color_th.push_back(hist_step_color_th); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_ep.push_back(hist_step_color_ep); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_fs.push_back(hist_step_color_fs); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_he.push_back(hist_step_color_he); // llenamos el vector de histogramas coloreado	
}


/*Llenamos con la info de cada histograma: integrales por region y Chi2*/


vector< vector<double>> vec_data_steps;

for(int i = 1; i<=steps;i++){
	ostringstream stream_steps_new;
	stream_steps_new << i;
	string str_stream_steps_new = stream_steps_new.str();

	vector<double> vec_data_step;

	string input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps_new+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

	auto df_flux_deconv_ndet = df_seed_loop_step.Take<int>("ndet").GetValue();
	auto df_flux_deconv_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();
	auto df_flux_deconv_intg_th = df_seed_loop_step.Take<double>("Intg_th").GetValue();
	auto df_flux_deconv_intg_ep = df_seed_loop_step.Take<double>("Intg_ep").GetValue();
	auto df_flux_deconv_intg_fs = df_seed_loop_step.Take<double>("Intg_fs").GetValue();
	auto df_flux_deconv_intg_he = df_seed_loop_step.Take<double>("Intg_he").GetValue();
	auto df_flux_deconv_Chi2 = df_seed_loop_step.Take<double>("Chi2").GetValue();
	auto df_flux_deconv_Chi2red = df_seed_loop_step.Take<double>("Chi2red").GetValue();
	auto df_flux_deconv_xi2 = df_seed_loop_step.Take<double>("xi2").GetValue();
	auto df_flux_deconv_barDelta = df_seed_loop_step.Take<double>("barDelta").GetValue();
	auto df_flux_deconv_std_cr = df_seed_loop_step.Take<double>("std_cr").GetValue();
	
	//~ cout <<"Branch deconv_vec size: " << df_flux_deconv_matrix.size() << endl;
	//~ cout <<"Element from branch deconv_vec size: " <<  df_flux_deconv_matrix[0].size() << endl;
	/**Extraemos el vector resultante del metodo EM dado cierta cantidad de pasos "steps" y asociad al numero de semilla "sed"*/

	vec_data_step.push_back((double)df_flux_deconv_ndet[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_intg_total[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_intg_th[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_intg_ep[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_intg_fs[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_intg_he[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_Chi2[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_Chi2red[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_xi2[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_barDelta[bin_seed-1]);
	vec_data_step.push_back(df_flux_deconv_std_cr[bin_seed-1]);

	vec_data_steps.push_back(vec_data_step);
}

//~ for(int i=0; i<vec_data_steps.size(); i++){
	//~ for (int j =0; j<vec_data_steps[i].size();j++){
		//~ cout << "i " << vec_data_steps[i][j] << endl;
	//~ }
//~ }

string canvas_name;

if(flux_representation=="Integral")
			{
				canvas_name = "Deconv Flux, Integral Representation, Event_"+str_stream_event;
			}
if(flux_representation=="Lethargy")
			{
				canvas_name = "Deconv Flux, Lethargy Representation, Event_"+str_stream_event;
			}
if(flux_representation=="Differential")
			{
				canvas_name = "Deconv Flux, Differential Representation, Event_"+str_stream_event;
			}


TCanvas *canvas_deconv = new TCanvas(canvas_name.c_str(),canvas_name.c_str(),1920,1080);
canvas_deconv->SetSupportGL(true);
 
int canvas_value;
//~ if(steps%2 == 0 || sqrt(steps)==(int)sqrt(steps) )
	//~ {
		//~ canvas_value = sqrt(steps);
		//~ canvas_deconv->Divide(canvas_value,canvas_value);
	//~ }
//~ else{
		//~ canvas_value = int(sqrt(steps));
		
		canvas_deconv->Divide(5,4);
	//~ }




// llenamos cada entrada del canvas con un histograma del vector de histogramas
for (int i = 0; i < hist_deconv_flux_vec.size(); i++){

	
	vector<double> data_to_hist;
	data_to_hist = vec_data_steps[i];
	
	std::ostringstream stream_steps_new;
	stream_steps_new << i+1;
	std::string str_stream_steps_new = stream_steps_new.str();

	canvas_deconv->cd(i+1);
	gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	
	canvas_deconv->GetPad(i+1)->SetLeftMargin(0.15);
	canvas_deconv->GetPad(i+1)->SetRightMargin(0.009);
	double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
	if (flux_representation=="Differential")
		{
			gPad->SetLogy();
		}

	/*Destacamos los pads en los cuales chi-square es menor a ndet*/
	TPad* pad = (TPad*)canvas_deconv->GetPad(i+1);
	if (data_to_hist[6]<ndet){
               // Change pad properties to highlight it
				pad->SetFillColor(kYellow-9);
				pad->SetFillStyle(3003); // Solid fill
         }
    /*Para mostrar a partir de que valor los ratios se normalizan al dividir por la integral de la region de alta energia */
	double sum_eta_ratios = data_to_hist[2]/data_to_hist[5] + data_to_hist[3]/data_to_hist[5] + data_to_hist[4]/data_to_hist[5];
	 if (sum_eta_ratios<=1.0){
		           // Change pad properties to highlight it
				pad->SetFillColor(kMagenta-9);
				pad->SetFillStyle(3003); // Solid fill
			}
	 if (data_to_hist[6]<ndet & sum_eta_ratios<=1.0){
		           // Change pad properties to highlight it
				pad->SetFillColor(kOrange-9);
				pad->SetFillStyle(3003); // Solid fill
			}
	

	gPad->SetLogx();
	gStyle->SetTitleX(0.5);
	gStyle->SetTitleAlign(23);
	gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
	gStyle->SetOptStat(1001111);

	ostringstream stream_ndet, stream_intgtotal, stream_intgth, stream_intgep, stream_intgfs, stream_intghe, stream_Chi2, stream_Chi2red;
	ostringstream stream_intg_total_ratio_th, stream_intg_total_ratio_ep, stream_intg_total_ratio_fs, stream_intg_total_ratio_he;
	ostringstream stream_intg_he_ratio_th, stream_intg_he_ratio_ep, stream_intg_he_ratio_fs;
	ostringstream stream_sum_eta;

	ostringstream stream_xi2, stream_barDelta, stream_std_cr;
	
	stream_ndet << data_to_hist[0];
	stream_intgtotal << scientific << setprecision(3) << data_to_hist[1];
	stream_intgth << scientific << setprecision(3) << data_to_hist[2];
	stream_intgep << scientific << setprecision(3) << data_to_hist[3];
	stream_intgfs << scientific << setprecision(3) << data_to_hist[4];
	stream_intghe << scientific << setprecision(3) << data_to_hist[5];
	stream_Chi2 << setprecision(3)<< data_to_hist[6];
	stream_Chi2red << setprecision(3)<< data_to_hist[7];
	stream_xi2 << setprecision(3)<< data_to_hist[8];
	stream_barDelta << setprecision(3)<< data_to_hist[9];
	stream_std_cr << setprecision(3)<< data_to_hist[10];
	stream_sum_eta << setprecision(3) << sum_eta_ratios;
	
	stream_intg_total_ratio_th << setprecision(2) << data_to_hist[2]/data_to_hist[1];
	stream_intg_total_ratio_ep << setprecision(2) << data_to_hist[3]/data_to_hist[1];
	stream_intg_total_ratio_fs << setprecision(2) << data_to_hist[4]/data_to_hist[1];
	stream_intg_total_ratio_he << setprecision(2) << data_to_hist[5]/data_to_hist[1];

	stream_intg_he_ratio_th << setprecision(2) << data_to_hist[2]/data_to_hist[5];
	stream_intg_he_ratio_ep << setprecision(2) << data_to_hist[3]/data_to_hist[5];
	stream_intg_he_ratio_fs << setprecision(2) << data_to_hist[4]/data_to_hist[5];
	
	string str_stream_ndet = "#Det: "+stream_ndet.str()+" (ndf)";
	string str_stream_intgtotal = "Intg Total: "+stream_intgtotal.str();
	string str_stream_intgth = stream_intgth.str();
	string str_stream_intgep = stream_intgep.str();
	string str_stream_intgfs = stream_intgfs.str();
	string str_stream_intghe = stream_intghe.str();
	string str_stream_Chi2 = "#chi^{2}: "+stream_Chi2.str();
	string str_stream_Chi2red = "#chi^{2}/ndf: "+stream_Chi2red.str();

	string str_stream_xi2 = "#xi^{2}: "+stream_xi2.str();
	string str_stream_barDelta = "#bar{#Delta}: "+stream_barDelta.str();
	string str_stream_std_cr = "#sigma_{STD}: "+stream_std_cr.str();

	string str_stream_intg_total_ratio_th = "#frac{#Phi_{th}}{#Phi_{tot}}="+stream_intg_total_ratio_th.str();
	string str_stream_intg_total_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{tot}}="+stream_intg_total_ratio_ep.str();
	string str_stream_intg_total_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{tot}}="+stream_intg_total_ratio_fs.str();
	string str_stream_intg_total_ratio_he = "#frac{#Phi_{he}}{#Phi_{tot}}="+stream_intg_total_ratio_he.str();

	string str_stream_intg_he_ratio_th = "#frac{#Phi_{th}}{#Phi_{he}}="+stream_intg_he_ratio_th.str();
	string str_stream_intg_he_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{he}}="+stream_intg_he_ratio_ep.str();
	string str_stream_intg_he_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{he}}="+stream_intg_he_ratio_fs.str();

	string str_stream_sum_eta = "#sum_{#eta}="+stream_sum_eta.str();

	TLatex *l_ndet = new TLatex(0.15+shift_margin,0.85,str_stream_ndet.c_str());
	TLatex *l_intg_total = new TLatex(0.15+shift_margin,0.8,str_stream_intgtotal.c_str());
	TLatex *l_Chi2 = new TLatex(0.15+shift_margin,0.75,str_stream_Chi2.c_str());
	//~ TLatex *l_sum_eta = new TLatex(0.35+shift_margin,0.75,str_stream_sum_eta.c_str());
	TLatex *l_Chi2red = new TLatex(0.15+shift_margin,0.70,str_stream_Chi2red.c_str());
	TLatex *l_intg_th = new TLatex(0.15+shift_margin,0.12,str_stream_intgth.c_str());
	TLatex *l_intg_ep = new TLatex(0.35+shift_margin,0.12,str_stream_intgep.c_str());
	TLatex *l_intg_fs = new TLatex(0.58+shift_margin,0.12,str_stream_intgfs.c_str());
	TLatex *l_intg_he = new TLatex(0.78+shift_margin,0.12,str_stream_intghe.c_str());

	TLatex *l_xi2 = new TLatex(0.35+shift_margin,0.70,str_stream_xi2.c_str());
	TLatex *l_barDelta = new TLatex(0.58+shift_margin,0.70,str_stream_barDelta.c_str());
	TLatex *l_std_cr = new TLatex(0.78+shift_margin,0.70,str_stream_std_cr.c_str());

	TLatex *l_intgtotal_ratio_th = new TLatex(0.15+shift_margin,0.55,str_stream_intg_total_ratio_th.c_str());
	TLatex *l_intgtotal_ratio_ep = new TLatex(0.35+shift_margin,0.55,str_stream_intg_total_ratio_ep.c_str());
	TLatex *l_intgtotal_ratio_fs = new TLatex(0.58+shift_margin,0.55,str_stream_intg_total_ratio_fs.c_str());
	TLatex *l_intgtotal_ratio_he = new TLatex(0.78+shift_margin,0.55,str_stream_intg_total_ratio_he.c_str());

	TLatex *l_intghe_ratio_th = new TLatex(0.15+shift_margin,0.35,str_stream_intg_he_ratio_th.c_str());
	TLatex *l_intghe_ratio_ep = new TLatex(0.35+shift_margin,0.35,str_stream_intg_he_ratio_ep.c_str());
	TLatex *l_intghe_ratio_fs = new TLatex(0.58+shift_margin,0.35,str_stream_intg_he_ratio_fs.c_str());

	TLatex *l_sum_eta = new TLatex(0.78+shift_margin,0.35,str_stream_sum_eta.c_str());

	//~ intg_total->SetTextAlign(23);
	//~ intg_total->SetTextSize(0.08);
	
	hist_deconv_flux_vec[i]->Draw("HIST");
	vec_hist_deconv_color_th[i]->Draw("SAME");
	vec_hist_deconv_color_ep[i]->Draw("SAME");
	vec_hist_deconv_color_fs[i]->Draw("SAME");
	vec_hist_deconv_color_he[i]->Draw("SAME");
	l_ndet->SetNDC();
	l_ndet->SetTextSize(0.04);
	l_intg_total->SetNDC();
	l_intg_total->SetTextSize(0.04);
	l_Chi2->SetNDC();
	l_Chi2->SetTextSize(0.04);
	l_Chi2red->SetNDC();
	l_Chi2red->SetTextSize(0.04);
	l_intg_th->SetNDC();
	l_intg_th->SetTextSize(0.04);
	l_intg_ep->SetNDC();
	l_intg_ep->SetTextSize(0.04);
	l_intg_fs->SetNDC();
	l_intg_fs->SetTextSize(0.04);
	l_intg_he->SetNDC();
	l_intg_he->SetTextSize(0.04);

	l_intgtotal_ratio_th->SetNDC();
	l_intgtotal_ratio_th->SetTextSize(0.04);
	l_intgtotal_ratio_ep->SetNDC();
	l_intgtotal_ratio_ep->SetTextSize(0.04);
	l_intgtotal_ratio_fs->SetNDC();
	l_intgtotal_ratio_fs->SetTextSize(0.04);
	l_intgtotal_ratio_he->SetNDC();
	l_intgtotal_ratio_he->SetTextSize(0.04);

	l_intghe_ratio_th->SetNDC();
	l_intghe_ratio_th->SetTextSize(0.04);
	l_intghe_ratio_ep->SetNDC();
	l_intghe_ratio_ep->SetTextSize(0.04);
	l_intghe_ratio_fs->SetNDC();
	l_intghe_ratio_fs->SetTextSize(0.04);
	
	l_sum_eta->SetNDC();
	l_sum_eta->SetTextSize(0.04);

	l_xi2->SetNDC();
	l_xi2->SetTextSize(0.04);
	l_barDelta->SetNDC();
	l_barDelta->SetTextSize(0.04);
	l_std_cr->SetNDC();
	l_std_cr->SetTextSize(0.04);

		
	l_ndet->Draw("SAME");
	l_intg_th->Draw("SAME");
	l_intg_total->Draw("SAME");
	l_Chi2->Draw("SAME");
	l_Chi2red->Draw("SAME");
	l_intg_ep->Draw("SAME");
	l_intg_fs->Draw("SAME");
	l_intg_he->Draw("SAME");
	
	l_intgtotal_ratio_th->Draw("SAME");
	l_intgtotal_ratio_ep->Draw("SAME");
	l_intgtotal_ratio_fs->Draw("SAME");
	l_intgtotal_ratio_he->Draw("SAME");

	l_intghe_ratio_th->Draw("SAME");
	l_intghe_ratio_ep->Draw("SAME");
	l_intghe_ratio_fs->Draw("SAME");

	l_sum_eta->Draw("SAME");

	l_xi2->Draw("SAME");
	l_barDelta->Draw("SAME");
	l_std_cr->Draw("SAME");



	gPad->RedrawAxis();
	}

/*Mostramos el canvas y lo guardamos*/

canvas_deconv->Draw();
canvas_deconv->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".pdf").c_str());
canvas_deconv->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".eps").c_str());


//~ delete canvas_deconv;


}

void deconv_flux_multiplot_by_stop_criteria(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation){
ostringstream stream_steps, stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_steps << steps;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
stream_seed << bin_seed;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_seed = stream_seed.str();
string str_stream_timegrid = stream_timegrid.str();

vector<TH1D*> hist_deconv_flux_vec;
vector<TH1D*> vec_hist_deconv_color_th; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_ep; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_fs; //vector de histogramas de flujos deconvolucionados
vector<TH1D*> vec_hist_deconv_color_he; //vector de histogramas de flujos deconvolucionados

/*Llenamos un vector de histogramas de flujos deconvolucionados por semilla para el mismo evento, donde la iteracio del metodo em para por el criterio  de stop*/
int max_seed = 186;
for(int i = 1; i<=max_seed;i++)
		{
			hist_deconv_flux_vec.push_back(deconv_hist_from_steps_and_seeds_TH1D(campaign,event,steps,timegrid,ndet,i,flux_representation));
		}
		
for(int i=0;i<hist_deconv_flux_vec.size();i++){
/*Coloremos los histogramas deconvolucionados por region de energia*/
	auto hist_step_color_th = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_th->SetFillColor(kGray);
	hist_step_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);
	
	auto hist_step_color_ep = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_ep->SetFillColor(kCyan-9);
	hist_step_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);
	
	auto hist_step_color_fs = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_fs->SetFillColor(kGreen-9);
	hist_step_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);
	
	auto hist_step_color_he = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	hist_step_color_he->SetFillColor(kRed-9);
	hist_step_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
	
	vec_hist_deconv_color_th.push_back(hist_step_color_th); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_ep.push_back(hist_step_color_ep); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_fs.push_back(hist_step_color_fs); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_he.push_back(hist_step_color_he); // llenamos el vector de histogramas coloreado	
}


/*Llenamos con la info de cada histograma: integrales por region, Chi2 y numero de paso de stop*/

vector< vector<double>> vec_data_matrix;

string input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

for(int i = 1; i<=max_seed;i++){
	//~ ostringstream stream_steps_new;
	//~ stream_steps_new << i;
	//~ string str_stream_steps_new = stream_steps_new.str();

	vector<double> vec_data;

	//~ string input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps_new+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

	auto df_flux_deconv_ndet = df_seed_loop_step.Take<int>("ndet").GetValue();
	auto df_flux_deconv_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();
	auto df_flux_deconv_intg_th = df_seed_loop_step.Take<double>("Intg_th").GetValue();
	auto df_flux_deconv_intg_ep = df_seed_loop_step.Take<double>("Intg_ep").GetValue();
	auto df_flux_deconv_intg_fs = df_seed_loop_step.Take<double>("Intg_fs").GetValue();
	auto df_flux_deconv_intg_he = df_seed_loop_step.Take<double>("Intg_he").GetValue();
	auto df_flux_deconv_Chi2 = df_seed_loop_step.Take<double>("Chi2").GetValue();
	auto df_flux_deconv_Chi2red = df_seed_loop_step.Take<double>("Chi2red").GetValue();
	auto df_flux_deconv_xi2 = df_seed_loop_step.Take<double>("xi2").GetValue();
	auto df_flux_deconv_barDelta = df_seed_loop_step.Take<double>("barDelta").GetValue();
	auto df_flux_deconv_std_cr = df_seed_loop_step.Take<double>("std_cr").GetValue();
	auto df_flux_deconv_em_it = df_seed_loop_step.Take<double>("em_it").GetValue();
	
	/**Extraemos el vector resultante del metodo EM dado cierta cantidad de pasos "steps" y asociad al numero de semilla "sed"*/

	vec_data.push_back((double)df_flux_deconv_ndet[i-1]);
	vec_data.push_back(df_flux_deconv_intg_total[i-1]);
	vec_data.push_back(df_flux_deconv_intg_th[i-1]);
	vec_data.push_back(df_flux_deconv_intg_ep[i-1]);
	vec_data.push_back(df_flux_deconv_intg_fs[i-1]);
	vec_data.push_back(df_flux_deconv_intg_he[i-1]);
	vec_data.push_back(df_flux_deconv_Chi2[i-1]);
	vec_data.push_back(df_flux_deconv_Chi2red[i-1]);
	vec_data.push_back(df_flux_deconv_xi2[i-1]);
	vec_data.push_back(df_flux_deconv_barDelta[i-1]);
	vec_data.push_back(df_flux_deconv_std_cr[i-1]);
	vec_data.push_back(df_flux_deconv_em_it[i-1]);

	vec_data_matrix.push_back(vec_data);
}

string canvas_name;

if(flux_representation=="Integral")
			{
				canvas_name = "Deconv Flux, Integral Representation, Event_"+str_stream_event;
			}
if(flux_representation=="Lethargy")
			{
				canvas_name = "Deconv Flux, Lethargy Representation, Event_"+str_stream_event;
			}
if(flux_representation=="Differential")
			{
				canvas_name = "Deconv Flux, Differential Representation, Event_"+str_stream_event;
			}

string canvas_name_g1 = canvas_name+"_group_1";
string canvas_name_g2 = canvas_name+"_group_2";
string canvas_name_g3 = canvas_name+"_group_3";
string canvas_name_g4 = canvas_name+"_group_4";
string canvas_name_g5 = canvas_name+"_group_5";
string canvas_name_g6 = canvas_name+"_group_6";
string canvas_name_g7 = canvas_name+"_group_7";
string canvas_name_g8 = canvas_name+"_group_8";
string canvas_name_g9 = canvas_name+"_group_9";
string canvas_name_g10 = canvas_name+"_group_10";

TCanvas *canvas_deconv_group_1 = new TCanvas(canvas_name_g1.c_str(),canvas_name_g1.c_str(),1920,1080);
TCanvas *canvas_deconv_group_2 = new TCanvas(canvas_name_g2.c_str(),canvas_name_g2.c_str(),1920,1080);
TCanvas *canvas_deconv_group_3 = new TCanvas(canvas_name_g3.c_str(),canvas_name_g3.c_str(),1920,1080);
TCanvas *canvas_deconv_group_4 = new TCanvas(canvas_name_g4.c_str(),canvas_name_g4.c_str(),1920,1080);
TCanvas *canvas_deconv_group_5 = new TCanvas(canvas_name_g5.c_str(),canvas_name_g5.c_str(),1920,1080);
TCanvas *canvas_deconv_group_6 = new TCanvas(canvas_name_g6.c_str(),canvas_name_g6.c_str(),1920,1080);
TCanvas *canvas_deconv_group_7 = new TCanvas(canvas_name_g7.c_str(),canvas_name_g7.c_str(),1920,1080);
TCanvas *canvas_deconv_group_8 = new TCanvas(canvas_name_g8.c_str(),canvas_name_g8.c_str(),1920,1080);
TCanvas *canvas_deconv_group_9 = new TCanvas(canvas_name_g9.c_str(),canvas_name_g9.c_str(),1920,1080);
TCanvas *canvas_deconv_group_10 = new TCanvas(canvas_name_g10.c_str(),canvas_name_g10.c_str(),1920,1080);
 
canvas_deconv_group_1->Divide(5,4);//seed 1-20
canvas_deconv_group_2->Divide(5,4);//seed 21-40
canvas_deconv_group_3->Divide(5,4);//seed 41-60
canvas_deconv_group_4->Divide(5,4);//seed 61-80
canvas_deconv_group_5->Divide(5,4);//seed 81-100
canvas_deconv_group_6->Divide(5,4);//seed 101-120
canvas_deconv_group_7->Divide(5,4);//seed 121-140
canvas_deconv_group_8->Divide(5,4);//seed 141-160
canvas_deconv_group_9->Divide(5,4);//seed 161-180
canvas_deconv_group_10->Divide(3,2);//seed 181-186

// llenamos cada entrada del canvas con un histograma del vector de histogramas
for (int i = 0; i<186; i++){

	
	vector<double> data_to_hist;
	double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
	
	if(i<20)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1);
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_1->cd(i+1);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_1->GetPad(i+1)->SetLeftMargin(0.15);
			canvas_deconv_group_1->GetPad(i+1)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}
	if(20<=i & i<40)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-20;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_2->cd((i+1)-20);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_2->GetPad((i+1)-20)->SetLeftMargin(0.15);
			canvas_deconv_group_2->GetPad((i+1)-20)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}
	if(40<=i & i<60)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-40;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_3->cd((i+1)-40);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_3->GetPad((i+1)-40)->SetLeftMargin(0.15);
			canvas_deconv_group_3->GetPad((i+1)-40)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}
	if(60<=i & i<80)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-60;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_4->cd((i+1)-60);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_4->GetPad((i+1)-60)->SetLeftMargin(0.15);
			canvas_deconv_group_4->GetPad((i+1)-60)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}
	if(80<=i & i<100)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-80;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_5->cd((i+1)-80);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_5->GetPad((i+1)-80)->SetLeftMargin(0.15);
			canvas_deconv_group_5->GetPad((i+1)-80)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}		

	if(100<=i & i<120)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-100;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_6->cd((i+1)-100);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_6->GetPad((i+1)-100)->SetLeftMargin(0.15);
			canvas_deconv_group_6->GetPad((i+1)-100)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}	

	if(120<=i & i<140)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-120;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_7->cd((i+1)-120);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_7->GetPad((i+1)-120)->SetLeftMargin(0.15);
			canvas_deconv_group_7->GetPad((i+1)-120)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}	

	if(140<=i & i<160)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-140;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_8->cd((i+1)-140);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_8->GetPad((i+1)-140)->SetLeftMargin(0.15);
			canvas_deconv_group_8->GetPad((i+1)-140)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}	

	if(160<=i & i<180)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-160;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_9->cd((i+1)-160);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_9->GetPad((i+1)-160)->SetLeftMargin(0.15);
			canvas_deconv_group_9->GetPad((i+1)-160)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}	

	if(180<=i & i<186)
		{
			data_to_hist = vec_data_matrix[i];
			
			std::ostringstream stream_steps_new;
			stream_steps_new << (i+1)-180;
			std::string str_stream_steps_new = stream_steps_new.str();

			canvas_deconv_group_10->cd((i+1)-180);
			gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
			
			canvas_deconv_group_10->GetPad((i+1)-180)->SetLeftMargin(0.15);
			canvas_deconv_group_10->GetPad((i+1)-180)->SetRightMargin(0.009);
			//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
			if (flux_representation=="Differential")
				{
					gPad->SetLogy();
				}
		}	

	gPad->SetLogx();
	gStyle->SetTitleX(0.5);
	gStyle->SetTitleAlign(23);
	gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
	gStyle->SetOptStat(1001111);

	double sum_eta_ratios = data_to_hist[2]/data_to_hist[5] + data_to_hist[3]/data_to_hist[5] + data_to_hist[4]/data_to_hist[5];
		
	ostringstream stream_ndet, stream_intgtotal, stream_intgth, stream_intgep, stream_intgfs, stream_intghe, stream_Chi2, stream_Chi2red;
	ostringstream stream_intg_total_ratio_th, stream_intg_total_ratio_ep, stream_intg_total_ratio_fs, stream_intg_total_ratio_he;
	ostringstream stream_intg_he_ratio_th, stream_intg_he_ratio_ep, stream_intg_he_ratio_fs;
	ostringstream stream_sum_eta;
	ostringstream stream_steps_stop;
	ostringstream stream_xi2, stream_barDelta, stream_std_cr;
	
	
	stream_ndet << data_to_hist[0];
	stream_intgtotal << scientific << setprecision(3) << data_to_hist[1];
	stream_intgth << scientific << setprecision(3) << data_to_hist[2];
	stream_intgep << scientific << setprecision(3) << data_to_hist[3];
	stream_intgfs << scientific << setprecision(3) << data_to_hist[4];
	stream_intghe << scientific << setprecision(3) << data_to_hist[5];
	stream_Chi2 << setprecision(3)<< data_to_hist[6];
	stream_Chi2red << setprecision(3)<< data_to_hist[7];
	stream_xi2 << setprecision(3)<< data_to_hist[8];
	stream_barDelta << setprecision(3)<< data_to_hist[9];
	stream_std_cr << setprecision(3)<< data_to_hist[10];
	stream_sum_eta << setprecision(3) << sum_eta_ratios;
	
	stream_intg_total_ratio_th << setprecision(2) << data_to_hist[2]/data_to_hist[1];
	stream_intg_total_ratio_ep << setprecision(2) << data_to_hist[3]/data_to_hist[1];
	stream_intg_total_ratio_fs << setprecision(2) << data_to_hist[4]/data_to_hist[1];
	stream_intg_total_ratio_he << setprecision(2) << data_to_hist[5]/data_to_hist[1];

	stream_intg_he_ratio_th << setprecision(2) << data_to_hist[2]/data_to_hist[5];
	stream_intg_he_ratio_ep << setprecision(2) << data_to_hist[3]/data_to_hist[5];
	stream_intg_he_ratio_fs << setprecision(2) << data_to_hist[4]/data_to_hist[5];

	stream_steps_stop << data_to_hist[11];
	
	string str_stream_ndet = "#Det: "+stream_ndet.str()+" (ndf)";
	string str_stream_intgtotal = "Intg Total: "+stream_intgtotal.str();
	string str_stream_intgth = stream_intgth.str();
	string str_stream_intgep = stream_intgep.str();
	string str_stream_intgfs = stream_intgfs.str();
	string str_stream_intghe = stream_intghe.str();
	string str_stream_Chi2 = "#chi^{2}: "+stream_Chi2.str();
	string str_stream_Chi2red = "#chi^{2}/ndf: "+stream_Chi2red.str();

	string str_stream_xi2 = "#xi^{2}: "+stream_xi2.str();
	string str_stream_barDelta = "#bar{#Delta}: "+stream_barDelta.str();
	string str_stream_std_cr = "#sigma_{STD}: "+stream_Chi2red.str();

	string str_stream_intg_total_ratio_th = "#frac{#Phi_{th}}{#Phi_{tot}}="+stream_intg_total_ratio_th.str();
	string str_stream_intg_total_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{tot}}="+stream_intg_total_ratio_ep.str();
	string str_stream_intg_total_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{tot}}="+stream_intg_total_ratio_fs.str();
	string str_stream_intg_total_ratio_he = "#frac{#Phi_{he}}{#Phi_{tot}}="+stream_intg_total_ratio_he.str();

	string str_stream_intg_he_ratio_th = "#frac{#Phi_{th}}{#Phi_{he}}="+stream_intg_he_ratio_th.str();
	string str_stream_intg_he_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{he}}="+stream_intg_he_ratio_ep.str();
	string str_stream_intg_he_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{he}}="+stream_intg_he_ratio_fs.str();

	string str_stream_sum_eta = "#sum_{#eta}="+stream_sum_eta.str();

	string str_stream_steps_stop = "Steps="+stream_steps_stop.str();

	TLatex *l_ndet = new TLatex(0.15+shift_margin,0.85,str_stream_ndet.c_str());
	TLatex *l_intg_total = new TLatex(0.15+shift_margin,0.8,str_stream_intgtotal.c_str());
	TLatex *l_Chi2 = new TLatex(0.15+shift_margin,0.75,str_stream_Chi2.c_str());
	TLatex *l_steps_stop = new TLatex(0.35+shift_margin,0.75,str_stream_steps_stop.c_str());
	TLatex *l_Chi2red = new TLatex(0.15+shift_margin,0.70,str_stream_Chi2red.c_str());

	TLatex *l_xi2 = new TLatex(0.35+shift_margin,0.70,str_stream_xi2.c_str());
	TLatex *l_barDelta = new TLatex(0.58+shift_margin,0.70,str_stream_barDelta.c_str());
	TLatex *l_std_cr = new TLatex(0.78+shift_margin,0.70,str_stream_std_cr.c_str());



	TLatex *l_intg_th = new TLatex(0.15+shift_margin,0.12,str_stream_intgth.c_str());
	TLatex *l_intg_ep = new TLatex(0.35+shift_margin,0.12,str_stream_intgep.c_str());
	TLatex *l_intg_fs = new TLatex(0.58+shift_margin,0.12,str_stream_intgfs.c_str());
	TLatex *l_intg_he = new TLatex(0.78+shift_margin,0.12,str_stream_intghe.c_str());

	TLatex *l_intgtotal_ratio_th = new TLatex(0.15+shift_margin,0.55,str_stream_intg_total_ratio_th.c_str());
	TLatex *l_intgtotal_ratio_ep = new TLatex(0.35+shift_margin,0.55,str_stream_intg_total_ratio_ep.c_str());
	TLatex *l_intgtotal_ratio_fs = new TLatex(0.58+shift_margin,0.55,str_stream_intg_total_ratio_fs.c_str());
	TLatex *l_intgtotal_ratio_he = new TLatex(0.78+shift_margin,0.55,str_stream_intg_total_ratio_he.c_str());

	TLatex *l_intghe_ratio_th = new TLatex(0.15+shift_margin,0.35,str_stream_intg_he_ratio_th.c_str());
	TLatex *l_intghe_ratio_ep = new TLatex(0.35+shift_margin,0.35,str_stream_intg_he_ratio_ep.c_str());
	TLatex *l_intghe_ratio_fs = new TLatex(0.58+shift_margin,0.35,str_stream_intg_he_ratio_fs.c_str());

	TLatex *l_sum_eta = new TLatex(0.78+shift_margin,0.35,str_stream_sum_eta.c_str());

	//~ intg_total->SetTextAlign(23);
	//~ intg_total->SetTextSize(0.08);
	
	hist_deconv_flux_vec[i]->Draw("HIST");
	vec_hist_deconv_color_th[i]->Draw("SAME");
	vec_hist_deconv_color_ep[i]->Draw("SAME");
	vec_hist_deconv_color_fs[i]->Draw("SAME");
	vec_hist_deconv_color_he[i]->Draw("SAME");
	l_ndet->SetNDC();
	l_ndet->SetTextSize(0.04);
	l_intg_total->SetNDC();
	l_intg_total->SetTextSize(0.04);
	l_Chi2->SetNDC();
	l_Chi2->SetTextSize(0.04);
	l_Chi2red->SetNDC();
	l_Chi2red->SetTextSize(0.04);
	l_intg_th->SetNDC();
	l_intg_th->SetTextSize(0.04);
	l_intg_ep->SetNDC();
	l_intg_ep->SetTextSize(0.04);
	l_intg_fs->SetNDC();
	l_intg_fs->SetTextSize(0.04);
	l_intg_he->SetNDC();
	l_intg_he->SetTextSize(0.04);

	l_intgtotal_ratio_th->SetNDC();
	l_intgtotal_ratio_th->SetTextSize(0.04);
	l_intgtotal_ratio_ep->SetNDC();
	l_intgtotal_ratio_ep->SetTextSize(0.04);
	l_intgtotal_ratio_fs->SetNDC();
	l_intgtotal_ratio_fs->SetTextSize(0.04);
	l_intgtotal_ratio_he->SetNDC();
	l_intgtotal_ratio_he->SetTextSize(0.04);

	l_intghe_ratio_th->SetNDC();
	l_intghe_ratio_th->SetTextSize(0.04);
	l_intghe_ratio_ep->SetNDC();
	l_intghe_ratio_ep->SetTextSize(0.04);
	l_intghe_ratio_fs->SetNDC();
	l_intghe_ratio_fs->SetTextSize(0.04);
	
	l_sum_eta->SetNDC();
	l_sum_eta->SetTextSize(0.04);

	l_steps_stop->SetNDC();
	l_steps_stop->SetTextSize(0.04);

	l_xi2->SetNDC();
	l_xi2->SetTextSize(0.04);
	l_barDelta->SetNDC();
	l_barDelta->SetTextSize(0.04);
	l_std_cr->SetNDC();
	l_std_cr->SetTextSize(0.04);
	
		
	l_ndet->Draw("SAME");
	l_intg_th->Draw("SAME");
	l_intg_total->Draw("SAME");
	l_Chi2->Draw("SAME");
	l_Chi2red->Draw("SAME");
	l_intg_ep->Draw("SAME");
	l_intg_fs->Draw("SAME");
	l_intg_he->Draw("SAME");
	
	l_intgtotal_ratio_th->Draw("SAME");
	l_intgtotal_ratio_ep->Draw("SAME");
	l_intgtotal_ratio_fs->Draw("SAME");
	l_intgtotal_ratio_he->Draw("SAME");

	l_intghe_ratio_th->Draw("SAME");
	l_intghe_ratio_ep->Draw("SAME");
	l_intghe_ratio_fs->Draw("SAME");

	l_sum_eta->Draw("SAME");
	
	l_steps_stop->Draw("SAME");

	l_xi2->Draw("SAME");
	l_barDelta->Draw("SAME");
	l_std_cr->Draw("SAME");

	gPad->RedrawAxis();
	}

canvas_deconv_group_1->Draw();
canvas_deconv_group_2->Draw();
canvas_deconv_group_3->Draw();
canvas_deconv_group_4->Draw();
canvas_deconv_group_5->Draw();
canvas_deconv_group_6->Draw();
canvas_deconv_group_7->Draw();
canvas_deconv_group_8->Draw();
canvas_deconv_group_9->Draw();
canvas_deconv_group_10->Draw();
}

TH1D* em_step_plot_Chi_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();


string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Chi2_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model_chi2 = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");
//~ auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "rdfentry_", "Chi2");
auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "seed_bin_edgeds", "Chi2");

//~ auto Chi2_profile= df_seed_loop_step.Profile1D({profile_name_const, profile_name_const,50,0.,50}, "rdfentry_", "Chi2");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Chi2_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "#chi^{2}");
return h_steps;

}

TH1D* em_step_plot_IntgTotal_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Total_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");

auto IntgTotal_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_total");


//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)IntgTotal_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "IntgTotal");
return h_steps;

}

TH1D* em_step_plot_Intgth_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();
;

string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Thermal_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");

auto Intgth_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_th");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgth_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgth");
return h_steps;

}

TH1D* em_step_plot_Intgep_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Epithermal_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");

auto Intgep_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_ep");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgep_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgep");
return h_steps;

}

TH1D* em_step_plot_Intgfs_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();


string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Fast_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");

auto Intgfs_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_fs");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgfs_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgfs");
return h_steps;

}

TH1D* em_step_plot_Intghe_TH1D(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();


string input_complete_file;
if(steps==0)
{
	input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_High_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

for(int i=0;i<186;i++)
	{
		if(i<=150)
			{
				double x_bin_lowedges = i/5.;
				x_vec_seed.push_back(x_bin_lowedges);
			}
		if(i>150)
			{
				double x_bin_lowedges = (i- 135.)*2;
				x_vec_seed.push_back(x_bin_lowedges);
			}
    }

double *x_bin_edgeds = x_vec_seed.data();

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, x_vec_seed.size()-1, x_bin_edgeds, "");

auto Intghe_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_he");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intghe_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intghe");
return h_steps;

}
/*Funcion que genera un canvas donde se grafica en cada pad (6 en total): en el eje x el valor de semilla y en el eje y el valor de: Chi2, la integral total del flujo integral decnvolcionado */
/*la integral del rango termico, epitermico, rapido y de alta energia del flujo integral decnvolcionado, respectivamente. Todo esto para un cierto numero de iteraciones*/
/*del algoritmo EM*/
void em_loop_seed_plot_template(string campaign, int event, int steps, int timegrid, int ndet){

ostringstream stream_steps, stream_event, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();

vector<TH1D*> hist_vec_Chi2;
vector<TH1D*> hist_vec_IntgTotal;
vector<TH1D*> hist_vec_IntgTh;
vector<TH1D*> hist_vec_IntgEp;
vector<TH1D*> hist_vec_IntgFs;
vector<TH1D*> hist_vec_IntgHe;

for(int i = 1; i<=steps;i++){
	hist_vec_Chi2.push_back(em_step_plot_Chi_TH1D(campaign,event,i,timegrid,ndet));
	hist_vec_IntgTotal.push_back(em_step_plot_IntgTotal_TH1D(campaign,event,i,timegrid,ndet));
	hist_vec_IntgTh.push_back(em_step_plot_Intgth_TH1D(campaign,event,i,timegrid,ndet));
	hist_vec_IntgEp.push_back(em_step_plot_Intgep_TH1D(campaign,event,i,timegrid,ndet));
	hist_vec_IntgFs.push_back(em_step_plot_Intgfs_TH1D(campaign,event,i,timegrid,ndet));
	hist_vec_IntgHe.push_back(em_step_plot_Intghe_TH1D(campaign,event,i,timegrid,ndet));		
}

string canvas_name = "Chi2 seed loop, Event: "+str_stream_event;
TCanvas *canvas_Chi2 = new TCanvas("Chi2 seed loop",canvas_name.c_str());

canvas_Chi2->Divide(2,3);

//~ kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
//~ kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
//~ kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900

vector<int> colors = {800,632,900,616,880,600,860,432,840,416,820,400,600-4,600-7,600-9,600-10,600-9,600-6,600-2,600+3};

canvas_Chi2->cd(1);

	for(int i = 0; i<steps;i++){
	 hist_vec_Chi2[i]->SetLineColor(colors[i]);
	}

	hist_vec_Chi2[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_Chi2[i]->DrawClone("SAME");
	}

canvas_Chi2->cd(2);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgTotal[i]->SetLineColor(colors[i]);
	}

	hist_vec_IntgTotal[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgTotal[i]->DrawClone("SAME");
	}

canvas_Chi2->cd(3);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgTh[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgTh[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgTh[i]->DrawClone("SAME");
	}

canvas_Chi2->cd(4);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgEp[i]->SetLineColor(colors[i]);
	}

	hist_vec_IntgEp[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgEp[i]->DrawClone("SAME");
	}

canvas_Chi2->cd(5);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgFs[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgFs[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgFs[i]->DrawClone("SAME");
	}

canvas_Chi2->cd(6);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgHe[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgHe[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgHe[i]->DrawClone("SAME");
	}


}

void em_loop_seed_plot(int event, int steps){

std::ostringstream stream_event;
stream_event << event;
std::string str_stream_event = stream_event.str();

string input_complete_file_1 = "/home/flopez/LIN/TESIS_DOC/Analysis/deconv/EM_unfolding_loop_event_"+str_stream_event+"_steps_1.root";
string input_complete_file_2 = "/home/flopez/LIN/TESIS_DOC/Analysis/deconv/EM_unfolding_loop_event_"+str_stream_event+"_steps_2.root";
string input_complete_file_3 = "/home/flopez/LIN/TESIS_DOC/Analysis/deconv/EM_unfolding_loop_event_"+str_stream_event+"_steps_3.root";
string input_complete_file_4 = "/home/flopez/LIN/TESIS_DOC/Analysis/deconv/EM_unfolding_loop_event_"+str_stream_event+"_steps_4.root";
string input_complete_file_5 = "/home/flopez/LIN/TESIS_DOC/Analysis/deconv/EM_unfolding_loop_event_"+str_stream_event+"_steps_5.root";

ROOT::RDataFrame df_seed_loop_step_1("em_loop_tree", input_complete_file_1);
ROOT::RDataFrame df_seed_loop_step_2("em_loop_tree", input_complete_file_2);
ROOT::RDataFrame df_seed_loop_step_3("em_loop_tree", input_complete_file_3);
ROOT::RDataFrame df_seed_loop_step_4("em_loop_tree", input_complete_file_4);
ROOT::RDataFrame df_seed_loop_step_5("em_loop_tree", input_complete_file_5);

auto Chi2_profile_1 = df_seed_loop_step_1.Profile1D({"Chi2_Step_1", "EM loop",50,0.,50}, "rdfentry_", "Chi2");
auto Chi2_profile_2 = df_seed_loop_step_2.Profile1D({"Chi2_Step_2", "EM loop",50,0.,50}, "rdfentry_", "Chi2");
auto Chi2_profile_3 = df_seed_loop_step_3.Profile1D({"Chi2_Step_3", "EM loop",50,0.,50}, "rdfentry_", "Chi2");
auto Chi2_profile_4 = df_seed_loop_step_4.Profile1D({"Chi2_Step_4", "EM loop",50,0.,50}, "rdfentry_", "Chi2");
auto Chi2_profile_5 = df_seed_loop_step_5.Profile1D({"Chi2_Step_5", "EM loop",50,0.,50}, "rdfentry_", "Chi2");

string canvas_name = "Chi2 seed loop, Event: "+str_stream_event;
TCanvas *canvas_Chi2 = new TCanvas("Chi2 seed loop",canvas_name.c_str());

Chi2_profile_1->SetLineColor(kOrange);
Chi2_profile_2->SetLineColor(kGreen);
Chi2_profile_3->SetLineColor(kBlue);
Chi2_profile_4->SetLineColor(kRed);
Chi2_profile_5->SetLineColor(kYellow-3);

TH1D *h_steps_1 = (TH1D*)Chi2_profile_1->Clone("Step1");
TH1D *h_steps_2 = (TH1D*)Chi2_profile_2->Clone("Step2");
TH1D *h_steps_3 = (TH1D*)Chi2_profile_3->Clone("Step3");
TH1D *h_steps_4 = (TH1D*)Chi2_profile_4->Clone("Step4");
TH1D *h_steps_5 = (TH1D*)Chi2_profile_5->Clone("Step5");

h_steps_1->GetXaxis()->SetTitle("Seed" );
h_steps_1->GetYaxis()->SetTitle( "#chi^{2}");
h_steps_1->DrawClone("HIST");
h_steps_2->DrawClone("SAME");
h_steps_3->DrawClone("SAME");
h_steps_4->DrawClone("SAME");
h_steps_5->DrawClone("SAME");

auto legend = new TLegend(0.744,0.785,0.948,0.949);
legend->SetHeader("#chi^2 value by steps","C"); // option "C" allows to center the header
legend->AddEntry(h_steps_1,"Steps 1","l");
legend->AddEntry(h_steps_2,"Steps 2","l");
legend->AddEntry(h_steps_3,"Steps 3","l");
legend->AddEntry(h_steps_4,"Steps 4","l");
legend->AddEntry(h_steps_5,"Steps 5","l");
legend->Draw();



}

void scatter_plot_4var(string campaign, int event, int steps, int timegrid, int ndet)
{
	ostringstream stream_steps, stream_event, stream_ndet, stream_timegrid;
	stream_steps << steps;
	stream_timegrid << timegrid;
	stream_event << event;
	stream_ndet << ndet;
	string str_stream_steps = stream_steps.str();
	string str_stream_event = stream_event.str();
	string str_stream_ndet = stream_ndet.str();
	string str_stream_timegrid = stream_timegrid.str();
	
   auto canvas = new TCanvas("scatter_plot","scatter_plot",1920,1080);
   gPad->Modified();
   gPad->Update();
   gStyle->SetCanvasPreferGL(kTRUE);
   gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
   gStyle->SetPalette(kBird, 0, 0.6); // define a transparent palette
   

	string input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	ROOT::RDataFrame df_event("em_loop_tree", input_complete_file);

	auto df_event_vwc = df_event.Take<double>("seed_bin_edgeds").GetValue();
	auto df_event_chi2 = df_event.Take<double>("Chi2").GetValue();
	auto df_event_em_it = df_event.Take<double>("em_it").GetValue();
	auto df_event_Intg_total = df_event.Take<double>("Intg_total").GetValue();

	int n_scatter_size = df_event_vwc.size();
	/*borde de bines como array*/
	double *x_vwc = df_event_vwc.data();
	double *y_chi2 = df_event_chi2.data();
	double *c_em_it = df_event_em_it.data(); // color
	double *s_intg_total = df_event_Intg_total.data(); //size 

   string scatter_plot_title = campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot;%VWC;#chi^{2}";
   auto scatter = new TScatter(n_scatter_size, x_vwc, y_chi2, c_em_it, s_intg_total);
   scatter->SetMarkerStyle(20);
   //~ scatter->SetTitle("Scatter plot;VWC;#chi^{2}");
   scatter->SetTitle(scatter_plot_title.c_str());
   scatter->Draw("A");

   canvas->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot.pdf").c_str());


}

TScatter* scatter_plot_4var_tscatter(string campaign, int event, int steps, int timegrid, int ndet)
{
	ostringstream stream_steps, stream_event, stream_ndet, stream_timegrid;
	stream_steps << steps;
	stream_timegrid << timegrid;
	stream_event << event;
	stream_ndet << ndet;
	string str_stream_steps = stream_steps.str();
	string str_stream_event = stream_event.str();
	string str_stream_ndet = stream_ndet.str();
	string str_stream_timegrid = stream_timegrid.str();


	string input_complete_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	ROOT::RDataFrame df_event("em_loop_tree", input_complete_file);

	auto df_event_vwc = df_event.Take<double>("seed_bin_edgeds").GetValue();
	auto df_event_chi2 = df_event.Take<double>("Chi2").GetValue();
	auto df_event_em_it = df_event.Take<double>("em_it").GetValue();
	auto df_event_Intg_total = df_event.Take<double>("Intg_total").GetValue();

	int n_scatter_size = df_event_vwc.size();
	/*borde de bines como array*/
	double *x_vwc = df_event_vwc.data();
	double *y_chi2 = df_event_chi2.data();
	double *c_em_it = df_event_em_it.data(); // color
	double *s_intg_total = df_event_Intg_total.data(); //size 
 
   string scatter_plot_title = campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot;%VWC;#chi^{2}";
   auto scatter = new TScatter(n_scatter_size, x_vwc, y_chi2, c_em_it, s_intg_total);
   scatter->SetMarkerStyle(20);
   //~ scatter->SetTitle("Scatter plot;VWC;#chi^{2}");
   scatter->SetMaxMarkerSize(3);
   scatter->SetMinMarkerSize(0.5);
   scatter->SetTitle(scatter_plot_title.c_str());

	return scatter;
	delete scatter;
}

void scatter_plot_4var_MC(string campaign, int event, int steps, int timegrid, int ndet, int step_filter, int chi2cut)
{
	ostringstream stream_steps, stream_event, stream_ndet, stream_timegrid;
	stream_steps << steps;
	stream_timegrid << timegrid;
	stream_event << event;
	stream_ndet << ndet;
	string str_stream_steps = stream_steps.str();
	string str_stream_event = stream_event.str();
	string str_stream_ndet = stream_ndet.str();
	string str_stream_timegrid = stream_timegrid.str();
	
   auto canvas = new TCanvas("scatter_plot","scatter_plot",1920,1080);
   gPad->Modified();
   gPad->Update();
   gStyle->SetCanvasPreferGL(kTRUE);
   gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
   gStyle->SetPalette(kBird, 0, 0.6); // define a transparent palette
   

	string input_complete_file= "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
	ROOT::RDataFrame df_event("em_loop_tree", input_complete_file);

	
	double step_event = step_filter;
	auto lambda_cut_step = [&](double &em_it){
		if(em_it<=step_event)
			{
				return true;
			}
		else{return false;}
		
	};
	double chi2_cut = chi2cut;
	auto lambda_cut_chi2 = [&](double &Chi2){
		if(Chi2>chi2_cut)
			{
				return true;
			}
		else{return false;}
		
	};

	auto df_event_entry = df_event.Filter(lambda_cut_chi2,{"Chi2"}).Filter(lambda_cut_step,{"em_it"}).Take<ULong64_t>("rdfentry_").GetValue();
	vector<double> df_event_entry_fix;
	for(int i=0;i<df_event_entry.size();i++)
		{
			double val = (double)df_event_entry[i];
			df_event_entry_fix.push_back(val);
	    }
	auto df_event_chi2 = df_event.Filter(lambda_cut_chi2,{"Chi2"}).Filter(lambda_cut_step,{"em_it"}).Take<double>("Chi2").GetValue();
	auto df_event_em_it = df_event.Filter(lambda_cut_chi2,{"Chi2"}).Filter(lambda_cut_step,{"em_it"}).Take<double>("em_it").GetValue();
	auto df_event_Intg_total = df_event.Filter(lambda_cut_chi2,{"Chi2"}).Filter(lambda_cut_step,{"em_it"}).Take<double>("Intg_total").GetValue();

	int n_scatter_size = df_event_entry_fix.size();
	/*borde de bines como array*/
	double *x_entry= df_event_entry_fix.data();
	double *y_chi2 = df_event_chi2.data();
	double *c_em_it = df_event_em_it.data(); // color
	double *s_intg_total = df_event_Intg_total.data(); //size 

	ostringstream stream_mc_it;
	stream_mc_it << n_scatter_size;
	string str_stream_mc_it = stream_mc_it.str();
   string scatter_plot_title = campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot_MC_"+str_stream_mc_it+"_it;entry;#chi^{2}";
   auto scatter = new TScatter(n_scatter_size, x_entry, y_chi2, c_em_it, s_intg_total);
   scatter->SetMarkerStyle(20);
   //~ scatter->SetTitle("Scatter plot;VWC;#chi^{2}");
   scatter->SetTitle(scatter_plot_title.c_str());
   scatter->Draw("A");

   canvas->SaveAs(("./deconv_data_pdf/EM_scatter_plots/MC/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot_MC_"+str_stream_mc_it+"_it.pdf").c_str());


}

void scatter_plots_event_loop(string campaign, int event, int steps, int timegrid, int ndet){

	ostringstream stream_steps, stream_event, stream_ndet, stream_timegrid;
	stream_steps << steps;
	stream_timegrid << timegrid;
	stream_event << event;
	stream_ndet << ndet;
	string str_stream_steps = stream_steps.str();
	string str_stream_event = stream_event.str();
	string str_stream_ndet = stream_ndet.str();
	string str_stream_timegrid = stream_timegrid.str();


vector<TScatter*> vec_scater_plot;

/*Iteramos sobre el numero de eventos*/
for(int i=1;i<=21;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=23; i<=45; i++)
	{
		 vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=49;i<=54;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=55;i<=69;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=71;i<=83;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=85;i<=110;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=112;i<=193;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=194;i<=239;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }   
for(int i=241;i<=272;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=275;i<=283;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }
for(int i=285;i<=289;i++)
	{
		vec_scater_plot.push_back(scatter_plot_4var_tscatter(campaign,i,steps,timegrid, ndet));
    }

string canvas_name = "Scatter_plot";

string canvas_name_g1 = canvas_name+"_group_1";
string canvas_name_g2 = canvas_name+"_group_2";
string canvas_name_g3 = canvas_name+"_group_3";
string canvas_name_g4 = canvas_name+"_group_4";
string canvas_name_g5 = canvas_name+"_group_5";
string canvas_name_g6 = canvas_name+"_group_6";
string canvas_name_g7 = canvas_name+"_group_7";
string canvas_name_g8 = canvas_name+"_group_8";
string canvas_name_g9 = canvas_name+"_group_9";
string canvas_name_g10 = canvas_name+"_group_10";
string canvas_name_g11 = canvas_name+"_group_11";
string canvas_name_g12 = canvas_name+"_group_12";
string canvas_name_g13 = canvas_name+"_group_13";
string canvas_name_g14 = canvas_name+"_group_14";
string canvas_name_g15 = canvas_name+"_group_15";
string canvas_name_g16 = canvas_name+"_group_16";
string canvas_name_g17 = canvas_name+"_group_17";
string canvas_name_g18 = canvas_name+"_group_18";

TCanvas *canvas_deconv_group_1 = new TCanvas(canvas_name_g1.c_str(),canvas_name_g1.c_str(),1920,1080);
TCanvas *canvas_deconv_group_2 = new TCanvas(canvas_name_g2.c_str(),canvas_name_g2.c_str(),1920,1080);
TCanvas *canvas_deconv_group_3 = new TCanvas(canvas_name_g3.c_str(),canvas_name_g3.c_str(),1920,1080);
TCanvas *canvas_deconv_group_4 = new TCanvas(canvas_name_g4.c_str(),canvas_name_g4.c_str(),1920,1080);
TCanvas *canvas_deconv_group_5 = new TCanvas(canvas_name_g5.c_str(),canvas_name_g5.c_str(),1920,1080);
TCanvas *canvas_deconv_group_6 = new TCanvas(canvas_name_g6.c_str(),canvas_name_g6.c_str(),1920,1080);
TCanvas *canvas_deconv_group_7 = new TCanvas(canvas_name_g7.c_str(),canvas_name_g7.c_str(),1920,1080);
TCanvas *canvas_deconv_group_8 = new TCanvas(canvas_name_g8.c_str(),canvas_name_g8.c_str(),1920,1080);
TCanvas *canvas_deconv_group_9 = new TCanvas(canvas_name_g9.c_str(),canvas_name_g9.c_str(),1920,1080);
TCanvas *canvas_deconv_group_10 = new TCanvas(canvas_name_g10.c_str(),canvas_name_g10.c_str(),1920,1080);
TCanvas *canvas_deconv_group_11 = new TCanvas(canvas_name_g11.c_str(),canvas_name_g11.c_str(),1920,1080);
TCanvas *canvas_deconv_group_12 = new TCanvas(canvas_name_g12.c_str(),canvas_name_g12.c_str(),1920,1080);
TCanvas *canvas_deconv_group_13 = new TCanvas(canvas_name_g13.c_str(),canvas_name_g13.c_str(),1920,1080);
TCanvas *canvas_deconv_group_14 = new TCanvas(canvas_name_g14.c_str(),canvas_name_g14.c_str(),1920,1080);
TCanvas *canvas_deconv_group_15 = new TCanvas(canvas_name_g15.c_str(),canvas_name_g15.c_str(),1920,1080);
TCanvas *canvas_deconv_group_16 = new TCanvas(canvas_name_g16.c_str(),canvas_name_g16.c_str(),1920,1080);
TCanvas *canvas_deconv_group_17 = new TCanvas(canvas_name_g17.c_str(),canvas_name_g17.c_str(),1920,1080);
TCanvas *canvas_deconv_group_18 = new TCanvas(canvas_name_g18.c_str(),canvas_name_g18.c_str(),1920,1080);
 
canvas_deconv_group_1->Divide(4,4);//seed 1-16
canvas_deconv_group_2->Divide(4,4);//seed 17-33
canvas_deconv_group_3->Divide(4,4);//seed 34-50
canvas_deconv_group_4->Divide(4,4);//seed 51-67
canvas_deconv_group_5->Divide(4,4);//seed 68-84
canvas_deconv_group_6->Divide(4,4);//seed 85-101
canvas_deconv_group_7->Divide(4,4);//seed 102-118
canvas_deconv_group_8->Divide(4,4);//seed 119-135
canvas_deconv_group_9->Divide(4,4);//seed 136-152
canvas_deconv_group_10->Divide(4,4);//seed 153-169
canvas_deconv_group_11->Divide(4,4);//seed 170-186
canvas_deconv_group_12->Divide(4,4);
canvas_deconv_group_13->Divide(4,4);
canvas_deconv_group_14->Divide(4,4);
canvas_deconv_group_15->Divide(4,4);
canvas_deconv_group_16->Divide(4,4);
canvas_deconv_group_17->Divide(4,4);
canvas_deconv_group_18->Divide(4,4);

/* llenamos cada entrada del canvas con un histograma del vector de histogramas*/
int count_group=0;
int total_events = 289 - 11; //278
//~ int total_events = 289;
for (int i = 0; i<total_events; i++){

		  gPad->Modified();
		  gPad->Update();
		  gStyle->SetCanvasPreferGL(kTRUE);
		  gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
		  gStyle->SetPalette(kBird, 0, 0.6); // define a transparent palette
		if(i<16)
			{
			 canvas_deconv_group_1->cd(i+1);
			}
		if(16<=i & i<32)
			{
			 canvas_deconv_group_2->cd((i+1)-16);
			}
		if(32<=i & i<48)
			{
			 canvas_deconv_group_3->cd((i+1)-32);
			}
		if(48<=i & i<64)
			{
			 canvas_deconv_group_4->cd((i+1)-48);
			}
		if(64<=i & i<80)
			{
			 canvas_deconv_group_5->cd((i+1)-64);
			}
		if(80<=i & i<96)
			{
			 canvas_deconv_group_6->cd((i+1)-80);
			}
		if(96<=i & i<112)
			{
			 canvas_deconv_group_7->cd((i+1)-96);
			}
		if(112<=i & i<128)
			{
			 canvas_deconv_group_8->cd((i+1)-112);
			}
		if(128<=i & i<144)
			{
			 canvas_deconv_group_9->cd((i+1)-128);
			}
		if(144<=i & i<160)
			{
			 canvas_deconv_group_10->cd((i+1)-144);
			}								
		if(160<=i & i<176)
			{
			 canvas_deconv_group_11->cd((i+1)-160);
			}	
		if(176<=i & i<192)
			{
			 canvas_deconv_group_12->cd((i+1)-176);
			}	
		if(192<=i & i<208)
			{
			 canvas_deconv_group_13->cd((i+1)-192);
			}	
		if(208<=i & i<224)
			{
			 canvas_deconv_group_14->cd((i+1)-208);
			}	
		if(224<=i & i<240)
			{
			 canvas_deconv_group_15->cd((i+1)-224);
			}
		if(240<=i & i<256)
			{
			 canvas_deconv_group_16->cd((i+1)-240);
			}
		if(256<=i & i<272)
			{
			 canvas_deconv_group_17->cd((i+1)-256);
			}
		if(272<=i & i<278)
			{
			 canvas_deconv_group_18->cd((i+1)-272);
			}
		vec_scater_plot[i]->Draw("A");

		count_group+=i;
	}
	
canvas_deconv_group_1->Draw();
canvas_deconv_group_2->Draw();
canvas_deconv_group_3->Draw();
canvas_deconv_group_4->Draw();
canvas_deconv_group_5->Draw();
canvas_deconv_group_6->Draw();
canvas_deconv_group_7->Draw();
canvas_deconv_group_8->Draw();
canvas_deconv_group_9->Draw();
canvas_deconv_group_10->Draw();
canvas_deconv_group_11->Draw();
canvas_deconv_group_12->Draw();
canvas_deconv_group_13->Draw();
canvas_deconv_group_14->Draw();
canvas_deconv_group_15->Draw();
canvas_deconv_group_16->Draw();
canvas_deconv_group_17->Draw();
canvas_deconv_group_18->Draw();

	canvas_deconv_group_1->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g1+".pdf").c_str());
	canvas_deconv_group_2->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g2+".pdf").c_str());
	canvas_deconv_group_3->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g3+".pdf").c_str());
	canvas_deconv_group_4->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g4+".pdf").c_str());
	canvas_deconv_group_5->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g5+".pdf").c_str());
	canvas_deconv_group_6->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g6+".pdf").c_str());
	canvas_deconv_group_7->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g7+".pdf").c_str());
	canvas_deconv_group_8->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g8+".pdf").c_str());
	canvas_deconv_group_9->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g9+".pdf").c_str());
	canvas_deconv_group_10->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g10+".pdf").c_str());
	canvas_deconv_group_11->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g11+".pdf").c_str());
	canvas_deconv_group_12->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g12+".pdf").c_str());
	canvas_deconv_group_13->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g13+".pdf").c_str());
	canvas_deconv_group_14->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g14+".pdf").c_str());
	canvas_deconv_group_15->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g15+".pdf").c_str());
	canvas_deconv_group_16->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g16+".pdf").c_str());
	canvas_deconv_group_17->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g17+".pdf").c_str());
	canvas_deconv_group_18->SaveAs(("./deconv_data_pdf/EM_scatter_plots/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g18+".pdf").c_str());
}

RVec<double> deconv_steps_diff(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed){

ostringstream stream_event, stream_ndet, stream_seed, stream_timegrid;
//~ stream_steps << steps;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
stream_seed << bin_seed;
//~ string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_seed = stream_seed.str();
string str_stream_timegrid = stream_timegrid.str();
	
/*Vector de flujo integral deconvolucionado*/
RVec<double> deconv_vec;

string input_complete_file;


RVec<RVec<double>> deconv_vec_matrix;
vector<double> vec_intg_total;

		
for(int i=1;i<=20;i++)
	{
		double intg_value=0.;



		ostringstream stream_steps;
		stream_steps << i;
		string str_stream_steps;
		str_stream_steps = stream_steps.str();
		input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

		ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

		auto df_flux_deconv_matrix = df_seed_loop_step.Take<vector<double>>("deconv_vec").GetValue();
		auto df_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();

		deconv_vec = df_flux_deconv_matrix[bin_seed-1];
		intg_value = df_intg_total[bin_seed-1];


		deconv_vec_matrix.push_back(deconv_vec);
		vec_intg_total.push_back(intg_value);
	}


RVec<RVec<double>> diff_matrix;
RVec<double> sum_diff_vec;
RVec<int> steps_vec;


for(int j=0;j<deconv_vec_matrix.size()-1;j++)
	{
		RVec<double> diff;
		diff = abs(deconv_vec_matrix[j+1]-deconv_vec_matrix[j])/vec_intg_total[j];

		double sum_vec =0;
		for(int k=0;k<diff.size();k++)
			{
				sum_vec+=diff[k];
			}
		//~ cout<<" j " << j <<" sum_vec : " << sum_vec << endl;
		//~ diff_matrix.push_back(diff);
		sum_diff_vec.push_back(sum_vec);
		//~ steps_vec.push_back(j+1);
		//~ cout << diff << endl;
	}



 int n = sum_diff_vec.size();
 auto g = new TGraph(n);
   for (int i = 0; i < sum_diff_vec.size(); ++i) {
        g->SetPoint(i, i, sum_diff_vec[i]);
    }

 //~ TCanvas *canvas_diff = new TCanvas("diff","diff",1920,1080);
    //~ TLine *line = new TLine(0, 0.01,18, 0.01);
	//~ gPad->Modified();
	//~ gPad->Update();
   
    //~ line->SetLineColor(kRed);
   //~ string graph_name = "Event_"+str_stream_event+"_bin_seed_"+str_stream_seed+";steps;Diff";
   //~ g->SetTitle(graph_name.c_str());
   //~ g->Draw("AC*");
   //~ line->DrawClone();

   //~ delete canvas_diff;
   return sum_diff_vec;

}

void event_seed_picker_1(string campaign, int event, int steps, int timegrid, int ndet){

/**diff<1**/

ostringstream stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_timegrid = stream_timegrid.str();
	


vector<int> step_pick;

		
for(int i=1;i<=186;i++)
	{
		
		RVec<double> diff_vec = deconv_steps_diff(campaign,event,steps,timegrid,ndet,i);
		int count_step=1; 
		
		for(int j=0;j<diff_vec.size();j++)
			{
					
					if(diff_vec[j]>0.01)
						{
							count_step++;
						}
					else{break;}

				
			}
				cout << "seed " << i << " step " << count_step+1 << endl;
			    step_pick.push_back(count_step+1); // from 1 because we kept the deconv flux j+1 from the difference in steps
			    //~ count_step=0;
			
		
	}

vector<vector<double>> deconv_vec_matrix;
vector<double> vec_intg_total;

for(int i=1;i<=186;i++)
	{
		vector<double> deconv_vec;
		double intg_value;
		
		
		ostringstream stream_step_pick;
		stream_step_pick <<step_pick[i-1];
		string str_stream_step_pick = stream_step_pick.str();
		
		string input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

		ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

		auto df_flux_deconv_matrix = df_seed_loop_step.Take<vector<double>>("deconv_vec").GetValue();
		auto df_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();
		deconv_vec = df_flux_deconv_matrix[i-1];
		intg_value = df_intg_total[i-1];
		deconv_vec_matrix.push_back(deconv_vec);
		vec_intg_total.push_back(intg_value );
		vector<double>().swap(deconv_vec); //liberamos el vector de la memoria
	}



/**************Energy Bin********************/
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;
/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
//~ Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
int binnum = df_seed_flux_vec.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;
/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;
//~ /*Generamos el vector de ancho de energias*/
//~ auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
//~ dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;

double *bins = df_binedges_vec.data();
vector<TH1D*> hist_vec;

for(int i=0;i<deconv_vec_matrix.size();i++)
	{
		TH1D *hist_step = new TH1D(TString::Format("h0_%d", i+1),"Flujo de neutrones deconvolucionado, diff<1%", binnum, bins);
		
		for(int j=0;j<deconv_vec_matrix[i].size();j++)
			{
				hist_step->SetBinContent(j+1,deconv_vec_matrix[i][j]);
				
			}
			hist_vec.push_back(hist_step);
	}

TCanvas *canvas_deconv_fluxes = new TCanvas("deconv_fluxes","deconv_fluxes",1920,1080);
canvas_deconv_fluxes->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetOptStat(0);

hist_vec[0]->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
hist_vec[0]->GetXaxis()->SetTitleOffset(1.2);
hist_vec[0]->GetXaxis()->CenterTitle();
hist_vec[0]->GetXaxis()->SetTitleSize(0.04);
hist_vec[0]->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
hist_vec[0]->GetYaxis()->SetTitleOffset(1.4);
hist_vec[0]->GetYaxis()->CenterTitle();
hist_vec[0]->GetYaxis()->SetTitleSize(0.04);

//~ kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
//~ kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
//~ kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900

vector<int> colors = {800,632,900,616,880,600,860,432,840,416,820,400,600-4,600-7,600-9,600-10,600-9,600-6,600-2,600+3};

hist_vec[0]->SetLineColorAlpha(colors[1],0.45);
hist_vec[0]->Draw("HIST");
gPad->SetLogx();
gPad->RedrawAxis();


for(int i=1;i<hist_vec.size();i++)
	{
		if(step_pick[i-1]==7)
		{
			hist_vec[i]->SetLineColorAlpha(colors[0],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==8)
		{
			hist_vec[i]->SetLineColorAlpha(colors[1],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==9)
		{
			hist_vec[i]->SetLineColorAlpha(colors[2],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==10)
		{
			hist_vec[i]->SetLineColorAlpha(colors[3],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==11)
		{
			hist_vec[i]->SetLineColorAlpha(colors[4],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==12)
		{
			hist_vec[i]->SetLineColorAlpha(colors[5],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==13)
		{
			hist_vec[i]->SetLineColorAlpha(colors[6],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==14)
		{
			hist_vec[i]->SetLineColorAlpha(colors[7],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==15)
		{
			hist_vec[i]->SetLineColorAlpha(colors[8],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==16)
		{
			hist_vec[i]->SetLineColorAlpha(colors[9],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}		
	}
hist_vec[70]->SetLineColor(kYellow);
hist_vec[70]->Draw("HIST SAME");


canvas_deconv_fluxes->Draw();
canvas_deconv_fluxes->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos.pdf").c_str());


}

void event_seed_picker_2(string campaign, int event, int steps, int timegrid, int ndet){

/**chi2<11 && diff<1%**/

ostringstream stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_timegrid = stream_timegrid.str();
	


vector<int> step_pick;
vector<vector<double>> matrix_chi2;

for(int i=1;i<=186;i++)
	{
		vector<double> vec_chi2;
		
		for(int k=1;k<=20;k++)
			{
				double intg_value=0.;
				double chi2_value=0.;
				

				ostringstream stream_steps;
				stream_steps << k;
				string str_stream_steps;
				str_stream_steps = stream_steps.str();
				string input_complete_file = "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

				ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

				auto df_chi2 = df_seed_loop_step.Take<double>("Chi2").GetValue();
				chi2_value = df_chi2[i-1];
				//~ cout << "chi2 "<< chi2_value << endl;
				vec_chi2.push_back(chi2_value);
			}
			matrix_chi2.push_back(vec_chi2);
			vector<double>().swap(vec_chi2); //liberamos el vector de la memoria
	}

for(int i=1;i<=186;i++)
	{

		RVec<double> diff_vec = deconv_steps_diff(campaign,event,steps,timegrid,ndet,i);
		int count_step; 
		
		for(int j=0;j<diff_vec.size();j++)
			{
				 //~ cout << j << " " << matrix_chi2[i-1][j+1] << " " << diff_vec[j] << endl;
				if(matrix_chi2[i-1][j+1]<11. && diff_vec[j]<0.01)
					{
								
								count_step = j+1; // +1 because j start from 0
								break;
					}

			}
			cout << "seed " << i << " step " << count_step+1 << endl; 
			step_pick.push_back(count_step+1); // from 1 because we kept the deconv flux j+1 from the difference in steps

}

vector<vector<double>> deconv_vec_matrix;
vector<double> vec_intg_total;

for(int i=1;i<=186;i++)
	{
		vector<double> deconv_vec;
		double intg_value;
		
		
		ostringstream stream_step_pick;
		stream_step_pick <<step_pick[i-1];
		string str_stream_step_pick = stream_step_pick.str();
		
		string input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

		ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

		auto df_flux_deconv_matrix = df_seed_loop_step.Take<vector<double>>("deconv_vec").GetValue();
		auto df_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();
		deconv_vec = df_flux_deconv_matrix[i-1];
		intg_value = df_intg_total[i-1];
		deconv_vec_matrix.push_back(deconv_vec);
		vec_intg_total.push_back(intg_value );
		vector<double>().swap(deconv_vec); //liberamos el vector de la memoria
	}



/**************Energy Bin********************/
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;
/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
//~ Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
int binnum = df_seed_flux_vec.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;
/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;
//~ /*Generamos el vector de ancho de energias*/
//~ auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
//~ dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;

double *bins = df_binedges_vec.data();
vector<TH1D*> hist_vec;

for(int i=0;i<deconv_vec_matrix.size();i++)
	{
		TH1D *hist_step = new TH1D(TString::Format("h0_%d", i+1),"Flujo de neutrones deconvolucionado, #chi^{2}<11 y diff<1%", binnum, bins);
		
		for(int j=0;j<deconv_vec_matrix[i].size();j++)
			{
				hist_step->SetBinContent(j+1,deconv_vec_matrix[i][j]);
				
			}
			hist_vec.push_back(hist_step);
	}

TCanvas *canvas_deconv_fluxes = new TCanvas("deconv_fluxes","deconv_fluxes",1920,1080);
canvas_deconv_fluxes->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetOptStat(0);

hist_vec[0]->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
hist_vec[0]->GetXaxis()->SetTitleOffset(1.2);
hist_vec[0]->GetXaxis()->CenterTitle();
hist_vec[0]->GetXaxis()->SetTitleSize(0.04);
hist_vec[0]->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
hist_vec[0]->GetYaxis()->SetTitleOffset(1.4);
hist_vec[0]->GetYaxis()->CenterTitle();
hist_vec[0]->GetYaxis()->SetTitleSize(0.04);

//~ kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
//~ kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
//~ kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900

vector<int> colors = {800,632,900,616,880,600,860,432,840,416,820,400,600-4,600-7,600-9,600-10,600-9,600-6,600-2,600+3};

hist_vec[0]->SetLineColorAlpha(colors[1],0.45);
hist_vec[0]->Draw("HIST");
gPad->SetLogx();
gPad->RedrawAxis();


for(int i=1;i<hist_vec.size();i++)
	{
		
		if(step_pick[i-1]==7)
		{
			hist_vec[i]->SetLineColorAlpha(colors[0],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==8)
		{
			hist_vec[i]->SetLineColorAlpha(colors[1],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==9)
		{
			hist_vec[i]->SetLineColorAlpha(colors[2],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==10)
		{
			hist_vec[i]->SetLineColorAlpha(colors[3],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==11)
		{
			hist_vec[i]->SetLineColorAlpha(colors[4],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==12)
		{
			hist_vec[i]->SetLineColorAlpha(colors[5],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==13)
		{
			hist_vec[i]->SetLineColorAlpha(colors[6],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==14)
		{
			hist_vec[i]->SetLineColorAlpha(colors[7],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==15)
		{
			hist_vec[i]->SetLineColorAlpha(colors[8],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==16)
		{
			hist_vec[i]->SetLineColorAlpha(colors[9],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
hist_vec[70]->SetLineColor(kYellow);
hist_vec[70]->Draw("HIST SAME");
}

canvas_deconv_fluxes->Draw();
canvas_deconv_fluxes->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos.pdf").c_str());


}

void event_seed_picker_3(string campaign, int event, int steps, int timegrid, int ndet){

/**chi2<11**/

ostringstream stream_event, stream_ndet, stream_seed, stream_timegrid;
stream_timegrid << timegrid;
stream_event << event;
stream_ndet << ndet;
string str_stream_event = stream_event.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_timegrid = stream_timegrid.str();
	


vector<int> step_pick;
vector<vector<double>> matrix_chi2;

for(int i=1;i<=186;i++)
	{
		vector<double> vec_chi2;
		
		for(int k=1;k<=20;k++)
			{
				double intg_value=0.;
				double chi2_value=0.;
				

				ostringstream stream_steps;
				stream_steps << k;
				string str_stream_steps;
				str_stream_steps = stream_steps.str();
				string input_complete_file = "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

				ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

				auto df_chi2 = df_seed_loop_step.Take<double>("Chi2").GetValue();
				chi2_value = df_chi2[i-1];
				//~ cout << "chi2 "<< chi2_value << endl;
				vec_chi2.push_back(chi2_value);
			}
			matrix_chi2.push_back(vec_chi2);
			vector<double>().swap(vec_chi2); //liberamos el vector de la memoria
	}

for(int i=1;i<=186;i++)
	{

		int count_step;
		
		for(int j=0;j<matrix_chi2[i-1].size();j++)
			{
				 //~ cout << j << " " << matrix_chi2[i-1][j+1] << " " << diff_vec[j] << endl;
				if(matrix_chi2[i-1][j]<11.)
					{
								
								count_step = j+1;
								break;
					}

			}
			cout << "seed " << i << " step " << count_step << endl;
			step_pick.push_back(count_step);

}

vector<vector<double>> deconv_vec_matrix;
vector<double> vec_intg_total;

for(int i=1;i<=186;i++)
	{
		vector<double> deconv_vec;
		double intg_value;
		
		
		ostringstream stream_step_pick;
		stream_step_pick <<step_pick[i-1];
		string str_stream_step_pick = stream_step_pick.str();
		
		string input_complete_file= "./deconv_data_rootfile/EM/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

		ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

		auto df_flux_deconv_matrix = df_seed_loop_step.Take<vector<double>>("deconv_vec").GetValue();
		auto df_intg_total = df_seed_loop_step.Take<double>("Intg_total").GetValue();
		deconv_vec = df_flux_deconv_matrix[i-1];
		intg_value = df_intg_total[i-1];
		deconv_vec_matrix.push_back(deconv_vec);
		vec_intg_total.push_back(intg_value );
		vector<double>().swap(deconv_vec); //liberamos el vector de la memoria
	}



/**************Energy Bin********************/
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ cout <<"Generated root file from csv file" << endl;
/*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto seed_ref_cut_LCO = seed_rdf;
auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ cout << "seed_ref_cut_LCO vector size : " << d_cut_entries << endl;

/*Generamos el vector de flujo semilla*/
auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
//~ Seed = df_seed_flux_vec;
//~ cout << "Seed vector size: " << Seed.size() << endl;
/*Numero de bines*/
int binnum = df_seed_flux_vec.size()-1;
//~ binnum = 130;
//~ cout << "binnum: Seed.size()-1 : " << binnum << endl;
/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ B = df_binedges_vec;
//~ cout << "B: df_binedges_vec size " << B.size() << endl;
//~ /*Generamos el vector de ancho de energias*/
//~ auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
//~ dE = df_dE_vec;
//~ cout << "dE: df_dE_vec " << B.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;

double *bins = df_binedges_vec.data();
vector<TH1D*> hist_vec;

for(int i=0;i<deconv_vec_matrix.size();i++)
	{
		TH1D *hist_step = new TH1D(TString::Format("h0_%d", i+1),"Flujo de neutrones deconvolucionado, #chi^{2}<11", binnum, bins);
		
		for(int j=0;j<deconv_vec_matrix[i].size();j++)
			{
				hist_step->SetBinContent(j+1,deconv_vec_matrix[i][j]);
				
			}
			hist_vec.push_back(hist_step);
	}

TCanvas *canvas_deconv_fluxes = new TCanvas("deconv_fluxes","deconv_fluxes",1920,1080);
canvas_deconv_fluxes->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetOptStat(0);

hist_vec[0]->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
hist_vec[0]->GetXaxis()->SetTitleOffset(1.2);
hist_vec[0]->GetXaxis()->CenterTitle();
hist_vec[0]->GetXaxis()->SetTitleSize(0.04);
hist_vec[0]->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
hist_vec[0]->GetYaxis()->SetTitleOffset(1.4);
hist_vec[0]->GetYaxis()->CenterTitle();
hist_vec[0]->GetYaxis()->SetTitleSize(0.04);

//~ kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
//~ kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
//~ kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900

vector<int> colors = {800,632,900,616,880,600,860,432,840,416,820,400,600-4,600-7,600-9,600-10,600-9,600-6,600-2,600+3};

hist_vec[0]->SetLineColorAlpha(kOrange-9,0.45);
hist_vec[0]->Draw("HIST");
gPad->SetLogx();
gPad->RedrawAxis();


for(int i=1;i<hist_vec.size();i++)
	{
		if(step_pick[i-1]==4)
		{
			hist_vec[i]->SetLineColorAlpha(kOrange-9,0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==5)
		{
			hist_vec[i]->SetLineColorAlpha(kOrange+2,0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==6)
		{
			hist_vec[i]->SetLineColorAlpha(kOrange+8,0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		
		if(step_pick[i-1]==7)
		{
			hist_vec[i]->SetLineColorAlpha(colors[0],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==8)
		{
			hist_vec[i]->SetLineColorAlpha(colors[1],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==9)
		{
			hist_vec[i]->SetLineColorAlpha(colors[2],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==10)
		{
			hist_vec[i]->SetLineColorAlpha(colors[3],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==11)
		{
			hist_vec[i]->SetLineColorAlpha(colors[4],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==12)
		{
			hist_vec[i]->SetLineColorAlpha(colors[5],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==13)
		{
			hist_vec[i]->SetLineColorAlpha(colors[6],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==14)
		{
			hist_vec[i]->SetLineColorAlpha(colors[7],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==15)
		{
			hist_vec[i]->SetLineColorAlpha(colors[8],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
		if(step_pick[i-1]==16)
		{
			hist_vec[i]->SetLineColorAlpha(colors[9],0.45);
			hist_vec[i]->Draw("HIST SAME");
		}
hist_vec[70]->SetLineColor(kYellow);
hist_vec[70]->Draw("HIST SAME");
}

canvas_deconv_fluxes->Draw();
canvas_deconv_fluxes->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos.pdf").c_str());


}


/*Funcion que itera la funcion em_loop_seed() sobre el numero de pasos*/
void em_loop_steps(string campaign,int event,int steps,int time_grid, int ndet){


if(steps==0)
	{
		em_loop_seed(campaign,event,steps,time_grid);
	}

else
	{
		/*Iteramos sobre el numero de pasos*/
		for(int i=1; i<=steps; i++)
			{
				cout << "Number of steps: " << i << endl;
				em_loop_seed(campaign,event,i,time_grid);
			}
	}

}

/*Funcion que itera la funcion em_loop_steps() sobre el numero de eventos*/
//~ void em_loop_events(string campaign,int min_event, int max_event,int steps,int time_grid, int ndet){
void em_loop_events(string campaign,int steps,int time_grid, int ndet){

/*Iteramos sobre el numero de eventos*/
//~ for(int i=46; i<=53; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }
    
//~ for(int i=55; i<=192; i++)
//~ for(int i=111; i<=192; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }

//~ for(int i=194; i<=289; i++)
//~ for(int i=284; i<=289; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }

for(int i=194; i<=194; i++)
	{
		 cout << "Number of event: " << i << endl;
		 em_loop_steps(campaign,i,steps,time_grid,ndet);
    }

/*************************/

//~ for(int i=21; i<=21; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }


}

void em_routine(string campaign){
/*Generamos los archivos .root*/
em_loop_steps(campaign,210,20,15,11); //lluvia
/*Graficamos Chi2 e integrales dado cierta cantidad de pasos*/
//~ em_loop_seed_plot_template(240,100,15,11);
/*Graficamos los histogramas de los flujos deconvolucionados por cantidad de pasos para la misma semilla dada*/
//~ deconv_flux_multiplot_by_seed(240,100,15,11,1);
}

void em_routine_plot(string campaign, int event, int max_steps, int max_bin_seed){

/*Iteramos sobre el numero de semillas*/
for(int i=1; i<=max_bin_seed; i++)
	{
		cout << "Number of bin seed: " << i << endl;
		//~ deconv_flux_multiplot_by_seed(210,max_steps,15,11,i,"Lethargy");
		deconv_flux_multiplot_by_seed(campaign,event,max_steps,15,11,i,"Lethargy");
    }
}

void root_test_multithread(){

// RDataFrame guarantees that different threads will invoke the expression with different slot numbers - slot numbers will range from zero to ROOT::GetThreadPoolSize()-1.
//~ ROOT::EnableImplicitMT(); // Enable Multiple threads in RDataFrame
// To see how many threads are available to your program:
auto poolSize = ROOT::GetThreadPoolSize(); // numero de nucleos del pc
std::cout << "Pool size = " << poolSize << std::endl; 

}

int main(){

//15min
deconv_em("LCO",240,9,8,15,"Intg",0);


return 0;
}

