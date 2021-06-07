#pragma once
#include "Vector.h"
#include "String.h"
#include "String.cpp"
#include "Date.h"
#include "Time.h"

#include <cstring>
#include <iostream>



class Convertor {
public:
  char* stringToChar(String command);
  void stringToDate(String& dateS, Date& date);
  void stringToTime(String& timeS, Time& time);
  int stringToInt(String& number);
  double stringToDouble(String& number);

};