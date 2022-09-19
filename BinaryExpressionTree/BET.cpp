//Name: Jose Brouwer
#include"BET.h"

BET::BET()
{
  numNodes = 0;
  root = nullptr;
}
BET::BET(const string& postfix) : root{nullptr}
{
  numNodes = 0;
  bool built = buildFromPostfix(postfix);
}
BET::BET(const BET& bet2) : root{nullptr}
{
  numNodes = 0;
  root = clone(bet2.root);
}
BET::~BET()
{
  makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix)
{
  if(operator()(postfix))
  {
    if(!empty())
      makeEmpty(root);
    stringstream word(postfix);
    string grab;
    while(word >> grab)
    {
      if(isdigit(grab[0]))
        theStack.push(new BinaryNode(grab, nullptr, nullptr));
      else if(isalpha(grab[0]))
        theStack.push(new BinaryNode(grab, nullptr, nullptr));
      else if((grab) == "+" || (grab) == "-" || (grab) == "*" || (grab) == "/")
      {
        BinaryNode* b = new BinaryNode(grab, nullptr, theStack.top()); //make node for operator
        theStack.pop(); //pop stack
        b->left = theStack.top(); //make operator left child other operand
        theStack.pop();
        theStack.push(b);
      }
      root = theStack.top(); //make the root  = operator
    }
    return true;
  }
  else if(postfix.size() == 1)
  {
    root = theStack.top();
    return true;
  }
  return false;
}
const BET & BET::operator= (const BET & bet2) //: root{nullptr}
{
  root = clone(bet2.root);
  return *this;
}

void BET::printInfixExpression()
{
  if(root != nullptr)
    printInfixExpression(root);
  cout << endl;
}
void BET::printPostfixExpression()
{
  if(root != nullptr)
    printPostfixExpression(root);
  cout << endl;
}

size_t BET::size()
{
  if(root != nullptr)
  {
    size(root);
    size_t ans = numNodes;
    numNodes = 0;
    return ans;
  }
  return 0;
}
size_t BET::leaf_nodes()
{
  if(root != nullptr)
  {
    leaf_nodes(root);
    size_t ans = numNodes;
    numNodes = 0;
    return ans;
  }
  return 0;
}

bool BET::empty()
{
  if(root == nullptr)
    return true;
  return false;
}
bool BET::operator()(const string& postfix)
{
  size_t numDig = 0;
  size_t ops = 0;
  stringstream word(postfix);
  string grab;
  while(word >> grab)
  {
    if(isdigit(grab[0]))
      numDig++;
    else if(isalpha(grab[0]))
      numDig++;
    else if((grab) == "+" || (grab) == "-" || (grab) == "*" || (grab) == "/")
    {
      ops++;
    }
  }
  if(ops == (numDig - 1))
    return true;
  else if(ops > numDig)
  {
    cout << "ERROR: Operators don't have corresponding operands..." << endl;
    return false;
  }
  else if(ops > numDig)
  {
    cout << "ERROR: Operands don't have corresponding operators..." << endl;
    return false;
  }
}

void BET::printInfixExpression(BinaryNode *n) const
{
  if(n != nullptr)
  {
      if(l_lower(n)) //if child has lower precedenece
      {
        //WE WANT THE CHILD AND ITS CHILDREN IN PARENTHESIS
        cout << "( ";
        printInfixExpression(n->left);
        cout << ") ";
        cout << n->element << " ";
        printInfixExpression(n->right);
      }
      else if(r_lower(n))
      {
        printInfixExpression(n->left);
        cout << n->element << " ";
        cout << "( ";
        printInfixExpression(n->right);
        cout << ") ";
      }
      else if(rSame(n)) //right child has same precendence
      {
        //WE WANT THE CHILD AND ITS CHILDREN IN PARENTHESIS
        printInfixExpression(n->left);
        cout << n->element << " ";
        cout << "( ";
        printInfixExpression(n->right);
        cout << ") ";
      }
      else
      {
        //REGULAR INFIX
        printInfixExpression(n->left);
        cout << n->element << " ";
        printInfixExpression(n->right);
      }
  }
}

void BET::makeEmpty(BinaryNode* &t)
{
  if(t != nullptr)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

typename BET::BinaryNode * BET::clone(BinaryNode *t)
{
  if(t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

void BET::printPostfixExpression(BinaryNode *n) const
{
  if(n->left != nullptr)
    printPostfixExpression(n->left); //go to left child
  if(n->right != nullptr)
    printPostfixExpression(n->right); //go to right child
  cout << n->element << " "; //no more children, print myself
}

size_t BET::size(BinaryNode *t)
{
  if(t == nullptr)
    return 0;
  else
  {
    numNodes++; //root node and subsequent nodes
    size(t->left); //go to left child
    size(t->right); //go to right child
  }
  return numNodes;
}
size_t BET::leaf_nodes(BinaryNode *t)
{
  if(t == nullptr)
    return 0;
  else
  {
    if(t->left == nullptr || t->right == nullptr)
      numNodes++;
    leaf_nodes(t->left);
    leaf_nodes(t->right);
  }
  return numNodes;
}

bool BET::l_lower( const BinaryNode* n) const //check for lower precedence in children
{
  if((n->element == "*" || n->element == "/") && (n->left->element == "+"
  || n->left->element == "-" ))
  {
    return true;
  }
}
bool BET::r_lower(const BinaryNode* n) const //check for lower precedence in children
{
  if((n->element == "*" || n->element == "/") && (n->right->element == "+"
  || n->right->element == "-"))
  {
    return true;
  }
}
bool BET::rSame( const BinaryNode* n) const //check for same precedence in right child
{
  if((n->element == "*" || n->element == "/") && (n->right->element == "*"
  || n->right->element == "/"))
  {
    return true;
  }
  else if((n->element == "+" || n->element == "-") && (n->right->element == "+"
  || n->right->element == "-"))
  {
    return true;
  }
}
