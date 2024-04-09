#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>


using namespace std;
using namespace ROOT::VecOps; // para definir vectores como  RVec<double>>("vecCol");

string uncertainty_value(double value, double error_value)
{
ostringstream stream_uncert,stream_uncert_round;
string str_stream_uncert, str_stream_uncert_round;

			//~ int exponent = (error_value/value == 0) ? 0 : 1 + (int)std::floor(std::log10(std::fabs(error_value/value)));
			int exponent_ratio = (int)std::floor(std::log10(std::fabs(error_value/value)));
			int exponent_value = (int)std::floor(std::log10(std::fabs(value)));
			int exponent_error_value = (int)std::floor(std::log10(std::fabs(error_value)));
			cout <<"exponent_ratio " << exponent_ratio << endl;
			cout <<"exponent_value " << exponent_value << endl;
			cout <<"exponent_error_value " << exponent_error_value << endl;

			int diff_exp = exponent_value - exponent_error_value;
			
			int subs;
			if(exponent_ratio<0 && exponent_value<0)
				{
					subs = fabs(exponent_ratio)+fabs(exponent_value);
				}
			if(exponent_ratio<0 && exponent_value<0 & exponent_ratio==exponent_value)
				{
					subs = fabs(exponent_error_value);
				}
			if(exponent_ratio<0 && exponent_value>0)
				{
					subs = fabs(exponent_value)-fabs(exponent_ratio);
				}
			if(exponent_ratio<0 && exponent_value<0 && exponent_error_value==exponent_value)
				{
					subs = fabs(exponent_error_value)-1;
				}
			if(exponent_error_value<0 && exponent_value<0 && (diff_exp==1))
				{
					subs= fabs(exponent_error_value);
				}
			if(exponent_error_value<0 && exponent_value<0 && (diff_exp==0))
				{
					subs= fabs(exponent_error_value)+1;
				}
			
			double uncertainty_value = error_value*pow(10,subs);
			double uncertainty_value_round = round(error_value*pow(10,subs));
			
			stream_uncert << uncertainty_value;
			stream_uncert_round << uncertainty_value_round;

	str_stream_uncert = stream_uncert.str();
	str_stream_uncert_round = stream_uncert_round.str();
	cout <<"str_stream_uncert " << str_stream_uncert << endl;
	cout <<"str_stream_uncert_round " << str_stream_uncert_round << endl;

    // Find the position of the first . character
    //~ size_t lenght = str_stream_uncert.find_first_of(".");
    //~ cout << lenght << endl;

    // If startPos is string::npos, it means there are no non-zero digits
    // if (startPos == std::string::npos) {
        //// Return "0" as the significant number
        // return "0";
	// }

	// Extract and return the significant number
    //~ return  str_stream_uncert.substr(0,lenght);
     return str_stream_uncert_round;
}




vector<double> bubbleSort( vector<double> vec, int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++)
	 
			// Last i elements are already
			// in place
			for (j = 0; j < n - i - 1; j++)
				if (vec[j] > vec[j + 1])
					swap(vec[j], vec[j + 1]);

		return vec;
	}

void gauss_random_cr(){

int N = 500000;

TCanvas *canvas_gaus = new TCanvas("Counting rate sampling MC","Counting rate sampling MC");
canvas_gaus->Divide(2,1);

TH1D* gaus_hist = new TH1D("gaus_hist","Counting rate sampling MC",N,0,500000);
for(int k=1;k<=N;k++)
	{
		double cr_gauss = gRandom->Gaus(600/(15*60.),sqrt(600)/(15*60.));
		gaus_hist->SetBinContent(k+1,cr_gauss);
	}

canvas_gaus->cd(1);
//~ TLatex *info_1 = new TLatex(0.58,0.35,"#bf{f_G(n_{i},\sigma_{i})}");
//~ TLatex *info_2 = new TLatex(0.58,0.20,"#bf{n_{i},#frac{#sqrt(n_{i}}{T}}");
//~ l_ndet_->SetNDC();
//~ l_ndet->SetTextSize(0.04);
gaus_hist->Draw("HIST");

vector<Double_t> fit_parameters;

canvas_gaus->cd(2);	
TH1D* prjY = new TH1D("prjY", "Counting rate distribution", N, 0 ,1);
prjY->GetXaxis()->SetTitle("#bf{n_{i}} /s");
prjY->GetYaxis()->SetTitle("#bf{P(n_{i})}");
prjY->GetXaxis()->SetTitleSize(0.03);
prjY->GetYaxis()->SetTitleSize(0.03);
//~ prjY->GetXaxis()->SetTitleOffset(0.8);
prjY->GetXaxis()->SetLabelSize(0.03);
prjY->GetYaxis()->SetLabelSize(0.03);
		
prjY->SetBins(10000, 0.5, 0.85); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
for (int i = 0; i <N; i++)
	{
		prjY->Fill(gaus_hist->GetBinContent(i+1));
			//~ prjY->SetBinContent(i,Ch_hist->GetBinContent(i));
	}

/*FIT & get parameters*/
TF1* fit = new TF1("fit","gaus");
prjY->Fit(fit);



double p1 = fit->GetParameter(1); //obtenemos el mean
double p2 = fit->GetParameter(2); //obtenemos el sigma

fit_parameters.push_back(p1);
fit_parameters.push_back(p2);
	
cout << "Mean: " << fit_parameters[0] << endl;
cout << "Sigma: " << fit_parameters[1] << endl;

//~ return fit_parameters;

}

