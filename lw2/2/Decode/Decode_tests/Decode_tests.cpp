#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Decode/HtmlDecode.h"

std::map <std::string, std::string>& wordsToDecode;

SCENARIO("Decoding an empty string yields an empty string")
{
	FillWordsToDecode(wordsToDecode);
	REQUIRE(HtmlDecode("", wordsToDecode).empty());
}

SCENARIO("Decoding a string that does not contain special characters returns the same string")
{
	std::string str = "abcde";
	REQUIRE(HtmlDecode(str, wordsToDecode) == str);
}

SCENARIO("Decoding a string with special characters returns the modified string")
{
	std::string source = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string result = "Cat <says> \"Meow\". M&M's";
	REQUIRE(HtmlDecode(source, wordsToDecode) == result);
}

SCENARIO("Decoding a string with &amp;lt; returns &lt; string")
{
	std::string source = "&amp;lt;";
	std::string result = "&lt;";
	REQUIRE(HtmlDecode(source, wordsToDecode) == result);
}