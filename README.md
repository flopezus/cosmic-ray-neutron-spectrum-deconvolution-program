# Cosmic Ray Neutron Spectra Deconvolutions
## Root Macro 
    
  `deconv_CRNS.C` is a `ROOT` macro written using the paradigm of functional programming. The main objective of this macro is to obtain a  
  neutron spectrum using several deconvolution or unfolding algorithms, which use as input:  
    
  -Experimental counting rate data from the CEFNEN-Spectrometer based on the Bonner's Sphere Method.  
  -Simulated Response Functions of the CEFNEN-Spectrometer using Geant4 code.  
  -Calculated neutron spectrum at ground level using EXPACS/PARMA code as the seed of the unfolding algorithms.  
## Implemented Functions
    
	1. For the input data:
		- `vector<vector<double_t> > Response_function_matrix_lin_spec_2023()` is a function that takes as input the simulated response functions
		  as root file of each detector-moderator system of the CEFNEN-Spectrometer and return a vector of vector (matrix) where each column corresponds to each  
		  response function of each detector-moderator of the spectrometer sorted as:  
			- `Efi_1_12cmHDPE_VV.root`
			- `Efi_2_10cmHDPE_VV.root`
			- `Efi_3_4cmHDPE_VV.root`
			- `Efi_4_CylinderHDPE_VV.root`
			- `Efi_5_Cylinder7mmAl_1.8cmBHDPECore_VV.root`
			- `Efi_6_18cmHDPE_VV.root`
			- `Efi_7_20cmHDPE_VV.root`
			- `Efi_8_1inchBHDPE_10cmHDPE_VV.root`
			- `Efi_9_20cmBHDPE_1.0inch_VV.root`
			- `Efi_10_Cylinder_4cm_VV.root`
			- `Efi_11_Cylinder_3cm_VV.root`
			- `Efi_12_Pb_10cmBHDPEcore_VV.root`
			- `Efi_13_1inchBHDPE_15cmGraphite_VV.root`
			- `Efi_14_inchBHDPE_15cmHDPE_VV.root`
			- `Efi_15_24cmHDPE_VV.root`
			- `Efi_16_Naked_1inch_VV.root`
		- `vector<vector<double_t> > Counting_rate_matrix(int time)` is a function that takes the grid time (15 or 60 minutes for now) as input and retrieves the number of accumulated neutrons indexed in this time grid.
		  It returns a matrix (vector of vectors) where each column corresponds to the counting rate per grid time corresponding to each detector-moderator system, sorted as in `Response_function_matrix_lin_spec_2023()` function.  
		  In this manner, each row or event of this matrix represents the value of the counting rate throughout the measurement time width at a campaign's location, with an average value of 3 days or 72 hours.  
		- `vector<vector<double_t> > neutrons_count_matrix(int time)`  is a function that takes the grid time (15 or 60 minutes for now) as input and retrieves the number of accumulated neutrons indexed in this time grid.
		  It returns a matrix (vector of vectors) where each column corresponds to number of neutrons accumulated in the time grid corresponding to each detector-moderator system, sorted as in `Response_function_matrix_lin_spec_2023()` function.  
		  In this manner, each row or event of this matrix represents the value of the acumulated neutrons throughout the measurement time width at a campaign's location, with an average value of 3 days or 72 hours.  
		- `vector<vector<double_t> > E_neutrons_count_matrix(int time)`  is a function that takes the grid time (15 or 60 minutes for now) as input and retrieves the number of accumulated neutrons indexed in this time grid. It returns the uncertainty of counting rate, due only to the counting statistics.
	2. Unfolding Algorithms:
		- `vector<Double_t> Recalculate(vector< vector<Double_t>> R, vector<Double_t> Flux, vector<Double_t> dE, double ndet)` is a function that returns the calculated counting rates of neutrons for each iteration of the EM algorithm. To achieve this, it use the deconvoluted neutron flux of each step in its differential representation, along with the response functions and the bin energy width. As output, it generates a vector with the recalculated counting rates for each step, where each entry of the vector is associated with each detector from detector 1 to 16.
		- `void deconv_em(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm)` is a function that performs the Expectation-Maximization (EM) method. It takes as input the response functions given by `Response_function_matrix_lin_spec_2023()`,
		  the counting rate data given by `Counting_rate_matrix()`, the numbers of accumulated neutrons given by `neutrons_count_matrix()`, the uncertainty of counting rate given by `E_neutrons_count_matrix()` and the initial spectrum value or seed of the unfolding method  
		  calculated using EXPACS/PARMA, stored as a `.csv` file which also contains the energy binning (same as the response functions). The parameters of the function correspond to:  
			- `string campaign` name of the campaign to analize
			- `int event` number of the event from which take the counting rates values.
			- `int steps` number of iterations of the EM algorithm.
			- `int vwc_seed` number of the seed to use, from a data pool of 51 different volume water content percentages of the ground in steps of 0.2% from 0% (dry soil) to 100%(pure water).
			- `int crptime,` time grid value of the data, 15 or 60 for now.
			- `string flux_type` type of plot representation of the spectrum, either `Differential`, `Integral`, or `Lethargy`.
			- `int norm` normalization of the spectrum, either `1` o `0`.
			  The function returns the plot of the seed spectrum, plot of the spectrum of the last iteration of the EM method, and plot spectra of each iteration of EM method.  
		- `vector<double> deconv_em_output(string campaign, int event, int steps, int vwc_seed, int crptime, string flux_type, int norm)` is a function that performs the Expectation-Maximization (EM) method. It takes as input the response functions given by `Response_function_matrix_lin_spec_2023()`,
		  the counting rate data given by `Counting_rate_matrix()`, the numbers of accumulated neutrons given by `neutrons_count_matrix()`, the uncertainty of counting rate given by `E_neutrons_count_matrix()` and the initial spectrum value or seed of the unfolding method  
		  calculated using EXPACS/PARMA, stored as a `.csv` file which also contains the energy binning (same as the response functions). The parameters of the function correspond to:  
			- `string campaign` name of the campaign to analize
			- `int event` number of the event from which take the counting rates values.
			- `int steps` number of iterations of the EM algorithm.
			- `int vwc_seed` number of the seed to use, from a data pool of 51 different volume water content percentages of the ground in steps of 0.2% from 0% (dry soil) to 100%(pure water).
			- `int crptime,` time grid value of the data, 15 or 60 for now.
			- `string flux_type` type of plot representation of the spectrum, either `Differential`, `Integral`, or `Lethargy`.
			- `int norm` normalization of the spectrum, either 1 o 0.
			  The function returns a vector whith the spectrum in its differential representation resulting of the unfolding method after a number of iterations given by `steps`. Appended to this vector are the:  
			- `int ndet`: The numbers of detectors to use in the EM deconvolution.
			- `double integral_flux_deconv_total_Intg`: The total integral of the deconvoluted spectrum in its integral representation.
			- `double integral_flux_deconv_th`: The integral in the thermal region of the deconvoluted spectrum in its integral representation.
			- `double integral_flux_deconv_ep`: The integral in the epithermal region of the deconvoluted spectrum in its integral representation.
			- `double integral_flux_deconv_fs`: The integral in the fast region of the deconvoluted spectrum in its integral representation.
			- `double integral_flux_deconv_he`: The integral in the high-energy region of the deconvoluted spectrum in its integral representation.
			- `double chi2`: The value of chi-quare coresponding to the last iteration of the EM method.
			- `doublle chi2_red`: The value of reduced chi-square coresponding to the last iteration of the EM method.
	3. Statistical Estimators:
		- `double_t Chi_Square(vector<Double_t> C_i,vector<Double_t> dCR, vector<Double_t> N_rec, double ndet, int crptime)` is a function that returns the chi-square value given an experimental and calculated counting rates.
		- `double_t Chi_Square_red(vector<Double_t> C_i, vector<Double_t> dCR, vector<Double_t> N_rec, double ndet, int crptime)` is a function that returns the reduced chi-square value given an experimental and calculated counting rate. That is, the chi-square value divided by the degrees of fredom of the system, in our case the number of detectors.
		- `double_t Xi_Square(vector<Double_t> C_i, vector<Double_t> N_rec, double ndet, int crptime)` is a function that returns the xi-square value given an experimental and calculated counting rates.
		- `double_t bar_delta(vector<Double_t> C_i, vector<Double_t> N_rec, double ndet, int crptime)` is a function that returns the average difference between the experimental and calculated counting rates.
		- `double_t STD_cr(vector<Double_t> C_i, vector<Double_t> N_rec, double ndet, int crptime)`  is a function that returns the standard deviation for N measurements of counting rates.
