#include "../HttpUrl.h"


void ProcessURLParsing(std::istream& inputStream, std::ostream& outputStream);

int main()
{
	ProcessURLParsing(std::cin, std::cout);

	return 0;
}

void ProcessURLParsing(std::istream& inputStream, std::ostream& outputStream)
{
	std::string url;
	while (std::getline(inputStream, url))
	{
		try
		{
			HttpUrl inputUrl = HttpUrl(url);
			outputStream << "Protocol: " << (inputUrl.GetProtocol() == HttpUrl::Protocol::HTTP ? "http" : "https") << std::endl
						 << "Domain:   " << inputUrl.GetDomain() << std::endl
						 << "Port:     " << inputUrl.GetPort() << std::endl
						 << "Document: " << inputUrl.GetDocument() << std::endl;
		}
		catch (std::exception& e)
		{
			outputStream << e.what() << std::endl;
		}
	}

	return;
}