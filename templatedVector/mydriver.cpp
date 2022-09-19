//Name: Jose Brouwer
//Section: 5
#include <iostream>
#include <string>

#include "tvector.h"

using namespace std;

template <typename T>
void PrintList(const TVector<T>& v, string label)
{
   cout << label << " size is: " << v.GetSize() << "\n"
        << label << " = ";
   v.Print(cout);
   cout << "\n\n";
}

int main()
{
  TVector<int> v1; //testing default constructor w//ints
  TVector<double> v2(5.5, 5); //testing constructor with parameters w/ doubles
  PrintList(v1, "v1"); //testing GetSize and Print
  PrintList(v2, "v2"); //Also tests copy constructor when passing in label by value
  if(v1.IsEmpty()) //Testing IsEmpty on v1
    cout << "V1 is empty \n";
  else
    cout << "V1 is NOT empty \n";
  cout << "Testing Clear on v2 \n";
  v2.Clear(); //Testing clear
  if(v2.IsEmpty()) //Testing IsEmpty on v2
    cout << "V2 is empty \n";
  else
    cout << "V2 is NOT empty \n";
  PrintList(v2, "v2");
  TVector<char> v3('a', 5); //creating vector of chars
  PrintList(v3, "v3");
  TVector<char> v4 = v3; //Testing Copy Assignment Operator
  PrintList(v4, "v4");
  v3.InsertBack('b'); //INSERTBACK TEST 1
  PrintList(v3, "v3");
  TVector<char> v5(v3);//Testing move constructor
  PrintList(v5, "v5");
  v5 = v4 + v3; //Testing Move assignment and operator+
  PrintList(v5, "v5");
  for (int i = 0; i < 10; i++) //Populate v1
    v1.InsertBack(i); //INSERTBACK TEST 2
  TVector<int> v6(10, 5);
  v1 = v1 + v6; //testing on ints
  PrintList(v1, "v1");
  int first = v1.GetFirst(); //Testing GetFirst
  cout << "Using GetFirst on v1 returns: " << first << '\n';
  int last = v1.GetLast(); //Testing GetLast
  cout << "Using GetLast on v1 returns: " << last << '\n';
  cout << "calling InsertBack on v2 which is empty: \n";
  v2.InsertBack(0.1); //INSERTBACK TEST 3
  PrintList(v2, "v2");
  cout << "calling RemoveBack on v2: \n";
  v2.RemoveBack(); //REMOVEBACK TEST1
  PrintList(v2, "v2");
  cout << "calling InsertBack on v5 twice, adding letters c and d: \n";
  v5.InsertBack('c'); //INSERTBACK TEST 4
  v5.InsertBack('d'); //INSERTBACK TEST 5
  PrintList(v5, "v5");
  TVector<string> v7; //creating vector of strings
  cout << "calling InsertBack on a vector of type string: \n";
  v7.InsertBack("Hello"); //INSERTBACK TEST 6
  v7.InsertBack("There"); //INSERTBACK TEST 7
  for(int i = 0; i < 3; i++)
    v7.InsertBack("!"); //INSERTBACK TEST 8, 9, and 10
  PrintList(v7, "v7");
  cout << "All 10 tests for InsertBack have been made... \n";
  cout << "calling RemoveBack on v7 leaving Hello inside: \n";
  for(int i = 0; i < 4; i++)
    v7.RemoveBack(); //REMOVEBACK TESTS 2 - 5
  PrintList(v7, "v7");
  cout << "calling RemoveBack on v5 to get rid of d, c, and b: \n";
  cout << "Vector before RemoveBack: \n";
  PrintList(v5, "v5");
  for(int i = 0; i < 3; i++)
    v5.RemoveBack(); //REMOVEBACK TESTS 6-8
  cout << "Vector after RemoveBack: \n";
  PrintList(v5, "v5");
  cout << "calling RemoveBack on v1 to get rid of the 10s: \n";
  cout << "Vector before RemoveBack: \n";
  PrintList(v1, "v1");
  for(int i = 0; i < 5; i++)
    v1.RemoveBack(); //REMOVEBACK TESTS 8-13
  cout << "Vector after RemoveBack: \n";
  PrintList(v1, "v1");
  cout << "All 10 tests for RemoveBack have been made... \n";
  cout << "testing setCapacity on v1 to shrink the vector: \n";
  v1.SetCapacity(4); //Tetsing shrinking case of SetCapacity
  PrintList(v1, "v1");
  cout << "Setting v1's capacity to 10 after shrinking: \n";
  v1.SetCapacity(10); //Testing normal case of SetCapacity
  PrintList(v1, "v1");
  cout << "testing Insert with GetIterator on v5: \n";
  cout << "v5 before Insert: \n";
  PrintList(v5, "v5");
  TVectorIterator<char> charItr = v5.GetIterator(); //Testing GetIterator
  for(int i = 0; i < 3; i++)
  {
    v5.Insert(charItr, 'b'); //INSERT TESTS 1-3
    charItr.Next();
    charItr.Next(); //Testing next to place b inbetween a's
  }
  cout << "v5 after Insert: \n";
  PrintList(v5, "v5");
  cout << "testing HasNext and HasPrevious with GetIteratorEnd on v1: \n";
  TVectorIterator<int> intItr = v1.GetIteratorEnd();
  if(intItr.HasNext()) //Testing HasNext
    cout << "There is a next item \n";
  else
    cout << "There is no next item \n";
  if(intItr.HasPrevious())
    cout << "There is a previous item \n";
  else
    cout << "There is no previous item \n";
  cout << "testing Insert with GetIteratorEnd on v1: \n";
  cout << "v1 pre inserts: \n";
  PrintList(v1, "v1");
  for(int i = 0; i < 3; i++)
  {
    v1.Insert(intItr, 0); //INSERT TESTS 4-6
    intItr.Previous(); //Testing Previous to place 0s inbetween integers
  }
  cout << "v1 post inserts: \n";
  PrintList(v1, "v1");
  TVectorIterator<string> strItr = v7.GetIterator();
  cout << "Repopulating v7 for insert tests... \n";
  v7.InsertBack("There");
  cout << "v7 pre inserts: \n";
  PrintList(v7, "v7");
  for(int i = 0; i < 4; i++)
    v7.Insert(strItr, "!"); //INSERT TESTS 7-10
  cout << "v7 after inserting !!!! at the start: \n";
  PrintList(v7, "v7");
  cout << "All 10 tests for Insert have been made... \n";
  cout << "Testing remove(1 parameter): \n";
  cout << "v1 before removes: \n";
  PrintList(v1, "v1");
  for(int i = 0; i < 3; i++)
  {
    v1.Remove(intItr); //REMOVE TESTS 1-3
    intItr.Next(); //Moves next to remove all numbers other than 0
  }
  cout << "v1 after removes: \n";
  PrintList(v1, "v1");
  cout << "Testing remove(1 parameter) on v5: \n";
  PrintList(v5, "v5");
  cout << "iterator index is at: " << charItr.GetIndex() << "\n";
  for(int i = 0; i < 4; i++)
    v5.Remove(charItr); //REMOVE TESTS 4-7
  cout << "v5 should've removed 4 a's from the end: \n";
  PrintList(v5, "v5");
  PrintList(v2, "v2");
  cout << "repopulating v2 to test remove on doubles...\n";
  for(int i = 0; i < 3; i++)
  {
    v2.InsertBack(11.76);
    v2.InsertBack(9.99);
  }
  PrintList(v2, "v2");
  TVectorIterator<double> dblItr = v2.GetIterator();
  for(int i = 0; i < 4; i++)
    v2.Remove(dblItr); //REMOVE TESTS 8-10
  cout << "v2 should've removed the first 4 items: \n";
  PrintList(v2, "v2");
  cout << "iterator index is at: " << dblItr.GetIndex() << "\n";
  cout << "All 10 tests for Remove(1 param) have been made... \n";
  cout << "Testing remove(range): \n";
  cout << "v5 before removes: \n";
  PrintList(v5, "v5");
  TVectorIterator<char> charItr2 = v5.GetIterator();
  charItr.Previous();
  v5.Remove(charItr2, charItr); //REMOVE(2) TEST1
  cout << "v5 after removes: \n"; //removed b a b a b
  PrintList(v5, "v5");
  cout << "iterator index is at: " << charItr.GetIndex() << "\n";
  cout << "iterator2 index is at: " << charItr2.GetIndex() << "\n";
  charItr.Previous();
  charItr.Previous();
  charItr.Previous();
  cout << "iterator index is at: " << charItr.GetIndex() << "\n";
  v5.Remove(charItr2, charItr); //removing the rest of the vector items in pairs
  PrintList(v5, "v5"); //REMOVE(2) TEST 2
  v5.Remove(charItr2, charItr);//REMOVE(2) TEST 3
  PrintList(v5, "v5");
  cout << "adding an item to v2...\n";
  v2.InsertBack(10.01);
  PrintList(v2, "v2");
  TVectorIterator<double> dblItr2 = v2.GetIterator();
  dblItr2.Next();
  dblItr2.Next();
  v2.Remove(dblItr, dblItr2); //Remove(2) TEST 4
  cout << "v2 after removes: \n";
  PrintList(v2, "v2");
  cout << "creating a vector of ints...\n";
  TVector<int> v8(10, 10);
  PrintList(v8, "v8");
  TVectorIterator<int> v8Itr = v8.GetIterator();
  TVectorIterator<int> v8Itr2 = v8.GetIterator();
  v8Itr2.Next();
  v8Itr2.Next();
  v8Itr2.Next();
  v8Itr2.Next(); //index 4
  v8.Remove(v8Itr, v8Itr2); //Remove(2) TEST 5
  cout << "v8 after Remove(2): \n";
  PrintList(v8, "v8");
  cout << "Removing again...\n";
  v8.Remove(v8Itr, v8Itr2); //Remove(2) TEST 6
  PrintList(v8, "v8");
  PrintList(v3, "v3");
  TVectorIterator<char> v3Itr = v3.GetIterator();
  TVectorIterator<char> v3Itr2 = v3.GetIterator();
  v3Itr2.Next();
  v3Itr2.Next();
  v3Itr2.Next(); //index 3
  v3.Remove(v3Itr, v3Itr2); //Remove(2) TEST 7
  PrintList(v3, "v3");
  v3Itr2.Previous();
  v3.Remove(v3Itr, v3Itr2); //Remove(2) TEST 8
  PrintList(v3, "v3");
  cout << "creating vector of strings... \n";
  TVector<string> v9("wow", 6);
  PrintList(v9, "v9");
  TVectorIterator<string> v9Itr = v9.GetIterator();
  TVectorIterator<string> v9Itr2 = v9.GetIterator();
  v9Itr2.Next();
  v9Itr2.Next();
  v9Itr2.Next(); //index 3
  v9.Remove(v9Itr, v9Itr2); //Remove(2) TEST 9, removes half
  PrintList(v9, "v9");
  v9.Remove(v9Itr, v9Itr2); //Remove(2) TEST 10, removes remaining half
  PrintList(v9, "v9");
  cout << "All 10 tests for Remove(2 param) have been made... \n";
  TVector<int> v10(1, 5);
  PrintList(v10, "v10");
  cout << "Traversing v10 front to back... \n";
  TVectorIterator<int> v10Itr = v10.GetIterator();
  for(int i = 0; i <= 4; i++)
  {
    cout << "iterator index is at: " << v10Itr.GetIndex() << "\n";
    v10Itr.Next();
  }
  PrintList(v10, "v10");
  TVectorIterator<int> v10Itr2 = v10.GetIteratorEnd();
  cout << "Traversing v10 back to front... \n";
  for(int i = 0; i < 5; i++)
  {
    cout << "iterator index is at: " << v10Itr2.GetIndex() << "\n";
    v10Itr2.Previous();
  }
  PrintList(v10, "v10");
  cout << "All tests concluded...\n";

}
