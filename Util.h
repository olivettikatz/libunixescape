/* Copyright 2013 Oliver Katz
 *
 * This file is part of LibUNIXEscape.
 *
 * LibUNIXEscape is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibUNIXEscape is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibUNIXEscape.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file Util.h
  *  \brief Basic utilities for all of LibUNIXEscape.
  *  Util.h contains console message formatting, macros to display debug messages,
  *  warnings, non-fatal errors and fatal errors. It also contains the testing system,
  *  which is very primitive, but hey. Lastly, it contains file IO for the basic loading
  *  of configuration/script files. */

/*! \def UE_MESSAGE_STREAM
 *  \brief The IO stream to output console messages to.
 *  This can easily be changed to cerr, if stdout conflicts with other messages. */

/*! \def UE_MESSAGE_PREFIX
 *  \brief The prefix to use for all console messages.
 *  Contains the file and line number location that the message originated from. */

/*! \def UE_MESSAGE_PREFIX_ERROR
 *  \brief The prefix to use for all errors. */

/*! \def UE_MESSAGE_PREFIX_WARNING
 *  \brief The prefix to use for all warnings. */

/*! \def UE_MESSAGE_PREFIX_DEBUG
 *  \brief The prefix to use for all debug messages. */

/*! \def UE_MESSAGE_PREFIX_TEST
 *  \brief The prefix to use for all test message. */

/*! \def UE_MESSAGE_DISPLAY(msg)
 *  \brief Displays text in \a msg to console. 
 *  Displays text with no prefix to stream defined in UE_MESSAGE_STREAM. */

/*! \def UE_FATAL(msg)
 *  \brief Displays fatal error to console, then halts program.
 *  After it displays the fatal error, it will throw a std::runtime_error
 *  exception, so that the source of the fatal error may be backtraced
 *  with a debugger. */

/*! \def UE_ERROR(msg)
 *  \brief Displays error to console, but doesn't halt program.
 *  Fun fact: the output to the console is identical to that of UE_FATAL. */

/*! \def UE_WARNING(msg)
 *  \brief Displays a warning to console. */

/*! \def UE_DEBUG(msg)
 *  \brief Displays a debug message to console. */

/*! \def UE_TEST_HEADER(name)
 *  \brief Denotes the beginning of a test.
 *  When you are testing something in a test file, use this at the beginning of a test
 *  to tell the user that a new test is starting.
 *
 *  For example:
 *  \include TestUtil.cpp */

/*! \def UE_TEST_ASSERT(expected, recieved)
 *  \brief Displays the result of a test.
 *  Displays the value of \a expected and \a recieved, as well as the code for \a recieved
 *  so that the user can see what the test was for. */

#ifndef __LIB_UNIX_ESCAPE_UTIL_H
#define __LIB_UNIX_ESCAPE_UTIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#define UE_MESSAGE_STREAM cout
#define UE_MESSAGE_PREFIX "[UnixEscape "<<__FILE__<<":"<<__LINE__<<"] "
#define UE_MESSAGE_PREFIX_ERROR UE_MESSAGE_PREFIX<<"error: "
#define UE_MESSAGE_PREFIX_WARNING UE_MESSAGE_PREFIX<<"warning: "
#define UE_MESSAGE_PREFIX_DEBUG UE_MESSAGE_PREFIX<<"debug: "
#define UE_MESSAGE_PREFIX_TEST UE_MESSAGE_PREFIX<<"test: "
#define UE_MESSAGE_DISPLAY(msg) {UE_MESSAGE_STREAM<<msg<<"\n";}

#define UE_FATAL(msg) {UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_ERROR<<msg);throw std::runtime_error("internal unix escape error");}
#define UE_ERROR(msg) {UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_ERROR<<msg);}
#define UE_WARNING(msg) {UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_WARNING<<msg);}
#define UE_DEBUG(msg) {UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_WARNING<<msg);}

#define UE_TEST_HEADER(name) {UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_TEST<<"running '"<<name<<"'");}
#define UE_TEST_ASSERT(expected, recieved) { \
	std::stringstream _ssExpected; \
	_ssExpected << expected; \
	std::stringstream _ssRecieved; \
	_ssRecieved << recieved; \
	if (_ssExpected.str().compare(_ssRecieved.str()) == 0) \
	{ \
		UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_TEST << "    '" << #expected << "' succeeded ('" << _ssExpected.str() << "' == '" << _ssRecieved.str() << "')."); \
	} \
	else \
	{ \
		UE_MESSAGE_DISPLAY(UE_MESSAGE_PREFIX_TEST << "    '" << #expected << "' failed ('" << _ssExpected.str() << "' != '" << _ssRecieved.str() << "')."); \
	} \
}

/*! Namespace for all LibUNIXEscape classes/methods/global variables. */
namespace unixescape
{
	using namespace std;

	string makeCharPrintable(char c);
	string makeCharsPrintable(string s);
	string replaceEscapes(string s);
}

#endif