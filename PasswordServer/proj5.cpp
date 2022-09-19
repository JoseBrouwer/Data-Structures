//Name: Jose Brouwer
#include "hashtable.h"
#include "passserver.h"
#include <cctype>
#include <string>
using namespace std;
using namespace cop4530;
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main()
{
  int size;
  cout << "Enter the preffered hash table capacity: ";
  cin >> size;
  PassServer p(size);
  char input;
  do
  {
    void Menu();
    cin >> input;
    tolower(input);
    switch(input)
    {
      case 'l':
      {
        cout << "\nEnter password file name to load from: ";
        std::string filename;
        cin >> filename;
        if(!p.load(filename.c_str())) //for char ptr
          cout << "Cannot open file " << filename << "\n";
        break;
      }
      case 'a':
      {
        std::string username;
        std::string password;
        cout << "\nEnter username: ";
        cin >> username;
        cout << "\nEnter password: ";
        cin >> password;
        std::pair<std::string, std::string> kv(username, password);
        if(p.addUser(kv))
          cout << " \n\nUser " << username << " added.\n\n";
        else
          cout <<"*****Error: User already exists. Could not add user" << endl;
        break;
      }
      case 'r':
      {
        std::string username;
        cout <<"Eneter username: ";
        cin >> username;
        if(p.removeUser(username))
          cout <<  " \n\nUser " << username << " deleted.\n\n";
        else
          cout << "*****Error: User not found. Could not delete user\n";
        break;
      }
      case 'c':
      {
        std::string username;
        std::string password;
        std::string newpassword;
        cout << "Enter username:";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter new password: ";
        cin >> newpassword;
        std::pair<std::string, std::string> kv(username, password);
        if(p.changePassword(kv, newpassword))
          cout << "Password changed for " << username << "\n";
        else
          cout << "*****Error: Could not change user password\n";
        break;
      }
      case 'f':
      {
        std::string username;
        cout << "Enter username: ";
        cin >> username;
        if(p.find(username))
          cout << "User '" << username << "' found.\n";
        else
          cout << "User '" << username << "' not found.\n";
        break;
      }
      case 'd':
      {
        p.dump();
        break;
      }
      case 's':
      {
        cout << "size of hashtable: " << p.size() << endl;
        break;
      }
      case 'w':
      {
        std::string filename;
        cout << "Enter password file name to write to: ";
        cin >> filename;
        p.write_to_file(filename.c_str());
        break;
      }
      case 'x':
      {
        break;
      }
    }//end switch
  } while(input != 'x');
}
