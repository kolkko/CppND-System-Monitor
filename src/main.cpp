#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system);

  //TESTS TO TERMINAL
  //system.System::CpuUtilization();
  //system.System::MemoryUtilization();
  //system.System::Processes();


}