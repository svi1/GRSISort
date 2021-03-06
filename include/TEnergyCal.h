#ifndef TENERGYCAL_H__
#define TENERGYCAL_H__

#include "TCal.h"
#include "TPeak.h"
#include "TSpectrum.h"

class TEnergyCal : public TCal {
 public: 
   TEnergyCal();
   TEnergyCal(const char* name, const char* title) : TCal(name,title){}
   ~TEnergyCal(); 

 public:
   std::vector<Double_t> GetParameters() const;
   Double_t GetParameter(Int_t parameter) const;
   void WriteToChannel() const;

   void AddPoint(Double_t measured, Double_t accepted,Double_t measured_uncertainty = 0.0, Double_t accepted_uncertainty = 0.0);
   Bool_t SetPoint(Int_t idx, Double_t measured);
   Bool_t SetPoint(Int_t idx, TPeak* peak);
   Bool_t SetPointError(Int_t idx, Double_t measured_uncertainty);

   void SetNucleus(TNucleus *nuc,Option_t* opt = "");

   void Clear(Option_t *opt = "");
   void Print(Option_t *opt = "") const;
   void SetDefaultTitles();
 //  void Draw(Option_t *opt = "ap"){Graph()->Draw(opt);}

   Bool_t IsGroupable() const {return true;}

 private:
   
   ClassDef(TEnergyCal,1); //Class used for Energy Calibrations

};

#endif
