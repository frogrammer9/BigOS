#include "power.h"

void machine_poweroff() {
	//TODO: 
	machine_halt();
}

void machine_reboot() {
	//TODO: 
	machine_halt();
}

void machine_halt() {
	for(;;) asm volatile("wfi");
}
