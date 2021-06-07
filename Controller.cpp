#pragma once
#include "Controller.h"



Controller::Controller() {
  commands.push_back("open");
  commands.push_back("close");
  commands.push_back("save");
  commands.push_back("saveas");
  commands.push_back("exit");
  commands.push_back("help");
  commands.push_back("book");
  commands.push_back("unbook");
  commands.push_back("agenda");
  commands.push_back("change");
  commands.push_back("find");
  commands.push_back("holiday");
  commands.push_back("busydays");
  commands.push_back("findslot");
  commands.push_back("findslotwith");
  commands.push_back("merge");
  
}

Vector<String> Controller::getSplittedCommand(String& commandRow) {
  Vector<String> temp;
  int singleIndex = 0;
  String each;
  for(int i = 0; commandRow[i] != '\0'; i++) {

    if(commandRow[i] == ' ') {      

      temp.push_back(each);
      each = "";
      continue;
    }
    each.push_back(commandRow[i]);
    
  }
  temp.push_back(each);
  return temp;
}

int Controller::getCommand(Vector<String> splitted, Vector<String> commands) {
  for(int i = 0; i < commands.getSize(); i++) {
    if(commands[i] == splitted[0]) return i;
  }
  return -1;
}

bool Controller::isHoliday(Date& date) {
  int size = holidays.getSize();

  for(int i = 0; i < size; i++) {
    if(holidays[i] == date) {
      return false;
    }
  }
  return true;
}

bool Controller::checkIfFree(Date& date, Time& start, Time& end) {
  int size = calendar.getSize();

  double newTimeS = (double)start.hour + ((double)start.minute / 60);
  double newTimeE = (double)end.hour + ((double)end.minute / 60);
  for(int i = 0; i < size; i++) {
    if(calendar[i].getDate() == date) {
      double currStart = (double)calendar[i].getStart().hour + ((double)calendar[i].getStart().minute / 60);
      double currEnd = (double)calendar[i].getEnd().hour + ((double)calendar[i].getEnd().minute / 60);

      if(newTimeS <= currEnd && currStart <= newTimeS){ 
        return false;
      }
      else if (newTimeE <= currEnd && currStart <= newTimeE){
        return false;
      }  
      else if (newTimeS <= currStart && newTimeE >= currEnd){
        return false;
      }
    } 
  }

  return true;
}

void Controller::updateDate(Date& date) {
   bool isLeap = (((date.year % 4 == 0) &&
                  (date.year % 100 != 0)) ||
                  (date.year % 400 == 0));

  switch(date.month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: {
      if(date.day + 1 > 31) {
        date.day = 1;
        if(date.month + 1 > 12){
          date.month = 1;
          date.year = date.year + 1;
          break;
        } 
        date.month = date.month + 1;
        break;
      }
      date.day = date.day + 1;
      break;
    }

    case 4:
    case 6:
    case 9:
    case 11: {
      if(date.day + 1 > 30) {
        date.day = 1;
        date.month = date.month + 1;
        break;
      }
      date.day = date.day + 1;
      break;
    }
    case 2: {
      if(isLeap) {
        if(date.day + 1 > 29) {
          date.day = 1;
          date.month = 3;
          break;
        }
        date.day = date.day + 1;
        break;
      }
      else {
        if(date.day + 1 > 28) {
          date.day = 1;
          date.month = 3;
          break;
        }
        date.day = date.day + 1;
        break;
      }
    }
  }
}

int Controller::daysBetween(Date start, Date& end) {
  int counter = 1;
  while(true) {
    if(start == end) return counter;

    updateDate(start);
    counter++;
  }
}

void Controller::sortCalendar(Vector<Meet>& curr) {
  int size = curr.getSize();

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size - i - 1; j++) {
      if(curr[j].getStart() > curr[j + 1].getStart()) {
        Meet temp = curr[j];
        curr[j] = curr[j + 1];
        curr[j + 1] = temp;
      }
    }
  }
}

