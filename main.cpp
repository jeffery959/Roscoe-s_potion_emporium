#include <iostream>
#include <string_view>
#include <array>
#include <limits>
#include "Random.h"
#include <cassert>


namespace Potion {
	enum Type {
		healing,
		mana,
		speed,
		invisibility,
		max_size

	};
	using namespace std::literals::string_view_literals;
	std::array types{ healing,mana,speed,invisibility };
	std::array costs{20,30,12,50};
	std::array names{"healing"sv,"mana"sv,"speed"sv,"invisibilitiy"sv};

	static_assert(std::size(types) == max_size);
	static_assert(std::size(costs) == max_size);
	static_assert(std::size(names) == max_size);

}

void shop() {
	std::cout << '\n';
	std::cout << "Here is our selection for today:\n";
	

	for (std::size_t i{ 0 }; i < Potion::max_size; ++i) {
		std::cout << i << ")" << " " << Potion::names[i] << " costs " << Potion::costs[i]<<"\n";
	}
}

class Player {

	std::string m_name{};
	std::array<int, Potion::max_size> m_inventory {};
	int m_gold{ Random::get(80,120) };
public:
	explicit Player(std::string_view name)
		:m_name{name}

	{};

	std::string_view getName() { return m_name; };
	int getGold() { return m_gold; };

	void printInventory() {
		std::cout << "Your inventory contains:\n";
		for (std::size_t i{ 0 }; i < std::size(m_inventory);++i) {
			if (m_inventory[i] < 1)
				continue;
			std::cout <<m_inventory[i]<<"x potion of "<<Potion::names[i]<<'\n';
			
			

		}
	}

	void buy(int x) {
		m_gold -= x;
	}
	
	void addToInventory(int index) {
		assert(index >= 0 && index <= 3, "Invalid index,Out of bounds!!");
		m_inventory[index] += 1;


	  

	}

};




std::string getNameFromUser() {
	std::cout << "Enter your name: ";
	std::string name{};
	std::getline(std::cin>>std::ws, name);
	return name;

}
//Ask the user for a char input from 0-3 and 'q' ,returns the users input afterwards. 
char getOptions() {
	std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
	char x{};
	while (true) {
		std::cin >> x;

		

		if (!std::cin) {
			if (std::cin.eof()) {
				std::exit(0);
			}
			std::cin.clear();
			goto errorMessage;

		}
		if (!std::cin.eof() && std::cin.peek() != '\n') {
			goto errorMessage;

		}
		
		if ((x >= '0' &&x <='3')||(x == 'q')) {
			break;
		
		}


	errorMessage:
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "I didn't understand what you said. Try again:";
		continue;
		
		
	
		



	} ;


	return x;

}


int main() {
	//Setup program
	std::cout << "Welcome to Roscoe's potion emporium!\n";
	Player player (getNameFromUser());
	std::cout << "Hello, " << player.getName() << ", you have " <<
	player.getGold() << " gold.\n\n";

	//Runing program

	while (true) {
	shop();

	char options{ getOptions() };
	
	if (options == 'q') {
		break;
	}
	int optionToInt{ static_cast<int>(options - '0') };

	if (player.getGold()<Potion::costs[optionToInt]) {
		std::cout << "You can not afford that.\n";
		continue;
	}

	player.buy(Potion::costs[optionToInt]);
	player.addToInventory(optionToInt);
	std::cout << "You purschased a potion of "<<Potion::names[optionToInt]<<". You have " << player.getGold() << " gold left.\n";
	
	





	}

	//Exiting program
	std::cout << '\n';
	player.printInventory();
	std::cout << "You escaped with " << player.getGold()<<" gold reamining.\n";
	std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

	return 0;
}
