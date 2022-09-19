//Name: Jose Brouwer
#include "passserver.h"

PassServer::PassServer(size_t size)
{
  HashTable<std::string, std::string> server(size);
}
PassServer::~PassServer()
{
  server.clear();
}

bool PassServer::load(const char *filename)
{
  if(server.load(filename))
    return true;
  return false;
}
bool PassServer::addUser(std::pair<string,  string> & kv)
{
  kv.second = encrypt(kv.second); //encrypt password
  if(server.insert(kv))
    return true;
  return false;
}
bool PassServer::addUser(std::pair<string, string> && kv)
{
  kv.second = encrypt(std::move(kv.second)); //encrypt password
  if(server.insert(std::move(kv)))
    return true;
  return false;
}
bool PassServer::removeUser(const string & k)
{
  if(server.remove(k))
    return true;
  return false;
}
bool PassServer::changePassword(const std::pair<string, string> &p, const string & newpassword)
{
  if(!(server.contains(p.first)))
    return false;
  string ogPass = encrypt(p.second);
  string newPass = encrypt(newpassword);
  pair<string, string> kv1(p.first, ogPass);
  if(p.second == newPass) //if current pass != p.second
    return false;
  if(!(server.match(kv1)))
    return false;
  else
  {
    pair<string, string> kv2(p.first, newPass);
    server.insert(kv2);
    return true;
  }
}
bool PassServer::find(const string & user)
{
  return server.contains(user);
}

void PassServer::dump()
{
  //scope resolute?
  server.dump(); //HashTable version of dump
}
size_t PassServer::size()
{
  server.size();
}

bool PassServer::write_to_file(const char *filename)
{
  if(server.write_to_file(filename))
    return true;
  return false;
}
string PassServer::encrypt(const string & str)
{
  char salt[] = "$1$########";
  string key = str;
  char* password = new char [100];
  strcpy ( password, crypt(key.c_str(), salt));
  return password;
}
