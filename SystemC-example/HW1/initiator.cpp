#include <systemc.h>

SC_MODULE(Counter) {
    sc_in<bool> clk;        // Clock input
    sc_out<int> count_out;  // Output for count value
    int count;  // Counter variable

    void counter_process() {
        while (true) {
            // TODO: Increment count on positive clock edge
			// Output the count value (HINT: write)
            cout << "Count: " << count << endl; // Display count value
            
			// wait for next clock cycle
        }
    }

    // Constructor
    SC_CTOR(Counter) {
        count = 0;
        // TODO: Define counter_process SC_THREAD and sensitivity to clock positive edge
    }
};

// Main function
int sc_main(int argc, char* argv[]) {
    // Define signals
    sc_clock clk("clk", 5, SC_NS); // Clock signal with period 5 ns
    sc_signal<int> count_out;       // Output signal for count value

    // TODO: Instantiate Counter module
    // Connect clock signal
    // Connect count output

    // Start simulation
    sc_start(50, SC_NS); // Simulate for 50 ns

    return 0;
}