## Loops over EM method

	- `void em_loop_seed(string campaign, int event, int steps, int time_grid)` is a function that takes as input the number of the event to process (from which counting rates are extracted), a fixed number of steps to iterate the EM method for each seed, and the time grid of the couting rates.
		It then iterates the EM algorithm `deconv_em_output()` (for the given number of steps) over all the seed values. It returns a unique root file for every seed value in which a TTree is stored. The branches of the tree include:
			- `vector<Double_t> deconv_vec`: Deconvoluted flux (resulting from the specified the number of steps of EM method) in its integral representation as a vector.
			- `int ndet`: The numbers of detectors used in the EM method.
			- `Intg_total`: The total integral of the spectrum.
			- `Intg_th`: The integral in the thermal region of the spectrum.
			- `Intg_ep`: The integral in the epithermal region of the spectrum.
			- `Intg_fs`: The integral in the fast region of the spectrum.
			- `Intg_he`: The integral in the high-energy region of the spectrum.
			- `double Chi2`: The chi-square value.
			- `duble Chi2red`: The reduce chi-square value.
	- `void em_loop_steps(string campaign, int event, int steps, int time_grid, int ndet)` is a function that iterates the `em_loop_seed()` function over a number of steps from `1` to `steps`, generating a unique root file for each seed and steps value for a given event.
	- `void em_loop_events(string campaign,int steps,int time_grid, int ndet)` is a function that iterates the `em_loop_steps()` function over all events from a campaign.
