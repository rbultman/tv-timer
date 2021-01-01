/*
    rtcClock32khz.cpp

    Stuff related to reading the 32Khz input from the RTC.

    Initializes the peripheral and timer to accept input from the
    32Khz output from the RTC and call a callback once per second.

    Author: Rob Bultman
    License: MIT
*/

#include "mtu2_iobitmask.h"
extern "C"
{
    #include "RZ_A1H.h"
    #include "irq_ctrl.h"
}
#include "rtcClock32khz.h"

DigitalIn rtcClock32khzInput(P1_1, PullUp);
void InitRtcClock32khzInput(IRQHandler isrHandler)
{
    // Enable clock to MTU2
    CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
    // Set Channel 2 TCNT input to TCLKC, reset by TGRA
    MTU2.TCR_2 = 0x26;
    // Reset TGRA after 1 second
    MTU2.TGRA_2 = 32768;
    // use alternate pin function
    GPIO.PIPC1 = GPIO.PIPC1 | 0x0002;
    // set P1_1 to alt mode 3
    GPIO.PFCAE1 = GPIO.PFCAE1 & ~0x0002;
    GPIO.PFCE1 = GPIO.PFCE1 | 0x0002;
    GPIO.PFC1 = GPIO.PFC1 & ~0x0002;
    GPIO.PMC1 = GPIO.PMC1 | 0x0002;
    // Install the interrupt handler
    uint32_t retval = InterruptHandlerRegister(TGI2A_IRQn, isrHandler);
    if (retval == 0)
    {
        puts("IRQ for RTC clock successfully installed.");
    }
    else
    {
        puts("ERROR installing IRQ for RTC clock.");
    }
    // Enable the interrupt in MTU2
    MTU2.TIER_2 = MTU2.TIER_2 | MTU2_TIER_n_TGIEA;
    // Enable the IRQ at the core
    IRQ_Enable(TGI2A_IRQn);
    // start the timer
    MTU2.TSTR = MTU2.TSTR | 0x04;
}
