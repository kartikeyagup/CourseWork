all: hashing.cpp Test.cpp HashTable.cpp HashTest.cpp 
	g++ hashing.cpp Test.cpp HashTable.cpp WordCompression.cpp WordDecompression.cpp HashTest.cpp

compress: hashing.cpp HashTable.cpp WordCompression.cpp WordDecompression.cpp Compression.cpp
	g++ hashing.cpp HashTable.cpp WordCompression.cpp WordDecompression.cpp Compression.cpp

decompress:
	g++ WordDecompression.cpp Decompression.cpp

clean:
	rm a.out

