#ifndef DESCANTHIT_H
#define DESCANTHIT_H

#include <cstdio>
#include <cmath>

#include "TFragment.h"
#include "TChannel.h"
#include "TCrystalHit.h"

#include "TVector3.h"

#include "TGRSIDetectorHit.h"

class TDescantHit : public TGRSIDetectorHit {
  public:
    TDescantHit();
    ~TDescantHit();

  private:
    UShort_t detector;
    UInt_t   address;
    Int_t    filter;
    Int_t    charge;
    Int_t    cfd;
    Int_t    psd;
    Double_t energy;
    Long_t   time;

    std::vector<Short_t> waveform; //

  public:
		/////////////////////////		/////////////////////////////////////
      inline void SetDetectorNumber(const int &x)  { detector = x; }   //!
      inline void SetAddress(const UInt_t &x)      { address  = x; }   //!
      inline void SetFilterPattern(const int &x)   { filter   = x; }   //! 
      inline void SetCharge(const int &x)          { charge   = x; }   //!
      inline void SetCfd(const int &x)             { cfd      = x; }   //!
      inline void SetPsd(const int &x)             { psd      = x; }   //!
      inline void SetEnergy(const Double_t &x)     { energy   = x; }   //!
      inline void SetTime(const Long_t &x)         { time     = x; }   //!
      inline void SetPosition(TVector3 x)          { position = x; }   //!

      inline void SetWaveform(std::vector<Short_t> x) {
         if(x.size() <= 8) {
            return;
         }
         size_t length = x.size() - (x.size()%8);
         waveform.resize(length-8);
         for(size_t i = 0; i < length; ++i) {
            // reorder so that samples 0-7 are: 7,6,1,0,3,2,5,4
            //                                  0,1,2,3,4,5,6,7
            // pairwise swap: 0->1,1->0 => i+1 (1,2) => i+1-(2*i%2) (1,0)
            // 67,01,32,45: shift all by +2, except for the last pair which need to be shifted by -6
            Int_t reordered = i-2;
            reordered = reordered+1-2*(reordered%2);
            if(reordered >= waveform.size()) {
               continue;
            }
            if(reordered%8 < 6) {
               //std::cout<<i<<" => "<<reordered+2<<std::endl;
               waveform[reordered+2] = x[i];
            } else {
               //std::cout<<i<<" => "<<reordered-6<<std::endl;
               waveform[reordered-6] = x[i];
            }
         }
      } //!

      /////////////////////////		/////////////////////////////////////
		inline UShort_t   GetDetectorNumber()     { return detector;   }  //!
      inline UInt_t     GetAddress()            { return address;    }  //!
      inline Int_t      GetFiterPatter()        { return filter;     }  //!
		inline Int_t      GetCharge()             { return charge;     }  //!
      inline Int_t      GetCfd()                { return cfd;        }  //!
      inline Int_t      GetPsd()                { return psd;        }  //!
      inline Double_t   GetEnergy()             { return energy;     }  //!
		inline Long_t     GetTime()               { return time;       }  //!

      inline std::vector<Short_t> GetWaveform() { return waveform; }  //!

      Int_t CalculateCfd(double attenuation, int delay, int halfsmoothingwindow, int interpolation_steps); //!
      Int_t CalculateCfdAndMonitor(double attenuation, int delay, int halfsmoothingwindow, int interpolation_steps, std::vector<Short_t> &monitor); //!
      std::vector<Short_t> CalculateCfdMonitor(double attenuation, int delay, int halfsmoothingwindow); //!
      std::vector<Short_t> CalculateSmoothedWaveform(unsigned int halfsmoothingwindow); //!
      std::vector<Int_t> CalculatePartialSum(); //!
      Int_t CalculatePsd(double fraction, int interpolation_steps); //!
      Int_t CalculatePsdAndPartialSums(double fraction, int interpolation_steps, std::vector<Int_t>& partialsums); //!

      bool   InFilter(Int_t);                                          //!

      static bool CompareEnergy(TDescantHit*,TDescantHit*);            //!
      void Add(TDescantHit*);                                          //!

      bool AnalyzeWaveform();                                          //!

	public:
		void Clear(Option_t *opt = "");		                    //!
		void Print(Option_t *opt = "");		                    //!

	ClassDef(TDescantHit,3)
};




#endif
