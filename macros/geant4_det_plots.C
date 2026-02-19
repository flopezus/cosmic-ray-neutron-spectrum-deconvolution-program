#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>

#include <ROOT/RDFHelpers.hxx>

using namespace std;
using namespace ROOT::VecOps; // para definir vectores como  RVec<double>>("vecCol");

void plot_gdml_from_geant4(){

// TCanvas* canvas = new TCanvas("canvas", "canvas", 1400, 1000);
// canvas->SetSupportGL(true);
// gStyle->SetCanvasPreferGL(kTRUE);
// gStyle->SetLineScalePS(1); // Para que guardar correctamente el canvas (lineas delgadas)

TGeoManager::Import("/home/flopez/LIN/TESIS_DOC/Analysis/geant4_to_root/gdml/13_BHDPE_grafito.gdml");

   /* ------------------------------------------------------------------
    * 1.  Global display settings  – make the viewer draw filled faces
    * ---------------------------------------------------------------- */
	gGeoManager->SetTopVisible();

   gGeoManager->SetVisOption(0);     // 0 = shaded (solid), 1 = wire-frame,
                                     // 2 = shaded+edges, 3 = bounding boxes …
   gGeoManager->SetVisLevel(7);      // how deep down the geometry tree to draw
   // Load GDML geometry
    //TGeoManager::Import("geometry_exported.gdml");

  // Forzar actualización del volumen madre si está muy transparente
  TGeoVolume *mother = gGeoManager->FindVolumeFast("Mother_Logic_Alpha");
  if (mother) {
    mother->SetLineColor(kGray + 1);
    mother->SetTransparency(90); // Casi invisible para ver dentro
  }

  // Hacer visible y opaco el volumen de interés
  // TGeoVolume *logCore = gGeoManager->FindVolumeFast("Logic_Core_Alpha");
  // if (logCore) {
    // logCore->SetLineColor(kRed);
    // logCore->SetTransparency(0); // 0 = opaco
    // logCore->SetVisibility(kTRUE);
  // }

  // Crear el canvas y dibujar
  TCanvas *c1 = new TCanvas("c1", "Geometry View", 1200, 1000);

  // Draw the top volume
  gGeoManager->GetTopVolume()->SetVisContainers(kTRUE);
  gGeoManager->GetTopVolume()->SetVisibility(kFALSE);
  

  gGeoManager->GetTopVolume()->Draw("ogl");

  // Esperar para asegurar renderizado antes de guardar
  gSystem->ProcessEvents();


	// 2. Grab the embedded GL viewer that lives inside the pad
TGLViewer *v = static_cast<TGLViewer*>(gPad->GetViewer3D());
if (!v) return;                   // safety check

// ------------------------------------------------------------------
//  QUICK WAY (pre-defined views)
// ------------------------------------------------------------------
// Choose one of the built-in cameras and make it current:
v->SetCurrentCamera(TGLViewer::kCameraPerspYOZ);   // XOZ perspective
//            kCameraPerspYOZ, kCameraPerspXOY,
//            kCameraOrthoXOY, kCameraOrthoXOZ, …  see enum list :contentReference[oaicite:0]{index=0}

v->ResetCurrentCamera();          // centres and zooms so everything is visible
v->RequestDraw();                 // or gPad->Modified(); gPad->Update();


// ------------------------------------------------------------------
//  FULL CONTROL (field-of-view, distance, rotations …)
// ------------------------------------------------------------------
// Double_t center[3] = {-1.522449,0,-3.623747};     // point the camera looks at (world coordinates)
Double_t center[3] = {0,0,0};     // point the camera looks at (world coordinates)
Double_t fov     = 30.;           // field-of-view in degrees
Double_t dolly   = 1.;          // distance from center (units = your geometry)
// Double_t hRot    = TMath::DegToRad()*45.;  // horizontal rotation  (azimuth)

//Vis 1 (se ve completo el productor)
// Double_t hRot    = -TMath::DegToRad()*30.;  // horizontal rotation  (azimuth)
// Double_t vRot    = TMath::DegToRad()*45.;  // vertical   rotation  (elevation)

//Vis 2 (se ve completo el productor)
Double_t hRot    = -TMath::DegToRad()*17.;  // horizontal rotation  (azimuth)
Double_t vRot    = TMath::DegToRad()*60.;  // vertical   rotation  (elevation)

v->SetPerspectiveCamera(TGLViewer::kCameraPerspYOZ,fov, dolly, center, hRot, vRot); 
v->RequestDraw();                 // redraw with the new camera


}

