/*
 * Program to read Portable Executable 64 bit files (.exe) in binary format
 *
 * Sources:
 * 1. https://www.youtube.com/watch?v=-OzGawe9fmM&ab_channel=AlekOS
 * 2. https://en.wikipedia.org/wiki/Portable_Executable#/media/File:Portable_Executable_32_bit_Structure_in_SVG_fixed.svg
 * 3. https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
 * 4. https://www.mitec.cz/exe.html
 * 5. http://xn--80akaaied0aladi2a9h.xn--p1ai/course/sem_4/index.html
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <map>

std::string epoch_to_human(const time_t& rawtime) {
	struct tm local_timezone;
	char buf[80];

	local_timezone = *localtime(&rawtime);

	strftime(buf, sizeof(buf), "%a %d.%m.%Y %H:%M:%S", &local_timezone);

	return buf;
}

std::string uint64_to_text(const uint64_t& num) {
	std::string result = "";

	// Decode each 8-bit character by shifting right and masking with 0xFF
	for (int i = 7; i >= 0; i--) {
		uint8_t ch = (num >> (i * 8)) & 0xFF;
		if (ch != 0) {
			result = char(ch) + result;
		}
	}
	return result;
}

struct section_table {
	uint64_t Name;                   // Name of the section
	//uint32_t VirtualSize;
	//uint32_t VirtualAddress;       // RVA address of section with code
	uint32_t SizeOfRawData;          // Size of data of section
	uint32_t PointerToRawData;       // address of RAW data
	//uint32_t PointerToRelocations;
	//uint32_t PointerTotextnumbers;
	//uint16_t NumberOfRelocations;
	//uint16_t NumberOftextnumbers;
	//uint32_t CharacteristicsSectionHeader;
};

struct exe_info {
	/*
	 *
	 * DOS Header:
	 *
	 */

	uint16_t e_magic;    // Magic number 0x5A4D for exe files ("MZ" in ASCII)
	/*
	uint16_t e_cblp;     // Bytes on last page of file
	uint16_t e_cp;       // Pages in file
	uint16_t e_crlc;     // Relocations
	uint16_t e_cparhdr;  // Size of header in paragraphs
	uint16_t e_minalloc; // Minimum extra paragraphs needed
	uint16_t e_maxalloc; // Maximum extra paragraphs needed
	uint16_t e_ss;       // Initial (relative) SS value
	uint16_t e_sp;       // Initial SP value
	uint16_t e_csum;     // Checksum
	uint16_t e_ip;       // Initial IP value
	uint16_t e_cs;       // Initial (relative) CS value
	uint16_t e_lfarlc;   // File address of relocation table
	uint16_t e_ovno;     // Overlay number
	uint16_t e_res[4];   // Reserved words
	uint16_t e_oemid;    // OEM identifier (for e_oeminfo)
	uint16_t e_oeminfo;  // OEM information; e_oemid specific
	uint16_t e_res2[10]; // Reserved words
	*/
	uint32_t e_lfanew;   // File address of new exe header

	/*
	 *
	 * I skip DOS Stub. Ends in e_lfanew address.
	 *
	 */

	/*
	 *
	 * COFF Header (File Header):
	 *
	 */

	uint32_t PE_Signature;              // 0x00004550 (Portable Executable)
	uint16_t Machine;                   // Architecture (intel 32 bit)
	uint16_t NumberOfSections;          // Number of sections in Section Header
	uint32_t TimeDateStamp;             // Date and Time of file creation
	uint32_t PointerToSymbolTable;      // zeros
	uint32_t NumberOfSymbols;           // zeros
	uint16_t SizeOfOptionalHeader;      // Size of the next header
	uint16_t CharacteristicsFileHeader; // Characteristics of file

	static const std::map<uint16_t, std::string>& getMachineTypes() {
		static const std::map<uint16_t, std::string> MachineTypes = {
			{0x0, "The content of this field is assumed to be applicable to any machine type"},
			{0x184, "Alpha AXP, 32-bit address space"},
			{0x284, "Alpha 64, 64-bit address space"},
			{0x1d3, "Matsushita AM33"},
			{0x8664, "x64"},
			{0x1c0, "ARM little endian"},
			{0xaa64, "ARM64 little endian"},
			{0x1c4, "ARM Thumb-2 little endian"},
			{0x1c2, "Thumb"},
			{0x14c, "Intel 386 or later processors and compatible processors"},
			{0x200, "Intel Itanium processor family"},
			{0x6232, "LoongArch 32-bit processor family"},
			{0x6264, "LoongArch 64-bit processor family"},
			{0x9041, "Mitsubishi M32R little endian"},
			{0x266, "MIPS16"},
			{0x366, "MIPS with FPU"},
			{0x466, "MIPS16 with FPU"},
			{0x1f0, "Power PC little endian"},
			{0x1f1, "Power PC with floating point support"},
			{0x166, "MIPS little endian"},
			{0x5032, "RISC-V 32-bit address space"},
			{0x5064, "RISC-V 64-bit address space"},
			{0x5128, "RISC-V 128-bit address space"},
			{0x1a2, "Hitachi SH3"},
			{0x1a3, "Hitachi SH3 DSP"},
			{0x1a6, "Hitachi SH4"},
			{0x1a8, "Hitachi SH5"},
			{0x169, "MIPS little-endian WCE v2"}
		};
		return MachineTypes;
	}

	// CFHTypes stands for Characteristics File Header Types
	static const std::map<uint16_t, std::string>& getCFHTypes() {
		static const std::map<uint16_t, std::string> CFHTypes = {
            {0x0001, "Image only, Windows CE, and Microsoft Windows NT and later."},
			{0x0002, "Image only."},
			{0x0004, "COFF text numbers have been removed."},
			{0x0008, "COFF symbol table entries for local symbols have been removed."},
			{0x0010, "Obsolete. Aggressively trim working set."},
			{0x0020, "Application can handle > 2-GB addresses."},
			{0x0040, "This flag is reserved for future use."},
			{0x0080, "Little endian: the least significant bit (LSB) precedes the most significant bit (MSB) in memory."},
			{0x0100, "Machine is based on a 32-bit-word architecture."},
			{0x0200, "Debugging information is removed from the image file."},
			{0x0400, "If the image is on removable media, fully load it and copy it to the swap file."},
			{0x0800, "If the image is on network media, fully load it and copy it to the swap file."},
			{0x1000, "The image file is a system file, not a user program."},
			{0x2000, "The image file is a dynamic-link library (DLL)."},
			{0x4000, "The file should be run only on a uniprocessor machine."},
			{0x8000, "Big endian: the MSB precedes the LSB in memory."},
        };
        return CFHTypes;
    }

	/*
	 *
	 * Optional Header:
	 *
	 */
	
	// Standard COFF fields
	uint16_t Magic;                   // 0x020B (PE32+)
	uint8_t MajorLinkerVersion;       // версия компановщика (5.4 ~ 05)
	uint8_t MinorLinkerVersion;       // версия компановщика (5.4 ~ 04)
	uint32_t SizeOfCode;              // Size of code sections  
	uint32_t SizeOfInitializedData;   // Size of initialized data sections
	uint32_t SizeOfUninitializedData; // Size of not initialized data sections
	uint32_t AddressOfEntryPoint;     // RVA of entry point to program
	uint32_t BaseOfCode;              // RVA (relative virtual address) sections with code

	// Windows Specific fields
	uint64_t ImageBase;                   // Preferable virtual address (multiple to 64kb, default 4mb)
	uint32_t SectionAlignment;            // Alignment in virtual memory (4 kilobytes)
	uint32_t FileAlignment;               // Alignment in exe file (512kb)
	uint16_t MajorOperatingSystemVersion; // Operating system version (default 4.0 ~ 0004)
	uint16_t MinorOperatingSystemVersion; // Operating system version (default 4.0 ~ 0000)
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;       // Operating system version
	uint16_t MinorSubsystemVersion;       // Operating system version
	uint32_t Win32VersionValue;           // reserved (0x00000000)
	uint32_t SizeOfImage;                 // Size of program in virtual memory
	uint32_t SizeOfHeaders;               // Size of all Headers (multiple to File Alignment 512kb)
	uint32_t CheckSum;
	uint16_t Subsystem;                   // type of program (graphical or console)
	uint16_t DllCharacteristics;
	uint64_t SizeOfStackReserve;          // reserved size for Stack (default 1Mb)
	uint64_t SizeOfStackCommit;           // initial Stack size (default 4kb)
	uint64_t SizeOfHeapReserve;           // reserved size for Heap (default 1Mb)
	uint64_t SizeOfHeapCommit;            // initial Heap size (default 4kb)
	uint32_t LoaderFlags;                 // unused (0x00000000)
	uint32_t NumberOfRvaAndSizes;         // number of elements in data_directories (16)

	static const std::map<uint16_t, std::string>& getSubsystemTypes() {
		static const std::map<uint16_t, std::string> SubsystemTypes = {
			{0, "An unknown subsystem."},
			{1, "Device drivers and native Windows processes."},
			{2, "The Windows graphical user interface (GUI) subsystem."},
			{3, "The Windows character subsystem."},
			{5, "The OS/2 character subsystem."},
			{7, "The Posix character subsystem."},
			{8, "Native Win9x driver."},
			{9, "Windows CE."},
			{10, "An Extensible Firmware Interface (EFI) application."},
			{11, "An EFI driver with boot services."},
			{12, "An EFI driver with run-time services."},
			{13, "An EFI ROM image."},
			{14, "XBOX."},
			{16, "Windows boot application."}
		};
		return SubsystemTypes;
	}

	static const std::map<uint16_t, std::string>& getDLLTypes() {
		static const std::map<uint16_t, std::string> DLLTypes = {
			{0x0001, "Reserved, must be zero."},
			{0x0002, "Reserved, must be zero."},
			{0x0004, "Reserved, must be zero."},
			{0x0008, "Reserved, must be zero."},
			{0x0020, "Image can handle a high entropy 64-bit virtual address space."},
			{0x0040, "DLL can be relocated at load time."},
			{0x0080, "Code Integrity checks are enforced."},
			{0x0100, "Image is NX compatible."},
			{0x0200, "Isolation aware, but do not isolate the image."},
			{0x0400, "Does not use structured exception (SE) handling. No SE handler may be called in this image."},
			{0x0800, "Do not bind the image."},
			{0x1000, "Image must execute in an AppContainer."},
			{0x2000, "A WDM driver."},
			{0x4000, "Image supports Control Flow Guard."},
			{0x8000, "Terminal Server aware."}
		};
		return DLLTypes;
	}

	// Data Directories
	/*
	uint64_t ExportTable;           // address and size of export table
	uint64_t ImportTable;           // address and size of import table
	uint64_t ResourceTable;         // address and size of resources table
	uint64_t ExceptionTable;        // ...
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
	uint64_t Reserved;              // must be zero
	*/

	/*
	 *
	 * Section Header:
	 *
	 */

	std::vector<section_table> Section;
};

