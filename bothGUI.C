{   TString OurTString;
//this message just tests git commits, if you see it, i managed to make commit this change to github
// main frame
   TGMainFrame *OurFrame = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
   OurFrame->SetLayoutBroken(kTRUE);
//    embedded canvas
   TRootEmbeddedCanvas *OurCanvas = new TRootEmbeddedCanvas(0,OurFrame,624,425,kSunkenFrame);
   Int_t Cnum = OurCanvas->GetCanvasWindowId();
   TCanvas* Canv = new TCanvas("Canv", 10, 10, Cnum);
   OurCanvas->AdoptCanvas(Canv);
      OurFrame->AddFrame(OurCanvas);
//   Text Label defined
   TGLabel *OurLabel = new TGLabel(OurFrame,"OurLabel");      
   OurLabel->SetTextJustify(kTextLeft);
   OurLabel->SetText("Enter data Below");
      OurFrame->AddFrame(OurLabel);
//  Text entry defined   
   TGTextBuffer *Buf=new TGTextBuffer(228);
   TGTextEntry *OurText=new TGTextEntry(OurFrame,Buf,-1);
   OurText->SetAlignment(kTextLeft);
   OurText->SetText("Here ...");
      OurFrame->AddFrame(OurText);                                   
//        Buttons  defined  and placed 
   ReadButton = new TGTextButton(OurFrame, "Read data", "Do_Get_Text()");
       OurFrame->AddFrame(ReadButton);
   ExitButton = new TGTextButton(OurFrame, "EXIT", "Do_Exit()");
       OurFrame->AddFrame(ExitButton);
//   Housekeeping
   OurFrame->MapSubwindows();
                                    OurLabel->MoveResize  ( 24,453,260, 28);      
                                    OurText->MoveResize   ( 24,483,480, 28);
                                    OurCanvas->MoveResize ( 24, 16,704,425);
                                    ReadButton->MoveResize(544,446,184, 32);  
                                    ExitButton->MoveResize(544,483,184, 32);
   OurFrame->MapWindow();           OurFrame->Resize      (776,531);
//              Canvas - THIS IS AN EXAMPLE ONLY    
   Canv->cd();
   TTimeStamp da2(2020,05,06,9,30,00,0,kTRUE);
    TTimeStamp da1(2015,05,20,9,30,00,0,kTRUE);        double timefinish = da2.GetSec();
    double timestart = da1.GetSec();
	    double timeincrement=(timefinish-timestart)/1250;         double Time[1250];
    for(int i=0;i<1251;i++){Time[i]= i*timeincrement;} 
       TH1F * hist=new TH1F("waiting","Empty histogram; date; price", 100,Time[0],Time[1249]);
   	hist->GetXaxis()->SetTimeDisplay(1);
	hist->GetXaxis()->SetNdivisions(7);
	hist->Draw();
}  
void Do_Get_Text(){                //  For the Read Button
    OurTString=  OurText->GetText();
    Canv->cd();        ifstream opener;    opener.open(OurTString);
    if(!opener.is_open()){ hist->SetTitle("File not found"); 
        Canv->Update();  Canv->Modified();}
    else{
        opener.close();
    if(OurTString=="APPLdata.txt"){
    TF1 *APPL = new TF1("plotFun","129.461+x*(-1.27307e-06)+(x^2)*(5.68492e-14)+(x^3)*(-9.02653e-21)+(x^4)*(5.06863e-28)+(x^5)*(-1.28267e-35)+(x^6)*(1.74805e-43)+(x^7)*(-1.33266e-51)+(x^8)*(5.34718e-60)+(x^9)*(-8.78194e-69)",Time[0],Time[1249]);
	gStyle->SetTimeOffset(timestart);
	APPL->GetXaxis()->SetTimeDisplay(1);
	APPL->GetXaxis()->SetTimeFormat("%m/%Y");
	APPL->GetYaxis()->SetTitle("share price $");
	APPL->GetXaxis()->SetTitle("date");
    	APPL->Draw();
    	APPL->SetTitle(OurTString); 
	auto legend = new TLegend(0.1,0.7,0.48,0.9);
	TLegendEntry *APPLL= legend->AddEntry("APPL", "APPL stock best fit line", "l");
	APPLL->SetLineColor(2);
	legend->Draw();
	Canv->Update();  Canv->Modified();  }
 	if(OurTString=="TSLAdata.txt"){
TF1 *TSLA=new TF1("plotFun","310.195+x*(-3.40719e-05)+(x^2)*(5.07842e-12)+(x^3)*(-3.35228E-19)+(x^4)*(1.1327e-26)+(x^5)*(-2.15174e-34)+(x^6)*(2.4006e-42)+(x^7)*(-1.5615e-50)+(x^8)*(5.47877e-59)+(x^9)*(-8.00695e-68)",Time[0],Time[1249]);
	gStyle->SetTimeOffset(timestart);
	TSLA->GetXaxis()->SetTimeDisplay(1);
	TSLA->GetXaxis()->SetTimeFormat("%m/%Y");
	TSLA->GetYaxis()->SetTitle("share price $");
	TSLA->GetXaxis()->SetTitle("date");
	TSLA->SetLineColor(3);
    	TSLA->Draw();
    	TSLA->SetTitle(OurTString); 
	auto legend = new TLegend(0.1,0.7,0.48,0.9);
	TLegendEntry *TSLAL= legend->AddEntry("TSLA", "TSLA stock best fit line", "l");
	TSLAL->SetLineColor(3);
	legend->Draw();
	Canv->Update();  Canv->Modified();  }   
}   }
void Do_Exit(){                   //  For the Exit Button
    gROOT->ProcessLine(".q");
}
