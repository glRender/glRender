#ifndef __BASE_H__
#define __BASE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <sstream>
#include <fstream>
#include <functional>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <time.h>
#include <typeinfo>
#include <assert.h>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <stdint.h>
#include <codecvt>
#include <locale>

// Math
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_2PI                    6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }

    // std::hash wrapper for variadic parameters
    template<typename T>
    std::size_t hash(T p)
    {
        return std::hash<std::string>{}(p);
    }

    template<typename T0, typename ... Args>
    std::size_t hash(T0 p0, Args ... args)
    {
        return hash(p0) + hash(args...);
    }

}

inline std::vector<std::string> split(const std::string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

inline void replaceAll(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

// convert UTF-8 string to wstring
inline std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
inline std::string wstring_to_utf8(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}

// number of alphabets in UTF-8 string
inline std::size_t strlen_utf8(const std::string & str)
{
    std::size_t length = 0;
    for (char c : str)
    {
        if ((c & 0xC0) != 0x80)
        {
            ++length;
        }
    }
    return length;
}

#ifdef _WIN32
    typedef unsigned int uint;
#endif

#endif /* BASE_H_ */
