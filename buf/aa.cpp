#include <bits/stdc++.h>
using namespace std;

int main() {
  regex e("abc*");
  bool m = regex_search("abccc", e);

  // 输出 yes
  cout << (m ? "yes" : "no") << endl;
}
