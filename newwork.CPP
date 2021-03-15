#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <time.h>
#include <ctime>
using namespace std;




// create a moving average function based on past data:
void MovingAverage(double arr[],int sizeofarr, int sizeofavrg, double* avg)
{ 
//  sizeofavrg is described best by ex. if sizeofavrg=3 this is a 
//	3 day moving average. 
//  avg is an array that will be overriten by the results.
//  to use this function the array pointer, the last argument must be declared 
//	and will be overwritten by the rsults from this func.
//  so this function provides an array of the moving average 
//	of the past sizeofavrg days.
 avg[0]=arr[0];   // First average is the number itself
 for (int i=1; i<sizeofarr; i++){
 	double avgs=0.0;                   // local for the summing
 	int sizloc=sizeofavrg;             // how many to average over
 	if( sizloc > (i+1) ) sizloc=i+1;   // for i-th, it is i+1 numbers
    for (int j=0;j<sizloc;j++) { 
          avgs = avgs + arr[i-j]; } 
    avg[i] = avgs/double(sizloc); }}    //works
// example of how to use, use in main() 
//double movingaverageresult[count-1];
//MovingAverage(value,count-1,10, movingaverageresult);
//for (int i=0;i<count-1;i++){
//cout<<movingaverageresult[i]<<"  "<<endl; }


//funtion simulating N trials of completely random trading
void randomsimulator(double arr[], int sizeofarr, int numtrials, double *randresults){    //arr is the array with values
for(int j=0; j<numtrials; j++){                                                   //randresults is where the results will be
    double randomcosts=0;
    double randomprofits=0;
    double currentvalue=arr[0];
    double totalcapital[sizeofarr];
    int token=0;  //token 0 means i have the stock, token 1 means i have no stock
    for(int i=0; i<sizeofarr; i++){
        int toss = rand()%2; //toss 0 is do nothing, toss=1 is sell/buy
        if(token==0){
        if(toss==0){                                              // exmaple of how to use
            currentvalue=arr[i];}                               // double whatever[100];
        if(toss==1){                                              // randomsimulator(value, count-1, 100, whatever);
            currentvalue=0;                                       // whatever has results
            randomprofits +=arr[i]; 
            token=1; } }
    else{
        currentvalue=0;
        if(toss==1){
            randomcosts -= arr[i];
            currentvalue = arr[i];  
            token=0; } }
    totalcapital[i]= randomcosts + randomprofits + currentvalue; }
    randresults[j] = totalcapital[sizeofarr-1]; }    }



// finding max of an array function.
double findmax(double in[], int sizeofin){
double max = 0;
for (int l =0; l < sizeofin; l++){
if (in[l] > max){
max = in[l];     }               }   
return max;                              } //works



// finding min of an array function.
double findmin(double in[], int sizeofin){
double min = 10000;
for (int l=0; l < sizeofin; l++){
if (in[l] < min){
min = in[l];    }               }    
return min;                              } //works



// finding the  % rate of change on previous day.
void rateofchange(double arr[],int sizeofarr, double* rate){
rate[0]=0;
for (int i=1; i<= sizeofarr; i++)              {
rate[i]= ((arr[i]-arr[i-1])/arr[i-1])*100;     }           } // works
// works the same as MovingAverage.



//finding location of a value in an array.
int locate(double arr[], int sizeofarr, double NumToLoc){
int loc =0;
for (int i=0; i<sizeofarr; i++){
if (arr[i] == NumToLoc){
loc =i;                }   }
return loc;                                             } //works

                                              

// finding the average of any array.
double FindAverage(double arr[], int sizeofarr){
double averg = 0;
for (int i=0; i<sizeofarr; i++){
averg =+ arr[i]/sizeofarr;     }
return averg;                                } //works



///////
// finding the contribution of the best N days for stock growth.
double GrowthOfNBestDays(double arr[], int sizeoffarr, int Ndays){
if (sizeoffarr < Ndays){     // error if given array < Ndays
printf("invalid input of GrowthOfNDays function");
                       }
double holderarr[Ndays];
int loc = 0;
for (int i =0; i<Ndays; i++){
holderarr[i]=i;             } //just fills the array initially
for (int i =Ndays; i<sizeoffarr; i++){
if (arr[i] > findmin(holderarr, Ndays)){ 
int index = locate(holderarr, Ndays, findmin(holderarr, Ndays));
holderarr[index] = arr[i];           } }
double value=0;
for (int i =0; i<Ndays; i++){ 
value += holderarr[i];   }
return value;                                                    }  //works, needs findmin and locate functions.
                             
                                                            

