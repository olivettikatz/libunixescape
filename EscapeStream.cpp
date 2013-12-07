#include "EscapeStream.h"

namespace unixescape
{
	stringstream &EscapeStream::stream()
	{
		return ss;
	}

	AttributeText<EscapeStream::Attribute> EscapeStream::flush(char numchar)
	{
		string s = ss.str();
		AttributeText<Attribute> rtn;

		for (size_t i = 0; i < s.size(); i++)
		{
			if (isprint(s[i]))
			{
				rtn.push_back(s[i]);
			}
			else
			{
				if (string("\n\r\t\b\x7f\a\x5").find(s[i]) != string::npos)
				{
					rtn.push_back(0, Attribute(string(1, s[i])));
				}
				else if (s[i] == '\033')
				{
					i++;
					if (i >= s.size())
					{
						break;
					}
					else if (s[i] != '[')
					{
						continue;
					}

					i++;
					if (i >= s.size())
					{
						break;
					}

					if (string("ABCDEFGJKSTmsu").find(s[i]) != string::npos)
					{
						rtn.push_back(0, Attribute(string("\033[")+s[i]));
					}
					else if (s[i] == 'i')
					{
						i++;
						if (i >= s.size())
						{
							break;
						}
						else if (s[i] != '@')
						{
							continue;
						}

						int j = 0;
						while(s[i+1+j] != '@' && i+1+j < s.size())
							j++;

						if (i+1+j >= s.size())
						{
							break;
						}
						else if (j == 0)
						{
							i++;
							continue;
						}
						else
						{
							rtn.push_back(0, Attribute(string("\033[i@"+s.substr(i+1, j)+"@")));
						}
					}
					else if (s[i] == '?')
					{
						int j = 0;
						while(isdigit(s[i+1+j]) && i+1+j < s.size())
							j++;

						if (i+1+j >= s.size())
						{
							break;
						}
						else if (j == 0)
						{
							i++;
							continue;
						}
						else
						{
							Attribute a;
							a.i1 = atoi(s.substr(i+1, j).c_str());
							i += 1+j;

							if (s[i] == 'l' || s[i] == 'h')
							{
								a.escape = string("\033[?")+s.substr(i-j-1, j)+s[i];
								rtn.push_back(0, a);
							}
						}
					}
					else
					{
						int j = 0;
						while (isdigit(s[i+1+j]) && i+1+j < s.size())
							j++;

						if (i+1+j >= s.size())
						{
							break;
						}
						else if (j == 0)
						{
							i++;
							continue;
						}
						else
						{
							Attribute a;
							string s1 = s.substr(i+1, j);
							a.i1 = atoi(s1.c_str());
							i += 1+j;

							if (string("ABCDEFGJKSTnm").find(s[i]) != string::npos)
							{
								a.escape = string("\033[")+s1+s[i];
								rtn.push_back(0, a);
							}
							else if (s[i] == ';')
							{
								int k = 0;
								while(isdigit(s[i+1+k]) && i+1+k < s.size())
									k++;

								if (i+1+k >= s.size())
								{
									break;
								}
								else if (k == 0)
								{
									i++;
									continue;
								}
								else
								{
									string s2 = s.substr(i+1, k);
									a.i2 = atoi(s2.c_str());
									i += 1+k;

									if (string("Hfm").find(s[i]) != string::npos)
									{
										a.escape = string("\033[")+s1+";"+s2+s[i];
										rtn.push_back(0, a);
									}
								}
							}
						}
					}
				}
			}
		}

		ss.str("");
		return rtn;
	}
}
