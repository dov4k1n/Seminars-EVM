#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class PEFile {
public:
    bool analyze(const string& fileName) {
        ifstream file(fileName, ios::binary);

        if (!file) {
            cerr << "Error opening the file: " << fileName << endl;
            return false;
        }

        // Read DOS header
        file.seekg(0, ios::beg);
        file.read(reinterpret_cast<char*>(&dosHeader), sizeof(dosHeader));

        // Check if the file has a valid DOS header
        if (dosHeader.magicNumber != 0x5A4D) {
            cerr << "Invalid DOS header. Not a valid PE file." << endl;
            file.close();
            return false;
        }

        // Read PE signature offset
        file.seekg(0x3C, ios::beg);
        file.read(reinterpret_cast<char*>(&peSignatureOffset), sizeof(peSignatureOffset));

        // Read PE signature
        file.seekg(peSignatureOffset, ios::beg);
        file.read(reinterpret_cast<char*>(&peSignature), sizeof(peSignature));

        // Check if the file has a valid PE signature
        if (peSignature != 0x00004550) {
            cerr << "Invalid PE signature. Not a valid PE file." << endl;
            file.close();
            return false;
        }

        // Read COFF header
        file.seekg(peSignatureOffset + sizeof(peSignature), ios::beg);
        file.read(reinterpret_cast<char*>(&coffHeader), sizeof(coffHeader));

        // Read optional header
        file.ignore(coffHeader.sizeOfOptionalHeader - sizeof(coffHeader), '\0');
        if (coffHeader.sizeOfOptionalHeader >= 96) {
            file.read(reinterpret_cast<char*>(&optionalHeader.pe32plus), sizeof(optionalHeader.pe32plus));
        }
        else {
            file.read(reinterpret_cast<char*>(&optionalHeader.pe32), sizeof(optionalHeader.pe32));
        }

        // Read section headers
        sectionHeaders.resize(coffHeader.numberOfSections);
        for (SectionHeader& section : sectionHeaders) {
            file.read(section.name, sizeof(section.name));
            file.read(reinterpret_cast<char*>(&section.header), sizeof(section.header));
            file.read(reinterpret_cast<char*>(&section.additionalFields), sizeof(section.additionalFields));
        }

        file.close();
        return true;
    }

    void printContent() const {
        printDOSHeader();
        printCOFFHeader();
        printOptionalHeader();
        printSectionHeaders();
    }

