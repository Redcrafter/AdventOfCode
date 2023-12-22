#pragma once
#include <immintrin.h>

#include <bit>
#include <fstream>
#include <span>
#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#define always__inline __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define always__inline __forceinline inline
#else
#define always__inline
#endif

std::string readFile(const char* path) {
    std::ifstream file(path);
    std::string res((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));
    return res;
}

std::vector<std::string> readLines(const char* path, bool skipEmpty = true) {
    std::ifstream file(path);
    std::vector<std::string> res;
    std::string line;

    while (file) {
        std::getline(file, line);
        if (skipEmpty && line.empty()) continue;
        res.push_back(line);
    }
    // TODO: somehow fails if no empty last line

    return res;
}

std::vector<std::string> split(const std::string& str, const char c) {
    std::vector<std::string> res;

    int start = 0;
    int pos = 0;

    while (pos < str.size()) {
        if (str[pos] == c) {
            res.push_back(str.substr(start, pos - start));
            start = pos + 1;
        }
        pos++;
    }
    res.push_back(str.substr(start, str.size() - start));

    return res;
}

bool inline isDigit(char c) {
    return c >= '0' && c <= '9';
}

auto findChar(const char* str, char c) {
    const auto cmp_val = _mm256_set1_epi8(c);

    for (size_t i = 0;; i += 32) {
        auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)(str + i)), cmp_val));
        if (mask != 0) {
            return i + std::countr_zero((uint32_t)mask);
        }
    }
}

template <typename T>
bool contains(const std::span<const T> arr, T search) {
    bool ok = false;
    for (auto& i : arr) {
        ok |= i == search;
    }
    return ok;
}

template <typename T>
bool contains(const T* ptr, int start, int end, T search) {
    bool ok = false;
    for (size_t i = start; i < end; i++) {
        ok |= ptr[i] == search;
    }
    return ok;
}

template <typename T = uint32_t>
T readInt(const std::string& input, size_t& pos) {
    T val = input[pos++] & 0xF;
    char c;
    while (isDigit(c = input[pos++])) {
        val = val * 10 + (c & 0xF);
    }
    return val;
}

// reads an integer with a maximum of 4 digits
uint32_t readInt4(const std::string& input, size_t& pos) {
    uint32_t val = *(uint32_t*)(input.data() + pos);

    if (!isDigit(val >> 8)) {
        pos += 2;
        return (val & 0xF);
    }
    if (!isDigit(val >> 16)) {
        pos += 3;
        return (val & 0xF) * 10 + ((val >> 8) & 0xF);
    }
    if (!isDigit(val >> 24)) {
        pos += 4;
        return (val & 0xF) * 100 + ((val >> 8) & 0xF) * 10 + ((val >> 16) & 0xF);
    }
    pos += 5;
    return (val & 0xF) * 1000 + ((val >> 8) & 0xF) * 100 + ((val >> 16) & 0xF) * 10 + ((val >> 24) & 0xF);
}

constexpr auto makeHexLookup() {
    std::array<uint8_t, 256> data;
    data.fill(0);
    for (auto i = '0'; i <= '9'; i++) {
        data[i] = i - '0';
    }
    for (auto i = 'a'; i <= 'f'; i++) {
        data[i] = i - 'a' + 10;
    }
    return data;
}
const auto hexLookup = makeHexLookup();

uint8_t hextoint(char x) {
    return hexLookup[x];
}
