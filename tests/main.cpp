#include <iostream>
#include <fstream>
#include <sstream>
#include "LoRDeck.hpp"

class deckTester
{
	private:
		std::vector<LoRDeck> decksFromCode;
		std::vector<LoRDeck> decksFromCards;
	public:
		deckTester(void) = default;
		deckTester(const std::string &filepath) {
			std::ifstream file(filepath);
			std::string buffer;
			LoRDeck tempDeck;
			while (getline(file, buffer)) {
				if (buffer.empty() && !tempDeck.isEmpty()) {
					decksFromCards.push_back(tempDeck);
					tempDeck.clear();
					continue;
				}
				if (buffer.find(':') == std::string::npos)
					decksFromCode.push_back(LoRDeck(buffer));
				else
					tempDeck.addCard({
						LoRCard(buffer.substr(2, 7)),
						std::stoi(buffer.substr(0,1))
					});
			}
		}
		void clear(void) {
			decksFromCards.clear();
			decksFromCode.clear();
		}
		void loadFromFile(const std::string &filepath) {
			clear();
			(*this) = deckTester(filepath);
		}
		bool testDecks(void) {
			for (auto it = decksFromCards.begin(), it2 = decksFromCode.begin(); it != decksFromCards.end() && it2 != decksFromCode.end(); it++, it2++) {
				const LoRDeck &deckFromCard = (*it);
				const LoRDeck &deckFromCode = (*it2);

				if (deckFromCard != deckFromCode) {
					std::cout << "Testing failed" << std::endl;
					std::cout << "deckFromCard:" << std::endl;
					std::cout << deckFromCard.encode() << std::endl;
					for (const auto &[card, quantity] : deckFromCard)
						std::cout << quantity << ":" << card.getCode() << std::endl;
					std::cout << std::endl << "deckFromCode:" << std::endl;
					std::cout << deckFromCode.encode() << std::endl;
					for (const auto &[card, quantity] : deckFromCode)
						std::cout << quantity << ":" << card.getCode() << std::endl;
					return false;
				}
			}
			std::cout << "Testing succeed, encoding/decoding is working properly !" << std::endl;
			return true;
		}
};

int main(void) {

    deckTester tester("./tests/test.txt");
	tester.testDecks();
    return 0;
}