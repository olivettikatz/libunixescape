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

/*! \file EscapeStream.h
 *  \brief Contains EscapeStream class. */

#ifndef __LIB_UNIX_ESCAPE_ESCAPE_STREAM_H
#define __LIB_UNIX_ESCAPE_ESCAPE_STREAM_H

#include "Util.h"
#include "AttributeText.h"

/*! Namespace for all LibUNIXEscape classes/methods/global variables. */
namespace unixescape
{
	using namespace std;

	/*! Class which allows the user to define a stream from which AttributeText can be extracted automatically. */
	class EscapeStream
	{
	public:
		/*! The attribute type used by the AttributeText resulting from the stream. */
		typedef struct Attribute
		{
			/*! The full text of the escape. */
			string escape;

			/*! The integral arguments found in the escape (0 by default). */
			int i1, i2;

			/*! Constructor. */
			Attribute() : i1(0), i2(0) {}

			/*! Constructor. */
			Attribute(string e, int _i1 = 0, int _i2 = 0) : escape(e), i1(_i1), i2(_i2) {}
		} Attribute;

	protected:
		stringstream ss;

	public:
		/*! Constructor. */
		EscapeStream() {}

		/*! Gets reference to the stream object. */
		stringstream &stream();

		/*! Erases the stream object's data and returns an AttributeText object with the parsed data. */
		AttributeText<Attribute> flush(char numchar = '%');
	};
}

#endif