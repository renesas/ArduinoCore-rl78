#ifndef _MSTIMER2_H_
#define _MSTIMER2_H_

namespace MsTimer2
{
    void set(unsigned long ms, void (*f)());
    void setMicros(unsigned short us, void (*f)());
    void setClock(unsigned short fclk, void (*f)());
    void start();
    void stop();
}

#endif/*_MSTIMER2_H_*/