void Controller::SaveCalendarToFile(const char* fileName, Vector<Meet>& v) {
 std::ofstream output(fileName);
 int lengthMeets = v.getSize();
 int lengthHoliday = holidays.getSize();
 for(int i = 0; i < lengthHoliday; i++) {
   output << holidays[i].day << " " << holidays[i].month << " " << holidays[i].year << '\n';
 }
 output<<"---\n";

 for(int i = 0; i < lengthMeets - 1; i++) {
    output << v[i].getDate().day << " " << v[i].getDate().month << " " << v[i].getDate().year << " "; 
    output << v[i].getStart().hour << " " << v[i].getStart().minute << " "; 
    output << v[i].getEnd().hour << " " << v[i].getEnd().minute << " " << v[i].getHoliday() << " ";
    output << v[i].getName() << ":"; 
    output << v[i].getNote() << "\n"; 
    
  }  
  
    output << v[lengthMeets - 1].getDate().day << " " << v[lengthMeets - 1].getDate().month << " " << v[lengthMeets - 1].getDate().year << " "; 
    output << v[lengthMeets - 1].getStart().hour << " " << v[lengthMeets - 1].getStart().minute << " "; 
    output << v[lengthMeets - 1].getEnd().hour << " " << v[lengthMeets - 1].getEnd().minute << " " << v[lengthMeets - 1].getHoliday() << " ";
    output << v[lengthMeets - 1].getName() << ":"; 
    output << v[lengthMeets - 1].getNote(); 
    output.close();
  
}

void Controller::getMeetings(const char* inputName, Vector<Meet>& v, Vector<Date>& dates) {
  std::ifstream input(inputName);
  v.clear();
  char row[512];
  bool isHolidays = true;
  while(input.getline(row, 512)) {
    int length = strlen(row);
    if(isHolidays) {
      int day = 0, month = 0, year = 0;
      int index = 0;
      if(!strcmp(row, "---")) {
        isHolidays = false;
        continue;
      }
      for(;index < length; index++) {
      if(row[index] == ' ') {
        index++;
        break;
      }
        day *= 10;
        day +=(row[index] - '0');
      }

      for(;index < length; index++) {
      if(row[index] == ' ') {
        index++;
        break;
      }
        month *= 10;
        month +=(row[index] - '0');
      }

      for(;index < length; index++) {
      if(row[index] == ' ') {
        index++;
        break;
      }
        year *= 10;
        year +=(row[index] - '0');
      }
      Date temp{day, month, year};
      dates.push_back(temp);
    }
     else {

      int day = 0, month = 0, year = 0;
      int startH = 0, startM = 0;
      int endH = 0, endM = 0;
      bool holiday = false;
      int holidayN = 0;
      char name[64];
      char note[64];

      int index = 0;
      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        day *= 10;
        day +=(row[index] - '0');
      }
      // std::cout<<day<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        month *= 10;
        month +=(row[index] - '0');
      }
      // std::cout<<month<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        year *= 10;
        year +=(row[index] - '0');
      }
      // std::cout<<year<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        startH *= 10;
        startH +=(row[index] - '0');
      }
      // std::cout<<startH<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        startM *= 10;
        startM +=(row[index] - '0');
      }
      // std::cout<<startM<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        endH *= 10;
        endH +=(row[index] - '0');
      }
      // std::cout<<endH<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        endM *= 10;
        endM +=(row[index] - '0');
      }
      // std::cout<<endM<<' ';

      for(;index < length; index++) {
        if(row[index] == ' ') {
          index++;
          break;
        }
        holidayN *= 10;
        holidayN +=(row[index] - '0');
      }
      if(holidayN == 0) holiday = false;
      else holiday = true;
      // std::cout<<std::boolalpha<<holiday << '\n';

    int nameIndex = 0;
    for(;index < length; index++) {
        if(row[index] == ':') {
          index++;
          break;
        }
        name[nameIndex++] = row[index];
      }
      name[nameIndex] = '\0';
      // std::cout<<name<<' ';

    int noteIndex = 0;
    for(;index < length; index++) {
        if(row[index] == ':') {
          index++;
          break;
        }
        note[noteIndex++] = row[index];
      }
      note[noteIndex] = '\0';
      // std::cout<<note<<'\n';
      
      Date currentDate{day, month, year};
      Time currentStart{startH, startM};
      Time currentEnd{endH, endM};
      Meet temp(currentDate, name, note,currentStart, currentEnd);
      temp.setHoliday(holiday);
      
      v.push_back(temp);
     }
  }

}

