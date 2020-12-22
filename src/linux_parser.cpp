#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// DONE: Read and return CPU utilization
float LinuxParser::CpuUtilization() { 
  vector<string> cpuutil;
  float a, b, c, d, e, f, g, h, i, j, cputotal, cpuutiltotal;
  string line, data;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> data >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
    //std::cout << data << " a: " << a << " b: " << b << " c: " << c << " d: " << d << "\n";
    cputotal = a + b + c + f + g + h;
    cpuutiltotal = cputotal/ (cputotal + d + e);
    //std::cout << "cpuutil: " << cpuutiltotal << "\n";
  }
  return cpuutiltotal; }

  // DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { string line, key, value, kb;
  string memtotalstr, memfreestr;
  float memtotal, memfree, memused;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kb) {
        if (key == "MemTotal:") {
          memtotalstr = value;
        }
        if (key == "MemFree:") {
          memfreestr = value;
          break;
        }
      }
    }
  }
  std::stringstream total(memtotalstr);
  total >> memtotal;
  std::stringstream free(memfreestr);
  free >> memfree;
  memused = (memtotal - memfree) / memtotal;
  //std::cout << "memused: " << memused << "\n";
  return memused;  }

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
   string line, key, totalprocessesstr;
   int value;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line); 
        linestream >> key >> value;
        if (key == "processes" && value) break;
    }
  }
  return value;}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line, key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") break;
    }
  }
  return value; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long totalup, totalidle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> totalup >> totalidle;
  }
  // idle time is included in totalup already
  return totalup; }


// ======== PROCESSES ========

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  std::string key, value, line, uid, x, user;
  //Get Uid
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        uid = value; 
        break;}
    }
  }
  // Match Uid with Username
  std::ifstream filestream1(kPasswordPath);
  if (filestream.is_open()) {
    while(std::getline(filestream1, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream1(line);
      linestream1 >> value >> x >> key;
      if (key == uid) {
        user = value; 
        break;}
    }
  }
  return user; }
// Read and return process CPU utilization data
float LinuxParser::CpuUtilization(int pid) {
  string value, line;
  float totaltime, seconds, cpuutil;
  vector<string> data;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 22; i++) {
      linestream >> value;
      if (i >= 13) data.push_back(value);
    
    }
  totaltime = (std::stof(data[0]) + std::stof(data[1]) + std::stof(data[2]) + std::stof(data[3])) / sysconf(_SC_CLK_TCK); //total time spent for process
  float uptime = LinuxParser::UpTime();
  //std::cout << "data[8]: " << data[8];
  //total uptime of system - time at which process started, in seconds
  seconds = uptime - (std::stof(data[8]) / sysconf(_SC_CLK_TCK));
  cpuutil = 100 * (totaltime / seconds);
  //std::cout << "cpuutil: " << cpuutil << " totaltime: " << totaltime << "system uptime: " << uptime << " seconds: " << seconds << "\n";
}
  return cpuutil;}

// TODO: Read and return the memory used by a process
int LinuxParser::Ram(int pid) { 
  std::string line, key;
  int value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "VmSize:") break;
    }
  }
  return value; }

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  std::string value, line;
  long alluptime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 22; i++) {
      linestream >> value;
      }
      //std::cout << "UPTIME FILE: " << value << "\n";
  }
  alluptime = (std::stol(value)/sysconf(_SC_CLK_TCK));
  return  alluptime; }  //needs to have total computer up time subtracted from it

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  std::string line, command;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  //std::cout << "COMMAND: " << command << "\n";
  return command; }