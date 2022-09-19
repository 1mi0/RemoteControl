#include "pch.h"
#include "Application.h"

int main()
{
	std::unique_ptr<Application> application = std::unique_ptr<Application>(new Application);
	application->run();

	std::cin.get();
	return 0;
}
