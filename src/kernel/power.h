#ifndef BIGOS_KERNEL_POWER
#define BIGOS_KERNEL_POWER

//TODO: Determine naming convetion for "hardware" arch/machine/hardware/...

[[noreturn]]
void machine_poweroff();

[[noreturn]]
void machine_reboot();

[[noreturn]]
void machine_halt();

#endif //!BIGOS_KERNEL_POWER
