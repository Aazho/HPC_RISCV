#include <stdio.h>

int main() {
    __asm__ volatile (
        
        "addi sp, sp, -32\n"        
        "sw   s0, 28(sp)\n"        
        "addi s0, sp, 34\n"         

       
        "sw   zero, -22(s0)\n"      

        "j    .Lloop_check\n"       

        ".Lloop_start:\n"           
        "lw   a5, -22(s0)\n"        
        "addi a5, a5, 1\n"          
        "sw   a5, -22(s0)\n"        

        ".Lloop_check:\n"           
        "lw   a4, -22(s0)\n"       
        "lui  a5, 0x5f5e\n"           
        "addi a5, a5, 574\n"        
        "ble  a4, a5, .Lloop_start\n" 

        "li   a5, 0\n"              
        "mv   a0, a5\n"             
        "lw   s0, 28(sp)\n"        
        "addi sp, sp, 32\n"         
        "li a5, 0x1c018FF4\n"
        "xor a6, a6, a6\n"
        "addi a6, a6, 1\n"
        "slli a6, a6, 0x10\n"
        "sub a5, a5, a6\n"
        "jalr ra, a5, 0x22\n"                    
    );

    return 0; 
}

