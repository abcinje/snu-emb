#include <systemc.h>

SC_MODULE(Counter) {
    sc_in<bool> clk;        // Clock input
    sc_out<int> count_out;  // Output for count value
    int count;  // Counter variable

    void counter_process() {
        while (true) {
            // TODO: Increment count on positive clock edge
            count++;

            // Output the count value (HINT: write)
            count_out.write(count);

            // Display count value
            cout << "Count: " << count << endl;

            // wait for next clock cycle
            wait();
        }
    }

    // Constructor
    SC_CTOR(Counter) {
        count = 0;

        // TODO: Define counter_process SC_THREAD and sensitivity to clock positive edge
        SC_THREAD(counter_process);
        sensitive << clk.pos();
    }
};

// Main function
int sc_main(int argc, char* argv[]) {
    // Define signals
    sc_clock clk("clk", 5, SC_NS); // Clock signal with period 5 ns
    sc_signal<int> count_out;       // Output signal for count value

    // TODO: Instantiate Counter module
    Counter counter("counter");

    // Connect clock signal
    // Connect count output
    counter(clk, count_out);

    // Start simulation
    sc_start(50, SC_NS); // Simulate for 50 ns

    return 0;
}
