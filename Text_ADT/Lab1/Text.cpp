
#include "Text.h"

Text::Text ( const char *charSeq )
{
	bufferSize = strlen(charSeq) + 1;
	buffer = new char[bufferSize];
	strcpy(buffer, charSeq);
}

Text::Text ( const Text &other )
{
	bufferSize = other.bufferSize;
}

void Text::operator = ( const Text &other )
{
	if (other.bufferSize > bufferSize)
	{
		realloc(buffer, other.bufferSize);
	}
	strcpy(buffer, other.buffer);
}

Text::~Text ()
{
	delete[] buffer;
}

int Text::getLength () const
{
	return strlen(buffer);
}

char Text::operator [] ( int n ) const
{
	if (n > bufferSize) {
		return '\0';
	} else {
		return buffer[n];
	}
}

void Text::clear ()
{
	for (int i = 0; i < bufferSize; i++)
	{
		buffer[i] = '\0';
	}
}

void Text::showStructure () const
{
	string s = "";
	for (size_t i = 0; i < bufferSize; i++)
	{
		s += buffer[i];
	}
	cout << s << endl;
}

Text Text::toUpper( ) const
{
	char* buffer2 = new char[bufferSize];
	for (int i = 0; i < getLength(); i++)
	{
		buffer2[i] = toupper(buffer[i]);
	}
	Text temp(buffer2);
	delete[] buffer2;
	return temp;
}

Text Text::toLower( ) const
{
	char* buffer2 = new char[bufferSize];
	for (int i = 0; i < getLength(); i++)
	{
		buffer2[i] = tolower(buffer[i]);
	}
	Text temp(buffer2);
	delete[] buffer2;
	return temp;
}

bool Text::operator == ( const Text& other ) const
{
	int ret;
	ret = strcmp(buffer, other.buffer);
	if (ret == 0) {
		return true;
	}
	return false;
}

bool Text::operator <  ( const Text& other ) const
{
	int ret;
	ret = strcmp(buffer, other.buffer);
	if (ret < 0) {
		return true;
	}
	return false;
}

bool Text::operator >  ( const Text& other ) const
{
	int ret;
	ret = strcmp(buffer, other.buffer);
	if (ret > 0) {
		return true;
	}
	return false;
}
