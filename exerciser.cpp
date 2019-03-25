#include "exerciser.h"
#include <fstream>
#include <string>
using namespace pqxx;
using namespace std;
void exercise(connection *C) {
  // asdda   U MIN MAX U  MIN MAX  U MIN MAX  U MIN MAX  U  MIN MAX U MIN MAX
  // query1(C, 1, 25, 40, 0, 3, 15, 0, 1, 7, 0, 1, 15, 0, 0.1, 0.4, 0, 0.2,
  // 0.8);
  string s1("Burak");
  string s2("Gunay");
  add_player(C, 3, 5, s1, s2, 10, 15, 10, 10, 0.5, 0.3);
  string s3("BurkinaFaso");
  add_team(C, s3, 4, 5, 20, 0);
  string s4("ZZ");
  add_state(C, s4);
  string s5("KizilOrdu");
  add_color(C, s5);
  string s6("Ja'Querhin");
  add_color(C, s6); // check if apos check works
  string s7("Black");
  // query2(C, s7);
  string s8("UNC");
  // query3(C, s8);
  string s9("NY");
  string s10("Orange");
  // query4(C, s9, s10);
  int num_wins = 10;
  query5(C, num_wins);
}
