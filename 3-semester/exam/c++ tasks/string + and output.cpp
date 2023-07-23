#include <iostream>

// https://codereview.stackexchange.com/questions/98329/stdstring-implementation

class String {
	public:
    String() :
      data(nullptr),
      size(0)
    { }


    String(const char *str) {
      if(str) {
        int isize = strlen(str) + 1;
        data = new char[isize];
        memset(data, 0, isize);
        size = isize;
        memcpy(data, str, strlen(str));
      }
    }

		~String() {
      if (data)
        delete[] data;
    }

		char* data;
    int size;
};

std::ostream& operator<<(std::ostream& out, const String& str) {
  for(int i = 0; i < str.size; i++ )
    out << str[i];
  return out;
}

int main() {
  char grade = 'A';
  String a;
  std::cout << a << std::endl; 

  return 0;
}