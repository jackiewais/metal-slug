#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <sstream>
#include <string.h>


using namespace std;

class Util {

public:
		static void SplitElem(const std::string &s, char delim, std::vector<std::string> &elems) {
		    stringstream ss;
		    ss.str(s);
		    string item;
		    while (getline(ss, item, delim)) {
		        elems.push_back(item);
		    }
		};

		static std::vector<std::string> Split(const std::string &s, const char delim){
		    vector<string> elems;
		    SplitElem(s, delim, elems);
		    return elems;
		};
};

#endif
