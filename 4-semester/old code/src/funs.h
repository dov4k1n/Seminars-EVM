#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdint>
#include <ctime>

struct section_table {
  uint64_t Name;
  //uint32_t VirtualSize;
  //uint32_t VirtualAddress;                // RVA address of section with code
  uint32_t SizeOfRawData;
  uint32_t PointerToRawData;                // address of RAW data
  //uint32_t PointerToRelocations;
  //uint32_t PointerTotextnumbers;
  //uint16_t NumberOfRelocations;
  //uint16_t NumberOftextnumbers;
  //uint32_t CharacteristicsSectionHeader;
};

class exe_info {
  public:
    // DOS Header:
    uint16_t e_magic;         // Magic number 0x5A4D for exe files (~MZ in ASCII)
    /*uint16_t e_cblp;          // Bytes on last page of file
    uint16_t e_cp;            // Pages in file
    uint16_t e_crlc;          // Relocations
    uint16_t e_cparhdr;       // Size of header in paragraphs
    uint16_t e_minalloc;      // Minimum extra paragraphs needed
    uint16_t e_maxalloc;      // Maximum extra paragraphs needed
    uint16_t e_ss;            // Initial (relative) SS value
    uint16_t e_sp;            // Initial SP value
    uint16_t e_csum;          // Checksum
    uint16_t e_ip;            // Initial IP value
    uint16_t e_cs;            // Initial (relative) CS value
    uint16_t e_lfarlc;        // File address of relocation table
    uint16_t e_ovno;          // Overlay number
    uint16_t e_res[4];        // Reserved words
    uint16_t e_oemid;         // OEM identifier (for e_oeminfo)
    uint16_t e_oeminfo;       // OEM information; e_oemid specific
    uint16_t e_res2[10];*/     // Reserved words
    uint32_t e_lfanew;        // File address of new exe header
    
    // DOS Stub is not neaded to read. ends in e_lfanew address in hex

    uint32_t Signature;       // 0x00004550 (Portable Executable)

    // COFF Header ~ File Header:
    uint16_t Machine;                       // Architecture (intel 32 bit)
    uint16_t NumberOfSections;              // Number of sections in Section Header (1, 2, 3, ...)
    uint32_t TimeDateStamp;                 // Date and Time of file creation
    uint32_t PointerToSymbolTable;          // zeros
    uint32_t NumberOfSymbols;               // zeros
    uint16_t SizeOfOptionalHeader;          // Size of the next header
    uint16_t CharacteristicsFileHeader;     // Characteristics of file

    // Optional Header:
    // Standard COFF Fields
    uint16_t Magic;                         // 0x020B (PE32+)
    uint8_t MajorLinkerVersion;             // версия компановщика (5.4 ~ 05)
    uint8_t MinorLinkerVersion;             // версия компановщика (5.4 ~ 04)
    uint32_t SizeOfCode;                    // Size of code sections  
    uint32_t SizeOfInitializedData;         // Size of initialized data sections
    uint32_t SizeOfUninitializedData;       // Size of not initialized data sections
    uint32_t AddressOfEntryPoint;           // RVA of entry point to program
    uint32_t BaseOfCode;                    // RVA (relative virtual address) sections with code

    // Windows Specific Fields
    uint64_t ImageBase;                     // Preferable virtual address (multiple to 64kb, default 4mb)
    uint32_t SectionAlignment;              // Alignment in virtual memory (4 kilobytes)
    uint32_t FileAlignment;                 // Alignment in exe file (512kb)
    uint16_t MajorOperatingSystemVersion;   // Operating system version (default 4.0 ~ 0004)
    uint16_t MinorOperatingSystemVersion;   // Operating system version (default 4.0 ~ 0000)
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;         // Operating system version
    uint16_t MinorSubsystemVersion;         // Operating system version
    uint32_t Win32VersionValue;             // reserved (0x00000000)
    uint32_t SizeOfImage;                   // Size of program in virtual memory
    uint32_t SizeOfHeaders;                 // Size of all Headers (multiple to File Alignment 512kb)
    uint32_t CheckSum;
    uint16_t Subsystem;                     // type of program (graphical or console)
    uint16_t DllCharacteristics;
    uint64_t SizeOfStackReserve;            // reserved size for Stack (default 1Mb)
    uint64_t SizeOfStackCommit;             // initial Stack size (default 4kb)
    uint64_t SizeOfHeapReserve;             // reserved size for Heap (default 1Mb)
    uint64_t SizeOfHeapCommit;              // initial Heap size (default 4kb)
    uint32_t LoaderFlags;                   // unused (0x00000000)
    uint32_t NumberOfRvaAndSizes;           // number of elements in data_directories (16)

    // Data Directories
    /*
    uint64_t ExportTable;                   // address and size of export table
    uint64_t ImportTable;                   // address and size of import table
    uint64_t ResourceTable;                 // address and size of resources table
    uint64_t ExceptionTable;                // ...
    uint64_t CertificateTable;
    uint64_t BaseRelocationTable;
    uint64_t Debug;
    uint64_t Architecture;
    uint64_t GlobalPtr;
    uint64_t TLSTable;
    uint64_t LoadConfigTable;
    uint64_t BoundImport;
    uint64_t IAT;
    uint64_t DelayImportDescriptor;
    uint64_t CLRRuntimeHeader;
    uint64_t Reserved;                      // must be zero
    */
    // end of Optional Header.

    // Section Header:
    std::vector<section_table> Section;
};

int read_exe_info (exe_info *exe, FILE *f);

std::string epoch_to_human(const time_t& rawtime);

std::string uint64_to_text(const uint64_t& num);

void print_exe_info(exe_info *exe);

std::vector<uint8_t> text_to_uint8vect(const std::string& text);

std::string uint8vect_to_text(const std::vector<uint8_t>& encoded);