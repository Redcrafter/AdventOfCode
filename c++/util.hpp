#pragma once
#include <immintrin.h>

#include <span>
#include <string_view>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#define always__inline __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define always__inline __forceinline inline
#else
#define always__inline
#endif

template<typename T = std::string_view>
std::vector<T> split(T str, const char c) {
    std::vector<T> res;

    int start = 0;
    int pos = 0;

    while(pos < str.size()) {
        if(str[pos] == c) {
            res.push_back(str.substr(start, pos - start));
            start = pos + 1;
        }
        pos++;
    }
    res.push_back(str.substr(start, str.size() - start));

    return res;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// assumes there is exactly one number per line
template<typename T, bool readNegative = false>
auto extractNumbers(std::string_view str) {
    std::vector<T> res;

    size_t i = 0;
    while(i < str.size()) {
        char c = str[i++];

        if(readNegative && c == '-') {
            if(i < str.size() && isDigit(c = str[i])) {
                i++;

                T n = c & 0xF;
                while(i < str.size()) {
                    c = str[i++];
                    if(!isDigit(c)) {
                        i--;
                        break;
                    }
                    n = (n * 10) + (c & 0xF);
                }
                res.push_back(-n);
            }
            continue;
        }

        if(isDigit(c)) {
            T n = c & 0xF;
            while(i < str.size()) {
                c = str[i++];
                if(!isDigit(c)) {
                    i--;
                    break;
                }
                n = (n * 10) + (c & 0xF);
            }
            res.push_back(n);
        }
    }
    return res;
}

auto findChar(const char* str, char c) {
    const auto cmp_val = _mm256_set1_epi8(c);

    for(size_t i = 0;; i += 32) {
        auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)(str + i)), cmp_val));
        if(mask != 0) {
            return i + std::countr_zero((uint32_t)mask);
        }
    }
}

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    char value[N];
};

template<StringLiteral val>
bool stringMatch(std::string_view str, size_t& pos) {
    for(size_t i = 0; i < sizeof(val) - 1; i++) {
        if(str[pos + i] != val.value[i]) return false;
    }

    pos += sizeof(val) - 1;
    return true;
}

template<typename T>
bool contains(const std::span<const T> arr, T search) {
    bool ok = false;
    for(auto& i : arr) {
        ok |= i == search;
    }
    return ok;
}

template<typename T>
bool contains(const T* ptr, int start, int end, T search) {
    bool ok = false;
    for(size_t i = start; i < end; i++) {
        ok |= ptr[i] == search;
    }
    return ok;
}

template<typename T = int32_t>
T readSInt(std::string_view input, size_t& pos) {
    char c = input[pos++];
    T val = 0;

    if(c == '-') {
        while(isDigit(c = input[pos++])) {
            val = val * 10 + (c & 0xF);
        }
        return -val;
    }
    val = c & 0xF;
    while(isDigit(c = input[pos++])) {
        val = val * 10 + (c & 0xF);
    }
    return val;
}

template<typename T = uint32_t>
T parseInt(std::string_view str) {
    T val = 0;
    if(str[0] == '-') {
        for(auto c : str.substr(1)) {
            val = val * 10 + (c & 0xF);
        }
        return -val;
    } else {
        for(auto c : str) {
            val = val * 10 + (c & 0xF);
        }
        return val;
    }
}

template<typename T = uint32_t>
T readUInt(std::string_view input, size_t& pos) {
    T val = input[pos++] & 0xF;
    char c;
    while(isDigit(c = input[pos++])) {
        val = val * 10 + (c & 0xF);
    }
    return val;
}

// reads an integer with a maximum of 4 digits
uint32_t readUInt4(std::string_view input, size_t& pos) {
    uint32_t val = *(uint32_t*)(input.data() + pos);

    if(!isDigit(val >> 8)) {
        pos += 2;
        return (val & 0xF);
    }
    if(!isDigit(val >> 16)) {
        pos += 3;
        return (val & 0xF) * 10 + ((val >> 8) & 0xF);
    }
    if(!isDigit(val >> 24)) {
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

    switch(len) {
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

uint64_t readUInt128(std::string_view input, size_t& pos) {
    return readUInt128(input.data(), pos);
}

template<typename T, int length>
auto readExactInt(std::string_view str, size_t index) {
    T res = 0;
    for(int i = 0; i < length; i++) {
        res = res * 10 + (str[index + i] & 0xF);
    }
    return res;
}
