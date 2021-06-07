#pragma once
#include "Vector.h"
#include "String.h"
#include "String.cpp"
#include "Convertor.h"
#include "Convertor.cpp"

#include <iostream>

class Validator {
  public:
  bool validateOpen(Vector<String>&);
  bool validateSaveAs(Vector<String>&);
  bool validateClose(Vector<String>&);
  bool validateSave(Vector<String>&);
  bool validateExit(Vector<String>&);
  bool validateHelp(Vector<String>&);
  bool validateBook(Vector<String>&);
  bool validateUnbook(Vector<String>&);
  bool validateAgenda(Vector<String>&);
  bool validateChange(Vector<String>&);
  bool validateFind(Vector<String>&);
  bool validateHoliday(Vector<String>&);
  bool validateBusyDays(Vector<String>&);
  bool validateFindSlot(Vector<String>&);
  bool validateFindSlotWith(Vector<String>&);
  bool validateMerge(Vector<String>&);

  bool validateDate(Date&);
  bool validateTime(Time&);
  private:
  Convertor convert;
};