void Controller::helpCommand() {
  std::cout<<"The calendar has the following commands:\n" 
           << "1.  open <file>                                     - opens <file> \n"
           << "2.  close                                           - closes the current file\n"
           << "3.  save                                            - saves the contents of the current file\n"
           << "4.  saveas <file>                                   - saves the contents of the current file to <file>\n"
           << "5.  help                                            - displays the help menu\n"
           << "6.  exit                                            - exits the program\n"
           << "7.  book <date> <starttime> <endtime> <name> <note> - books a meet with <name> and comment <note> on <date> with starting hour <starttime> and end hour <endtime>\n"
           << "8.  unbook <date> <starttime> <endtime>             - unbooks a meet on <date> with starting hour <starttime> and end hour <endtime>\n"
           << "9.  agenda <date>                                   - prints the meets on <date> in chronological order\n"
           << "10. change <date> <starttime> <option> <newvalue>   - changes the <option> with <newvalue> of the meet on <date> with <starttime>\n"
           << "11. find <string>                                   - prints all the meets with <string> in their name or notes\n"
           << "12. holiday <date>                                  - sets the <date> as a holiday\n"
           << "13. busydays <from> <to>                            - prints statistic of the busy hours per day <from> date <to> date\n"
           << "14. findslot <fromdate> <hours>                     - finds a date for a meet <fromdate> date for <hours> hours\n"
           << "15. findslotwith <fromdate> <hours> <calendar>      - finds a date for a meet <fromdate> date for <hours> hours in <calendar>\n"
           << "16. merge <calendar>                                - merges <calendar> with the current calendar\n";
              
}

void Controller::openCommand(const char* fileName) {
  std::ofstream temp(fileName, std::ofstream::app);
  temp.close();
  std::ifstream in(fileName);
  while(!in.eof()){
    char row[512];
    in.getline(row, 512);
    std::cout<<row << '\n';
  }
  in.close();
}

void Controller::bookCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date newDate {0,0,0};
  Time newStart {0,0};
  Time newEnd {0,0};

  int sizeSplit = splitted.getSize();

  convert.stringToDate(splitted[1], newDate);
  convert.stringToTime(splitted[2], newStart);
  convert.stringToTime(splitted[3], newEnd);
  char* name = convert.stringToChar(splitted[4]);
  String tempNote = splitted[5];
  for(int i = 6; i < sizeSplit; i++) {
    tempNote.push_back(' ');
    tempNote = tempNote + splitted[i];
  }
  
  char* note = convert.stringToChar(tempNote);

  int holidaySize = holidays.getSize();

  for(int i = 0; i < holidaySize; i++) {
    if(holidays[i] == newDate) {
      std::cout<<"This date is set as a holiday\n";
      return;
    }
  }
  bool isBooked = false;
  Meet newMeet(newDate, name, note, newStart, newEnd);
  if(valid.validateTime(newStart) && valid.validateTime(newEnd) && valid.validateDate(newDate)) {
    if(newStart.hour >= newEnd.hour && newStart.minute >= newEnd.minute){
      std::cout<<"The start hour is after the end hour";
      return;
    }

    
    double newTimeS = (double)newStart.hour + ((double)newStart.minute / 60);
    double newTimeE = (double)newEnd.hour + ((double)newEnd.minute / 60);
    int calLength = calendar.getSize();
    for(int i = 0; i < calLength && !isBooked; i++) {
      if(calendar[i].getDate() == newDate) {

        double currStart = (double)calendar[i].getStart().hour + ((double)calendar[i].getStart().minute / 60);
        double currEnd = (double)calendar[i].getEnd().hour + ((double)calendar[i].getEnd().minute / 60);

        if(newTimeS <= currEnd && currStart <= newTimeS){ 
          isBooked = true;
        }
        else if (newTimeE <= currEnd && currStart <= newTimeE){
          isBooked = true;
        }  
        else if (newTimeS <= currStart && newTimeE >= currEnd){
          isBooked = true;
        }
      }
    }
    if(!isBooked) {
      calendar.push_back(newMeet);
      std::cout<<"The new meet was added to the calendar\n";
    }
    else {
      std::cout<<"The new meet's start or end conflicts with other meets\n";
    }
  }  
}

