#include "ConsoleUI.h"

ArrayList<std::string> ConsoleUI::split(std::string string) const
{
	ArrayList<std::string> words;

	if (string.empty())
	{
		return words;
	}

	std::istringstream stringStream(string);
	std::string word;

	while (stringStream)
	{
		stringStream >> word;
		words.add(word.at(word.size() - 1) == ',' ? word.substr(0, word.size() - 1) : word);
	}

	words.removeAt(words.getSize() - 1);

	return words;
}

void ConsoleUI::displayError(std::string error) const
{
	std::cout << "Error: " << error << "\n";
}

void ConsoleUI::start()
{
	std::string command;

	while (true)
	{
		std::getline(std::cin, command);
		auto words = split(command);

		std::string commandType = words.getFirst();
		if (commandType == "exit")
		{
			return;
		}
		else if (commandType == "mode")
		{
			if (words.getSize() != 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			service.setMode(words.get(1).at(0));
		}
		else if (commandType == "add")
		{
			if (words.getSize() != 5)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			if (!service.addTrenchCoat(words.get(1), words.get(2), std::stoi(words.get(3)), words.get(4)))
			{
				displayError("Something went wrong!");
			}
		}
		else if (commandType == "update")
		{
			if (words.getSize() != 5)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			if (!service.updateTrenchCoat(words.get(1), words.get(2), std::stoi(words.get(3)), words.get(4)))
			{
				displayError("Something went wrong!");
			}
		}
		else if (commandType == "delete")
		{
			if (words.getSize() != 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			if (!service.deleteTrenchCoat(words.get(1)))
			{
				displayError("Something went wrong!");
			}
		}
		else if (commandType == "list")
		{
			if (words.getSize() == 1)
			{
				service.getListOfTrenchCoats().forEach([](const TrenchCoat& trenchCoat) {
					std::cout << trenchCoat.toString() << "\n";
				});
				continue;
			}
			if (words.getSize() == 3)
			{
				service.getListOfTrenchCoatsBySizeAndPrice(words.get(1), std::stoi(words.get(2))).forEach([](const TrenchCoat& trenchCoat) {
					std::cout << trenchCoat.toString() << "\n";
				});
				continue;
			}
			displayError("Incorrect number of parameters!");
		}
		else if (commandType == "next")
		{
			if (words.getSize() != 1)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			std::cout << service.getNextTrenchCoat().toString() << "\n";
		}
		else if (commandType == "save")
		{
			if (words.getSize() != 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			if (!service.saveTrenchCoat(words.get(1)))
			{
				displayError("Something went wrong!");
			}
		}
		else if (commandType == "mylist")
		{
			if (words.getSize() != 1)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			service.getShoppingListOfTrenchCoats().forEach([](const TrenchCoat& trenchCoat) {
				std::cout << trenchCoat.toString() << "\n";
				});
		}
		else if (commandType == "fileLocation")
		{
			if (words.getSize() < 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}

			std::string filePath = words.get(1);
			words.forEachIndexed([&](const std::string& splittedPathBySpace, int index) {
				if (index < 2)
				{
					return;
				}
				filePath += " " + splittedPathBySpace;
			});

			service.setFileLocation(filePath);
		}
		else if (commandType == "mylistLocation")
		{
			if (words.getSize() < 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}

			std::string filePath = words.get(1);
			words.forEachIndexed([&](const std::string& splittedPathBySpace, int index) {
				if (index < 2)
				{
					return;
				}
				filePath += " " + splittedPathBySpace;
			});

			service.setShoppingCartLocation(filePath);
		}
		else if (commandType == "help") 
		{
			if (words.getSize() < 1)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			help();
		}
		else if (command == "more help")
		{
			if (words.getSize() < 2)
			{
				displayError("Incorrect number of parameters!");
				continue;
			}
			moreHelp();
		}
		else
		{
			displayError("Invalid command!");
		}
	}
}

void ConsoleUI::help()
{
	std::stringstream menuHelp;
	menuHelp << "\n----------------------------------------------------------------------------------------------------------\n";
	menuHelp << "This Help Menu lists the commands for the Trench_Coat_Store Manager application \n\n";
	menuHelp << "fileLocation\n"
		<< "mylistLocation\n"
		<< "mode\n"
		<< "add\n"
		<< "update\n"
		<< "delete\n"
		<< "list\n"
		<< "mylist\n"
		<< "next\n"
		<< "save\n"
		<< "more help"
		<< "\n----------------------------------------------------------------------------------------------------------\n"
		<< "\n\n";
	std::cout<< menuHelp.str();	
}

void ConsoleUI::moreHelp()
{
	std::stringstream menuMoreHelp;
	menuMoreHelp << "\n----------------------------------------------------------------------------------------------------------\n";
	menuMoreHelp << "This Help Menu explains briefly with examples how to use the Console UI of the application\n\n";
	menuMoreHelp
		<< "fileLocation\n"
			<<"--> set the name of the file where to save the Trench Coats for the store\n"
			<<"--> the name of the file must have one of the extension csv, html, txt\n"
			<<"\t ex: fileLocation data.html\n"
		<< "mylistLocation\n"
			<<"--> set the name of the file where to save the Trench Coats for wishlist\n"
			<<"--> the name of the file must have one of the extension csv, html, txt\n"
			<<"\t ex: mylistLocation wishlist.txt\n"
		<< "mode\n"
			<<"--> enables dual ussage of the app: manager/ client \n"
			<<"mode A= Admin-> can add, remove update data for store \n"
			<<"default = simple user-> view store's catallogue and add/ remove frmo wishlist\n"
			<<"\t ex: mode A\n"
		<< "add\n"
			<<"--> add a Trench Coat to the store's catallogue \n" 		
			<<"--> only in admin mode\n"
			<<"\t ex: add Summer Coat, XL, 120, imgsource\n"
		<< "update\n"
			<<"--> update a Trench Coat with new information after identifying it via its name\n"
			<<"--> name cannot be update since it it the identifier \n"
			<<"--> only in admin mode\n"
			<<"\t ex: update Summer Coat, M, 80, imgsource\n"
		<< "delete\n"
			<<"--> delete a trench coat\n"
			<<"--> only in admin mode\n"
			<<"\t ex: delete Summer Coat\n"
		<< "list\n"
			<<"--> list the items from the store's catallogue\n"
			<<"\t ex: list"
		<< "mylist\n"
			<<"--> list the items from the wishlist\n"
			<< "\t ex: mylist"
		<< "next\n"
			<<"--> iterate through the store's catallogue\n"
			<< "\t ex: next"
		<< "save\n"
			<<"--> save item to wishlist\n"
			<< "\t ex: save\n"	
		<< "\n----------------------------------------------------------------------------------------------------------\n"
		<< "\n\n";
	std::cout<< menuMoreHelp.str();
}
