#include <iostream>
#include <cstdint>
#include <cstdio>

class exe_info {
  public:
    uint64_t DOS_Header;
    uint64_t DOS_Stub;

    // COFF Header
    uint32_t Signature;
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics1;

    // Standard COFF Fields
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;

    // Windows Specific Fields
    uint32_t BaseOfData;
    uint32_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;

    // Data Directories
    uint64_t ExportTable;
    uint64_t ImportTable;
    uint64_t ResourceTable;
    uint64_t ExceptionTable;
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
    // uint64_t Reserved; must be zero

    // Section Table
    uint64_t Name;
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics2;
};

const int EXE_SUCCESS = 0;
const int READ_ERROR = -1;
const int NOT_EXE = -10;
const int EXE_UNSUPPORTED = -11;

int read_exe_info (exe_info *exe, FILE *f) {
  fseek(f, 0, SEEK_SET);
  int res;

  uint16_t magic_signature;
  res = fread(&magic_signature, sizeof(magic_signature), 1, f);
  if (res != 1)
    return READ_ERROR;
  if (magic_signature != 0x5A4D)
    return NOT_EXE;
  
  uint64_t DOS_Header;
  res = fread(&DOS_Header, sizeof(DOS_Header), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->DOS_Header = DOS_Header;

  uint64_t DOS_Stub;
  res = fread(&DOS_Stub, sizeof(DOS_Stub), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->DOS_Stub = DOS_Stub;

  uint32_t Signature;
  res = fread(&Signature, sizeof(Signature), 1, f);
  if (res != 1)
    return READ_ERROR;
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
  
  uint16_t Characteristics1;
  res = fread(&Characteristics1, sizeof(Characteristics1), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Characteristics1 = Characteristics1;
  
  uint16_t Magic;
  res = fread(&Magic, sizeof(Magic), 1, f);
  if (res != 1)
    return READ_ERROR;
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

  uint64_t ExportTable;
  res = fread(&ExportTable, sizeof(ExportTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->ExportTable = ExportTable;

  uint64_t ImportTable;
  res = fread(&ImportTable, sizeof(ImportTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->ImportTable = ImportTable;

  uint64_t ResourceTable;
  res = fread(&ResourceTable, sizeof(ResourceTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->ResourceTable = ResourceTable;

  uint64_t ExceptionTable;
  res = fread(&ExceptionTable, sizeof(ExceptionTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->ExceptionTable = ExceptionTable;

  uint64_t CertificateTable;
  res = fread(&CertificateTable, sizeof(CertificateTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->CertificateTable = CertificateTable;

  uint64_t BaseRelocationTable;
  res = fread(&BaseRelocationTable, sizeof(BaseRelocationTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->BaseRelocationTable = BaseRelocationTable;

  uint64_t Debug;
  res = fread(&Debug, sizeof(Debug), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Debug = Debug;

  uint64_t Architecture;
  res = fread(&Architecture, sizeof(Architecture), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Architecture = Architecture;

  uint64_t GlobalPtr;
  res = fread(&GlobalPtr, sizeof(GlobalPtr), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->GlobalPtr = GlobalPtr;

  uint64_t TLSTable;
  res = fread(&TLSTable, sizeof(TLSTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->TLSTable = TLSTable;

  uint64_t LoadConfigTable;
  res = fread(&LoadConfigTable, sizeof(LoadConfigTable), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->LoadConfigTable = LoadConfigTable;

  uint64_t BoundImport;
  res = fread(&BoundImport, sizeof(BoundImport), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->BoundImport = BoundImport;

  uint64_t IAT;
  res = fread(&IAT, sizeof(IAT), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->IAT = IAT;

  uint64_t DelayImportDescriptor;
  res = fread(&DelayImportDescriptor, sizeof(DelayImportDescriptor), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->DelayImportDescriptor = DelayImportDescriptor;

  uint64_t CLRRuntimeHeader;
  res = fread(&CLRRuntimeHeader, sizeof(CLRRuntimeHeader), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->CLRRuntimeHeader = CLRRuntimeHeader;

  uint64_t Name;
  res = fread(&Name, sizeof(Name), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Name = Name;

  uint32_t VirtualSize;
  res = fread(&VirtualSize, sizeof(VirtualSize), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->VirtualSize = VirtualSize;

  uint32_t VirtualAddress;
  res = fread(&VirtualAddress, sizeof(VirtualAddress), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->VirtualAddress = VirtualAddress;

  uint32_t SizeOfRawData;
  res = fread(&SizeOfRawData, sizeof(SizeOfRawData), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->SizeOfRawData = SizeOfRawData;

  uint32_t PointerToRawData;
  res = fread(&PointerToRawData, sizeof(PointerToRawData), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->PointerToRawData = PointerToRawData;

  uint32_t PointerToRelocations;
  res = fread(&PointerToRelocations, sizeof(PointerToRelocations), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->PointerToRelocations = PointerToRelocations;

  uint32_t PointerToLinenumbers;
  res = fread(&PointerToLinenumbers, sizeof(PointerToLinenumbers), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->PointerToLinenumbers = PointerToLinenumbers;

  uint16_t NumberOfRelocations;
  res = fread(&NumberOfRelocations, sizeof(NumberOfRelocations), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->NumberOfRelocations = NumberOfRelocations;

  uint16_t NumberOfLinenumbers;
  res = fread(&NumberOfLinenumbers, sizeof(NumberOfLinenumbers), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->NumberOfLinenumbers = NumberOfLinenumbers;

  uint32_t Characteristics2;
  res = fread(&Characteristics2, sizeof(Characteristics2), 1, f);
  if (res != 1)
    return READ_ERROR;
  exe->Characteristics2 = Characteristics2;

  return EXE_SUCCESS;
}

int print_exe_info(exe_info *exe) {

  return EXE_SUCCESS;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Need an image!" << std::endl;
		std::cout << argv[0] << " <image name>" << std::endl;
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
		std::cout << "error reading pcx file: " << ret << std::endl;
		return -1;
	}

	print_exe_info(&exe);

	fclose(f);
	return 0;
}