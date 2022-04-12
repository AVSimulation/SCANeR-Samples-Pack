// Interface Encoding: UTF8
#pragma once

#include "stk/STK.h"

#include <string>

namespace stk {

	STK_API void eatwhite(std::istream &in);

	STK_API void string_printf(std::string& s, const char* format, ...);
	STK_API void string_printf(std::wstring& s, const wchar_t* format, ...);
	
	STK_API bool FileExist(const char* name);
	STK_API bool FileExist(const wchar_t* name);

	STK_API bool IsSeparator(char c);
	STK_API bool IsAbsolutePath(const std::string& path);

	STK_API const char* JustDrive(const char* Name);// Optional drive letter, followed by a colon (:)
	STK_API const wchar_t* JustDrive(const wchar_t* Name);// Optional drive letter, followed by a colon (:)

	STK_API const char* JustFileName(const char* Name);
	STK_API const wchar_t* JustFileName(const wchar_t* Name);

	STK_API const char* JustExtension(const char* name); //with the '.' for ex: ".csv"
	STK_API const wchar_t* JustExtension(const wchar_t* name); //with the '.' for ex: ".csv"

	STK_API const char* WithoutExtension(const char* Name);
	STK_API const wchar_t* WithoutExtension(const wchar_t* Name);

	STK_API const char* JustDirName(const char *Name);
	STK_API const wchar_t* JustDirName(const wchar_t *Name);

	STK_API std::string GetApplicationPath();
	STK_API std::wstring GetApplicationPathW();

	STK_API std::string GetTemporaryPath();

	// Given the absolute current directory and an absolute file name, returns a relative file name.
	// For example, if the current directory is C:\foo\bar and the filename C:\foo\whee\text.txt is given,
	// GetRelativeFilename will return ..\whee\text.txt.
	// If the absoluteFilename is not absolute, return it
	STK_API std::string RelativeFilename(const std::string& absoluteDirectory, const std::string& absoluteFilename);

	STK_API std::string AbsoluteFilename(const std::string& currentDirectory, const std::string& relativeOrAbsoluteFilename, bool fixCase = false);
	
	// fix path separators, remove useless "../" and lowercase
	STK_API std::string NormalizePath( const std::string& path ); 

	// replace all "\" by "/" for system compatibility.
	// replace ":/" by ":\" to restore windows drive letter if necessary.
	STK_API std::string FixPathSeparators(const std::string & path);

	// If the file exists, it's renamed with a date/hour tag.
	// This is used to protect files from deletion.
	STK_API void MoveIfExists(const std::string& fileName );

	STK_API std::string RestoreCase(const std::string& fileName);

} //namespace
