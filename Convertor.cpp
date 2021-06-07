#pragma once
#include "Convertor.h"

char* Convertor::stringToChar(String command) {
  int length = command.length();
  char* commandC = new char[length + 1]; 
  int i = 0;
  for(; i < length;) {
    commandC[i] = command[i];
    i++;
  }
  commandC[i] = '\0';
  return commandC;
}

void Convertor::stringToDate(String& dateS, Date& date) {
  
  int length = dateS.length();
  int index = 0;
  int day = 0, month = 0, year = 0;
  for(; index < length; index++) {
    if(dateS[index] == '.') {
      index++;
      break;
    }
    day *= 10;
    day += (dateS[index] - '0');
  }

  for(; index < length; index++) {
    if(dateS[index] == '.') {
      index++;
      break;
    }
    month *= 10;
    month += (dateS[index] - '0');
  }

  for(; index < length; index++) {
    if(dateS[index] == '.') {
      index++;
      break;
    }
    year *= 10;
    year += (dateS[index] - '0');
  }  
  date.day = day;
  date.month = month;
  date.year = year;
}

void Convertor::stringToTime(String& timeS, Time& time) {
  int length = timeS.length();

  int hour = 0, minute = 0;
  int index = 0;

  for(; index < length; index++) {
    if(timeS[index] == ':') {
      index++;
      break;
    }
    hour *= 10;
    hour += (timeS[index] - '0');
  }

  for(; index < length; index++) {
    if(timeS[index] == '\0') {
      index++;
      break;
    }
    minute *= 10;
    minute += (timeS[index] - '0');
  }
  time.hour = hour;
  time.minute = minute;
}

int Convertor::stringToInt(String& number) {
  int length = number.length();
  int result = 0;
  for(int i = 0; i < length; i++) {
    result *= 10;
    result += (number[i] - '0');
  }
  return result;
}

double Convertor::stringToDouble(String& number) {
  char* strNumber = stringToChar(number);
  double result = atof(strNumber);
  std::cout<<result;
  return result;
}