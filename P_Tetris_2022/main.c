#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
	SHT 3704, 3705

	CLK PORTA0
	CS PORTA1
	DIN PORTA2
*/

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

unsigned char number[10][8] =
{
	{
		0B00111000,
		0B01000100,
		0B01000100,
		0B01000100,
		0B01000100,
		0B01000100,
		0B01000100,
		0B00111000
	},
	{
		0B00010000,
		0B00110000,
		0B00010000,
		0B00010000,
		0B00010000,
		0B00010000,
		0B00010000,
		0B00111000
	},
	{
		0B00111000,
		0B01000100,
		0B00000100,
		0B00000100,
		0B00001000,
		0B00010000,
		0B00100000,
		0B01111100
	},
	{
		0B00111000,
		0B01000100,
		0B00000100,
		0B00011000,
		0B00000100,
		0B00000100,
		0B01000100,
		0B00111000
	},
	{
		0B00000100,
		0B00001100,
		0B00010100,
		0B00100100,
		0B01000100,
		0B01111100,
		0B00000100,
		0B00000100
	},
	{
		0B01111100,
		0B01000000,
		0B01000000,
		0B01111000,
		0B00000100,
		0B00000100,
		0B01000100,
		0B00111000
	},
	{
		0B00111000,
		0B01000100,
		0B01000000,
		0B01111000,
		0B01000100,
		0B01000100,
		0B01000100,
		0B00111000
	},
	{
		0B01111100,
		0B00000100,
		0B00000100,
		0B00001000,
		0B00010000,
		0B00100000,
		0B00100000,
		0B00100000
	},
	{
		0B00111000,
		0B01000100,
		0B01000100,
		0B00111000,
		0B01000100,
		0B01000100,
		0B01000100,
		0B00111000
	},
	{
		0B00111000,
		0B01000100,
		0B01000100,
		0B01000100,
		0B00111100,
		0B00000100,
		0B01000100,
		0B00111000
	}
};
unsigned long welcome[4][8] =
{
	{
		0b00000100,
		0b00000100,
		0b00000101,
		0b00110101,
		0b01001010,
		0b01000000,
		0b01001000,
		0b00110000
	},
	{
		0b01000001,
		0b01000001,
		0b01000001,
		0b01011001, 
		0b10100101, 
		0b00100100,
		0b00100100,
		0b00011000
	},
	{
		0b11000000,
		0b00000000,
		0b11000000,
		0b00001010,
		0b11010101,
		0b00010101,
		0b00010001,
		0b00010001
	},
	{
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000111,
		0b01110100,
		0b00000111,
		0b00000100,
		0b00000111
	}
};


unsigned char display_1[8], display_2[8], display_3[8], display_4[8], space_1[8], space_2[8], space_3[8], space_4[8];
unsigned long cnt1, cnt2, flag = 1, status, down, side, destroy, endline, zero1, zero2, space[8], space_temp[8], temp[12];
unsigned char block[4][8], block_temp[8];
int m1, m2, PressLeft, PressRight, m5, m6, m7 = 1, m8 = 0, m_start = 1, score, br, br_temp, gameend, set = 1;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 254;
	cnt1++;
	if(cnt1 >= 65535) cnt1 = 0;
}

ISR(TIMER2_OVF_vect)
{
	if(!m_start) cnt2++;
	if(cnt2 <= 100) m7 = 0;
	if(cnt2 >= 5000)
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
	PORTA |= (1 << PORTA1); // CS ON
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

void left();
void right();
void left()
{
	if(!(temp[0] | temp[1] | temp[2]))
		for (int i = 0; i < 8; i++)
			temp[i+1] = temp[i+2];
	else PressLeft--;
}

void right()
{
	if(!(temp[9] | temp[10] | temp[11]))
		for (int i = 7; i >= 0; i--)
			temp[i+2] = temp[i+1];
	else PressRight--;	
}

void side_check()
{
	if(PressLeft > PressRight)
		for(int i = 1; i <= PressLeft - PressRight; i++)
			left();
	else if(PressRight > PressLeft)
		for(int i = 1; i <= PressRight - PressLeft; i++)
			right();
	
	if(m5)
	{
		for(int i = 0; i < 8; i++)
		{
			if(space[i] & (temp[i+2] << down))
			{
				right();
				PressLeft--;
			}
		}
	}
	if(m6)
	{
		for(int i = 0; i < 8; i++)
		{
			if(space[i] & (temp[i+2] << down))
			{
				left();
				PressRight--;
			}
		}
	}
}

void down_check()
{
	m1 = 0, m2 = 0;
	for(int i = 0; i < 8; i++)
	{
		if(space[i] & (temp[i+2] << down))
		{
			down--;
			m2 = 1;
		}
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
		
		down = 0, PressLeft = 0, PressRight = 0, status = 0, m_start = 1;
		endline = (space[0] | space[1] | space[2] | space[3] | space[4] | space[5] | space[6] | space[7]);
		if(endline & 0x01)
			m_start = 1, m8 = 0, gameend = 1;
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
			{
				down = 0;
				PressLeft = 0, PressRight = 0;
				status = 0;
				m_start = 1;
				endline = (space[0] | space[1] | space[2] | space[3] | space[4] | space[5] | space[6] | space[7]);
				if(endline & 0x01)
					m_start = 1, m8 = 0, gameend = 1;
			}
			for(int i = 0; i < 8; i++)
				space[i] = space[i] | (temp[i+2] << down);
				
			
			return;
		}
	}
}

