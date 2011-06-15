/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include "PolyGlobals.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
using std::vector;

using namespace std;

typedef std::string Str;
typedef std::wstring WStr;

void utf8toWStr(WStr& dest, const Str& src);
void wstrToUtf8(Str& dest, const WStr& src);	

namespace Polycode {

	/**
	* Unicode-friendly string. The Polycode String class wraps around STL wstring to support Unicode text in the engine. You can request data from it in different encodings (currently only UTF-8) or plain char data. It is mostly just a wrapper around STL created for easier Unicode support, LUA bindings and convenience methods.
	*/
	class _PolyExport String {
		public:
		
			/**
			* Default constructor
			*/			
			String();
			
			/**
			* Initializes the string from a pointer to wide character buffer.
			*/			
			String(const wchar_t *str);
			
			/**
			* Initializes the string from a pointer to wide character buffer of a certain size.
			*/						
			String(const wchar_t *str, size_t n);		
			
			/**
			* Initializes the string from a regular character buffer.
			*/									
			String(const char *str);
			
			/**
			* Initializes the string from an STL string.
			*/												
			String(string str);
			
			/**
			* Initializes the string from an STL wstring.
			*/															
			String(wstring str);
		
			virtual ~String();
		
			/**
			* Return the length of the string.
			*/														
			size_t size() { return contents.size(); }
			
			/**
			* Return the length of the string.
			*/			
			size_t length() { return contents.size(); }
		
			/**
			* Return the string and an STL string.
			*/		
			string getSTLString();
			
			/**
			* Return the string and an STL wstring.
			*/			
			wstring getSTLWString();
		
			/**
			* Returns the substring of the string.
			* @param pos Position of a character in the current string object to be used as starting character for the substring.
			* @param n Length of the substring.
			* @return A string object containing a substring of the current object.
			*/					
			String substr(size_t pos = 0, size_t n = wstring::npos) const { return String(contents.substr(pos,n)); }

			/**
			* Find last occurrence of content in string. 
			* @param str String to be searched for in the object.
			* @param pos Position of the last character in the string to be taken into consideration for possible matches. The default value indicates that the entire string is searched.
			* @return The position of the last occurrence in the string of the searched content
			*/							
			size_t rfind ( const String &str, size_t pos = wstring::npos ) const { return contents.rfind(str.contents, pos); }
			
			/**
			* Find content in string. 
			* @param str String to be searched for in the object.
			* @param pos Position of the first character in the string to be taken into consideration for possible matches. The default value indicates that the entire string is searched.
			* @return The position of the first occurrence in the string of the searched content
			*/										
			size_t find ( const String &str, size_t pos = 0 ) const { return contents.find(str.contents, pos); }
			
			/**
			* Find character in string from the end. Searches the string from the end for any of the characters that are part of the passed string.
			* @param str String containing the characters to search for.
			* @param pos Position of the last character in the string to be taken into consideration for possible matches. The default value indicates that the entire string is searched.
			* @return The position of the last occurrence in the string of any of the characters searched for.
			*/													
			size_t find_last_of(const String& str, size_t pos = wstring::npos ) { return contents.find_last_of(str.contents, pos); }
		
			inline String operator + (const char *str) const { return String(contents + String(str).contents); }		
			inline String operator + (const String &str) const { return String(contents + str.contents); }		
			String operator += (const String &str) { contents = contents + str.contents; return *this; }		
			String operator = (const String &str) {  contents = str.contents; return *this;}
			inline bool operator == (const String &str) const {  return (str.contents == contents); }		
			inline bool operator != (const String &str) const {  return (str.contents != contents); }		
			inline wchar_t operator [] ( const size_t i ) const { return contents[i]; }

			/**
			* Returns the lowercase version of the string.
			* @return Lowercase version of the stirng.
			*/															
			String toLowerCase();
			
			/**
			* Returns the uppercase version of the string.
			* @return Uppercase version of the stirng.
			*/																		
			String toUpperCase();
					
			/**
			* Splits the string by the specified delimeter
			* @param delim The delimeter to split by.
			* @return An STL vector of the split parts of the string. 
			*/																				
			vector<String> split(const String &delim);

			/**
			* Replaces parts of the string with another string.
			* @param what Ocurrences of which string to replace in this string.
			* @param withWhat What to replace them with.
			* @return A new string with the specified matches replaced with the specified string.
			*/																							
			String replace(const String &what, const String &withWhat);
			
			/**
			* Convert a Number to a String.
			* @param value Number to convert.
			* @return A string converted from the Number.
			*/																										
			static String NumberToString(Number value);
		
			/**
			* Pointer to char data.
			* @return A pointer to char data.
			*/																												
			const char *c_str();
			
			/**
			* Pointer to wchar data.
			* @return A pointer to wchar data.
			*/																															
			const wchar_t *wc_str();

			/**
			* Pointer to wchar data.
			* @return A pointer to wchar data.
			*/																																	
			const wchar_t *data(){ return contents.data(); }

			/**
			* Returns data with the specified encoding. Currently the only supported encoding is String::ENCODING_UTF8
			* @param encoding The encoding to use.
			* @return A pointer to the data using specified encoding.
			* @see getDataSizeWithEncoding()
			*/																															
			const char *getDataWithEncoding(int encoding);
			
			/**
			* Returns the size of the data with the specified encoding. Currently the only supported encoding is String::ENCODING_UTF8
			* @param encoding The encoding to use.
			* @return The size the data would take up if returned with this encoding.
			* @see getDataWithEncoding()
			*/																																				
			size_t getDataSizeWithEncoding(int encoding);
					
			
			/**
			* Sets the data for the string using specified encoding.
			* @param data Data to set the string with.
			* @param encoding The encoding to use.
			*/																																		
			void setDataWithEncoding(char *data, int encoding);
			
			/**
			* STL wstring version of the string.
			*/																																					
			wstring contents;	
			
			/**
			* STL string version of the string.
			*/																																								
			string s_contents;
			
			/**
			* UTF-8 encoding.
			*/																																							
			static const int ENCODING_UTF8 = 0; 
			
		
		private:
		
	};

	static inline String operator+ (const char *str, const String &rstr) { return String(String(str).contents + rstr.contents); }
	static inline String operator+ (const wchar_t *str, const String &rstr) { return String(String(str).contents + rstr.contents); }	
	static inline String operator+ (const wchar_t str, const String &rstr) { wstring tmp=L" "; tmp[0] = str; return String(tmp + rstr.contents); }		
}
