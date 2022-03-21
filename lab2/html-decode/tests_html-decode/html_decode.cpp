#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "html_decode.h"

struct HtmlEntity
{
	std::string htmlCode;
	char symbol;
};

std::string HtmlStringDecode(std::string const& string, const HtmlEntity& entity)
{
	size_t currPos = 0;
	std::string result;
	const char htmlDelimeter = ';';

	const auto searcher = std::boyer_moore_horspool_searcher(entity.htmlCode.begin(), entity.htmlCode.end());
	while (currPos < string.length())
	{
		const auto htmlCodeIt = std::search(string.begin() + currPos, string.end(), searcher);
		const auto htmlDelimeterIt = std::find(htmlCodeIt, string.end(), htmlDelimeter);
		result.append(string, currPos, htmlCodeIt - string.begin() - currPos);

		if (htmlCodeIt == string.end())
		{
			break;
		}
		else if (htmlDelimeterIt == string.end())
		{
			result.append(string, htmlCodeIt - string.begin(), string.end() - htmlCodeIt);

			break;
		}
		else
		{
			result.push_back(entity.symbol);
			currPos += htmlCodeIt - string.begin() - currPos + entity.htmlCode.length();
		}

		if (htmlDelimeterIt - string.begin() == htmlCodeIt - string.begin() + entity.htmlCode.length())
		{
			currPos += 1;
		}
	}

	return result;
}

std::string HtmlDecode(std::string const& text)
{
	std::string result = text;
	size_t startPos = 0;
	std::vector<HtmlEntity> HtmlEntities = { { "&quot", '"' }, { "&apos", '\'' }, { "&lt", '<' }, { "&gt", '>' }, { "&amp", '&' } };
	for (auto htmlEntity : HtmlEntities)
	{
		result = HtmlStringDecode(result, htmlEntity);
	}

	return result;
}

void HtmlTextDecode(std::istream& inputFile, std::ostream& outputFile)
{
	std::string line;
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);

		outputFile << HtmlDecode(line) << std::endl;
	}
}