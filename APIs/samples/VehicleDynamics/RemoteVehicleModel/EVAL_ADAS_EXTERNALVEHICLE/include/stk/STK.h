
#pragma once

#if !defined(WIN32)
	#define STK_API
	#define STK_EXT
	#define STK_EXPORT_COMPARE(T)
	#define STK_EXPORT_VECTOR(T)
#else
	#ifdef STK_EXPORTS
		#define STK_API __declspec(dllexport)
		#define STK_EXT
	#else
		#define STK_API __declspec(dllimport)
		#define STK_EXT
	#endif

	#define STK_EXPORT_COMPARE(T) \
inline bool operator<(const T&,const T&) {return false;} \
inline bool operator==(const T&,const T&) {return false;}

	#define STK_EXPORT_VECTOR(T) \
STK_EXT template class STK_API std::allocator<T >; \
STK_EXT template class STK_API std::vector<T >;

#endif // WIN32

