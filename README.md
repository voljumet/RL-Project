# RL-Project
Reinforcement Learning project using Axie-Infinity as inspiration for game engine and learning process


Requirements:

pybind11 libary (pip install pybind11)


compile lib on Mac 
```
clang -O3 -Wall -shared -undefined dynamic_lookup -std=c++17 -fPIC $(python3 -m pybind11 --includes) DeepAxie.cpp -o DeepAxie.so -target x86_64-apple-darwin-macho
```


compile on linux:
```
g++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) DeepAxie.cpp -o DeepAxieLinux.so
```


windows might want to use "g++" or "gcc" instead of "clang"



Compiling lib for other OS, check "Target Triple" here: https://clang.llvm.org/docs/CrossCompilation.html