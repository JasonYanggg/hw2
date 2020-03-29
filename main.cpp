#include "mbed.h"

AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
DigitalIn Switch(SW3);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
Serial pc(USBTX, USBRX);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
float ADCdata[1024];
int i, j;
int sample = 1024;
int freq, dis[10];
bool tmp;
float k;

int main(void)
{
    for (i = 0; i < sample; i++) {
        ADCdata[i] = Ain;
        wait(1./sample);
    }
    tmp = (ADCdata[0] > 0.3 ? true : false);
    for (i = 1; i < sample; i++) {
        if ((ADCdata[i] > 0.3) != tmp) {
            tmp = !tmp;
            break;
        }
    }
    for (j = 0; i < sample; i++, j++) {
        if ((ADCdata[i] > 0.3) != tmp) {
            break;
        }
    }
    freq = int(1.0/(2.0*j/sample));
    for (i = 0; i < sample; i++) {
        pc.printf("%1.3f\r\n", ADCdata[i]);
        wait(0.02);
    }
    for (i = freq, j = 0; i != 0; i /= 10, j++) {
            dis[j] = i % 10;
    }
    while (1) {
        if (Switch == 1) {
            greenLED = 0;
            redLED = 1;
            display = 0x0;
            for (k = 0; k < 1; k += 1.0/sample) {
                Aout = 0.5 + 0.5 * sin(2 * 3.14159 * freq * k);
                wait(1./sample);
            }
        }
        else {
            redLED = 0;
            greenLED = 1;
            for (i = j - 1; i > 0; i--) {
                display = table[dis[i]];
                wait(1);
            }
            display = table[dis[0]] | 0x80;
            wait(1);
        }
    }
}