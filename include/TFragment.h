#ifndef TFRAGMENT_H
#define TFRAGMENT_H

#include "Globals.h"

#include<vector>
//#include<stdint.h>
#include<time.h>

#include<Rtypes.h>
#include<TObject.h>

//#ifndef __CINT__
//#include "Globals.h"
//#endif

////////////////////////////////////////////////////////////////
//                                                            //
// TFragment                                                  //
//                                                            //
// This Class contains all of the information in an event     //
// fragment                                                   //
//                                                            //
////////////////////////////////////////////////////////////////

class TFragment : public TObject	{
public:
   TFragment(); 
   ~TFragment(); 

   time_t   MidasTimeStamp;       //->  Timestamp of the MIDAS event  
   Int_t    MidasId;              //->  MIDAS ID
   Long_t   TriggerId;            //->  MasterFilterID in Griffin DAQ  
   Int_t    FragmentId;           //->  Channel Trigger ID
   Int_t    TriggerBitPattern;	 //->  MasterFilterPattern in Griffin DAQ

   Int_t    NetworkPacketNumber;  //->  Network packet number

   Short_t ChannelNumber;         //->  Channel Number
   UInt_t ChannelAddress;         //->  Address of the channel
   std::vector<Int_t> Cfd;        //->  CFD of each pileup hit
   std::vector<Int_t> Led;        //->  LED of each pileup hit
   std::vector<Int_t> Charge;	    //->  The Integrated Charge 

   //unsigned long TimeStamp;     //->
   Int_t TimeStampLow;            //->  Timestamp low bits
   Int_t TimeStampHigh;           //->  Timestamp high bits
   Int_t TimeToTrig;              //->

	/// Added to combine Grif Fragment  ////

   UInt_t PPG;                    //-> Programmable pattern generator value
   UShort_t DeadTime;	          //-> Deadtime from trigger
   UShort_t NumberOfFilters;      //-> Number of filter patterns passed
   UShort_t NumberOfPileups;      //-> Number of piled up hits 1-3
   UShort_t DataType;             //-> 
   UShort_t DetectorType;         //-> Detector Type (PACES,HPGe, etc)
   UInt_t ChannelId;              //-> Threshold crossing counter for a channel

   std::vector<UShort_t>  KValue; //-> KValue for each pileup hit

   /// *****************************  ////

   std::vector<Short_t>  wavebuffer;//-> waveform words
  
   long GetTimeStamp(); //!
   const char *GetName(); //!
   double GetEnergy(); //!
   virtual void	Clear(Option_t *opt = ""); //!
   using TObject::Print; 
   virtual void Print(Option_t *opt = ""); //!
    
   ClassDef(TFragment,3);  // Event Fragments
};
#endif // TFRAGMENT_H
