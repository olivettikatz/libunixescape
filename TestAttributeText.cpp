#include "AttributeText.h"

using namespace unixescape;

int main()
{
	UE_TEST_HEADER("AttributeText");
	AttributeText<int> text;

	// you can add plain text
	text += "hi";
	// text now contains two plain characters: 'h' and 'i'

	// but you can also queue attributes to be added to the text with the next appending
	int a = 5;
	text.queueAttribute(a);
	// text still contains two plain characters: 'h' and 'i'

	text += "5";
	// text now contains the following:
	//     'h' - no attributes
	//     'i' - no attributes
	//     '5' - attribute: 5

	// then, after all is said and done, you can split the AttributeText up into segments
	// of either plain text or attributes.
	vector<AttributeText<int>::Segment> tmp = text.splitByAttributes();
	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].isAttribute())
		{
			cout << "Attribute: " << tmp[i].getAttribute() << "\n";
		}
		else
		{
			cout << "String: '" << tmp[i].getString() << "'\n";
		}
	}

	// expected output:
	// String: 'hi'
	// Attribute: 5
	// String: '5'
}