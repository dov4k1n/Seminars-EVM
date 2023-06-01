#include <iostream>
#include <cstdint>
#include <cstdio>

class exe_info {
  public:
    // DOS Header:
    uint16_t e_magic;         // Magic number 0x5A4D (~MZ in ASCII)
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
    
    // DOS Stub not neaded to read. ends in e_lfanew address in hex

    uint32_t Signature;       // 0x00004550 (Portable Executable)

    // COFF Header ~ File Header:
    uint16_t Machine;                       // Architecture (intel 32 bit)
    uint16_t NumberOfSections;              
    uint32_t TimeDateStamp;                 // Date and Time of file creation
    uint32_t PointerToSymbolTable;          // zeros
    uint32_t NumberOfSymbols;               // zeros
    uint16_t SizeOfOptionalHeader;          // Size of the next header
    uint16_t CharacteristicsFileHeader;     // Characteristics of file

    // Optional Header 32:
    // Standard COFF Fields
    uint16_t Magic;                         // 0x010B (PE32)
    uint8_t MajorLinkerVersion;             // версия компановщика (5.4 ~ 05)
    uint8_t MinorLinkerVersion;             // версия компановщика (5.4 ~ 04)
    uint32_t SizeOfCode;                    // Size of code sections  
    uint32_t SizeOfInitializedData;         // Size of initialized data sections
    uint32_t SizeOfUninitializedData;       // Size of not initialized data sections
    uint32_t AddressOfEntryPoint;           // RVA of entry point to program
    uint32_t BaseOfCode;                    // RVA (relative virtual address) sections with code

    // Windows Specific Fields
    uint32_t BaseOfData;                    // RVA sections with data
    uint32_t ImageBase;                     // Preferable virtual address (multiple to 64kb, default 4mb)
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
    uint32_t SizeOfStackReserve;            // reserved size for Stack (default 1Mb)
    uint32_t SizeOfStackCommit;             // initial Stack size (default 4kb)
    uint32_t SizeOfHeapReserve;             // reserved size for Heap (default 1Mb)
    uint32_t SizeOfHeapCommit;              // initial Heap size (default 4kb)
    uint32_t LoaderFlags;                   // unused (0x00000000)
    uint32_t NumberOfRvaAndSizes;           // number of elements in data_directories (16)

    // Data Directories ~ array of structures and pointers and lengths
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
    // end of Optional Header 32.

    // Section Table ~ Section Header
    // Each section header (section table entry) has
    // the following format, for a total of 40 bytes per entry.
    /*
    uint64_t Name;
    uint32_t VirtualSize;
    uint32_t VirtualAddress;                // RVA address of section with code
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t CharacteristicsSectionHeader;
    */
};

const int EXE_SUCCESS = 0;
const int READ_ERROR = -1;
const int NOT_EXE = -10;
const int NOT_PE = -11;
const int NOT_PE32 = -12;

