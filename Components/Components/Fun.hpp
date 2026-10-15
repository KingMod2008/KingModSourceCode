#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Fun
{
public:
    static void QueueModal(
        int modalType,
        const std::string& title,
        const std::string& body,
        uint8_t red,
        uint8_t green,
        uint8_t blue,
        uint8_t alpha,
        const std::vector<std::string>& citations,
        const std::vector<std::string>& buttons);
    static void HandleModalEvents();
    static void ShowWelcomeModal();
};