private:
    struct DOSHeader {
        uint16_t magicNumber;
        // Add more fields if needed
        uint16_t lastSize;
        uint16_t nblocks;
        uint16_t nreloc;
        uint16_t hdrSize;
        uint16_t minalloc;
        uint16_t maxalloc;
        uint16_t ss;
        uint16_t sp;
        uint16_t checksum;
        uint16_t ip;
        uint16_t cs;
        uint16_t relocPos;
        uint16_t noverlay;
        uint16_t reserved1[4];
        uint16_t oem_id;
        uint16_t oem_info;
        uint16_t reserved2[10];
        uint32_t e_lfanew;
        // ...
    };

    struct COFFHeader {
        uint16_t machineType;
        uint16_t numberOfSections;
        // Add more fields if needed
        uint32_t timestamp;
        uint32_t pointerToSymbolTable;
        uint32_t numberOfSymbols;
        uint16_t sizeOfOptionalHeader;
        uint16_t characteristics;
        // ...
    };

    struct OptionalHeader {
        struct PE32 {
            uint32_t imageBase;
            uint32_t sectionAlignment;
            uint32_t fileAlignment;
            uint16_t majorOperatingSystemVersion;
            uint16_t minorOperatingSystemVersion;
            uint16_t majorImageVersion;
            uint16_t minorImageVersion;
            uint16_t majorSubsystemVersion;
            uint16_t minorSubsystemVersion;
            uint32_t win32VersionValue;
            uint32_t sizeOfImage;
            uint32_t sizeOfHeaders;
            uint32_t checksum;
            uint16_t subsystem;
            uint16_t dllCharacteristics;
            uint32_t sizeOfStackReserve;
            uint32_t sizeOfStackCommit;
            uint32_t sizeOfHeapReserve;
            uint32_t sizeOfHeapCommit;
            uint32_t loaderFlags;
            uint32_t numberOfRvaAndSizes;
            // Add more fields if needed
            uint32_t exportTableAddress;
            uint32_t exportTableSize;
            uint32_t importTableAddress;
            uint32_t importTableSize;
            uint32_t resourceTableAddress;
            uint32_t resourceTableSize;
            uint32_t exceptionTableAddress;
            uint32_t exceptionTableSize;
            uint32_t certificateTableAddress;
            uint32_t certificateTableSize;
            uint32_t baseRelocationTableAddress;
            uint32_t baseRelocationTableSize;
            uint32_t debugAddress;
            uint32_t debugSize;
            uint32_t architectureDataAddress;
            uint32_t architectureDataSize;
            uint32_t globalPtrAddress;
            uint32_t globalPtrSize;
            uint32_t tlsTableAddress;
            uint32_t tlsTableSize;
            uint32_t loadConfigTableAddress;
            uint32_t loadConfigTableSize;
            uint32_t boundImportTableAddress;
            uint32_t boundImportTableSize;
            uint32_t importAddressTableAddress;
            uint32_t importAddressTableSize;
            uint32_t delayImportDescriptorAddress;
            uint32_t delayImportDescriptorSize;
            uint32_t clrRuntimeHeaderAddress;
            uint32_t clrRuntimeHeaderSize;
            uint32_t reserved;
        } pe32;
        
        struct PE32Plus {
            uint64_t imageBase;
            uint32_t sectionAlignment;
            uint32_t fileAlignment;
            uint16_t majorOperatingSystemVersion;
            uint16_t minorOperatingSystemVersion;
            uint16_t majorImageVersion;
            uint16_t minorImageVersion;
            uint16_t majorSubsystemVersion;
            uint16_t minorSubsystemVersion;
            uint32_t win32VersionValue;
            uint32_t sizeOfImage;
            uint32_t sizeOfHeaders;
            uint32_t checksum;
            uint16_t subsystem;
            uint16_t dllCharacteristics;
            uint64_t sizeOfStackReserve;
            uint64_t sizeOfStackCommit;
            uint64_t sizeOfHeapReserve;
            uint64_t sizeOfHeapCommit;
            uint32_t loaderFlags;
            uint32_t numberOfRvaAndSizes;
            // Add more fields if needed
            uint32_t exportTableAddress;
            uint32_t exportTableSize;
            uint32_t importTableAddress;
            uint32_t importTableSize;
            uint32_t resourceTableAddress;
            uint32_t resourceTableSize;
            uint32_t exceptionTableAddress;
            uint32_t exceptionTableSize;
            uint32_t certificateTableAddress;
            uint32_t certificateTableSize;
            uint32_t baseRelocationTableAddress;
            uint32_t baseRelocationTableSize;
            uint32_t debugAddress;
            uint32_t debugSize;
            uint32_t architectureDataAddress;
            uint32_t architectureDataSize;
            uint64_t globalPtrAddress;
            uint32_t globalPtrSize;
            uint32_t tlsTableAddress;
            uint32_t tlsTableSize;
            uint32_t loadConfigTableAddress;
            uint32_t loadConfigTableSize;
            uint32_t boundImportTableAddress;
            uint32_t boundImportTableSize;
            uint32_t importAddressTableAddress;
            uint32_t importAddressTableSize;
            uint32_t delayImportDescriptorAddress;
            uint32_t delayImportDescriptorSize;
            uint64_t clrRuntimeHeaderAddress;
            uint32_t clrRuntimeHeaderSize;
            uint32_t reserved;
        } pe32plus;
    };

    struct SectionHeader {
        char name[8];
        // Add more fields if needed
        uint32_t virtualSize;
        uint32_t virtualAddress;
        uint32_t sizeOfRawData;
        uint32_t pointerToRawData;
        uint32_t pointerToRelocations;
        uint32_t pointerToLinenumbers;
        uint16_t numberOfRelocations;
        uint16_t numberOfLinenumbers;
        uint32_t characteristics;
        // ...
    };

    DOSHeader dosHeader;
    uint32_t peSignatureOffset;
    uint32_t peSignature;
    COFFHeader coffHeader;
    OptionalHeader optionalHeader;
    vector<SectionHeader> sectionHeaders;

    void printDOSHeader() const {
        cout << "DOS Header:" << endl;
        cout << "Magic Number: 0x" << hex << setw(4) << setfill('0') << dosHeader.magicNumber << endl;
        // Print more fields if needed
        cout << "Last Size: " << dosHeader.lastSize << endl;
        cout << "Number of Blocks: " << dosHeader.nblocks << endl;
        cout << "Number of Relocations: " << dosHeader.nreloc << endl;
        cout << "Header Size: " << dosHeader.hdrSize << endl;
        cout << "Minimum Allocation: " << dosHeader.minalloc << endl;
        cout << "Maximum Allocation: " << dosHeader.maxalloc << endl;
        cout << "Stack Segment: 0x" << hex << setw(4) << setfill('0') << dosHeader.ss << endl;
        cout << "Stack Pointer: 0x" << hex << setw(4) << setfill('0') << dosHeader.sp << endl;
        cout << "Checksum: 0x" << hex << setw(4) << setfill('0') << dosHeader.checksum << endl;
        cout << "Instruction Pointer: 0x" << hex << setw(4) << setfill('0') << dosHeader.ip << endl;
        cout << "Code Segment: 0x" << hex << setw(4) << setfill('0') << dosHeader.cs << endl;
        cout << "Relocation Table Offset: 0x" << hex << setw(4) << setfill('0') << dosHeader.relocPos << endl;
        cout << "Overlay Number: " << dosHeader.noverlay << endl;
        // Print more fields if needed
        cout << "OEM ID: 0x" << hex << setw(4) << setfill('0') << dosHeader.oem_id << endl;
        cout << "OEM Info: 0x" << hex << setw(4) << setfill('0') << dosHeader.oem_info << endl;
        // ...
        cout << "PE Signature Offset: 0x" << hex << setw(8) << setfill('0') << dosHeader.e_lfanew << endl;
        cout << endl;
    }

    void printCOFFHeader() const {
        cout << "COFF Header:" << endl;
        cout << "Machine Type: 0x" << hex << setw(4) << setfill('0') << coffHeader.machineType << endl;
        cout << "Number of Sections: " << coffHeader.numberOfSections << endl;
        // Print more fields if needed
        cout << "Timestamp: 0x" << hex << setw(8) << setfill('0') << coffHeader.timestamp << endl;
        cout << "Pointer to Symbol Table: 0x" << hex << setw(8) << setfill('0') << coffHeader.pointerToSymbolTable << endl;
        cout << "Number of Symbols: " << coffHeader.numberOfSymbols << endl;
        cout << "Size of Optional Header: " << coffHeader.sizeOfOptionalHeader << " bytes" << endl;
        cout << "Characteristics: 0x" << hex << setw(4) << setfill('0') << coffHeader.characteristics << endl;
        // ...
        cout << endl;
    }

    void printOptionalHeader() const {
        cout << "Optional Header:" << endl;
        if (coffHeader.sizeOfOptionalHeader >= 96) {
            printPE32PlusOptionalHeader();
        }
        else {
            printPE32OptionalHeader();
        }
        cout << endl;
    }

    void printPE32OptionalHeader() const {
        cout << "PE32 Optional Header:" << endl;
        cout << "Image Base: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.imageBase << endl;
        cout << "Section Alignment: " << optionalHeader.pe32.sectionAlignment << " bytes" << endl;
        cout << "File Alignment: " << optionalHeader.pe32.fileAlignment << " bytes" << endl;
        cout << "Major Operating System Version: " << optionalHeader.pe32.majorOperatingSystemVersion << endl;
        cout << "Minor Operating System Version: " << optionalHeader.pe32.minorOperatingSystemVersion << endl;
        cout << "Major Image Version: " << optionalHeader.pe32.majorImageVersion << endl;
        cout << "Minor Image Version: " << optionalHeader.pe32.minorImageVersion << endl;
        cout << "Major Subsystem Version: " << optionalHeader.pe32.majorSubsystemVersion << endl;
        cout << "Minor Subsystem Version: " << optionalHeader.pe32.minorSubsystemVersion << endl;
        cout << "Win32 Version Value: " << optionalHeader.pe32.win32VersionValue << endl;
        cout << "Size of Image: " << optionalHeader.pe32.sizeOfImage << " bytes" << endl;
        cout << "Size of Headers: " << optionalHeader.pe32.sizeOfHeaders << " bytes" << endl;
        cout << "Checksum: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.checksum << endl;
        cout << "Subsystem: 0x" << hex << setw(4) << setfill('0') << optionalHeader.pe32.subsystem << endl;
        cout << "DLL Characteristics: 0x" << hex << setw(4) << setfill('0') << optionalHeader.pe32.dllCharacteristics << endl;
        cout << "Size of Stack Reserve: " << optionalHeader.pe32.sizeOfStackReserve << " bytes" << endl;
        cout << "Size of Stack Commit: " << optionalHeader.pe32.sizeOfStackCommit << " bytes" << endl;
        cout << "Size of Heap Reserve: " << optionalHeader.pe32.sizeOfHeapReserve << " bytes" << endl;
        cout << "Size of Heap Commit: " << optionalHeader.pe32.sizeOfHeapCommit << " bytes" << endl;
        cout << "Loader Flags: " << optionalHeader.pe32.loaderFlags << endl;
        cout << "Number of Data Directories: " << optionalHeader.pe32.numberOfRvaAndSizes << endl;
        // Print more fields if needed
        cout << "Export Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.exportTableAddress << endl;
        cout << "Export Table Size: " << optionalHeader.pe32.exportTableSize << " bytes" << endl;
        cout << "Import Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.importTableAddress << endl;
        cout << "Import Table Size: " << optionalHeader.pe32.importTableSize << " bytes" << endl;
        cout << "Resource Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.resourceTableAddress << endl;
        cout << "Resource Table Size: " << optionalHeader.pe32.resourceTableSize << " bytes" << endl;
        cout << "Exception Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.exceptionTableAddress << endl;
        cout << "Exception Table Size: " << optionalHeader.pe32.exceptionTableSize << " bytes" << endl;
        cout << "Certificate Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.certificateTableAddress << endl;
        cout << "Certificate Table Size: " << optionalHeader.pe32.certificateTableSize << " bytes" << endl;
        cout << "Base Relocation Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.baseRelocationTableAddress << endl;
        cout << "Base Relocation Table Size: " << optionalHeader.pe32.baseRelocationTableSize << " bytes" << endl;
        cout << "Debug Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.debugAddress << endl;
        cout << "Debug Size: " << optionalHeader.pe32.debugSize << " bytes" << endl;
        cout << "Architecture Data Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.architectureDataAddress << endl;
        cout << "Architecture Data Size: " << optionalHeader.pe32.architectureDataSize << " bytes" << endl;
        cout << "Global Pointer Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.globalPtrAddress << endl;
        cout << "Global Pointer Size: " << optionalHeader.pe32.globalPtrSize << " bytes" << endl;
        cout << "TLS Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.tlsTableAddress << endl;
        cout << "TLS Table Size: " << optionalHeader.pe32.tlsTableSize << " bytes" << endl;
        cout << "Load Config Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.loadConfigTableAddress << endl;
        cout << "Load Config Table Size: " << optionalHeader.pe32.loadConfigTableSize << " bytes" << endl;
        cout << "Bound Import Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.boundImportTableAddress << endl;
        cout << "Bound Import Table Size: " << optionalHeader.pe32.boundImportTableSize << " bytes" << endl;
        cout << "Import Address Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.importAddressTableAddress << endl;
        cout << "Import Address Table Size: " << optionalHeader.pe32.importAddressTableSize << " bytes" << endl;
        cout << "Delay Import Descriptor Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.delayImportDescriptorAddress << endl;
        cout << "Delay Import Descriptor Size: " << optionalHeader.pe32.delayImportDescriptorSize << " bytes" << endl;
        cout << "CLR Runtime Header Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32.clrRuntimeHeaderAddress << endl;
        cout << "CLR Runtime Header Size: " << optionalHeader.pe32.clrRuntimeHeaderSize << " bytes" << endl;
        cout << "Reserved: " << optionalHeader.pe32.reserved << endl;
    }

    void printPE32PlusOptionalHeader() const {
        cout << "PE32+ Optional Header:" << endl;
        cout << "Image Base: 0x" << hex << setw(16) << setfill('0') << optionalHeader.pe32plus.imageBase << endl;
        cout << "Section Alignment: " << optionalHeader.pe32plus.sectionAlignment << " bytes" << endl;
        cout << "File Alignment: " << optionalHeader.pe32plus.fileAlignment << " bytes" << endl;
        cout << "Major Operating System Version: " << optionalHeader.pe32plus.majorOperatingSystemVersion << endl;
        cout << "Minor Operating System Version: " << optionalHeader.pe32plus.minorOperatingSystemVersion << endl;
        cout << "Major Image Version: " << optionalHeader.pe32plus.majorImageVersion << endl;
        cout << "Minor Image Version: " << optionalHeader.pe32plus.minorImageVersion << endl;
        cout << "Major Subsystem Version: " << optionalHeader.pe32plus.majorSubsystemVersion << endl;
        cout << "Minor Subsystem Version: " << optionalHeader.pe32plus.minorSubsystemVersion << endl;
        cout << "Win32 Version Value: " << optionalHeader.pe32plus.win32VersionValue << endl;
        cout << "Size of Image: " << optionalHeader.pe32plus.sizeOfImage << " bytes" << endl;
        cout << "Size of Headers: " << optionalHeader.pe32plus.sizeOfHeaders << " bytes" << endl;
        cout << "Checksum: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.checksum << endl;
        cout << "Subsystem: 0x" << hex << setw(4) << setfill('0') << optionalHeader.pe32plus.subsystem << endl;
        cout << "DLL Characteristics: 0x" << hex << setw(4) << setfill('0') << optionalHeader.pe32plus.dllCharacteristics << endl;
        cout << "Size of Stack Reserve: " << optionalHeader.pe32plus.sizeOfStackReserve << " bytes" << endl;
        cout << "Size of Stack Commit: " << optionalHeader.pe32plus.sizeOfStackCommit << " bytes" << endl;
        cout << "Size of Heap Reserve: " << optionalHeader.pe32plus.sizeOfHeapReserve << " bytes" << endl;
        cout << "Size of Heap Commit: " << optionalHeader.pe32plus.sizeOfHeapCommit << " bytes" << endl;
        cout << "Loader Flags: " << optionalHeader.pe32plus.loaderFlags << endl;
        cout << "Number of Data Directories: " << optionalHeader.pe32plus.numberOfRvaAndSizes << endl;
        // Print more fields if needed
        cout << "Export Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.exportTableAddress << endl;
        cout << "Export Table Size: " << optionalHeader.pe32plus.exportTableSize << " bytes" << endl;
        cout << "Import Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.importTableAddress << endl;
        cout << "Import Table Size: " << optionalHeader.pe32plus.importTableSize << " bytes" << endl;
        cout << "Resource Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.resourceTableAddress << endl;
        cout << "Resource Table Size: " << optionalHeader.pe32plus.resourceTableSize << " bytes" << endl;
        cout << "Exception Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.exceptionTableAddress << endl;
        cout << "Exception Table Size: " << optionalHeader.pe32plus.exceptionTableSize << " bytes" << endl;
        cout << "Certificate Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.certificateTableAddress << endl;
        cout << "Certificate Table Size: " << optionalHeader.pe32plus.certificateTableSize << " bytes" << endl;
        cout << "Base Relocation Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.baseRelocationTableAddress << endl;
        cout << "Base Relocation Table Size: " << optionalHeader.pe32plus.baseRelocationTableSize << " bytes" << endl;
        cout << "Debug Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.debugAddress << endl;
        cout << "Debug Size: " << optionalHeader.pe32plus.debugSize << " bytes" << endl;
        cout << "Architecture Data Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.architectureDataAddress << endl;
        cout << "Architecture Data Size: " << optionalHeader.pe32plus.architectureDataSize << " bytes" << endl;
        cout << "Global Pointer Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.globalPtrAddress << endl;
        cout << "Global Pointer Size: " << optionalHeader.pe32plus.globalPtrSize << " bytes" << endl;
        cout << "TLS Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.tlsTableAddress << endl;
        cout << "TLS Table Size: " << optionalHeader.pe32plus.tlsTableSize << " bytes" << endl;
        cout << "Load Config Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.loadConfigTableAddress << endl;
        cout << "Load Config Table Size: " << optionalHeader.pe32plus.loadConfigTableSize << " bytes" << endl;
        cout << "Bound Import Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.boundImportTableAddress << endl;
        cout << "Bound Import Table Size: " << optionalHeader.pe32plus.boundImportTableSize << " bytes" << endl;
        cout << "Import Address Table Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.importAddressTableAddress << endl;
        cout << "Import Address Table Size: " << optionalHeader.pe32plus.importAddressTableSize << " bytes" << endl;
        cout << "Delay Import Descriptor Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.delayImportDescriptorAddress << endl;
        cout << "Delay Import Descriptor Size: " << optionalHeader.pe32plus.delayImportDescriptorSize << " bytes" << endl;
        cout << "CLR Runtime Header Address: 0x" << hex << setw(8) << setfill('0') << optionalHeader.pe32plus.clrRuntimeHeaderAddress << endl;
        cout << "CLR Runtime Header Size: " << optionalHeader.pe32plus.clrRuntimeHeaderSize << " bytes" << endl;
        cout << "Reserved: " << optionalHeader.pe32plus.reserved << endl;
    }

    void printSectionHeader() const {
        cout << "Section Headers:" << endl;
        for (const auto& section : sectionHeaders) {
            cout << "Name: " << section.name << endl;
            cout << "Virtual Size: " << section.virtualSize << " bytes" << endl;
            cout << "Virtual Address: 0x" << hex << setw(8) << setfill('0') << section.virtualAddress << endl;
            cout << "Size of Raw Data: " << section.sizeOfRawData << " bytes" << endl;
            cout << "Pointer to Raw Data: 0x" << hex << setw(8) << setfill('0') << section.pointerToRawData << endl;
            cout << "Pointer to Relocations: 0x" << hex << setw(8) << setfill('0') << section.pointerToRelocations << endl;
            cout << "Pointer to Line Numbers: 0x" << hex << setw(8) << setfill('0') << section.pointerToLineNumbers << endl;
            cout << "Number of Relocations: " << section.numberOfRelocations << endl;
            cout << "Number of Line Numbers: " << section.numberOfLineNumbers << endl;
            cout << "Characteristics: 0x" << hex << setw(8) << setfill('0') << section.characteristics << endl;
            cout << endl;
        }
    }
};

