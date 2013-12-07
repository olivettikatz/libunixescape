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

/*! \file AttributeText.h
 *  \brief Contains AttributeText class which handles text intermingled with attributes.
 *  Each character in an AttributeText string can be either plain or can have attributes. This means that
 *  that character is paired with an object of whatever the template argument of AttributeText is.
 *  For example:
 *  \include TestAttributeText.cpp
 *  */

#ifndef __LIB_UNIX_ESCAPE_ATTRIBUTE_TEXT_H
#define __LIB_UNIX_ESCAPE_ATTRIBUTE_TEXT_H

#include "Util.h"

/*! Namespace for all LibUNIXEscape classes/methods/global variables. */
namespace unixescape
{
	/*! Class for attribute-containing text. The template argument is whatever type you want the
	 *  attributes to be.
	 *  \warning Is mostly compatible with STL strings - most methods, members, and subtypes of std::string work for AttributeText objects. */
	template<typename T> class AttributeText
	{
	public:
		/*! A character type that can have attributes. */
		typedef struct Char
		{
			/*! The character value.
			 *  \warning It is recomended to use getChar() instead. */
			char c;

			/*! True if there is an attribute assigned.
			 *  \warning It is recomended to use hasAttributes() instead. */
			bool useAttr;

			/*! The attributes for the character.
			 *  \warning It is recomended to use getAttributes() instead. */
			T attr;

			/*! Constructor. */
			Char(char _c) : c(_c), useAttr(false) {}

			/*! Constructor. */
			Char(char _c, T a) : c(_c), useAttr(true), attr(a) {}

			/*! Gets the character value. */
			char &getChar();

			/*! Returns true if an attribute is associated with character (relies only on useAttr, not on
			 *  the value of the attribute in any way.) */
			bool hasAttributes();

			/*! Gets the value of the attributes. */
			T &getAttributes();

			/*! Assignment operator. */
			Char &operator = (Char c);

			/*! Assignment operator. */
			Char &operator = (char c);

			/*! Comparison operator. */
			bool operator == (Char &c);

			/*! Comparison operator. */
			bool operator == (char c);
		} Char;

		/*! Segment of text or attributes used by splitByAttributes(). */
		typedef struct Segment
		{
			/*! True if the segment is storing an attribute.
			 *  \warning It is recomended to use isAttribute() instead. */
			bool isAttr;

			/*! A pointer to the attributes. 
			 *  \warning It is recomended to use getAttribute() instead. */
			T *attr;

			/*! The string value.
			 *  \warning It is recomended to use getString() instead. */
			string str;

			/*! Constructor. */
			Segment(T &a) : isAttr(true), attr(&a) {}

			/*! Constructor. */
			Segment(string s) : isAttr(false), attr(NULL), str(s) {}

			/*! Returns true if the segment is an attribute (relies only on isAttr, not on
			 *  the value of the attribute pointer in any way.) */
			bool isAttribute();

			/*! Returns the attribute. */
			T &getAttribute();

			/*! Returns the string. */
			string &getString();
		} Segment;

	protected:
		vector<Char> content;
		T *attrQueue;

		void applyQueue(T **q);

	public:
		// C++ STL::string compatibility
		typedef typename vector<Char>::iterator iterator;
		typedef typename vector<Char>::const_iterator const_iterator;
		typedef typename vector<Char>::reverse_iterator reverse_iterator;
		typedef typename vector<Char>::const_reverse_iterator const_reverse_iterator;

		const static size_t npos = string::npos;

		AttributeText() : attrQueue(NULL) {}
		AttributeText(const AttributeText &t) : content(t.content), attrQueue(NULL) {}
		AttributeText(const char *s);
		AttributeText(const char *s, size_t n);
		AttributeText(size_t n, char c);
		AttributeText(size_t n, char c, T a);
		AttributeText &operator = (const AttributeText &t);
		AttributeText &operator = (const char *s);
		AttributeText &operator = (char c);
		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin();
		const_reverse_iterator crend();
		size_t size();
		size_t length();
		void clear();
		bool empty();
		char &operator [] (size_t pos);
		char &at(size_t pos);
		char &back();
		char &front();
		AttributeText &operator += (const AttributeText &t);
		AttributeText &operator += (const char *s);
		AttributeText &operator += (char c);
		AttributeText &append(const AttributeText &t);
		AttributeText &append(const char *s);
		AttributeText &append(const char *s, size_t n);
		AttributeText &append(size_t n, char c);
		AttributeText &push_back(char c);
		AttributeText &push_back(char c, T a);
		AttributeText &insert(size_t pos, const AttributeText &t);
		AttributeText &erase(size_t pos = 0, size_t len = npos);
		iterator erase(iterator p);
		iterator erase(iterator first, iterator last);
		AttributeText &replace(iterator i1, iterator i2, const AttributeText &t);
		void swap(AttributeText &t);
		void pop_back();
		const char *c_str();
		const char *data();
		size_t find(const AttributeText &t, size_t pos = 0);
		size_t find(const char *s, size_t pos = 0);
		size_t find(char c, size_t pos = 0);
		size_t rfind(const AttributeText &t, size_t pos = 0);
		size_t rfind(const char *s, size_t pos = 0);
		size_t rfind(char c, size_t pos = 0);
		AttributeText substr(size_t pos = 0, size_t len = npos);
		int compare(const AttributeText &t);
		int compare(size_t pos, size_t len, const AttributeText &t);
		int compare(const char *s);
		int compare(size_t pos, size_t len, const char *s);

		// non-stl methods
		/*! Converts AttributeText to std::string (removes attributes). */
		string toStdString();

		/*! Converts AttributeText to std::string for debugging purposes (keeps attributes). */
		string toDebugString();

		/*! There is an attribute queue (1-long max) that queues attributes for
		 *  appending with the next appendature. This sets the queue to this attribute. */
		void queueAttribute(T &a);

		/*! Gets the attributes at a certain index. */
		T &getAttributes(size_t pos);

		/*! Splits the AttributeText into a vector of Segment instances, which can be either plain text strings
		 *  or individual attributes. */
		vector<Segment> splitByAttributes();
	};

