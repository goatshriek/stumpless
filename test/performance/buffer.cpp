#include <iostream>
#include <chrono>
#include "stumpless.h" // Adjust the include based on your project's structure

// Function to simulate writing to a buffer
void write_to_buffer(stumpless_buffer_t *buffer, const char *message) {
    stumpless_add_entry(buffer, stumpless_new_entry(message));
}

// Function to run performance test
void run_performance_test() {
    const int iterations = 100000; // Adjust based on your performance needs
    stumpless_buffer_t *buffer = stumpless_new_buffer();

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        write_to_buffer(buffer, "Test message");
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken for " << iterations << " iterations: " << elapsed.count() << " seconds\n";

    stumpless_free_buffer(buffer);
}

int main() {
    run_performance_test();
    return 0;
}
