// ============================================================================
// Constant Lable
// ============================================================================
LEVEL1_BASE_ADDR = 0x00020000

// ============================================================================
// text section
// ============================================================================
.text
mcr p15, 0, r0, c7,c5, 6        // BPIALL Disable Branch Predictor Ararry
mcr p15, 0, r0, c8,c7, 0        // TLBIALL Disable TLB

// ============================================================================
// about TTBCR
// Architecture Reference Manual ARMv7-A and ARMv7-R B4.1.153
// TTBCR Translation Table Base Control Register
// TTBCR determines which of the Translation Table Base Registers, TTBR0 or TTBR1,
// defines the base address for a translation table walk required for the stage 1 translation
// of a memory access from any mode other than Hyp mode.
// * Register Format *
// [31]      EAE 1:40bit address translate 0:32bit address translate
// [30:6]    must be 0
// [5]       PD1 1:Disable Table Walk for TTBR1, 0:Enable Table Walk for TTBR1
// [4]       PD0 1:Disable Table Walk for TTBR0, 0:Enable Table Walk for TTBR0
// [3]       must be 0
// [2:0]     N Set Table size of TTBR0 
//           0x00:16KB, 0x01:8KB, 0x02:4KB, 0x03:2KB, 0x04:1KB
//           0x05:512Byte 0x06:256Byte 0x07 128Byte
// ============================================================================

// virtual address range is 0x00000000 ～ 0xFFFFFFFF
// SRAM A1,A2 (0x0000 0000～ 0x0000 8000) are used for stack area.
mov r0, #0x00               // EAE:0, PD1:Enable, PD0:Enable N:16KB
mcr p15, 0, r0, c2,c0, 2    // TTBCR Disable TLB

// about TTBR0(TTBR1 is same)
// Architecture Reference Manual ARMv7-A and ARMv7-R B4.1.154
// TTBR0 Translation Table Base Register 0
// TTBR0 holds the base address of translation table 0,
// and information about the memory it occupies.
// This is one of the translation tables for the stage 1 
// translation of memory accesses from modes other than Hyp mode.
// This register is part of the Virtual memory control registers functional group.
// * Register Format *
// [31:14-N(TTBCR)] N is TTCR.N
// [13-N:7]
// [6]      IRGN multiprocessing extensions, On Cortex-A7, must be 0
// [5]      NOS Not Outer Shareable 1:Enable Outer Share 0:Disable Outer Share. On Cortex-A7, must be 0
// [4]      RGN Region Indicates the Outer cacheability attributes
//          for the memory associated with the translation table walks
//          internal memory is not cacheable
// [1]      1   Shareable bit 1:Enable Share 0:Disable Share
// [0]      C   Cacheable bit 1:Enable Inner Cache 0:Disable Inner Cache
ldr r0, =LEVEL1_BASE_ADDR   // level 1 translation table base address
mcr p15, 0, r0, c2, c0, 0   // write TTBR0

// Enable MMU
mrc p15, 0, r0, c1, c0,0    // read SCTLR
orr r0, r0, #0x01           // set MMU Enable(M0 is 1)
mcr p15, 0, r0, c1, c0, 0   // write SCTLR

