#pragma once 
#include "Meet.h"
#include <iostream>
#include <cstring>

Meet::Meet() {
  date.day = 1;
  date.month = 1;
  date.year = 1970;

  start.hour = 0;
  start.minute = 0;

  end.hour = 0;
  end.minute = 0;

  holiday = false;

  name = nullptr;
  note = nullptr;
}

Meet::Meet(Date& _date, const char* _name, const char* _note, Time& _start, Time& _end) {
  date.day = _date.day;
  date.month = _date.month;
  date.year = _date.year;

  name = new char[strlen(_name) + 1];
  strcpy(name, _name);
  
  note = new char[strlen(_note) + 1];
  strcpy(note, _note);
  // std::cout<<_note;
  start.hour = _start.hour;
  start.minute = _start.minute;


  end.hour = _end.hour;
  end.minute = _end.minute;

  holiday = false;
}

Meet::Meet(const Meet& other) {
  date.day = other.date.day;
  date.month = other.date.month;
  date.year = other.date.year;

  name = new char[strlen(other.name) + 1];
  strcpy(name, other.name);

  note = new char[strlen(other.note) + 1];
  strcpy(note, other.note);

  start.hour = other.start.hour;
  start.minute = other.start.minute;


  end.hour = other.end.hour;
  end.minute = other.end.minute;

  holiday = other.holiday;
}

Meet Meet::operator=(const Meet& other) {
  if(this != &other) {
    date.day = other.date.day;
    date.month = other.date.month;
    date.year = other.date.year;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    note = new char[strlen(other.note) + 1];
    strcpy(note, other.note);

    start.hour = other.start.hour;
    start.minute = other.start.minute;


    end.hour = other.end.hour;
    end.minute = other.end.minute;
    holiday = other.holiday;
  }
  return *this;
}

Meet::~Meet() {
  delete[] name;
  delete[] note;
}
Date Meet::getDate() const{
  return date;
}
Time Meet::getStart() const{
  return this->start;
}
Time Meet::getEnd() const{
  return end;
}
char* Meet::getName() const{
  return name;
}
char* Meet::getNote() const{
  return note;
}
bool Meet::getHoliday() const{
  return holiday;
}

void Meet::setHoliday(bool _holiday) {
    holiday = _holiday;
  }

void Meet::print() {
  std::cout<<date.day << "." << date.month << "."<< date.year 
  << " Meet's name: " << name 
  << " Meet's note: " << note 
  << " start: " << start.hour << ":"<< start.minute 
  << " end: "<<end.hour<<":"<<end.minute <<'\n';
}

void Meet::setNote(const char* _note) {
  delete[] note;

  note = new char[strlen(_note) + 1];
  strcpy(note, _note);
}

void Meet::setName(const char* _name) {
  delete[] name;

  name = new char[strlen(_name) + 1];
  strcpy(name, _name);
}

void Meet::setDate(Date& _date) {
  date.day = _date.day;
  date.month = _date.month;
  date.year = _date.year;
}

void Meet::setStart(Time& _start) {
  start.hour = _start.hour;
  start.minute = _start.minute;
}

void Meet::setEnd(Time& _end) {
  end.hour = _end.hour;
  end.minute = _end.minute;
}