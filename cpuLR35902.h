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
	// CPU instructions (counted 73)

	// ===== REGISTERS =====
	// Accumulator and flags
	uint16_t af   = 0x0000; 
	// The below 3 registers are general purpose 16 bit registers, 
	// or they can be used as 2 separate 8 bit registers
	uint16_t bc   = 0x0000; // High: B / LOW: C 
	uint16_t de   = 0x0000; // High: D / LOW: E
	uint16_t hl   = 0x0000; // High: H / LOW: L
	// Procedural registers
	uint16_t stkp = 0x0000; // stack pointer
	uint16_t pc   = 0x0000; // program counter

	void irq();
	void nmi();
	void clock();

	void ConnectBus(Bus* n) { bus = n; }

	// lower 8 bits of AF register
	// upper nibble is the flags, lower nibble is always 0x0
	enum FLAGS35902
	{
		Z = (1 << 7), // Zero flag
		N = (1 << 6), // Subtraction flag (BCD)
		H = (1 << 5), // Half carry flag (lower 4 bit carry) (BCD)
		C = (1 << 4)  // Carry flag
	};

private:
	Bus* bus = nullptr;
	uint8_t read(uint16_t a);
	void    write(uint16_t a, uint8_t d);

	uint8_t fetch();

	struct INSTRUCTION
	{
		std::string name;
		uint8_t (cpuLR35902::* operate)(void) = nullptr;
		uint8_t (cpuLR35902::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;

private:
	// ===== CPU INSTRUCTIONS =====
	uint8_t NOP();
	uint8_t LD();
	uint8_t INC();
	uint8_t DEC();
	uint8_t ADD();
	uint8_t RLCA();
	uint8_t RRCA();
	uint8_t RLA();
	uint8_t RRA();
	uint8_t DAA();
	uint8_t CPL();
	uint8_t SCF();
	uint8_t CCF();
	uint8_t JR();
	uint8_t JR_COND();
	uint8_t STOP();
	uint8_t HALT();
	uint8_t ADDC();
	uint8_t SUB();
	uint8_t SBC();
	uint8_t AND();
	uint8_t XOR();
	uint8_t OR();
	uint8_t CP();
	uint8_t RET_COND();
	uint8_t RET();
	uint8_t RETi();
	uint8_t JP_COND();
	uint8_t JP();
	uint8_t CALL_COND();
	uint8_t CALL();
	uint8_t RST();
	uint8_t POP();
	uint8_t PUSH();
	uint8_t LDH();
	uint8_t DI();
	uint8_t EI();
	// $CB
	uint8_t RLC();
	uint8_t RRC();
	uint8_t RL();
	uint8_t RR();
	uint8_t SLA();
	uint8_t SRA();
	uint8_t SWAP();
	uint8_t SRL();
	uint8_t BIT();
	uint8_t RES();
	uint8_t SET();
	// Catch all
	uint8_t XXX();

};