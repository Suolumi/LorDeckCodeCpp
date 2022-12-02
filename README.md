# LorDeckCodeCpp

A C++ implementation of [Riot's Deck API](https://github.com/RiotGames/LoRDeckCodes) for Legends of Runeterra.

## Installation & Tests

```bash
$ git clone https://github.com/Suolumi/LorDeckCodeCpp
$ cd  LoRDeckCodeCpp
$ cmake .
$ make
$ ./LorDeckCode (or ./deckTesting for unit tests)
```

## Example usage

```c++
#include <iostream>
#include "LoRDeck.hpp"

int main(void) {

    LoRDeck deck;
    LoRCard card("01SI011");
    deck.addCard(card, 3);
    deck.addCard("01SI015", 3);
    deck.addCard("01SI018", 3);
    deck.addCard("01SI030", 3);
    deck.addCard("01SI032", 3);
    deck.addCard("01SI041", 3);
    deck.addCard("01SI042", 3);
    deck.addCard("01SI043", 3);
    deck.addCard("01SI048", 3);
    deck.addCard("01SI001", 2);
    deck.addCard("01SI020", 2);
    deck.addCard("01SI029", 2);
    deck.addCard("01SI035", 2);
    deck.addCard("01SI044", 2);
    deck.addCard("01SI045", 2);
    deck.addCard("01SI026", 1);
    std::string encoded =  deck.encode();

    LoRDeck deck2(encoded);

    std::cout << encoded << std::endl;
    for (const auto &[card, quantity] : deck2) {
        std::cout << quantity << ":" << card.getCode() << std::endl;
    }
    return 0;
}
```

### Dependencies

* [Base32 de(en)coder](https://github.com/tplgy/cppcodec) by @tplgy
