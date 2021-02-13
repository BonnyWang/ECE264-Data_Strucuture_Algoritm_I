// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

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

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
           << pData->firstName << " " 
           << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

/* DSA Project Two Sorting Problem
   Yue(Bonny) Wang
   2019 Fall
*/

vector<string> sortedLastName = {"ACOSTA","ADAMS","ADKINS","AGUILAR","AGUIRRE","ALEXANDER","ALLEN","ALVARADO","ALVAREZ","ANDERSON","ANDREWS","ARMSTRONG","ARNOLD","AUSTIN","AVILA","AYALA","BAILEY","BAKER","BALDWIN","BANKS","BARBER","BARKER","BARNES","BARNETT","BARRETT","BARTON","BATES","BECK","BECKER","BELL","BENNETT","BENSON","BERRY","BISHOP","BLACK","BLAIR","BLAKE","BOWEN","BOWMAN","BOYD","BRADLEY","BRADY","BREWER","BROOKS","BROWN","BRYANT","BURGESS","BURKE","BURNS","BURTON","BUSH","BUTLER","BYRD","CABRERA","CALDERON","CALDWELL","CAMACHO","CAMPBELL","CAMPOS","CANNON","CARDENAS","CARLSON","CARPENTER","CARR","CARRILLO","CARROLL","CARTER","CASTANEDA","CASTILLO","CASTRO","CERVANTES","CHAMBERS","CHAN","CHANDLER","CHANG","CHAPMAN","CHAVEZ","CHEN","CHRISTENSEN","CLARK","CLARKE","COHEN","COLE","COLEMAN","COLLINS","COLON","CONTRERAS","COOK","COOPER","CORTEZ","COX","CRAIG","CRAWFORD","CROSS","CRUZ","CUMMINGS","CUNNINGHAM","CURRY","CURTIS","DANIEL","DANIELS","DAVIDSON","DAVIS","DAWSON","DAY","DEAN","DELACRUZ","DELEON","DELGADO","DENNIS","DIAZ","DIXON","DOMINGUEZ","DOUGLAS","DOYLE","DUNCAN","DUNN","DURAN","EDWARDS","ELLIOTT","ELLIS","ERICKSON","ESPINOZA","ESTRADA","EVANS","FARMER","FERGUSON","FERNANDEZ","FIELDS","FIGUEROA","FISCHER","FISHER","FITZGERALD","FLEMING","FLETCHER","FLORES","FORD","FOSTER","FOWLER","FOX","FRANCIS","FRANCO","FRANK","FRANKLIN","FRAZIER","FREEMAN","FUENTES","FULLER","GALLAGHER","GALLEGOS","GARCIA","GARDNER","GARNER","GARRETT","GARZA","GEORGE","GIBSON","GILBERT","GILL","GOMEZ","GONZALES","GONZALEZ","GOODMAN","GOODWIN","GORDON","GRAHAM","GRANT","GRAVES","GRAY","GREEN","GREENE","GREGORY","GRIFFIN","GRIFFITH","GROSS","GUERRA","GUERRERO","GUTIERREZ","GUZMAN","HAIL","HALE","HALL","HAMILTON","HAMMOND","HAMPTON","HANSEN","HANSON","HARDY","HARMON","HARPER","HARRINGTON","HARRIS","HARRISON","HART","HARVEY","HAWKINS","HAYES","HAYNES","HENDERSON","HENRY","HERNANDEZ","HERRERA","HICKS","HIGGINS","HILL","HINES","HODGES","HOFFMAN","HOLLAND","HOLMES","HOLT","HOPKINS","HORTON","HOWARD","HOWELL","HUANG","HUBBARD","HUDSON","HUGHES","HUNT","HUNTER","INGRAM","JACKSON","JACOBS","JAMES","JENKINS","JENNINGS","JENSEN","JIMENEZ","JOHNSON","JOHNSTON","JONES","JORDAN","JOSEPH","JUAREZ","KELLER","KELLEY","KELLY","KENNEDY","KHAN","KIM","KING","KLEIN","KNIGHT","LAMBERT","LANE","LARA","LARSON","LAWRENCE","LAWSON","LE","LEE","LEON","LEONARD","LEWIS","LI","LIN","LITTLE","LIU","LOGAN","LONG","LOPEZ","LOVE","LOWE","LUCAS","LUNA","LYNCH","LYONS","MACK","MALDONADO","MALONE","MANN","MANNING","MARQUEZ","MARSHALL","MARTIN","MARTINEZ","MASON","MATTHEWS","MAXWELL","MAY","MCCARTHY","MCCOY","MCDANIEL","MCDONALD","MCGEE","MCKINNEY","MCLAUGHLIN","MEDINA","MEJIA","MENDEZ","MENDOZA","MEYER","MILES","MILLER","MILLS","MIRANDA","MITCHELL","MOLINA","MONTGOMERY","MONTOYA","MOORE","MORALES","MORAN","MORENO","MORGAN","MORRIS","MORRISON","MOSS","MULLINS","MUNOZ","MURPHY","MURRAY","MYERS","NAVARRO","NEAL","NELSON","NEWMAN","NEWTON","NGUYEN","NICHOLS","NORMAN","NORRIS","NUNEZ","OBRIEN","OCHOA","OCONNOR","OLIVER","OLSON","ORTEGA","ORTIZ","OWENS","PACHECO","PADILLA","PAGE","PALMER","PARK","PARKER","PARKS","PARSONS","PATEL","PATTERSON","PAUL","PAYNE","PEARSON","PENA","PEREZ","PERKINS","PERRY","PERSON","PETERS","PETERSON","PHAM","PHILLIPS","PIERCE","PORTER","POTTER","POWELL","POWERS","PRICE","QUINN","RAMIREZ","RAMOS","RAMSEY","RAY","REED","REESE","REEVES","REID","REYES","REYNOLDS","RHODES","RICE","RICHARDS","RICHARDSON","RILEY","RIOS","RIVAS","RIVERA","ROBBINS","ROBERTS","ROBERTSON","ROBINSON","ROBLES","RODGERS","RODRIGUEZ","ROGERS","ROJAS","ROMAN","ROMERO","ROSALES","ROSE","ROSS","ROWE","RUIZ","RUSSELL","RYAN","SALAZAR","SALINAS","SANCHEZ","SANDERS","SANDOVAL","SANTIAGO","SANTOS","SAUNDERS","SCHMIDT","SCHNEIDER","SCHROEDER","SCHULTZ","SCHWARTZ","SCOTT","SERRANO","SHARP","SHAW","SHELTON","SHERMAN","SILVA","SIMMONS","SIMON","SIMPSON","SIMS","SINGH","SMITH","SNYDER","SOLIS","SOTO","SPENCER","STANLEY","STEELE","STEPHENS","STEVENS","STEVENSON","STEWART","STONE","STRICKLAND","SULLIVAN","SUTTON","SWANSON","TATE","TAYLOR","TERRY","THOMAS","THOMPSON","THORNTON","TODD","TORRES","TOWNSEND","TRAN","TRUJILLO","TUCKER","TURNER","VALDEZ","VALENCIA","VARGAS","VASQUEZ","VAUGHN","VAZQUEZ","VEGA","VELASQUEZ","WADE","WAGNER","WALKER","WALLACE","WALSH","WALTERS","WALTON","WANG","WARD","WARNER","WARREN","WASHINGTON","WATERS","WATKINS","WATSON","WATTS","WEAVER","WEBB","WEBER","WEBSTER","WELCH","WELLS","WEST","WHEELER","WHITE","WILLIAMS","WILLIAMSON","WILLIS","WILSON","WISE","WOLF","WOLFE","WONG","WOOD","WOODS","WRIGHT","WU","YANG","YOUNG","ZHANG","ZIMMERMAN"};

