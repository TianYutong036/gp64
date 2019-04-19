#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class User{
public:
  string username;
  string password;
};

class Record{
public:
  string date,note;
  int amount,type;
  char sign;
  Record * next;
};

class Account{
public:
  int budget;
};

bool user_login(User user){
  //function: to check the username and password for login(3 attempts to enter the password)
  //input: username and password
  //output: return false if all three are wrong,return true otherwise.
  int i = 3;
  string un;
  while (1){
    cout << "Username:";
    cin >> un;
    if (un == user.username){
      break;
    }
    cout << "Incorrect username!"<<endl;
  }

  string inputpassword;
  cout << "Password:";
  while (1) {
    cin >> inputpassword;
    if (inputpassword == user.password){
      return true;
    }
    i--;
    if (i == 0){
      return false;
    }
    cout << "Incorrect password. Please try again."<<endl;
    cout << "Password:";
  }
}

void set_budget(Account account){
  //function: to set a monthly budget
  //input: None
  //output:None
  int x;
  cout << "Please enter the budget:";
  cin >> x;
  account.budget = x;
  cout << "Budget set up."<< endl;
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
  User user;
  cout << "********************************" << endl;
  cout << "* Welcome to Accounting system *" << endl;
  cout << "********************************" << endl;
  bool flag = user_login(user);//check user name and password
  if (flag){
    int choice;
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
  cout << "Unsuccessful login." << endl;
  exit(1);
}