int read_exe_info (exe_info *exe, FILE *f) {
	const int EXE_SUCCESS = 0;
	const int READ_ERROR = -1;
	const int NOT_EXE = -2;
	const int NOT_PE = -3;
	const int NOT_PE32plus = -4;
	
	fseek(f, 0, SEEK_SET);
	int res;

	/*
	 *
	 * Reading DOS Header fields:
	 *
	 */

	uint16_t e_magic;
	res = fread(&e_magic, sizeof(e_magic), 1, f);
	if (res != 1) return READ_ERROR;
	if (e_magic != 0x5A4D) return NOT_EXE;
	exe->e_magic = e_magic;

	fseek(f, 60, SEEK_SET); // Seek to the position of e_lfanew
	uint32_t e_lfanew;
	res = fread(&e_lfanew, sizeof(e_lfanew), 1, f);
	if (res != 1) return READ_ERROR;
	exe->e_lfanew = e_lfanew;

	/*
	 *
	 * Reading COFF Header fields:
	 *
	 */

	fseek(f, e_lfanew, SEEK_SET); // Seek to the position of PE_Signature
	uint32_t PE_Signature;
	res = fread(&PE_Signature, sizeof(PE_Signature), 1, f);
	if (res != 1) return READ_ERROR;
	if (PE_Signature != 0x4550) return NOT_PE;
	exe->PE_Signature = PE_Signature;

	uint16_t Machine;
	res = fread(&Machine, sizeof(Machine), 1, f);
	if (res != 1) return READ_ERROR;
	exe->Machine = Machine;

	uint16_t NumberOfSections;
	res = fread(&NumberOfSections, sizeof(NumberOfSections), 1, f);
	if (res != 1) return READ_ERROR;
	exe->NumberOfSections = NumberOfSections;

	uint32_t TimeDateStamp;
	res = fread(&TimeDateStamp, sizeof(TimeDateStamp), 1, f);
	if (res != 1) return READ_ERROR;
	exe->TimeDateStamp = TimeDateStamp;

	uint32_t PointerToSymbolTable;
	res = fread(&PointerToSymbolTable, sizeof(PointerToSymbolTable), 1, f);
	if (res != 1) return READ_ERROR;
	exe->PointerToSymbolTable = PointerToSymbolTable;

	uint32_t NumberOfSymbols;
	res = fread(&NumberOfSymbols, sizeof(NumberOfSymbols), 1, f);
	if (res != 1) return READ_ERROR;
	exe->NumberOfSymbols = NumberOfSymbols;

	uint16_t SizeOfOptionalHeader;
	res = fread(&SizeOfOptionalHeader, sizeof(SizeOfOptionalHeader), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfOptionalHeader = SizeOfOptionalHeader;
	
	uint16_t CharacteristicsFileHeader;
	res = fread(&CharacteristicsFileHeader, sizeof(CharacteristicsFileHeader), 1, f);
	if (res != 1) return READ_ERROR;
	exe->CharacteristicsFileHeader = CharacteristicsFileHeader;

	/*
	 *
	 * Reading Optional Header fields:
	 *
	 */
	
	// Standard COFF fields

	uint16_t Magic;
	res = fread(&Magic, sizeof(Magic), 1, f);
	if (res != 1) return READ_ERROR;
	if (Magic != 0x020B) return NOT_PE32plus;
	exe->Magic = Magic;
	
	uint8_t MajorLinkerVersion;
	res = fread(&MajorLinkerVersion, sizeof(MajorLinkerVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MajorLinkerVersion = MajorLinkerVersion;
	
	uint8_t MinorLinkerVersion;
	res = fread(&MinorLinkerVersion, sizeof(MinorLinkerVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MinorLinkerVersion = MinorLinkerVersion;
	
	uint32_t SizeOfCode;
	res = fread(&SizeOfCode, sizeof(SizeOfCode), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfCode = SizeOfCode;
	
	uint32_t SizeOfInitializedData;
	res = fread(&SizeOfInitializedData, sizeof(SizeOfInitializedData), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfInitializedData = SizeOfInitializedData;

	uint32_t SizeOfUninitializedData;
	res = fread(&SizeOfUninitializedData, sizeof(SizeOfUninitializedData), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfUninitializedData = SizeOfUninitializedData;

	uint32_t AddressOfEntryPoint;
	res = fread(&AddressOfEntryPoint, sizeof(AddressOfEntryPoint), 1, f);
	if (res != 1) return READ_ERROR;
	exe->AddressOfEntryPoint = AddressOfEntryPoint;
	
	uint32_t BaseOfCode;
	res = fread(&BaseOfCode, sizeof(BaseOfCode), 1, f);
	if (res != 1) return READ_ERROR;
	exe->BaseOfCode = BaseOfCode;

	// Windows Specific fields

	uint64_t ImageBase;
	res = fread(&ImageBase, sizeof(ImageBase), 1, f);
	if (res != 1) return READ_ERROR;
	exe->ImageBase = ImageBase;

	uint32_t SectionAlignment;
	res = fread(&SectionAlignment, sizeof(SectionAlignment), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SectionAlignment = SectionAlignment;

	uint32_t FileAlignment;
	res = fread(&FileAlignment, sizeof(FileAlignment), 1, f);
	if (res != 1) return READ_ERROR;
	exe->FileAlignment = FileAlignment;

	uint16_t MajorOperatingSystemVersion;
	res = fread(&MajorOperatingSystemVersion, sizeof(MajorOperatingSystemVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MajorOperatingSystemVersion = MajorOperatingSystemVersion;
	
	uint16_t MinorOperatingSystemVersion;
	res = fread(&MinorOperatingSystemVersion, sizeof(MinorOperatingSystemVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MinorOperatingSystemVersion = MinorOperatingSystemVersion;
	
	uint16_t MajorImageVersion;
	res = fread(&MajorImageVersion, sizeof(MajorImageVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MajorImageVersion = MajorImageVersion;
	
	uint16_t MinorImageVersion;
	res = fread(&MinorImageVersion, sizeof(MinorImageVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MinorImageVersion = MinorImageVersion;
	
	uint16_t MajorSubsystemVersion;
	res = fread(&MajorSubsystemVersion, sizeof(MajorSubsystemVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MajorSubsystemVersion = MajorSubsystemVersion;

	uint16_t MinorSubsystemVersion;
	res = fread(&MinorSubsystemVersion, sizeof(MinorSubsystemVersion), 1, f);
	if (res != 1) return READ_ERROR;
	exe->MinorSubsystemVersion = MinorSubsystemVersion;

	uint32_t Win32VersionValue;
	res = fread(&Win32VersionValue, sizeof(Win32VersionValue), 1, f);
	if (res != 1) return READ_ERROR;
	exe->Win32VersionValue = Win32VersionValue;

	uint32_t SizeOfImage;
	res = fread(&SizeOfImage, sizeof(SizeOfImage), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfImage = SizeOfImage;

	uint32_t SizeOfHeaders;
	res = fread(&SizeOfHeaders, sizeof(SizeOfHeaders), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfHeaders = SizeOfHeaders;

	uint32_t CheckSum;
	res = fread(&CheckSum, sizeof(CheckSum), 1, f);
	if (res != 1) return READ_ERROR;
	exe->CheckSum = CheckSum;

	uint16_t Subsystem;
	res = fread(&Subsystem, sizeof(Subsystem), 1, f);
	if (res != 1) return READ_ERROR;
	exe->Subsystem = Subsystem;

	uint16_t DllCharacteristics;
	res = fread(&DllCharacteristics, sizeof(DllCharacteristics), 1, f);
	if (res != 1) return READ_ERROR;
	exe->DllCharacteristics = DllCharacteristics; 

	uint64_t SizeOfStackReserve;
	res = fread(&SizeOfStackReserve, sizeof(SizeOfStackReserve), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfStackReserve = SizeOfStackReserve;

	uint64_t SizeOfStackCommit;
	res = fread(&SizeOfStackCommit, sizeof(SizeOfStackCommit), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfStackCommit = SizeOfStackCommit;

	uint64_t SizeOfHeapReserve;
	res = fread(&SizeOfHeapReserve, sizeof(SizeOfHeapReserve), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfHeapReserve = SizeOfHeapReserve;

	uint64_t SizeOfHeapCommit;
	res = fread(&SizeOfHeapCommit, sizeof(SizeOfHeapCommit), 1, f);
	if (res != 1) return READ_ERROR;
	exe->SizeOfHeapCommit = SizeOfHeapCommit;

	uint32_t LoaderFlags;
	res = fread(&LoaderFlags, sizeof(LoaderFlags), 1, f);
	if (res != 1) return READ_ERROR;
	exe->LoaderFlags = LoaderFlags;

	uint32_t NumberOfRvaAndSizes;
	res = fread(&NumberOfRvaAndSizes, sizeof(NumberOfRvaAndSizes), 1, f);
	if (res != 1) return READ_ERROR;
	exe->NumberOfRvaAndSizes = NumberOfRvaAndSizes;

	/*
	 *
	 * Reading Section Table:
	 *
	 */
	
	section_table section;
	int SizeOfCoffHeader = 24;
	fseek(f, e_lfanew + SizeOfCoffHeader + SizeOfOptionalHeader, SEEK_SET);
	
	for (int i = 0; i < NumberOfSections; i++) {
		res = fread(&section.Name, sizeof(section.Name), 1, f);
		if (res != 1) return READ_ERROR;

		fseek(f, 8, SEEK_CUR);

		res = fread(&section.SizeOfRawData, sizeof(section.SizeOfRawData), 1, f);
		if (res != 1) return READ_ERROR;

		res = fread(&section.PointerToRawData, sizeof(section.PointerToRawData), 1, f);
		if (res != 1) return READ_ERROR;
		
		exe->Section.push_back(section);

		if (i < NumberOfSections - 1) {
			fseek(f, 16, SEEK_CUR);
		}
	}
	
	fseek(f, 0, SEEK_SET);

	return EXE_SUCCESS;
}

void print_exe_info(exe_info *exe) {

	std::cout << "\n" << "analysed:\n" << std::endl;

	/*
	 *
	 * Printing DOS Header:
	 *
	 */

	std::cout << "DOS Header Magic Number: 0x" << std::hex
			  << exe->e_magic << std::dec << std::endl;

	std::cout << "File address of new exe header: 0x" << std::hex
			  << exe->e_lfanew << std::dec << std::endl;

	std::cout << std::endl;
	
	/*		
	 *
	 * Printing COFF Header:
	 *
	 */

	std::cout << "COFF Header PE_Signature: 0x" << std::hex 
			  << exe->PE_Signature << std::dec << std::endl;

	std::cout << "Machine: ";
	if (exe_info::getMachineTypes().find(exe->Machine) !=
		exe_info::getMachineTypes().end()) {
		std::cout << exe_info::getMachineTypes().at(exe->Machine) << std::endl;
	} else {
		std::cout << "non classified 0x" << std::hex 
				  << exe->Machine << std::dec << std::endl;
	}

	std::cout << "Number of Sections: " 
			  << exe->NumberOfSections << std::endl;

	std::cout << "Timestamp: "
			  << epoch_to_human(exe->TimeDateStamp) << std::endl;

	std::cout << "Pointer to symbol table: 0x" << std::hex
			  << exe->PointerToSymbolTable << std::dec << std::endl;

	std::cout << "Number of Symbols: "
			  << exe->NumberOfSymbols << std::endl;

	std::cout << "Size of Optional Header: "
			  << exe->SizeOfOptionalHeader<< std::endl;
	
	std::cout << "Characteristics File Header: ";
	if (exe_info::getCFHTypes().find(exe->CharacteristicsFileHeader) !=
		exe_info::getCFHTypes().end()) {
    	std::cout << exe_info::getCFHTypes().at(exe->CharacteristicsFileHeader)
				  << std::endl;
	} else {
    	std::cout << "non classified 0x" << std::hex
				  << exe->CharacteristicsFileHeader << std::dec << std::endl;
	}

	std::cout << std::endl;

	/*
	 *
	 * Printing Optional Header:
	 *
	 */

	/*
	 * Standard COFF fields
	 */
	std::cout << "Optional Header Magic: 0x" << std::hex
			  << exe->Magic << std::dec << std::endl;

	std::cout << "Linker Version: "
			  << unsigned(exe->MajorLinkerVersion) << "." 
			  << unsigned(exe->MinorLinkerVersion) << std::endl;
	
	std::cout << "Size Of Code: "
			  << exe->SizeOfCode << std::endl;
	
	std::cout << "Size Of Initialized Data: "
			  << exe->SizeOfInitializedData << std::endl;

	std::cout << "Size Of Uninitialized Data: "
			  << exe->SizeOfUninitializedData << std::endl;

	std::cout << "Address Of Entry Point: 0x"
			  << std::hex << exe->AddressOfEntryPoint << std::endl;

	std::cout << "Base Of Code: 0x"
			  << exe->BaseOfCode << std::endl;

	/*
	 * Windows Specific fields
	 */
	std::cout << "Image Base: 0x"
			  << exe->ImageBase << std::dec << std::endl;
	
	std::cout << "Section Alignment: "
			  << exe->SectionAlignment << std::endl;
	
	std::cout << "File Alignment: "
			  << exe->FileAlignment << std::endl;
	
	std::cout << "Operating System Version: "
			  << exe->MajorOperatingSystemVersion << "."
			  << exe->MinorOperatingSystemVersion << std::endl;
	
	std::cout << "Image Version: "
			  << exe->MajorImageVersion << "."
			  << exe->MinorImageVersion << std::endl;
	
	std::cout << "Subsystem Version: "
			  << exe->MajorSubsystemVersion << "."
			  << exe->MinorSubsystemVersion << std::endl;
	
	std::cout << "Win32 Version Value: "
			  << exe->Win32VersionValue << std::endl;
	
	std::cout << "Size Of Image: "
			  << exe->SizeOfImage << std::endl;
	
	std::cout << "Size Of Headers: "
			  << exe->SizeOfHeaders << std::endl;
	
	std::cout << "Check Sum: 0x" << std::hex
			  << exe->CheckSum << std::dec << std::endl;

	std::cout << "Windows Subsystem: ";
	if (exe_info::getSubsystemTypes().find(exe->Subsystem) !=
		exe_info::getSubsystemTypes().end()) {
    	std::cout << exe_info::getSubsystemTypes().at(exe->Subsystem)
				  << std::endl;
	} else {
    	std::cout << "non classified 0x" << std::hex
				  << exe->Subsystem << std::dec << std::endl;
	}

	std::cout << "Dll Characteristics: ";
	if (exe_info::getDLLTypes().find(exe->DllCharacteristics) !=
		exe_info::getDLLTypes().end()) {
    	std::cout << exe_info::getDLLTypes().at(exe->DllCharacteristics)
				  << std::endl;
	} else {
    	std::cout << "non classified 0x" << std::hex
				  << exe->DllCharacteristics << std::dec << std::endl;
	}

	std::cout << "Size Of Stack Reserve: "
			  << exe->SizeOfStackReserve << std::endl;
	
	std::cout << "Size Of Stack Commit: "
			  << exe->SizeOfStackCommit << std::endl;
	
	std::cout << "Size Of Heap Reserve: "
			  << exe->SizeOfHeapReserve << std::endl;
	
	std::cout << "Size Of Heap Commit: "
			  << exe->SizeOfHeapCommit << std::endl;
	
	std::cout << "Loader Flags: 0x" << std::hex
			  << exe->LoaderFlags << std::dec << std::endl;
	
	std::cout << "Number Of RVA And Sizes: "
			  << exe->NumberOfRvaAndSizes << std::endl;
	
	std::cout << std::endl;

	/*
	 *
	 * Printing Section Header:
	 *
	 */
	
	for (int i = 0; i < exe->NumberOfSections; i++) {
		std::cout << "Section: "
				  << uint64_to_text(exe->Section[i].Name) << std::endl;

		std::cout << "Size of Raw Data: "
				  << exe->Section[i].SizeOfRawData << std::endl;

		std::cout << "Pointer to Raw Data: 0x"
				  << std::hex << exe->Section[i].PointerToRawData
				  << std::dec << std::endl;

		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

	FILE *f = fopen(argv[1], "rb");
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

	fclose(f);
	
	print_exe_info(&exe);

	return 0;
}