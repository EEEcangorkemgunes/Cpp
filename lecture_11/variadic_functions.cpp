#include <iostream>
#include <cstdarg>

int sum(int first, ...) {
    int total = 0;
    va_list args;
    va_start(args, first);  // Initialize va_list with the first argument

    int current = first;
    while (current != 0) {  // Stop when we encounter the sentinel value (0)
        total += current;
        current = va_arg(args, int);  // Get the next argument
    }

    va_end(args);  // Clean up
    return total;
}

int main() {
    // Example usage: the last argument (0) marks the end
    std::cout << "Sum of 1, 2, 3, 4, 5 is: " << sum(1, 2, 3, 4, 5, 0) << std::endl;
    return 0;
}