void plot_em_mc(string campaign){

ROOT::EnableImplicitMT(); 
//~ TFile *em_mc_loop = new TFile("./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_211_steps_0_timegrid_15_ndet_11_MC_stop_1000_it.root");
string file_name = "./deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_LCO_event_211_steps_0_timegrid_15_ndet_11_MC_stop_5e05_it.root";
TFile *em_mc_loop = new TFile(file_name.c_str());
ROOT::RDataFrame df_em_mc("em_loop_tree", em_mc_loop);

auto df_cut_steps = df_em_mc.Filter("em_it<30.");
auto deconv_matrix = df_em_mc.Take<vector<double>>("deconv_vec").GetValue();
auto deconv_matrix_filter = df_cut_steps.Take<vector<double>>("deconv_vec").GetValue();

cout << "deconv_matrix size: " << deconv_matrix.size() << endl;
cout << "deconv_matrix_filter size: " << deconv_matrix_filter.size() << endl;

TCanvas *canvas_gaus = new TCanvas("gaus","gaus");
canvas_gaus->Divide(2,2);

vector<double> deconv_bin;
for(int j=0;j< deconv_matrix.size();j++)
	{
		auto value_bin1 = deconv_matrix[j][0];
		deconv_bin.push_back(value_bin1);
	}
cout << "deconv_bin " << deconv_bin.size() << endl;
vector<double> deconv_bin_sort = bubbleSort(deconv_bin,deconv_bin.size());
cout << "deconv_bin min value: " << deconv_bin_sort[0] << endl;
cout << "deconv_bin max value: " << deconv_bin_sort[deconv_bin.size()-1] << endl;


TH1D* deconv_hist_bin = new TH1D("deconv_hist","deconv_hist",deconv_bin.size(),0,1000);
for(int i=0;i<deconv_bin.size();i++)
	{
		deconv_hist_bin->SetBinContent(i+1,deconv_bin[i]);
	}

canvas_gaus->cd(1);
deconv_hist_bin->Draw();

vector<Double_t> fit_parameters;

canvas_gaus->cd(2);	
TH1D* prjY = new TH1D("prjY", "prjY", deconv_bin.size(), 0 ,1.0e-06);
//~ TH1D* prjY = new TH1D("prjY", "prjY", deconv_bin.size(), 0 ,1);
		
//~ prjY->SetBins(deconv_bin.size(), 0, deconv_bin_sort[deconv_bin.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
prjY->SetBins(100, 0, 1.0e-06); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
for (int i = 0; i <deconv_bin.size(); i++)
	{
		prjY->Fill(deconv_hist_bin->GetBinContent(i+1));
	}

/*FIT & get parameters*/
TF1* fit = new TF1("fit","gaus");
prjY->Fit(fit);

double p1 = fit->GetParameter(1); //obtenemos el mean
double p2 = fit->GetParameter(2); //obtenemos el sigma

fit_parameters.push_back(p1);
fit_parameters.push_back(p2);
	
cout << "Mean: " << fit_parameters[0] << endl;
cout << "Sigma: " << fit_parameters[1] << endl;


vector<double> deconv_bin_filter;
for(int j=0;j< deconv_matrix_filter.size();j++)
	{
		auto value_bin1 = deconv_matrix_filter[j][0];
		deconv_bin_filter.push_back(value_bin1);
	}
cout << "deconv_bin_filter " << deconv_bin_filter.size() << endl;
vector<double> deconv_bin_sort_filter = bubbleSort(deconv_bin_filter,deconv_bin_filter.size());
cout << "deconv_bin min value: " << deconv_bin_sort_filter[0] << endl;
cout << "deconv_bin max value: " << deconv_bin_sort_filter[deconv_bin_filter.size()-1] << endl;


TH1D* deconv_hist_bin_filter = new TH1D("deconv_hist_filter","deconv_hist_filter",deconv_bin_filter.size(),0,deconv_bin_filter.size());
for(int i=0;i<deconv_bin_filter.size();i++)
	{
		deconv_hist_bin_filter->SetBinContent(i+1,deconv_bin_filter[i]);	
	}

canvas_gaus->cd(3);
deconv_hist_bin_filter->Draw();


canvas_gaus->cd(4);	
TH1D* prjY_filter = new TH1D("prjY_filter", "prjY_filter", deconv_bin_filter.size(), 0 ,deconv_bin_sort_filter[deconv_bin_filter.size()-1]);
//~ TH1D* prjY = new TH1D("prjY", "prjY", deconv_bin.size(), 0 ,1);
		
//~ prjY->SetBins(deconv_bin.size(), 0, deconv_bin_sort[deconv_bin.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
prjY_filter->SetBins(100, 0, deconv_bin_sort_filter[deconv_bin_filter.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
for (int i = 0; i <deconv_bin_filter.size(); i++)
	{
		prjY_filter->Fill(deconv_hist_bin_filter->GetBinContent(i+1));
	}

/*FIT & get parameters*/
TF1* fit_filter = new TF1("fit_filter","gaus");
prjY_filter->Fit(fit_filter);

double p1_f = fit_filter->GetParameter(1); //obtenemos el mean
double p2_f = fit_filter->GetParameter(2); //obtenemos el sigma

vector<Double_t> fit_parameters_f;

fit_parameters_f.push_back(p1_f);
fit_parameters_f.push_back(p2_f);
	
cout << "Mean: " << fit_parameters_f[0] << endl;
cout << "Sigma: " << fit_parameters_f[1] << endl;


}

void em_mc_graph(string campaign,int event, int timegrid, int step_filter, int bin_energy){

auto start = std::chrono::system_clock::now();


vector<double> fitGaussParam;

ostringstream  stream_event, stream_timegrid, stream_binenergy, stream_binenergy_name, stream_step_filter;
stream_event << event;
stream_timegrid << timegrid; 
stream_binenergy << bin_energy-1;
stream_binenergy_name << bin_energy;
stream_step_filter << step_filter;
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_binenergy = stream_binenergy.str();
string str_stream_binenergy_name = stream_binenergy_name.str();
string str_stream_step_filter = stream_step_filter.str();

//~ ROOT::EnableImplicitMT(); 
//~ TFile *em_mc_loop = new TFile("./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_211_steps_0_timegrid_15_ndet_11_MC_stop_1000_it.root");
//~ string file_name_MC = "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_"+str_stream_event+"_steps_0_timegrid_15_ndet_11_MC_stop_5e05_it.root";
string file_name_MC = "./deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_LCO_event_"+str_stream_event+"_steps_0_timegrid_"+str_stream_timegrid+"_ndet_11_MC_stop.root";
//~ string file_name_MC = "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_"+str_stream_event+"_steps_0_timegrid_15_ndet_11_MC_stop_2e04_it.root";
TFile *em_mc_loop = new TFile(file_name_MC.c_str());
ROOT::RDataFrame df_em_mc("em_loop_tree", em_mc_loop);

/*Matriz de flujo deconv*/
auto deconv_matrix = df_em_mc.Take<vector<double>>("deconv_vec").GetValue();
/*Matriz de flujo deconv filtrado para los pasos en que el algoritmo EM sea menor igual a 9.*/
//~ auto df_cut_steps = df_em_mc.Filter("em_it<=9."); //EVENT 211
//~ auto df_cut_steps = df_em_mc.Filter("em_it<=15. & Chi2<11. "); //EVENT 211

double step_event = step_filter;
auto lambda_cut_step = [&](double &em_it){
	if(em_it<=step_event)
		{
			return true;
		}
	else{return false;}
	
};

double chi2_event = 11.;
auto lambda_cut_chi2 = [&](double &Chi2){
	if(Chi2<chi2_event)
		{
			return true;
		}
	else{return false;}
	
};

//~ auto df_cut_steps = df_em_mc.Filter("em_it<=9."); // EVENT 211
auto df_cut_steps = df_em_mc.Filter(lambda_cut_step,{"em_it"}).Filter(lambda_cut_chi2,{"Chi2"}); // EVENT 211
//~ auto df_cut_steps = df_em_mc.Filter(lambda_cut_step,{"em_it"});
//~ auto df_cut_steps = df_em_mc.Filter("Chi2<11.");  
//~ auto df_cut_steps = df_em_mc.Filter("em_it<1001.");
auto deconv_matrix_filter = df_cut_steps.Take<vector<double>>("deconv_vec").GetValue();

/*Valor promedio del deconv_vec bin energy j*/
//~ auto mean_val_deconv_bin1 = df_em_bin1.Mean("deconv_bin_1").GetValue();

string deconv_vec_bin_j = "deconv_vec["+str_stream_binenergy+"]";
string deconv_vec_branchname = "deconv_bin_"+str_stream_binenergy_name;

//~ auto mean_val_deconv_bin_j = df_em_mc.Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Filter("em_it<=16.").Mean(deconv_vec_branchname.c_str()).GetValue();
//~ /*STD del deconv_vec bin1*/
//~ auto std_val_deconv_bin_j = df_em_mc.Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Filter("em_it<=16.").StdDev(deconv_vec_branchname.c_str()).GetValue();

//~ auto mean_val_deconv_bin_j = df_em_mc.Filter("em_it<=9.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Mean(deconv_vec_branchname.c_str()).GetValue();
auto mean_val_deconv_bin_j = df_em_mc.Filter("Chi2<11.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Mean(deconv_vec_branchname.c_str()).GetValue();
/*STD del deconv_vec bin1*/
//~ auto std_val_deconv_bin_j = df_em_mc.Filter("em_it<=9.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).StdDev(deconv_vec_branchname.c_str()).GetValue();
auto std_val_deconv_bin_j = df_em_mc.Filter("Chi2<11.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).StdDev(deconv_vec_branchname.c_str()).GetValue();

cout << "Mean deconv bin 1: " << mean_val_deconv_bin_j << endl;
cout << "STD deconv bin 1: " << std_val_deconv_bin_j << endl;


cout << "deconv_matrix size: " << deconv_matrix.size() << endl;
cout << "deconv_matrix_filter size: " << deconv_matrix_filter.size() << endl;

TCanvas *canvas_gaus = new TCanvas("gaus","gaus",1920,1080);
gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas 
canvas_gaus->Divide(2,2);

vector<double> deconv_bin;
for(int j=0;j< deconv_matrix.size();j++)
	{
		auto value_bin1 = deconv_matrix[j][bin_energy-1];
		deconv_bin.push_back(value_bin1);
	}
cout << "deconv_bin " << deconv_bin.size() << endl;
//~ vector<double> deconv_bin_sort = bubbleSort(deconv_bin,deconv_bin.size());
//~ cout << "deconv_bin min value: " << deconv_bin_sort[0] << endl;
//~ cout << "deconv_bin max value: " << deconv_bin_sort[deconv_bin.size()-1] << endl;


string deconv_hist_name = "deconv_hist_MC_bin_energy_"+str_stream_binenergy_name+"_event_"+str_stream_event;
TH1D* deconv_hist_bin = new TH1D( deconv_hist_name.c_str(), deconv_hist_name.c_str(),deconv_bin.size(),0,500000);
for(int i=0;i<deconv_bin.size();i++)
	{
		deconv_hist_bin->SetBinContent(i+1,deconv_bin[i]);
	}

canvas_gaus->cd(1);
gStyle->SetOptStat();
deconv_hist_bin->Draw();

vector<Double_t> fit_parameters;

canvas_gaus->cd(2);
//~ double flux_value_upper_limit = mean_val_deconv_bin_j+15.*std_val_deconv_bin_j;
double flux_value_upper_limit = mean_val_deconv_bin_j+4.*std_val_deconv_bin_j;
cout << "flux_value_upper_limit_prjY: " << flux_value_upper_limit << endl;
//~ TH1D* prjY = new TH1D("prjY", "prjY", deconv_bin.size(), 0 ,1.2e-06);

string deconv_pjY_name = "prjY_MC_bin_energy_"+str_stream_binenergy_name+"_event_"+str_stream_event;
TH1D* prjY = new TH1D(deconv_pjY_name.c_str(),deconv_pjY_name.c_str(), deconv_bin.size(), 4e-06 ,flux_value_upper_limit);
//~ prjY->SetBins(deconv_bin.size(), 0, deconv_bin_sort[deconv_bin.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
//~ prjY->SetBins(1000, 0, 1.2e-06); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
//~ prjY->SetBins(10000, 4e-06, flux_value_upper_limit);
prjY->SetBins(10000, 4e-06, flux_value_upper_limit);
for (int i = 0; i <deconv_bin.size(); i++)
	{
		prjY->Fill(deconv_hist_bin->GetBinContent(i+1));
	}

/*FIT & get parameters*/

TF1* fit = new TF1("fit","gaus");
prjY->Fit(fit);

double p1 = fit->GetParameter(1); //obtenemos el mean
double p2 = fit->GetParameter(2); //obtenemos el sigma

fit_parameters.push_back(p1);
fit_parameters.push_back(p2);
	
cout << "Mean: " << fit_parameters[0] << endl;
cout << "Sigma: " << fit_parameters[1] << endl;
cout << "%Sigma: " << fit_parameters[1]*100/fit_parameters[0]  << endl;

gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()

TPaveStats *st = (TPaveStats*)prjY->FindObject("stats");
st->SetX1NDC(0.689394); //new x start position
st->SetY1NDC(0.649759); //new x end position
st->SetX2NDC(0.979122); //new x start position
st->SetY2NDC(0.935987); //new x end position
//~ gStyle->SetOptStat(11);
gStyle->SetOptStat(11);
gStyle->SetOptFit();



/***********************************************************************/
/***********************************************************************/

vector<double> deconv_bin_filter;
for(int j=0;j< deconv_matrix_filter.size();j++)
	{
		auto value_bin1 = deconv_matrix_filter[j][bin_energy-1];
		deconv_bin_filter.push_back(value_bin1);
	}
cout << "deconv_bin_filter " << deconv_bin_filter.size() << endl;
//~ vector<double> deconv_bin_sort_filter = bubbleSort(deconv_bin_filter,deconv_bin_filter.size());
//~ cout << "deconv_bin min value: " << deconv_bin_sort_filter[0] << endl;
//~ cout << "deconv_bin max value: " << deconv_bin_sort_filter[deconv_bin_filter.size()-1] << endl;

string deconv_hist_name_filter = "deconv_hist_MC_bin_energy_"+str_stream_binenergy_name+"_filter_em_it<="+str_stream_step_filter+"_event_"+str_stream_event;
TH1D* deconv_hist_bin_filter = new TH1D(deconv_hist_name_filter.c_str(),deconv_hist_name_filter.c_str(),deconv_bin_filter.size(),0,deconv_bin_filter.size());
for(int i=0;i<deconv_bin_filter.size();i++)
	{
		deconv_hist_bin_filter->SetBinContent(i+1,deconv_bin_filter[i]);	
	}

canvas_gaus->cd(3);
gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gStyle->SetOptStat();
deconv_hist_bin_filter->Draw();

canvas_gaus->cd(4);	
//~ TH1D* prjY_filter = new TH1D("prjY_filter", "prjY_filter", deconv_bin_filter.size(), 0 ,deconv_bin_sort_filter[deconv_bin_filter.size()-1]);
//~ double flux_value_upper_limit_prjY = mean_val_deconv_bin_j+15.*std_val_deconv_bin_j;
double flux_value_upper_limit_prjY = mean_val_deconv_bin_j+4.*std_val_deconv_bin_j;
//~ TH1D* prjY_filter = new TH1D("prjY_filter em_it<=9", "prjY_filter em_it<=9", deconv_bin_filter.size(), 0.4e-06,1.1e-06);

string deconv_pjY_name_filter = "prjY_MC_bin_energy_"+str_stream_binenergy_name+"_filter_em_it<="+str_stream_step_filter+"_event_"+str_stream_event;
TH1D* prjY_filter = new TH1D(deconv_pjY_name_filter.c_str(), deconv_pjY_name_filter.c_str(), deconv_bin_filter.size(), 0.,flux_value_upper_limit_prjY);		
//~ prjY->SetBins(deconv_bin.size(), 0, deconv_bin_sort[deconv_bin.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
//~ prjY_filter->SetBins(100, 0, deconv_bin_sort_filter[deconv_bin_filter.size()-1]); // corresponde al rango donde se encuentra el offset en el eje Y de una senial pulsada
//~ prjY_filter->SetBins(1000, 0.4e-06, 1.1e-06);
//~ prjY_filter->SetBins(1000, 0., flux_value_upper_limit_prjY);
prjY_filter->SetBins(1000, 0., flux_value_upper_limit_prjY);
for (int i = 0; i <deconv_bin_filter.size(); i++)
	{
		prjY_filter->Fill(deconv_hist_bin_filter->GetBinContent(i+1));
	}

/*FIT & get parameters*/

/*Asymetric Gaussian fit*/
//~ int binmax = prjY->GetMaximumBin();
//~ double x_max = prjY->GetXaxis()->GetBinCenter(binmax);
//~ // for(int i=1;i<6;i++)
	//~ // {
	//~ TF1* f = new TF1("f","2.*gaus(x-[3],[0],0,[1])*ROOT::Math::normal_cdf([2]*(x-[3]),1,0)",-1.,1.0);
	//~ f->SetParameters(x_max,std_val_deconv_bin_j,4,mean_val_deconv_bin_j);
	//~ // f->Draw();
	//~ prjY_filter->Fit(f);
	//~ // }
//~ double chi2 = f->GetChisquare();
//~ double NDF =  f->GetNDF();

//~ double p1_f = f->GetParameter(1); //obtenemos el mean
//~ double p2_f = f->GetParameter(2); //obtenemos el sigma


/*Gaussian fit*/
TF1* fit_filter = new TF1("fit_filter","gaus");
prjY_filter->Fit(fit_filter);
double p1_f = fit_filter->GetParameter(1); //obtenemos el mean
double p2_f = fit_filter->GetParameter(2); //obtenemos el sigma

vector<Double_t> fit_parameters_f;
fit_parameters_f.push_back(p1_f);
fit_parameters_f.push_back(p2_f);
	
cout << "Mean: " << fit_parameters_f[0] << endl;
cout << "Sigma: " << fit_parameters_f[1] << endl;
cout << "%Sigma: " << fit_parameters_f[1]*100/fit_parameters_f[0]  << endl;

gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()

TPaveStats *st_filter = (TPaveStats*)prjY_filter->FindObject("stats");
st_filter->SetX1NDC(0.689394); //new x start position
st_filter->SetY1NDC(0.649759); //new x end position
st_filter->SetX2NDC(0.979122); //new x start position
st_filter->SetY2NDC(0.935987); //new x end position
gStyle->SetOptStat(11);
gStyle->SetOptFit();

fitGaussParam.push_back(p1_f);
fitGaussParam.push_back(p2_f);

canvas_gaus->Draw();

gStyle->SetImageScaling(3.); //works only in bach mode
//~ canvas_gaus->SaveAs(("./deconv_data_pdf/EM_MC_fitting/event_41_fitting/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_bin_energy_"+str_stream_binenergy_name +".pdf").c_str());
//~ canvas_gaus->SaveAs(("./deconv_data_pdf/EM_MC_fitting/event_41_fitting/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_bin_energy_"+str_stream_binenergy_name +".png").c_str());

auto end = std::chrono::system_clock::now();
//~ std::chrono::duration<float> duration = end - start; //seconds
std::chrono::duration<float,std::ratio<3600>> duration = end - start; //hours
cout << duration.count() << "hr " << endl;
 
//~ return fitGaussParam;



}



vector<double> em_mc_vec(string campaign, int event, int timegrid, int ndet, int step_filter, int bin_energy){

//~ ROOT::Math::MinimizerOptions::SetDefaultMinimizer(“Minuit2”);

vector<double> fitGaussParam;

ostringstream  stream_event, stream_timegrid, stream_ndet, stream_binenergy, stream_binenergy_name;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
stream_binenergy << bin_energy-1;
stream_binenergy_name << bin_energy;
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_binenergy = stream_binenergy.str();
string str_stream_binenergy_name = stream_binenergy_name.str();
string str_stream_ndet = stream_ndet.str();

//~ ROOT::EnableImplicitMT(); 
//~ TFile *em_mc_loop = new TFile("./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_211_steps_0_timegrid_15_ndet_11_MC_stop_1000_it.root");
//~ string file_name_MC = "./deconv_data_rootfile/EM_MC_stop/EM_unfolding_loop_campaign_LCO_event_"+str_stream_event+"_steps_0_timegrid_15_ndet_11_MC_stop_5e05_it.root";
string file_name_MC = "./deconv_data_rootfile/EM_MC_stop/"+campaign+"/EM_unfolding_loop_campaign_LCO_event_"+str_stream_event+"_steps_0_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_MC_stop.root";
TFile *em_mc_loop = new TFile(file_name_MC.c_str());
ROOT::RDataFrame df_em_mc("em_loop_tree", em_mc_loop);

/*Matriz de flujo deconv*/
auto deconv_matrix = df_em_mc.Take<vector<double>>("deconv_vec").GetValue();
cout << "deconv_matrix[0] size: " << deconv_matrix[0].size() << endl;
/*Matriz de flujo deconv filtrado para los pasos en que el algoritmo EM sea menor igual a 9.*/

//~ double step_event = 9.;
double step_event = step_filter;
auto lambda_cut_step = [&](double &em_it){
	if(em_it<=step_event)
		{
			return true;
		}
	else{return false;}
	
};

double chi2_event = 11.;
auto lambda_cut_chi2 = [&](double &Chi2){
	if(Chi2<chi2_event)
		{
			return true;
		}
	else{return false;}
	
};

//~ auto df_cut_steps = df_em_mc.Filter("em_it<=9."); // EVENT 211
//~ auto df_cut_steps = df_em_mc.Filter(lambda_cut_step,{"em_it"}); // EVENT 211
auto df_cut_steps = df_em_mc.Filter(lambda_cut_step,{"em_it"}).Filter(lambda_cut_chi2,{"Chi2"}); 
//~ auto df_cut_steps = df_em_mc.Filter("em_it<=16."); // EVENT 41
//~ auto df_cut_steps = df_em_mc.Filter("Chi2<11.");
//~ auto df_cut_steps = df_em_mc.Filter("em_it<1001.");
auto deconv_matrix_filter = df_cut_steps.Take<vector<double>>("deconv_vec").GetValue();
cout << "deconv_matrix_filter[0] size: " << deconv_matrix_filter[0].size() << endl;

/*Valor promedio del deconv_vec bin energy j*/
//~ auto mean_val_deconv_bin1 = df_em_bin1.Mean("deconv_bin_1").GetValue();

string deconv_vec_bin_j = "deconv_vec["+str_stream_binenergy+"]";
cout << " deconv_vec_bin_j: " << deconv_vec_bin_j << endl;
string deconv_vec_branchname = "deconv_bin_"+str_stream_binenergy_name;


//~ auto mean_val_deconv_bin_j = df_em_mc.Filter("em_it<=9.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Mean(deconv_vec_branchname.c_str()).GetValue();
//~ auto mean_val_deconv_bin_j = df_em_mc.Filter("Chi2<11.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Mean(deconv_vec_branchname.c_str()).GetValue();
auto mean_val_deconv_bin_j = df_em_mc.Filter(lambda_cut_chi2,{"Chi2"}).Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).Mean(deconv_vec_branchname.c_str()).GetValue();
/*STD del deconv_vec bin1*/
//~ auto std_val_deconv_bin_j = df_em_mc.Filter("em_it<=9.").Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).StdDev(deconv_vec_branchname.c_str()).GetValue();
auto std_val_deconv_bin_j = df_em_mc.Filter(lambda_cut_chi2,{"Chi2"}).Define(deconv_vec_branchname.c_str(),deconv_vec_bin_j.c_str()).StdDev(deconv_vec_branchname.c_str()).GetValue();

cout << "Mean deconv bin 1: " << mean_val_deconv_bin_j << endl;
cout << "STD deconv bin 1: " << std_val_deconv_bin_j << endl;


cout << "deconv_matrix size: " << deconv_matrix.size() << endl;
cout << "deconv_matrix_filter size: " << deconv_matrix_filter.size() << endl;

vector<double> deconv_bin_filter;
for(int j=0;j<deconv_matrix_filter.size();j++)
//~ for(int j=0;j<1;j++)
	{
		//~ auto value_bin1 = deconv_matrix_filter[j][bin_energy-1];
		double value_bin1 = deconv_matrix_filter[j][bin_energy-1];
		//~ cout << " value_bin1: " << value_bin1 << endl;
		deconv_bin_filter.push_back(value_bin1);
	}
cout << "deconv_bin_filter " << deconv_bin_filter.size() << endl;

string deconv_hist_name_filter = "deconv_hist_MC_bin_energy_"+str_stream_binenergy_name+"_filter_em_it<=9"+"_event_"+str_stream_event;

TH1D* deconv_hist_bin_filter = new TH1D(deconv_hist_name_filter.c_str(),deconv_hist_name_filter.c_str(),deconv_bin_filter.size(),0,deconv_bin_filter.size());
for(int i=0;i<deconv_bin_filter.size();i++)
	{
		deconv_hist_bin_filter->SetBinContent(i+1,deconv_bin_filter[i]);
		//~ cout << " i " << i << "	deconv_bin_filter: " << deconv_bin_filter[i] << endl;
	}

cout << "deconv_hist_bin_filter bins: " << deconv_hist_bin_filter->GetNbinsX() << endl;

double flux_value_upper_limit_prjY = mean_val_deconv_bin_j+4.*std_val_deconv_bin_j;
cout << "flux_value_upper_limit_prjY: " << flux_value_upper_limit_prjY << endl;

string deconv_pjY_name_filter = "prjY_MC_bin_energy_"+str_stream_binenergy_name+"_filter_em_it<=9"+"_event_"+str_stream_event;
TH1D* prjY_filter = new TH1D(deconv_pjY_name_filter.c_str(), deconv_pjY_name_filter.c_str(), deconv_bin_filter.size(), 0.,flux_value_upper_limit_prjY);

prjY_filter->SetBins(1000, 0., flux_value_upper_limit_prjY);
for (int i = 0; i <deconv_bin_filter.size(); i++)
	{
		prjY_filter->Fill(deconv_hist_bin_filter->GetBinContent(i+1));
		//~ prjY_filter->SetBinContent(i+1,deconv_hist_bin_filter->GetBinContent(i+1));
	}

cout << "prjY_filter bins: " << prjY_filter->GetNbinsX() << endl;

/*FIT & get parameters*/
TF1* fit_filter = new TF1("fit_filter","gaus");
prjY_filter->Fit(fit_filter,"QN");

double p1_f = fit_filter->GetParameter(1); //obtenemos el mean
double p2_f = fit_filter->GetParameter(2); //obtenemos el sigma

	
cout << "Mean: " << p1_f << endl;
cout << "Sigma: " << p2_f << endl;
cout << "%Sigma: " << p2_f*100/p1_f << endl;

fitGaussParam.push_back(p1_f);
fitGaussParam.push_back(p2_f);

return fitGaussParam;


}

void fit_loop_bin_energy(string campaign, int event, int timegrid, int ndet, int step_filter){


auto start = std::chrono::system_clock::now();

ostringstream  stream_event, stream_timegrid, stream_ndet;
stream_event << event;
stream_timegrid << timegrid;
stream_ndet << ndet;
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

ROOT::RDataFrame df_fit_loop_i(130);
vector<vector<double>> fit_parameters_loop;

//~ auto poolSize = ROOT::GetThreadPoolSize(); //number of cores available
//~ ROOT::EnableImplicitMT(poolSize-2);
ROOT::EnableImplicitMT(6);

for(int i=1;i<=130;i++)
	{
	 cout <<"\r " << " Event " << event << " Energy bin: " << i << endl;
	 fit_parameters_loop.push_back(em_mc_vec(campaign,event,timegrid,ndet,step_filter,i));

	}

cout << " fit_parameters_loop size: " << fit_parameters_loop.size() << endl;

int rowid_mean = 0;
int rowid_sigma = 0;
int rowid_sigma_perc = 0;


auto df_fit_loop = df_fit_loop_i.Define("mean", [&]() {
									  auto vec_fit_parameters_loop_element =  fit_parameters_loop[rowid_mean];
									  double mean_value = vec_fit_parameters_loop_element[0] ;
									  rowid_mean++;
									  return mean_value;
									})
									.Define("sigma", [&]() {
									  auto vec_fit_parameters_loop_element =  fit_parameters_loop[rowid_sigma];
									  double sigma_value = vec_fit_parameters_loop_element[1] ;
									  rowid_sigma++;
									  return sigma_value;
									})
									.Define("sigma_perc", [&]() {
									  auto vec_fit_parameters_loop_element =  fit_parameters_loop[rowid_sigma_perc];

									  double mean_value = vec_fit_parameters_loop_element[0] ;
									  double sigma_value = vec_fit_parameters_loop_element[1] ;
									  
									  double sigma_perc_value = sigma_value*100/mean_value ;
									  rowid_sigma_perc++;
									  return sigma_perc_value;
									});


string df_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";

ROOT::DisableImplicitMT();
df_fit_loop.Snapshot("fit_loop_tree",df_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/

auto end = std::chrono::system_clock::now();
std::chrono::duration<float,std::ratio<60>> duration = end - start; //hours
cout << duration.count() << "min " << endl;

}

void loop_fit_over_events(int timegrid, int ndet)
{
	for(int i=1;i<22;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=23;i<46;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=49;i<70;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=71;i<84;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=85;i<111;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=112;i<240;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=241;i<273;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }
	for(int i=275;i<=289;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }	    	      
}

void loop_fit_over_events_range(int event_inf, int event_sup, int timegrid, int ndet)
{
	for(int i=event_inf;i<event_sup;i++)
		{
		 fit_loop_bin_energy("LCO",i,timegrid,ndet,20);
	    }	      
}

void plot_deconv_spectrum_with_error(string campaign, int event, int steps, int time_grid, int ndet, string flux_representation, int bin_seed){
ostringstream stream_steps, stream_event, stream_timegrid, stream_ndet, stream_bin_seed;
stream_steps << steps;
stream_event << event;
stream_timegrid << time_grid;
stream_ndet << ndet;
stream_bin_seed << bin_seed;
string str_stream_steps = stream_steps.str();
string str_stream_event = stream_event.str();
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();
string str_stream_bin_seed = stream_bin_seed.str();

int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> dE; /*Vector de anchos de energia*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de Energias*/

//~ string input_deconv_file= "./deconv_data_rootfile/EM_stop/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
string input_deconv_file= "./deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_15_ndet_"+str_stream_ndet+".root";
ROOT::RDataFrame df_event("em_loop_tree", input_deconv_file);

//~ string df_fit_mc_file = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_em_it_9.root";
//~ string df_fit_mc_file = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_5e05_it.root";
//~ string df_fit_mc_file = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_2e04_it.root";
//~ string df_fit_mc_file = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_2e04_it_filter.root";
//~ string df_fit_mc_file = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_backup.root";
string df_fit_mc_file = "./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".root";
ROOT::RDataFrame df_fit_file("fit_loop_tree", df_fit_mc_file);

// string deconv_vec_bin_seed = "deconv_vec["+sstr_stream_bin_seed+"]";

/*Deconv EM_STOP*/
auto deconv_matrix =   df_event.Take<vector<double>>("deconv_vec").GetValue();
auto deconv_vec = deconv_matrix[bin_seed-1];

/*Deconv EM_MC_STOP*/
auto deconv_mean_vec = df_fit_file.Take<double>("mean").GetValue();
auto deconv_sigma_vec = df_fit_file.Take<double>("sigma").GetValue();
auto deconv_sigma_perc_vec = df_fit_file.Take<double>("sigma_perc").GetValue();

cout << "deconv_vec size: " << deconv_vec.size() << endl;
cout << "deconv_sigma_vec size: " << deconv_sigma_vec.size() << endl;


//~ /**************Energy Bin********************/
//~ auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
//~ char delimiter = ',';
//~ char double_type ='D';
//~ std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
//~ auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
//~ seed_rdf.Snapshot("expacs_flux","./seed_expacs.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/
//~ /*Seleccionamos los datos del flujo semilla para LCO*/
//~ auto seed_ref_cut_LCO = seed_rdf;
//~ auto d_cut_entries = seed_ref_cut_LCO.Count().GetValue();
//~ /*Generamos el vector de flujo semilla*/
//~ auto df_seed_flux_vec = seed_ref_cut_LCO.Take<double>("flux_value").GetValue();
//~ Seed = df_seed_flux_vec;
//~ /*Numero de bines*/
//~ binnum = Seed.size()-1;
//~ /*Generamos el vector de bordes de bin*/
//~ auto df_binedges_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ //*Generamos el vector de ancho de energias*/
//~ auto df_dE_vec = seed_ref_cut_LCO.Take<double>("bin_width").GetValue();
//~ dE = df_dE_vec;
//~ // cout << "dE: df_dE_vec " << B.size() << endl;

//~ auto df_E_vec = seed_ref_cut_LCO.Take<double>("lower_edge_binvalue").GetValue();
//~ E = df_E_vec;

/****Cargamos el flujo semilla*****/

string str_stream_vwc_file;
string seed_flux_expacs_csv;

int bin_seed_new = bin_seed -1;
if(bin_seed_new<=150)
		{
			// Map: 0->0 (VWC 0%)
			// Map: 1->1 (VWC 0.2%)
			// Map: 150->150 (30%)
			ostringstream stream_vwc;
			stream_vwc << bin_seed_new;
			//~ string str_stream_vwc =stream_vwc.str();
			 str_stream_vwc_file =stream_vwc.str();

			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc_file+".csv";
				}
		}

if(bin_seed_new>150)
		{
			// Map: 151->32 (VWC 32%)
			// Map: 152->34 (vwc 34%)
			// Map: 185->100 ((vwc 100%)
			int vwc_old_51_seed = (bin_seed_new - 135)*2;

			ostringstream stream_vwc_old_51_seed;
			stream_vwc_old_51_seed << vwc_old_51_seed;
			string str_stream_vwc_old_51_seed = stream_vwc_old_51_seed.str();
			str_stream_vwc_file = str_stream_vwc_old_51_seed;
			
			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc_file+".csv";
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

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = df_binedges_vec.data();

/*VWC%*/
ostringstream stream_vwc ;
auto df_vwc_vec =  df_event.Take<double>("seed_bin_edgeds").GetValue();
double vwc_value = df_vwc_vec[bin_seed-1];
stream_vwc << vwc_value;
string str_stream_vwc = stream_vwc.str();

TCanvas *canvas_deconv_error = new TCanvas("deconv_err","deconv_err",1920,1080);
canvas_deconv_error->SetSupportGL(true);


/***Neutron flux in Integral form to obtain integral values***/

string name_hist_deconv_integral_repre = "Spectrum_"+campaign+"_Event_"+str_stream_event+"_Steps_"+str_stream_steps+"_BinSeed_"+str_stream_bin_seed+"(VWC "+str_stream_vwc+"%)_Integral";
TH1D* flux_deconv_integral = new TH1D(name_hist_deconv_integral_repre.c_str(),name_hist_deconv_integral_repre.c_str(), binnum , bins);
for (int i = 0; i <deconv_mean_vec.size()-1; i++)
	{
		double E_mid;
				E_mid = dE[i]; // integral flux
		/*Flux per unit lethargic dado que el flujo de entrada es el flujo integral, esto es, Flujo integral: deconv_vec[i]=Flux[i]*dE[i] */
		flux_deconv_integral->SetBinContent(i+1,(deconv_mean_vec[i]/dE[i])*E_mid); 
	}

/*Filling error*/
for (int i = 0; i <deconv_mean_vec.size()-1; i++)
	{
		double E_mid;
		E_mid = dE[i]; // integral flux
		//~ flux_deconv_2->SetBinError(i+1,(deconv_sigma_vec[i]/dE[i])*E_mid); 
		flux_deconv_integral->SetBinError(i+1,(deconv_sigma_vec[i]/dE[i])*E_mid); 
	}



/***************************************************************/

/*Hisotgram from EM_stop data*/
string name_hist_deconv = "Spectrum_"+campaign+"_Event_"+str_stream_event+"_Steps_"+str_stream_steps+"_BinSeed_"+str_stream_bin_seed+"(VWC "+str_stream_vwc+"%)";
string name_hist_deconv_legend = "Flux deconv EM_stop BinSeed_"+str_stream_bin_seed+"(VWC "+str_stream_vwc+"%)";
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

/*Filling error*/
for (int i = 0; i <deconv_vec.size(); i++)
	{
		flux_deconv->SetBinError(i+1,deconv_sigma_vec[i]); 
	}

/************************************************************************************************/


cout << " flux_deconv->GetBinError(1): " << flux_deconv->GetBinError(129) << endl;

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

//~ flux_deconv->Draw("E3");
//~ flux_deconv->Draw("SAME");
//~ hist_deconv_color_th->Draw("SAME");
//~ hist_deconv_color_ep->Draw("SAME");
//~ hist_deconv_color_fs->Draw("SAME");
//~ hist_deconv_color_he->Draw("SAME");


gPad->SetLogx();


TCanvas *canvas_error = new TCanvas("deconv_err_2","deconv_err_2",1920,1080);
canvas_error->SetSupportGL(true);
gStyle->SetCanvasPreferGL(kTRUE);

//~ string deconv_2_hist_title = "Spectrum_"+campaign+"_Event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_BinSeed_"+str_stream_bin_seed+"(VWC "+str_stream_vwc+"%)";
string deconv_2_hist_title = "Spectrum_"+campaign+"_Event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_Random_Seed";

TH1D* flux_deconv_2 = new TH1D(deconv_2_hist_title .c_str(),deconv_2_hist_title .c_str(), binnum , bins);
for (int i = 0; i <deconv_mean_vec.size()-1; i++)
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
		flux_deconv_2->SetBinContent(i+1,(deconv_mean_vec[i]/dE[i])*E_mid);
		
		//~ flux_deconv_2->SetBinContent(i+1, deconv_mean_vec[i]); 
	}

/*Fluxdeconv_2 hist title*/

flux_deconv_2->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
flux_deconv_2->GetXaxis()->SetTitleOffset(1.2);
flux_deconv_2->GetXaxis()->CenterTitle();
flux_deconv_2->GetXaxis()->SetTitleSize(0.04);
flux_deconv_2->SetStats(0);

		if(flux_representation=="Integral")
			{
				flux_deconv_2->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
				flux_deconv_2->GetYaxis()->SetTitleOffset(1.4);
			}
		if(flux_representation=="Lethargy")
			{
				flux_deconv_2->GetYaxis()->SetTitle("#bf{E#times#Phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
				flux_deconv_2->GetYaxis()->SetTitleOffset(1.7);
			}
		if(flux_representation=="Differential")
			{
				flux_deconv_2->GetYaxis()->SetTitle("#bf{#Phi(E) [cm^{-2} s^{-1} MeV^{-1}]}");
				flux_deconv_2->GetYaxis()->SetTitleOffset(1.3);
			}

flux_deconv_2->GetYaxis()->CenterTitle();
flux_deconv_2->GetYaxis()->SetTitleSize(0.04);


//~ /*Coloremos los histogramas deconvolucionados por region de energia*/
auto hist_deconv_color_th = (TH1D*)flux_deconv_2->Clone();
//~ hist_deconv_color_th->SetFillColor(kGray);
hist_deconv_color_th->SetFillColorAlpha(kGray,0.45);
hist_deconv_color_th->GetXaxis()->SetRangeUser(0, 2*1e-07);

auto hist_deconv_color_ep = (TH1D*)flux_deconv_2->Clone();
//~ hist_deconv_color_ep->SetFillColor(kCyan-9);
hist_deconv_color_ep->SetFillColorAlpha(kCyan-9,0.45);
hist_deconv_color_ep->GetXaxis()->SetRangeUser(2*1e-07, 1*1e-02);

auto hist_deconv_color_fs = (TH1D*)flux_deconv_2->Clone();
//~ hist_deconv_color_fs->SetFillColor(kGreen-9);
hist_deconv_color_fs->SetFillColorAlpha(kGreen-9,0.45);
hist_deconv_color_fs->GetXaxis()->SetRangeUser(1*1e-02, 1*1e+01);

auto hist_deconv_color_he = (TH1D*)flux_deconv_2->Clone();
//~ hist_deconv_color_he->SetFillColor(kRed-9);
hist_deconv_color_he->SetFillColorAlpha(kRed-9,0.45);
hist_deconv_color_he->GetXaxis()->SetRangeUser(1*1e+01,7.43*1e+03);
	

/*Filling error*/
for (int i = 0; i <deconv_mean_vec.size()-1; i++)
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
		//~ flux_deconv_2->SetBinContent(i+1,(deconv_mean_vec[i]/dE[i])*E_mid);
		
		flux_deconv_2->SetBinError(i+1,(deconv_sigma_vec[i]/dE[i])*E_mid); 
	}


/****Retrieve Values*/
//~ Double_t error_MC_th;
//~ Double_t integral_flux_deconv_MC_th = flux_deconv_integral->IntegralAndError(flux_deconv_integral->FindBin(0),flux_deconv_integral->FindBin(1.9*1e-07), error_MC_th, ""); // "" ... or ... "width"
//~ std::cout << "Integral thermal region flux deconv: " << scientific << setprecision(3) << integral_flux_deconv_MC_th << " Error: " << error_MC_th << std::endl;

//~ Double_t error_MC_ep;
//~ Double_t integral_flux_deconv_MC_ep = flux_deconv_integral->IntegralAndError(flux_deconv_integral->FindBin(2.2*1e-07),flux_deconv_integral->FindBin(0.9*1e-02), error_MC_ep, ""); // "" ... or ... "width"
//~ std::cout << "Integral epithermal region flux deconv: " << scientific << setprecision(3) << integral_flux_deconv_MC_ep << " Error:  " << error_MC_ep << std::endl;

//~ Double_t error_MC_fs;
//~ Double_t integral_flux_deconv_MC_fs = flux_deconv_integral->IntegralAndError(flux_deconv_integral->FindBin(1.1*1e-02),flux_deconv_integral->FindBin(0.89*1e+01), error_MC_fs, ""); // "" ... or ... "width"
//~ std::cout << "Integral fast region flux deconv: " << scientific << setprecision(3) << integral_flux_deconv_MC_fs << " Error: " << error_MC_fs << std::endl;

//~ Double_t error_MC_he;
//~ Double_t integral_flux_deconv_MC_he = flux_deconv_integral->IntegralAndError(flux_deconv_integral->FindBin(1.05*1e+01),flux_deconv_integral->FindBin(7.6*1e+03), error_MC_he, ""); // "" ... or ... "width"
//~ std::cout << "Integral high-energy region flux deconv: " << scientific << setprecision(3) << integral_flux_deconv_MC_he << " Error: " << error_MC_he << std::endl;

//~ Double_t error_MC_total;
//~ Double_t integral_flux_deconv_MC_total = flux_deconv_integral->IntegralAndError(flux_deconv_integral->FindBin(0),flux_deconv_integral->FindBin(7.6*1e+03), error_MC_total, ""); // "" ... or ... "width"
//~ std::cout << "Integral total flux deconv: " << scientific << setprecision(3) << integral_flux_deconv_MC_total << " Error: " << error_MC_total << std::endl;



//~ double th_tot = integral_flux_deconv_MC_th/integral_flux_deconv_MC_total;
//~ double ep_tot = integral_flux_deconv_MC_ep/integral_flux_deconv_MC_total;
//~ double fs_tot = integral_flux_deconv_MC_fs/integral_flux_deconv_MC_total;
//~ double he_tot = integral_flux_deconv_MC_he/integral_flux_deconv_MC_total;

//~ double th_he = integral_flux_deconv_MC_th/integral_flux_deconv_MC_he;
//~ double ep_he = integral_flux_deconv_MC_ep/integral_flux_deconv_MC_he;
//~ double fs_he = integral_flux_deconv_MC_fs/integral_flux_deconv_MC_he;

//~ double err_th_he =th_he*sqrt(pow(error_MC_th/integral_flux_deconv_MC_th,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));
//~ double err_ep_he =th_he*sqrt(pow(error_MC_ep/integral_flux_deconv_MC_ep,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));
//~ double err_fs_he =th_he*sqrt(pow(error_MC_fs/integral_flux_deconv_MC_fs,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));

//~ double err_th_tot =th_tot*sqrt(pow(error_MC_th/integral_flux_deconv_MC_th,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
//~ double err_ep_tot =ep_tot*sqrt(pow(error_MC_ep/integral_flux_deconv_MC_ep,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
//~ double err_fs_tot =fs_tot*sqrt(pow(error_MC_fs/integral_flux_deconv_MC_fs,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
//~ double err_he_tot =he_tot*sqrt(pow(error_MC_he/integral_flux_deconv_MC_he,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));

//~ cout << " ratio th_tot: "  << scientific << setprecision(3) << th_tot << " error: " << err_th_tot << endl;
//~ cout << " ratio ep_tot: "  << scientific << setprecision(3) << ep_tot << " error: " << err_ep_tot << endl;
//~ cout << " ratio fs_tot: "  << scientific << setprecision(3) << fs_tot << " error: " << err_fs_tot << endl;
//~ cout << " ratio he_tot: "  << scientific << setprecision(3) << he_tot << " error: " << err_he_tot << endl;
//~ cout <<  endl;
//~ cout << " ratio th_he: "  << scientific << setprecision(3) << th_he << " error: " << err_th_he << endl;
//~ cout << " ratio ep_he: "  << scientific << setprecision(3) << ep_he << " error: " << err_ep_he << endl;
//~ cout << " ratio fs_he: "  << scientific << setprecision(3) << fs_he << " error: " << err_fs_he << endl;

/***********FIXED UNCERTAINTIES VALUES*****************/
/****Retrieve Values*/

Double_t integral_flux_deconv_MC_total = flux_deconv_integral->Integral(flux_deconv_integral->FindBin(1e-09),flux_deconv_integral->FindBin(7.6*1e+03));
Double_t integral_flux_deconv_MC_th = flux_deconv_integral->Integral(flux_deconv_integral->FindBin(1e-09),flux_deconv_integral->FindBin(1.9*1e-07));
cout << "Thermal region: " << "1e-09 MeV" << "(bin: " << flux_deconv_integral->FindBin(1e-09) <<")" << " " << "1.9*1e-07 MeV" << "(bin: "<< flux_deconv_integral->FindBin(1.9*1e-07) <<")" << endl;
Double_t integral_flux_deconv_MC_ep = flux_deconv_integral->Integral(flux_deconv_integral->FindBin(2.2*1e-07),flux_deconv_integral->FindBin(0.9*1e-02));
cout << "Epithermal region: " << "2.2*1e-07 MeV" << "(bin: "<< flux_deconv_integral->FindBin(2.2*1e-07)<<")" << " " << "0.9*1e-02 MeV" << "(bin: "<< flux_deconv_integral->FindBin(0.9*1e-02) <<")" << endl;
Double_t integral_flux_deconv_MC_fs = flux_deconv_integral->Integral(flux_deconv_integral->FindBin(1.1*1e-02),flux_deconv_integral->FindBin(0.89*1e+01));
cout << "Fast region: " << "1.1*1e-02 MeV" << "(bin: "<< flux_deconv_integral->FindBin(1.1*1e-02)<<")" << " " << "0.9*1e-02 MeV" << "(bin: "<<flux_deconv_integral->FindBin(0.89*1e+01)<<")" << endl;
Double_t integral_flux_deconv_MC_he = flux_deconv_integral->Integral(flux_deconv_integral->FindBin(1.05*1e+01),flux_deconv_integral->FindBin(7.6*1e+03));
cout << "High energy region: " << "1.05*1e+01 MeV" << "(bin: "<<flux_deconv_integral->FindBin(1.05*1e+01)<<")" << " " << "0.9*1e-02 MeV" <<"(bin: "<<flux_deconv_integral->FindBin(7.6*1e+03)<<")" << endl;


double error_MC_th = 0.;
double error_MC_ep = 0.;
double error_MC_fs = 0.;
double error_MC_he = 0.;
double error_MC_total = 0.;

for(int i=flux_deconv_integral->FindBin(1e-09);i<=flux_deconv_integral->FindBin(1.9*1e-07);i++)
{
	double sum_error_partial=0;
	sum_error_partial = flux_deconv_integral->GetBinError(i+1);
	//~ cout << "bin: " << i << " error: " << sum_error_partial << endl;
	 error_MC_th += sum_error_partial;
}

for(int i=flux_deconv_integral->FindBin(2.2*1e-07);i<=flux_deconv_integral->FindBin(0.9*1e-02);i++)
{
	double sum_error_partial=0;
	sum_error_partial = flux_deconv_integral->GetBinError(i+1);
	//~ cout << "bin: " << i << " error: " << sum_error_partial << endl;
	error_MC_ep += sum_error_partial;
}

for(int i=flux_deconv_integral->FindBin(1.1*1e-02);i<=flux_deconv_integral->FindBin(0.89*1e+01);i++)
{
	double sum_error_partial=0;
	sum_error_partial = flux_deconv_integral->GetBinError(i+1);
	//~ cout << "bin: " << i << " error: " << sum_error_partial << endl;
	error_MC_fs+= sum_error_partial;
}

for(int i=flux_deconv_integral->FindBin(1.05*1e+01);i<=flux_deconv_integral->FindBin(7.6*1e+03);i++)
{
	double sum_error_partial=0;
	sum_error_partial = flux_deconv_integral->GetBinError(i+1);
	//~ cout << "bin: " << i << " error: " << sum_error_partial << endl;
	error_MC_he+= sum_error_partial;
}

for(int i=flux_deconv_integral->FindBin(0);i<=flux_deconv_integral->FindBin(7.6*1e+03);i++)
{
	double sum_error_partial=0;
	sum_error_partial = flux_deconv_integral->GetBinError(i);
	//~ cout << "bin: " << i << " error: " << sum_error_partial << endl;
	error_MC_total += sum_error_partial;
}



cout << "integral_flux_deconv_MC_th " << scientific << setprecision(1)<< integral_flux_deconv_MC_th << " error_th_region " << error_MC_th << endl;
cout << "integral_flux_deconv_MC_ep " << scientific << setprecision(1) << integral_flux_deconv_MC_ep <<  " error_ep_region " << error_MC_ep << endl;
cout << "integral_flux_deconv_MC_fs " << scientific << setprecision(1) << integral_flux_deconv_MC_fs <<  " error_fs_region " << error_MC_fs << endl;
cout << "integral_flux_deconv_MC_he " << scientific << setprecision(1) << integral_flux_deconv_MC_he <<  " error_he_region " << error_MC_he << endl;
cout << "integral_flux_deconv_MC_total " <<  scientific << setprecision(1) << integral_flux_deconv_MC_total << " error_total " << error_MC_total << endl;

double th_tot = integral_flux_deconv_MC_th/integral_flux_deconv_MC_total;
double ep_tot = integral_flux_deconv_MC_ep/integral_flux_deconv_MC_total;
double fs_tot = integral_flux_deconv_MC_fs/integral_flux_deconv_MC_total;
double he_tot = integral_flux_deconv_MC_he/integral_flux_deconv_MC_total;

double th_he = integral_flux_deconv_MC_th/integral_flux_deconv_MC_he;
double ep_he = integral_flux_deconv_MC_ep/integral_flux_deconv_MC_he;
double fs_he = integral_flux_deconv_MC_fs/integral_flux_deconv_MC_he;

double err_th_he =th_he*sqrt(pow(error_MC_th/integral_flux_deconv_MC_th,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));
double err_ep_he =th_he*sqrt(pow(error_MC_ep/integral_flux_deconv_MC_ep,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));
double err_fs_he =th_he*sqrt(pow(error_MC_fs/integral_flux_deconv_MC_fs,2) + pow(error_MC_he/integral_flux_deconv_MC_he,2));

double err_th_tot =th_tot*sqrt(pow(error_MC_th/integral_flux_deconv_MC_th,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
double err_ep_tot =ep_tot*sqrt(pow(error_MC_ep/integral_flux_deconv_MC_ep,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
double err_fs_tot =fs_tot*sqrt(pow(error_MC_fs/integral_flux_deconv_MC_fs,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
double err_he_tot =he_tot*sqrt(pow(error_MC_he/integral_flux_deconv_MC_he,2) + pow(error_MC_total/integral_flux_deconv_MC_total,2));
cout << endl;
cout << " ratio th_tot: "  << scientific << setprecision(2) << th_tot << " error: " << err_th_tot << endl;
cout << " ratio ep_tot: "  << scientific << setprecision(2) << ep_tot << " error: " << err_ep_tot << endl;
cout << " ratio fs_tot: "  << scientific << setprecision(2) << fs_tot << " error: " << err_fs_tot << endl;
cout << " ratio he_tot: "  << scientific << setprecision(2) << he_tot << " error: " << err_he_tot << endl;
cout <<  endl;
cout << " ratio th_he: "  << scientific << setprecision(2) << th_he << " error: " << err_th_he << endl;
cout << " ratio ep_he: "  << scientific << setprecision(2) << ep_he << " error: " << err_ep_he << endl;
cout << " ratio fs_he: "  << scientific << setprecision(2) << fs_he << " error: " << err_fs_he << endl;


/***************************************/





auto flux_deconv_2_dot_error =  (TH1D*)flux_deconv_2->Clone("hist_error");
flux_deconv_2_dot_error->SetMarkerStyle(20);
flux_deconv_2_dot_error->SetMarkerSize(1.1);
flux_deconv_2_dot_error->SetLineWidth(1);

flux_deconv_2->SetLineColor(kBlack);
flux_deconv_2->SetFillColor(kRed);
flux_deconv_2->SetFillStyle(3144);
flux_deconv_2->SetLineWidth(1);
flux_deconv_2->SetFillColorAlpha(kViolet-2,0.55);


/*Setting Hist*/

gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	
canvas_error->SetLeftMargin(0.15);
canvas_error->SetRightMargin(0.009);
double shift_margin = 0.05; // para reajustar la poscion de el texto dentro del pad
if (flux_representation=="Differential")
	{
			gPad->SetLogy();
	}


	ostringstream stream_intgtotal, stream_intgth, stream_intgep, stream_intgfs, stream_intghe;
	ostringstream stream_intg_total_ratio_th, stream_intg_total_ratio_ep, stream_intg_total_ratio_fs, stream_intg_total_ratio_he;
	ostringstream stream_intg_he_ratio_th, stream_intg_he_ratio_ep, stream_intg_he_ratio_fs;
	//~ ostringstream stream_sum_eta;
	
	//~ stream_ndet << ndet;
	/*scientific << setprecision(3) doesn't work, this mean 3 decimals after point in scientific notation.
	 * If we want 3 significant numbers of a float, we do: scientific << setprecision(2) */
	stream_intgtotal << scientific << setprecision(1) << integral_flux_deconv_MC_total;
	stream_intgth << scientific  << setprecision(1) << integral_flux_deconv_MC_th;
	stream_intgep << scientific << setprecision(1) << integral_flux_deconv_MC_ep;
	stream_intgfs << scientific << setprecision(1) << integral_flux_deconv_MC_fs;
	stream_intghe << scientific << setprecision(1) << integral_flux_deconv_MC_he;
	//~ stream_Chi2 << setprecision(3)<< data_to_hist[6];
	//~ stream_Chi2red << setprecision(3)<< data_to_hist[7];
	//~ stream_sum_eta << setprecision(3) << sum_eta_ratios;
	
	//~ stream_intg_total_ratio_th << fixed << setprecision(2) << th_tot;
	//~ stream_intg_total_ratio_ep << fixed << setprecision(2) << ep_tot;
	//~ stream_intg_total_ratio_fs << fixed << setprecision(2) << fs_tot;
	//~ stream_intg_total_ratio_he << fixed << setprecision(2) << he_tot;

	stream_intg_total_ratio_th << scientific << setprecision(1) << th_tot;
	stream_intg_total_ratio_ep << scientific<< setprecision(1) << ep_tot;
	stream_intg_total_ratio_fs << scientific << setprecision(1) << fs_tot;
	stream_intg_total_ratio_he << scientific << setprecision(1) << he_tot;


	stream_intg_he_ratio_th << scientific << setprecision(1) << th_he;
	stream_intg_he_ratio_ep << scientific << setprecision(1) << ep_he;
	stream_intg_he_ratio_fs << scientific << setprecision(1) << fs_he;

	/*Separate number from exponent*/
	size_t lenght_intg_tot = stream_intgtotal.str().find_first_of("e");
	size_t lenght_intg_th = stream_intgth.str().find_first_of("e");
	size_t lenght_intg_ep =stream_intgep.str().find_first_of("e");
	size_t lenght_intg_fs = stream_intgfs.str().find_first_of("e");
	size_t lenght_intg_he = stream_intghe.str().find_first_of("e");

	size_t lenght_intg_total_ratio_th = stream_intg_total_ratio_th.str().find_first_of("e");
	size_t lenght_intg_total_ratio_ep = stream_intg_total_ratio_ep.str().find_first_of("e");
	size_t lenght_intg_total_ratio_fs = stream_intg_total_ratio_fs.str().find_first_of("e");
	size_t lenght_intg_total_ratio_he = stream_intg_total_ratio_he.str().find_first_of("e");

	size_t lenght_intg_he_ratio_th = stream_intg_he_ratio_th.str().find_first_of("e");
	size_t lenght_intg_he_ratio_ep = stream_intg_he_ratio_ep.str().find_first_of("e");
	size_t lenght_intg_he_ratio_fs = stream_intg_he_ratio_fs.str().find_first_of("e");
	
	string str_stream_intgtotal_number = stream_intgtotal.str().substr(0,lenght_intg_tot);
	string str_stream_intgtotal_exp = stream_intgtotal.str().substr(lenght_intg_tot+1,1)+stream_intgtotal.str().substr(lenght_intg_tot+3,1);
	string str_stream_intgth_number =stream_intgth.str().substr(0,lenght_intg_th);
	string str_stream_intgth_exp = stream_intgth.str().substr(lenght_intg_th+1,1)+stream_intgth.str().substr(lenght_intg_th+3,1);
	string str_stream_intgep_number = stream_intgep.str().substr(0,lenght_intg_ep);
	string str_stream_intgep_exp = stream_intgep.str().substr(lenght_intg_ep+1,1)+stream_intgep.str().substr(lenght_intg_ep+3,1);
	string str_stream_intgfs_number =stream_intgfs.str().substr(0,lenght_intg_fs);
	string str_stream_intgfs_exp = stream_intgfs.str().substr(lenght_intg_fs+1,1)+stream_intgfs.str().substr(lenght_intg_fs+3,1);
	string str_stream_intghe_number = stream_intghe.str().substr(0,lenght_intg_he);
	string str_stream_intghe_exp = stream_intghe.str().substr(lenght_intg_he+1,1)+stream_intghe.str().substr(lenght_intg_he+3,1);

	string str_stream_intg_total_ratio_th_number = stream_intg_total_ratio_th.str().substr(0,lenght_intg_total_ratio_th);
	//~ string str_stream_intg_total_ratio_th_exp =stream_intg_total_ratio_th.str().substr(lenght_intg_total_ratio_th+1);
	string str_stream_intg_total_ratio_th_exp = stream_intg_total_ratio_th.str().substr(lenght_intg_total_ratio_th+1,1)+stream_intg_total_ratio_th.str().substr(lenght_intg_total_ratio_th+3,1);
	string str_stream_intg_total_ratio_ep_number = stream_intg_total_ratio_ep.str().substr(0,lenght_intg_total_ratio_ep);
	string str_stream_intg_total_ratio_ep_exp = stream_intg_total_ratio_ep.str().substr(lenght_intg_total_ratio_ep+1,1)+stream_intg_total_ratio_ep.str().substr(lenght_intg_total_ratio_ep+3,1);
	string str_stream_intg_total_ratio_fs_number = stream_intg_total_ratio_fs.str().substr(0,lenght_intg_total_ratio_fs);
	string str_stream_intg_total_ratio_fs_exp = stream_intg_total_ratio_fs.str().substr(lenght_intg_total_ratio_fs+1,1)+stream_intg_total_ratio_fs.str().substr(lenght_intg_total_ratio_fs+3,1);
	string str_stream_intg_total_ratio_he_number = stream_intg_total_ratio_he.str().substr(0,lenght_intg_total_ratio_he);
	string str_stream_intg_total_ratio_he_exp = stream_intg_total_ratio_he.str().substr(lenght_intg_total_ratio_he+1,1)+stream_intg_total_ratio_he.str().substr(lenght_intg_total_ratio_he+3,1);

	string str_stream_intg_he_ratio_th_number = stream_intg_he_ratio_th.str().substr(0,lenght_intg_he_ratio_th);
	string str_stream_intg_he_ratio_th_exp = stream_intg_he_ratio_th.str().substr(lenght_intg_he_ratio_th+1,1)+stream_intg_he_ratio_th.str().substr(lenght_intg_he_ratio_th+3,1);
	string str_stream_intg_he_ratio_ep_number = stream_intg_he_ratio_ep.str().substr(0,lenght_intg_he_ratio_ep);
	string str_stream_intg_he_ratio_ep_exp = stream_intg_he_ratio_ep.str().substr(lenght_intg_he_ratio_ep+1,1)+stream_intg_he_ratio_ep.str().substr(lenght_intg_he_ratio_ep+3,1);
	string str_stream_intg_he_ratio_fs_number = stream_intg_he_ratio_fs.str().substr(0,lenght_intg_he_ratio_fs);
	string str_stream_intg_he_ratio_fs_exp = stream_intg_he_ratio_fs.str().substr(lenght_intg_he_ratio_fs+1,1)+stream_intg_he_ratio_fs.str().substr(lenght_intg_he_ratio_fs+3,1);
	
	
	string str_stream_ndet_new = "#Det: "+stream_ndet.str()+" (ndf)";
	cout<< "Integral total" << endl;
	string str_stream_intgtotal = "Intg Total: "+str_stream_intgtotal_number+"("+uncertainty_value(integral_flux_deconv_MC_total,error_MC_total)+")#times10^{"+str_stream_intgtotal_exp+"} cm^{-2}s^{-1}";
	cout << endl;
	cout<< "Integral thermal region" << endl;
	string str_stream_intgth = str_stream_intgth_number+"("+uncertainty_value(integral_flux_deconv_MC_th,error_MC_th)+")#times10^{"+str_stream_intgth_exp+"} cm^{-2}s^{-1}";
	cout << endl;
	cout<< "Integral epithermal region" << endl;
	string str_stream_intgep = str_stream_intgep_number+"("+uncertainty_value(integral_flux_deconv_MC_ep,error_MC_ep)+")#times10^{"+str_stream_intgep_exp+"} cm^{-2}s^{-1}";
	cout << endl;
	cout<< "Integral fast region" << endl;
	string str_stream_intgfs = str_stream_intgfs_number+"("+uncertainty_value(integral_flux_deconv_MC_fs,error_MC_fs)+")#times10^{"+str_stream_intgfs_exp+"} cm^{-2}s^{-1}";
	cout << endl;
	cout<< "Integral high energy region" << endl;
	string str_stream_intghe = str_stream_intghe_number+"("+uncertainty_value(integral_flux_deconv_MC_he,error_MC_he)+")#times10^{"+str_stream_intghe_exp+"} cm^{-2}s^{-1}";
	//~ string str_stream_Chi2 = "#chi^{2}: "+stream_Chi2.str();
	//~ string str_stream_Chi2red = "#chi^{2}/ndf: "+stream_Chi2red.str();

	string str_stream_intg_total_ratio_th = "#frac{#Phi_{th}}{#Phi_{tot}}="+str_stream_intg_total_ratio_th_number+"("+uncertainty_value(th_tot,err_th_tot)+")#times10^{"+str_stream_intg_total_ratio_th_exp+"}";
	string str_stream_intg_total_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{tot}}="+str_stream_intg_total_ratio_ep_number+"("+uncertainty_value(ep_tot,err_ep_tot)+")#times10^{"+str_stream_intg_total_ratio_ep_exp+"}";
	string str_stream_intg_total_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{tot}}="+str_stream_intg_total_ratio_fs_number+"("+uncertainty_value(fs_tot,err_fs_tot)+")#times10^{"+str_stream_intg_total_ratio_fs_exp+"}";
	string str_stream_intg_total_ratio_he = "#frac{#Phi_{he}}{#Phi_{tot}}="+str_stream_intg_total_ratio_he_number+"("+uncertainty_value(he_tot,err_he_tot)+")#times10^{"+str_stream_intg_total_ratio_he_exp+"}";

	string str_stream_intg_he_ratio_th = "#frac{#Phi_{th}}{#Phi_{he}}="+str_stream_intg_he_ratio_th_number+"("+uncertainty_value(th_he,err_th_he)+")#times10^{"+str_stream_intg_he_ratio_th_exp+"}";
	string str_stream_intg_he_ratio_ep = "#frac{#Phi_{ep}}{#Phi_{he}}="+str_stream_intg_he_ratio_ep_number+"("+uncertainty_value(ep_he,err_ep_he)+")#times10^{"+str_stream_intg_he_ratio_ep_exp+"}";
	string str_stream_intg_he_ratio_fs = "#frac{#Phi_{fs}}{#Phi_{he}}="+str_stream_intg_he_ratio_fs_number+"("+uncertainty_value(fs_he,err_fs_he)+")#times10^{"+str_stream_intg_he_ratio_fs_exp+"}";

	//~ string str_stream_sum_eta = "#sum_{#eta}="+stream_sum_eta.str();

	TLatex *l_ndet = new TLatex(0.15+shift_margin,0.85,str_stream_ndet_new.c_str());
	TLatex *l_intg_total = new TLatex(0.15+shift_margin,0.8,str_stream_intgtotal.c_str());
	//~ TLatex *l_Chi2 = new TLatex(0.15+shift_margin,0.75,str_stream_Chi2.c_str());
	//~ TLatex *l_sum_eta = new TLatex(0.35+shift_margin,0.75,str_stream_sum_eta.c_str());
	//~ TLatex *l_Chi2red = new TLatex(0.15+shift_margin,0.70,str_stream_Chi2red.c_str());
	TLatex *l_intg_th = new TLatex(0.15+shift_margin,0.12,str_stream_intgth.c_str());
	TLatex *l_intg_ep = new TLatex(0.35+shift_margin,0.12,str_stream_intgep.c_str());
	TLatex *l_intg_fs = new TLatex(0.58+shift_margin,0.12,str_stream_intgfs.c_str());
	TLatex *l_intg_he = new TLatex(0.76+shift_margin,0.12,str_stream_intghe.c_str());

	TLatex *l_intgtotal_ratio_th = new TLatex(0.15+shift_margin,0.55,str_stream_intg_total_ratio_th.c_str());
	TLatex *l_intgtotal_ratio_ep = new TLatex(0.35+shift_margin,0.55,str_stream_intg_total_ratio_ep.c_str());
	TLatex *l_intgtotal_ratio_fs = new TLatex(0.58+shift_margin,0.55,str_stream_intg_total_ratio_fs.c_str());
	TLatex *l_intgtotal_ratio_he = new TLatex(0.78+shift_margin,0.55,str_stream_intg_total_ratio_he.c_str());

	TLatex *l_intghe_ratio_th = new TLatex(0.15+shift_margin,0.35,str_stream_intg_he_ratio_th.c_str());
	TLatex *l_intghe_ratio_ep = new TLatex(0.35+shift_margin,0.35,str_stream_intg_he_ratio_ep.c_str());
	TLatex *l_intghe_ratio_fs = new TLatex(0.58+shift_margin,0.35,str_stream_intg_he_ratio_fs.c_str());



	flux_deconv_2_dot_error->GetYaxis()->SetRangeUser(0,0.01);
	flux_deconv_2->GetYaxis()->SetRangeUser(0,0.01);
	//~ Double_t max_y = flux_inicial->GetMaximum();
	flux_deconv_2_dot_error->SetMaximum(0.005);
	flux_deconv_2_dot_error->SetMinimum(0.);

	flux_deconv_2->SetMaximum(0.005);
	flux_deconv_2->SetMinimum(0.); 

	gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	

	//~ intg_total->SetTextAlign(23);
	//~ intg_total->SetTextSize(0.08);
	flux_deconv_2_dot_error->Draw("E1");
	flux_deconv_2->Draw("E3");
	
	flux_deconv_2_dot_error->Draw("SAME");
	flux_deconv_2->Draw("SAME");
	
	hist_deconv_color_th->Draw("SAME");
	hist_deconv_color_ep->Draw("SAME");
	hist_deconv_color_fs->Draw("SAME");
	hist_deconv_color_he->Draw("SAME");



	l_ndet->SetNDC();
	l_ndet->SetTextSize(0.04);
	l_intg_total->SetNDC();
	l_intg_total->SetTextSize(0.04);
	//~ l_Chi2->SetNDC();
	//~ l_Chi2->SetTextSize(0.04);
	//~ l_Chi2red->SetNDC();
	//~ l_Chi2red->SetTextSize(0.04);
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
	
	//~ l_sum_eta->SetNDC();
	//~ l_sum_eta->SetTextSize(0.04);

		
	l_ndet->Draw("SAME");
	l_intg_th->Draw("SAME");
	l_intg_total->Draw("SAME");
	//~ l_Chi2->Draw("SAME");
	//~ l_Chi2red->Draw("SAME");
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

	//~ l_sum_eta->Draw("SAME");


gStyle->SetOptStat(0);
gPad->SetLogx();
gPad->RedrawAxis();

canvas_error->Draw();
canvas_error->SaveAs(("./deconv_data_pdf/EM_MC_fitting/spectrum/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+flux_representation+"_MC_stop_w_error.pdf").c_str());


TCanvas *canvas_compare = new TCanvas("Compare flux seed, flux deconv","Compare flux seed, flux decon",1920,1080);
gStyle->SetCanvasPreferGL(kTRUE);



//~ /*Histograma de flujo inicial*/
auto name_hist_seed = "flux_seed_expacs_"+str_stream_vwc+"%";
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
for (int i = 0; i <deconv_vec.size(); i++)
{
		double E_mid;
		
		if(flux_representation=="Integral")
			{
				E_mid = E[i]+(dE[i]/2.); // integral flux
			}
		if(flux_representation=="Lethargy")
			{
				// E_mid = E[i]+(dE[i]/2.); // per unit lethargic
				 E_mid = 1.;
				 dE[i] = 1.;
			}
		if(flux_representation=="Differential")
			{
				E_mid = E[i]+(dE[i]/2.); //differential flux
				dE[i] = 1.;
			}
		//double E_mid;
		//E_mid = E[i]+(dE[i]/2.);
		flux_inicial->SetBinContent(i+1,(Seed[i]/E_mid)*dE[i]); //integral
		// flux_inicial->SetBinContent(i+1,Seed[i]); //integral
}


flux_inicial->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
flux_inicial->GetXaxis()->SetTitleOffset(1.2);
flux_inicial->GetXaxis()->CenterTitle();
flux_inicial->GetXaxis()->SetTitleSize(0.04);
flux_inicial->SetStats(0);

		if(flux_representation=="Integral")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.4);
			}
		if(flux_representation=="Lethargy")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{E#times#Phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.7);
			}
		if(flux_representation=="Differential")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{#Phi(E) [cm^{-2} s^{-1} MeV^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.3);
			}


flux_inicial->GetYaxis()->CenterTitle();
flux_inicial->GetYaxis()->SetTitleSize(0.04);
flux_deconv_2_dot_error->GetYaxis()->SetRangeUser(0,flux_inicial->GetMaximum());
Double_t max_y = flux_inicial->GetMaximum();
flux_deconv_2_dot_error->SetMaximum(max_y+max_y*0.1); 

gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
	
flux_deconv->SetLineColor(kRed);
flux_inicial->SetLineColor(kBlue);

//~ flux_inicial->Draw("HIST");
flux_deconv_2_dot_error->Draw("E1");
//~ flux_deconv_2->Draw("E3");
	
flux_deconv_2_dot_error->Draw("SAME");
flux_deconv_2->Draw("SAME");

flux_inicial->Draw("HIST SAME");
//~ flux_deconv_2->Draw("E1 SAME");
//~ flux_deconv_2->Draw("SAME");
flux_deconv->Draw("HIST SAME");

//~ flux_inicial->GetYaxis()->SetTitle("Flux" );
//~ flux_inicial->GetXaxis()->SetTitle("Energy [MeV]" );

gPad->SetLogx();
canvas_compare->SetLeftMargin(0.15);
//~ canvas_deconv->GetPad(i+1)->SetRightMargin(0.009);

TLegend *legend_c = new TLegend(0.32,0.59,0.59,0.82);
legend_c->AddEntry(flux_inicial,name_hist_seed.c_str(),"l");
legend_c->AddEntry(flux_deconv_2,"Flux deconv EM_MC_stop_random_seed","l");
legend_c->AddEntry(flux_deconv,name_hist_deconv_legend.c_str(),"l");
legend_c->Draw();

canvas_compare->Draw();
canvas_compare->SaveAs(("./deconv_data_pdf/EM_MC_fitting/spectrum/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_"+str_stream_event+"_steps_"+str_stream_steps+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_"+flux_representation+"_MC_stop_w_error_compare.pdf").c_str());


/**update RDataframe**/
//~ ROOT::RDataFrame df_seed_loop_i(51);
ROOT::RDataFrame  df_fit_file_new(1);
auto  df_fit_file_update =  df_fit_file_new.Define("deconv_vec_MC", [&]() {
										  vector<double> deconv_vec_mc = deconv_mean_vec;
										  return deconv_vec_mc;
										})
										.Define("deconv_sigma_vec_MC", [&]() {
										  vector<double> deconv_sigma_vec_mc = deconv_sigma_vec;
										  return deconv_sigma_vec_mc;
										})
										.Define("deconv_sigma_perc_vec_MC", [&]() {
										  vector<double> deconv_sigma_perc_vec_mc = deconv_sigma_perc_vec;
										  return deconv_sigma_perc_vec_mc;
										})
										.Define("Intg_total",[&]() {
												double Intg_total_MC = integral_flux_deconv_MC_total;
												return Intg_total_MC;
										})
										.Define("Intg_th",[&]() {
												double Intg_th_MC = integral_flux_deconv_MC_th;
												return Intg_th_MC;
										})
										.Define("Intg_ep",[&]() {
												double Intg_ep_MC = integral_flux_deconv_MC_ep;
												return Intg_ep_MC;
										})
										.Define("Intg_fs",[&]() {
												double Intg_fs_MC = integral_flux_deconv_MC_fs;
												return Intg_fs_MC;
										})
										.Define("Intg_he",[&]() {
												double Intg_he_MC = integral_flux_deconv_MC_he;
												return Intg_he_MC;
										})
										.Define("ratio_th_tot",[&]() {
												double rat_th_tot_MC = th_tot;
												return rat_th_tot_MC;
										})
										.Define("ratio_ep_tot",[&]() {
												double rat_ep_tot_MC = ep_tot;
												return rat_ep_tot_MC;
										})
										.Define("ratio_fs_tot",[&]() {
												double rat_fs_tot_MC = fs_tot;
												return rat_fs_tot_MC;
										})
										.Define("ratio_he_tot",[&]() {
												double rat_he_tot_MC = he_tot;
												return rat_he_tot_MC;
										})
										.Define("eta_th",[&]() {
												double eta_th_MC = th_he;
												return eta_th_MC;
										})
										.Define("eta_ep",[&]() {
												double eta_ep_MC = ep_he;
												return eta_ep_MC;
										})										
										.Define("eta_fs",[&]() {
												double eta_fs_MC = fs_he;
												return eta_fs_MC;
										})
										.Define("err_intg_total",[&]() {
												double error_Intg_total_MC =  error_MC_total;
												return error_Intg_total_MC;
										})
										.Define("err_intg_th",[&]() {
												double error_Intg_th_MC =  error_MC_th;
												return error_Intg_th_MC;
										})
										.Define("err_intg_ep",[&]() {
												double error_Intg_ep_MC =  error_MC_ep;
												return error_Intg_ep_MC;
										})
										.Define("err_intg_fs",[&]() {
												double error_Intg_fs_MC =  error_MC_fs;
												return error_Intg_fs_MC;
										})
										.Define("err_intg_he",[&]() {
												double error_Intg_he_MC =  error_MC_he;
												return error_Intg_he_MC;
										})
										.Define("err_ratio_th_tot",[&]() {
												double error_ratio_th_tot_MC =  err_th_tot;
												return error_ratio_th_tot_MC;
										})
										.Define("err_ratio_ep_tot",[&]() {
												double error_ratio_ep_tot_MC =  err_ep_tot;
												return error_ratio_ep_tot_MC;
										})
										.Define("err_ratio_fs_tot",[&]() {
												double error_ratio_fs_tot_MC =  err_fs_tot;
												return error_ratio_fs_tot_MC;
										})
										.Define("err_ratio_he_tot",[&]() {
												double error_ratio_he_tot_MC =  err_he_tot;
												return error_ratio_he_tot_MC;
										})
										.Define("err_eta_th",[&]() {
												double error_ratio_th_he_MC =  err_th_he;
												return error_ratio_th_he_MC;
										})
										.Define("err_eta_ep",[&]() {
												double error_ratio_ep_he_MC =  err_ep_he;
												return error_ratio_ep_he_MC;
										})
										.Define("err_eta_fs",[&]() {
												double error_ratio_fs_he_MC =  err_fs_he;
												return error_ratio_fs_he_MC;
										});
										
string fit_event_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_update.root";
df_fit_file_update.Snapshot("fit_loop_tree_update",fit_event_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/


delete canvas_error;
delete canvas_compare;
delete flux_inicial;
}

TH1D* plot_expacs_seed_TH1D(string campaign, int bin_seed, string flux_representation){

int binnum = 0; /*numero de bines*/
vector<Double_t> Seed; /*vector de flujo semilla*/
vector<Double_t> dE; /*Vector de anchos de energia*/
vector<Double_t> B; /*bins*/ /*matriz de bordes de bins*/
vector<Double_t> E; /*bins*/ /*matriz de Energias*/


string input_deconv_file= "./deconv_data_rootfile/EM_stop/"+campaign+"/EM_unfolding_loop_campaign_"+campaign+"_event_1_steps_0_timegrid_15_ndet_11.root";
ROOT::RDataFrame df_event("em_loop_tree", input_deconv_file);

/****Cargamos el flujo semilla*****/

string str_stream_vwc_file;

string seed_flux_expacs_csv;

int bin_seed_new = bin_seed -1;
if(bin_seed_new<=150)
		{
			// Map: 0->0 (VWC 0%)
			// Map: 1->1 (VWC 0.2%)
			// Map: 150->150 (30%)
			ostringstream stream_vwc;
			stream_vwc << bin_seed_new;
			//~ string str_stream_vwc =stream_vwc.str();
			 str_stream_vwc_file =stream_vwc.str();

			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux_500/csv_files/LasCampanasAtacama_"+str_stream_vwc_file+".csv";
				}
		}

if(bin_seed_new>150)
		{
			// Map: 151->32 (VWC 32%)
			// Map: 152->34 (vwc 34%)
			// Map: 185->100 ((vwc 100%)
			int vwc_old_51_seed = (bin_seed_new - 135)*2;

			ostringstream stream_vwc_old_51_seed;
			stream_vwc_old_51_seed << vwc_old_51_seed;
			string str_stream_vwc_old_51_seed = stream_vwc_old_51_seed.str();
			str_stream_vwc_file = str_stream_vwc_old_51_seed;
			
			if(campaign=="LCO")
				{
					seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_"+str_stream_vwc_file+".csv";
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

/*VWC%*/
ostringstream stream_vwc ;
auto df_vwc_vec =  df_event.Take<double>("seed_bin_edgeds").GetValue();
double vwc_value = df_vwc_vec[bin_seed-1];
stream_vwc << vwc_value;
string str_stream_vwc = stream_vwc.str();

/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = df_binedges_vec.data();

//~ /*Histograma de flujo inicial*/
auto name_hist_seed = "Expacs/Parma Seed "+str_stream_vwc+"% VWC";
TH1D* flux_inicial = new TH1D(name_hist_seed.c_str(),name_hist_seed.c_str(), binnum , bins);
for (int i = 0; i <df_binedges_vec.size(); i++)
{
		double E_mid;
		
		if(flux_representation=="Integral")
			{
				E_mid = E[i]+(dE[i]/2.); // integral flux
			}
		if(flux_representation=="Lethargy")
			{
				// E_mid = E[i]+(dE[i]/2.); // per unit lethargic
				 E_mid = 1.;
				 dE[i] = 1.;
			}
		if(flux_representation=="Differential")
			{
				E_mid = E[i]+(dE[i]/2.); //differential flux
				dE[i] = 1.;
			}
		//double E_mid;
		//E_mid = E[i]+(dE[i]/2.);
		flux_inicial->SetBinContent(i+1,(Seed[i]/E_mid)*dE[i]); //integral
		// flux_inicial->SetBinContent(i+1,Seed[i]); //integral
}

TCanvas *canvas_expacs = new TCanvas("expacs","expacs",1920,1080);

flux_inicial->GetXaxis()->SetTitle("#bf{Neutron Energy [MeV]}");
flux_inicial->GetXaxis()->SetTitleOffset(1.2);
flux_inicial->GetXaxis()->CenterTitle();
flux_inicial->GetXaxis()->SetTitleSize(0.04);
flux_inicial->SetStats(0);

		if(flux_representation=="Integral")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{#Phi(E)#timesdE [cm^{-2} s^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.4);
			}
		if(flux_representation=="Lethargy")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{E#times#Phi(E) [cm^{-2} s^{-1} lethargy^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.7);
			}
		if(flux_representation=="Differential")
			{
				flux_inicial->GetYaxis()->SetTitle("#bf{#Phi(E) [cm^{-2} s^{-1} MeV^{-1}]}");
				flux_inicial->GetYaxis()->SetTitleOffset(1.3);
			}


gPad->SetLogx();
gPad->SetLeftMargin(0.13);
gPad->SetRightMargin(0.009);
flux_inicial->GetYaxis()->CenterTitle();
flux_inicial->GetYaxis()->SetTitleSize(0.04);
//~ flux_deconv_2_dot_error->GetYaxis()->SetRangeUser(0,flux_inicial->GetMaximum());
//~ Double_t max_y = flux_inicial->GetMaximum();
//~ flux_deconv_2_dot_error->SetMaximum(max_y+max_y*0.1);

return flux_inicial;
delete canvas_expacs;
//~ flux_inicial->Draw("HIST");


}

void plot_several_seed(){

TH1D* seed_1 = plot_expacs_seed_TH1D("LCO",1,"Lethargy");
TH1D* seed_2 = plot_expacs_seed_TH1D("LCO",6,"Lethargy");
TH1D* seed_3 = plot_expacs_seed_TH1D("LCO",51,"Lethargy");
TH1D* seed_4 = plot_expacs_seed_TH1D("LCO",101,"Lethargy");
TH1D* seed_5 = plot_expacs_seed_TH1D("LCO",156,"Lethargy");
TH1D* seed_6 = plot_expacs_seed_TH1D("LCO",161,"Lethargy");
TH1D* seed_7 = plot_expacs_seed_TH1D("LCO",181,"Lethargy");
TH1D* seed_8 = plot_expacs_seed_TH1D("LCO",186,"Lethargy");

TCanvas *canvas_expacs_seed = new TCanvas("expacs_seed","expacs_seed",1920,1080);

gPad->SetLogx();
gPad->SetLeftMargin(0.13);
gPad->SetRightMargin(0.009);

seed_1->SetLineColor(kRed);
seed_2->SetLineColor(kBlue);
seed_3->SetLineColor(kGreen);
seed_4->SetLineColor(kOrange);
seed_5->SetLineColor(kCyan);
seed_6->SetLineColor(kMagenta);
seed_7->SetLineColor(kOrange+3);
seed_8->SetLineColor(kAzure+1);

seed_1->SetLineWidth(2);
seed_2->SetLineWidth(2);
seed_3->SetLineWidth(2);
seed_4->SetLineWidth(2);
seed_5->SetLineWidth(2);
seed_6->SetLineWidth(2);
seed_7->SetLineWidth(2);
seed_8->SetLineWidth(2);

seed_1->Draw("HIST");
seed_2->Draw("HIST SAME");
seed_3->Draw("HIST SAME");
seed_4->Draw("HIST SAME");
seed_5->Draw("HIST SAME");
seed_6->Draw("HIST SAME");
seed_7->Draw("HIST SAME");
seed_8->Draw("HIST SAME");

TLegend *legend_c = new TLegend(0.32,0.59,0.59,0.82);
legend_c->AddEntry(seed_1,seed_1->GetTitle(),"l");
legend_c->AddEntry(seed_2,seed_2->GetTitle(),"l");
legend_c->AddEntry(seed_3,seed_3->GetTitle(),"l");
legend_c->AddEntry(seed_4,seed_4->GetTitle(),"l");
legend_c->AddEntry(seed_5,seed_5->GetTitle(),"l");
legend_c->AddEntry(seed_6,seed_6->GetTitle(),"l");
legend_c->AddEntry(seed_7,seed_7->GetTitle(),"l");
legend_c->AddEntry(seed_8,seed_8->GetTitle(),"l");


//~ legend_c->AddEntry(flux_deconv_2,"Flux deconv EM_MC_stop_random_seed","l");
//~ legend_c->AddEntry(flux_deconv,name_hist_deconv_legend.c_str(),"l");
legend_c->Draw();

}
	


void loop_plot_deconv_over_events(string campaign, int event_inf, int event_sup, int steps, int time_grid, int ndet, string flux_representation, int bin_seed)
{
	for (int i=event_inf;i<=event_sup;i++)
		{
		 plot_deconv_spectrum_with_error(campaign,i,steps,time_grid,ndet,flux_representation,bin_seed);
		}
}

void routine_final_plot_lco_15min()
{
  loop_plot_deconv_over_events("LCO",1,21,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",23,45,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",49,69,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",71,83,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",85,110,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",112,239,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",241,272,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",275,283,0,15,11,"Lethargy",51);
  loop_plot_deconv_over_events("LCO",285,289,0,15,11,"Lethargy",51);
}

void em_mc_graph_loop(string campaign, int event, int timegrid, int step_filter){

auto start = std::chrono::system_clock::now();

auto poolSize = ROOT::GetThreadPoolSize(); //number of cores available
ROOT::EnableImplicitMT(poolSize-2);


for(int i = 1; i<130;i++)
	{
		em_mc_graph(campaign,event,timegrid,step_filter,i);
	}

auto end = std::chrono::system_clock::now();
std::chrono::duration<float,std::ratio<60>> duration = end - start; //hours
cout << duration.count() << "min " << endl;

}

void compare_sigma_perc(){

string fit_1 = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_LCO_event_41_5e05_it.root";
string fit_2 = "./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_LCO_event_41_2e04_it.root";
ROOT::RDataFrame df_fit_1("fit_loop_tree", fit_1);
ROOT::RDataFrame df_fit_2("fit_loop_tree", fit_2);

auto fit_1_vec_sigma = df_fit_1.Take<double>("sigma_perc").GetValue();
auto fit_2_vec_sigma = df_fit_2.Take<double>("sigma_perc").GetValue();

//~ auto hist_d01 = df_complete.Filter("NEUrate_D01>=0").Histo1D({"CR_d01", "Counting rate d01", 300, 0., 300}, "time_in_s");
//~ auto myProf1 = df_complete.Profile1D({"profName", "profTitle", 1000, 1., 1000.}, "NEUrate_D01", "VWC_20cm");
//~ auto myProf1 = df_complete.Profile1D({"profName", "profTitle", 1000, 1., 1000.}, "NEUrate_D01", "Rain_mm_acc");
//~ auto myProf1 = df_complete.Profile1D({"profName", "profTitle", 672, 0., 86400*7}, "rdfentry_", "NEUrate_D01");

/**************Energy Bin********************/
auto seed_flux_expacs_csv ="./EXPACS_Data/EXPACS_Calc_nflux/csv_files/LasCampanasAtacama_2.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"lower_edge_binvalue",double_type},{"bin_width", double_type},{"flux_value", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(seed_flux_expacs_csv,true,delimiter,-1, std::move(msdata_map));
/*Seleccionamos los datos del flujo semilla para LCO*/
auto d_entries = seed_rdf.Count().GetValue();
/*Numero de bines*/
int binnum = d_entries-1;
/*Generamos el vector de bordes de bin*/
auto df_binedges_vec = seed_rdf.Take<double>("lower_edge_binvalue").GetValue();
//*Generamos el vector de ancho de energias*/
auto df_dE_vec = seed_rdf.Take<double>("bin_width").GetValue();


/****Definimos los histogramas****/

/*borde de bines como array*/
double *bins = df_binedges_vec.data();


//~ auto profile_model_1 = ROOT::RDF::TProfile1DModel("fit_1_5e05_it","fit_1_5e05_it", binnum, bins, "");
//~ auto profile_model_2 = ROOT::RDF::TProfile1DModel("fit_1_2e04_it","fit_2_2e04_it", binnum, bins, "");

TCanvas *counting_rate_canvas = new TCanvas("Compare fit","Compare fit");

//~ auto myProf_fit_1 = df_fit_1.Profile1D({"fit_1_5e05_it", "fit_1_5e05_it", 129, 0., 129}, "rdfentry_", "sigma_perc");
//~ auto myProf_fit_1 = df_fit_1.Profile1D(profile_model, "rdfentry_", "sigma_perc");
//~ auto myProf_fit_2 = df_fit_2.Profile1D({"fit_2_2e04_it", "fit_2_2e04_it", 129, 0., 129}, "rdfentry_", "sigma_perc");

TH1D* h_fit_1 = new TH1D("fit_1_5e05_it","fit_1_5e05_it", binnum, bins);
TH1D* h_fit_2 = new TH1D("fit_2_2e04_it","fit_2_2e04_it", binnum, bins);

for (int i = 0; i<df_binedges_vec.size(); i++)
	{
		h_fit_1->SetBinContent(i+1,fit_1_vec_sigma[i]);
		h_fit_2->SetBinContent(i+1,fit_2_vec_sigma[i]); 
	}

h_fit_1->SetLineColor(kRed);
h_fit_2->SetLineColor(kBlue);

//~ TH1D *h_fit_1 = (TH1D*)myProf_fit_1->Clone("fit_1_5e05_it");
//~ TH1D *h_fit_2 = (TH1D*)myProf_fit_2->Clone("fit_2_5e05_it");

h_fit_1->GetYaxis()->SetTitle("%#sigma/mean" );
h_fit_1->GetXaxis()->SetTitle("Energy [MeV]" );

h_fit_1->DrawClone("HIST");
h_fit_2->DrawClone("HIST SAME");
gPad->SetLogx();


 TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
 legend->AddEntry(h_fit_1,"fit_1_5e05_it","l");
 legend->AddEntry(h_fit_2,"fit_2_2e04_it","l");
 legend->Draw();

counting_rate_canvas->Draw();


//~ TCanvas *spectrum_canvas = new TCanvas("Compare fit","Compare fit");


//~ TH1D* spec_1 = new TH1D("spec_1_5e05_it","spec_1_5e05_it", binnum, bins);
//~ TH1D* spec_2 = new TH1D("spec_2_2e04_it","spec_2_2e04_it", binnum, bins);

}

void integral_data_merge(string campaign, int time_grid, int ndet){

ostringstream stream_timegrid, stream_ndet;
stream_timegrid << time_grid;
stream_ndet << ndet;
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

vector<double> event_vec;
vector<double> intg_total_vec;
vector<double> intg_th_vec;
vector<double> intg_ep_vec;
vector<double> intg_fs_vec;
vector<double> intg_he_vec;
vector<double> ratio_th_tot_vec;
vector<double> ratio_ep_tot_vec;
vector<double> ratio_fs_tot_vec;
vector<double> ratio_he_tot_vec;
vector<double> eta_th_vec;
vector<double> eta_ep_vec;
vector<double> eta_fs_vec;
vector<double> err_intg_total_vec;
vector<double> err_intg_th_vec;
vector<double> err_intg_ep_vec;
vector<double> err_intg_fs_vec;
vector<double> err_intg_he_vec;
vector<double> err_ratio_th_tot_vec;
vector<double> err_ratio_ep_tot_vec;
vector<double> err_ratio_fs_tot_vec;
vector<double> err_ratio_he_tot_vec;
vector<double> err_eta_th_vec;
vector<double> err_eta_ep_vec;
vector<double> err_eta_fs_vec;
vector<vector<double>> deconv_matrix_MC;
vector<vector<double>> deconv_sigma_Matrix_MC;

for(int i=1;i<=289;i++)
	{
		ostringstream  stream_event_i;
		stream_event_i << i; 
		string str_stream_event_i = stream_event_i.str();

		string fit_event_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event_i+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_update.root";
		
		//~ TFile *event_file = TFile::Open(fit_event_file_name.c_str());
		
		TFile *event_file = new TFile(fit_event_file_name.c_str());
		
		if(event_file->IsZombie())
			{
				cout << "There is no .root file" << endl;

				vector<double> deconv_vec_zero_MC(130,0.0);
				vector<double> deconv_sigma_vec_zero_MC(130,0.0);
				
				intg_total_vec.push_back(0);
				intg_th_vec.push_back(0);
				intg_ep_vec.push_back(0);
				intg_fs_vec.push_back(0);
				intg_he_vec.push_back(0);
				ratio_th_tot_vec.push_back(0);
                ratio_ep_tot_vec.push_back(0);
                ratio_fs_tot_vec.push_back(0);
                ratio_he_tot_vec.push_back(0);
                eta_th_vec.push_back(0);
                eta_ep_vec.push_back(0);
                eta_fs_vec.push_back(0);
                err_intg_total_vec.push_back(0);
                err_intg_th_vec.push_back(0);
                err_intg_ep_vec.push_back(0);
                err_intg_fs_vec.push_back(0);
                err_intg_he_vec.push_back(0);
                err_ratio_th_tot_vec.push_back(0);
                err_ratio_ep_tot_vec.push_back(0);
                err_ratio_fs_tot_vec.push_back(0);
                err_ratio_he_tot_vec.push_back(0);
                err_eta_th_vec.push_back(0);
                err_eta_ep_vec.push_back(0);
                err_eta_fs_vec.push_back(0);
                deconv_matrix_MC.push_back(deconv_vec_zero_MC);
                deconv_sigma_Matrix_MC.push_back(deconv_sigma_vec_zero_MC);
                

				delete event_file;

			}
			
		else
			{
					//~ string fit_event_file_name ="./deconv_mc_data_energy_fitting/EM_MC_fit_parameters_campaign_"+campaign+"_event_"+str_stream_event_i+"_update.root";
					ROOT::RDataFrame df_fit_event("fit_loop_tree_update", fit_event_file_name);

					auto intg_total_value = df_fit_event.Take<double>("Intg_total").GetValue();
					auto intg_th_value = df_fit_event.Take<double>("Intg_th").GetValue();
					auto intg_ep_value = df_fit_event.Take<double>("Intg_ep").GetValue();
					auto intg_fs_value = df_fit_event.Take<double>("Intg_fs").GetValue();
					auto intg_he_value = df_fit_event.Take<double>("Intg_he").GetValue();
					auto ratio_th_tot_value = df_fit_event.Take<double>("ratio_th_tot").GetValue();
					auto ratio_ep_tot_value = df_fit_event.Take<double>("ratio_ep_tot").GetValue();
					auto ratio_fs_tot_value = df_fit_event.Take<double>("ratio_fs_tot").GetValue();
					auto ratio_he_tot_value = df_fit_event.Take<double>("ratio_he_tot").GetValue();
					auto eta_th_value = df_fit_event.Take<double>("eta_th").GetValue();
					auto eta_ep_value = df_fit_event.Take<double>("eta_ep").GetValue();
					auto eta_fs_value = df_fit_event.Take<double>("eta_fs").GetValue();
					auto err_intg_total_value = df_fit_event.Take<double>("err_intg_total").GetValue();
					auto err_intg_th_value = df_fit_event.Take<double>("err_intg_th").GetValue();
					auto err_intg_ep_value = df_fit_event.Take<double>("err_intg_ep").GetValue();
					auto err_intg_fs_value = df_fit_event.Take<double>("err_intg_fs").GetValue();
					auto err_intg_he_value = df_fit_event.Take<double>("err_intg_he").GetValue();
					auto err_ratio_th_tot_value = df_fit_event.Take<double>("err_ratio_th_tot").GetValue();
					auto err_ratio_ep_tot_value = df_fit_event.Take<double>("err_ratio_ep_tot").GetValue();
					auto err_ratio_fs_tot_value = df_fit_event.Take<double>("err_ratio_fs_tot").GetValue();
					auto err_ratio_he_tot_value = df_fit_event.Take<double>("err_ratio_he_tot").GetValue();
					auto err_eta_th_value = df_fit_event.Take<double>("err_eta_th").GetValue();
					auto err_eta_ep_value = df_fit_event.Take<double>("err_eta_ep").GetValue();
					auto err_eta_fs_value = df_fit_event.Take<double>("err_eta_fs").GetValue();

					auto deconv_vec_mc = df_fit_event.Take<vector<double>>("deconv_vec_MC").GetValue();
					auto deconv_sigma_vec_mc = df_fit_event.Take<vector<double>>("deconv_sigma_vec_MC").GetValue();


				
					intg_total_vec.push_back(intg_total_value[0]);
					intg_th_vec.push_back(intg_th_value[0]);
                    intg_ep_vec.push_back(intg_ep_value[0]);
                    intg_fs_vec.push_back(intg_fs_value[0]);
                    intg_he_vec.push_back(intg_he_value[0]);
                    ratio_th_tot_vec.push_back(ratio_th_tot_value[0]);
                    ratio_ep_tot_vec.push_back(ratio_ep_tot_value[0]);
                    ratio_fs_tot_vec.push_back(ratio_fs_tot_value[0]);
                    ratio_he_tot_vec.push_back(ratio_he_tot_value[0]);
                    eta_th_vec.push_back(eta_th_value[0]);
                    eta_ep_vec.push_back(eta_ep_value[0]);
                    eta_fs_vec.push_back(eta_fs_value[0]);
                    err_intg_total_vec.push_back(err_intg_total_value[0]);
                    err_intg_th_vec.push_back(err_intg_th_value[0]);
                    err_intg_ep_vec.push_back(err_intg_ep_value[0]);
                    err_intg_fs_vec.push_back(err_intg_fs_value[0]);
                    err_intg_he_vec.push_back(err_intg_he_value[0]);
                    err_ratio_th_tot_vec.push_back(err_ratio_th_tot_value[0]);
                    err_ratio_ep_tot_vec.push_back(err_ratio_ep_tot_value[0]);
                    err_ratio_fs_tot_vec.push_back(err_ratio_fs_tot_value[0]);
                    err_ratio_he_tot_vec.push_back(err_ratio_he_tot_value[0]);
                    err_eta_th_vec.push_back(err_eta_th_value[0]);
					err_eta_ep_vec.push_back(err_eta_ep_value[0]);
					err_eta_fs_vec.push_back(err_eta_fs_value[0]);

					deconv_matrix_MC.push_back(deconv_vec_mc[0]);
					deconv_sigma_Matrix_MC.push_back(deconv_sigma_vec_mc[0]);
					


					delete event_file;
			 }

		event_vec.push_back(i);

		
	}


int event_id = 0;
int intg_total_id = 0;
int intg_th_id = 0;
int intg_ep_id = 0;
int intg_fs_id = 0;
int intg_he_id = 0;
int ratio_th_tot_id = 0;
int ratio_ep_tot_id = 0;
int ratio_fs_tot_id = 0;
int ratio_he_tot_id = 0;
int eta_th_id = 0;
int eta_ep_id = 0;
int eta_fs_id = 0;
int err_intg_total_id = 0;
int err_intg_th_id = 0;
int err_intg_ep_id = 0;
int err_intg_fs_id = 0;
int err_intg_he_id = 0;
int err_ratio_th_tot_id = 0;
int err_ratio_ep_tot_id = 0;
int err_ratio_fs_tot_id = 0;
int err_ratio_he_tot_id = 0;
int err_eta_th_id = 0;
int err_eta_ep_id = 0;
int err_eta_fs_id = 0;

int deconv_matrix_MC_id = 0;
int deconv_sigma_Matrix_MC_id = 0;

ROOT::RDataFrame  df_fit_file_new(289);
auto  df_fit_file_update =  df_fit_file_new.Define("event_id",[&]() {
												auto event_elem = event_vec[event_id];
												event_id++;
												return event_elem;
											})
											.Define("Intg_total",[&]() {
												auto intg_total_elem = intg_total_vec[intg_total_id];
												intg_total_id++;
												return intg_total_elem;
											})
											.Define("Intg_th",[&]() {
												auto intg_th_elem = intg_th_vec[intg_th_id];
												intg_th_id++;
												return intg_th_elem;
											})
											.Define("Intg_ep",[&]() {
												auto intg_ep_elem = intg_ep_vec[intg_ep_id];
												intg_ep_id++;
												return intg_ep_elem;
											})
											.Define("Intg_fs",[&]() {
												auto intg_fs_elem = intg_fs_vec[intg_fs_id];
												intg_fs_id++;
												return intg_fs_elem;
											})
											.Define("Intg_he",[&]() {
												auto intg_he_elem = intg_he_vec[intg_he_id];
												intg_he_id++;
												return intg_he_elem;
											})
											.Define("ratio_th_tot",[&]() {
												auto ratio_th_tot_elem = ratio_th_tot_vec[ratio_th_tot_id];
												ratio_th_tot_id++;
												return ratio_th_tot_elem;
											})
											.Define("ratio_ep_tot",[&]() {
												auto ratio_ep_tot_elem = ratio_ep_tot_vec[ratio_ep_tot_id];
												ratio_ep_tot_id++;
												return ratio_ep_tot_elem;
											})
											.Define("ratio_fs_tot",[&]() {
												auto ratio_fs_tot_elem = ratio_fs_tot_vec[ratio_fs_tot_id];
												ratio_fs_tot_id++;
												return ratio_fs_tot_elem;
											})
											.Define("ratio_he_tot",[&]() {
												auto ratio_he_tot_elem = ratio_he_tot_vec[ratio_he_tot_id];
												ratio_he_tot_id++;
												return ratio_he_tot_elem;
											})
											.Define("eta_th",[&]() {
												auto eta_th_elem = eta_th_vec[eta_th_id];
												eta_th_id++;
												return eta_th_elem;
											})
											.Define("eta_ep",[&]() {
												auto eta_ep_elem = eta_ep_vec[eta_ep_id];
												eta_ep_id++;
												return eta_ep_elem;
											})
											.Define("eta_fs",[&]() {
												auto eta_fs_elem = eta_fs_vec[eta_fs_id];
												eta_fs_id++;
												return eta_fs_elem;
											})
											.Define("err_intg_total",[&]() {
												auto err_intg_total_elem = err_intg_total_vec[err_intg_total_id];
												err_intg_total_id++;
												return err_intg_total_elem;
											})
											.Define("err_intg_th",[&]() {
												auto err_intg_th_elem = err_intg_th_vec[err_intg_th_id];
												err_intg_th_id++;
												return err_intg_th_elem;
											})
											.Define("err_intg_ep",[&]() {
												auto err_intg_ep_elem = err_intg_ep_vec[err_intg_ep_id];
												err_intg_ep_id++;
												return err_intg_ep_elem;
											})
											.Define("err_intg_fs",[&]() {
												auto err_intg_fs_elem = err_intg_fs_vec[err_intg_fs_id];
												err_intg_fs_id++;
												return err_intg_fs_elem;
											})
											.Define("err_intg_he",[&]() {
												auto err_intg_he_elem = err_intg_he_vec[err_intg_he_id];
												err_intg_he_id++;
												return err_intg_he_elem;
											})
											.Define("err_ratio_th_tot",[&]() {
												auto err_ratio_th_tot_elem = err_ratio_th_tot_vec[err_ratio_th_tot_id];
												err_ratio_th_tot_id++;
												return err_ratio_th_tot_elem;
											})
											.Define("err_ratio_ep_tot",[&]() {
												auto err_ratio_ep_tot_elem = err_ratio_ep_tot_vec[err_ratio_ep_tot_id];
												err_ratio_ep_tot_id++;
												return err_ratio_ep_tot_elem;
											})
											.Define("err_ratio_fs_tot",[&]() {
												auto err_ratio_fs_tot_elem = err_ratio_fs_tot_vec[err_ratio_fs_tot_id];
												err_ratio_fs_tot_id++;
												return err_ratio_fs_tot_elem;
											})
											.Define("err_ratio_he_tot",[&]() {
												auto err_ratio_he_tot_elem = err_ratio_he_tot_vec[err_ratio_he_tot_id];
												err_ratio_he_tot_id++;
												return err_ratio_he_tot_elem;
											})
											.Define("err_eta_th",[&]() {
												auto err_eta_th_elem = err_eta_th_vec[err_eta_th_id];
												err_eta_th_id++;
												return err_eta_th_elem;
											})
											.Define("err_eta_ep",[&]() {
												auto err_eta_ep_elem = err_eta_ep_vec[err_eta_ep_id];
												err_eta_ep_id++;
												return err_eta_ep_elem;
											})
											.Define("err_eta_fs",[&]() {
												auto err_eta_fs_elem = err_eta_fs_vec[err_eta_fs_id];
												err_eta_fs_id++;
												return err_eta_fs_elem;
											})
											.Define("flux_intg_MC",[&]() {
												auto deconv_vec_element =  deconv_matrix_MC[deconv_matrix_MC_id];
												deconv_matrix_MC_id++;
												return deconv_vec_element;
											})
											.Define("err_flux_intg_MC",[&]() {
												auto err_deconv_vec_element =  deconv_sigma_Matrix_MC[deconv_sigma_Matrix_MC_id];
												deconv_sigma_Matrix_MC_id++;
												return err_deconv_vec_element;
											});
	
	


										
string fit_event_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_update_merge.root";
df_fit_file_update.Snapshot("fit_loop_tree_update",fit_event_file_name); /*Save selected columns to disk, in a new TTree treename in file filename*/



}

void plot_data_merge(string campaign, int time_grid, int ndet)
{

ostringstream stream_timegrid, stream_ndet;
stream_timegrid << time_grid;
stream_ndet << ndet;
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();



string merge_data_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_update_merge.root";
ROOT::RDataFrame df_merge_data("fit_loop_tree_update", merge_data_file_name);

auto Intg_total_error_vec = df_merge_data.Take<double>("err_intg_total").GetValue();
auto Intg_th_error_vec = df_merge_data.Take<double>("err_intg_th").GetValue();
RVec<double> Intg_ep_error_vec = df_merge_data.Take<double>("err_intg_ep").GetValue();
auto Intg_fs_error_vec = df_merge_data.Take<double>("err_intg_fs").GetValue();
auto Intg_he_error_vec = df_merge_data.Take<double>("err_intg_he").GetValue();


auto lambda_ratio_intg_num_den = [&](double &Intg_num, double &Intg_den){
		if(Intg_num==0 && Intg_den ==0)
			{return 0.;}
		else{
		double ratio = (Intg_num/Intg_den);
		return ratio;
			}
};

auto lambda_sum_intg_sum1_sum2 = [&](double &Intg_sum1, double &Intg_sum2){
		if(Intg_sum1==0 && Intg_sum2 ==0)
			{return 0.;}
		else{
		double sum = Intg_sum1 + Intg_sum2;
		return sum;
			}
};

auto lambda_err_ratio_intg_num_den = [&](double &Intg_num, double &Intg_den, double &err_intg_num, double &err_intg_den){
		if(Intg_num==0 && Intg_den ==0)
			{return 0.;}
		else{
		double err = (Intg_num/Intg_den)*sqrt(pow(err_intg_num/Intg_num,2) + pow(err_intg_den/Intg_den,2));
		return err;
			}
};

auto lambda_err_sum_intg_sum1_sum2 = [&](double &Intg_sum1, double &Intg_sum2, double &err_intg_sum1, double &err_intg_sum2){
		if(Intg_sum1==0 && Intg_sum2==0)
			{return 0.;}
		else{
		double err = sqrt(pow(err_intg_sum1,2) + pow(err_intg_sum2,2));
		return err;
			}
};

auto df_merge_data_new = df_merge_data.Define("err_event","err_intg_ep*0.")
									  .Define("ratio_intg_th_ep",lambda_ratio_intg_num_den,{"Intg_th","Intg_ep"})
									  .Define("ratio_intg_th_fs",lambda_ratio_intg_num_den,{"Intg_th","Intg_fs"})
									  .Define("ratio_intg_fs_ep",lambda_ratio_intg_num_den,{"Intg_fs","Intg_ep"})
									  .Define("ratio_intg_th_total",lambda_ratio_intg_num_den,{"Intg_th","Intg_total"})
									  .Define("err_ratio_intg_th_ep",lambda_err_ratio_intg_num_den,{"Intg_th","Intg_ep","err_intg_th","err_intg_ep"})
									  .Define("err_ratio_intg_th_fs",lambda_err_ratio_intg_num_den,{"Intg_th","Intg_fs","err_intg_th","err_intg_fs"})
									  .Define("err_ratio_intg_fs_ep",lambda_err_ratio_intg_num_den,{"Intg_fs","Intg_ep","err_intg_fs","err_intg_ep"})
									  .Define("err_ratio_intg_th_total",lambda_err_ratio_intg_num_den,{"Intg_th","Intg_total","err_intg_th","err_intg_total"})
									  .Define("sum_intg_fs_ep",lambda_sum_intg_sum1_sum2,{"Intg_fs","Intg_ep"})
									  .Define("sum_intg_fs_ep_he",lambda_sum_intg_sum1_sum2,{"sum_intg_fs_ep","Intg_he"})
									  .Define("err_sum_intg_sum_fs_ep",lambda_err_sum_intg_sum1_sum2,{"Intg_fs","Intg_ep","err_intg_fs","err_intg_ep"})
									  .Define("err_sum_intg_sum_fs_ep_he",lambda_err_sum_intg_sum1_sum2,{"err_sum_intg_sum_fs_ep","Intg_he","err_sum_intg_sum_fs_ep","err_intg_he"})
									  .Define("ratio_intg_th_sum_fs_ep",lambda_ratio_intg_num_den,{"Intg_th","sum_intg_fs_ep"})
									  .Define("ratio_intg_th_sum_fs_ep_he",lambda_ratio_intg_num_den,{"Intg_th","sum_intg_fs_ep_he"})
									  .Define("err_ratio_intg_th_sum_fs_ep",lambda_err_ratio_intg_num_den,{"Intg_th","sum_intg_fs_ep","err_intg_th","err_sum_intg_sum_fs_ep"})
									  .Define("err_ratio_intg_th_sum_fs_ep_he",lambda_err_ratio_intg_num_den,{"Intg_th","sum_intg_fs_ep_he","err_intg_th","err_sum_intg_sum_fs_ep_he"});
									  
									  
									  

//~ auto myHist0 = df_merge_data.Histo1D({"histName0", "histTitle0", 24*7, 0.,  86400*7}, "Time_in_s");

//~ auto myProf_Intg_total = df_merge_data.Profile1D({"Intg_total", "Intg_total", 289, 1., 290}, "event_id", "Intg_total");
//~ auto myProf_Intg_th = df_merge_data.Profile1D({"Intg_th", "Intg_th", 289, 1., 290}, "event_id", "Intg_th");
//~ auto myProf_Intg_ep = df_merge_data.Profile1D({"Intg_ep", "Intg_ep", 289, 1., 290}, "event_id", "Intg_ep");
//~ auto myProf_Intg_fs = df_merge_data.Profile1D({"Intg_fs", "Intg_fs", 289, 1., 290}, "event_id", "Intg_fs");
//~ auto myProf_Intg_he = df_merge_data.Profile1D({"Intg_he", "Intg_he", 289, 1., 290}, "event_id", "Intg_he");

//~ TH1D *h_Intg_total = (TH1D*)myProf_Intg_total->Clone("Intg_total");
//~ TH1D *h_Intg_th = (TH1D*)myProf_Intg_th->Clone("Intg_th");
//~ TH1D *h_Intg_ep = (TH1D*)myProf_Intg_ep->Clone("Intg_ep");
//~ TH1D *h_Intg_fs = (TH1D*)myProf_Intg_fs->Clone("Intg_fs");
//~ TH1D *h_Intg_he = (TH1D*)myProf_Intg_he->Clone("Intg_he");

//~ RVec<double> Intg_ep_error_vec_low = Intg_ep_error_vec/2.;
//~ RVec<double> Intg_ep_error_vec_up = Intg_ep_error_vec/2.;

//~ double *array_intg_ep_err_low = Intg_ep_error_vec_low.data();
//~ double *array_intg_ep_err_up = Intg_ep_error_vec_up.data();


//~ hist_intg_ep->SetMarkerSize(1);


//~ h_Intg_fs->SetLineColor(kGreen-9);
//~ h_Intg_he->SetLineColor(kRed-9);

//~ h_Intg_ep->SetFillColor(kCyan-9);

TCanvas *canvas_intg = new TCanvas("Integrales","Integrales",689,1040);

canvas_intg->Divide(1,5);


int n = Intg_total_error_vec.size();
auto hist_intg_total_tg = df_merge_data_new.GraphAsymmErrors("event_id","Intg_total","err_event","err_event","err_intg_total","err_intg_total");
auto hist_intg_th_tg = df_merge_data_new.GraphAsymmErrors("event_id","Intg_th","err_event","err_event","err_intg_th","err_intg_th");
auto hist_intg_ep_tg = df_merge_data_new.GraphAsymmErrors("event_id","Intg_ep","err_event","err_event","err_intg_ep","err_intg_ep");
auto hist_intg_fs_tg = df_merge_data_new.GraphAsymmErrors("event_id","Intg_fs","err_event","err_event","err_intg_fs","err_intg_fs");
auto hist_intg_he_tg = df_merge_data_new.GraphAsymmErrors("event_id","Intg_he","err_event","err_event","err_intg_he","err_intg_he");


// Clonamos para que muestre corectamente el color en TLegend
auto *hist_intg_total = (TGraphAsymmErrors*)hist_intg_total_tg->Clone("Intg_total");
auto *hist_intg_th = (TGraphAsymmErrors*)hist_intg_th_tg->Clone("Intg_th");
auto *hist_intg_ep = (TGraphAsymmErrors*)hist_intg_ep_tg->Clone("Intg_ep");
auto *hist_intg_fs = (TGraphAsymmErrors*)hist_intg_fs_tg->Clone("Intg_fs");
auto *hist_intg_he = (TGraphAsymmErrors*)hist_intg_he_tg->Clone("Intg_he");

hist_intg_total->SetTitle("#bf{Integral total flux}");
hist_intg_th->SetTitle("#bf{Integral thermal flux }");
hist_intg_ep->SetTitle("#bf{Integral epithermal flux}");
hist_intg_fs->SetTitle("#bf{Integral fast flux}");
hist_intg_he->SetTitle("#bf{Integral high energy flux}");

hist_intg_total->GetXaxis()->SetTitleSize(0.06);
hist_intg_total->GetXaxis()->SetTitleOffset(0.8);
hist_intg_total->GetXaxis()->SetLabelSize(0.06);

hist_intg_total->GetYaxis()->CenterTitle();
hist_intg_total->GetYaxis()->SetTitleSize(0.08);
hist_intg_total->GetYaxis()->SetTitleOffset(0.6);
hist_intg_total->GetYaxis()->SetLabelSize(0.06);

hist_intg_th->GetXaxis()->SetTitleSize(0.06);
hist_intg_th->GetXaxis()->SetTitleOffset(0.8);
hist_intg_th->GetXaxis()->SetLabelSize(0.06);
		  
hist_intg_th->GetYaxis()->CenterTitle();
hist_intg_th->GetYaxis()->SetTitleSize(0.08);
hist_intg_th->GetYaxis()->SetTitleOffset(0.6);
hist_intg_th->GetYaxis()->SetLabelSize(0.06);

hist_intg_ep->GetXaxis()->SetTitleSize(0.06);
hist_intg_ep->GetXaxis()->SetTitleOffset(0.8);
hist_intg_ep->GetXaxis()->SetLabelSize(0.06);
		  
hist_intg_ep->GetYaxis()->CenterTitle();
hist_intg_ep->GetYaxis()->SetTitleSize(0.08);
hist_intg_ep->GetYaxis()->SetTitleOffset(0.6);
hist_intg_ep->GetYaxis()->SetLabelSize(0.06);

hist_intg_fs->GetXaxis()->SetTitleSize(0.06);
hist_intg_fs->GetXaxis()->SetTitleOffset(0.8);
hist_intg_fs->GetXaxis()->SetLabelSize(0.06);
		  
hist_intg_fs->GetYaxis()->CenterTitle();
hist_intg_fs->GetYaxis()->SetTitleSize(0.08);
hist_intg_fs->GetYaxis()->SetTitleOffset(0.6);
hist_intg_fs->GetYaxis()->SetLabelSize(0.06);

hist_intg_he->GetXaxis()->SetTitleSize(0.06);
hist_intg_he->GetXaxis()->SetTitleOffset(0.8);
hist_intg_he->GetXaxis()->SetLabelSize(0.06);
		  
hist_intg_he->GetYaxis()->CenterTitle();
hist_intg_he->GetYaxis()->SetTitleSize(0.08);
hist_intg_he->GetYaxis()->SetTitleOffset(0.6);
hist_intg_he->GetYaxis()->SetLabelSize(0.06);


hist_intg_total->GetYaxis()->SetTitle("#bf{#Phi_{total} (cm^{-2} s^{-1})}");
hist_intg_total->GetXaxis()->SetTitle("#bf{Event}");

hist_intg_th->GetYaxis()->SetTitle("#bf{#Phi_{th} (cm^{-2} s^{-1})}");
hist_intg_th->GetXaxis()->SetTitle("#bf{Event}");

hist_intg_ep->GetYaxis()->SetTitle("#bf{#Phi_{ep} (cm^{-2} s^{-1})}");
hist_intg_ep->GetXaxis()->SetTitle("#bf{Event}");

hist_intg_fs->GetYaxis()->SetTitle("#bf{#Phi_{fs} (cm^{-2} s^{-1})}");
hist_intg_fs->GetXaxis()->SetTitle("#bf{Event}");

hist_intg_he->GetYaxis()->SetTitle("#bf{#Phi_{he} (cm^{-2} s^{-1})}");
hist_intg_he->GetXaxis()->SetTitle("#bf{Event}");

hist_intg_total->SetLineColor(kBlue);
hist_intg_th->SetLineColor(kGray);
hist_intg_ep->SetLineColor(kCyan-9);
hist_intg_fs->SetLineColor(kGreen-9);
hist_intg_he->SetLineColor(kRed-9);

hist_intg_total->SetMarkerStyle(20);
hist_intg_th->SetMarkerStyle(20);
hist_intg_ep->SetMarkerStyle(20);
hist_intg_fs->SetMarkerStyle(20);
hist_intg_he->SetMarkerStyle(20);

//~ hist_intg_total->SetFillColor(kBlue);
//~ hist_intg_total->SetFillStyle(3144);

hist_intg_total->SetLineWidth(2);
hist_intg_th->SetLineWidth(2);
hist_intg_ep->SetLineWidth(2);
hist_intg_fs->SetLineWidth(2);
hist_intg_he->SetLineWidth(2);

hist_intg_total->SetMarkerSize(1);


TLatex *lco_campg = new TLatex(0.1,0.91,(campaign+" Campaign").c_str());
TLatex *lco_date = new TLatex(0.68,0.91,"2023-07-10/2023-07-13");
TLatex *lco_masl = new TLatex(0.13,0.81,"2319 masl, R_{c}= 10.31 GV");

lco_campg->SetTextColor(kBlack);
lco_date->SetTextColor(kBlack);
lco_masl->SetTextColor(kBlack);
lco_campg->SetNDC(true);
lco_date->SetNDC(true);
lco_masl->SetNDC(true);
lco_campg->SetTextSize(0.08);
lco_date->SetTextSize(0.08);
lco_masl->SetTextSize(0.06);

canvas_intg->cd(1);
/*FIT & get parameters*/
gStyle->SetTitleFontSize(0.1);
hist_intg_total->GetXaxis()->SetRangeUser(0,290);
hist_intg_total->SetMinimum(0.0);
TF1* fit_lin_1 = new TF1("fit_lin1","pol0");
TF1* fit_lin_2 = new TF1("fit_lin2","pol0");
hist_intg_total->Fit(fit_lin_1,"R","",1,179);
hist_intg_total->Fit(fit_lin_2,"R+","",179,289);
double p0_1_total = fit_lin_1->GetParameter("p0"); //obtenemos el p0	
double p0_2_total = fit_lin_2->GetParameter("p0"); //obtenemos el p0
hist_intg_total->Draw("AP");
TLegend *legend_intg_total = new TLegend(0.719083,0.702733,0.898806,0.904346);
legend_intg_total->AddEntry(hist_intg_total,"#Phi_{total}","lep");
legend_intg_total->AddEntry(fit_lin_1,"Fit Region 1","lep");
legend_intg_total->AddEntry(fit_lin_2,"Fit Region 2 (Rain)","lep");
lco_campg->Draw();
lco_date->Draw();
lco_masl->Draw();
legend_intg_total->Draw();



canvas_intg->cd(2);
/*FIT & get parameters*/
hist_intg_th->GetXaxis()->SetRangeUser(0,290);
hist_intg_th->SetMinimum(0.0);
TF1* fit_th_lin_1 = new TF1("fit_th_lin1","pol0");
TF1* fit_th_lin_2 = new TF1("fit_th_lin2","pol0");
TF1* fit_th_lin_3 = new TF1("fit_th_lin3","pol0");
hist_intg_th->Fit(fit_th_lin_1,"R","",1,186);
hist_intg_th->Fit(fit_th_lin_2,"R+","",187,289);
hist_intg_th->Fit(fit_th_lin_3,"R+","",187,245);
double p0_1_th = fit_th_lin_1->GetParameter("p0"); //obtenemos el p0
double p0_2_th = fit_th_lin_2->GetParameter("p0"); //obtenemos el p0
double p0_3_th = fit_th_lin_3->GetParameter("p0"); //obtenemos el p0
hist_intg_th->DrawClone("AP");
TLegend *legend_intg_th = new TLegend(0.719083,0.702733,0.898806,0.904346);
legend_intg_th->AddEntry(hist_intg_th,"#Phi_{thermal}","lep");
legend_intg_th->AddEntry(fit_th_lin_1,"Fit Region 1","lep");
legend_intg_th->AddEntry(fit_th_lin_2,"Fit Region 2 (Rain)","lep");
legend_intg_th->Draw();



canvas_intg->cd(3);
/*FIT & get parameters*/
hist_intg_ep->GetXaxis()->SetRangeUser(0,290);
hist_intg_ep->SetMinimum(0.0);
TF1* fit_ep_lin_1 = new TF1("fit_ep_lin1","pol0");
TF1* fit_ep_lin_2 = new TF1("fit_ep_lin2","pol0");
hist_intg_ep->Fit(fit_ep_lin_1,"R","",1,186);
hist_intg_ep->Fit(fit_ep_lin_2,"R+","",187,289);
double p0_1_ep = fit_ep_lin_1->GetParameter("p0"); //obtenemos el p0
double p0_2_ep = fit_ep_lin_2->GetParameter("p0"); //obtenemos el p0
hist_intg_ep->DrawClone("AP");
TLegend *legend_intg_ep = new TLegend(0.719083,0.702733,0.898806,0.904346);
legend_intg_ep->AddEntry(hist_intg_ep,"#Phi_{epithermal}","lep");
legend_intg_ep->AddEntry(fit_ep_lin_1,"Fit Region 1","lep");
legend_intg_ep->AddEntry(fit_ep_lin_2,"Fit Region 2 (Rain)","lep");
legend_intg_ep->Draw();


canvas_intg->cd(4);
/*FIT & get parameters*/
hist_intg_fs->GetXaxis()->SetRangeUser(0,290);
hist_intg_fs->SetMinimum(0.0);
TF1* fit_fs_lin_1 = new TF1("fit_fs_lin1","pol0");
TF1* fit_fs_lin_2 = new TF1("fit_fs_lin2","pol0");
hist_intg_fs->Fit(fit_fs_lin_1,"R","",1,186);
hist_intg_fs->Fit(fit_fs_lin_2,"R+","",187,289);
double p0_1_fs = fit_fs_lin_1->GetParameter("p0"); //obtenemos el p0
double p0_2_fs = fit_fs_lin_2->GetParameter("p0"); //obtenemos el p0
hist_intg_fs->DrawClone("AP");
TLegend *legend_intg_fs = new TLegend(0.719083,0.702733,0.898806,0.904346);
legend_intg_fs->AddEntry(hist_intg_fs,"#Phi_{fast}","lep");
legend_intg_fs->AddEntry(fit_fs_lin_1,"Fit Region 1","lep");
legend_intg_fs->AddEntry(fit_fs_lin_2,"Fit Region 2 (Rain)","lep");
legend_intg_fs->Draw();


canvas_intg->cd(5);
/*FIT & get parameters*/
hist_intg_he->GetXaxis()->SetRangeUser(0,290);
hist_intg_he->SetMinimum(0.0);
TF1* fit_he_lin_1 = new TF1("fit_he_lin1","pol0");
TF1* fit_he_lin_2 = new TF1("fit_he_lin2","pol0");
hist_intg_he->Fit(fit_he_lin_1,"R","",1,186);
hist_intg_he->Fit(fit_he_lin_2,"R+","",187,289);
double p0_1_he = fit_he_lin_1->GetParameter("p0"); //obtenemos el p0
double p0_2_he = fit_he_lin_2->GetParameter("p0"); //obtenemos el p0
hist_intg_he->DrawClone("AP");
TLegend *legend_intg_he = new TLegend(0.719083,0.702733,0.898806,0.904346);
legend_intg_he->AddEntry(hist_intg_he,"#Phi_{high energy}","lep");
legend_intg_he->AddEntry(fit_he_lin_1,"Fit Region 1","lep");
legend_intg_he->AddEntry(fit_he_lin_2,"Fit Region 2 (Rain)","lep");
legend_intg_he->Draw();



cout << "p0_total_1 (intercepto): " << p0_1_total << endl;
cout << "p0_total_2 (intercepto): " << p0_2_total << endl;
cout<< endl;
cout << "p0_th_1 (intercepto): " << p0_1_th << endl;
cout << "p0_th_2 (intercepto): " << p0_2_th << endl;
cout<< endl;
cout << "p0_ep_1 (intercepto): " << p0_1_ep << endl;
cout << "p0_ep_2 (intercepto): " << p0_2_ep << endl;
cout<< endl;
cout << "p0_fs_1 (intercepto): " << p0_1_fs << endl;
cout << "p0_fs_2 (intercepto): " << p0_2_fs << endl;
cout<< endl;
cout << "p0_he_1 (intercepto): " << p0_1_he << endl;
cout << "p0_he_2 (intercepto): " << p0_2_he << endl;

canvas_intg->SaveAs(("./deconv_data_pdf/EM_MC_fitting/integral_flux_relations/"+campaign+"/EM_integrales_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".pdf").c_str());


TCanvas *canvas_ratio_integrales = new TCanvas("Ratio_Integrales","Ratio_Integrales",786,927);

auto hist_intg_ratio_th_ep = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_th_ep","err_event","err_event","err_ratio_intg_th_ep","err_ratio_intg_th_ep");
auto hist_intg_ratio_th_fs = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_th_fs","err_event","err_event","err_ratio_intg_th_fs","err_ratio_intg_th_fs");
auto hist_intg_ratio_fs_ep = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_fs_ep","err_event","err_event","err_ratio_intg_fs_ep","err_ratio_intg_fs_ep");
auto hist_intg_ratio_th_sum_fs_ep = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_th_sum_fs_ep","err_event","err_event","err_ratio_intg_th_sum_fs_ep","err_ratio_intg_th_sum_fs_ep");
auto hist_intg_ratio_th_sum_fs_ep_he = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_th_sum_fs_ep_he","err_event","err_event","err_ratio_intg_th_sum_fs_ep_he","err_ratio_intg_th_sum_fs_ep_he");
auto hist_intg_ratio_th_total = df_merge_data_new.GraphAsymmErrors("event_id","ratio_intg_th_total","err_event","err_event","err_ratio_intg_th_total","err_ratio_intg_th_total");

// Clonamos para que muestre corectamente el color en TLegend
auto *hist_intg_ratio_th_ep_clone = (TGraphAsymmErrors*)hist_intg_ratio_th_ep->Clone("ratio_intg_th_ep");
auto *hist_intg_ratio_th_fs_clone = (TGraphAsymmErrors*)hist_intg_ratio_th_fs->Clone("ratio_intg_th_fs");
auto *hist_intg_ratio_fs_ep_clone = (TGraphAsymmErrors*)hist_intg_ratio_fs_ep->Clone("ratio_intg_fs_ep");
auto *hist_intg_ratio_th_sum_fs_ep_clone = (TGraphAsymmErrors*)hist_intg_ratio_th_sum_fs_ep->Clone("ratio_intg_th_sum_fs_ep");
auto *hist_intg_ratio_th_sum_fs_ep_he_clone = (TGraphAsymmErrors*)hist_intg_ratio_th_sum_fs_ep_he->Clone("ratio_intg_th_sum_fs_ep_he");
auto *hist_intg_ratio_th_total_clone = (TGraphAsymmErrors*)hist_intg_ratio_th_total->Clone("ratio_intg_th_total");

hist_intg_ratio_th_ep_clone->GetYaxis()->SetRangeUser(0.02,4.5);
hist_intg_ratio_th_ep_clone->GetXaxis()->SetRangeUser(0,290);
//~ Double_t max_y = hist_intg_ratio_fs_ep_clone->GetMaximum();
//~ TMath::MaxElement(n,hist_intg_ratio_fs_ep_clone->GetY());
hist_intg_ratio_th_ep_clone->SetMaximum(4.5);

//~ gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
//~ gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()

canvas_ratio_integrales->SetLogy();
gStyle->SetTitleFontSize(0.06);
hist_intg_ratio_th_ep_clone->SetTitle("#bf{#Phi_{th}/#Phi_{i}}");
hist_intg_ratio_th_ep_clone->SetLineColor(kBlue);
hist_intg_ratio_th_fs_clone->SetLineColor(kViolet+1);
hist_intg_ratio_fs_ep_clone->SetLineColor(kRed-9);
hist_intg_ratio_th_sum_fs_ep_clone->SetLineColor(8);
hist_intg_ratio_th_sum_fs_ep_he_clone->SetLineColor(kOrange-3);
hist_intg_ratio_th_total_clone->SetLineColor(kCyan-3);

hist_intg_ratio_th_ep_clone->SetMarkerStyle(20);
hist_intg_ratio_th_fs_clone->SetMarkerStyle(20);
hist_intg_ratio_fs_ep_clone->SetMarkerStyle(20);
hist_intg_ratio_th_sum_fs_ep_clone->SetMarkerStyle(20);
hist_intg_ratio_th_sum_fs_ep_he_clone->SetMarkerStyle(20);
hist_intg_ratio_th_total_clone->SetMarkerStyle(20);

hist_intg_ratio_th_ep_clone->SetMarkerColor(kBlue);
hist_intg_ratio_th_fs_clone->SetMarkerColor(kViolet+1);
hist_intg_ratio_fs_ep_clone->SetMarkerColor(kRed-9);
hist_intg_ratio_th_sum_fs_ep_clone->SetMarkerColor(8);
hist_intg_ratio_th_sum_fs_ep_he_clone->SetMarkerColor(kOrange-3);
hist_intg_ratio_th_total_clone->SetMarkerColor(kCyan-3);

hist_intg_ratio_th_ep_clone->GetYaxis()->SetTitleOffset(0.4);
hist_intg_ratio_th_ep_clone->GetYaxis()->SetTitle("#bf{Ratio}");
hist_intg_ratio_th_ep_clone->GetXaxis()->SetTitle("#bf{Event}");

TLatex *lco_campg_2 = new TLatex(0.1,0.91,(campaign+" Campaign").c_str());
TLatex *lco_date_2 = new TLatex(0.6,0.91,"2023-07-10/2023-07-13");

lco_campg_2->SetTextColor(kBlack);
lco_date_2->SetTextColor(kBlack);
lco_campg_2->SetNDC(true);
lco_date_2->SetNDC(true);
lco_campg_2->SetTextSize(0.03);
lco_date_2->SetTextSize(0.03);

hist_intg_ratio_th_ep_clone->DrawClone("AP");
hist_intg_ratio_th_fs_clone->DrawClone("P");
hist_intg_ratio_fs_ep_clone->DrawClone("P");
hist_intg_ratio_th_sum_fs_ep_clone->DrawClone("P");
hist_intg_ratio_th_sum_fs_ep_he_clone->DrawClone("P");
hist_intg_ratio_th_total_clone->DrawClone("P");
lco_campg_2->Draw();
lco_date_2->Draw();

TLegend *legend_c = new TLegend(0.66199,0.800111,0.899235,0.900886);
legend_c->AddEntry(hist_intg_ratio_fs_ep_clone,"Ratio #Phi_{fs}/#Phi_{ep}","lep");
legend_c->AddEntry(hist_intg_ratio_th_ep_clone,"Ratio #Phi_{th}/#Phi_{ep}","lep");
legend_c->AddEntry(hist_intg_ratio_th_fs_clone,"Ratio #Phi_{th}/#Phi_{fs}","lep");
legend_c->AddEntry(hist_intg_ratio_th_sum_fs_ep_clone,"Ratio #Phi_{th}/(#Phi_{fs}+#Phi_{ep})","lep");
legend_c->AddEntry(hist_intg_ratio_th_sum_fs_ep_he_clone,"Ratio #Phi_{th}/(#Phi_{fs}+#Phi_{ep}+#Phi_{he})","lep");
legend_c->AddEntry(hist_intg_ratio_th_total_clone,"Ratio #Phi_{th}/(#Phi_{total})","lep");
legend_c->Draw();

canvas_ratio_integrales->Draw();
canvas_ratio_integrales->SaveAs(("./deconv_data_pdf/EM_MC_fitting/integral_flux_relations/"+campaign+"/EM_ratio_integrales_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".pdf").c_str());

TCanvas *canvas_eta_integrales = new TCanvas("Eta_Integrales","#Eta Integrales",700,1027);
canvas_eta_integrales->Divide(1,3);

auto hist_intg_eta_th = df_merge_data_new.GraphAsymmErrors("event_id","eta_th","err_event","err_event","err_eta_th","err_eta_th");
auto hist_intg_eta_ep = df_merge_data_new.GraphAsymmErrors("event_id","eta_ep","err_event","err_event","err_eta_ep","err_eta_ep");
auto hist_intg_eta_fs = df_merge_data_new.GraphAsymmErrors("event_id","eta_fs","err_event","err_event","err_eta_fs","err_eta_fs");

// Clonamos para que muestre corectamente el color en TLegend
auto *hist_intg_eta_th_clone = (TGraphAsymmErrors*)hist_intg_eta_th->Clone("eta_th");
auto *hist_intg_eta_ep_clone = (TGraphAsymmErrors*)hist_intg_eta_ep->Clone("eta_ep");
auto *hist_intg_eta_fs_clone = (TGraphAsymmErrors*)hist_intg_eta_fs->Clone("eta_fs");



hist_intg_eta_th_clone->SetLineColor(kGray);
hist_intg_eta_ep_clone->SetLineColor(kCyan-9);
hist_intg_eta_fs_clone->SetLineColor(kGreen-9);

hist_intg_eta_th_clone->SetMarkerStyle(20);
hist_intg_eta_ep_clone->SetMarkerStyle(20);
hist_intg_eta_fs_clone->SetMarkerStyle(20);

//~ hist_intg_eta_th_clone->SetMarkerColor(kGray);
//~ hist_intg_eta_ep_clone->SetMarkerColor(kCyan-9);
//~ hist_intg_eta_fs_clone->SetMarkerColor(kGreen-9);


TLatex *lco_campg_3 = new TLatex(0.1,0.91,(campaign+" Campaign").c_str());
TLatex *lco_date_3 = new TLatex(0.61,0.91,"2023-07-10/2023-07-13");

lco_campg_3->SetTextColor(kBlack);
lco_date_3->SetTextColor(kBlack);
lco_campg_3->SetNDC(true);
lco_date_3->SetNDC(true);
lco_campg_3->SetTextSize(0.06);
lco_date_3->SetTextSize(0.06);


hist_intg_eta_th_clone->SetTitle("#bf{#eta_{th} = #Phi_{th}/#Phi_{he}}");
hist_intg_eta_ep_clone->SetTitle("#bf{#eta_{ep} = #Phi_{ep}/#Phi_{he}}");
hist_intg_eta_fs_clone->SetTitle("#bf{#eta_{fs} = #Phi_{fs}/#Phi_{he}}");

canvas_eta_integrales->cd(1);

gStyle->SetTitleFontSize(0.06);
hist_intg_eta_th_clone->GetXaxis()->SetRangeUser(0,290);
hist_intg_eta_th_clone->SetMinimum(0.0);
//~ gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
//~ gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()

hist_intg_eta_th_clone->GetXaxis()->SetTitleSize(0.06);
hist_intg_eta_th_clone->GetXaxis()->SetTitleOffset(0.8);
hist_intg_eta_th_clone->GetXaxis()->SetLabelSize(0.06);
hist_intg_eta_th_clone->GetYaxis()->CenterTitle();
hist_intg_eta_th_clone->GetYaxis()->SetTitleSize(0.08);
hist_intg_eta_th_clone->GetYaxis()->SetTitleOffset(0.6);
hist_intg_eta_th_clone->GetYaxis()->SetLabelSize(0.06);
hist_intg_eta_th_clone->SetLineWidth(2);

hist_intg_eta_th_clone->GetYaxis()->SetTitle("#bf{#eta_{th}}");
hist_intg_eta_th_clone->GetXaxis()->SetTitle("#bf{Event}");
hist_intg_eta_th_clone->DrawClone("AP");
TLegend *legend_th = new TLegend(0.802614,0.759253,0.899099,0.900054);
legend_th->AddEntry(hist_intg_eta_th_clone,"Ratio #eta_{th}","lep");
lco_campg_3->Draw();
lco_date_3->Draw();
legend_th->Draw();


canvas_eta_integrales->cd(2);
hist_intg_eta_ep_clone->GetXaxis()->SetRangeUser(0,290);
hist_intg_eta_ep_clone->SetMinimum(0.0);
//~ gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
//~ gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
hist_intg_eta_ep_clone->GetXaxis()->SetTitleSize(0.06);
hist_intg_eta_ep_clone->GetXaxis()->SetTitleOffset(0.8);
hist_intg_eta_ep_clone->GetXaxis()->SetLabelSize(0.06);
hist_intg_eta_ep_clone->GetYaxis()->CenterTitle();
hist_intg_eta_ep_clone->GetYaxis()->SetTitleSize(0.08);
hist_intg_eta_ep_clone->GetYaxis()->SetTitleOffset(0.6);
hist_intg_eta_ep_clone->GetYaxis()->SetLabelSize(0.06);

hist_intg_eta_ep_clone->GetYaxis()->SetTitle("#bf{#eta_{ep}}");
hist_intg_eta_ep_clone->GetXaxis()->SetTitle("#bf{Event}");
hist_intg_eta_ep_clone->DrawClone("AP");
TLegend *legend_ep = new TLegend(0.802614,0.759253,0.899099,0.900054);
legend_ep->AddEntry(hist_intg_eta_ep_clone,"Ratio #eta_{ep}","lep");
legend_ep->Draw();

canvas_eta_integrales->cd(3);
hist_intg_eta_fs_clone->GetXaxis()->SetRangeUser(0,290);
hist_intg_eta_fs_clone->SetMinimum(0.0);
//~ gPad->Modified(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
//~ gPad->Update(); // para que un valor correcto el gPad->GetUymin() y gPad->GetUymax()
hist_intg_eta_fs_clone->GetXaxis()->SetTitleSize(0.06);
hist_intg_eta_fs_clone->GetXaxis()->SetTitleOffset(0.8);
hist_intg_eta_fs_clone->GetXaxis()->SetLabelSize(0.06);
hist_intg_eta_fs_clone->GetYaxis()->CenterTitle();
hist_intg_eta_fs_clone->GetYaxis()->SetTitleSize(0.08);
hist_intg_eta_fs_clone->GetYaxis()->SetTitleOffset(0.6);
hist_intg_eta_fs_clone->GetYaxis()->SetLabelSize(0.06);

hist_intg_eta_fs_clone->GetYaxis()->SetTitle("#bf{#eta_{fs}}");
hist_intg_eta_fs_clone->GetXaxis()->SetTitle("#bf{Event}");
hist_intg_eta_fs_clone->DrawClone("AP");

TLegend *legend_fs = new TLegend(0.802614,0.759253,0.899099,0.900054);
legend_fs->AddEntry(hist_intg_eta_fs_clone,"Ratio #eta_{fs}","lep");
legend_fs->Draw();

canvas_eta_integrales->Draw();
canvas_eta_integrales->SaveAs(("./deconv_data_pdf/EM_MC_fitting/integral_flux_relations/"+campaign+"/EM_eta_integrales_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+".pdf").c_str());


string fit_event_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_update_merge_02.root";
df_merge_data_new.Snapshot("EM_MC_tree", fit_event_file_name);

}

void tscatter_plot(string campaign, string x_arr, string y_arr, string color_arr, string size_arr, string num){

string input_file = "./deconv_mc_data_energy_fitting/"+campaign+"/3rd_"+campaign+"_data_complete_update.root";
ROOT::RDataFrame df_data("LCO_data_tree", input_file );
auto df_merge_data_new = df_data.Define("err_msdata","VWC_5cm*0.");

	
//~ auto canvas_scatter_plot = new TCanvas(("relations_scatter_plot_"+num).c_str(),("relations_scatter_plot_"+num).c_str(),1920,1080);
auto canvas_scatter_plot = new TCanvas(("relations_scatter_plot_"+num).c_str(),("relations_scatter_plot_"+num).c_str(),1300,1040);
   gPad->Modified();
   gPad->Update();
   gStyle->SetCanvasPreferGL(kTRUE);
   gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas
   gStyle->SetPaperSize(20,24);
   gStyle->SetPalette(kTemperatureMap, 0, 0.6); // define a transparent palette
   
   /**Column type**/
   auto df_x_vec_colType = df_merge_data_new.GetColumnType(x_arr);
   auto df_y_vec_colType = df_merge_data_new.GetColumnType(y_arr);
   auto df_color_vec_colType = df_merge_data_new.GetColumnType(color_arr);
   auto df_size_vec_colType = df_merge_data_new.GetColumnType(size_arr);

	cout << "Colum: " << x_arr << " has type " << df_x_vec_colType << endl;
	cout << "Colum: " << y_arr << " has type " << df_y_vec_colType << endl;
	cout << "Colum: " << color_arr << " has type " << df_color_vec_colType << endl;
	cout << "Colum: " << size_arr << " has type " << df_size_vec_colType << endl;

	vector<double>  df_y_vec;
	vector<double>  df_x_vec;
	vector<double>  df_color_vec;
	vector<double>  df_size_vec;
	

	if(df_x_vec_colType=="Double_t")
		{
			df_x_vec = df_merge_data_new.Take<double>(x_arr).GetValue();
		}
	if(df_x_vec_colType=="Int_t")
		{
			auto df_x_vec_int = df_merge_data_new.Take<int>(x_arr).GetValue();
			vector<double> df_x_vec_double(df_x_vec_int.begin(), df_x_vec_int.end());
			df_x_vec =  df_x_vec_double;
		}
	if(df_y_vec_colType=="Double_t")
		{
			df_y_vec = df_merge_data_new.Take<double>(y_arr).GetValue();
		}
	if(df_y_vec_colType=="Int_t")
		{
			auto df_y_vec_int = df_merge_data_new.Take<int>(y_arr).GetValue();
			vector<double> df_y_vec_double(df_y_vec_int.begin(), df_y_vec_int.end());
			df_y_vec =  df_y_vec_double;
		}
	if(df_color_vec_colType=="Double_t")
		{
			df_color_vec = df_merge_data_new.Take<double>(color_arr).GetValue();
		}
	if(df_color_vec_colType=="Int_t")
		{
			auto df_color_vec_int = df_merge_data_new.Take<int>(color_arr).GetValue();
			vector<double> df_color_vec_double(df_color_vec_int.begin(), df_color_vec_int.end());
			df_color_vec =  df_color_vec_double;
		}
	if(df_size_vec_colType=="Double_t")
		{
			df_size_vec = df_merge_data_new.Take<double>(size_arr).GetValue();
		}
	if(df_size_vec_colType=="Int_t")
		{
			auto df_size_vec_int = df_merge_data_new.Take<int>(size_arr).GetValue();
			vector<double> df_size_vec_double(df_size_vec_int.begin(), df_size_vec_int.end());
			df_size_vec =  df_size_vec_double;
		}	


		
	int n_scatter_size =  df_x_vec.size();
	/*borde de bines como array*/
	double *x_array=  df_x_vec.data();
	double *y_array = df_y_vec.data();
	double *color_array = df_color_vec.data(); // color
	double *size_array = df_size_vec.data(); //size 

   auto scatter = new TScatter(n_scatter_size, x_array, y_array, color_array, size_array);
   scatter->SetMarkerStyle(20);
   scatter->SetMaxMarkerSize(5);
   scatter->SetMinMarkerSize(1);

	string y_array_latex_name = y_arr;
	string x_array_latex_name = x_arr;
	string color_array_latex_name = color_arr;
	string size_array_latex_name = size_arr;

	
   if(y_arr=="ratio_intg_th_ep")
	{
		y_array_latex_name = "#Phi_{th}/#Phi_{ep}";
	}
	if(y_arr=="ratio_intg_th_fs")
	{
		y_array_latex_name = "#Phi_{th}/#Phi_{fs}";
	}
	if(y_arr=="ratio_intg_th_sum_fs_ep")
	{
		y_array_latex_name = "#Phi_{th}/(#Phi_{fs}+#Phi_{ep})";
	}
	if(y_arr=="ratio_intg_fs_ep")
	{
		y_array_latex_name = "#Phi_{fs}/#Phi_{ep}";
	}
	//~ else{y_array_latex_name=y_arr;}

	
   if(x_arr=="ratio_intg_th_ep")
	{
		x_array_latex_name = "#Phi_{th}/#Phi_{ep}";
	}
	if(x_arr=="ratio_intg_th_fs")
	{
		x_array_latex_name = "#Phi_{th}/#Phi_{fs}";
	}
	if(x_arr=="ratio_intg_th_sum_fs_ep")
	{
		x_array_latex_name = "#Phi_{th}/(#Phi_{fs}+#Phi_{ep})";
	}
	if(x_arr=="ratio_intg_fs_ep")
	{
		x_array_latex_name = "#Phi_{fs}/#Phi_{ep}";
	}
	//~ else{x_array_latex_name=x_arr;}


	
   if(color_arr=="ratio_intg_th_ep")
	{
		color_array_latex_name = "#Phi_{th}/#Phi_{ep}";
	}
	if(color_arr=="ratio_intg_th_fs")
	{
		color_array_latex_name = "#Phi_{th}/#Phi_{fs}";
	}
	if(color_arr=="ratio_intg_th_sum_fs_ep")
	{
		color_array_latex_name = "#Phi_{th}/(#Phi_{fs}+#Phi_{ep})";
	}
	if(color_arr=="ratio_intg_fs_ep")
	{
		color_array_latex_name = "#Phi_{fs}/#Phi_{ep}";
	}
	//~ else{color_array_latex_name=color_arr;}


	if(size_arr=="ratio_intg_th_ep")
	{
		size_array_latex_name = "#Phi_{th}/#Phi_{ep}";
	}
	if(size_arr=="ratio_intg_th_fs")
	{
		size_array_latex_name = "#Phi_{th}/#Phi_{fs}";
	}
	if(size_arr=="ratio_intg_th_sum_fs_ep")
	{
		size_array_latex_name = "#Phi_{th}/(#Phi_{fs}+#Phi_{ep})";
	}
	if(size_arr=="ratio_intg_fs_ep")
	{
		size_array_latex_name = "#Phi_{fs}/#Phi_{ep}";
	}
	//~ else{size_array_latex_name=size_arr;}


   string scatter_plot_tittle = "Scatter Plot "+num+": "+x_array_latex_name+", "+y_array_latex_name+", "+color_array_latex_name+", "+size_array_latex_name+";#bf{"+x_array_latex_name+"};#bf{"+y_array_latex_name+"}";
   scatter->SetTitle(scatter_plot_tittle.c_str());

	string color_name = "Color: "+color_array_latex_name;
	string size_name = "#bullet Size: "+size_array_latex_name;
   TLatex *color_variable = new TLatex(0.85,0.91,color_name.c_str());
   TLatex *size_variable = new TLatex(0.1,0.91,size_name.c_str());

	color_variable->SetTextColor(kBlack);
	size_variable->SetTextColor(kBlack);
	color_variable->SetNDC(true);
	size_variable->SetNDC(true);
	color_variable->SetTextSize(0.02);
	size_variable->SetTextSize(0.02);
   
   scatter->Draw("A");
   color_variable->Draw();
   size_variable->Draw();
   canvas_scatter_plot->Draw();
   
   canvas_scatter_plot->SaveAs(("./deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_MC_stop_relations/3rd_"+campaign+"_Campaign_relations_"+num+".pdf").c_str());

	x_arr.clear();
	y_arr.clear();
	y_array_latex_name.clear();
    x_array_latex_name.clear();
    color_array_latex_name.clear();
    size_array_latex_name.clear();
	delete canvas_scatter_plot;
	delete scatter;

}   


//~ void msdata_update(string campaign, int timegrid, int ndet){

//~ /*MSDATA*/
//~ string counting_rate_campaign_path;

//~ if(timegrid==15)
//~ {
	//~ if(campaign=="LCO")
		//~ {
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_15min.root";
		//~ }
//~ }

//~ if(timegrid==60)
//~ {
	//~ if(campaign=="LCO")
		//~ {
				//~ counting_rate_campaign_path ="./CRNS_Data/LCO/3rd_LCO_data_complete_1h.root";
		//~ }
//~ }


//~ ROOT::RDataFrame d1("CRNS_MSDATA", counting_rate_campaign_path);


//~ }

void relations_integral_local_variables_merge(string campaign, int time_grid, int ndet){

ostringstream stream_timegrid, stream_ndet;
stream_timegrid << time_grid;
stream_ndet << ndet;
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();

/*MSDATA*/
string input_complete_file = "./CRNS_Data/"+campaign+"/3rd_LCO_data_complete_15min.root";
string fit_event_file_name ="./deconv_mc_data_energy_fitting/"+campaign+"/EM_MC_fit_parameters_campaign_"+campaign+"_update_merge_02.root";

TFile *file1 = TFile::Open(input_complete_file.c_str());
TFile *file2 = TFile::Open(fit_event_file_name.c_str());

// Crear el dataframe para el primer archivo
//~ ROOT::RDataFrame d1("CRNS_MSDATA", file1);
  // Crear el dataframe para el segundo archivo
//~ ROOT::RDataFrame d2("EM_MC_tree", file2);
auto *t1 = file1->Get<TTree>("CRNS_MSDATA");
auto *t2 = file2->Get<TTree>("EM_MC_tree");
t1->AddFriend(t2);
ROOT::RDataFrame df(*t1);
df.Snapshot("LCO_data_tree", "./deconv_mc_data_energy_fitting/"+campaign+"/3rd_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_data_complete_update.root");
cout <<"Merging data complete" << endl;



}


void plot_relations_integral_local_variables_merge(string campaign, int time_grid, int ndet){

ostringstream stream_timegrid, stream_ndet;
stream_timegrid << time_grid;
stream_ndet << ndet;
string str_stream_timegrid = stream_timegrid.str();
string str_stream_ndet = stream_ndet.str();


string input_file = "./deconv_mc_data_energy_fitting/"+campaign+"/3rd_"+campaign+"_timegrid_"+str_stream_timegrid+"_ndet_"+str_stream_ndet+"_data_complete_update.root";
ROOT::RDataFrame df_data("LCO_data_tree", input_file);


auto df_merge_data_new = df_data.Define("err_msdata","VWC_5cm*0.");

auto tgraph_intg_total_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","Intg_total","err_msdata","err_msdata","err_intg_total","err_intg_total");
auto tgraph_intg_th_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","Intg_th","err_msdata","err_msdata","err_intg_total","err_intg_total");
auto tgraph_intg_ep_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","Intg_ep","err_msdata","err_msdata","err_intg_total","err_intg_total");
auto tgraph_intg_fs_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","Intg_fs","err_msdata","err_msdata","err_intg_total","err_intg_total");
auto tgraph_intg_he_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","Intg_he","err_msdata","err_msdata","err_intg_total","err_intg_total");

auto *tgraph_intg_total_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_total_vwc5cm->Clone("relation_Intg_total_VWC5cm");
auto *tgraph_intg_th_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_th_vwc5cm->Clone("relation_Intg_th_VWC5cm");
auto *tgraph_intg_ep_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_ep_vwc5cm->Clone("relation_Intg_ep_VWC5cm");
auto *tgraph_intg_fs_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_fs_vwc5cm->Clone("relation_Intg_fs_VWC5cm");
auto *tgraph_intg_he_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_he_vwc5cm->Clone("relation_Intg_he_VWC5cm");




tgraph_intg_total_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_total_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_total_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
		  
tgraph_intg_total_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_total_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_total_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_total_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);


tgraph_intg_total_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{total} [cm^{-2} s^{-1}]}");
tgraph_intg_total_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");


tgraph_intg_th_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_th_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_th_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
		  
tgraph_intg_th_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_th_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_th_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_th_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);


tgraph_intg_th_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{th} [cm^{-2} s^{-1}]}");
tgraph_intg_th_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");


tgraph_intg_ep_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_ep_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_ep_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
		  
tgraph_intg_ep_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_ep_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_ep_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_ep_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);


tgraph_intg_ep_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{ep} [cm^{-2} s^{-1}]}");
tgraph_intg_ep_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");

tgraph_intg_fs_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_fs_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_fs_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
		  
tgraph_intg_fs_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_fs_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_fs_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_fs_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);


tgraph_intg_fs_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{fs} [cm^{-2} s^{-1}]}");
tgraph_intg_fs_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");

tgraph_intg_he_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_he_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_he_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
		  
tgraph_intg_he_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_he_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_he_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_he_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);


tgraph_intg_he_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{he} [cm^{-2} s^{-1}]}");
tgraph_intg_he_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");



tgraph_intg_total_vwc5cm_clone->SetLineColor(kBlue);
tgraph_intg_th_vwc5cm_clone->SetLineColor(kGray);
tgraph_intg_ep_vwc5cm_clone->SetLineColor(kCyan-9);
tgraph_intg_fs_vwc5cm_clone->SetLineColor(kGreen-9);
tgraph_intg_he_vwc5cm_clone->SetLineColor(kRed-9);

tgraph_intg_total_vwc5cm_clone->SetMarkerStyle(20);
tgraph_intg_th_vwc5cm_clone->SetMarkerStyle(20);
tgraph_intg_ep_vwc5cm_clone->SetMarkerStyle(20);
tgraph_intg_fs_vwc5cm_clone->SetMarkerStyle(20);
tgraph_intg_he_vwc5cm_clone->SetMarkerStyle(20);

tgraph_intg_total_vwc5cm_clone->SetLineWidth(2);
tgraph_intg_th_vwc5cm_clone->SetLineWidth(2);
tgraph_intg_ep_vwc5cm_clone->SetLineWidth(2);
tgraph_intg_fs_vwc5cm_clone->SetLineWidth(2);
tgraph_intg_he_vwc5cm_clone->SetLineWidth(2);

tgraph_intg_total_vwc5cm_clone->SetMarkerColor(kBlue);
tgraph_intg_th_vwc5cm_clone->SetMarkerColor(kGray);
tgraph_intg_ep_vwc5cm_clone->SetMarkerColor(kCyan-9);
tgraph_intg_fs_vwc5cm_clone->SetMarkerColor(kGreen-9);
tgraph_intg_he_vwc5cm_clone->SetMarkerColor(kRed-9);


TCanvas *canvas_intg_relations = new TCanvas("Integrales_relations","Integrales_relations",689,1040);

canvas_intg_relations->Divide(1,5);

canvas_intg_relations->cd(1);
tgraph_intg_total_vwc5cm_clone->DrawClone("AP");
canvas_intg_relations->cd(2);
tgraph_intg_th_vwc5cm_clone->DrawClone("AP");
canvas_intg_relations->cd(3);
tgraph_intg_ep_vwc5cm_clone->DrawClone("AP");
canvas_intg_relations->cd(4);
tgraph_intg_fs_vwc5cm_clone->DrawClone("AP");
canvas_intg_relations->cd(5);
tgraph_intg_he_vwc5cm_clone->DrawClone("AP");

//~ canvas_intg_relations->Draw();
canvas_intg_relations->SaveAs(("./deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_MC_stop_relations/3rd_"+campaign+"_Campaign_relations_intg_VWC_5cm.pdf").c_str());

TCanvas *canvas_ratios_relations = new TCanvas("ratios_relations","ratios_relations",689,1040);


auto tgraph_ratio_th_ep_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","ratio_intg_th_ep","err_msdata","err_msdata","err_ratio_intg_th_ep","err_ratio_intg_th_ep");
auto tgraph_ratio_th_fs_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","ratio_intg_th_fs","err_msdata","err_msdata","err_ratio_intg_th_fs","err_ratio_intg_th_fs");
auto tgraph_ratio_fs_ep_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","ratio_intg_fs_ep","err_msdata","err_msdata","err_ratio_intg_fs_ep","err_ratio_intg_fs_ep");
auto tgraph_intg_th_fsep_vwc5cm = df_merge_data_new.GraphAsymmErrors("VWC_5cm","ratio_intg_th_sum_fs_ep","err_msdata","err_msdata","err_ratio_intg_th_sum_fs_ep","err_ratio_intg_th_sum_fs_ep");

auto *tgraph_ratio_th_ep_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_ratio_th_ep_vwc5cm->Clone("relation_ratio_th_ep_VWC5cm");
auto *tgraph_ratio_th_fs_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_ratio_th_fs_vwc5cm->Clone("relation_ratio_th_fs_VWC5cm");
auto *tgraph_ratio_fs_ep_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_ratio_fs_ep_vwc5cm->Clone("relation_ratio_fs_ep_VWC5cm");
auto *tgraph_intg_th_fsep_vwc5cm_clone = (TGraphAsymmErrors*)tgraph_intg_th_fsep_vwc5cm->Clone("relation_ratio_th_sum_fs_ep_VWC5cm");

tgraph_ratio_th_ep_vwc5cm_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{ep} with Soil water content 5cm depth} ");
tgraph_ratio_th_fs_vwc5cm_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{fs} with Soil water content 5cm depth } ");
tgraph_ratio_fs_ep_vwc5cm_clone->SetTitle("#bf{Relation #Phi_{fs}/#Phi_{ep} with Soil water content 5cm depth} ");
tgraph_intg_th_fsep_vwc5cm_clone->SetTitle("#bf{Relation #Phi_{th}/(#Phi_{ep}+#Phi_{fs}) with Soil water content 5cm depth} ");

tgraph_ratio_th_ep_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_ep_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_ep_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_ep_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_ep_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_ep_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{ep}}");
tgraph_ratio_th_ep_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");

tgraph_ratio_th_fs_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_fs_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_fs_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_fs_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_fs_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_fs_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{fs}}");
tgraph_ratio_th_fs_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");

tgraph_ratio_fs_ep_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_fs_ep_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_fs_ep_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_ratio_fs_ep_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_fs_ep_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_fs_ep_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{fs}/#Phi_{ep}}");
tgraph_ratio_fs_ep_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");

tgraph_intg_th_fsep_vwc5cm_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_th_fsep_vwc5cm_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_th_fsep_vwc5cm_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_vwc5cm_clone->GetYaxis()->CenterTitle();
tgraph_intg_th_fsep_vwc5cm_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_th_fsep_vwc5cm_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_th_fsep_vwc5cm_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_vwc5cm_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/(#Phi_{fs}+#Phi_{ep})}");
tgraph_intg_th_fsep_vwc5cm_clone->GetXaxis()->SetTitle("#bf{Soil VWC 5cm}");


tgraph_ratio_th_ep_vwc5cm_clone->SetLineColor(kBlue);
tgraph_ratio_th_fs_vwc5cm_clone->SetLineColor(kViolet+1);
tgraph_ratio_fs_ep_vwc5cm_clone->SetLineColor(kRed-9);
tgraph_intg_th_fsep_vwc5cm_clone->SetLineColor(8);

tgraph_ratio_th_ep_vwc5cm_clone->SetMarkerStyle(20);
tgraph_ratio_th_fs_vwc5cm_clone->SetMarkerStyle(20);
tgraph_ratio_fs_ep_vwc5cm_clone->SetMarkerStyle(20);
tgraph_intg_th_fsep_vwc5cm_clone->SetMarkerStyle(20);

tgraph_ratio_th_ep_vwc5cm_clone->SetMarkerColor(kBlue);
tgraph_ratio_th_fs_vwc5cm_clone->SetMarkerColor(kViolet+1);
tgraph_ratio_fs_ep_vwc5cm_clone->SetMarkerColor(kRed-9);
tgraph_intg_th_fsep_vwc5cm_clone->SetMarkerColor(8);

canvas_ratios_relations->Divide(1,4);

gStyle->SetTitleFontSize(0.09);
canvas_ratios_relations->cd(1);
tgraph_ratio_fs_ep_vwc5cm_clone->SetMinimum(0.0);
tgraph_ratio_fs_ep_vwc5cm_clone->DrawClone("AP");
canvas_ratios_relations->cd(2);
tgraph_ratio_th_ep_vwc5cm_clone->SetMinimum(0.0);
tgraph_ratio_th_ep_vwc5cm_clone->DrawClone("AP");
canvas_ratios_relations->cd(3);
tgraph_ratio_th_fs_vwc5cm_clone->SetMinimum(0.0);
tgraph_ratio_th_fs_vwc5cm_clone->DrawClone("AP");
canvas_ratios_relations->cd(4);
tgraph_intg_th_fsep_vwc5cm_clone->SetMinimum(0.0);
tgraph_intg_th_fsep_vwc5cm_clone->DrawClone("AP");

//~ canvas_ratios_relations->Draw();
canvas_ratios_relations->SaveAs(("./deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_MC_stop_relations/3rd_"+campaign+"_Campaign_relations_ratios_VWC_5cm.pdf").c_str());


TCanvas *canvas_ratios_relations_airTC = new TCanvas("ratios_relations_airtc","ratios_relations_airtc",689,1040);


auto tgraph_ratio_th_ep_AirTC_Avg = df_merge_data_new.GraphAsymmErrors("AirTC_Avg","ratio_intg_th_ep","err_msdata","err_msdata","err_ratio_intg_th_ep","err_ratio_intg_th_ep");
auto tgraph_ratio_th_fs_AirTC_Avg = df_merge_data_new.GraphAsymmErrors("AirTC_Avg","ratio_intg_th_fs","err_msdata","err_msdata","err_ratio_intg_th_fs","err_ratio_intg_th_fs");
auto tgraph_ratio_fs_ep_AirTC_Avg = df_merge_data_new.GraphAsymmErrors("AirTC_Avg","ratio_intg_fs_ep","err_msdata","err_msdata","err_ratio_intg_fs_ep","err_ratio_intg_fs_ep");
auto tgraph_intg_th_fsep_AirTC_Avg = df_merge_data_new.GraphAsymmErrors("AirTC_Avg","ratio_intg_th_sum_fs_ep","err_msdata","err_msdata","err_ratio_intg_th_sum_fs_ep","err_ratio_intg_th_sum_fs_ep");

auto *tgraph_ratio_th_ep_AirTC_Avg_clone = (TGraphAsymmErrors*)tgraph_ratio_th_ep_AirTC_Avg->Clone("relation_ratio_th_ep_AirTC_Avg");
auto *tgraph_ratio_th_fs_AirTC_Avg_clone = (TGraphAsymmErrors*)tgraph_ratio_th_fs_AirTC_Avg->Clone("relation_ratio_th_fs_AirTC_Avg");
auto *tgraph_ratio_fs_ep_AirTC_Avg_clone = (TGraphAsymmErrors*)tgraph_ratio_fs_ep_AirTC_Avg->Clone("relation_ratio_fs_ep_AirTC_Avg");
auto *tgraph_intg_th_fsep_AirTC_Avg_clone = (TGraphAsymmErrors*)tgraph_intg_th_fsep_AirTC_Avg->Clone("relation_ratio_th_sum_fs_ep_AirTC_Avg");


tgraph_ratio_th_ep_AirTC_Avg_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{ep} with air temperature}");
tgraph_ratio_th_fs_AirTC_Avg_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{fs} with air temperature}");
tgraph_ratio_fs_ep_AirTC_Avg_clone->SetTitle("#bf{Relation #Phi_{fs}/#Phi_{ep} with air temperature}");
tgraph_intg_th_fsep_AirTC_Avg_clone->SetTitle("#bf{Relation #Phi_{th}/(#Phi_{fs}+#Phi_{ep}) with air temperature}");

tgraph_ratio_th_ep_AirTC_Avg_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_ep_AirTC_Avg_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_AirTC_Avg_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{ep}}");
tgraph_ratio_th_ep_AirTC_Avg_clone->GetXaxis()->SetTitle("#bf{AirTC}");

tgraph_ratio_th_fs_AirTC_Avg_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_fs_AirTC_Avg_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_AirTC_Avg_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{fs}}");
tgraph_ratio_th_fs_AirTC_Avg_clone->GetXaxis()->SetTitle("#bf{AirTC}");

tgraph_ratio_fs_ep_AirTC_Avg_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetYaxis()->CenterTitle();
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetYaxis()->SetTitle("#bf{#Phi_{fs}/#Phi_{ep}}");
tgraph_ratio_fs_ep_AirTC_Avg_clone->GetXaxis()->SetTitle("#bf{AirTC}");

tgraph_intg_th_fsep_AirTC_Avg_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetYaxis()->CenterTitle();
tgraph_intg_th_fsep_AirTC_Avg_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_AirTC_Avg_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/(#Phi_{fs}+#Phi_{ep})}");
tgraph_intg_th_fsep_AirTC_Avg_clone->GetXaxis()->SetTitle("#bf{AirTC}");


tgraph_ratio_th_ep_AirTC_Avg_clone->SetLineColor(kBlue);
tgraph_ratio_th_fs_AirTC_Avg_clone->SetLineColor(kViolet+1);
tgraph_ratio_fs_ep_AirTC_Avg_clone->SetLineColor(kRed-9);
tgraph_intg_th_fsep_AirTC_Avg_clone->SetLineColor(8);

tgraph_ratio_th_ep_AirTC_Avg_clone->SetMarkerStyle(20);
tgraph_ratio_th_fs_AirTC_Avg_clone->SetMarkerStyle(20);
tgraph_ratio_fs_ep_AirTC_Avg_clone->SetMarkerStyle(20);
tgraph_intg_th_fsep_AirTC_Avg_clone->SetMarkerStyle(20);

tgraph_ratio_th_ep_AirTC_Avg_clone->SetMarkerColor(kBlue);
tgraph_ratio_th_fs_AirTC_Avg_clone->SetMarkerColor(kViolet+1);
tgraph_ratio_fs_ep_AirTC_Avg_clone->SetMarkerColor(kRed-9);
tgraph_intg_th_fsep_AirTC_Avg_clone->SetMarkerColor(8);

canvas_ratios_relations_airTC->Divide(1,4);

canvas_ratios_relations_airTC->cd(1);
tgraph_ratio_fs_ep_AirTC_Avg_clone->SetMinimum(0.0);
tgraph_ratio_fs_ep_AirTC_Avg_clone->DrawClone("AP");
canvas_ratios_relations_airTC->cd(2);
tgraph_ratio_th_ep_AirTC_Avg_clone->SetMinimum(0.0);
tgraph_ratio_th_ep_AirTC_Avg_clone->DrawClone("AP");
canvas_ratios_relations_airTC->cd(3);
tgraph_ratio_th_fs_AirTC_Avg_clone->SetMinimum(0.0);
tgraph_ratio_th_fs_AirTC_Avg_clone->DrawClone("AP");
canvas_ratios_relations_airTC->cd(4);
tgraph_intg_th_fsep_AirTC_Avg_clone->SetMinimum(0.0);
tgraph_intg_th_fsep_AirTC_Avg_clone->DrawClone("AP");

//~ canvas_ratios_relations_airTC->Draw();
canvas_ratios_relations_airTC->SaveAs(("./deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_MC_stop_relations/3rd_"+campaign+"_Campaign_relations_ratios_AirTC.pdf").c_str());


TCanvas *canvas_ratios_relations_HR_Min = new TCanvas("ratios_relations_HR_Min","ratios_relations_HR_Min",689,1040);


auto tgraph_ratio_th_ep_RH_Min = df_merge_data_new.GraphAsymmErrors("RH_Min","ratio_intg_th_ep","err_msdata","err_msdata","err_ratio_intg_th_ep","err_ratio_intg_th_ep");
auto tgraph_ratio_th_fs_RH_Min = df_merge_data_new.GraphAsymmErrors("RH_Min","ratio_intg_th_fs","err_msdata","err_msdata","err_ratio_intg_th_fs","err_ratio_intg_th_fs");
auto tgraph_ratio_fs_ep_RH_Min = df_merge_data_new.GraphAsymmErrors("RH_Min","ratio_intg_fs_ep","err_msdata","err_msdata","err_ratio_intg_fs_ep","err_ratio_intg_fs_ep");
auto tgraph_intg_th_fsep_RH_Min = df_merge_data_new.GraphAsymmErrors("RH_Min","ratio_intg_th_sum_fs_ep","err_msdata","err_msdata","err_ratio_intg_th_sum_fs_ep","err_ratio_intg_th_sum_fs_ep");

auto *tgraph_ratio_th_ep_RH_Min_clone = (TGraphAsymmErrors*)tgraph_ratio_th_ep_RH_Min->Clone("relation_ratio_th_ep_RH_Min");
auto *tgraph_ratio_th_fs_RH_Min_clone = (TGraphAsymmErrors*)tgraph_ratio_th_fs_RH_Min->Clone("relation_ratio_th_fs_RH_Min");
auto *tgraph_ratio_fs_ep_RH_Min_clone = (TGraphAsymmErrors*)tgraph_ratio_fs_ep_RH_Min->Clone("relation_ratio_fs_ep_RH_Min");
auto *tgraph_intg_th_fsep_RH_Min_clone = (TGraphAsymmErrors*)tgraph_intg_th_fsep_RH_Min->Clone("relation_ratio_th_sum_fs_ep_RH_Min");


tgraph_ratio_th_ep_RH_Min_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{ep} with relative humidity} ");
tgraph_ratio_th_fs_RH_Min_clone->SetTitle("#bf{Relation #Phi_{th}/#Phi_{fs} with relative humidity} ");
tgraph_ratio_fs_ep_RH_Min_clone->SetTitle("#bf{Relation #Phi_{fs}/#Phi_{ep} with relative humidity} ");
tgraph_intg_th_fsep_RH_Min_clone->SetTitle("#bf{Relation #Phi_{th}/(#Phi_{fs}+#Phi_{ep}) with relative humidity} ");

tgraph_ratio_th_ep_RH_Min_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_ep_RH_Min_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_ep_RH_Min_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_RH_Min_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_ep_RH_Min_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_ep_RH_Min_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_ep_RH_Min_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_ep_RH_Min_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{ep}}");
tgraph_ratio_th_ep_RH_Min_clone->GetXaxis()->SetTitle("#bf{AirRH}");

tgraph_ratio_th_fs_RH_Min_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_th_fs_RH_Min_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_th_fs_RH_Min_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_RH_Min_clone->GetYaxis()->CenterTitle();
tgraph_ratio_th_fs_RH_Min_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_th_fs_RH_Min_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_th_fs_RH_Min_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_th_fs_RH_Min_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/#Phi_{fs}}");
tgraph_ratio_th_fs_RH_Min_clone->GetXaxis()->SetTitle("#bf{AirRH}");

tgraph_ratio_fs_ep_RH_Min_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_ratio_fs_ep_RH_Min_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_ratio_fs_ep_RH_Min_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_RH_Min_clone->GetYaxis()->CenterTitle();
tgraph_ratio_fs_ep_RH_Min_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_ratio_fs_ep_RH_Min_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_ratio_fs_ep_RH_Min_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_ratio_fs_ep_RH_Min_clone->GetYaxis()->SetTitle("#bf{#Phi_{fs}/#Phi_{ep}}");
tgraph_ratio_fs_ep_RH_Min_clone->GetXaxis()->SetTitle("#bf{AirRH}");

tgraph_intg_th_fsep_RH_Min_clone->GetXaxis()->SetTitleSize(0.06);
tgraph_intg_th_fsep_RH_Min_clone->GetXaxis()->SetTitleOffset(0.8);
tgraph_intg_th_fsep_RH_Min_clone->GetXaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_RH_Min_clone->GetYaxis()->CenterTitle();
tgraph_intg_th_fsep_RH_Min_clone->GetYaxis()->SetTitleSize(0.08);
tgraph_intg_th_fsep_RH_Min_clone->GetYaxis()->SetTitleOffset(0.6);
tgraph_intg_th_fsep_RH_Min_clone->GetYaxis()->SetLabelSize(0.06);
tgraph_intg_th_fsep_RH_Min_clone->GetYaxis()->SetTitle("#bf{#Phi_{th}/(#Phi_{fs}+#Phi_{ep})}");
tgraph_intg_th_fsep_RH_Min_clone->GetXaxis()->SetTitle("#bf{AirRH}");


tgraph_ratio_th_ep_RH_Min_clone->SetLineColor(kBlue);
tgraph_ratio_th_fs_RH_Min_clone->SetLineColor(kViolet+1);
tgraph_ratio_fs_ep_RH_Min_clone->SetLineColor(kRed-9);
tgraph_intg_th_fsep_RH_Min_clone->SetLineColor(8);

tgraph_ratio_th_ep_RH_Min_clone->SetMarkerStyle(20);
tgraph_ratio_th_fs_RH_Min_clone->SetMarkerStyle(20);
tgraph_ratio_fs_ep_RH_Min_clone->SetMarkerStyle(20);
tgraph_intg_th_fsep_RH_Min_clone->SetMarkerStyle(20);

tgraph_ratio_th_ep_RH_Min_clone->SetMarkerColor(kBlue);
tgraph_ratio_th_fs_RH_Min_clone->SetMarkerColor(kViolet+1);
tgraph_ratio_fs_ep_RH_Min_clone->SetMarkerColor(kRed-9);
tgraph_intg_th_fsep_RH_Min_clone->SetMarkerColor(8);

canvas_ratios_relations_HR_Min->Divide(1,4);

canvas_ratios_relations_HR_Min->cd(1);
tgraph_ratio_fs_ep_RH_Min_clone->SetMinimum(0.0);
tgraph_ratio_fs_ep_RH_Min_clone->DrawClone("AP");
canvas_ratios_relations_HR_Min->cd(2);
tgraph_ratio_th_ep_RH_Min_clone->SetMinimum(0.0);
tgraph_ratio_th_ep_RH_Min_clone->DrawClone("AP");
canvas_ratios_relations_HR_Min->cd(3);
tgraph_ratio_th_fs_RH_Min_clone->SetMinimum(0.0);
tgraph_ratio_th_fs_RH_Min_clone->DrawClone("AP");
canvas_ratios_relations_HR_Min->cd(4);
tgraph_intg_th_fsep_RH_Min_clone->SetMinimum(0.0);
tgraph_intg_th_fsep_RH_Min_clone->DrawClone("AP");

//~ canvas_ratios_relations_HR_Min->Draw();
canvas_ratios_relations_HR_Min->SaveAs(("./deconv_data_pdf/EM_scatter_plots/"+campaign+"/EM_MC_stop_relations/3rd_"+campaign+"_Campaign_relations_ratios_HR_min.pdf").c_str());

/******************Scatter PLOT*******************/

	tscatter_plot("LCO","AirTC_Avg","ratio_intg_th_ep","RH_Min","TC_5cm", "1");
	tscatter_plot("LCO","AirTC_Avg","ratio_intg_th_fs","RH_Min","TC_5cm", "2");
	tscatter_plot("LCO","AirTC_Avg","ratio_intg_th_sum_fs_ep","RH_Min","TC_5cm", "3");
	tscatter_plot("LCO","AirTC_Avg","ratio_intg_fs_ep","RH_Min","TC_5cm", "4");

	tscatter_plot("LCO","RH_Min","ratio_intg_th_ep","AirTC_Avg","TC_5cm", "5");
	tscatter_plot("LCO","RH_Min","ratio_intg_th_fs","AirTC_Avg","TC_5cm", "6");
	tscatter_plot("LCO","RH_Min","ratio_intg_th_sum_fs_ep","AirTC_Avg","TC_5cm", "7");
	tscatter_plot("LCO","RH_Min","ratio_intg_fs_ep","AirTC_Avg","TC_5cm", "8");

	tscatter_plot("LCO","AirTC_Avg","RH_Min","ratio_intg_th_ep","TC_5cm", "9");
	tscatter_plot("LCO","AirTC_Avg","RH_Min","ratio_intg_th_fs","TC_5cm", "10");
	tscatter_plot("LCO","AirTC_Avg","RH_Min","ratio_intg_th_sum_fs_ep","TC_5cm", "11");
	tscatter_plot("LCO","AirTC_Avg","RH_Min","ratio_intg_fs_ep","TC_5cm", "12");

	tscatter_plot("LCO","Intg_th","Intg_ep","RH_Min","AirTC_Avg","13");

	tscatter_plot("LCO","AirTC_Avg","NEUrate_D16","RH_Min","TC_5cm", "14");
	tscatter_plot("LCO","AirTC_Avg","NEUrate_D12","RH_Min","TC_5cm", "15");
	tscatter_plot("LCO","AirTC_Avg","NEUrate_D02","RH_Min","TC_5cm", "16");
	
	tscatter_plot("LCO","VWC_5cm","ratio_intg_th_sum_fs_ep","RH_Min","TC_5cm","17");
	tscatter_plot("LCO","VWC_5cm","ratio_intg_th_sum_fs_ep","event_id","TC_5cm","18");
	tscatter_plot("LCO","VWC_5cm","ratio_intg_th_sum_fs_ep","AirTC_Avg","TC_5cm","19");
	
}

