#include <unistd.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// ctor
Process::Process(const int pidint) : pid(pidint){};

int Process::Pid() { return pid; }

float Process::CpuUtilization() {
  auto result =
      ((float)LinuxParser::ActiveJiffies(pid) / LinuxParser::ClkTPS());

  cpu_utilization = result / UpTime();
  return this->cpu_utilization;
}

string Process::Command() { return LinuxParser::Command(pid); }

string Process::Ram() { return LinuxParser::Ram(pid); }

string Process::User() { return LinuxParser::User(pid); }

long int Process::UpTime() { return LinuxParser::UpTime(pid); }

bool Process::operator<(Process const& a) const {
  return ( stoi(LinuxParser::Ram(pid)) > stoi(LinuxParser::Ram(a.pid)));
}