#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

#include "process.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the operating system name 
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

//TODO RA: Return CPU util without processor class/ object
float System::CpuUtilization() { return LinuxParser::CpuUtilization(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids();
    int n = pids.size();
    for(int i = 0; i < n; i++){
        Process temp;
        temp.Pid(pids[i]);
        temp.User(pids[i]);
        temp.Command(pids[i]);
        temp.Ram(pids[i]);
        temp.UpTime(pids[i]);
        temp.CpuUtilization(pids[i]);
        processes_.push_back(temp); 
        //std::cout << "PID ---> " << processes_[i].Pid() << " Size: " << processes_.size() << " \n";
    }
    return processes_; }