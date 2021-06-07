#include "Validator.h"

bool Validator::validateOpen(Vector<String>& splitted) {
  int size = splitted.getSize();
  if(size != 2){
    std::cout<<"The open command needs 1 argument for the file name\n";
    return false;
  }
  int fileNameLength = splitted[1].length();
  if(splitted[1][fileNameLength - 1] != 't' || 
     splitted[1][fileNameLength - 2] != 'x' || 
     splitted[1][fileNameLength - 3] != 't' || 
     splitted[1][fileNameLength - 4] != '.') {
    std::cout<<"File must end with .txt\n";
    return false;
  }
  return true;
}

bool Validator::validateSaveAs(Vector<String>& splitted) {
  int size = splitted.getSize();
  if(size != 2){
    std::cout<<"The saveas command needs 1 argument for the destination\n";
    return false;
  }
  int fileNameLength = splitted[1].length();
  if(splitted[1][fileNameLength - 1] != 't' || 
     splitted[1][fileNameLength - 2] != 'x' || 
     splitted[1][fileNameLength - 3] != 't' || 
     splitted[1][fileNameLength - 4] != '.') {
    std::cout << "File must end with .txt\n";
    return false;
  }
  return true;
}

bool Validator::validateClose(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 1) {
    std::cout<<"The close command doesn't need arguments\n";
    return false;
  }
  return true;
}

bool Validator::validateSave(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 1) {
    std::cout<<"The save command doesn't need arguments\n";
    return false;
  }

  return true;
}

bool Validator::validateExit(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 1) {
    std::cout<<"The exit command doesn't need arguments\n";
    return false;
  }
  return true;
}

bool Validator::validateHelp(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 1) {
    std::cout<<"The help command doesn't need arguments\n";
    return false;
  }
  return true;
}

bool Validator::validateBook(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size < 6) {
    std::cout<<"The book command need 5 arguments: first for date, second for start time, third for end time, forth for name and fifth for note\n";
    return false;
  }

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }

  int startLength = splitted[2].length();

  for(int i = 0; i < startLength; i++) {
    if(splitted[2][i] == ':' || (splitted[2][i] >= '0' && splitted[2][i] <= '9')) {
      continue;
    }
    std::cout<<"Time needs to be in hh:mm format.\n";
    return false;
  }

  int endLength = splitted[3].length();

  for(int i = 0; i < endLength; i++) {
    if(splitted[3][i] == ':' || (splitted[3][i] >= '0' && splitted[3][i] <= '9')) {
      continue;
    }
    std::cout<<"Time needs to be in hh:mm format.\n";
    return false;
  }

  return true;
}

bool Validator::validateUnbook(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 4) {
    std::cout<<"The unbook command needs only 3 arguments. First for date, second for starting time and third for ending time of the meet\n";
    return false;
  }

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }

  int startLength = splitted[2].length();

  for(int i = 0; i < startLength; i++) {
    if(splitted[2][i] == ':' || (splitted[2][i] >= '0' && splitted[2][i] <= '9')) {
      continue;
    }
    std::cout<<"Time needs to be in hh:mm format.\n";
    return false;
  }

  int endLength = splitted[3].length();

  for(int i = 0; i < endLength; i++) {
    if(splitted[3][i] == ':' || (splitted[3][i] >= '0' && splitted[3][i] <= '9')) {
      continue;
    }
    std::cout<<"Time needs to be in hh:mm format.\n";
    return false;
  }

  return true;
}

bool Validator::validateAgenda(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 2) {
    std::cout<<"The agenda command need only one argument for the date.\n";
    return false;
  }

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }

  return true;
}

bool Validator::validateChange(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size < 5) {
    std::cout<<"The change command need 4 arguments: first for the date, second for the start, third for the option and forth for the new value\n";
    return false;
  }

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }

  int startLength = splitted[2].length();

  for(int i = 0; i < startLength; i++) {
    if(splitted[2][i] == ':' || (splitted[2][i] >= '0' && splitted[2][i] <= '9')) {
      continue;
    }
    std::cout<<"Time needs to be in hh:mm format.\n";
    return false;
  }

  if(splitted[3] != "name" && splitted[3] != "note" && splitted[3] != "date" && splitted[3] != "starttime" && splitted[3] != "endtime") {
    std::cout<<"The option in the change command must be name, note, date, starttime or endtime\n";
    return false;
  }

  return true;
}

bool Validator::validateFind(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size < 2) {
    std::cout<<"The find command need only one argument for the search term\n";
    return false;
  }
  return true;
}

bool Validator::validateHoliday(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 2) {
    std::cout<<"The holiday command needs only one argument for the date.\n";
    return false;
  }

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }
  Date tempDate;
  convert.stringToDate(splitted[1], tempDate);

  if(!validateDate(tempDate))  {
    std::cout<<"This date isn't valid\n";
    return false;
  }

  return true;
}