	template<typename T> char &AttributeText<T>::Char::getChar()
	{
		return c;
	}

	template<typename T> bool AttributeText<T>::Char::hasAttributes()
	{
		return useAttr;
	}

	template<typename T> T &AttributeText<T>::Char::getAttributes()
	{
		return attr;
	}

	template<typename T> typename AttributeText<T>::Char &AttributeText<T>::Char::operator = (Char c)
	{
		c = c.c;
		useAttr = c.useAttr;
		attr = c.attr;
		return *this;
	}

	template<typename T> typename AttributeText<T>::Char &AttributeText<T>::Char::operator = (char c)
	{
		this->c = c;
		useAttr = false;
		attr = T();
		return *this;
	}

	template<typename T> bool AttributeText<T>::Char::operator == (Char &c)
	{
		return (this->c != c.c);
	}

	template<typename T> bool AttributeText<T>::Char::operator == (char c)
	{
		return (this->c != c);
	}

	template<typename T> bool AttributeText<T>::Segment::isAttribute()
	{
		return isAttr;
	}

	template<typename T> T &AttributeText<T>::Segment::getAttribute()
	{
		return *attr;
	}

	template<typename T> string &AttributeText<T>::Segment::getString()
	{
		return str;
	}

	template<typename T> void AttributeText<T>::applyQueue(T **a)
	{
		if (a == NULL)
			return ;

		if (*a == NULL)
			return ;

		if (content.empty())
			return ;

		if (content[0].hasAttributes())
			return ;

		cout << "applying queued attribute to '" << toStdString() << "'...\n";
		content[0].attr = **a;
		content[0].useAttr = true;
		*a = NULL;
	}

	template<typename T> AttributeText<T>::AttributeText(const char *s)
	{
		attrQueue = NULL;

		while(*s != 0)
		{
			content.push_back(Char(*s));
			s++;
		}
	}

	template<typename T> AttributeText<T>::AttributeText(const char *s, size_t n)
	{
		attrQueue = NULL;
		
		for (int i = 0; i < n; i++)
			content.push_back(Char(s[i]));
	}

