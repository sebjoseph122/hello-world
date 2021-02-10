#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

ifstream inFile;
vector<string> files;

vector<string> intro();
void loading();
void Menu2();
void Menu1();
void display_help();
void summary();
void summary2();
void GapRegion();
void CodeRegion();
void BasePairRange();
void ManualInput();
void FileInput();

int main(){
	intro();
	loading();
	Menu1();
	
}

vector<string> intro(){
	string filenames;
	string object;
	cout << "DNA Sequence Database Software\n\nSpecify the name of the DNA sequence file names you would like to load. For multiple files, add a ',' between each file name.\n>";
	cin >> filenames;
	stringstream ss(filenames);
	while(getline(ss, object, ',')){
		files.push_back(object);
	}
	return files;
}
void loading(){
	
	for(int i=0; i<files.size(); i++){
		cout << "Loading " << files[i] << "...\n";
		inFile.open(files[i]);
		if(inFile.is_open()){
			cout << "Successful loading of the " << files[i] << endl; 
			inFile.close();
		}
		else{
			cout << "Invalid Files. Try again!!!" << endl;
			intro();
		}
		
	}
}
void Menu1(){
	char menu1_in;
	cout << "\nSelect one of the following options:\n" << endl;
	cout << "(S) Summary statistics of the DNA Database" << endl;
	for(int i=0; i<files.size(); i++){
		cout << "(" << i+1 << ") Analyse " << files[i] << endl; 
	}
	cout << "(Q) Quit\n>";
	cin >> menu1_in;
	int x = menu1_in - '0';
	if(menu1_in == 'S' || menu1_in == 's'){
		summary();
		Menu1();
	}
	else if(menu1_in == 'Q' || menu1_in == 'q'){
		cout << "Program ended." << endl;
		return;
	}
	else if(x<=files.size()){
		cout << files[x-1] << endl;
		inFile.open(files[x-1]);
		Menu2();
	}
	else{
		cout << menu1_in;
		cout << "Try Again!!!" << endl;
		Menu1();
	}
}
void Menu2(){
	char menu2_in;
	string temp, gid;
	cout << "\n(H) Help\n(S) Summary Statistics of the DNA Sequence\n(1) Analyse Gap Region\n(2) Analyse coded region\n(3) Analyse base pair range\n(4) Find DNA sequence by manual input\n(5) Find DNA sequence by file input\n(R) Return to the previous menu\n(Q) Quit\n>";
	cin >> menu2_in;
	switch(menu2_in){
		case 'H':
		case 'h':
			display_help();
			Menu2();
			break;
		case 'S':
		case 's':
			summary2();
			Menu2();
			break;
		case '1':
			GapRegion();
			Menu2();
			break;
		case '2':
			CodeRegion();
			Menu2();
			break;
		case '3':
			BasePairRange();
			Menu2();
			break;
		case '4':
			ManualInput();
			Menu2();
			break;
		case '5':
			FileInput();
			Menu2();
			break;
		case 'R':
		case 'r':
			Menu1();
			break;
		case 'Q':
		case 'q':
			return;
		default:
			cout << "Try again" << endl;
			Menu2();
	}
	}
	
void display_help(){
	cout << "Code\tBase Description" << endl;
	cout << "G\tGuanine" << endl;
	cout << "A\tAdenine" << endl;
	cout << "T\tThymine(Uracil in RNA)" << endl;
	cout << "C\tCytosine" << endl;
	cout << "R\tPurine(A or G)" << endl;
	cout << "Y\tPyrimidine (C or T or U)" << endl;
	cout << "M\tAmino (A or C)" << endl;
	cout << "K\tKetone (G or T)"<< endl;
	cout << "S\tStrong interaction (C or G)" << endl;
	cout << "W\tWeak interaction (A or T)" << endl;
	cout << "H\tNot-G (A or C or T) H follows G in the alphabet" << endl;
	cout << "B\tNot-A (C or G or T) B follows A in the alphabet" << endl;
	cout << "V\tNot-T (not-U) (A or C or G) V follows U in the alphabet" << endl;
	cout << "D\tNot-C (A or G or T) D follows C in the alphabet" << endl;
	cout << "N\tAny (A or C or G or T)" << endl;
}

