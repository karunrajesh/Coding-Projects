// D. Resler 11/18
// requires C++11 (compiling with "-std=c++11" using g++)

#define NOTHING -1 /*must be < 0 as it can't be opcode value!*/
#define NUM_OPCODES 26 /*count of class opc's opcodes array defined below*/
using namespace std;
namespace egre246 {

class SMinstr{
 private:
  int label, opcode, operand;

//-------------------------------------------------------------
  class opc {
  public:
    /* To add opcodes to the machine:
       (1) add the code string to the array below
       (2) update the definition of NUM_OPCODES above
           (necessary to define because of C++ rules on initializing entities)
       (3) update hasOperand/hasLabel below as appropriate
    */
    string opcodes[NUM_OPCODES]=
      { // part 1 opcodes
        "CLR","HALT","NEG","DUP","ADD","SUB","MUL","DIV","LDC",        /* count:  9 */
        "INP","OUT","DBG","TRA","SWAP",                                /* count:  5 */
        // part 2 opcodes
        "LDA","STO","EQ","LESS","GTR","NOT","JMP","JMPZ","NOP",        /* count:  9 */
        // part 3 opcodes
        "CALL","RET","ARGS" };                                         /* count:  3 */
  };
//-------------------------------------------------------------

  static string ots(int i) {
    if(i<0 || i>=NUM_OPCODES) return "ILLEGAL";
    return (new opc)->opcodes[i];
  }

  static int sto(string s) {
    transform(s.begin(),s.end(),s.begin(),::toupper);
    opc codes;
    for(int i=0; i< NUM_OPCODES; i++) if(codes.opcodes[i]==s) return i;    return NOTHING;
  }

//================================================================
 public:
  SMinstr() { opcode = NOTHING; operand = NOTHING; label = NOTHING; }
  SMinstr(int op, int rand) { opcode = op; operand = rand; label = NOTHING;}
  SMinstr(int op) { opcode = op; operand = NOTHING; label = NOTHING; }
  SMinstr(const SMinstr& i) { opcode = i.opcode; operand = i.operand; label = i.label; }
  ~SMinstr() {}

  // getters/setters
  int getOpcode() const { return opcode; }
  int getOperand() const { return operand; }
  int getLabel() const { return label; }
  void setOpcode(int op) { opcode = op; }
  void setOpcode(string s) { opcode = sto(s); }
  void setOperand(int op) { operand = op; }
  void setLabel(int l) { label = l; }

  string toString() const {
    string s = "";
    if (hasLabel(opcode)) s = to_string(label)+": ";
    s += ots(opcode);
    if(hasOperand(opcode)) s += (" " + to_string(operand));
    return s;
  }

  // static routines
  static bool hasOperand(int n) {
    return (n==toOpcode("LDC")||n==toOpcode("LDA")||n==toOpcode("STO")||
            n==toOpcode("JMP")||n==toOpcode("JMPZ")||n==toOpcode("CALL"));
  }
  static bool hasLabel(int n) { return (n==toOpcode("NOP")); }

  static int numOpCodes() { return NUM_OPCODES; }
  static bool isInstr(string s) { return (toOpcode(s) != NOTHING); }
  static string toString(int n) { return ots(n); }
  static int toOpcode(string s) { return sto(s); }
  friend std::ostream& operator <<(std::ostream& os, const SMinstr& i){
    os << i.toString();
    return os;
  }

}; // class

}  // namespace
