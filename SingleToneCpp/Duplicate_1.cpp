/*#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

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
    std::string status; // To mark duplicates

    // Constructor for simplicity
    Record(int i, std::string n, double v, std::string c, int a, std::string addr, double s, std::string d)
        : id(i), name(n), value(v), category(c), age(a), address(addr), salary(s), department(d), status("unique") {}
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

// Function to find and mark duplicates
void markDuplicates(std::vector<Record>& records) {
    std::unordered_map<Record, int, RecordHash, RecordEqual> recordPositions;

    for (size_t i = 0; i < records.size(); ++i) {
        const Record& record = records[i];

        // Check if the record is already in the map
        auto it = recordPositions.find(record);
        if (it != recordPositions.end()) {
            // Mark current record as duplicate
            records[i].status = "duplicate";
            // Mark the first occurrence as duplicate
            records[it->second].status = "duplicate";
        } else {
            // Store the position of the first occurrence
            recordPositions[record] = i;
        }
    }
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

    // Mark duplicates
    markDuplicates(records);

    // Print records with their status
    for (const auto& record : records) {
        std::cout << "ID: " << record.id
                  << ", Name: " << record.name
                  << ", Status: " << record.status << "\n";
    }

    return 0;
}*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

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
    std::string status; // To mark duplicates

    // Constructor for simplicity
    Record(int i, std::string n, double v, std::string c, int a, std::string addr, double s, std::string d)
        : id(i), name(n), value(v), category(c), age(a), address(addr), salary(s), department(d), status("unique") {}
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

// Function to find and mark duplicates
void markDuplicates(std::vector<Record>& records) {
    std::unordered_set<Record, RecordHash, RecordEqual> seenRecords;

    for (auto& record : records) {
        // Check if the record has already been seen
        if (seenRecords.find(record) != seenRecords.end()) {
            // Mark current record as duplicate
            record.status = "duplicate";
        } else {
            // Mark the first occurrence as unique and add it to the set
            record.status = "unique";
            seenRecords.insert(record);
        }
    }
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

    // Mark duplicates
    markDuplicates(records);

    // Print records with their status
    for (const auto& record : records) {
        std::cout << "ID: " << record.id
                  << ", Name: " << record.name
                  << ", Status: " << record.status << "\n";
    }

    return 0;
}