## Plotting functions
	- `TH1D* em_step_plot_IntgTotal_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the total integral of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used. 
	- `TH1D* em_step_plot_Intgth_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the integral in the thermal region of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used. 
	- `TH1D* em_step_plot_Intgep_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the integral in the epithermal region of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used. 
	- `TH1D* em_step_plot_Intgfs_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the integral in the fast region of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used. 
	- `TH1D* em_step_plot_Intghe_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the integral in the high-energy region of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used. 
	- `TH1D* em_step_plot_Chi_TH1D(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a TH1D histogram object for the chi-square resulting from the last step of the EM method of the deconvoluted flux in its integral representation (with the x-axis representing the seed value as a bin value) for a given event, number of steps, time grid, and number of detectors used.
	- `void em_loop_seed_plot_template(string campaign, int event, int steps, int timegrid, int ndet)` is a function that returns a canvas divided in 6 pads, within each pad is plotted the corresponding histogram obtained from the previous 6 functions.
	- `TH1D* deconv_hist_from_steps_and_seeds_TH1D(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation)` is a function that returns a TH1D histogram object for a deconvoluted flux for a given event, number of steps, time grid, number of detectors used, and seed value (as bin number, from 1 to 51), in a selected spectrum representation: `Differential`, `Integral`, or `Lethargy`.
	- `void deconv_flux_multiplot_by_seed(string campaign, int event, int steps, int timegrid, int ndet, int bin_seed, string flux_representation)` is a function that returns a canvas divided into a number of pads according to the maximum of steps to iterate the EM method from `1` to `steps`, with a TH1D histogram object in each of them resulting from the previous function, i.e., representing the deconvoluted flux. 
	- `void em_routine_plot(string campaign, int event, int max_steps, int max_bin_seed)` is a function that loop over `deconv_flux_multiplot_by_seed()` generating a PDF for each iteration.
	- `void em_loop_seed_plot(string campaign, int event, int steps)` test of `em_loop_seed_plot_template()` using only chi-square values in function of seed values.
	
## Other functions
	- `void RF_CEFNEN_spectrometer_root_file()` is a function that returns a root file containing a TTree with branches representing the energy binning and the simulated response functions of each detector-moderator system of the CEFNEN-Spectrometer.
	- `void neutron_flux_plots(int vwc_seed)` is a function that returns a canvas containing the histogram plot for a given seed (generated from EXPACS/PARMA code) in three different representations: `Differential`, `Integral` or `Group Plot`, and `Lethargy` or `Group Plot per Energy`, as well as the EXPACS spectrum, which is a spectrum in its lethargy representation.
	- `vector<vector<double_t> > Response_function_matrix_fm()` is a function that returns a matrix with the simulated response functions from `.csv` files.
	- `void em_routine(string campaign)` is a function designed to execute functions from the "Loops over EM method" section in a logical order.
	- `void TRS_data_csv_to_root()`
	- `void TRS_plot_spectra()`
	- `void neutron_flux_plots(int vwc_seed)` to compare neutron spectra representationS using seed fluxes from EXPACS

## USAGE

To iterate one event over all seeds with different steps in the EM algoithm, we execute, for instance:
Event: 210, Steps: from 1 to 20, Time grid: 15, Detectors used: 11.

`em_loop_steps(,"LCO",210,20,15,11);`

After this Execution, we can use:

To generate the corresponding plot of the spectra in its Lethargy representation using the spectra generated by the previous function for a specific value of bin seed, for instance `1`, we use:

`deconv_flux_multiplot_by_seed("LCO",210,20,15,11,1,"Lethargy")`

To loop an event over all seed values, generating a PDF for each one using `deconv_flux_multiplot_by_seed()` function:

`em_routine_plot("LCO",40,20,51)`

To generate a canvas with 6 pads with plots of Chi-square value, total integral, integral in the thermal region, integral in the epithermal region, integral in the fast region, and integral in the high-energy region for results of EM deconvolutions using steps from `1` to `20`, we use:

`em_loop_seed_plot_template("LCO",210,20,15,11)`

To loop the EM algorithm using steps from 1 to 20, in a time grid of 15 min, using 11 detectors over all events from a determined campaign ("LCO" in this case), we use:

`em_loop_events("LCO",20,15,11)`


