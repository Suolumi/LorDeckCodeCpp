#include "LoRFaction.hpp"

class LoRCard
{
	private:
		std::string set;
		LoRFaction faction;
		std::string id;
		std::string code;
	public:
		LoRCard(void) = default;
		~LoRCard(void) = default;
		LoRCard(const char *codeS) {
			std::string code = codeS;
			this->code = code;
			set = code.substr(0, 2);
			faction.setCode(code.substr(2, 2));
			this->id = code.substr(4, 3);
		}
		LoRCard(const std::string &code) {
			this->code = code;
			set = code.substr(0, 2);
			faction.setCode(code.substr(2, 2));
			this->id = code.substr(4, 3);
		}
		LoRCard(const std::string &set, const LoRFaction &faction, const std::string &id) {
			this->set = set;
			this->faction = faction;
			this->id = id;
			code = set + faction.getCodeStr() + id;
		}
		void setCode(const std::string &code) {
			(*this) = LoRCard(code);
		}
		void setElements(const std::string &set, const LoRFaction &faction, const std::string &id) {
			(*this) = LoRCard(set, faction, id);
		}
		std::string getSet() const & {
			return set;
		}
		LoRFaction getFaction() const & {
			return faction;
		}
		std::string getId() const & {
			return id;
		}
		std::string getCode() const & {
			return code;
		}
		bool operator == (const LoRCard &card) const & {
			return this->code == card.code;
		}
		bool operator != (const LoRCard &card) const & {
			return this->code != card.code;
		}
		operator std::string() {
			return code;
		}
		operator const char *() {
			return code.c_str();
		}
};