vector<double> interpolate_tgraph(string dose){

vector<double> interpolate_coeff_vec;

string input_file = "/home/flopez/LIN/TESIS_DOC/Analysis/binning_E.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"E_EXPACS_binning",double_type},{"E_ICRP116_binning", double_type},{"E_ICRP74_binning", double_type},{"E_TRS403_binning", double_type},{"E_ISO_ICRP116", double_type},{"E_ISO_ICRP74", double_type},{"E_ISO_TRS403", double_type},{"H10_ICRP74", double_type},{"H10_TRS403", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(input_file,true,delimiter,-1, std::move(msdata_map));
 //~ auto seed_rdf = ROOT::RDF::FromCSV(input_file);
//~ seed_rdf.Snapshot("binning_E","./binning_E.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


//~ auto energy_icrp_vec = seed_rdf.Take<double>("E_ICRP116_binning").GetValue();
//~ auto energy_icrp_vec = seed_rdf.Take<double>("E_flux_binning").GetValue();

int bin_cut = 68;
auto seed_ref_cut = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries = seed_ref_cut.Count().GetValue();

int bin_cut_expacs =130;
auto seed_ref_cut_expacs = seed_rdf.Range(0, bin_cut_expacs, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries_expacs = seed_ref_cut_expacs.Count().GetValue();

int bin_cut_icrp_74 = 59;
auto seed_ref_cut_icrp_74 = seed_rdf.Range(0, bin_cut_icrp_74, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries_icrp_74 = seed_ref_cut_icrp_74.Count().GetValue();

auto expacs_binning = seed_ref_cut_expacs.Take<double>("E_EXPACS_binning").GetValue();
auto icrp116_binning_vec = seed_ref_cut.Take<double>("E_ICRP116_binning").GetValue();
auto icrp74_binning_vec = seed_ref_cut_icrp_74.Take<double>("E_ICRP74_binning").GetValue();
auto trs403_binning_vec = seed_ref_cut.Take<double>("E_TRS403_binning").GetValue();
auto E_iso_icrp116_vec = seed_ref_cut.Take<double>("E_ISO_ICRP116").GetValue();
auto E_iso_icrp74_vec = seed_ref_cut_icrp_74.Take<double>("E_ISO_ICRP74").GetValue();
auto E_iso_trs403_vec = seed_ref_cut.Take<double>("E_ISO_TRS403").GetValue();
auto h10_icrp74_vec = seed_ref_cut_icrp_74.Take<double>("H10_ICRP74").GetValue();
auto h10_trs403_vec = seed_ref_cut.Take<double>("H10_TRS403").GetValue();

/***EXPACS BINNING***/
int binnum_expacs = expacs_binning.size()-1;
cout << "expacs_binning size " <<  expacs_binning.size() << endl;
cout << "binnum:_expacs " << binnum_expacs  << endl;

/*borde de bines como array*/
double *bins_expacs = expacs_binning.data();
double *bins_icrp116 = icrp116_binning_vec.data();
double *bins_icrp74 = icrp74_binning_vec.data();
double *bins_trs403 = trs403_binning_vec.data();
/*******************/



int binnum = icrp116_binning_vec.size()-1;
cout << "energy_icrp_vec size " <<  icrp116_binning_vec.size() << endl;
cout << "binnum: " << binnum  << endl;

/*borde de bines como array*/
double *bins_iso = E_iso_icrp116_vec.data();
double *bins_iso_icrp74 = E_iso_icrp74_vec.data();
double *bins_iso_trs403 = E_iso_trs403_vec.data();
double *bins_h10_icrp74 = h10_icrp74_vec.data();
double *bins_h10_trs403 = h10_trs403_vec.data();

int n =  icrp116_binning_vec.size();
int n_icrp74 =  icrp74_binning_vec.size();
int n_trs403 =  trs403_binning_vec.size();



TCanvas* canvas = new TCanvas ("canvas","canvas",1920,1080) ;
canvas->SetLogx();
canvas->SetLogy();

auto g = new TGraph(n,bins_icrp116,bins_iso);
auto g_e_icrp74 = new TGraph(n_icrp74,bins_icrp74,bins_iso_icrp74);
auto g_e_trs403 = new TGraph(n_trs403,bins_trs403,bins_iso_trs403);
auto g_h10_icrp74 = new TGraph(n_icrp74,bins_icrp74,bins_h10_icrp74);
auto g_h10_trs403 = new TGraph(n_trs403,bins_trs403,bins_h10_trs403);

/***Interpolations***/

vector<double> vec_energy_icrp_interpolate;
vector<double> vec_h10_icrp74_interpolate;

for(int i=0;i<expacs_binning.size();i++)
	{
		double interpolate_spline_point = g->Eval(expacs_binning[i],0, "S"); // a TSpline3 object is created using this graph and the interpolated value from the spline is returned. the internally created spline is deleted on return.
		vec_energy_icrp_interpolate.push_back(interpolate_spline_point);
	}

for(int i=0;i<expacs_binning.size();i++)
	{
		double interpolate_spline_point_2 = g_h10_icrp74->Eval(expacs_binning[i],0, ""); //if spline==0 and option="" a linear interpolation between the two points close to x is computed. If x is outside the graph range, a linear extrapolation is computed.
		vec_h10_icrp74_interpolate.push_back(interpolate_spline_point_2);
	}



double *bins_iso_interpolate = vec_energy_icrp_interpolate.data();
double *bins_h10_icrp74_interpolate =vec_h10_icrp74_interpolate.data();

int n_interpolate =  expacs_binning.size();
auto g_interpolate = new TGraph(n_interpolate,bins_expacs,bins_iso_interpolate);
auto g_h10_icrp74_interpolate = new TGraph(n_interpolate,bins_expacs,bins_h10_icrp74_interpolate);

g_interpolate->SetMarkerColor(kBlue);
g_interpolate->SetMarkerStyle(4);

g_h10_icrp74_interpolate->SetMarkerColor(kOrange);
g_h10_icrp74_interpolate->SetMarkerStyle(46);

g_interpolate->SetTitle("Effective dose per fluence conversion coefficients interpolate points for EXPACS binning");
g_h10_icrp74_interpolate->SetTitle("H*(10) fluence conversion coefficients from ICRP 74 interpolate points for EXPACS binning");
g->SetTitle("Effective dose per fluence conversion coefficients points from ICRP 116 binning");
g_e_icrp74->SetTitle("Effective dose per fluence conversion coefficients points from ICRP 74 binning");
g_e_trs403->SetTitle("Effective dose per fluence conversion coefficients points from TRS 403 binning");
g_h10_icrp74->SetTitle("Ambient dose equivalent H*(10) per fluence conversion coefficients points from ICRP 74 binning");
g_h10_trs403->SetTitle("Ambient dose equivalent H*(10) per fluence conversion coefficients points from TRS 403 binning");
g->GetXaxis()->SetTitleSize(0.03);
g->GetYaxis()->SetTitleSize(0.03);
g->GetXaxis()->SetTitleOffset(1.2);
g->GetYaxis()->SetTitle("#bf{Effective dose per fluence conversion coefficients (pSv cm^{2})}");
g->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
g->SetMarkerColor(kBlue);
g_e_icrp74->SetMarkerColor(kRed);
g_e_trs403->SetMarkerColor(kGreen);
g_h10_icrp74->SetMarkerColor(kOrange);
g_h10_trs403->SetMarkerColor(kMagenta);
g->SetMarkerStyle(8);
g_e_icrp74->SetMarkerStyle(33);
g_e_trs403->SetMarkerStyle(34);
g_h10_icrp74->SetMarkerStyle(47);
g_h10_trs403->SetMarkerStyle(22);
g->Draw("AP");
g_interpolate->Draw("P");
g_h10_icrp74_interpolate->Draw("P");
g_e_icrp74->Draw("P");
g_e_trs403->Draw("P");
g_h10_icrp74->Draw("P");
g_h10_trs403->Draw("P");

TLegend *legend_c = new TLegend(0.136905,0.720314,0.542208,0.897939);
legend_c->AddEntry(g_interpolate,"#bf{Interpolate points (TSpline3) for EXPACS binning}","p");
legend_c->AddEntry(g_h10_icrp74_interpolate,"#bf{H*(10) Interpolate (Linear interpolation) points for EXPACS binning}","p");
legend_c->AddEntry(g,"#bf{E Conversion coefficients points from ICRP 116 binning}","p");
legend_c->AddEntry(g_e_icrp74,"#bf{E Conversion coefficients points from ICRP 74 binning}","p");
legend_c->AddEntry(g_e_trs403,"#bf{E Conversion coefficients points from TRS 403 binning}","p");
legend_c->AddEntry(g_h10_icrp74,"#bf{H*(10) Conversion coefficients points from ICRP 74 binning & Ferrari1998}","p");
legend_c->AddEntry(g_h10_trs403,"#bf{H*(10) Conversion coefficients points from TRS 403 binning}","p");
legend_c->SetTextSize(0.02);
legend_c->SetMargin(0.1);// acorta la distancia entre el marcador y el texto
legend_c->Draw();



if(dose=="E_ICRP116_ISO")
	{
		interpolate_coeff_vec = vec_energy_icrp_interpolate;
	}
if(dose=="H10_ICRP74")
	{
		interpolate_coeff_vec = vec_h10_icrp74_interpolate;
	}

return interpolate_coeff_vec;


}

void dose_coeff_conversion(){
string input_file = "/home/flopez/LIN/TESIS_DOC/Analysis/binning_E.csv";
char delimiter = ',';
char double_type ='D';
std::unordered_map<std::string, char> msdata_map = {{"E_EXPACS_binning",double_type},{"E_ICRP116_binning", double_type},{"E_ICRP74_binning", double_type},{"E_TRS403_binning", double_type},{"E_ISO_ICRP116", double_type},{"E_ISO_ICRP74", double_type},{"E_ISO_TRS403", double_type},{"H10_ICRP74", double_type},{"H10_TRS403", double_type}}; // mapa de values (nombre de columna)-key (tipo de variable de la columna)
auto seed_rdf = ROOT::RDF::FromCSV(input_file,true,delimiter,-1, std::move(msdata_map));
 //~ auto seed_rdf = ROOT::RDF::FromCSV(input_file);
//~ seed_rdf.Snapshot("binning_E","./binning_E.root"); /*Save selected columns to disk, in a new TTree treename in file filename*/


//~ auto energy_icrp_vec = seed_rdf.Take<double>("E_ICRP116_binning").GetValue();
//~ auto energy_icrp_vec = seed_rdf.Take<double>("E_flux_binning").GetValue();

int bin_cut = 68;
auto seed_ref_cut = seed_rdf.Range(0, bin_cut, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries = seed_ref_cut.Count().GetValue();

int bin_cut_expacs =130;
auto seed_ref_cut_expacs = seed_rdf.Range(0, bin_cut_expacs, 1); // (a,b,c) pick an event every c entries from a to b, excluding b .
auto d_cut_entries_expacs = seed_ref_cut_expacs.Count().GetValue();

auto expacs_binning = seed_ref_cut_expacs.Take<double>("E_EXPACS_binning").GetValue();
auto energy_icrp_vec = seed_ref_cut.Take<double>("E_ICRP116_binning").GetValue();
auto iso_vec = seed_ref_cut.Take<double>("E_ISO_ICRP116").GetValue();


/***EXPACS BINNING***/
int binnum_expacs = expacs_binning.size()-1;
cout << "expacs_binning size " <<  expacs_binning.size() << endl;
cout << "binnum:_expacs " << binnum_expacs  << endl;

/*borde de bines como array*/
double *bins_expacs = expacs_binning.data();
/*******************/



int binnum = energy_icrp_vec.size()-1;
cout << "energy_icrp_vec size " <<  energy_icrp_vec.size() << endl;
cout << "binnum: " << binnum  << endl;

/*borde de bines como array*/
double *bins = energy_icrp_vec.data();

/***Interpolate data***/

vector<double> vec_interpolate_expacs = interpolate_tgraph("E_ICRP116_ISO");
int binnum_interpolate = vec_interpolate_expacs.size()-1;
/***********************/

TCanvas *canvas_dose = new TCanvas("dose_conver_coeff","dose_conver_coeff",1920,1080);
canvas_dose->SetLogx();
canvas_dose->SetLogy();

/*Histograma de flujo inicial*/

/*Coefficientes en bineado ICRP 116*/
TH1D* fluence_to_dose_coef_hist = new TH1D("dose_coeff_ICRP_116","dose_coeff_ICRP_116", binnum , bins);
for (int i = 0; i<energy_icrp_vec.size(); i++)
	{
		fluence_to_dose_coef_hist->SetBinContent(i+1,iso_vec[i]);
	}

/*Coefficientes en bineado ICRP 116*/
TH1D* fluence_to_dose_coef_hist_interpolate = new TH1D("dose_coeff_interpolate","dose_coeff_interpolate", binnum_interpolate,bins_expacs);
for (int i = 0; i<vec_interpolate_expacs.size(); i++)
	{
		fluence_to_dose_coef_hist_interpolate->SetBinContent(i+1,vec_interpolate_expacs[i]);
	}

/*Coefficientes en bineado ICRP 116 EN REPRESENTACION DIFERENCIAL*/
TH1D* fluence_to_dose_coef_hist_diff = new TH1D("dose_coeff_ICRP_116_diff","dose_coeff_ICRP_116_diff", binnum , bins);
for (int i = 0; i<energy_icrp_vec.size(); i++)
	{
		double bin_width = fluence_to_dose_coef_hist->GetXaxis()->GetBinWidth(i+1);
		fluence_to_dose_coef_hist_diff->SetBinContent(i+1,iso_vec[i]/bin_width);
	}


TH1D* fluence_to_dose_coef_hist_expacs_binning = new TH1D("dose_coeff_expacs_binning","dose_coeff_expacs_binning", binnum_expacs , bins_expacs);
for (int i = 0; i<expacs_binning.size(); i++)
	{
		double intg_value  = fluence_to_dose_coef_hist_diff->Integral(fluence_to_dose_coef_hist_diff->FindBin(expacs_binning[i]+(expacs_binning[i]*1.5e-01)),fluence_to_dose_coef_hist_diff->FindBin(expacs_binning[i+1]-(expacs_binning[i+1]*1.5e-01)));
		fluence_to_dose_coef_hist_expacs_binning->SetBinContent(i+1,intg_value);
	}


TH1D* fluence_to_dose_coef_hist_expacs_binning_intg = new TH1D("dose_coeff_expacs_binning_intg","dose_coeff_expacs_binning_intg", binnum_expacs , bins_expacs);
for (int i = 0; i<expacs_binning.size(); i++)
	{
		double bin_width = fluence_to_dose_coef_hist_expacs_binning->GetXaxis()->GetBinWidth(i+1);
		fluence_to_dose_coef_hist_expacs_binning_intg->SetBinContent(i+1,fluence_to_dose_coef_hist_expacs_binning->GetBinContent(i+1)*bin_width);
	}


/***TEST INTEGRALES**/
//~ double integral_expacs = fluence_to_dose_coef_hist_expacs_binning_intg->Integral(1,10);
//~ double integral_fluence_to_dose_coef_hist =fluence_to_dose_coef_hist->Integral(1,1);

double integral_expacs = fluence_to_dose_coef_hist_expacs_binning_intg->Integral(1,10);
double integral_fluence_to_dose_coef_hist =fluence_to_dose_coef_hist->Integral(1,1);


cout << "integral_expacs (bin 1, bin 10): " << integral_expacs << endl;
cout << "integral_fluence_to_dose_coef_hist (bin 1, bin 1): " << integral_fluence_to_dose_coef_hist << endl;


fluence_to_dose_coef_hist->SetTitle("#bf{The effective dose conversion coefficients for neutrons in ISO irradiation geometry.} ");
fluence_to_dose_coef_hist->GetYaxis()->SetTitle("#bf{Effective dose per fluence conversion coefficients (pSv cm^{2})}");
fluence_to_dose_coef_hist->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
fluence_to_dose_coef_hist->Draw("HIST");
fluence_to_dose_coef_hist_diff->Draw("HIST SAME");

TCanvas *canvas_dose_expacs_binning = new TCanvas("dose_conver_coeff_expacs_binning","dose_conver_coeff_expacs_binning",1920,1080);
canvas_dose_expacs_binning->SetLogx();
canvas_dose_expacs_binning->SetLogy();
fluence_to_dose_coef_hist_expacs_binning->SetLineColor(kBlue);
fluence_to_dose_coef_hist_diff->SetLineColor(kRed);
fluence_to_dose_coef_hist_diff->SetLineStyle(9);

fluence_to_dose_coef_hist_expacs_binning->SetTitle("#bf{The effective dose conversion coefficients for neutrons in ISO irradiation geometry for EXPACS binning.} ");
fluence_to_dose_coef_hist_expacs_binning->GetYaxis()->SetTitle("#bf{Effective dose per fluence conversion coefficients (pSv cm^{2})}");
fluence_to_dose_coef_hist_expacs_binning->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
fluence_to_dose_coef_hist_expacs_binning->Draw("HIST");
fluence_to_dose_coef_hist_diff->Draw("HIST SAME");


TCanvas *canvas_dose_expacs_binning_intg = new TCanvas("dose_conver_coeff_expacs_binning_intg","dose_conver_coeff_expacs_binning_intg",1920,1080);
canvas_dose_expacs_binning_intg ->SetLogx();
canvas_dose_expacs_binning_intg ->SetLogy();
fluence_to_dose_coef_hist_expacs_binning_intg->SetLineColor(kBlue);
fluence_to_dose_coef_hist->SetLineColor(kRed);
fluence_to_dose_coef_hist->SetLineStyle(9);

fluence_to_dose_coef_hist_expacs_binning_intg->SetTitle("#bf{The effective dose conversion coefficients for neutrons in ISO irradiation geometry for EXPACS binning - Integral Representation.} ");
fluence_to_dose_coef_hist_expacs_binning_intg->GetYaxis()->SetTitle("#bf{Effective dose per fluence conversion coefficients (pSv cm^{2})}");
fluence_to_dose_coef_hist_expacs_binning_intg->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
fluence_to_dose_coef_hist_expacs_binning_intg->Draw("HIST");
fluence_to_dose_coef_hist->Draw("HIST SAME");


TCanvas *canvas_dose_expacs_binning_intg_interpolate = new TCanvas("dose_conver_coeff_expacs_binning_intg_interpolate","dose_conver_coeff_expacs_binning_intg_interpolate",1920,1080);
canvas_dose_expacs_binning_intg_interpolate->SetLogx();
canvas_dose_expacs_binning_intg_interpolate->SetLogy();
fluence_to_dose_coef_hist_interpolate->SetLineColor(kBlue);
fluence_to_dose_coef_hist->SetLineColor(kRed);
fluence_to_dose_coef_hist->SetLineStyle(9);

fluence_to_dose_coef_hist_interpolate->SetTitle("#bf{The effective dose conversion coefficients for neutrons in ISO irradiation geometry for EXPACS binning - Integral Representation.} ");
fluence_to_dose_coef_hist_interpolate->GetYaxis()->SetTitle("#bf{Effective dose per fluence conversion coefficients (pSv cm^{2})}");
fluence_to_dose_coef_hist_interpolate->GetXaxis()->SetTitle("#bf{Neutron Energy (MeV)}");
fluence_to_dose_coef_hist_interpolate->GetXaxis()->SetTitleSize(0.03);
fluence_to_dose_coef_hist_interpolate->GetYaxis()->SetTitleSize(0.03);
fluence_to_dose_coef_hist_interpolate->GetXaxis()->SetTitleOffset(1.2);
fluence_to_dose_coef_hist_interpolate->Draw("HIST");
fluence_to_dose_coef_hist->Draw("HIST SAME");

TLegend *legend_c = new TLegend(0.136905,0.720314,0.502706,0.896958);
legend_c->AddEntry(fluence_to_dose_coef_hist_interpolate,"#bf{Interpolate points for EXPACS binning}","l");
legend_c->AddEntry(fluence_to_dose_coef_hist,"#bf{Conversion coefficients points from ICRP 116 binning}","l");
legend_c->SetTextSize(0.02);
legend_c->Draw();

}

void effective_dose_per_diff_flux_H(string campaign){
	
string input_file = "./deconv_mc_data_energy_fitting/"+campaign+"/3rd_"+campaign+"_data_complete_update.root";
ROOT::RDataFrame df_data("LCO_data_tree", input_file);

RVec<double> coeff_conver_fluence_to_dose_vec = interpolate_tgraph("E_ICRP116_ISO"); // C(E)
RVec<double> coeff_conver_fluence_to_ambient_dose_vec = interpolate_tgraph("H10_ICRP74");

auto flux_intg_mc_matrix = df_data.Take<RVec<double>>("flux_intg_MC").GetValue();
auto err_flux_intg_mc_matrix = df_data.Take<RVec<double>>("err_flux_intg_MC").GetValue();

RVec<RVec<double>>  effective_dose_per_event_matrix;
RVec<double>  effective_dose_per_event_sum_vector;

RVec<RVec<double>>  ambient_dose_per_event_matrix;
RVec<double>  ambient_dose_per_event_sum_vector;

for(int i=0; i<flux_intg_mc_matrix.size(); i++)
	{
		RVec<double> effective_dose_per_event_vector = flux_intg_mc_matrix[i]*coeff_conver_fluence_to_dose_vec;
		RVec<double> ambient_dose_per_event_vector = flux_intg_mc_matrix[i]*coeff_conver_fluence_to_ambient_dose_vec;
		double effective_dose_sum = 0.0;
		double ambient_dose_sum = 0.0;
		for(int j=0;j<effective_dose_per_event_vector.size();j++)
			{
				//~ double partial_sum =0.0;
				effective_dose_sum += effective_dose_per_event_vector[j];
				ambient_dose_sum +=  ambient_dose_per_event_vector[j];
			}
		

		effective_dose_per_event_sum_vector.push_back(effective_dose_sum*3.6); // to pass from (pSv/s) to (nSv/h) we multiplied by 3.6
		effective_dose_per_event_matrix.push_back(effective_dose_per_event_vector);

		ambient_dose_per_event_sum_vector.push_back(ambient_dose_sum*3.6); // to pass from (pSv/s) to (nSv/h) we multiplied by 3.6
		ambient_dose_per_event_matrix.push_back(ambient_dose_per_event_vector);
	}

int event_dose_id = 0;
int event_ambient_dose_id = 0;

auto df_data_update = df_data.Define("effective_dose",[&]() {
												auto event_dose_elem =effective_dose_per_event_sum_vector[event_dose_id];
												event_dose_id++;
												return event_dose_elem;
							 })
							 .Define("ambient_dose_equivalent",[&]() {
												auto event_dose_elem =ambient_dose_per_event_sum_vector[event_ambient_dose_id];
												event_ambient_dose_id++;
												return event_dose_elem;
							 });

	
auto effec_dose_hist = df_data_update.GraphAsymmErrors("event_id","effective_dose","err_event","err_event","err_event","err_event");
auto ambient_dose_hist = df_data_update.GraphAsymmErrors("event_id","ambient_dose_equivalent","err_event","err_event","err_event","err_event");

auto *effec_dose_hist_clone = (TGraphAsymmErrors*)effec_dose_hist->Clone("effective_dose");
auto *ambient_dose_hist_clone = (TGraphAsymmErrors*)ambient_dose_hist->Clone("ambient_dose_equivalent");

TCanvas* canvas = new TCanvas ("canvas","canvas",1920,1080) ;

effec_dose_hist_clone->SetLineColor(kBlue);
effec_dose_hist_clone->SetMarkerStyle(20);
effec_dose_hist_clone->SetLineWidth(2);
effec_dose_hist_clone->SetMarkerColor(kBlue);

ambient_dose_hist_clone->SetLineColor(kOrange);
ambient_dose_hist_clone->SetMarkerStyle(47);
ambient_dose_hist_clone->SetLineWidth(2);
ambient_dose_hist_clone->SetMarkerColor(kOrange);

ambient_dose_hist_clone->SetTitle("#bf{H*(10) Ambient dose equivalent per event @LCO Campaign (ICRP 74 & Ferrari1998 Conv Coeff)}"); // pag 131
effec_dose_hist_clone->SetTitle("#bf{Effective dose per event @LCO Campaign (ICRP 116 ISO Conv Coeff)}"); // pag 131
effec_dose_hist_clone->GetYaxis()->SetTitle("#bf{Effective dose (nSv/h) }");
effec_dose_hist_clone->GetXaxis()->SetTitle("#bf{Event}");


effec_dose_hist_clone->DrawClone("AP");
ambient_dose_hist_clone->DrawClone("P");

TLegend *legend_c = new TLegend(0.136905,0.720314,0.502706,0.896958);
legend_c->AddEntry(ambient_dose_hist_clone,"#bf{E Ambient dose equivalent per event @LCO Campaign (ICRP 74 & Ferrari1998 Conv Coeff)}","p");
legend_c->AddEntry(effec_dose_hist_clone,"#bf{Effective dose per event @LCO Campaign (ICRP 116 ISO Conv Coeff)}","p");
legend_c->SetTextSize(0.02);
legend_c->SetMargin(0.1);// acorta la distancia entre el marcador y el texto
legend_c->Draw();

}


void routine_data_merge_em_mc(){
integral_data_merge("LCO",15,11);
plot_data_merge("LCO",15,11);
relations_integral_local_variables_merge("LCO",15,11);
plot_relations_integral_local_variables_merge("LCO",15,11);

}