void set_visibility_and_export_gdml(string input_gdml, string output_gdml) {
    // Load the GDML file

	string path = "/home/flopez/Data/Dropbox/DOC_WORK/TESIS_DOC/Analysis/geant4_to_root/gdml/";

	string file_path_input = path+input_gdml;
	string file_path_output = path+output_gdml;

	
    
    TGeoManager::Import(file_path_input.c_str());

    gGeoManager->SetTopVisible();

   gGeoManager->SetVisOption(0);     // 0 = shaded (solid), 1 = wire-frame,
                                     // 2 = shaded+edges, 3 = bounding boxes …
   gGeoManager->SetVisLevel(7);      // how deep down the geometry tree to draw
    // if (!gGeoManager) {
        // std::cerr << "Failed to load GDML file: " << input_gdml << std::endl;
        // return;
    //}

    // Get all volumes in the geometry
    // TObjArray* volumes = gGeoManager->GetListOfVolumes();
    // if (!volumes) {
        // std::cerr << "No volumes found in geometry." << std::endl;
        // return;
    // }

    // Set all volumes to be visible
    //for (int i = 0; i < volumes->GetEntries(); ++i) {
        // TGeoVolume* vol = dynamic_cast<TGeoVolume*>(volumes->At(i));
        //if (vol) {
            // vol->SetVisibility(kTRUE);  // or vol->SetVisLeaves(kTRUE);
        // }
    // }

	TGeoVolume *mother = gGeoManager->FindVolumeFast("Mother_Logic_Alpha");

   TGeoVolume *Mother = gGeoManager->FindVolumeFast("WordlLogic");

   TGeoVolume *BoxShieldZminus = gGeoManager->FindVolumeFast("Box_Shielding_Z_Minus");
   TGeoVolume *BoxShieldZplus = gGeoManager->FindVolumeFast("Box_Shielding_Z_Plus");
   TGeoVolume *BoxShieldXminus = gGeoManager->FindVolumeFast("Box_Shielding_X_Minus");
   TGeoVolume *BoxShieldXplus = gGeoManager->FindVolumeFast("Box_Shielding_X_Plus");
   TGeoVolume *BoxShieldYminus = gGeoManager->FindVolumeFast("Box_Shielding_Y_Minus");
   TGeoVolume *BoxShieldYplus = gGeoManager->FindVolumeFast("Box_Shielding_Y_Plus");
   
   TGeoVolume *BoxCdZminus = gGeoManager->FindVolumeFast("Box_Cadmium_Z_Minus");
   TGeoVolume *BoxCdZplus = gGeoManager->FindVolumeFast("Box_Cadmium_Z_Plus");
   TGeoVolume *BoxCdXminus = gGeoManager->FindVolumeFast("Box_Cadmium_X_Minus");
   TGeoVolume *BoxCdXplus = gGeoManager->FindVolumeFast("Box_Cadmium_X_Plus");
   TGeoVolume *BoxCdYminus = gGeoManager->FindVolumeFast("Box_Cadmium_Y_Minus");
   TGeoVolume *BoxCdYplus = gGeoManager->FindVolumeFast("Box_Cadmium_Y_Plus");

   TGeoVolume *BoxProducer = gGeoManager->FindVolumeFast("Box_Producer_Logical");

   TGeoVolume *BoxInLog = gGeoManager->FindVolumeFast("Box_In_Logical");
   TGeoVolume *BoxInnerMod = gGeoManager->FindVolumeFast("Box_Matrix_Logical");

   TGeoVolume *CilindroSpace_InMod = gGeoManager->FindVolumeFast("Cilindro_Img_Cover");
   TGeoVolume *CilindroSpace_ProdMod = gGeoManager->FindVolumeFast("Cilindro_Cable_Producer_Log");
   TGeoVolume *CilindroSpace_ExtMod = gGeoManager->FindVolumeFast("Cilindro_Cable_Shield_Log");

   TGeoVolume *DetectorAV = gGeoManager->FindVolumeFast("DetectorLV");

   /**Colores y Transparencia**/
	int transparency = 50;
	int transparency_shield = 0;
	int transparency_cd = 0;
	// int transparency =0;
	// bool act_trans = kFALSE;
	bool act_trans = kTRUE;
	bool act_trans_shield = kTRUE;
	// bool act_cd = kFALSE;
	bool act_cd = kTRUE;

	// string color_prod = kGray;
	Color_t color_HDPE = 12;
	Color_t color_prod = kRed;
	Color_t color_cad = kYellow;
	Color_t color_graphite = 14;
	//Color_t color_BHDPE = 8;

	//auto myGreen = new TColor(3001,0.0,0.8,0.0); // 0.8 instead of 1.0<br>vol->SetLineColor(myGreen->GetNumber());<br>vol->SetFillColor(myGreen->GetNumber());
	auto myGreen = new TColor(3001, 0.00, 0.90, 0.00);
	// Color_t color_BHDPE = myGreen->GetNumber();
	Color_t color_BHDPE = myGreen->GetNumber();

   	if(BoxShieldZminus){
		BoxShieldZminus->SetVisibility(act_trans_shield);
		BoxShieldZminus->SetTransparency(transparency_shield); 
		BoxShieldZminus->SetLineColor(12);
	}
	if(BoxShieldZplus){
		BoxShieldZplus->SetVisibility(act_trans_shield);
		BoxShieldZplus->SetTransparency(transparency_shield); 
		BoxShieldZplus->SetLineColor(12);
		BoxShieldZplus->SetFillColor(12);
	}
	
    BoxShieldXminus->SetVisibility(act_trans_shield);
	BoxShieldXminus->SetTransparency(transparency_shield); 
	BoxShieldXminus->SetLineColor(color_HDPE);
    BoxShieldXplus->SetVisibility(act_trans_shield);
	BoxShieldXplus->SetTransparency(transparency_shield); 
	BoxShieldXplus->SetLineColor(color_HDPE);
	
    BoxShieldYminus->SetVisibility(act_trans_shield);
	BoxShieldYminus->SetTransparency(transparency_shield); 
	BoxShieldYminus->SetLineColor(color_HDPE);
    BoxShieldYplus->SetVisibility(act_trans_shield);
	BoxShieldYplus->SetTransparency(transparency_shield); 
	BoxShieldYplus->SetLineColor(color_HDPE);
	
    BoxCdZminus->SetVisibility(kFALSE);
	BoxCdZminus->SetTransparency(transparency_cd); 
	BoxCdZminus->SetLineColor(color_cad);
    BoxCdZplus->SetVisibility(kFALSE);
	BoxCdZplus->SetTransparency(transparency_cd); 
	BoxCdZplus->SetLineColor(color_cad);
	
    BoxCdXminus->SetVisibility(act_cd);
	BoxCdXminus->SetTransparency(transparency_cd); 
	BoxCdXminus->SetLineColor(color_cad);
    BoxCdXplus->SetVisibility(act_cd);
	BoxCdXplus->SetTransparency(transparency_cd); 
	BoxCdXplus->SetLineColor(color_cad);
	
    BoxCdYminus->SetVisibility(act_cd);
	BoxCdYminus->SetTransparency(transparency_cd); 
	BoxCdYminus->SetLineColor(color_cad);
    BoxCdYplus->SetVisibility(kFALSE);
	BoxCdYplus->SetTransparency(transparency_cd); 
	BoxCdYplus->SetLineColor(color_cad);
	
    BoxProducer->SetVisibility(act_trans);
	BoxProducer->SetTransparency(0); 
	BoxProducer->SetLineColor(color_prod);
	BoxProducer->SetFillColor(color_prod);
	BoxProducer->SetFillStyle(1001);
	
    BoxInnerMod->SetVisibility(act_trans);
	BoxInnerMod->SetTransparency(0); 
	BoxInnerMod->SetLineColor(color_BHDPE);
	BoxInnerMod->SetFillColor(color_BHDPE);
	BoxInnerMod->SetFillStyle(1001);

	CilindroSpace_InMod->SetVisibility(act_trans);
	CilindroSpace_InMod->SetTransparency(0); 
	CilindroSpace_InMod->SetLineColor(kCyan-10);
	CilindroSpace_InMod->SetFillColor(kCyan-10);
	CilindroSpace_InMod->SetFillStyle(1001);
	
	CilindroSpace_ProdMod->SetVisibility(act_trans);
	CilindroSpace_ProdMod->SetTransparency(0); 
	CilindroSpace_ProdMod->SetLineColor(kCyan-10);
	CilindroSpace_ProdMod->SetFillColor(kCyan-10);
	CilindroSpace_ProdMod->SetFillStyle(1001);
	
	CilindroSpace_ExtMod->SetVisibility(act_trans);
	CilindroSpace_ExtMod->SetTransparency(0); 
	CilindroSpace_ExtMod->SetLineColor(kCyan-10);
	CilindroSpace_ExtMod->SetFillColor(kCyan-10);
	CilindroSpace_ExtMod->SetFillStyle(1001);
	
    DetectorAV->SetVisibility(act_trans);
	DetectorAV->SetTransparency(transparency); 
	DetectorAV->SetLineColor(kViolet);
	
    BoxInLog->SetVisibility(0);

    // Export modified geometry to GDML
    gGeoManager->Export(file_path_output.c_str());
    std::cout << "Exported modified GDML to: " << output_gdml << std::endl;
}

