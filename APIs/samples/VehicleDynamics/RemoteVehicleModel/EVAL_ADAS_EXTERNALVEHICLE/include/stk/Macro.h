
#pragma once

#include "stk/STK.h"

#define NATIVE_INT size_t

#ifndef PI
#define PI 3.1415926535897932384626
#endif //PI

//macros utilitaires
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_BEGIN(a) (a)
#define ARRAY_END(a) (a+(sizeof(a)/sizeof(a[0])))
#define LIMIT_INTERVAL(A,B,C) ((B<A) ? A : ((B>C) ? C : B))
#define SIGNE_DE(A) ((A>=0) ? 1 : -1)
#if defined(WIN32) && (_MSC_VER<1600)
 #define CMAX std::_cpp_max
 #define CMIN std::_cpp_min
 #define ISNAN(x) _isnan(x)
#else
 #include <algorithm>
 #ifdef min
  #undef min
 #endif
 #ifdef max
  #undef max
 #endif
 #define CMAX std::max
 #define CMIN std::min
 #if defined(WIN32)
  #define ISNAN(x) _isnan(x)
 #else
  #include <math.h>
  #define ISNAN(x) isnan(x)
 #endif
#endif
#define ZERO_ARRAY(a) {memset(&a[0], 0, sizeof(a));}
#define IS_CLOSE( A, B, TOL ) (fabs((A) - (B))<TOL)

#define DECALAGE(STRUCT,MEMBRE) (NATIVE_INT)(&((STRUCT*)NULL)->MEMBRE)
#define GET_MEMBER(TYPE,OBJ,DECALAGE) (*(TYPE*)(((char*)&OBJ)+DECALAGE))

const size_t	kUnusedIndex	= (size_t) -1;

#if (defined(WIN32) && (_MSC_VER >= 1800)) || !defined(WIN32)
#include <stdint.h>
#else
typedef char                int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
#endif