void line_break()
{
	destroy = ~(space[0] & space[1] & space[2] & space[3] & space[4] & space[5] & space[6] & space[7]);
	if(~destroy)
	{
		for(int i = 0; i < 8; i++)
			space[i] &= destroy;
		
		for(int i = 0; i < 24; i++)
		{
			if(destroy % 2 == 0)
			{
				if(!zero1) zero1 = i, zero2 = i;
				else zero2 = i;
			}
			destroy /= 2;
		}
		zero2++;
		destroy = ~0;
		
		for(int i = 0; i < 8; i++)
		{
			space_temp[i] = ~(0xFFFFFFFF << zero1) & space[i];
			space[i] &= (0xFFFFFFFF << zero1);
			space[i] |= (space_temp[i] << (zero2 - zero1));
		}
		
		score += ((zero2 - zero1)*(zero2 - zero1)) * 10;
		zero1 = 0, zero2 = 0;
		
		for(int i = 0; i < 8; i++)
		{
			display_4[i] = (space[i] << 8) >> 24;
			display_3[i] = (space[i] << 16) >> 24;
			display_2[i] = (space[i] << 24) >> 24;
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
	w(0x0A, 0x02);
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
		if(gameend)
		{
			for(int i = 0; i < 8; i++)
			{
				space[i] = 0;
				display_1[i] = 0;
				display_2[i] = 0;
				display_3[i] = 0; 
				display_4[i] = 0;
				space_1[i] = 0;
				space_2[i] = 0;
				space_3[i] = 0;
				space_4[i] = 0;
			}
				
			while(1)
			{
				for(int i = 1; i <= 8; i++)
				{	
					write(i, number[score % 10][i-1]);
					write(i, number[(score % 100) / 10][i-1]);
					write(i, number[(score % 1000) / 100][i-1]);
					write(i, number[score / 1000][i-1]);
					PORTA |= (1 << PORTA1);
				}
				
				unsigned char sw = ~PINC & 0x0F;
				
				if(sw)
				{	
					m1 = 0, m2 = 0, PressLeft = 0, PressRight = 0, m5 = 0, m6 = 0, m7 = 1, m8 = 0, m_start = 1, score = 0, br = 0, br_temp = 0, gameend = 0, set = 1;
					break;
				}
			}
		}
		
		while(m_start)
		{
			if(set)
			{
				for(int i = 1; i <= 8; i++)
				{
					write(i, welcome[3][i-1]);	
					write(i, welcome[2][i-1]);
					write(i, welcome[1][i-1]);
					write(i, welcome[0][i-1]);
					PORTA |= (1 << PORTA1);
				}
				set = 0;
			}
			
			unsigned char sw = ~PINC & 0x0F;
			srand(cnt1);
			if(sw | m8)
			{
				if(!br)
					br = rand() % 7 + 1;
				else
					br = br_temp;
				br_temp = rand() % 7 + 1;
				
				while(br_temp == br)
					br_temp = rand() % 7 + 1;

				if(br == 1) 
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_1[i][j];
				if(br == 2)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_2[i][j];
				if(br == 3)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_3[i][j];
				if(br == 4)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_4[i][j];
				if(br == 5)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_5[i][j];
				if(br == 6)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_6[i][j];
				if(br == 7)
					for(int i = 0; i < 4; i++)
						for(int j = 0; j < 8; j++)
							block[i][j] = block_7[i][j];
				if(br_temp == 1)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_1[0][i];
				if(br_temp == 2)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_2[0][i];
				if(br_temp == 3)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_3[0][i];
				if(br_temp == 4)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_4[0][i];
				if(br_temp == 5)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_5[0][i];
				if(br_temp == 6)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_6[0][i];
				if(br_temp == 7)
					for(int i = 0; i < 8; i++)
						block_temp[i] = block_7[0][i];
				
				m_start = 0;
			}
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
					temp[i+2] = block[status][i];
				turn_check();
			}
		}
		else if(sw & 0x02)
		{
			if(flag & m7)
			{
				flag = 0;
				PressLeft++;
				m5 = 1;
			}
		}
		else if(sw & 0x04)
		{
			cnt2 += 3500;
		}
		else if(sw & 0x08)
		{
			if(flag & m7)
			{
				flag = 0;
				PressRight++;
				m6 = 1;
			}
		}
		else flag = 1;
		
		line_break();
		
		for(int i = 0; i < 8; i++)
			temp[i+2] = block[status][i];
			
		side_check();
		down_check();
		
		for(int i = 0; i < 8; i++)
		{
			space_4[i] = (space[i] << 8) >> 24;
			space_3[i] = (space[i] << 16) >> 24;
			space_2[i] = (space[i] << 24) >> 24;
			space_1[i] = 0x10 | (block_temp[i] << 1);
		}
		
		m5 = 0, m6 = 0 , m7 = 1, m8 = 1;
		output();
	}
}
