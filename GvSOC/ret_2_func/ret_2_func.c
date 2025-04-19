#include <stdio.h>
#include <string.h>
#include <pmsis.h>

static uint32_t cycles_cnt = 0;
static uint32_t instr_cnt = 0;
static uint32_t active_cnt = 0;
static uint32_t imiss_cnt = 0;
static uint32_t jr_stall_cnt = 0;
static uint32_t jump_cnt = 0;
static uint32_t branch_cnt = 0;
static uint32_t btaken_cnt = 0;
static uint32_t rvc_cnt = 0;

void start_perf_counters() {
    pi_perf_conf(
        (1 << PI_PERF_CYCLES) | 
        (1 << PI_PERF_INSTR) | 
        (1 << PI_PERF_ACTIVE_CYCLES) | 
        (1 << PI_PERF_IMISS) | 
        (1 << PI_PERF_JR_STALL) | 
        (1 << PI_PERF_JUMP) | 
        (1 << PI_PERF_BRANCH) | 
        (1 << PI_PERF_BTAKEN) | 
        (1 << PI_PERF_RVC)
    );
    pi_perf_reset();   
    pi_perf_start();   
}

void stop_perf_counters() {
    
    pi_perf_stop();

   
    cycles_cnt = pi_perf_read(PI_PERF_CYCLES);
    instr_cnt = pi_perf_read(PI_PERF_INSTR);
    active_cnt = pi_perf_read(PI_PERF_ACTIVE_CYCLES);
    imiss_cnt = pi_perf_read(PI_PERF_IMISS);
    jr_stall_cnt = pi_perf_read(PI_PERF_JR_STALL);
    jump_cnt = pi_perf_read(PI_PERF_JUMP);
    branch_cnt = pi_perf_read(PI_PERF_BRANCH);
    btaken_cnt = pi_perf_read(PI_PERF_BTAKEN);
    rvc_cnt = pi_perf_read(PI_PERF_RVC);
}

void print_perf_counters() {
    printf("Performance Counters:\n");
    printf("Cycles: %lu\n", cycles_cnt);
    printf("Instructions: %lu\n", instr_cnt);
    printf("Active Cycles: %lu\n", active_cnt);
    printf("I-Cache Misses: %lu\n", imiss_cnt);
    printf("JR Stalls: %lu\n", jr_stall_cnt);
    printf("Jumps: %lu\n", jump_cnt);
    printf("Branches: %lu\n", branch_cnt);
    printf("Branches Taken: %lu\n", btaken_cnt);
    printf("RVC Instructions: %lu\n", rvc_cnt);

    if (instr_cnt > 0) {
        printf("CPI: %.2f\n", (float)cycles_cnt / instr_cnt); // Cycles Per Instruction
    }
}

void win() {
    stop_perf_counters();  
    printf("You Win!\n");
    print_perf_counters(); 
    exit(0);               // Exit the program
}

void vuln() {
    char small_buffer[8];
    //char big_buffer[32] = "AAAAA";
    char big_buffer[32] = "AAAAAAAAAAAAAAAAAAAA\x90\x8f\x00\x1c"; 
    printf("Overflowing buffer...\n");
    strcpy(small_buffer, big_buffer); 

    if ((uintptr_t)&big_buffer == 0xdeadbeef) { // Unlikely condition for testing
        win();
    }
}

int main() {
    start_perf_counters(); 
    vuln();               

    stop_perf_counters();  
    printf("Returned safely\n");
    
    print_perf_counters(); 
    return 0;
}