vector<string> sortedFirstName = {"AALIYAH","AARON","ABEL","ABIGAIL","ABRAHAM","ADALINE","ADALYN","ADALYNN","ADAM","ADDISON","ADELINE","ADELYN","ADRIAN","ADRIANA","AIDAN","AIDEN","ALAINA","ALAN","ALANA","ALAYNA","ALEJANDRO","ALEX","ALEXA","ALEXANDER","ALEXANDRA","ALEXIS","ALICE","ALINA","ALIVIA","ALIYAH","ALLISON","ALYSSA","AMARA","AMAYA","AMELIA","AMIR","AMY","ANA","ANASTASIA","ANDREA","ANDRES","ANDREW","ANGEL","ANGELA","ANGELINA","ANNA","ANNABELLE","ANTHONY","ANTONIO","ARABELLA","ARIA","ARIANA","ARIANNA","ARIEL","ARTHUR","ARYA","ASHER","ASHLEY","ASHTON","ATHENA","AUBREE","AUBREY","AUDREY","AUGUST","AURORA","AUSTIN","AUTUMN","AVA","AVERY","AVERY","AXEL","AYDEN","AYLA","BAILEY","BARRETT","BEAU","BECKETT","BELLA","BENJAMIN","BENNETT","BENTLEY","BLAKE","BRADLEY","BRADY","BRANDON","BRANTLEY","BRAXTON","BRAYDEN","BRIAN","BRIANNA","BRIELLE","BRODY","BROOKE","BROOKLYN","BROOKLYNN","BROOKS","BRYAN","BRYCE","BRYNLEE","BRYSON","CADEN","CALEB","CALLIE","CALVIN","CAMDEN","CAMERON","CAMILA","CARLOS","CAROLINE","CARSON","CARTER","CATHERINE","CAYDEN","CECILIA","CHARLES","CHARLIE","CHARLIE","CHARLOTTE","CHASE","CHLOE","CHRISTIAN","CHRISTOPHER","CLAIRE","CLARA","CLAYTON","COLE","COLIN","COLTON","CONNOR","COOPER","CORA","DAISY","DAKOTA","DALEYZA","DAMIAN","DANIEL","DANIELA","DAVID","DAWSON","DEAN","DECLAN","DELANEY","DELILAH","DEREK","DESTINY","DIANA","DIEGO","DOMINIC","DYLAN","EASTON","EDEN","EDWARD","ELEANOR","ELENA","ELI","ELIANA","ELIAS","ELIJAH","ELISE","ELIZA","ELIZABETH","ELLA","ELLIANA","ELLIE","ELLIOT","ELLIOTT","ELOISE","EMERSON","EMERSYN","EMERY","EMILIA","EMILIANO","EMILY","EMMA","EMMANUEL","EMMETT","ERIC","ESTHER","ETHAN","EVA","EVAN","EVELYN","EVERETT","EVERLY","EZEKIEL","EZRA","FAITH","FELIX","FINLEY","FINN","FIONA","GABRIEL","GABRIELLA","GAEL","GAVIN","GENESIS","GENEVIEVE","GEORGE","GEORGIA","GIANNA","GIOVANNI","GRACE","GRACIE","GRAHAM","GRANT","GRAYSON","GREYSON","GRIFFIN","HADLEY","HAILEY","HANNAH","HARLEY","HARMONY","HARPER","HARRISON","HAYDEN","HAYDEN","HAZEL","HENRY","HOLDEN","HUDSON","HUNTER","IAN","IRIS","ISAAC","ISABEL","ISABELLA","ISABELLE","ISAIAH","ISLA","ISRAEL","IVAN","IVY","JACE","JACK","JACKSON","JACOB","JADE","JADEN","JAKE","JAMES","JAMESON","JASMINE","JASON","JASPER","JAVIER","JAX","JAXON","JAXSON","JAYCE","JAYDEN","JAYLA","JEREMIAH","JEREMY","JESSE","JESSICA","JESUS","JOANNA","JOCELYN","JOEL","JOHN","JONAH","JONATHAN","JORDAN","JORDYN","JORGE","JOSE","JOSEPH","JOSEPHINE","JOSHUA","JOSIAH","JOSIE","JOSUE","JUAN","JUDAH","JUDE","JULIA","JULIAN","JULIANA","JULIANNA","JULIET","JULIETTE","JUNE","JUSTIN","KADEN","KAI","KAIDEN","KALEB","KARTER","KATHERINE","KAYDEN","KAYLA","KAYLEE","KENDALL","KENNEDY","KENNETH","KEVIN","KHLOE","KILLIAN","KIMBERLY","KING","KINGSTON","KINSLEY","KNOX","KYLE","KYLIE","KYRIE","LAILA","LANDON","LAUREN","LAYLA","LEAH","LEILA","LEILANI","LEO","LEON","LEONARDO","LEVI","LIAM","LILA","LILIANA","LILLIAN","LILLY","LILY","LINCOLN","LOGAN","LOLA","LONDON","LONDYN","LORENZO","LUCA","LUCAS","LUCIA","LUCY","LUIS","LUKAS","LUKE","LUNA","LYDIA","LYLA","MACKENZIE","MADDOX","MADELINE","MADELYN","MADISON","MAGGIE","MAKAYLA","MALACHI","MALIA","MARCUS","MARGARET","MARIA","MARIAH","MARK","MARLEY","MARY","MASON","MATEO","MATIAS","MATTEO","MATTHEW","MAVERICK","MAX","MAXIMUS","MAXWELL","MAYA","MCKENZIE","MELANIE","MELODY","MESSIAH","MIA","MICAH","MICHAEL","MICHELLE","MIGUEL","MILA","MILES","MILO","MOLLY","MORGAN","MYA","MYLES","NAOMI","NATALIA","NATALIE","NATHAN","NATHANIEL","NEVAEH","NICHOLAS","NICOLAS","NICOLE","NOAH","NOELLE","NOLAN","NORA","NORAH","NOVA","OLIVER","OLIVIA","OMAR","OSCAR","OWEN","PAIGE","PAISLEY","PARKER","PARKER","PATRICK","PAUL","PAXTON","PAYTON","PENELOPE","PETER","PEYTON","PIPER","PRESLEY","PRESTON","QUINN","RACHEL","RAELYNN","REAGAN","REBECCA","REESE","REMI","REMINGTON","RHETT","RICHARD","RILEY","RIVER","ROBERT","ROMAN","ROSALIE","ROSE","ROWAN","ROWAN","RUBY","RYAN","RYDER","RYKER","RYLEE","RYLEIGH","SADIE","SAMANTHA","SAMUEL","SANTIAGO","SARA","SARAH","SAVANNAH","SAWYER","SAWYER","SCARLETT","SEBASTIAN","SELENA","SERENITY","SIENNA","SILAS","SKYLAR","SLOANE","SOFIA","SOPHIA","SOPHIE","STELLA","STEVEN","SUMMER","SYDNEY","TAYLOR","TEAGAN","TESSA","THEODORE","THIAGO","THOMAS","TIMOTHY","TRINITY","TRISTAN","TUCKER","TYLER","VALENTINA","VALERIA","VALERIE","VANESSA","VICTOR","VICTORIA","VINCENT","VIOLET","VIVIAN","WAYLON","WESLEY","WESTON","WILLIAM","WILLOW","WYATT","XANDER","XAVIER","XIMENA","ZACHARY","ZANDER","ZANE","ZAYDEN","ZION","ZOE","ZOEY"};

