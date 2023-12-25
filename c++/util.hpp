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

template <typename T = int32_t>
T readSInt(const std::string& input, size_t& pos) {
    char c = input[pos++];
    T val = 0;

    if (c == '-') {
        while (isDigit(c = input[pos++])) {
            val = val * 10 + (c & 0xF);
        }
        return -val;
    }
    val = c & 0xF;
    while (isDigit(c = input[pos++])) {
        val = val * 10 + (c & 0xF);
    }
    return val;
}

template <typename T = uint32_t>
T readUInt(const std::string& input, size_t& pos) {
    T val = input[pos++] & 0xF;
    char c;
    while (isDigit(c = input[pos++])) {
        val = val * 10 + (c & 0xF);
    }
    return val;
}

// reads an integer with a maximum of 4 digits
uint32_t readUInt4(const std::string& input, size_t& pos) {
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

auto check_len(__m128i chunk) {
    const auto check_high = _mm_cmpgt_epi8(chunk, _mm_set1_epi8('9'));
    const auto check_low = _mm_cmpgt_epi8(_mm_set1_epi8('0'), chunk);

    chunk = _mm_or_si128(check_high, check_low);
    const auto res = _mm_movemask_epi8(chunk);
    return _tzcnt_u32(res);
}

uint64_t readUInt128(const char* input, size_t& pos) {
    auto chunk = _mm_loadu_si128((__m128i*)(input + pos));
    const auto len = check_len(chunk);
    pos += len + 1;

    chunk = _mm_and_si128(chunk, _mm_set1_epi8(0xF));

    switch (len) {
        case 0: return 0;
        case 1: return _mm_cvtsi128_si32(chunk) & 0xFF;
        case 2: chunk = _mm_bslli_si128(chunk, 14); break;
        case 3: chunk = _mm_bslli_si128(chunk, 13); break; 
        case 4: chunk = _mm_bslli_si128(chunk, 12); break;
        case 5: chunk = _mm_bslli_si128(chunk, 11); break;
        case 6: chunk = _mm_bslli_si128(chunk, 10); break;
        case 7: chunk = _mm_bslli_si128(chunk, 9); break;
        case 8: chunk = _mm_bslli_si128(chunk, 8); break;
        case 9: chunk = _mm_bslli_si128(chunk, 7); break;
        case 10: chunk = _mm_bslli_si128(chunk, 6); break;
        case 11: chunk = _mm_bslli_si128(chunk, 5); break;
        case 12: chunk = _mm_bslli_si128(chunk, 4); break;
        case 13: chunk = _mm_bslli_si128(chunk, 3); break;
        case 14: chunk = _mm_bslli_si128(chunk, 2); break;
        case 15: chunk = _mm_bslli_si128(chunk, 1); break;
    };

    // combine numbers [ 0x0038 | 0x0022 | 0x000c | 0x005a | 0x004e | 0x0038 | 0x0022 | 0x000c ( 56 | 34 | 12 | 90 | 78 | 56 | 34 | 12 ) ]
    chunk = _mm_maddubs_epi16(chunk, _mm_set_epi8(1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10));

    // combine again   [ 0x0000 | 0x0d80 | 0x0000 | 0x2334 | 0x0000 | 0x162e | 0x0000 | 0x04d2 ( 0 | 3456 | 0 | 9012 | 0 | 5678 | 0 | 1234) ]
    chunk = _mm_madd_epi16(chunk, _mm_set_epi16(1, 100, 1, 100, 1, 100, 1, 100));
    // remove extra bytes [ (64 bits, same as the right ) | 0x0d80 | 0x2334 | 0x162e | 0x04d2 ( 3456 | 9012 | 5678 | 1234) ]
    chunk = _mm_packus_epi32(chunk, chunk);

    // combine again [ (64 bits, zeroes) | 0x055f2cc0 | 0x00bc614e ( 90123456 | 12345678 ) ]
    chunk = _mm_madd_epi16(chunk, _mm_set_epi16(0, 0, 0, 0, 1, 10000, 1, 10000));

    const auto a = _mm_cvtsi128_si64(chunk);
    return ((a & 0xffffffff) * 100000000) + (a >> 32);
}

uint64_t readUInt128(const std::string& input, size_t& pos) {
    return readUInt128(input.data(), pos);
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