void Controller::unbookCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date removeDate {0,0,0};
  Time removeStart {0,0};
  Time removeEnd {0,0};

  convert.stringToDate(splitted[1], removeDate);
  convert.stringToTime(splitted[2], removeStart);
  convert.stringToTime(splitted[3], removeEnd);

  int calendarSize = calendar.getSize();
  bool exists = false;
  Vector<Meet> tempo;
  for(int i = 0; i < calendarSize; i++) {
    if(calendar[i].getDate() == removeDate && 
       calendar[i].getStart() == removeStart &&
       calendar[i].getEnd() == removeEnd) {
         exists = true;
         continue;
       }
    tempo.push_back(calendar[i]);
  }
  if(exists) {
    calendar = tempo;
  } else {
    std::cout<<"There is no such meeting in your calendar\n";
  }
}

void Controller::angendaCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date currentDate{0,0,0};
  convert.stringToDate(splitted[1], currentDate);
  int sizeCalendar = calendar.getSize();


  Vector<Meet> toBeSorted;
  for(int i = 0; i < sizeCalendar; i++) {
    if(calendar[i].getDate() == currentDate) {
      toBeSorted.push_back(calendar[i]);
    }
  }
  
  int toBeSortedSize = toBeSorted.getSize();
  if(toBeSortedSize == 0) {
    std::cout<<"There are no meets on this date\n";
    return;
  }
  for(int i = 0; i < toBeSortedSize; i++) {
    for(int j = 0; j < toBeSortedSize - i - 1; j++) {
      if(toBeSorted[j].getStart() > toBeSorted[j + 1].getStart()) {
        Meet temp = toBeSorted[j];
        toBeSorted[j] = toBeSorted[j + 1];
        toBeSorted[j + 1] = temp;
      }
    }
  }

  for(int i = 0; i < toBeSortedSize; i++) 
    toBeSorted[i].print();
  

}

void Controller::changeCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date currDate{0,0,0};
  Time currStart{0,0};
  convert.stringToDate(splitted[1], currDate);
  convert.stringToTime(splitted[2], currStart);


  int sizeCalendar = calendar.getSize();
  for(int i = 0; i < sizeCalendar; i++) {
    if(calendar[i].getDate() == currDate && calendar[i].getStart() == currStart) {
      if(splitted[3] == "note") {
        String tempNote = splitted[4];
        int splittedSize = splitted.getSize();
        for(int i = 5; i < splittedSize ; i++) {
          tempNote.push_back(' ');
          tempNote = tempNote + splitted[i];
        }
        char* changeValue = convert.stringToChar(tempNote);
        calendar[i].setNote(changeValue);
        std::cout<<"The note was changed\n";
        break;
      }
      else if(splitted[3] == "name") {
        char* changeValue = convert.stringToChar(splitted[4]);
        calendar[i].setName(changeValue);
        std::cout<<"The name was changed\n";
        break;
      }
      else if(splitted[3] == "date") {
        Date newDate{0,0,0};
        convert.stringToDate(splitted[4], newDate);
        if(isHoliday(newDate)) {
          std::cout<<"This date is set as holiday\n";
          return;
        }
        Time start{calendar[i].getStart().hour, calendar[i].getStart().minute};
        Time end{calendar[i].getEnd().hour, calendar[i].getEnd().minute};
        if(checkIfFree(newDate, start, end)) {
          calendar[i].setDate(newDate);
          std::cout<<"The date was changed\n";
          break;
        }        
      }
      else if(splitted[3] == "starttime") {
        Time newStart{0,0};
        convert.stringToTime(splitted[4], newStart);
        Time end{calendar[i].getEnd().hour, calendar[i].getEnd().minute};
        Date date{calendar[i].getDate().day, calendar[i].getDate().month, calendar[i].getDate().year};
        if(checkIfFree(date, newStart, end)) {
          calendar[i].setStart(newStart);
          std::cout<<"The start time was changed\n";
          break;
        }
      }
      else if(splitted[3] == "endtime") {
        Time newEnd{0,0};
        convert.stringToTime(splitted[4], newEnd);
        Date date{calendar[i].getDate().day, calendar[i].getDate().month, calendar[i].getDate().year};
        Time start{calendar[i].getStart().hour, calendar[i].getStart().minute};
        if(checkIfFree(date, start, newEnd)) {
          calendar[i].setEnd(newEnd);
          std::cout<<"The end time was changed\n";
          break;
        }
      }
    }
  } 
}

