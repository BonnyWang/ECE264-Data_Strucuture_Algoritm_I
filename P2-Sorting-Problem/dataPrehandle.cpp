#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

list<string> lastName;

string commandProcess(string data){
	
	string command; //hold each word 
	int position = 0;// first, second or third word


	// Seperate words from line
	for(auto c : data){
		if(c == ' '){
			position++;
		}else if (c != '\r'){ //a carriage return
			command = command + c;
		}
	}
    
    return command;
}

void inputRead(string fileName){
	
	ifstream input_File;
	string input_Data;

  	input_File.open (fileName);

	while (!input_File.eof())
	{
		getline(input_File, input_Data);
		
		//Pass each line of data to process
		
        lastName.push_back(commandProcess(input_Data));
	}
	
  	input_File.close();

}



void outputWrite(string fileName, list<string> output_Info){
	
	ofstream output_File;

	output_File.open(fileName);

	//Execute if open successfully
	while(output_File){
		for(auto line : output_Info ){
			unsigned long long int value;
			value = 1;
			int i;
			int j[] ={132,123,33,4,678,932,123,111,624,21,42,213,121};
			i = 0;
			for(char letter : line){
				value = value *(letter-'A'+1);
				i = i++;
				//cout<< (letter-'A'+1)*j[i]<<endl;
			}
			output_File <<value<< endl;
		}
		break;
	}

	output_File.close();
}

int main(){
    inputRead("lastNames.txt");

    lastName.sort();

    outputWrite("LN.txt",lastName);


    return 0;
}