#include <emmintrin.h>
#include <immintrin.h>

#include <cstdint>
#include <string>

auto check_len(__m128i chunk) {
    const auto cmp_max = _mm_set1_epi8('9');
    const auto cmp_min = _mm_set1_epi8('0');
    const auto check_high = _mm_cmpgt_epi8(chunk, cmp_max);
    const auto check_low = _mm_cmpgt_epi8(cmp_min, chunk);

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
