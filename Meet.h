#pragma once 
#include "Date.h"
#include "Time.h"

class Meet {
public:
  Meet();
  Meet(Date&, const char*, const char*, Time&, Time&);
  Meet(const Meet&);
  Meet operator=(const Meet&);
  ~Meet();

  //getters
  Date getDate() const;
  Time getStart() const;
  Time getEnd() const;
  char* getName() const;
  char* getNote() const;
  bool getHoliday() const;

  //setters
  void setHoliday(const bool);
  void setNote(const char*);
  void setName(const char*);
  void setDate(Date&);
  void setStart(Time&);
  void setEnd(Time&);


  void print();
public:
  Date date;
  Time start;
  Time end;
  char* name;
  char* note;
  bool holiday;
};