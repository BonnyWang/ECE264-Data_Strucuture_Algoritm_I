/*
Yue(Bonny) Wang
DSA Programming Assignment #1
Queue and Stack Implementation
2019/11
*/

#include <iostream>
#include <fstream>
#include <string> 
#include <sstream> 
#include <list>
#include <iterator> 
using namespace std;


//Base Class for Queue and Stack
template <typename Object>

class SimpleList{

private:

	class Node; //forward declearation
	int size;
	Node *head;
	Node *tail;
	string name;

	//Nested Class
	class Node { 
	public: 
    	Object data; 
   		Node *next; 
		
		//Constructor
		Node(const Object &d = Object{ }, Node *n = nullptr)
			:data{d}, next{n}{ }
	}; 

	//Initialize the Class
	void init(){
		size = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
	}

protected:

	void insertHead(Object newHead){
		Node *temp = new Node;
		temp->data = newHead;
		temp->next = head;
		head = temp;
		size++;

	}
	
	void insertTail(Object newTail){
		Node *temp = new Node;
		temp->data = newTail;

		//Three situation
		if(size == 0){
			head = temp;
			head->next = tail;
		}else if(size == 1){
			tail = temp;
			head->next = tail;
		}else{
			tail->next = temp;
			tail = temp;
		}	

		size++;
	}
	
	void removeHead(){
		Node *temp = new Node;
		temp = head;
		head = head->next;
		delete temp;
		size--;
	}

	string getHeadData(){
		string head_Data;

		// to convert the data into string
		stringstream converter;
		converter << head->data;
		head_Data = converter.str();

		return head_Data;
	}


public:

	void setName(string name){
		this->name = name;
	}

	string getName(){
		return name;
	}

	bool isEmpty(){
		if (size == 0){
			return true;
		}else{
			return false;
		}
	}

	//Constructor
	SimpleList(){
		init();
	}

	~SimpleList(){
		delete head;
		delete tail;
		//clear other stuff
	}

	//Abstract function for child Class
	virtual string pop() = 0;
	virtual void push(Object mobject) = 0;
};


//Extended child class Stack from SimpleList
template <typename Object>

class Stack : public SimpleList<Object>{

public:
	string pop(){
		string head_Data = this->getHeadData();
		this->removeHead();
		return head_Data;
	}

	void push(Object Top){
		this->insertHead(Top);
	}

	Stack(string name){
		this->setName(name);
	}

};

//Extended child class Queue from SimpleList
template <typename Object>

class Queue : public SimpleList<Object>{

public:
	string pop(){
		string head_Data = this->getHeadData();
		this->removeHead();
		return head_Data;
	}


	void push(Object End){
		this->insertTail(End);
	}

	Queue(string name){
		this->setName(name);
	}

};

//Global variables
list<string> output_Info; //Usd to store the output messages
list<SimpleList<int> *> listSLi; // all integer stacks and queues
list<SimpleList<double> *> listSLd; // all double stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues

//For generate Processing Command output txt
void process_Info(string command0, string name, string type = ""){

	string message;

	if(command0 == "pop"){
		message = "PROCESSING COMMAND: " + command0 +" "+ name;
	}else{
		message = "PROCESSING COMMAND: " + command0 +" "+ name +" "+ type;
	}
	output_Info.push_back(message);
}

//For generate error info, 0 for already have name, 1 for name no exist, 2 for list empty
void error_Info(int type){
	string message ;
	if(type == 0){
		message = "ERROR: This name already exists!";
	}
	if(type == 1){
		message = "ERROR: This name does not exist!";
	}
	if(type == 2){
		message = "ERROR: This list is empty!";
	}
	output_Info.push_back(message);
	
}

//For generate pop info message
void pop_Info(string data){
	string message = "Value popped: " + data;
	output_Info.push_back(message);
}


//Search if a stack or queue with certain name already exist
template <typename Object>

SimpleList<Object>* listSearch(list<SimpleList<Object>*> sList, string name){
	
	typename list<SimpleList<Object>*>::iterator it; 
	
    for(it = sList.begin(); it != sList.end(); it++){
		if((*it)->getName() == name){
			return *it;
		}
	}

	return nullptr;
}


//To execute the push command
template <typename Object>

void push_Process(list<SimpleList<Object>* > listSl, string command[], Object data){

	process_Info("push",command[1],command[2]);

	SimpleList<Object>* target = listSearch<Object>( listSl, command[1]);
	if( target != nullptr){

		//Check whether it is a stack or queue
		Stack<Object>* tempS = dynamic_cast<Stack<Object>*>(target);
		Queue<Object>* tempQ = dynamic_cast<Queue<Object>*>(target);

		if(tempS != nullptr){
			tempS->push(data);
		}
		if(tempQ != nullptr){
			tempQ->push(data);
		}	
	}else{
		error_Info(1); // No existing stack or queue
	}
}


