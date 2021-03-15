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
                             
                                                            

void fitTSLA(){
//empty arrays for data from file to go into
int array_size = 99999; //maximum array size, increase this for larger arrays (or smaller to save storage)
int count = 0;
string dates[array_size];
double value[array_size];
int volume[array_size];
//asks user for input of what <data>.txt which stock data they want to analyse. must be in the form date<string> value<double> volume<int> with no headers and seperated by spaces. will be usefull if i wanna use a smaller or larger data sample.

char * filename= "TSLAdata.txt";
ifstream opener;
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
double future_profit=0;
for(int i=0; i<count-1; i++){
if(value[i] > value[i+1]){
future_profit += value[i]-value[i+1];
                         }  }
double ideal = future_profit+buyandhold;
double idealp = 100*(ideal/value[0]); //the percentage gain/loss


//plotting the graph, long code as it is complicated to plot date on x-axis
auto ct = new TCanvas("ct","Time on axis",0,0,600,600);
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
TSLA->GetXaxis()->SetLabelSize(0.03);
TSLA->GetXaxis()->SetTitleSize(0.05);
TSLA->GetYaxis()->SetTitleSize(0.05);
TSLA->GetXaxis()->SetNdivisions(10); //more divisions and they start to overlap
TSLA->GetXaxis()->SetTimeFormat("%m/%Y");
TSLA->GetYaxis()->SetTitle("share price $");
TSLA->GetXaxis()->SetTitle("date");
TSLA->SetLineColor(3);
TSLA->Draw("LA");
//////fit /////
TF1 *plotFun=new TF1("plotFun","310.195+x*(-3.40719e-05)+(x^2)*(5.07842e-12)+(x^3)*(-3.35228E-19)+(x^4)*(1.1327e-26)+(x^5)*(-2.15174e-34)+(x^6)*(2.4006e-42)+(x^7)*(-1.5615e-50)+(x^8)*(5.47877e-59)+(x^9)*(-8.00695e-68)",Time[0],Time[1250]); //last 2 digits are the x range//
plotFun->GetXaxis()->SetTimeDisplay(1);
plotFun->GetXaxis()->SetTimeFormat("%m/%Y");
plotFun->Draw("same");











}
