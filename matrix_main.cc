#include <map>
#include <string>
#include <cstdlib>
#include "matrix.h"

typedef Matrix<double> DoubleMatrix;

bool ParseMatrix(const map<string, DoubleMatrix>& matrices, const string& str,
                 DoubleMatrix* mat) {
  bool negate = false, transpose = false;
  string name = str;

  for(size_t i=0;i<name.length();i++)
  {
      if(name[i] == '-')
      {
          negate = true;
          name = name.substr(i+1, name.npos);
      }
      if(name[i] == '\'')
      {
          transpose = true;
          name = name.substr(0, i);
      }
  }

  //   str="-a" => negate=true, transpose=false, name="a"
  //   str="b'" => negate=false, transpose=true, name="b"
  //   str="-c'" => negate=true, transpose=true, name="c"
  //   str="d" => negate=false, transpose=false, name="d"

  map<string, DoubleMatrix>::const_iterator it = matrices.find(name);
  if (it == matrices.end()) return false;
  *mat = negate ? -it->second : it->second;
  if (transpose) *mat = mat->Transpose();
  return true;
}

int main() {
  map<string, DoubleMatrix> matrices;
  string cmd;
  while (cmd != "quit") {
    cin >> cmd;
    if (cmd == "matrix") {
      string name;
      DoubleMatrix mat;
      cin >> name >> mat;
      matrices[name] = mat;
      cout << name << ":" << endl << mat;
    } else if (cmd == "list") {
      for (map<string, DoubleMatrix>::const_iterator it = matrices.begin();
           it != matrices.end(); ++it) {
        cout << it->first << " "
             << it->second.rows() << " " << it->second.cols() << endl;
      }
    } else if (cmd == "print") {
      string str;
      cin >> str;
      DoubleMatrix mat;
      if (ParseMatrix(matrices, str, &mat)) cout << mat;
      else cout << atoi(str.c_str()) << endl;
    } else if (cmd == "eval") {
      string lhs, op, rhs;
      cin >> lhs >> op >> rhs;
      DoubleMatrix lmat, rmat;
      bool left = ParseMatrix(matrices, lhs, &lmat);
      bool right = ParseMatrix(matrices, rhs, &rmat);
      int lval = left ? 0 : atoi(lhs.c_str());
      int rval = right ? 0 : atoi(rhs.c_str());
      if (left && right) {
        if (op == "+") cout << (lmat + rmat);
        else if (op == "-") cout << (lmat - rmat);
        else if (op == "*") cout << (lmat * rmat);
        else cout << "Invalid operator " << op << endl;
      } else if (left) {
        if (op == "+") cout << (lmat + rval);
        else if (op == "-") cout << (lmat - rval);
        else if (op == "*") cout << (lmat * rval);
        else cout << "Invalid operator " << op << endl;
      } else if (right) {
        if (op == "+") cout << (lval + rmat);
        else if (op == "-") cout << (lval - rmat);
        else if (op == "*") cout << (lval * rmat);
        else cout << "Invalid operator " << op << endl;
      } else {
        if (op == "+") cout << (lval + rval) << endl;
        else if (op == "-") cout << (lval - rval) << endl;
        else if (op == "*") cout << (lval * rval) << endl;
        else cout << "Invalid operator " << op << endl;
      }
    }
  }
  return 0;
}
