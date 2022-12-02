#include "LoRError.hpp"
#include <vector>
#include <tuple>

enum factionIdentifier {
	DEMACIA = 0,
	FREJLORD = 1,
	IONIA = 2,
	NOXUS = 3,
	PILTOVER_ZAUN = 4,
	SHADOW_ISLES = 5,
	BILGEWATER = 6,
	MOUNT_TARGON = 9,
	SHURIMA = 7,
	BANDLE_CITY = 10,
	RUNETERRA = 12
};

const std::vector<std::tuple<std::string, int, factionIdentifier>> factions = {
	{"DE", 1, DEMACIA},
	{"FR", 1, FREJLORD},
	{"IO", 1, IONIA},
	{"NX", 1, NOXUS},
	{"PZ", 1, PILTOVER_ZAUN},
	{"SI", 1, SHADOW_ISLES},
	{"BW", 2, BILGEWATER},
	{"MT", 2, MOUNT_TARGON},
	{"SH", 3, SHURIMA},
	{"BC", 4, BANDLE_CITY},
	{"RU", 5, RUNETERRA}
};

class LoRFaction
{
	private:
		int index = -1;
		factionIdentifier id;
		std::string code;
	public:
		LoRFaction(void) = default;
		~LoRFaction(void) = default;
		LoRFaction(const factionIdentifier &faction) {
			int i = 0;
			for (const std::tuple<std::string, int, factionIdentifier> &tuple : factions) {
				const factionIdentifier &id = std::get<2>(tuple);
				if (faction == id) {
					this->code = std::get<0>(tuple);
					this->index = i;
					this->id = std::get<2>(tuple);
					index = i;
					break;
				}
				i++;
			}
			if (index == -1)
				throw LoRError("Card code " + std::to_string(faction) + " doesn't exist");
		}
		LoRFaction(const std::string &code) {
			int i = 0;
			for (const std::tuple<std::string, int, factionIdentifier> &tuple : factions) {
				const std::string &faction = std::get<0>(tuple);
				if (code == faction) {
					this->code = code;
					this->index = i;
					id = std::get<2>(tuple);
					index = i;
					break;
				}
				i++;
			}
			if (index == -1)
				throw LoRError("Card code " + code + " doesn't exist");
		}
		void setCode(const factionIdentifier &code) {
			(*this) = LoRFaction(code);
		}
		void setCode(const std::string &code) {
			(*this) = LoRFaction(code);
		}
		int getCodeInt(void) const & {
			return static_cast<int>(id);
		}
		factionIdentifier getIdentifier(void) const & {
			return id;
		}
		std::string getCodeStr(void) const & {
			return code;
		}
		bool operator == (const LoRFaction &faction) {
			return this->index == faction.index;
		}
		bool operator == (const std::string &faction) {
			return this->code == faction;
		}
		bool operator == (const int &faction) {
			return this->index == faction;
		}
		bool operator != (const LoRFaction &faction) {
			return this->index != faction.index;
		}
		bool operator != (const std::string &faction) {
			return this->code != faction;
		}
		bool operator != (const int &faction) {
			return this->index != faction;
		}
		operator int (void) {
			return index;
		}
		operator std::string(void) {
			return code;
		}
		operator const char *(void) {
			return code.c_str();
		}
};