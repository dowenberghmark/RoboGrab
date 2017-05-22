//---------------------------------------------------------------------------------
// Bo mon Ky thuat May tinh, Vien CNTT-TT, Dai hoc Bach Khoa Ha Noi
//                                LAB 01
//---------------------------------------------------------------------------------
#include <stdio.h>
#include "brick.h"

int main()
{
	printf( "Bai lab01.\n" );
	printf( "EV3 dang khoi dong...\n" );
	brick_init();
	
	// Check connection at B and C
	if(tacho_is_plugged(OUTB | OUTC, LEGO_EV3_L_MOTOR)) 
	{
		// set up brake
		tacho_set_stop_action(OUTB | OUTC, TACHO_BRAKE);
		
		// set up speed
		tacho_set_duty_cycle_sp(OUTB | OUTC, 50);

		// Ra lenh cho dong co hoat dong
		tacho_run_direct(OUTB | OUTC);
		printf( "Dong co dang chay.\n" );
		
		//printf( "Doi 3 giay...\n" );
		// Doi 3 (s)
		//sleep_ms(3000);
		
		
		// Dung dong co
		//tacho_stop(OUTB | OUTC);
		//printf( "Dong co dung.\n" );
	}
	
	brick_uninit();
	printf( "Ket thuc...\n" );
	return 0;
}
