FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    qt6-base-dev \
    qt6-declarative-dev \
    libgl1-mesa-dev \
    libxkbcommon-dev \
    libvulkan-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/client
COPY . .
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF
RUN cmake --build build --parallel
CMD ["./build/client"]
