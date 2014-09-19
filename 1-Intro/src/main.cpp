//
//  main.cpp
//
//  Systems Software, WS14, UZH Zurich
//
//  Exercise 1 - Introduction
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "employeerecord.h"

int main(int argc, const char* argv[])
{
  if (argc != 2) {
    std::cout << "Wrong argument!\n";
    return 1;
  }

  std::ifstream input_file_stream(argv[1]);

  std::vector<EmployeeRecord> employees;

  std::string line;
  std::string _first_name, _last_name;
  long _yearly_salary;
  int _age, _clearance_level;
  while (std::getline(input_file_stream, line))
  {
    std::istringstream iss(line);

    if (!(iss >> _last_name >> _first_name >> _yearly_salary >> _age >> _clearance_level)) { break; } // error

    employees.push_back(EmployeeRecord(_last_name, _first_name, _yearly_salary, _age, _clearance_level));
  }
  input_file_stream.close();

  std::sort(employees.begin(), employees.end());

  /*
  Only for the TA
  std::ofstream output_stream("sorted_db.txt");

  for(auto& employee : employees) {
    output_stream << employee << std::endl;
  }

  output_stream.close();
  */

  for(auto& employee : employees) {
    std::cout << employee << std::endl;
  }

  return 0;
}
