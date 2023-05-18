#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <algorithm>
#include <iterator>
#include<sstream>
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


int main(){
	string input,location;
	
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
	
	else if(input=="help"){
		displayHelp();
	}
	else if(input.substr(0, 3) == "add") {
		
        size_t pos = input.find(' '); // Find position of first space
        if (pos !=string::npos  && input.substr(0, pos) == "add") {
        string location = input.substr(pos+1);
        transform(location.begin(), location.end(), location.begin(), ::toupper);
        ofstream outfile("location.csv", ios_base::app);
        outfile << location <<endl;
        outfile.close();
        cout << "Location added: " << location <<endl;
           }
           else{
           	cout<<"Error occured while adding location"<<endl;
		   }

    }else if (input.substr(0, 4) == "list") {
    	size_t pos=input.find(' ');
//    	if (pos !=string::npos && input.substr(0, pos) == "list"){
    		if(input.substr(pos+1)=="locations"){
    	
            ifstream infile("location.csv");
            string line;
            vector<string> locations;
            while (getline(infile, line)) {
                locations.push_back(line);
                }
                infile.close();
                sort(locations.begin(),locations.end());
                vector<string>::iterator i;
                for (i = locations.begin(); i  != locations.end(); ++i) {
                 cout << *i <<endl;
        }
			}
			else if(input.substr(pos+1)=="diseases"){

				ifstream infile("records.csv");
				string line;
				vector<string> diseases;
				while(getline(infile,line)){

					istringstream iss(line);
					string location, disease, num_of_cases;
					getline(iss, location,',');
					getline(iss, disease,',');
					getline(iss, num_of_cases,',');
			
					 transform(disease.begin(),disease.end(), disease.begin(), ::toupper);
                    diseases.push_back(disease);
					}

				
				infile.close();
				
				sort(diseases.begin(),diseases.end());
				      vector<string>::iterator i;
                for (i = diseases.begin(); i  != diseases.end(); ++i) {
                 cout << *i <<endl;
        }
			
			}

    	
    
            
    } 
else if (input.substr(0, 6) == "delete") {
    size_t pos = input.find(' ');
    if (pos != string::npos && input.substr(0, pos) == "delete") {
        string location = input.substr(pos + 1);
        transform(location.begin(), location.end(), location.begin(), ::toupper);

        // Delete location from "location.csv"
        ifstream locationFile("location.csv");
        vector<string> lines;
        string line;
        bool locationExists = false;

        while (getline(locationFile, line)) {
            if (line == location) {
                locationExists = true;
            } else {
                lines.push_back(line);
            }
        }

        locationFile.close();

        if (locationExists) {
            ofstream outfile("location.csv");
            copy(lines.begin(), lines.end(), ostream_iterator<string>(outfile, "\n"));
            outfile.close();
//            cout << "Location deleted: " << location << endl;

            // Delete records associated with the location from "records.csv"
            ifstream recordsFile("records.csv");
            lines.clear();
            bool recordExists = false;
            while (getline(recordsFile, line)) {
                stringstream ss(line);
                vector<string> record;
                string value;
//reads individual 
                while (getline(ss, value, ',')) {
                    record.push_back(value);
                }

                if (record.size() >= 1 && record[0] == location) {
                    recordExists = true;
                } else {
                    lines.push_back(line);
                }
            }

            recordsFile.close();

            if (recordExists) {
                ofstream recordsOutfile("records.csv");
                copy(lines.begin(), lines.end(), ostream_iterator<string>(recordsOutfile, "\n"));
                recordsOutfile.close();
                cout << "Records deleted for location: " << location << endl;
            }
        } else {
            cout << "Location not found: " << location << endl;
        }
    }
}
    else if (input.substr(0, 6) == "record") {
    	size_t pos=input.find(' ');
    	if (pos !=string::npos && input.substr(0, pos) == "record"){
    		
    		
    		
    		 string location, disease, cases;
        stringstream inputStream(input.substr(pos + 1));
				
        if (inputStream >> location >> disease >> cases) {
        	transform(location.begin(), location.end(), location.begin(), ::toupper);
            // Check if location exists in "location.csv"
            ifstream locationFile("location.csv");
            string line;
            bool locationExists = false;
            while (getline(locationFile, line)) {
                if (line == location) {
                    locationExists = true;
                    break;
                }
            }
            locationFile.close();

            if (locationExists) {
                // Add record to the CSV file
                ofstream outfile("records.csv", ios_base::app);
                outfile << location << "," << disease << "," << cases << endl;
                outfile.close();
                cout << "Record added for location: " << location << endl;
            } else {
                cout << "Location not found: " << location << endl;
            }
        } else {
            cout << "Invalid input format. Please provide location, disease, and cases." << endl;
        }
    }
        
    }


else if (input.substr(0, 5) == "where") {
	
    size_t pos=input.find(' ');
    string disease=input.substr(pos+1);
//    transform(disease.begin(), disease.end(), disease.begin(), ::toupper);

    ifstream infile("records.csv");
    string line;
    vector<string> locations;

    while (getline(infile, line)) {
        istringstream iss(line);
        string location, currentDisease, num_of_cases;
        getline(iss, location, ',');
        getline(iss, currentDisease, ',') >> num_of_cases;


            if (currentDisease == disease) {
                locations.push_back(location);
            }

    }
    infile.close();

    if (!locations.empty()) {
        sort(locations.begin(), locations.end());
       		      vector<string>::iterator i;
                for (i = locations.begin(); i  != locations.end(); ++i) {
                 cout << *i <<endl;
        }
    } else {
        cout << "No locations found with the disease: " << disease << endl;
    }
}
else if (input.substr(0, 5) == "cases") {
   size_t pos = input.find(' ');
    string remainingInput = input.substr(pos + 1);
    stringstream inputStream(remainingInput);
    string disease;
    getline(inputStream,disease,' ');
    
    ifstream infile("records.csv");
    string line;
    int totalCases = 0;

    while (getline(infile, line)) {
        istringstream iss(line);
        string recordLocation, currentDisease, num_of_cases;
        getline(iss, recordLocation, ',');
        getline(iss, currentDisease, ',');
        getline(iss, num_of_cases, ',');

    if (currentDisease == disease) {
    int casesCount = 0;
    std::stringstream converter(num_of_cases);
    converter >> casesCount;
    totalCases += casesCount;
    }
}


        infile.close();

    if (totalCases > 0) {

        cout << "Total cases of '" << disease << "' =" << totalCases << endl;
    } else {
        cout << "No cases found for disease: " << disease << endl;
    }



}

else{
	cout<<"Command doesn't exist"<<endl;
}
  	


	
}
	return 0;
}

	

	


