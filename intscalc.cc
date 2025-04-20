#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <random>
#include <assert.h>
#include <stdlib.h>

//#define int int64_t
#define int int32_t
#include "lieonn.hh"
typedef myfloat num_t;

using std::cout;
using std::cerr;
using std::endl;
using std::atoi;
using std::string;
using std::to_string;
using std::vector;
using std::sort;
using std::binary_search;
using std::make_pair;
using std::istringstream;

#undef int
int main(int argc, const char* argv[]) {
  assert(2 < argc);
  SimpleMatrix<num_t> m;
  std::cin >> m;
  // N.B. mleft == - mright.
  SimpleMatrix<num_t> mleft(m.rows(), argc - 2);
  SimpleMatrix<num_t> mright(m.rows(), m.cols() - (argc - 2));
  auto nidx(std::atoi(argv[2]));
  for(int i = 0, j = 0, k = 0, n = 3; i < m.cols(); i ++) {
    if(nidx == i) {
      mleft.setCol(j ++, m.col(i));
      nidx = std::atoi(argv[n ++]);
    } else mright.setCol(k ++, m.col(i));
  }
  const auto recur(std::atoi(argv[1]));
  SimpleMatrix<num_t> noised(mright.cols(), recur);
  for(int i = 0; i < noised.rows(); i ++)
    for(int j = 0; j < noised.cols(); j ++)
      noised(i, j) = num_t(arc4random_uniform(0x20001)) / num_t(0x20000);
  mright = mright * noised;
  auto res(mright.col(0));
  for(int i = 1; i < mright.cols(); i ++)
    res += mright.col(i);
  mright.resize(0, 0);
  std::cout << (res = mleft.solve(res));
  return 0;
 usage:
  cerr << "Usage:" << endl;
  cerr << argv[0] << " <recur> <state index to get 0> ..." << std::endl;
  cerr << "   state index should be applied as ascendant order." << std::endl;
  return - 1;
}

