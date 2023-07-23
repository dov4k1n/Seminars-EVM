#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct SectionHeader {
    char name[9];
    uint32_t virtualSize;
    uint32_t virtualAddress;
    uint32_t rawDataSize;
    uint32_t rawDataPtr;
};

void analyzePE(const string& fileName) {
    ifstream file(fileName, ios::binary);

    if (!file) {
        cerr << "Error opening the file: " << fileName << endl;
        return;
    }

    // Read DOS header
    file.seekg(0, ios::beg);
    uint16_t dosMagicNumber;
    file.read(reinterpret_cast<char*>(&dosMagicNumber), sizeof(dosMagicNumber));

    // Check if the file has a valid DOS header
    if (dosMagicNumber != 0x5A4D) {
        cerr << "Invalid DOS header. Not a valid PE file." << endl;
        file.close();
        return;
    }

    // Read PE signature offset
    file.seekg(0x3C, ios::beg);
    uint32_t peSignatureOffset;
    file.read(reinterpret_cast<char*>(&peSignatureOffset), sizeof(peSignatureOffset));

    // Read PE signature
    file.seekg(peSignatureOffset, ios::beg);
    uint32_t peSignature;
    file.read(reinterpret_cast<char*>(&peSignature), sizeof(peSignature));

    // Check if the file has a valid PE signature
    if (peSignature != 0x00004550) {
        cerr << "Invalid PE signature. Not a valid PE file." << endl;
        file.close();
        return;
    }

    // Read COFF header
    file.seekg(peSignatureOffset + sizeof(peSignature), ios::beg);
    uint16_t machineType;
    file.read(reinterpret_cast<char*>(&machineType), sizeof(machineType));

    // Output machine type
    cout << "Machine Type: 0x" << hex << setw(4) << setfill('0') << machineType << endl;

    // Read number of sections
    uint16_t numberOfSections;
    file.read(reinterpret_cast<char*>(&numberOfSections), sizeof(numberOfSections));

    // Output number of sections
    cout << "Number of Sections: " << dec << numberOfSections << endl;

    // Skip timestamp, symbols, and optional header
    file.ignore(10 + 8 + 4 + 2 + 2 + 2 + 2, '\0');

    // Read section headers
    vector<SectionHeader> sectionHeaders(numberOfSections);
    for (SectionHeader& section : sectionHeaders) {
        file.read(section.name, sizeof(section.name));
        file.read(reinterpret_cast<char*>(&section.virtualSize), sizeof(section.virtualSize));
        file.read(reinterpret_cast<char*>(&section.virtualAddress), sizeof(section.virtualAddress));
        file.read(reinterpret_cast<char*>(&section.rawDataSize), sizeof(section.rawDataSize));
        file.read(reinterpret_cast<char*>(&section.rawDataPtr), sizeof(section.rawDataPtr));
        file.ignore(12);
    }

    // Output section headers
    cout << endl;
    cout << "Section Headers:" << endl;
    cout << left << setw(12) << "Name" << setw(12) << "Virtual Size" << setw(12) << "Virtual Address"
         << setw(12) << "Raw Data Size" << setw(12) << "Raw Data Ptr" << endl;

    for (const SectionHeader& section : sectionHeaders) {
        cout << left << setw(12) << section.name << setw(12) << hex << section.virtualSize
             << setw(12) << section.virtualAddress << setw(12) << section.rawDataSize
             << setw(12) << section.rawDataPtr << endl;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename.exe>" << endl;
        return 1;
    }

    string fileName = argv[1];
    analyzePE(fileName);

    return 0;
}