void Controller::findCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  // splitted[1] -> tyrsenata duma
  Vector<Meet> foundMeets;
  int size = calendar.getSize();
  
  for(int i = 0; i < size; i++) {
    bool inNotes = false;
    
    String note = calendar[i].getNote();
    Vector<String> eachNote = getSplittedCommand(note);
    int noteSize = eachNote.getSize();

    for(int j = 0; j < noteSize; j++) {
      if(eachNote[j] == splitted[1]) {
        inNotes = true;
        break;
      }
    }

    if(splitted[1] == calendar[i].getName() || inNotes) {
      calendar[i].print();
    }
  }
}

void Controller::holidayCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  int calendarSize = calendar.getSize();
  int sizeHolidays = holidays.getSize();


  Date toBeHolidated;
  convert.stringToDate(splitted[1], toBeHolidated);
  bool existingHoliday = false;

  for(int i = 0; i <  sizeHolidays; i++) {
    if(holidays[i] == toBeHolidated){
      existingHoliday = true;
      break;
    }
  }
  
  if(existingHoliday) {
    std::cout<<"This date is already set as a holiday\n";
  } else {
    holidays.push_back(toBeHolidated);
    std::cout<<"The date " << toBeHolidated.day << "." <<toBeHolidated.month << "." << toBeHolidated.year << " was set as a holiday\n";
    
    Vector<Meet> tempo;
    for(int i = 0; i < calendarSize; i++) {
      if(calendar[i].getDate() == toBeHolidated) {
        continue;
      }
      tempo.push_back(calendar[i]);
    }

    calendar = tempo;
  }
}

void Controller::busyDaysCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date start{0,0,0};
  Date end{0,0,0};

  convert.stringToDate(splitted[1], start);
  convert.stringToDate(splitted[2], end);
  if(valid.validateDate(start) && valid.validateDate(end)) {
    int daysCount = daysBetween(start, end);
    int* busyness = new int[daysCount];
    int busynessIndex = 0;
    Vector<Date> busyDates;
    int sizeCalendar = calendar.getSize();
    while(true) {
      busyDates.push_back(start);
      busyness[busynessIndex] = 0;
      for(int i = 0; i < sizeCalendar; i++) {
        if(calendar[i].getDate() == start) {
          busyness[busynessIndex] += 1;
        }
      }

      if(start == end) {
        break;
      }
      else {
        updateDate(start);
        busynessIndex++;
      }
    }

    int sizeBusyDate = busyDates.getSize();
    for(int i = 0; i < sizeBusyDate; i++) {
      std::cout << "On " << busyDates[i].day << "." << busyDates[i].month << "." << busyDates[i].year << " there are " << busyness[i] << " meets\n";
    }
    delete[] busyness;
  }
}

