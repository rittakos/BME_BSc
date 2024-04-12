/****************************************************
 Egy 4 bites felfele sz�ml�l� System-C modellje
 bemenetek: clk, reset, enable
 kimenetek: q(4)
****************************************************/
#pragma once
#include <systemc.h>

SC_MODULE(counter8) // az SC_MODULE makr� az sc_module oszt�lyb�l sz�rmaztat
{
	// a portok az oszt�ly bels� v�ltoz�i lesznek
	// digit�lis jelet szimpl�n a bool adatt�pussal, 
	// n bites el�jel n�lk�li sz�mot az sc_uint<> template
	// haszn�lat�val modellez�nk

	// input portok 
	sc_in<bool>		reset;
	sc_in<bool>		enable;
	sc_in<bool>		clk;

	// output port - 8 bites kimenet 
	sc_out<sc_uint<8> >	seconds;
	//output port- tc kimenet 1 ha seconds 60
	sc_out<bool>	tc;

	// az output port bels� regisztere
	// mag�n a porton csak a write m�velet �rtelmezett
	// a t�rol�st bels� v�ltoz�kkal kell megoldani.
	sc_uint<8>		count;
	bool tc_value;
	// itt �rjuk meg a val�di m�k�d�st. A met�dus neve tetsz�leges, a do_foobar szok�sjog
	void	do_count()
	{
		// alacsony aktiv reset
		if (reset.read() == 0)
		{
			count = 0;
			tc_value = 0;
		}
		else if (enable == true && count >= 59)
		{
			count = 0;
			
		}
		else if (enable == true) // nem kell �lland�an ki�rni, ez enable.read()-et jelent
		{
			
			count++;
		}
		if (count == 59)
		{
			tc_value = 1;
		}
		else
		{
			tc_value = 0;
		}
		
		

		seconds.write(count);
		tc.write(tc_value);
	}

	// a konstruktorban adjuk meg a m�k�d�st le�r� met�dust
	// �s az �rz�kenys�gi list�t (v�. Verilog always, VHDL PROCESS)
	SC_CTOR(counter8)
	{
		SC_METHOD(do_count);
		// az �rajel felfut� �l�re vagy a reset lefut� �l�re lesz �rz�keny
		sensitive << clk.pos() << reset.neg();	
	}
};

