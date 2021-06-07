#pragma once
#include <iostream>

class String {
public:
	//constructors/destructor
	String();
	String(const char* other);
	String(const String& other);
	~String();

	//operators
	String& operator=(const String& other);
	String& operator=(const char* source);
	bool operator==(const String& other) const;
	bool operator==(const char* other) const;
	bool operator!=(const String& other) const;

	//remove last letter
	void pop_back();
	//add letter at the end
	void push_back(const char letter);

	//comibining 2 string into 1
	String operator+(const String& other);
	String operator+=(const char);
	//length comparison
	bool operator>(const String& other) const;
	//get letter at index position
	char operator[](const int index);
	//gets the length of the string
	int length() const;


	friend std::ostream& operator<<(std::ostream& out, const String& string);
	friend std::istream& operator>>(std::istream& in, String& string);

private:
	char* string;
	int len;
};