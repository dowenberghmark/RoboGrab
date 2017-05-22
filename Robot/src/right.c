//---------------------------------------------------------------------------------
// Bo mon Ky thuat May tinh, Vien CNTT-TT, Dai hoc Bach Khoa Ha Noi
//                                LAB 02
//---------------------------------------------------------------------------------

#include <stdio.h>
#include "brick.h"

int main()
{
	int val;
	
	printf( "Bai lab03.\n" );
	printf( "EV3 dang khoi dong...\n" );
	brick_init();
	
	if(sensor_is_plugged(IN3, LEGO_EV3_COLOR))
	{
		printf("Found color sensor!\n");
		// Thiet lap che do do anh sang phan chieu cho cam bien mau
		// Trong che do nay gia tri tra ve cua cam bien tu 0 - 100
		color_set_mode_col_reflect(IN3);
	}

	// Thiet lap che do dung cho dong co
	tacho_set_stop_action(OUTB | OUTC, TACHO_BRAKE);
	// Thiet lap toc do cho dong co
	tacho_set_duty_cycle_sp(OUTB | OUTC, 50);
	// Ra lenh cho dong co hoat dong
	tacho_run_direct(OUTB | OUTC);
	
	while(1)
	{
		// Lay gia tri tu cam bien mau
		val = sensor_get_value(0, IN3, 0);
		// In gia tri ra man hinh
		printf("val = %d\n", val);
		
		// Neu gia tri 
		if(val > 40)
		{
			// Giam toc do cua dong co ben trai (OUTB) de quay sang ben trai
			tacho_set_duty_cycle_sp(OUTB, 10);
			tacho_set_duty_cycle_sp(OUTC, 50);
		}
		else
		{
			// Giam toc do cua dong co ben phai (OUTC) de quay sang ben phai
			tacho_set_duty_cycle_sp(OUTC, 0);
			tacho_set_duty_cycle_sp(OUTB, 50);
		}
	}
	
	brick_uninit();
	printf( "Ket thuc...\n" );
	return 0;
}