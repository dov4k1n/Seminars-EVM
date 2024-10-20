/*
 * Program changes Timestamp of Portable Executable 64 bit .exe file
 * to Sun 11.11.2001 00:00:00. If wanted, could be changed to any date
 * the user wants.
 * 
 * To read and print .exe file's binary data I use my 
 * ../01-file-processing-in-binary-mode/view_exePE32+_file.cpp program.
 */

#include <iostream>

/*
 * Function takes file in binary mode as input,
 * seeks to the fixed position in DOS Header called "e_lfanew".
 * "e_lfanew" contains adress to the beginning of COFF Header
 * (also called FIle Header) which is not fixed.
 * 
 * From the beginning of COFF Header function seeks 8 bytes more to
 * the Timestamp (its position is fixed relatively to the COFF Header).
 * 
 * And overwrites Timestamp with the NewDate.
 */
int patch(FILE *f) {
    const int PATCH_SUCCESS = 0;
    const int PATCH_ERROR = -1;
    const int READ_ERROR = -2;
    const int NewDate = 1005426000; // epoch of 11.11.2001 00:00:00

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

/*
 * Main function takes as an argument name of the file that is
 * needed to be patched. Example of use after compilation
 * ".\a.exe target_file.exe".
 * 
 * In my example, I compile "g++ victim.cpp -o victim",
 * then compile "g++ view_exePE32+_file.cpp -o print", 
 * then type ".\print.exe victim.exe",
 * it prints all the data from "victim.exe".
 * 
 * Then I compile "g++ change_timestamp.cpp -o patch", 
 * type ".\patch.exe victim.exe"
 * and ".\print.exe victim.exe".
 * 
 * Before the patch, typing ".\print.exe victim.exe" prints data with
 * Timestamp = date_of_compilation of victim.exe.
 * After the patch, typing ".\print.exe victim.exe" prints data with
 * Timestamp = "Sun 11.11.2001 00:00:00".
 * 
 * "victim.cpp" file itself does not change.
 */
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

    std::cout << "Timestamp changed" << std::endl;

    fclose(f);

    return 0;
}