void Controller::findSlotCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  Date currDate{0,0,0};
  convert.stringToDate(splitted[1], currDate);
  double wantedHours = convert.stringToDouble(splitted[2]);
  
  if(!valid.validateDate(currDate)) return;

  int holidaySize = holidays.getSize();
  int calendarSize = calendar.getSize();

  bool isHoliday = false;
  while(true) {
    isHoliday = false;
    for(int i = 0; i < holidaySize; i++) {
      if(currDate == holidays[i]) {
        updateDate(currDate);
        isHoliday = true;
        break;
      }
    }


    if(isHoliday) continue;
    else {
      Time beginning {8,0};
      Vector<Meet> currMeets;
      for(int i = 0; i < calendarSize; i++)
        if(calendar[i].getDate() == currDate && calendar[i].getStart() >= beginning)
          currMeets.push_back(calendar[i]);

      int currSize = currMeets.getSize();

      if(currSize == 0) {
        std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year << " at 8:00 to " << 8 + wantedHours << ":00\n";
        return;
      }
      else {
        sortCalendar(currMeets);

        double beginHours = (double)currMeets[0].getStart().hour + (double)currMeets[0].getStart().minute / 60.0;
        double beginCheck = beginHours - 8.0;
        if(beginCheck >= wantedHours){
          std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year << " at 8:00 to " << 8 + wantedHours << ":00\n";
          return;
        }

        for(int i = 1; i < currSize; i++) {
          double currEnd = (double)calendar[i - 1].getEnd().hour + (double)calendar[i - 1].getEnd().minute / 60.0;
          double currStart = (double)calendar[i].getStart().hour + (double)calendar[i].getStart().minute / 60.0;

          double currFree = currStart - currEnd;
          if(currFree >= wantedHours) {
            std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year 
            << " at " << calendar[i - 1].getEnd().hour << ":" << calendar[i - 1].getEnd().minute 
            << " to " <<  calendar[i - 1].getEnd().hour + wantedHours << ":" << calendar[i - 1].getEnd().minute << "\n";
            return;
          }
        }
        // Time ending {17,0};
        double endHours = (double)currMeets[currSize - 1].getEnd().hour + (double)currMeets[currSize - 1].getEnd().minute / 60.0; 
        double endCheck = 17.0 - endHours;

        if(endCheck >= wantedHours) {
          std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year 
          << " at " << currMeets[currSize - 1].getEnd().hour << ":" << currMeets[currSize - 1].getEnd().minute
          << " to " << currMeets[currSize - 1].getEnd().hour + wantedHours << ":" << currMeets[currSize - 1].getEnd().minute << "\n";
          return;
        }
        updateDate(currDate);
      }
    }
  }


}

void Controller::findSlotWithCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  std::cout<<"In the current calendar:\n";
  findSlotCommand(splitted, calendar);
  
  Date currDate{0,0,0};
  convert.stringToDate(splitted[1], currDate);
  double wantedHours = convert.stringToDouble(splitted[2]);
  char* fileName = convert.stringToChar(splitted[3]);

  std::cout<<"In " << fileName << " calendar:\n";

  Vector<Meet> newCalendar;
  Vector<Date> newHolidays;
  getMeetings(fileName, newCalendar, newHolidays);

  int newCalendarSize = newCalendar.getSize();
  int newHolidaySize = newHolidays.getSize();

  bool isHoliday = false;
  while(true) {
    isHoliday = false;
    for(int i = 0; i < newHolidaySize; i++) {
      if(currDate == newHolidays[i]) {
        updateDate(currDate);
        isHoliday = true;
        break;
      }
    }


    if(isHoliday) continue;
    else {
      Time beginning {8,0};
      Vector<Meet> currMeets;
      for(int i = 0; i < newCalendarSize; i++)
        if(newCalendar[i].getDate() == currDate && newCalendar[i].getStart() >= beginning)
          currMeets.push_back(newCalendar[i]);

      int currSize = currMeets.getSize();

      if(currSize == 0) {
        std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year << " at 8:00 to " << 8 + wantedHours << ":00\n";
        return;
      }
      else {
        sortCalendar(currMeets);
        for(int i = 0; i < currSize; i++) currMeets[i].print();
        double beginHours = (double)currMeets[0].getStart().hour + (double)currMeets[0].getStart().minute / 60.0;
        double beginCheck = beginHours - 8.0;
        if(beginCheck >= wantedHours){
          std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year << " at 8:00 to " << 8 + wantedHours << ":00\n";
          return;
        }

        for(int i = 1; i < currSize; i++) {
          double currEnd = (double)newCalendar[i - 1].getEnd().hour + (double)newCalendar[i - 1].getEnd().minute / 60.0;
          double currStart = (double)newCalendar[i].getStart().hour + (double)newCalendar[i].getStart().minute / 60.0;

          double currFree = currStart - currEnd;
          if(currFree >= wantedHours) {
            std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year 
            << " at " << currMeets[i - 1].getEnd().hour << ":" << currMeets[i - 1].getEnd().minute 
            << " to " <<  currMeets[i - 1].getEnd().hour + wantedHours << ":" << currMeets[i - 1].getEnd().minute << "\n";
            return;
          }
        }
        // Time ending {17,0};
        double endHours = (double)currMeets[currSize - 1].getEnd().hour + (double)currMeets[currSize - 1].getEnd().minute / 60.0; 
        double endCheck = 17.0 - endHours;

        if(endCheck >= wantedHours) {
          std::cout<< "There is a free time for a meet on " << currDate.day << "." << currDate.month << "." << currDate.year 
          << " at " << currMeets[currSize - 1].getEnd().hour << ":" << currMeets[currSize - 1].getEnd().minute
          << " to " << currMeets[currSize - 1].getEnd().hour + wantedHours << ":" << currMeets[currSize - 1].getEnd().minute << "\n";
          return;
        }
        updateDate(currDate);
      }
    }
  }
}