void summary(){
	cout << "The DNA Sequence Database holds " << files.size() << " Sequences." << endl;
	cout << endl;
	for(int i = 0; i<files.size(); i++){
	string gid, waste, ref, name;
	string seq;
	inFile.open(files[i]);
	getline(inFile, waste, '|');
	getline(inFile, gid , '|');
	getline(inFile, waste, '|');
	getline(inFile, ref, '|');
	getline(inFile, waste, ' ');
	getline(inFile, name, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	cout << "Sequence " << i+1 << ":" << endl;
	cout << "Name:\t" << name << endl;
	cout << "GID:\t" << gid <<  endl;
	cout << "REF:\t" << ref << endl;
	cout << "# base pairs:\t" << seq.size() << endl;
	cout << endl;
	inFile.close();
	}
}

void summary2(){
	cout << "Sequence Identifiers:" << endl;
	string gid, waste, ref, name;
	string seq;
	int Gcount=0, Acount=0, Tcount=0, Ccount=0, Rcount=0, Ycount=0, Mcount=0, Kcount=0, Scount=0, Wcount=0, Hcount=0, Bcount=0, Vcount=0, Dcount=0, Ncount=0, unknown=0;
	int Nregions=0, Cregions=0;
	getline(inFile, waste, '|');
	getline(inFile, gid , '|');
	getline(inFile, waste, '|');
	getline(inFile, ref, '|');
	getline(inFile, waste, ' ');
	getline(inFile, name, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	cout << "Name:\t" << name << endl;
	cout << "GID:\t" << gid <<  endl;
	cout << "REF:\t" << ref << endl;
	inFile.clear();
	inFile.seekg(0, ios::beg);
	
	for(int i=0; i<seq.size()-1; i++){
		if(seq[i] == 'N' && seq[i+1] != 'N'){
		Nregions++;
		}
		else if(seq[i] != 'N' && seq [i+1] == 'N'){
		Cregions++;
		}
		else {
		Nregions=Nregions;
		Cregions=Cregions;
		}
	}
	if(seq[seq.size()-1]== 'N'){
		Nregions++;
	}
	else {
		Cregions++;
	}
	
	cout << "Region Characteristics:" << endl;
	cout << "# regions:\t" << Cregions+Nregions << endl;
	cout << "# N regions:\t" << Nregions << endl;
	cout << "# C regions:\t" << Cregions << endl;
	
	
	for(int i=0; i<seq.size(); i++){
		if (seq[i] == 'G'){
				Gcount++;
		}
		else if (seq[i] == 'A'){
			Acount++;
		}
		else if (seq[i] == 'T'){
			Tcount++;
		}
		else if (seq[i] == 'C'){
			Ccount++;
		}
		else if (seq[i] == 'R'){
			Rcount++;
		}
		else if (seq[i] == 'Y'){
			Ycount++;
		}
		else if (seq[i] == 'M'){
			Mcount++;
		}
		else if (seq[i] == 'K'){
			Kcount++;
		}
		else if (seq[i] == 'S'){
			Scount++;
		}
		else if (seq[i] == 'W'){
			Wcount++;
		}
		else if (seq[i] == 'H'){
			Hcount++;
		}
		else if (seq[i] == 'B'){
			Bcount++;
		}
		else if (seq[i] == 'V'){
			Vcount++;
		}
		else if (seq[i] == 'D'){
			Dcount++;
		}
		else if (seq[i] == 'N'){
			Ncount++;
		}
		else{
			unknown++;
		}
	}
	
	cout << "Base Pair Characteristics:" << endl;
	cout << "# base pairs:\t" << seq.size() << endl;
	cout << "G:\t" << Gcount << endl;
	cout << "A:\t" << Acount << endl;
	cout << "T:\t" << Tcount << endl;
	cout << "C:\t" << Ccount << endl;
	cout << "R:\t" << Rcount << endl;
	cout << "Y:\t" << Ycount << endl;
	cout << "M:\t" << Mcount << endl;
	cout << "K:\t" << Kcount << endl;
	cout << "S:\t" << Scount << endl;
	cout << "W:\t" << Wcount << endl;
	cout << "H:\t" << Hcount << endl;
	cout << "B:\t" << Bcount << endl;
	cout << "V:\t" << Vcount << endl;
	cout << "D:\t" << Dcount << endl;
	cout << "N:\t" << Ncount << endl;
	cout << "Unknown:\t" << unknown << endl;
}

void GapRegion(){
	string waste;
	string seq;
	int Nregions = 0;
	int gapregion;
	vector<int> gapregionstart;
	vector<int> gapregionend;
	
	getline(inFile, waste, '|');
	getline(inFile, waste , '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, ' ');
	getline(inFile, waste, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	
	for(int i=0; i<seq.size()-1; i++){
		if(seq[i] == 'N' && seq[i+1] != 'N'){
		Nregions++;
		}
		else{
			Nregions=Nregions;
		}
	}
	if(seq[seq.size()-1]== 'N'){
		Nregions++;
	}
	else {
	}
	if(seq[0] == 'N'){
		gapregionstart.push_back(0);
	}
	else{
	}
	for(int i=0; i<seq.size()-1; i++){
		if(seq[i] == 'N' && seq[i+1] !='N'){
			gapregionend.push_back(i+1);
		} 
		else if(seq[i] != 'N' && seq[i+1] == 'N'){
			gapregionstart.push_back(i+2);								//+2 because actually seq start position needed.
		}
		else{
		}
	}
	if(seq[seq.size()-1] == 'N'){
		gapregionend.push_back(seq.size());
	}
	
	cout << "Enter gap region number:\n>" << endl;
	cin >> gapregion;
	if (gapregion <= Nregions){
	cout << "Selected Sequence:" << endl;
	cout << "Base Pair range: (" << gapregionstart.at(gapregion-1) << "," << gapregionend.at(gapregion-1)<< ")" << endl;		
	cout << " Gap Region number: " << gapregion << endl;
	cout << endl;
	cout << "Sequence: " << endl;
	for (int i=gapregionstart.at(gapregion-1)-1; i<gapregionend.at(gapregion-1); i++){
		cout << seq[i];
	}
	cout << endl;
	}
	else{
		cout << "Invalid Gap Region" << endl;
		Menu2();
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
}

void CodeRegion(){
	string waste;
	string seq;
	int Cregions = 0;
	int coderegion;
	vector<int> coderegionstart;
	vector<int> coderegionend;
	
	getline(inFile, waste, '|');
	getline(inFile, waste , '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, ' ');
	getline(inFile, waste, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	for(int i=0; i<seq.size()-1; i++){
		if(seq[i] != 'N' && seq[i+1] == 'N'){
		Cregions++;
		}
		else{
			Cregions=Cregions;
		}
	}
	if(seq[seq.size()-1] != 'N'){
		Cregions++;
	}
	else{
	}
	if (seq[0]!= 'N'){
		coderegionstart.push_back(0);
	}
	else{
	}
	for(int i=0; i<seq.size()-1; i++){
		if(seq[i] == 'N' && seq[i+1] != 'N'){
			coderegionstart.push_back(i+2);
		}
		else if (seq[i] != 'N' && seq[i+1] == 'N'){
			coderegionend.push_back(i+1);
		}
		else{
		}
	}
	if(seq[seq.size()-1] != 'N'){
		coderegionend.push_back(seq.size());
	}
	
	cout << "Enter coded region number:\n>" << endl;
	cin >> coderegion;
	if(coderegion <= Cregions){
		cout << endl;
		cout << "Selected sequence:" << endl;
		cout << "Base pair range: (" << coderegionstart.at(coderegion-1) << "," << coderegionend.at(coderegion-1) << ")" << endl;
		cout << "Coded region number: " << coderegion << endl;
		cout << endl;
		cout << "Sequence:" << endl;
		for(int i=coderegionstart.at(coderegion-1)-1; i<coderegionend.at(coderegion-1); i++){
			cout << seq[i];
		}
		cout << endl;
	}
	else{
		cout << "Invalid coded region number" << endl;
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
	
}

void BasePairRange(){
	string waste;
	string seq;
	string basepairrange;
	string strstart, strend;
	int start, end;
	getline(inFile, waste, '|');
	getline(inFile, waste , '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, ' ');
	getline(inFile, waste, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	cout << "Enter a comma ',' separated base pair range:\n>" << endl;
	cin >> basepairrange;
	stringstream ss(basepairrange);
	getline(ss, strstart, ',');
	getline(ss, strend, '\n');
	stringstream sss(strstart);
	sss >> start;
	stringstream ssss(strend);
	ssss >> end;
	cout << "Selected sequence:" << endl;
	cout << "Base pair range: (" << start << "," << end << ")" << endl;
	cout << endl;
	cout << "Sequence:" << endl;
	for(int i=start-1; i<end; i++){
		cout << seq[i];
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
}

void ManualInput(){
	string waste;
	string seq, findseq;
	vector<size_t> findseqpos;
	getline(inFile, waste, '|');
	getline(inFile, waste , '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, ' ');
	getline(inFile, waste, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	cout << "Specify the DNA sequence nucleotides you would like to find:\n>";
	cin >> findseq;
	size_t found = seq.find(findseq);
	while( found != string::npos){
	findseqpos.push_back(found);
	
	found = seq.find(findseq, found + findseq.size());
	}
	for (int i = 0; i<findseqpos.size(); i++){
		cout << i+1 << ". Base pair range: (" << findseqpos.at(i)+1 << "," << findseqpos.at(i)+findseq.size() << ")" << endl;
		for(int j=findseqpos.at(i)-20; j<findseqpos.at(i); j++){
			cout << seq.at(j);
		}
		cout << endl;
		for(int j=findseqpos.at(i); j<=findseqpos.at(i)+findseq.size()-1; j++){
			cout << seq.at(j);
		}
		cout << endl;
		for(int j=findseqpos.at(i)+findseq.size(); j<findseqpos.at(i)+findseq.size()+20; j++){
			cout << seq.at(j);
		}
		cout << endl;
		cout << endl;
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
}

void FileInput(){
	string waste;
	string FN; //filename
	string seq, fileseq;
	vector<size_t> findfileseqpos;
	ifstream IF;
	getline(inFile, waste, '|');
	getline(inFile, waste , '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, '|');
	getline(inFile, waste, ' ');
	getline(inFile, waste, '\n');
	
	while(!inFile.eof()){
		getline(inFile, waste, '\n');
		seq += waste;
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
	cout << "Specify the DNA sequence file you would like to find:\n>";
	cin >> FN;
	cout << "Loading " << FN << "..." << endl;
	IF.open(FN);
	if(IF.is_open()){
		cout << "Successful loading of " << FN << endl;
		getline(IF, waste, '|');
		getline(IF, waste , '|');
		getline(IF, waste, '|');
		getline(IF, waste, '|');
		getline(IF, waste, ' ');
		getline(IF, waste, '\n');
		
		while(!IF.eof()){
			getline(IF, waste, '\n');
			fileseq += waste;
		}
		IF.close();
	}
	else {
		IF.close();
		cout << "Invalid Files. Try again!!!" << endl;
		FileInput();
	}
	size_t found = seq.find(fileseq);
	while(found != string::npos){
		findfileseqpos.push_back(found);
		found = seq.find(fileseq, found + fileseq.size());
	}
	cout << endl;
	cout << findfileseqpos.size() << " matching sequence(s) found." << endl;
	for(int i=0; i<findfileseqpos.size(); i++){
		cout << i+1 << ". Base pair range: (" << findfileseqpos.at(i)+1 << "," << findfileseqpos.at(i)+fileseq.size() << ")" << endl;
		for(int j=findfileseqpos.at(i)-20; j<findfileseqpos.at(i); j++){
			cout << seq.at(j);
		}
		cout << endl;
		for(int j=findfileseqpos.at(i); j<findfileseqpos.at(i)+fileseq.size(); j++){
			cout << seq.at(j);
		}
		cout << endl;
		for(int j=findfileseqpos.at(i)+fileseq.size(); j<findfileseqpos.at(i)+fileseq.size()+20; j++){
			cout << seq[j];
		}
		cout << endl;
	}
}