int main() {
    PEParser parser;
    if (parser.load("example.exe")) {
        parser.printDOSHeader();
        parser.printCOFFHeader();
        parser.printOptionalHeader();
        parser.printSectionHeader();
    }

    return 0;
}


/* Printing example:

DOS Header:
Magic Number: 0x5A4D
Address of New Exe Header: 0x00000080

COFF Header:
Machine Type: 0x014C
Number of Sections: 5
Timestamp: 0x609F3C21
Pointer to Symbol Table: 0x00000000
Number of Symbols: 0
Size of Optional Header: 224 bytes
Characteristics: 0x010F

Optional Header:
Magic Number: 0x010B
Linker Version: 14.29
Size of Code: 8192 bytes
Size of Initialized Data: 122880 bytes
Size of Uninitialized Data: 0 bytes
Entry Point Address: 0x00401000
Base of Code: 0x00401000
Base of Data: 0x00403000
Image Base: 0x00400000
Section Alignment: 4096 bytes
File Alignment: 512 bytes
Major Operating System Version: 6
Minor Operating System Version: 0
Major Image Version: 0
Minor Image Version: 0
Major Subsystem Version: 6
Minor Subsystem Version: 0
Win32 Version Value: 0
Size of Image: 159744 bytes
Size of Headers: 1024 bytes
Checksum: 0x00000000
Subsystem: 0x0003
DLL Characteristics: 0x8540
Size of Stack Reserve: 1048576 bytes
Size of Stack Commit: 4096 bytes
Size of Heap Reserve: 1048576 bytes
Size of Heap Commit: 4096 bytes
Loader Flags: 0
Number of Data Directories: 16

Section Headers:
Name: .text
Virtual Size: 12288 bytes
Virtual Address: 0x00001000
Size of Raw Data: 12288 bytes
Pointer to Raw Data: 0x00000400
Pointer to Relocations: 0x00000000
Pointer to Line Numbers: 0x00000000
Number of Relocations: 0
Number of Line Numbers: 0
Characteristics: 0x60000020

Name: .data
Virtual Size: 4096 bytes
Virtual Address: 0x00004000
Size of Raw Data: 4096 bytes
Pointer to Raw Data: 0x00003400
Pointer to Relocations: 0x00000000
Pointer to Line Numbers: 0x00000000
Number of Relocations: 0
Number of Line Numbers: 0
Characteristics: 0xC0000040

Name: .rdata
Virtual Size: 4096 bytes
Virtual Address: 0x00005000
Size of Raw Data: 4096 bytes
Pointer to Raw Data: 0x00003800
Pointer to Relocations: 0x00000000
Pointer to Line Numbers: 0x00000000
Number of Relocations: 0
Number of Line Numbers: 0
Characteristics: 0x40000040

Name: .reloc
Virtual Size: 3072 bytes
Virtual Address: 0x00006000
Size of Raw Data: 3072 bytes
Pointer to Raw Data: 0x00003C00
Pointer to Relocations: 0x00000000
Pointer to Line Numbers: 0x00000000
Number of Relocations: 0
Number of Line Numbers: 0
Characteristics: 0x42000040

Name: .rsrc
Virtual Size: 4096 bytes
Virtual Address: 0x00002000
Size of Raw Data: 4096 bytes
Pointer to Raw Data: 0x00003000
Pointer to Relocations: 0x00000000
Pointer to Line Numbers: 0x00000000
Number of Relocations: 0
Number of Line Numbers: 0
Characteristics: 0x40000040

*/