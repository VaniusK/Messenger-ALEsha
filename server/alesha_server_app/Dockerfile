# Multi-stage build for messenger server

# Build stage
FROM drogonframework/drogon AS builder

WORKDIR /app
COPY . .

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF
RUN cmake --build build --parallel

# Runtime stage
FROM drogonframework/drogon

WORKDIR /app

# Copy executable
COPY --from=builder /app/build/alesha_server_app .

# Copy config files if needed
COPY --from=builder /app/config.json ./config.json
COPY --from=builder /app/config.yaml ./config.yaml

# Copy static files
COPY --from=builder /app/index.html ./index.html

EXPOSE 5555

CMD ["./alesha_server_app"]
