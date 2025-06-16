#include <cassert>
#include <iostream>

constexpr float tempThreshold = 35.0f;
constexpr float gasVoltThreshold = 1.5f;

bool computeDanger(int tempRaw, int gasRaw) {
    float temperature = (tempRaw / 1023.0f) * 3.3f * 100.0f;
    float gasVoltage  = (gasRaw  / 1023.0f) * 5.0f;
    return (temperature > tempThreshold || gasVoltage > gasVoltThreshold);
}

int main() {
    // Both readings below thresholds
    assert(!computeDanger(100, 100));

    // Temperature above threshold
    int tempRawHigh = static_cast<int>((tempThreshold / 100.0f / 3.3f) * 1023.0f) + 1;
    assert(computeDanger(tempRawHigh, 100));

    // Gas voltage above threshold
    int gasRawHigh = static_cast<int>((gasVoltThreshold / 5.0f) * 1023.0f) + 1;
    assert(computeDanger(100, gasRawHigh));

    // Both readings above thresholds
    assert(computeDanger(tempRawHigh, gasRawHigh));

    std::cout << "All danger tests passed.\n";
    return 0;
}