//To execute the pop Process
template <typename Object>

void pop_Process(list<SimpleList<Object>* > listSl, string command[]){

	process_Info("pop",command[1]);

	SimpleList<Object>* target = listSearch<Object>(listSl, command[1]);

	if( target != nullptr){
		Stack<Object>* tempS = dynamic_cast<Stack<Object>*>(target);
		Queue<Object>* tempQ = dynamic_cast<Queue<Object>*>(target);

		//check if it is a stack or queue, casting successful or not
		if(tempS != nullptr){ 

			//check if empty list
			if(!tempS->isEmpty()){
				pop_Info( tempS->pop());
			}else{
				error_Info(2);// empty list error message
			}
		}

		if(tempQ != nullptr){
			if(!tempQ->isEmpty()){
				pop_Info(tempQ->pop());
			}else{
				error_Info(2);// empty list error message
			}
		}	
	}else{
		error_Info(1);// type 1 for name no exist error 
	}
}


//To execute the Create command
template <class dataType, class Object>

list<SimpleList<dataType>*> create_Process(list<SimpleList<dataType>* > listSl, string command[], string type){

	process_Info("create",command[1], type);

	if(listSearch<dataType>(listSl, command[1]) == nullptr){ 
		SimpleList<dataType> *pSLi;
		pSLi = new Object(command[1]);
		listSl.push_front(pSLi);
	}else{
		error_Info(0); //name already exist error message
	}

	return listSl;
}


//Big function to handle each line for data
void commandProcess(string data){
	
	string command[3]; //hold each word 
	int position = 0;// first, second or third word


	// Seperate words from line
	for(auto c : data){
		if(c == ' '){
			position++;
		}else if (c != '\r'){ //a carriage return
			command[position] = command[position] + c;
		}
	}

	//Determine the first command, second command , third command and sepreate cases
	if(command[0] == "create"){
		if(command[2] == "stack"){
			if(command[1].at(0) == 'i'){
				listSLi = create_Process<int, Stack<int>>(listSLi, command,"stack");
			}
			if(command[1].at(0) == 'd'){
				listSLd = create_Process<double, Stack<double>>(listSLd, command,"stack");
			}
			if(command[1].at(0) == 's'){
				listSLs = create_Process<string, Stack<string>>(listSLs, command,"stack");
			}
		}
		if(command[2] == "queue"){
			if(command[1].at(0) == 'i'){
				listSLi = create_Process<int, Queue<int>>(listSLi, command, "queue");
			}
			if(command[1].at(0) == 'd'){
				listSLd = create_Process<double, Queue<double>>(listSLd, command,"queue");
			}
			if(command[1].at(0) == 's'){
				listSLs = create_Process<string, Queue<string>>(listSLs, command,"queue");
			}
		}
	}

	if(command[0] == "pop"){
		if(command[1].at(0) == 'i' ){
			pop_Process<int>(listSLi,command);
		}
		if(command[1].at(0) == 'd' ){
			pop_Process<double>(listSLd,command);
		}
		if(command[1].at(0) == 's' ){
			pop_Process<string>(listSLs,command);
		}
	}

	if(command[0] == "push"){
		if(command[1].at(0) == 'i'){
			push_Process<int>(listSLi,command, stoi(command[2]));
		}
		if(command[1].at(0) == 'd'){
			push_Process<double>(listSLd,command, stod(command[2]));
		}
		if(command[1].at(0) == 's'){
			push_Process<string>(listSLs,command, command[2]);
		}
	}
}


//Function to read the input file
void inputRead(string fileName){
	
	ifstream input_File;
	string input_Data;

  	input_File.open (fileName);

	while (!input_File.eof())
	{
		getline(input_File, input_Data);
		
		//Pass each line of data to process
		commandProcess(input_Data);
	}
	
  	input_File.close();

}

//Output the string messages into the output file
void outputWrite(string fileName, list<string> output_Info){
	
	ofstream output_File;

	output_File.open(fileName);

	//Execute if open successfully
	while(output_File){
		for(auto line : output_Info ){
			output_File << line <<endl;
		}
		break;
	}

	output_File.close();
}


int main(){

	string ifile_Name;
	string ofile_Name;

	cout<<"Please type the file name you want to use: ";
	cin >> ifile_Name;
	cout<<"Please type the file name you want to output: ";
	cin >> ofile_Name;

	inputRead(ifile_Name);

	outputWrite(ofile_Name, output_Info);

  return 0;
}


