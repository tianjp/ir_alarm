#include "configs.h"

// 音符定义
#define xz  0	// 休止符
#define l1  1	// 低音 1
#define l2  2	// 低音 2
#define l3  3	// 低音 3
#define l4  4	// 低音 4
#define l5  5	// 低音 5
#define l6  6	// 低音 6
#define l7  7	// 低音 7
#define m1  8	// 中音 1
#define m2  9	// 中音 2
#define m3  10	// 中音 3
#define m4  11	// 中音 4
#define m5  12	// 中音 5
#define m6  13	// 中音 6
#define m7  14	// 中音 7
#define h1  15	// 高音 1
#define h2  16	// 高音 2
#define h3  17	// 高音 3
#define h4  18	// 高音 4
#define h5  19	// 高音 5
#define h6  20	// 高音 6
#define h7  21	// 高音 7

#if 1 
// 8位PWM对应的周期值
code const unsigned char pwm8b_mc[] = {
	0, 120, 106, 95, 89, 80, 71, 63, 
	60, 53, 47, 45, 40, 36, 32, 30, 
	27, 24, 22, 20, 18, 16
};
	
// 10位PWM对应的周期值--高字节在前
code const unsigned char pwm10b_mc[] = {
	0, 0, 3, 188, 3, 97, 2, 247, 
	2, 204, 2, 126, 2, 56, 1, 250, 
	1, 222, 1, 170, 1, 123, 1, 102, 
	1, 63, 1, 28, 0, 253, 0, 239, 
	0, 213, 0, 190, 0, 179, 0, 159, 
	0, 142, 0, 127
};
#endif

// 16位PWM对应的周期值--高字节在前
code const unsigned char pwm16b_mc[] = {
	0, 0, 59, 192, 54, 17, 47, 108, 
	44, 197, 39, 220, 35, 131, 31, 161, 
	29, 224, 26, 153, 23, 182, 22, 95, 
	19, 238, 17, 193, 15, 209, 14, 240, 
	13, 76, 11, 219, 11, 47, 9, 247, 
	8, 225, 7, 232
};

// 铃儿响叮当
code const unsigned char jingle_bell2[] = {
	8, m3, 1, 0, 8, m3, 1, 0, 
	16, m3, 1, 0, 8, m3, 1, 0, 
	8, m3, 1, 0, 16, m3, 1, 0, 
	8, m3, 8, m5, 12, m1, 4, m2, 
	24, m3, 8, m3, 16, m4, 1, 0, 
	12, m4, 1, 0, 4, m4, 1, 0, 
	8, m4, 16, m3, 1, 0, 4, m3, 
	1, 0, 4, m3, 8, m5, 8, m4, 
	8, m3, 8, m2, 32, m1
};

void play_music(void)
{
	unsigned char i;
	unsigned char len = sizeof(jingle_bell2);
	unsigned int delay;
	unsigned char freq_l, freq_h;
	unsigned int freq;
	unsigned char pos;
	
	for (i=0; i<len; i+=2)
	{
		delay = jingle_bell2[i];
		pos = jingle_bell2[i + 1];
		
		delay &= 0x1f;	// 取后5位
		delay *= 40;	// 单位40毫秒
			
		freq_h = pwm16b_mc[pos * 2];
		freq_l = pwm16b_mc[pos * 2 + 1];
		
		freq = (freq_h << 8) + freq_l;
		
		load_pwm(freq);
		//delay_ms(delay);
	}
}	
