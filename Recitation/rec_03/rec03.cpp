/*
  rec03_start.cpp
  Adonis Garcia
  Using classes to create accounts and transactions
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
  string name;
  int account_number;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2{
  friend ostream& operator<<(ostream& os, const Account2& account);

public:
  Account2(const string& aName, int some_account_number)
    : name(aName), account_number(some_account_number) {}

  const string& getName() const {return name;}
  int getAccountNumber() const {return account_number;}

private:
  string name;
  int account_number;
};

// ostream& operator<<(ostream& os, Account2& account){
//   cout << "Name: " << account.getName() << ", #: " << account.getAccountNumber() << endl;
//   return os;
// }

ostream& operator<<(ostream& os, const Account2& account){
  cout << "Name: " << account.name << ", #: " << account.account_number << endl;
  return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes

class Transaction {
  friend ostream& operator<<(ostream& os, const Transaction& transaction);
public:
  Transaction(const string& aType, int aQuantity)
    : type(aType), quantity(aQuantity) {}

private:
  string type;
  int quantity;
};

ostream& operator<<(ostream& os, const Transaction& transaction){
  cout << transaction.type << " " << transaction.quantity << endl;
  return os;
}

class Account3{
  friend ostream& operator<<(ostream& os, const Account3& account);

public:
  Account3(const string& aName, int some_account_number)
    : name(aName), account_number(some_account_number) {}

  void deposit(int amount){
    history.emplace_back("deposit", amount);
    balance += amount;
  }

  void withdraw(int amount){
    if (amount > balance){
      cout << "Account# " << account_number << " only has "
      << balance << ". Insufficient for withdrawal of "
      << amount << endl;
    } else {
      history.emplace_back("withdraw", amount);
      balance -= amount;
    }
  }

  int getAccountNumber() const {return account_number;}

private:
  string name;
  int account_number;
  vector<Transaction> history;
  int balance{};
};

ostream& operator<<(ostream& os, const Account3& account){
  cout << account.name << " " << account.account_number << endl;
  for (const Transaction& transaction: account.history){
    cout << '\t' << transaction;
  }
  return os;
}


// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)




class Account4{
  friend ostream& operator<<(ostream& os, const Account4& account);

public:
  class Transaction2 {
    friend ostream& operator<<(ostream& os, const Transaction2& transaction);
  public:
    Transaction2(const string& aType, int aQuantity)
      : type(aType), quantity(aQuantity) {}

  private:
    string type;
    int quantity;
  };

  Account4(const string& aName, int some_account_number)
    : name(aName), account_number(some_account_number) {}

  void deposit(int amount){
    history.emplace_back("deposit", amount);
    balance += amount;
  }

  void withdraw(int amount){
    if (amount > balance){
      cout << "Account# " << account_number << " only has "
      << balance << ". Insufficient for withdrawal of "
      << amount << endl;
    } else {
      history.emplace_back("withdraw", amount);
      balance -= amount;
    }
  }

  int getAccountNumber() const {return account_number;}

private:
  string name;
  int account_number;
  vector<Transaction2> history;
  int balance{};
};

ostream& operator<<(ostream& os, const Account4& account){
  cout << account.name << " " << account.account_number << endl;
  for (const Account4::Transaction2& transaction: account.history){
    cout << '\t' << transaction;
  }
  return os;
}

ostream& operator<<(ostream& os, const Account4::Transaction2& transaction){
  cout << transaction.type << " " << transaction.quantity << endl;
  return os;
}

// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)

class Account5{
  class Transaction3 {
    friend ostream& operator<<(ostream& os, const Transaction3& transaction);
  public:
    Transaction3(const string& aType, int aQuantity)
      : type(aType), quantity(aQuantity) {}

  private:
    string type;
    int quantity;
  };

  friend ostream& operator<<(ostream& os, const Account5& account);
  friend ostream& operator<<(ostream& os, const Transaction3& transaction);

public:

  Account5(const string& aName, int some_account_number)
    : name(aName), account_number(some_account_number) {}

  void deposit(int amount){
    history.emplace_back("deposit", amount);
    balance += amount;
  }

  void withdraw(int amount){
    if (amount > balance){
      cout << "Account# " << account_number << " only has "
      << balance << ". Insufficient for withdrawal of "
      << amount << endl;
    } else {
      history.emplace_back("withdraw", amount);
      balance -= amount;
    }
  }

  int getAccountNumber() const
  {return account_number;}

private:
  string name;
  int account_number;
  vector<Transaction3> history;
  int balance{};
};

ostream& operator<<(ostream& os, const Account5& account){
  cout << account.name << " " << account.account_number << endl;
  for (const Account5::Transaction3& transaction: account.history){
    cout << '\t' << transaction;
  }
  return os;
}

ostream& operator<<(ostream& os, const Account5::Transaction3& transaction){
  cout << transaction.type << " " << transaction.quantity << endl;
  return os;
}

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream input_file;
    input_file.open("accounts.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    string name;
    int account_number;
    vector<Account> accounts;

    while (input_file >> name >> account_number){
      Account new_account;
      new_account.name = name;
      new_account.account_number = account_number;
      accounts.push_back(new_account);
    }

    input_file.close();

    for (const Account& account: accounts){
      cout << "Name: " << account.name << ", #:" << account.account_number << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();

    input_file.open("accounts.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    while (input_file >> name >> account_number){
      Account new_account{name, account_number};
      accounts.push_back(new_account);
    }

    input_file.close();

    for (const Account& account: accounts){
      cout << "Name: " << account.name << ", #:" << account.account_number << endl;
    }

    accounts.clear();

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    vector<Account2> accounts2;

    input_file.open("accounts.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    while (input_file >> name >> account_number){
      Account2 new_account(name, account_number);
      accounts2.push_back(new_account);
    }

    input_file.close();

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    
    for (Account2& account: accounts2){
      cout << "Name: " << account.getName() << ", #: " << account.getAccountNumber() << endl;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";

    for (Account2& account: accounts2){
      cout << account;
    }

    input_file.close();
    accounts2.clear();

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    input_file.open("accounts.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    while (input_file >> name >> account_number){
      accounts2.push_back(Account2(name, account_number));
    }

    for (Account2& account: accounts2){
      cout << account;
    }

    input_file.close();
    accounts2.clear();

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";

    input_file.open("accounts.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    while (input_file >> name >> account_number){
      accounts2.emplace_back(name, account_number);
    }

    for (const Account2& account: accounts2){
      cout << account;
    }

    input_file.close();
    accounts2.clear();
    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    input_file.open("transactions.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    vector<Account3> accounts3;
    string command;
    int quantity;

    while (input_file >> command){
      if (command == "Account"){
        input_file >> name >> account_number;
        accounts3.emplace_back(name, account_number);
        continue;
      } else {
        input_file >> account_number >> quantity;
        for (size_t i{}; i < accounts3.size(); i++){
          if (accounts3[i].getAccountNumber() == account_number){
            if (command == "Deposit"){
              accounts3[i].deposit(quantity);
            } else {
              accounts3[i].withdraw(quantity);
            }
          } 
        }
      }
    }

    for (const Account3& account: accounts3){
      cout << account << endl;
    }


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    input_file.close();

    input_file.open("transactions.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    vector<Account4> accounts4;

    while (input_file >> command){
      if (command == "Account"){
        input_file >> name >> account_number;
        accounts4.emplace_back(name, account_number);
        continue;
      } else {
        input_file >> account_number >> quantity;
        for (size_t i{}; i < accounts4.size(); i++){
          if (accounts4[i].getAccountNumber() == account_number){
            if (command == "Deposit"){
              accounts4[i].deposit(quantity);
            } else {
              accounts4[i].withdraw(quantity);
            }
          } 
        }
      }
    }

    for (const Account4& account: accounts4){
      cout << account << endl;
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    input_file.close();

    input_file.open("transactions.txt");
    if (!input_file){
      cout << "File didn't open" << endl;
      exit(1);
    }

    vector<Account5> accounts5;

    while (input_file >> command){
      if (command == "Account"){
        input_file >> name >> account_number;
        accounts5.emplace_back(name, account_number);
        continue;
      } else {
        input_file >> account_number >> quantity;
        for (size_t i{}; i < accounts5.size(); i++){
          if (accounts5[i].getAccountNumber() == account_number){
            if (command == "Deposit"){
              accounts5[i].deposit(quantity);
            } else {
              accounts5[i].withdraw(quantity);
            }
          } 
        }
      }
    }

    for (const Account5& account: accounts5){
      cout << account << endl;
    }

    return 0;
}
