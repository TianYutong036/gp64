#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Account{
  string date,name;
  int budget;
  double balance;

public:
  void user_login();
  void set_budget();
  void add_account();
  void show_record();
  void edit_record();
  void delete_record();
  void add_record();
  void monthly_statement();
  void financial_analysis();
};

void open_record_file(){
  ifstream fin;
  fin.open(record.txt);
  if (fin.fail){
    cout << "No record files found!" << endl;
    exit(1);
  }
}

void Account :: user_login(){

}

void Account :: set_budget(){
  int a;
  cout << "Please enter your budget: ";
  cin >> a;
  budget = a;
  cout << "Budget is set successfully!"<< endl;
}

void Account :: add_account(){
  cout << "\n Please follow the steps to enter all information";
  show_type_list();
  cout << "\n Please choose the account type:";
  cin >> type;
  cout << "\n Please enter the balance:";
  cin >> balance;
}

void Account :: add_record(){

}

void Account :: show_record(){

}

void Account :: edit_record(){

}

void Account :: delete_record(){

}

void Account :: monthly_statement(){

}

void Account :: financial_analysis(){
  
}

int main(){
  Account account;
  int choice = 1;
  while (choice != 0){
    cout << "Enter 0 to exit.\n 1. creat new account \n 2. add a record \n 3. edit a record \n 4. delete a record \n 5. display the records \n 6. send the monthly statement \n 7. send the finantial analysis";
    cin >> choice;
    switch (choice){
      case 0 : exit(1);
      break;
      case 1: account.add_account();
      break;
      case 2: account.add_record();
      break;
      case 3: account.edit_record();
      break;
      case 4: account.delete_record();
      break;
      case 5: account.show_record();
      break;
      case 6: account.monthly_statement();
      break;
      case 7: account.financial_analysis();
      break;
      default: cout << "Invalid option!" << endl;
    }
  }
  return 0;
}
