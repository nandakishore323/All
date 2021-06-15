#include <string>

#include "format.h"

using std::string;

string FormatNum(long num){
    if ( num < 10 )
      return "0" + std::to_string(num);
    return std::to_string(num);
}

string Format::ElapsedTime(long seconds) {
    long hours = seconds/3600;
    long secs = seconds%60;
    long mins = (seconds - hours*3600)/60;
    
    return (FormatNum(hours)+":"+FormatNum(mins)+":"+FormatNum(secs)); 
}