#include <bitset>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

std::ostream &operator<<(std::ostream &os, std::byte b) {
  return os << std::bitset<8>(std::to_integer<int>(b));
}

class Bytes {
public:
  Bytes(char *var);
  byte *Encode();
  char *Decode();

private:
  byte data[256];
  char *Array = new char[255];
  char *Array_ = new char[255];
  enum { ID_int = 1, ID_float = 2, ID_char = 3, ID_string = 4 };
};

Bytes::Bytes(char *var) { Array = var; }

byte *Bytes::Encode() {
  data[0] = byte{ID_char};
  data[1] = byte{(unsigned char)strlen(Array)};
  data[strlen(Array) + 2] = byte{(unsigned char)'\0'};
  memcpy(data + 2, Array, strlen(Array));
  return data;
}

char *Bytes::Decode() {
  for (size_t i = 2; i < strlen(Array) + 2; i++) {
    Array_[i - 2] = (char)data[i];
  }
  return Array_;
}

int main() {
  char a[] = "aaa";
  Bytes b(a);
  for (int i = 0; i < strlen(a) + 3; i++) {
    cout << b.Encode()[i] << endl;
  }
  for (int i = 0; i < strlen(a); i++) {
    cout << b.Decode()[i] << endl;
  }
  return 0;
}
