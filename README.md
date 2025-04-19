# Hardware performance-counter based malware detection on resource-constrained embedded systems

This repository contains the work I did during my master's thesis titled **"Hardware performance-counter based malware detection on resource-constrained embedded systems."**

The goal of this thesis is to evaluate whether software exploitation can be detected using hardware performance counters (HPC) on RISC-V embedded systems.

In it you'll find a folder called "GvSOC" containing the code used to extract HPCs and simulate a buffer overflow. You will also find in this folder the csv file containing the HPCs for each program execution and a python script for displaying a graph of normalized metrics based on the number of instructions executed. I will also create a folder called "Chipyard" in which I will add my current work based on a BOOM core.

## Methodology 

1. **Literature Review**
   - Studied RISC-V architecture and various RISC-V simulators.
   - Learned about the uses of HPCs for anomaly detection.
   - Reviewed common software exploitation techniques and RISC-V specificities.

2. **Initial Experiments**
   - First experiments aimed to simulate a simple buffer overflow and observe HPC behavior during exploitation.
   - Started using **Chipyard**, but encountered difficulties in accessing HPC data.
   - Researched related academic papers and found one using **GVSOC** for a similar purpose.

3. **Switch to GVSOC**
   - Successfully simulated simple buffer overflow attacks and collected HPC data.
   - However, the software exploitation using GvSOC were limited (no OS, minimal libc, no input).

4. **Upcoming Work**
   - Transitioning to **Chipyard** to allow more complex exploitations.
   - Plan to study the potential impact of new counters on improving detection accuracy (ret counter).

## Current Results

- Ran and monitored a basic buffer overflow attack using **GVSOC** and the **PULP RI5CY core**.
- Collected HPC data during both normal and exploited execution flows.
    - Due to GvSOC limitations, gathered the results only at the end of the execution flow.
- No clear or consistent anomalies were observed in the perfomance counters provided by the RI5CY core.
    - Need more counters and more realistic/complex software exploitation.

## Research Questions

1. **Can HPCs be used to detect software exploitation on embedded RISC-V systems?**
2. **What kind of HPC patterns or anomalies correspond to such exploitations?**
3. **Would creating new hardware performance counters improve detection capabilities? If so, what kind of counters would be most effective?**

## Planned Thesis Structure

1. **Introduction**
2. **State of the Art**
   - Embedded security & malware
   - RISC-V architecture
   - Hardware Performance Counters
3. **Threat Model and Attack Scenarios**
4. **Experimental Setup**
   - GVSOC, Chipyard
   - Payload and overflow setup
5. **Detection Methodology**
   - Data collection via HPCs
   - Analysis techniques
6. **Results**
7. **Challenges, limitations**
8. **Conclusion**


