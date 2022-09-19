//Name: Jose Brouwer
#include <stack>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

class BET
{
  public:
    BET();
    BET(const string& postfix);
    BET(const BET&);
    ~BET();

    bool buildFromPostfix(const string& postfix);
    const BET & operator= (const BET &);

    void printInfixExpression();
    void printPostfixExpression();

    size_t size();
    size_t leaf_nodes();

    bool empty();
    bool operator()(const string& postfix);
  private:
    struct BinaryNode
    {
	    string element;
	    BinaryNode *left;
	    BinaryNode *right;

	    BinaryNode(const string &theElement, BinaryNode *lt, BinaryNode *rt)
		      : element{theElement}, left{lt}, right{rt} {}
	    BinaryNode(string && theElement, BinaryNode *lt, BinaryNode *rt)
		      : element{std::move(theElement)}, left{lt}, right{rt} {}
	  };
    void printInfixExpression(BinaryNode *n) const;
    void makeEmpty(BinaryNode* &t);

    BinaryNode * clone(BinaryNode *t);

    void printPostfixExpression(BinaryNode *n) const;

    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);

    bool l_lower( const BinaryNode* n) const;
    bool r_lower( const BinaryNode* n) const;
    bool rSame( const BinaryNode* n) const;

    stack<BinaryNode*> theStack;
    size_t numNodes;
    BinaryNode* root;
};
