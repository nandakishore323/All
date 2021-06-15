#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 public:
  Process(const int pidint);
  bool UpdateInfo(void);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

 private:
    int pid;
   std::string _user;
   std::string _command;
   float cpu_utilization;
   std::string _ram;
   long int _upTime; 
};

#endif