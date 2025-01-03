#include "../src/include/pinyinime.h"
#include <codecvt>
#include <chrono>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <cstring>

std::string fromUtf16(const ime_pinyin::char16 *buf, size_t len) {
    std::u16string utf16Str(reinterpret_cast<const char16_t *>(buf), len);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(utf16Str);
}

void test_pinyin_search_and_segment(const std::string &user_pinyin) {
    auto start_time = std::chrono::high_resolution_clock::now();  // 开始计时

    std::string pinyin_str = user_pinyin;

    const char *pinyin = pinyin_str.c_str();
    size_t cand_cnt = ime_pinyin::im_search(pinyin, strlen(pinyin));
    const ime_pinyin::uint16 *spl_start = nullptr;
    size_t segment_count = ime_pinyin::im_get_spl_start_pos(spl_start);

    if (spl_start != nullptr && segment_count > 0) {
        std::string segmented_pinyin;
        for (size_t i = 0; i < segment_count; ++i) {
            size_t start = spl_start[i];
            size_t end = spl_start[i + 1];
            std::string segment(pinyin + start, end - start);
            segmented_pinyin += segment;
            if (i < segment_count - 1) {
                segmented_pinyin += "'";  // 在分段之间添加分词符
            }
        }
        std::cout << "拼音分词：" << segmented_pinyin << "\n";
    } else {
        std::cout << "Failed to get segments or no segments found!\n";
    }

    std::string msg;
    std::vector<std::string> candidateList;
    for (size_t i = 0; i < cand_cnt; ++i) {
        ime_pinyin::char16 buf[256] = {0};
        ime_pinyin::im_get_candidate(i, buf, 255);
        size_t len = 0;
        while (buf[len] != 0 && len < 255) ++len;
        msg.append(fromUtf16(buf, len) + " ");
        candidateList.push_back(fromUtf16(buf, len));
    }

    std::cout << "候选项数量: " << cand_cnt << std::endl;
    std::cout << "候选项本体: " << msg << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();  // 结束计时
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "函数执行时间: " << duration.count() << " 微秒\n";
}

int main() {
    ime_pinyin::im_set_max_lens(64, 32);
    if (!ime_pinyin::im_open_decoder("./data/dict_pinyin.dat", "./data/user_dict.dat")) {
        std::cout << "fany bug.\n";
        return 0;
    }
    test_pinyin_search_and_segment("qusiba");
    test_pinyin_search_and_segment("shuoshenmene");
    test_pinyin_search_and_segment("yiwushichushima");
    test_pinyin_search_and_segment("zhonghuarenmingongheguo");
    test_pinyin_search_and_segment("meilijianhezhongguo");
    test_pinyin_search_and_segment("qunimadegouridequsibawonengzenmeban");
    test_pinyin_search_and_segment("kanbuchulaishizenmexianzhichangdude");
    test_pinyin_search_and_segment("ninininininininininininininininini");
    return 0;
}