void Controller::mergeCommand(Vector<String>& splitted, Vector<Meet>& calendar) {
  char* newFile = convert.stringToChar(splitted[1]);
  Vector<Meet> newCalendar;
  Vector<Date> newHolidays;
  getMeetings(newFile, newCalendar, newHolidays);

  int calendarSize = calendar.getSize();
  int holidaySize = holidays.getSize();

  int newCalendarSize = newCalendar.getSize();
  int newHolidaySize = newHolidays.getSize();

  //adding the new holidays from the other calendar
  for(int i = 0; i < newHolidaySize; i++) {
    
    bool existing = false;
    
    for(int j = 0; j < holidaySize; j++) {
      if(holidays[j] == newHolidays[i]) {
        existing = true;
        break;
      }
    }

    if(existing) continue;
    else {
      while(true) {
        std::cout << "Do you want the date " << newHolidays[i].day << "." << newHolidays[i].month << "." << newHolidays[i].year << " to be set as holiday\nType y/n(yes/no): ";
        char answer;
        std::cin>>answer;
        std::cin.ignore();
        if(answer == 'n') break;
        else if (answer == 'y') {
          holidays.push_back(newHolidays[i]);
          break;
        }
      }
    }
  }
  

  // adding the meets from the other calendar
  for(int i = 0; i < newCalendarSize; i++) {

    Time newStartTemp{newCalendar[i].getStart().hour, newCalendar[i].getStart().minute};
    Time newEndTemp{newCalendar[i].getEnd().hour, newCalendar[i].getEnd().minute};
    Date newDateTemp{newCalendar[i].getDate().day, newCalendar[i].getDate().month, newCalendar[i].getDate().year};
    if(checkIfFree(newDateTemp, newStartTemp, newEndTemp)) {
      calendar.push_back(newCalendar[i]);
    } else {
      while(true) {
        std::cout<<"There is a conflict with ";
        newCalendar[i].print();
        std::cout<<"Do you want to change(add) or not. Type y/n(yes/no): ";
        char answer;
        std::cin>>answer; 
        std::cin.ignore();
        if(answer == 'n') break;
        else if(answer == 'y') {
          
          while(true) {
            std::cout<<"What do you want to change: 1.Date or 2.Times :";
            int answer = 0;
            std::cin>>answer;
            if(answer == 1) {
             while(true) {
              std::cout<<"Type the new date in dd.mm.yyyy format: ";
              String date;
              std::cin>>date;
              Date newDate{0,0,0};
              convert.stringToDate(date, newDate);
              if(!valid.validateDate(newDate)) continue;
              if(checkIfFree(newDate, newStartTemp, newEndTemp)) {
                newCalendar[i].setDate(newDate);
                calendar.push_back(newCalendar[i]);
                break;
              } 
            }
             break;
            }
            else if(answer == 2) {
              while(true) {
                std::cout<<"Enter the new starting time in hh:mm format: ";
                String startTime;
                std::cin>>startTime;
                Time newStart{0,0};
                convert.stringToTime(startTime, newStart);
                if(!valid.validateTime(newStart)) continue;
                std::cout<<"Enter the new starting time in hh:mm format: ";
                String endTime;
                std::cin>>endTime;
                Time newEnd{0,0};
                convert.stringToTime(startTime, newEnd);
                if(!valid.validateTime(newEnd)) continue;
                if(checkIfFree(newDateTemp, newStart, newEnd)) {
                  newCalendar[i].setStart(newStart);
                  newCalendar[i].setEnd(newEnd);
                  calendar.push_back(newCalendar[i]);
                  break;
                }
              }
              break;
            }
          }
        }
      }
    }
  }
  
  Vector<Meet> tempCal;
  int updatedCalendarSize = calendar.getSize();
  int updatedHolidaySize = holidays.getSize();
  for(int i = 0; i < updatedCalendarSize; i++) {
    bool isHolidayed = false;
    for(int j = 0; j < updatedHolidaySize; j++) {
      if(holidays[j] == calendar[i].getDate()) {
        isHolidayed = true;
        break;
      }
    }
    if(isHolidayed) {
      continue;
    }
    else {
      tempCal.push_back(calendar[i]);
    }
  }
  calendar = tempCal;
}

