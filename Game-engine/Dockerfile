FROM base:latest

RUN mkdir /Game-engine
WORKDIR /Game-engine
COPY . /Game-engine

RUN g++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) DeepAxie.cpp -o DeepAxieLinux.so
RUN python3 DQN.py