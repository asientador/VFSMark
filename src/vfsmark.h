#define pathname "test.txt"
#define pathnameInput "bible.txt"
#define blockSize 1024 

enum modes{
  r_sequential = 1 ,
  r_block = 2
};
void createFilesWithSize(int numberFiles, int size);
void createFileWithSize(int size);
double g_readFromFile(int numFiles, int mode);
void writeFiles(int numberFiles, int bytesToWriteOn);
