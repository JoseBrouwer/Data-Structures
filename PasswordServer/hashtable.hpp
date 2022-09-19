//Name: Jose Brouwer
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
  hashTable.resize(prime_below(size)); //vector resize function
  currentSize = 0; //empty vector
  if(hashTable.capacity() <= 0)
    hashTable.resize(default_capacity);
}
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
  clear();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
{
  auto & whatTable = hashTable[myhash(k)];
  auto itr = whatTable.begin();
  for(itr; itr != whatTable.end(); itr++)
  {
    std::pair<K, V> p = *itr;
    if(p.first == k)
      return true;
  }
  return false;
}
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> &kv)
{
  auto & whatTable = hashTable[myhash(kv.first)];
  if(find(begin(whatTable), end(whatTable), kv) != end(whatTable))
    return true;
  return false;
}
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
{
  auto & whatTable = hashTable[myhash(kv.first)];
  //whatTable.resize(prime_below(hashTable.size()));
  auto itr = find(whatTable.begin(), whatTable.end(), kv);
  if(itr != whatTable.end())
    return false;
  whatTable.push_back(kv);
  //cout << "currentSize is: " << currentSize << endl;
  //cout << "table Size is: " << whatTable.size() << endl;
  if(++currentSize > hashTable.capacity())
  {
    cout << "calling rehash()..." << endl;
    rehash();
  }
  return true;
}
template <typename K, typename V>
bool HashTable<K, V>::insert (std::pair<K, V> && kv)
{
  auto & whatTable = hashTable[myhash(std::move(kv.first))];
  //whatTable.resize(prime_below(hashTable.size()));
  if(find(begin(whatTable), end(whatTable), std::move(kv)) != end(whatTable))
    return false;
  whatTable.push_back(std::move(kv));
  //cout << "currentSize is: " << currentSize << endl;
  //cout << "table Size is: " << whatTable.size() << endl;
  if(++currentSize > hashTable.capacity())
  {
    cout << "calling rehash()..." << endl;
    rehash();
  }
  return true;
}
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
  auto & whatTable = hashTable[myhash(k)];
  auto itr = whatTable.begin();

  for(itr; itr != whatTable.end(); itr++)
  {
    std::pair<K, V> p = *itr;
    if(p.first == k)
    {
      whatTable.erase(itr);
      --currentSize;
      return true;
    }
  }
  return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
  ifstream theFile;
  theFile.open(filename, std::ifstream::in);
  std::pair<K, V> kv; //create a pair
  if(theFile.is_open()) //if file is opened
  {
    while(!(theFile.eof())) //while there is content
    {
      cin >> kv.first;
      cin >> kv.second;
      insert(kv);
    }
    theFile.close();
    return true; //file loaded
  }
  else
    return false; //file not found
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
{
  int i = 0;
  if(currentSize > 0) //if there are items
  {
    auto itr = hashTable.begin();
    for(itr; itr != hashTable.end(); itr++)
    {
      list<std::pair<K, V>> l = *itr; //list at index
      if(l.size() == 1) //list has one item
      {
        auto listItr = l.begin(); //list iterator
        std::pair<K, V> sub = *listItr; //data at node
        cout << "v[" << i << "]: " << sub.first << " " << sub.second << endl;
        i++;
      }
      else if(l.size() > 1)
      {
        auto listItr = l.begin(); //list iterator
        cout << "v[" << i << "]: "; //print index
        auto endItr = l.end(); //to prevent printing of extra colon
        endItr--;
        for(listItr; listItr != endItr; listItr++) //iterate list
        {
          std::pair<K, V> sub = *listItr; //data at node
          cout << sub.first << " " << sub.second << " : "; //print list and semicolon
        }
        std::pair<K, V> sub = *listItr; //last node
        cout << sub.first << " " << sub.second << endl; //print last item
        i++; //increase index
      }
      else if(l.size() == 0) //if index is empty
      {
        cout << "v[" << i << "]: " << endl; //print index
        i++;
      }
    }//end for loop
  }//end main if
  else //empty hashTable
  {
    auto itr = hashTable.begin();
    for(itr; itr != hashTable.end(); itr++)
    {
      cout << "v[" << i << "]: " << endl; //print index
      i++;
    }
  }
}//end dump
template <typename K, typename V>
size_t HashTable<K, V>::size() const
{
  return currentSize;
}
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)
{
  ofstream theFile;
  theFile.open(filename);
  if(theFile.is_open())
  {
    for(int i = 0; i < hashTable.size(); i++)
    {
      for(auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
      {
        std::pair<K, V> sub = *itr;
        theFile << sub.first << ' ' << sub.second << '\n';
      }
    }//end for
    theFile.close();
    return true;
  }//end is open
  return false;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
  for(auto & x : hashTable)
  {
    x.clear();
  }
  currentSize = 0;
}
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
  vector<list<std::pair<K, V>>> oldTable = hashTable;

  cout << "resizing hashTable..." << endl;
  hashTable.resize(prime_below(2*hashTable.size()));
  //hashTable.capacity = hashTable.capacity();
  for(auto & x : hashTable)
    x.clear();

  currentSize = 0;
  for(auto & x : oldTable)
    for(auto & y : x)
    {
      //cout << "repopulating table..." << endl;
      insert(std::move(y));
    }
}
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
  std::hash<K> hashKey;
  return hashKey(k) % hashTable.size(); //we have separate chaining so return right away
}
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  cout <<"number passed into prime_below: " << n << endl;
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
