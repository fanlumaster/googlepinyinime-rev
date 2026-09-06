#include "pinyinime.h"
#include <cstdio>
#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) return 2;
    std::remove(argv[2]);
    if (!ime_pinyin::im_open_decoder(argv[1], argv[2])) {
        std::cerr << "Cannot open decoder dictionary\n";
        return 1;
    }
    int status = 0;
    for (const char* input : {"nihao", "zhongguo", "shurufa"}) {
        ime_pinyin::im_reset_search();
        const auto count = ime_pinyin::im_search(input, std::strlen(input));
        ime_pinyin::char16 candidate[256] = {};
        if (!count || !ime_pinyin::im_get_candidate(0, candidate, 256) || !candidate[0]) {
            std::cerr << "No candidate for " << input << '\n';
            status = 1;
        }
    }
    ime_pinyin::im_close_decoder();
    std::remove(argv[2]);
    return status;
}