#define NAMEMAX 500 //Number of last names and first names

Data* lastFirstSame[500][500][100];
int lastFirstOccur[500][500];
int position_Last;
int position_First;


list<Data*> sortedList;
list <Data *> :: iterator it;  


int tempFD; // first 3 position
int tempSD; //second 3 position
string tempSSN;
#define FDMAX 1000
#define SDMAX  1000

void whichPatern(list<Data *> &l);

void sortForT1(list<Data *> &l);
void sortForT2(list<Data *> &l);
void sortForT3(list<Data*> &l);
void sortForT4(list<Data*> &l);


void sortLastFirst(list<Data *> &l);
void sortLastFirstT1(list<Data *> &l);


void sortDataList(list<Data *> &l) {
  whichPatern(l);
}


//To determine what type of dataset
void whichPatern(list<Data *> &l){
  
  list <Data *> :: iterator itEnd;
  list <Data *> :: iterator itNext;
  
  itNext = l.begin(); 
  itNext++; 
  
  itEnd = l.end();
  itEnd--;
 
  if((*l.begin())->lastName == (*itEnd)->lastName){
    sortForT4(l);
  }else if((*l.begin())->lastName == (*itNext)->lastName){
    sortForT3(l);
  }else if(l.size()> 200000 ){
    sortForT2(l);
  }else{
    sortForT1(l);
  }

}

