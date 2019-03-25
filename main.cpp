#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"
#include "setup.h"

using namespace std;
using namespace pqxx;

int main(int argc, char *argv[]) {

  // Allocate & initialize a Postgres connection object
  connection *C;

  try {
    // Establish a connection to the database
    // Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd ");
    if (C->is_open()) {
      // cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e) {
    cout << "Caught error" << endl;
    cerr << e.what() << std::endl;
    return 1;
  }

  // TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL
  // database
  //      load each table with rows from the provided source txt files
  setup(C);
  exercise(C);

  // Close database connection
  C->disconnect();

  return 0;
}
