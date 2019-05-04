.text

# BPIALL Disable Branch Predictor Ararry
mcr p15, 0, r0, c7,c5, 6
# TLBIALL Disable TLB
mcr p15, 0, r0, c8,c7, 0

# Architecture Reference Manual ARMv7-A and ARMv7-R B4.1.153
# TTBCR Translation Table Base Control Register
# TTBCR determines which of the Translation Table Base Registers, TTBR0 or TTBR1,
# defines the base address for a translation table walk required for the stage 1 translation
# of a memory access from any mode other than Hyp mode.
# Register Format
# [31]      EAE 1:40bit address translate 0:32bit address translate
# [30:6]    must be 0
# [5]       PD1 1:Disable Table Walk for TTBR1, 0:Enable Table Walk for TTBR1
# [4]       PD0 1:Disable Table Walk for TTBR0, 0:Enable Table Walk for TTBR0
# [3]       must be 0
# [2:0]     N Set Table size of TTBR0 
#           0x00:16KB, 0x01:8KB, 0x02:4KB, 0x03:2KB, 0x04:1KB
#           0x05:512Byte 0x06:256Byte 0x07 128Byte

# EAE:0, PD1:Enable, PD0:Enable N:16KB
mov r0, #0x00

# TTBCR Disable TLB
mcr p15, 0, r0, c2,c0, 2
