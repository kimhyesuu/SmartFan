//#define F_CPU 16000000L
//#include <avr/io.h>
//#include <avr/interrupt.h>

volatile int count1 = 0;				// �����÷ΰ� �߻��� Ƚ��
volatile int state1 = 0;				// LED ���� ����

// �̰� ISR(TIMER0_OVF_vect)   ��16ms ���� ��� �´�.
ISR(TIMER0_OVF_vect)
{
	count1++;
}


ISR(TIMER0_COMP_vect)
{			//AtmelStudio ���� ���ͷ�Ʈ ���� ��ƾ
	static char i=0;
	//FND_CONTROL_PORT &= 0b11110000;			
	//FND_CONTROL_PORT |= 0b00000001<<i;
	//FND_DATA_PORT = FND[i];
	i++;
	if(i==4)i=0;
}

void Timer0_Init(void)
{
	TCCR0 = 0b00001110;
	OCR0 = 255;
	//  1024/16000000 = 255 / 16000 => 1/64 ==> 0.015625sec
	//  0.015625sec  ==> 16 ms ���� OCR Int�� �߻�
	TIMSK |= 1<<OCIE0;
	TIFR = 0x00;                                 // clear all interrupt flags
	ETIFR = 0x00;
}

void Timer2_Init(void)
{
	TCCR2 = 0b00000101;    // ���ֺ� 1024�� ������    // 16M/1024 ==> 16000000/1024 ==> 15,625 HZ  ==> 15,625 
	                                                  // T = 1/f ==> 1/15625Hz = 0.000064sec x 1000 = 0.064 ms 
													  // 0.064 x 1000 = 64us�� �ҿ�
													  // �׷��� TCN0 1�� 64us �̹Ƿ� 64�� �����ذ��̴�. 
													  // 1cm�̵��� 29us �ҿ�
}	

