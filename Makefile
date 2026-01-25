CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra


format:
	find server client common -path "*/build/*" -prune -o \( -name "*.hpp" -o -name "*.cpp" \) -print 2>/dev/null | xargs -r clang-format-15 -i