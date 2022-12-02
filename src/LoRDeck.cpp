#include "LoRDeck.hpp"
#include <base32_rfc4648.hpp>
#include <list>
#include "utils.hpp"

static const int format = 1;
static const int maxKnownVersion = 5;

typedef struct LoRGroup {
	int listSize = 0;
	int set;
	int faction;
	std::list<int> cardsCode;

	LoRGroup(int set, int faction) {
		this->set = set;
		this->faction = faction;
	}
	void addCard(int cardCode) & {
		cardsCode.emplace_back(cardCode);
		this->listSize++;
	}
	void sort() & {
		cardsCode.sort([](const int &first, const int &second) -> bool {
			return first < second;
		});
	}
} LoRGroup;

static std::list<LoRGroup> getGroups(std::vector<std::pair<LoRCard, int>> cards) {
	std::list<LoRGroup> groupList;

	for (const std::pair<LoRCard, int> &pair : cards) {
		const LoRCard &card = pair.first;
		const int cardSet = std::stoi(card.getSet());
		const int cardFac = card.getFaction().getCodeInt();
		bool cont = false;

		for (LoRGroup &group : groupList) {
			if (cardSet == group.set && cardFac == group.faction) {
				group.addCard(stoi(card.getId()));
				cont = true;
				break;
			}
		}
		if (cont)
			continue;
		groupList.emplace_back(LoRGroup(cardSet, cardFac));
		groupList.back().addCard(stoi(card.getId()));
	}

	groupList.sort([](const LoRGroup &first, const LoRGroup &second) -> bool {
		return first.listSize < second.listSize;
	});
	for (LoRGroup &group : groupList)
		group.sort();
	return groupList;
}

LoRDeck::LoRDeck(std::string encodedDeck) {
	while (encodedDeck.size() % 8 != 0)
		encodedDeck.push_back('=');
	std::vector<std::uint8_t> b32_decoded = cppcodec::base32_rfc4648::decode(encodedDeck);

	int version = getNextVarInt(&b32_decoded) & 0xf;
	if (version > maxKnownVersion)
		throw LoRError("Unknown version");
	for (int group = 3; group > 0; group--) {
		int size = getNextVarInt(&b32_decoded);
		for (int groupSize = 0; groupSize < size; groupSize++) {
			int codeListLength = getNextVarInt(&b32_decoded);
			std::string set = "0" + std::to_string(getNextVarInt(&b32_decoded));
			LoRFaction faction(static_cast<factionIdentifier>(getNextVarInt(&b32_decoded)));
			for (int length = 0; length < codeListLength; length++) {
				std::string cardCode = std::to_string(getNextVarInt(&b32_decoded));
				while (cardCode.size() < 3)
					cardCode.insert(cardCode.begin(), '0');
				LoRCard card(set, faction, cardCode);
				addCard(card, group);
			}
		}
	}
}

std::string LoRDeck::encode() const {
	if (cardsInDeck > 40)
		throw LoRError("Too many cards in the deck");
	std::string encodedDeck;
	std::vector<std::pair<LoRCard, int>> oneCopies, twoCopies, threeCopies;
	auto filter = [](const int i) -> auto {
		return [i](const std::pair<LoRCard, int>& card) -> bool {
			return card.second == i;
		};
	};

	std::copy_if(deck.begin(), deck.end(), std::back_inserter(oneCopies), filter(1));
	std::copy_if(deck.begin(), deck.end(), std::back_inserter(twoCopies), filter(2));
	std::copy_if(deck.begin(), deck.end(), std::back_inserter(threeCopies), filter(3));

	std::vector<std::list<LoRGroup>> groups = {
		getGroups(threeCopies),
		getGroups(twoCopies),
		getGroups(oneCopies)
	};


	writeVarint(&encodedDeck, format << 4 | maxVersion);
	for (const std::list<LoRGroup> &list : groups) {
		writeVarint(&encodedDeck, list.size());
		for (const LoRGroup &group : list) {
			writeVarint(&encodedDeck, group.listSize);
			writeVarint(&encodedDeck, group.set);
			writeVarint(&encodedDeck, group.faction);
			for (const int &cardCode : group.cardsCode)
				writeVarint(&encodedDeck, cardCode);
		}
	}

	encodedDeck = cppcodec::base32_rfc4648::encode(encodedDeck);
	while (encodedDeck.ends_with("="))
		encodedDeck.pop_back();
	return encodedDeck;
}