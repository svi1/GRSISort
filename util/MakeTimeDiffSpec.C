//g++ MakeTimeDiffSpec.C -I$GRSISYS/include -L$GRSISYS/libraries -lGRSIFormat `root-config --cflags --libs` -lTreePlayer -o MakeTimeDiffSpec





//Takes in a FargmentTree, makes CES time diff spectra
//
//
#include <utility>
#include <vector>
#include <cstdio>

#include "TTree.h"
#include "TTreeIndex.h"
#include "TVirtualIndex.h"
#include "TFile.h"
#include "TList.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

#include "TChannel.h"

#include "TFragment.h"

TList *MakeTimeDiffSpec(TTree *tree) {

   const size_t MEM_SIZE = (size_t)1024*(size_t)1024*(size_t)1024*(size_t)8; // 8 GB

   TList *list = new TList;
   
   TFragment *currentFrag = 0;
   //TFragment *oldFrag_beta   = new TFragment; bool first_beta_set  = false;
   //TFragment *oldFrag_gamma  = new TFragment; bool first_gamma_set = false;
   std::vector<std::pair<long,int> > oldBetaTimeStamp;
   std::vector<std::pair<long,int> > oldGammaTimeStamp;

   bool last_beta_filled = false;
   bool last_gamma_filled = false;

   //TChannel::ReadCalFromTree(tree);
   TChannel::ReadCalFile("/tig/grsmid01_data1/griffin/nbernier/FragmentTrees/allGRIFFINcal_1316.cal");

   //tree->SetBranchAddress("TFragment",&currentFrag);
   printf("Loading tree branches into mem..."); fflush(stdout);
   TBranch *branch = tree->GetBranch("TFragment");
   branch->SetAddress(&currentFrag);
   tree->LoadBaskets(MEM_SIZE);
   printf(" done!\n");

   printf("Tree Index not found, building index on %s/%s...",
          "TimeStampHigh","TimeStampLow");  fflush(stdout);
   tree->BuildIndex("TimeStampHigh","TimeStampLow");
   printf(" done!\n");


   TTreeIndex *index = (TTreeIndex*)tree->GetTreeIndex();
   Long64_t *indexvalues = index->GetIndex();
   int fEntries = index->GetN();


   TH1F *gg_diff    = new TH1F("gg_diff","gg_diff",12000,-6000,6000); list->Add(gg_diff);
   TH2F *promptEng  = new TH2F("promptEng","Prompt Gamma Rays",100,0,100,4000,0,4000); list->Add(promptEng);
   TH2F *coincEng   = new TH2F("coincEng","Coincident Gamma Rays",100,0,100,4000,0,4000); list->Add(coincEng);	

   TH2F *gg_adc     = new TH2F("gg_adc","Coincident Gamma Rays by adc number",
                               100,0,100,100,0,100);  list->Add(gg_adc);


   //TH2F *gg_diff_mod[4];
   //gg_diff_mod[0] = new TH2F("gg_diff_0","gg_diff_0",4,0,4,600,0,600); list->Add(gg_diff_mod[0]);
   //gg_diff_mod[1] = new TH2F("gg_diff_1","gg_diff_1",4,0,4,600,0,600); list->Add(gg_diff_mod[1]);
   //gg_diff_mod[2] = new TH2F("gg_diff_2","gg_diff_2",4,0,4,600,0,600); list->Add(gg_diff_mod[2]);
   //gg_diff_mod[3] = new TH2F("gg_diff_3","gg_diff_3",4,0,4,600,0,600); list->Add(gg_diff_mod[3]);

   //TH2F *gg_diff_ch[16];
   //gg_diff_ch[0] = new TH2F("gg_diff_ch_0","gg_diff_0",16,0,16,600,0,600); list->Add(gg_diff_ch[0]);
   //gg_diff_ch[1] = new TH2F("gg_diff_ch_1","gg_diff_1",16,0,16,600,0,600); list->Add(gg_diff_ch[1]);
   //gg_diff_ch[2] = new TH2F("gg_diff_ch_2","gg_diff_2",16,0,16,600,0,600); list->Add(gg_diff_ch[2]);
   //gg_diff_ch[3] = new TH2F("gg_diff_ch_3","gg_diff_3",16,0,16,600,0,600); list->Add(gg_diff_ch[3]);
   //gg_diff_ch[4] = new TH2F("gg_diff_ch_4","gg_diff_4",16,0,16,600,0,600); list->Add(gg_diff_ch[4]);
   //gg_diff_ch[5] = new TH2F("gg_diff_ch_5","gg_diff_5",16,0,16,600,0,600); list->Add(gg_diff_ch[5]);
   //gg_diff_ch[6] = new TH2F("gg_diff_ch_6","gg_diff_6",16,0,16,600,0,600); list->Add(gg_diff_ch[6]);
   //gg_diff_ch[7] = new TH2F("gg_diff_ch_7","gg_diff_7",16,0,16,600,0,600); list->Add(gg_diff_ch[7]);
   //gg_diff_ch[8] = new TH2F("gg_diff_ch_8","gg_diff_8",16,0,16,600,0,600); list->Add(gg_diff_ch[8]);
   //gg_diff_ch[9] = new TH2F("gg_diff_ch_9","gg_diff_9",16,0,16,600,0,600); list->Add(gg_diff_ch[9]);
   //gg_diff_ch[10] = new TH2F("gg_diff_ch_10","gg_diff_10",16,0,16,600,0,600); list->Add(gg_diff_ch[10]);
   //gg_diff_ch[11] = new TH2F("gg_diff_ch_11","gg_diff_11",16,0,16,600,0,600); list->Add(gg_diff_ch[11]);
   //gg_diff_ch[12] = new TH2F("gg_diff_ch_12","gg_diff_12",16,0,16,600,0,600); list->Add(gg_diff_ch[12]);
   //gg_diff_ch[13] = new TH2F("gg_diff_ch_13","gg_diff_13",16,0,16,600,0,600); list->Add(gg_diff_ch[13]);
   //gg_diff_ch[14] = new TH2F("gg_diff_ch_14","gg_diff_14",16,0,16,600,0,600); list->Add(gg_diff_ch[14]);
   //gg_diff_ch[15] = new TH2F("gg_diff_ch_15","gg_diff_15",16,0,16,600,0,600); list->Add(gg_diff_ch[15]);

   //TH2F *gg_diff_mat_same16 = new TH2F("gg_diff_mat_same16","gg_diff_mat_same16",10,0,10,600,0,600); list->Add(gg_diff_mat_same16);
   //TH2F *gg_diff_mat_diff16 = new TH2F("gg_diff_mat_diff16","gg_diff_mat_diff16",10,0,10,600,0,600); list->Add(gg_diff_mat_diff16);
   //TH2F *gg_diff_mat_diffrev16 = new TH2F("gg_diff_mat_diffrev16","gg_diff_mat_diffrev16",10,0,10,600,0,600); list->Add(gg_diff_mat_diffrev16);

   //TH2F *gg_diff_mat_same16_ch = new TH2F("gg_diff_mat_same16_ch","gg_diff_mat_same16_ch",65,0,65,600,0,600); list->Add(gg_diff_mat_same16_ch);
   //TH2F *gg_diff_mat_diff16_ch = new TH2F("gg_diff_mat_diff16_ch","gg_diff_mat_diff16_ch",65,0,65,600,0,600); list->Add(gg_diff_mat_diff16_ch);
   //TH2F *gg_diff_mat_diffrev16_ch = new TH2F("gg_diff_mat_diffrev16_ch","gg_diff_mat_diffrev16_ch",65,0,65,600,0,600); list->Add(gg_diff_mat_diffrev16_ch);

   TH1F *gb_diff = new TH1F("gb_diff","gb_diff",12000,-6000,6000); list->Add(gb_diff);
   TH1F *bg_diff = new TH1F("bg_diff","bg_diff",12000,-6000,6000); list->Add(bg_diff);
   TH1F *bb_diff = new TH1F("bb_diff","bb_diff",12000,-6000,6000); list->Add(bb_diff);

   TH1F* bg_coinc_gE = new TH1F("bg_coinc_gE","bg_coinc_gE",16000,0,16000); list->Add(bg_coinc_gE);
  
 //  TH2F* gg_coinc_gE = new TH1F("gg_coinc","gg_coinc", 8000,0,8000,8000,0,8000); list->Add(gg_coinc);

   //TH2F *gg_diff_E1 = new TH2F("gg_diff_E1","gg time difference of card 3&1 vs energy of card 1",4000,0.,4000.,600,0.,600.); list->Add(gg_diff_E1);
   //TH2F *gg_diff_E3 = new TH2F("gg_diff_E3","gg time difference of card 3&1 vs energy of card 3",4000,0.,4000.,600,0.,600.); list->Add(gg_diff_E3);

   TH3F *bb_diff_Id = new TH3F("bb_diff_Id","bb_diff_Id",400,1200,1600,400,1200,1600,50,-25,25); list->Add(bb_diff_Id);
   TH2F *bb_diff_E1 = new TH2F("bb_diff_E1","bb_diff_E1",1200,-600,600,1000,0,50e3); list->Add(bb_diff_E1);
   TH2F *bb_diff_E2 = new TH2F("bb_diff_E2","bb_diff_E2",1200,-600,600,1000,0,50e3); list->Add(bb_diff_E2);

   TH2F *gb_diff_Id = new TH2F("gb_diff_Id","gb_diff_Id",2000,0,2000,2000,0,2000); list->Add(gb_diff_Id);
   TH2F *gb_diff_Eg = new TH2F("gb_diff_Eg","gb_diff_Eg",1200,-600,600,1000,0,50e3); list->Add(gb_diff_Eg);
   TH2F *gb_diff_Eb = new TH2F("gb_diff_Eb","gb_diff_Eb",1200,-600,600,1000,0,50e3); list->Add(gb_diff_Eb);

   TH2F *EbVsEg = new TH2F("EbVsEg","EbVsEg",1000,0,50e3,1000,0,50e3); list->Add(EbVsEg);

   int FragsIn = 0;

   tree->GetEntry(indexvalues[0]);
   FragsIn++;

   for(long x=1;x<fEntries;x++) {
      if(tree->GetEntry(indexvalues[x]) == -1 ) { //move current frag to the next (x'th) entry in the tree
         printf( "FIRE!!!" "\n");
         continue;
      } 
   
      TFragment myFrag  = *currentFrag;         //Set myfrag to be the x'th fragment before incrementing it.
      long time = (long)currentFrag->GetTimeStamp();  //Get the timestamp of the x'th fragment 
     
      long timelow  = time - 1000;
      long timehigh  = time + 1000; 
//        long timelow = time + 0;
//        long timehigh = time + 10000;   
      int time_low  = (int) (timelow & 0x0fffffff);
      int time_high = (int) (timelow >> 28); 


      //long start = indexvalues[index->FindValues(time_high,time_low)];////tree->GetEntryNumberWithBestIndex(time_high,time_low);
      
      //find the entry where the low part of the gate fits.
      long start = index->FindValues(time_high,time_low);////tree->GetEntryNumberWithBestIndex(time_high,time_low);

     
      time_low  = (int) (timehigh & 0x0fffffff);
      time_high = (int) (timehigh >> 28); 
    
      //long stop = indexvalues[index->FindValues(time_high,time_low)];////tree->GetEntryNumberWithBestIndex(time_high,time_low);
      
      //Find the entry where the high part of the gate fits
      long stop = index->FindValues(time_high,time_low);////tree->GetEntryNumberWithBestIndex(time_high,time_low);

      //printf("\nlooping over y = %ld - %ld\n",start,stop);
      //
      //printf("Multiplicity = %d\n",stop-start)
      for(long y=start;y<=stop;y++) {
         //If the index of the comapred fragment equals the index of the first fragment, do nothing
         if(y == x) {
            continue;
         }
         if(tree->GetEntry(indexvalues[y]) == -1 ) { //move currentfrag to the next fragment
            printf( "FIRE!!!" "\n");
            continue;
         } 
         //printf("myFrag.DetectorType = %i, currentFrag.DetectorType = %i",myFrag.DetectorType,currentFrag->DetectorType);
         if(myFrag.ChannelAddress == currentFrag->ChannelAddress) {
           continue;
         }

         std::string myFragName = myFrag.GetName();
         std::string currFragName = currentFrag->GetName();
           
         //if(myFrag.DetectorType == 0) {
         if(myFragName.compare(0,3,"GRG") == 0 && myFrag.DetectorType == 1) {
            if(currFragName.compare(0,3,"GRG") == 0 && myFrag.DetectorType == 1) {
              TFragment tempFrag=*currentFrag;
              gg_diff->Fill(myFrag.GetTimeStamp() - currentFrag->GetTimeStamp());
              gg_adc->Fill(currentFrag->ChannelNumber,myFrag.ChannelNumber);
		          promptEng->Fill(currentFrag->GetTimeStamp() - myFrag.GetTimeStamp() ,myFrag.GetEnergy());
		          coincEng->Fill(currentFrag->GetTimeStamp() - myFrag.GetTimeStamp() ,tempFrag.GetEnergy());
            } else if(!currFragName.compare(0,3,"SEP")) {
               gb_diff->Fill((long)myFrag.GetTimeStamp() - (long)currentFrag->GetTimeStamp());
               bg_coinc_gE->Fill(myFrag.GetEnergy());
            } else {
          
            }
         } else if(myFragName.compare(0,3,"SEP") == 0 && myFrag.DetectorType == 2) {
            if(currFragName.compare(0,3,"GRG") == 0 && myFrag.DetectorType == 1) {
               bg_diff->Fill((long)myFrag.GetTimeStamp() - (long)currentFrag->GetTimeStamp());
               bg_coinc_gE->Fill(currentFrag->GetEnergy());
            } else if(currFragName.compare(0,3,"SEP") == 0 && currentFrag->DetectorType == 2) {
               bb_diff->Fill(myFrag.GetTimeStamp() - currentFrag->GetTimeStamp());
               bb_diff_Id->Fill(myFrag.ChannelAddress, currentFrag->ChannelAddress, myFrag.GetTimeStamp() - currentFrag->GetTimeStamp());
               if(myFrag.ChannelAddress < currentFrag->ChannelAddress) {
                  bb_diff_E1->Fill(myFrag.GetTimeStamp() - currentFrag->GetTimeStamp(),myFrag.Charge[0]);
               } else if(myFrag.ChannelAddress > currentFrag->ChannelAddress) {
                  bb_diff_E2->Fill(myFrag.GetTimeStamp() - currentFrag->GetTimeStamp(),myFrag.Charge[0]);
               }
            } else {
               
            }
         }
      }

      if(x%1500==0)
         printf("\tOn fragment %i/%i               \r",x,fEntries);
  //    if(x>1000000)
  //       break;
   }
   printf("\n\n");
  
   return list;
}



#ifndef __CINT__ 

int main(int argc, char **argv) {
   
   if(argc!=2)  {
      printf("try again.\n");
      return 0;
   }
   TFile *f = new TFile(argv[1]);
   TTree *tree = (TTree*)f->Get("FragmentTree");

   TList *list = MakeTimeDiffSpec(tree);

   const char* name = f->GetName();

 //  TFile *outfile = new TFile(Form("mats_%s",name),"recreate");
   TFile *outfile = new TFile("junk.root","recreate");
   list->Write();

   return 0;

}

#endif






