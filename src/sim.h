#ifndef _SIM_H_
#define _SIM_H_ 1


#if (SIM == 1)
        #define sim_out(val)  (*((volatile char *)0x20)) = (val)
#else
        #define sim_out(val)
#endif

#endif
