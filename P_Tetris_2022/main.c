#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*

*/

unsigned char display_1[8], display_2[8], display_3[8], display_4[8], space_1[8], space_2[8], space_3[8], space_4[8];

unsigned char block_1[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000010,
		0b00000010,
		0b00000010,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001111,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000010,
		0b00000010,
		0b00000010,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_2[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_3[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000010,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000111,
		0b00000001,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000001,
		0b00000001,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000100,
		0b00000111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_4[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000010,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000111,
		0b00000100,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000110,
		0b00000010,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000001,
		0b00000111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_5[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000011,
		0b00000001,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000110,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000011,
		0b00000001,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000011,
		0b00000110,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_6[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000011,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000111,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000110,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000010,
		0b00000111,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};
unsigned char block_7[4][8] =
{
	{
		0b00000000,
		0b00000000,
		0b00000001,
		0b00000011,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000110,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000001,
		0b00000011,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000110,
		0b00000011,
		0b00000000,
		0b00000000,
		0b00000000
	}
};

unsigned long cnt1, cnt2, flag = 1, status, down, side, space[8], temp[12] = {};
unsigned char (*block)[8];
int m1, m2, m3, m4;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 254;
	cnt1++;
	if(cnt1 >= 65535)
	cnt1 = 0;
}

ISR(TIMER2_OVF_vect)
{
	cnt2++;
	if(cnt2 >= 1000)
	{
		cnt2 = 0;
		down++;
	}
}

void write(unsigned char H, unsigned char L)
{
	PORTA &= ~(1 << PORTA1);
	for(int i = 0; i < 8; i++)
	{
		PORTA &= ~(1 << PORTA0);
		if(H & 0x80)
			PORTA |= (1 << PORTA2);
		else
			PORTA &= ~(1 << PORTA2);
		H = H << 1;
		PORTA |= (1 << PORTA0);
	}
	for(int i = 0; i < 8; i++)
	{
		PORTA &= ~(1 << PORTA0);
		if(L & 0x80)
			PORTA |= (1 << PORTA2);
		else
			PORTA &= ~(1 << PORTA2);
		L = L << 1;
		PORTA |= (1 << PORTA0);
	}
}

void w(unsigned char H, unsigned char L)
{
	PORTA &= ~(1 << PORTA1);
	for(int i = 0; i < 8; i++)
	{
		PORTA &= ~(1 << PORTA0);
		if(H & 0x80)
			PORTA |= (1 << PORTA2);
		else
			PORTA &= ~(1 << PORTA2);
		H = H << 1;
		PORTA |= (1 << PORTA0);
	}
	for(int i = 0; i < 8; i++)
	{
		PORTA &= ~(1 << PORTA0);
		if(L & 0x80)
			PORTA |= (1 << PORTA2);
		else
			PORTA &= ~(1 << PORTA2);
		L = L << 1;
		PORTA |= (1 << PORTA0);
	}
	PORTA |= (1 << PORTA1);
}

void output()
{
	for(int i = 1; i <= 8; i++)
	{
		write(i, space_1[i-1]);
		write(i, space_2[i-1]);
		write(i, space_3[i-1]);
		write(i, space_4[i-1]);
		PORTA |= (1 << PORTA1);
	}
}

void turn_check()
{
	if(temp[0] | temp[1] | temp[10] | temp[11])
	{
		if(status > 0) status--;
		else status = 3;
		return;
	}
	for(int i = 0; i < 8; i++)
	{
		if(space[i] & ((temp[i+2]) << down))
		{
			if(status > 0) status--;
			else status = 3;
			return;
		}
	}
}

void left()
{
	if(!(temp[0] | temp[1] | temp[2]))
	{
		for (int i = 0; i < 8; i++)
		{
			temp[i+1]	= temp[i+2];
		}
	}
	else
		m3--;
}

void right()
{
	if(!(temp[9] | temp[10] | temp[11]))
	{
		for (int i = 7; i >= 0; i--)
		{
			temp[i+2] = temp[i+1];
		}
	}
	else
		m4--;
}

void side_check()
{	
	if(m3 > m4)
		for(int i = 1; i <= m3-m4; i++)
			left();
	if(m4 > m3) 
		for(int i = 1; i <= m4-m3; i++)
			right();
}

void down_check()
{
	m1 = 0, m2 = 0;
	for(int i = 0; i < 8; i++)
		if(space[i] & (temp[i+2] << down))
		{
			down--;
			m2 = 1;
		}
	if(m2)
	{
		for(int j = 0; j < 8; j++)
		{
			temp[j+2] = ((temp[j+2] << (down)));
			display_4[j] |= (temp[j+2] << 8) >> 24;
			display_3[j] |= (temp[j+2] << 16) >> 24;
			display_2[j] |= (temp[j+2] << 24) >> 24;
		}
		down = 0;
		return;
	}
	for(int i = 0; i < 8; i++)
	{
		if((temp[i+2] << down) >> 24)
		{
			down--;
			m1 = 1;
			i = 0;
		}
		if(m1)
		{
			for(int j = 0; j < 8; j++)
			{
				unsigned char temp1 = ((temp[j+2] << (down)) >> 16);
				display_4[j] |= temp1;
			}
		}
		if(i == 7)
		{
			if(m1)
				down = 0;
			for(int i = 0; i < 8; i++)
				space[i] = space[i] | (temp[i+2] << down);
			return;
		}
	}
}

int main(void)
{
	DDRA = 0x07;
	TCNT0 = 254;
	TCCR0 = 0x01;
	TCCR2 = 0x02;
	TIMSK = 0x41;
	sei();
	
	w(0x09, 0x00);
	w(0x0A, 0x01);
	w(0x0B, 0x07);
	w(0x0C, 0x01);
	w(0x0F, 0x00);
	
	for(int i = 1; i <= 8; i++)
	{
		w(i, display_1[i-1]);
		w(i, display_2[i-1]);
		w(i, display_3[i-1]);
		w(i, display_4[i-1]);
	}

	while(1)
	{
		srand(cnt1);
		if(0){
			m1 = rand() % 7 + 1;
			if(m1 == 1) block = block_1;
			if(m1 == 2) block = block_2;
			if(m1 == 3) block = block_3;
			if(m1 == 4) block = block_4;
			if(m1 == 5) block = block_5;
			if(m1 == 6) block = block_6;
			if(m1 == 7) block = block_7;
		}
		
		for(int i = 0; i < 8; i++)
			space[i] = 0;
		for(int i = 0; i < 8; i++)
		{
			space[i] = display_4[i];
			space[i] = (space[i] << 8) | display_3[i];
			space[i] = (space[i] << 8) | display_2[i];
			//space[i] = (space[i] << 8) | display_1[i];
		}
		
		unsigned char sw = ~PINC & 0x0F;
		if(sw & 0x01)
		{
			if(flag)
			{
				flag = 0;
				status = (status + 1) % 4;
				for(int i = 0; i < 8; i++)
					temp[i+2] = block_1[status][i];
				turn_check();
			}
		}
		else if(sw & 0x02)
		{
			if(flag)
			{
				flag = 0; 
				m3++;
			}
		}
		else if(sw & 0x08)
		{
			if(flag)
			{
				flag = 0;
				m4++;
			}
		}
		else flag = 1;
		
		for(int i = 0; i < 8; i++)
			temp[i+2] = block_1[status][i];
		side_check();
		down_check();
		
		
		for(int i = 0; i < 8; i++)
		{
			space_4[i] = (space[i] << 8) >> 24;
			space_3[i] = (space[i] << 16) >> 24;
			space_2[i] = (space[i] << 24) >> 24;
			space_1[i] = 0x10;
		}
		output();
	}
}
