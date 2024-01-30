#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Function to parse a CSV file and store its contents in a 2D vector
std::vector<std::vector<std::string >> parseCSV(const std::string& filename) {
    std::vector<std::vector<std::string >> data;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector < std::string > row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_file>" << std::endl;
        return 1;
    }

    // Get the CSV file path from the command-line argument
    std::string filename = argv[1];

    // Parse the CSV file and store it in a 2D vector
    std::vector<std::vector<std::string >> csvData = parseCSV(filename);

    // Display the contents of the 2D vector
    for (const auto& row : csvData) {
        for (const std::string& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}