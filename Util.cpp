#include "Util.h"

namespace unixescape
{
	string makeCharPrintable(char c)
	{
		stringstream ss;

		if (isprint(c))
		{
			ss << c;
		}
		else
		{
			ss << "\\x" << hex << (int)c;
		}

		return ss.str();
	}

	string makeAllCharsPrintable(string s)
	{
		stringstream ss;

		for (string::iterator i = s.begin(); i != s.end(); i++)
		{
			ss << makeCharPrintable(*i);
		}

		return ss.str();
	}

	string replaceEscapes(string s)
	{
		stringstream ss;

		for (string::iterator i = s.begin(); i != s.end(); i++)
		{
			if (*i == '\\')
			{
				i++;
				if (i == s.end())
					break;

				if (*i == 'a')
					ss << '\a';
				else if (*i == 'b')
					ss << '\b';
				else if (*i == 'f')
					ss << '\f';
				else if (*i == 'n')
					ss << '\n';
				else if (*i == 'r')
					ss << '\r';
				else if (*i == 't')
					ss << '\t';
				else if (*i == 'v')
					ss << '\v';
				else if (*i == '\'')
					ss << '\'';
				else if (*i == '\"')
					ss << '\"';
				else if (*i == '?')
					ss << '?';
				else if (*i == '\\')
					ss << '\\';
				else if (*i == 'x')
				{
					stringstream ss2;

					i++;
					if (i == s.end())
						break;
					ss2 << *i;

					i++;
					if (i == s.end())
						break;
					ss2 << *i;

					char c;
					ss2 >> hex >> c;
					ss << c;
				}
				else if (*i == '0')
				{
					stringstream ss2;

					i++;
					if (i == s.end())
						break;
					ss2 << *i;

					i++;
					if (i == s.end())
						break;
					ss2 << *i;

					char *save;
					char c = strtol(ss2.str().c_str(), &save, 8);
					ss << c;
				}
			}
			else
			{
				ss << *i;
			}
		}

		return ss.str();
	}
}