void visualize_detector(){
  // Importar GDML
// TGeoManager::Import("/home/flopez/LIN/TESIS/Programas_Tesis/geant4_codes/detector_sapito/build/geometry_exported.gdml");

//string det_name = "12_MiniMonitor";
string det_name = "13_BHDPE_grafito";

TGeoManager::Import(("/home/flopez/LIN/TESIS_DOC/Analysis/geant4_to_root/gdml/"+det_name+".gdml").c_str());

   /* ------------------------------------------------------------------
    * 1.  Global display settings  – make the viewer draw filled faces
    * ---------------------------------------------------------------- */
   gGeoManager->SetTopVisible();

   gGeoManager->SetVisOption(3);     // 0 = shaded (solid), 1 = wire-frame,
                                     // 2 = shaded+edges, 3 = bounding boxes …
   gGeoManager->SetVisLevel(7);      // how deep down the geometry tree to draw

/**Colores y Transparencia**/
	int transparency = 50;
	int transparency_shield = 0;
	int transparency_cd = 0;
	// int transparency =0;
	// bool act_trans = kFALSE;
	bool act_trans = kTRUE;
	bool act_trans_shield = kTRUE;
	bool act_cd = kFALSE;

	// string color_prod = kGray;
	Color_t color_HDPE = 12;
	Color_t color_prod = kRed;
	Color_t color_cad = kYellow;
	Color_t color_graphite = 14;
	// Color_t color_BHDPE = 8;

	// auto myGreen = new TColor(3001,0.0,0.8,0.0); // 0.8 instead of 1.0<br>vol->SetLineColor(myGreen->GetNumber());<br>vol->SetFillColor(myGreen->GetNumber());
	auto myGreen = new TColor(3001, 0.00, 0.90, 0.00);
	// Color_t color_BHDPE = myGreen->GetNumber();
	Color_t color_BHDPE = myGreen->GetNumber();
/***********************************/

if(det_name=="12_MiniMonitor"){

// TGeoManager *geom = new TGeoManager("simple1", "/home/flopez/LIN/TESIS/Programas_Tesis/geant4_codes/detector_sapito/build/geometry_exported.gdml");

  /***********MiniMonitor****************/
  // Obtener volumen de interés

   TGeoVolume *Mother = gGeoManager->FindVolumeFast("WordlLogic");

   TGeoVolume *BoxShieldZminus = gGeoManager->FindVolumeFast("Box_Shielding_Z_Minus");
   TGeoVolume *BoxShieldZplus = gGeoManager->FindVolumeFast("Box_Shielding_Z_Plus");
   TGeoVolume *BoxShieldXminus = gGeoManager->FindVolumeFast("Box_Shielding_X_Minus");
   TGeoVolume *BoxShieldXplus = gGeoManager->FindVolumeFast("Box_Shielding_X_Plus");
   TGeoVolume *BoxShieldYminus = gGeoManager->FindVolumeFast("Box_Shielding_Y_Minus");
   TGeoVolume *BoxShieldYplus = gGeoManager->FindVolumeFast("Box_Shielding_Y_Plus");
   
   TGeoVolume *BoxCdZminus = gGeoManager->FindVolumeFast("Box_Cadmium_Z_Minus");
   TGeoVolume *BoxCdZplus = gGeoManager->FindVolumeFast("Box_Cadmium_Z_Plus");
   TGeoVolume *BoxCdXminus = gGeoManager->FindVolumeFast("Box_Cadmium_X_Minus");
   TGeoVolume *BoxCdXplus = gGeoManager->FindVolumeFast("Box_Cadmium_X_Plus");
   TGeoVolume *BoxCdYminus = gGeoManager->FindVolumeFast("Box_Cadmium_Y_Minus");
   TGeoVolume *BoxCdYplus = gGeoManager->FindVolumeFast("Box_Cadmium_Y_Plus");

   TGeoVolume *BoxProducer = gGeoManager->FindVolumeFast("Box_Producer_Logical");

   TGeoVolume *BoxInLog = gGeoManager->FindVolumeFast("Box_In_Logical");
   TGeoVolume *BoxInnerMod = gGeoManager->FindVolumeFast("Box_Matrix_Logical");

   TGeoVolume *CilindroSpace_InMod = gGeoManager->FindVolumeFast("Cilindro_Img_Cover");
   TGeoVolume *CilindroSpace_ProdMod = gGeoManager->FindVolumeFast("Cilindro_Cable_Producer_Log");
   TGeoVolume *CilindroSpace_ExtMod = gGeoManager->FindVolumeFast("Cilindro_Cable_Shield_Log");

   TGeoVolume *DetectorAV = gGeoManager->FindVolumeFast("DetectorLV");





	// Mother->SetVisContainers(kTRUE);
	// Mother->SetVisibility(kFALSE);

	if(BoxShieldZminus){
		BoxShieldZminus->SetVisibility(act_trans_shield);
		BoxShieldZminus->SetTransparency(transparency_shield); 
		BoxShieldZminus->SetLineColor(12);
	}
	if(BoxShieldZplus){
		BoxShieldZplus->SetVisibility(act_trans_shield);
		BoxShieldZplus->SetTransparency(transparency_shield); 
		BoxShieldZplus->SetLineColor(12);
		BoxShieldZplus->SetFillColor(12);
	}
	
    BoxShieldXminus->SetVisibility(act_trans_shield);
	BoxShieldXminus->SetTransparency(transparency_shield); 
	BoxShieldXminus->SetLineColor(color_HDPE);
    BoxShieldXplus->SetVisibility(act_trans_shield);
	BoxShieldXplus->SetTransparency(transparency_shield); 
	BoxShieldXplus->SetLineColor(color_HDPE);
	
    BoxShieldYminus->SetVisibility(act_trans_shield);
	BoxShieldYminus->SetTransparency(transparency_shield); 
	BoxShieldYminus->SetLineColor(color_HDPE);
    BoxShieldYplus->SetVisibility(act_trans_shield);
	BoxShieldYplus->SetTransparency(transparency_shield); 
	BoxShieldYplus->SetLineColor(color_HDPE);
	
    BoxCdZminus->SetVisibility(kFALSE);
	BoxCdZminus->SetTransparency(transparency_cd); 
	BoxCdZminus->SetLineColor(color_cad);
    BoxCdZplus->SetVisibility(kFALSE);
	BoxCdZplus->SetTransparency(transparency_cd); 
	BoxCdZplus->SetLineColor(color_cad);
	
    BoxCdXminus->SetVisibility(act_cd);
	BoxCdXminus->SetTransparency(transparency_cd); 
	BoxCdXminus->SetLineColor(color_cad);
    BoxCdXplus->SetVisibility(act_cd);
	BoxCdXplus->SetTransparency(transparency_cd); 
	BoxCdXplus->SetLineColor(color_cad);
	
    BoxCdYminus->SetVisibility(act_cd);
	BoxCdYminus->SetTransparency(transparency_cd); 
	BoxCdYminus->SetLineColor(color_cad);
    BoxCdYplus->SetVisibility(kFALSE);
	BoxCdYplus->SetTransparency(transparency_cd); 
	BoxCdYplus->SetLineColor(color_cad);
	
    BoxProducer->SetVisibility(act_trans);
	BoxProducer->SetTransparency(0); 
	BoxProducer->SetLineColor(color_prod);
	BoxProducer->SetFillColor(color_prod);
	BoxProducer->SetFillStyle(1001);
	
    BoxInnerMod->SetVisibility(act_trans);
	BoxInnerMod->SetTransparency(0); 
	BoxInnerMod->SetLineColor(color_BHDPE);
	BoxInnerMod->SetFillColor(color_BHDPE);
	BoxInnerMod->SetFillStyle(1001);

	CilindroSpace_InMod->SetVisibility(act_trans);
	CilindroSpace_InMod->SetTransparency(0); 
	CilindroSpace_InMod->SetLineColor(kCyan-10);
	CilindroSpace_InMod->SetFillColor(kCyan-10);
	CilindroSpace_InMod->SetFillStyle(1001);
	
	CilindroSpace_ProdMod->SetVisibility(act_trans);
	CilindroSpace_ProdMod->SetTransparency(0); 
	CilindroSpace_ProdMod->SetLineColor(kCyan-10);
	CilindroSpace_ProdMod->SetFillColor(kCyan-10);
	CilindroSpace_ProdMod->SetFillStyle(1001);
	
	CilindroSpace_ExtMod->SetVisibility(act_trans);
	CilindroSpace_ExtMod->SetTransparency(0); 
	CilindroSpace_ExtMod->SetLineColor(kCyan-10);
	CilindroSpace_ExtMod->SetFillColor(kCyan-10);
	CilindroSpace_ExtMod->SetFillStyle(1001);
	
    DetectorAV->SetVisibility(act_trans);
	DetectorAV->SetTransparency(transparency); 
	DetectorAV->SetLineColor(kViolet);
	
    BoxInLog->SetVisibility(0);

}

if(det_name=="13_BHDPE_grafito"){

	TGeoVolume *Mother = gGeoManager->FindVolumeFast("WordlLogic");

   TGeoVolume *TapaDer = gGeoManager->FindVolumeFast("Logic_Tapa_Der");
   TGeoVolume *TapaIzq = gGeoManager->FindVolumeFast("Logic_Tapa_Izq");
   TGeoVolume *ExtCore = gGeoManager->FindVolumeFast("Logic_Box_Boron_Polyethylene_TS_Alpha");
   TGeoVolume *AirCore = gGeoManager->FindVolumeFast("CoreAir_VolAlpha");
   TGeoVolume *GraphiteCore = gGeoManager->FindVolumeFast("Logic_Core_Alpha");
   TGeoVolume *CilindroSpace_InMod = gGeoManager->FindVolumeFast("Cilindro_Air_Vol_Alpha");
	TGeoVolume *DetectorAV = gGeoManager->FindVolumeFast("DetectorLV");
   
    TapaDer->SetVisibility(act_trans);
	TapaDer->SetTransparency(0); 
	TapaDer->SetLineColor(color_BHDPE);
	TapaDer->SetFillColor(color_BHDPE);
	TapaDer->SetFillStyle(1001);
	
    TapaIzq->SetVisibility(act_trans);
	TapaIzq->SetTransparency(0); 
	TapaIzq->SetLineColor(color_BHDPE);
	TapaIzq->SetFillColor(color_BHDPE);
	TapaIzq->SetFillStyle(1001);
	
    ExtCore->SetVisibility(act_trans);
	ExtCore->SetTransparency(0); 
	ExtCore->SetLineColor(color_BHDPE);
	ExtCore->SetFillColor(color_BHDPE);
	ExtCore->SetFillStyle(1001);

	AirCore->SetVisibility(0);

	GraphiteCore->SetVisibility(act_trans);
	GraphiteCore->SetTransparency(transparency); 
	GraphiteCore->SetLineColor(color_graphite);
	GraphiteCore->SetFillColor(color_graphite);
	GraphiteCore->SetFillStyle(1001);

	CilindroSpace_InMod->SetVisibility(act_trans);
	CilindroSpace_InMod->SetTransparency(transparency); 
	CilindroSpace_InMod->SetLineColor(kCyan-10);
	CilindroSpace_InMod->SetFillColor(kCyan-10);
	CilindroSpace_InMod->SetFillStyle(1001);

	DetectorAV->SetVisibility(act_trans);
	DetectorAV->SetTransparency(transparency); 
	DetectorAV->SetLineColor(kViolet);


}


  // Crear canvas y viewer
  TCanvas *c1 = new TCanvas("c1", "GDML Geometry", 1200, 1000);
  c1->cd();

  // Draw the top volume
  gGeoManager->GetTopVolume()->SetVisContainers(kTRUE);
  gGeoManager->GetTopVolume()->SetVisibility(kFALSE);

  gGeoManager->GetTopVolume()->Draw("ogl");
  // Esperar para asegurar renderizado antes de guardar
  gSystem->ProcessEvents();


	// 2. Grab the embedded GL viewer that lives inside the pad
TGLViewer *v = static_cast<TGLViewer*>(gPad->GetViewer3D());
if (!v) return;                   // safety check

// ------------------------------------------------------------------
//  QUICK WAY (pre-defined views)
// ------------------------------------------------------------------
// Choose one of the built-in cameras and make it current:
v->SetCurrentCamera(TGLViewer::kCameraPerspYOZ);   // XOZ perspective
//            kCameraPerspYOZ, kCameraPerspXOY,
//            kCameraOrthoXOY, kCameraOrthoXOZ, …  see enum list :contentReference[oaicite:0]{index=0}

v->ResetCurrentCamera();          // centres and zooms so everything is visible
v->RequestDraw();                 // or gPad->Modified(); gPad->Update();


// ------------------------------------------------------------------
//  FULL CONTROL (field-of-view, distance, rotations …)
// ------------------------------------------------------------------
// Double_t center[3] = {-1.522449,0,-3.623747};     // point the camera looks at (world coordinates)
Double_t center[3] = {0,0,0};     // point the camera looks at (world coordinates)
Double_t fov     = 30.;           // field-of-view in degrees
Double_t dolly   = 1.;          // distance from center (units = your geometry)
// Double_t hRot    = TMath::DegToRad()*45.;  // horizontal rotation  (azimuth)

//Vis 1 (se ve completo el productor)
// Double_t hRot    = -TMath::DegToRad()*30.;  // horizontal rotation  (azimuth)
// Double_t vRot    = TMath::DegToRad()*45.;  // vertical   rotation  (elevation)

//Vis 2 (se ve completo el productor)
Double_t hRot    = -TMath::DegToRad()*17.;  // horizontal rotation  (azimuth)
Double_t vRot    = TMath::DegToRad()*60.;  // vertical   rotation  (elevation)

v->SetPerspectiveCamera(TGLViewer::kCameraPerspYOZ,fov, dolly, center, hRot, vRot); 
v->RequestDraw();                 // redraw with the new camera

  
  //gGeoManager->Export("/home/flopez/LIN/TESIS_DOC/Analysis/geant4_to_root/root_files/12_MiniMonitor.root");

  // Exportar como PDF
  // gPad->Print("myGeom.pdf");
  // c1->SaveAs("geometry_view.pdf");
}
