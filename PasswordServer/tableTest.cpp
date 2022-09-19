#include "hashtable.h"
using namespace cop4530;
using namespace std;

int main()
{
  HashTable<int, int> h1(5);
  cout << "h1 size is: " << h1.size() << endl;
  std::pair<int, int> kv1(1, 1);
  std::pair<int, int> kv2(2, 2);
  std::pair<int, int> kv3(3, 3);
  std::pair<int, int> kv4(6, 6);
  h1.insert(kv1);
  h1.insert(kv2);
  h1.insert(kv3);
  h1.insert(kv4);
  h1.dump();
  cout << "h1 size is: " << h1.size() << endl;
  if(h1.match(kv4))
    cout << "kv4 K, V is in the table." << endl;
  else
    cout << "kv4 K, V is not in the table." << endl;

  if(h1.contains(3))
    cout << "3 is in the table" << endl;
  else
    cout << "3 is not in the table" << endl;
  if(h1.remove(6))
    cout << "removing 6..." << endl;
  else
    cout << "remove failed..." << endl;
  h1.dump();
  cout << "\nclearing..." << endl;
  h1.clear();
  h1.dump();
  cout << "h1 size is: " << h1.size() << endl;
  HashTable<std::string, std::string> h2(5);
  cout << "loading table from file..." << endl;
  h1.load("load.txt");
  h1.dump();
  cout <<"writing to file from table..." << endl;
  h1.write_to_file("load.txt");
  

}
