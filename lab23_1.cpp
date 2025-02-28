#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream file(filename) ;
    string textline;
    char name[100];
    int s1,s2,s3 ;
    while(getline(file,textline)){
        sscanf(textline.c_str(),"%[^:]: %d %d %d",name,&s1,&s2,&s3);
        names.push_back(name) ;
        scores.push_back(s1+s2+s3);
        grades.push_back(score2grade(s1+s2+s3));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n" ;
    cin >> command;
    command = toUpperStr(command) ;
    if(command == "GRADE"){
        cin >> key ;
    }if(command == "NAME"){
        cin.ignore();
        getline(cin,key) ;
    }     
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades, string key){
    int count = 0;
    cout << "---------------------------------" << endl ;
    for(unsigned i=0;i<names.size();i++){
        if(key==toUpperStr(names[i])){
            cout << names[i] << "'s" << " score = " << scores[i] << endl;
            cout << names[i] << "'s" << " grade = " << grades[i]  << endl ;
            count ++;
        }
    }
    if(count==0){
            cout << "Cannot found." << endl ;
    }
    cout << "---------------------------------\n" ;
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    int count = 0;
    cout << "---------------------------------" << endl ;
    for(unsigned int i = 0;i<names.size();i++){
        if(*key.c_str()==grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl ;
            count++ ;
        }
    }
    if(count==0){
        cout << "Cannot found." << endl ;
    }
    cout << "---------------------------------\n" ;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}