	template<typename T> AttributeText<T>::AttributeText(size_t n, char c)
	{
		attrQueue = NULL;
		
		for (int i = 0; i < n; i++)
			content.push_back(Char(c));
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator = (const AttributeText<T> &t)
	{
		content = t.content;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator = (const char *s)
	{
		content = AttributeText<T>(s).content;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator = (char c)
	{
		content = AttributeText<T>(1, c).content;
	}

	template<typename T> typename AttributeText<T>::iterator AttributeText<T>::begin()
	{
		return content.begin();
	}

	template<typename T> typename AttributeText<T>::reverse_iterator AttributeText<T>::rbegin()
	{
		return content.rbegin();
	}

	template<typename T> typename AttributeText<T>::const_iterator AttributeText<T>::cbegin()
	{
		return content.cbegin();
	}

	template<typename T> typename AttributeText<T>::const_reverse_iterator AttributeText<T>::crbegin()
	{
		return content.crbegin();
	}

	template<typename T> typename AttributeText<T>::iterator AttributeText<T>::end()
	{
		return content.end();
	}

	template<typename T> typename AttributeText<T>::reverse_iterator AttributeText<T>::rend()
	{
		return content.rend();
	}

	template<typename T> typename AttributeText<T>::const_iterator AttributeText<T>::cend()
	{
		return content.cend();
	}

	template<typename T> typename AttributeText<T>::const_reverse_iterator AttributeText<T>::crend()
	{
		return content.crend();
	}

	template<typename T> size_t AttributeText<T>::size()
	{
		return content.size();
	}

	template<typename T> size_t AttributeText<T>::length()
	{
		return content.length();
	}

	template<typename T> void AttributeText<T>::clear()
	{
		content.clear();
	}

	template<typename T> bool AttributeText<T>::empty()
	{
		return content.empty();
	}

	template<typename T> char &AttributeText<T>::operator [] (size_t pos)
	{
		return content[pos].c;
	}

	template<typename T> char &AttributeText<T>::at(size_t pos)
	{
		return content[pos].c;
	}

	template<typename T> char &AttributeText<T>::back()
	{
		return content.back().c;
	}

	template<typename T> char &AttributeText<T>::front()
	{
		return content.front().c;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator += (const AttributeText<T> &t)
	{
		AttributeText<T> tmp(t);
		tmp.applyQueue(attrQueue);
		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator += (const char *s)
	{
		AttributeText<T> tmp = AttributeText<T>(s);
		tmp.applyQueue(&attrQueue);

		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
		return *this;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::operator += (char c)
	{
		if (attrQueue != NULL)
		{
			content.push_back(Char(c, *attrQueue));
			attrQueue = NULL;
		}
		else
		{
			content.push_back(Char(c));
		}
	}

	template<typename T> AttributeText<T> &AttributeText<T>::append(const AttributeText<T> &t)
	{
		AttributeText<T> tmp(t);
		tmp.applyQueue(attrQueue);
		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::append(const char *s)
	{
		AttributeText<T> tmp = AttributeText<T>(s);
		tmp.applyQueue(attrQueue);
		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::append(const char *s, size_t n)
	{
		AttributeText<T> tmp = AttributeText<T>(s, n);
		tmp.applyQueue(attrQueue);
		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::append(size_t n, char c)
	{
		AttributeText<T> tmp = AttributeText<T>(n, c);
		tmp.applyQueue(attrQueue);
		content.insert(content.end(), tmp.content.begin(), tmp.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::push_back(char c)
	{
		if (attrQueue != NULL)
		{
			content.push_back(Char(c, *attrQueue));
			attrQueue = NULL;
		}
		else
		{
			content.push_back(Char(c));
		}

		return *this;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::push_back(char c, T a)
	{
		content.push_back(Char(c, a));
		return *this;
	}

	template<typename T> AttributeText<T> &AttributeText<T>::insert(size_t pos, const AttributeText<T> &t)
	{
		content.insert(content.begin()+pos, t.content.begin(), t.content.end());
	}

	template<typename T> AttributeText<T> &AttributeText<T>::erase(size_t pos, size_t len)
	{
		content.erase(pos, len);
	}

	template<typename T> typename AttributeText<T>::iterator AttributeText<T>::erase(typename AttributeText<T>::iterator p)
	{
		content.erase(p);
	}

	template<typename T> typename AttributeText<T>::iterator AttributeText<T>::erase(typename AttributeText<T>::iterator first, typename AttributeText<T>::iterator last)
	{
		content.erase(first, last);
	}

	template<typename T> AttributeText<T> &AttributeText<T>::replace(typename AttributeText<T>::iterator i1, typename AttributeText<T>::iterator i2, const AttributeText<T> &t)
	{
		content.replace(i1, i2, t.content);
	}

	template<typename T> void AttributeText<T>::swap(AttributeText<T> &t)
	{
		content.swap(t.content);
	}

	template<typename T> void AttributeText<T>::pop_back()
	{
		content.pop_back();
	}

	template<typename T> const char *AttributeText<T>::c_str()
	{
		string tmp;
		for (iterator i = content.begin(); i != content.end(); i++)
		{
			if (i->c != 0)
			{
				tmp.push_back(i->c);
			}
		}
		return tmp.c_str();
	}

	template<typename T> const char *AttributeText<T>::data()
	{
		string tmp;
		for (iterator i = content.begin(); i != content.end(); i++)
		{
			if (i->c != 0)
			{
				tmp.push_back(i->c);
			}
		}
		return tmp.c_str();
	}

	template<typename T> size_t AttributeText<T>::find(const AttributeText<T> &t, size_t pos)
	{
		for (size_t i = pos; i < content.size()-t.content.size(); i++)
		{
			bool found = true;
			for (size_t j = 0; j < t.content.size(); j++)
			{
				if (content[i+j] != t.content[j])
				{
					found = false;
					break;
				}
			}

			if (found == true)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> size_t AttributeText<T>::find(const char *s, size_t pos)
	{
		for (size_t i = pos; i < content.size()-string(s).size(); i++)
		{
			bool found = true;
			for (size_t j = 0; j < string(s).size(); j++)
			{
				if (content[i+j] != s[j])
				{
					found = false;
					break;
				}
			}

			if (found == true)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> size_t AttributeText<T>::find(char c, size_t pos)
	{
		for (size_t i = pos; i < content.size(); i++)
		{
			if (content[i] == c)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> size_t AttributeText<T>::rfind(const AttributeText<T> &t, size_t pos)
	{
		for (size_t i = content.size()-t.content.size()-1; i > pos; i++)
		{
			bool found = true;
			for (size_t j = 0; j < t.content.size(); j++)
			{
				if (content[i+j] != t.content[j])
				{
					found = false;
					break;
				}
			}

			if (found == true)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> size_t AttributeText<T>::rfind(const char *s, size_t pos)
	{
		for (size_t i = content.size()-string(s).size()-1; i > pos; i++)
		{
			bool found = true;
			for (size_t j = 0; j < string(s).size(); j++)
			{
				if (content[i+j] != s[j])
				{
					found = false;
					break;
				}
			}

			if (found == true)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> size_t AttributeText<T>::rfind(char c, size_t pos)
	{
		for (size_t i = content.size()-1; i > pos; i++)
		{
			if (content[i] == c)
			{
				return i;
			}
		}

		return npos;
	}

	template<typename T> AttributeText<T> AttributeText<T>::substr(size_t pos, size_t len)
	{
		AttributeText<T> rtn;
		if (len == npos)
		{
			vector<Char> tmp(content.begin(), content.end());
			rtn = tmp;
		}
		else
		{
			vector<Char> tmp(content.begin()+pos, content.begin()+len);
			rtn = tmp;
		}
		return rtn;
	}

	template<typename T> int AttributeText<T>::compare(const AttributeText<T> &t)
	{
		if (content.size() < t.content.size())
		{
			return -1;
		}
		else if (content.size() == t.content.size())
		{
			for (size_t i = 0; i < content.size(); i++)
			{
				if (content[i].c < t.content[i].c)
				{
					return -1;
				}
				else if (content[i].c == t.content[i].c)
				{
					continue;
				}
				else
				{
					return 1;
				}
			}

			return 0;
		}
		else
		{
			return 1;
		}
	}

	template<typename T> int AttributeText<T>::compare(size_t pos, size_t len, const AttributeText<T> &t)
	{
		if (pos+len > content.size())
		{
			return -1;
		}

		if (content.size() < t.content.size())
		{
			return -1;
		}
		else if (content.size() == t.content.size())
		{
			for (size_t i = pos; i < pos+len; i++)
			{
				if (content[i].c < t.content[i].c)
				{
					return -1;
				}
				else if (content[i].c == t.content[i].c)
				{
					continue;
				}
				else
				{
					return 1;
				}
			}

			return 0;
		}
		else
		{
			return 1;
		}
	}

	template<typename T> int AttributeText<T>::compare(const char *s)
	{
		return compare(AttributeText<T>(s));
	}

	template<typename T> int AttributeText<T>::compare(size_t pos, size_t len, const char *s)
	{
		return compare(pos, len, AttributeText<T>(s));
	}

	template<typename T> string AttributeText<T>::toStdString()
	{
		string tmp;
		for (iterator i = content.begin(); i != content.end(); i++)
		{
			if (i->c != 0)
			{
				tmp.push_back(i->c);
			}
		}
		return tmp;
	}

	template<typename T> string AttributeText<T>::toDebugString()
	{
		stringstream ss;
		for (iterator i = content.begin(); i != content.end(); i++)
		{
			ss << " '" << i->getChar() << "'";
			if (i->hasAttributes())
			{
				ss << " (" << i->getAttributes() << ")";
			}
		}
		return ss.str().substr(1);
	}

	template<typename T> void AttributeText<T>::queueAttribute(T &a)
	{
		attrQueue = &a;
	}

	template<typename T> T &AttributeText<T>::getAttributes(size_t pos)
	{
		return content[pos].attr;
	}

	template<typename T> vector<typename AttributeText<T>::Segment> AttributeText<T>::splitByAttributes()
	{
		vector<Segment> rtn;
		string buf;

		for (iterator i = content.begin(); i != content.end(); i++)
		{
			if (i->hasAttributes())
			{
				if (buf.empty() == false)
				{
					rtn.push_back(Segment(buf));
					buf = "";
				}

				rtn.push_back(Segment(i->getAttributes()));
				rtn.push_back(Segment(string(1, i->getChar())));
			}
			else
			{
				buf += i->getChar();
			}
		}

		if (buf.empty() == false)
		{
			rtn.push_back(Segment(buf));
		}

		return rtn;
	}
}

#endif