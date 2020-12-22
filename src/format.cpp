#include <string>
#include <bits/stdc++.h>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
std::string Format::ElapsedTime(long times){
    std::string timeformat, hourstr, minstr, secstr;
    long hours, minutes, seconds;

    //Calculate hours minutes and seconds from Uptime in seconds
    hours = floor(times / 3600);
    minutes = floor((times%3600)/60);
    seconds = times%60;
    
    //Format times for display
    if(hours >= 1 && hours < 10) {hourstr = "0" + std::to_string(hours);}
    else if(hours < 1 ) {hourstr = "00";}
    else {hourstr = std::to_string(hours);}

    if(minutes >= 1 && minutes < 10) {minstr = "0" + std::to_string(minutes);}
    else if(minutes < 1 ) {minstr = "00";}
    else {minstr = std::to_string(minutes);}
    
    if(seconds >= 1 && seconds < 10) {secstr = "0" + std::to_string(seconds);}
    else if(seconds < 1 ) {secstr = "00";}
    else {secstr = std::to_string(seconds);}

    timeformat = hourstr + ":" + minstr + ":" + secstr;

return timeformat;}