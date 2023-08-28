/*
 * Program changes Timestamp of Portable Executable 64 bit .exe files
 */

#include <iostream>

int patch(FILE *f) {
    const int PATCH_SUCCESS = 0;
    const int PATCH_ERROR = -1;
    const int READ_ERROR = -2;
    const int NewDate = 1005426000; // epoch of 11.11.2001

    uint32_t e_lfanew;
    int res;

    fseek(f, 60, SEEK_SET); // Seek to the position of e_lfanew
	res = fread(&e_lfanew, sizeof(e_lfanew), 1, f);
	if (res != 1) return READ_ERROR;
    
    fseek(f, e_lfanew + 8, SEEK_SET); // Seek to the position of Timestamp
    res = fwrite(&NewDate, sizeof(NewDate), 1, f);
    if (res != 1) return PATCH_ERROR;

    return PATCH_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
		std::cout << "Need an exe file!" << std::endl;
		std::cout << argv[0] << " <file name>" << std::endl;
		return -1;
	}

	FILE *f = fopen(argv[1], "rb+");
	if (f == NULL) {
		std::cout << "Error openning file" << std::endl;
		return -1;
	}

    int ret;
    ret = patch(f);
    if (ret != 0) {
		std::cout << "error patching exe file: " << ret << std::endl;
		fclose(f);
		return -1;
	}

    fclose(f);

    return 0;
}