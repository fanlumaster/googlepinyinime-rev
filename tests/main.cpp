#include "../src/include/pinyinime.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <utf8cpp/utf8.h>
#include <Windows.h>

std::string fromUtf16(const ime_pinyin::char16 *buf, size_t len) {
    const char16_t *utf16Data = reinterpret_cast<const char16_t *>(buf);
    std::u16string utf16Str(utf16Data, len);

    std::string utf8Result;
    utf8::utf16to8(utf16Str.begin(), utf16Str.end(), std::back_inserter(utf8Result));

    return utf8Result;
}

void test_pinyin_search_and_segment(const std::string &user_pinyin) {
    auto start_time = std::chrono::high_resolution_clock::now();

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
                segmented_pinyin += "'";
            }
        }
        std::cout << "Pinyin segmented：" << segmented_pinyin << "\n";
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

    std::cout << "Count of candidates: " << cand_cnt << std::endl;
    std::cout << "Candidates: " << msg << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Time used: " << duration.count() << " us\n";
    std::cout << "========================================" << std::endl;
}

void test_pinyin_search_when_retriving_first_element(const std::string &user_pinyin) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::string pinyin_str = user_pinyin;

    const char *pinyin = pinyin_str.c_str();
    size_t cand_cnt = ime_pinyin::im_search(pinyin, strlen(pinyin));
    std::string msg;
    std::vector<std::string> candidateList;
    cand_cnt = cand_cnt > 1 ? 1 : cand_cnt;
    for (size_t i = 0; i < cand_cnt; ++i) {
        ime_pinyin::char16 buf[256] = {0};
        ime_pinyin::im_get_candidate(i, buf, 255);
        size_t len = 0;
        while (buf[len] != 0 && len < 255) ++len;
        msg.append(fromUtf16(buf, len) + " ");
        candidateList.push_back(fromUtf16(buf, len));
    }

    std::cout << "Count of candidates: " << cand_cnt << std::endl;
    std::cout << "Candidates: " << msg << std::endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Time used: " << duration.count() << " us\n";
    std::cout << "========================================" << std::endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
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
    test_pinyin_search_and_segment("jingjiandao");
    test_pinyin_search_and_segment("zhen'ta'ma'an'jing");
    test_pinyin_search_and_segment("zhen'ta'ma'an'jing");
    test_pinyin_search_and_segment("ni'shuo'ni'ma'ne");
    test_pinyin_search_when_retriving_first_element("qunimadegouridequsibawonengzenmeban");
    test_pinyin_search_when_retriving_first_element("zh'ta'ma'an'jing");
    test_pinyin_search_when_retriving_first_element("ni'shuo'ne'ma'de");
    test_pinyin_search_when_retriving_first_element("wei'ni'qian'gua'bu'bian");
    test_pinyin_search_when_retriving_first_element("wo'lai'kan'kan'zhe'ge'zui'duo'neng'shu'ru'duo'shao'ge'zi'kan'shang'qu'shi'bi'jiao'he'li'de");
    return 0;
}