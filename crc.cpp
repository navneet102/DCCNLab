#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

uint16_t calculate_crc12(const std::string& data) {
    uint16_t crc = 0;
    const uint16_t poly = 0x80F;
    const uint16_t mask = 0xFFF;

    for (char b : data) {
        uint8_t byte = b;
        for (int i = 0; i < 8; ++i) {
            bool crc_top = (crc & 0x0800) != 0;
            bool data_top = (byte & 0x80) != 0;
            crc <<= 1;
            if (crc_top ^ data_top) {
                crc ^= poly;
            }
            crc &= mask;
            byte <<= 1;
        }
    }
    return crc;
}

uint16_t calculate_crc16(const std::string& data) {
    uint16_t crc = 0;
    const uint16_t poly = 0x8005;

    for (char b : data) {
        uint8_t byte = b;
        for (int i = 0; i < 8; ++i) {
            bool crc_top = (crc & 0x8000) != 0;
            bool data_top = (byte & 0x80) != 0;
            crc <<= 1;
            if (crc_top ^ data_top) {
                crc ^= poly;
            }
            byte <<= 1;
        }
    }
    return crc;
}

uint16_t calculate_crc_ccitt(const std::string& data) {
    uint16_t crc = 0;
    const uint16_t poly = 0x1021;

    for (char b : data) {
        uint8_t byte = b;
        for (int i = 0; i < 8; ++i) {
            bool crc_top = (crc & 0x8000) != 0;
            bool data_top = (byte & 0x80) != 0;
            crc <<= 1;
            if (crc_top ^ data_top) {
                crc ^= poly;
            }
            byte <<= 1;
        }
    }
    return crc;
}

uint32_t calculate_crc32(const std::string& data) {
    uint32_t crc = 0;
    const uint32_t poly = 0x04C11DB7;

    for (char b : data) {
        uint8_t byte = b;
        for (int i = 0; i < 8; ++i) {
            bool crc_top = (crc & 0x80000000) != 0;
            bool data_top = (byte & 0x80) != 0;
            crc <<= 1;
            if (crc_top ^ data_top) {
                crc ^= poly;
            }
            byte <<= 1;
        }
    }
    return crc;
}

int main() {
    std::string input_data;
    std::cout << "Enter data string: ";
    std::getline(std::cin, input_data);

    std::cout << std::hex << std::uppercase << std::setfill('0');

    uint16_t crc12 = calculate_crc12(input_data);
    std::cout << "CRC-12:    0x" << std::setw(3) << crc12 << std::endl;

    uint16_t crc16 = calculate_crc16(input_data);
    std::cout << "CRC-16:    0x" << std::setw(4) << crc16 << std::endl;

    uint16_t crc_ccitt = calculate_crc_ccitt(input_data);
    std::cout << "CRC-CCITT: 0x" << std::setw(4) << crc_ccitt << std::endl;

    uint32_t crc32 = calculate_crc32(input_data);
    std::cout << "CRC-32:    0x" << std::setw(8) << crc32 << std::endl;

    return 0;
}