# RL-Project
Reinforcement Learning project using Axie-Infinity as inspiration for game engine and learning process


compile lib on Mac 
```
clang -O3 -Wall -shared -undefined dynamic_lookup -std=c++17 -fPIC $(python3 -m pybind11 --includes) juice.cpp -o libjuice.so -target x86_64-apple-darwin-macho
```
(requires pybind11: pip install pybind11)

windows and linux might want to use "g++" instead of "clang"


compiling lib for other OS, check "Target Triple" here: https://clang.llvm.org/docs/CrossCompilation.html