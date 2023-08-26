#include <iostream>

#include "LogMessage.hpp"


void printLogMessage(const LogMessage& logMessage);


int main() {
#if WIN32
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
	std::cout << "\tПаттерн \"Цепочка ответственности\"\n\n" << std::endl;

	std::string filename = "out.txt";

	LogMessageWarning logMessageWarning;
	LogMessageError logMessageError(filename);
	LogMessageFatalError logMessageFatalError;
	LogMessageUnknownMessage logMessageUnknownMessage;

	std::cout << "Предупреждение:" << std::endl;
	printLogMessage(logMessageWarning);
	std::cout << std::endl;

	std::cout << "Ошибка:" << std::endl;
	printLogMessage(logMessageError);
	std::cout << std::endl;

	std::cout << "Фатальная ошибка:" << std::endl;
	printLogMessage(logMessageFatalError);
	std::cout << std::endl;

	std::cout << "Неизвестное сообщение:" << std::endl;
	printLogMessage(logMessageUnknownMessage);
	std::cout << std::endl;

	std::cin.get();
	return 0;
}

void printLogMessage(const LogMessage& logMessage){
	try {
		std::cout << logMessage.message() << std::endl;
	}
	catch (const char* er){
		std::cout << er << std::endl;
	}
}
