#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Record{
  string date,note;
  int amount,type;
  char sign;
  Record * next;
};

void user_login(){
}

void set_budget(){
}

void add_account(){
}

void show_record(){
}

void edit_record(){
}

void delete_record(){
}

void add_record(){
}

void monthly_statement(){
}

void financial_analysis(){
}

void sort_record(){

}

void change_password(){

}

int main(){
  cout << "********************************" << endl;
  cout << "* Welcome to Accounting system *" << endl;
  cout << "********************************" << endl;
  cout<< “*please input your password*”<<endl;//check user name and password


  cout << "1. Add a new record." << endl;
  cout << "2. Print all records." << endl;
  cout << "3. Edit the record." << endl;
  cout << "4. Search the records by partial match of the name." << endl;
  cout << "5. Show monthly statement." << endl;
  cout << "6. Show financial analysis of the month." << endl;
  cout << "7. Set budget." << endl;
  cout << "8. Sort the records by date or amount." <<endl;
  cout << "9. Change login password." << endl;
  cout << "0. Quit. " << endl;
  cout << "Please enter your choice: ";
  // read user selection
  cin >> choice;
  cout << endl;

  return choice;
}
