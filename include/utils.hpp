#include <string>
#include <vector>

int writeVarint(std::string* buffer, std::uint64_t value);
int getNextVarInt(std::vector<std::uint8_t>* stream );