int read_exe_info (exe_info *exe, FILE *f) {
  fseek(f, 0, SEEK_SET);
  int res;

  uint16_t e_magic;
  res = fread(&e_magic, sizeof(e_magic), 1, f);
  if (res != 1)
    return READ_ERROR;
  if (e_magic != 0x5A4D)
    return NOT_EXE;
  exe->e_magic = e_magic;
  
  fseek(f, 60, SEEK_SET); // сместились на 60 байт, чтобы считать e_lfanew
  uint32_t e_lfanew;
  res = fread(&e_lfanew, sizeof(e_lfanew), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->e_lfanew = e_lfanew;

  fseek(f, e_lfanew, SEEK_SET); // сместились к началу signature

  uint32_t Signature;
  res = fread(&Signature, sizeof(Signature), 1, f);
  if (res != 1)
    return READ_ERROR;
  if (Signature != 0x00004550)
    return NOT_PE;
  exe->Signature = Signature;

  uint16_t Machine;
  res = fread(&Machine, sizeof(Machine), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Machine = Machine;

  uint16_t NumberOfSections;
  res = fread(&NumberOfSections, sizeof(NumberOfSections), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->NumberOfSections = NumberOfSections;

  uint32_t TimeDateStamp;
  res = fread(&TimeDateStamp, sizeof(TimeDateStamp), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->TimeDateStamp = TimeDateStamp;

  uint32_t PointerToSymbolTable;
  res = fread(&PointerToSymbolTable, sizeof(PointerToSymbolTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->PointerToSymbolTable = PointerToSymbolTable;

  uint32_t NumberOfSymbols;
  res = fread(&NumberOfSymbols, sizeof(NumberOfSymbols), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->NumberOfSymbols = NumberOfSymbols;

  uint16_t SizeOfOptionalHeader;
  res = fread(&SizeOfOptionalHeader, sizeof(SizeOfOptionalHeader), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfOptionalHeader = SizeOfOptionalHeader;
  
  uint16_t CharacteristicsFileHeader;
  res = fread(&CharacteristicsFileHeader, sizeof(CharacteristicsFileHeader), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->CharacteristicsFileHeader = CharacteristicsFileHeader;
  
  uint16_t Magic;
  res = fread(&Magic, sizeof(Magic), 1, f);
  if (res != 1)
    return READ_ERROR;
  if (Magic != 0x010B)
    return NOT_PE32;
  exe->Magic = Magic;
  
  uint8_t MajorLinkerVersion;
  res = fread(&MajorLinkerVersion, sizeof(MajorLinkerVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MajorLinkerVersion = MajorLinkerVersion;
  
  uint8_t MinorLinkerVersion;
  res = fread(&MinorLinkerVersion, sizeof(MinorLinkerVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MinorLinkerVersion = MinorLinkerVersion;
  
  uint32_t SizeOfCode;
  res = fread(&SizeOfCode, sizeof(SizeOfCode), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfCode = SizeOfCode;
  
  uint32_t SizeOfInitializedData;
  res = fread(&SizeOfInitializedData, sizeof(SizeOfInitializedData), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfInitializedData = SizeOfInitializedData;

  uint32_t SizeOfUninitializedData;
  res = fread(&SizeOfUninitializedData, sizeof(SizeOfUninitializedData), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfUninitializedData = SizeOfUninitializedData;

  uint32_t AddressOfEntryPoint;
  res = fread(&AddressOfEntryPoint, sizeof(AddressOfEntryPoint), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->AddressOfEntryPoint = AddressOfEntryPoint;
  
  uint32_t BaseOfCode;
  res = fread(&BaseOfCode, sizeof(BaseOfCode), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->BaseOfCode = BaseOfCode;
  
  uint32_t BaseOfData;
  res = fread(&BaseOfData, sizeof(BaseOfData), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->BaseOfData = BaseOfData;

  uint32_t ImageBase;
  res = fread(&ImageBase, sizeof(ImageBase), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->ImageBase = ImageBase;

  uint32_t SectionAlignment;
  res = fread(&SectionAlignment, sizeof(SectionAlignment), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SectionAlignment = SectionAlignment;

  uint32_t FileAlignment;
  res = fread(&FileAlignment, sizeof(FileAlignment), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->FileAlignment = FileAlignment;

  uint16_t MajorOperatingSystemVersion;
  res = fread(&MajorOperatingSystemVersion, sizeof(MajorOperatingSystemVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MajorOperatingSystemVersion = MajorOperatingSystemVersion;
  
  uint16_t MinorOperatingSystemVersion;
  res = fread(&MinorOperatingSystemVersion, sizeof(MinorOperatingSystemVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MinorOperatingSystemVersion = MinorOperatingSystemVersion;
  
  uint16_t MajorImageVersion;
  res = fread(&MajorImageVersion, sizeof(MajorImageVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MajorImageVersion = MajorImageVersion;
  
  uint16_t MinorImageVersion;
  res = fread(&MinorImageVersion, sizeof(MinorImageVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MinorImageVersion = MinorImageVersion;
  
  uint16_t MajorSubsystemVersion;
  res = fread(&MajorSubsystemVersion, sizeof(MajorSubsystemVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MajorSubsystemVersion = MajorSubsystemVersion;

  uint16_t MinorSubsystemVersion;
  res = fread(&MinorSubsystemVersion, sizeof(MinorSubsystemVersion), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->MinorSubsystemVersion = MinorSubsystemVersion;

  uint32_t Win32VersionValue;
  res = fread(&Win32VersionValue, sizeof(Win32VersionValue), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Win32VersionValue = Win32VersionValue;

  uint32_t SizeOfImage;
  res = fread(&SizeOfImage, sizeof(SizeOfImage), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfImage = SizeOfImage;

  uint32_t SizeOfHeaders;
  res = fread(&SizeOfHeaders, sizeof(SizeOfHeaders), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfHeaders = SizeOfHeaders;

  uint32_t CheckSum;
  res = fread(&CheckSum, sizeof(CheckSum), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->CheckSum = CheckSum;

  uint16_t Subsystem;
  res = fread(&Subsystem, sizeof(Subsystem), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Subsystem = Subsystem;

  uint16_t DllCharacteristics;
  res = fread(&DllCharacteristics, sizeof(DllCharacteristics), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->DllCharacteristics = DllCharacteristics; 

  uint32_t SizeOfStackReserve;
  res = fread(&SizeOfStackReserve, sizeof(SizeOfStackReserve), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfStackReserve = SizeOfStackReserve;

  uint32_t SizeOfStackCommit;
  res = fread(&SizeOfStackCommit, sizeof(SizeOfStackCommit), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfStackCommit = SizeOfStackCommit;

  uint32_t SizeOfHeapReserve;
  res = fread(&SizeOfHeapReserve, sizeof(SizeOfHeapReserve), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfHeapReserve = SizeOfHeapReserve;

  uint32_t SizeOfHeapCommit;
  res = fread(&SizeOfHeapCommit, sizeof(SizeOfHeapCommit), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfHeapCommit = SizeOfHeapCommit;

  uint32_t LoaderFlags;
  res = fread(&LoaderFlags, sizeof(LoaderFlags), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->LoaderFlags = LoaderFlags;

  uint32_t NumberOfRvaAndSizes;
  res = fread(&NumberOfRvaAndSizes, sizeof(NumberOfRvaAndSizes), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->NumberOfRvaAndSizes = NumberOfRvaAndSizes;

  return EXE_SUCCESS;
}

int print_exe_info(exe_info *exe) {

	std::cout << "\n" << "analysed:\n" << std::endl;

  std::cout << "DOS Header Magic Number: 0x" << std::hex << exe->e_magic << std::dec << std::endl;
  std::cout << "File address of new exe header: 0x" << std::hex << exe->e_lfanew << std::dec << std::endl;

	std::cout << std::endl;

  std::cout << "COFF Header Signature: 0x" << std::hex << exe->Signature << std::dec << std::endl;

  std::cout << "Machine: ";
  if (exe->Machine == 0x0) {
    std::cout << "The content of this field is assumed to be applicable to any machine type" << std::endl;
  }

  if (exe->Machine == 0x184) {
    std::cout << "Alpha AXP, 32-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x284) {
    std::cout << "Alpha 64, 64-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x184) {
    std::cout << "Alpha AXP, 32-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x1d3) {
    std::cout << "Matsushita AM33" << std::endl;
  }

  else if (exe->Machine == 0x8664) {
    std::cout << "x64" << std::endl;
  }

  else if (exe->Machine == 0x1c0) {
    std::cout << "ARM little endian" << std::endl;
  }

  else if (exe->Machine == 0xaa64) {
    std::cout << "ARM64 little endian" << std::endl;
  }

  else if (exe->Machine == 0x1c4) {
    std::cout << "ARM Thumb-2 little endian" << std::endl;
  }

  else if (exe->Machine == 0x284) {
    std::cout << "AXP 64 (Same as Alpha 64)" << std::endl;
  }

  else if (exe->Machine == 0xebc) {
    std::cout << "EFI byte code" << std::endl;
  }

  else if (exe->Machine == 0x14c) {
    std::cout << "Intel 386 or later processors and compatible processors" << std::endl;
  }

  else if (exe->Machine == 0x200) {
    std::cout << "Intel Itanium processor family" << std::endl;
  }

  else if (exe->Machine == 0x6232) {
    std::cout << "LoongArch 32-bit processor family" << std::endl;
  }

  else if (exe->Machine == 0x6264) {
    std::cout << "LoongArch 64-bit processor family" << std::endl;
  }

  else if (exe->Machine == 0x9041) {
    std::cout << "Mitsubishi M32R little endian" << std::endl;
  }

  else if (exe->Machine == 0x266) {
    std::cout << "MIPS16" << std::endl;
  }

  else if (exe->Machine == 0x366) {
    std::cout << "MIPS with FPU" << std::endl;
  }

  else if (exe->Machine == 0x466) {
    std::cout << "MIPS16 with FPU" << std::endl;
  }

  else if (exe->Machine == 0x1f0) {
    std::cout << "Power PC little endian" << std::endl;
  }

  else if (exe->Machine == 0x1f1) {
    std::cout << "Power PC with floating point support" << std::endl;
  }

  else if (exe->Machine == 0x166) {
    std::cout << "MIPS little endian" << std::endl;
  }

  else if (exe->Machine == 0x5032) {
    std::cout << "RISC-V 32-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x5064) {
    std::cout << "RISC-V 64-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x5128) {
    std::cout << "RISC-V 128-bit address space" << std::endl;
  }

  else if (exe->Machine == 0x1a2) {
    std::cout << "Hitachi SH3" << std::endl;
  }

  else if (exe->Machine == 0x1a3) {
    std::cout << "Hitachi SH3 DSP" << std::endl;
  }

  else if (exe->Machine == 0x1a6) {
    std::cout << "Hitachi SH4" << std::endl;
  }

  else if (exe->Machine == 0x1a8) {
    std::cout << "Hitachi SH5" << std::endl;
  }

  else if (exe->Machine == 0x1c2) {
    std::cout << "Thumb" << std::endl;
  }

  else if (exe->Machine == 0x169) {
    std::cout << "MIPS little-endian WCE v2" << std::endl;
  }

	else {
		std::cout << "non classified 0x" << std::hex << exe->Machine << std::dec << std::endl;
	}

  std::cout << "Number of Sections: " << exe->NumberOfSections << std::endl;
	std::cout << "Timestamp: 0x" << std::hex << exe->TimeDateStamp << std::dec << std::endl;
	std::cout << "Pointer to symbol table (zero): 0x" << std::hex << exe->PointerToSymbolTable << std::dec << std::endl;
	std::cout << "Number of Symbols (zero): " << exe->NumberOfSymbols << std::endl;
  std::cout << "Size of Optional Header: " << exe->SizeOfOptionalHeader << std::endl;
  
  std::cout << "Characteristics File Header: ";
  if (exe->CharacteristicsFileHeader == 0x0001) {
    std::cout << "Image only, Windows CE, and Microsoft Windows NT and later." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0002) {
    std::cout << "Image only." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0004) {
    std::cout << "COFF line numbers have been removed." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0008) {
    std::cout << "COFF symbol table entries for local symbols have been removed." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0010) {
    std::cout << "Obsolete. Aggressively trim working set." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0020) {
    std::cout << "Application can handle > 2-GB addresses." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0040) {
    std::cout << "This flag is reserved for future use." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0080) {
    std::cout << "Little endian: the least significant bit (LSB) precedes the most significant bit (MSB) in memory." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0100) {
    std::cout << "Machine is based on a 32-bit-word architecture." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0200) {
    std::cout << "Debugging information is removed from the image file." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0400) {
    std::cout << "If the image is on removable media, fully load it and copy it to the swap file." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x0800) {
    std::cout << "If the image is on network media, fully load it and copy it to the swap file." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x1000) {
    std::cout << "The image file is a system file, not a user program." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x2000) {
    std::cout << "The image file is a dynamic-link library (DLL). Such files are considered executable files for almost all purposes, although they cannot be directly run." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x4000) {
    std::cout << "The file should be run only on a uniprocessor machine." << std::endl;
  }

  else if (exe->CharacteristicsFileHeader == 0x8000) {
    std::cout << "Big endian: the MSB precedes the LSB in memory." << std::endl;
  }

	else {
		std::cout << "non classified 0x" << std::hex << exe->CharacteristicsFileHeader << std::dec << std::endl;
	}

	std::cout << std::endl;

  std::cout << "Optional Header Magic: 0x" << std::hex << exe->Magic << std::dec << std::endl;
  std::cout << "Linker Version: " << unsigned(exe->MajorLinkerVersion) << "." << unsigned(exe->MinorLinkerVersion) << std::endl;
  std::cout << "Size Of Code: " << exe->SizeOfCode << std::endl;
  std::cout << "Size Of Initialized Data: " << exe->SizeOfInitializedData << std::endl;
  std::cout << "Size Of Uninitialized Data: " << exe->SizeOfUninitializedData << std::endl;
  std::cout << "Address Of Entry Point: 0x" << std::hex << exe->AddressOfEntryPoint << std::endl;
  std::cout << "Base Of Code: 0x" << exe->BaseOfCode << std::endl;
  std::cout << "Base Of Data: 0x" << exe->BaseOfData << std::endl;
  std::cout << "Image Base: 0x" << exe->ImageBase << std::dec << std::endl;
  std::cout << "Section Alignment: " << exe->SectionAlignment << std::endl;
  std::cout << "File Alignment: " << exe->FileAlignment << std::endl;
  std::cout << "Operating System Version: " << exe->MajorOperatingSystemVersion << "." << exe->MinorOperatingSystemVersion << std::endl;
  std::cout << "Image Version: " << exe->MajorImageVersion << "." << exe->MinorImageVersion << std::endl;
  std::cout << "Subsystem Version: " << exe->MajorSubsystemVersion << "." << exe->MinorSubsystemVersion << std::endl;
  std::cout << "Win32 Version Value: " << exe->Win32VersionValue << std::endl;
  std::cout << "Size Of Image: " << exe->SizeOfImage << std::endl;
  std::cout << "Size Of Headers: " << exe->SizeOfHeaders << std::endl;
  std::cout << "Check Sum: " << exe->CheckSum << std::endl;

  std::cout << "Windows Subsystem: ";
  if (exe->Subsystem == 0) {
    std::cout << "An unknown subsystem." << std::endl;
  }

  else if (exe->Subsystem == 1) {
    std::cout << "Device drivers and native Windows processes." << std::endl;
  }

  else if (exe->Subsystem == 2) {
    std::cout << "The Windows graphical user interface (GUI) subsystem." << std::endl;
  }

  else if (exe->Subsystem == 3) {
    std::cout << "The Windows character subsystem." << std::endl;
  }

  else if (exe->Subsystem == 5) {
    std::cout << "The OS/2 character subsystem." << std::endl;
  }

  else if (exe->Subsystem == 7) {
    std::cout << "The Posix character subsystem." << std::endl;
  }

  else if (exe->Subsystem == 8) {
    std::cout << "Native Win9x driver." << std::endl;
  }

  else if (exe->Subsystem == 9) {
    std::cout << "Windows CE." << std::endl;
  }

  else if (exe->Subsystem == 10) {
    std::cout << "An Extensible Firmware Interface (EFI) application." << std::endl;
  }

  else if (exe->Subsystem == 11) {
    std::cout << "An EFI driver with boot services." << std::endl;
  }

  else if (exe->Subsystem == 12) {
    std::cout << "An EFI driver with run-time services." << std::endl;
  }

  else if (exe->Subsystem == 13) {
    std::cout << "An EFI ROM image." << std::endl;
  }

  else if (exe->Subsystem == 14) {
    std::cout << "XBOX." << std::endl;
  }

  else if (exe->Subsystem == 16) {
    std::cout << "Windows boot application." << std::endl;
  }

	else {
		std::cout << "non classified 0x" << std::hex << exe->Subsystem << std::dec << std::endl;
	}

  std::cout << "Dll Characteristics: ";
  if (exe->DllCharacteristics == 0x0001) {
    std::cout << "Reserved, must be zero." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0002) {
    std::cout << "Reserved, must be zero." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0004) {
    std::cout << "Reserved, must be zero." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0008) {
    std::cout << "Reserved, must be zero." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0020) {
    std::cout << "Image can handle a high entropy 64-bit virtual address space." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0040) {
    std::cout << "DLL can be relocated at load time." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0080) {
    std::cout << "Code Integrity checks are enforced." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0100) {
    std::cout << "Image is NX compatible." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0200) {
    std::cout << "Isolation aware, but do not isolate the image." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0400) {
    std::cout << "Does not use structured exception (SE) handling. No SE handler may be called in this image." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x0800) {
    std::cout << "Do not bind the image." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x1000) {
    std::cout << "Image must execute in an AppContainer." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x2000) {
    std::cout << "A WDM driver." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x4000) {
    std::cout << "Image supports Control Flow Guard." << std::endl;
  }

  else if (exe->DllCharacteristics == 0x8000) {
    std::cout << "Terminal Server aware." << std::endl;
  }

	else {
		std::cout << "non classified 0x" << std::hex << exe->DllCharacteristics << std::dec << std::endl;
	}

  std::cout << "Size Of Stack Reserve: " << exe->SizeOfStackReserve << std::endl;
  std::cout << "Size Of Stack Commit: " << exe->SizeOfStackCommit << std::endl;
  std::cout << "Size Of Heap Reserve: " << exe->SizeOfHeapReserve << std::endl;
  std::cout << "Size Of Heap Commit: " << exe->SizeOfHeapCommit << std::endl;
  std::cout << "Loader Flags: 0x" << std::hex << exe->LoaderFlags << std::dec << std::endl;
  std::cout << "Number Of RVA And Sizes: " << exe->NumberOfRvaAndSizes << std::endl;
  
  return EXE_SUCCESS;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

	FILE *f = fopen( argv[1], "rb");
	if (f == NULL) {
		std::cout << "Error openning file" << std::endl;
		return -1;
	}

	exe_info exe;

	int ret;
	if ( (ret = read_exe_info(&exe, f)) < 0 ) {
		std::cout << "error reading exe file: " << ret << std::endl;
		fclose(f);
		return -1;
	}

	print_exe_info(&exe);

	fclose(f);
	return 0;
}