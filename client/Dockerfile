FROM ubuntu
RUN apt-get update && apt-get install -y clang++-15 build-essential
WORKDIR /usr/src/client
COPY . .
RUN clang++-15 -o main test_docker.cpp
CMD ["./main"]