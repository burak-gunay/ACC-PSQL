#include "exerciser.h"
#include <fstream>
#include <string>
void drop_if(connection *C) {
  work W(*C);
  const char *drop_if =
      "DROP TABLE IF EXISTS team;\nDROP TABLE IF EXISTS state;\nDROP TABLE IF "
      "EXISTS player;\nDROP TABLE IF EXISTS color;";
  W.exec(drop_if);
  W.commit();
}
void generate_tables(connection *C) {
  const char *color_table =
      "CREATE TABLE COLOR(COLOR_ID SERIAL PRIMARY KEY NOT "
      "NULL, NAME TEXT NOT NULL);";
  const char *state_table = "CREATE TABLE STATE(STATE_ID SERIAL PRIMARY KEY "
                            "NOT NULL ,NAME CHAR(2));";
  const char *team_table =
      "CREATE TABLE TEAM(TEAM_ID SERIAL PRIMARY KEY NOT NULL, NAME "
      "VARCHAR(20), "
      "STATE_ID INT, COLOR_ID INT, WINS INT, LOSSES INT);";
  const char *player_table =
      "CREATE TABLE PLAYER(PLAYER_ID SERIAL PRIMARY KEY NOT NULL,TEAM_ID "
      "INT,UNIFORM_NUM INT, FIRST_NAME VARCHAR(40), LAST_NAME VARCHAR(40),MPG "
      "INT, PPG INT, RPG INT, APG INT,SPG DECIMAL(18,1), BPG DECIMAL(18,1));";
  work W(*C);
  W.exec(player_table);
  W.exec(team_table);
  W.exec(state_table);
  W.exec(color_table);
  W.commit();
}
void swap_space(string &curr_str) {
  size_t i = curr_str.find_first_of(" ");
  while (i != string::npos) {
    // i is index of " " found
    curr_str[i] = ',';
    i = curr_str.find_first_of(" ", i + 1);
  }
  // Insert comma at end, remove later. Helps with parsing
  curr_str.push_back(',');
}
void insert_apos(string &curr_str, size_t apos_index) {
  size_t comma_ind = curr_str.find_first_of(",");
  while (apos_index > 0) {
    comma_ind = curr_str.find_first_of(",", comma_ind + 1);
    apos_index--;
  } // might cause problem here, can debug
  // Now, insert the apos
  curr_str.insert(curr_str.begin() + comma_ind + 1, '\''); // insert apos
  size_t seccomma_ind = curr_str.find_first_of(",", comma_ind + 1);
  curr_str.insert(curr_str.begin() + seccomma_ind, '\'');
}
void inserttable_color(ifstream &color_file, connection *C) {
  string temp;
  work W(*C);
  const char *insert_color = "INSERT INTO COLOR (NAME) VALUES (";
  const char *finish_str = ");";
  while (!color_file.eof()) {
    getline(color_file, temp);
    if (temp.size() != 0) { // might pass empty string due to getline
      swap_space(temp);
      if (temp.find_first_of("'") != string::npos) {
        size_t ind = temp.find_first_of("'");
        // If already an apos, add one more to escape in SQL
        temp.insert(temp.begin() + ind, '\''); // Hardcoded, can change
      }
      insert_apos(temp, 0);
      temp.pop_back(); // get rid of the , at the end
                       // cout << temp;
      size_t comma_ind = temp.find_first_of(",");
      temp.erase(0, comma_ind + 1);
      W.exec(insert_color + temp + finish_str);
      // cout << insert_color + temp + finish_str;
      temp.clear();
    }
  }
  W.commit();
}
void inserttable_state(ifstream &state_file, connection *C) {
  string temp;
  work W(*C);
  const char *insert_state = "INSERT INTO STATE (NAME) VALUES (";
  const char *finish_str = ");";
  while (!state_file.eof()) {
    getline(state_file, temp);
    if (temp.size() != 0) { // might pass empty string due to getline
      swap_space(temp);
      if (temp.find_first_of("'") != string::npos) {
        size_t ind = temp.find_first_of("'");
        // If already an apos, add one more to escape in SQL
        temp.insert(temp.begin() + ind, '\''); // Hardcoded, can change
      }
      insert_apos(temp, 0);
      temp.pop_back(); // get rid of the , at the end
                       // cout << temp;
      size_t comma_ind = temp.find_first_of(",");
      temp.erase(0, comma_ind + 1);
      W.exec(insert_state + temp + finish_str);
      // cout << insert_color + temp + finish_str;
      temp.clear();
    }
  }
  W.commit();
}
void inserttable_player(ifstream &player_file, connection *C) {
  string temp;
  work W(*C);
  const char *insert_player = "INSERT INTO PLAYER "
                              "(TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_"
                              "NAME,MPG,PPG,RPG,APG,SPG,BPG) VALUES (";
  const char *finish_str = ");";
  while (!player_file.eof()) {
    getline(player_file, temp);
    if (temp.size() != 0) { // might pass empty string due to getline
      swap_space(temp);
      if (temp.find_first_of("'") != string::npos) {
        size_t ind = temp.find_first_of("'");
        // If already an apos, add one more to escape in SQL
        temp.insert(temp.begin() + ind, '\''); // Hardcoded, can change
      }
      // This way, escape apos
      insert_apos(temp, 2);
      insert_apos(temp, 3);
      temp.pop_back(); // get rid of the , at the end
                       // cout << temp;
      size_t comma_ind = temp.find_first_of(",");
      temp.erase(0, comma_ind + 1);
      W.exec(insert_player + temp + finish_str);
      // cout << insert_player + temp + finish_str << endl;
      temp.clear();
    }
  }
  W.commit();
}
void inserttable_team(ifstream &team_file, connection *C) {
  string temp;
  work W(*C);
  const char *insert_team =
      "INSERT INTO TEAM (NAME,STATE_ID,COLOR_ID,WINS,LOSSES) VALUES (";
  const char *finish_str = ");";
  while (!team_file.eof()) {
    getline(team_file, temp);
    if (temp.size() != 0) { // might pass empty string due to getline
      swap_space(temp);
      if (temp.find_first_of("'") != string::npos) {
        size_t ind = temp.find_first_of("'");
        // If already an apos, add one more to escape in SQL
        temp.insert(temp.begin() + ind, '\''); // Hardcoded, can change
      }
      // This way, escape apos
      insert_apos(temp, 0);
      temp.pop_back(); // get rid of the , at the end
                       // cout << temp;
      size_t comma_ind = temp.find_first_of(",");
      temp.erase(0, comma_ind + 1);
      W.exec(insert_team + temp + finish_str);
      // cout << insert_team + temp + finish_str << endl;
      temp.clear();
    }
  }
  W.commit();
}
void read_files(connection *C) {

  ifstream state_file("state.txt");   // index 0
  ifstream color_file("color.txt");   // index 1
  ifstream team_file("team.txt");     // index 2
  ifstream player_file("player.txt"); // index 3
  if (!player_file.is_open() || !team_file.is_open() || !state_file.is_open() ||
      !color_file.is_open()) {
    cout << "Couldn't open a filestream, issue!" << endl;
  }
  inserttable_color(color_file, C);
  inserttable_state(state_file, C);
  inserttable_player(player_file, C);
  inserttable_team(team_file, C);
  // Now, need to inser '' to the text ones.
}
void setup(connection *C) {
  drop_if(C);
  generate_tables(C);
  read_files(C);
  // Now, read tables and put them in
}
