#pragma once
#include <vector>
#include <string>
#include <map>

class Bus;

class cpuLR35902
{
public:
	cpuLR35902();
	~cpuLR35902();

public:
	// TODO:
	// REGISTERS
	// external event functions
	// connect to bus
	// CPU flags
	// CPU instructions

	// ===== REGISTERS =====
	// Accumulator and flags
	uint16_t af     = 0x0000; 
	// The below 3 registers are general purpose 16 bit registers, 
	// or they can be used as 2 separate 8 bit registers
	uint16_t bc     = 0x0000; // High: B / LOW: C 
	uint16_t de     = 0x0000; // High: D / LOW: E
	uint16_t hl     = 0x0000; // High: H / LOW: L
	// Procedural registers
	uint16_t stkp   = 0x0000; // stack pointer
	uint16_t pc     = 0x0000; // program counter
	uint8_t  status = 0x00; // status register
	

	void reset();
	void irq();
	void nmi();
	void clock();

	void ConnectBus(Bus* n) { bus = n; }

	// lower 8 bits of AF register
	// upper nibble is the flags, lower nibble is always 0x0
	enum FLAGS35902
	{
		C = (1 << 4), // Carry flag
		H = (1 << 5), // Half carry flag (lower 4 bit carry) (BCD)
		N = (1 << 6), // Subtraction flag (BCD)
		Z = (1 << 7)  // Zero flag
	};

private:
	uint8_t GetFlag(FLAGS35902 f);
	void    SetFlag(FLAGS35902 f, bool v);

	// Assistance variables
	uint8_t fetched      = 0x00;
	uint16_t temp        = 0x0000;
	uint16_t addr_abs    = 0x0000;
	uint16_t addr_rel    = 0x0000; // TODO: Need this?
	uint8_t opcode       = 0x00;
	uint8_t cycles       = 0x00;
	uint32_t clock_count = 0x00000000;

	Bus* bus = nullptr;
	uint8_t read(uint16_t a);
	void    write(uint16_t a, uint8_t d);

	uint8_t fetch();

	struct INSTRUCTION
	{
		std::string name;
		uint8_t (cpuLR35902::* operate)(void) = nullptr;
		
		// it doesn't seem like GB has multiple addressing modes? keeping for now just in case
		// UPDATE: THERE ARE DIFFERENT ADDRESSING MODES, AT LEAST 2 SO FAR:
		// Immediate d8: Immediate 8 bit data
		// Immediate d16: Immediate 16 bit data
		// Implied: No additional data is required, just simple stuff like changing a status bit
		// Absolute: A full 16 bit address is loaded and used
		// 
		//uint8_t (cpuLR35902::* addrmode)(void) = nullptr; // TODO TODO TODO ADD THIS TO lookup TODO TODO TODO
		
		uint8_t cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;

private:
	// ===== ADDRESSING MODES =====
	uint8_t IMP();
	uint8_t IMM();
	uint8_t ABS();

private:
	// ===== CPU INSTRUCTIONS =====
	uint8_t ADC();      uint8_t HALT();		uint8_t RETI();
	uint8_t ADD();	 	uint8_t INC();		uint8_t RLA();
	uint8_t AND();	 	uint8_t JP();		uint8_t RLCA();
	uint8_t CALL();	 	uint8_t JR();		uint8_t RRA();
	uint8_t CCF();	 	uint8_t LD();		uint8_t RRCA();
	uint8_t CP();	 	uint8_t LDH();		uint8_t RST();
	uint8_t CPL();	 	uint8_t NOP();		uint8_t SBC();
	uint8_t DAA();	 	uint8_t OR();		uint8_t SCF();
	uint8_t DEC();	 	uint8_t POP();		uint8_t STOP();
	uint8_t DI();	 	uint8_t PUSH();		uint8_t SUB();
	uint8_t EI();	 	uint8_t RET();		uint8_t XOR();

	// IDK about these 3:
	uint8_t JR_r8(); // ????????????????
	uint8_t OR_d8(); // ????????????????
	uint8_t PREFIX_CB(); // ??? This one is definitely important, how to handle this?
	
	uint8_t XXX(); // catch all for "???" instructions

};