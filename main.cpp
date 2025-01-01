#include "./pinyinime.h"
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

std::string fromUtf16(const ime_pinyin::char16 *buf, size_t len) {
    // 转换为标准 char16_t
    std::u16string utf16Str(reinterpret_cast<const char16_t *>(buf), len);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(utf16Str);
}

int main() {
    if (!ime_pinyin::im_open_decoder("./dict_pinyin.dat", "./user_dict.dat")) {
        std::cout << "fany bug.\n";
        return 0;
    }

    std::string pinyin = "ni'ma'si'le";
    pinyin = "ni'ma'mei'si";
    pinyin = "huang'yi";
    size_t qty = ime_pinyin::im_search(pinyin.c_str(), pinyin.size());
    ime_pinyin::char16 buf[256] = {0};
    std::string msg;
    for (size_t i = 0; i < 100; ++i) {
        ime_pinyin::im_get_candidate(i, buf, 255);
        size_t len = 0;
        while (buf[len] != 0 && len < 255) ++len;
        msg.append(fromUtf16(buf, len) + " ");
    }
    std::cout << "候选项: " << msg << std::endl;
    return 0;
}
