#include "LoRCard.hpp"

class LoRDeck
{
	private:
		std::vector<std::pair<LoRCard, int>> deck;
		int cardsInDeck = 0;
		int maxVersion = 1;

	public:
		LoRDeck(void) = default;
		LoRDeck(std::string encodedDeck);
		~LoRDeck(void) = default;

		auto begin() {
			return deck.begin();
		}
		auto begin() const {
			return deck.begin();
		}
		auto end() {
			return deck.end();
		}
		auto end() const {
			return deck.end();
		}
		void fromEncoded(const std::string &encodedDeck) {
			deck.clear();
			(*this) = LoRDeck(encodedDeck);
		}
		void addCard(const LoRCard &card, int quantity = 1) {
			if (quantity < 1 || quantity > 3)
				throw LoRError("Incorrect quantity of " + card.getCode());
			if (cardsInDeck + quantity > 40)
				throw LoRError("Too many cards in deck");
			maxVersion = std::get<1>(factions[card.getFaction()]) > maxVersion ? std::get<1>(factions[card.getFaction()]) : maxVersion;
			cardsInDeck += quantity;
			for (std::pair<LoRCard, int> &cards : deck) {
				if (cards.first == card) {
					if (quantity + cards.second > 3)
						throw LoRError("Incorrect quantity of " + card.getCode());
					cards = {cards.first, quantity + cards.second};
					return;
				}
			}
			deck.push_back({card, quantity});
		}
		void addCard(const std::pair<LoRCard, int> &pair) {
			addCard(pair.first, pair.second);
		}
		void removeCard(const LoRCard &card, int quantity = 3) {
			if (quantity < 1 || quantity > 3)
				throw LoRError("Incorrect quantity of " + card.getCode());
			for (auto it = deck.begin(); it != deck.end(); it++) {
				const auto [deckCard, cardQuantity] = (*it);
				if (deckCard == card) {
					if (quantity >= cardQuantity) {
						cardsInDeck -= cardQuantity;
						deck.erase(it);
						break;
					} else {
						(*it) = {deckCard, cardQuantity - quantity};
						cardsInDeck -= quantity;
						break;
					}
				}
			}
			maxVersion = 1;
			for (const auto &[card, quantity] : deck)
				maxVersion = std::get<1>(factions[card.getFaction()]) > maxVersion ? std::get<1>(factions[card.getFaction()]) : maxVersion;
		}
		void removeCard(const std::pair<LoRCard, int> &pair) {
			removeCard(pair.first, pair.second);
		}
		std::vector<std::pair<LoRCard, int>> getCards() {
			return deck;
		}
		std::vector<LoRCard> getCardsOnly() {
			std::vector<LoRCard> vec;
			for (const std::pair<LoRCard, int> &pair : deck)
				vec.push_back(pair.first);
			return vec;
		}
		int getNumberOfCardsInDeck() {
			return cardsInDeck;
		}
		void clear() {
			maxVersion = 1;
			cardsInDeck = 0;
			deck.clear();
		}
		bool isEmpty() const & {
			return deck.empty();
		}
		bool operator == (const LoRDeck &deck) const & {
			return encode() == deck.encode();
		}
		bool operator == (const std::string &encodedDeck) const & {
			return encode() == encodedDeck;
		}
		bool operator != (const LoRDeck &deck) const & {
			return encode() != deck.encode();
		}
		bool operator != (const std::string &encodedDeck) const & {
			return encode() != encodedDeck;
		}
		std::string encode() const;
};