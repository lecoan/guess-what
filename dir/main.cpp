#include <iostream> 
#include <string>
int main()
{
	std::cout << (0 == nullptr);
	std::string command;
	while (std::cin >> command) {
		if (command == "login") {
			
		}
		else if(command == "register") {

		}
		else if (command == "play") {

		}
		else if (command == "order") {

		} 
		else if (command == "logout") {

		}
		else if (command == "exit") {
			std::cout << "bey!" << std::endl;
			break;
		}
		else {
			std::cout << "unknown command" << std::endl;
		}
	}
	return 0;
}