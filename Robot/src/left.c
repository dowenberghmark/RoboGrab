//---------------------------------------------------------------------------------
// Bo mon Ky thuat May tinh, Vien CNTT-TT, Dai hoc Bach Khoa Ha Noi
//                                LAB 02
//---------------------------------------------------------------------------------
#include <stdio.h>
#include "brick.h"
int main()
{
	int val;
	
	printf( "Bai lab02.\n" );
	printf( "EV3 dang khoi dong...\n" );
	brick_init();
	
	// Thiet lap che do dung cho dong co
	tacho_set_stop_action(OUTB | OUTC, TACHO_BRAKE);
	// Thiet lap toc do cho dong co
	tacho_set_duty_cycle_sp(OUTB | OUTC, 50);
	// Ra lenh cho dong co hoat dong
	tacho_run_direct(OUTB | OUTC);
	
	while(1)
	{
		// Doi 100 (ms)
		sleep_ms(100);
		// Lay gia tri khoang cach toi vat can tu cam bien sieu am
		val = sensor_get_value (0, IN4, 0);
		// In gia tri ra man hinh
		printf("val = %d\n", val);
		
		if( val <= 10)	// Neu khoang cach nho hon hoac bang 30 (cm)
		{
			// Dung dong co
			tacho_stop(OUTB | OUTC);
			break;
		}
	}
	
	brick_uninit();
	printf( "Ket thuc...\n" );
	return 0;
}
