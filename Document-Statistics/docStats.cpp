//Name: Jose Brouwer
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <utility>
using namespace std;

void printResults(vector<std::pair<std::string, int>> v, string w)
{
  if(v.size() > 10)
  {
    cout <<"Total "<<v.size()<<" different "<<w<<", 10 most used "<< w <<"\n";
    for(int i = 0; i < 10; i++)
      cout << "No. " << i << ": " << v[i].first << "\t" << v[i].second << endl;
  }
  else
  {
    cout <<"Total "<<v.size()<<" different "<<w<<", "<<v.size()<<" most used "<< w <<"\n";
    for(int i = 0; i < v.size(); i++)
      cout << "No. " << i << ": " << v[i].first << "\t" << v[i].second << endl;
  }
}

int main() //reading in from standard input.
{
  std::map<char, int> charMap;
  std::unordered_map<std::string,int> stringMap;
  std::unordered_map<std::string, int> numMap;
  vector<std::pair<char, int>> v1;
  vector<std::pair<std::string, int>> v2;
  vector<std::pair<std::string, int>> v3;
  //stringstream word;
  std::string line; //read in line by line with getline
  int sPos, ePos;
  while(!std::cin.eof()) //while there is content
  {
    stringstream word;
    getline(std::cin, line); //newline is default delim
    //cout << "Line is: " << line << endl;
    word << line; //send the line to the stream
    //if cin.peek == '\n' then go through process in for loop same for '\t'
    auto itr = line.cbegin();
    for(itr; itr != line.cend(); itr++) //go through array with iterator
    {
      if(charMap.count(*itr)) //map contains key
        charMap[*itr]++; //increment value at key index
      else
      {
        //cout << "*itr is: " << *itr << endl;
        std::pair<char, int> character(*itr, 1); //make a pair
        charMap.insert(character); //insert pair into map
      }
    }//end for

    string grab; //word in stream
    sPos = 0, ePos = 0; //start and end index
    while(word >> grab)
    {
      for(auto & x: grab)
        x = tolower(x);
      while(sPos + 1 <= grab.size() && ePos + 1 <= grab.size()) //while still in bounds
      {
        //cout << "inside while #2" << endl;
        if(isalpha(grab[sPos])) //if index is a letter
        {
          //while inside bounds and next token is a letter
          while(ePos + 1 <= grab.size() && isalpha(grab[ePos+1]))
          {
            ePos++; //move until end of word is reached
          }
          int size = ePos - sPos; //size for substring
          size++; //account for last index
          string check = grab.substr(sPos, size); //store word
          //cout << "Check is: " << check << endl;
          if(stringMap.count(check)) //if key is in map
          {
            stringMap[check]++; //increase value
            ePos++; //move to next index
            sPos = ePos; //start and end are in same location
          }
          else //not in map
          {
            std::pair<std::string, int> w(check, 1); //make a pair
            stringMap.insert(w); //insert pair into map
            ePos++;
            sPos = ePos;
          }
        }//end check for words
        else if(isdigit(grab[sPos])) //token is a number
        {
          while(ePos + 1 <= grab.size() && isdigit(grab[ePos+1]))
            ePos++;
          int size = ePos - sPos;
          size++; //account for last index
          if(numMap.count(grab.substr(sPos, size)))
          {
            numMap[grab.substr(sPos, size)]++;
            ePos++;
            sPos = ePos;
          }
          else
          {
            std::pair<std::string, int> number(grab.substr(sPos, size), 1); //make a pair
            numMap.insert(number); //insert pair into map
            ePos++;
            sPos = ePos;
          }
        }
        else if(!isalpha(grab[sPos]) && !isdigit(grab[sPos]))
        {
          ePos++;
          sPos = ePos;
        }
      }//end while#2
      sPos = 0; //reset psoitions for new word
      ePos = 0;
    }//end while#1
  }//end while

  //change vector to deque and use push front
  for(auto x : charMap)
    v1.push_back(x);
  std::stable_sort(v1.begin(), v1.end(), [](const auto& p1, const auto& p2)
  {return p1.second > p2.second;});

  for(auto x : stringMap)
    v2.push_back(x);
  std::stable_sort(v2.begin(), v2.end(), [](const auto& p1, const auto& p2)
  {return p1.second > p2.second;});

  for(auto x : numMap)
    v3.push_back(x);
  std::stable_sort(v3.begin(), v3.end(), [](const auto& p1, const auto& p2)
  {return p1.second > p2.second;});

  if(v1.size() > 10)
  {
    cout << "Total "<< v1.size() << " different characters, " << " 10 most used characters\n";
    for(int i = 0; i < 10; i++)
      cout << "No. " << i << ": " << v1[i].first << "\t" << v1[i].second << endl;
  }
  else
  {
    cout << "Total "<< v1.size() << " different characters, " << v1.size() << " most used characters\n";
    for(int i = 0; i < v1.size(); i++)
      cout << "No. " << i << ": " << v1[i].first << "\t" << v1[i].second << endl;
  }

  printResults(v2, "words");
  printResults(v3, "numbers");
}
