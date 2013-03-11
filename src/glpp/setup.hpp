/**
 * Copyright (c) 2012 Konstantinos Paliouras <squarious _ gmail _dot com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GLPP_SETUP_HPP_INCLUDED
#define GLPP_SETUP_HPP_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////
// Platform

#define GLPP_PLATFORM_UNKNOWN		0x00000000
#define GLPP_PLATFORM_WINDOWS		0x00010000
#define GLPP_PLATFORM_LINUX			0x00020000
#define GLPP_PLATFORM_APPLE			0x00040000
//#define GLPP_PLATFORM_IOS			0x00080000
#define GLPP_PLATFORM_ANDROID		0x00100000
#define GLPP_PLATFORM_CHROME_NACL	0x00200000
#define GLPP_PLATFORM_UNIX			0x00400000

#ifdef GLPP_FORCE_PLATFORM_UNKNOWN
#	define GLPP_PLATFORM GLPP_PLATFORM_UNKNOWN
#elif defined(__APPLE__)
#   define GLPP_PLATFORM GLPP_PLATFORM_APPLE
#elif defined(_WIN32)
#	define GLPP_PLATFORM GLPP_PLATFORM_WINDOWS
#elif defined(__native_client__)
#	define GLPP_PLATFORM GLPP_PLATFORM_CHROME_NACL
#elif defined(ANDROID)
#   define GLPP_PLATFORM GLPP_PLATFORM_ANDROID
#elif defined(__linux)
#   define GLPP_PLATFORM GLPP_PLATFORM_LINUX
#elif defined(__unix)
#   define GLPP_PLATFORM GLPP_PLATFORM_UNIX
#else
#	define GLPP_PLATFORM GLPP_PLATFORM_UNKNOWN
#endif//

// Report platform detection
#if(defined(GLPP_MESSAGES) && !defined(GLPP_MESSAGE_PLATFORM_DISPLAYED))
#	define GLPP_MESSAGE_PLATFORM_DISPLAYED
#	if(GLPP_PLATFORM & GLPP_PLATFORM_WINDOWS)
#		pragma message("GLPP: Windows platform detected")
//#	elif(GLPP_PLATFORM & GLPP_PLATFORM_IOS)
//#		pragma message("GLPP: iOS platform detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_APPLE)
#		pragma message("GLPP: Apple platform detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_LINUX)
#		pragma message("GLPP: Linux platform detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_UNIX)
#		pragma message("GLPP: UNIX platform detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_ANDROID)
#		pragma message("GLPP: Android platform detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_CHROME_NACL)
#		pragma message("GLPP: Chrone Native Client detected")
#	elif(GLPP_PLATFORM & GLPP_PLATFORM_UNKNOWN)
#		pragma message("GLPP: platform unknown")
#	else
#		pragma message("GLPP: platform not detected")
#	endif
#endif//GLPP_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Compiler

// User defines: GLPP_FORCE_COMPILER_UNKNOWN
// TODO ? __llvm__

#define GLPP_COMPILER_UNKNOWN		0x00000000

// Visual C++ defines
#define GLPP_COMPILER_VC			0x01000000
#define GLPP_COMPILER_VC2			0x01000010
#define GLPP_COMPILER_VC4			0x01000020
#define GLPP_COMPILER_VC5			0x01000030
#define GLPP_COMPILER_VC6			0x01000040
#define GLPP_COMPILER_VC2002		0x01000050
#define GLPP_COMPILER_VC2003		0x01000060
#define GLPP_COMPILER_VC2005		0x01000070
#define GLPP_COMPILER_VC2008		0x01000080
#define GLPP_COMPILER_VC2010		0x01000090
#define GLPP_COMPILER_VC2011		0x010000A0

// GCC defines
#define GLPP_COMPILER_GCC			0x02000000
#define GLPP_COMPILER_GCC_LLVM		0x02000001
#define GLPP_COMPILER_GCC_CLANG		0x02000002
#define GLPP_COMPILER_GCC30			0x02000010
#define GLPP_COMPILER_GCC31			0x02000020
#define GLPP_COMPILER_GCC32			0x02000030
#define GLPP_COMPILER_GCC33			0x02000040
#define GLPP_COMPILER_GCC34			0x02000050
#define GLPP_COMPILER_GCC35			0x02000060
#define GLPP_COMPILER_GCC40			0x02000070
#define GLPP_COMPILER_GCC41			0x02000080
#define GLPP_COMPILER_GCC42			0x02000090
#define GLPP_COMPILER_GCC43			0x020000A0
#define GLPP_COMPILER_GCC44			0x020000B0
#define GLPP_COMPILER_GCC45			0x020000C0
#define GLPP_COMPILER_GCC46			0x020000D0
#define GLPP_COMPILER_GCC47			0x020000E0
#define GLPP_COMPILER_GCC48			0x020000F0
#define GLPP_COMPILER_GCC49			0x02000100
#define GLPP_COMPILER_GCC50			0x02000200

// G++ command line to display defined
// echo "" | g++ -E -dM -x c++ - | sort

// Borland C++ defines. How to identify BC?
#define GLPP_COMPILER_BC			0x04000000
#define GLPP_COMPILER_BCB4			0x04000100
#define GLPP_COMPILER_BCB5			0x04000200
#define GLPP_COMPILER_BCB6			0x04000300
//#define GLPP_COMPILER_BCBX			0x04000400 // What's the version value?
#define GLPP_COMPILER_BCB2009		0x04000500

// CodeWarrior
#define GLPP_COMPILER_CODEWARRIOR	0x08000000

// CUDA
#define GLPP_COMPILER_CUDA			0x10000000
#define GLPP_COMPILER_CUDA30		0x10000010
#define GLPP_COMPILER_CUDA31		0x10000020
#define GLPP_COMPILER_CUDA32		0x10000030
#define GLPP_COMPILER_CUDA40		0x10000040
#define GLPP_COMPILER_CUDA41		0x10000050
#define GLPP_COMPILER_CUDA42		0x10000060

// Clang
#define GLPP_COMPILER_CLANG			0x20000000
#define GLPP_COMPILER_CLANG26		0x20000010
#define GLPP_COMPILER_CLANG27		0x20000020
#define GLPP_COMPILER_CLANG28		0x20000030
#define GLPP_COMPILER_CLANG29		0x20000040
#define GLPP_COMPILER_CLANG30		0x20000050
#define GLPP_COMPILER_CLANG31		0x20000060
#define GLPP_COMPILER_CLANG32		0x20000070
#define GLPP_COMPILER_CLANG33		0x20000080

// LLVM GCC
#define GLPP_COMPILER_LLVM_GCC		0x40000000

// Intel
#define GLPP_COMPILER_INTEL			0x80000000
#define GLPP_COMPILER_INTEL9		0x80000010
#define GLPP_COMPILER_INTEL10_0		0x80000020
#define GLPP_COMPILER_INTEL10_1		0x80000030
#define GLPP_COMPILER_INTEL11_0		0x80000040
#define GLPP_COMPILER_INTEL11_1		0x80000050
#define GLPP_COMPILER_INTEL12_0		0x80000060
#define GLPP_COMPILER_INTEL12_1		0x80000070
#define GLPP_COMPILER_INTEL13_0		0x80000080

// Build model
#define GLPP_MODEL_32				0x00000010
#define GLPP_MODEL_64				0x00000020

// Force generic C++ compiler
#ifdef GLPP_FORCE_COMPILER_UNKNOWN
#	define GLPP_COMPILER GLPP_COMPILER_UNKNOWN

#elif defined(__INTEL_COMPILER)
#	if __INTEL_COMPILER == 900
#		define GLPP_COMPILER GLPP_COMPILER_INTEL9
#	elif __INTEL_COMPILER == 1000
#		define GLPP_COMPILER GLPP_COMPILER_INTEL10_0
#	elif __INTEL_COMPILER == 1010
#		define GLPP_COMPILER GLPP_COMPILER_INTEL10_1
#	elif __INTEL_COMPILER == 1100
#		define GLPP_COMPILER GLPP_COMPILER_INTEL11_0
#	elif __INTEL_COMPILER == 1110
#		define GLPP_COMPILER GLPP_COMPILER_INTEL11_1
#	elif __INTEL_COMPILER == 1200
#		define GLPP_COMPILER GLPP_COMPILER_INTEL12_0
#	elif __INTEL_COMPILER == 1210
#		define GLPP_COMPILER GLPP_COMPILER_INTEL12_1
#	elif __INTEL_COMPILER == 1300
#		define GLPP_COMPILER GLPP_COMPILER_INTEL13_0
#	else
#		define GLPP_COMPILER GLPP_COMPILER_INTEL
#	endif


// Visual C++
#elif defined(_MSC_VER)
#	if _MSC_VER == 900
#		define GLPP_COMPILER GLPP_COMPILER_VC2
#	elif _MSC_VER == 1000
#		define GLPP_COMPILER GLPP_COMPILER_VC4
#	elif _MSC_VER == 1100
#		define GLPP_COMPILER GLPP_COMPILER_VC5
#	elif _MSC_VER == 1200
#		define GLPP_COMPILER GLPP_COMPILER_VC6
#	elif _MSC_VER == 1300
#		define GLPP_COMPILER GLPP_COMPILER_VC2002
#	elif _MSC_VER == 1310
#		define GLPP_COMPILER GLPP_COMPILER_VC2003
#	elif _MSC_VER == 1400
#		define GLPP_COMPILER GLPP_COMPILER_VC2005
#	elif _MSC_VER == 1500
#		define GLPP_COMPILER GLPP_COMPILER_VC2008
#	elif _MSC_VER == 1600
#		define GLPP_COMPILER GLPP_COMPILER_VC2010
#	elif _MSC_VER == 1700
#		define GLPP_COMPILER GLPP_COMPILER_VC2011
#	else//_MSC_VER
#		define GLPP_COMPILER GLPP_COMPILER_VC
#	endif//_MSC_VER

// Clang
#elif defined(__clang__)
#	if(__clang_major__ == 2) && (__clang_minor__ == 6)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG26
#	elif(__clang_major__ == 2) && (__clang_minor__ == 7)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG27
#	elif(__clang_major__ == 2) && (__clang_minor__ == 8)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG28
#	elif(__clang_major__ == 2) && (__clang_minor__ == 9)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG29
#	elif(__clang_major__ == 3) && (__clang_minor__ == 0)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG30
#	elif(__clang_major__ == 3) && (__clang_minor__ == 1)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG31
#	elif(__clang_major__ == 3) && (__clang_minor__ == 2)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG32
#	elif(__clang_major__ == 3) && (__clang_minor__ == 3)
#		define GLPP_COMPILER GLPP_COMPILER_CLANG33
#	else
#		define GLPP_COMPILER GLPP_COMPILER_CLANG
#   endif

// G++
#elif(defined(__GNUC__) || defined(__MINGW32__))// || defined(__llvm__) || defined(__clang__)
#   if defined (__llvm__)
#       define GLPP_COMPILER_GCC_EXTRA GLPP_COMPILER_GCC_LLVM
#   elif defined (__clang__)
#       define GLPP_COMPILER_GCC_EXTRA GLPP_COMPILER_GCC_CLANG
#   else
#       define GLPP_COMPILER_GCC_EXTRA 0
#   endif
#
#	if   (__GNUC__ == 3) && (__GNUC_MINOR__ == 2)
#		define GLPP_COMPILER GLPP_COMPILER_GCC32
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
#		define GLPP_COMPILER GLPP_COMPILER_GCC33
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 4)
#		define GLPP_COMPILER GLPP_COMPILER_GCC34
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 5)
#		define GLPP_COMPILER GLPP_COMPILER_GCC35
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 0)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC40 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 1)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC41 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 2)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC42 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC43 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC44 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 5)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC45 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 6)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC46 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC47 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC48 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 9)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC49 | GLPP_COMPILER_GCC_EXTRA)
#	elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 0)
#		define GLPP_COMPILER (GLPP_COMPILER_GCC50 | GLPP_COMPILER_GCC_EXTRA)
#	else
#		define GLPP_COMPILER (GLPP_COMPILER_GCC | GLPP_COMPILER_GCC_EXTRA)
#	endif

// Borland C++
#elif defined(_BORLANDC_)
#	if defined(VER125)
#		define GLPP_COMPILER GLPP_COMPILER_BCB4
#	elif defined(VER130)
#		define GLPP_COMPILER GLPP_COMPILER_BCB5
#	elif defined(VER140)
#		define GLPP_COMPILER GLPP_COMPILER_BCB6
#	elif defined(VER200)
#		define GLPP_COMPILER GLPP_COMPILER_BCB2009
#	else
#		define GLPP_COMPILER GLPP_COMPILER_BC
#	endif

// Codewarrior
#elif defined(__MWERKS__)
#	define GLPP_COMPILER GLPP_COMPILER_CODEWARRIOR

#else
#	define GLPP_COMPILER GLPP_COMPILER_UNKNOWN
#endif

#ifndef GLPP_COMPILER
#error "GLPP_COMPILER undefined, your compiler may not be supported by GLPP. Add #define GLPP_COMPILER 0 to ignore this message."
#endif//GLPP_COMPILER

// Report compiler detection
#if(defined(GLPP_MESSAGES) && !defined(GLPP_MESSAGE_COMPILER_DISPLAYED))
#	define GLPP_MESSAGE_COMPILER_DISPLAYED
#	if(GLPP_COMPILER & GLPP_COMPILER_CUDA)
#		pragma message("GLPP: CUDA compiler detected")
#	elif(GLPP_COMPILER & GLPP_COMPILER_VC)
#		pragma message("GLPP: Visual C++ compiler detected")
#	elif(GLPP_COMPILER & GLPP_COMPILER_CLANG)
#		pragma message("GLPP: Clang compiler detected")
#	elif(GLPP_COMPILER & GLPP_COMPILER_LLVM_GCC)
#		pragma message("GLPP: LLVM GCC compiler detected")
#	elif(GLPP_COMPILER & GLPP_COMPILER_GCC)
#       if(GLPP_COMPILER == GLPP_COMPILER_GCC_LLVM)
#           pragma message("GLPP: LLVM GCC compiler detected")
#       elif(GLPP_COMPILER == GLPP_COMPILER_GCC_CLANG)
#           pragma message("GLPP: CLANG compiler detected")
#       else
#           pragma message("GLPP: GCC compiler detected")
#       endif
#	elif(GLPP_COMPILER & GLPP_COMPILER_BC)
#		pragma message("GLPP: Borland compiler detected but not supported")
#	elif(GLPP_COMPILER & GLPP_COMPILER_CODEWARRIOR)
#		pragma message("GLPP: Codewarrior compiler detected but not supported")
#	else
#		pragma message("GLPP: Compiler not detected")
#	endif
#endif//GLPP_MESSAGE


/////////////////
// C++ Version //
#define GLPP_LANG_CXX			(0 << 0)
#define GLPP_LANG_CXX98			((1 << 1) | GLPP_LANG_CXX)
#define GLPP_LANG_CXX03			((1 << 2) | GLPP_LANG_CXX98)
#define GLPP_LANG_CXX0X			((1 << 3) | GLPP_LANG_CXX03)
#define GLPP_LANG_CXX11			((1 << 4) | GLPP_LANG_CXX0X)
#define GLPP_LANG_CXXMS			(1 << 5)
#define GLPP_LANG_CXXGNU			(1 << 6)

#if(defined(GLPP_FORCE_CXX11))
#	define GLPP_LANG GLPP_LANG_CXX11
#elif(defined(GLPP_FORCE_CXX03))
#	define GLPP_LANG GLPP_LANG_CXX03
#elif(defined(GLPP_FORCE_CXX98))
#	define GLPP_LANG GLPP_LANG_CXX98
#else
//  -std=c++0x or -std=gnu++0x
#	if(((GLPP_COMPILER & GLPP_COMPILER_GCC) == GLPP_COMPILER_GCC) && defined(__GXX_EXPERIMENTAL_CXX0X__))
#		define GLPP_LANG GLPP_LANG_CXX0X
#	elif(((GLPP_COMPILER & GLPP_COMPILER_VC) == GLPP_COMPILER_VC) && defined(_MSC_EXTENSIONS))
#		define GLPP_LANG GLPP_LANG_CXXMS
#	elif(((GLPP_COMPILER & GLPP_COMPILER_VC) == GLPP_COMPILER_VC) && !defined(_MSC_EXTENSIONS))
#		if(GLPP_COMPILER >= GLPP_COMPILER_VC2010)
#			define GLPP_LANG GLPP_LANG_CXX0X
#		else
#			define GLPP_LANG GLPP_LANG_CXX98
#		endif//(GLPP_COMPILER == GLPP_COMPILER_VC2010)
#	elif((GLPP_COMPILER & GLPP_COMPILER_GCC) == GLPP_COMPILER_GCC) //&& defined(__STRICT_ANSI__))
#		define GLPP_LANG GLPP_LANG_CXX98
#	elif((GLPP_COMPILER & GLPP_COMPILER_CLANG) == GLPP_COMPILER_CLANG)
#		define GLPP_LANG GLPP_LANG_CXX98
#	else
#		define GLPP_LANG GLPP_LANG_CXX
#	endif
#endif


#if (GLPP_LANG == GLPP_LANG_CXX0X) || (GLPP_LANG == GLPP_LANG_CXX11)
#	include "cxx11_support.hpp"
#else
#	include "boost_support.hpp"
#endif


#endif