int lastThree_1;
int lastThree_2;

struct lastThreeCompare {
  bool operator() (Data* d1, Data* d2) { 
    
    lastThree_1 = (d1->ssn.at(8)-'0')*100+(d1->ssn.at(9)-'0')*10+ (d1->ssn.at(10)-'0'); 
    lastThree_2 = (d2->ssn.at(8)-'0')*100+(d2->ssn.at(9)-'0')*10+ (d2->ssn.at(10)-'0');

    
    if(lastThree_1 < lastThree_2){
      return true;
    }
    return false;
  }
}t4Operator;


struct ssnF2Compare {
  bool operator() (Data* d1, Data* d2) { 

    //compare each char by char
    for(int i = 0 ; i < 11; i++){
      if(d1->ssn.at(i) != d2->ssn.at(i)){
        return d1->ssn.at(i) < d2->ssn.at(i);
      }
    }

    return false;
  }
}ssnF2Operator;


list<Data*> lastFirstSameT1[500][500];

void sortForT1(list<Data *> &l){
  
  sortLastFirstT1(l);

  for(int i = 0; i < NAMEMAX; i++){
      for(int j = 0; j < NAMEMAX; j++){
        lastFirstSameT1[i][j].sort(ssnF2Operator); //Sort for ssn if last first is the same
        sortedList.splice(sortedList.end(),lastFirstSameT1[i][j]);
      }
  }
  l.assign(sortedList.begin(),sortedList.end());
}


void sortLastFirstT1(list<Data *> &l){
  
  for(it = l.begin(); it != l.end(); ++it ){
    position_Last = lower_bound(sortedLastName.begin(),sortedLastName.end(),(*it)->lastName) - sortedLastName.begin();

    position_First = lower_bound(sortedFirstName.begin(),sortedFirstName.end(),(*it)->firstName) - sortedFirstName.begin();

    lastFirstSameT1[position_Last][position_First].push_front(*it);
  }

}



