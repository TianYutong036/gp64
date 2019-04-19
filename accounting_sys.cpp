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
  stream<<n; //n为int类型
  return stream.str();
}

//function: to check the username and password for login(3 attempts to enter the password).
//input: username and password.
//output: return false if all three are wrong,return true otherwise.
bool User :: user_login(){
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

//function:reset the password.
//input:None.
//output:None.
void User :: set_password(){
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

//function: to set a monthly budget.
//input: None.
//output:None.
void set_budget(User user){
  int x;
  cout << "Please enter the budget:";
  cin >> x;
  user.budget = x;
  cout << "Budget set up."<< endl;
}

//function:print out all records in the file.
//input:the array of all the records, the number of records.
//output:None.
void show_record(Record record[], int num){
    for(int i = 0; i < num; i++){
    string amount = record[i].sign + itos(record[i].amount);
    cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
    cout << setw(7) << i+1 << setw(12) << record[i].date << setw(10) << record[i].type << setw(10) << amount << setw(20) << record[i].note << endl;
  }
}

//function:edit one record in the file.
//input:the array of all the records, the number of records.
//output:None.
void edit_record(Record record[], int num){
  show_record(record, num);
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
    record[x-1].date = correction;
  }

  cout << "Change the type(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the type:";
    cin >> correction;
    record[x-1].type = correction;
  }

  cout << "Change the amount(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the amount:";
    cin >> amount;
    record[x-1].amount = amount;
  }
  cout << "Change the note(Y/N)?"
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the note:";
    cin >> correction;
    record[x-1].note = correction;
  }
  cout << "Modify completed!"<< endl;
}

//function:delete one record in the file.
//input:the array of all the records, the number of records.
//output:None.
void delete_record(Record & record[], int & num){
  show_record(record, num);
  char ans;
  int x;
  cout << "Please choose the record to edit:";
  cin >> x;
  cout << "Delete record " << x << "(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    Record * new = new Record [num - 1];
    num--;
    for (int i = 0; i < x - 1; i++){
      new[i] = record[i];
    }
    for (int i = x; i < num; i++){
      new[i] = record[i];
    }
    record = new;
  }
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
    char choice = selection_menu();
    while (choice != '0'){
      switch (choice){
        case '1':
          cout << "Please enter the filename: ";
          cin >> str;
          num_records = load_phonebook(str, phonebook, phonebook_size);
          cout << endl << num_records << " record(s) loaded." << endl << endl;
          break;

        case '2':
          print_phonebook(phonebook, num_records);
          break;

        case '3':
          sort_phonebook(phonebook, num_records);
          print_phonebook(phonebook, num_records);
          break;

        case '4':
          cout << "Please enter a name: ";
          cin >> str;
          cout << endl;
          count = search_phonebook(str, phonebook, num_records);
          cout << count << " record(s) found." << endl << endl;
          break;

        case '5':
          cout << "Please enter the filename: ";
          cin >> str;
          count = save_phonebook(str, phonebook, num_records);
          cout << endl << count << " record(s) saved." << endl << endl;
          break;

        case '6':
          if (num_records >= phonebook_size)
            grow_phonebook(phonebook, phonebook_size, 3);

          if (num_records < phonebook_size)
            num_records = add_record(phonebook, num_records);
          cout << "There are now " << num_records <<
              " record(s) in the phonebook." << endl << endl;
          break;

        default:
          cout << "Invalid input!" << endl;
        }
  choice = selection_menu();
    }
  cout << "Goodbye!" << endl << endl;
  delete [] phonebook;
  }
  else{
    cout << "Unsuccessful login." << endl;
    exit(1);
  }

  return 0;
}
