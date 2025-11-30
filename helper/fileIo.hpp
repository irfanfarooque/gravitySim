#pragma once
#include <fstream>
inline char *loadFileToHeap(const char *filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file)
    return nullptr;

  // Get file size
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  // Allocate memory (Size + 1 for the null terminator \0)
  char *buffer = new char[size + 1];

  // Read file
  if (file.read(buffer, size)) {
    buffer[size] = '\0'; // Manually null-terminate!
    return buffer;
  }

  delete[] buffer; // Cleanup on read failure
  return nullptr;
}