void sortForT2(list<Data *> &l){
  
  sortLastFirst(l);

  for(int i = 0; i < NAMEMAX; i++){
      for(int j = 0; j < NAMEMAX; j++){
        sort(lastFirstSame[i][j], lastFirstSame[i][j]+lastFirstOccur[i][j],ssnF2Operator);
        for(int z = 0; z < lastFirstOccur[i][j]; z++){
          sortedList.push_back(lastFirstSame[i][j][z]);
        }
      }
  }

  l.assign(sortedList.begin(),sortedList.end());
}



void sortLastFirst(list<Data *> &l){
  
  for(it = l.begin(); it != l.end(); ++it ){
    position_Last = lower_bound(sortedLastName.begin(),sortedLastName.end(),(*it)->lastName) - sortedLastName.begin();

    position_First = lower_bound(sortedFirstName.begin(),sortedFirstName.end(),(*it)->firstName) - sortedFirstName.begin();

    lastFirstSame[position_Last][position_First][lastFirstOccur[position_Last][position_First]] = (*it);
    lastFirstOccur[position_Last][position_First]++;
  }

}

string temp_LastName;
string temp_FirstName;
int p1; // hold position for last name
int p2; // hold position for first name

void sortForT3(list<Data*> &l){
  
  //initialize
  temp_LastName = (*l.begin())->lastName;
  temp_FirstName = (*l.begin())->firstName;
  p1 = 0;
  p2 = lower_bound(sortedFirstName.begin(),sortedFirstName.end(),(*l.begin())->firstName) - sortedFirstName.begin();

  //sort by groups(same last name and first name)
  for(it = l.begin(); it != l.end(); ++it ){
      
    if((*it)->lastName == temp_LastName && (*it)->firstName == temp_FirstName){
        
        lastFirstSame[p1][p2][lastFirstOccur[p1][p2]] = *it;
        lastFirstOccur[p1][p2]++;
        
    }else{
        sort(lastFirstSame[p1][p2], lastFirstSame[p1][p2]+lastFirstOccur[p1][p2],ssnF2Operator);
     
        if((*it)->lastName == temp_LastName){
            p2 = lower_bound(sortedFirstName.begin(),sortedFirstName.end(),(*it)->firstName) - sortedFirstName.begin();
        }else if((*it)->firstName == temp_FirstName) {
            p1++;
        }else{
            p1++;
            p2 = lower_bound(sortedFirstName.begin(),sortedFirstName.end(),(*it)->firstName) - sortedFirstName.begin();
        }

        temp_LastName = (*it)->lastName;
        temp_FirstName = (*it)->firstName;
        
        lastFirstSame[p1][p2][lastFirstOccur[p1][p2]] = *it;
        lastFirstOccur[p1][p2]++;

    }
  }

  sort(lastFirstSame[p1][p2], lastFirstSame[p1][p2]+lastFirstOccur[p1][p2],ssnF2Operator);

  for(int i = 0; i < NAMEMAX; i++){
      for(int j = 0; j < NAMEMAX; j++){
        for(int z = 0; z < lastFirstOccur[i][j]; z++){
          sortedList.push_back(lastFirstSame[i][j][z]);
        }
      }
  }
  
  l.assign(sortedList.begin(),sortedList.end());
}


Data* t4Groups[1000][1000][10];
int t4GroupsOccur[1000][1000];

void sortForT4(list<Data*> &l){

  for(it = l.begin(); it != l.end(); ++it ){
    tempSSN = (*it)->ssn;
    
    //convert to group number
    tempFD = (tempSSN.at(0)-'0')*100 + (tempSSN.at(1)-'0')*10 + (tempSSN.at(2)-'0'); 
    tempSD = (tempSSN.at(4)-'0')*100 + (tempSSN.at(5)-'0')*10 + (tempSSN.at(7)-'0');
    
    t4Groups[tempFD][tempSD][t4GroupsOccur[tempFD][tempSD]] = (*it);
    t4GroupsOccur[tempFD][tempSD]++;
  }

  for(int i = 0; i < FDMAX; i++ ){
    for(int j = 0; j < SDMAX; j++ ){
      sort(t4Groups[i][j], t4Groups[i][j] + t4GroupsOccur[i][j], t4Operator);
      for(int z = 0; z < t4GroupsOccur[i][j]; z++){
        sortedList.push_back(t4Groups[i][j][z]);
      }
    }
  }

  l.assign(sortedList.begin(), sortedList.end());
}