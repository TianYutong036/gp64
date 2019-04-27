#include"budget.h"

using namespace std;

class User{
  //difine a User class storing user's username,password and budget.
public:
  bool user_login();
  void set_password();
  void set_budget();
  void load_user();
  void output_user();
  void check_budget();
  string username;
  string password;
  Budget budget;
};
