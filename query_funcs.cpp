#include "query_funcs.h"

void add_player(connection *C, int team_id, int jersey_num, string first_name,
                string last_name, int mpg, int ppg, int rpg, int apg,
                double spg, double bpg) {
  work W(*C);
  stringstream temp;
  if (size_t ind = first_name.find_first_of("'") != string::npos) {
    // If already an apos, add one more to escape in SQL
    string temp2("'");
    first_name.insert(ind + 1, temp2); // SQL ' ESCAPE char
  }
  if (size_t ind = last_name.find_first_of("'") != string::npos) {
    // If already an apos, add one more to escape in SQL
    string temp2("'");
    last_name.insert(ind + 1, temp2); // SQL ' ESCAPE char
  }
  temp << "INSERT INTO PLAYER "
          "(TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_NAME,MPG,PPG,RPG,APG,SPG,BPG) "
          "VALUES (";
  // now, add values with , in between.
  temp << team_id << ',' << jersey_num << ',' << '\'' << first_name << '\''
       << ',' << '\'' << last_name << '\'' << ',' << mpg << ',' << ppg << ','
       << rpg << ',' << apg << ',' << spg << ',' << bpg << ");";
  W.exec(temp.str().c_str());
  W.commit();
}

void add_team(connection *C, string name, int state_id, int color_id, int wins,
              int losses) {
  work W(*C);
  stringstream temp;
  if (size_t ind = name.find_first_of("'") != string::npos) {
    // If already an apos, add one more to escape in SQL
    string temp2("'");
    name.insert(ind + 1, temp2); // SQL ' ESCAPE char
  }
  temp << "INSERT INTO TEAM (NAME,STATE_ID,COLOR_ID,WINS,LOSSES) VALUES (";
  temp << '\'' << name << '\'' << ',' << state_id << ',' << color_id << ','
       << wins << ',' << losses << ");";
  W.exec(temp.str().c_str());
  W.commit();
}

void add_state(connection *C, string name) {
  work W(*C);
  stringstream temp;
  if (size_t ind = name.find_first_of("'") != string::npos) {
    // If already an apos, add one more to escape in SQL
    string temp2("'");
    name.insert(ind + 1, temp2); // SQL ' ESCAPE char
  }
  temp << "INSERT INTO STATE(NAME) VALUES(";
  temp << '\'' << name << '\'' << ");";
  W.exec(temp.str().c_str());
  W.commit();
}

void add_color(connection *C, string name) {
  work W(*C);
  stringstream temp;
  if (size_t ind = name.find_first_of("'") != string::npos) {
    // If already an apos, add one more to escape in SQL
    string temp2("'");
    name.insert(ind + 1, temp2); // SQL ' ESCAPE char
  }
  temp << "INSERT INTO COLOR(NAME) VALUES(";
  temp << '\'' << name << '\'' << ");";
  W.exec(temp.str().c_str());
  W.commit();
}
void print_query(
    result &r) { // from libpqxx page(Get started), to print query result
  const int num_rows = r.size();
  for (int rownum = 0; rownum < num_rows; ++rownum) {
    const pqxx::tuple row = r[rownum];
    const int num_cols = row.size();
    for (int colnum = 0; colnum < num_cols; ++colnum) {
      const pqxx::field field = row[colnum];
      std::cout << field.c_str() << '\t';
    }
    std::cout << std::endl;
  }
}
void query1(connection *C, int use_mpg, int min_mpg, int max_mpg, int use_ppg,
            int min_ppg, int max_ppg, int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg, int use_spg, double min_spg,
            double max_spg, int use_bpg, double min_bpg, double max_bpg) {
  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG"
          "SPG BPG"
       << endl;
  if (use_mpg == 0 && use_ppg == 0 && use_rpg == 0 && use_apg == 0 &&
      use_spg == 0 && use_bpg == 0) {
    return;
  }
  const char *query_players = "SELECT * FROM PLAYER WHERE";
  stringstream temp;
  bool added_one = false;

  temp << query_players; // Not ideal way to solve it, but need to have this
                         // many if clauses.
  if (use_mpg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " MPG>=" << min_mpg << " AND MPG<=" << max_mpg;
    added_one = true;
  }
  if (use_ppg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " PPG>=" << min_ppg << " AND PPG<=" << max_ppg;
    added_one = true;
  }
  if (use_rpg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " RPG>=" << min_rpg << " AND RPG<=" << max_rpg;
    added_one = true;
  }
  if (use_apg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " APG>=" << min_apg << " AND APG<=" << max_apg;
    added_one = true;
  }
  if (use_spg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " SPG>=" << min_spg << " AND SPG<=" << max_spg;
    added_one = true;
  }
  if (use_bpg != 0) {
    if (added_one) {
      temp << " AND";
    }
    temp << " BPG>=" << min_bpg << " AND SPG<=" << max_bpg;
    added_one = true;
  }

  work W(*C);
  // Now, exec with this query
  result r = W.exec(temp.str().c_str());
  print_query(r);
}

void query2(connection *C, string team_color) {
  // SELECT team.name from team,color where team_color=color.name and team
  stringstream temp;
  cout << "NAME" << endl;
  work W(*C);
  temp << "SELECT TEAM.NAME FROM TEAM, COLOR WHERE "
       << "COLOR.NAME=" << '\'' << team_color << '\''
       << " AND COLOR.COLOR_ID=TEAM.COLOR_ID;";
  // cout << temp.str();
  result r = W.exec(temp.str().c_str());
  print_query(r);
}

void query3(connection *C, string team_name) {
  stringstream temp;
  cout << "FIRST_NAME LAST_NAME" << endl;
  work W(*C);
  temp << "SELECT PLAYER.FIRST_NAME,PLAYER.LAST_NAME FROM PLAYER,TEAM WHERE "
          "TEAM.NAME="
       << '\'' << team_name << '\''
       << " AND PLAYER.TEAM_ID=TEAM.TEAM_ID ORDER BY PLAYER.PPG ASC;";
  result r = W.exec(temp.str().c_str());
  print_query(r);
}

void query4(connection *C, string team_state, string team_color) {
  stringstream temp;
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  work W(*C);
  temp << "SELECT PLAYER.FIRST_NAME,PLAYER.LAST_NAME,PLAYER.UNIFORM_NUM FROM "
          "PLAYER,STATE,COLOR,TEAM WHERE STATE.NAME ="
       << '\'' << team_state << '\'' << " AND COLOR.NAME=" << '\'' << team_color
       << '\''
       << " AND TEAM.STATE_ID=STATE.STATE_ID AND TEAM.COLOR_ID=COLOR.COLOR_ID "
          "AND PLAYER.TEAM_ID=TEAM.TEAM_ID;";
  result r = W.exec(temp.str().c_str());
  print_query(r);
}
void query5(connection *C, int num_wins) {
  stringstream temp;
  cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
  work W(*C);
  temp << "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS "
          "FROM PLAYER,TEAM WHERE TEAM.WINS>"
       << num_wins << " AND PLAYER.TEAM_ID=TEAM.TEAM_ID;";
  result r = W.exec(temp.str().c_str());
  print_query(r);
}
