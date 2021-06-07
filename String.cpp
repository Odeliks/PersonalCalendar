#pragma once 
#include "String.h"
#include <cstring>




String::String() {
	len = 0;
	string = nullptr;
}

String::String(const char* other) {
	if (other != nullptr) {
		len = strlen(other);
		string = new char[len + 1];
		for (int i = 0; i < len; i++) {
			string[i] = other[i];
		}
		string[len] = '\0';
	}
	else {
		len = 1;
		string = new char[len];
		string[0] = '\0';
	}
}

String::String(const String& other) {
	if (other.string != nullptr) {
		len = strlen(other.string);
		string = new char[len + 1];
		for (int i = 0; i < len; i++) {
			string[i] = other.string[i];
		}
		string[len] = '\0';
	}
	else {
		len = 1;
		string = new char[len];
		string[0] = '\0';
	}
}

String::~String() {
	delete[] string;
}

int String::length() const {
	return len;
}

String& String::operator=(const String& other) {

	if (this != &other) {
		delete[] string;
		len = other.len;
		string = new char[len + 1];
		for (int i = 0; i < len; i++) {
			string[i] = other.string[i];
		}
		string[len] = '\0';
	}
	return *this;
}

String& String::operator=(const char* source) {
	delete[] string;
	len = strlen(source);
	string = new char[len + 1];
	for (int i = 0; i < len; i++) {
		string[i] = source[i];
	}
	string[len] = '\0';
	return *this;
}

bool String::operator==(const String& other) const {
	if (len != other.len) 
		return false;
	return !strcmp(string, other.string);
}

bool String::operator==(const char* other) const {
	if(len != strlen(other)) {
		return false;
	}
	return !strcmp(string, other);
}

bool String::operator!=(const String& other) const {
	return !(other == *this);
}

void String::pop_back() {
	len = len - 1;
	string[len] = '\0';
}

void String::push_back(const char letter) {

	char* temp = new char[len + 2];
	for (int i = 0; i < len; i++) {
		temp[i] = string[i];
	}
	temp[len] = letter;
	temp[len + 1] = '\0';
	delete[] string;
	string = temp;
	len++;
}

String String::operator+(const String& other) {
	int bufferLength = len + other.len;
	char* buffer = new char[bufferLength + 1];
	for (int i = 0; string[i] != '\0'; i++) {
		buffer[i] = string[i];
	}
	for(int i = 0; other.string[i] != '\0';i++) {
		buffer[len + i] = other.string[i];
	}
	buffer[bufferLength] = '\0';
	String temp(buffer);

	return temp;
}

bool String::operator>(const String& other) const {
	return len > other.len;
}

char String::operator[](const int index) {
	if (index < 0 || index >= len) {
		return string[len];
	}
	else {
		return string[index];
	}
}

std::ostream& operator<<(std::ostream& out, const String& string) {

	out << string.string;

	return out;
}

std::istream& operator>>(std::istream& in, String& string) {

	char buffer[1024];
	in >> buffer;

	delete[] string.string;
	string.len = strlen(buffer);
	string.string = new char[string.len + 1];

	strcpy_s(string.string, strlen(buffer) + 1, buffer);

	return in;
}