void Controller::start() {
  String command;
  char currentFile[128];
  while(true) {
    std::cout<<"First enter a file name to start: ";
    std::cin>>currentFile;
    std::cin.ignore();
    int length = strlen(currentFile);
    if(length < 5 || currentFile[length - 1] != 't'
                  || currentFile[length - 2] != 'x' 
                  || currentFile[length - 3] != 't' 
                  || currentFile[length - 4] != '.') {
      std::cout<<"Please enter a file name with .txt extension at the end\n";
      continue;
    }
    break;
  }
  std::ofstream test(currentFile, std::ofstream::app);
  test.close();
  getMeetings(currentFile, calendar, holidays);

  while(true){
    std::cout<<"Enter the command you want to perform: ";
    Vector<String> splitted;
    char temp[256];
    splitted.clear();
    command = "";
    std::cin.getline(temp, 256);
    command = temp;
    splitted = getSplittedCommand(command);

    int commandIndex = getCommand(splitted, commands);

    switch(commandIndex) {
      case 0: {
        if(valid.validateOpen(splitted)) {
          std::cout<< splitted[1]<< " was opened \n";
          char* newFile = convert.stringToChar(splitted[1]);
          strcpy(currentFile, newFile);
          std::ofstream temp(currentFile, std::ofstream::app);
          temp.close();

          Vector<Meet> tempo;
          Vector<Date> tempD;
          getMeetings(currentFile, tempo, tempD);
          calendar = tempo;
          holidays = tempD;

        }
        break;
      }
      case 1: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateClose(splitted)) {   
          std::cout << currentFile << " was closed.\n";
          strcpy(currentFile, ".");


        }
        break;
      }
      case 2: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateSave(splitted)) {
          SaveCalendarToFile(currentFile, calendar);
          std::cout << "Calendar was saved to " << currentFile << '\n';

        }
        break;
      }
      case 3: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateSaveAs(splitted)) {
          std::cout<<"Calendar was saved to " << splitted[1] << '\n';
          char* otherFile = convert.stringToChar(splitted[1]);
          std::ofstream newfile(otherFile);
          newfile.close();
          SaveCalendarToFile(otherFile, calendar);

        }
        break;
      }
      case 4: {
        if(valid.validateExit(splitted)) {
          std::cout<<"Exiting from the program...\n";
          return;
        }
      }
      case 5: {
        if(valid.validateHelp(splitted)) {
          helpCommand();
          break;
        }
        break;
      }
      case 6: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateBook(splitted)){
          bookCommand(splitted, calendar);
          break;
        }
        break;
      }
      case 7: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateUnbook(splitted)) {
          unbookCommand(splitted, calendar);
          std::cout<<"The meet was deleted from your calendar\n";
        }
        break;
      }
      case 8: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateAgenda(splitted)) {
          angendaCommand(splitted, calendar);
        }
        break;
      }
      case 9: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateChange(splitted)) {
          changeCommand(splitted, calendar);
        }
        break;
      }
      case 10: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateFind(splitted)) {
          findCommand(splitted, calendar);
        }
        break;
      }
      case 11: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateHoliday(splitted)) {
          holidayCommand(splitted, calendar);
        }
        break;
      }
      case 12: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateBusyDays(splitted)) {
          busyDaysCommand(splitted, calendar);
        }
        break;
      }
      case 13: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateFindSlot(splitted)){
          findSlotCommand(splitted, calendar);
        }
        break;
      }
      case 14: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateFindSlotWith(splitted)){
          findSlotWithCommand(splitted, calendar);
        }
        break;
      }
      case 15: {
        if(strlen(currentFile) < 5) {
          std::cout << "Please open a file first\n";
          break;
        }
        if(valid.validateMerge(splitted)){
          mergeCommand(splitted, calendar);
        }
        break;
      }
      default: {
        std::cout<<"Wrong command\n";
        break;
      }
    }
  }
}