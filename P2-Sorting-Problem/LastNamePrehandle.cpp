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

int LastA[15400];

void inputRead(string fileName){
	
	ifstream input_File;
	string input_Data;

  	input_File.open (fileName);

    int i = 0;
	while (!input_File.eof())
	{
		getline(input_File, input_Data);
		
		//Pass each line of data to process
		
        //lastName.push_back(commandProcess(input_Data));
        LastA[stoi(input_Data)] = i;
        i++;
	}
	
  	input_File.close();

}


int main(){

    inputRead("Avalue.txt");

    
    for(int i; i < 15400; i++){
        cout<< LastA[i]<< ",";
    }
    cout<< LastA[8720]<< endl;
    cout<< LastA[5285]<< endl;
    cout<< LastA[7662]<< endl;
    return 0;
}