#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
#include "SMinstr.cpp"
#include <string>
using namespace egre246;
struct Node{
  int dat;
  Node *next;
};
class Stack{
  public:
    Stack();
    ~Stack();
    void push(int);
    int pop();
    bool isEmpty();
    void clr();
    void neg();
    void dup();
    void swap();
    void add();
    void sub();
    void mul();
    void div();
    void ldc(int);
    void out();
    void dbg();
    void tra();
    void halt();
  private:
    Node *top;
};
Stack::Stack(){
  top = NULL;
}
Stack::~Stack(){

}
void Stack::push(int a){
  Node *temp = new Node;
  temp->dat = a;
  temp->next = top;
  top = temp;
}
int Stack::pop(){
  if(!isEmpty()){
    int b;
    b = top -> dat;
    Node *old = top;
    top = old->next;
    delete old;
    return b;
  }
  else{
    cout << "[error - empty stack]" << endl;
    exit(1);
  }
}
bool Stack::isEmpty(){
  return (top == NULL);
}
void Stack::clr(){
  while(!isEmpty()){
    pop();
  }
}
void Stack::neg(){
  int neg;
  neg = pop();
  neg = neg * -1;
  push(neg);
}
void Stack::dup(){
  int dupl;
  dupl = pop();
  push(dupl);
  push(dupl);
}
void Stack::swap(){
  int s1, s2;
  s1 = pop();
  s2 = pop();
  push(s1);
  push(s2);
}
void Stack::add(){
  int a, b, c;
  a = pop();
  b = pop();
  c = a + b;
  push(c);
}
void Stack::sub(){
  int a, b ,c;
  a = pop();
  b = pop();
  c = b - a;
  push(c);
}
void Stack::mul(){
  int a, b, c;
  a = pop();
  b = pop();
  c = a*b;
  push(c);
}
void Stack::div(){
  int a, b, c;
  a = pop();
  b = pop();
  if(b == 0){
    cout << "[error - division by zero]" << endl;
    halt();
  }
  c = a/b;
  push(c);
  //Check if b is zero and error check that
}
void Stack::ldc (int n){
  push(n);
  //check n
}

void Stack::out(){
  int a;
  a = pop();
  cout << "Output: " << a << endl;
}
void Stack::dbg(){
  string output;

  if(isEmpty()){
    output = output + "NULL";
  }
  else{
    Node *curr = top;
    while(curr != NULL){
      output = to_string(curr->dat) + output;
      if((curr->next) != NULL){
        output = "," + output;
      }
      curr = curr->next;
    }
  }
  output.insert(0,"DEBUG: [");
  output = output + "](top)";
  cout << output << endl;
}

void Stack::halt(){
  exit(1);
}

int main(int argc, char *argv[]){
    Stack stk;
    SMinstr a;
    int count = 0;
    int trace = -1;
    int halt = 0;
    int warn = 0;
    string s, file, val, valB;
    file = argv[1];
    std::ifstream infile(file);
    while(getline(infile,s)){
    istringstream iss(s);
    //cout << "Input: " << s << endl;
    while(true){
      string temp, tempB;
      iss >> temp;
      string whitespaces (" \t\f\v\n\r");
      size_t found = temp.find_last_not_of(whitespaces);
      // temp.erase(0,temp.find_first_not_of(' '));
      if (found!=std::string::npos){
        temp.erase(found+1);
      }
      else{
        continue;
      }


      //temp.erase(temp.find_last_not_of(' ') + 1);
      cout << temp << endl;
      if(temp == "%") break;
      for(int i = 0; i < temp.length(); i++)
       temp[i] = toupper(temp[i]);
      if(!a.isInstr(temp)){
        cout << "[error - illegal command '" << temp << "']" << endl;
        stk.halt();
      }
      //cout << temp << endl;

      a.setOpcode(temp);
      if (temp != "LDC"){
        break;
      }
      if(temp == "LDC"){
        if(iss.eof()){
          cout << "[warning - illegal input ignored]" << endl;
          warn = -1;
        }
        iss >> tempB;
        cout << tempB << endl;
        for(int i = 0; i < tempB.length(); i++)
         if(!isdigit(tempB[i])){
           cout << "[warning - illegal input ignored]" << endl;
           warn = -1;
         }
        valB = tempB;
        stk.dbg();
        break;
        //cout << valB << endl;
      }
      //cout << val << endl;
      if(iss.eof()) break;
    }
    if(trace == 1){
      if((a.toString(a.getOpcode()) =="LDC") && (warn != -1)){
        cout << "[trace - pc #" << count << ": " << a.toString(a.getOpcode()) << " " << valB << ']' << endl;
      }
      else{
        cout << "[trace - pc #" << count << ": " << a.toString(a.getOpcode()) << ']' << endl;
      }
    }
    if(a.toString(a.getOpcode()) == "LDC"){
      if(warn == -1){
        warn = 0;
      }
      else{
        // cout << "aaaaah" << endl;
        stk.push(stoi(valB));
      }
      stk.dbg();
      //cout << "I'm a winner" << endl;
      //cout << stoi(valB) << endl;
      //stk.dbg();
    }
    else if(a.toString(a.getOpcode()) == "CLR"){
      stk.clr();
    }
    else if(a.toString(a.getOpcode()) == "NEG"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.neg();
    }
    else if(a.toString(a.getOpcode()) == "DUP"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.dup();
    }
    else if(a.toString(a.getOpcode()) == "SWAP"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.swap();
    }
    else if(a.toString(a.getOpcode()) == "ADD"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.add();
    }
    else if(a.toString(a.getOpcode()) == "SUB"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.sub();
    }
    else if(a.toString(a.getOpcode()) == "MUL"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.mul();
      stk.dbg();
    }
    else if(a.toString(a.getOpcode()) == "DIV"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.div();
    }
    else if(a.toString(a.getOpcode()) == "INP"){
      int input;
      cout << "input: ";
      cin >> input;
      stk.push(input);
    }
    else if(a.toString(a.getOpcode()) == "OUT"){
      if(stk.isEmpty()){
        cout << "[error - empty stack]" << endl;
        stk.halt();
      }
      stk.out();
    }
    else if(a.toString(a.getOpcode()) == "DBG"){
      stk.dbg();
    }
    else if(a.toString(a.getOpcode()) == "TRA"){
      trace = trace * -1;
    }
    else if(a.toString(a.getOpcode()) == "HALT"){
      halt = 1;
      if(trace == 1){
          cout << "[machine halted]" << endl;
      }
      stk.halt();
    }
    count +=1;
  }
  if(halt == 0){
    cout << "[warning - no HALT instruction]" << endl;
  }
  return 0;

}
