#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct CityRecord {
    std::string Name;
    size_t Population;
    double Longitude, Latitude;

    // CityRecord() {}
    // CityRecord(std::string name, size_t population, double latitude, double longitude)
    //     : Name(name), Population(population), Latitude(latitude), Longitude(longitude) {}
};

namespace std {
template <>
struct hash<CityRecord> {
    size_t operator()(const CityRecord& key) {
        return hash<std::string>()(key.Name);
    }
};

}  // namespace std

std::ostream& operator<<(std::ostream& instream, const CityRecord& record) {
    instream << record.Name << ",\t" << record.Population << ",\t(" << record.Latitude << ", " << record.Longitude << ')';
    return instream;
}

int main() {
    std::unordered_map<CityRecord, std::uint32_t> hashMap;
    std::map<std::string, CityRecord> cityMap;
    cityMap["Mumbai"] = CityRecord{"Mumbai", 100000, 2.4, 1.5};
    cityMap["Delhi"] = CityRecord{"Delhi", 100000, 2.4, 1.5};
    cityMap["Bangalore"] = CityRecord{"Bangalore", 100000, 2.4, 1.5};
    cityMap["Kolkata"] = CityRecord{"Kolkata", 100000, 2.4, 1.5};
    cityMap["Chennai"] = CityRecord{"Chennai", 100000, 2.4, 1.5};
    cityMap["Hyderabad"] = CityRecord{"Hyderabad", 100000, 2.4, 1.5};

    CityRecord& city = cityMap["Hyderabad"];
    std::cout << city << std::endl;

    CityRecord& indore = cityMap["Indore"];
    indore.Name = "Indore";
    indore.Population = 1000849;
    indore.Latitude = 45.6;
    indore.Longitude = -12.5;

    for (const auto& [key, value] : cityMap) {
        std::cout << value << std::endl;
    }

    const auto& cities = cityMap;
    if (cities.find("Hubli") != cities.end()) {
        const CityRecord& new_city = cities.at("Hubli");
        std::cout << new_city << std::endl;
    }

    for (auto& kv : cities) {
        const std::string& name = kv.first;
        CityRecord city = kv.second;
        std::cout << city << std::endl;
    }
}