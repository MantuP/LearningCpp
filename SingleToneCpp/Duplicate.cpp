#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

// Define the structure
struct Record {
    int id;
    std::string name;
    double value;
    std::string category;
    int age;
    std::string address;
    double salary;
    std::string department;
    // ... Additional 122 members

    // Constructor for simplicity
    Record(int i, std::string n, double v, std::string c, int a, std::string addr, double s, std::string d)
        : id(i), name(n), value(v), category(c), age(a), address(addr), salary(s), department(d) {}
};

// Custom hash function for 8 members
struct RecordHash {
    std::size_t operator()(const Record& record) const {
        return std::hash<int>()(record.id) ^
               std::hash<std::string>()(record.name) ^
               std::hash<std::string>()(record.category) ^
               std::hash<std::string>()(record.department) ^
               std::hash<int>()(record.age) ^
               std::hash<std::string>()(record.address) ^
               std::hash<double>()(record.salary) ^
               std::hash<double>()(record.value);
    }
};

// Custom equality function for 8 members
struct RecordEqual {
    bool operator()(const Record& lhs, const Record& rhs) const {
        return lhs.id == rhs.id &&
               lhs.name == rhs.name &&
               lhs.category == rhs.category &&
               lhs.department == rhs.department &&
               lhs.age == rhs.age &&
               lhs.address == rhs.address &&
               lhs.salary == rhs.salary &&
               lhs.value == rhs.value;
    }
};

// Function to find duplicates
std::vector<Record> findDuplicates(const std::vector<Record>& records) {
    std::unordered_set<Record, RecordHash, RecordEqual> uniqueRecords;
    std::vector<Record> duplicates;

    for (const auto& record : records) {
        if (!uniqueRecords.insert(record).second) {
            duplicates.push_back(record); // Duplicate found
        }
    }

    return duplicates;
}

// Main function
int main() {
    // Example vector with records
    std::vector<Record> records = {
        {1, "Alice", 100.5, "A", 25, "Addr1", 5000.0, "HR"},
        {2, "Bob", 200.5, "B", 30, "Addr2", 6000.0, "IT"},
        {1, "Alice", 100.5, "A", 25, "Addr1", 5000.0, "HR"}, // Duplicate
        {3, "Charlie", 300.5, "C", 35, "Addr3", 7000.0, "Finance"},
        {2, "Bob", 200.5, "B", 30, "Addr2", 6000.0, "IT"}    // Duplicate
    };

    // Find duplicates
    std::vector<Record> duplicates = findDuplicates(records);

    // Print duplicates
    std::cout << "Duplicates found:\n";
    for (const auto& dup : duplicates) {
        std::cout << "ID: " << dup.id << ", Name: " << dup.name << "\n";
    }

    return 0;
}
