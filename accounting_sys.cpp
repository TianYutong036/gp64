#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class User{
public:
  string username = "Kit";
  string password = "000000";
  int budget;
  bool user_login();
  void set_password();
  void set_budget();
};

class Record{
public:
  string date,note;
  int amount,type;
  char sign;
};

string itos(int n){
  //fuction: convert int to string
  //input:int n
  //output:n in string type
  ostringstream stream;
  stream<<n;
  return stream.str();
}

bool User :: user_login(){
  //function: to check the username and password for login(3 attempts to enter the password).
  //input: username and password.
  //output: return false if all three are wrong,return true otherwise.
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

  string pw;
  cout << "Password:";
  while (1) {
    cin >> pw;
    if (pw == password){
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

void User :: set_budget(){
  int x;
  cout << "Please enter the budget:";
  cin >> x;
  budget = x;
  cout << "Budget set up."<< endl;
}

void User :: set_password(){
  //function:reset the password.
  //input:None.
  //output:None.
  string pw, pwcheck;
  cout << "Please enter the original password:";
  cin >> pw;
  while (pw != password){
    cout << "Wrong password. Please try again." << endl;
    cout << "Please enter the original password:";
    cin >> pw;
  }
    cout << "Please enter the new password:";
    cin >> pw;
    cout << "Re-enter the new password:";
    cin >>pwcheck;
    if (pw == pwcheck){
      cout << "Password motified successfully."<< endl;
      password = pw;
    }
}

void load_record(string filename, Record * &ar, int &num){
  ifstream fin;
  fin.open(filename.c_str());
  if (fin.fail()){
    cout << "Failed to open the file." << endl;
    exit(1);
  }
  int i = 0;
  string line;
  while(getline(fin, line)){
    if (i >= num){
      grow_record(ar,num);
    }
    if (i < num){
      istringstream iss(line);
      if (!getline(iss, ar[i].date,','))
        break;
      if (!getline(iss, ar[i].type,','))
        break;
      if (!getline(iss, ar[i].sign,','))
        break;
      if (!getline(iss, ar[i].amount,','))
        break;
      if (!getline(iss, ar[i].note))
        break;
      i++;
    }
  }
  fin.close();
}

void grow_record(Record * &ar, int &num){
  //
  //
  //
  ar_new = new Record [2 * num];
  for (int i = 0; i < num; i++){
    ar_new[i] = ar[i];
  }
  delete [] ar;
  ar = ar_new;
  num *= 2;
}

void show_record(Record ar[], int num){
  //function:print out all records in the file.
  //input:the array of all the records, the number of records.
  //output:None.
    for(int i = 0; i < num; i++){
    string amount = ar[i].sign + itos(ar[i].amount);
    cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
    cout << setw(7) << i+1 << setw(12) << ar[i].date << setw(10) << ar[i].type << setw(10) << amount << setw(20) << ar[i].note << endl;
  }
}

void edit_record(Record &ar[], int num){
  //function:edit one record in the file.
  //input:the array of all the records, the number of records.
  //output:None.
  show_record(ar[],num);
  int x, amount;
  char ans;
  string correction;
  cout << "Please choose the record to edit:";
  cin >> x;

  cout << "Change the date(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the date:";
    cin >> correction;
    ar[x-1].date = correction;
  }

  cout << "Change the type(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the type:";
    cin >> correction;
    ar[x-1].type = correction;
  }

  cout << "Change the amount(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the amount:";
    cin >> amount;
    ar[x-1].amount = amount;
  }
  cout << "Change the note(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the note:";
    cin >> correction;
    ar[x-1].note = correction;
  }
  cout << "Modify completed!"<< endl;
}

void delete_record(Record &ar[], int &num){
  //function:delete one record in the file.
  //input:the array of all the records, the number of records.
  //output:None.
  show_record(ar[],num);
  char ans;
  int x;
  cout << "Please choose the record to edit:";
  cin >> x;
  cout << "Delete record " << x << "(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    num--;
    Record * new_r = new Record [num];
    for (int i = 0; i < x - 1; i++){
      new_r[i] = ar[i];
    }
    for (int i = x; i < num; i++){
      new_r[i] = ar[i];
    }
    ar = new_r;
  }
}

void add_record(Record &ar[], int &num){
  //
  //
  //
	string str;
	getline(cin, str); // flush the keyboard buffer
	cout << "Please enter the date: ";
	getline(cin, new_list[num].date);
	cout << "Please enter the type: ";
	getline(cin, new_list[num].type);
  cout << "Please enter the amount: ";
  getline(cin, new_list[num].amount);
  cout << "Please enter the note: ";
  getline(cin, new_list[num].note);
	cout << "Date:\t" << new_list[nRec].date << endl;
  cout << "Type:\t" << new_list[nRec].type << endl << endl;
  cout << "Amount:\t" << pb[nRec].amount << endl << endl;
  cout << "Note:\t" << pb[nRec].note << endl << endl;
  cout << "Add to record (Y/N)? ";
	cin >> ans;
	if (ans == 'Y'){
    cout << "1 record added." << endl;
		num++;
	}
}

void sort_record(Record &ar[], int num){

}

void search_record(Record ar[], int num){

}

void monthly_statement(Record ar[], int num){
}

void financial_analysis(Record ar[], int num){
}

char selection_menu(){
	char choice;

	// print selection menu
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

int main(){
  User user;
  cout << "********************************" << endl;
  cout << "* Welcome to Accounting system *" << endl;
  cout << "********************************" << endl;
  bool flag = user.user_login(user);//check user name and password
  if (flag){
    int num = 3;
    Record * ar = new Record [num];
    string str;
    cout << "Please enter the filename to import records: ";
    cin >> str;
    load_record(str, ar, num);
    char choice = selection_menu();
    while (choice != '0'){
      switch (choice){
        case '1':
          add_record(ar, num);
          break;
        case '2':
          show_record(ar, num);
          break;
        case '3':
          edit_record(ar, num);
          break;
        case '4':
          search_record(ar, num);
          break;
        case '5':
          monthly_statement(ar,num);
          break;
        case '6':
          financial_analysis(ar, num);
          break;
        case '7':
          user.set_budget();
          break;
        case '8':
          sort_record(ar, num);
          break;
        case '9':
          user.set_password();
          break;
        default:
          cout << "Invalid input!" << endl;
        }
  choice = selection_menu();
    }
  cout << "Goodbye!" << endl << endl;
  delete [] ar;
  }
  else{
    cout << "Unsuccessful login." << endl;
    exit(1);
  }

  return 0;
}
