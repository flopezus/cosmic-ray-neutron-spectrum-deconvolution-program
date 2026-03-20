#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <iterator> // for std::begin, std::end (C++11 and above)
#include <sstream>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TDecompSVD.h> // Necesario para la descomposición SVD



using namespace std;
using namespace ROOT::VecOps; // para definir vectores como  RVec<double>>("vecCol");
namespace fs = std::filesystem;

const std::array<int,16>& Detectors_Array(const std::string& campaign)
{
    static const std::array<int,16> array_lco = {1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};
	static const std::array<int,16> array_chapiquilta = {1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1};
    static const std::array<int,16> array_all = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    if (campaign=="PUC" || campaign=="UTFSM" || campaign=="LCO" || campaign == "Maricunga" || campaign == "RetenDesierto" || campaign == "UDA" || campaign == "ULS"|| campaign == "JuanSoldado"){
        return array_lco;
	}

    else if (campaign == "Chapiquilta" || campaign == "SanPedro") {
        return array_chapiquilta;
    }
    else if (campaign == "AllActive") {
        return array_all;
    }

    throw std::runtime_error("Unknown campaign: " + campaign);
}

void Response_function_matrix_lin_spec_2023_plot(){


		TFile *E01_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		TFile *E02_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		TFile *E03_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_3_4cmHDPE_VV.root");
		TFile *E04_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		TFile *E05_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root");
		TFile *E06_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		TFile *E07_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		TFile *E08_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_8_1inchBHDPE_10cmHDPE_VV.root");
		TFile *E09_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_9_20cmBHDPE_1.0inch_VV.root");
		TFile *E10_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		TFile *E11_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		TFile *E12_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_12_Pb_10cmBHDPEcore_VV.root");
		TFile *E13_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_13_1inchBHDPE_15cmGraphite_VV.root");
		TFile *E14_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_14_inchBHDPE_15cmHDPE_VV.root");
		TFile *E15_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		TFile *E16_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_16_Naked_1inch_VV.root");
		
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


//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1 = new TCanvas();
		c1->SetLogx();
		c1->SetLogy();

		h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);

		h_d01->SetTitle("Response Function Spectrometer CEFNEN 2023");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME");
		h_d07->Draw("HIST SAME");
		h_d08->Draw("HIST SAME");
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME");
		h_d15->Draw("HIST SAME");
		h_d16->Draw("HIST SAME");

		auto legend = new TLegend(0.744,0.785,0.948,0.949);
	   legend->SetHeader("Response Functions","C"); // option "C" allows to center the header
	   legend->AddEntry(h_d01,"E1_12cmHDPE","l");
	   legend->AddEntry(h_d02,"E2_10cmHDPE","l");
	   legend->AddEntry(h_d03,"E3_4cmHDPE","l");
	   legend->AddEntry(h_d04,"E4_CylinderHDPE","l");
	   legend->AddEntry(h_d05,"E5_Cylinder7mmAl_1.8cmBHDPECore","l");
	   legend->AddEntry(h_d06,"E6_18cmHDPE","l");
	   legend->AddEntry(h_d07,"E7_20cmHDPE","l");
	   legend->AddEntry(h_d08,"E8_1inchBHDPE_10cmHDPE","l");
	   legend->AddEntry(h_d09,"E9_20cmBHDPE_1.0inch","l");
	   legend->AddEntry(h_d10,"E10_Cylinder_4cm","l");
	   legend->AddEntry(h_d11,"E11_Cylinder_3cm","l");
	   legend->AddEntry(h_d12,"E12_Pb_10cmBHDPEcore","l");
	   legend->AddEntry(h_d13,"E13_1inchBHDPE_15cmGraphite","l");
	   legend->AddEntry(h_d14,"E14_inchBHDPE_15cmHDPE","l");
	   legend->AddEntry(h_d15,"E15_24cmHDPE","l");
	   legend->AddEntry(h_d16,"E16_Naked_1inch","l");
	   
	   legend->Draw();
	

}

void Response_function_matrix_lin_spec_2024_plot(){


		TFile *E01_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		TFile *E02_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		TFile *E03_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		TFile *E04_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		TFile *E05_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		TFile *E06_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		TFile *E07_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		TFile *E08_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		TFile *E09_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		TFile *E10_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		TFile *E11_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		TFile *E12_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		TFile *E13_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		TFile *E14_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		TFile *E15_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		TFile *E16_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");
		
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
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");


//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1_new = new TCanvas();
		c1_new->SetLogx();
		c1_new->SetLogy();

		h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);

		h_d01->SetTitle("Response Function Spectrometer CEFNEN 2024");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME");
		h_d07->Draw("HIST SAME");
		h_d08->Draw("HIST SAME");
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME");
		h_d15->Draw("HIST SAME");
		h_d16->Draw("HIST SAME");

		auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
	   legend_new->SetHeader("Response Functions","C"); // option "C" allows to center the header
	   legend_new->AddEntry(h_d01,"E1_12cmHDPE","l");
	   legend_new->AddEntry(h_d02,"E2_10cmHDPE","l");
	   legend_new->AddEntry(h_d03,"E3_4cmHDPE_NEW","l");
	   legend_new->AddEntry(h_d04,"E4_CylinderHDPE","l");
	   legend_new->AddEntry(h_d05,"E5_Cylinder7mmAl_1.8cmBHDPECore_NEW","l");
	   legend_new->AddEntry(h_d06,"E6_18cmHDPE","l");
	   legend_new->AddEntry(h_d07,"E7_20cmHDPE","l");
	   legend_new->AddEntry(h_d08,"E8_1inchBHDPE_10cmHDPE_NEW","l");
	   legend_new->AddEntry(h_d09,"E9_20cmBHDPE_1.0inch_NEW","l");
	   legend_new->AddEntry(h_d10,"E10_Cylinder_4cm","l");
	   legend_new->AddEntry(h_d11,"E11_Cylinder_3cm","l");
	   legend_new->AddEntry(h_d12,"E12_Pb_10cmBHDPEcore_NEW","l");
	   legend_new->AddEntry(h_d13,"E13_1inchBHDPE_15cmGraphite_NEW","l");
	   legend_new->AddEntry(h_d14,"E14_inchBHDPE_15cmHDPE_NEW","l");
	   legend_new->AddEntry(h_d15,"E15_24cmHDPE","l");
	   legend_new->AddEntry(h_d16,"E16_Naked_1inch_NEW","l");
	   
	   legend_new->Draw();
	

}


vector<vector<double_t> > Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(){
	
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

TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV.root");
TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV.root");
TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV.root");
//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV.root");
TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV.root");
TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV.root");
TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV.root");
TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV.root");
TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV.root");
TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV.root");

TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW");
TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW");
TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE");
TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW");
TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW");
TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW");
TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW");
TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW");
TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");



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

	vector<vector<double_t> > Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth(){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

//~ string scale_factor = "/RF_wo_aquarter_factor/"; //con el factor 1/4
string scale_factor = "/"; //sin el factor 1/4

TFile *E01_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_1_12cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E02_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_2_10cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E03_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_3_4cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());

//~ TFile *E04_file = new TFile(("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_4_CylinderHDPE_NEW_VV.root").c_str()); //2023
//~ TFile *E04_file = new TFile(("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_4_CylinderHDPE_NEW_VV_smooth_smooth_root_15.root").c_str()); //2023

TFile *E04_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root").c_str());
TFile *E05_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E06_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_6_18cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E07_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_7_20cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E08_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E09_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E10_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_10_Cylinder_4cm_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E11_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_11_Cylinder_3cm_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E12_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E13_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E14_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E15_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_15_24cmHDPE_NEW_VV_smooth_smooth_root_15.root").c_str());
TFile *E16_file = new TFile(("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_16_Naked_1inch_NEW_VV_smooth_smooth_root_15.root").c_str());
//~ TFile *E17_file = new TFile(("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix"+scale_factor+"Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root").c_str());


TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth_smooth_root_15");

//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW"); //2023
//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW_smooth_smooth_root_15"); //2023

TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15");
TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15");
TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15");
TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth_smooth_root_15");
TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth_smooth_root_15");
TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth_smooth_root_15");
TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth_smooth_root_15");
TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth_smooth_root_15");
TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth_smooth_root_15");
//~ TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");




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

TFile *E01_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
TFile *E02_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
TFile *E03_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_3_4cmHDPE_VV.root");
TFile *E04_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
TFile *E05_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root");
TFile *E06_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
TFile *E07_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
TFile *E08_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_8_1inchBHDPE_10cmHDPE_VV.root");
TFile *E09_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_9_20cmBHDPE_1.0inch_VV.root");
TFile *E10_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
TFile *E11_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
TFile *E12_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_12_Pb_10cmBHDPEcore_VV.root");
TFile *E13_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_13_1inchBHDPE_15cmGraphite_VV.root");
TFile *E14_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_14_inchBHDPE_15cmHDPE_VV.root");
TFile *E15_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
TFile *E16_file = TFile::Open("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_16_Naked_1inch_VV.root");

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

/**Matriz de funciones respuesta para los experimentos de 2023 (LCO, MAR, etc) y posteriores (cambio det #4 por #17) donde se permite seleccionar la libreria
fisica usada en geant4, ya sea la QGSP_BERT o la FTFP_BERT, ademas del factor de escalimamiento de 1/4**/

vector<vector<double_t> > Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth(string physic_list, string scale_factor, string neufield_type, string campaign){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

string path;
string phylst_name;
string scale_path;

//Solo acepta "ws" o "wos"
if (scale_factor == "ws" || scale_factor == "wos") {
     scale_path = scale_factor + "_factor";
	 std::cout << "scale_factor " << scale_factor << "\n";
 } else {
   std::cout << "scale_factor inexistente o incorrecto: " << scale_factor << "\n";
}


if(physic_list=="QGSP_BERT")
	{ path = "../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/"+scale_path;
	  phylst_name = "NEW";
	  cout << physic_list+" Physic_list" << endl;}	
else if(physic_list=="FTFP_BERT")
	{path ="../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/"+scale_path;
	 phylst_name = "FTFP_BERT";
	 cout << physic_list+" Physic_list" << endl;}
else{cout << "Physics list inexistente o incorrecta" << endl;}

//Cambio de detector #4 de Efi_4_CylinderHDPE (PUC, UTFSM, LCO, Maricunga, RetenDesierto, UDA, ULS, JuanSoldado) a Efi_7_20cmHDPE (desde Campania sur Nov 2023 en adelante)
string det_change;

if(campaign=="PUC" || campaign=="UTFSM" || campaign=="LCO" || campaign == "Maricunga" || campaign == "RetenDesierto" || campaign == "UDA" || campaign == "ULS"|| campaign == "JuanSoldado"){
	det_change = (path+"/Efi_4_CylinderHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root");
}
else{det_change = ("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/"+scale_path+"/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");}

//~ TFile *E01_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E02_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E03_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E05_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E06_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E07_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E08_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E09_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E10_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E11_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E12_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E13_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E14_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E15_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV_smooth_smooth_root_15.root");
//~ TFile *E16_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV_smooth_smooth_root_15.root");
// TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");

TFile *E01_file = new TFile((path+"/Efi_1_12cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E02_file = new TFile((path+"/Efi_2_10cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E03_file = new TFile((path+"/Efi_3_4cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());

//TFile *E04_file = new TFile((path+"/Efi_4_CylinderHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E04_file = new TFile(det_change.c_str());

TFile *E05_file = new TFile((path+"/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E06_file = new TFile((path+"/Efi_6_18cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E07_file = new TFile((path+"/Efi_7_20cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E08_file = new TFile((path+"/Efi_8_1inchBHDPE_10cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E09_file = new TFile((path+"/Efi_9_20cmBHDPE_1.0inch_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E10_file = new TFile((path+"/Efi_10_Cylinder_4cm_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E11_file = new TFile((path+"/Efi_11_Cylinder_3cm_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());

TFile *E12_file = new TFile((path+"/Efi_12_Pb_10cmBHDPEcore_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
//~ TFile *E12_file = new TFile(("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/wos_factor/Efi_12_Pb_10cmBHDPEcore_"+phylst_name+"_VV_smooth_smooth_root_15_wos.root").c_str());

TFile *E13_file = new TFile((path+"/Efi_13_1inchBHDPE_15cmGraphite_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E14_file = new TFile((path+"/Efi_14_inchBHDPE_15cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E15_file = new TFile((path+"/Efi_15_24cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E16_file = new TFile((path+"/Efi_16_Naked_1inch_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
// TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15_"+scale_factor+".root");


//~ TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth_smooth_root_15");
//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15");
//~ TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15");
//~ TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15");
//~ TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth_smooth_root_15");
//~ TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth_smooth_root_15");
//~ TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth_smooth_root_15");
//~ TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth_smooth_root_15");
//~ TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth_smooth_root_15");
//~ TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth_smooth_root_15");
//~ TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");

TH1D *h_d01 = (TH1D*)E01_file->Get((string("E1_12cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d02 = (TH1D*)E02_file->Get((string("E2_10cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

// TH1D *h_d03 = (TH1D*)E03_file->Get((string("E3_4cmHDPE_smooth_smooth_root_15").c_str());
TH1D *h_d03 = (TH1D*)E03_file->Get((string("E3_4cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

TH1D *h_d04 = (TH1D*)E04_file->Get((string("E4_CylinderHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

// TH1D *h_d05 = (TH1D*)E05_file->Get((string("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15").c_str());
TH1D *h_d05 = (TH1D*)E05_file->Get((string("E5_Cylinder7mmAl_1.8cmBHDPECore_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

TH1D *h_d06 = (TH1D*)E06_file->Get((string("E6_18cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d07 = (TH1D*)E07_file->Get((string("E7_20cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

// TH1D *h_d08 = (TH1D*)E08_file->Get((string("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15").c_str());
// TH1D *h_d09 = (TH1D*)E09_file->Get((string("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15").c_str());

TH1D *h_d08 = (TH1D*)E08_file->Get((string("E8_1inchBHDPE_10cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d09 = (TH1D*)E09_file->Get((string("E9_20cmBHDPE_1.0inch_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

TH1D *h_d10 = (TH1D*)E10_file->Get((string("E10_Cylinder_4cm_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d11 = (TH1D*)E11_file->Get((string("E11_Cylinder_3cm_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

TH1D *h_d12 = (TH1D*)E12_file->Get((string("E12_Pb_10cmBHDPEcore_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());

TH1D *h_d13 = (TH1D*)E13_file->Get((string("E13_1inchBHDPE_15cmGraphite_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d14 = (TH1D*)E14_file->Get((string("E14_inchBHDPE_15cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d15 = (TH1D*)E15_file->Get((string("E15_24cmHDPE_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
TH1D *h_d16 = (TH1D*)E16_file->Get((string("E16_Naked_1inch_")+phylst_name+"_smooth_smooth_root_15"+"_"+scale_factor).c_str());
// TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");




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


constexpr int NDET = 16;

// factores "beam full" por detector (1..16) en orden
const std::array<double, NDET> sf_beam = {
    1.38, 1.37, 1.28, 1.42,
    1.37, 1.37, 1.36, 2.33,
    1.29, 1.43, 1.41, 5.00,
    1.80, 1.96, 1.30, 1.15
};


std::array<double, NDET> sf_arr; 
sf_arr.fill(1.0); // ISO por defecto

if (neufield_type == "BEAM") {
    sf_arr = sf_beam;
	cout<<"Neutron Field BEAM TYPE"<<endl;
}
else if (neufield_type == "MIX") {
    // solo aplicar r_beam (los demás quedan en 1.0)
    // Det05,06,07,08,09,12,13,14,15  => índices 4,5,6,7,8,11,12,13,14
    for (int idx : {4,5,6,7,8,11,12,13,14}) {
        sf_arr[idx] = sf_beam[idx];
    }
	cout<<"Neutron Field MIX TYPE"<<endl;
}

else if (neufield_type == "ISO") {
    cout << "Neutron Field ISOTROPIC TYPE" << endl;
}
else {
    cout << "Unknown Neutron Field TYPE" << endl;
}

// si realmente necesitas std::vector<double>
vector<double> sf(sf_arr.begin(), sf_arr.end());

for(int i =0; i<binning; i++)
{
	 if(h_d01->GetBinContent(i+1)!=0.0)
		{
			 RF_d01_vec.push_back((h_d01->GetBinContent(i+1))*sf[0]);
			 //~ //cout << i << "  " << h_d01->GetBinContent(i+1) << endl;
			 RF_d02_vec.push_back((h_d02->GetBinContent(i+1))*sf[1]);
			 RF_d03_vec.push_back((h_d03->GetBinContent(i+1))*sf[2]);
			 RF_d04_vec.push_back((h_d04->GetBinContent(i+1))*sf[3]);			 
			 RF_d05_vec.push_back((h_d05->GetBinContent(i+1))*sf[4]);
			 RF_d06_vec.push_back((h_d06->GetBinContent(i+1))*sf[5]);			 
			 RF_d07_vec.push_back((h_d07->GetBinContent(i+1))*sf[6]);
			 RF_d08_vec.push_back((h_d08->GetBinContent(i+1))*sf[7]);
			 RF_d09_vec.push_back((h_d09->GetBinContent(i+1))*sf[8]);
			 RF_d10_vec.push_back((h_d10->GetBinContent(i+1))*sf[9]);
			 RF_d11_vec.push_back((h_d11->GetBinContent(i+1))*sf[10]);

			 //~ RF_d12_vec.push_back((h_d12->GetBinContent(i+1))*(5./4.));
			 RF_d12_vec.push_back((h_d12->GetBinContent(i+1))*sf[11]);

			 RF_d13_vec.push_back((h_d13->GetBinContent(i+1))*sf[12]);
			 RF_d14_vec.push_back((h_d14->GetBinContent(i+1))*sf[13]);
			 RF_d15_vec.push_back((h_d15->GetBinContent(i+1))*sf[14]);
			 RF_d16_vec.push_back((h_d16->GetBinContent(i+1))*sf[15]);
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



void Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth_root_plot(){

		//~ TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		//~ TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		//~ TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		//~ TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		//~ TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		//~ TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		//~ TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		//~ TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		//~ TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		//~ TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		//~ TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		//~ TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		//~ TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		//~ TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		//~ TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		//~ TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth_smooth_root_15.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth_smooth_root_15.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV_smooth_smooth_root_15.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV_smooth_smooth_root_15.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth_smooth_root_15.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth_smooth_root_15.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");


		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth_smooth_root_15");

		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW_smooth_smooth_root_15");

		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth_smooth_root_15");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth_smooth_root_15");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth_smooth_root_15");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth_smooth_root_15");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		

//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

		
		c1_new->SetLogx();
		c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);
		//~ h_d17->SetLineColor(kBlue);


		h_d01->SetLineWidth(3);
		h_d02->SetLineWidth(3);
		h_d03->SetLineWidth(3);
		h_d04->SetLineWidth(3);
		h_d05->SetLineWidth(3);
		h_d06->SetLineWidth(3);
		h_d07->SetLineWidth(3);
		h_d08->SetLineWidth(3);
		h_d09->SetLineWidth(3);
		h_d10->SetLineWidth(3);
		h_d11->SetLineWidth(3);
		h_d12->SetLineWidth(3);
		h_d13->SetLineWidth(3);
		h_d14->SetLineWidth(3);
		h_d15->SetLineWidth(3);
		h_d16->SetLineWidth(3);
		//~ h_d17->SetLineWidth(3);

		
		//~ h_d01->SetTitle("#bf{Response Functions Spectrometer CEFNEN 2024 Smooth ROOT}");
		h_d01->SetTitle("#bf{Smooth Response Functions for the CEFNEN 2023 Spectrometer}");

		h_d01->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d01->GetXaxis()->SetTitle("#bf{Energy (MeV)}");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME"); // no se considera en calculos
		h_d07->Draw("HIST SAME"); // no se considera en calculos
		h_d08->Draw("HIST SAME"); // no se considera en calculos
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME"); // no se considera en calculos
		h_d15->Draw("HIST SAME"); // no se considera en calculos
		h_d16->Draw("HIST SAME");
		//~ h_d17->Draw("HIST SAME");

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		auto legend_new = new TLegend(0.80303,0.100098,0.998918,0.917566);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Response Functions Smooth}","C"); // option "C" allows to center the header
	   legend_new->SetTextSize(0.018);
	   legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");
	   legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE}","l");
	   legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE_smooth}","l");
	   legend_new->AddEntry(h_d05,"#bf{E_5_7mmAlCylinder_6.6cmBHDPECore_smooth}","l");
	   legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch_smooth}","l");
	   legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm_smooth}","l");
	   legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm_smooth}","l");
	   legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore_smooth}","l");
	   legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite_smooth}","l");
	   legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch_smooth}","l");
	 
	   
	   legend_new->Draw();
	   //~ c1_new->Update();
	   c1_new->Draw();
		
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2023_fix_smooth_SG_smooth_root.svg");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2023_fix_smooth_SG_smooth_root.png");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2023_fix_smooth_SG_smooth_root.pdf");
	
	

}


void Response_function_matrix_lin_spec_2024_fix_active_volume_plot(){

		//~ TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		//~ TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		//~ TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		//~ TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		//~ TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		//~ TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		//~ TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		//~ TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		//~ TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		//~ TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		//~ TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		//~ TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		//~ TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		//~ TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		//~ TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		//~ TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV.root");
		TFile *E17_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV.root");

		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");
		TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE");

		
		//~ TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE");
		//~ TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE");
		//~ TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
		//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE");
		//~ TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
		//~ TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE");
		//~ TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE");
		//~ TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
		//~ TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
		//~ TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm");
		//~ TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm");
		//~ TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		//~ TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		//~ TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		//~ TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
		//~ TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");


//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

		c1_new->SetLogx();
		c1_new->SetLogy();
		h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);
		h_d17->SetLineColor(kBlue);



		vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1};; //detectores activados en deconv_em_ouput
		// vector<int> act_vector(vec_test.size(),1);
		vector<int> vec_pos;
		
		/*Redefinimos la activacion*/
		for(int i=0; i<vec_test.size(); i++)
			{
				if(vec_test[i]==1)
					{
						vec_pos.push_back(i+1);
					}
				else{}
				
			}

		h_d01->SetTitle("#bf{Response Function Spectrometer	 CEFNEN 2024}");

		h_d01->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d01->GetXaxis()->SetTitle("#bf{Energy (MeV)}");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME"); // no se considera en calculos
		h_d07->Draw("HIST SAME"); // no se considera en calculos
		h_d08->Draw("HIST SAME"); // no se considera en calculos
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME"); // no se considera en calculos
		h_d15->Draw("HIST SAME"); // no se considera en calculos
		h_d16->Draw("HIST SAME");
		h_d17->Draw("HIST SAME");

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		auto legend_new = new TLegend(0.80303,0.100098,0.998918,0.917566);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Response Functions}","C"); // option "C" allows to center the header
	   legend_new->SetTextSize(0.018);
	   legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE}","l");
	   legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE}","l");
	   legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE}","l");
	   legend_new->AddEntry(h_d05,"#bf{E_5_7mmAlCylinder_6.6cmBHDPECore}","l");
	   legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE}","l");
	   legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE}","l");
	   legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE}","l");
	   legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch}","l");
	   legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm}","l");
	   legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm}","l");
	   legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore}","l");
	   legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite}","l");
	   legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE}","l");
	   legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE}","l");
	   legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch}","l");
	   legend_new->AddEntry(h_d17,"#bf{E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE}","l");
	   
	   legend_new->Draw();
	   //~ c1_new->Update();
	   c1_new->Draw();
		
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spectrometer_CEFNEN_2024_raw_sim_log.pdf");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spectrometer_CEFNEN_2024_raw_sim_log.svg");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spectrometer_CEFNEN_2024_raw_sim_log.png");
	   c1_new->SaveAs("RF_Spectrometer_CEFNEN_2024_raw_sim_log.eps");
	
	

}

/*1er smooth Savitzky_Golay (SG)*/
void Response_function_matrix_lin_spec_2024_fix_active_volume_smooth_plot(){

		//~ TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		//~ TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		//~ TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		//~ TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		//~ TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		//~ TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		//~ TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		//~ TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		//~ TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		//~ TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		//~ TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		//~ TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		//~ TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		//~ TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		//~ TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		//~ TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV_smooth.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV_smooth.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV_smooth.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV_smooth.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV_smooth.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV_smooth.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV_smooth.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV_smooth.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV_smooth.root");
		TFile *E17_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth.root");


		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW_smooth");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth");
		TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth");
		

//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

		c1_new->SetLogx();
		c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);
		h_d17->SetLineColor(kBlue);


		h_d01->SetLineWidth(3);
		h_d02->SetLineWidth(3);
		h_d03->SetLineWidth(3);
		h_d04->SetLineWidth(3);
		h_d05->SetLineWidth(3);
		h_d06->SetLineWidth(3);
		h_d07->SetLineWidth(3);
		h_d08->SetLineWidth(3);
		h_d09->SetLineWidth(3);
		h_d10->SetLineWidth(3);
		h_d11->SetLineWidth(3);
		h_d12->SetLineWidth(3);
		h_d13->SetLineWidth(3);
		h_d14->SetLineWidth(3);
		h_d15->SetLineWidth(3);
		h_d16->SetLineWidth(3);
		h_d17->SetLineWidth(3);

		
		h_d01->SetTitle("#bf{Response Function Spectrometer CEFNEN 2024 Smoothing}");

		h_d01->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d01->GetXaxis()->SetTitle("#bf{Energy (MeV)}");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME"); // no se considera en calculos
		h_d07->Draw("HIST SAME"); // no se considera en calculos
		h_d08->Draw("HIST SAME"); // no se considera en calculos
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME"); // no se considera en calculos
		h_d15->Draw("HIST SAME"); // no se considera en calculos
		h_d16->Draw("HIST SAME");
		h_d17->Draw("HIST SAME");

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		auto legend_new = new TLegend(0.80303,0.100098,0.998918,0.917566);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Response Functions Smooth}","C"); // option "C" allows to center the header
	   legend_new->SetTextSize(0.018);
	   legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");
	   legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE}","l");
	   legend_new->AddEntry(h_d05,"#bf{E_5_7mmAlCylinder_6.6cmBHDPECore_smooth}","l");
	   legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch_smooth}","l");
	   legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm_smooth}","l");
	   legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm_smooth}","l");
	   legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore_smooth}","l");
	   legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite_smooth}","l");
	   legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch_smooth}","l");
	   legend_new->AddEntry(h_d17,"#bf{E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth}","l");
	   
	   legend_new->Draw();
	   //~ c1_new->Update();
	   c1_new->Draw();
		
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2024_fix_smooth_SG.svg");
	
	

}

/*2do smooth, root smooth*/
void Response_function_matrix_lin_spec_2024_fix_active_volume_smooth_root_plot(){

		//~ TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		//~ TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		//~ TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		//~ TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		//~ TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		//~ TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		//~ TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		//~ TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		//~ TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		//~ TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		//~ TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		//~ TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		//~ TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		//~ TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		//~ TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		//~ TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth_smooth_root_15.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth_smooth_root_15.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV_smooth_smooth_root_15.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV_smooth_smooth_root_15.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth_smooth_root_15.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth_smooth_root_15.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");


		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth_smooth_root_15");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth_smooth_root_15");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth_smooth_root_15");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth_smooth_root_15");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth_smooth_root_15");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth_smooth_root_15");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		

//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

		
		c1_new->SetLogx();
		c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);
		//~ h_d17->SetLineColor(kBlue);


		h_d01->SetLineWidth(3);
		h_d02->SetLineWidth(3);
		h_d03->SetLineWidth(3);
		h_d04->SetLineWidth(3);
		h_d05->SetLineWidth(3);
		h_d06->SetLineWidth(3);
		h_d07->SetLineWidth(3);
		h_d08->SetLineWidth(3);
		h_d09->SetLineWidth(3);
		h_d10->SetLineWidth(3);
		h_d11->SetLineWidth(3);
		h_d12->SetLineWidth(3);
		h_d13->SetLineWidth(3);
		h_d14->SetLineWidth(3);
		h_d15->SetLineWidth(3);
		h_d16->SetLineWidth(3);
		//~ h_d17->SetLineWidth(3);

		
		//~ h_d01->SetTitle("#bf{Response Functions Spectrometer CEFNEN 2024 Smooth ROOT}");
		h_d01->SetTitle("#bf{Smooth Response Functions for the CEFNEN 2024 Spectrometer}");

		h_d01->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d01->GetXaxis()->SetTitle("#bf{Energy (MeV)}");

		h_d01->Draw("HIST");
		h_d02->Draw("HIST SAME");
		h_d03->Draw("HIST SAME");
		h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		h_d06->Draw("HIST SAME"); // no se considera en calculos
		h_d07->Draw("HIST SAME"); // no se considera en calculos
		h_d08->Draw("HIST SAME"); // no se considera en calculos
		h_d09->Draw("HIST SAME");
		h_d10->Draw("HIST SAME");
		h_d11->Draw("HIST SAME");
		h_d12->Draw("HIST SAME");
		h_d13->Draw("HIST SAME");
		h_d14->Draw("HIST SAME"); // no se considera en calculos
		h_d15->Draw("HIST SAME"); // no se considera en calculos
		h_d16->Draw("HIST SAME");
		//~ h_d17->Draw("HIST SAME");

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		auto legend_new = new TLegend(0.80303,0.100098,0.998918,0.917566);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Response Functions Smooth}","C"); // option "C" allows to center the header
	   legend_new->SetTextSize(0.018);
	   legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");
	   legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE}","l");
	   legend_new->AddEntry(h_d04,"#bf{E4_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth}","l");
	   legend_new->AddEntry(h_d05,"#bf{E_5_7mmAlCylinder_6.6cmBHDPECore_smooth}","l");
	   legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch_smooth}","l");
	   legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm_smooth}","l");
	   legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm_smooth}","l");
	   legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore_smooth}","l");
	   legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite_smooth}","l");
	   legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE_smooth}","l");
	   legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch_smooth}","l");
	 
	   
	   legend_new->Draw();
	   //~ c1_new->Update();
	   c1_new->Draw();
		
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2024_fix_smooth_SG_smooth_root.svg");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2024_fix_smooth_SG_smooth_root.png");
	   c1_new->SaveAs("../outputs/pdf/deconv_data_pdf/RF_img/RF_Spec_CEFNEN_2024_fix_smooth_SG_smooth_root.pdf");
	
	

}


void Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_and_percperregion_plot(){

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
		//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV.root");

		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
		//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");

		/*Valores de integrales y porcentaje de ellas por region de energia c/r a la integral total*/

		/*Integrales totales*/
		double integral_total_E02 = h_d02->Integral(h_d02->FindBin(0),h_d02->FindBin(1e+03));
		double integral_total_E05 = h_d05->Integral(h_d05->FindBin(0),h_d05->FindBin(1e+03));
		double integral_total_E16 = h_d16->Integral(h_d16->FindBin(0),h_d16->FindBin(1e+03));


		/*Integrales por region de energia*/

		/*thernal*/
		double integral_E02_th =  h_d02->Integral( h_d02->FindBin(0), h_d02->FindBin(1.9*1e-07)); 
		double integral_E05_th =  h_d05->Integral( h_d05->FindBin(0), h_d05->FindBin(1.9*1e-07));
		double integral_E16_th =  h_d16->Integral( h_d16->FindBin(0), h_d16->FindBin(1.9*1e-07));

		/*epi*/
		double integral_E02_epi =  h_d02->Integral(h_d02->FindBin(2.2*1e-07), h_d02->FindBin(0.9*1e-02));
		double integral_E05_epi =  h_d05->Integral(h_d05->FindBin(2.2*1e-07), h_d05->FindBin(0.9*1e-02));
		double integral_E16_epi =  h_d16->Integral(h_d16->FindBin(2.2*1e-07), h_d16->FindBin(0.9*1e-02));

		/*Fast*/
		double integral_E02_fs =  h_d02->Integral(h_d02->FindBin(1.1*1e-02), h_d02->FindBin(0.89*1e+01));
		double integral_E05_fs =  h_d05->Integral(h_d05->FindBin(1.1*1e-02), h_d05->FindBin(0.89*1e+01));
		double integral_E16_fs =  h_d16->Integral(h_d16->FindBin(1.1*1e-02), h_d16->FindBin(0.89*1e+01));

		/*High-energy*/
		double integral_E02_he =  h_d02->Integral(h_d02->FindBin(1.05*1e+01),h_d02->FindBin(1e+03));
		double integral_E05_he =  h_d05->Integral(h_d05->FindBin(1.05*1e+01),h_d05->FindBin(1e+03));
		double integral_E16_he =  h_d16->Integral(h_d16->FindBin(1.05*1e+01),h_d16->FindBin(1e+03));


		/*Porcentajes de la inetgral por region c/r a la itegral total*/
		double perc_E02_th = integral_E02_th*100./integral_total_E02;
		double perc_E05_th = integral_E05_th*100./integral_total_E05;
		double perc_E16_th = integral_E16_th*100./integral_total_E16;

		double perc_E02_epi = integral_E02_epi*100./integral_total_E02;
		double perc_E05_epi = integral_E05_epi*100./integral_total_E05;
		double perc_E16_epi = integral_E16_epi*100./integral_total_E16;

		double perc_E02_fs = integral_E02_fs*100./integral_total_E02;
		double perc_E05_fs = integral_E05_fs*100./integral_total_E05;
		double perc_E16_fs = integral_E16_fs*100./integral_total_E16;

		double perc_E02_he = integral_E02_he*100./integral_total_E02;
		double perc_E05_he = integral_E05_he*100./integral_total_E05;
		double perc_E16_he = integral_E16_he*100./integral_total_E16;

		cout << "Integral total RF" << endl;
		cout << "RF 02 " << scientific << setprecision(2)<< integral_total_E02 << endl;
		cout << "RF 05 " << scientific << setprecision(2)<< integral_total_E05 << endl;
		cout << "RF 16 " << scientific << setprecision(2)<< integral_total_E16 << endl;

		cout << "Integral RF thermal region " << endl;
		cout << "RF 02 " << scientific << setprecision(2)<< integral_E02_th << " Perc c/r TOT " << fixed << perc_E02_th << " %"<< endl;
		cout << "RF 05 " << scientific << setprecision(3)<< integral_E05_th << " Perc c/r TOT " << fixed << perc_E05_th << " %"<< endl;
		cout << "RF 16 " << scientific << setprecision(2)<< integral_E16_th << " Perc c/r TOT " << fixed << perc_E16_th << " %"<< endl;
																				
		cout << "Integral RF epithermal region " << endl;                        
		cout << "RF 02 " << scientific << setprecision(2)<< integral_E02_epi << "Perc c/r TOT " << fixed << perc_E02_epi <<" %"<< endl;
		cout << "RF 05 " << scientific << setprecision(2)<< integral_E05_epi << "Perc c/r TOT " << fixed << perc_E05_epi <<" %"<< endl;
		cout << "RF 16 " << scientific << setprecision(2)<< integral_E16_epi << "Perc c/r TOT " << fixed << perc_E16_epi <<" %"<< endl;
																				 
		cout << "Integral RF fast region " << endl;                              
		cout << "RF 02 " << scientific << setprecision(2)<< integral_E02_fs << " Perc c/r TOT " << fixed << perc_E02_fs << " %"<< endl;
		cout << "RF 05 " << scientific << setprecision(2)<< integral_E05_fs << " Perc c/r TOT " << fixed << perc_E05_fs << " %"<< endl;
		cout << "RF 16 " << scientific << setprecision(2)<< integral_E16_fs << " Perc c/r TOT " << fixed << perc_E16_fs << " %"<< endl;
																				
		cout << "Integral RF high energy region " << endl;                       
		cout << "RF 02 " << scientific << setprecision(2)<< integral_E02_he << " Perc c/r TOT " << fixed << perc_E02_he <<" %"<< endl;
		cout << "RF 05 " << scientific << setprecision(2)<< integral_E05_he << " Perc c/r TOT " << fixed << perc_E05_he <<" %"<< endl;
		cout << "RF 16 " << scientific << setprecision(3)<< integral_E16_he << " Perc c/r TOT " << fixed << perc_E16_he <<" %"<< endl;

		/*SUMA PORCENTAJES*/
		double sum_perc_E02 =  perc_E02_th+ perc_E02_epi+ perc_E02_fs+  perc_E02_he;
		double sum_perc_E05 =  perc_E05_th+ perc_E05_epi+ perc_E05_fs+  perc_E05_he;
		double sum_perc_E16 =  perc_E16_th+ perc_E16_epi+ perc_E16_fs+  perc_E16_he;

		cout << "Sum perc in regions " << endl;
		cout << "RF 02 " << sum_perc_E02 << endl;
		cout << "RF 05 " << sum_perc_E05 << endl;
		cout << "RF 16 " << sum_perc_E16 << endl;
		
		/*SUMA*/
		double sum_intg_regions_E02 = integral_E02_th+integral_E02_epi+integral_E02_fs+integral_E02_he;
		double sum_intg_regions_E05 = integral_E05_th+integral_E05_epi+integral_E05_fs+integral_E05_he;
		double sum_intg_regions_E16 = integral_E16_th+integral_E16_epi+integral_E16_fs+integral_E16_he;

		cout << "Integral total RF sum regions	" << endl;
		cout << "RF 02 " << scientific << setprecision(2)<<  sum_intg_regions_E02 << endl;
		cout << "RF 05 " << scientific << setprecision(2)<<  sum_intg_regions_E05 << endl;
		cout << "RF 16 " << scientific << setprecision(2)<<  sum_intg_regions_E16 << endl;
		/****************************************************************************************/
		
		//~ TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE");
		//~ TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE");
		//~ TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
		//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE");
		//~ TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
		//~ TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE");
		//~ TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE");
		//~ TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
		//~ TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
		//~ TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm");
		//~ TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm");
		//~ TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		//~ TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		//~ TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		//~ TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
		//~ TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");

		TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		c1_new->SetLogx();
		//~ c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);

		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		h_d02->GetYaxis()->SetRangeUser(0,250);
		h_d02->GetXaxis()->SetRangeUser(0,1000);
		
		h_d01->SetLineColor(398);
		h_d02->SetLineColor(807);
		h_d03->SetLineColor(3);
		h_d04->SetLineColor(4);
		h_d05->SetLineColor(8);
		h_d06->SetLineColor(806);
		h_d07->SetLineColor(805);
		h_d08->SetLineColor(803);
		h_d09->SetLineColor(804);
		h_d10->SetLineColor(801);
		h_d11->SetLineColor(808);
		h_d12->SetLineColor(6);
		h_d13->SetLineColor(804);
		h_d14->SetLineColor(809);
		h_d15->SetLineColor(802);
		h_d16->SetLineColor(869);

		//~ h_d02->SetTitle("#bf{Response Function Spectrometer	 CEFNEN 2024}");
		h_d02->SetTitle("#bf{Proposal SND@LHC Neutron Spectrometer Set}");

		h_d01->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d01->GetXaxis()->SetTitle("#bf{Energy (MeV)}");
		//~ h_d02->GetYaxis()->SetTitle("#bf{Proposal SND@LHC Neutron Spectrometer Set}");
		//~ h_d02->GetXaxis()->SetTitle("#bf{Energy (MeV)}");

		//~ h_d01->Draw("HIST");
		h_d02->Draw("HIST");
		//~ h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		h_d05->Draw("HIST SAME");
		//~ h_d06->Draw("HIST SAME");  // no se considera en calculos
		//~ h_d07->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d08->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d09->Draw("HIST SAME");
		//~ h_d10->Draw("HIST SAME");
		//~ h_d11->Draw("HIST SAME");
		//~ h_d12->Draw("HIST SAME");
		//~ h_d13->Draw("HIST SAME");
		//~ h_d14->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d15->Draw("HIST SAME"); // no se considera en calculos
		h_d16->Draw("HIST SAME");

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		//~ auto legend_new = new TLegend(0.80303,0.100098,0.998918,0.917566);
	   auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Response Functions}","C"); // option "C" allows to center the header
	   legend_new->SetTextSize(0.018);
	   //~ legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE}","l");
	   legend_new->AddEntry(h_d02,"#bf{RF2 10cm HDPE}","l");
	   //~ legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE}","l");
	   legend_new->AddEntry(h_d05,"#bf{RF5 7mm Al Cylinder + 6.6cm BHDPECore}","l");
	   //~ legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch}","l");
	   //~ legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm}","l");
	   //~ legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm}","l");
	   //~ legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore}","l");
	   //~ legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite}","l");
	   //~ legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE}","l");
	   //~ legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE}","l");
	   legend_new->AddEntry(h_d16,"#bf{RF16 Naked 1inch}","l");
	   
	   legend_new->Draw();
	   //~ c1_new->Update();
	   c1_new->Draw();
		
	   //~ c1_new->SaveAs("RF_Spec_CEFNEN_2024_fix.svg");

			

}	

/*2do smooth, root smooth, PARA PAPER*/
void Response_function_matrix_lin_spec_paper_fix_active_volume_smooth_root_FTFP_plot(){

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_1_12cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_2_10cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_3_4cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_4_CylinderHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_6_18cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_7_20cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_8_1inchBHDPE_10cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_9_20cmBHDPE_1.0inch_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_10_Cylinder_4cm_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_11_Cylinder_3cm_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_12_Pb_10cmBHDPEcore_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_13_1inchBHDPE_15cmGraphite_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_14_inchBHDPE_15cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_15_24cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_16_Naked_1inch_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		//~ TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");


		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 01" << endl;
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 02" << endl;
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 03" << endl;
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 04" << endl;
		//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 05" << endl;
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 06" << endl;
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 07" << endl;
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 08" << endl;
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 09" << endl;
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 10" << endl;
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 11" << endl;
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 12" << endl;
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 13" << endl;
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 14" << endl;
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 15" << endl;
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_FTFP_BERT_smooth_smooth_root_15");
		cout << "det 16" << endl;
		//~ TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");

		

vector<TH1D*> vec_hist;
vec_hist.push_back(h_d01);
vec_hist.push_back(h_d02);
vec_hist.push_back(h_d03);
vec_hist.push_back(h_d04);
vec_hist.push_back(h_d05);
vec_hist.push_back(h_d06);
vec_hist.push_back(h_d07);
vec_hist.push_back(h_d08);
vec_hist.push_back(h_d09);
vec_hist.push_back(h_d10);
vec_hist.push_back(h_d11);
vec_hist.push_back(h_d12);
vec_hist.push_back(h_d13);
vec_hist.push_back(h_d14);
vec_hist.push_back(h_d15);
vec_hist.push_back(h_d16);
//~ vec_hist.push_back(h_d17);

/**Reescalamos**/
//~ double scale_factor = 0.25; // suponiendo una fuente isotropica
double scale_factor = 1.0; // Funciones respuesta ya escaladas en el smooth

vector<TH1D*> vec_hist_scaled;

for(int i=0;i<vec_hist.size();i++){
	cout << "det " <<i+1 << endl;
	TH1D *rf_scaled= (TH1D*)vec_hist[i]->Clone();
	rf_scaled->Scale(scale_factor);  // convert to %
	vec_hist_scaled.push_back(rf_scaled);
}


//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		//~ TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		TCanvas *c1_new = new TCanvas("RF","RF", 1400, 1000);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)
		//~ gPad->SetGrid();

		//~ TCanvas* canvas = new TCanvas("canvas", "Histogramas", 1400, 1000);

		c1_new->Divide(1,1);
    

		// --- Work on the first (and only) pad ---
		TPad *p = (TPad*)c1_new->cd(1);
		p->SetLogx();
		p->SetGrid();

		
		p->SetRightMargin(0.03); //borde derecho 0
		p->SetLeftMargin(0.125); 
		p->SetTopMargin(0.0409381);
		p->SetBottomMargin(0.1401);
	
		//~ c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		/*********************************/

	// Crea una paleta de colores arcoíris
	//~ int nColors = 256; // Puedes ajustar este valor según tus necesidades
	//~ int nColors = 501; // Puedes ajustar este valor según tus necesidades
	//~ int ndet = 17;
	int ndet = 16;
	int nColors =  ndet; // Puedes ajustar este valor según tus necesidades
	double stops[nColors];
	double red[nColors];
	double green[nColors];
	double blue[nColors];

	for (int i = 0; i < nColors; i++) {
		stops[i] = (double)i / (nColors - 1);
		red[i] = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
		green[i] = TMath::Sqrt(stops[i]);
		blue[i] = 1.0 - stops[i];
	}

	//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 255);
	//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 500);
	int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, ndet);

	//~ double n_hist = chi2_hist_vec.size();
	double n_hist =  ndet;
	double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
	TColor::InvertPalette();

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);

vector<double> vec_colorindex;
for(int i=0;i<ndet;i++){
	int colorIndex = static_cast<int>(i*step);
	int colorIndex2 = 51 + colorIndex * 48/n_hist;
	vec_colorindex.push_back(colorIndex2);
}

	     		//~ h_d01->SetTitle("#bf{Response Functions Spectrometer CEFNEN 2024 Smooth ROOT}");
		vec_hist_scaled[0]->SetTitle("#bf{Smooth Response Functions for the CEFNEN 23-24 Spectrometer}");

		vec_hist_scaled[0]->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		vec_hist_scaled[0]->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
		vec_hist_scaled[0]->GetXaxis()->CenterTitle(true);
		vec_hist_scaled[0]->GetYaxis()->CenterTitle(true);
		vec_hist_scaled[0]->GetXaxis()->SetRangeUser(1e-9,1e4);
		//~ vec_hist_scaled[0]->GetYaxis()->SetRangeUser(0,220); //sin escalar
		vec_hist_scaled[0]->GetYaxis()->SetRangeUser(0,55); //escalando


		vec_hist_scaled[0]->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
		vec_hist_scaled[0]->GetYaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist_scaled[0]->GetXaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist_scaled[0]->GetYaxis()->SetTitleOffset(1.2);
		vec_hist_scaled[0]->GetXaxis()->SetTitleOffset(1.4);
		vec_hist_scaled[0]->GetXaxis()->SetLabelSize(0.05);
		vec_hist_scaled[0]->GetYaxis()->SetLabelSize(0.05);
		//~ vec_hist[0]->GetYaxis()->SetMaxDigits(1);
		vec_hist_scaled[0]->SetLineWidth(4);

		//~ vec_hist[0]->SetLineColor(51);
		vec_hist_scaled[0]->SetLineColor(vec_colorindex[6]); //Det01 12 cm
	    //~ vec_hist[0]->SetLineWidth(3);
	    vec_hist_scaled[0]->Draw("HIST");
	    
//Arreglo de colores
/*****************************************************************/
	    h_d16->SetLineColor(vec_colorindex[0]);
	    h_d03->SetLineColor(vec_colorindex[1]);
	    h_d11->SetLineColor(vec_colorindex[2]);
	    h_d10->SetLineColor(vec_colorindex[3]);
	    h_d04->SetLineColor(vec_colorindex[4]);
	    h_d02->SetLineColor(vec_colorindex[5]);
	    //~ h_d01->SetLineColor(vec_colorindex[6]);
	    
	    h_d06->SetLineColor(vec_colorindex[7]);
	    h_d05->SetLineColor(vec_colorindex[8]);

		h_d07->SetLineColor(vec_colorindex[9]);
	   
	    h_d15->SetLineColor(vec_colorindex[10]);
	    h_d13->SetLineColor(vec_colorindex[11]);
	    h_d08->SetLineColor(vec_colorindex[12]);
	    h_d14->SetLineColor(vec_colorindex[13]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    // h_d09->SetLineColor(vec_colorindex[15]);
	    // h_d12->SetLineColor(vec_colorindex[16]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    h_d09->SetLineColor(vec_colorindex[14]);
	    h_d12->SetLineColor(vec_colorindex[15]);
/******************************************************************/

	    vec_hist_scaled[15]->SetLineColor(vec_colorindex[0]);
	    vec_hist_scaled[2]->SetLineColor(vec_colorindex[1]);
	    vec_hist_scaled[10]->SetLineColor(vec_colorindex[2]);
	    vec_hist_scaled[9]->SetLineColor(vec_colorindex[3]);
	    vec_hist_scaled[3]->SetLineColor(vec_colorindex[4]);
	    vec_hist_scaled[1]->SetLineColor(vec_colorindex[5]);
	    //~ h_d01->SetLineColor(vec_colorindex[6]);
	    vec_hist_scaled[5]->SetLineColor(vec_colorindex[7]);
	    vec_hist_scaled[4]->SetLineColor(vec_colorindex[8]);
	    vec_hist_scaled[6]->SetLineColor(vec_colorindex[9]);
	    vec_hist_scaled[14]->SetLineColor(vec_colorindex[10]);
	    vec_hist_scaled[12]->SetLineColor(vec_colorindex[11]);
	    vec_hist_scaled[7]->SetLineColor(vec_colorindex[12]);
	    vec_hist_scaled[13]->SetLineColor(vec_colorindex[13]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    // h_d09->SetLineColor(vec_colorindex[15]);
	    // h_d12->SetLineColor(vec_colorindex[16]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	   vec_hist_scaled[8]->SetLineColor(vec_colorindex[14]);
	   vec_hist_scaled[11]->SetLineColor(vec_colorindex[15]);


/******************************************************************/

	    //~ h_d01->SetLineColor(398);
		//~ h_d02->SetLineColor(807);
		//~ h_d03->SetLineColor(3);
		//~ h_d04->SetLineColor(4);
		//~ h_d05->SetLineColor(8);
		//~ h_d06->SetLineColor(806);
		//~ h_d07->SetLineColor(805);
		//~ h_d08->SetLineColor(803);
		//~ h_d09->SetLineColor(804);
		//~ h_d10->SetLineColor(801);
		//~ h_d11->SetLineColor(808);
		//~ h_d12->SetLineColor(6);
		//~ h_d13->SetLineColor(804);
		//~ h_d14->SetLineColor(809);
		//~ h_d15->SetLineColor(802);
		//~ h_d16->SetLineColor(869);
		//~ h_d17->SetLineColor(kBlue);

for(int i=1;i<ndet;i++){
	     vec_hist_scaled[i]->SetLineWidth(4);
	     vec_hist_scaled[i]->Draw("HIST SAME");
}


		//~ h_d01->Draw("HIST");
		//~ h_d02->Draw("HIST SAME");
		//~ h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		//~ h_d05->Draw("HIST SAME");
		//~ h_d06->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d07->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d08->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d09->Draw("HIST SAME");
		//~ h_d10->Draw("HIST SAME");
		//~ h_d11->Draw("HIST SAME");
		//~ h_d12->Draw("HIST SAME");
		//~ h_d13->Draw("HIST SAME");
		//~ h_d14->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d15->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d16->Draw("HIST SAME");
		//~ h_d17->Draw("HIST SAME");

		// ---------- 2. Coordinates (NDC: 0–1, relative to pad) ----------
		double x_ndc = 0.221176;   // left edge of text box
		double y_ndc = 0.889972;   // bottom edge of text box
		double x2_ndc = 0.921156;   // box width  (adjust)
		double y2_ndc = 0.9496565;   // box height (adjust)

		// ---------- 3. Create a TPaveText that behaves like TLatex ----------
		TPaveText *box = new TPaveText(x_ndc, y_ndc, x2_ndc, y2_ndc ,"NDC");   // “NDC” → use pad-relative coords

		box->SetFillColor(kWhite);        // solid white background
		box->SetFillStyle(1001);          // 1001 = opaque
		box->SetLineColor(kWhite);        // hide border (or SetBorderSize(0))
		box->SetBorderSize(0);

		// ---------- 4. Add one (or several) LaTeX strings ----------
		//~ TText *txt = box->AddText("CEFNEN-23/24 Spectrometer Response Functions");   // TLatex markup works
		TText *txt = box->AddText("CEFNEN, 16 Det. Spectrometer Response Functions");   // TLatex markup works
		//~ txt->SetTextFont(132);   // 132 → Computer-Modern Roman (LaTeX‐like)
		txt->SetTextSize(0.045); // relative to pad
		//~ txt->SetNDC(true);
		// ---------- 5. Draw it ----------
		box->Draw();

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		//~ auto legend_new = new TLegend(0.368506,0.609879,0.660714,0.854839);
		auto legend_new = new TLegend(0.293437,0.598277,0.452556,0.886835);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Detector}","C"); // option "C" allows to center the header
	   //~ legend_new->SetTextSize(0.018);
	   //~ legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d05,"#bf{E5_7mmAlCylinder_6.6cmBHDPECore_smooth}","l");
	   //~ legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch_smooth}","l");
	   //~ legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm_smooth}","l");
	   //~ legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm_smooth}","l");
	   //~ legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore_smooth}","l");
	   //~ legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite_smooth}","l");
	   //~ legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth}","l");
		legend_new->SetNColumns(2);
		legend_new->SetTextSize(0.023);
/**********************/		
		//~ legend_new->AddEntry(h_d16,"#bf{D16}","l");
		//~ legend_new->AddEntry(h_d05,"#bf{D05}","l");
		//~ legend_new->AddEntry(h_d03,"#bf{D03}","l");
		//~ legend_new->AddEntry(h_d15,"#bf{D15}","l");
		//~ legend_new->AddEntry(h_d11,"#bf{D11}","l");
		//~ legend_new->AddEntry(h_d13,"#bf{D13}","l");	
		//~ legend_new->AddEntry(h_d10,"#bf{D10}","l");
		//~ legend_new->AddEntry(h_d08,"#bf{D08}","l");
		//~ legend_new->AddEntry(h_d04,"#bf{D04}","l");
		//~ legend_new->AddEntry(h_d14,"#bf{D14}","l");
		//~ legend_new->AddEntry(h_d02,"#bf{D02}","l");
		//~ // legend_new->AddEntry(h_d17,"#bf{D17}","l");
		//~ legend_new->AddEntry(h_d01,"#bf{D01}","l");
		//~ legend_new->AddEntry(h_d09,"#bf{D09}","l");
		//~ legend_new->AddEntry(h_d06,"#bf{D06}","l");	   
		//~ legend_new->AddEntry(h_d12,"#bf{D12}","l");
		//~ legend_new->AddEntry(h_d07,"#bf{D07}","l");
/************************/	

		legend_new->AddEntry(vec_hist_scaled[15],"#bf{D16}","l");
		legend_new->AddEntry(vec_hist_scaled[4],"#bf{D05}","l");
		legend_new->AddEntry(vec_hist_scaled[2],"#bf{D03}","l");
		legend_new->AddEntry(vec_hist_scaled[6],"#bf{D07}","l");	
		legend_new->AddEntry(vec_hist_scaled[10],"#bf{D11}","l");
		legend_new->AddEntry(vec_hist_scaled[14],"#bf{D15}","l");
		legend_new->AddEntry(vec_hist_scaled[9],"#bf{D10}","l");
		legend_new->AddEntry(vec_hist_scaled[12],"#bf{D13}","l");
		legend_new->AddEntry(vec_hist_scaled[3],"#bf{D04}","l");
		legend_new->AddEntry(vec_hist_scaled[7],"#bf{D08}","l");
		legend_new->AddEntry(vec_hist_scaled[1],"#bf{D02}","l");
		legend_new->AddEntry(vec_hist_scaled[13],"#bf{D14}","l");
		legend_new->AddEntry(vec_hist_scaled[0],"#bf{D01}","l");
		legend_new->AddEntry(vec_hist_scaled[8],"#bf{D09}","l");
		legend_new->AddEntry(vec_hist_scaled[5],"#bf{D06}","l");	   
		legend_new->AddEntry(vec_hist_scaled[11],"#bf{D12}","l");
		//~ legend_new->AddEntry(vec_hist_scaled[6],"#bf{D07}","l");

	   
	   legend_new->Draw();
	   //~ c1_new->Update();

		TPad *p_insert = new TPad("p","p", 0.524818,0.511506,0.924818,0.882845);
		p_insert->Draw();
		p_insert->cd();
		p_insert->SetLogx();
		p_insert->SetGrid();

		p_insert->SetRightMargin(0.03); //borde derecho 0
		p_insert->SetLeftMargin(0.135); 
		p_insert->SetTopMargin(0.0409381);
		p_insert->SetBottomMargin(0.171);

		//~ TLatex *lco_masl = new TLatex(0.13,0.81,(str_stream_altitude+RG_campaign).c_str()); // Chapiquilta Top left
		TLatex *insert_text = new TLatex(0.17,0.84,"a)"); // Chapiquilta Botoom left
		insert_text->SetTextColor(kBlack);
		insert_text->SetNDC(true);
		insert_text->SetTextSize(0.1);

		
		TH1D *h_d05_copy = (TH1D*)vec_hist_scaled[4]->DrawCopy("HIST");
		h_d05_copy->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d05_copy->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
		h_d05_copy->GetXaxis()->CenterTitle(true);
		h_d05_copy->GetYaxis()->CenterTitle(true);
		h_d05_copy->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
		h_d05_copy->GetYaxis()->SetTitleSize(0.07); // Cambia "Título del Eje Y" al título deseado para el eje Y
		h_d05_copy->GetXaxis()->SetTitleSize(0.07); // Cambia "Título del Eje Y" al título deseado para el eje Y
		h_d05_copy->GetYaxis()->SetTitleOffset(1.0);
		h_d05_copy->GetXaxis()->SetTitleOffset(1.2);
		h_d05_copy->GetXaxis()->SetLabelSize(0.07);
		h_d05_copy->GetYaxis()->SetLabelSize(0.07);
		h_d05_copy->SetLineWidth(4);
		TH1D *h_d13_copy = (TH1D*)vec_hist_scaled[12]->DrawCopy("HIST SAME");
		//~ TH1D *h_d17_copy = (TH1D*)h_d17->DrawCopy("HIST SAME");
		TH1D *h_d09_copy = (TH1D*)vec_hist_scaled[8]->DrawCopy("HIST SAME");
		TH1D *h_d12_copy = (TH1D *)vec_hist_scaled[11]->DrawCopy("HIST SAME");
		insert_text->Draw("SAME");
		h_d05_copy->GetXaxis()->SetRangeUser(1e-1,1e3);
		//~ h_d05_copy->GetYaxis()->SetRangeUser(0.,25.); // sin escalar
		h_d05_copy->GetYaxis()->SetRangeUser(0.,6.3); // escalando
		
	   c1_new->Draw();
		
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_2025_FTFP_smooth_SG_smooth_root_scaled.svg");
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_2025_FTFP_smooth_SG_smooth_root_scaled.png");
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_2025_FTFP_smooth_SG_smooth_root_scaled.pdf");
}



/*2do smooth, root smooth, PARA PAPER*/
void Response_function_matrix_lin_spec_23_24_fix_active_volume_smooth_root_plot(){

		//~ TFile *E01_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_1_12cmHDPE_VV.root");
		//~ TFile *E02_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_2_10cmHDPE_VV.root");
		//~ TFile *E03_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_3_4cmHDPE_NEW_VV.root");
		//~ TFile *E04_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_4_CylinderHDPE_VV.root");
		//~ TFile *E05_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		//~ TFile *E06_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_6_18cmHDPE_VV.root");
		//~ TFile *E07_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_7_20cmHDPE_VV.root");
		//~ TFile *E08_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		//~ TFile *E09_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		//~ TFile *E10_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_10_Cylinder_4cm_VV.root");
		//~ TFile *E11_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_11_Cylinder_3cm_VV.root");
		//~ TFile *E12_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		//~ TFile *E13_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		//~ TFile *E14_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		//~ TFile *E15_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2023/Efi_15_24cmHDPE_VV.root");
		//~ TFile *E16_file = TFile::Open("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024/Efi_16_Naked_1inch_NEW_VV.root");
		
		//PCLIN5
		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_1_12cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_2_10cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_3_4cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_4_CylinderHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_6_18cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_7_20cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_8_1inchBHDPE_10cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_9_20cmBHDPE_1.0inch_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_10_Cylinder_4cm_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_11_Cylinder_3cm_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_12_Pb_10cmBHDPEcore_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_13_1inchBHDPE_15cmGraphite_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_14_inchBHDPE_15cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_15_24cmHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_16_Naked_1inch_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");
		TFile *E17_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_FTFP_BERT_VV_smooth_smooth_root_15_ws.root");

		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_FTFP_BERT_smooth_smooth_root_15");
		// TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_FTFP_BERT_smooth_smooth_root_15");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_FTFP_BERT_smooth_smooth_root_15");
		// TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		

vector<TH1D*> vec_hist;
vec_hist.push_back(h_d01);
vec_hist.push_back(h_d02);
vec_hist.push_back(h_d03);
vec_hist.push_back(h_d04);
vec_hist.push_back(h_d05);
vec_hist.push_back(h_d06);
vec_hist.push_back(h_d07);
vec_hist.push_back(h_d08);
vec_hist.push_back(h_d09);
vec_hist.push_back(h_d10);
vec_hist.push_back(h_d11);
vec_hist.push_back(h_d12);
vec_hist.push_back(h_d13);
vec_hist.push_back(h_d14);
vec_hist.push_back(h_d15);
vec_hist.push_back(h_d16);
//~ vec_hist.push_back(h_d17);

/**Reescalamos**/
//~ double scale_factor = 0.25; // suponiendo una fuente isotropica
double scale_factor = 1.0; // Funciones respuesta ya escaladas en el smooth

vector<TH1D*> vec_hist_scaled;

for(int i=0;i<vec_hist.size();i++){
	TH1D *rf_scaled= (TH1D*)vec_hist[i]->Clone();
	rf_scaled->Scale(scale_factor);  // convert to %
	vec_hist_scaled.push_back(rf_scaled);
}


//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		//~ TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		TCanvas *c1_new = new TCanvas("RF","RF", 1400, 1000);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)
		//~ gPad->SetGrid();

		//~ TCanvas* canvas = new TCanvas("canvas", "Histogramas", 1400, 1000);

		c1_new->Divide(1,1);
    

		// --- Work on the first (and only) pad ---
		TPad *p = (TPad*)c1_new->cd(1);
		p->SetLogx();
		p->SetGrid();

		
		p->SetRightMargin(0.03); //borde derecho 0
		p->SetLeftMargin(0.125); 
		p->SetTopMargin(0.0409381);
		p->SetBottomMargin(0.1401);
	
		//~ c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		/*********************************/

	// Crea una paleta de colores arcoíris
	//~ int nColors = 256; // Puedes ajustar este valor según tus necesidades
	//~ int nColors = 501; // Puedes ajustar este valor según tus necesidades
	//~ int ndet = 17;
	int ndet = 16;
	int nColors =  ndet; // Puedes ajustar este valor según tus necesidades
	double stops[nColors];
	double red[nColors];
	double green[nColors];
	double blue[nColors];

	for (int i = 0; i < nColors; i++) {
		stops[i] = (double)i / (nColors - 1);
		red[i] = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
		green[i] = TMath::Sqrt(stops[i]);
		blue[i] = 1.0 - stops[i];
	}

	//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 255);
	//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 500);
	int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, ndet);

	//~ double n_hist = chi2_hist_vec.size();
	double n_hist =  ndet;
	double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
	TColor::InvertPalette();

		
		//~ h_d01->GetYaxis()->SetRangeUser(0,220);
		//~ h_d01->GetYaxis()->SetRangeUser(0,218);
		//~ h_d01->GetXaxis()->SetRangeUser(0,15300);
		//~ h_d01->GetYaxis()->SetRangeUser(0,300);
		//~ h_d01->GetXaxis()->SetRangeUser(0,1000);
		//~ h_d02->GetXaxis()->SetRangeUser(0,1000);

vector<double> vec_colorindex;
for(int i=0;i<ndet;i++){
	int colorIndex = static_cast<int>(i*step);
	int colorIndex2 = 51 + colorIndex * 48/n_hist;
	vec_colorindex.push_back(colorIndex2);
}

	     		//~ h_d01->SetTitle("#bf{Response Functions Spectrometer CEFNEN 2024 Smooth ROOT}");
		vec_hist_scaled[0]->SetTitle("#bf{Smooth Response Functions for the CEFNEN 23-24 Spectrometer}");

		vec_hist_scaled[0]->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		vec_hist_scaled[0]->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
		vec_hist_scaled[0]->GetXaxis()->CenterTitle(true);
		vec_hist_scaled[0]->GetYaxis()->CenterTitle(true);
		vec_hist_scaled[0]->GetXaxis()->SetRangeUser(1e-9,1e4);
		//~ vec_hist_scaled[0]->GetYaxis()->SetRangeUser(0,220); //sin escalar
		vec_hist_scaled[0]->GetYaxis()->SetRangeUser(0,55); //escalando


		vec_hist_scaled[0]->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
		vec_hist_scaled[0]->GetYaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist_scaled[0]->GetXaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist_scaled[0]->GetYaxis()->SetTitleOffset(1.2);
		vec_hist_scaled[0]->GetXaxis()->SetTitleOffset(1.4);
		vec_hist_scaled[0]->GetXaxis()->SetLabelSize(0.05);
		vec_hist_scaled[0]->GetYaxis()->SetLabelSize(0.05);
		//~ vec_hist[0]->GetYaxis()->SetMaxDigits(1);
		vec_hist_scaled[0]->SetLineWidth(4);

		//~ vec_hist[0]->SetLineColor(51);
		vec_hist_scaled[0]->SetLineColor(vec_colorindex[6]); //Det01 12 cm
	    //~ vec_hist[0]->SetLineWidth(3);
	    vec_hist_scaled[0]->Draw("HIST");
	    
//Arreglo de colores
/*****************************************************************/
	    h_d16->SetLineColor(vec_colorindex[0]);
	    h_d03->SetLineColor(vec_colorindex[1]);
	    h_d11->SetLineColor(vec_colorindex[2]);
	    h_d10->SetLineColor(vec_colorindex[3]);
	    h_d04->SetLineColor(vec_colorindex[4]);
	    h_d02->SetLineColor(vec_colorindex[5]);
	    //~ h_d01->SetLineColor(vec_colorindex[6]);
	    
	    h_d06->SetLineColor(vec_colorindex[7]);
	    h_d05->SetLineColor(vec_colorindex[8]);

		h_d07->SetLineColor(vec_colorindex[9]);
	   
	    h_d15->SetLineColor(vec_colorindex[10]);
	    h_d13->SetLineColor(vec_colorindex[11]);
	    h_d08->SetLineColor(vec_colorindex[12]);
	    h_d14->SetLineColor(vec_colorindex[13]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    // h_d09->SetLineColor(vec_colorindex[15]);
	    // h_d12->SetLineColor(vec_colorindex[16]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    h_d09->SetLineColor(vec_colorindex[14]);
	    h_d12->SetLineColor(vec_colorindex[15]);
/******************************************************************/

	    vec_hist_scaled[15]->SetLineColor(vec_colorindex[0]);
	    vec_hist_scaled[2]->SetLineColor(vec_colorindex[1]);
	    vec_hist_scaled[10]->SetLineColor(vec_colorindex[2]);
	    vec_hist_scaled[9]->SetLineColor(vec_colorindex[3]);
	    vec_hist_scaled[3]->SetLineColor(vec_colorindex[4]);
	    vec_hist_scaled[1]->SetLineColor(vec_colorindex[5]);
	    //~ h_d01->SetLineColor(vec_colorindex[6]);
	    vec_hist_scaled[5]->SetLineColor(vec_colorindex[7]);
	    vec_hist_scaled[4]->SetLineColor(vec_colorindex[8]);
	    vec_hist_scaled[6]->SetLineColor(vec_colorindex[9]);
	    vec_hist_scaled[14]->SetLineColor(vec_colorindex[10]);
	    vec_hist_scaled[12]->SetLineColor(vec_colorindex[11]);
	    vec_hist_scaled[7]->SetLineColor(vec_colorindex[12]);
	    vec_hist_scaled[13]->SetLineColor(vec_colorindex[13]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	    // h_d09->SetLineColor(vec_colorindex[15]);
	    // h_d12->SetLineColor(vec_colorindex[16]);

	    // h_d17->SetLineColor(vec_colorindex[14]);
	   vec_hist_scaled[8]->SetLineColor(vec_colorindex[14]);
	   vec_hist_scaled[11]->SetLineColor(vec_colorindex[15]);


/******************************************************************/

	    //~ h_d01->SetLineColor(398);
		//~ h_d02->SetLineColor(807);
		//~ h_d03->SetLineColor(3);
		//~ h_d04->SetLineColor(4);
		//~ h_d05->SetLineColor(8);
		//~ h_d06->SetLineColor(806);
		//~ h_d07->SetLineColor(805);
		//~ h_d08->SetLineColor(803);
		//~ h_d09->SetLineColor(804);
		//~ h_d10->SetLineColor(801);
		//~ h_d11->SetLineColor(808);
		//~ h_d12->SetLineColor(6);
		//~ h_d13->SetLineColor(804);
		//~ h_d14->SetLineColor(809);
		//~ h_d15->SetLineColor(802);
		//~ h_d16->SetLineColor(869);
		//~ h_d17->SetLineColor(kBlue);

for(int i=1;i<ndet;i++){
	     vec_hist_scaled[i]->SetLineWidth(4);
	     vec_hist_scaled[i]->Draw("HIST SAME");
}


		//~ h_d01->Draw("HIST");
		//~ h_d02->Draw("HIST SAME");
		//~ h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		//~ h_d05->Draw("HIST SAME");
		//~ h_d06->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d07->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d08->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d09->Draw("HIST SAME");
		//~ h_d10->Draw("HIST SAME");
		//~ h_d11->Draw("HIST SAME");
		//~ h_d12->Draw("HIST SAME");
		//~ h_d13->Draw("HIST SAME");
		//~ h_d14->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d15->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d16->Draw("HIST SAME");
		//~ h_d17->Draw("HIST SAME");

		// ---------- 2. Coordinates (NDC: 0–1, relative to pad) ----------
		double x_ndc = 0.221176;   // left edge of text box
		double y_ndc = 0.889972;   // bottom edge of text box
		double x2_ndc = 0.921156;   // box width  (adjust)
		double y2_ndc = 0.9496565;   // box height (adjust)

		// ---------- 3. Create a TPaveText that behaves like TLatex ----------
		TPaveText *box = new TPaveText(x_ndc, y_ndc, x2_ndc, y2_ndc ,"NDC");   // “NDC” → use pad-relative coords

		box->SetFillColor(kWhite);        // solid white background
		box->SetFillStyle(1001);          // 1001 = opaque
		box->SetLineColor(kWhite);        // hide border (or SetBorderSize(0))
		box->SetBorderSize(0);

		// ---------- 4. Add one (or several) LaTeX strings ----------
		//~ TText *txt = box->AddText("CEFNEN-23/24 Spectrometer Response Functions");   // TLatex markup works
		TText *txt = box->AddText("CEFNEN, 16 Det. Spectrometer Response Functions");   // TLatex markup works
		//~ txt->SetTextFont(132);   // 132 → Computer-Modern Roman (LaTeX‐like)
		txt->SetTextSize(0.045); // relative to pad
		//~ txt->SetNDC(true);
		// ---------- 5. Draw it ----------
		box->Draw();

		//~ auto legend_new = new TLegend(0.744,0.785,0.948,0.949);
		//~ auto legend_new = new TLegend(0.368506,0.609879,0.660714,0.854839);
		auto legend_new = new TLegend(0.293437,0.598277,0.452556,0.886835);
		//~ auto legend_new = new TLegend(0.632576,0.670363,0.900433,0.900202);
	   legend_new->SetHeader("#bf{Detector}","C"); // option "C" allows to center the header
	   //~ legend_new->SetTextSize(0.018);
	   //~ legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d03,"#bf{E3_4cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E4_CylinderHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d05,"#bf{E5_7mmAlCylinder_6.6cmBHDPECore_smooth}","l");
	   //~ legend_new->AddEntry(h_d06,"#bf{E6_18cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d07,"#bf{E7_20cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d08,"#bf{E8_1inchBHDPE_10cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d09,"#bf{E9_20cmBHDPE_1.0inch_smooth}","l");
	   //~ legend_new->AddEntry(h_d10,"#bf{E10_Cylinder_4cm_smooth}","l");
	   //~ legend_new->AddEntry(h_d11,"#bf{E11_Cylinder_3cm_smooth}","l");
	   //~ legend_new->AddEntry(h_d12,"#bf{E12_Pb_10cmBHDPEcore_smooth}","l");
	   //~ legend_new->AddEntry(h_d13,"#bf{E13_1inchBHDPE_15cmGraphite_smooth}","l");
	   //~ legend_new->AddEntry(h_d14,"#bf{E14_1inchBHDPE_15cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d15,"#bf{E15_24cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d16,"#bf{E16_Naked_1inch_smooth}","l");
	   //~ legend_new->AddEntry(h_d04,"#bf{E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth}","l");
		legend_new->SetNColumns(2);
		legend_new->SetTextSize(0.023);
/**********************/		
		//~ legend_new->AddEntry(h_d16,"#bf{D16}","l");
		//~ legend_new->AddEntry(h_d05,"#bf{D05}","l");
		//~ legend_new->AddEntry(h_d03,"#bf{D03}","l");
		//~ legend_new->AddEntry(h_d15,"#bf{D15}","l");
		//~ legend_new->AddEntry(h_d11,"#bf{D11}","l");
		//~ legend_new->AddEntry(h_d13,"#bf{D13}","l");	
		//~ legend_new->AddEntry(h_d10,"#bf{D10}","l");
		//~ legend_new->AddEntry(h_d08,"#bf{D08}","l");
		//~ legend_new->AddEntry(h_d04,"#bf{D04}","l");
		//~ legend_new->AddEntry(h_d14,"#bf{D14}","l");
		//~ legend_new->AddEntry(h_d02,"#bf{D02}","l");
		//~ // legend_new->AddEntry(h_d17,"#bf{D17}","l");
		//~ legend_new->AddEntry(h_d01,"#bf{D01}","l");
		//~ legend_new->AddEntry(h_d09,"#bf{D09}","l");
		//~ legend_new->AddEntry(h_d06,"#bf{D06}","l");	   
		//~ legend_new->AddEntry(h_d12,"#bf{D12}","l");
		//~ legend_new->AddEntry(h_d07,"#bf{D07}","l");
/************************/	

		legend_new->AddEntry(vec_hist_scaled[15],"#bf{D16}","l");
		legend_new->AddEntry(vec_hist_scaled[4],"#bf{D05}","l");
		legend_new->AddEntry(vec_hist_scaled[2],"#bf{D03}","l");
		legend_new->AddEntry(vec_hist_scaled[6],"#bf{D07}","l");	
		legend_new->AddEntry(vec_hist_scaled[10],"#bf{D11}","l");
		legend_new->AddEntry(vec_hist_scaled[14],"#bf{D15}","l");
		legend_new->AddEntry(vec_hist_scaled[9],"#bf{D10}","l");
		legend_new->AddEntry(vec_hist_scaled[12],"#bf{D13}","l");
		legend_new->AddEntry(vec_hist_scaled[3],"#bf{D04}","l");
		legend_new->AddEntry(vec_hist_scaled[7],"#bf{D08}","l");
		legend_new->AddEntry(vec_hist_scaled[1],"#bf{D02}","l");
		legend_new->AddEntry(vec_hist_scaled[13],"#bf{D14}","l");
		legend_new->AddEntry(vec_hist_scaled[0],"#bf{D01}","l");
		legend_new->AddEntry(vec_hist_scaled[8],"#bf{D09}","l");
		legend_new->AddEntry(vec_hist_scaled[5],"#bf{D06}","l");	   
		legend_new->AddEntry(vec_hist_scaled[11],"#bf{D12}","l");
		//~ legend_new->AddEntry(vec_hist_scaled[6],"#bf{D07}","l");

	   
	   legend_new->Draw();
	   //~ c1_new->Update();

		TPad *p_insert = new TPad("p","p", 0.524818,0.511506,0.924818,0.882845);
		p_insert->Draw();
		p_insert->cd();
		p_insert->SetLogx();
		p_insert->SetGrid();

		p_insert->SetRightMargin(0.03); //borde derecho 0
		p_insert->SetLeftMargin(0.135); 
		p_insert->SetTopMargin(0.0409381);
		p_insert->SetBottomMargin(0.171);

		//~ TLatex *lco_masl = new TLatex(0.13,0.81,(str_stream_altitude+RG_campaign).c_str()); // Chapiquilta Top left
		TLatex *insert_text = new TLatex(0.17,0.84,"a)"); // Chapiquilta Botoom left
		insert_text->SetTextColor(kBlack);
		insert_text->SetNDC(true);
		insert_text->SetTextSize(0.1);

		
		TH1D *h_d05_copy = (TH1D*)vec_hist_scaled[4]->DrawCopy("HIST");
		h_d05_copy->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		h_d05_copy->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
		h_d05_copy->GetXaxis()->CenterTitle(true);
		h_d05_copy->GetYaxis()->CenterTitle(true);
		h_d05_copy->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
		h_d05_copy->GetYaxis()->SetTitleSize(0.07); // Cambia "Título del Eje Y" al título deseado para el eje Y
		h_d05_copy->GetXaxis()->SetTitleSize(0.07); // Cambia "Título del Eje Y" al título deseado para el eje Y
		h_d05_copy->GetYaxis()->SetTitleOffset(1.0);
		h_d05_copy->GetXaxis()->SetTitleOffset(1.2);
		h_d05_copy->GetXaxis()->SetLabelSize(0.07);
		h_d05_copy->GetYaxis()->SetLabelSize(0.07);
		h_d05_copy->SetLineWidth(4);
		TH1D *h_d13_copy = (TH1D*)vec_hist_scaled[12]->DrawCopy("HIST SAME");
		//~ TH1D *h_d17_copy = (TH1D*)h_d17->DrawCopy("HIST SAME");
		TH1D *h_d09_copy = (TH1D*)vec_hist_scaled[8]->DrawCopy("HIST SAME");
		TH1D *h_d12_copy = (TH1D *)vec_hist_scaled[11]->DrawCopy("HIST SAME");
		insert_text->Draw("SAME");
		h_d05_copy->GetXaxis()->SetRangeUser(1e-1,1e3);
		//~ h_d05_copy->GetYaxis()->SetRangeUser(0.,25.); // sin escalar
		h_d05_copy->GetYaxis()->SetRangeUser(0.,6.3); // escalando
		
	   c1_new->Draw();
		
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_23_24_fix_smooth_SG_smooth_root_scaled_NEW.svg");
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_23_24_fix_smooth_SG_smooth_root_scaled_NEW.png");
	   c1_new->SaveAs("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_Spec_CEFNEN_23_24_fix_smooth_SG_smooth_root_scaled_NEW.pdf");
}



void Response_function_comparison_plot(int det){

		TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV.root");
		TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV.root");
		TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV.root");
		TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
		TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
		TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV.root");
		TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV.root");
		TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
		TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
		TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV.root");
		TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV.root");
		TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
		TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
		TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
		TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV.root");
		TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV.root");
		TFile *E17_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV.root");

		//* NEW RF*//
		TFile *E01_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_1_12cmHDPE_FTFP_VV.root");
		TFile *E02_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_2_10cmHDPE_FTFP_VV.root");
		TFile *E03_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_3_4cmHDPE_FTFP_VV.root");
		TFile *E04_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_4_CylinderHDPE_FTFP_VV.root");
		TFile *E05_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_FTFP_VV.root");
		TFile *E06_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_6_18cmHDPE_FTFP_VV.root");
		TFile *E07_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_7_20cmHDPE_FTFP_VV.root");
		TFile *E08_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_8_1inchBHDPE_10cmHDPE_FTFP_VV.root");
		TFile *E09_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_9_20cmBHDPE_1.0inch_FTFP_VV.root");
		TFile *E10_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_10_Cylinder_4cm_FTFP_VV.root");
		TFile *E11_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_11_Cylinder_3cm_FTFP_VV.root");
		TFile *E12_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_12_Pb_10cmBHDPEcore_FTFP_VV.root");
		TFile *E13_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_13_1inchBHDPE_15cmGraphite_FTFP_VV.root");
		TFile *E14_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_14_inchBHDPE_15cmHDPE_FTFP_VV.root");
		TFile *E15_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_15_24cmHDPE_FTFP_VV.root");
		TFile *E16_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_16_Naked_1inch_FTFP_VV.root");
		TFile *E17_file_ftfp = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_FTFP_VV.root");

		//~ TFile *E02_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E03_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E04_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E05_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E06_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E07_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E08_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E09_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E10_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E11_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E12_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E13_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E14_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E15_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E16_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV_smooth_smooth_root_15.root");
		//~ TFile *E17_file = new TFile("./Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_VV_smooth_smooth_root_15.root");

		TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW");
		TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW");
		TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
		TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
		TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
		TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW");
		TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW");
		TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
		TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
		TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW");
		TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW");
		TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
		TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
		TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
		TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW");
		TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");
		TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE");

		TH1D *h_d01_ftfp = (TH1D*)E01_file_ftfp->Get("E1_12cmHDPE_FTFP");
		TH1D *h_d02_ftfp = (TH1D*)E02_file_ftfp->Get("E2_10cmHDPE_FTFP");
		TH1D *h_d03_ftfp = (TH1D*)E03_file_ftfp->Get("E3_4cmHDPE_FTFP");
		TH1D *h_d04_ftfp = (TH1D*)E04_file_ftfp->Get("E4_CylinderHDPE_FTFP");
		TH1D *h_d05_ftfp = (TH1D*)E05_file_ftfp->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_FTFP");
		TH1D *h_d06_ftfp = (TH1D*)E06_file_ftfp->Get("E6_18cmHDPE_FTFP");
		TH1D *h_d07_ftfp = (TH1D*)E07_file_ftfp->Get("E7_20cmHDPE_FTFP");
		TH1D *h_d08_ftfp = (TH1D*)E08_file_ftfp->Get("E8_1inchBHDPE_10cmHDPE_FTFP");
		TH1D *h_d09_ftfp = (TH1D*)E09_file_ftfp->Get("E9_20cmBHDPE_1.0inch_FTFP");
		TH1D *h_d10_ftfp = (TH1D*)E10_file_ftfp->Get("E10_Cylinder_4cm_FTFP");
		TH1D *h_d11_ftfp = (TH1D*)E11_file_ftfp->Get("E11_Cylinder_3cm_FTFP");
		TH1D *h_d12_ftfp = (TH1D*)E12_file_ftfp->Get("E12_Pb_10cmBHDPEcore_FTFP");
		TH1D *h_d13_ftfp = (TH1D*)E13_file_ftfp->Get("E13_1inchBHDPE_15cmGraphite_FTFP");
		TH1D *h_d14_ftfp = (TH1D*)E14_file_ftfp->Get("E14_inchBHDPE_15cmHDPE_FTFP");
		TH1D *h_d15_ftfp = (TH1D*)E15_file_ftfp->Get("E15_24cmHDPE_FTFP");
		TH1D *h_d16_ftfp = (TH1D*)E16_file_ftfp->Get("E16_Naked_1inch_FTFP");
		TH1D *h_d17_ftfp = (TH1D*)E17_file_ftfp->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_FTFP");

		//~ TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE_smooth_smooth_root_15");
		//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW_smooth_smooth_root_15");
		//~ // TH1D *h_d04 = (TH1D*)E04_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");
		//~ TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore_smooth_smooth_root_15");
		//~ TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE_smooth_smooth_root_15");
		//~ TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch_smooth_smooth_root_15");
		//~ TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW_smooth_smooth_root_15");
		//~ TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW_smooth_smooth_root_15");
		//~ // TH1D *h_d17 = (TH1D*)E17_file->Get("E17_Cylinder_HDPE_10cm_plus_5cm_BHDPE_smooth_smooth_root_15");

		vector<string> vec_names = {" D01_12cmHDPE",
                                     "D02_10cmHDPE",
                                     "D03_4cmHDPE",
                                     "D04_CylinderHDPE",
                                     "D05_Cylinder7mmAl_1.8cmBHDPECore",
                                     "D06_18cmHDPE",
                                     "D07_20cmHDPE",
                                     "D08_1inchBHDPE_10cmHDPE",
                                     "D09_20cmBHDPE_1.0inch",
                                     "D10_Cylinder_4cm",
                                     "D11_Cylinder_3cm",
                                     "D12_Pb_10cmBHDPEcore",
                                     "D13_1inchBHDPE_15cmGraphite",
                                     "D14_inchBHDPE_15cmHDPE",
                                     "D15_24cmHDPE",
                                     "D16_Naked_1inch",
                                     "D17_Cylinder_HDPE_10cm_plus_5cm_BHDPE",};

vector<TH1D*> vec_hist;
vector<TH1D*> vec_hist_ftfp;

vec_hist.push_back(h_d01);
vec_hist.push_back(h_d02);
vec_hist.push_back(h_d03);
vec_hist.push_back(h_d04);
vec_hist.push_back(h_d05);
vec_hist.push_back(h_d06);
vec_hist.push_back(h_d07);
vec_hist.push_back(h_d08);
vec_hist.push_back(h_d09);
vec_hist.push_back(h_d10);
vec_hist.push_back(h_d11);
vec_hist.push_back(h_d12);
vec_hist.push_back(h_d13);
vec_hist.push_back(h_d14);
vec_hist.push_back(h_d15);
vec_hist.push_back(h_d16);
vec_hist.push_back(h_d17);


vec_hist_ftfp.push_back(h_d01_ftfp);
vec_hist_ftfp.push_back(h_d02_ftfp);
vec_hist_ftfp.push_back(h_d03_ftfp);
vec_hist_ftfp.push_back(h_d04_ftfp);
vec_hist_ftfp.push_back(h_d05_ftfp);
vec_hist_ftfp.push_back(h_d06_ftfp);
vec_hist_ftfp.push_back(h_d07_ftfp);
vec_hist_ftfp.push_back(h_d08_ftfp);
vec_hist_ftfp.push_back(h_d09_ftfp);
vec_hist_ftfp.push_back(h_d10_ftfp);
vec_hist_ftfp.push_back(h_d11_ftfp);
vec_hist_ftfp.push_back(h_d12_ftfp);
vec_hist_ftfp.push_back(h_d13_ftfp);
vec_hist_ftfp.push_back(h_d14_ftfp);
vec_hist_ftfp.push_back(h_d15_ftfp);
vec_hist_ftfp.push_back(h_d16_ftfp);
vec_hist_ftfp.push_back(h_d17_ftfp);



//~ Generador_Funcion_Respuesta("./01_12cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","1_12cmHDPE",2.8128e-4,"V","","HIST",398);
//~ Generador_Funcion_Respuesta("./02_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","2_10cmHDPE",2.3e-4,"V","","HIST",807);
//~ Generador_Funcion_Respuesta("./03_04cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","3_4cmHDPE",8.72e-05,"V","","HIST",3); //arreglado
//~ Generador_Funcion_Respuesta("./04_Cylinder_HDPE/Resultado/Data_Sistema.root","binning_150.dat","4_CylinderHDPE",1.12908e-4,"V","","HIST SAME",4);
//~ Generador_Funcion_Respuesta("./05_Cylinder_7mmAl_1.8cmBHDPEcore/Resultado/Data_Sistema.root","binning_150.dat","5_Cylinder7mmAl_1.8cmBHDPECore",1.16515e-4,"V","","HIST SAME",8);
//~ Generador_Funcion_Respuesta("./06_18cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","6_18cmHDPE",4.428e-4,"V","","HIST SAME",806);
//~ Generador_Funcion_Respuesta("./07_20cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","7_20cmHDPE",5e-4,"V","","HIST SAME",805);
//~ Generador_Funcion_Respuesta("./08_1inchBHDPE_10cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","8_1inchBHDPE_10cmHDPE",3.57e-4,"V","","HIST SAME",803);
//~ Generador_Funcion_Respuesta("./09_20cmBHDPE_1.0_inchHe3/Resultado/Data_Sistema.root","binning_150.dat","9_20cmBHDPE_1.0inch",5e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./10_Cylinder_HDPE_r_4cm/Resultado/Data_Sistema.root","binning_150.dat","10_Cylinder_4cm",1.18124e-4,"V","","HIST SAME",801);
//~ Generador_Funcion_Respuesta("./11_Cylinder_HDPE_r_3cm/Resultado/Data_Sistema.root","binning_150.dat","11_Cylinder_3cm",8.6708e-5,"V","","HIST SAME",808);
//~ Generador_Funcion_Respuesta("./12_Pb_Cd_5cmHDPE_10cmBHDPE_1-inch-He3-Detector/Resultado/Data_Sistema.root","binning_150.dat","12_Pb_10cmBHDPEcore",1.09468e-03,"V","","HIST SAME",6); //scale arreglado
//~ Generador_Funcion_Respuesta("./13_1inchBHDPE_15cmGraphite/Resultado/Data_Sistema.root","binning_150.dat","13_1inchBHDPE_15cmGraphite",4.5664e-4,"V","","HIST SAME",804);
//~ Generador_Funcion_Respuesta("./14_1inchBHDPE_15cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","14_inchBHDPE_15cmHDPE",4.56e-04 ,"V","","HIST SAME",809); //scale factor arreglado
//~ Generador_Funcion_Respuesta("./15_24cmHDPE/Resultado/Data_Sistema.root","binning_150.dat","15_24cmHDPE",6.192e-4,"V","","HIST SAME",802);
//~ Generador_Funcion_Respuesta("./16_Naked_1inch/Resultado/Data_Sistema.root","binning_150.dat","16_Naked_1inch",3.45269e-05,"V","","HIST SAME",869); // scale factor arreglado
		
		//~ TCanvas *c1_new = new TCanvas("RF","RF",1920,1080);
		TCanvas *c1_new = new TCanvas("RF","RF", 780, 900);
		c1_new->SetSupportGL(true);
		gStyle->SetCanvasPreferGL(kTRUE);
		//~ gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)
		//~ gPad->SetGrid();


	   //~ c1_new->Divide(1,2);
    

		// --- Work on the first (and only) pad ---
		//~ TPad *p = (TPad*)c1_new->cd(1);

		TPad *p = new TPad("p1", "Top pad", 0, 0.35, 1, 1.0); // ylow=0.4, yhigh=1.0
		TPad *pad2 = new TPad("p2", "Bottom pad", 0, 0.0, 1, 0.35);

		double h1_frac = p->GetHNDC(); // height of pad in NDC units
		double h2_frac = pad2->GetHNDC();

		//~ double offset1 = 0.8;
		//~ double offset2 = offset1 * (pad2_height / pad1_height);

		double offset1    = 1.2;
		double offset2 = offset1 * (h2_frac / h1_frac);

		p->Draw();
		pad2->Draw();


		p->cd();
		p->SetLogx();
		p->SetLogy();

		p->SetRightMargin(0.03); //borde derecho 0
		p->SetLeftMargin(0.135); 
		//~ p->SetTopMargin(0.0409381);
		p->SetTopMargin(0.0409836);
		//~ p->SetBottomMargin(0.171);
		//~ p->SetBottomMargin(0.01);
		p->SetBottomMargin(0.0226986);
		//~ p->SetGrid();

	
		//~ c1_new->SetLogx();
		//~ c1_new->SetLogy();
		//~ h_d01->GetYaxis()->SetRangeUser(1e-07,1e+03);
		//~ h_d01->GetYaxis()->SetRangeUser(0,250);

		/*********************************/

		//~ int det_number = 1;
		int det_number = det;

	     		//~ h_d01->SetTitle("#bf{Response Functions Spectrometer CEFNEN 2024 Smooth ROOT}");
		vec_hist[det_number-1]->SetTitle("#bf{Smooth Response Functions for the CEFNEN Spectrometer}");

		vec_hist[det_number-1]->GetYaxis()->SetTitle("#bf{Response function (cm^{2})}");
		vec_hist[det_number-1]->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
		vec_hist[det_number-1]->GetXaxis()->CenterTitle(true);
		vec_hist[det_number-1]->GetYaxis()->CenterTitle(true);
		vec_hist[det_number-1]->GetXaxis()->SetRangeUser(1e-9,1e4);
		//~ vec_hist[det_number-1]->GetYaxis()->SetRangeUser(0,220);
		

		vec_hist[det_number-1]->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
		vec_hist[det_number-1]->GetYaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist[det_number-1]->GetXaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
		vec_hist[det_number-1]->GetYaxis()->SetTitleOffset(offset1);
		//~ vec_hist[det_number-1]->GetYaxis()->SetTitleOffset(1.2);
		//~ vec_hist[det_number-1]->GetXaxis()->SetTitleOffset(1.4);
		//~ vec_hist[det_number-1]->GetXaxis()->SetLabelSize(0.045);
		vec_hist[det_number-1]->GetXaxis()->SetLabelSize(0); //no label
		vec_hist[det_number-1]->GetYaxis()->SetLabelSize(0.045);
		//~ vec_hist[0]->GetYaxis()->SetMaxDigits(1);
		vec_hist[det_number-1]->SetLineWidth(4);
		//~ vec_hist[det_number-1]->SetLineWidth(6);

		//~ vec_hist[0]->SetLineColor(51);
		vec_hist[det_number-1]->SetLineColor(kRed);
	    //~ vec_hist[0]->SetLineWidth(3);
	    vec_hist[det_number-1]->Scale(0.25);  // Escalamos por 0.25, que resulta de usar un flujo isotropica de neutrones para la simulacion
		vec_hist[det_number-1]->GetYaxis()->SetRangeUser(1e-7,1e3);
	    vec_hist[det_number-1]->Draw("HIST");

	    //~ h_d16->SetLineColor(vec_colorindex[0]);



//~ for(int i=1;i<1;i++){
	     //~ vec_hist[i]->SetLineWidth(4);
	     //~ vec_hist[i]->Draw("HIST SAME");

	     vec_hist_ftfp[det_number-1]->Scale(0.25);  // Escalamos por 0.25, que resulta de usar un flujo isotropica de neutrones para la simulacion
	     vec_hist_ftfp[det_number-1]->SetLineWidth(4);
	     vec_hist_ftfp[det_number-1]->SetLineStyle(10);
	     vec_hist_ftfp[det_number-1]->SetLineColor(kBlue);
	     vec_hist_ftfp[det_number-1]->Draw("HIST SAME");
	   
//~ }


		//~ h_d01->Draw("HIST");
		//~ h_d02->Draw("HIST SAME");
		//~ h_d03->Draw("HIST SAME");
		//~ h_d04->Draw("HIST SAME");
		//~ h_d05->Draw("HIST SAME");
		//~ h_d06->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d07->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d08->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d09->Draw("HIST SAME");
		//~ h_d10->Draw("HIST SAME");
		//~ h_d11->Draw("HIST SAME");
		//~ h_d12->Draw("HIST SAME");
		//~ h_d13->Draw("HIST SAME");
		//~ h_d14->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d15->Draw("HIST SAME"); // no se considera en calculos
		//~ h_d16->Draw("HIST SAME");
		//~ h_d17->Draw("HIST SAME");

		// ---------- 2. Coordinates (NDC: 0–1, relative to pad) ----------
		double x_ndc = 0.221176;   // left edge of text box
		double y_ndc = 0.889972;   // bottom edge of text box
		double x2_ndc = 0.921156;   // box width  (adjust)
		double y2_ndc = 0.9496565;   // box height (adjust)

		// ---------- 3. Create a TPaveText that behaves like TLatex ----------
		TPaveText *box = new TPaveText(x_ndc, y_ndc, x2_ndc, y2_ndc ,"NDC");   // “NDC” → use pad-relative coords

		box->SetFillColor(kWhite);        // solid white background
		box->SetFillStyle(1001);          // 1001 = opaque
		box->SetLineColor(kWhite);        // hide border (or SetBorderSize(0))
		box->SetBorderSize(0);

		// ---------- 4. Add one (or several) LaTeX strings ----------
		//~ TText *txt = box->AddText("CEFNEN-23/24 Spectrometer Response Functions");   // TLatex markup works
		//~ TText *txt = box->AddText("CEFNEN, 16 Det. Spectrometer Response Functions");   // TLatex markup works
		TText *txt = box->AddText(vec_names[det_number-1].c_str());   // TLatex markup works

		//~ txt->SetTextFont(132);   // 132 → Computer-Modern Roman (LaTeX‐like)
		txt->SetTextSize(0.045); // relative to pad
		//~ txt->SetNDC(true);
		// ---------- 5. Draw it ----------
		box->Draw();


		//~ auto legend_new = new TLegend(0.293437,0.598277,0.452556,0.886835);
		//~ auto legend_new = new TLegend(0.185265,0.681589,0.376252,0.877049); //arrriba a la izquierda
		auto legend_new = new TLegend(0.737789,0.0990516,0.951157,0.293994); // ababjo a la derecha
	
	   legend_new->SetHeader("#bf{Detector + Physics List}","C"); // option "C" allows to center the header
	   //~ legend_new->SetTextSize(0.018);
	   //~ legend_new->AddEntry(h_d01,"#bf{E1_12cmHDPE_smooth}","l");
	   //~ legend_new->AddEntry(h_d02,"#bf{E2_2_10cm HDPE_smooth}","l");


		string det_name = std::to_string(det_number);

		TString det_qgsp = "D"+det_name+"_QGSP_BERT";
		TString det_ftfp = "D"+det_name+"_FTFP_BERT";
		
		
		//~ legend_new->SetTextSize(0.023);
		legend_new->SetTextSize(0.026);
		legend_new->AddEntry(vec_hist[det_number-1],det_qgsp,"l");
		legend_new->AddEntry(vec_hist_ftfp[det_number-1],det_ftfp,"l");

	 
	   
	   legend_new->Draw();

	   //~ c1_new->Update();

	    //~ TPad *pad2 = (TPad*)c1_new->cd(2);

		pad2->cd();
		pad2->SetLogx();

		pad2->SetRightMargin(0.03); //borde derecho 0
		pad2->SetLeftMargin(0.135); 
		//~ pad2->SetTopMargin(0.0409381);
		//~ pad2->SetTopMargin(0.01);
		//~ pad2->SetTopMargin(0.004683);
		pad2->SetTopMargin(0.028103);
		//~ pad2->SetBottomMargin(0.171);
		pad2->SetBottomMargin(0.260539);
	    
	    TH1D *resid = (TH1D*)vec_hist[det_number-1]->Clone("resid");
		resid->Add(vec_hist_ftfp[det_number-1], -1); // residual = h1 - h2
		resid->Divide(vec_hist_ftfp[det_number-1]);    // (h1 - h2)/h2
		resid->Scale(100.0);  // convert to %

		resid->SetTitle("");
		resid->GetYaxis()->SetTitle("#bf{Residuals %}");
		resid->SetLineColor(kBlack);

		double scale = h1_frac / h2_frac;

		resid->GetYaxis()->SetLabelSize(0.045 * scale);
		resid->GetYaxis()->SetTitleSize(0.05 * scale);
		
		resid->GetXaxis()->SetLabelSize(0.045 * scale);
		//~ resid->GetXaxis()->SetLabelSize(0*scale); //remove axis
		resid->GetXaxis()->SetTitleSize(0.05*scale);

		resid->GetYaxis()->SetTitleOffset(offset2);
		//~ resid->GetYaxis()->SetTitleOffset(999);


		
		//~ resid->GetYaxis()->SetTitleSize(0.07);
		//~ resid->GetYaxis()->SetLabelSize(0.05);
		//~ resid->GetXaxis()->SetTitleSize(0.12);
		//~ resid->GetXaxis()->SetLabelSize(0.05);

		
		//~ resid->GetXaxis()->SetRangeUser(1e-9,1e4);
		//~ resid->GetYaxis()->SetRangeUser(-1,1);
		resid->GetYaxis()->SetRangeUser(-0.6,0.6);
		//~ resid->GetYaxis()->SetRangeUser(-20.0,20.0);
		resid->Draw("HIST");
		
		// Draw horizontal line at 0
		TLine *line = new TLine(resid->GetXaxis()->GetXmin(), 0,
								//~ resid->GetXaxis()->GetXmax(), 0);
								1e4, 0);
		line->SetLineStyle(2);
		line->Draw("SAME");
		
	    c1_new->Draw();

	    //~ c1_new->cd();
		//~ c1_new->Update();
		
	   c1_new->SaveAs(("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_2025_IMG/RF_Spec_CEFNEN_DET"+det_name+"_Comparison.svg").c_str());
	   c1_new->SaveAs(("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_2025_IMG/RF_Spec_CEFNEN_DET"+det_name+"_Comparison.png").c_str());
	   c1_new->SaveAs(("../data/external/Response_Functions_CEFNEN_Spectrometer/RF_img/RF_2025_IMG/RF_Spec_CEFNEN_DET"+det_name+"_Comparison.pdf").c_str());
}

void Response_function_comparison_plot_loop(){

//~ for (int i=1; i<18;i++){
for (int i=1; i<17;i++){
	 Response_function_comparison_plot(i);
};

}

vector<vector<double_t> > Response_function_matrix_NM(){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/


//~ TFile *E01_file = new TFile("/home/flopez/Data/Dropbox/Tesis_doc/geant4_CEFNEN_RF_sim/Monitor-6NM64/Efi_6NM64_VV.root");
//~ TFile *E02_file = new TFile("/home/flopez/Data/Dropbox/Tesis_doc/geant4_CEFNEN_RF_sim/Efi_NM2023_VV.root");
TFile *E01_file = new TFile("/home/flopez/Data/Dropbox/DOC_WORK/Tesis_doc_misc/geant4_CEFNEN_RF_sim/Monitor-6NM64/Efi_6NM64_VV.root");
TFile *E02_file = new TFile("/home/flopez/Data/Dropbox/DOC_WORK/Tesis_doc_misc/geant4_CEFNEN_RF_sim/Efi_NM2023_VV.root");


TH1D *h_d01 = (TH1D*)E01_file->Get("fr_1");
TH1D *h_d02 = (TH1D*)E02_file->Get("ENM2023");

int binning = h_d01->GetNbinsX();
// cout << "Binning en x: " << binning << endl;

vector<double> RF_d01_vec;
vector<double> RF_d02_vec;


for(int i =0; i<binning; i++)
{
	 if(h_d01->GetBinContent(i+1)!=0.0)
		{
			 RF_d01_vec.push_back(h_d01->GetBinContent(i+1));
			  //cout << i << "  " << h_d01->GetBinContent(i+1) << endl;
			 RF_d02_vec.push_back(h_d02->GetBinContent(i+1));
	    }
	 else{
		   RF_d01_vec.push_back(1.E-23);
		   RF_d02_vec.push_back(1.E-23);
	     }
}


	 R.push_back(RF_d01_vec); 
	 R.push_back(RF_d02_vec);


E01_file->Close();
E02_file->Close();

delete E01_file;
delete E02_file;


return R;

}


void RF_CEFNEN_spectrometer_root_file(){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

/*LIN SPECTROMETER 2023*/
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

/*LIN SPECTROMETER 2023 FIX active volume*/

TFile *E01_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_1_12cmHDPE_NEW_VV.root");
TFile *E02_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_2_10cmHDPE_NEW_VV.root");
TFile *E03_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_3_4cmHDPE_NEW_VV.root");
TFile *E04_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_4_CylinderHDPE_NEW_VV.root");
TFile *E05_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_NEW_VV.root");
TFile *E06_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_6_18cmHDPE_NEW_VV.root");
TFile *E07_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_7_20cmHDPE_NEW_VV.root");
TFile *E08_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_8_1inchBHDPE_10cmHDPE_NEW_VV.root");
TFile *E09_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_9_20cmBHDPE_1.0inch_NEW_VV.root");
TFile *E10_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_10_Cylinder_4cm_NEW_VV.root");
TFile *E11_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_11_Cylinder_3cm_NEW_VV.root");
TFile *E12_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_12_Pb_10cmBHDPEcore_NEW_VV.root");
TFile *E13_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_13_1inchBHDPE_15cmGraphite_NEW_VV.root");
TFile *E14_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_14_inchBHDPE_15cmHDPE_NEW_VV.root");
TFile *E15_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_15_24cmHDPE_NEW_VV.root");
TFile *E16_file = new TFile("../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/Efi_16_Naked_1inch_NEW_VV.root");

/**************************************************/

//~ TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE");
//~ TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE");
//~ TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
//~ TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE");
//~ TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
//~ TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE");
//~ TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE");
//~ TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
//~ TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
//~ TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm");
//~ TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm");
//~ TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore");
//~ TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite");
//~ TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE");
//~ TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE");
//~ TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch");

TH1D *h_d01 = (TH1D*)E01_file->Get("E1_12cmHDPE_NEW");
TH1D *h_d02 = (TH1D*)E02_file->Get("E2_10cmHDPE_NEW");
TH1D *h_d03 = (TH1D*)E03_file->Get("E3_4cmHDPE");
TH1D *h_d04 = (TH1D*)E04_file->Get("E4_CylinderHDPE_NEW");
TH1D *h_d05 = (TH1D*)E05_file->Get("E5_Cylinder7mmAl_1.8cmBHDPECore");
TH1D *h_d06 = (TH1D*)E06_file->Get("E6_18cmHDPE_NEW");
TH1D *h_d07 = (TH1D*)E07_file->Get("E7_20cmHDPE_NEW");
TH1D *h_d08 = (TH1D*)E08_file->Get("E8_1inchBHDPE_10cmHDPE");
TH1D *h_d09 = (TH1D*)E09_file->Get("E9_20cmBHDPE_1.0inch");
TH1D *h_d10 = (TH1D*)E10_file->Get("E10_Cylinder_4cm_NEW");
TH1D *h_d11 = (TH1D*)E11_file->Get("E11_Cylinder_3cm_NEW");
TH1D *h_d12 = (TH1D*)E12_file->Get("E12_Pb_10cmBHDPEcore_NEW");
TH1D *h_d13 = (TH1D*)E13_file->Get("E13_1inchBHDPE_15cmGraphite_NEW");
TH1D *h_d14 = (TH1D*)E14_file->Get("E14_inchBHDPE_15cmHDPE_NEW");
TH1D *h_d15 = (TH1D*)E15_file->Get("E15_24cmHDPE_NEW");
TH1D *h_d16 = (TH1D*)E16_file->Get("E16_Naked_1inch_NEW");


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
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
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

df_final.Snapshot("Response_function_tree","../outputs/root/Response_function_CEFNEN_2024_fix.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


}

void RF_CEFNEN_23_FTFP_BERT_ISO_spectrometer_root_file(string physic_list, string scale_factor){
	
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/
string path;
string phylst_name;
string scale_path;

// Solo acepta "ws" o "wos"
if (scale_factor == "ws" || scale_factor == "wos") {
    scale_path = scale_factor + "_factor";
} else {
    std::cout << "scale_factor inexistente o incorrecto: " << scale_factor << "\n";
}

if(physic_list=="QGSP_BERT")
	{ path = "../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2024_active_vol_fix/"+scale_path;
	  phylst_name = "NEW";
	  cout << physic_list+" Physic_list" << endl;}
else if(physic_list=="FTFP_BERT")
	{path ="../data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/"+scale_path;
	 phylst_name = "FTFP_BERT";
	 cout << physic_list+" Physic_list" << endl;}
else{cout << "Physics list inexistente o incorrecta" << endl;}


/*LIN SPECTROMETER 2023 FIX active volume*/

TFile *E01_file = new TFile((path+"/Efi_1_12cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E02_file = new TFile((path+"/Efi_2_10cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E03_file = new TFile((path+"/Efi_3_4cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E04_file = new TFile((path+"/Efi_4_CylinderHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E05_file = new TFile((path+"/Efi_5_Cylinder7mmAl_1.8cmBHDPECore_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E06_file = new TFile((path+"/Efi_6_18cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E07_file = new TFile((path+"/Efi_7_20cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E08_file = new TFile((path+"/Efi_8_1inchBHDPE_10cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E09_file = new TFile((path+"/Efi_9_20cmBHDPE_1.0inch_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E10_file = new TFile((path+"/Efi_10_Cylinder_4cm_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E11_file = new TFile((path+"/Efi_11_Cylinder_3cm_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E12_file = new TFile((path+"/Efi_12_Pb_10cmBHDPEcore_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E13_file = new TFile((path+"/Efi_13_1inchBHDPE_15cmGraphite_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E14_file = new TFile((path+"/Efi_14_inchBHDPE_15cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E15_file = new TFile((path+"/Efi_15_24cmHDPE_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());
TFile *E16_file = new TFile((path+"/Efi_16_Naked_1inch_"+phylst_name+"_VV_smooth_smooth_root_15_"+scale_factor+".root").c_str());

/**************************************************/

TH1D *h_d01 = (TH1D*)E01_file->Get((string("E1_12cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d02 = (TH1D*)E02_file->Get((string("E2_10cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d03 = (TH1D*)E03_file->Get((string("E3_4cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d04 = (TH1D*)E04_file->Get((string("E4_CylinderHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d05 = (TH1D*)E05_file->Get((string("E5_Cylinder7mmAl_1.8cmBHDPECore_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d06 = (TH1D*)E06_file->Get((string("E6_18cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d07 = (TH1D*)E07_file->Get((string("E7_20cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d08 = (TH1D*)E08_file->Get((string("E8_1inchBHDPE_10cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d09 = (TH1D*)E09_file->Get((string("E9_20cmBHDPE_1.0inch_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d10 = (TH1D*)E10_file->Get((string("E10_Cylinder_4cm_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d11 = (TH1D*)E11_file->Get((string("E11_Cylinder_3cm_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d12 = (TH1D*)E12_file->Get((string("E12_Pb_10cmBHDPEcore_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d13 = (TH1D*)E13_file->Get((string("E13_1inchBHDPE_15cmGraphite_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d14 = (TH1D*)E14_file->Get((string("E14_inchBHDPE_15cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d15 = (TH1D*)E15_file->Get((string("E15_24cmHDPE_")+phylst_name+"_smooth_smooth_root_15").c_str());
TH1D *h_d16 = (TH1D*)E16_file->Get((string("E16_Naked_1inch_")+phylst_name+"_smooth_smooth_root_15").c_str());


int binning = h_d01->GetNbinsX();
cout << "RF N BINS: " << binning << endl;

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

cout << "RF vec size: " <<  RF_d01_vec.size() << endl;
//~ for (int j=0; j<RF_d01_vec.size();j++)
//~ {
	//~ cout << j << " " << RF_d01_vec[j] << endl;
//~ }


//~ auto seed_flux_expacs_csv ="/home/flopez/Dropbox/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
//~ auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
//~ char delimiter = ',';
//~ char double_type ='D';
//~ std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
//~ auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
//~ auto E_cut_LCO = seed_rdf.Range(0, 151, 1); // pick an event every 1 entries from 0 to 150 because the last is excluded, that is 151 .


//~ /**************Energy Bin********************/

//~ /*Seleccionamos los datos del flujo semilla para LCO*/
int bin_cut = 130;

/*ICRP binning*/
char delimiter = ',';
char double_type ='D';
string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));

//~ auto df_energy_vec = E_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ auto d_cut_entries = E_cut_LCO.Count().GetValue();
//~ cout << "Entries number of LCO seed : " << d_cut_entries << endl;


const Int_t array_size = 129;

/*Emid from icrp116*/
auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); //deja un vector de 130, (0,130,1) del 0 al 129
auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue();
auto eupper_icrp116_vec = df_icrp116_cut.Take<double>("Eupper").GetValue();

/*borde de bines como array*/
double *bins = elower_icrp116_vec.data();

cout << "emid_icrp116_vec size " << emid_icrp116_vec.size() << endl; //130
cout << "ewid_icrp116_vec size " << ewid_icrp116_vec.size() << endl; //130
cout << "elower_icrp116_vec size " << elower_icrp116_vec.size() << endl; //130
cout << "eupper_icrp116_vec size " << eupper_icrp116_vec.size() << endl; //130


ROOT::RDataFrame df_spec(130);

auto df_final = df_spec
    .Define("Energy", [&](ULong64_t i){return elower_icrp116_vec.at(i);}, {"rdfentry_"})
    .Define("Emid", [&](ULong64_t i){if (i == 129) return 0.0;return emid_icrp116_vec.at(i);}, {"rdfentry_"}) // Todo lo demás: copiar 0..128 y forzar 0 en i=129
    .Define("Ewid", [&](ULong64_t i){if (i == 129) return 0.0;return ewid_icrp116_vec.at(i);}, {"rdfentry_"})
    .Define("RF_01", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d01_vec.at(i); }, {"rdfentry_"})
    .Define("RF_02", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d02_vec.at(i); }, {"rdfentry_"})
    .Define("RF_03", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d03_vec.at(i); }, {"rdfentry_"})
    .Define("RF_04", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d04_vec.at(i); }, {"rdfentry_"})
    .Define("RF_05", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d05_vec.at(i); }, {"rdfentry_"})
    .Define("RF_06", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d06_vec.at(i); }, {"rdfentry_"})
    .Define("RF_07", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d07_vec.at(i); }, {"rdfentry_"})
    .Define("RF_08", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d08_vec.at(i); }, {"rdfentry_"})
    .Define("RF_09", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d09_vec.at(i); }, {"rdfentry_"})
    .Define("RF_10", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d10_vec.at(i); }, {"rdfentry_"})
    .Define("RF_11", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d11_vec.at(i); }, {"rdfentry_"})
    .Define("RF_12", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d12_vec.at(i); }, {"rdfentry_"})
    .Define("RF_13", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d13_vec.at(i); }, {"rdfentry_"})
    .Define("RF_14", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d14_vec.at(i); }, {"rdfentry_"})
    .Define("RF_15", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d15_vec.at(i); }, {"rdfentry_"})
    .Define("RF_16", [&](ULong64_t i){ return (i == 129) ? 0.0 : RF_d16_vec.at(i); }, {"rdfentry_"});




df_final.Snapshot("Response_Function_CEFNEN_tree","../outputs/root/Response_Function_CEFNEN_Spectrometer.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


}


vector<vector<double_t> > Response_function_matrix_fm()
{
vector< vector<Double_t>> R; /*matriz de eficiencias absolutas (viene de la funcion respuesta)*/

/**Generamos archivos .root de cada csv file de funcion respuesta**/
string path_files = "../data/external/Response_Functions_CEFNEN_Spectrometer/old_fm/csv_files/";
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
/**Funcion que calcula el Resolving Power del espectrometro**/
void BackusGilbert_ResolutionPower(string campaign){

     //~ int n; // Número de detectores
    //~ const int m = 150; // Número de puntos de discretización para la integral
    //~ double Eo; // Energía a evaluar en MeV
	//~ std::cout << "Ingrese el valor de E0 en MeV: ";
    //~ std::cin >> Eo;
    // Leer los valores de energía y calcular J(Eo, E)
    //~ std::ifstream inputFile("binning_150.lst");
    //~ if (!inputFile.is_open()) {
        //~ std::cerr << "Error: No se pudo abrir el archivo 'binning_150.lst'" << std::endl;
        //~ // return 1;
    //~ }

	int ndet = 16; /*numero de detectores*/
	vector< vector<Double_t>> R;   /*matriz de funciones respuesta del espectrometro*/
	vector< vector<Double_t>> RjValues;   /*matriz de funciones respuesta del espectrometro reducida*/
	vector<Double_t> N(ndet,0); /*vector de neutrones medidos*/

    int n; // Número de detectores
    //~ const int m = 150; // Número de puntos de discretización para la integral
    const int m = 130; // Número de puntos de discretización para la integral
    //~ const int m = 129; // Número de puntos de discretización para la integral
    double Eo; // Energía a evaluar en MeV
	std::cout << "Ingrese el valor de E0 en MeV: ";
    std::cin >> Eo;
   
    
     //Leemos el bineado de energias
    std::vector<double> energies,dLethargy;
    std::vector<double> J;
    //~ double energy;
    //~ while (inputFile >> energy) {
        //~ energies.push_back(energy);
        //~ J.push_back(std::pow(std::log10(energy) - std::log10(Eo), 2));
    //~ }
    //~ inputFile.close();

 	/****CARGAMOS EL BINEADO ICRP116**********/
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	int bin_cut = 130;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue(); //130 size
	/**************Energy Bin********************/

	for(int i=0;i<m;i++){
         //~ J.push_back(std::pow(std::log10(energy) - std::log10(Eo), 2));
         J.push_back(std::pow(std::log10(elower_icrp116_vec[i]) - std::log10(Eo), 2));
		}


    
    //~ double* energiesArray = &energies[0]; 
    double* energiesArray = &elower_icrp116_vec[0];
    /*borde de bines como array*/
	//~ double *bins = B.data();
	//~ double *energiesArray = elower_icrp116_vec.data();
    std::stringstream numero;
    numero << Eo;
    std::string numeronotacioncientifica = numero.str();
    TFile *archivo = new TFile("../outputs/root/histogramas2.root", "RECREATE");
	if (!archivo || archivo->IsZombie()) {
		std::cerr << "File 'histogramas2.root' is a zombie or could not be opened.\n";
		return;
	}
	std::cout << "'histogramas2.root' opened OK.\n";
	archivo->cd();
	
    TString nombreHistograma = "histoA"+ numeronotacioncientifica; // Genera nombres únicos
    TH1D *histograma = new TH1D(nombreHistograma, "Histograma",m-1, energiesArray);
	histograma->SetDirectory(archivo);  // Ensure it belongs to that TFile
    
    for(int i =1;i<m;i++){
		//~ dLethargy.push_back(std::log10(energies[i]) - std::log10(energies[i-1]));
		dLethargy.push_back(std::log10(elower_icrp116_vec[i]) - std::log10(elower_icrp116_vec[i-1]));
		//std::cout<<energies[i]<<" "<<std::log10(energies[i]) - std::log10(energies[i-1])<<std::endl;
		}


/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024 region activa arreglada y mas estadistica, considerando el nuevo detecto d04*/
cout << "Cargamos la matriz de funcion respuesta" << endl;
//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","ws","iso",campaign);  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 


//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15) SanPedro y Chapiquilta*/ 
cout << "Response Function matrix filled: R " << endl;

/**Reducimos el tamanio de la matriz**/
//~ for(int i=0; i<R.size();i++){
	//~ vector<double> rf_ch_new(m-1,0);
	//~ for(int j=0; j<m;j++){
		//~ rf_ch_new.push_back(R[i][j]);
	//~ }

	//~ RjValues.push_back(rf_ch_new);
//~ }

RjValues = R;

/****************ACTIVACION/DESACTIVACION DE DETECTORES*************/

vector< vector<Double_t>> RjValues_new;   /*matriz de funciones respuesta del espectrometro redefinida*/


vector<string> det_names{"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13","D14","D15","D16"}; /*vector de nombres de detectores activados*/
vector<string> det_names_act;

// vector<int> act_vector(ndet,1);

// vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //Todos los detectores activados
const auto& vec_test = Detectors_Array("AllActive");

//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, MARICUNGA, RETEN DESIERTO

//~ vector<int> vec_test{1,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba

//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  San Pedro / Chapiquilta tes2

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			RjValues_new.push_back(RjValues[i]);
		}
	else{}
}

/*Redefinimos Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = RjValues_new.size();
ndet = ndet_new;

/*Redefinimos R*/
RjValues =  RjValues_new;

    // Vector para almacenar los nombres de los archivos de datos
    //~ std::vector<std::string> dataFiles;

    // Leer la lista de nombres de archivos desde el archivo "file_list.txt"
   // std::ifstream fileList("file_list.txt");
    //~ std::ifstream fileList("new_file_list.txt");
    //~ if (!fileList.is_open()) {
        //~ std::cerr << "Error: No se pudo abrir el archivo 'new_file_list.txt'" << std::endl;
        //~ // return 1;
    //~ }
 //~ int ii=0;
    //~ std::string fileName;
    //~ while (std::getline(fileList, fileName)) {
        //~ dataFiles.push_back(fileName);
    
        //~ ii++;
    //~ }
    //~ fileList.close();

/*Redefinimos N*/
 n=ndet;
 
    // Crear una matriz de vectores para almacenar los valores de R_j
    //~ std::vector<std::vector<double>> RjValues(n, std::vector<double>(m)), dE(n, std::vector<double>(m));

    // Leer los datos de cada archivo y llenar los vectores R_j
    //~ for (int j = 0; j < n; j++) {
        //~ // Abrir el archivo de datos para el detector j
        //~ std::ifstream dataFile(dataFiles[j]);
        //~ if (!dataFile.is_open()) {
            //~ std::cerr << "Error: No se pudo abrir el archivo de datos '" << dataFiles[j] << "'" << std::endl;
            //~ //~return 1;
        //~ }

        //~ double value1, value2, value3;
        //~ int i = 0;
        //~ while (dataFile >> value1 >> value2) {
            //~ RjValues[j][i] = value2;
            //~ dE[j][i]= value2;
            //~ i++;
        //~ }
        //~ dataFile.close();
    //~ }

/*****************************************************************************************/
/**********************************CALCULOS**********************************************/

    // Matriz de coeficientes A y vector B
    TMatrixD A(n+1, n+1);
    TVectorD B(n+1); // Añadimos 1 para la restricción de la ecuación 2

    // Llenar la matriz A
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int i = 0; i < m; i++) {
                sum += J[i] * RjValues[j][i] * RjValues[k][i];
                               
            }
           //~ std::cout<<k<<", "<<j<<" "<<sum<<std::endl;
            A(k, j) = sum;
            
        }
        

        double sumB = 0.0;
        for (int i = 0; i < m; i++) {
            sumB += RjValues[k][i];
        }
        B[k] = -sumB;
        A(k,n) = sumB;
    }

    // Agregar la restricción de la ecuación 2
    for (int j = 0; j < n; j++) {
        double sumRj = 0.0;
        for (int i = 0; i < m; i++) {
            sumRj += RjValues[j][i];
        }
       //  std::cout<<n<<", "<<j<<" "<<sumRj<<std::endl;
        A(n, j) = sumRj;
    }

    // Valor objetivo para la restricción de la ecuación 2 (debe ser igual a 1)
    double constraintValue = 1.0;
    B[n] = constraintValue;
    B[n+1] = 0;
    

    // Resolución del sistema de ecuaciones utilizando la descomposición SVD
    TDecompSVD svd(A);
    Bool_t ok; // Variable para verificar si la solución es exitosa
    TVectorD solution = svd.Solve(B, ok);

	for(int i=0;i<16;i++){

	cout << "solution[k] " << i << " " <<   solution[i] << endl;
	}
    if (!ok) {
        std::cerr << "Error: La descomposición SVD no pudo encontrar una solución." << std::endl;
        //~ return 1;
    }

    // Imprimir los coeficientes a_k
    std::cout << "Coeficientes a_k:" << std::endl;
    double sumA = 0.0;
    double L = 0.0;
    double DL =0.0;
for (int k = 0; k < n; k++) {
    double sumP = 0.0;
     double sumL = 0.0;
    
    std::cout << "a_" << k << ": " << solution[k] << std::endl;
    for (int i = 0; i < m; i++) {
        sumP += RjValues[k][i];
        sumL += RjValues[k][i]*std::log10(elower_icrp116_vec[i]);
        //~ cout << "elower_icrp116_vec[i] : " <<  i << " " << elower_icrp116_vec[i] << " " <<std::log10(elower_icrp116_vec[i])  << endl;
        cout << "i" << i << "sumP=" << sumP << "sumL=" << sumL << "RjValues[k][i] " << RjValues[k][i] << endl; 
    }

    sumA += sumP * solution[k];
    L += sumL*solution[k];
}

for (int k = 0; k < n; k++) {
	 double sumDL = 0.0;
	 for (int i = 0; i < m; i++) {
		  sumDL += RjValues[k][i]*std::pow(std::log10(elower_icrp116_vec[i])-L,2);
	 }
	 DL+= sumDL*solution[k];
}
    
    
std::cout << "Lambda: " << solution[n] << std::endl;
std::cout << "Unity of a_k: " << sumA << std::endl;
std::cout << "L: " << L << std::endl;
std::cout << "DL: " << std::sqrt(DL) << std::endl;

  
for (int i = 0; i < m; i++) {
	 double sumAEo = 0.0;
	 for (int k = 0; k < n; k++) {
		  sumAEo += RjValues[k][i]*solution[k];
	 }
	 histograma->SetBinContent(i+1,sumAEo);
}

//~ histograma->Write();
//~ histograma->GetMean();
//~ histograma->GetRMS();
cout<< "MEAN: " << histograma->GetMean() << " RMS: " << histograma->GetRMS() <<endl;
histograma->Draw();
//~ archivo->Close();


    //~ return 0;
}

TH1D* BackusGilbert_ResolutionPower_TH1D(double Eo_input, string campaign){
     //~ int n; // Número de detectores
    //~ const int m = 150; // Número de puntos de discretización para la integral
    //~ double Eo; // Energía a evaluar en MeV
	//~ std::cout << "Ingrese el valor de E0 en MeV: ";
    //~ std::cin >> Eo;
    // Leer los valores de energía y calcular J(Eo, E)
    //~ std::ifstream inputFile("binning_150.lst");
    //~ if (!inputFile.is_open()) {
        //~ std::cerr << "Error: No se pudo abrir el archivo 'binning_150.lst'" << std::endl;
        //~ // return 1;
    //~ }

	int ndet = 16; /*numero de detectores*/
	vector< vector<Double_t>> R;   /*matriz de funciones respuesta del espectrometro*/
	vector< vector<Double_t>> RjValues;   /*matriz de funciones respuesta del espectrometro reducida*/
	vector<Double_t> N(ndet,0); /*vector de neutrones medidos*/

    int n; // Número de detectores
    //~ const int m = 150; // Número de puntos de discretización para la integral
    //~ const int m = 130; // Número de puntos de discretización para la integral
    const int m = 131; // Número de puntos de discretización para la integral
    //~ const int m = 129; // Número de puntos de discretización para la integral
    double Eo = Eo_input; // Energía a evaluar en MeV
	//~ std::cout << "Ingrese el valor de E0 en MeV: ";
    //~ std::cin >> Eo;
   
    
     //Leemos el bineado de energias
    std::vector<double> energies,dLethargy;
    std::vector<double> J;
    //~ double energy;
    //~ while (inputFile >> energy) {
        //~ energies.push_back(energy);
        //~ J.push_back(std::pow(std::log10(energy) - std::log10(Eo), 2));
    //~ }
    //~ inputFile.close();

 	/****CARGAMOS EL BINEADO ICRP116**********/
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	//~ int bin_cut = 130;
	int bin_cut = 131;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue(); //130 size
	/**************Energy Bin********************/

	//Bordes de bin: 130
	for(int i=0;i<m;i++){
         //~ J.push_back(std::pow(std::log10(energy) - std::log10(Eo), 2));
         J.push_back(std::pow(std::log10(elower_icrp116_vec[i]) - std::log10(Eo), 2));
		}


    
    //~ double* energiesArray = &energies[0]; 
    double* energiesArray = &elower_icrp116_vec[0];
    /*borde de bines como array*/
	//~ double *bins = B.data();
	//~ double *energiesArray = elower_icrp116_vec.data();
    std::stringstream numero;
    numero << Eo;
    std::string numeronotacioncientifica = numero.str();
    TFile *archivo = new TFile("../outputs/root/histogramas2.root", "RECREATE");
	if (!archivo || archivo->IsZombie()) {
		std::cerr << "File 'histogramas2.root' is a zombie or could not be opened.\n";
		//~ return;
	}
	std::cout << "'histogramas2.root' opened OK.\n";
	archivo->cd();
	
    TString nombreHistograma = "histoA"+ numeronotacioncientifica; // Genera nombres únicos
    TH1D *histograma = new TH1D(nombreHistograma, "Histograma",m-1, energiesArray);
	histograma->SetDirectory(archivo);  // Ensure it belongs to that TFile

    //Binnum o anchos de bin: 129
    for(int i =1;i<m;i++){
		//~ dLethargy.push_back(std::log10(energies[i]) - std::log10(energies[i-1]));
		dLethargy.push_back(std::log10(elower_icrp116_vec[i]) - std::log10(elower_icrp116_vec[i-1]));
		//std::cout<<energies[i]<<" "<<std::log10(energies[i]) - std::log10(energies[i-1])<<std::endl;
		}


/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024 region activa arreglada y mas estadistica, considerando el nuevo detecto d04*/
cout << "Cargamos la matriz de funcion respuesta" << endl;
//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","ws","iso",campaign);  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 


//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15) SanPedro y Chapiquilta*/ 
cout << "Response Function matrix filled: R " << endl;

/**Reducimos el tamanio de la matriz**/
//~ for(int i=0; i<R.size();i++){
	//~ vector<double> rf_ch_new(m-1,0);
	//~ for(int j=0; j<m;j++){
		//~ rf_ch_new.push_back(R[i][j]);
	//~ }

	//~ RjValues.push_back(rf_ch_new);
//~ }

RjValues = R;

/****************ACTIVACION/DESACTIVACION DE DETECTORES*************/

vector< vector<Double_t>> RjValues_new;   /*matriz de funciones respuesta del espectrometro redefinida*/


vector<string> det_names{"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13","D14","D15","D16"}; /*vector de nombres de detectores activados*/
vector<string> det_names_act;

// vector<int> act_vector(ndet,1);

//  vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //Todos los detectores activados
const auto& vec_test = Detectors_Array("AllActive");

// vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, MARICUNGA, RETEN DESIERTO

//~ vector<int> vec_test{1,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba

//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  San Pedro / Chapiquilta tes2

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			RjValues_new.push_back(RjValues[i]);
		}
	else{}
}

/*Redefinimos Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = RjValues_new.size();
ndet = ndet_new;

/*Redefinimos R*/
RjValues =  RjValues_new;

    // Vector para almacenar los nombres de los archivos de datos
    //~ std::vector<std::string> dataFiles;

    // Leer la lista de nombres de archivos desde el archivo "file_list.txt"
   // std::ifstream fileList("file_list.txt");
    //~ std::ifstream fileList("new_file_list.txt");
    //~ if (!fileList.is_open()) {
        //~ std::cerr << "Error: No se pudo abrir el archivo 'new_file_list.txt'" << std::endl;
        //~ // return 1;
    //~ }
 //~ int ii=0;
    //~ std::string fileName;
    //~ while (std::getline(fileList, fileName)) {
        //~ dataFiles.push_back(fileName);
    
        //~ ii++;
    //~ }
    //~ fileList.close();

/*Redefinimos N*/
 n=ndet;
 
    // Crear una matriz de vectores para almacenar los valores de R_j
    //~ std::vector<std::vector<double>> RjValues(n, std::vector<double>(m)), dE(n, std::vector<double>(m));

    // Leer los datos de cada archivo y llenar los vectores R_j
    //~ for (int j = 0; j < n; j++) {
        //~ // Abrir el archivo de datos para el detector j
        //~ std::ifstream dataFile(dataFiles[j]);
        //~ if (!dataFile.is_open()) {
            //~ std::cerr << "Error: No se pudo abrir el archivo de datos '" << dataFiles[j] << "'" << std::endl;
            //~ //~return 1;
        //~ }

        //~ double value1, value2, value3;
        //~ int i = 0;
        //~ while (dataFile >> value1 >> value2) {
            //~ RjValues[j][i] = value2;
            //~ dE[j][i]= value2;
            //~ i++;
        //~ }
        //~ dataFile.close();
    //~ }

/*****************************************************************************************/
/**********************************CALCULOS**********************************************/

    // Matriz de coeficientes A y vector B
    TMatrixD A(n+1, n+1);
    TVectorD B(n+1); // Añadimos 1 para la restricción de la ecuación 2

    // Llenar la matriz A
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int i = 0; i < m; i++) {
                sum += J[i] * RjValues[j][i] * RjValues[k][i];
                               
            }
           //~ std::cout<<k<<", "<<j<<" "<<sum<<std::endl;
            A(k, j) = sum;
            
        }
        

        double sumB = 0.0;
        for (int i = 0; i < m; i++) {
            sumB += RjValues[k][i];
        }
        B[k] = -sumB;
        A(k,n) = sumB;
    }

    // Agregar la restricción de la ecuación 2
    for (int j = 0; j < n; j++) {
        double sumRj = 0.0;
        for (int i = 0; i < m; i++) {
            sumRj += RjValues[j][i];
        }
       //  std::cout<<n<<", "<<j<<" "<<sumRj<<std::endl;
        A(n, j) = sumRj;
    }

    // Valor objetivo para la restricción de la ecuación 2 (debe ser igual a 1)
    double constraintValue = 1.0;
    B[n] = constraintValue;
    //~ B[n+1] = 0;
    

    // Resolución del sistema de ecuaciones utilizando la descomposición SVD
    TDecompSVD svd(A);
    Bool_t ok; // Variable para verificar si la solución es exitosa
    TVectorD solution = svd.Solve(B, ok);

	for(int i=0;i<16;i++){

	//~ cout << "solution[k] " << i << " " <<   solution[i] << endl;
	}
    if (!ok) {
        std::cerr << "Error: La descomposición SVD no pudo encontrar una solución." << std::endl;
        //~ return 1;
    }

    // Imprimir los coeficientes a_k
    std::cout << "Coeficientes a_k:" << std::endl;
    double sumA = 0.0;
    double L = 0.0;
    double DL =0.0;
for (int k = 0; k < n; k++) {
    double sumP = 0.0;
     double sumL = 0.0;
    
    std::cout << "a_" << k << ": " << solution[k] << std::endl;
    for (int i = 0; i < m; i++) {
        sumP += RjValues[k][i];
        sumL += RjValues[k][i]*std::log10(elower_icrp116_vec[i]);
        //~ cout << "elower_icrp116_vec[i] : " <<  i << " " << elower_icrp116_vec[i] << " " <<std::log10(elower_icrp116_vec[i])  << endl;
        //~ cout << "i" << i << "sumP=" << sumP << "sumL=" << sumL << "RjValues[k][i] " << RjValues[k][i] << endl; 
    }

    sumA += sumP * solution[k];
    L += sumL*solution[k];
}

for (int k = 0; k < n; k++) {
	 double sumDL = 0.0;
	 for (int i = 0; i < m; i++) {
		  sumDL += RjValues[k][i]*std::pow(std::log10(elower_icrp116_vec[i])-L,2);
	 }
	 DL+= sumDL*solution[k];
}
    
    
std::cout << "Lambda: " << solution[n] << std::endl;
std::cout << "Unity of a_k: " << sumA << std::endl;
std::cout << "L: " << L << std::endl;
std::cout << "DL: " << std::sqrt(DL) << std::endl;

  
for (int i = 0; i < m; i++) {
	 double sumAEo = 0.0;
	 for (int k = 0; k < n; k++) {
		  sumAEo += RjValues[k][i]*solution[k];
	 }
	 histograma->SetBinContent(i+1,sumAEo);
}

//~ histograma->Write();
//~ histograma->GetMean();
//~ histograma->GetRMS();
//~ cout<< "MEAN: " << histograma->GetMean() << " RMS: " << histograma->GetRMS() <<endl;

//~ histograma->Draw();

return histograma;

//~ cout << "Integral: " <<  histograma->Integral() << endl;
archivo->Close();

    //~ return 0;
}

void drawHistograms_ResolvingPower(string campaign){
    // Abre el archivo ROOT
    //~ TFile* rootFile = new TFile(rootFileName);

    // Verifica si el archivo se abrió correctamente
    //~ if (!rootFile || rootFile->IsZombie()) {
        //~ std::cout << "Error: No se pudo abrir el archivo ROOT." << std::endl;
        //~ return;
    //~ }

    // Nombres de los histogramas y sus colores correspondientes
    const char* histogramNames[] = {
        "histoA1e-08", "histoA1e-07", "histoA1e-06", "histoA1e-05",
        "histoA0.0001", "histoA0.001", "histoA0.01", "histoA0.1",
        "histoA1", "histoA10", "histoA100", "histoA1000"
    };
    const int colors[] = {kGreen, kBlue, kRed, kBlack, kGreen, kBlue, kRed, kBlack, kGreen, kBlue, kRed, kBlack};

    // Crea un canvas con escala logarítmica en X
	//~ TCanvas* canvas = new TCanvas("canvas", "Histogramas", 1400, 800);
	TCanvas* canvas = new TCanvas("canvas", "Histogramas", 1400, 1000);
	canvas->SetSupportGL(true);
	gStyle->SetCanvasPreferGL(kTRUE);
	gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

    canvas->Divide(1,1);
    

    // --- Work on the first (and only) pad ---
	TPad *p = (TPad*)canvas->cd(1);
	p->SetLogx();
	p->SetGrid();

	p->SetRightMargin(0.03); //borde derecho 0
	p->SetLeftMargin(0.125); 
	p->SetTopMargin(0.0409381);
	p->SetBottomMargin(0.1401);
	

//Calculamos el Resolving Powerpor decadade energia
	vector<TH1D*> vec_resolving_hist;
	int n_decades= 12;

	for(int i=0; i<n_decades; i++){
			double dec = pow(10,i-8);
			vec_resolving_hist.push_back(BackusGilbert_ResolutionPower_TH1D(dec,campaign));
			cout << "Integral: " <<  vec_resolving_hist[i]->Integral() << endl;
	}


	// 1. Loop to find the maximum of all histograms.
	double globalMax = 0.0;
	for (int i = 0; i < n_decades; i++){
		double thisMax = vec_resolving_hist[i]->GetMaximum();
		if (thisMax > globalMax) {
			globalMax = thisMax;
		}
	}

// We’ll scale it up so the top of the frame is higher than any individual maximum.
double yAxisMax = 1.15 * globalMax;


/*********************************/

// Crea una paleta de colores arcoíris
//~ int nColors = 256; // Puedes ajustar este valor según tus necesidades
//~ int nColors = 501; // Puedes ajustar este valor según tus necesidades
int nColors = n_decades; // Puedes ajustar este valor según tus necesidades
double stops[nColors];
double red[nColors];
double green[nColors];
double blue[nColors];

for (int i = 0; i < nColors; i++) {
    stops[i] = (double)i / (nColors - 1);
    red[i] = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
    green[i] = TMath::Sqrt(stops[i]);
    blue[i] = 1.0 - stops[i];
}

//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 255);
//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 500);
int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, n_decades);

//~ double n_hist = chi2_hist_vec.size();
double n_hist = n_decades;
double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
TColor::InvertPalette();

//~ for(int j=1;j<501;j++){

	//~ int colorIndex = static_cast<int>(j*step);
    //~ // int colorIndex2 = 51 + colorIndex * 48 / 256;
    //~ int colorIndex2 = 51 + colorIndex * 48 /501;
    //~ chi2_hist_vec[j]->SetLineColor(colorIndex2);
	//~ chi2_hist_vec[j]->Draw("HIST SAME");

//~ }

// 2. Set the y-axis range on whichever histogram you draw first.
vec_resolving_hist[0]->GetXaxis()->SetRangeUser(1e-9,1e4);
vec_resolving_hist[0]->SetMinimum(-0.005);
vec_resolving_hist[0]->SetStats(0);
vec_resolving_hist[0]->SetMaximum(yAxisMax);
//~ vec_resolving_hist[0]->SetTitle("Average Kernel A(E_{0},E) for CEFNEN Spectrometer"); // Cambia "Título del Histograma" al título deseado
vec_resolving_hist[0]->SetTitle(" "); // Cambia "Título del Histograma" al título deseado
vec_resolving_hist[0]->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}"); // Cambia "Título del Eje X" al título deseado para el eje X
vec_resolving_hist[0]->GetYaxis()->SetTitle("#bf{A(E_{0},E)}"); // Cambia "Título del Eje Y" al título deseado para el eje Y
vec_resolving_hist[0]->GetYaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
vec_resolving_hist[0]->GetXaxis()->SetTitleSize(0.05); // Cambia "Título del Eje Y" al título deseado para el eje Y
vec_resolving_hist[0]->GetYaxis()->SetTitleOffset(1.2);
vec_resolving_hist[0]->GetXaxis()->SetTitleOffset(1.4);
vec_resolving_hist[0]->GetXaxis()->SetLabelSize(0.05);
vec_resolving_hist[0]->GetYaxis()->SetLabelSize(0.05);
vec_resolving_hist[0]->GetXaxis()->CenterTitle(true);
vec_resolving_hist[0]->GetYaxis()->CenterTitle(true);
//~ vec_resolving_hist[0]->SetLineColor(colors[0]);
//~ vec_resolving_hist[0]->GetYaxis()->SetMaxDigits(1);
vec_resolving_hist[0]->SetLineColor(51);
//~ vec_resolving_hist[0]->SetLineWidth(2);
vec_resolving_hist[0]->SetLineWidth(4);
vec_resolving_hist[0]->Draw("HIST");


    // Dibuja los histogramas
    for (int i = 1; i < 12; i++) {
        //~ TH1D* histo = (TH1D*)rootFile->Get(histogramNames[i]);
        //~ TH1D* histo = (TH1D*)rootFile->Get(histogramNames[i]);
        //~ if (!histo) {
            //~ std::cerr << "Error: No se pudo encontrar el histograma '" << histogramNames[i] << "' en el archivo ROOT." << std::endl;
            //~ return;
        //~ }

		vec_resolving_hist[i]->SetTitle("Average Kernel A(E_{0},E) for CEFNEN Spectrometer"); // Cambia "Título del Histograma" al título deseado
		vec_resolving_hist[i]->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}"); // Cambia "Título del Eje X" al título deseado para el eje X
		vec_resolving_hist[i]->GetYaxis()->SetTitle("#bf{A(E_{0},E)}"); // Cambia "Título del Eje Y" al título deseado para el eje Y
		//~ vec_resolving_hist[i]->SetLineColor(colors[i]);

		int colorIndex = static_cast<int>(i*step);
		// int colorIndex2 = 51 + colorIndex * 48 / 256;
		// int colorIndex2 = 51 + colorIndex * 48 /501;
		int colorIndex2 = 51 + colorIndex * 48 /n_decades;
		vec_resolving_hist[i]->SetLineColor(colorIndex2);
		
		//~ vec_resolving_hist[i]->SetLineWidth(2);
		vec_resolving_hist[i]->SetLineWidth(4);
		//~ vec_resolving_hist[i]->Draw((i == 0) ? "HIST" : "HIST SAME");
		vec_resolving_hist[i]->Draw("HIST SAME");
          // Elimina el TPaveStats (estadísticas en el canvas)

              TVirtualPad* statsPad = (TVirtualPad*)canvas->GetPrimitive("stats");
    if (statsPad) {
        statsPad->SetFillColor(0);
        statsPad->SetBorderSize(0);
        canvas->Modified();
    }
 }


double xvec[2] ={10.0,10.0};
double yvec[2] ={0,yAxisMax};


TGraph *tenMeV_valley = new TGraph(2,xvec,yvec);
tenMeV_valley->SetMarkerStyle(21);
//~ gr_median->SetLineStyle(7);
//~ gr_media->SetLineStyle(9);
tenMeV_valley->SetLineWidth(2);
tenMeV_valley->SetLineColor(kMagenta);

//~ tenMeV_valley->Draw("L SAME"); // Linea vertical en 10 MeV 

//~ canvas->Update();

        // Encuentra el valor máximo en el histograma
        //~ double maxY = vec_resolving_hist[i]->GetMaximum();
        //~ double maxX = vec_resolving_hist[i]->GetXaxis()->GetBinCenter(vec_resolving_hist[i]->GetMaximumBin());

        // Convierte las coordenadas del histograma a las coordenadas logarítmicas del canvas
        //~ double canvasX = maxX;
        //~ double canvasY = maxY+0.0006;
        //~ std:cout<<maxX<<","<<maxY<<std::endl;
        // Calcula las coordenadas logarítmicas para la anotación cerca de la parte superior del histograma
        //~ double annotationX = canvasX;
        //~ double annotationY = canvasY;

        //~ const char* annotationText[] = {
            //~ "10^{-8}", "10^{-7}", "10^{-6}", "10^{-5}",
            //~ "10^{-4}", "10^{-3}", "10^{-2}", "10^{-1}",
            //~ "10^{0}", "10^{1}", "10^{2}", "10^{3}"
        //~ };

        // Agrega una anotación con el valor máximo cerca de la parte superior de la curva
        //~ TLatex latex;
        //~ latex.SetTextSize(0.03);
        //~ latex.SetTextColor(colors[i]);
        //~ latex.SetTextAlign(22); // Alineación centrada
        //~ latex.DrawLatex(annotationX, annotationY, annotationText[i]);
    //~ }
 //~ TVirtualPad* statsPad = (TVirtualPad*)canvas->GetPrimitive("stats");
    //~ if (statsPad) {
        //~ statsPad->SetFillColor(0);
        //~ statsPad->SetBorderSize(0);
        //~ canvas->Modified();
    //~ }

for (int i = 0; i < n_decades; i++) {
    // Find the x-position of the max for this histogram
    double maxBinCenter = vec_resolving_hist[i]->GetXaxis()->GetBinCenter(
                              vec_resolving_hist[i]->GetMaximumBin()
                          );
    // Get the y-value at that max bin
    double maxBinValue  = vec_resolving_hist[i]->GetMaximum();

    // Add a small offset so the text appears just above the peak
    double offset = 0.04 * globalMax; // for example
    double annotationX = maxBinCenter;
    double annotationY = maxBinValue + offset;

    const char* annotationText[] = {
            "10^{-8}", "10^{-7}", "10^{-6}", "10^{-5}",
            "10^{-4}", "10^{-3}", "10^{-2}", "10^{-1}",
            "10^{0}", "10^{1}", "10^{2}", "10^{3}"
        };

	int colorIndex = static_cast<int>(i*step);
	// int colorIndex2 = 51 + colorIndex * 48 / 256;
	// int colorIndex2 = 51 + colorIndex * 48 /501;
	int colorIndex2 = 51 + colorIndex * 48 /n_decades;
	//~ vec_resolving_hist[i]->SetLineColor(colorIndex2);

    TLatex latex;
    //~ latex.SetTextSize(0.03);
    latex.SetTextSize(0.05);
    //~ latex.SetTextColor(colors[i]);
    latex.SetTextColor(colorIndex2);
    latex.SetTextAlign(22);
    latex.DrawLatex(annotationX, annotationY, annotationText[i]);
}

//~ TLatex *RP_name = new TLatex(0.25,0.91,"#bf{CEFNEN-24 Spectrometer Resolving Power}"); // Chapiquilta

//~ RP_name->SetTextColor(kBlack);
//~ RP_name->SetNDC(true);
//~ RP_name->SetTextSize(0.05);
//~ RP_name->Draw("SAME");

// ---------- 2. Coordinates (NDC: 0–1, relative to pad) ----------
//~ double x_ndc = 0.225555;   // left edge of text box
//~ double y_ndc = 0.896245;   // bottom edge of text box
//~ double x2_ndc = 0.862033;   // box width  (adjust)
//~ double y2_ndc = 0.955838;   // box height (adjust)
double x_ndc = 0.208038;   // left edge of text box
double y_ndc = 0.891017;   // bottom edge of text box
double x2_ndc = 0.88831;   // box width  (adjust)
double y2_ndc = 0.950611;   // box height (adjust)

// ---------- 3. Create a TPaveText that behaves like TLatex ----------
TPaveText *box = new TPaveText(x_ndc, y_ndc, x2_ndc, y2_ndc ,"NDC");   // “NDC” → use pad-relative coords

box->SetFillColor(kWhite);        // solid white background
box->SetFillStyle(1001);          // 1001 = opaque
box->SetLineColor(kWhite);        // hide border (or SetBorderSize(0))
box->SetBorderSize(0);

// ---------- 4. Add one (or several) LaTeX strings ----------
//~ TText *txt = box->AddText("CEFNEN-24 Spectrometer Resolving Power");   // TLatex markup works
// TText *txt = box->AddText("CEFNEN, 11 Det Spectrometer Resolving Power");   // TLatex markup works
TText *txt = box->AddText("CEFNEN, 16 Det Spectrometer Resolving Power");   // TLatex markup works
//~ txt->SetTextFont(132);   // 132 → Computer-Modern Roman (LaTeX‐like)
txt->SetTextSize(0.045); // relative to pad
//~ txt->SetNDC(true);
// ---------- 5. Draw it ----------
box->Draw();

    // Muestra el canvas
    canvas->Draw();
    //~ canvas->SaveAs("./ResolvingPower_16det_LCO.pdf");
    //~ canvas->SaveAs("./ResolvingPower_16det_LCO.png");
    //~ canvas->SaveAs("./ResolvingPower_11det_LCO_MSF.pdf");
    //~ canvas->SaveAs("./ResolvingPower_11det_LCO_MSF.png");

    //~ canvas->SaveAs("./ResolvingPower_16det_SPA_CHA.pdf");
    //~ canvas->SaveAs("./ResolvingPower_16det_SPA_CHA.png");

        
     canvas->SaveAs("../outputs/pdf/deconv_data_pdf/ResolvingPower/ResolvingPower_16det_LCO_MAR_FTFP_BERT.pdf");
     canvas->SaveAs("../outputs/pdf/deconv_data_pdf/ResolvingPower/ResolvingPower_16det_LCO_MAR_FTFP_BERT.png");
     canvas->SaveAs("../outputs/pdf/deconv_data_pdf/ResolvingPower/ResolvingPower_16det_LCO_MAR_FTFP_BERT.svg");
    
    // canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_LCO_MAR_FTFP_BERT.pdf");
    // canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_LCO_MAR_FTFP_BERT.png");
    // canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_LCO_MAR_FTFP_BERT.svg");
    
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_16det_SPA_CHA.pdf");
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_16det_SPA_CHA.png");
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_16det_SPA_CHA.svg");
    
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_SPA_CHA.pdf");
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_SPA_CHA.png");
    //~ canvas->SaveAs("./deconv_data_pdf/ResolvingPower/ResolvingPower_11det_SPA_CHA.svg");

}


vector<vector<double_t> > neutrons_count_matrix(string campaign, int time, string cut){

vector< vector<Double_t>> neutrons_count_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
			//~ cout << "Read Data LCO " << endl;
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root"; //Old deconv
				counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_15min_complete.root";
		}
	if(campaign=="Maricunga")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/Maricunga/3rd_Maricunga_data_15min_complete.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/Maricunga/Maricunga_data_15min_complete.root";
		}
	if(campaign=="RetenDesierto")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/RetenDesierto/3rd_RetenDesierto_data_15min_complete.root";
		}	
	if(campaign=="Chapiquilta")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/Chapiquilta/Chapiquilta_data_15min_complete.root";
		}	
	if(campaign=="SanPedrodeAtacama")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/SanPedrodeAtacama/SanPedrodeAtacama_data_15min_complete.root";
		}	
}

if(time==60)
{
	if(campaign=="LCO")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_60min_complete.root";
		}
}

ROOT::RDataFrame df_NC("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

vector<int> df_NC_E01;
vector<int> df_NC_E02;
vector<int> df_NC_E03;
vector<int> df_NC_E04;
vector<int> df_NC_E05;
vector<int> df_NC_E06;
vector<int> df_NC_E07;
vector<int> df_NC_E08;
vector<int> df_NC_E09;
vector<int> df_NC_E10;
vector<int> df_NC_E11;
vector<int> df_NC_E12;
vector<int> df_NC_E13;
vector<int> df_NC_E14;
vector<int> df_NC_E15;
vector<int> df_NC_E16;

if(cut=="cut1")
{
	df_NC_E01 = df_NC.Take<int>("NEUrate_D01").GetValue();
	df_NC_E02 = df_NC.Take<int>("NEUrate_D02").GetValue();
	df_NC_E03 = df_NC.Take<int>("NEUrate_D03").GetValue();
	df_NC_E04 = df_NC.Take<int>("NEUrate_D04").GetValue();
	df_NC_E05 = df_NC.Take<int>("NEUrate_D05").GetValue();
	df_NC_E06 = df_NC.Take<int>("NEUrate_D06").GetValue();
	df_NC_E07 = df_NC.Take<int>("NEUrate_D07").GetValue();
	df_NC_E08 = df_NC.Take<int>("NEUrate_D08").GetValue();
	df_NC_E09 = df_NC.Take<int>("NEUrate_D09").GetValue();
	df_NC_E10 = df_NC.Take<int>("NEUrate_D10").GetValue();
	df_NC_E11 = df_NC.Take<int>("NEUrate_D11").GetValue();
	df_NC_E12 = df_NC.Take<int>("NEUrate_D12").GetValue();
	df_NC_E13 = df_NC.Take<int>("NEUrate_D13").GetValue();
	df_NC_E14 = df_NC.Take<int>("NEUrate_D14").GetValue();
	df_NC_E15 = df_NC.Take<int>("NEUrate_D15").GetValue();
	df_NC_E16 = df_NC.Take<int>("NEUrate_D16").GetValue();
}

if(cut=="cut2")
{
	df_NC_E01 = df_NC.Take<int>("NEUrateT_D01").GetValue();
	df_NC_E02 = df_NC.Take<int>("NEUrateT_D02").GetValue();
	df_NC_E03 = df_NC.Take<int>("NEUrateT_D03").GetValue();
	df_NC_E04 = df_NC.Take<int>("NEUrateT_D04").GetValue();
	df_NC_E05 = df_NC.Take<int>("NEUrateT_D05").GetValue();
	df_NC_E06 = df_NC.Take<int>("NEUrateT_D06").GetValue();
	df_NC_E07 = df_NC.Take<int>("NEUrateT_D07").GetValue();
	df_NC_E08 = df_NC.Take<int>("NEUrateT_D08").GetValue();
	df_NC_E09 = df_NC.Take<int>("NEUrateT_D09").GetValue();
	df_NC_E10 = df_NC.Take<int>("NEUrateT_D10").GetValue();
	df_NC_E11 = df_NC.Take<int>("NEUrateT_D11").GetValue();
	df_NC_E12 = df_NC.Take<int>("NEUrateT_D12").GetValue();
	df_NC_E13 = df_NC.Take<int>("NEUrateT_D13").GetValue();
	df_NC_E14 = df_NC.Take<int>("NEUrateT_D14").GetValue();
	df_NC_E15 = df_NC.Take<int>("NEUrateT_D15").GetValue();
	df_NC_E16 = df_NC.Take<int>("NEUrateT_D16").GetValue();
}

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

vector<vector<double_t> > E_neutrons_count_matrix(string campaign,int time, string cut){

vector< vector<Double_t>> E_neutrons_count_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
			//~ cout << "Read Data LCO " << endl;
			//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root"; //Old deconv
			counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_15min_complete.root";
		}
	if(campaign=="Maricunga")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/Maricunga/3rd_Maricunga_data_15min_complete.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/Maricunga/Maricunga_data_15min_complete.root";
		}
	if(campaign=="RetenDesierto")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/RetenDesierto/3rd_RetenDesierto_data_15min_complete.root";
		}
	if(campaign=="Chapiquilta")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/Chapiquilta/Chapiquilta_data_15min_complete.root";
		}
	if(campaign=="SanPedrodeAtacama")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/SanPedrodeAtacama/SanPedrodeAtacama_data_15min_complete.root";
		}	
}

if(time==60)
{
	if(campaign=="LCO")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_60min_complete.root";
		}
}

ROOT::RDataFrame df_NC("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

vector<int> df_NC_E01;
vector<int> df_NC_E02;
vector<int> df_NC_E03;
vector<int> df_NC_E04;
vector<int> df_NC_E05;
vector<int> df_NC_E06;
vector<int> df_NC_E07;
vector<int> df_NC_E08;
vector<int> df_NC_E09;
vector<int> df_NC_E10;
vector<int> df_NC_E11;
vector<int> df_NC_E12;
vector<int> df_NC_E13;
vector<int> df_NC_E14;
vector<int> df_NC_E15;
vector<int> df_NC_E16;

if(cut=="cut1")
{

	df_NC_E01 = df_NC.Take<int>("NEUrate_D01").GetValue();
	df_NC_E02 = df_NC.Take<int>("NEUrate_D02").GetValue();
	df_NC_E03 = df_NC.Take<int>("NEUrate_D03").GetValue();
	df_NC_E04 = df_NC.Take<int>("NEUrate_D04").GetValue();
	df_NC_E05 = df_NC.Take<int>("NEUrate_D05").GetValue();
	df_NC_E06 = df_NC.Take<int>("NEUrate_D06").GetValue();
	df_NC_E07 = df_NC.Take<int>("NEUrate_D07").GetValue();
	df_NC_E08 = df_NC.Take<int>("NEUrate_D08").GetValue();
	df_NC_E09 = df_NC.Take<int>("NEUrate_D09").GetValue();
	df_NC_E10 = df_NC.Take<int>("NEUrate_D10").GetValue();
	df_NC_E11 = df_NC.Take<int>("NEUrate_D11").GetValue();
	df_NC_E12 = df_NC.Take<int>("NEUrate_D12").GetValue();
	df_NC_E13 = df_NC.Take<int>("NEUrate_D13").GetValue();
	df_NC_E14 = df_NC.Take<int>("NEUrate_D14").GetValue();
	df_NC_E15 = df_NC.Take<int>("NEUrate_D15").GetValue();
	df_NC_E16 = df_NC.Take<int>("NEUrate_D16").GetValue();
}

if(cut=="cut2")
{

	df_NC_E01 = df_NC.Take<int>("NEUrateT_D01").GetValue();
	df_NC_E02 = df_NC.Take<int>("NEUrateT_D02").GetValue();
	df_NC_E03 = df_NC.Take<int>("NEUrateT_D03").GetValue();
	df_NC_E04 = df_NC.Take<int>("NEUrateT_D04").GetValue();
	df_NC_E05 = df_NC.Take<int>("NEUrateT_D05").GetValue();
	df_NC_E06 = df_NC.Take<int>("NEUrateT_D06").GetValue();
	df_NC_E07 = df_NC.Take<int>("NEUrateT_D07").GetValue();
	df_NC_E08 = df_NC.Take<int>("NEUrateT_D08").GetValue();
	df_NC_E09 = df_NC.Take<int>("NEUrateT_D09").GetValue();
	df_NC_E10 = df_NC.Take<int>("NEUrateT_D10").GetValue();
	df_NC_E11 = df_NC.Take<int>("NEUrateT_D11").GetValue();
	df_NC_E12 = df_NC.Take<int>("NEUrateT_D12").GetValue();
	df_NC_E13 = df_NC.Take<int>("NEUrateT_D13").GetValue();
	df_NC_E14 = df_NC.Take<int>("NEUrateT_D14").GetValue();
	df_NC_E15 = df_NC.Take<int>("NEUrateT_D15").GetValue();
	df_NC_E16 = df_NC.Take<int>("NEUrateT_D16").GetValue();
}

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

vector<vector<double_t> > Counting_rate_matrix(string campaign, int time, string cut){

vector< vector<Double_t>> counting_rate_matrix;
string counting_rate_campaign_path;

if(time==15)
{
	if(campaign=="LCO")
		{
			//~ cout << "Read Data LCO " << endl;
			//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root"; //Old deconv
			counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_15min_complete.root";
		}
	if(campaign=="Maricunga")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/Maricunga/3rd_Maricunga_data_15min_complete.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/Maricunga/Maricunga_data_15min_complete.root";
		}
	if(campaign=="RetenDesierto")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/RetenDesierto/3rd_RetenDesierto_data_15min_complete.root";
		}	
	if(campaign=="Chapiquilta")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/Chapiquilta/Chapiquilta_data_15min_complete.root";
		}
	if(campaign=="SanPedrodeAtacama")
		{
				counting_rate_campaign_path ="../data/external/CRNS_Data/SanPedrodeAtacama/SanPedrodeAtacama_data_15min_complete.root";
		}	
}

if(time==60)
{
	if(campaign=="LCO")
		{
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
				counting_rate_campaign_path ="../data/external/CRNS_Data/LCO/LCO_data_60min_complete.root";
		}
}

ROOT::RDataFrame df_CR("CRNS_MSDATA", counting_rate_campaign_path);

/*Generamos el vector de Counting rates por cada evento por cada detector*/

vector<int> df_CR_E01;
vector<int> df_CR_E02;
vector<int> df_CR_E03;
vector<int> df_CR_E04;
vector<int> df_CR_E05;
vector<int> df_CR_E06;
vector<int> df_CR_E07;
vector<int> df_CR_E08;
vector<int> df_CR_E09;
vector<int> df_CR_E10;
vector<int> df_CR_E11;
vector<int> df_CR_E12;
vector<int> df_CR_E13;
vector<int> df_CR_E14;
vector<int> df_CR_E15;
vector<int> df_CR_E16;


/*Corte del espectro entre 140 keV y 810 keV*/
if(cut=="cut1"){

	 df_CR_E01 = df_CR.Take<int>("NEUrate_D01").GetValue();
	 df_CR_E02 = df_CR.Take<int>("NEUrate_D02").GetValue();
	 df_CR_E03 = df_CR.Take<int>("NEUrate_D03").GetValue();
	 df_CR_E04 = df_CR.Take<int>("NEUrate_D04").GetValue();
	 df_CR_E05 = df_CR.Take<int>("NEUrate_D05").GetValue();
	 df_CR_E06 = df_CR.Take<int>("NEUrate_D06").GetValue();
	 df_CR_E07 = df_CR.Take<int>("NEUrate_D07").GetValue();
	 df_CR_E08 = df_CR.Take<int>("NEUrate_D08").GetValue();
	 df_CR_E09 = df_CR.Take<int>("NEUrate_D09").GetValue();
	 df_CR_E10 = df_CR.Take<int>("NEUrate_D10").GetValue();
	 df_CR_E11 = df_CR.Take<int>("NEUrate_D11").GetValue();
	 df_CR_E12 = df_CR.Take<int>("NEUrate_D12").GetValue();
	 df_CR_E13 = df_CR.Take<int>("NEUrate_D13").GetValue();
	 df_CR_E14 = df_CR.Take<int>("NEUrate_D14").GetValue();
	 df_CR_E15 = df_CR.Take<int>("NEUrate_D15").GetValue();
	 df_CR_E16 = df_CR.Take<int>("NEUrate_D16").GetValue();
	}

/*Corte del espectro entre 140 keV y 4 MeV*/
if(cut=="cut2"){

	 df_CR_E01 = df_CR.Take<int>("NEUrateT_D01").GetValue();
	 df_CR_E02 = df_CR.Take<int>("NEUrateT_D02").GetValue();
	 df_CR_E03 = df_CR.Take<int>("NEUrateT_D03").GetValue();
	 df_CR_E04 = df_CR.Take<int>("NEUrateT_D04").GetValue();
	 df_CR_E05 = df_CR.Take<int>("NEUrateT_D05").GetValue();
	 df_CR_E06 = df_CR.Take<int>("NEUrateT_D06").GetValue();
	 df_CR_E07 = df_CR.Take<int>("NEUrateT_D07").GetValue();
	 df_CR_E08 = df_CR.Take<int>("NEUrateT_D08").GetValue();
	 df_CR_E09 = df_CR.Take<int>("NEUrateT_D09").GetValue();
	 df_CR_E10 = df_CR.Take<int>("NEUrateT_D10").GetValue();
	 df_CR_E11 = df_CR.Take<int>("NEUrateT_D11").GetValue();
	 df_CR_E12 = df_CR.Take<int>("NEUrateT_D12").GetValue();
	 df_CR_E13 = df_CR.Take<int>("NEUrateT_D13").GetValue();
	 df_CR_E14 = df_CR.Take<int>("NEUrateT_D14").GetValue();
	 df_CR_E15 = df_CR.Take<int>("NEUrateT_D15").GetValue();
	 df_CR_E16 = df_CR.Take<int>("NEUrateT_D16").GetValue();
	}
	
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

vector<Double_t> neutron_count_vector_gauss_MC(string campaign, int event, int crptime,string cut){

vector<Double_t> neutron_gauss_vec; // vector con los cr generados aleatoriamente de una distribucion gaussiana
vector<Double_t> N; /*vector de neutrones medidos*/

N = neutrons_count_matrix(campaign,crptime,cut)[event];


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

vector<Double_t> neutron_count_vector_poisson_MC(string campaign, int event, int crptime,string cut){

vector<Double_t> neutron_poisson_vec; // vector con los cr generados aleatoriamente de una distribucion poissoniana
vector<Double_t> N; /*vector de neutrones medidos*/

N = neutrons_count_matrix(campaign,crptime,cut)[event];


for(int i=0;i<N.size();i++)
	{
	  double deltaN = sqrt(N[i]);
	  double neutron_poisson = gRandom->Poisson(N[i]);
	  neutron_poisson_vec.push_back(neutron_poisson);
	  
	}
//~ for(int i=0;i<N.size();i++)
	//~ {
		//~ cout << " N " << N[i] << setw(15) << setfill(' ') << " N Gauss " << neutron_gauss_vec[i] << endl;
	//~ }
return neutron_poisson_vec;


}

vector<Double_t> Counting_rate_vector_gauss_MC(string campaign, int event, int crptime,string cut){

vector<Double_t> N_g; /*vector de neutrones aletarios gaussianos*/
vector<Double_t> CR_g; /*vector de counting rate de neutrones aleatorios gaussianos*/
vector<Double_t> CR; /*vector de counting rate de neutrones medidos*/

N_g = neutron_count_vector_gauss_MC(campaign,event,crptime,cut);
CR = Counting_rate_matrix(campaign,crptime,cut)[event]; //Para comparar


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

vector<Double_t> E_neutrons_count_vector_gauss_MC(string campaign, int event, int crptime,string cut){

vector<Double_t> N_g; /*vector de neutrones aletarios gaussianos*/
vector<Double_t> E_neutrons_count_vector; /*vector de counting rate de errores de neutrones aleatorios gaussianos*/

N_g = neutron_count_vector_gauss_MC(campaign,event, crptime,cut);


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
	//~ ofstream debug_em("debug_em.txt"); // archivo de salida de chi^2
	//~ vec_test{1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1}

	
	for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i])/(dCR[i]);
		 chi += partial_sum*partial_sum;
		 //~ cout <<"Det " << i+1 << " vec_pos: "<< vec_pos[i] <<" C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		 //~ cout <<"Det " << i+1  <<" C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		 //~ debug_em  <<"Det " << i+1 << " vec_pos: "<< vec_pos[i] <<" C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		 partial_sum=0;
		 }
	return chi;
	
	
}


double_t Chi_Square_debug(vector<Double_t> C_i,vector<Double_t> dCR, vector<Double_t> CR_rec, double ndet, int crptime, std::ofstream &debug_em, vector<int> detec_act)
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
	//~ ofstream debug_em("debug_em.txt"); // archivo de salida de chi^2
	//~ vec_test{1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1}


	//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1};
	vector<int> vec_test = detec_act; //detectores activados en deconv_em_ouput
	vector<int> act_vector(vec_test.size(),1);
	vector<int> vec_pos;

	/*Redefinimos la activacion*/
	for(int i=0; i<vec_test.size(); i++)
	{
	 if(act_vector[i] == vec_test[i])
		{
			vec_pos.push_back(i+1);
		}
	else{}

	}

	
	for (int i = 0; i < ndet; i++){
		 partial_sum = (C_i[i] - CR_rec[i])/(dCR[i]);
		 chi += partial_sum*partial_sum;
		 cout <<"Det " << i+1 << " vec_pos: "<< vec_pos[i] <<" C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		 debug_em  <<"Det " << i+1 << " vec_pos: "<< vec_pos[i] <<" C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
		//~ debug_em << "Det " << i+1 << " C_i " << C_i[i] <<" CR_rec " << CR_rec[i] << " chi-square : " << partial_sum*partial_sum << endl;
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
	//~ ofstream debug_em("debug_em.txt"); // archivo de salida de chi^2
	
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
void deconv_em(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm,string cut){

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

ofstream Chi2("../outputs/log/chi2.txt"); // archivo de salida de chi2

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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="RetenDesierto")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/DesiertoAtacama_"+str_stream_vwc+".csv";
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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
		}

char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
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
N = neutrons_count_matrix(campaign,crptime,cut)[event]; //Tomamos el primer evento para probar
dN = E_neutrons_count_matrix(campaign,crptime,cut)[event]; //Tomamos el primer evento para probar
/***Llenamos el vector de CR de neutrones medidos: N/T ****/
CR = Counting_rate_matrix(campaign,crptime,cut)[event]; //Tomamos el primer evento para probar

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
//vector<int> act_vector(ndet,1);

//~ vector<int> vec_test{0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1};
//~ vector<int> vec_test{1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1};
//~ vector<int> vec_test{1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1};

//vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};
const auto& vec_test = Detectors_Array(campaign);

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			R_new.push_back(R[i]);
		}
	else{}
}

//*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
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
vector<double> deconv_em_output(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm, int max_steps, string cut){

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

ofstream Chi2("../outputs/log/Stat_Estimators.txt"); // archivo de salida de Chi2
//~ ofstream debug_em("debug_em.txt"); // archivo de salida de Chi2
// Abro una sola vez en modo append
ofstream debug_em("../outputs/log/debug_em.txt", std::ios::app);

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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="RetenDesierto")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/DesiertoAtacama_"+str_stream_vwc+".csv";
				}
			/**2024**/
			if(campaign=="Chapiquilta")
				{
					/*Tomamos las mismas semillas que maricunga*/
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Chapiquilta")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
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
N = neutrons_count_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar
dN = E_neutrons_count_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar
/***Llenamos el vector de CR de neutrones medidos: N/T ****/
CR = Counting_rate_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar

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
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024 region activa arreglada y mas estadistica, considerando el nuevo detecto d04*/

//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15)*/
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP","ws","iso",campaign);  /*matriz de funciones respuesta del espectrometro 2023 usando FTFP_BERT en root con un smooth SG y smooth de root (factor 15)*/

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
// vector<int> act_vector(ndet,1);

//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //Todos los detectores activados

//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, MARICUNGA, RETEN DESIERTO
//~ vector<int> vec_test{1,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba

// vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  Chapiquilta test2
const auto& vec_test = Detectors_Array(campaign);
vector<int> vec_test_new(vec_test.begin(),vec_test.end());

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
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
	 if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
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
	vector< vector<double_t> > vec_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados integral por paso
	vector< vector<double_t> > matrix_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados integral por paso
	std::vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
	vector<double> seed_integral_representation(Seed.size());
	//~ vector<double> sum_diff_vec;
	
	for (int i = 0; i<Seed.size(); i++)
	{
		double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		seed_integral_representation[i] = (Seed[i]/E_mid)*dE[i]; /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}
	matrix_fluxnext_Intg.push_back(seed_integral_representation); //Llenamos la matrix de flujo deconvolucionados integral por paso con e valor de semilla inicial
	vec_fluxnext_Intg.push_back(seed_integral_representation); //Llenamos la matrix de flujo deconvolucionados integral por paso con e valor de semilla inicial
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
double diff_criteria_cota = 0.02;
	 //~ Chi2 <<setw(5) << setfill(' ') << "it" << " "
		 //~ <<setw(15) << setfill(' ') << "chi2" << " "
		 //~ <<setw(25) << setfill(' ') << "chi2_red"  << " "
		 //~ <<setw(25) << setfill(' ') << "xi2"  << " "
		 //~ <<setw(25) << setfill(' ') << "barDelta"  << " "
		 //~ <<setw(25) << setfill(' ') << "STD_cr" << endl;  

	//~ Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 //~ <<setw(15) << setfill(' ') << chi2 << " "
				 //~ <<setw(25) << setfill(' ') << chi2_red << endl;

//~ ofstream debug_em("debug_em.txt", ios::out | ios::app);


if(steps==0)
{				 
	while(diff_criteria>diff_criteria_cota || chi2>ndet) // El ciclo solo terminará cuando ambos criterios sean falsos simultáneamente (F || F : F, ya que F || V: V) 
	{
		
		if(em_it>max_steps)
			{
				std::cout << " Maximum iteration limit reached." << std::endl;
				break;
		    }


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
				double sum_vec = 0.0 ;
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
		//~ cout << "\r " << " em_it " << em_it;
		cout << "\r " << " em_it " << em_it << " chi2 " << chi2 << " diff value " << diff_criteria;
		delete hist_deconv_flux_step_preceding;

		
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
		//~ debug_em << "EVENT: " << event << endl;
		//~ debug_em << "SEED: " << vwc_seed << endl;
		debug_em << "EVENT: " << event << " SEED: " << vwc_seed << " step " << it+1 << endl;
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


		//From std:vector to RVec
		RVec<double> deconv_flux_step_preceding = vector<double>(vec_fluxnext_Intg[vec_fluxnext_Intg.size()-2].begin(), vec_fluxnext_Intg[vec_fluxnext_Intg.size()-2].end());
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
		//~ chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2 = Chi_Square_debug(CR,dCR, CR_rec, ndet, crptime,debug_em,vec_test_new); //Chi^2 con debug
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		debug_em << "Chi^2 total: " << chi2 << endl;


		//~ em_it+=it;
		em_it++;

		delete hist_deconv_flux_step_preceding;
		sum_vec=0;
		
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}
}

debug_em.close(); // al terminar el loop

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
FluxMin_Intg.push_back(diff_criteria);
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
/*Algoritmo EM que entrega como salida un vector (considerando un archivo .root de flujos EXPACS): */
vector<double> deconv_em_output_update(string campaign, int event, int steps, int vwc_seed, vector<double> diff_flux, vector<double> emid, vector<double> ewid, vector<double> elower, int crptime, string flux_type, int norm, int max_steps, string cut, string physic_list, string scale_factor, string neufield_type){

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

ofstream Chi2("../outputs/log/Stat_Estimators.txt"); // archivo de salida de Chi2
//~ ofstream debug_em("debug_em.txt"); // archivo de salida de Chi2
// Abro una sola vez en modo append
ofstream debug_em("../outputs/log/debug_em.txt", std::ios::app);

/****Cargamos el flujo semilla*****/

string str_stream_vwc;
string seed_flux_expacs_csv;

/**********************************************************************************************************************/
/**********************************************************************************************************************/

/************Cargamos el flujo semilla a partir del vector de entrada******************/
Seed = diff_flux; //Flujo semilla
//~ binnum = Seed.size()-1;
binnum = Seed.size(); //129
cout << "binnum: Seed vec size=" << binnum  << endl;

/*Generamos el vector de bordes de bin*/
B = elower;
cout << "B: elower vec size=" << B.size() << endl;

/*Generamos el vector de ancho de energias*/
dE = ewid;
cout << "dE: Ewid vec size=" << dE.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;
E = elower;
// cout << "E: df_E_vec " << B.size() << endl;

/**Inicializamos los vectores**/
//~ Flux.reserve(binnum);
//~ FluxMin_diff.reserve(binnum);
//~ FluxMin_Intg.reserve(binnum);

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
//~ TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
//~ for (int i = 0; i <Seed.size()-1; i++)
for (int i = 0; i <binnum; i++)
	{
		flux_inicial->SetBinContent(i+1,Seed[i]);
	}

double_t integral_flux_seed = flux_inicial->Integral();

Emid = emid;
cout << "Emid size " <<  Emid.size() << endl;


for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux[i] = Seed[i];
} 


cout << "Flux seed size="<<Flux.size() << endl;

//~ for(int i=0;i<Flux.size();i++){
	//~ cout << "i="<<i<<" "<< Flux[i] << endl;
//~ }

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

/***Llenamos el vector de neutrones y de errores de neutrones medidos****/
//~ cout << "Read N " << endl;
N = neutrons_count_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar
//~ cout << "Read dN " << endl;
dN = E_neutrons_count_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar
/***Llenamos el vector de CR de neutrones medidos: N/T ****/
//~ cout << "Read CR " << endl;
CR = Counting_rate_matrix(campaign,crptime,cut)[event-1]; //Tomamos el primer evento para probar

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
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024 region activa arreglada y mas estadistica, considerando el nuevo detecto d04*/
cout << "Cargamos la matriz de funcion respuesta" << endl;
//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth(physic_list, scale_factor, neufield_type,campaign);  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 

//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15) SanPedro y Chapiquilta*/ 

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
// vector<int> act_vector(ndet,1);

//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //Todos los detectores activados

//vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, MARICUNGA, RETEN DESIERTO
const auto& vec_test = Detectors_Array(campaign);
vector<int> vec_test_new(vec_test.begin(),vec_test.end());

//~ vector<int> vec_test{1,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta prueba

//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  San Pedro / Chapiquilta tes2

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
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
	 if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
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
	vector< vector<double_t> > vec_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados integral por paso
	vector< vector<double_t> > matrix_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados integral por paso
	std::vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
	vector<double> seed_integral_representation(Seed.size());
	//~ vector<double> sum_diff_vec;
	
	for (int i = 0; i<Seed.size(); i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		seed_integral_representation[i] = Seed[i]*dE[i]; /*expacs entrega el flujo diferencial, para pasarlo a flujo integral dividimos por E_mid*/
	}
	matrix_fluxnext_Intg.push_back(seed_integral_representation); //Llenamos la matrix de flujo deconvolucionados integral por paso con e valor de semilla inicial
	vec_fluxnext_Intg.push_back(seed_integral_representation); //Llenamos la matrix de flujo deconvolucionados integral por paso con e valor de semilla inicial
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
double diff_criteria_cota = 0.02;
	 //~ Chi2 <<setw(5) << setfill(' ') << "it" << " "
		 //~ <<setw(15) << setfill(' ') << "chi2" << " "
		 //~ <<setw(25) << setfill(' ') << "chi2_red"  << " "
		 //~ <<setw(25) << setfill(' ') << "xi2"  << " "
		 //~ <<setw(25) << setfill(' ') << "barDelta"  << " "
		 //~ <<setw(25) << setfill(' ') << "STD_cr" << endl;  

	//~ Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 //~ <<setw(15) << setfill(' ') << chi2 << " "
				 //~ <<setw(25) << setfill(' ') << chi2_red << endl;

//~ ofstream debug_em("debug_em.txt", ios::out | ios::app);


if(steps==0)
{				 
	while(diff_criteria>diff_criteria_cota || chi2>ndet) // El ciclo solo terminará cuando ambos criterios sean falsos simultáneamente (F || F : F, ya que F || V: V) 
	{
		
		if(em_it>max_steps)
			{
				std::cout << " Maximum iteration limit reached." << std::endl;
				break;
		    }


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
				double sum_vec = 0.0 ;
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
		//~ cout << "\r " << " em_it " << em_it;
		cout << "\r " << " em_it " << em_it << " chi2 " << chi2 << " diff value " << diff_criteria;
		delete hist_deconv_flux_step_preceding;

		
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
		//~ debug_em << "EVENT: " << event << endl;
		//~ debug_em << "SEED: " << vwc_seed << endl;
		debug_em << "EVENT: " << event << " SEED: " << vwc_seed << " step " << it+1 << endl;
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


		//From std:vector to RVec
		RVec<double> deconv_flux_step_preceding = vector<double>(vec_fluxnext_Intg[vec_fluxnext_Intg.size()-2].begin(), vec_fluxnext_Intg[vec_fluxnext_Intg.size()-2].end());
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
			cout << " deconv_flux_step_present vec size="<< deconv_flux_step_present.size() << endl; 
			cout << " deconv_flux_step_preceding vec size="<<deconv_flux_step_preceding.size() << endl; 
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
		//~ chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2 = Chi_Square_debug(CR,dCR, CR_rec, ndet, crptime,debug_em,vec_test_new); //Chi^2 con debug
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		debug_em << "Chi^2 total: " << chi2 << endl;


		//~ em_it+=it;
		em_it++;

		delete hist_deconv_flux_step_preceding;
		sum_vec=0;
		
		//~ cout << it << "  "  << " chi2: " << chi2   << "  "  << " chi2 red: " << chi2_red <<" " << " xi2: " << xi2_estimator << " barDelta: " << " " << barDelta_estimator << " " << "STD_cr: " << STD_cr_estimator<< endl;
		
		 //~ Chi2<<setw(5) << setfill(' ') << it << " "
			 //~ <<setw(15) << setfill(' ') << chi2 << " "
			 //~ <<setw(25) << setfill(' ') << chi2_red  << " "
			 //~ <<setw(25) << setfill(' ') << xi2_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << barDelta_estimator  << " "
			 //~ <<setw(25) << setfill(' ') << STD_cr_estimator << endl;  
	}
}

debug_em.close(); // al terminar el loop

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
FluxMin_Intg.push_back(diff_criteria);
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

// ---------------------------------------------------------------------
// Una sola función: carga semillas (21) desde PARMA y guarda por step
// ---------------------------------------------------------------------
void deconv_em_event_write_singlefile(
    std::string campaign,
    int event,
    int time_grid,          // = crptime
    int max_steps,          // ej 200
    std::string cut,
    std::string physic_list,
    std::string scale_factor = "ws",  // o "wos" si aplica en tu RF
    int norm = 0                         // igual que en tu flujo
){
    // -----------------------------
    // Campaign path 
    // -----------------------------
    std::string campaign_path;
    if(physic_list=="QGSP_BERT")      campaign_path = campaign;
    else if(physic_list=="FTFP_BERT") campaign_path = campaign + "_FTFP_BERT";
    else { std::cerr << "Physics list inexistente o incorrecta\n"; return; }

    // -----------------------------
    // 1) ICRP116 binning 
    // -----------------------------
    char delimiter = ',';
    char double_type ='D';

    std::string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
    std::unordered_map<std::string, char> icrp116_map = {
        {"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}
    };

    auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path, true, delimiter, -1, std::move(icrp116_map));

    int bin_cut = 130;                  // tu valor
    int binnum  = bin_cut - 1;          // tu flujo seed usa 129
    auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1);

    auto emid_full   = df_icrp116_cut.Take<double>("Emid").GetValue();    // size 130
    auto ewid_full   = df_icrp116_cut.Take<double>("Ewid").GetValue();    // size 130
    auto elower_full = df_icrp116_cut.Take<double>("Elower").GetValue();  // size 130

    // Recortamos a 129 exactamente como tu diff_flux_bin_seed_new
    std::vector<double> emid(emid_full.begin(),   emid_full.begin()   + binnum);
    std::vector<double> ewid(ewid_full.begin(),   ewid_full.begin()   + binnum);
    std::vector<double> elower(elower_full.begin(), elower_full.begin() + binnum);

    // -----------------------------
    // 2) PARMA/EXPACS seeds del ROOT file
    // -----------------------------
    std::string parma_file_path = "../data/external/EXPACS_Data/parma_cpp_flopez/" + campaign + "_parma_fluxes_5.root";
    ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);

    int year_input=0, month_input=0, day_input=0;
    if(campaign=="LCO"){ year_input=2023; month_input=7; day_input=10; }
    if(campaign=="Maricunga"){ year_input=2023; month_input=7; day_input=14; }
    if(campaign=="SanPedrodeAtacama"){ year_input=2024; month_input=11; day_input=10; }
    if(campaign=="Chapiquilta"){ year_input=2024; month_input=11; day_input=17; }

    auto lambda_filter_flux = [&](int &year, int &month, int &day){
        return (year_input==year && month_input==month && day_input==day);
    };

    auto df_parma_filter = df_parma_spectra.Filter(lambda_filter_flux, {"Year","Month","Day"});

    // vector<vector<double>>: NeutronFdiff (501 spectra típicamente)
    auto diff_flux_parma_all = df_parma_filter.Take<std::vector<double>>("NeutronFdiff").GetValue();
    auto waterwf_all         = df_parma_filter.Take<double>("WaterWF").GetValue(); // 0..1

    if(diff_flux_parma_all.empty() || waterwf_all.empty()){
        std::cerr << "ERROR: df_parma_filter devolvió vacío (fecha no encontrada?)\n";
        return;
    }
    if(diff_flux_parma_all.size() != waterwf_all.size()){
        std::cerr << "ERROR: tamaños inconsistentes NeutronFdiff vs WaterWF\n";
        return;
    }

    std::cout << "#SPECTRA size: " << diff_flux_parma_all.size() << "\n";
    std::cout << "#WaterWF size: " << waterwf_all.size() << "\n";
    std::cout << "#NeutronFdiff[0] size: " << diff_flux_parma_all[0].size() << "\n";

    // -----------------------------
    // 3) Seleccionar 21 seeds (0..100 cada 5%) por nearest WaterWF*100
    // -----------------------------
    std::vector<int> selected_idx; selected_idx.reserve(21);

    auto nearest_index_for_target = [&](double target_percent)->int{
        double best = std::numeric_limits<double>::max();
        int best_i = 0;
        for(int i=0;i<(int)waterwf_all.size();++i){
            double v = waterwf_all[i]*100.0;
            double d = std::abs(v - target_percent);
            if(d < best){
                best = d; best_i = i;
            }
        }
        return best_i;
    };

    for(int s=0;s<=100;s+=5){
        int idx = nearest_index_for_target((double)s);
        selected_idx.push_back(idx);
    }

    // (opcional) evitar duplicados si WaterWF no cubre exacto: los colapsa
    // si NO quieres colapsar, comenta esto.
    {
        std::vector<int> tmp = selected_idx;
        std::sort(tmp.begin(), tmp.end());
        tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
        if((int)tmp.size() != (int)selected_idx.size()){
            std::cout << "WARN: Algunos targets 5% cayeron en el mismo índice (WaterWF discreto). "
                         "Se mantendrán igual (sin colapsar) para preservar 21 seeds.\n";
        }
    }

	 // -----------------------------
    // Datos medidos + RF (una sola vez)
    // -----------------------------
    int ndet = 16;

    std::vector<double> N(ndet,0), dN(ndet,0), CR(ndet,0), dCR(ndet,0), perc_e_N(ndet,0);
    N  = neutrons_count_matrix(campaign, time_grid, cut)[event-1];
    dN = E_neutrons_count_matrix(campaign, time_grid, cut)[event-1];
    CR = Counting_rate_matrix(campaign, time_grid, cut)[event-1];

    for(int i=0;i<ndet;i++){
        perc_e_N[i] = dN[i]/N[i];
        dCR[i] = CR[i]*perc_e_N[i];
    }

    std::cout << "Cargamos RF matrix...\n";
    std::vector<std::vector<double>> R =
        Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth(physic_list, scale_factor,"iso",campaign);

    // selección detectores (tu vec_test)
    // std::vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1};
	const auto& vec_test = Detectors_Array(campaign);
   
	// std::vector<int> act_vector(ndet,1);


    std::vector<std::vector<double>> R_new;
    std::vector<double> CR_new, dCR_new;

    for(int i=0;i<ndet;i++){
        if(vec_test[i]==1){
            R_new.push_back(R[i]);
            CR_new.push_back(CR[i]);
            dCR_new.push_back(dCR[i]);
        }
    }
    R = R_new;
    CR = CR_new;
    dCR = dCR_new;
    ndet = (int)R.size();

    // -----------------------------
    // Output ROOT (un archivo por evento)
    // -----------------------------
    std::ostringstream ss_event, ss_timegrid;
    ss_event << event; ss_timegrid << time_grid;

    std::string outFileName =
        "../outputs/root/deconv_data_rootfile/EM_single/" + campaign_path +
        "/EM_single_campaign_" + campaign +
        "_event_" + ss_event.str() +
        "_timegrid_" + ss_timegrid.str() +
        "_ndet_" + std::to_string(ndet) +
        "_maxsteps_" + std::to_string(max_steps) +
        ".root";

    TFile* fout = TFile::Open(outFileName.c_str(), "RECREATE");
    if(!fout || fout->IsZombie()){
        std::cerr << "ERROR: cannot create " << outFileName << "\n";
        return;
    }

    // -----------------------------
    // TTree simple (sin struct)
    // -----------------------------
    TTree* t = new TTree("em_event_tree", "EM results per step and seed (21 seeds)");

    Int_t    step = 0;
    Int_t    seed_idx = 0;      // 0..20
    Int_t    parma_index = 0;   // índice real en array PARMA filtrado
    Double_t vwc_percent = 0.0; // WaterWF*100 del seed real

    Double_t Chi2 = 0.0, Chi2red = 0.0, diff_criteria = 0.0;
    Double_t xi2 = 0.0, barDelta = 0.0, std_cr = 0.0;

    Double_t Intg_total = 0.0, Intg_th = 0.0, Intg_ep = 0.0, Intg_fs = 0.0, Intg_he = 0.0;

    std::vector<double> flux_intg; // tamaño 129

    t->Branch("step", &step);
    t->Branch("seed_idx", &seed_idx);
    t->Branch("parma_index", &parma_index);
    t->Branch("vwc_percent", &vwc_percent);

    t->Branch("Chi2", &Chi2);
    t->Branch("Chi2red", &Chi2red);
    t->Branch("diff_criteria", &diff_criteria);
    t->Branch("xi2", &xi2);
    t->Branch("barDelta", &barDelta);
    t->Branch("std_cr", &std_cr);

    t->Branch("Intg_total", &Intg_total);
    t->Branch("Intg_th", &Intg_th);
    t->Branch("Intg_ep", &Intg_ep);
    t->Branch("Intg_fs", &Intg_fs);
    t->Branch("Intg_he", &Intg_he);

    t->Branch("flux_intg", &flux_intg);

    // -----------------------------
    // índices de regiones (en 129 bins)
    // (igual filosofía que tu Integral(FindBin...) pero aquí por sumas)
    // -----------------------------
    auto last_bin_leq = [&](double Emax)->int{
        int idx = 0;
        for(int i=0;i<binnum;i++){
            if(elower[i] <= Emax) idx = i;
            else break;
        }
        return std::max(idx, 0);
    };
    const int i_th_max = last_bin_leq(1.9e-07);
    const int i_ep_max = last_bin_leq(0.9e-02);
    const int i_fs_max = last_bin_leq(0.89e+01);
    const int i_he_max = last_bin_leq(7.6e+03);

    // -----------------------------
    // Loop: 21 seeds x steps (EM incremental)
    // -----------------------------
    for(seed_idx=0; seed_idx<21; ++seed_idx){

        parma_index = selected_idx[seed_idx];
        vwc_percent = waterwf_all[parma_index]*100.0;

        // construir diff_flux seed recortado a 129 (bin_cut-1)
        std::vector<double> Seed(binnum, 0.0);
        // NeutronFdiff puede venir con >=129; copiamos 129
        for(int j=0;j<binnum;j++){
            Seed[j] = diff_flux_parma_all[parma_index][j];
        }

        std::cout << "EM unfolding Campaign: " << campaign
                  << " Event: " << event
                  << " Time grid: " << time_grid
                  << " Seed_idx: " << seed_idx
                  << " PARMA idx: " << parma_index
                  << " VWC: " << vwc_percent << "%  Starting...\n";

        // Inicializar Flux (diferencial)
        std::vector<double> Flux = Seed, FluxNext(binnum,0.0);
        std::vector<double> FluxMin_diff(binnum,0.0), FluxMin_Intg(binnum,0.0);

        // normalización opcional (física): sum(Seed[i]*dE[i])
        double integral_seed = 0.0;
        for(int i=0;i<binnum;i++) integral_seed += Seed[i]*ewid[i];
        if(norm==1 && integral_seed>0){
            for(int i=0;i<binnum;i++) Flux[i] /= integral_seed;
        }

        // prev para diff_criteria (primera referencia)
        std::vector<double> prev_flux_intg(binnum,0.0);
        for(int i=0;i<binnum;i++){
            // prev_flux_intg[i] = (Flux[i]/emid[i]) * ewid[i];  // como tu seed_integral_representation
			   prev_flux_intg[i] = Flux[i]*ewid[i];   // Seed es diferencial
        }

        Chi2 = 30.0; Chi2red = 0.0; diff_criteria = 10.0;

        for(step=1; step<=max_steps; ++step){

            // --- EM update ---
            for(int b=0;b<binnum;b++){
                double Sum_R = 0.0;
                for(int r=0;r<ndet;r++) Sum_R += R[r][b];

                double Sum_N_R_Flux = 0.0;
                for(int r=0;r<ndet;r++){
                    double Sum_R_Flux = 0.0;
                    for(int k=0;k<binnum;k++){
                        Sum_R_Flux += R[r][k] * Flux[k] * ewid[k];
                    }
                    Sum_N_R_Flux += (R[r][b] * Flux[b] * CR[r]) / Sum_R_Flux;
                }
                FluxNext[b] = Sum_N_R_Flux / Sum_R;
            }
            Flux.swap(FluxNext);

            // --- flujos diff e intg ---
            for(int i=0;i<binnum;i++){
                FluxMin_diff[i] = Flux[i];
                FluxMin_Intg[i] = Flux[i] * ewid[i];
            }

            // --- diff_criteria ---
            double integral_prev = 0.0;
            for(int i=0;i<binnum;i++) integral_prev += prev_flux_intg[i];

            double sum_vec = 0.0;
            if(integral_prev>0){
                for(int i=0;i<binnum;i++){
                    sum_vec += std::abs(FluxMin_Intg[i] - prev_flux_intg[i]) / integral_prev;
                }
            }
            diff_criteria = sum_vec;
            prev_flux_intg = FluxMin_Intg;

            // --- CR recalculado + estimadores ---
            std::vector<double> CR_rec = Recalculate(R, FluxMin_diff, ewid, ndet);

            Chi2    = Chi_Square(CR, dCR, CR_rec, ndet, time_grid);
            Chi2red = Chi_Square_red(CR, dCR, CR_rec, ndet, time_grid);
            xi2     = Xi_Square(CR, CR_rec, ndet, time_grid);
            barDelta= bar_delta(CR, CR_rec, ndet, time_grid);
            std_cr  = STD_cr(CR, CR_rec, ndet, time_grid);

            // --- integrales por región (sumas de FluxMin_Intg) ---
            Intg_total = 0.0; for(int i=0;i<=i_he_max;i++) Intg_total += FluxMin_Intg[i];
            Intg_th    = 0.0; for(int i=0;i<=i_th_max;i++) Intg_th += FluxMin_Intg[i];
            Intg_ep    = 0.0; for(int i=i_th_max+1;i<=i_ep_max;i++) Intg_ep += FluxMin_Intg[i];
            Intg_fs    = 0.0; for(int i=i_ep_max+1;i<=i_fs_max;i++) Intg_fs += FluxMin_Intg[i];
            Intg_he    = 0.0; for(int i=i_fs_max+1;i<=i_he_max;i++) Intg_he += FluxMin_Intg[i];

            // --- flux branch ---
            flux_intg = FluxMin_Intg;

            // --- Fill TTree ---
            t->Fill();

            if(step % 25 == 0) t->AutoSave("SaveSelf");
        }

        std::cout << "Finished seed_idx=" << seed_idx << " (VWC " << vwc_percent << "%)\n\n";
    }

    fout->Write();
    fout->Close();
    std::cout << "Saved: " << outFileName << "\n";
}

vector<double> deconv_em_output_MC(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm, int max_steps,string cut){

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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="RetenDesierto")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/DesiertoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Chapiquilta")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
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
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Maricunga")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/PasoSanFcoAtacama_"+str_stream_vwc+".csv";
				}
			if(campaign=="Chapiquilta")
				{
					seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
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
N = neutron_count_vector_gauss_MC(campaign,event-1,crptime,cut);
//~ N = neutron_count_vector_poisson_MC(campaign,event-1,crptime,cut);

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
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024*/
R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15)*/

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
// vector<int> act_vector(ndet,1);


//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, Maricunga, RetenDesierto
//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta tes1
// vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  Chapiquilta tes2
const auto& vec_test = Detectors_Array(campaign);

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
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
	  if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;
//~ cout << "ndet " << ndet << endl;
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

//~ cout << "Inicia Deconvolucion" << endl;
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
		// seed_integral_representation[i] = (Seed[i]/E_mid)*dE[i]; /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
		seed_integral_representation[i] = Seed[i]*dE[i]; /*expacs entrega el flujo diferencial, para pasarlo a flujo diff integral multiplicamos por dE*/

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
double diff_criteria_cota = 0.02;

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
	//~ while(diff_criteria>0.01 || chi2>ndet )
	while(diff_criteria>diff_criteria_cota || chi2>ndet )
	{

		if(em_it>max_steps)
			{
				//~ std::cout << " Maximum iteration limit reached." << std::endl;
				//~ std::cout << " Maximum iteration limit reached. ";
				break;
			}

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
			    double sum_vec=0.0;
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
		//~ cout << "\r " << " em_it " << em_it;
		delete hist_deconv_flux_step_preceding;
		
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
FluxMin_Intg.push_back(diff_criteria);
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

/*Nueva funcion de deconvolucion, que toma como input un vector de flujo diferencial y
 * los valores de Emid, Ewid y ELower del archivo icrp116_binning_resume.csv*/
 
vector<double> deconv_em_output_MC_update(string campaign, int event, int steps, int vwc_seed, vector<double> diff_flux, vector<double> emid, vector<double> ewid, vector<double> elower, int crptime, string flux_type, int norm, int max_steps,string cut, string physic_list, string scale_factor, string neufield_type){

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

/**********************************************************************************************************************/
/**********************************************************************************************************************/

/************Cargamos el flujo semilla a partir del vector de entrada******************/
Seed = diff_flux; //Flujo semilla
//~ binnum = Seed.size()-1;
binnum = Seed.size(); //129
//~ cout << "binnum: Seed vec size=" << binnum  << endl;

/*Generamos el vector de bordes de bin*/
B = elower;
//~ cout << "B: elower vec size=" << B.size() << endl;

/*Generamos el vector de ancho de energias*/
dE = ewid;
//~ cout << "dE: Ewid vec size=" << dE.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;
E = elower;
// cout << "E: df_E_vec " << B.size() << endl;

//**Inicializamos los vectores**/
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
//~ TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
//~ for (int i = 0; i <Seed.size()-1; i++)
for (int i = 0; i <binnum; i++)
	{
		flux_inicial->SetBinContent(i+1,Seed[i]);
	}

double_t integral_flux_seed = flux_inicial->Integral();

Emid = emid;
//~ cout << "Emid size " <<  Emid.size() << endl;


for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux[i] = Seed[i];
} 

//~ cout << "Flux seed size="<<Flux.size() << endl;

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

/***Llenamos el vector de neutrones y de errores de neutrones aleatorios gausianos****/
N = neutron_count_vector_gauss_MC(campaign,event-1,crptime,cut);
//~ N = neutron_count_vector_poisson_MC(campaign,event-1,crptime,cut);

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
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 

//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","wos");  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
//R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","ws","iso");  /*Con el factor 1/4. matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 

/********************************************************/
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth(physic_list,scale_factor,neufield_type,campaign);  /*Con el factor 1/4. matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
/*********************************************************/

//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15)*/

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
// vector<int> act_vector(ndet,1);


// vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, Maricunga, RetenDesierto
const auto& vec_test = Detectors_Array(campaign);
//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta tes1
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  Chapiquilta, SanPedro

/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
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
	  if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	  if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	 if(vec_test[i]==1)
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;
//~ cout << "ndet " << ndet << endl;
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

//~ cout << "Inicia Deconvolucion" << endl;
	Double_t Sum_R=0.;
	Double_t Sum_R_Flux=0.;
	Double_t Sum_N_R_Flux=0.;
	
	//~ vector< vector<double_t> > vec_fluxnext_diff; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	vector< vector<double> > matrix_fluxnext_Intg; // vector de vectores de flux next o flujos deconvolucionados diferencial por paso
	std::vector<TH1D*> vec_hist_deconv; //vector de histogramas de flujos deconvolucionados
	vector<double> seed_integral_representation(Seed.size());
	for (int i = 0; i<Seed.size(); i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		seed_integral_representation[i] = (Seed[i]/Emid[i])*dE[i]; /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
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
double diff_criteria_cota = 0.02;

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
	//~ while(diff_criteria>0.01 || chi2>ndet )
	while(diff_criteria>diff_criteria_cota || chi2>ndet )
	{

		if(em_it>max_steps)
			{
				//~ std::cout << " Maximum iteration limit reached." << std::endl;
				//~ std::cout << " Maximum iteration limit reached. ";
				break;
			}

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
			    double sum_vec=0.0;
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
		//~ cout << "\r " << " em_it " << em_it;
		delete hist_deconv_flux_step_preceding;
		
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
FluxMin_Intg.push_back(diff_criteria);
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

vector<double> deconv_em_output_MC_update_refactor(string campaign, int event, int steps, int vwc_seed, vector<double> diff_flux, vector<double> emid, vector<double> ewid, vector<double> elower, int crptime, string flux_type, int norm, int max_steps,string cut, string physic_list, string scale_factor, string neufield_type){

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
//vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
//vector<Double_t> E; /*bins*/ /*matriz de bordes inferiores de Energias*/
//vector<Double_t> Emid; /*bins*/ /*matriz de Energias centrales*/

vector<Double_t> em_vec_output;

//~ ofstream Chi2("Stat_Estimators.txt"); // archivo de salida de Chi2
//~ ofstream debug_em("debug_em.txt"); // archivo de salida de Chi2

/****Cargamos el flujo semilla*****/

string str_stream_vwc;
string seed_flux_expacs_csv;

/**********************************************************************************************************************/
/**********************************************************************************************************************/

/************Cargamos el flujo semilla a partir del vector de entrada******************/
Seed = diff_flux; //Flujo semilla
//~ binnum = Seed.size()-1;
binnum = Seed.size(); //129
//~ cout << "binnum: Seed vec size=" << binnum  << endl;

/*Generamos el vector de bordes de bin*/
//B = elower;
//~ cout << "B: elower vec size=" << B.size() << endl;

/*Generamos el vector de ancho de energias*/
dE = ewid;
//~ cout << "dE: Ewid vec size=" << dE.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;
//E = elower;
// cout << "E: df_E_vec " << B.size() << endl;

//**Inicializamos los vectores**/
// for (int i = 0; i < Seed.size(); i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
// {
// 	Flux.push_back(0) ;
// 	FluxMin_diff.push_back(0);
// 	FluxMin_Intg.push_back(0);
// } 

Flux.resize(binnum, 0.0);
FluxMin_diff.resize(binnum, 0.0);
FluxMin_Intg.resize(binnum, 0.0);      // luego agregamos +13 con push_back
FluxMin_Intg.reserve(binnum + 13);     // evita realloc en los push_back finales

/****Definimos los histogramas****/

/*borde de bines como array*/
//double *bins = B.data();
//~ TCanvas *canvas_expacs = new TCanvas("Expacs_flux","Expacs_flux");

//Emid = emid;
//~ cout << "Emid size " <<  Emid.size() << endl;


for (int i = 0; i < binnum; i++) /*Llenamos los vectores de flujo deconv y flujo deconv min con ceros*/
{
	Flux[i] = Seed[i];
} 

//~ cout << "Flux seed size="<<Flux.size() << endl;

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

/***Llenamos el vector de neutrones y de errores de neutrones aleatorios gausianos****/
N = neutron_count_vector_gauss_MC(campaign,event-1,crptime,cut);
//~ N = neutron_count_vector_poisson_MC(campaign,event-1,crptime,cut);

//N protection
for (int i = 0; i < (int)N.size();i++) {
    if (N[i] < 0) N[i] = 0;
    dN[i] = sqrt(N[i]);
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

//perc con proteccion
for (int i = 0; i < (int)N.size(); i++) {
    perc_e_N[i] = (N[i] > 0 ? dN[i]/N[i] : 0.0);
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

//proteccion para no dividir por cero en chisquare
const double eps_cr = 1e-12; // cps
for (int i = 0; i < (int)dCR.size(); ++i)
	{
		dCR[i] = std::max(dCR[i], eps_cr);
	}

/**********Matrix de funciones respuesta*****/
//~ R = Response_function_matrix_fm(); /*matriz de funciones respuesta del espectrometro*/
//~ vector< vector<double>> R_fm = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2023(); /*matriz de funciones respuesta del espectrometro*/
//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 

//~ R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","wos");  /*matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
//R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth("FTFP_BERT","ws","iso");  /*Con el factor 1/4. matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 

/********************************************************/
R = Response_function_matrix_lin_spec_2023_fix_active_volume_more_statistics_smooth(physic_list,scale_factor,neufield_type,campaign);  /*Con el factor 1/4. matriz de funciones respuesta del espectrometro 2023 con un smooth SG y smooth de root (factor 15) LCO*/ 
/*********************************************************/

//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics(); /*matriz de funciones respuesta del espectrometro 2024*/
//~ R = Response_function_matrix_lin_spec_2024_fix_active_volume_more_statistics_smooth();  /*matriz de funciones respuesta del espectrometro 2024 con un smooth SG y smooth de root (factor 15)*/

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
//vector<int> act_vector(ndet,1);


//vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; //LCO, Maricunga, RetenDesierto
//~ vector<int> vec_test{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//~ vector<int> vec_test{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1}; // Chapiquilta tes1
//~ vector<int> vec_test{1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,1}; //  Chapiquilta, SanPedro

const auto& vec_test = Detectors_Array(campaign);


/*Redefinimos la matriz de funcion respuesta*/
for(int i=0; i<ndet; i++)
{
	 //if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
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
	//  if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
		{
			N_new.push_back(N[i]);
		}
	else{}
}

/*Redefinimos el vector de perc_e_N*/
for(int i=0; i<ndet; i++)
{
	//  if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
		{
			perc_e_N_new.push_back(perc_e_N[i]);
		}
	else{}
}

/*Redefinimos el vector de CR*/
for(int i=0; i<ndet; i++)
{
	//  if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
		{
			CR_new.push_back(CR[i]);
		}
	else{}
}

/*Redefinimos el vector dCR*/
for(int i=0; i<ndet; i++)
{
	//  if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
		{
			dCR_new.push_back(dCR[i]);
		}
	else{}
}

/*Vect de nombres*/
for(int i=0; i<ndet; i++)
{
	//  if(act_vector[i] == vec_test[i])
	 if(vec_test[i]==1)
		{
			det_names_act.push_back(det_names[i]);
		}
	else{}
}

/*Redefinimos ndet*/

int ndet_new = R_new.size();
ndet = ndet_new;
//~ cout << "ndet " << ndet << endl;
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

double integral_flux_seed = 0.0;
for (int i = 0; i < binnum; ++i) integral_flux_seed += Seed[i];

/********Flujo semilla diferencial normalizado************/
for (int i = 0; i <binnum; i++)
	{
		Flux[i] = Flux[i]/integral_flux_seed; //Normalizamos el flujo semilla
		// cout << i << " " << Flux[i] << endl;
	}

}
else {}



/*************************************************************/
/**************Algoritmo de deconvolucion EM******************/
/*************************************************************/

//~ cout << "Inicia Deconvolucion" << endl;
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
double diff_criteria_cota = 0.02;

	 //~ Chi2 <<setw(5) << setfill(' ') << "it" << " "
		 //~ <<setw(15) << setfill(' ') << "chi2" << " "
		 //~ <<setw(25) << setfill(' ') << "chi2_red"  << " "
		 //~ <<setw(25) << setfill(' ') << "xi2"  << " "
		 //~ <<setw(25) << setfill(' ') << "barDelta"  << " "
		 //~ <<setw(25) << setfill(' ') << "STD_cr" << endl;  

	//~ Chi2 <<setw(5) << setfill(' ') << "Init" << " "
				 //~ <<setw(15) << setfill(' ') << chi2 << " "
				 //~ <<setw(25) << setfill(' ') << chi2_red << endl;

// Paso 0: semilla en representación integral por bin
vector<double> prev_Intg(binnum, 0.0);
	for (int i = 0; i < binnum; i++) {
		prev_Intg[i] = Seed[i]*dE[i];   // Seed es diferencial
	}

const double eps = 1e-300;
// Precompute once (outside iterations): SumR[b] = Σ_r R[r][b]
vector<double> SumR(binnum, 0.0); 
	for (int b = 0; b < binnum; b++) {
		double s = 0.0;
		for (int r = 0; r < ndet; r++) s += R[r][b];
		SumR[b] = s;
}

vector<double> Den(ndet, 0.0);
vector<double> w(ndet, 0.0);


if(steps==0)
{				 
	//~ while(diff_criteria>0.01 || chi2>ndet )
	while(diff_criteria>diff_criteria_cota || chi2>ndet )
	{

		if(em_it>max_steps)
			{
				//~ std::cout << " Maximum iteration limit reached." << std::endl;
				//~ std::cout << " Maximum iteration limit reached. ";
				break;
			}


		FluxNext = Flux;

		// 1) Denominadores por detector: Den[r] = Σ_k R[r][k] * Flux[k] * dE[k]
		for (int r = 0; r < ndet; r++) {
				double den = 0.0;
				for (int k = 0; k < binnum; k++) {
					den += R[r][k] * Flux[k] * dE[k];
		}
			Den[r] = den;

			// w = CR/Den (protección mínima division por cero)
			w[r] = CR[r] / (Den[r] > eps ? Den[r] : eps);
		}

		// 2) Update por bin: FluxNext[b] = Flux[b] * (Σ_r R[r][b] * w[r]) / (Σ_r R[r][b])
		for (int b = 0; b < binnum; b++) {
		double num = 0.0;
		for (int r = 0; r < ndet; r++) {
			num += R[r][b] * w[r];
		}

		//(protección mínima division por cero)
		const double sb = (SumR[b] > eps ? SumR[b] : eps);
		FluxNext[b] = Flux[b] * (num / sb);
		}
				
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < binnum; i++) 
		 {
			FluxMin_diff[i] = Flux[i]; // flujo diferencial
			FluxMin_Intg[i] = Flux[i]*dE[i]; //integral
		 }

		
		// ===== Diferencia de flujos consecutivos sin ROOT =====
		// diff = sum |curr-prev| / sum(prev), con curr = Flux*dE
		double integral_prev = 0.0;
		double sum_abs = 0.0;

		for (int i = 0; i < binnum; i++) {
			// const double curr = Flux[i] * dE[i]; //flujo integral deconv
			const double curr = FluxMin_Intg[i]; //flujo integral deconv
			integral_prev += prev_Intg[i];
			sum_abs       += std::abs(curr - prev_Intg[i]);
			prev_Intg[i] = curr; // actualiza "paso anterior" para la próxima iteración
		}


		diff_criteria = sum_abs / (integral_prev > eps ? integral_prev : eps);
	
		/*Counting rate recalculado*/
		CR_rec = Recalculate(R, FluxMin_diff, dE, ndet); // CR recalculado

		/***Calculamos los estimadores estadisticos***/
		chi2 = Chi_Square(CR,dCR, CR_rec, ndet, crptime);
		chi2_red = Chi_Square_red(CR,dCR, CR_rec, ndet, crptime);
		xi2_estimator = Xi_Square(CR, CR_rec, ndet, crptime);
		barDelta_estimator = bar_delta(CR, CR_rec, ndet, crptime);
		STD_cr_estimator = STD_cr(CR, CR_rec, ndet, crptime);

		em_it++;
		//~ cout << "\r " << " em_it " << em_it;
		
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

		// 1) Denominadores por detector: Den[r] = Σ_k R[r][k] * Flux[k] * dE[k]
		for (int r = 0; r < ndet; r++) {
				double den = 0.0;
				for (int k = 0; k < binnum; k++) {
					den += R[r][k] * Flux[k] * dE[k];
		}
			Den[r] = den;

			// w = CR/Den (protección mínima division por cero)
			w[r] = CR[r] / (Den[r] > eps ? Den[r] : eps);
		}

		// 2) Update por bin: FluxNext[b] = Flux[b] * (Σ_r R[r][b] * w[r]) / (Σ_r R[r][b])
		for (int b = 0; b < binnum; b++) {
		double num = 0.0;
		for (int r = 0; r < ndet; r++) {
			num += R[r][b] * w[r];
		}

		//(protección mínima division por cero)
		const double sb = (SumR[b] > eps ? SumR[b] : eps);
		FluxNext[b] = Flux[b] * (num / sb);
		}
				
		Flux=FluxNext; /*flujo deconvolucionado*/
		
		//Llenamos el vector de vectores de fluxnext
		 for (int i = 0; i < binnum; i++) 
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
// -------------------------
// Integrales por región (por índices) 
// -------------------------
constexpr int r0_lo = 0,   r0_hi = 23;
constexpr int r1_lo = 23,  r1_hi = 70;
constexpr int r2_lo = 70,  r2_hi = 100;
constexpr int r3_lo = 100, r3_hi = 129;

double integral_flux_deconv_total_Intg = 0.0;
double integral_flux_deconv_th = 0.0;
double integral_flux_deconv_ep = 0.0;
double integral_flux_deconv_fs = 0.0;
double integral_flux_deconv_he = 0.0;

for (int i = 0; i < binnum; ++i) {
    const double v = FluxMin_Intg[i];
    integral_flux_deconv_total_Intg += v;

    if      (i >= r0_lo && i < r0_hi) integral_flux_deconv_th += v;
    else if (i >= r1_lo && i < r1_hi) integral_flux_deconv_ep += v;
    else if (i >= r2_lo && i < r2_hi) integral_flux_deconv_fs += v;
    else if (i >= r3_lo && i < r3_hi) integral_flux_deconv_he += v;
}

// cout << "Integrals from sum in vector" << endl;
// cout << "Integral total flux deconv integral: " <<  setprecision(7) << integral_flux_deconv_total_Intg << endl;
// cout << "Integral thermal flux deconv integral: " <<  setprecision(7) << integral_flux_deconv_th << endl;
// cout << "Integral epithermal flux deconv integral: " <<  setprecision(7) << integral_flux_deconv_ep << endl;
// cout << "Integral fast flux deconv integral: " <<  setprecision(7) << integral_flux_deconv_fs << endl;
// cout << "Integral high energy flux deconv integral: " <<  setprecision(7) << integral_flux_deconv_he << endl;
// cout << " " <<endl;




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
FluxMin_Intg.push_back(diff_criteria);
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

//~ auto seed_flux_expacs_csv ="/home/flopez/Dropbox./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc+".csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
cout <<"Generated root file from csv file" << endl;

/*Seleccionamos los datos del flujo semilla para LCO*/
//~ auto seed_ref_cut_LCO = seed_rdf.Range(0, 158, 1); // pick an event every 1 entries from 0 to 150 because the last is excluded, that is 151 .
auto seed_ref_cut_LCO = seed_rdf.Range(0, 129, 1); // pick an event every 1 entries from 0 to 150 because the last is excluded, that is 151 .
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
//~ TH1D* neutron_flux_lethargy = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), 157, bins);
TH1D* neutron_flux_lethargy = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), d_cut_entries, bins);
for (int i = 0; i < binnum; i++)
{
	neutron_flux_lethargy->SetBinContent(i+1,Seed[i]);
}

//~ TH1D* neutron_flux_diff = new TH1D("Differential Neutron Flux","Differential Neutron Flux", 157, bins);
//~ for (int i = 0; i < binnum; i++)
//~ {
	//~ neutron_flux_diff->SetBinContent(i+1,Seed[i]/E[i]);
//~ }

//~ TH1D* group_plot = new TH1D("Group Plot","Group Plot", 157, bins);
//~ for (int i = 0; i < binnum; i++)
//~ {
	//~ group_plot->SetBinContent(i+1,(Seed[i]/E[i])*dE[i]);
//~ }

//~ TH1D* group_plot_per_energy = new TH1D("Group Plot per Energy","Group Plot per Energy", 157, bins);
//~ for (int i = 0; i < binnum; i++)
//~ {
	//~ group_plot_per_energy->SetBinContent(i+1,(Seed[i]/E[i])*E[i]);
//~ }

//~ double int_group =  group_plot->Integral();
//~ double int_group_per_energy = group_plot_per_energy->Integral();

//~ cout << "Ratio " << int_group_per_energy/int_group << endl;


//~ neutron_flux_diff->SetLineColor(kOrange);
//~ group_plot->SetLineColor(kGreen);
//~ group_plot_per_energy->SetLineColor(kBlue);
//~ neutron_flux_lethargy->SetLineColor(kRed);

//~ group_plot_per_energy->SetLineStyle(8);
//~ neutron_flux_lethargy->SetLineStyle(3);


//~ neutron_flux_diff->SetLineWidth(4);
//~ group_plot->SetLineWidth(4);
//~ group_plot_per_energy->SetLineWidth(4);
//~ neutron_flux_lethargy->SetLineWidth(4);


TCanvas *canvas_ne = new TCanvas("Neutron Spectrum","Neutron Spectrum");
//~ gPad->SetLogx();
//~ gPad->SetLogy();
neutron_flux_lethargy->GetXaxis()->SetTitle("Energy [MeV]" );
neutron_flux_lethargy->Draw("HIST");
//~ group_plot->Draw("HIST SAME");
//~ neutron_flux_diff->Draw("HIST SAME");
//~ group_plot_per_energy->Draw("HIST SAME");


auto legend = new TLegend(0.744,0.785,0.948,0.949);
legend->SetHeader("Neutron flux spectrum representation","C"); // option "C" allows to center the header
legend->AddEntry(neutron_flux_lethargy,"Expacs Flux","l");
//~ legend->AddEntry(neutron_flux_diff,"Differential Neutron Flux","l");
//~ legend->AddEntry(group_plot,"Group Plot","l");
//~ legend->AddEntry(group_plot_per_energy,"Group Plot per Energy","l");
legend->Draw();
	



}

void TRS_data_csv_to_root(){
auto fileNameCSV ="/home/flopez/Data/Dropbox/DOC_WORK/TESIS_DOC/Analysis/IAEA_REPORTS/TRS_403_DATA_Spectra_small.csv";
//~ auto df = ROOT::RDF::MakeCsvDataFrame(fileNameCSV);


char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"Elow",double_type},{"Eup", double_type},{"BinWidth", double_type},{"Cf-252", double_type},{"D2O-Cf-252", double_type},{"241Am-Be", double_type},{"241Am-B", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto df = ROOT::RDF::FromCSV(fileNameCSV,true,delimiter,-1, std::move(msdata_map));
//~ auto df = ROOT::RDF::MakeCsvDataFrame(fileNameCSV); 													
//~ df.Snapshot("MAIRE_DATA_Spectra","./MAIRE_neutron_flux_Maricunga.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
df.Snapshot("TRS_403_DATA_Spectra","../outputs/root/TRS_403_DATA_Spectra.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
}

void MAIRE_data_csv_to_root(){
//~ auto fileNameCSV ="/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/MAIRE_neutron_flux_Maricunga.csv"; // energy from 1.13E-11
auto fileNameCSV ="../data/external/EXPACS_Data/parma_cpp_flopez/MAIRE_neutron_flux_Maricunga_cut.csv"; //energy from 1.13E-09

char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"energy_diff",double_type},{"diff_flux_up", double_type},{"diff_flux_down", double_type},{"diff_flux_total", double_type},{"energy_integral", double_type},{"integral_flux", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto df = ROOT::RDF::FromCSV(fileNameCSV,true,delimiter,-1, std::move(msdata_map));
//~ auto df = ROOT::RDF::MakeCsvDataFrame(fileNameCSV); 													
df.Snapshot("MAIRE_DATA_Spectra","../outputs/root/MAIRE_neutron_flux_Maricunga.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
}


/*Graficamos los espectro diff, integral y letargico del archivo .root de salida de main.cpp de parma_cpp code*/
void neutron_flux_plot_expacs_code(){

//~ string campaign = "Chacaltaya";
string campaign = "Maricunga";
//~ string campaign = "Chapiquilta";
string name_file = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root"; 

TFile *icrp116_binning_file = new TFile("../outputs/root/ICRP116_binning.root");
TFile *maire_root_file = new TFile(("../outputs/root/MAIRE_neutron_flux_"+campaign+".root").c_str()); //Por ahora solo existe el archivo de Maricunga
//~ TFile *parma_root_file = new TFile("/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/Maricunga_parma_fluxes.root");
TFile *parma_root_file = new TFile(name_file.c_str());

string parma_tree_name = "BkgNeutronSpectra";
string icrp_tree_name = "ICRP116_binning";
string maire_tree_name = "MAIRE_DATA_Spectra";

ROOT::RDataFrame df_icrp116(icrp_tree_name, icrp116_binning_file);
ROOT::RDataFrame df_parma(parma_tree_name, parma_root_file);
ROOT::RDataFrame df_maire(maire_tree_name, maire_root_file);

/*Tomamos el espectro de un dia con un valor de humedad de suelo*/

/*Chapiquilta*/
//~ int year_input = 2024;
//~ int month_input = 11;
//~ int day_input = 18;
//~ double vwc_input = 80; // 0%-100%

/*Maricunga*/
int year_input = 2023;
int month_input = 07;
int day_input = 14;
double vwc_input = 80; // 0%-100%

/*Chacaltaya*/
//~ int year_input = 2023;
//~ int month_input = 04;
//~ int day_input = 14;
//~ double vwc_input = 80; // 0%-100%

double vwc_input_fraction = vwc_input/100.;

auto lambda_filter_flux = [&](int &year, int &month, int &day, double &vwc)
	{
		if(year_input == year && month_input == month && day_input == day && vwc_input_fraction == vwc)
			{
				return true;
			}
		else{return false;}
	};

auto df_parma_filter = df_parma.Filter(lambda_filter_flux,{"Year","Month","Day","WaterWF"});
auto vec_flux_diff = df_parma_filter.Take<vector<float>>("NeutronFdiff").GetValue();
auto vec_flux_intg = df_parma_filter.Take<vector<float>>("NeutronFint").GetValue();
auto vec_flux_let = df_parma_filter.Take<vector<float>>("NeutronFlet").GetValue();

auto latitude = df_parma_filter.Take<double>("Latitude").GetValue();
auto longitude = df_parma_filter.Take<double>("Longitude").GetValue();
auto altitude = df_parma_filter.Take<double>("Altitude").GetValue();
auto solarMod = df_parma_filter.Take<double>("SolarMod").GetValue();
auto Rigidity = df_parma_filter.Take<double>("Rigidity").GetValue();
auto AtmDepth = df_parma_filter.Take<double>("AtmDepth").GetValue();

double lat = latitude[0];
double longi = longitude[0];
double alt = altitude[0];
double W  = solarMod [0];
double RC = Rigidity[0];
double depth = AtmDepth [0];

/*MAIRE*/
auto vec_flux_diff_maire = df_maire.Take<double>("diff_flux_total").GetValue();
auto vec_flux_integral_maire = df_maire.Take<double>("integral_flux").GetValue();


cout << "vec_flux_diff size: " << vec_flux_diff.size() << endl;

int vec_flux_diff_size = vec_flux_diff[0].size();

cout << "vec_flux_diff[0] size or nbins: " << vec_flux_diff_size << endl;


/*Vector de flujos*/
//~ //binnum , bins
auto vec_low_edges = df_icrp116.Take<double>("elow").GetValue();
auto vec_emid = df_icrp116.Take<double>("emid").GetValue();
auto vec_ewid = df_icrp116.Take<double>("ewid").GetValue();

int binnum_edges =  vec_low_edges.size();
cout << "binnum edges: " << binnum_edges << endl;

/*Agregamos el borde low extra faltante, para que asi contenga el valor mas bajo de borde (1.00E-09) y el valor mas grade de borde (7.99595e+06)*/
vec_low_edges.push_back(7.99595e+06);

int binnum_new =  vec_low_edges.size(); // #bordes de bin: 160
cout << "binnum edges new: " <<vec_low_edges.size() << endl;

/*borde de bines como array*/
//Tienen que haber nbin+1 bordes de bin de tal manera de graficar nbin valores de flujo
//En nuestro caso tenemos 160 valores de bordes de bin, esto es, podemos graficar 159 valores de flujo (tenemos 160 en total)
//Entonces de los valores de flujo, sacamos el ultimo valor.

double *bins = vec_low_edges.data();

//~ int nbins = binnum_new - 1; //159


/*******************PARMA/EXPACS**************************/
string hist_name_diff = "Differential flux";

TH1D* hist_flux_diff = new TH1D(hist_name_diff.c_str(),hist_name_diff.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff->SetBinContent(i+1,vec_flux_diff[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

string hist_name_integral = "Integral flux";
TH1D* hist_integral_flux = new TH1D(hist_name_integral.c_str(),hist_name_integral.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_integral_flux->SetBinContent(i+1,vec_flux_intg[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

//~ string hist_name_lethargic = "Lethargic flux";
ostringstream oss;
oss << fixed << setprecision(1) << vwc_input;
string vwc_input_str = oss.str();

string hist_name_lethargic = "Neutron flux @"+campaign+" "+std::to_string(year_input)+"/"+std::to_string(month_input)+"/"+std::to_string(day_input)+" VWC% " + vwc_input_str;
TH1D* hist_lethargic_flux = new TH1D(hist_name_lethargic.c_str(),hist_name_lethargic.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_lethargic_flux->SetBinContent(i+1,vec_flux_let[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/******************************************************/


/*******************MAIRE**************************/

string hist_name_diff_maire = "Maire Differential flux";

TH1D* hist_flux_diff_maire = new TH1D(hist_name_diff_maire.c_str(),hist_name_diff_maire.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff_maire->SetBinContent(i+1,vec_flux_diff_maire[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

string hist_name_integral_maire = "Maire Integral flux";
TH1D* hist_integral_flux_maire = new TH1D(hist_name_integral_maire.c_str(),hist_name_integral_maire.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_integral_flux_maire->SetBinContent(i+1,vec_flux_integral_maire[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/******************************************************/



/*Reconstruyamos el flujo diferencial a partir del flujo letargico, tal y como lo he hecho hasta ahora,
 * dado que el flujo salida de EXPACS (archivos csv) esta en la representacion letargica: Flux[ip][ie]*emid[ie]= DiffFlux*emid*/

/********Flujo semilla diferencial para el algortimo EM*********/
int vec_flux_size = vec_flux_let[0].size();
vector<float> Flux_diff_calc;

for (int i = 0; i<vec_flux_size; i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		float E_mid = vec_low_edges[i]+(vec_ewid[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux_diff_calc.push_back(vec_flux_let[0][i]/(E_mid)); /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}


string hist_name_diff_calc = "Differential flux calculated";

TH1D* hist_flux_diff_calc = new TH1D(hist_name_diff_calc.c_str(),hist_name_diff_calc.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff_calc->SetBinContent(i+1,Flux_diff_calc[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/***********************************************************************/

ostringstream lat_stream, longi_stream, alt_stream,w_stream, rc_stream, depth_stream;
lat_stream << fixed << setprecision(1) << lat;
longi_stream << fixed << setprecision(1) << longi;
alt_stream << fixed << setprecision(1) << alt;
w_stream << fixed << setprecision(1) << W;
rc_stream << fixed << setprecision(1) << RC;
depth_stream << fixed << setprecision(1) << depth;
string lat_str = lat_stream.str();
string longi_str = longi_stream.str();
string alt_str = alt_stream.str();
string w_str = w_stream.str();
string rc_str = rc_stream.str();
string depth_str = depth_stream.str();

string coord = "Coord: ("+lat_str+","+longi_str+")";
string altitude_str = "Alt: "+alt_str+" m.a.s.l";
string w_format = "W: "+ w_str;
string rc_format = "R_{c}: "+ rc_str+" (GV)";
string depth_format = "Depth : "+ depth_str+" (g/cm^{2})";

TLatex *l_coord = new TLatex(0.75,0.60, coord.c_str());
TLatex *l_alt = new TLatex(0.75,0.55, altitude_str.c_str());
TLatex *l_w = new TLatex(0.75,0.50, w_format.c_str());
TLatex *l_rc = new TLatex(0.75,0.45, rc_format.c_str());
TLatex *l_d = new TLatex(0.75,0.40, depth_format.c_str());

l_coord->SetNDC();
l_coord->SetTextSize(0.03);
l_alt->SetNDC();
l_alt->SetTextSize(0.03);
l_w->SetNDC();
l_w->SetTextSize(0.03);
l_rc->SetNDC();
l_rc->SetTextSize(0.03);
l_d->SetNDC();
l_d->SetTextSize(0.03);



/************************************************************************/

TCanvas *canvas_diff_flux = new TCanvas("Diff Flux","Diff Flux",1920,1080);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas
gPad->SetLogx();
gPad->SetLogy();
hist_flux_diff->GetXaxis()->SetTitle("Energy [MeV]");
hist_flux_diff->GetXaxis()->SetTitleOffset(1.2);
hist_flux_diff->GetYaxis()->SetTitle("Differential flux cm^{-1} s^{-1} MeV^{-1}");
hist_flux_diff->GetYaxis()->CenterTitle();
hist_flux_diff_calc->SetLineColor(kRed);

hist_flux_diff->DrawClone("HIST");
hist_flux_diff_calc->DrawClone("HIST SAME");
canvas_diff_flux->Draw();


TCanvas *canvas_integral_flux = new TCanvas("Integral Flux","Integral Flux",1920,1080);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas
gPad->SetLogx();
//~ gPad->SetLogy();
hist_lethargic_flux->GetXaxis()->SetTitle("#bf{Energy (MeV)}");
hist_lethargic_flux->GetXaxis()->SetTitleOffset(1.2);
hist_lethargic_flux->GetYaxis()->SetTitle("#bf{Neutron flux (cm^{-1} s^{-1})}");
hist_lethargic_flux->GetYaxis()->CenterTitle();
hist_lethargic_flux->SetLineColor(kRed);
//~ hist_integral_flux_maire->SetLineColor(kGreen);

TLegend *legend_c = new TLegend(0.188853,0.736895,0.607143,0.889113);
legend_c->AddEntry(hist_lethargic_flux,"Flux per unit lethargy #bf{E#times#it{#phi}(E) (cm^{-2} s^{-1} lethargy^{-1})}","l");
legend_c->AddEntry(hist_integral_flux,"Flux group representation #bf{#Phi(E) (cm^{-2} s^{-1})}","l");

hist_lethargic_flux->DrawClone("HIST");
hist_integral_flux->DrawClone("HIST SAME");
//~ hist_integral_flux_maire->DrawClone("HIST SAME");
l_coord->Draw("SAME");
l_alt->Draw("SAME");
l_w->Draw("SAME");
l_rc->Draw("SAME");
l_d->Draw("SAME");
legend_c->Draw();
canvas_integral_flux->Draw();

}

/*Graficamos los espectro diff, integral y letargico del archivo .root de salida de main.cpp de parma_cpp code tanto para g entre 0 y 1, y g =10 (no earth)
 * Ademas se grafican los flujos obtenidos con MAIRE*/
void neutron_flux_plot_maire(){

//~ string campaign = "Chacaltaya";
string campaign = "Maricunga";
//~ string campaign = "Chapiquilta";
string name_file = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root"; 
string name_file_no_earth = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes_no_earth.root"; 
string name_file_blackhole = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes_blackhole.root"; 

TFile *icrp116_binning_file = new TFile("../outputs/root/ICRP116_binning.root");
TFile *maire_root_file = new TFile(("../outputs/root/MAIRE_neutron_flux_"+campaign+".root").c_str()); //Por ahora solo existe el archivo de Maricunga
//~ TFile *parma_root_file = new TFile("/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/Maricunga_parma_fluxes.root");
TFile *parma_root_file = new TFile(name_file.c_str());
TFile *parma_root_file_no_earth = new TFile(name_file_no_earth.c_str());
TFile *parma_root_file_blackhole = new TFile(name_file_blackhole.c_str());

string parma_tree_name = "BkgNeutronSpectra";
string icrp_tree_name = "ICRP116_binning";
string maire_tree_name = "MAIRE_DATA_Spectra";

ROOT::RDataFrame df_icrp116(icrp_tree_name, icrp116_binning_file);
ROOT::RDataFrame df_parma(parma_tree_name, parma_root_file);
ROOT::RDataFrame df_maire(maire_tree_name, maire_root_file);
ROOT::RDataFrame df_parma_no_earth(parma_tree_name, parma_root_file_no_earth);
ROOT::RDataFrame df_parma_blackhole(parma_tree_name, parma_root_file_blackhole);

/*Tomamos el espectro de un dia con un valor de humedad de suelo*/

/*Chapiquilta*/
//~ int year_input = 2024;
//~ int month_input = 11;
//~ int day_input = 18;
//~ double vwc_input = 80; // 0%-100%

/*Maricunga*/
int year_input = 2023;
int month_input = 07;
int day_input = 14;
double vwc_input = 80; // 0%-100%

/*Chacaltaya*/
//~ int year_input = 2023;
//~ int month_input = 04;
//~ int day_input = 14;
//~ double vwc_input = 80; // 0%-100%

double vwc_input_fraction = vwc_input/100.;

auto lambda_filter_flux = [&](int &year, int &month, int &day, double &vwc)
	{
		if(year_input == year && month_input == month && day_input == day && vwc_input_fraction == vwc)
			{
				return true;
			}
		else{return false;}
	};
	
auto lambda_filter_flux_ymd = [&](int &year, int &month, int &day)
	{
		if(year_input == year && month_input == month && day_input == day)
			{
				return true;
			}
		else{return false;}
	};



auto df_parma_filter = df_parma.Filter(lambda_filter_flux,{"Year","Month","Day","WaterWF"});
auto vec_flux_diff = df_parma_filter.Take<vector<float>>("NeutronFdiff").GetValue();
auto vec_flux_intg = df_parma_filter.Take<vector<float>>("NeutronFint").GetValue();
auto vec_flux_let = df_parma_filter.Take<vector<float>>("NeutronFlet").GetValue();

auto latitude = df_parma_filter.Take<double>("Latitude").GetValue();
auto longitude = df_parma_filter.Take<double>("Longitude").GetValue();
auto altitude = df_parma_filter.Take<double>("Altitude").GetValue();
auto solarMod = df_parma_filter.Take<double>("SolarMod").GetValue();
auto Rigidity = df_parma_filter.Take<double>("Rigidity").GetValue();
auto AtmDepth = df_parma_filter.Take<double>("AtmDepth").GetValue();

double lat = latitude[0];
double longi = longitude[0];
double alt = altitude[0];
double W  = solarMod [0];
double RC = Rigidity[0];
double depth = AtmDepth [0];

/************PARMA_EXPCAS NO EARTH******/

auto df_parma_filter_no_earth = df_parma_no_earth.Filter(lambda_filter_flux_ymd,{"Year","Month","Day"});
auto vec_flux_diff_no_earth = df_parma_filter_no_earth.Take<vector<float>>("NeutronFdiff").GetValue();
auto vec_flux_intg_no_earth = df_parma_filter_no_earth.Take<vector<float>>("NeutronFint").GetValue();
auto vec_flux_let_no_earth= df_parma_filter_no_earth.Take<vector<float>>("NeutronFlet").GetValue();

cout << "vec_flux_diff size parma (no earth): " << vec_flux_diff_no_earth.size() << endl;

int vec_flux_diff_size_no_earth = vec_flux_diff_no_earth[0].size();

/************************/

/************PARMA_EXPCAS BLACKHOLE******/

auto df_parma_filter_blackhole = df_parma_blackhole.Filter(lambda_filter_flux_ymd,{"Year","Month","Day"});
auto vec_flux_diff_blackhole = df_parma_filter_blackhole.Take<vector<float>>("NeutronFdiff").GetValue();
auto vec_flux_intg_blackhole = df_parma_filter_blackhole.Take<vector<float>>("NeutronFint").GetValue();
auto vec_flux_let_blackhole= df_parma_filter_blackhole.Take<vector<float>>("NeutronFlet").GetValue();

cout << "vec_flux_diff size parma (blackhole): " << vec_flux_diff_blackhole.size() << endl;

int vec_flux_diff_size_blackhole = vec_flux_diff_blackhole[0].size();

/************************/

cout << "vec_flux_diff size parma: " << vec_flux_diff.size() << endl;

int vec_flux_diff_size = vec_flux_diff[0].size();

cout << "vec_flux_diff[0] size or nbins parma: " << vec_flux_diff_size << endl;


/*Vector de flujos*/
//~ //binnum , bins
auto vec_low_edges = df_icrp116.Take<double>("elow").GetValue();
auto vec_emid = df_icrp116.Take<double>("emid").GetValue();
auto vec_ewid = df_icrp116.Take<double>("ewid").GetValue();

int binnum_edges =  vec_low_edges.size();
cout << "binnum edges parma: " << binnum_edges << endl;

/*Agregamos el borde low extra faltante, para que asi contenga el valor mas bajo de borde (1.00E-09) y el valor mas grade de borde (7.99595e+06)*/
vec_low_edges.push_back(7.99595e+06);

int binnum_new =  vec_low_edges.size(); // #bordes de bin: 160
cout << "binnum edges new parma: " <<vec_low_edges.size() << endl;

/*borde de bines como array*/
//Tienen que haber nbin+1 bordes de bin de tal manera de graficar nbin valores de flujo
//En nuestro caso tenemos 160 valores de bordes de bin, esto es, podemos graficar 159 valores de flujo (tenemos 160 en total)
//Entonces de los valores de flujo, sacamos el ultimo valor.

double *bins = vec_low_edges.data();

//~ int nbins = binnum_new - 1; //159


/*******************PARMA/EXPACS**************************/
string hist_name_diff = "Differential flux";
string hist_name_diff_no_earth = "Differential flux no earth";
string hist_name_diff_blackhole = "Differential flux blackhole";

TH1D* hist_flux_diff = new TH1D(hist_name_diff.c_str(),hist_name_diff.c_str(), binnum_edges, bins);
TH1D* hist_flux_diff_no_earth = new TH1D(hist_name_diff_no_earth.c_str(),hist_name_diff_no_earth.c_str(), binnum_edges, bins);
TH1D* hist_flux_diff_blackhole = new TH1D(hist_name_diff_blackhole.c_str(),hist_name_diff_blackhole.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff->SetBinContent(i+1,vec_flux_diff[0][i]); // del 1 al 159
	hist_flux_diff_no_earth->SetBinContent(i+1,vec_flux_diff_no_earth[0][i]); // del 1 al 159
	hist_flux_diff_blackhole->SetBinContent(i+1,vec_flux_diff_blackhole[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

string hist_name_integral = "Integral flux";
string hist_name_integral_no_earth = "Integral flux no earth";
string hist_name_integral_blackhole = "Integral flux blackhole";

TH1D* hist_integral_flux = new TH1D(hist_name_integral.c_str(),hist_name_integral.c_str(), binnum_edges, bins);
TH1D* hist_integral_flux_no_earth = new TH1D(hist_name_integral_no_earth.c_str(),hist_name_integral_no_earth.c_str(), binnum_edges, bins);
TH1D* hist_integral_flux_blackhole = new TH1D(hist_name_integral_blackhole.c_str(),hist_name_integral_blackhole.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_integral_flux->SetBinContent(i+1,vec_flux_intg[0][i]); // del 1 al 159
	hist_integral_flux_no_earth->SetBinContent(i+1,vec_flux_intg_no_earth[0][i]); // del 1 al 159
	hist_integral_flux_blackhole->SetBinContent(i+1,vec_flux_intg_blackhole[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

//~ string hist_name_lethargic = "Lethargic flux";
ostringstream oss;
oss << fixed << setprecision(1) << vwc_input;
string vwc_input_str = oss.str();

string hist_name_lethargic = "Neutron flux @"+campaign+" "+std::to_string(year_input)+"/"+std::to_string(month_input)+"/"+std::to_string(day_input)+" VWC% " + vwc_input_str;
string hist_name_lethargic_no_earth = "Neutron flux @"+campaign+" "+std::to_string(year_input)+"/"+std::to_string(month_input)+"/"+std::to_string(day_input)+" VWC% " + vwc_input_str+" no earth";
string hist_name_lethargic_blackhole = "Neutron flux @"+campaign+" "+std::to_string(year_input)+"/"+std::to_string(month_input)+"/"+std::to_string(day_input)+" VWC% " + vwc_input_str+" blackhole";
TH1D* hist_lethargic_flux = new TH1D(hist_name_lethargic.c_str(),hist_name_lethargic.c_str(), binnum_edges, bins);
TH1D* hist_lethargic_flux_no_earth = new TH1D(hist_name_lethargic_no_earth.c_str(),hist_name_lethargic_no_earth.c_str(), binnum_edges, bins);
TH1D* hist_lethargic_flux_blackhole = new TH1D(hist_name_lethargic_blackhole.c_str(),hist_name_lethargic_blackhole.c_str(), binnum_edges, bins);

//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_lethargic_flux->SetBinContent(i+1,vec_flux_let[0][i]); // del 1 al 159
	hist_lethargic_flux_no_earth->SetBinContent(i+1,vec_flux_let_no_earth[0][i]); // del 1 al 159
	hist_lethargic_flux_blackhole->SetBinContent(i+1,vec_flux_let_blackhole[0][i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/******************************************************/


/***Para Maire tenemos solo 145 bordes inferiores de bin, desde el 1.13E-09 hasta el 2.84E+05***/

/*********************MAIRE**********************/
auto vec_flux_diff_maire = df_maire.Take<double>("diff_flux_total").GetValue();
auto vec_flux_integral_maire = df_maire.Take<double>("integral_flux").GetValue();

auto vec_emid_maire = df_maire.Take<double>("energy_diff").GetValue();
auto vec_low_edges_maire = df_maire.Take<double>("energy_integral").GetValue();

int binnum_edges_maire =  vec_low_edges_maire.size();
cout << "binnum edges maire: " << binnum_edges_maire << endl;



//Sacamos los ultimos 5 valores

vector<double> vec_low_edges_maire_new;
for(int i=0;i<vec_low_edges_maire.size()-5;i++){
	vec_low_edges_maire_new.push_back( vec_low_edges_maire[i]);
}

int binnum_edges_maire_new =  vec_low_edges_maire_new.size();
cout << "binnum edges maire_new: " << binnum_edges_maire_new << endl;

double *bins_maire_new = vec_low_edges_maire_new.data();

/*******************************************/

/*******************MAIRE**************************/

string hist_name_diff_maire = "Maire Differential flux";

TH1D* hist_flux_diff_maire = new TH1D(hist_name_diff_maire.c_str(),hist_name_diff_maire.c_str(), binnum_edges_maire_new, bins_maire_new);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_edges_maire_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff_maire->SetBinContent(i+1,vec_flux_diff_maire[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

string hist_name_integral_maire = "Maire Integral flux";
TH1D* hist_integral_flux_maire = new TH1D(hist_name_integral_maire.c_str(),hist_name_integral_maire.c_str(), binnum_edges_maire_new, bins_maire_new);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_edges_maire_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_integral_flux_maire->SetBinContent(i+1,vec_flux_integral_maire[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/*Maire Integral flux calculated*/

vector<double> Flux_maire_integral_calc;

for (int i = 0; i<vec_low_edges_maire_new.size(); i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		float E_wid = vec_ewid[i]; // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux_maire_integral_calc.push_back(vec_flux_diff_maire[i]*vec_ewid[i]); /*Tenems el flujo diff de MAIRE, para pasarlo a flujo integral multiplicamos por ewid*/
	}


string hist_name_integral_maire_cal = "Maire Integral flux calculated";
TH1D* hist_integral_flux_maire_cal = new TH1D(hist_name_integral_maire_cal.c_str(),hist_name_integral_maire_cal.c_str(), binnum_edges_maire_new, bins_maire_new);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_edges_maire_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_integral_flux_maire_cal->SetBinContent(i+1,Flux_maire_integral_calc[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/*Maire Lethargic flux calculated*/

vector<double> Flux_maire_lethargic_calc;

for (int i = 0; i<vec_low_edges_maire_new.size(); i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		float E_wid = vec_ewid[i]; // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux_maire_lethargic_calc.push_back(vec_flux_diff_maire[i]*vec_emid_maire[i]); /*Tenems el flujo diff de MAIRE, para pasarlo a flujo integral multiplicamos por ewid*/
	}


string hist_name_lethargic_maire_cal = "Maire lethargic flux calculated";
TH1D* hist_lethargic_flux_maire_cal = new TH1D(hist_name_lethargic_maire_cal.c_str(),hist_name_lethargic_maire_cal.c_str(), binnum_edges_maire_new, bins_maire_new);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_edges_maire_new ; i++)
{
	//bin# 0 contains the underflow.
	 hist_lethargic_flux_maire_cal->SetBinContent(i+1, Flux_maire_lethargic_calc[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}



/******************************************************/



/*Reconstruyamos el flujo diferencial a partir del flujo letargico, tal y como lo he hecho hasta ahora,
 * dado que el flujo salida de EXPACS (archivos csv) esta en la representacion letargica: Flux[ip][ie]*emid[ie]= DiffFlux*emid*/

/********Flujo semilla diferencial para el algortimo EM*********/
int vec_flux_size = vec_flux_let[0].size();
vector<float> Flux_diff_calc;

for (int i = 0; i<vec_flux_size; i++)
	{
		//~ double E_mid = E[i]+(dE[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		float E_mid = vec_low_edges[i]+(vec_ewid[i]/2.); // bin: [Elow,Eup], luego E[i] =Elow y Eup-Elow = dE[i], entonces, Emid = Elow + dE/2.
		Flux_diff_calc.push_back(vec_flux_let[0][i]/(E_mid)); /*expacs entrega el flujo letargico, para pasarlo a flujo diff dividimos por E_mid*/
	}


string hist_name_diff_calc = "Differential flux calculated";

TH1D* hist_flux_diff_calc = new TH1D(hist_name_diff_calc.c_str(),hist_name_diff_calc.c_str(), binnum_edges, bins);
//Lenamos el histograma, sacando el ultimo valor
for (int i = 0; i < binnum_new ; i++)
{
	//bin# 0 contains the underflow.
	hist_flux_diff_calc->SetBinContent(i+1,Flux_diff_calc[i]); // del 1 al 159
	// The last bin (bin# nbins+1) contains the overflow.
}

/***********************************************************************/

ostringstream lat_stream, longi_stream, alt_stream,w_stream, rc_stream, depth_stream;
lat_stream << fixed << setprecision(1) << lat;
longi_stream << fixed << setprecision(1) << longi;
alt_stream << fixed << setprecision(1) << alt;
w_stream << fixed << setprecision(1) << W;
rc_stream << fixed << setprecision(1) << RC;
depth_stream << fixed << setprecision(1) << depth;
string lat_str = lat_stream.str();
string longi_str = longi_stream.str();
string alt_str = alt_stream.str();
string w_str = w_stream.str();
string rc_str = rc_stream.str();
string depth_str = depth_stream.str();

string coord = "Coord: ("+lat_str+","+longi_str+")";
string altitude_str = "Alt: "+alt_str+" m.a.s.l";
string w_format = "W: "+ w_str;
string rc_format = "R_{c}: "+ rc_str+" (GV)";
string depth_format = "Depth : "+ depth_str+" (g/cm^{2})";

TLatex *l_coord = new TLatex(0.75,0.60, coord.c_str());
TLatex *l_alt = new TLatex(0.75,0.55, altitude_str.c_str());
TLatex *l_w = new TLatex(0.75,0.50, w_format.c_str());
TLatex *l_rc = new TLatex(0.75,0.45, rc_format.c_str());
TLatex *l_d = new TLatex(0.75,0.40, depth_format.c_str());

l_coord->SetNDC();
l_coord->SetTextSize(0.03);
l_alt->SetNDC();
l_alt->SetTextSize(0.03);
l_w->SetNDC();
l_w->SetTextSize(0.03);
l_rc->SetNDC();
l_rc->SetTextSize(0.03);
l_d->SetNDC();
l_d->SetTextSize(0.03);



/************************************************************************/

TCanvas *canvas_diff_flux = new TCanvas("Diff Flux","Diff Flux",1920,1080);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas
gPad->SetLogx();
gPad->SetLogy();
hist_flux_diff->GetXaxis()->SetTitle("Energy [MeV]");
hist_flux_diff->GetXaxis()->SetTitleOffset(1.2);
hist_flux_diff->GetYaxis()->SetTitle("Differential flux cm^{-1} s^{-1} MeV^{-1}");
hist_flux_diff->GetYaxis()->CenterTitle();
hist_flux_diff->SetLineColor(kRed);
hist_flux_diff_no_earth->SetLineColor(kBlack);
hist_flux_diff_maire->SetLineColor(kGreen);
hist_flux_diff_blackhole->SetLineColor(kViolet);

hist_flux_diff->DrawClone("HIST");
hist_flux_diff_no_earth->DrawClone("HIST SAME");
hist_flux_diff_maire->DrawClone("HIST SAME");
hist_flux_diff_blackhole->DrawClone("HIST SAME");
//~ hist_flux_diff_calc->DrawClone("HIST SAME");
canvas_diff_flux->Draw();


TCanvas *canvas_integral_flux = new TCanvas("Integral Flux","Integral Flux",1920,1080);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas
gPad->SetLogx();
//~ gPad->SetLogy();
hist_lethargic_flux->GetXaxis()->SetTitle("#bf{Energy (MeV)}");
hist_lethargic_flux->GetXaxis()->SetTitleOffset(1.2);
hist_lethargic_flux->GetYaxis()->SetTitle("#bf{Neutron flux (cm^{-1} s^{-1})}");
hist_lethargic_flux->GetYaxis()->CenterTitle();
hist_lethargic_flux->SetLineColor(kRed);
hist_lethargic_flux_no_earth->SetLineColor(kBlack);
hist_lethargic_flux_blackhole->SetLineColor(kViolet);
hist_integral_flux->SetLineColor(kBlue);
hist_integral_flux_no_earth->SetLineColor(kMagenta);
hist_integral_flux_blackhole->SetLineColor(kViolet);
hist_integral_flux_maire_cal->SetLineColor(kGreen);
hist_lethargic_flux_maire_cal->SetLineColor(kCyan);
hist_lethargic_flux_maire_cal->SetTitle(hist_name_lethargic.c_str());

TLegend *legend_c = new TLegend(0.137987,0.737903,0.56277,0.890121);
legend_c->AddEntry(hist_lethargic_flux,"PARMA Flux per unit lethargy #bf{E#times#it{#phi}(E) (cm^{-2} s^{-1} lethargy^{-1})}","l");
legend_c->AddEntry(hist_lethargic_flux_no_earth,"PARMA (no earth) Flux per unit lethargy #bf{E#times#it{#phi}(E) (cm^{-2} s^{-1} lethargy^{-1})}","l");
legend_c->AddEntry(hist_lethargic_flux_blackhole,"PARMA (blackhole) Flux per unit lethargy #bf{E#times#it{#phi}(E) (cm^{-2} s^{-1} lethargy^{-1})}","l");
legend_c->AddEntry(hist_integral_flux,"PARMA Flux group representation #bf{#Phi(E) (cm^{-2} s^{-1})}","l");
legend_c->AddEntry(hist_integral_flux_no_earth,"PARMA (no earth) Flux group representation #bf{#Phi(E) (cm^{-2} s^{-1})}","l");
legend_c->AddEntry(hist_integral_flux_blackhole,"PARMA (blackhole) Flux group representation #bf{#Phi(E) (cm^{-2} s^{-1})}","l");
legend_c->AddEntry(hist_integral_flux_maire_cal,"Maire Flux group representation #bf{#Phi(E) (cm^{-2} s^{-1})}","l");
legend_c->AddEntry(hist_lethargic_flux_maire_cal,"Maire Flux per unit lethargy #bf{#Phi(E) (cm^{-2} s^{-1})}","l");


hist_lethargic_flux_maire_cal->DrawClone("HIST");
hist_lethargic_flux->DrawClone("HIST SAME");
hist_lethargic_flux_no_earth->DrawClone("HIST SAME");
hist_lethargic_flux_blackhole->DrawClone("HIST SAME");
hist_integral_flux->DrawClone("HIST SAME");
hist_integral_flux_no_earth->DrawClone("HIST SAME");
hist_integral_flux_blackhole->DrawClone("HIST SAME");
//~ hist_integral_flux_maire->DrawClone("HIST");
hist_integral_flux_maire_cal->DrawClone("HIST SAME");

l_coord->Draw("SAME");
l_alt->Draw("SAME");
l_w->Draw("SAME");
l_rc->Draw("SAME");
l_d->Draw("SAME");
legend_c->Draw();
canvas_integral_flux->Draw();

}


/*Funcion que genera el archivo de binning a utilizar en los espectros a partir del archivo ICRP116_new.inp*/
void generates_binning_file(){

/*****************READ INPUT FILES********************************/
//Read Dose Conversion Coefficient Data
// 1) Open file "dcc/dccname.inp" for reading
ifstream dccf("../configs/ICRP116_new.inp", ios::in);
//~ ifstream dccf("/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/dcc/ICRP116.inp", ios::in); // archivo original
string str;
// 2) Read (and discard) the first two lines (usually headers or titles)
getline(dccf, str);
getline(dccf, str);
// 3) For each energy bin (1 to nebin), read one line of data
//~ int nebin = 140; // codigo original
static constexpr int nebin = 160;
//~ int nebin = 160;
double emid[nebin+2],ewid[nebin+2]; //arrays double

for (int i = 1; i <= nebin; i++)
	{
		getline(dccf, str);          // Read a line into 'str'
		istringstream dccf1(str);    // Create a stream from 'str' for parsing

		// a) Read the mid-point energy of the bin into emid[ie]
		// b) Read the width of the energy bin into ewid[ie]
		dccf1 >> emid[i] >> ewid[i];
		// c) For each particle type (from 0 to npart), read the corresponding DCC value
		//    and store it in dcc[ip][ie].
		//~ for (ip = 0; ip <= npart; ip++)
			//~ {
				//~ dccf1 >> dcc[ip][ie];
			//~ }
	}

emid[nebin+1]=0.0;
ewid[nebin+1]=1.0;

//array to vec
vector<double> vec_emid(begin(emid), end(emid))	;
vector<double> vec_ewid(begin(ewid), end(ewid));

cout << "vec_emid size:" << vec_emid.size() << endl;
cout << "vec_ewid size:" << vec_ewid.size() << endl;


/*Calculamos ahora los bordes de bin*/
vector<double> vec_Elower(nebin-1,0);
vector<double> vec_Eupper(nebin-1,0);




for(int i=1; i<nebin;i++){
 double elower = sqrt(vec_emid[i-1]*vec_emid[i]);
 double eupper = sqrt(vec_emid[i]*vec_emid[i+1]);
 //~ vec_Elower.push_back(elower);
 cout << " i " << i << " elower " << elower << endl;
 vec_Elower[i] = elower;
 vec_Eupper.push_back(eupper);
}

vec_Elower[1]= 0.000000001;

for (int i=0;i<vec_emid.size();i++){

	cout << i << " " << vec_emid[i] << "   " << vec_ewid[i] << " " <<  vec_Elower[i] << " " <<  vec_Eupper[i] << endl;
	}

cout << "vec_Elower size: " << vec_Elower.size() << endl;

ROOT::RDataFrame df_binning(nebin-1);

int rowid_emid = 1;
int rowid_ewid = 1;
int rowid_elow = 1;

auto df_final = df_binning.Define("emid", [&]() {
						 return vec_emid[rowid_emid++];
						})
						.Define("ewid", [&]() {
						 return vec_ewid[rowid_ewid++];
						})
						.Define("elow", [&]() {
						 return vec_Elower[rowid_elow++];
						});

df_final.Snapshot("ICRP116_binning","../outputs/root/ICRP116_binning.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/

}





void TRS_plot_spectra(){

TFile *TRS_Spectra_file = new TFile("../outputs/root/TRS_403_DATA_Spectra.root");

ROOT::RDataFrame df_TRS_403("TRS_403_DATA_Spectra", TRS_Spectra_file);

/*Generamos un vector de bordes (elow) de energia*/
auto elow_vec = df_TRS_403.Take<double>("Elow").GetValue();
auto eup_vec = df_TRS_403.Take<double>("Eup").GetValue();
int eup_vec_size = eup_vec.size();

/*Generamos un vector de flujos de energia*/
auto cf252_spectrum_vec = df_TRS_403.Take<double>("Cf-252").GetValue();
auto Am241Be_spectrum_vec = df_TRS_403.Take<double>("241Am-Be").GetValue();

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

TH1D* neutron_fluence_214AmBe = new TH1D("Neutron Fluence 214Am-Be","Neutron Fluence 241Am-Be",binnum , bins);
for (int i = 0; i < binnum; i++)
{
	neutron_fluence_214AmBe ->SetBinContent(i+1,Am241Be_spectrum_vec[i]);
}

//~ neutron_fluence_214AmB ->Scale(100);


TCanvas *canvas_spectra = new TCanvas("Neutron Spectrum","Neutron Spectrum");
gPad->SetLogx();
//~ gPad->SetLogy();
neutron_fluence_214AmBe->GetXaxis()->SetTitle("Energy [MeV]");
neutron_fluence_214AmBe->GetYaxis()->SetTitle("Fluence per unit log energy [cm^{-2} lethargy^{-1}]");

neutron_fluence_cf252->SetLineWidth(4);
neutron_fluence_cf252->SetLineColor(kBlue);
neutron_fluence_214AmBe->SetLineWidth(4);
neutron_fluence_214AmBe->SetLineColor(kRed);

neutron_fluence_214AmBe->GetXaxis()->SetRangeUser(1E-2,1E+2);
neutron_fluence_214AmBe->GetYaxis()->SetRangeUser(0,0.8);

neutron_fluence_214AmBe->Draw("HIST");
neutron_fluence_cf252->Draw("HIST SAME");


auto legend = new TLegend(0.744,0.785,0.948,0.949);
legend->SetHeader("Neutron fluence per unit lethargy","C"); // option "C" allows to center the header
legend->AddEntry(neutron_fluence_cf252,"Cf-252","l");
legend->AddEntry(neutron_fluence_214AmBe,"241Am-Be","l");
legend->Draw();


}

/***Funcion que itera sobre todos los distintos valores de semilla sobre deconv_em_output()***/
void em_loop_seed(string campaign,int event,int steps,int time_grid, int max_steps,string cut){

ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
stream_steps << steps;
stream_event << event; 
stream_timegrid << time_grid;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_em_it;


//~ ROOT::RDataFrame df_seed_loop_i(51);

//186 en total (archivos): 1-151: 151, 32-100 (2 en 2): 35. Entonces 151+35=186
//~ int number_of_seeds = 151; //RetenDesierto
int number_of_seeds = 186; //LCO, Maricunga, Chapiquilta
//~ ROOT::RDataFrame df_seed_loop_i(186);
ROOT::RDataFrame df_seed_loop_i(number_of_seeds);

vector<vector<Double_t> > vec_loop_seed;

/**Iteramos sobre las semillas**/
//186 en total (archivos): 1-151: 151, 32-100 (2 en 2): 35. Entonces 151+35=186
//~ for(int i=0; i<186;i++)
for(int i=0; i<number_of_seeds;i++)
	{
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Starting ... "<< endl;
		vec_loop_seed.push_back(deconv_em_output(campaign,event,steps,i,time_grid,"Intg",0,max_steps,cut));
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Finished. "<< endl;
		cout << " " << endl;
    }

/*Definimos los bordes de bin de los VWC%*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
for(int i=0;i<number_of_seeds;i++)
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
//~ vector<int> cut_vec_ndet =  {vec_loop_seed_elem.end() - 12, vec_loop_seed_elem.end()-11};
vector<int> cut_vec_ndet =  {vec_loop_seed_elem.end() - 13, vec_loop_seed_elem.end()-12};
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
int rowid_diff_criteria = 0;
int rowid_xi2 = 0;
int rowid_bardelta = 0;
int rowid_std = 0;
int rowid_bin_seed = 0;
int rowid_em_it = 0;

auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
									  auto vec_loop_seed_element =  vec_loop_seed[rowid_deconv];
									  //~ vector<Double_t> deconv_vec = {vec_loop_seed_element.begin(), vec_loop_seed_element.end() - 12};
									  vector<Double_t> deconv_vec = {vec_loop_seed_element.begin(), vec_loop_seed_element.end() - 13};
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
									  //~ vector<int> cut_vec_ndet = {vec_loop_element.end() - 12, vec_loop_element.end()-11};
									  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
									  int ndet = cut_vec_ndet[0];
									  rowid_ndet++;
									  return ndet;
									  })
									.Define("Intg_total", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_total];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_total = cut_vec_intg[0];
									  rowid_intg_total++;
									  return Intg_total;
									  })
									.Define("Intg_th", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_th];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_th = cut_vec_intg[1];
									  rowid_intg_th++;
									  return Intg_th;
									  })
									.Define("Intg_ep", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_ep];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_ep = cut_vec_intg[2];
									  rowid_intg_ep++;
									  return Intg_ep;
									  })
									.Define("Intg_fs", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_fs];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_fs = cut_vec_intg[3];
									  rowid_intg_fs++;
									  return Intg_fs;
									  })
									.Define("Intg_he", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_he];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_he = cut_vec_intg[4];
									  rowid_intg_he++;
									  return Intg_he;
									  })                                                                                           
									.Define("Chi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  double Chi2_value = cut_vec[0];
									  rowid_Chi2++;
									  return Chi2_value;
									})
									.Define("Chi2red", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2red];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double Chi2red_value = cut_vec[1];
									  double Chi2red_value = cut_vec[1];
									  rowid_Chi2red++;
									  return Chi2red_value;
									})
									.Define("diff_criteria", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_diff_criteria];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  double diff_criteria_value = cut_vec[2];
									  rowid_diff_criteria++;
									  return diff_criteria_value;
									})
									.Define("xi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_xi2];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double xi2_value = cut_vec[2];
									  double xi2_value = cut_vec[3];
									  rowid_xi2++;
									  return xi2_value;
									})
									.Define("barDelta", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_bardelta];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double bardelta_value = cut_vec[3];
									  double bardelta_value = cut_vec[4];
									  rowid_bardelta++;
									  return bardelta_value;
									})
									.Define("std_cr", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_std];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double std_cr_value = cut_vec[4];
									  double std_cr_value = cut_vec[5];
									  rowid_std++;
									  return std_cr_value;
									})
									.Define("em_it", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_em_it];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double em_it_value = cut_vec[5];
									  double em_it_value = cut_vec[6];
									  rowid_em_it++;
									  return em_it_value;
									});

ostringstream stream_ndet; 
stream_ndet << ndet;
string str_stream_ndet = stream_ndet.str();

string df_file_name;
if(steps==0)
	{
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	}
else{	
		df_file_name = "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	}

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

}

/***Funcion que itera sobre todos los distintos valores de semilla sobre deconv_em_output_update() para un evento determinado, para esto usamos como input un archivo .root con los flujos calculados con EXPACS***/
void em_loop_seed_update(string campaign,int event,int steps,int time_grid, int max_steps,string cut, string physic_list, string scale_factor, string neufield_type){

ostringstream stream_steps, stream_event, stream_timegrid, stream_em_it;
stream_steps << steps;
stream_event << event; 
stream_timegrid << time_grid;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_em_it;

string campaign_path;

if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign+"_QGSP_BERT"; //Ex: LCO
	  cout << physic_list+" em_loop_seed_update() Physic_list" << endl;
	}
else if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
	 cout << physic_list+" em_loop_seed_update() Physic_list" << endl;
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string campaign_path_new = campaign_path+"_"+neufield_type;

/*****************************************************************************************************/
/********************************CARGAMOS EL BINEADO ICRP116*****************************************/
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	int bin_cut = 130;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue();

	/****CARGAMOS SEMILLAS DE PARMA/EXPACS**********/
	//~ string parma_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	string parma_file_path = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);

	int year_input;
	int month_input;
	int day_input;

	if(campaign=="LCO"){
		/*LCO*/
		year_input = 2023;
		month_input = 7;
		day_input = 10; //1st day
	}

	if(campaign=="Maricunga"){
		/*Maricunga*/
		year_input = 2023;
		month_input = 7;
		day_input = 14; //1st day
	}

	if(campaign=="SanPedrodeAtacama"){
		/*SanPedrodeAtacama*/
		year_input = 2024;
		month_input = 11;
		day_input = 10; //1st day
	//~ // double vwc_input = 80; // 0%-100%
	}
	
	if(campaign=="Chapiquilta"){
		/*Chapiquilta*/
		year_input = 2024;
		month_input = 11;
		day_input = 17; //1st day
	//~ // double vwc_input = 80; // 0%-100%
	}
	//~ double vwc_input_fraction = vwc_input/100.;

	//Filtro por dia//
	auto lambda_filter_flux = [&](int &year, int &month, int &day)
		{
			//~ if(year_input == year && month_input == month && day_input == day && vwc_input_fraction == vwc)
			if(year_input == year && month_input == month && day_input == day)
				{
					return true;
				}
			else{
					//~ cout << " Bad date " << endl;
					return false;}
		};


	auto df_parma_filter = df_parma_spectra.Filter(lambda_filter_flux,{"Year","Month","Day"}); // vector of vectors: 501 size

	auto diff_flux_parma = df_parma_filter.Take<vector<double>>("NeutronFdiff").GetValue();  // vector of flux diff vectors: 501 size
	//~ vector<double>diff_flux_parma_new(diff_flux_parma.begin(), diff_flux_parma.end()); //vector<float> to vector<double>
	int rand_max_number = diff_flux_parma.size();
	cout << "#SPECTRA size: " << rand_max_number << endl; //Numero de espectros totales: #daysX#vwc_value_per_day= #daysX501
	int diff_flux_vec_size = diff_flux_parma[0].size();
	cout << "#Neutron diff flux size: " << diff_flux_vec_size << endl;

	auto df_parma_filter_vwc =  df_parma_filter.Take<double>("WaterWF").GetValue(); // vector of 501 size
	int  df_parma_filter_vwc_size =  df_parma_filter_vwc.size();
	cout << "#WaterWF size: " << df_parma_filter_vwc_size << endl;
	


 /****************************************************************************************************/

//186 en total (archivos): 1-151: 151, 32-100 (2 en 2): 35. Entonces 151+35=186
//int number_of_seeds = 151; //RetenDesierto
//~ int number_of_seeds = 186; //LCO, Maricunga, Chapiquilta

int number_of_seeds = 501; //SanPedrodeAtacama (0% to 100%) 0.2 steps size
ROOT::RDataFrame df_seed_loop_i(number_of_seeds);

vector<vector<Double_t> > vec_loop_seed;

/**Iteramos sobre las semillas**/
//186 en total (archivos): 1-151: 151, 32-100 (2 en 2): 35. Entonces 151+35=186
//~ for(int i=0; i<186;i++)
for(int i=0; i<number_of_seeds;i++)
	{
		vector<double> diff_flux_bin_seed_new(bin_cut-1,0);
		//~ diff_flux_bin_seed_new.reserve(bin_cut);
		//~ diff_flux_bin_seed_new = df_parma_filter_flux_diff[i];
		for(int j = 0; j<bin_cut-1;j++){
			diff_flux_bin_seed_new [j] = diff_flux_parma[i][j];
		}
		
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Starting ... "<< endl;
		//~ vec_loop_seed.push_back(deconv_em_output_update(campaign,event,steps,i,time_grid,"Intg",0,max_steps,cut));
		vec_loop_seed.push_back(deconv_em_output_update(campaign,event,steps,i,diff_flux_bin_seed_new,emid_icrp116_vec, ewid_icrp116_vec, elower_icrp116_vec,time_grid,"Intg",0,max_steps,cut,physic_list,scale_factor,neufield_type));
		cout << "EM unfolding " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << i+1  << " Finished. "<< endl;
		cout << " " << endl;
    }

/*Definimos los bordes de bin de los VWC%*/
//~ vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
//~ for(int i=0;i<number_of_seeds;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }
 

/**extraemos la info del numero de detectores*/
auto vec_loop_seed_elem =  vec_loop_seed[0];
//~ vector<int> cut_vec_ndet =  {vec_loop_seed_elem.end() - 12, vec_loop_seed_elem.end()-11};
vector<int> cut_vec_ndet =  {vec_loop_seed_elem.end() - 13, vec_loop_seed_elem.end()-12};
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
int rowid_diff_criteria = 0;
int rowid_xi2 = 0;
int rowid_bardelta = 0;
int rowid_std = 0;
int rowid_bin_seed = 0;
int rowid_em_it = 0;

auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
									  auto vec_loop_seed_element =  vec_loop_seed[rowid_deconv];
									  //~ vector<Double_t> deconv_vec = {vec_loop_seed_element.begin(), vec_loop_seed_element.end() - 12};
									  vector<Double_t> deconv_vec = {vec_loop_seed_element.begin(), vec_loop_seed_element.end() - 13};
									  rowid_deconv++;
									  return deconv_vec;
									})
									.Define("seed_bin_edgeds", [&]() {
									  auto bin_element =  df_parma_filter_vwc[rowid_bin_seed]*100.; // *100 in order to move from WF to %wf
									  rowid_bin_seed++;
									  return bin_element;
									})
									.Define("ndet", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_ndet];
									  //~ vector<int> cut_vec_ndet = {vec_loop_element.end() - 12, vec_loop_element.end()-11};
									  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
									  int ndet = cut_vec_ndet[0];
									  rowid_ndet++;
									  return ndet;
									  })
									.Define("Intg_total", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_total];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_total = cut_vec_intg[0];
									  rowid_intg_total++;
									  return Intg_total;
									  })
									.Define("Intg_th", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_th];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_th = cut_vec_intg[1];
									  rowid_intg_th++;
									  return Intg_th;
									  })
									.Define("Intg_ep", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_ep];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_ep = cut_vec_intg[2];
									  rowid_intg_ep++;
									  return Intg_ep;
									  })
									.Define("Intg_fs", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_fs];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_fs = cut_vec_intg[3];
									  rowid_intg_fs++;
									  return Intg_fs;
									  })
									.Define("Intg_he", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_intg_he];
									  //~ vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 11, vec_loop_element.end()-6};
									  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
									  double Intg_he = cut_vec_intg[4];
									  rowid_intg_he++;
									  return Intg_he;
									  })                                                                                           
									.Define("Chi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  double Chi2_value = cut_vec[0];
									  rowid_Chi2++;
									  return Chi2_value;
									})
									.Define("Chi2red", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_Chi2red];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double Chi2red_value = cut_vec[1];
									  double Chi2red_value = cut_vec[1];
									  rowid_Chi2red++;
									  return Chi2red_value;
									})
									.Define("diff_criteria", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_diff_criteria];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  double diff_criteria_value = cut_vec[2];
									  rowid_diff_criteria++;
									  return diff_criteria_value;
									})
									.Define("xi2", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_xi2];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double xi2_value = cut_vec[2];
									  double xi2_value = cut_vec[3];
									  rowid_xi2++;
									  return xi2_value;
									})
									.Define("barDelta", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_bardelta];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double bardelta_value = cut_vec[3];
									  double bardelta_value = cut_vec[4];
									  rowid_bardelta++;
									  return bardelta_value;
									})
									.Define("std_cr", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_std];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double std_cr_value = cut_vec[4];
									  double std_cr_value = cut_vec[5];
									  rowid_std++;
									  return std_cr_value;
									})
									.Define("em_it", [&]() {
									  auto vec_loop_element =  vec_loop_seed[rowid_em_it];
									  //~ vector<Double_t> cut_vec = {vec_loop_element.end() - 6, vec_loop_element.end()};
									  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
									  //~ double em_it_value = cut_vec[5];
									  double em_it_value = cut_vec[6];
									  rowid_em_it++;
									  return em_it_value;
									});

ostringstream stream_ndet; 
stream_ndet << ndet;
string str_stream_ndet = stream_ndet.str();

string df_file_name;
if(steps==0)
	{
		//~ df_file_name = "./deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign+"/"+campaign_path_new+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	}
else{	
		//~ df_file_name = "./deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		df_file_name = "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/"+campaign_path_new+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC_stop/data_em_mc_it/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop"+"_mc_it_"+str_stream_mc_it+".root";
	}
else{	
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC/data_em_mc_it/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC"+"_mc_it_"+str_stream_mc_it+".root";
	}

//~ vector<Double_t>().swap(vec_event_MC_loop);

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

}

void em_loop_MC(string campaign,int event,int steps,int time_grid, int bin_seed,string cut){

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
				vec_event_MC_loop.push_back(deconv_em_output_MC(campaign,event,steps,bin_seed,time_grid,"Intg",0, max_steps,cut));
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
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
	}
else{	
		df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC.root";
	}

df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

auto end = std::chrono::system_clock::now();
std::chrono::duration<float,std::ratio<3600>> duration = end - start; //hours
cout <<"Duration: " <<duration.count() << " hr " << endl;

}

//~ void em_mc_seed_picker(){
//~ /*La semilla que cumple el criterio de stop y que tome a menor cantidad de pasos, esto a partir de los datos EM con criterio de stop*/



//~ }

void em_loop_MC_opt(string campaign,int event,int steps,int time_grid, int ndet, int bin_seed, int random_seed,string cut){

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

	string file_name_stat = "../outputs/root/deconv_data_rootfile/EM_MC_stop/"+campaign+"/event_"+str_stream_event+"_stat.txt";
	//~ ofstream event_mc_info(file_name_stat); // archivo de salida de con la info del evento sin sobreescribir la iteracion MC
	ofstream event_mc_info(file_name_stat, std::ofstream::trunc); // archivo de salida de con la info del evento sobreescribiendo la iteracion MC
	
	
	//~ int N = 500000; //numero de iteraciones MC
	//~ int N = 10; //numero de iteraciones MC
	//~ int max_steps = 1000; //numero de maximo de pasos aceptable en EM
	//~ int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC

	//~ int N = 500000; //numero de iteraciones MC
	//~ int max_steps = 30; //numero de maximo de pasos aceptable en EM
	//~ int max_steps_filter = 15; //numero de maximo de pasos aceptable en EM
	//~ int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC

	int N = 2000000; //numero de iteraciones MC
	//~ int max_steps_em = 19; //numero de maximo de pasos aceptable en EM (LCO)
	//~ int max_steps_em = 25; //numero de maximo de pasos aceptable en EM (Maricunga)
	int max_steps_em = 30; //numero de maximo de pasos aceptable en EM (RetenDesierto)
	//~ int max_steps_filter = 40; //numero de maximo de pasos aceptable en EM
	//~ int max_em_mc_it = 20000; //numero de maximo y suficiente de loops (datos) en EM MC (LCO)
	int max_em_mc_it = 30000; //numero de maximo y suficiente de loops (datos) en EM MC (Maricunga)


	/**Iteramos sobre los eventos**/
	//~ for(int i=event; i<=event;i++)
		//~ {
			int mc_it = 0;
			int mc_it_rejected =0;
			
			double em_it_value;
			/*Iteramos el algritmo EM sobre un evento i N veces.*/
			int bin_seed_new;
			TRandom3 r;
			auto start_loop = std::chrono::system_clock::now();
			for(int k=1;k<=N;k++)
				{

					
					//~ const auto random_number;
					if(random_seed==1)
						{
							/**Randm seed picker**/
							// Selecciona una semilla aleatoria de las 186 disponibles
							bin_seed_new = r.Integer(186); //LCO & Maricunga, Chaquipilta
							//~ bin_seed_new = r.Integer(151); //LCO & Maricunga->RetenDesierto en realidad
							//~ cout << "\r " << " bin_seed " << bin_seed_new << endl;
							//~ cout << " bin_seed " << bin_seed_new << endl;
							
						}
					else{bin_seed_new = bin_seed;}

					vector<Double_t> vec_event_MC_loop_element;
					
					//~ cout << "\r " << "EM unfolding MC " << " Campaign: "<< campaign << " Event: "<< event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << bin_seed_new  << " MC iteration " << k <<  " Starting ... "<< endl;
					cout << "\r " << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << bin_seed_new  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					vec_event_MC_loop_element = deconv_em_output_MC(campaign,event,steps,bin_seed_new,time_grid,"Intg",0,max_steps_em,cut);

					vec_event_MC_loop.push_back(vec_event_MC_loop_element);
					//~ vector<Double_t> cut_vec = {vec_event_MC_loop.end() - 6, vec_event_MC_loop.end()};
					//~ double em_it_value = cut_vec[5];
					em_it_value = vec_event_MC_loop_element.back();
					cout << "em_it: " << em_it_value << endl;
					//~ rowid_em_it++;
					//~ if (em_it_value<max_steps_filter)
					if (em_it_value<=max_steps_em) //Contabilizamos los eventos que toman pasos menor e igual a max_steps_em, si es mayor a max_steps_em se rechaza ( ya que hay un break en deconv_em_output_MC() )
						{
							mc_it++;
							//~ cout << "\r "<< " Accepted " << "iteration " << mc_it << endl;
							//~ deconv_em_output_MC_vec2rootfile(vec_event_MC_loop_element,campaign,event,steps,time_grid,ndet,mc_it);
							//~ cout << " " << endl;
						
							if(mc_it==max_em_mc_it)
								{
									cout << max_em_mc_it << " EM MC iterations complete" << endl;
									break;
									
								}
						}
					else{
							mc_it_rejected++;
							//~ cout << "\r " << " Rejected " << mc_it_rejected <<  endl;
							//~ cout << " " << endl;
						}
					auto end_loop = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end_loop - start_loop;
						
					cout << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
					//~ cout << "\r "<< " Accepted: " << mc_it <<  " Rejected: " << mc_it_rejected;

					event_mc_info.seekp(0); // Move file pointer to the beginning of the file
					event_mc_info << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << bin_seed_new  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					event_mc_info << " em_it: " << em_it_value << endl;
					event_mc_info << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
					
					vector<Double_t>().swap(vec_event_MC_loop_element);// liberamos el vector de la memoria
					
				}
				event_mc_info.close();
				cout << "Accepted "  << mc_it << endl;
				cout << "Rejected "  << mc_it_rejected << endl;
				

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
			df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_0"+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
		}
	else{	
			df_file_name = "../outputs/root/deconv_data_rootfile/EM_MC/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC.root";
		}

	df_seed_loop.Snapshot("em_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

	
	
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float,std::ratio<3600>> duration = end - start; //hours
	cout <<"Duration: " <<duration.count() << " hr " << endl;


	}

void em_loop_MC_opt_new(string campaign,int event,int steps,int time_grid, int ndet, int bin_seed, int random_seed,string cut){

	ROOT::EnableImplicitMT(0); // Desactiva el uso de múltiples hilos en ROOT
	
	auto start_loop = std::chrono::system_clock::now();



    TRandom3 r(random_seed); // Inicializa el generador de números aleatorios
    //~ int N = 2000000; //numero de iteraciones MC
    int N = 20000000; //numero de iteraciones MC (La aumentamos para evitar tener que generar nuevos MC y completar la estadistica de 10000)
    int mc_it = 0, mc_it_rejected = 0;
    //~ int max_em_mc_it = 30000; // Máximo número de eventos aceptados
    int max_em_mc_it = 10000; // Máximo número de eventos aceptados (Chapiquilta)
    int max_steps_em = 20;    // Máximo número de pasos permitidos en EM (Chapiquilta)

	// Reserva memoria para mejorar el rendimiento
    std::vector<std::vector<Double_t>> vec_event_MC_loop;
    vec_event_MC_loop.reserve(max_em_mc_it); // Solo almacenarás hasta max_em_mc_it eventos aceptados

    std::ofstream event_mc_info("../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/event_" + std::to_string(event) + "_stat.txt", std::ofstream::trunc);

    for (int k = 1; mc_it < max_em_mc_it && k <= N; ++k) {
        // Selecciona la semilla aleatoria
        int bin_seed_new = (random_seed == 1) ? r.Integer(186) : bin_seed;

        // Ejecuta el algoritmo EM y obtiene los resultados
        auto vec_event_MC_loop_element = deconv_em_output_MC(campaign, event, steps, bin_seed_new, time_grid, "Intg", 0, max_steps_em, cut);

        // Extrae valores relevantes del resultado
        double em_it_value = vec_event_MC_loop_element.back(); // Número de pasos realizados (em_it)
        double chi_square = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 7]; // Ejemplo: Chi2 (posición ajustada)
        double diff = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 5];      // Ejemplo: diff (posición ajustada)

        // Aplica el criterio de aceptación:
        // 1. Menos de 31 pasos (em_it < 31).
        // 2. Cumple criterio de stop (chi_square < ndet y 0.01 < diff).
        if (em_it_value < 31 && chi_square < ndet && diff < 0.02) {
            vec_event_MC_loop.push_back(vec_event_MC_loop_element); // Guarda solo si cumple ambos criterios
            mc_it++;
        }

        else {
            mc_it_rejected++;
        }

        auto end_loop_partial = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end_loop_partial - start_loop;

			        // Progreso y estadísticas
        //~ if (k % 1000 == 0) {
        if (k % 10 == 0) {
            //~ std::cout << "\r" << "Progreso: " << (k / 20000.0) * 100 << "% "
                      //~ << "Aceptados: " << mc_it << ", Rechazados: " << mc_it_rejected << std::flush;
			
					cout << "\r" << "Progreso EM_MC_Stop: " << (k /(double)N) * 100 << "% "
						 << " Event:" << setw(3) << event << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min " << std::flush;
					//~ cout << "\r "<< " Accepted: " << mc_it <<  " Rejected: " << mc_it_rejected;
			}

					event_mc_info.seekp(0); // Move file pointer to the beginning of the file
					event_mc_info << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << bin_seed_new  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					event_mc_info << " em_it: " << em_it_value << endl;
					event_mc_info << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
					

	}
				
	event_mc_info.close();

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
	int rowid_diff = 0;
	int rowid_xi2 = 0;
	int rowid_bardelta = 0;
	int rowid_std = 0;
	int rowid_bin_seed = 0;
	int rowid_em_it = 0;

	auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
										  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
										  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 13};
										  rowid_deconv++;
										  return deconv_vec;
										})
										.Define("ndet", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
										  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
										  int ndet = cut_vec_ndet[0];
										  rowid_ndet++;
										  return ndet;
										  })
										.Define("Intg_total", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_total = cut_vec_intg[0];
										  rowid_intg_total++;
										  return Intg_total;
										  })
										.Define("Intg_th", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_th = cut_vec_intg[1];
										  rowid_intg_th++;
										  return Intg_th;
										  })
										.Define("Intg_ep", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_ep = cut_vec_intg[2];
										  rowid_intg_ep++;
										  return Intg_ep;
										  })
										.Define("Intg_fs", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_fs = cut_vec_intg[3];
										  rowid_intg_fs++;
										  return Intg_fs;
										  })
										.Define("Intg_he", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_he = cut_vec_intg[4];
										  rowid_intg_he++;
										  return Intg_he;
										  })                                                                                           
										.Define("Chi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2_value = cut_vec[0];
										  rowid_Chi2++;
										  return Chi2_value;
										})
										.Define("Chi2red", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2red_value = cut_vec[1];
										  rowid_Chi2red++;
										  return Chi2red_value;
										})
										.Define("diff", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_diff];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double diff_value = cut_vec[2];
										  rowid_diff++;
										  return diff_value;
										})										
										.Define("xi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double xi2_value = cut_vec[3];
										  rowid_xi2++;
										  return xi2_value;
										})
										.Define("barDelta", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double bardelta_value = cut_vec[4];
										  rowid_bardelta++;
										  return bardelta_value;
										})
										.Define("std_cr", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double std_cr_value = cut_vec[5];
										  rowid_std++;
										  return std_cr_value;
										})
										.Define("em_it", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double em_it_value = cut_vec[6];
										  rowid_em_it++;
										  return em_it_value;
										});


	string df_file_name;
	if(steps==0)
		{
			df_file_name =  "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign +
                              "/EM_unfolding_loop_campaign_" + campaign +
                              "_event_" + std::to_string(event) +
                              "_steps_" + std::to_string(steps) +
                              "_timegrid_" + std::to_string(time_grid) +
                              "_ndet_" + std::to_string(ndet) + "_MC_stop.root";
        }
	else{	
			df_file_name =  "../outputs/root/deconv_data_rootfile/EM_MC/" + campaign +
                              "/EM_unfolding_loop_campaign_" + campaign +
                              "_event_" + std::to_string(event) +
                              "_steps_" + std::to_string(steps) +
                              "_timegrid_" + std::to_string(time_grid) +
                              "_ndet_" + std::to_string(ndet) + "_MC.root";
		}
	df_seed_loop.Snapshot("em_loop_tree",df_file_name.c_str()); /*Save selected columns to disk, in a new TTree treename in file filename*/

	cout << "Accepted "  << mc_it << endl;
	cout << "Rejected "  << mc_it_rejected << endl;
	
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float,std::ratio<3600>> duration = end - start_loop; //hours
	cout <<"Duration: " <<duration.count() << " hr " << endl;

	

}

/*Nuevo loop de deconvolucion EM_MC_stop, que da como input al .root de PARMA/EXPACS y
 * `icrp116_binning_resume.csv para la funcion deconv_em_output_MC_update() */
void em_loop_MC_opt_new_update(string campaign,int event,int steps,int time_grid, int ndet, int bin_seed, int random_seed, string cut, string physic_list, string scale_factor, string neufield_type){

	//~ ROOT::EnableImplicitMT(0); // Desactiva el uso de múltiples hilos en ROOT
	
	string campaign_path;

	if(physic_list=="QGSP_BERT")
		{
			campaign_path = campaign;
			//~ cout << physic_list+" Physic_list" << endl;
		}
	else if(physic_list=="FTFP_BERT")
		{
			campaign_path = campaign+"_FTFP_BERT";
			//~ cout << physic_list+" Physic_list" << endl;
		}
	else{cout << "Physics list inexistente o incorrecta" << endl;}

	//~ string campaign_phylst = campaign+"_FTFP_BERT";
	//~ string campaign_phylst = campaign; //QGSP_BERT (primer analisis)
	
	auto start_loop = std::chrono::system_clock::now();

    TRandom3 r(random_seed); // Inicializa el generador de números aleatorios
    //~ int N = 2000000; //numero de iteraciones MC
    int N = 20000000; //numero de iteraciones MC (La aumentamos para evitar tener que generar nuevos MC y completar la estadistica de 10000)
    int mc_it = 0, mc_it_rejected = 0;
    // int max_em_mc_it = 30000; // Máximo número de eventos aceptados
    int max_em_mc_it = 10000; // Máximo número de eventos aceptados (Chapiquilta)
    int max_steps_em = 20;    // Máximo número de pasos permitidos en EM (Chapiquilta)

	/******CREAMOS LA CARPETA DE SALIDA******/
	//~ fs::path outdir = PrepareOutputDir(campaign_path);
	
	string campaign_path_new = campaign_path+"_"+neufield_type;
	// if(neufield_type=="ISO"){
	// 	campaign_path_new = campaign_path;
	// }
	// else{campaign_path_new = campaign_path+"_"+neufield_type;}

	// Reserva memoria para mejorar el rendimiento
    std::vector<std::vector<Double_t>> vec_event_MC_loop;
    vec_event_MC_loop.reserve(max_em_mc_it); // Solo almacenarás hasta max_em_mc_it eventos aceptados

    std::ofstream event_mc_info("../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_path_new + "/event_" + std::to_string(event) + "_stat.txt", std::ofstream::trunc);

	/****CARGAMOS EL BINEADO ICRP116**********/
	//~ string icrp116_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/icrp116_binning_resume.csv";
	//~ ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	int bin_cut = 130;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue();

	/****CARGAMOS SEMILLAS DE PARMA/EXPACS**********/
	//~ string parma_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	string parma_file_path = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);

	auto diff_flux_parma = df_parma_spectra.Take<vector<double>>("NeutronFdiff").GetValue();
	//~ vector<vector<double>>diff_flux_parma_new(diff_flux_parma.begin(), diff_flux_parma.end()); //  vector<vector<float>> to vector<vector<double>>
	int rand_max_number = diff_flux_parma.size();
	cout << "#SPECTRA size: " << rand_max_number << endl; //Numero de espectros totales: #daysX#vwc_value_per_day= #daysX501
	int diff_flux_vec_size = diff_flux_parma[0].size();
	cout << "#Neutron diff flux size: " << diff_flux_parma[0].size() << endl; 
	
    for(int k = 1; mc_it < max_em_mc_it && k <= N; ++k) {
        // Selecciona la semilla aleatoria
        int bin_seed_new = (random_seed == 1) ? r.Integer(186) : bin_seed;
        
		vector<double> diff_flux_bin_seed_new(bin_cut-1,0);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		int rand_num_flux;
		if(random_seed == 1)//MC
			{
				rand_num_flux = r.Integer(rand_max_number);
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[rand_num_flux][j];
							}
			}
		else{
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[random_seed][j];
							}
			}

        // Ejecuta el algoritmo EM y obtiene los resultados
        //~ auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, bin_seed_new, time_grid, "Intg", 0, max_steps_em, cut);
        
		//auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, rand_num_flux, diff_flux_bin_seed_new, emid_icrp116_vec, ewid_icrp116_vec, elower_icrp116_vec, time_grid, "Intg", 0, max_steps_em, cut, physic_list, scale_factor, neufield_type);
		auto vec_event_MC_loop_element = deconv_em_output_MC_update_refactor(campaign, event, steps, rand_num_flux, diff_flux_bin_seed_new, emid_icrp116_vec, ewid_icrp116_vec, elower_icrp116_vec, time_grid, "Intg", 0, max_steps_em, cut, physic_list, scale_factor, neufield_type);
		


        // Extrae valores relevantes del resultado
        double em_it_value = vec_event_MC_loop_element.back(); // Número de pasos realizados (em_it)
        double chi_square = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 7]; // Ejemplo: Chi2 (posición ajustada)
        double diff = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 5];      // Ejemplo: diff (posición ajustada)

        // Aplica el criterio de aceptación:
        // 1. Menos de 31 pasos (em_it < 31).
        // 2. Cumple criterio de stop (chi_square < ndet y 0.01 < diff).
        //~ if (em_it_value < 31 && chi_square < ndet && diff < 0.02) {
        if (em_it_value < max_steps_em && chi_square < ndet && diff < 0.02) {
            vec_event_MC_loop.push_back(vec_event_MC_loop_element); // Guarda solo si cumple ambos criterios
            mc_it++;
        }

        else {
            mc_it_rejected++;
        }

        auto end_loop_partial = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end_loop_partial - start_loop;

			        // Progreso y estadísticas
        // if (k % 1000 == 0) {
        if (k % 10 == 0) {
            //  std::cout << "\r" << "Progreso: " << (k / 20000.0) * 100 << "% "
                      //  << "Aceptados: " << mc_it << ", Rechazados: " << mc_it_rejected << std::flush;
			
					cout << "\r" << "Progreso EM_MC_Stop: " << (k /(double)N) * 100 << "% "
						 << " Event:" << setw(3) << event << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min " << std::flush;
					// cout << "\r "<< " Accepted: " << mc_it <<  " Rejected: " << mc_it_rejected;
			}

					event_mc_info.seekp(0); // Move file pointer to the beginning of the file
					// event_mc_info << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << rand_num_flux  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					// event_mc_info << " em_it: " << em_it_value << " chi^2: " << chi_square << " diff: " << diff <<  endl;
					// event_mc_info << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
					// event_mc_info << " " << endl;

					std::ostringstream oss;
					oss  << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << rand_num_flux  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N)*100 <<")% " <<  setw(3) << " Starting ... " << "\n"
				 		 << " em_it: " << em_it_value << " chi^2: " << chi_square << " diff: " << diff << "\n"
					 	 << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min"  << "\n";

					std::string s = oss.str();
					event_mc_info << s;

					// “borra” cola: escribe un bloque grande de espacios y vuelve a inicio
					event_mc_info << std::string(200, ' ') << "\n";
					event_mc_info.flush();

	}
				
	event_mc_info.close();

				

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
	int rowid_diff = 0;
	int rowid_xi2 = 0;
	int rowid_bardelta = 0;
	int rowid_std = 0;
	int rowid_bin_seed = 0;
	int rowid_em_it = 0;

	auto df_seed_loop = df_seed_loop_i.Define("deconv_vec", [&]() {
										  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
										  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 13};
										  rowid_deconv++;
										  return deconv_vec;
										})
										.Define("ndet", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
										  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
										  int ndet = cut_vec_ndet[0];
										  rowid_ndet++;
										  return ndet;
										  })
										.Define("Intg_total", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_total = cut_vec_intg[0];
										  rowid_intg_total++;
										  return Intg_total;
										  })
										.Define("Intg_th", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_th = cut_vec_intg[1];
										  rowid_intg_th++;
										  return Intg_th;
										  })
										.Define("Intg_ep", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_ep = cut_vec_intg[2];
										  rowid_intg_ep++;
										  return Intg_ep;
										  })
										.Define("Intg_fs", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_fs = cut_vec_intg[3];
										  rowid_intg_fs++;
										  return Intg_fs;
										  })
										.Define("Intg_he", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_he = cut_vec_intg[4];
										  rowid_intg_he++;
										  return Intg_he;
										  })                                                                                           
										.Define("Chi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2_value = cut_vec[0];
										  rowid_Chi2++;
										  return Chi2_value;
										})
										.Define("Chi2red", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2red_value = cut_vec[1];
										  rowid_Chi2red++;
										  return Chi2red_value;
										})
										.Define("diff", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_diff];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double diff_value = cut_vec[2];
										  rowid_diff++;
										  return diff_value;
										})										
										.Define("xi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double xi2_value = cut_vec[3];
										  rowid_xi2++;
										  return xi2_value;
										})
										.Define("barDelta", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double bardelta_value = cut_vec[4];
										  rowid_bardelta++;
										  return bardelta_value;
										})
										.Define("std_cr", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double std_cr_value = cut_vec[5];
										  rowid_std++;
										  return std_cr_value;
										})
										.Define("em_it", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double em_it_value = cut_vec[6];
										  rowid_em_it++;
										  return em_it_value;
										});


	string df_file_name;
	if(steps==0)
		{
			df_file_name =  "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_path_new +
                              "/EM_unfolding_loop_campaign_" + campaign +
                              "_event_" + std::to_string(event) +
                              "_steps_" + std::to_string(steps) +
                              "_timegrid_" + std::to_string(time_grid) +
                              "_ndet_" + std::to_string(ndet) + "_MC_stop.root";
        }
	else{	
			df_file_name =  "../outputs/root/deconv_data_rootfile/EM_MC/" + campaign + "/" + campaign_path_new +
                              "/EM_unfolding_loop_campaign_" + campaign +
                              "_event_" + std::to_string(event) +
                              "_steps_" + std::to_string(steps) +
                              "_timegrid_" + std::to_string(time_grid) +
                              "_ndet_" + std::to_string(ndet) + "_MC.root";
		}
	df_seed_loop.Snapshot("em_loop_tree",df_file_name.c_str()); /*Save selected columns to disk, in a new TTree treename in file filename*/

	cout << "Accepted "  << mc_it << endl;
	cout << "Rejected "  << mc_it_rejected << endl;
	
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float,std::ratio<3600>> duration = end - start_loop; //hours
	cout <<"Duration: " <<duration.count() << " hr " << endl;

	

}

/*Basado en em_loop_MC_opt_new_update, agrega los MC faltantes para completar 10000*/
void em_loop_MC_opt_new_append(string campaign, int event, int steps, int time_grid, int ndet, int bin_seed, int random_seed, string cut, string physic_list, string scale_factor, string neufield_type){
    // Parámetros fijos
    const int N_new = 20000000;      // Iteraciones MC a intentar en esta ejecución
    const int max_em_mc_it = 10000;  // Eventos aceptados totales deseados
    const int max_steps_em = 20;

     int mc_it_rejected = 0;



    // --- 1) Nombre de ficheros old & new ---
    std::string old_root = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "_MC_stop.root";

    std::string new_root = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "append_MC_stop.root";

    std::string stat_txt = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign
        + "/event_" + std::to_string(event) + "_stat_append.txt";

    // --- 2) Cuenta cuántos ya hay en el ROOT viejo ---
    ROOT::RDataFrame df_old("em_loop_tree", old_root.c_str());
    auto old_count = *df_old.Count();               // cuántos ya habían
    int mc_it = std::min<int>(old_count, max_em_mc_it);
    if (mc_it >= max_em_mc_it) {
        std::cout << "Ya tienes " << mc_it
                  << " aceptados (>= " << max_em_mc_it << "). No hago nada.\n";
        return;
    }

    // --- 3) Prepara salida de estadísticas (re-escribe) ---
    std::ofstream event_mc_info(stat_txt, std::ofstream::trunc);
    event_mc_info << "# Antes: " << mc_it << " aceptados. Faltan: "
                  << (max_em_mc_it - mc_it) << "\n";

    // --- 4) Inicializaciones comunes (idénticas a tu función) ---
    TRandom3 r(random_seed);
    auto start_loop = std::chrono::system_clock::now();

    /****CARGAMOS EL BINEADO ICRP116**********/
	//~ string icrp116_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/icrp116_binning_resume.csv";
	//~ ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	int bin_cut = 130;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue();

	/****CARGAMOS SEMILLAS DE PARMA/EXPACS**********/
	//~ string parma_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	string parma_file_path = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);

	auto diff_flux_parma = df_parma_spectra.Take<vector<double>>("NeutronFdiff").GetValue();
	//~ vector<vector<double>>diff_flux_parma_new(diff_flux_parma.begin(), diff_flux_parma.end()); //  vector<vector<float>> to vector<vector<double>>
	int rand_max_number = diff_flux_parma.size();
	cout << "#SPECTRA size: " << rand_max_number << endl; //Numero de espectros totales: #daysX#vwc_value_per_day= #daysX501
	int diff_flux_vec_size = diff_flux_parma[0].size();
	cout << "#Neutron diff flux size: " << diff_flux_parma[0].size() << endl; 


	// (5)Genera UN vector *solo* con los NUEVOS eventos
	std::vector<std::vector<Double_t>> vec_event_MC_loop;
	vec_event_MC_loop.reserve(max_em_mc_it - mc_it);

	
    for(int k = 1; mc_it < max_em_mc_it && k <= N_new; ++k) {
        // Selecciona la semilla aleatoria
        int bin_seed_new = (random_seed == 1) ? r.Integer(186) : bin_seed;
        
		vector<double> diff_flux_bin_seed_new(bin_cut-1,0);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		int rand_num_flux;
		if(random_seed == 1)//MC
			{
				rand_num_flux = r.Integer(rand_max_number);
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[rand_num_flux][j];
							}
			}
		else{
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[random_seed][j];
							}
			}

        // Ejecuta el algoritmo EM y obtiene los resultados
        //~ auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, bin_seed_new, time_grid, "Intg", 0, max_steps_em, cut);
        auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, rand_num_flux, diff_flux_bin_seed_new, emid_icrp116_vec, ewid_icrp116_vec, elower_icrp116_vec, time_grid, "Intg", 0, max_steps_em, cut, physic_list, scale_factor, neufield_type);
		

        // Extrae valores relevantes del resultado
        double em_it_value = vec_event_MC_loop_element.back(); // Número de pasos realizados (em_it)
        double chi_square = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 7]; // Ejemplo: Chi2 (posición ajustada)
        double diff = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 5];      // Ejemplo: diff (posición ajustada)

        // Aplica el criterio de aceptación:
        // 1. Menos de 31 pasos (em_it < 31).
        // 2. Cumple criterio de stop (chi_square < ndet y 0.01 < diff).
        //~ if (em_it_value < 31 && chi_square < ndet && diff < 0.02) {
        if (em_it_value < max_steps_em && chi_square < ndet && diff < 0.02) {
            vec_event_MC_loop.push_back(vec_event_MC_loop_element); // Guarda solo si cumple ambos criterios
            mc_it++;
        }

        else {
            mc_it_rejected++;
        }

        auto end_loop_partial = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end_loop_partial - start_loop;

        //~ if (em_it_value < max_steps_em && chi2 < ndet && diff < 0.02) {
            //~ vec_event_MC_loop.push_back(out);
            //~ ++mc_it;
        //~ } else {
            //~ ++mc_rej;
        //~ }

        // Estadísticas cada 1 000 000 iters
        //~ if (k % 1000000 == 0) {
        // Estadísticas cada 10 iters
        //~ if (k % 10 == 0) {
            //~ double pct_done = 100. * k / N_new;
            //~ event_mc_info << "Iter new: " << k
                          //~ << "  aceptados totales: " << mc_it
                          //~ << "  faltan: " << (max_em_mc_it-mc_it)
                          //~ << "  rechazados (nuevos): " << mc_rej
                          //~ << "  %progreso: " << std::fixed
                          //~ << std::setprecision(1) << pct_done << "%" << "\n";
        //~ }
        			        // Progreso y estadísticas
        // if (k % 1000 == 0) {
        if (k % 10 == 0) {
            //  std::cout << "\r" << "Progreso: " << (k / 20000.0) * 100 << "% "
                      //  << "Aceptados: " << mc_it << ", Rechazados: " << mc_it_rejected << std::flush;
			
					cout << "\r" << "Progreso EM_MC_Stop: " << (k /(double)N_new) * 100. << "% "
						 << " Event:" << setw(3) << event << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min " << std::flush;
					// cout << "\r "<< " Accepted: " << mc_it <<  " Rejected: " << mc_it_rejected;
			}

					event_mc_info.seekp(0); // Move file pointer to the beginning of the file
					event_mc_info << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << rand_num_flux  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N_new)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					event_mc_info << " em_it: " << em_it_value << " chi^2: " << chi_square << " diff: " << diff <<  endl;
					event_mc_info << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected  << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
    }

    // --- 6) Construye RDataFrame para los nuevos eventos ---
    //~ ROOT::RDF::RDataFrame df_new{ mc_it - old_count };
    ROOT::RDataFrame df_new_i(mc_it-old_count);
    //~ int idx = 0;
    //~ auto df1 = df_new.Define("deconv_vec", [&](Long_t){ return vec_new[idx++]; });

	int rowid_deconv = 0;
	int rowid_intg_total = 0;
	int rowid_ndet = 0;
	int rowid_intg_th = 0;
	int rowid_intg_ep = 0;
	int rowid_intg_fs = 0;
	int rowid_intg_he = 0;
	int rowid_Chi2 = 0;
	int rowid_Chi2red = 0;
	int rowid_diff = 0;
	int rowid_xi2 = 0;
	int rowid_bardelta = 0;
	int rowid_std = 0;
	int rowid_bin_seed = 0;
	int rowid_em_it = 0;

	auto df1 = df_new_i.Define("deconv_vec", [&]() {
										  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
										  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 13};
										  rowid_deconv++;
										  return deconv_vec;
										})
										.Define("ndet", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
										  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
										  int ndet = cut_vec_ndet[0];
										  rowid_ndet++;
										  return ndet;
										  })
										.Define("Intg_total", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_total = cut_vec_intg[0];
										  rowid_intg_total++;
										  return Intg_total;
										  })
										.Define("Intg_th", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_th = cut_vec_intg[1];
										  rowid_intg_th++;
										  return Intg_th;
										  })
										.Define("Intg_ep", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_ep = cut_vec_intg[2];
										  rowid_intg_ep++;
										  return Intg_ep;
										  })
										.Define("Intg_fs", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_fs = cut_vec_intg[3];
										  rowid_intg_fs++;
										  return Intg_fs;
										  })
										.Define("Intg_he", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_he = cut_vec_intg[4];
										  rowid_intg_he++;
										  return Intg_he;
										  })                                                                                           
										.Define("Chi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2_value = cut_vec[0];
										  rowid_Chi2++;
										  return Chi2_value;
										})
										.Define("Chi2red", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2red_value = cut_vec[1];
										  rowid_Chi2red++;
										  return Chi2red_value;
										})
										.Define("diff", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_diff];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double diff_value = cut_vec[2];
										  rowid_diff++;
										  return diff_value;
										})										
										.Define("xi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double xi2_value = cut_vec[3];
										  rowid_xi2++;
										  return xi2_value;
										})
										.Define("barDelta", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double bardelta_value = cut_vec[4];
										  rowid_bardelta++;
										  return bardelta_value;
										})
										.Define("std_cr", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double std_cr_value = cut_vec[5];
										  rowid_std++;
										  return std_cr_value;
										})
										.Define("em_it", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double em_it_value = cut_vec[6];
										  rowid_em_it++;
										  return em_it_value;
										});


	df1.Snapshot("em_loop_tree",new_root.c_str()); /*Save selected columns to disk, in a new TTree treename in file filename*/

    // --- 7) Concatena viejo + nuevo y graba en append_MC_stop.root ---
    //~ auto df_old_simple = ROOT::RDataFrame("em_loop_tree", old_root.c_str());
    //~ auto df_concat = df_old_simple.Concatenate(df1);
    //~ df_concat.Snapshot("em_loop_tree", new_root);

	std::string new_root_final = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "append_final_MC_stop.root";
	auto df_merge_data = ROOT::RDataFrame("em_loop_tree", {old_root.c_str(),new_root.c_str()});
	df_merge_data.Snapshot("em_loop_tree",new_root_final.c_str()); 

    // --- 8) Cierre y resumen final ---
    auto end_loop = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_h =
        end_loop - start_loop;
    event_mc_info << "\n=== FINAL ===\n"
                  << "Tot aceptados: " << mc_it << "\n"
                  << "Tot rechazados (nuevos): " << mc_it_rejected << "\n"
                  << "Tiempo total (h): " << elapsed_h.count() << "\n";
    event_mc_info.close();

    std::cout << "He añadido " << (mc_it - old_count)
              << " eventos a " << new_root_final << "\n";
}

/*Version que actualiza el archivo .root cada vez que hay un evento nuevo que cumple los criterios, esto para evitar perder los datos cada vez que se reinicia el cluster*/
void em_loop_MC_opt_new_append_new(string campaign, int event, int steps, int time_grid, int ndet, int bin_seed, int random_seed, string cut, string physic_list, string scale_factor, string neufield_type){
    // Parámetros fijos
    const int N_new = 20000000;      // Iteraciones MC a intentar en esta ejecución
    const int max_em_mc_it = 10000;  // Eventos aceptados totales deseados
    const int max_steps_em = 20;

     int mc_it_rejected = 0;

string campaign_phylst = campaign+"_FTFP_BERT";
//~ string campaign_phylst = campaign; //QGSP_BERT (primer analisis)

    // --- 1) Nombre de ficheros old & new ---
    std::string old_root = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_phylst
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "_MC_stop.root";

    std::string new_root = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_phylst
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "append_MC_stop.root";

    std::string stat_txt = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_phylst
        + "/event_" + std::to_string(event) + "_stat_append.txt";

    // --- 2) Cuenta cuántos ya hay en el ROOT viejo ---
    ROOT::RDataFrame df_old("em_loop_tree", old_root.c_str());
    auto old_count = *df_old.Count();               // cuántos ya habían
    int mc_it = std::min<int>(old_count, max_em_mc_it);
    if (mc_it >= max_em_mc_it) {
        std::cout << "Ya tienes " << mc_it
                  << " aceptados (>= " << max_em_mc_it << "). No hago nada.\n";
        return;
    }

    // --- 3) Prepara salida de estadísticas (re-escribe) ---
    std::ofstream event_mc_info(stat_txt, std::ofstream::trunc);
    event_mc_info << "# Antes: " << mc_it << " aceptados. Faltan: "
                  << (max_em_mc_it - mc_it) << "\n";

    // --- 4) Inicializaciones comunes (idénticas a tu función) ---
    TRandom3 r(random_seed);
    auto start_loop = std::chrono::system_clock::now();

    /****CARGAMOS EL BINEADO ICRP116**********/
	//~ string icrp116_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/icrp116_binning_resume.csv";
	//~ ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);
	/**************Energy Bin********************/
	/*ICRP binning*/
	char delimiter = ',';
	char double_type ='D';
	//~ string icrp116_binning_csv_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/ICRP116_binning_resume.csv";
	string icrp116_binning_csv_path = "../data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv";
	std::unordered_map<std::string, char> icrp116_map = {{"Emid",double_type},{"Ewid", double_type},{"Elower", double_type},{"Eupper", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
	auto df_icrp116 = ROOT::RDF::FromCSV(icrp116_binning_csv_path,true,delimiter,-1, std::move(icrp116_map));
	/*Vectors*/
	int bin_cut = 130;
	auto df_icrp116_cut = df_icrp116.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
	auto emid_icrp116_vec = df_icrp116_cut.Take<double>("Emid").GetValue();
	auto ewid_icrp116_vec = df_icrp116_cut.Take<double>("Ewid").GetValue();
	auto elower_icrp116_vec = df_icrp116_cut.Take<double>("Elower").GetValue();

	/****CARGAMOS SEMILLAS DE PARMA/EXPACS**********/
	//~ string parma_file_path = "/home/flopez/Data/Dropbox/EXPACS/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	string parma_file_path = "../data/external/EXPACS_Data/parma_cpp_flopez/"+campaign+"_parma_fluxes.root";
	ROOT::RDataFrame df_parma_spectra("BkgNeutronSpectra", parma_file_path);

	auto diff_flux_parma = df_parma_spectra.Take<vector<double>>("NeutronFdiff").GetValue();
	//~ vector<vector<double>>diff_flux_parma_new(diff_flux_parma.begin(), diff_flux_parma.end()); //  vector<vector<float>> to vector<vector<double>>
	int rand_max_number = diff_flux_parma.size();
	cout << "#SPECTRA size: " << rand_max_number << endl; //Numero de espectros totales: #daysX#vwc_value_per_day= #daysX501
	int diff_flux_vec_size = diff_flux_parma[0].size();
	cout << "#Neutron diff flux size: " << diff_flux_parma[0].size() << endl; 


	// (5)Genera UN vector *solo* con los NUEVOS eventos
	std::vector<std::vector<Double_t>> vec_event_MC_loop;
	vec_event_MC_loop.reserve(max_em_mc_it - mc_it);

	
    for(int k = 1; mc_it < max_em_mc_it && k <= N_new; ++k) {
        // Selecciona la semilla aleatoria
        int bin_seed_new = (random_seed == 1) ? r.Integer(186) : bin_seed;
        
		vector<double> diff_flux_bin_seed_new(bin_cut-1,0);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		//~ diff_flux_bin_seed_new.reserve(diff_flux_vec_size);
		int rand_num_flux;
		if(random_seed == 1)//MC
			{
				rand_num_flux = r.Integer(rand_max_number);
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[rand_num_flux][j];
							}
			}
		else{
				for(int j = 0; j<bin_cut-1;j++)
							{
								diff_flux_bin_seed_new[j] =  diff_flux_parma[random_seed][j];
							}
			}

        // Ejecuta el algoritmo EM y obtiene los resultados
        //~ auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, bin_seed_new, time_grid, "Intg", 0, max_steps_em, cut);
        auto vec_event_MC_loop_element = deconv_em_output_MC_update(campaign, event, steps, rand_num_flux, diff_flux_bin_seed_new, emid_icrp116_vec, ewid_icrp116_vec, elower_icrp116_vec, time_grid, "Intg", 0, max_steps_em, cut, physic_list, scale_factor, neufield_type);
		

        // Extrae valores relevantes del resultado
        double em_it_value = vec_event_MC_loop_element.back(); // Número de pasos realizados (em_it)
        double chi_square = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 7]; // Ejemplo: Chi2 (posición ajustada)
        double diff = vec_event_MC_loop_element[vec_event_MC_loop_element.size() - 5];      // Ejemplo: diff (posición ajustada)

        // Aplica el criterio de aceptación:
        // 1. Menos de 31 pasos (em_it < 31).
        // 2. Cumple criterio de stop (chi_square < ndet y 0.01 < diff).
        //~ if (em_it_value < 31 && chi_square < ndet && diff < 0.02) {
        if (em_it_value < max_steps_em && chi_square < ndet && diff < 0.02) {
            vec_event_MC_loop.push_back(vec_event_MC_loop_element); // Guarda solo si cumple ambos criterios
            mc_it++;
        }

        else {
            mc_it_rejected++;
        }

        auto end_loop_partial = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end_loop_partial - start_loop;

        //~ if (em_it_value < max_steps_em && chi2 < ndet && diff < 0.02) {
            //~ vec_event_MC_loop.push_back(out);
            //~ ++mc_it;
        //~ } else {
            //~ ++mc_rej;
        //~ }

        // Estadísticas cada 1 000 000 iters
        //~ if (k % 1000000 == 0) {
        // Estadísticas cada 10 iters
        //~ if (k % 10 == 0) {
            //~ double pct_done = 100. * k / N_new;
            //~ event_mc_info << "Iter new: " << k
                          //~ << "  aceptados totales: " << mc_it
                          //~ << "  faltan: " << (max_em_mc_it-mc_it)
                          //~ << "  rechazados (nuevos): " << mc_rej
                          //~ << "  %progreso: " << std::fixed
                          //~ << std::setprecision(1) << pct_done << "%" << "\n";
        //~ }
        			        // Progreso y estadísticas
        // if (k % 1000 == 0) {
        if (k % 10 == 0) {
            //  std::cout << "\r" << "Progreso: " << (k / 20000.0) * 100 << "% "
                      //  << "Aceptados: " << mc_it << ", Rechazados: " << mc_it_rejected << std::flush;
			
					cout << "\r" << "Progreso EM_MC_Stop: " << (k /(double)N_new) * 100. << "% "
						 << " Event:" << setw(3) << event << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected << " Elapsed time: " << (elapsed_seconds.count())/60. << " min " << std::flush;
					// cout << "\r "<< " Accepted: " << mc_it <<  " Rejected: " << mc_it_rejected;
			}

					event_mc_info.seekp(0); // Move file pointer to the beginning of the file
					event_mc_info << " EM unfolding MC " << " Campaign: "<< campaign << " Event:" << setw(3) << event << " Steps: " << steps << " Time grid: " << time_grid << " Seed: " << setw(3) << rand_num_flux  << setw(3) << " MC iteration: " << setw(3) << k << std::fixed << std::setprecision(2) << " ("<< (k/(double)N_new)*100 <<")% " <<  setw(3) << " Starting ... "<< endl;
					event_mc_info << " em_it: " << em_it_value << " chi^2: " << chi_square << " diff: " << diff <<  endl;
					event_mc_info << " Accepted: " << mc_it <<"/" <<max_em_mc_it << setw(2) << " ("  << std::fixed << std::setprecision(2) <<(mc_it/(double) max_em_mc_it)*100. << setw(2) << ")%"<< " Rejected: " << mc_it_rejected  << " Elapsed time: " << (elapsed_seconds.count())/60. << " min" << endl;
    }

    // --- 6) Construye RDataFrame para los nuevos eventos ---
    //~ ROOT::RDF::RDataFrame df_new{ mc_it - old_count };
    ROOT::RDataFrame df_new_i(mc_it-old_count);
    //~ int idx = 0;
    //~ auto df1 = df_new.Define("deconv_vec", [&](Long_t){ return vec_new[idx++]; });

	int rowid_deconv = 0;
	int rowid_intg_total = 0;
	int rowid_ndet = 0;
	int rowid_intg_th = 0;
	int rowid_intg_ep = 0;
	int rowid_intg_fs = 0;
	int rowid_intg_he = 0;
	int rowid_Chi2 = 0;
	int rowid_Chi2red = 0;
	int rowid_diff = 0;
	int rowid_xi2 = 0;
	int rowid_bardelta = 0;
	int rowid_std = 0;
	int rowid_bin_seed = 0;
	int rowid_em_it = 0;

	auto df1 = df_new_i.Define("deconv_vec", [&]() {
										  auto vec_event_MC_loop_element =  vec_event_MC_loop[rowid_deconv];
										  vector<Double_t> deconv_vec = {vec_event_MC_loop_element.begin(), vec_event_MC_loop_element.end() - 13};
										  rowid_deconv++;
										  return deconv_vec;
										})
										.Define("ndet", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_ndet];
										  vector<int> cut_vec_ndet = {vec_loop_element.end() - 13, vec_loop_element.end()-12};
										  int ndet = cut_vec_ndet[0];
										  rowid_ndet++;
										  return ndet;
										  })
										.Define("Intg_total", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_total];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_total = cut_vec_intg[0];
										  rowid_intg_total++;
										  return Intg_total;
										  })
										.Define("Intg_th", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_th];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_th = cut_vec_intg[1];
										  rowid_intg_th++;
										  return Intg_th;
										  })
										.Define("Intg_ep", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_ep];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_ep = cut_vec_intg[2];
										  rowid_intg_ep++;
										  return Intg_ep;
										  })
										.Define("Intg_fs", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_fs];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_fs = cut_vec_intg[3];
										  rowid_intg_fs++;
										  return Intg_fs;
										  })
										.Define("Intg_he", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_intg_he];
										  vector<Double_t> cut_vec_intg = {vec_loop_element.end() - 12, vec_loop_element.end()-7};
										  double Intg_he = cut_vec_intg[4];
										  rowid_intg_he++;
										  return Intg_he;
										  })                                                                                           
										.Define("Chi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2_value = cut_vec[0];
										  rowid_Chi2++;
										  return Chi2_value;
										})
										.Define("Chi2red", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_Chi2red];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double Chi2red_value = cut_vec[1];
										  rowid_Chi2red++;
										  return Chi2red_value;
										})
										.Define("diff", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_diff];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double diff_value = cut_vec[2];
										  rowid_diff++;
										  return diff_value;
										})										
										.Define("xi2", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_xi2];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double xi2_value = cut_vec[3];
										  rowid_xi2++;
										  return xi2_value;
										})
										.Define("barDelta", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_bardelta];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double bardelta_value = cut_vec[4];
										  rowid_bardelta++;
										  return bardelta_value;
										})
										.Define("std_cr", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_std];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double std_cr_value = cut_vec[5];
										  rowid_std++;
										  return std_cr_value;
										})
										.Define("em_it", [&]() {
										  auto vec_loop_element =  vec_event_MC_loop[rowid_em_it];
										  vector<Double_t> cut_vec = {vec_loop_element.end() - 7, vec_loop_element.end()};
										  double em_it_value = cut_vec[6];
										  rowid_em_it++;
										  return em_it_value;
										});


	df1.Snapshot("em_loop_tree",new_root.c_str()); /*Save selected columns to disk, in a new TTree treename in file filename*/

    // --- 7) Concatena viejo + nuevo y graba en append_MC_stop.root ---
    //~ auto df_old_simple = ROOT::RDataFrame("em_loop_tree", old_root.c_str());
    //~ auto df_concat = df_old_simple.Concatenate(df1);
    //~ df_concat.Snapshot("em_loop_tree", new_root);

	std::string new_root_final = "../outputs/root/deconv_data_rootfile/EM_MC_stop/" + campaign + "/" + campaign_phylst
        + "/EM_unfolding_loop_campaign_" + campaign
        + "_event_" + std::to_string(event)
        + "_steps_" + std::to_string(steps)
        + "_timegrid_" + std::to_string(time_grid)
        + "_ndet_" + std::to_string(ndet)
        + "append_final_MC_stop.root";
	auto df_merge_data = ROOT::RDataFrame("em_loop_tree", {old_root.c_str(),new_root.c_str()});
	df_merge_data.Snapshot("em_loop_tree",new_root_final.c_str()); 

    // --- 8) Cierre y resumen final ---
    auto end_loop = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_h =
        end_loop - start_loop;
    event_mc_info << "\n=== FINAL ===\n"
                  << "Tot aceptados: " << mc_it << "\n"
                  << "Tot rechazados (nuevos): " << mc_it_rejected << "\n"
                  << "Tiempo total (h): " << elapsed_h.count() << "\n";
    event_mc_info.close();

    std::cout << "He añadido " << (mc_it - old_count)
              << " eventos a " << new_root_final << "\n";
}




void em_loop_events_MC_opt(string campaign,int event_inf, int event_sup, int steps,int time_grid, int ndet, int bin_seed, int random_seed, string cut)
{
	for(int i=event_inf;i<=event_sup;i++)
		{
				em_loop_MC_opt(campaign,i,steps,time_grid,ndet,bin_seed,random_seed,cut);
		}
}

void em_loop_events_MC_opt_new(string campaign,int event_inf, int event_sup, int steps,int time_grid, int ndet, int bin_seed, int random_seed, string cut)
{
	for(int i=event_inf;i<=event_sup;i++)
		{
				em_loop_MC_opt_new(campaign,i,steps,time_grid,ndet,bin_seed,random_seed,cut);
		}
}

void em_loop_events_MC_opt_new_update(string campaign,int event_inf, int event_sup, int steps,int time_grid, int ndet, int bin_seed, int random_seed, string cut, string physic_list, string scale_factor, string neufield_type)
{
	for(int i=event_inf;i<=event_sup;i++)
		{
				em_loop_MC_opt_new_update(campaign,i,steps,time_grid,ndet,bin_seed,random_seed,cut, physic_list, scale_factor, neufield_type);
		}
}

void em_loop_events_MC_opt_new_append(string campaign,int event_inf, int event_sup, int steps,int time_grid, int ndet, int bin_seed, int random_seed, string cut, string physic_list, string scale_factor, string neufield_type)
{
	for(int i=event_inf;i<=event_sup;i++)
		{
				em_loop_MC_opt_new_append(campaign,i,steps,time_grid,ndet,bin_seed,random_seed,cut,physic_list, scale_factor, neufield_type);
		}
}



TH1D* deconv_hist_from_steps_and_seeds_TH1D(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation, string physic_list){

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

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

/**************Energy Bin********************/
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
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
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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
				//~ flux_deconv->GetYaxis()->SetTitle("#bf{E#times#Phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
				flux_deconv->GetYaxis()->SetTitle("#bf{#phi(u)=E#times#phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
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

void deconv_flux_multiplot_by_seed(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation, string physic_list){

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

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

/*Llenamos un vector de histogramas por numero de pasos para la misma semilla*/
for(int i = 1; i<=steps;i++){
	hist_deconv_flux_vec.push_back(deconv_hist_from_steps_and_seeds_TH1D(campaign,event,i,timegrid, ndet, bin_seed,flux_representation, physic_list));
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

	string input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps_new+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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
	auto df_flux_deconv_diff_criteria = df_seed_loop_step.Take<double>("diff_criteria").GetValue();
	
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
	vec_data_step.push_back(df_flux_deconv_diff_criteria[bin_seed-1]);

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
		//~ canvas_deconv->Divide(6,5);
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
    //~ /*Para mostrar a partir de que valor los ratios se normalizan al dividir por la integral de la region de alta energia */
	double sum_eta_ratios = data_to_hist[2]/data_to_hist[5] + data_to_hist[3]/data_to_hist[5] + data_to_hist[4]/data_to_hist[5];
	 //~ if (sum_eta_ratios<=1.0){
		           //~ // Change pad properties to highlight it
				//~ pad->SetFillColor(kMagenta-9);
				//~ pad->SetFillStyle(3003); // Solid fill
			//~ }
	 //~ if (data_to_hist[6]<ndet & sum_eta_ratios<=1.0){
		           //~ // Change pad properties to highlight it
				//~ pad->SetFillColor(kOrange-9);
				//~ pad->SetFillStyle(3003); // Solid fill
			//~ }

/*Para mostrar a partir de que valor el diff criteria es menor al 2% */
	if (data_to_hist[11]<0.02){
               // Change pad properties to highlight it
				pad->SetFillColor(kMagenta-9);
				pad->SetFillStyle(3003); // Solid fill
         }
         
/*Para mostrar a partir de que valor se cumplen ambos criterios chi-square y diff criteria*/
	 if (data_to_hist[11]<0.02 && data_to_hist[6]<ndet){
		           // Change pad properties to highlight it
				pad->SetFillColor(kPink+9);
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

	ostringstream stream_diff_criteria;

	
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
	stream_diff_criteria  << setprecision(3) << data_to_hist[11];
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

	string str_stream_diff_criteria = "#Delta_{#Phi_{i+1}-#Phi_{i}}="+stream_diff_criteria.str();

	TLatex *l_ndet = new TLatex(0.15+shift_margin,0.85,str_stream_ndet.c_str());
	TLatex *l_intg_total = new TLatex(0.15+shift_margin,0.8,str_stream_intgtotal.c_str());
	TLatex *l_Chi2 = new TLatex(0.15+shift_margin,0.75,str_stream_Chi2.c_str());
	//~ TLatex *l_sum_eta = new TLatex(0.35+shift_margin,0.75,str_stream_sum_eta.c_str());
	TLatex *l_Chi2red = new TLatex(0.15+shift_margin,0.70,str_stream_Chi2red.c_str());
	TLatex *l_diff_criteria = new TLatex(0.15+shift_margin,0.65,str_stream_diff_criteria.c_str());
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

	l_diff_criteria->SetNDC();
	l_diff_criteria->SetTextSize(0.04);

		
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

	l_diff_criteria->Draw("SAME");



	gPad->RedrawAxis();
	}

/*Mostramos el canvas y lo guardamos*/

canvas_deconv->Draw();
canvas_deconv->SaveAs(("../outputs/pdf/deconv_data_pdf/deconv_flux_multiplot/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".pdf").c_str());
//~ canvas_deconv->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".eps").c_str());


//~ delete canvas_deconv;


}

void deconv_flux_multiplot_by_stop_criteria(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation, string physic_list){
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

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

/*Llenamos un vector de histogramas de flujos deconvolucionados por semilla para el mismo evento, donde la iteracio del metodo em para por el criterio  de stop*/
int max_seed = 186;
//~ int max_seed = 150;
for(int i = 1; i<=max_seed;i++)
		{
			hist_deconv_flux_vec.push_back(deconv_hist_from_steps_and_seeds_TH1D(campaign,event,steps,timegrid,ndet,i,flux_representation, physic_list));
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

string input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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


TH1D* em_step_plot_Chi_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
//~ ROOT::RDataFrame df_seed_loop_step_2("em_loop_tree", input_complete_file);

string profile_name = "Chi2_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }
    
for(int i=0;i<251;i++)
	{
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();

const int binnum = (int)x_vec_seed.size()-1;


auto profile_model_chi2 = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");
//~ // auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "rdfentry_", "Chi2");
auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "seed_bin_edgeds", "Chi2");

//~ auto hist_counting_rates = df_seed_loop_step.Histo1D({profile_name_const,profile_name_const, binnum, x_bin_edgeds}, "Chi2");

//~ TH1D* hist_counting_rates_clone = (TH1D*)hist_counting_rates->Clone(hist_title_cr.c_str());



//~ auto Chi2_profile= df_seed_loop_step.Profile1D({profile_name_const, profile_name_const,50,0.,50}, "rdfentry_", "Chi2");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Chi2_profile->Clone(clone_name_const);
//~ TH1D* h_steps = (TH1D*)hist_counting_rates->Clone(clone_name_const);

h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "#chi^{2}");
return h_steps;

}

TH1D* em_step_plot_IntgTotal_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Total_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }

for(int i=0;i<251;i++)
	{
			//~ double x_bin_lowedges = i/5.;
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();
const int binnum = (int)x_vec_seed.size()-1;

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");

auto IntgTotal_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_total");


//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)IntgTotal_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "IntgTotal");
return h_steps;

}

TH1D* em_step_plot_Intgth_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Thermal_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }

for(int i=0;i<251;i++)
	{
			//~ double x_bin_lowedges = i/5.;
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();
const int binnum = (int)x_vec_seed.size()-1;

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");

auto Intgth_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_th");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgth_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgth");
return h_steps;

}

TH1D* em_step_plot_Intgep_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Epithermal_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }

for(int i=0;i<251;i++)
	{
			//~ double x_bin_lowedges = i/5.;
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();
const int binnum = (int)x_vec_seed.size()-1;

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");

auto Intgep_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_ep");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgep_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgep");
return h_steps;

}

TH1D* em_step_plot_Intgfs_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_Fast_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }

for(int i=0;i<251;i++)
	{
			//~ double x_bin_lowedges = i/5.;
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();
const int binnum = (int)x_vec_seed.size()-1;

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");

auto Intgfs_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_fs");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intgfs_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intgfs");
return h_steps;

}

TH1D* em_step_plot_Intghe_TH1D(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet;
stream_steps << steps;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

string input_complete_file;
if(steps==0)
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

else
{
	input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
}

ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);

string profile_name = "Intg_High_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
const char *profile_name_const = profile_name.c_str();

/*Definimos el nuevo binning de las semillas*/
vector<double> x_vec_seed;

//~ for(int i=0;i<186;i++)
	//~ {
		//~ if(i<=150)
			//~ {
				//~ double x_bin_lowedges = i/5.;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
		//~ if(i>150)
			//~ {
				//~ double x_bin_lowedges = (i- 135.)*2;
				//~ x_vec_seed.push_back(x_bin_lowedges);
			//~ }
    //~ }

for(int i=0;i<251;i++)
	{
			//~ double x_bin_lowedges = i/5.;
			double x_bin_lowedges = i/2.5;
			x_vec_seed.push_back(x_bin_lowedges);

    }

double *x_bin_edgeds = x_vec_seed.data();
const int binnum = (int)x_vec_seed.size()-1;

auto profile_model = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum, x_bin_edgeds, "");

auto Intghe_profile= df_seed_loop_step.Profile1D(profile_model, "seed_bin_edgeds", "Intg_he");

//~ Chi2_profile->SetLineColor(kOrange);
string clone_name = "Step_"+str_stream_steps ;
const char * clone_name_const = clone_name.c_str();
TH1D *h_steps = (TH1D*)Intghe_profile->Clone(clone_name_const);
h_steps->GetXaxis()->SetTitle("VWC%");
h_steps->GetYaxis()->SetTitle( "Intghe");
return h_steps;

}

/*Funcion que genera 3 canvas: el grafico de chi-squared en funcion de las iteraciones del EM sin stop para distintos valores de semilla
 * El grafico conjunto de  chi-squared en funcion de las iteraciones del EM y de las diferencias porcentuales de flujos continuos del EM por paso
 * En el tercer canvas se grafican los valores de flujos integrales por region de energia en funcion de las iteraciones para distintos valores de semilla*/
void em_step_plot_ChiSquare_by_step_TH1D(string campaign, int event, int steps, int max_steps, int seed_value, int timegrid, int ndet, string physic_list){

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
vector<vector<double>> chi2_matrix;
vector<vector<double>> diff_matrix;
vector<vector<double>> em_it_matrix;
vector<vector<double>> flux_deconv;

vector<vector<double>> intg_total_matrix;
vector<vector<double>> intg_th_matrix;
vector<vector<double>> intg_ep_matrix;
vector<vector<double>> intg_fs_matrix;
vector<vector<double>> intg_he_matrix;

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

for(int i = 1; i<=max_steps;i++){
	//~ hist_vec_Chi2.push_back(em_step_plot_Chi_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgTotal.push_back(em_step_plot_IntgTotal_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgTh.push_back(em_step_plot_Intgth_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgEp.push_back(em_step_plot_Intgep_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgFs.push_back(em_step_plot_Intgfs_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgHe.push_back(em_step_plot_Intghe_TH1D(campaign,event,i,timegrid,ndet));		

	if(steps==0)
	{
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	}

	else
	{
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	}

	ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	auto chi2_vec = df_seed_loop_step.Take<double>("Chi2").GetValue(); 
	auto em_it_vec = df_seed_loop_step.Take<double>("em_it").GetValue();
	auto diff_vec = df_seed_loop_step.Take<double>("diff_criteria").GetValue();
	auto intg_total_vec = df_seed_loop_step.Take<double>("Intg_total").GetValue();
	auto intg_th_vec = df_seed_loop_step.Take<double>("Intg_th").GetValue();
	auto intg_ep_vec = df_seed_loop_step.Take<double>("Intg_ep").GetValue();
	auto intg_fs_vec = df_seed_loop_step.Take<double>("Intg_fs").GetValue();
	auto intg_he_vec = df_seed_loop_step.Take<double>("Intg_he").GetValue();

	chi2_matrix.push_back(chi2_vec);
	em_it_matrix.push_back(em_it_vec);
	diff_matrix.push_back(diff_vec);
	intg_total_matrix.push_back(intg_total_vec);
	intg_th_matrix.push_back(intg_th_vec);
	intg_ep_matrix.push_back(intg_ep_vec);
	intg_fs_matrix.push_back(intg_fs_vec);
	intg_he_matrix.push_back(intg_he_vec);
}

/*********************************/

// Crea una paleta de colores arcoíris
//~ int nColors = 256; // Puedes ajustar este valor según tus necesidades
int nColors = 501; // Puedes ajustar este valor según tus necesidades
double stops[nColors];
double red[nColors];
double green[nColors];
double blue[nColors];

for (int i = 0; i < nColors; i++) {
    stops[i] = (double)i / (nColors - 1);
    red[i] = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
    green[i] = TMath::Sqrt(stops[i]);
    blue[i] = 1.0 - stops[i];
}

//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 255);
int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 500);

/*************************************/

TCanvas *canvas_chi2 = new TCanvas("chi2_by_step","chi2_by_step",960,1080);
canvas_chi2->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetOptStat(0);
//~ gStyle->SetStatX(0.95);      // X2NDC of the box (right edge)
//~ gStyle->SetStatY(0.95);      // Y2NDC of the box (top edge)
//~ gStyle->SetStatW(0.20);      // box width  (fraction of pad)
//~ gStyle->SetStatH(0.12);      // box height (fraction of pad)

//~ gStyle->SetPadTopMargin(0); //
//~ gStyle->SetPadRightMargin(0); //

canvas_chi2->Divide(1,1);

canvas_chi2->cd(1);

// --- Work on the first (and only) pad ---
TPad *p_cr = (TPad*)canvas_chi2->cd(1);

p_cr->SetRightMargin(0.027); //borde derecho 0
p_cr->SetLeftMargin(0.100156); //borde derecho 0
p_cr->SetTopMargin(0.025);
p_cr->SetBottomMargin(0.0677269);



/****STEPS***/
vector<double> x_vec_steps;
for(int i=1;i<=max_steps;i++)
	{
		x_vec_steps.push_back(i);
    }

double *x_steps_edgeds = x_vec_steps.data();

const int binnum_steps = (int) x_vec_steps.size()-1;

string hist_name;

string str_stream_seed_chi2;

vector<TH1D*> chi2_hist_vec;

for(int j=0;j<501;j++){
		//~ double x_bin_lowedges = i/5.;
	double x_seed = j/5.;
	//~ x_vec_seed.push_back(x_bin_lowedges);
	//~ stream_seed_chi2 << x_seed;
	ostringstream stream_seed_chi2;
	stream_seed_chi2 << x_seed;
	str_stream_seed_chi2 = stream_seed_chi2.str();
	hist_name = "Chi2_by_step_seed_"+str_stream_seed_chi2;
	TH1D* chi2_by_step = new TH1D(hist_name.c_str(),hist_name.c_str(), binnum_steps , x_steps_edgeds);
	
	for(int i=0;i<max_steps;i++){
	//~ for(int i=1;i<max_steps;i++){ //Nos saltamos el 1er paso
		chi2_by_step->SetBinContent(i+1,(chi2_matrix[i][j]));
		cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << endl;
	}

	chi2_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
	chi2_by_step->GetYaxis()->SetTitle("#bf{#chi^{2}}");
	chi2_by_step->SetTitle("");
	chi2_by_step->GetYaxis()->SetTitleOffset(0.95);
	chi2_by_step->GetYaxis()->SetTitleSize(0.05);
	chi2_hist_vec.push_back(chi2_by_step);
	//~ chi2_by_step->Draw("HIST");
}

double n_hist = chi2_hist_vec.size();
double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
TColor::InvertPalette();

double xmin = chi2_hist_vec[0]->GetXaxis()->GetXmin();
double xmax = chi2_hist_vec[0]->GetXaxis()->GetXmax();

double tolerance  = 5/100.; // 5%

TLine *l_new=new TLine(xmin,ndet,xmax,ndet);
TLine *l_new_upper=new TLine(xmin,ndet+tolerance*ndet,xmax,ndet+tolerance*ndet);
TLine *l_new_lower=new TLine(xmin,ndet-tolerance*ndet,xmax,ndet-tolerance*ndet);

l_new->SetLineColor(kRed);
l_new_upper->SetLineColor(kRed);
l_new_lower->SetLineColor(kRed);
l_new->SetLineWidth(2.0);
l_new_upper->SetLineWidth(2.0);
l_new_lower->SetLineWidth(2.0);
//~ l_new->SetLineColorAlpha(kRed, opaque_value);
//~ l_new->SetLineStyle(9);

chi2_hist_vec[0]->Draw("HIST");
chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,35.0);
chi2_hist_vec[0]->SetStats(0);

TBox *box = new TBox(xmin,ndet+tolerance*ndet,xmax,ndet-tolerance*ndet);
//~ box->SetFillStyle(1001);
box->SetFillColorAlpha(kRed,0.35);
//~ box->SetLineColor(kRed);


for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    chi2_hist_vec[j]->SetLineColor(colorIndex2);
	chi2_hist_vec[j]->Draw("HIST SAME");

}

l_new->Draw("SAME");
//~ l_new_upper->Draw("SAME");
//~ l_new_lower->Draw("SAME");
box->Draw("SAME");

canvas_chi2->Draw();
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+".pdf").c_str());
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+".svg").c_str());
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+".png").c_str());


TCanvas *canvas_chi2_and_diff = new TCanvas("chi2_and_diff_by_step","chi2_and_diff_by_step",1920,1080);
//~ gStyle->SetStatX(0.95);      // X2NDC of the box (right edge)
//~ gStyle->SetStatY(0.95);      // Y2NDC of the box (top edge)
//~ gStyle->SetStatW(0.20);      // box width  (fraction of pad)
//~ gStyle->SetStatH(0.12);      // box height (fraction of pad)

canvas_chi2_and_diff->Divide(2,1);

canvas_chi2_and_diff->cd(1);

chi2_hist_vec[0]->Draw("HIST");
//~ chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,75);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    chi2_hist_vec[j]->SetLineColor(colorIndex2);

	chi2_hist_vec[j]->Draw("HIST SAME");
}

l_new->Draw("SAME");
l_new_upper->Draw("SAME");
l_new_lower->Draw("SAME");

//~ TCanvas *canvas_diff = new TCanvas("diff_by_step","diff_by_step",1920,1080);

canvas_chi2_and_diff->cd(2);

string hist_name_diff;

string str_stream_seed_diff;

vector<TH1D*> diff_hist_vec;

for(int j=0;j<501;j++){
			//~ double x_bin_lowedges = i/5.;
			double x_seed = j/5.;
			//~ x_vec_seed.push_back(x_bin_lowedges);
		ostringstream stream_seed_diff;
		stream_seed_diff << x_seed;
		str_stream_seed_diff = stream_seed_diff.str();
		hist_name_diff = "Diff_by_step_seed_"+str_stream_seed_diff;
		TH1D* diff_by_step = new TH1D(hist_name_diff.c_str(),hist_name_diff.c_str(), binnum_steps , x_steps_edgeds);
		
		for(int i=0;i<max_steps;i++){
			diff_by_step->SetBinContent(i+1,(diff_matrix[i][j]));
			cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << " diff: " <<  diff_matrix[i][j] << endl;
		}

		diff_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		diff_by_step->GetYaxis()->SetTitle("#bf{#Delta_{#Phi_{i+1} - #Phi_{i}}}");
		diff_by_step->GetYaxis()->SetMaxDigits(1);
		diff_hist_vec.push_back(diff_by_step);
		//~ chi2_by_step->Draw("HIST");

}

//~ double n_hist = chi2_hist_vec.size();
//~ double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
//~ TColor::InvertPalette();

double xmin_diff = diff_hist_vec[0]->GetXaxis()->GetXmin();
double xmax_diff = diff_hist_vec[0]->GetXaxis()->GetXmax();

double diff_threshold = 0.02;
TLine *l_new_diff=new TLine(xmin_diff,diff_threshold,xmax_diff,diff_threshold);
TLine *l_new_diff_upper=new TLine(xmin_diff,diff_threshold+tolerance*diff_threshold,xmax_diff,diff_threshold+tolerance*diff_threshold);
TLine *l_new_diff_lower=new TLine(xmin_diff,diff_threshold-tolerance*diff_threshold,xmax_diff,diff_threshold-tolerance*diff_threshold);


l_new_diff->SetLineColor(kRed);
l_new_diff_upper->SetLineColor(kRed);
l_new_diff_lower->SetLineColor(kRed);
l_new_diff->SetLineWidth(2.0);
l_new_diff_upper->SetLineWidth(2.0);
l_new_diff_lower->SetLineWidth(2.0);
//~ l_new->SetLineColorAlpha(kRed, opaque_value);
//~ l_new_diff->SetLineStyle(9);



diff_hist_vec[0]->Draw("HIST");
diff_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    diff_hist_vec[j]->SetLineColor(colorIndex2);

	diff_hist_vec[j]->Draw("HIST SAME");
}

l_new_diff->Draw("SAME");
l_new_diff_upper->Draw("SAME");
l_new_diff_lower->Draw("SAME");


TCanvas *canvas_intg_total = new TCanvas("intg_total_by_step","intg_total_by_step",1920,1080);

canvas_intg_total ->Divide(2,3);

string hist_name_intg_total;
string hist_name_intg_th;
string hist_name_intg_ep;
string hist_name_intg_fs;
string hist_name_intg_he;

vector<TH1D*> intg_total_hist_vec;
vector<TH1D*> intg_th_hist_vec;
vector<TH1D*> intg_ep_hist_vec;
vector<TH1D*> intg_fs_hist_vec;
vector<TH1D*> intg_he_hist_vec;

double title_size = 0.08;
double x_title_size = 0.05;
double title_offset = 0.5;
double x_title_offset = 0.7;
int y_axis_max_dig = 2;



string str_stream_seed;

for(int j=0;j<501;j++){
			//~ double x_bin_lowedges = i/5.;
			double x_seed = j/5.;
			//~ x_vec_seed.push_back(x_bin_lowedges);
		ostringstream stream_seed;
		stream_seed << x_seed;
		str_stream_seed = stream_seed.str();
		
		hist_name_intg_total = "Intg_total_by_step_seed_"+str_stream_seed;
		hist_name_intg_th = "Intg_th_by_step_seed_"+str_stream_seed;
		hist_name_intg_ep = "Intg_ep_by_step_seed_"+str_stream_seed;
		hist_name_intg_fs = "Intg_fs_by_step_seed_"+str_stream_seed;
		hist_name_intg_he = "Intg_he_by_step_seed_"+str_stream_seed;

		TH1D* intg_total_by_step = new TH1D(hist_name_intg_total.c_str(),hist_name_intg_total.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_th_by_step = new TH1D(hist_name_intg_th.c_str(),hist_name_intg_th.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_ep_by_step = new TH1D(hist_name_intg_ep.c_str(),hist_name_intg_ep.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_fs_by_step = new TH1D(hist_name_intg_fs.c_str(),hist_name_intg_fs.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_he_by_step = new TH1D(hist_name_intg_he.c_str(),hist_name_intg_he.c_str(), binnum_steps , x_steps_edgeds);
		
		for(int i=0;i<max_steps;i++){
			intg_total_by_step->SetBinContent(i+1,(intg_total_matrix[i][j]));
			intg_th_by_step->SetBinContent(i+1,(intg_th_matrix[i][j]));
			intg_ep_by_step->SetBinContent(i+1,(intg_ep_matrix[i][j]));
			intg_fs_by_step->SetBinContent(i+1,(intg_fs_matrix[i][j]));
			intg_he_by_step->SetBinContent(i+1,(intg_he_matrix[i][j]));


			cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << " diff: " <<  diff_matrix[i][j] << " Intg total: " << intg_total_matrix[i][j] << endl;
		}


		intg_total_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_total_by_step->GetYaxis()->SetTitle("#bf{#Phi_{total}}");
		intg_total_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_total_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_total_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_total_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_total_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_total_hist_vec.push_back(intg_total_by_step);
		
		intg_th_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_th_by_step->GetYaxis()->SetTitle("#bf{#Phi_{th}}");
		intg_th_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_th_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_th_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_th_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_th_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_th_hist_vec.push_back(intg_th_by_step);

		intg_ep_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_ep_by_step->GetYaxis()->SetTitle("#bf{#Phi_{ep}}");
		intg_ep_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_ep_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_ep_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_ep_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_ep_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_ep_hist_vec.push_back(intg_ep_by_step);
		
		intg_fs_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_fs_by_step->GetYaxis()->SetTitle("#bf{#Phi_{fs}}");
		intg_fs_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_fs_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_fs_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_fs_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_fs_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_fs_hist_vec.push_back(intg_fs_by_step);

		intg_he_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_he_by_step->GetYaxis()->SetTitle("#bf{#Phi_{he}}");
		intg_he_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_he_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_he_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_he_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_he_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_he_hist_vec.push_back(intg_he_by_step);


}

//~ double n_hist = chi2_hist_vec.size();
//~ double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
//~ TColor::InvertPalette();

canvas_intg_total->cd(1);

double xmin_intg_total = intg_total_hist_vec[0]->GetXaxis()->GetXmin();
double xmax_intg_total = intg_total_hist_vec[0]->GetXaxis()->GetXmax();

TLine *l_new_intg_total=new TLine(xmin_intg_total,0.02,xmax_intg_total,0.02);
l_new_intg_total->SetLineColor(kRed);
l_new_intg_total->SetLineWidth(2.0);

intg_total_hist_vec[0]->Draw("HIST");
//~ intg_total_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    intg_total_hist_vec[j]->SetLineColor(colorIndex2);

	intg_total_hist_vec[j]->Draw("HIST SAME");
	//~ l_new_intg_total->DrawClone("SAME");
}

canvas_intg_total->cd(2);

intg_th_hist_vec[0]->Draw("HIST");
//~ intg_th_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    intg_th_hist_vec[j]->SetLineColor(colorIndex2);

	intg_th_hist_vec[j]->Draw("HIST SAME");
	//~ l_new_intg_th->DrawClone("SAME");
}

canvas_intg_total->cd(3);

intg_ep_hist_vec[0]->Draw("HIST");
//~ intg_ep_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    intg_ep_hist_vec[j]->SetLineColor(colorIndex2);

	intg_ep_hist_vec[j]->Draw("HIST SAME");
	//~ l_new_intg_ep->DrawClone("SAME");
}


canvas_intg_total->cd(4);

intg_fs_hist_vec[0]->Draw("HIST");
//~ intg_fs_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    intg_fs_hist_vec[j]->SetLineColor(colorIndex2);

	intg_fs_hist_vec[j]->Draw("HIST SAME");
	//~ l_new_intg_fs->DrawClone("SAME");
}


canvas_intg_total->cd(5);

intg_he_hist_vec[0]->Draw("HIST");
//~ intg_he_hist_vec[0]->GetYaxis()->SetRangeUser(0.0,0.2);

for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    intg_he_hist_vec[j]->SetLineColor(colorIndex2);

	intg_he_hist_vec[j]->Draw("HIST SAME");
	//~ l_new_intg_he->DrawClone("SAME");
}


//~ string profile_name = "Chi2_Event_"+ stream_event.str()+"_Step_"+stream_steps.str();
//~ const char *profile_name_const = profile_name.c_str();

//~ /*Definimos el nuevo binning de las semillas*/
//~ vector<double> x_vec_seed;

    
//~ for(int i=0;i<251;i++)
	//~ {
			//~ double x_bin_lowedges = i/2.5;
			//~ x_vec_seed.push_back(x_bin_lowedges);

    //~ }

//~ double *x_bin_edgeds = x_vec_seed.data();

//~ const int binnum = (int)x_vec_seed.size()-1;

//~ /****STEPS***/

//~ vector<double> x_vec_steps;
//~ for(int i=1;i<=max_steps;i++)
	//~ {
			//~ // double x_bin_lowedges = i/2.5;
			//~ x_vec_steps.push_back(i);
    //~ }

//~ double *x_steps_edgeds = x_vec_steps.data();

//~ const int binnum_steps = (int) x_vec_steps.size()-1;


//~ auto profile_model_chi2 = ROOT::RDF::TProfile1DModel(profile_name_const,profile_name_const, binnum_steps, x_steps_edgeds, "");
 //~ // auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "rdfentry_", "Chi2");
//~ auto Chi2_profile= df_seed_loop_step.Profile1D(profile_model_chi2, "seed_bin_edgeds", "Chi2");

//~ // auto hist_counting_rates = df_seed_loop_step.Histo1D({profile_name_const,profile_name_const, binnum, x_bin_edgeds}, "Chi2");

//~ // TH1D* hist_counting_rates_clone = (TH1D*)hist_counting_rates->Clone(hist_title_cr.c_str());



//~ // auto Chi2_profile= df_seed_loop_step.Profile1D({profile_name_const, profile_name_const,50,0.,50}, "rdfentry_", "Chi2");

//~ // Chi2_profile->SetLineColor(kOrange);
//~ string clone_name = "Step_"+str_stream_steps ;
//~ const char * clone_name_const = clone_name.c_str();
//~ TH1D *h_steps = (TH1D*)Chi2_profile->Clone(clone_name_const);
//~ // TH1D* h_steps = (TH1D*)hist_counting_rates->Clone(clone_name_const);

//~ h_steps->GetXaxis()->SetTitle("VWC%");
//~ h_steps->GetYaxis()->SetTitle( "#chi^{2}");
//~ return h_steps;

}

/*Funcion de mejora de visualizacion que genera 3 canvas: el grafico de chi-squared en funcion de las iteraciones del EM sin stop para distintos valores de semilla
 * El grafico conjunto de  chi-squared en funcion de las iteraciones del EM y de las diferencias porcentuales de flujos continuos del EM por paso
 * En el tercer canvas se grafican los valores de flujos integrales por region de energia en funcion de las iteraciones para distintos valores de semilla*/
void em_step_plot_ChiSquare_by_step_TH1D_update(string campaign, int event, int steps, int max_steps, int seed_value, int timegrid, int ndet, string physic_list, string scale_factor){

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
vector<vector<double>> chi2_matrix;
vector<vector<double>> diff_matrix;
vector<vector<double>> em_it_matrix;
vector<vector<double>> flux_deconv;

vector<vector<double>> intg_total_matrix;
vector<vector<double>> intg_th_matrix;
vector<vector<double>> intg_ep_matrix;
vector<vector<double>> intg_fs_matrix;
vector<vector<double>> intg_he_matrix;

string campaign_path;
if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

for(int i = 1; i<=max_steps;i++){
	//~ hist_vec_Chi2.push_back(em_step_plot_Chi_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgTotal.push_back(em_step_plot_IntgTotal_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgTh.push_back(em_step_plot_Intgth_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgEp.push_back(em_step_plot_Intgep_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgFs.push_back(em_step_plot_Intgfs_TH1D(campaign,event,i,timegrid,ndet));
	//~ hist_vec_IntgHe.push_back(em_step_plot_Intghe_TH1D(campaign,event,i,timegrid,ndet));		

	if(steps==0)
	{
		if(scale_factor=="ws"){
		//Con factor 0.25
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"_ws/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		}
		if(scale_factor=="wos"){
		//Sin factor 
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		}
		//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	}

	else
	{
		if(scale_factor=="ws"){
		//Con factor 0.25
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"_ws/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		}
		if(scale_factor=="wos"){
		//Sin factor 
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+std::to_string(i)+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
		}
		//~ ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	}

	ROOT::RDataFrame df_seed_loop_step("em_loop_tree", input_complete_file);
	auto chi2_vec = df_seed_loop_step.Take<double>("Chi2").GetValue(); 
	auto em_it_vec = df_seed_loop_step.Take<double>("em_it").GetValue();
	auto diff_vec = df_seed_loop_step.Take<double>("diff_criteria").GetValue();
	auto intg_total_vec = df_seed_loop_step.Take<double>("Intg_total").GetValue();
	auto intg_th_vec = df_seed_loop_step.Take<double>("Intg_th").GetValue();
	auto intg_ep_vec = df_seed_loop_step.Take<double>("Intg_ep").GetValue();
	auto intg_fs_vec = df_seed_loop_step.Take<double>("Intg_fs").GetValue();
	auto intg_he_vec = df_seed_loop_step.Take<double>("Intg_he").GetValue();

	chi2_matrix.push_back(chi2_vec);
	em_it_matrix.push_back(em_it_vec);
	diff_matrix.push_back(diff_vec);
	intg_total_matrix.push_back(intg_total_vec);
	intg_th_matrix.push_back(intg_th_vec);
	intg_ep_matrix.push_back(intg_ep_vec);
	intg_fs_matrix.push_back(intg_fs_vec);
	intg_he_matrix.push_back(intg_he_vec);
}

/*********************************/

// Crea una paleta de colores arcoíris
//~ int nColors = 256; // Puedes ajustar este valor según tus necesidades
int nColors = 501; // Puedes ajustar este valor según tus necesidades
double stops[nColors];
double red[nColors];
double green[nColors];
double blue[nColors];

for (int i = 0; i < nColors; i++) {
    stops[i] = (double)i / (nColors - 1);
    red[i] = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
    green[i] = TMath::Sqrt(stops[i]);
    blue[i] = 1.0 - stops[i];
}

//~ int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 255);
int rainbowColorPalette = TColor::CreateGradientColorTable(nColors, stops, red, green, blue, 500);

/*************************************/

TCanvas *canvas_chi2 = new TCanvas("chi2_by_step","chi2_by_step",960,1080);
canvas_chi2->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetOptStat(0);
//~ gStyle->SetStatX(0.95);      // X2NDC of the box (right edge)
//~ gStyle->SetStatY(0.95);      // Y2NDC of the box (top edge)
//~ gStyle->SetStatW(0.20);      // box width  (fraction of pad)
//~ gStyle->SetStatH(0.12);      // box height (fraction of pad)

//~ gStyle->SetPadTopMargin(0); //
//~ gStyle->SetPadRightMargin(0); //

canvas_chi2->Divide(1,1);

canvas_chi2->cd(1);

// --- Work on the first (and only) pad ---
TPad *p_cr = (TPad*)canvas_chi2->cd(1);

p_cr->SetRightMargin(0.027); //borde derecho 0
p_cr->SetLeftMargin(0.100156); //borde derecho 0
p_cr->SetTopMargin(0.025);
p_cr->SetBottomMargin(0.0677269);



/****STEPS***/
vector<double> x_vec_steps;
for(int i=1;i<=max_steps;i++)
	{
		x_vec_steps.push_back(i);
    }

double *x_steps_edgeds = x_vec_steps.data();

const int binnum_steps = (int) x_vec_steps.size()-1;

string hist_name;

string str_stream_seed_chi2;

vector<TH1D*> chi2_hist_vec;

for(int j=0;j<501;j++){
		//~ double x_bin_lowedges = i/5.;
	double x_seed = j/5.;
	//~ x_vec_seed.push_back(x_bin_lowedges);
	//~ stream_seed_chi2 << x_seed;
	ostringstream stream_seed_chi2;
	stream_seed_chi2 << x_seed;
	str_stream_seed_chi2 = stream_seed_chi2.str();
	hist_name = "Chi2_by_step_seed_"+str_stream_seed_chi2;
	TH1D* chi2_by_step = new TH1D(hist_name.c_str(),hist_name.c_str(), binnum_steps , x_steps_edgeds);
	
	for(int i=0;i<max_steps;i++){
	//~ for(int i=1;i<max_steps;i++){ //Nos saltamos el 1er paso
		chi2_by_step->SetBinContent(i+1,(chi2_matrix[i][j]));
		//~ cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << endl;
	}

	chi2_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
	chi2_by_step->GetYaxis()->SetTitle("#bf{#chi^{2}}");
	chi2_by_step->SetTitle("");
	chi2_by_step->GetYaxis()->SetTitleOffset(0.95);
	chi2_by_step->GetYaxis()->SetTitleSize(0.05);
	chi2_hist_vec.push_back(chi2_by_step);
	//~ chi2_by_step->Draw("HIST");
}

double n_hist = chi2_hist_vec.size();
double step = static_cast<double>(nColors) / static_cast<double>(n_hist);
TColor::InvertPalette();



double xmin = chi2_hist_vec[0]->GetXaxis()->GetXmin();
double xmax = chi2_hist_vec[0]->GetXaxis()->GetXmax();

double tolerance  = 5/100.; // 5%

TLine *l_new=new TLine(xmin,ndet,xmax,ndet);
TLine *l_new_upper=new TLine(xmin,ndet+tolerance*ndet,xmax,ndet+tolerance*ndet);
TLine *l_new_lower=new TLine(xmin,ndet-tolerance*ndet,xmax,ndet-tolerance*ndet);

l_new->SetLineColor(kRed);
l_new_upper->SetLineColor(kRed);
l_new_lower->SetLineColor(kRed);
l_new->SetLineWidth(2.0);
l_new_upper->SetLineWidth(2.0);
l_new_lower->SetLineWidth(2.0);
//l_new->SetLineColorAlpha(kRed, opaque_value);
// l_new->SetLineStyle(9);

chi2_hist_vec[0]->Draw("HIST");

if(ndet==16){chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,400.0);}
if(ndet==11){chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,35.0);}

chi2_hist_vec[0]->SetStats(0);

TBox *box = new TBox(xmin,ndet+tolerance*ndet,xmax,ndet-tolerance*ndet);
//~ box->SetFillStyle(1001);
box->SetFillColorAlpha(kRed,0.35);
//~ box->SetLineColor(kRed);


for(int j=1;j<501;j++){

	int colorIndex = static_cast<int>(j*step);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 256;
    int colorIndex2 = 51 + colorIndex * 48 /501;
    chi2_hist_vec[j]->SetLineColor(colorIndex2);
	chi2_hist_vec[j]->Draw("HIST SAME");

}

l_new->Draw("SAME");
//~ l_new_upper->Draw("SAME");
//~ l_new_lower->Draw("SAME");
//~ box->Draw("SAME");

canvas_chi2->Draw();
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_factor+".pdf").c_str());
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_factor+".svg").c_str());
canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_factor+".png").c_str());

/*************************************/
/*** 2nd derivative of Chi2 curves ***/
/*************************************/

vector<TH1D*> chi2_dd2_hist_vec;
chi2_dd2_hist_vec.reserve(chi2_hist_vec.size());

const int nbins = chi2_hist_vec[0]->GetNbinsX();

// --- construimos histos de 2da derivada ---
for (size_t j = 0; j < chi2_hist_vec.size(); ++j) {

    TH1D* h = chi2_hist_vec[j];

    // Copiamos binning en X (mismo eje)
    TH1D* hdd2 = (TH1D*)h->Clone(Form("%s_dd2", h->GetName()));
    hdd2->Reset("ICES");
    hdd2->SetTitle("");
    hdd2->GetXaxis()->SetTitle("#bf{EM iteration}");
    hdd2->GetYaxis()->SetTitle("#bf{d^{2}#chi^{2}/ds^{2}}");
    hdd2->GetYaxis()->SetTitleOffset(0.95);
    hdd2->GetYaxis()->SetTitleSize(0.05);

    // Diferencias finitas centrales (dx=1). En bordes ponemos 0.
    hdd2->SetBinContent(1, 0.0);
    hdd2->SetBinContent(nbins, 0.0);

    for (int i = 2; i <= nbins-1; ++i) {
        double y_prev = h->GetBinContent(i-1);
        double y      = h->GetBinContent(i);
        double y_next = h->GetBinContent(i+1);

        double dd2 = (y_next - 2.0*y + y_prev); // dx=1
        hdd2->SetBinContent(i, dd2);
    }

    // (Opcional) reducir ruido un poco:
    // hdd2->Smooth(1); // o 2 si está muy ruidoso

    chi2_dd2_hist_vec.push_back(hdd2);
}

// --- (Opcional) estimar punto de inflexión por cambio de signo en dd2 ---
vector<double> inflection_x(chi2_dd2_hist_vec.size(), -999.0);

for (size_t j = 0; j < chi2_dd2_hist_vec.size(); ++j) {
    TH1D* hdd2 = chi2_dd2_hist_vec[j];

    // Busca primer cruce por 0 desde bin=2 (puedes empezar en 3 si quieres)
    for (int i = 2; i <= nbins-2; ++i) {
        double a = hdd2->GetBinContent(i);
        double b = hdd2->GetBinContent(i+1);

        if (a == 0.0) { inflection_x[j] = hdd2->GetBinCenter(i); break; }

        // Cambio de signo => inflexión aproximada
        if (a*b < 0.0) {
            // Interpolación lineal del cruce por cero entre i e i+1
            double x1 = hdd2->GetBinCenter(i);
            double x2 = hdd2->GetBinCenter(i+1);
            double x0 = x1 + (0.0 - a) * (x2 - x1) / (b - a);
            inflection_x[j] = x0;
            break;
        }
    }
    // Puedes imprimir si quieres:
    // cout << "seed idx " << j << " inflection ~ " << inflection_x[j] << endl;
}

// --- Canvas único para todas las 2das derivadas ---
TCanvas* c_dd2 = new TCanvas("chi2_dd2_by_step", "chi2_dd2_by_step", 1920, 1080);
c_dd2->cd();

TPad* p_dd2 = (TPad*)gPad;
p_dd2->SetLeftMargin(0.10);
p_dd2->SetRightMargin(0.03);
p_dd2->SetTopMargin(0.03);
p_dd2->SetBottomMargin(0.07);

// Para ver mejor la zona útil
chi2_dd2_hist_vec[0]->GetXaxis()->SetRangeUser(2, max_steps);

// Línea horizontal en 0 (para ver cruces)
//~ double x0min = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmin();
//~ double x0max = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmax();
//~ TLine* l0 = new TLine(x0min, 0.0, x0max, 0.0);
//~ l0->SetLineColor(kBlack);
//~ l0->SetLineWidth(2);

// Dibujamos primero el 0
chi2_dd2_hist_vec[0]->Draw("HIST");
//~ l0->Draw("SAME");

// Colores igual que antes
double n_hist2 = chi2_dd2_hist_vec.size();
double step2 = static_cast<double>(nColors) / static_cast<double>(n_hist2);

for (size_t j = 1; j < chi2_dd2_hist_vec.size(); ++j) {
    int colorIndex  = static_cast<int>(j * step2);
    int colorIndex2 = 51 + colorIndex * 48 / 501;
    chi2_dd2_hist_vec[j]->SetLineColor(colorIndex2);
    chi2_dd2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
    chi2_dd2_hist_vec[j]->Draw("HIST SAME");
}

 // (Opcional) marcar inflexiones con líneas verticales (ojo: 501 líneas puede ensuciar)
 // Si quieres solo una “promedio” o percentil, te puedo dejar esa versión.
 for (size_t j = 0; j < inflection_x.size(); ++j) {
     if (inflection_x[j] > 0) {
         TLine* lv = new TLine(inflection_x[j], p_dd2->GetUymin(), inflection_x[j], p_dd2->GetUymax());
         lv->SetLineColor(kGray+1);
         lv->SetLineStyle(3);
         lv->Draw("SAME");
     }
 }


//*************************************/
/*** 2nd derivative + knee (500 steps) ***/
/*************************************/

// ---- parámetros recomendados para 500 pasos y caída rápida ----
const int    START_BIN   = 12;   // ignora arranque
const int    K_CONSEC    = 12;   // meseta sostenida
const double EPS_FRAC    = 0.03; // eps = 3% del max(|dd2|)
const double STRONG_MULT = 5.0;  // "fuerte" si |dd2| > 5*eps

// helper: mediana robusta
auto median_of = [&](vector<double> v) -> double {
    v.erase(std::remove_if(v.begin(), v.end(), [](double x){ return x < 0; }), v.end());
    if (v.empty()) return -1.0;
    size_t mid = v.size()/2;
    std::nth_element(v.begin(), v.begin()+mid, v.end());
    double m = v[mid];
    if (v.size()%2==0) {
        auto it = std::max_element(v.begin(), v.begin()+mid);
        m = 0.5*(m + *it);
    }
    return m;
};

// 2) rodilla por seed: primer tramo de K bins con |dd2| < eps después de haber visto curvatura fuerte
vector<double> knee_step_per_seed(chi2_hist_vec.size(), -1.0);
vector<double> knee_chi2_per_seed(chi2_hist_vec.size(), -1.0);

for (size_t j = 0; j < chi2_hist_vec.size(); ++j) {

    TH1D* hchi = chi2_hist_vec[j];
    TH1D* hdd2 = chi2_dd2_hist_vec[j];

    // maxAbs en rango útil (desde START_BIN)
    double maxAbs = 0.0;
    for (int i = START_BIN; i <= nbins; ++i) {
        maxAbs = std::max(maxAbs, std::abs(hdd2->GetBinContent(i)));
    }
    if (maxAbs <= 0) continue;

    const double eps    = EPS_FRAC * maxAbs;
    const double strong = STRONG_MULT * eps;

    bool strongSeen = false;
    int  consec = 0;
    int  knee_bin = -1;

    for (int i = START_BIN; i <= nbins; ++i) {
        double v = std::abs(hdd2->GetBinContent(i));

        if (v > strong) strongSeen = true;

        if (strongSeen && v < eps) {
            consec++;
            if (consec >= K_CONSEC) {
                knee_bin = i - K_CONSEC + 1; // inicio del tramo plano
                break;
            }
        } else {
            consec = 0;
        }
    }

    if (knee_bin < 0) continue;

    knee_step_per_seed[j] = hdd2->GetBinCenter(knee_bin);
    knee_chi2_per_seed[j] = hchi->GetBinContent(knee_bin);
}

// 3) rodilla global robusta (mediana)
double knee_step_global = median_of(knee_step_per_seed);
double knee_chi2_global = -1.0;

if (knee_step_global > 0) {
    int kb = chi2_hist_vec[0]->FindBin(knee_step_global);
    vector<double> chi2_at_kb;
    chi2_at_kb.reserve(chi2_hist_vec.size());
    for (size_t j=0;j<chi2_hist_vec.size();++j){
        if (knee_step_per_seed[j] > 0) chi2_at_kb.push_back(chi2_hist_vec[j]->GetBinContent(kb));
    }
    knee_chi2_global = median_of(chi2_at_kb);
}

cout << "=== KNEE (global median, 500 steps) ===\n"
     << "knee_step ~ " << knee_step_global
     << "   knee_chi2 ~ " << knee_chi2_global << endl;

// 4) canvas dd2 (todas las curvas) + línea y=0 + línea vertical en rodilla global
//~ TCanvas* c_dd2 = new TCanvas("chi2_dd2_by_step", "chi2_dd2_by_step", 1920, 1080);
//~ c_dd2->cd();
//~ TPad* p_dd2 = (TPad*)gPad;
//~ p_dd2->SetLeftMargin(0.10);
//~ p_dd2->SetRightMargin(0.03);
//~ p_dd2->SetTopMargin(0.03);
//~ p_dd2->SetBottomMargin(0.07);

//~ chi2_dd2_hist_vec[0]->GetXaxis()->SetRangeUser(2, max_steps);
//~ chi2_dd2_hist_vec[0]->Draw("HIST");

// línea horizontal en 0
double xmin0 = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmin();
double xmax0 = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmax();
TLine* l0 = new TLine(xmin0, 0.0, xmax0, 0.0);
l0->SetLineColor(kBlack);
l0->SetLineWidth(2);
l0->Draw("SAME");

// colores consistentes con tu esquema
//~ double n_hist2 = chi2_dd2_hist_vec.size();
//~ double step2   = static_cast<double>(nColors) / static_cast<double>(n_hist2);

//~ for (size_t j = 1; j < chi2_dd2_hist_vec.size(); ++j) {
    //~ int colorIndex  = static_cast<int>(j * step2);
    //~ int colorIndex2 = 51 + colorIndex * 48 / 501;
    //~ chi2_dd2_hist_vec[j]->SetLineColor(colorIndex2);
    //~ chi2_dd2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
    //~ chi2_dd2_hist_vec[j]->Draw("HIST SAME");
//~ }

// línea vertical en rodilla global
p_dd2->Update();
if (knee_step_global > 0) {
    double y1 = p_dd2->GetUymin();
    double y2 = p_dd2->GetUymax();
    TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
    lk->SetLineColor(kBlack);
    lk->SetLineStyle(2);
    lk->SetLineWidth(3);
    lk->Draw("SAME");

    // etiqueta
    TLatex* t = new TLatex(0.15, 0.92,
        Form("#bf{knee: step=%.0f, #chi^{2}~%.3g}", knee_step_global, knee_chi2_global));
    t->SetNDC();
    t->SetTextSize(0.04);
    t->Draw("SAME");
}

c_dd2->Update();

/*************************************/
/*** Knee-step distribution (IQR)   ***/
/*************************************/

// Recolectar valores válidos
vector<double> knees;
knees.reserve(knee_step_per_seed.size());
for (double ks : knee_step_per_seed) {
    if (ks > 0) knees.push_back(ks);
}

if (!knees.empty()) {

    // --- cuantiles robustos (Q1, median, Q3) ---
    auto quantile = [&](vector<double> v, double q)->double{
        // q en [0,1]
        if (v.empty()) return -1.0;
        std::sort(v.begin(), v.end());
        double pos = q * (v.size() - 1);
        size_t i = (size_t)std::floor(pos);
        size_t j = (size_t)std::ceil(pos);
        if (i == j) return v[i];
        double t = pos - i;
        return v[i]*(1.0 - t) + v[j]*t;
    };

    double q1  = quantile(knees, 0.25);
    double med = quantile(knees, 0.50);
    double q3  = quantile(knees, 0.75);
    double iqr = q3 - q1;

    cout << "=== Knee-step distribution ===\n"
         << "N(valid)=" << knees.size()
         << "  Q1=" << q1 << "  Med=" << med << "  Q3=" << q3
         << "  IQR=" << iqr << endl;

    // --- histograma (bins de 1 iteración, con 500 pasos) ---
    // OJO: tu X empieza en 1, así que hacemos [0.5, max_steps+0.5]
    TH1D* h_knee = new TH1D("h_knee_step",
                           "Knee-step distribution;EM iteration (knee);Counts",
                           max_steps, 0.5, max_steps + 0.5);

    for (double ks : knees) h_knee->Fill(ks);

    // --- opcional: distribución de chi2 en la rodilla (por seed) ---
    TH1D* h_knee_chi2 = new TH1D("h_knee_chi2",
                                 "Chi2 at knee;#chi^{2}(knee);Counts",
                                 120, 0.0, (ndet==16 ? 400.0 : 35.0)); // ajusta si quieres
    for (size_t j=0;j<knee_chi2_per_seed.size();++j){
        if (knee_step_per_seed[j] > 0 && knee_chi2_per_seed[j] > 0)
            h_knee_chi2->Fill(knee_chi2_per_seed[j]);
    }

    // --- canvas con 2 pads (izq: knee_step, der: chi2@knee) ---
    TCanvas* c_knee_dist = new TCanvas("c_knee_dist", "knee distributions", 1920, 900);
    c_knee_dist->Divide(2,1);

    // ===== pad 1: hist knee_step + Q1/Med/Q3 =====
    c_knee_dist->cd(1);
    TPad* p1 = (TPad*)gPad;
    p1->SetLeftMargin(0.10);
    p1->SetRightMargin(0.03);
    p1->SetBottomMargin(0.10);

    h_knee->SetStats(0);
    h_knee->Draw("HIST");

    p1->Update();

	// límites reales del eje Y (para que la banda cubra todo el histograma)
	double y_min = p1->GetUymin();
	double y_max = p1->GetUymax();

	// ===== Banda IQR (Q1–Q3) =====
	TBox* box_iqr = new TBox(q1, y_min, q3, y_max);
	box_iqr->SetFillColorAlpha(kAzure-9, 0.35);  // color suave
	box_iqr->SetLineColor(kAzure-9);
	box_iqr->SetLineWidth(2);
	box_iqr->Draw("SAME");

	// ===== Líneas verticales =====
	TLine* l_q1  = new TLine(q1,  y_min, q1,  y_max);
	TLine* l_q3  = new TLine(q3,  y_min, q3,  y_max);
	TLine* l_med = new TLine(med, y_min, med, y_max);

	l_q1->SetLineColor(kBlue+2);
	l_q3->SetLineColor(kBlue+2);
	l_med->SetLineColor(kBlack);

	l_q1->SetLineStyle(3);
	l_q3->SetLineStyle(3);
	l_med->SetLineStyle(2);

	l_q1->SetLineWidth(3);
	l_q3->SetLineWidth(3);
	l_med->SetLineWidth(4);

	l_q1->Draw("SAME");
	l_q3->Draw("SAME");
	l_med->Draw("SAME");

	// ===== Texto explicativo =====
	TLatex* t_iqr = new TLatex(
		0.12, 0.92,
		Form("#bf{Median = %.0f   IQR = [%.0f , %.0f]  (#Delta = %.0f)}",
			 med, q1, q3, q3-q1)
	);
	t_iqr->SetNDC();
	t_iqr->SetTextSize(0.04);
	t_iqr->Draw("SAME");

    //~ p1->Update();
    //~ double y1 = p1->GetUymin();
    //~ double y2 = p1->GetUymax();

    //~ TLine* l_q1  = new TLine(q1,  y1, q1,  y2);
    //~ TLine* l_med = new TLine(med, y1, med, y2);
    //~ TLine* l_q3  = new TLine(q3,  y1, q3,  y2);

    //~ l_q1->SetLineColor(kGray+2);
    //~ l_q3->SetLineColor(kGray+2);
    //~ l_med->SetLineColor(kBlack);

    //~ l_q1->SetLineStyle(3);
    //~ l_q3->SetLineStyle(3);
    //~ l_med->SetLineStyle(2);

    //~ l_q1->SetLineWidth(3);
    //~ l_q3->SetLineWidth(3);
    //~ l_med->SetLineWidth(4);

    //~ l_q1->Draw("SAME");
    //~ l_med->Draw("SAME");
    //~ l_q3->Draw("SAME");

    //~ TLatex* tx = new TLatex(0.12, 0.92,
        //~ Form("#bf{Q1=%.0f  Med=%.0f  Q3=%.0f  (IQR=%.0f)   N=%zu}",
             //~ q1, med, q3, iqr, knees.size()));
    //~ tx->SetNDC();
    //~ tx->SetTextSize(0.04);
    //~ tx->Draw("SAME");

    // ===== pad 2: hist chi2@knee =====
    c_knee_dist->cd(2);
    TPad* p2 = (TPad*)gPad;
    p2->SetLeftMargin(0.10);
    p2->SetRightMargin(0.03);
    p2->SetBottomMargin(0.10);

    h_knee_chi2->SetStats(0);
    h_knee_chi2->Draw("HIST");

    // Guardar
    c_knee_dist->Update();

}

/******************************************************************************/
/************************DIFF flux & CHI Squared CANVAS************************/
/******************************************************************************/

vector<TH1D*> diff_hist_vec;
diff_hist_vec.reserve(501);

for(int j=0;j<501;j++){
		double x_seed = j/5.;
		ostringstream stream_seed_diff;
		stream_seed_diff << x_seed;
		string str_stream_seed_diff = stream_seed_diff.str();
		string hist_name_diff = "Diff_by_step_seed_"+str_stream_seed_diff;

		TH1D* diff_by_step = new TH1D(hist_name_diff.c_str(),hist_name_diff.c_str(), binnum_steps , x_steps_edgeds);
		
		for(int i=0;i<max_steps;i++){
			// diff_by_step->SetBinContent(i+1,(diff_matrix[i][j]*100.)); //diff flux porcentual
			diff_by_step->SetBinContent(i+1,(100*diff_matrix[i][j])); //diff flux porcentual
			//~ cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << " diff %: " <<  diff_matrix[i][j]*100.0 << endl;
		}

		diff_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		diff_by_step->GetYaxis()->SetTitle("#bf{#Delta#Phi % =#Sigma_{j}(#Phi_{j}^{s+1}-#Phi_{j}^{s}) /#Sigma_{j}#Phi_{j}^{s}#times 100}");
		// diff_by_step->GetYaxis()->SetMaxDigits(1);
		diff_by_step->GetXaxis()->SetRangeUser(2,max_steps);
		diff_hist_vec.push_back(diff_by_step);
		//~ chi2_by_step->Draw("HIST");

}

// TCanvas *canvas_chi2_and_diff = new TCanvas("chi2_and_diff_by_step","chi2_and_diff_by_step",1920,1080);
//~ gStyle->SetStatX(0.95);      // X2NDC of the box (right edge)
//~ gStyle->SetStatY(0.95);      // Y2NDC of the box (top edge)
//~ gStyle->SetStatW(0.20);      // box width  (fraction of pad)
//~ gStyle->SetStatH(0.12);      // box height (fraction of pad)

// double diff_threshold = 0.02;
// double diff_threshold = 2.0; //porcentual, 2%
// TLine *l_new_diff=new TLine(xmin_diff,diff_threshold,xmax_diff,diff_threshold);
// TLine *l_new_diff_upper=new TLine(xmin_diff,diff_threshold+tolerance*diff_threshold,xmax_diff,diff_threshold+tolerance*diff_threshold);
// TLine *l_new_diff_lower=new TLine(xmin_diff,diff_threshold-tolerance*diff_threshold,xmax_diff,diff_threshold-tolerance*diff_threshold);


// l_new_diff->SetLineColor(kRed);
// l_new_diff_upper->SetLineColor(kRed);
// l_new_diff_lower->SetLineColor(kRed);
// l_new_diff->SetLineWidth(2.0);
// l_new_diff_upper->SetLineWidth(2.0);
// l_new_diff_lower->SetLineWidth(2.0);

//~ l_new->SetLineColorAlpha(kRed, opaque_value);
//~ l_new_diff->SetLineStyle(9);


auto DrawChi2AndDiffCanvas =
[&](const char* cname, const char* ctitle, bool logx)
{
    TCanvas *c = new TCanvas(cname, ctitle, 1920, 1080);
    c->Divide(2,1);

    // ---------- PAD 1: chi2 ----------
    c->cd(1);
	TPad *pad_chi2 = (TPad*)gPad;
	string scale_rep;
    if (logx){
		pad_chi2->SetLogx();
		scale_rep = "log";
	}
	else{scale_rep = "lin";}

    TH1D* chi2_copy = (TH1D*)chi2_hist_vec[0]->Clone(Form("%s_chi2_copy", cname));
    chi2_copy->SetTitle("#bf{#chi^{2} by EM iteration}");
    chi2_copy->GetXaxis()->SetRangeUser(2, max_steps);
    if(ndet==16){chi2_copy->GetYaxis()->SetRangeUser(0,400.0);}
	if(ndet==11){chi2_copy->GetYaxis()->SetRangeUser(0,35.0);}
    chi2_copy->Draw("HIST");

    // double xmin_chisq = chi2_copy->GetXaxis()->GetXmin();
    // double xmax_chisq = chi2_copy->GetXaxis()->GetXmax();

    // TLine *l_chisq = new TLine(xmin_chisq, ndet, xmax_chisq, ndet);
    // l_chisq->SetLineColor(kRed);
    // l_chisq->Draw("SAME");

    for(int j=1;j<501;j++){
        int colorIndex  = static_cast<int>(j*step);
        int colorIndex2 = 51 + colorIndex * 48 / 501;
        chi2_hist_vec[j]->SetLineColor(colorIndex2);
        chi2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
        chi2_hist_vec[j]->Draw("HIST SAME");
    }

	pad_chi2->Update(); // 

    double diff_threshold_chi2 = ndet; // %

	// Rango real del eje Y en "user coords"
	double uymin_chi2 = pad_chi2->GetUymin();
	double uymax_chi2 = pad_chi2->GetUymax();

	// Si el threshold está fuera del rango visible, no se verá
	if (diff_threshold_chi2 >= uymin_chi2 && diff_threshold_chi2 <= uymax_chi2) {

    // Convierte y(user) -> y(NDC), respetando márgenes
    double yfrac = (diff_threshold_chi2 - uymin_chi2) / (uymax_chi2 - uymin_chi2);
    double y_ndc = pad_chi2->GetBottomMargin()
                 + yfrac * (1.0 - pad_chi2->GetBottomMargin() - pad_chi2->GetTopMargin());

    double x1_ndc = pad_chi2->GetLeftMargin();
    double x2_ndc = 1.0 - pad_chi2->GetRightMargin();

    TLine *l_diff = new TLine(x1_ndc, y_ndc, x2_ndc, y_ndc);
    l_diff->SetNDC(true);
    l_diff->SetLineColor(kBlack);
    l_diff->SetLineWidth(2);
    l_diff->Draw();
	}


    // ---------- PAD 2: diff ----------
    c->cd(2);
    TPad *pad_diff = (TPad*)gPad;
    pad_diff->SetLeftMargin(0.126849);
    if (logx) pad_diff->SetLogx();

    diff_hist_vec[0]->SetTitle("#bf{#Delta#Phi % by EM iteration}");
    diff_hist_vec[0]->Draw("HIST");

    for(int j=1;j<501;j++){
        int colorIndex  = static_cast<int>(j*step);
        int colorIndex2 = 51 + colorIndex * 48 / 501;
        diff_hist_vec[j]->SetLineColor(colorIndex2);
        diff_hist_vec[j]->Draw("HIST SAME");
    }

	pad_diff->Update(); // 

    double diff_threshold = 2.0; // %

	// Rango real del eje Y en "user coords"
	double uymin = pad_diff->GetUymin();
	double uymax = pad_diff->GetUymax();

	// Si el threshold está fuera del rango visible, no se verá
	if (diff_threshold >= uymin && diff_threshold <= uymax) {

    // Convierte y(user) -> y(NDC), respetando márgenes
    double yfrac = (diff_threshold - uymin) / (uymax - uymin);
    double y_ndc = pad_diff->GetBottomMargin()
                 + yfrac * (1.0 - pad_diff->GetBottomMargin() - pad_diff->GetTopMargin());

    double x1_ndc = pad_diff->GetLeftMargin();
    double x2_ndc = 1.0 - pad_diff->GetRightMargin();

    TLine *l_diff = new TLine(x1_ndc, y_ndc, x2_ndc, y_ndc);
    l_diff->SetNDC(true);
    l_diff->SetLineColor(kBlack);
    l_diff->SetLineWidth(2);
    l_diff->Draw();
	}

	c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_and_diff_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_rep+"_"+scale_factor+".pdf").c_str());
	c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Chi_squared_and_diff_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_rep+"_"+scale_factor+".svg").c_str());


    c->Update();
};

DrawChi2AndDiffCanvas("chi2_diff_lin",  "chi2_and_diff_by_step (X linear)", false);
DrawChi2AndDiffCanvas("chi2_diff_logx", "chi2_and_diff_by_step (X log)",    true);



/********************************************************/
/*** Canvas resumen: chi2 + dd2 + diff  (knee marked)  ***/
/********************************************************/

auto DrawSummaryKneeCanvas =
[&](const char* cname, const char* ctitle, bool logx)
{
    TCanvas* c = new TCanvas(cname, ctitle, 1920, 1200);
    c->Divide(1,3);

    // ---------- helper: estilo colores consistente ----------
    auto set_color = [&](TH1D* h, size_t j, size_t ncurves){
        // esquema similar al tuyo
        double stepC = (double)nColors / (double)ncurves;
        int colorIndex  = (int)(j * stepC);
        int colorIndex2 = 51 + colorIndex * 48 / 501; // fijo a tu paleta 501
        h->SetLineColor(colorIndex2);
    };

    // =========================================================
    // PAD 1: CHI2
    // =========================================================
    c->cd(1);
    TPad* p1 = (TPad*)gPad;
    p1->SetLeftMargin(0.10);
    p1->SetRightMargin(0.03);
    p1->SetTopMargin(0.06);
    p1->SetBottomMargin(0.10);
    if (logx) p1->SetLogx();

    TH1D* hchi0 = (TH1D*)chi2_hist_vec[0]->Clone(Form("%s_chi2_0", cname));
    hchi0->SetTitle("#bf{#chi^{2} vs EM iteration}");
    hchi0->GetXaxis()->SetRangeUser(2, max_steps);
    hchi0->GetXaxis()->SetLabelSize(0.04);
    hchi0->GetYaxis()->SetLabelSize(0.04);
    hchi0->SetStats(0);
    if(ndet==16) hchi0->GetYaxis()->SetRangeUser(0, 400.0);
    if(ndet==11) hchi0->GetYaxis()->SetRangeUser(0, 35.0);
    hchi0->Draw("HIST");

    for (size_t j=1; j<chi2_hist_vec.size(); ++j){
        TH1D* h = chi2_hist_vec[j];
        h->GetXaxis()->SetRangeUser(2, max_steps);
        set_color(h, j, chi2_hist_vec.size());
        h->Draw("HIST SAME");
    }

    p1->Update();
    if (knee_step_global > 0) {
        double y1 = p1->GetUymin();
        double y2 = p1->GetUymax();
        TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
        lk->SetLineColor(kBlack);
        lk->SetLineStyle(2);
        lk->SetLineWidth(3);
        lk->Draw("SAME");

        TLatex* t = new TLatex(0.12, 0.88,
            Form("#bf{knee: step=%.0f, #chi^{2}(knee)~%.3g}", knee_step_global, knee_chi2_global));
        t->SetNDC();
        t->SetTextSize(0.05);
        t->Draw("SAME");
    }

    // =========================================================
    // PAD 2: 2nd derivative
    // =========================================================
    c->cd(2);
    TPad* p2 = (TPad*)gPad;
    p2->SetLeftMargin(0.10);
    p2->SetRightMargin(0.03);
    p2->SetTopMargin(0.03);
    p2->SetBottomMargin(0.10);
    if (logx) p2->SetLogx();

    TH1D* hdd0 = (TH1D*)chi2_dd2_hist_vec[0]->Clone(Form("%s_dd2_0", cname));
    hdd0->SetTitle("#bf{d^{2}#chi^{2}/ds^{2} vs EM iteration}");
    hdd0->GetXaxis()->SetRangeUser(2, max_steps);
    hdd0->GetXaxis()->SetLabelSize(0.04);
    hdd0->GetYaxis()->SetLabelSize(0.04);
    hdd0->SetStats(0);
    hdd0->Draw("HIST");

    // línea horizontal en 0
    double xmin0 = hdd0->GetXaxis()->GetXmin();
    double xmax0 = hdd0->GetXaxis()->GetXmax();
    TLine* l0 = new TLine(xmin0, 0.0, xmax0, 0.0);
    l0->SetLineColor(kBlack);
    l0->SetLineWidth(2);
    l0->Draw("SAME");

    for (size_t j=1; j<chi2_dd2_hist_vec.size(); ++j){
        TH1D* h = chi2_dd2_hist_vec[j];
        h->GetXaxis()->SetRangeUser(2, max_steps);
        set_color(h, j, chi2_dd2_hist_vec.size());
        h->Draw("HIST SAME");
    }

    p2->Update();
    if (knee_step_global > 0) {
        double y1 = p2->GetUymin();
        double y2 = p2->GetUymax();
        TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
        lk->SetLineColor(kBlack);
        lk->SetLineStyle(2);
        lk->SetLineWidth(3);
        lk->Draw("SAME");
    }

    // =========================================================
    // PAD 3: DIFF (%)
    // =========================================================
    c->cd(3);
    TPad* p3 = (TPad*)gPad;
    p3->SetLeftMargin(0.10);
    p3->SetRightMargin(0.03);
    p3->SetTopMargin(0.03);
    p3->SetBottomMargin(0.12);
    if (logx) p3->SetLogx();

    TH1D* hdf0 = (TH1D*)diff_hist_vec[0]->Clone(Form("%s_diff_0", cname));
    hdf0->SetTitle("#bf{#Delta#Phi (%) vs EM iteration}");
    hdf0->GetXaxis()->SetRangeUser(2, max_steps);
    hdf0->GetXaxis()->SetLabelSize(0.04);
    hdf0->GetYaxis()->SetLabelSize(0.04);
    hdf0->SetStats(0);
    hdf0->Draw("HIST");

    for (size_t j=1; j<diff_hist_vec.size(); ++j){
        TH1D* h = diff_hist_vec[j];
        h->GetXaxis()->SetRangeUser(2, max_steps);
        set_color(h, j, diff_hist_vec.size());
        h->Draw("HIST SAME");
    }

    // línea horizontal 2%
    double diff_threshold = 2.0;
    double xminD = hdf0->GetXaxis()->GetXmin();
    double xmaxD = hdf0->GetXaxis()->GetXmax();
    TLine* ld = new TLine(xminD, diff_threshold, xmaxD, diff_threshold);
    ld->SetLineColor(kBlack);
    ld->SetLineStyle(3);
    ld->SetLineWidth(3);
    ld->Draw("SAME");

    p3->Update();
    if (knee_step_global > 0) {
        double y1 = p3->GetUymin();
        double y2 = p3->GetUymax();
        TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
        lk->SetLineColor(kBlack);
        lk->SetLineStyle(2);
        lk->SetLineWidth(3);
        lk->Draw("SAME");
    }

    c->Update();

    string scale_rep = logx ? "log" : "lin";
    c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
               "/Summary_knee_"+campaign+"_Campaign_event_"+str_stream_event+
               "_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+
               "_"+scale_rep+"_"+scale_factor+".pdf").c_str());
    c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
               "/Summary_knee_"+campaign+"_Campaign_event_"+str_stream_event+
               "_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+
               "_"+scale_rep+"_"+scale_factor+".svg").c_str());
};

// llamadas (lineal y logx)
DrawSummaryKneeCanvas("c_summary_knee_lin",  "Summary: chi2 + dd2 + diff (lin x)", false);
DrawSummaryKneeCanvas("c_summary_knee_log",  "Summary: chi2 + dd2 + diff (log x)", true);

/*************************************************************************************************/
/*************************************************************************************************/
/*************************************************************************************************/

//~ TCanvas *canvas_intg_total = new TCanvas("intg_total_by_step","intg_total_by_step",1920,1080);

//~ canvas_intg_total ->Divide(2,3);

string hist_name_intg_total;
string hist_name_intg_th;
string hist_name_intg_ep;
string hist_name_intg_fs;
string hist_name_intg_he;

vector<TH1D*> intg_total_hist_vec;
vector<TH1D*> intg_th_hist_vec;
vector<TH1D*> intg_ep_hist_vec;
vector<TH1D*> intg_fs_hist_vec;
vector<TH1D*> intg_he_hist_vec;

double title_size = 0.08;
double x_title_size = 0.05;
double title_offset = 0.5;
double x_title_offset = 0.7;
int y_axis_max_dig = 2;



string str_stream_seed;

for(int j=0;j<501;j++){
			//~ double x_bin_lowedges = i/5.;
			double x_seed = j/5.;
			//~ x_vec_seed.push_back(x_bin_lowedges);
		ostringstream stream_seed;
		stream_seed << x_seed;
		str_stream_seed = stream_seed.str();
		
		hist_name_intg_total = "Intg_total_by_step_seed_"+str_stream_seed;
		hist_name_intg_th = "Intg_th_by_step_seed_"+str_stream_seed;
		hist_name_intg_ep = "Intg_ep_by_step_seed_"+str_stream_seed;
		hist_name_intg_fs = "Intg_fs_by_step_seed_"+str_stream_seed;
		hist_name_intg_he = "Intg_he_by_step_seed_"+str_stream_seed;

		TH1D* intg_total_by_step = new TH1D(hist_name_intg_total.c_str(),hist_name_intg_total.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_th_by_step = new TH1D(hist_name_intg_th.c_str(),hist_name_intg_th.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_ep_by_step = new TH1D(hist_name_intg_ep.c_str(),hist_name_intg_ep.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_fs_by_step = new TH1D(hist_name_intg_fs.c_str(),hist_name_intg_fs.c_str(), binnum_steps , x_steps_edgeds);
		TH1D* intg_he_by_step = new TH1D(hist_name_intg_he.c_str(),hist_name_intg_he.c_str(), binnum_steps , x_steps_edgeds);
		
		for(int i=0;i<max_steps;i++){
			intg_total_by_step->SetBinContent(i+1,(intg_total_matrix[i][j]));
			intg_th_by_step->SetBinContent(i+1,(intg_th_matrix[i][j]));
			intg_ep_by_step->SetBinContent(i+1,(intg_ep_matrix[i][j]));
			intg_fs_by_step->SetBinContent(i+1,(intg_fs_matrix[i][j]));
			intg_he_by_step->SetBinContent(i+1,(intg_he_matrix[i][j]));


			//~ cout << "step: " << em_it_matrix[i][j] << " chi2: " << chi2_matrix[i][j] << " diff: " <<  diff_matrix[i][j] << " Intg total: " << intg_total_matrix[i][j] << endl;
		}


		intg_total_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_total_by_step->GetYaxis()->SetTitle("#bf{#Phi_{total}}");
		intg_total_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_total_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_total_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_total_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_total_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_total_hist_vec.push_back(intg_total_by_step);
		
		intg_th_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_th_by_step->GetYaxis()->SetTitle("#bf{#Phi_{th}}");
		intg_th_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_th_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_th_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_th_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_th_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_th_hist_vec.push_back(intg_th_by_step);

		intg_ep_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_ep_by_step->GetYaxis()->SetTitle("#bf{#Phi_{ep}}");
		intg_ep_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_ep_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_ep_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_ep_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_ep_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_ep_hist_vec.push_back(intg_ep_by_step);
		
		intg_fs_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_fs_by_step->GetYaxis()->SetTitle("#bf{#Phi_{fs}}");
		intg_fs_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_fs_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_fs_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_fs_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_fs_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_fs_hist_vec.push_back(intg_fs_by_step);

		intg_he_by_step->GetXaxis()->SetTitle("#bf{EM iteration}");
		intg_he_by_step->GetYaxis()->SetTitle("#bf{#Phi_{he}}");
		intg_he_by_step->GetXaxis()->SetTitleSize(x_title_size);
		intg_he_by_step->GetXaxis()->SetTitleOffset(x_title_offset);
		intg_he_by_step->GetYaxis()->SetTitleSize(title_size);
		intg_he_by_step->GetYaxis()->SetTitleOffset(title_offset);
		intg_he_by_step->GetYaxis()->SetMaxDigits(y_axis_max_dig);
		intg_he_hist_vec.push_back(intg_he_by_step);


}


/**Linear and Log x-axis scale for integral flux values per integral region**/
	auto DrawIntgCanvas = [&](const char* cname,
                              const char* ctitle,
                              bool logx,
                              const vector<TH1D*>& intg_total_hist_vec,
                              const vector<TH1D*>& intg_th_hist_vec,
                              const vector<TH1D*>& intg_ep_hist_vec,
                              const vector<TH1D*>& intg_fs_hist_vec,
                              const vector<TH1D*>& intg_he_hist_vec)
    {
        TCanvas *c = new TCanvas(cname, ctitle, 1920, 1080);
        c->Divide(2,3);

		string scale_rep;
        // === lambda interna para evitar repetir código ===
        auto draw_vec = [&](int pad,
                            const vector<TH1D*>& vec_hist)
        {
            c->cd(pad);
            //~ if (logx) gPad->SetLogx();

            
			if (logx){
				gPad->SetLogx();
				scale_rep = "log";
			}
			else{scale_rep = "lin";}

			double sc_factor;
			if(scale_factor=="ws"){sc_factor=1.0;}
			if(scale_factor=="wos"){sc_factor=0.25;}

            if(pad==2){//thermal region
				//~ vec_hist[0]->GetYaxis()->SetRangeUser(3e-03,10e-03);
				//~ double up_lim = 10.*sc_factor;
				vec_hist[0]->GetYaxis()->SetRangeUser(3.0*sc_factor*pow(10.0,-3), 10.0*sc_factor*pow(10.0,-3));
			};
            if(pad==3){//epithermal region
				if(ndet==11){
				vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),19.0*sc_factor*pow(10.0,-3)); // ndet 11
				}
				if(ndet==16){
				vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),22.0*sc_factor*pow(10.0,-3)); //ndet 16
				}
			};
            if(pad==4){//fast region
				if(ndet==11){
				vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),26.0*sc_factor*pow(10.0,-3)); //ndet 11
				}
				if(ndet==16){
				vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),26.0*sc_factor*pow(10.0,-3)); // ndet 16
				}
			};
            if(pad==5){//high region
				if(ndet==11){
				vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),51.0*sc_factor*pow(10.0,-3)); //ndet 11
				}
				if(ndet==16){
				vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),51.*sc_factor*pow(10.0,-3)); // ndet 16
				}
			};

            vec_hist[0]->Draw("HIST");

            //~ int nColors = 51 + 48;
            int nColors = 501;
            double step = double(nColors) / double(vec_hist.size());

            for (size_t j = 1; j < vec_hist.size(); ++j) {
                int colorIndex = int(j * step);
                int colorIndex2 = 51 + colorIndex * 48 / vec_hist.size();
                vec_hist[j]->SetLineColor(colorIndex2);
                vec_hist[j]->Draw("HIST SAME");
            }
        };

        // Dibujar cada familia
        draw_vec(1, intg_total_hist_vec);
        draw_vec(2, intg_th_hist_vec);
        draw_vec(3, intg_ep_hist_vec);
        draw_vec(4, intg_fs_hist_vec);
        draw_vec(5, intg_he_hist_vec);

        c->Update();

        c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Integral_flux_values_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_rep+"_"+scale_factor+".pdf").c_str());
		c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+"/Integral_flux_values_"+campaign+"_Campaign_"+"event_"+str_stream_event+"_timegrid_"+std::to_string(timegrid)+"_ndet_"+std::to_string(ndet)+"_"+scale_rep+"_"+scale_factor+".svg").c_str());

    };

    // === llamadas ===
    DrawIntgCanvas("c_lin",  "Flux vs step (linear X)", false,
                   intg_total_hist_vec, intg_th_hist_vec,
                   intg_ep_hist_vec, intg_fs_hist_vec, intg_he_hist_vec);

    DrawIntgCanvas("c_log",  "Flux vs step (log X)", true,
                   intg_total_hist_vec, intg_th_hist_vec,
                   intg_ep_hist_vec, intg_fs_hist_vec, intg_he_hist_vec);


}


// ------------------------------------------------------------
//  Helper: mediana robusta (MISMA idea que usaste)
// ------------------------------------------------------------
static double median_of(std::vector<double> v){
    v.erase(std::remove_if(v.begin(), v.end(),
                           [](double x){ return x < 0; }),
            v.end());
    if(v.empty()) return -1.0;
    std::sort(v.begin(), v.end());
    size_t mid = v.size()/2;
    if(v.size()%2) return v[mid];
    return 0.5*(v[mid-1] + v[mid]);
}

void em_knee_and_chi2stop_from_singlefile_update(
    std::string campaign,
    int event,
    int timegrid,
    int max_steps,
    int ndet,
    std::string physic_list,
    std::string scale_factor // "ws" o "wos" (lo uso para paths/sufijos como tú)
){
    // -------------------------
    // Strings (igual estilo tuyo)
    // -------------------------
    std::ostringstream stream_event, stream_timegrid, stream_ndet;
    stream_event << event;
    stream_timegrid << timegrid;
    stream_ndet << ndet;

    std::string str_stream_event    = stream_event.str();
    std::string str_stream_timegrid = stream_timegrid.str();
    std::string str_stream_ndet     = stream_ndet.str();

    std::string campaign_path;
    if(physic_list=="QGSP_BERT"){
        campaign_path = campaign;
    }else if(physic_list=="FTFP_BERT"){
        campaign_path = campaign+"_FTFP_BERT";
    }else{
        std::cout << "Physics list inexistente o incorrecta\n";
        return;
    }

    // -------------------------
    // Input ROOT único (21 seeds)
    // AJUSTA ESTE PATH a tu naming real si difiere
    // -------------------------
    std::string input_single_file =
        "../outputs/root/deconv_data_rootfile/EM_single/"+campaign_path+
        "/EM_single_campaign_"+campaign+
        "_event_"+str_stream_event+
        "_timegrid_"+str_stream_timegrid+
        "_ndet_"+std::to_string(ndet)+
        "_maxsteps_"+std::to_string(max_steps)+
        ".root";

    TFile* fin = TFile::Open(input_single_file.c_str(), "READ");
    if(!fin || fin->IsZombie()){
        std::cout << "ERROR: no pude abrir: " << input_single_file << "\n";
        return;
    }

    // Tree
    TTree* t = (TTree*)fin->Get("em_event_tree");
    if(!t){
        std::cout << "ERROR: no existe TTree em_event_tree en " << input_single_file << "\n";
        fin->Close();
        return;
    }

    // -------------------------
    // Branches
    // -------------------------
    Int_t step=0, seed_idx=0;
    Double_t Chi2=0.0, diff_criteria=0.0;

    t->SetBranchAddress("step", &step);
    t->SetBranchAddress("seed_idx", &seed_idx);
    t->SetBranchAddress("Chi2", &Chi2);

    // diff_criteria puede no existir; si existe lo tomamos
    bool has_diff = (t->GetBranch("diff_criteria") != nullptr);
    if(has_diff){
        t->SetBranchAddress("diff_criteria", &diff_criteria);
    }

    // -------------------------
    // Determinar nSeeds a partir del tree (máximo seed_idx)
    // -------------------------
    int max_seed = 0;
    Long64_t nentries = t->GetEntries();
    for(Long64_t i=0;i<nentries;i++){
        t->GetEntry(i);
        if(seed_idx > max_seed) max_seed = seed_idx;
    }
    int nSeeds = max_seed + 1;

    std::cout << "Input: " << input_single_file << "\n";
    std::cout << "Entries=" << nentries << "  nSeeds="<<nSeeds<<"  max_steps="<<max_steps<<"\n";

    // -------------------------
    // Matrices (step x seed) como en tu viejo código
    // -------------------------
    std::vector<std::vector<double>> chi2_matrix(max_steps, std::vector<double>(nSeeds, 0.0));
    std::vector<std::vector<double>> diff_matrix; // opcional
    if(has_diff){
        diff_matrix.assign(max_steps, std::vector<double>(nSeeds, 0.0));
    }

    // Llenar matrices
    for(Long64_t i=0;i<nentries;i++){
        t->GetEntry(i);
        if(step>=1 && step<=max_steps && seed_idx>=0 && seed_idx<nSeeds){
            chi2_matrix[step-1][seed_idx] = Chi2;
            if(has_diff) diff_matrix[step-1][seed_idx] = diff_criteria;
        }
    }

    // -------------------------
    // Paleta (tu misma idea, pero ajustando a nSeeds)
    // -------------------------
    int nColors = nSeeds;
    std::vector<double> stops(nColors), red(nColors), green(nColors), blue(nColors);

    for (int i = 0; i < nColors; i++) {
        stops[i] = (double)i / (nColors - 1);
        red[i]   = TMath::Max(0.0, TMath::Min(1.0, 2.0 * stops[i] - 0.5));
        green[i] = TMath::Sqrt(stops[i]);
        blue[i]  = 1.0 - stops[i];
    }
    TColor::CreateGradientColorTable(nColors, stops.data(), red.data(), green.data(), blue.data(), nColors-1);
    TColor::InvertPalette();

    // -------------------------
    // Construir histos Chi2 por seed (igual a tu loop j)
    // -------------------------
    std::vector<double> x_vec_steps;
    x_vec_steps.reserve(max_steps);
    for(int i=1;i<=max_steps;i++) x_vec_steps.push_back(i);
    double* x_steps_edges = x_vec_steps.data();
    const int binnum_steps = (int)x_vec_steps.size()-1;

    std::vector<TH1D*> chi2_hist_vec;
    chi2_hist_vec.reserve(nSeeds);

    for(int j=0;j<nSeeds;j++){
        double x_seed = (double)j/5.0; // tú lo usas así (0–100% en pasos 0.2 => 501)
        std::ostringstream ss; ss << x_seed;
        std::string hname = "Chi2_by_step_seed_"+ss.str();

        TH1D* h = new TH1D(hname.c_str(), hname.c_str(), binnum_steps, x_steps_edges);

        for(int i=0;i<max_steps;i++){
            h->SetBinContent(i+1, chi2_matrix[i][j]);
        }

        h->GetXaxis()->SetTitle("#bf{EM iteration}");
        h->GetYaxis()->SetTitle("#bf{#chi^{2}}");
        h->SetTitle("");
        h->GetYaxis()->SetTitleOffset(0.95);
        h->GetYaxis()->SetTitleSize(0.05);

        chi2_hist_vec.push_back(h);
    }

    // -------------------------
    // Canvas CHI2 (idéntico estilo general)
    // -------------------------
    gStyle->SetOptStat(0);

    TCanvas *canvas_chi2 = new TCanvas("chi2_by_step","chi2_by_step",960,1080);
    canvas_chi2->Divide(1,1);
    TPad *p_cr = (TPad*)canvas_chi2->cd(1);

    p_cr->SetRightMargin(0.027);
    p_cr->SetLeftMargin(0.100156);
    p_cr->SetTopMargin(0.025);
    p_cr->SetBottomMargin(0.0677269);

    chi2_hist_vec[0]->Draw("HIST");
    if(ndet==16) chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,400.0);
    if(ndet==11) chi2_hist_vec[0]->GetYaxis()->SetRangeUser(0,35.0);
    chi2_hist_vec[0]->SetStats(0);

    double stepC = (double)nColors / (double)chi2_hist_vec.size();

    for(int j=1;j<nSeeds;j++){
        int colorIndex  = (int)(j*stepC);
        int colorIndex2 = 51 + colorIndex * 48 / nSeeds; // mismo mapping que usabas (solo reescalado)
        chi2_hist_vec[j]->SetLineColor(colorIndex2);
        chi2_hist_vec[j]->Draw("HIST SAME");
    }

    // línea ndet
    double xmin = chi2_hist_vec[0]->GetXaxis()->GetXmin();
    double xmax = chi2_hist_vec[0]->GetXaxis()->GetXmax();
    TLine *l_new = new TLine(xmin, ndet, xmax, ndet);
    l_new->SetLineColor(kRed);
    l_new->SetLineWidth(2.0);
    l_new->Draw("SAME");

    // Guardar (mismo naming tuyo)
    canvas_chi2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
                         "/Chi_squared_"+campaign+"_Campaign_event_"+str_stream_event+
                         "_timegrid_"+std::to_string(timegrid)+
                         "_ndet_"+std::to_string(ndet)+
                         "_"+scale_factor+"_NEW.pdf").c_str());

    // -------------------------
    // 2nd derivative (MISMA IMPLEMENTACION tuya)
    // -------------------------
    std::vector<TH1D*> chi2_dd2_hist_vec;
    chi2_dd2_hist_vec.reserve(chi2_hist_vec.size());

    const int nbins = chi2_hist_vec[0]->GetNbinsX();

    for(size_t j=0;j<chi2_hist_vec.size();++j){
        TH1D* h = chi2_hist_vec[j];

        TH1D* hdd2 = (TH1D*)h->Clone(Form("%s_dd2", h->GetName()));
        hdd2->Reset("ICES");
        hdd2->SetTitle("");
        hdd2->GetXaxis()->SetTitle("#bf{EM iteration}");
        hdd2->GetYaxis()->SetTitle("#bf{d^{2}#chi^{2}/ds^{2}}");
        hdd2->GetYaxis()->SetTitleOffset(0.95);
        hdd2->GetYaxis()->SetTitleSize(0.05);

        hdd2->SetBinContent(1, 0.0);
        hdd2->SetBinContent(nbins, 0.0);

        for(int i=2;i<=nbins-1;++i){
            double y_prev = h->GetBinContent(i-1);
            double y      = h->GetBinContent(i);
            double y_next = h->GetBinContent(i+1);
            double dd2 = (y_next - 2.0*y + y_prev);
            hdd2->SetBinContent(i, dd2);
        }

        chi2_dd2_hist_vec.push_back(hdd2);
    }

    // Canvas dd2 (como el tuyo)
    TCanvas* c_dd2 = new TCanvas("chi2_dd2_by_step", "chi2_dd2_by_step", 1920, 1080);
    c_dd2->cd();
    TPad* p_dd2 = (TPad*)gPad;
    p_dd2->SetLeftMargin(0.10);
    p_dd2->SetRightMargin(0.03);
    p_dd2->SetTopMargin(0.03);
    p_dd2->SetBottomMargin(0.07);

    chi2_dd2_hist_vec[0]->GetXaxis()->SetRangeUser(2, max_steps);
    chi2_dd2_hist_vec[0]->Draw("HIST");

    // línea 0
    double xmin0 = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmin();
    double xmax0 = chi2_dd2_hist_vec[0]->GetXaxis()->GetXmax();
    TLine* l0 = new TLine(xmin0, 0.0, xmax0, 0.0);
    l0->SetLineColor(kBlack);
    l0->SetLineWidth(2);
    l0->Draw("SAME");

    for(size_t j=1;j<chi2_dd2_hist_vec.size();++j){
        int colorIndex  = (int)(j*stepC);
        int colorIndex2 = 51 + colorIndex * 48 / nSeeds;
        chi2_dd2_hist_vec[j]->SetLineColor(colorIndex2);
        chi2_dd2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
        chi2_dd2_hist_vec[j]->Draw("HIST SAME");
    }

    // -------------------------
    // KNEE (MISMA IMPLEMENTACION tuya)
    // -------------------------
    const int    START_BIN   = 12;
    const int    K_CONSEC    = 12;
    const double EPS_FRAC    = 0.03;
    const double STRONG_MULT = 5.0;

    std::vector<double> knee_step_per_seed(chi2_hist_vec.size(), -1.0);
    std::vector<double> knee_chi2_per_seed(chi2_hist_vec.size(), -1.0);

    for(size_t j=0;j<chi2_hist_vec.size();++j){
        TH1D* hchi = chi2_hist_vec[j];
        TH1D* hdd2 = chi2_dd2_hist_vec[j];

        double maxAbs = 0.0;
        for(int i=START_BIN;i<=nbins;++i){
            maxAbs = std::max(maxAbs, std::abs(hdd2->GetBinContent(i)));
        }
        if(maxAbs <= 0) continue;

        const double eps    = EPS_FRAC * maxAbs;
        const double strong = STRONG_MULT * eps;

        bool strongSeen = false;
        int consec = 0;
        int knee_bin = -1;

        for(int i=START_BIN;i<=nbins;++i){
            double v = std::abs(hdd2->GetBinContent(i));
            if(v > strong) strongSeen = true;

            if(strongSeen && v < eps){
                consec++;
                if(consec >= K_CONSEC){
                    knee_bin = i - K_CONSEC + 1;
                    break;
                }
            }else{
                consec = 0;
            }
        }

        if(knee_bin < 0) continue;

        knee_step_per_seed[j] = hdd2->GetBinCenter(knee_bin);
        knee_chi2_per_seed[j] = hchi->GetBinContent(knee_bin);
    }

    double knee_step_global = median_of(knee_step_per_seed);
    double knee_chi2_global = median_of(knee_chi2_per_seed);

    std::cout << "=== KNEE (global median, same algo) ===\n"
              << "knee_step ~ " << knee_step_global
              << "   chi2_stop(median) ~ " << knee_chi2_global << "\n";

    // marcar rodilla global en dd2
    p_dd2->Update();
    if(knee_step_global > 0){
        double y1 = p_dd2->GetUymin();
        double y2 = p_dd2->GetUymax();
        TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
        lk->SetLineColor(kBlack);
        lk->SetLineStyle(2);
        lk->SetLineWidth(3);
        lk->Draw("SAME");

        TLatex* txt = new TLatex(0.15, 0.92,
            Form("#bf{knee: step=%.0f, #chi^{2}~%.3g}", knee_step_global, knee_chi2_global));
        txt->SetNDC();
        txt->SetTextSize(0.04);
        txt->Draw("SAME");
    }
    c_dd2->Update();

    c_dd2->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
                   "/Chi_squared_dd2_"+campaign+"_Campaign_event_"+str_stream_event+
                   "_timegrid_"+std::to_string(timegrid)+
                   "_ndet_"+std::to_string(ndet)+
                   "_"+scale_factor+"_NEW.pdf").c_str());

    // -------------------------
    // Knee-step distribution (MISMA lógica IQR tuya)
    // -------------------------
    std::vector<double> knees;
    knees.reserve(knee_step_per_seed.size());
    for(double ks : knee_step_per_seed){
        if(ks > 0) knees.push_back(ks);
    }

    if(!knees.empty()){
        auto quantile = [&](std::vector<double> v, double q)->double{
            if(v.empty()) return -1.0;
            std::sort(v.begin(), v.end());
            double pos = q * (v.size() - 1);
            size_t i = (size_t)std::floor(pos);
            size_t j = (size_t)std::ceil(pos);
            if(i==j) return v[i];
            double t = pos - i;
            return v[i]*(1.0-t) + v[j]*t;
        };

        double q1  = quantile(knees, 0.25);
        double med = quantile(knees, 0.50);
        double q3  = quantile(knees, 0.75);

        TH1D* h_knee = new TH1D("h_knee_step",
            "Knee-step distribution;EM iteration (knee);Counts",
            max_steps, 0.5, max_steps + 0.5);

        for(double ks : knees) h_knee->Fill(ks);

        TH1D* h_knee_chi2 = new TH1D("h_knee_chi2",
            "Chi2 at knee;#chi^{2}(knee);Counts",
            120, 0.0, (ndet==16 ? 400.0 : 35.0));

        for(size_t j=0;j<knee_chi2_per_seed.size();++j){
            if(knee_step_per_seed[j] > 0 && knee_chi2_per_seed[j] > 0)
                h_knee_chi2->Fill(knee_chi2_per_seed[j]);
        }

        TCanvas* c_knee_dist = new TCanvas("c_knee_dist", "knee distributions", 1920, 900);
        c_knee_dist->Divide(2,1);

        c_knee_dist->cd(1);
        TPad* p1 = (TPad*)gPad;
        p1->SetLeftMargin(0.10);
        p1->SetRightMargin(0.03);
        p1->SetBottomMargin(0.10);

        h_knee->SetStats(0);
        h_knee->Draw("HIST");
        p1->Update();

        double y_min = p1->GetUymin();
        double y_max = p1->GetUymax();

        TBox* box_iqr = new TBox(q1, y_min, q3, y_max);
        box_iqr->SetFillColorAlpha(kAzure-9, 0.35);
        box_iqr->SetLineColor(kAzure-9);
        box_iqr->SetLineWidth(2);
        box_iqr->Draw("SAME");

        TLine* l_q1  = new TLine(q1,  y_min, q1,  y_max);
        TLine* l_q3  = new TLine(q3,  y_min, q3,  y_max);
        TLine* l_med = new TLine(med, y_min, med, y_max);

        l_q1->SetLineColor(kBlue+2);
        l_q3->SetLineColor(kBlue+2);
        l_med->SetLineColor(kBlack);

        l_q1->SetLineStyle(3);
        l_q3->SetLineStyle(3);
        l_med->SetLineStyle(2);

        l_q1->SetLineWidth(3);
        l_q3->SetLineWidth(3);
        l_med->SetLineWidth(4);

        l_q1->Draw("SAME");
        l_q3->Draw("SAME");
        l_med->Draw("SAME");

        TLatex* t_iqr = new TLatex(
            0.12, 0.92,
            Form("#bf{Median = %.0f   IQR = [%.0f , %.0f]  (#Delta = %.0f)}",
                 med, q1, q3, q3-q1)
        );
        t_iqr->SetNDC();
        t_iqr->SetTextSize(0.04);
        t_iqr->Draw("SAME");

        c_knee_dist->cd(2);
        TPad* p2 = (TPad*)gPad;
        p2->SetLeftMargin(0.10);
        p2->SetRightMargin(0.03);
        p2->SetBottomMargin(0.10);

        h_knee_chi2->SetStats(0);
        h_knee_chi2->Draw("HIST");

        c_knee_dist->Update();

        c_knee_dist->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
                             "/Knee_distributions_"+campaign+"_Campaign_event_"+str_stream_event+
                             "_timegrid_"+std::to_string(timegrid)+
                             "_ndet_"+std::to_string(ndet)+
                             "_"+scale_factor+"_NEW.pdf").c_str());
    }

    // -------------------------
    // (Opcional, pero recomendado) Canvas resumen chi2 + dd2 + diff (marcando knee)
    // Solo si diff_criteria existe
    // -------------------------
    if(has_diff){
        // construir diff_hist_vec igual que tu implementación (por seed)
        std::vector<TH1D*> diff_hist_vec;
        diff_hist_vec.reserve(nSeeds);

        for(int j=0;j<nSeeds;j++){
            double x_seed = (double)j/5.0;
            std::ostringstream ss; ss << x_seed;
            std::string hname = "Diff_by_step_seed_"+ss.str();
            TH1D* h = new TH1D(hname.c_str(), hname.c_str(), binnum_steps, x_steps_edges);

            for(int i=0;i<max_steps;i++){
                h->SetBinContent(i+1, 100.0*diff_matrix[i][j]);
            }

            h->GetXaxis()->SetTitle("#bf{EM iteration}");
            h->GetYaxis()->SetTitle("#bf{#Delta#Phi %}");
            h->GetXaxis()->SetRangeUser(2, max_steps);

            diff_hist_vec.push_back(h);
        }

        auto DrawSummaryKneeCanvas =
        [&](const char* cname, const char* ctitle, bool logx){
            TCanvas* c = new TCanvas(cname, ctitle, 1920, 1200);
            c->Divide(1,3);

            auto set_color = [&](TH1D* h, size_t j){
                int colorIndex  = (int)(j * stepC);
                int colorIndex2 = 51 + colorIndex * 48 / nSeeds;
                h->SetLineColor(colorIndex2);
            };

            // PAD1 chi2
            c->cd(1);
            TPad* p1 = (TPad*)gPad;
            p1->SetLeftMargin(0.10);
            p1->SetRightMargin(0.03);
            p1->SetTopMargin(0.06);
            p1->SetBottomMargin(0.10);
            if(logx) p1->SetLogx();

            TH1D* hchi0 = (TH1D*)chi2_hist_vec[0]->Clone(Form("%s_chi2_0", cname));
            hchi0->SetTitle("#bf{#chi^{2} vs EM iteration}");
            hchi0->GetXaxis()->SetRangeUser(2, max_steps);
            hchi0->SetStats(0);
            if(ndet==16) hchi0->GetYaxis()->SetRangeUser(0, 400.0);
            if(ndet==11) hchi0->GetYaxis()->SetRangeUser(0, 35.0);
            hchi0->Draw("HIST");

            for(size_t j=1;j<chi2_hist_vec.size();++j){
                chi2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
                set_color(chi2_hist_vec[j], j);
                chi2_hist_vec[j]->Draw("HIST SAME");
            }

            p1->Update();
            if(knee_step_global > 0){
                double y1 = p1->GetUymin();
                double y2 = p1->GetUymax();
                TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
                lk->SetLineColor(kBlack);
                lk->SetLineStyle(2);
                lk->SetLineWidth(3);
                lk->Draw("SAME");
            }

            // PAD2 dd2
            c->cd(2);
            TPad* p2 = (TPad*)gPad;
            p2->SetLeftMargin(0.10);
            p2->SetRightMargin(0.03);
            p2->SetTopMargin(0.03);
            p2->SetBottomMargin(0.10);
            if(logx) p2->SetLogx();

            TH1D* hdd0 = (TH1D*)chi2_dd2_hist_vec[0]->Clone(Form("%s_dd2_0", cname));
            hdd0->SetTitle("#bf{d^{2}#chi^{2}/ds^{2} vs EM iteration}");
            hdd0->GetXaxis()->SetRangeUser(2, max_steps);
            hdd0->SetStats(0);
            hdd0->Draw("HIST");

            TLine* l00 = new TLine(xmin0, 0.0, xmax0, 0.0);
            l00->SetLineColor(kBlack);
            l00->SetLineWidth(2);
            l00->Draw("SAME");

            for(size_t j=1;j<chi2_dd2_hist_vec.size();++j){
                chi2_dd2_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
                set_color(chi2_dd2_hist_vec[j], j);
                chi2_dd2_hist_vec[j]->Draw("HIST SAME");
            }

            p2->Update();
            if(knee_step_global > 0){
                double y1 = p2->GetUymin();
                double y2 = p2->GetUymax();
                TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
                lk->SetLineColor(kBlack);
                lk->SetLineStyle(2);
                lk->SetLineWidth(3);
                lk->Draw("SAME");
            }

            // PAD3 diff
            c->cd(3);
            TPad* p3 = (TPad*)gPad;
            p3->SetLeftMargin(0.10);
            p3->SetRightMargin(0.03);
            p3->SetTopMargin(0.03);
            p3->SetBottomMargin(0.12);
            if(logx) p3->SetLogx();

            TH1D* hdf0 = (TH1D*)diff_hist_vec[0]->Clone(Form("%s_diff_0", cname));
            hdf0->SetTitle("#bf{#Delta#Phi (%) vs EM iteration}");
            hdf0->GetXaxis()->SetRangeUser(2, max_steps);
            hdf0->SetStats(0);
            hdf0->Draw("HIST");

            for(size_t j=1;j<diff_hist_vec.size();++j){
                diff_hist_vec[j]->GetXaxis()->SetRangeUser(2, max_steps);
                set_color(diff_hist_vec[j], j);
                diff_hist_vec[j]->Draw("HIST SAME");
            }

            double diff_threshold = 2.0;
            double xminD = hdf0->GetXaxis()->GetXmin();
            double xmaxD = hdf0->GetXaxis()->GetXmax();
            TLine* ld = new TLine(xminD, diff_threshold, xmaxD, diff_threshold);
            ld->SetLineColor(kBlack);
            ld->SetLineStyle(3);
            ld->SetLineWidth(3);
            ld->Draw("SAME");

            p3->Update();
            if(knee_step_global > 0){
                double y1 = p3->GetUymin();
                double y2 = p3->GetUymax();
                TLine* lk = new TLine(knee_step_global, y1, knee_step_global, y2);
                lk->SetLineColor(kBlack);
                lk->SetLineStyle(2);
                lk->SetLineWidth(3);
                lk->Draw("SAME");
            }

            c->Update();

            std::string scale_rep = logx ? "log" : "lin";
            c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
                       "/Summary_knee_"+campaign+"_Campaign_event_"+str_stream_event+
                       "_timegrid_"+std::to_string(timegrid)+
                       "_ndet_"+std::to_string(ndet)+
                       "_"+scale_rep+"_"+scale_factor+"_NEW.pdf").c_str());
        };

        DrawSummaryKneeCanvas("c_summary_knee_lin", "Summary knee (lin x)", false);
        DrawSummaryKneeCanvas("c_summary_knee_log", "Summary knee (log x)", true);
    }

    // -------------------------
    // Guardar chi2_stop por seed + resumen por evento a un ROOT
    // -------------------------
    std::string out_root =
        "../outputs/root/deconv_data_rootfile/Knee/"+campaign_path+
        "/Knee_chi2stop_"+campaign+"_Campaign_event_"+str_stream_event+
        "_timegrid_"+std::to_string(timegrid)+
        "_ndet_"+std::to_string(ndet)+
        "_"+scale_factor+".root";

    // crea dirs si no existen (si trabajas en ROOT macro puro quizá no tienes filesystem aquí)
    // -> si lo necesitas te lo dejo con gSystem->mkdir()

    TFile* fout = TFile::Open(out_root.c_str(), "RECREATE");
    TTree* tk = new TTree("knee_tree", "knee and chi2_stop per seed");

    Int_t out_event = event;
    Int_t out_seed  = 0;
    Double_t out_knee_step = -1.0;
    Double_t out_chi2_stop = -1.0;

    tk->Branch("event", &out_event);
    tk->Branch("seed_idx", &out_seed);
    tk->Branch("knee_step", &out_knee_step);
    tk->Branch("chi2_stop", &out_chi2_stop);

    for(int j=0;j<nSeeds;j++){
        out_seed      = j;
        out_knee_step = knee_step_per_seed[j];
        out_chi2_stop = knee_chi2_per_seed[j];
        tk->Fill();
    }

    // resumen por evento
    TTree* te = new TTree("event_summary", "event-level summary");
    Double_t knee_step_median = knee_step_global;
    Double_t chi2_stop_median = knee_chi2_global;
    Int_t n_valid = 0;
    for(double ks : knee_step_per_seed) if(ks>0) n_valid++;

    te->Branch("event", &out_event);
    te->Branch("knee_step_median", &knee_step_median);
    te->Branch("chi2_stop_median", &chi2_stop_median);
    te->Branch("n_valid_seeds", &n_valid);
    te->Branch("n_total_seeds", &nSeeds);
    te->Fill();

    tk->Write();
    te->Write();
    fout->Close();

    fin->Close();

    std::cout << "Guardado: " << out_root << "\n";

/******************************************************************************/
/*** Integral flux by step, per seed (single ROOT file with all steps)      ***/
/******************************************************************************/

		// ====== input single file ======
		//~ std::string input_single_file =
			//~ "./deconv_data_rootfile/EM_single/EM_single_campaign_" + campaign +
			//~ "_event_" + str_stream_event +
			//~ "_timegrid_" + str_stream_timegrid +
			//~ "_ndet_" + str_stream_ndet +
			//~ "_maxsteps_" + std::to_string(max_steps) + ".root";

		// Ajusta el nombre del tree si es distinto:
		ROOT::RDataFrame df_single("em_event_tree", input_single_file);

		// ====== definir N seeds y steps ======
		const int NSEED = 21;               // 
		const int NSTEP = max_steps;         // 1..max_steps

		// ====== matrices [step][seed] ======
		std::vector<std::vector<double>> intg_total_matrix(NSTEP, std::vector<double>(NSEED, 0.0));
		std::vector<std::vector<double>> intg_th_matrix   (NSTEP, std::vector<double>(NSEED, 0.0));
		std::vector<std::vector<double>> intg_ep_matrix   (NSTEP, std::vector<double>(NSEED, 0.0));
		std::vector<std::vector<double>> intg_fs_matrix   (NSTEP, std::vector<double>(NSEED, 0.0));
		std::vector<std::vector<double>> intg_he_matrix   (NSTEP, std::vector<double>(NSEED, 0.0));

		// ====== tomamos columnas completas (vector de longitud = nEntries) ======
		auto v_step  = df_single.Take<int>("step").GetValue();
		auto v_seed  = df_single.Take<int>("seed_idx").GetValue();       // o "seed_id", etc.
		auto v_tot   = df_single.Take<double>("Intg_total").GetValue();
		auto v_th    = df_single.Take<double>("Intg_th").GetValue();
		auto v_ep    = df_single.Take<double>("Intg_ep").GetValue();
		auto v_fs    = df_single.Take<double>("Intg_fs").GetValue();
		auto v_he    = df_single.Take<double>("Intg_he").GetValue();

		if (v_step.size() != v_seed.size()) {
			std::cerr << "[ERROR] step and seed vector sizes mismatch\n";
		}

		// ====== rellenar matrices ======
		for (size_t i = 0; i < v_step.size(); ++i) {
			int s = v_step[i];     // 1..max_steps
			int j = v_seed[i];     // 0..500 (o 1..501)

			// Si tus seeds vienen 1..501, descomenta:
			// j = j - 1;

			if (s < 1 || s > NSTEP) continue;
			if (j < 0 || j >= NSEED) continue;

			intg_total_matrix[s-1][j] = v_tot[i];
			intg_th_matrix[s-1][j]    = v_th[i];
			intg_ep_matrix[s-1][j]    = v_ep[i];
			intg_fs_matrix[s-1][j]    = v_fs[i];
			intg_he_matrix[s-1][j]    = v_he[i];
		}

		// ====== construir eje X steps (igual que antes) ======
		//~ std::vector<double> x_vec_steps;
		//~ x_vec_steps.reserve(max_steps);
		//~ for (int i=1; i<=max_steps; ++i) x_vec_steps.push_back(i);

		double *x_steps_edgeds = x_vec_steps.data();
		//~ const int binnum_steps = (int)x_vec_steps.size()-1;

		// ====== build hist vectors por seed ======
		std::string hist_name_intg_total, hist_name_intg_th, hist_name_intg_ep, hist_name_intg_fs, hist_name_intg_he;

		std::vector<TH1D*> intg_total_hist_vec;
		std::vector<TH1D*> intg_th_hist_vec;
		std::vector<TH1D*> intg_ep_hist_vec;
		std::vector<TH1D*> intg_fs_hist_vec;
		std::vector<TH1D*> intg_he_hist_vec;

		intg_total_hist_vec.reserve(NSEED);
		intg_th_hist_vec.reserve(NSEED);
		intg_ep_hist_vec.reserve(NSEED);
		intg_fs_hist_vec.reserve(NSEED);
		intg_he_hist_vec.reserve(NSEED);

		double title_size    = 0.08;
		double x_title_size  = 0.05;
		double title_offset  = 0.5;
		double x_title_offset= 0.7;
		int y_axis_max_dig   = 2;

		for(int j=0; j<NSEED; ++j){

			//~ double x_seed = j/5.0; // mismo mapeo visual que usabas (501 semillas)
			double x_seed = j/0.2; // mismo mapeo visual que usabas (21 semillas)
			std::ostringstream stream_seed;
			stream_seed << x_seed;
			std::string str_stream_seed = stream_seed.str();

			hist_name_intg_total = "Intg_total_by_step_seed_" + str_stream_seed;
			hist_name_intg_th    = "Intg_th_by_step_seed_"    + str_stream_seed;
			hist_name_intg_ep    = "Intg_ep_by_step_seed_"    + str_stream_seed;
			hist_name_intg_fs    = "Intg_fs_by_step_seed_"    + str_stream_seed;
			hist_name_intg_he    = "Intg_he_by_step_seed_"    + str_stream_seed;

			TH1D* h_tot = new TH1D(hist_name_intg_total.c_str(), hist_name_intg_total.c_str(), binnum_steps, x_steps_edgeds);
			TH1D* h_th  = new TH1D(hist_name_intg_th.c_str(),    hist_name_intg_th.c_str(),    binnum_steps, x_steps_edgeds);
			TH1D* h_ep  = new TH1D(hist_name_intg_ep.c_str(),    hist_name_intg_ep.c_str(),    binnum_steps, x_steps_edgeds);
			TH1D* h_fs  = new TH1D(hist_name_intg_fs.c_str(),    hist_name_intg_fs.c_str(),    binnum_steps, x_steps_edgeds);
			TH1D* h_he  = new TH1D(hist_name_intg_he.c_str(),    hist_name_intg_he.c_str(),    binnum_steps, x_steps_edgeds);

			for(int i=0; i<max_steps; ++i){
				h_tot->SetBinContent(i+1, intg_total_matrix[i][j]);
				h_th ->SetBinContent(i+1, intg_th_matrix[i][j]);
				h_ep ->SetBinContent(i+1, intg_ep_matrix[i][j]);
				h_fs ->SetBinContent(i+1, intg_fs_matrix[i][j]);
				h_he ->SetBinContent(i+1, intg_he_matrix[i][j]);
			}

			auto style_intg = [&](TH1D* h, const char* ytitle){
				h->GetXaxis()->SetTitle("#bf{EM iteration}");
				h->GetYaxis()->SetTitle(ytitle);
				h->GetXaxis()->SetTitleSize(x_title_size);
				h->GetXaxis()->SetTitleOffset(x_title_offset);
				h->GetYaxis()->SetTitleSize(title_size);
				h->GetYaxis()->SetTitleOffset(title_offset);
				h->GetYaxis()->SetMaxDigits(y_axis_max_dig);
			};

			style_intg(h_tot, "#bf{#Phi_{total}}");
			style_intg(h_th,  "#bf{#Phi_{th}}");
			style_intg(h_ep,  "#bf{#Phi_{ep}}");
			style_intg(h_fs,  "#bf{#Phi_{fs}}");
			style_intg(h_he,  "#bf{#Phi_{he}}");

			intg_total_hist_vec.push_back(h_tot);
			intg_th_hist_vec.push_back(h_th);
			intg_ep_hist_vec.push_back(h_ep);
			intg_fs_hist_vec.push_back(h_fs);
			intg_he_hist_vec.push_back(h_he);
		}

		// ====== dibujar canvas (reuso tu función) ======
		auto DrawIntgCanvas = [&](const char* cname,
								  const char* ctitle,
								  bool logx,
								  const std::vector<TH1D*>& v_tot,
								  const std::vector<TH1D*>& v_th,
								  const std::vector<TH1D*>& v_ep,
								  const std::vector<TH1D*>& v_fs,
								  const std::vector<TH1D*>& v_he)
		{
			TCanvas *c = new TCanvas(cname, ctitle, 1920, 1080);
			c->Divide(2,3);

			std::string scale_rep;

			auto draw_vec = [&](int pad, const std::vector<TH1D*>& vec_hist)
			{
				c->cd(pad);

				//~ if (logx){ gPad->SetLogx(); scale_rep="log"; }
				//~ else     { scale_rep="lin"; }

			if (logx){
				gPad->SetLogx();
				scale_rep = "log";
			}
			else{scale_rep = "lin";}

				double sc_factor;
				if(scale_factor=="ws"){sc_factor=1.0;}
				if(scale_factor=="wos"){sc_factor=0.25;}

				if(pad==2){//thermal region
					//~ vec_hist[0]->GetYaxis()->SetRangeUser(3e-03,10e-03);
					//~ double up_lim = 10.*sc_factor;
					vec_hist[0]->GetYaxis()->SetRangeUser(3.0*sc_factor*pow(10.0,-3), 10.0*sc_factor*pow(10.0,-3));
				}
				if(pad==3){//epithermal region
					if(ndet==11){
					vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),19.0*sc_factor*pow(10.0,-3)); // ndet 11
					}
					if(ndet==16){
					vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),22.0*sc_factor*pow(10.0,-3)); //ndet 16
					}
				}
				if(pad==4){//fast region
					if(ndet==11){
					vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),26.0*sc_factor*pow(10.0,-3)); //ndet 11
					}
					if(ndet==16){
					vec_hist[0]->GetYaxis()->SetRangeUser(10.0*sc_factor*pow(10.0,-3),26.0*sc_factor*pow(10.0,-3)); // ndet 16
					}
				}
				if(pad==5){//high region
					if(ndet==11){
					vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),51.0*sc_factor*pow(10.0,-3)); //ndet 11
					}
					if(ndet==16){
					vec_hist[0]->GetYaxis()->SetRangeUser(15.0*sc_factor*pow(10.0,-3),51.*sc_factor*pow(10.0,-3)); // ndet 16
					}
				}

				// dibuja
				vec_hist[0]->Draw("HIST");

				//~ int nColors = 501;
				int nColors = 21;
				double step = double(nColors) / double(vec_hist.size());

				for (size_t j=1; j<vec_hist.size(); ++j){
					int colorIndex  = int(j*step);
					int colorIndex2 = 51 + colorIndex * 48 / vec_hist.size();
					vec_hist[j]->SetLineColor(colorIndex2);
					vec_hist[j]->Draw("HIST SAME");
				}
			};

			draw_vec(1, v_tot);
			draw_vec(2, v_th);
			draw_vec(3, v_ep);
			draw_vec(4, v_fs);
			draw_vec(5, v_he);

			c->Update();

			c->SaveAs(("../outputs/pdf/deconv_data_pdf/Chi_squared/"+campaign_path+
					   "/Integral_flux_values_singlefile_"+campaign+
					   "_event_"+str_stream_event+
					   "_timegrid_"+std::to_string(timegrid)+
					   "_ndet_"+std::to_string(ndet)+
					   "_"+scale_rep+"_"+scale_factor+".pdf").c_str());

			//~ c->SaveAs(("./deconv_data_pdf/Chi_squared/"+campaign_path+
					   //~ "/Integral_flux_values_singlefile_"+campaign+
					   //~ "_event_"+str_stream_event+
					   //~ "_timegrid_"+std::to_string(timegrid)+
					   //~ "_ndet_"+std::to_string(ndet)+
					   //~ "_"+scale_rep+"_"+scale_factor+".svg").c_str());
		};

		DrawIntgCanvas("c_intg_lin_single", "Integral flux vs step (linear X, single file)", false,
					   intg_total_hist_vec, intg_th_hist_vec, intg_ep_hist_vec, intg_fs_hist_vec, intg_he_hist_vec);

		DrawIntgCanvas("c_intg_log_single", "Integral flux vs step (log X, single file)", true,
					   intg_total_hist_vec, intg_th_hist_vec, intg_ep_hist_vec, intg_fs_hist_vec, intg_he_hist_vec);


    
}



/**Funcion que grafica el espectro resultante del EM para un evento determinado para un numero de paso determinado**/
void deconv_flux_plot_by_seed(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation, string physic_list){

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

string campaign_path;

if(physic_list=="QGSP_BERT")
	{
	  campaign_path = campaign; //Ex: LCO
	  //~ cout << physic_list+" Physic_list" << endl;}
	}
if(physic_list=="FTFP_BERT")
	{
	 campaign_path = campaign+"_FTFP_BERT"; //Ex: LCO_FTFP_BERT
	 //~ cout << physic_list+" Physic_list" << endl;}
    }
else{cout << "Physics list inexistente o incorrecta" << endl;}

/*Llenamos un vector de histogramas por numero de pasos para la misma semilla*/
for(int i = steps; i<=steps;i++){
	hist_deconv_flux_vec.push_back(deconv_hist_from_steps_and_seeds_TH1D(campaign,event,i,timegrid, ndet, bin_seed,flux_representation, physic_list));
}

for(int i=0;i<hist_deconv_flux_vec.size();i++){
		/*Coloremos los histogramas deconvolucionados por region de energia*/
	//~ auto hist_deconv_color_th = (TH1D*)flux_deconv_2->Clone();
	auto hist_step_color_th = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_deconv_color_th->SetFillColor(kGray);
	hist_step_color_th->SetFillColorAlpha(kGray,0.45);
	//~ hist_deconv_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);
	int binNumber_th = 23;  // example bin index
	// Get the upper edge of bin 
	double upperEdge_th =hist_step_color_th->GetXaxis()->GetBinUpEdge(binNumber_th);
	cout << "UpperEdge thermal region="<< upperEdge_th << " bin=" << binNumber_th << endl;
	hist_step_color_th->GetXaxis()->SetRangeUser(0, upperEdge_th);

	//~ auto hist_deconv_color_ep = (TH1D*)flux_deconv_2->Clone();
	auto hist_step_color_ep = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_deconv_color_ep->SetFillColor(kCyan-9);
	 hist_step_color_ep->SetFillColorAlpha(kCyan-9,0.45);
	//~ hist_deconv_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);
	int binNumber_ep = 70;  // example bin index
	// Get the upper edge of bin 
	double upperEdge_ep =  hist_step_color_ep->GetXaxis()->GetBinUpEdge(binNumber_ep);
	cout << "UpperEdge epithermal region="<< upperEdge_ep << " bin=" << binNumber_ep  << endl;
	 hist_step_color_ep->GetXaxis()->SetRangeUser(upperEdge_th, upperEdge_ep);

	//~ auto hist_deconv_color_fs = (TH1D*)flux_deconv_2->Clone();
	auto hist_step_color_fs = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_deconv_color_fs->SetFillColor(kGreen-9);
	hist_step_color_fs->SetFillColorAlpha(kGreen-9,0.45);
	//~ hist_deconv_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);
	int binNumber_fs = 100;  // example bin index
	// Get the upper edge of bin 
	double upperEdge_fs = hist_step_color_fs->GetXaxis()->GetBinUpEdge(binNumber_fs);
	cout << "UpperEdge fast region="<< upperEdge_fs << " bin=" << binNumber_fs  << endl;
	hist_step_color_fs->GetXaxis()->SetRangeUser(upperEdge_ep, upperEdge_fs);

	//~ auto hist_deconv_color_he = (TH1D*)flux_deconv_2->Clone();
	auto hist_step_color_he = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_deconv_color_he->SetFillColor(kRed-9);
	hist_step_color_he->SetFillColorAlpha(kRed-9,0.45);
	//~ hist_deconv_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
	int binNumber_he = 129;  // example bin index
	// Get the upper edge of bin 
	double upperEdge_he = hist_step_color_he->GetXaxis()->GetBinUpEdge(binNumber_he);
	cout << "UpperEdge high energy region="<< upperEdge_he << " bin=" << binNumber_he  << endl;
	hist_step_color_he->GetXaxis()->SetRangeUser(upperEdge_fs, upperEdge_he);

	
/*Coloremos los histogramas deconvolucionados por region de energia*/
	//~ auto hist_step_color_th = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_step_color_th->SetFillColor(kGray);
	//~ hist_step_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);
	
	//~ auto hist_step_color_ep = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_step_color_ep->SetFillColor(kCyan-9);
	//~ hist_step_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);
	
	//~ auto hist_step_color_fs = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_step_color_fs->SetFillColor(kGreen-9);
	//~ hist_step_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);
	
	//~ auto hist_step_color_he = (TH1D*)hist_deconv_flux_vec[i]->Clone();
	//~ hist_step_color_he->SetFillColor(kRed-9);
	//~ hist_step_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
	
	vec_hist_deconv_color_th.push_back(hist_step_color_th); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_ep.push_back(hist_step_color_ep); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_fs.push_back(hist_step_color_fs); // llenamos el vector de histogramas coloreado
	vec_hist_deconv_color_he.push_back(hist_step_color_he); // llenamos el vector de histogramas coloreado	
}

/*Llenamos con la info de cada histograma: integrales por region y Chi2*/

vector< vector<double>> vec_data_steps;

for(int i = steps; i<=steps;i++){
	ostringstream stream_steps_new;
	stream_steps_new << i;
	string str_stream_steps_new = stream_steps_new.str();

	vector<double> vec_data_step;

	string input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps_new+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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
	auto df_flux_deconv_diff_criteria = df_seed_loop_step.Take<double>("diff_criteria").GetValue();
	
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
	vec_data_step.push_back(df_flux_deconv_diff_criteria[bin_seed-1]);

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
		
canvas_deconv->Divide(1,1);
		//~ canvas_deconv->Divide(6,5);
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
	
	//~ canvas_deconv->GetPad(i+1)->SetLeftMargin(0.15);
	canvas_deconv->GetPad(i+1)->SetLeftMargin(0.08);
	canvas_deconv->GetPad(i+1)->SetRightMargin(0.009);
	//~ double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
	double shift_margin = -0.03; // para reajustar la poscion de el texto dentro del pad
	if (flux_representation=="Differential")
		{
			gPad->SetLogy();
		}

	/*Destacamos los pads en los cuales chi-square es menor a ndet*/
	TPad* pad = (TPad*)canvas_deconv->GetPad(i+1);
	//~ if (data_to_hist[6]<ndet){
               // Change pad properties to highlight it
				//~ pad->SetFillColor(kYellow-9);
				//~ pad->SetFillStyle(3003); // Solid fill
         //~ }
	if (data_to_hist[6]>1.0){
               // Change pad properties to highlight it
				//~ pad->SetFillColor(kYellow-9);
				//~ pad->SetFillStyle(3003); // Solid fill
         }
    //~ /*Para mostrar a partir de que valor los ratios se normalizan al dividir por la integral de la region de alta energia */
	double sum_eta_ratios = data_to_hist[2]/data_to_hist[5] + data_to_hist[3]/data_to_hist[5] + data_to_hist[4]/data_to_hist[5];
	 //~ if (sum_eta_ratios<=1.0){
		           //~ // Change pad properties to highlight it
				//~ pad->SetFillColor(kMagenta-9);
				//~ pad->SetFillStyle(3003); // Solid fill
			//~ }
	 //~ if (data_to_hist[6]<ndet & sum_eta_ratios<=1.0){
		           //~ // Change pad properties to highlight it
				//~ pad->SetFillColor(kOrange-9);
				//~ pad->SetFillStyle(3003); // Solid fill
			//~ }

/*Para mostrar a partir de que valor el diff criteria es menor al 2% */
	if (data_to_hist[11]<0.02){
               // Change pad properties to highlight it
				//~ pad->SetFillColor(kMagenta-9);
				//~ pad->SetFillStyle(3003); // Solid fill
         }

/*Para mostrar a partir de que valor se cumplen ambos criterios chi-square y diff criteria*/
	 if (data_to_hist[11]<0.02 && data_to_hist[6]<ndet){
		           // Change pad properties to highlight it
				//~ pad->SetFillColor(kPink+9);
				//~ pad->SetFillStyle(3003); // Solid fill
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

	ostringstream stream_diff_criteria;

	
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
	stream_diff_criteria  << setprecision(3) << data_to_hist[11];
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

	string str_stream_diff_criteria = "#Delta_{#Phi_{i+1}-#Phi_{i}}="+stream_diff_criteria.str();

	TLatex *l_ndet = new TLatex(0.15+shift_margin,0.85,str_stream_ndet.c_str());
	TLatex *l_intg_total = new TLatex(0.15+shift_margin,0.8,str_stream_intgtotal.c_str());
	TLatex *l_Chi2 = new TLatex(0.15+shift_margin,0.75,str_stream_Chi2.c_str());
	//~ TLatex *l_sum_eta = new TLatex(0.35+shift_margin,0.75,str_stream_sum_eta.c_str());
	TLatex *l_Chi2red = new TLatex(0.15+shift_margin,0.70,str_stream_Chi2red.c_str());
	TLatex *l_diff_criteria = new TLatex(0.15+shift_margin,0.65,str_stream_diff_criteria.c_str());
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

	hist_deconv_flux_vec[i]->SetLineWidth(3);
	hist_deconv_flux_vec[i]->GetYaxis()->SetMaxDigits(3);
	hist_deconv_flux_vec[i]->GetYaxis()->SetTitleOffset(0.8);
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

	//~ l_intgtotal_ratio_th->SetNDC();
	//~ l_intgtotal_ratio_th->SetTextSize(0.04);
	//~ l_intgtotal_ratio_ep->SetNDC();
	//~ l_intgtotal_ratio_ep->SetTextSize(0.04);
	//~ l_intgtotal_ratio_fs->SetNDC();
	//~ l_intgtotal_ratio_fs->SetTextSize(0.04);
	//~ l_intgtotal_ratio_he->SetNDC();
	//~ l_intgtotal_ratio_he->SetTextSize(0.04);

	//~ l_intghe_ratio_th->SetNDC();
	//~ l_intghe_ratio_th->SetTextSize(0.04);
	//~ l_intghe_ratio_ep->SetNDC();
	//~ l_intghe_ratio_ep->SetTextSize(0.04);
	//~ l_intghe_ratio_fs->SetNDC();
	//~ l_intghe_ratio_fs->SetTextSize(0.04);
	
	//~ l_sum_eta->SetNDC();
	//~ l_sum_eta->SetTextSize(0.04);

	//~ l_xi2->SetNDC();
	//~ l_xi2->SetTextSize(0.04);
	//~ l_barDelta->SetNDC();
	//~ l_barDelta->SetTextSize(0.04);
	//~ l_std_cr->SetNDC();
	//~ l_std_cr->SetTextSize(0.04);

	l_diff_criteria->SetNDC();
	l_diff_criteria->SetTextSize(0.04);

		
	l_ndet->Draw("SAME");
	l_intg_th->Draw("SAME");
	l_intg_total->Draw("SAME");
	l_Chi2->Draw("SAME");
	l_Chi2red->Draw("SAME");
	l_intg_ep->Draw("SAME");
	l_intg_fs->Draw("SAME");
	l_intg_he->Draw("SAME");
	
	//~ l_intgtotal_ratio_th->Draw("SAME");
	//~ l_intgtotal_ratio_ep->Draw("SAME");
	//~ l_intgtotal_ratio_fs->Draw("SAME");
	//~ l_intgtotal_ratio_he->Draw("SAME");

	//~ l_intghe_ratio_th->Draw("SAME");
	//~ l_intghe_ratio_ep->Draw("SAME");
	//~ l_intghe_ratio_fs->Draw("SAME");

	//~ l_sum_eta->Draw("SAME");

	//~ l_xi2->Draw("SAME");
	//~ l_barDelta->Draw("SAME");
	//~ l_std_cr->Draw("SAME");

	l_diff_criteria->Draw("SAME");



	gPad->RedrawAxis();
	}

/*Mostramos el canvas y lo guardamos*/

canvas_deconv->Draw();
canvas_deconv->SaveAs(("../outputs/pdf/deconv_data_pdf/deconv_flux_multiplot/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".pdf").c_str());
canvas_deconv->SaveAs(("../outputs/pdf/deconv_data_pdf/deconv_flux_multiplot/"+campaign_path+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".svg").c_str());
//~ canvas_deconv->SaveAs(("./deconv_data_pdf/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_maxsteps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_binseed_"+str_stream_seed+".eps").c_str());


//~ delete canvas_deconv;


}

void loop_deconv_flux_plot_by_seed(){

	//~ for(int i=1;i<=450;i++){
	 //~ deconv_flux_plot_by_seed("LCO",70,i,15,11,75,"Lethargy","FTFP_BERT");
	//~ };
	for(int i=451;i<=470;i++){
	 deconv_flux_plot_by_seed("LCO",70,i,15,11,75,"Lethargy","FTFP_BERT");
	};

}

/*Funcion que genera un canvas donde se grafica en cada pad (6 en total): en el eje x el valor de semilla y en el eje y el valor de: Chi2, la integral total del flujo integral decnvolcionado */
/*la integral del rango termico, epitermico, rapido y de alta energia del flujo integral decnvolcionado, respectivamente. Todo esto para un cierto numero de iteraciones*/
/*del algoritmo EM*/
void em_loop_seed_plot_template(string campaign, int event, int steps, int timegrid, int ndet, string physic_list){

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
	hist_vec_Chi2.push_back(em_step_plot_Chi_TH1D(campaign,event,i,timegrid,ndet, physic_list));
	hist_vec_IntgTotal.push_back(em_step_plot_IntgTotal_TH1D(campaign,event,i,timegrid,ndet,physic_list));
	hist_vec_IntgTh.push_back(em_step_plot_Intgth_TH1D(campaign,event,i,timegrid,ndet,physic_list));
	hist_vec_IntgEp.push_back(em_step_plot_Intgep_TH1D(campaign,event,i,timegrid,ndet,physic_list));
	hist_vec_IntgFs.push_back(em_step_plot_Intgfs_TH1D(campaign,event,i,timegrid,ndet,physic_list));
	hist_vec_IntgHe.push_back(em_step_plot_Intghe_TH1D(campaign,event,i,timegrid,ndet,physic_list));		
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
		hist_vec_Chi2[i]->DrawClone("HIST SAME");
	}

canvas_Chi2->cd(2);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgTotal[i]->SetLineColor(colors[i]);
	}

	hist_vec_IntgTotal[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgTotal[i]->DrawClone("HIST SAME");
	}

canvas_Chi2->cd(3);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgTh[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgTh[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgTh[i]->DrawClone("HIST SAME");
	}

canvas_Chi2->cd(4);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgEp[i]->SetLineColor(colors[i]);
	}

	hist_vec_IntgEp[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgEp[i]->DrawClone("HIST SAME");
	}

canvas_Chi2->cd(5);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgFs[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgFs[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgFs[i]->DrawClone("HIST SAME");
	}

canvas_Chi2->cd(6);

	for(int i = 0; i<steps;i++){
	 hist_vec_IntgHe[i]->SetLineColor(colors[i]);
	}
	
	hist_vec_IntgHe[0]->DrawClone("HIST");

	for(int i = 1; i<steps;i++){
		hist_vec_IntgHe[i]->DrawClone("HIST SAME");
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
   

	string input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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

   canvas->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot.pdf").c_str());


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


	//~ string input_complete_file= "./deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	//~ string input_complete_file= "./deconv_data_rootfile/EM_stop/"+campaign+"/em_stop_2_percent_criteria/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
	string input_complete_file= "../outputs/root/deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
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
   

	string input_complete_file= "../outputs/root/deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
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

   canvas->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/MC/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_scatterplot_MC_"+str_stream_mc_it+"_it.pdf").c_str());


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
 
canvas_deconv_group_1->Divide(4,4);//Events 1-16
canvas_deconv_group_2->Divide(4,4);//Events 17-33
canvas_deconv_group_3->Divide(4,4);//Events 34-50
canvas_deconv_group_4->Divide(4,4);//Events 51-67
canvas_deconv_group_5->Divide(4,4);//Events 68-84
canvas_deconv_group_6->Divide(4,4);//Events 85-101
canvas_deconv_group_7->Divide(4,4);//Events 102-118
canvas_deconv_group_8->Divide(4,4);//Events 119-135
canvas_deconv_group_9->Divide(4,4);//Events 136-152
canvas_deconv_group_10->Divide(4,4);//Events  153-169
canvas_deconv_group_11->Divide(4,4);//Events  170-186
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

	canvas_deconv_group_1->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g1+".pdf").c_str());
	canvas_deconv_group_2->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g2+".pdf").c_str());
	canvas_deconv_group_3->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g3+".pdf").c_str());
	canvas_deconv_group_4->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g4+".pdf").c_str());
	canvas_deconv_group_5->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g5+".pdf").c_str());
	canvas_deconv_group_6->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g6+".pdf").c_str());
	canvas_deconv_group_7->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g7+".pdf").c_str());
	canvas_deconv_group_8->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g8+".pdf").c_str());
	canvas_deconv_group_9->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g9+".pdf").c_str());
	canvas_deconv_group_10->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g10+".pdf").c_str());
	canvas_deconv_group_11->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g11+".pdf").c_str());
	canvas_deconv_group_12->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g12+".pdf").c_str());
	canvas_deconv_group_13->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g13+".pdf").c_str());
	canvas_deconv_group_14->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g14+".pdf").c_str());
	canvas_deconv_group_15->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g15+".pdf").c_str());
	canvas_deconv_group_16->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g16+".pdf").c_str());
	canvas_deconv_group_17->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g17+".pdf").c_str());
	canvas_deconv_group_18->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g18+".pdf").c_str());
}

void scatter_plots_event_loop_general(string campaign, int event, int steps, int timegrid, int ndet){

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

//~ int number_of_events_in_campaign = 342; //Maricunga
//~ int number_of_events_in_campaign = 271; //RetenDesierto
int number_of_events_in_campaign = 300; //Chaquipilta

/*Iteramos sobre el numero de eventos*/
for(int i=1;i<=number_of_events_in_campaign;i++)
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
string canvas_name_g19 = canvas_name+"_group_19";
string canvas_name_g20 = canvas_name+"_group_20";
string canvas_name_g21 = canvas_name+"_group_21";
string canvas_name_g22 = canvas_name+"_group_22";

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
TCanvas *canvas_deconv_group_19 = new TCanvas(canvas_name_g19.c_str(),canvas_name_g19.c_str(),1920,1080);
TCanvas *canvas_deconv_group_20 = new TCanvas(canvas_name_g20.c_str(),canvas_name_g20.c_str(),1920,1080);
TCanvas *canvas_deconv_group_21 = new TCanvas(canvas_name_g21.c_str(),canvas_name_g21.c_str(),1920,1080);
TCanvas *canvas_deconv_group_22 = new TCanvas(canvas_name_g22.c_str(),canvas_name_g22.c_str(),1920,1080);
 
canvas_deconv_group_1->Divide(4,4);//Events 1-16
canvas_deconv_group_2->Divide(4,4);//Events 17-33
canvas_deconv_group_3->Divide(4,4);//Events 34-50
canvas_deconv_group_4->Divide(4,4);//Events 51-67
canvas_deconv_group_5->Divide(4,4);//Events 68-84
canvas_deconv_group_6->Divide(4,4);//Events 85-101
canvas_deconv_group_7->Divide(4,4);//Events 102-118
canvas_deconv_group_8->Divide(4,4);//Events 119-135
canvas_deconv_group_9->Divide(4,4);//Events 136-152
canvas_deconv_group_10->Divide(4,4);//Events  153-169
canvas_deconv_group_11->Divide(4,4);//Events  170-186
canvas_deconv_group_12->Divide(4,4);
canvas_deconv_group_13->Divide(4,4);
canvas_deconv_group_14->Divide(4,4);
canvas_deconv_group_15->Divide(4,4);
canvas_deconv_group_16->Divide(4,4);
canvas_deconv_group_17->Divide(4,4);
canvas_deconv_group_18->Divide(4,4);
canvas_deconv_group_19->Divide(4,4);
canvas_deconv_group_20->Divide(4,4);
canvas_deconv_group_21->Divide(4,4);
canvas_deconv_group_22->Divide(4,4);

/*llenamos cada entrada del canvas con un histograma del vector de histogramas*/
int count_group=0;
//~ int total_events = 289 (total) - 11(error en EM); //278 LCO
int total_events = number_of_events_in_campaign; //Maricunga

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
		if(272<=i & i<288)
			{
			 canvas_deconv_group_18->cd((i+1)-272);
			}
		if(288<=i & i<304)
			{
			 canvas_deconv_group_19->cd((i+1)-288);
			}
		if(304<=i & i<320)
			{
			 canvas_deconv_group_20->cd((i+1)-304);
			}
		if(320<=i & i<336)
			{
			 canvas_deconv_group_21->cd((i+1)-320);
			}			
		if(336<=i & i<=342)
			{
			 canvas_deconv_group_22->cd((i+1)-336);
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
canvas_deconv_group_19->Draw();
canvas_deconv_group_20->Draw();
canvas_deconv_group_21->Draw();
canvas_deconv_group_22->Draw();

canvas_deconv_group_1->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g1+".pdf").c_str());
canvas_deconv_group_2->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g2+".pdf").c_str());
canvas_deconv_group_3->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g3+".pdf").c_str());
canvas_deconv_group_4->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g4+".pdf").c_str());
canvas_deconv_group_5->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g5+".pdf").c_str());
canvas_deconv_group_6->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g6+".pdf").c_str());
canvas_deconv_group_7->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g7+".pdf").c_str());
canvas_deconv_group_8->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g8+".pdf").c_str());
canvas_deconv_group_9->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g9+".pdf").c_str());
canvas_deconv_group_10->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g10+".pdf").c_str());
canvas_deconv_group_11->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g11+".pdf").c_str());
canvas_deconv_group_12->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g12+".pdf").c_str());
canvas_deconv_group_13->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g13+".pdf").c_str());
canvas_deconv_group_14->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g14+".pdf").c_str());
canvas_deconv_group_15->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g15+".pdf").c_str());
canvas_deconv_group_16->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g16+".pdf").c_str());
canvas_deconv_group_17->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g17+".pdf").c_str());
canvas_deconv_group_18->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g18+".pdf").c_str());
canvas_deconv_group_19->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g19+".pdf").c_str());
canvas_deconv_group_20->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g20+".pdf").c_str());
canvas_deconv_group_21->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g21+".pdf").c_str());
canvas_deconv_group_22->SaveAs(("../outputs/pdf/deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+canvas_name_g22+".pdf").c_str());
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
		input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
		
		string input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
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
canvas_deconv_fluxes->SaveAs(("../outputs/pdf/deconv_data_pdf/event_seed_picker/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos_picker_1.pdf").c_str());


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
				string input_complete_file = "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
		
		string input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
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
canvas_deconv_fluxes->SaveAs(("../outputs/pdf/deconv_data_pdf/event_seed_picker/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos_picker_2.pdf").c_str());


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
				string input_complete_file = "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
		
		string input_complete_file= "../outputs/root/deconv_data_rootfile/EM/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_step_pick+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

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
auto seed_flux_expacs_csv ="../data/external/EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
seed_rdf.Snapshot("expacs_flux","../outputs/root/seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
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
canvas_deconv_fluxes->SaveAs(("../outputs/pdf/deconv_data_pdf/event_seed_picker/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_comparacion_semillas_eventos_picker_3.pdf").c_str());


}


/*Funcion que itera la funcion em_loop_seed() sobre el numero de pasos*/
void em_loop_steps(string campaign,int event,int steps,int time_grid, int ndet, int max_steps, string cut){

/*Criterio de stop*/
if(steps==0)
	{
		em_loop_seed(campaign,event,steps,time_grid,max_steps,cut);
	}

else
	{
		/*Iteramos sobre el numero de pasos*/
		for(int i=1; i<=steps; i++)
			{
				cout << "Number of steps: " << i << endl;
				em_loop_seed(campaign,event,i,time_grid,max_steps,cut);
			}
	}

}

void em_loop_steps_update(string campaign,int event,int steps,int time_grid, int ndet, int max_steps, string cut, string physic_list, string scale_factor, string neufield_type){

/*Criterio de stop*/
if(steps==0)
	{
		em_loop_seed_update(campaign,event,steps,time_grid,max_steps,cut,physic_list,scale_factor,neufield_type);
	}

else
	{
		/*Iteramos sobre el numero de pasos*/
		for(int i=1; i<=steps; i++)
			{
				cout << "Number of steps: " << i << endl;
				em_loop_seed_update(campaign,event,i,time_grid,max_steps,cut,physic_list,scale_factor,neufield_type);
			}
	}

}

/*Funcion que itera la funcion em_loop_steps() sobre el numero de eventos*/
//~ void em_loop_events(string campaign,int min_event, int max_event,int steps,int time_grid, int ndet){
void em_loop_events(string campaign,int steps,int time_grid, int ndet, int max_steps, string cut, string physic_list, string scale_factor, string neufield_type){

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

//~ for(int i=194; i<=194; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }

/*************************/

//~ for(int i=21; i<=21; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet);
    //~ }

/*********LCO****************/

/*15 mim*/
for(int i=1; i<=289; i++)
	{
		cout << "Number of event: " << i << endl;
		em_loop_steps_update(campaign,i,steps,time_grid,ndet,max_steps,cut,physic_list,scale_factor,neufield_type);
    }
/*60 mim*/
//~ for(int i=1; i<=72; i++)
	//~ {
		//~ cout << "Number of event: " << i << endl;
		//~ em_loop_steps_update(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }


/************Maricunga**********/
//15 min timegrid gives 342 events (0,341)
//~ for(int i=1; i<=31; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,cut);
    //~ }

//~ for(int i=33; i<=44; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }
    
//~ for(int i=46; i<=342; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }

//~ for(int i=32; i<=32; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }
    
//~ for(int i=290; i<=342; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps_update(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }



/***********RetenDesierto**********/

//~ for(int i=1; i<=271; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }
/***********Chaquipilta**********/

//~ for(int i=1; i<=838; i++)
//~ for(int i=1; i<=100; i++)
//~ for(int i=1; i<=837; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }

/***********SanPedrodeAtacama**********/

//~ for(int i=1; i<=386; i++)
	//~ {
		 //~ cout << "Number of event: " << i << endl;
		 //~ em_loop_steps_update(campaign,i,steps,time_grid,ndet,max_steps,cut);
    //~ }

}

void em_routine(string campaign){
/*Generamos los archivos .root*/
em_loop_steps(campaign,210,20,15,11,1000,"cut1"); //lluvia
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
		//~ deconv_flux_multiplot_by_seed(campaign,event,max_steps,15,11,i,"Lethargy");
		deconv_flux_multiplot_by_seed(campaign,event,max_steps,15,11,i,"Lethargy","QGSP_BERT");
    }
}

/*Funcion que grafica los espectros de distintos eventos para distintos pasos para el mismo valor de semilla*/
void em_routine_plot_events(string campaign, int max_event, int max_steps, int time_grid, int ndet, int bin_seed){

/*Iteramos sobre el numero eventos*/
for(int i=1; i<=max_event; i++)
	{
		cout << "Number of bin seed: " << i << endl;
		//~ deconv_flux_multiplot_by_seed(210,max_steps,15,11,i,"Lethargy");
		//~ deconv_flux_multiplot_by_seed(campaign,i,max_steps,time_grid,ndet,bin_seed,"Lethargy");
		deconv_flux_multiplot_by_seed(campaign,i,max_steps,time_grid,ndet,bin_seed,"Lethargy","QGSP_BERT");
    }
}

void root_test_multithread(){

// RDataFrame guarantees that different threads will invoke the expression with different slot numbers - slot numbers will range from zero to ROOT::GetThreadPoolSize()-1.
//~ ROOT::EnableImplicitMT(); // Enable Multiple threads in RDataFrame
// To see how many threads are available to your program:
auto poolSize = ROOT::GetThreadPoolSize(); // numero de nucleos del pc
std::cout << "Pool size = " << poolSize << std::endl; 

}

void em_event_step(int event, int det)
	{
		
		em_loop_steps("Chapiquilta",event,20,15,det,20,"cut1");
		//~ deconv_flux_multiplot_by_seed("Chapiquilta",event,20,15,det,20,"Lethargy");
		deconv_flux_multiplot_by_seed("Chapiquilta",event,20,15,det,20,"Lethargy","QGSP_BERT");
		//~ em_loop_seed_plot_template("Chapiquilta",event,20,15,det);

	}

/*EM para 1 solo evento*/
void em_event_step_update(int event, int det)
	{

		//~ em_loop_steps_update("Maricunga",event,20,15,det,20,"cut1");
		//~ deconv_flux_multiplot_by_seed("Maricunga",event,20,15,det,20,"Lethargy");
		//em_loop_seed_plot_template("Maricunga",event,20,15,det);

		//~ em_loop_steps_update("LCO",event,20,15,det,20,"cut1");
		//~ deconv_flux_multiplot_by_seed("LCO",event,20,15,det,20,"Lethargy");
		//~ em_loop_seed_plot_template("Chapiquilta",event,20,15,det);
		
		//~ em_loop_steps_update("Chapiquilta",event,30,15,det,30,"cut1");
		//~ deconv_flux_multiplot_by_seed("Chapiquilta",event,30,15,det,30,"Lethargy");
		//~ em_loop_seed_plot_template("Chapiquilta",event,30,15,det);

		//~ em_loop_steps_update("SanPedrodeAtacama",event,20,15,det,20,"cut1");
		//~ em_loop_steps_update("SanPedrodeAtacama",event,100,15,det,20,"cut1");
		//~ em_loop_steps_update("SanPedrodeAtacama",event,100,15,det,20,"cut1");
		//~ em_loop_steps_update("SanPedrodeAtacama",event,100,15,det,20,"cut1","QGSP_BERT");

		//~ deconv_flux_multiplot_by_seed("SanPedrodeAtacama",event,20,15,det,20,"Lethargy");
		//~ em_loop_seed_plot_template("SanPedrodeAtacama",event,20,15,det);

		/**LCO PRUEBA CON NUEVA LIBRERIA FISICA PARA LAS SIMULACIONES MC de LAS FUNCIONES RESPUESTA, SIN CRITERIO DE STOP y 1000 pasos maximo**/
		em_loop_steps_update("LCO",event,1000,15,det,1000,"cut1","FTFP_BERT","ws","ISO");

		

	}


void em_and_knee_loop_event_list_from_singlefile_update(
    const std::string& campaign,
    int timegrid,
    int max_steps,
    int ndet,
    const std::string& physic_list,
    const std::string& scale_factor
){
	int event_min = 1;
	int event_max  = 289;
	/**EM**/
    //~ for(int ev = event_min; ev <= event_max; ++ev){
        //~ std::cout << "\n==== EM EVENT " << ev << " ====\n";
        //~ deconv_em_event_write_singlefile(campaign,ev,timegrid,max_steps,"cut1",physic_list,scale_factor,0);
    //~ }

	/*graficos*/
       for(int ev = event_min; ev <= event_max; ++ev){
        std::cout << "\n==== KNEE EVENT " << ev << " ====\n";
        em_knee_and_chi2stop_from_singlefile_update(campaign,ev,timegrid,max_steps, ndet,physic_list, scale_factor);
    }
}
