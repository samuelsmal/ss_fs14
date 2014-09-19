#ifndef EMPLOYEERECORD
#define EMPLOYEERECORD

#include <string>
#include <iostream>

struct EmployeeRecord {
  std::string last_name;
  std::string first_name;
  long yearly_salary;
  int age;
  int clearance_level;

  EmployeeRecord(
    std::string _last_name,
    std::string _first_name,
    long _yearly_salary,
    int _age,
    int _clearance_level
    ) : last_name(_last_name), first_name(_first_name), yearly_salary(_yearly_salary), age(_age), clearance_level(_clearance_level){}

};

inline bool operator< (const EmployeeRecord& lhs, const EmployeeRecord& rhs) {
  return lhs.yearly_salary > rhs.yearly_salary;
}

inline std::ostream& operator<< (std::ostream& ostream, const EmployeeRecord& employeeRecord) {
  return ostream << employeeRecord.last_name << " " << employeeRecord.first_name << " " << employeeRecord.yearly_salary << " " << employeeRecord.age << " " << employeeRecord.clearance_level;
}

#endif
