//Created by Long Li, Duke University, Jan 12 2018

void trapezoidalfilter(TString filename, Long64_t entryNumber,Int_t peaktime=510,Int_t gaptime=510){
  TFile inputFile(filename,"READ");
  TTree* dataTree=(TTree*)inputFile.Get("sis3316tree");
  UShort_t channelID;
  UInt_t nSamples;
  UShort_t waveform[65536];

  dataTree->SetBranchAddress( "channelID", &channelID );
  dataTree->SetBranchAddress( "nSamples", &nSamples );
  dataTree->SetBranchAddress( "waveform", waveform );


  Long64_t nEntries = dataTree->GetEntries();
  cout<<"total entries:"<<nEntries<<endl;
  dataTree->GetEntry( entryNumber ); //finish reading one waveform

  Double_t tmpwf[nSamples],filteredwf[nSamples];
  for (int i=0;i<peaktime;i++) tmpwf[0]+=waveform[i];//calculate the first sample
  for (int i=1;i<nSamples-peaktime;i++) tmpwf[i]=tmpwf[i-1]-waveform[i-1]+waveform[i-1+peaktime];//calculate the rest samples
  for (int i=0;i<nSamples-2*peaktime-gaptime;i++) filteredwf[i]=tmpwf[i+peaktime+gaptime]-tmpwf[i];//calculate trapezoidalfilteredwaveform

    //begin to plot the rawwaveform and the filtered
    inputFile.Close();
    
    Int_t sampletime=4; //using 4ns per sample digitizer
    auto h1=new TH1D("hist","rawwaveform",nSamples,0,sampletime * nSamples);
    h1->SetXTitle("t/ns");
    h1->SetYTitle("ADC units");
    h1->SetOption("L");
    for(Int_t i=0; i<nSamples;i++)  h1->SetBinContent(i+1,waveform[i]);

    auto h2=new TH1D("hist","trapezoidalfilteredwaveform",nSamples-2*peaktime-gaptime,0,sampletime * (nSamples-2*peaktime-gaptime));
    h2->SetXTitle("t/ns");
    h2->SetYTitle("ADC units");
    h2->SetOption("L");
    for(Int_t i=0; i<nSamples-2*peaktime-gaptime;i++)  h2->SetBinContent(i+1,filteredwf[i]);

    auto c=new TCanvas("c","twowaveforms");
    c->Divide(1,2);
    c->cd(1);
    h1->Draw();
    c->cd(2);
    h2->Draw();
    c->Update();

}
