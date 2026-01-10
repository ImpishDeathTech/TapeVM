g++ -std=c++17 -fpic -I./include -c source/TapeVM/InputStream/StringInputSource.cpp -o build/StringInputSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/InputStream/FileInputSource.cpp -o build/FileInputSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/InputStream/StdinSource.cpp -o build/StdinSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/InputStream.cpp -o build/InputStream.cpp.o -DTAPE_EXPORTS

g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream/FileOutputSource.cpp -o build/FileOutputSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream/StringOutputSource.cpp -o build/StringOutputSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream/StdoutSource.cpp -o build/StdoutSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream/StderrSource.cpp -o build/StderrSource.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream.cpp -o build/OutputStream.cpp.o -DTAPE_EXPORTS

g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/CompilerPrimitives.cpp -o build/CompilerPrimitives.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/ControlStructures.cpp -o build/ControlStructures.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/ParsingWords.cpp -o build/ParsingWords.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/StackOperators.cpp -o build/StackOperators.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/StdIO.cpp -o build/StdIO.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/Variables.cpp -o build/Variables.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base.cpp -o build/Base.cpp.o -DTAPE_EXPORTS

g++ -std=c++17 -fpic -I./include -c source/TapeVM.cpp -o build/TapeVM.cpp.o -DTAPE_EXPORTS
g++ -std=c++17 -shared -L./library -o library/tapevm.dll build/*.cpp.o