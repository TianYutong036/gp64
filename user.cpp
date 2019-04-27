#include"user.h"

using namespace std;

void User::load_user(){
  //function : load user information from "user_info.txt".
  //input : None.
  //output : None.
  string filename = "user_info.txt";
  ifstream fin;
  fin.open(filename.c_str());

  if (fin.fail()){
    cout << "Fail to get user information." << endl;
    exit(1);
  }
  //load user information
    fin >> username;
    fin >> password;
    fin >> budget.amount;
    fin >> budget.check;
    fin >> budget.expenses;
    fin.close();
}

bool User :: user_login(){
  //function : to check the username and password for login(3 attempts to enter the password).
  //input : None.
  //output : return 0 if unsuccessfully login, return 1 if successfully login.
  int i = 3;
  string un;
  while (1){
    cout << "Username:";
    cin >> un;
    if (un == username){
      break;
    }
    cout << "Incorrect username!"<<endl;
  }
  // input password if username is correct.
  string pw;
  cout << "Password:";
  while (1) {
    cin >> pw;
    if (pw == password){
      return true;
    }
    i--;
    // if input incorrect password 3 times then login is unsuccessful.
    if (i == 0){
      return false;
    }

    cout << "Incorrect password. Please try again."<<endl;
    cout << "Password:";
  }
}

void User :: set_budget(){
  //function : to set a monthly budget.
  //input : None.
  //output : None.
  double x;
  cout << "Please enter the budget:";
  cin >> x;
  budget.amount = x;
  budget.check = 1;
  budget.expenses = 0;
  cout << "Budget set up."<< endl << endl;
}

void User :: check_budget(){
  //function : check if monthly expenses is over the set budget.
  //input : None.
  //output : None.
  if(budget.expenses >= budget.amount){
      cout<<"Attention! You have already spend "<<budget.expenses<<" which is over your budget."<<endl;
      cout<<"Your budget set is eliminated."<<endl;
      // eliminate the budget set.
      budget.amount=0;
      budget.check=0;
      budget.expenses=0;
  }
}

void User :: set_password(){
  //function : reset the password.
  //input : None.
  //output : None.
  string pw, pwcheck;
  cout << "Please enter the original password:";
  cin >> pw;
  //input original password first.
  while (pw != password){
    cout << "Wrong password. Please try again." << endl;
    cout << "Please enter the original password:";
    cin >> pw;
  }
  //set new password.
    cout << "Please enter the new password:";
    cin >> pw;
    cout << "Re-enter the new password:";
    cin >>pwcheck;

    while (pw != pwcheck){
      cout << "Wrong pastword entered! Please try again." << endl;
      cout << "Re-enter the new password:";
      cin >>pwcheck;
    }

      cout << "Password set successfully."<< endl << endl;
      password = pw;
}

void User::output_user(){
  //function : to store the user information in the file "user_info.txt" when exit the program.
  //input : None.
  //output : None.
  string filename = "user_info.txt";
  ofstream fout;
  fout.open(filename.c_str());

  if(fout.fail()){
    cout << "Failed to output user information into " << filename << "." << endl;
    exit(1);
  }
  //output the user information.
  fout << username << endl;
  fout << password << endl;
  fout << budget.amount << endl;
  fout << budget.check << endl;
  fout << budget.expenses << endl;
  fout.close();
}