void newwork(){
//empty arrays for data from file to go into
int array_size = 99999; //maximum array size, increase this for larger arrays (or smaller to save storage)
int count = 0;
string dates[array_size];
double value[array_size];
int volume[array_size];
//asks user for input of what <data>.txt which stock data they want to analyse. must be in the form date<string> value<double> volume<int> with no headers and seperated by spaces. will be usefull if i wanna use a smaller or larger data sample.
cout <<"enter the name of the <data>.txt file you want to analyse:"<< endl;
char filename[50];
ifstream opener;
cin.getline(filename,50);
opener.open(filename);
if(!opener.is_open()){
cout << "file not found" <<endl;
exit(EXIT_FAILURE);  }
cout <<filename<<" found"<<endl;
while(opener >> dates[count] >> value[count] >> volume[count]){
count++;                                                      } //takes data from file, sorts and places it in allocated array.
printf("\n");
//comparing profits of a "buy and hold" strategy vs being able to tell the future (accurately predict the market)
double buyandhold = value[count-1]-value[0];
double buyandholdp = 100*(buyandhold/value[0]); //the percentage gain/loss
cout <<"buying 1 share on "<<dates[0]<<" and selling on "<<dates[count-1]<< " generates profit of $"<< buyandhold <<" or "<< buyandholdp<< "%"<<endl;
double future_profit=0;
for(int i=0; i<count-1; i++){
if(value[i] > value[i+1]){
future_profit += value[i]-value[i+1];
                         }  }
double ideal = future_profit+buyandhold;
double idealp = 100*(ideal/value[0]); //the percentage gain/loss
cout<<"\n\naccurately predicting the market over the same period of time, makes a profit off $"<< ideal <<" or "<<idealp<<"%"<<  endl; //prints results of method #2.



//plotting the graph, long code as it is complicated to plot date on x-axis
auto ct = new TCanvas("ct","Time on axis",0,0,600,600);
ct->Divide(1,3);//splits the canvas into 3
ct->cd(1);
gStyle->SetTitleH(0.08);
TTimeStamp da1(2015,05,20,9,30,00,0,kTRUE); //SM opens at 9:30 am
TTimeStamp da2(2020,05,06,9,30,00,0,kTRUE);
double timestart= da1.GetSec();
double timefinish= da2.GetSec();
gStyle->SetTimeOffset(timestart);
double timeincrement= (timefinish-timestart)/(count-2);
double Time[count-1];
for (int i=0;i<count; i++) {
Time[i]= i * timeincrement;}
TGraph * TSLA = new TGraph (count-1,Time, value);
TSLA->SetTitle("TSLA stock price");
TSLA->GetXaxis()->SetTimeDisplay(1);
TSLA->GetXaxis()->SetLabelSize(0.045);
TSLA->GetXaxis()->SetTitleSize(0.05);
TSLA->GetYaxis()->SetTitleSize(0.05);
TSLA->GetXaxis()->SetNdivisions(15); //more divisions and they start to overlap
TSLA->GetXaxis()->SetTimeFormat("%m/%Y");
TSLA->GetYaxis()->SetTitle("share price $");
TSLA->GetXaxis()->SetTitle("date");
TSLA->SetLineColor(3);
TSLA->Draw("LA");
// now draw the 1 month moving average.
double movingaverageresult[count-1];
MovingAverage(value,count-1,20, movingaverageresult);
TGraph * MOVIN = new TGraph (count-1, Time, movingaverageresult);
MOVIN->SetTitle("TSLA data");
MOVIN->GetXaxis()->SetTimeDisplay(1);
MOVIN->GetXaxis()->SetLabelSize(0.045);
MOVIN->GetXaxis()->SetTitleSize(0.05);
MOVIN->GetYaxis()->SetTitleSize(0.05);
MOVIN->GetXaxis()->SetNdivisions(15); //more divisions and they start to overlap
MOVIN->GetXaxis()->SetTimeFormat("%m/%Y");
MOVIN->GetYaxis()->SetTitle("share price $");
MOVIN->GetXaxis()->SetTitle("date");
MOVIN->Draw("same");
auto legend = new TLegend(0.1,0.7,0.48,0.9);
legend->AddEntry("MOVIN","1 month moving average", "l");
TLegendEntry *TSLAL= legend->AddEntry("TSLA", "tesla stock price", "l");
TSLAL->SetLineColor(3);
legend->Draw();
//finally such a hassel



//////// monthly moving average of % rate of growth day to day 
ct->cd(2);
double rate[count-1];
rateofchange(value,count-1, rate);
double movingrate[count-1];
MovingAverage(rate,count-1,21,movingrate);
//want the graph axis to look the same as the one above
gStyle->SetTimeOffset(timestart);
TGraph * RATE = new TGraph (count-1,Time, movingrate);
RATE->SetTitle("Moving 1 month average of daily percentage change in TSLA price");
RATE->GetXaxis()->SetTimeDisplay(1);
RATE->GetXaxis()->SetLabelSize(0.045);
RATE->GetXaxis()->SetTitleSize(0.05);
RATE->GetYaxis()->SetTitleSize(0.05);
RATE->GetXaxis()->SetNdivisions(15);
RATE->GetXaxis()->SetTimeFormat("%m/%Y");
RATE->GetYaxis()->SetTitle("percentage daily change");
RATE->GetXaxis()->SetTitle("date");
RATE->Draw("ap");


double dailyavrgrate = FindAverage(rate,count-1);


////////// effect on trading volume on stock price.
ct->cd(3);
gPad->SetLogy();
double vol[count-1];        //need as double to be able to plot.
for (int i=0; i<count; i++){
vol[i]=volume[i];          }
TGraph * volrate = new TGraph(count-1, rate, vol);
volrate->SetTitle("Trading volume effect on price change ");
volrate->GetXaxis()->SetLabelSize(0.045);
volrate->GetXaxis()->SetTitleSize(0.05);
volrate->GetXaxis()->SetTitle("rate of change [%]");
volrate->GetYaxis()->SetTitle("trading volume");
volrate->GetYaxis()->SetLabelSize(0.045);
volrate->GetYaxis()->SetTitleSize(0.05);
volrate->SetMarkerSize(5);
volrate->Draw("AP");



/////// what would happen if the best trading days r missed.
//cout<< "testyield" <<endl;
//double valpercentsum = GrowthOfNBestDays(rate, count-1 ,1);
//cout << valpercentsum << "percent missed by missing the best 1 days"<< endl;





// simulating random trading strategy N (10000) times seeing how many times it beats the market, and mow many it doesnt.
int trialnumber=100000; //ONLY CHANGE THIS TO CHANGE EVERYTHING WITH THE NUMBER OF TRIALS OF THE RANDOM METHOD
double whatever[trialnumber];
randomsimulator(value, count-1, trialnumber, whatever);
int win=0;
int loss=0;
for(int i=0; i<trialnumber; i++){
    double statresult= whatever[i]-value[count-1];
    if(statresult>0){
        win +=1; }
    else{ loss +=1;}  }
//cout<< "out of "<<trialnumber<<" trials"<<endl;
//cout<< "number of win = "<< win <<endl;
//cout<< "number of losses ="<< loss<< endl;
//////plot starts here :) histogram with results.
auto ch = new TCanvas("ch","random distribution", 0, 0, 300, 300);
gStyle->SetTitleH(0.08);
TH1D *hist = new TH1D("random trading","results from 100000 runs of random trading;return on investment; counts", 100, -1200,1500);
for(int i=0; i<trialnumber; i++){
    hist->Fill(whatever[i]-value[0]);       }  //fills the histogram with values from whatever
double markerx[2] = {buyandhold, buyandhold};
double markery[2] = {0 , 20000};
TGraph *meanmarker = new TGraph(2,markerx,markery);
hist->Draw();
meanmarker->Draw("same");
auto legend2 = new TLegend(0.1,0.8,0.45,0.9);
legend2->AddEntry("meanmarker","result of doing nothing", "l");
legend2->Draw();






return 0;
}



















