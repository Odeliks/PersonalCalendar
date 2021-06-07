#pragma once
#include "Vector.h"
#include "Meet.h"
#include "Meet.cpp"
#include "String.h"
#include "String.cpp"
#include "Validator.h" 
#include "Validator.cpp" 
#include "Convertor.h"
#include "Convertor.cpp"

#include <iostream>
#include <fstream>
#include<cmath>


class Controller {

public:
  Controller();
  void start();

private:
  Vector<String> getSplittedCommand(String& commandRow);
  int getCommand(Vector<String> splitted, Vector<String> commands);

  bool checkIfFree(Date& date, Time& start, Time& end);
  bool isHoliday(Date& date);
  int daysBetween(Date start, Date& end);
  void updateDate(Date& date);
  void sortCalendar(Vector<Meet>& curr);

  void SaveCalendarToFile(const char*, Vector<Meet>&);
  void helpCommand();
  void getMeetings(const char*, Vector<Meet>&, Vector<Date>&);
  void openCommand(const char*);
  void bookCommand(Vector<String>&, Vector<Meet>&);
  void unbookCommand(Vector<String>&, Vector<Meet>&);
  void angendaCommand(Vector<String>&, Vector<Meet>&);
  void changeCommand(Vector<String>&, Vector<Meet>&);
  void findCommand(Vector<String>&, Vector<Meet>&);
  void holidayCommand(Vector<String>&, Vector<Meet>&);
  void busyDaysCommand(Vector<String>&, Vector<Meet>&);
  void findSlotCommand(Vector<String>&, Vector<Meet>&);
  void findSlotWithCommand(Vector<String>&, Vector<Meet>&);
  void mergeCommand(Vector<String>&, Vector<Meet>&);

  Vector<String> commands;
  Vector<Meet> calendar;
  Vector<Date> holidays;
  Validator valid;
  Convertor convert;
};