#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    // Return process variables
    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp

    //Set process variables
    void Pid(int pid);
    void User(int pid);
    void CpuUtilization(int pid);
    void Ram(int pid);
    void UpTime(int pid);
    void Command(int pid);

  //Process data, set when vector of processes is created
 private:
    int pid_;
    std::string user_;
    std::string command_;
    float cpuutil_;
    std::string ram_;
    long int uptime_;
};

#endif