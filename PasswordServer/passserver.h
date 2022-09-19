//Name: Jose Brouwer
#include "hashtable.h"
#include<crypt.h>
#include<cstring>
#include <string>
using namespace cop4530;
using namespace std;

class PassServer
{
public:
  PassServer(size_t size = 101);
  ~PassServer();

  bool load(const char *filename);
  bool addUser(std::pair<string,  string> & kv);
  bool addUser(std::pair<string, string> && kv);
  bool removeUser(const string & k);
  bool changePassword(const std::pair<string, string> &p, const string & newpassword);
  bool find(const string & user);

  void dump();
  size_t size();

  bool write_to_file(const char *filename);
private:
  string encrypt(const string & str);
  HashTable<std::string, std::string> server;
};
