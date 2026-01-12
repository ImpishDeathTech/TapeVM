import os

for item in os.listdir('source'):
  if item.endswith(".cpp"):
    os.system(f"g++ -std=c++17 -fpic -I./include -c source/{item} -o build/{item}.o -DTAPE_EXPORTS")

for item in os.listdir(f'source/TapeVM'):
  if item.endswith(".cpp"):
    os.system(f"g++ -std=c++17 -fpic -I./include -c source/TapeVM/{item} -o build/{item}.o -DTAPE_EXPORTS")

for item in os.listdir(f'source/TapeVM/InputStream'):
  if (item.endswith('.cpp')):
    os.system(f"g++ -std=c++17 -fpic -I./include -c source/TapeVM/InputStream/{item} -o build/{item}.o -DTAPE_EXPORTS")

for item in os.listdir(f'source/TapeVM/OutputStream'):
  if (item.endswith('.cpp')):
    os.system(f"g++ -std=c++17 -fpic -I./include -c source/TapeVM/OutputStream/{item} -o build/{item}.o -DTAPE_EXPORTS")

for item in os.listdir(f'source/TapeVM/Base'):
  if (item.endswith('.cpp')):
    os.system(f"g++ -std=c++17 -fpic -I./include -c source/TapeVM/Base/{item} -o build/{item}.o -DTAPE_EXPORTS")

os.system(f"g++ -std=c++17 -shared -I./include -L./bin -o bin/tapevm.dll ./build/*.cpp.o")
os.system(f"g++ -std=c++17 -I./include -L./bin -o bin/tapevm.exe Main.cpp -ltapevm")