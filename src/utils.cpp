#include "utils.hpp"

int writeVarint(std::string* buffer, std::uint64_t value) {
    int encoded = 0;

    do {
        uint8_t next_byte = value & 0x7F;
        value >>= 7;

        if (value)
            next_byte |= 0x80;

        (*buffer) += next_byte;
        encoded++;

    } while (value);

    return encoded;
}

int getNextVarInt(std::vector<std::uint8_t>* stream ) {
    if (stream->empty()) return -1;
    int n_read = 0;
    int result = 0;
    int shift  = 0;
    while (true) {
        uint8_t c = (*stream)[n_read++];
        result |= (c & 0x07f) << shift;
        shift += 7;
        if (!(c & 0x80))
            break;
    }
    stream->erase(stream->begin(), stream->begin() + n_read);
    return result;
}