#include <iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<stdio.h>
#include<sstream>
#include <typeinfo>
using namespace std;




int displayHelp(){
	cout<<"=============================================================="<<endl;
	cout<<"*                         HELP MENU                           *"<<endl;
	cout<<"=============================================================="<<endl;
	cout<<"add <Location>:                           :Add new location"<<endl;
	cout<<"delete <Location>:                        :Delete an existing location"<<endl;
	cout<<"record <Location> <disease> <cases>:      :Record a disease and it's cases'"<<endl;
	cout<<"list locations:                           :list all existing locations"<<endl;
	cout<<"list diseases:                            :list exisitng diseases in locations"<<endl;
	cout<<"where <disease>:                          :find where disease exists"<<endl;
	cout<<"cases <location><disease>:                :find cases of a disease in a location"<<endl;
	cout<<"cases <disease>:                          :find total cases of a given disease"<<endl;
	cout<<"help:                                     :prints user manual"<<endl;
	cout<<"Exit:                                     :Exit the program"<<endl;	
}

size_t getWhiteSpacePos(string input){
	return input.find(' ');
}

bool locationExists(string location){
	ifstream locationsFile("locations.txt");
	string line, lines;
	
	while(getline(locationsFile, line)){
		
		if(line==location){
			locationsFile.close();
			return true;
		}
	}
	locationsFile.close();
	return false;
	
		
	}

int main(){
	string input;
	
	cout<<" ================================================================================ "<<endl;
	cout<<"*                 Welcome to disease Cases reporting system                          *"<<endl;
	cout<<"*                 *****************************************                          *"<<endl;
	cout<<"*                                                                                    *"<<endl;
	cout<<"*               It is developed by INEZA Ange Michaella as a practical               *"<<endl;
	cout<<"*                  Evaluation for the end of year3                                   *"<<endl;
	cout<<"                =================================================                     "<<endl;
	cout<<"                =================================================                     "<<endl;
	cout<<"                =================================================                     "<<endl;
	cout<<" Starting time:Thu April 5 \n Need help? type help then press enter key \n            "<<endl;
	while(true){
		cout<<"Console>";
		getline(cin, input);
		if(input=="Exit"){
			cout<<"------------Exiting program--------"<<endl;
		     break;
		}
		if(input=="help"){
			displayHelp();
		}
		else if(input.substr(0,3)=="add"){
			size_t pos=getWhiteSpacePos(input);
			string location=input.substr(pos+1);
			transform(location.begin(), location.end(), location.begin(), ::toupper);
	
			if(locationExists(location)){
			cout<<"Location already exists!!"<<endl;
			}
			else{
			ofstream locationsFile("locations.txt", ios_base::app);
			locationsFile << location << endl;
			locationsFile.close();
			cout<<location << " successfully added"<<endl;	
			}
			
		}
		else if(input.substr(0,6)=="delete"){
			size_t pos=getWhiteSpacePos(input);
			string location=input.substr(pos+1);
			ifstream locationsFile("locations.txt");
			string line;
			ofstream tempFile("temp.txt", ios_base::app);
			transform(location.begin(), location.end(), location.begin(), ::toupper);
			if(locationExists(location)){
			while(getline(locationsFile, line))	{
				if(!(line==location)){
					tempFile << line << endl;
				}
			
				
			}
			locationsFile.close();
			tempFile.close();
			remove("locations.txt");
			rename("temp.txt", "locations.txt");
			cout<<"Location deleted"<<endl;
			}
			else{
				cout<<"Location doesn't exist"<<endl;
			}
			
		}
		else if(input=="list locations"){
			ifstream locationsFile("locations.txt");
			string line;
			while(getline(locationsFile, line)){
				cout<<line<<endl;
			}
		}
		else if(input.substr(0,6)=="record"){
			
			string command,location, disease;
			int cases;
			stringstream ss(input);
			ss>>command>>location>>disease>>cases;
			transform(location.begin(), location.end(), location.begin(), ::toupper);
			if(locationExists(location)){
				ofstream recordsFile("records.txt",ios_base::app);
				recordsFile<<location<<" "<<disease<<" "<<cases<<endl;
				cout<<"record addedd"<<endl;
			}
			else{
				cout<<"Location doesn't exist"<<endl;
			}
		}
		else if(input=="list diseases"){
			string location, disease, cases, line;
			ifstream recordsFile("records.txt");
			while(getline(recordsFile, line)){
				
				istringstream ss(line);
				ss>>location>>disease>>cases;
				transform(disease.begin(), disease.end(), disease.begin(), ::toupper);
				cout<<disease<<endl;
				
				
			}
			recordsFile.close();
		
	}
	else if(input.substr(0,5)=="where"){
		string command, disease, line, diseaseLine, location,cases;
		istringstream ss(input);
		ss>>command>>disease;
		ifstream recordsFile("records.txt");
		while(getline(recordsFile, line)){
			istringstream sc(line);
			sc>>location>>diseaseLine>>cases;
			if(disease==diseaseLine){
				cout<<location<<endl;
			}
			
		}
		
		
		
		recordsFile.close();
	}
	else if(input.substr(0,5)=="cases"){
		string command,first,second, line,location,disease;
		int cases;
		int totalCases=0;
		istringstream sr(input);
		sr>>command>>first>>second;
		if(locationExists(first)){
			transform(first.begin(), first.end(), first.begin(),::toupper);
		  	ifstream recordsFile("records.txt");
		  	while(getline(recordsFile, line)){
		  		istringstream rc(line);
		  		rc>>location>>disease>>cases;
		  		if((first==location)&&(disease==second)){
		  			cout<<cases<<endl;
				  }
			  }
			  recordsFile.close();
			  
			  
		}
		else{
			ifstream recordsFile("records.txt");
			while(getline(recordsFile, line)){
				istringstream sz(line);
				sz>>location>>disease>>cases;
				if(first==disease){
					totalCases+=cases;
				}
			}
			cout<<totalCases<<endl;
			recordsFile.close();
		}
	}
	
	
}
}
