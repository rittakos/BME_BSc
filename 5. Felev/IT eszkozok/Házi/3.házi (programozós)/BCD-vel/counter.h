
#pragma once
#include <systemc.h>

SC_MODULE(counter4) // az SC_MODULE makró az sc_module osztályból származtat
{
	sc_in<bool>		reset;
	sc_in<bool>		clk;
	sc_out<sc_uint<8> >	output;	
	sc_out<bool>		tc;

	sc_uint<8>		count;
	sc_uint<8>		carry;


	void	do_count()
	{
		
		if (reset.read() == 0)
			count = 0;
		else 
			if (count%10 == 9) {
				//59 esetén nullázuk az órát
				if (count + carry == 0x59) {
					count = 0;
					carry = 0;
					tc = false;
				}

				else {
				carry += 16;
				count = 0;
				}
			}
			else{
				count++;
				if (count + carry == 0x59) tc = true;
				else tc=false;
			}
			

		output.write(count+carry);
	}

	// a konstruktorban adjuk meg a mûködést leíró metódust
	// és az érzékenységi listát (vö. Verilog always, VHDL PROCESS)
	SC_CTOR(counter4)
	{
		SC_METHOD(do_count);
		// az órajel felfutó élére vagy a reset lefutó élére lesz érzékeny
		sensitive << clk.pos() << reset.neg();	
	}
};

