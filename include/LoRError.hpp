#include <exception>
#include <string>

class LoRError : public std::exception
{
	private:
        const std::string _message;
    public:
        explicit LoRError(std::string message) : _message(std::move(message)) {};

        explicit LoRError(const char *message) : _message(std::string(message)) {};

        [[nodiscard]] const char *what() const noexcept override {
            return _message.c_str();
        }
};