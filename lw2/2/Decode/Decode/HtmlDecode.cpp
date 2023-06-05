#include "HtmlDecode.h"

void FillWordsToDecode(std::map <std::string, std::string>& wordsToDecode)
{
	wordsToDecode["&quot;"] = "\"";
	wordsToDecode["&apos;"] = "'";
	wordsToDecode["&lt;"] = "<";
	wordsToDecode["&gt;"] = ">";
	wordsToDecode["&amp;"] = "&";
}

std::string HtmlDecode(std::string const& html, const std::map <std::string, std::string>& wordsToDecode)
{
	std::string tStr = html;
	std::string result = "";
	const char ampersandSymbol = '&';

	size_t pos = 0;
	size_t foundPos = html.find(ampersandSymbol, pos);

	while (foundPos != std::string::npos)
	{
		result.append(html, pos, foundPos - pos);
		pos = foundPos;

		for (auto pair : wordsToDecode)
		{
			if (html.substr(foundPos, pair.first.length()) == pair.first)
			{
				result += pair.second;
				pos = foundPos + pair.first.length();
				foundPos = pos;
				break;
			}
		}

		foundPos = html.find(ampersandSymbol, pos);
	}

	result.append(html, pos, foundPos - pos);

	return result;
}