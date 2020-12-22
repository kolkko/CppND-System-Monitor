#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Set this process's ID
void Process::Pid(int pid) { 
    pid_ = pid;
    return;  }

// Set the user (name) that generated this process
void Process::User(int pid) { 
    user_ = LinuxParser::User(pid);
    return; }

// TODO: Set this process's CPU utilization
void Process::CpuUtilization(int pid) { 
    cpuutil_ = LinuxParser::CpuUtilization(pid);
    return; }

// Set this process's memory utilization
void Process::Ram(int pid) { 
    int ram = LinuxParser::Ram(pid);
    ram_ = to_string(ram/1000); //memory utilisation in MB
    //std::cout << "RAM: " << ram_ << "\n";
    return; }

// Set the age of this process (in seconds)
void Process::UpTime(int pid) { 
    long pidup, systemup;
    pidup = LinuxParser::UpTime(pid);
    systemup = LinuxParser::UpTime();
    //std::cout << "PIDUP: " << pidup << " SYSTEMUP: " << systemup << "\n";
    uptime_ = systemup - pidup;
    //std::cout << "uptime_ " << uptime_ << "\n";
    return; }

// Set the command that generated this process
void Process::Command(int pid) { 
    command_ = LinuxParser::Command(pid); 
    return; }

//Process return functions
// DONE: Return this process's ID
int Process::Pid() { 
    return pid_;  }

// DONE: Return the user (name) that generated this process
string Process::User() { 
    return user_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return cpuutil_; }

// DONE: Return this process's memory utilization
string Process::Ram() { 
    return ram_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return uptime_; }

// DONE: Return the command that generated this process
string Process::Command() { 
    return command_; }