bool Validator::validateBusyDays(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 3) {
    std::cout<<"The busydays command needs 2 arguments, first for the start date and second for the end date\n.";
    return false;
  }

  int dateStartLength = splitted[1].length();

  for(int i = 0; i < dateStartLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }
  Date tempStartDate;
  convert.stringToDate(splitted[1], tempStartDate);

  if(!validateDate(tempStartDate))  {
    std::cout<<"This date isn't valid\n";
    return false;
  }

  int dateEndLength = splitted[2].length();

  for(int i = 0; i < dateEndLength; i++) {
    if(splitted[2][i] == '.' || (splitted[2][i] >= '0' && splitted[2][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }
  Date tempEndDate;
  convert.stringToDate(splitted[2], tempEndDate);

  if(!validateDate(tempEndDate))  {
    std::cout<<"This date isn't valid\n";
    return false;
  }

  return true;
}

bool Validator::validateFindSlot(Vector<String>& splitted) {
  int size = splitted.getSize();

  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }
  Date tempStartDate;
  convert.stringToDate(splitted[1], tempStartDate);

  if(!validateDate(tempStartDate))  {
    std::cout<<"This date isn't valid\n";
    return false;
  }

  int hoursWanted = convert.stringToInt(splitted[2]);
  if(hoursWanted < 0 || hoursWanted > 9) {
    std::cout<<"The hours wanted must be between 0 and 9\n";
    return false;
  }

  return true;
}

bool Validator::validateFindSlotWith(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 4) {
    std::cout<<"The findslotwith command need 3 arguments, first for the date, second for the time wanted and the thrid for the calendar file\n";
    return false;
  }


  int dateLength = splitted[1].length();

  for(int i = 0; i < dateLength; i++) {
    if(splitted[1][i] == '.' || (splitted[1][i] >= '0' && splitted[1][i] <= '9')) {
      continue;
    }
    std::cout<<"Date needs to be in dd.mm.yyyy format.\n";
    return false;
  }
  Date tempStartDate;
  convert.stringToDate(splitted[1], tempStartDate);

  if(!validateDate(tempStartDate))  {
    std::cout<<"This date isn't valid\n";
    return false;
  }

  int hoursWanted = convert.stringToInt(splitted[2]);
  if(hoursWanted < 0 || hoursWanted > 9) {
    std::cout<<"The hours wanted must be between 0 and 9\n";
    return false;
  }

  // int fileNameLength = splitted[3].length();
  // // if(fileNameLength < 5) {
  // //   std::cout<<"File must end with .txt\n";
  // //   return false;
  // // }
  // if(splitted[1][fileNameLength - 1] != 't' || 
  //    splitted[1][fileNameLength - 2] != 'x' || 
  //    splitted[1][fileNameLength - 3] != 't' || 
  //    splitted[1][fileNameLength - 4] != '.') {
  //   std::cout<<"File must end with .txt\n";
  //   return false;
  // }

  return true;
}

bool Validator::validateMerge(Vector<String>& splitted) {
  int size = splitted.getSize();

  if(size != 2) {
    std::cout<<"The merge commands need 1 argument for the name of the calendar\n";
    return false;
  }

  int fileNameLength = splitted[1].length();
  if(fileNameLength < 5) {
    std::cout<<"File must end with .txt\n";
    return false;
  }
  if(splitted[1][fileNameLength - 1] != 't' || 
     splitted[1][fileNameLength - 2] != 'x' || 
     splitted[1][fileNameLength - 3] != 't' || 
     splitted[1][fileNameLength - 4] != '.') {
    std::cout<<"File must end with .txt\n";
    return false;
  }

  return true;
}

bool Validator::validateDate(Date& date) {
  bool isLeap = (((date.year % 4 == 0) &&
                  (date.year % 100 != 0)) ||
                  (date.year % 400 == 0));


  if(date.year > 2025 || date.year < 2021){
    std::cout<<"Year must be between 2021 and 2025\n";
    return false;
  }
  if(date.month < 1 || date.month > 12) {
      std::cout<<"Month must be between 1 and 12\n";
      return false;
  }
  if(date.day < 1 || date.day > 31) {
    std::cout<<"Day must be between 1 and 31\n";
    return false;
  }

  if(date.month == 2 ) {
    if(isLeap && date.day > 29) {
      std::cout<<"In leap years February has only 29 days\n";
      return false;
    } else {
      if(date.day > 28) {
        std::cout<<"In non-leap years February has only 28 days\n";
        return false;
      }
    }
  }

  if(date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
    if(date.month > 30) {
      std::cout<<"The months of April, June, September and November have only 30 days\n";
      return false;
    }
  }
  return true;
}

bool Validator::validateTime(Time& time) {
  if(time.hour < 1 || time.hour > 24) {
    std::cout<<"The hour must be between 1 and 24\n";
    return false;
  }
  
  if(time.minute < 0 || time.minute > 60) {
    std::cout<<"The minutes must be between 0 and 60\n";
    return false;
  }

  return true;
}