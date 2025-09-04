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
	
public:
	// Get/Set A Register
	uint8_t GetRegA()
	{
		uint8_t reg = 0x00 | (af >> 8);
		return reg;
	}

	void SetRegA(uint8_t val)
	{
		uint16_t tmp = 0x0000 | val;
		tmp = tmp << 8;
		af = 0x00F0 & af;
		af |= tmp;
	}

	// Get/Set B Register
	uint8_t GetRegB()
	{
		uint16_t reg = (0xFF00 & bc);
		reg = reg >> 8;
		uint8_t ret = 0x00 | reg;
		return ret;
	}

	void SetRegB(uint8_t val)
	{
		uint16_t reg = 0x0000 | (val);
		reg = reg << 8;
		bc = 0x00FF & bc;
		bc = bc | reg;
	}

	// Get/Set C Register
	uint8_t GetRegC()
	{
		uint16_t reg = (0x00FF & bc);
		uint8_t ret = 0x00 | reg;
		return ret;
	}

	void SetRegC(uint8_t val)
	{
		uint16_t reg = 0x0000 | (val);
		bc = 0xFF00 & bc;
		bc = bc | reg;
	}

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
		// UPDATE: THERE ARE DIFFERENT ADDRESSING MODES, SO FAR:
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
	
	// !!!!!!!!!!!!!!!!!!!!! OLDDDDDDDDD METHOD !!!!!!!!!!!!!!!!!!!!!!!!!
	// ===== CPU INSTRUCTIONS =====
	//uint8_t ADC();      uint8_t HALT();		uint8_t RETI();
	//uint8_t ADD();	 	uint8_t INC();		uint8_t RLA();
	//uint8_t AND();	 	uint8_t JP();		uint8_t RLCA();
	//uint8_t CALL();	 	uint8_t JR();		uint8_t RRA();
	//uint8_t CCF();	 	uint8_t LD();		uint8_t RRCA();
	//uint8_t CP();	 	uint8_t LDH();		uint8_t RST();
	//uint8_t CPL();	 	uint8_t NOP();		uint8_t SBC();
	//uint8_t DAA();	 	uint8_t OR();		uint8_t SCF();
	//uint8_t DEC();	 	uint8_t POP();		uint8_t STOP();
	//uint8_t DI();	 	uint8_t PUSH();		uint8_t SUB();
	//uint8_t EI();	 	uint8_t RET();		uint8_t XOR();
	//uint8_t PREFIX_CB(); // ??? This one is definitely important, how to handle this?
	//uint8_t XXX(); // catch for all undefined opcodes

	//// IDK about these 2:
	//uint8_t JR_r8(); // ????????????????
	//uint8_t OR_d8(); // ????????????????
	

	//-o------------------------------------------------------------------o
	// |   STANDARD OPCODES                                                     |
	//-o------------------------------------------------------------------o
	uint8_t OP_00(); uint8_t OP_10(); uint8_t OP_20(); uint8_t OP_30();	uint8_t OP_40(); uint8_t OP_50(); uint8_t OP_60(); uint8_t OP_70();
	uint8_t OP_01(); uint8_t OP_11(); uint8_t OP_21(); uint8_t OP_31();	uint8_t OP_41(); uint8_t OP_51(); uint8_t OP_61(); uint8_t OP_71();
	uint8_t OP_02(); uint8_t OP_12(); uint8_t OP_22(); uint8_t OP_32();	uint8_t OP_42(); uint8_t OP_52(); uint8_t OP_62(); uint8_t OP_72();
	uint8_t OP_03(); uint8_t OP_13(); uint8_t OP_23(); uint8_t OP_33();	uint8_t OP_43(); uint8_t OP_53(); uint8_t OP_63(); uint8_t OP_73();
	uint8_t OP_04(); uint8_t OP_14(); uint8_t OP_24(); uint8_t OP_34();	uint8_t OP_44(); uint8_t OP_54(); uint8_t OP_64(); uint8_t OP_74();
	uint8_t OP_05(); uint8_t OP_15(); uint8_t OP_25(); uint8_t OP_35();	uint8_t OP_45(); uint8_t OP_55(); uint8_t OP_65(); uint8_t OP_75();
	uint8_t OP_06(); uint8_t OP_16(); uint8_t OP_26(); uint8_t OP_36();	uint8_t OP_46(); uint8_t OP_56(); uint8_t OP_66(); uint8_t OP_76();
	uint8_t OP_07(); uint8_t OP_17(); uint8_t OP_27(); uint8_t OP_37();	uint8_t OP_47(); uint8_t OP_57(); uint8_t OP_67(); uint8_t OP_77();
	uint8_t OP_08(); uint8_t OP_18(); uint8_t OP_28(); uint8_t OP_38();	uint8_t OP_48(); uint8_t OP_58(); uint8_t OP_68(); uint8_t OP_78();
	uint8_t OP_09(); uint8_t OP_19(); uint8_t OP_29(); uint8_t OP_39();	uint8_t OP_49(); uint8_t OP_59(); uint8_t OP_69(); uint8_t OP_79();
	uint8_t OP_0A(); uint8_t OP_1A(); uint8_t OP_2A(); uint8_t OP_3A();	uint8_t OP_4A(); uint8_t OP_5A(); uint8_t OP_6A(); uint8_t OP_7A();
	uint8_t OP_0B(); uint8_t OP_1B(); uint8_t OP_2B(); uint8_t OP_3B();	uint8_t OP_4B(); uint8_t OP_5B(); uint8_t OP_6B(); uint8_t OP_7B();
	uint8_t OP_0C(); uint8_t OP_1C(); uint8_t OP_2C(); uint8_t OP_3C();	uint8_t OP_4C(); uint8_t OP_5C(); uint8_t OP_6C(); uint8_t OP_7C();
	uint8_t OP_0D(); uint8_t OP_1D(); uint8_t OP_2D(); uint8_t OP_3D();	uint8_t OP_4D(); uint8_t OP_5D(); uint8_t OP_6D(); uint8_t OP_7D();
	uint8_t OP_0E(); uint8_t OP_1E(); uint8_t OP_2E(); uint8_t OP_3E();	uint8_t OP_4E(); uint8_t OP_5E(); uint8_t OP_6E(); uint8_t OP_7E();
	uint8_t OP_0F(); uint8_t OP_1F(); uint8_t OP_2F(); uint8_t OP_3F();	uint8_t OP_4F(); uint8_t OP_5F(); uint8_t OP_6F(); uint8_t OP_7F();
					 
					 
	uint8_t OP_80(); uint8_t OP_90(); uint8_t OP_A0(); uint8_t OP_B0();	uint8_t OP_C0(); uint8_t OP_D0(); uint8_t OP_E0(); uint8_t OP_F0();
	uint8_t OP_81(); uint8_t OP_91(); uint8_t OP_A1(); uint8_t OP_B1();	uint8_t OP_C1(); uint8_t OP_D1(); uint8_t OP_E1(); uint8_t OP_F1();
	uint8_t OP_82(); uint8_t OP_92(); uint8_t OP_A2(); uint8_t OP_B2();	uint8_t OP_C2(); uint8_t OP_D2(); uint8_t OP_E2(); uint8_t OP_F2();
	uint8_t OP_83(); uint8_t OP_93(); uint8_t OP_A3(); uint8_t OP_B3();	uint8_t OP_C3(); uint8_t OP_D3(); uint8_t OP_E3(); uint8_t OP_F3();
	uint8_t OP_84(); uint8_t OP_94(); uint8_t OP_A4(); uint8_t OP_B4();	uint8_t OP_C4(); uint8_t OP_D4(); uint8_t OP_E4(); uint8_t OP_F4();
	uint8_t OP_85(); uint8_t OP_95(); uint8_t OP_A5(); uint8_t OP_B5();	uint8_t OP_C5(); uint8_t OP_D5(); uint8_t OP_E5(); uint8_t OP_F5();
	uint8_t OP_86(); uint8_t OP_96(); uint8_t OP_A6(); uint8_t OP_B6();	uint8_t OP_C6(); uint8_t OP_D6(); uint8_t OP_E6(); uint8_t OP_F6();
	uint8_t OP_87(); uint8_t OP_97(); uint8_t OP_A7(); uint8_t OP_B7();	uint8_t OP_C7(); uint8_t OP_D7(); uint8_t OP_E7(); uint8_t OP_F7();
	uint8_t OP_88(); uint8_t OP_98(); uint8_t OP_A8(); uint8_t OP_B8();	uint8_t OP_C8(); uint8_t OP_D8(); uint8_t OP_E8(); uint8_t OP_F8();
	uint8_t OP_89(); uint8_t OP_99(); uint8_t OP_A9(); uint8_t OP_B9();	uint8_t OP_C9(); uint8_t OP_D9(); uint8_t OP_E9(); uint8_t OP_F9();
	uint8_t OP_8A(); uint8_t OP_9A(); uint8_t OP_AA(); uint8_t OP_BA();	uint8_t OP_CA(); uint8_t OP_DA(); uint8_t OP_EA(); uint8_t OP_FA();
	uint8_t OP_8B(); uint8_t OP_9B(); uint8_t OP_AB(); uint8_t OP_BB();	uint8_t OP_CB(); uint8_t OP_DB(); uint8_t OP_EB(); uint8_t OP_FB();
	uint8_t OP_8C(); uint8_t OP_9C(); uint8_t OP_AC(); uint8_t OP_BC();	uint8_t OP_CC(); uint8_t OP_DC(); uint8_t OP_EC(); uint8_t OP_FC();
	uint8_t OP_8D(); uint8_t OP_9D(); uint8_t OP_AD(); uint8_t OP_BD();	uint8_t OP_CD(); uint8_t OP_DD(); uint8_t OP_ED(); uint8_t OP_FD();
	uint8_t OP_8E(); uint8_t OP_9E(); uint8_t OP_AE(); uint8_t OP_BE();	uint8_t OP_CE(); uint8_t OP_DE(); uint8_t OP_EE(); uint8_t OP_FE();
	uint8_t OP_8F(); uint8_t OP_9F(); uint8_t OP_AF(); uint8_t OP_BF();	uint8_t OP_CF(); uint8_t OP_DF(); uint8_t OP_EF(); uint8_t OP_FF();


	//-o------------------------------------------------------------------o
	// |   CB OPCODES                                                     |
	//-o------------------------------------------------------------------o
	uint8_t OP_CB_00(); uint8_t OP_CB_10(); uint8_t OP_CB_20(); uint8_t OP_CB_30(); uint8_t OP_CB_40();	uint8_t OP_CB_50();	uint8_t OP_CB_60();	uint8_t OP_CB_70();
	uint8_t OP_CB_01(); uint8_t OP_CB_11(); uint8_t OP_CB_21(); uint8_t OP_CB_31(); uint8_t OP_CB_41();	uint8_t OP_CB_51();	uint8_t OP_CB_61();	uint8_t OP_CB_71();
	uint8_t OP_CB_02(); uint8_t OP_CB_12(); uint8_t OP_CB_22(); uint8_t OP_CB_32(); uint8_t OP_CB_42();	uint8_t OP_CB_52();	uint8_t OP_CB_62();	uint8_t OP_CB_72();
	uint8_t OP_CB_03(); uint8_t OP_CB_13(); uint8_t OP_CB_23(); uint8_t OP_CB_33(); uint8_t OP_CB_43();	uint8_t OP_CB_53();	uint8_t OP_CB_63();	uint8_t OP_CB_73();
	uint8_t OP_CB_04(); uint8_t OP_CB_14(); uint8_t OP_CB_24(); uint8_t OP_CB_34(); uint8_t OP_CB_44();	uint8_t OP_CB_54();	uint8_t OP_CB_64();	uint8_t OP_CB_74();
	uint8_t OP_CB_05(); uint8_t OP_CB_15(); uint8_t OP_CB_25(); uint8_t OP_CB_35(); uint8_t OP_CB_45();	uint8_t OP_CB_55();	uint8_t OP_CB_65();	uint8_t OP_CB_75();
	uint8_t OP_CB_06(); uint8_t OP_CB_16(); uint8_t OP_CB_26(); uint8_t OP_CB_36(); uint8_t OP_CB_46();	uint8_t OP_CB_56();	uint8_t OP_CB_66();	uint8_t OP_CB_76();
	uint8_t OP_CB_07(); uint8_t OP_CB_17(); uint8_t OP_CB_27(); uint8_t OP_CB_37(); uint8_t OP_CB_47();	uint8_t OP_CB_57();	uint8_t OP_CB_67();	uint8_t OP_CB_77();
	uint8_t OP_CB_08(); uint8_t OP_CB_18(); uint8_t OP_CB_28(); uint8_t OP_CB_38(); uint8_t OP_CB_48();	uint8_t OP_CB_58();	uint8_t OP_CB_68();	uint8_t OP_CB_78();
	uint8_t OP_CB_09(); uint8_t OP_CB_19(); uint8_t OP_CB_29(); uint8_t OP_CB_39(); uint8_t OP_CB_49();	uint8_t OP_CB_59();	uint8_t OP_CB_69();	uint8_t OP_CB_79();
	uint8_t OP_CB_0A(); uint8_t OP_CB_1A(); uint8_t OP_CB_2A(); uint8_t OP_CB_3A(); uint8_t OP_CB_4A();	uint8_t OP_CB_5A();	uint8_t OP_CB_6A();	uint8_t OP_CB_7A();
	uint8_t OP_CB_0B(); uint8_t OP_CB_1B(); uint8_t OP_CB_2B(); uint8_t OP_CB_3B(); uint8_t OP_CB_4B();	uint8_t OP_CB_5B();	uint8_t OP_CB_6B();	uint8_t OP_CB_7B();
	uint8_t OP_CB_0C(); uint8_t OP_CB_1C(); uint8_t OP_CB_2C(); uint8_t OP_CB_3C(); uint8_t OP_CB_4C();	uint8_t OP_CB_5C();	uint8_t OP_CB_6C();	uint8_t OP_CB_7C();
	uint8_t OP_CB_0D(); uint8_t OP_CB_1D(); uint8_t OP_CB_2D(); uint8_t OP_CB_3D(); uint8_t OP_CB_4D();	uint8_t OP_CB_5D();	uint8_t OP_CB_6D();	uint8_t OP_CB_7D();
	uint8_t OP_CB_0E(); uint8_t OP_CB_1E(); uint8_t OP_CB_2E(); uint8_t OP_CB_3E(); uint8_t OP_CB_4E();	uint8_t OP_CB_5E();	uint8_t OP_CB_6E();	uint8_t OP_CB_7E();
	uint8_t OP_CB_0F(); uint8_t OP_CB_1F(); uint8_t OP_CB_2F(); uint8_t OP_CB_3F(); uint8_t OP_CB_4F();	uint8_t OP_CB_5F();	uint8_t OP_CB_6F();	uint8_t OP_CB_7F();


	uint8_t OP_CB_80();	uint8_t OP_CB_90();	uint8_t OP_CB_A0();	uint8_t OP_CB_B0();	uint8_t OP_CB_C0();	uint8_t OP_CB_D0();	uint8_t OP_CB_E0();	uint8_t OP_CB_F0();
	uint8_t OP_CB_81();	uint8_t OP_CB_91();	uint8_t OP_CB_A1();	uint8_t OP_CB_B1();	uint8_t OP_CB_C1();	uint8_t OP_CB_D1();	uint8_t OP_CB_E1();	uint8_t OP_CB_F1();
	uint8_t OP_CB_82();	uint8_t OP_CB_92();	uint8_t OP_CB_A2();	uint8_t OP_CB_B2();	uint8_t OP_CB_C2();	uint8_t OP_CB_D2();	uint8_t OP_CB_E2();	uint8_t OP_CB_F2();
	uint8_t OP_CB_83();	uint8_t OP_CB_93();	uint8_t OP_CB_A3();	uint8_t OP_CB_B3();	uint8_t OP_CB_C3();	uint8_t OP_CB_D3();	uint8_t OP_CB_E3();	uint8_t OP_CB_F3();
	uint8_t OP_CB_84();	uint8_t OP_CB_94();	uint8_t OP_CB_A4();	uint8_t OP_CB_B4();	uint8_t OP_CB_C4();	uint8_t OP_CB_D4();	uint8_t OP_CB_E4();	uint8_t OP_CB_F4();
	uint8_t OP_CB_85();	uint8_t OP_CB_95();	uint8_t OP_CB_A5();	uint8_t OP_CB_B5();	uint8_t OP_CB_C5();	uint8_t OP_CB_D5();	uint8_t OP_CB_E5();	uint8_t OP_CB_F5();
	uint8_t OP_CB_86();	uint8_t OP_CB_96();	uint8_t OP_CB_A6();	uint8_t OP_CB_B6();	uint8_t OP_CB_C6();	uint8_t OP_CB_D6();	uint8_t OP_CB_E6();	uint8_t OP_CB_F6();
	uint8_t OP_CB_87();	uint8_t OP_CB_97();	uint8_t OP_CB_A7();	uint8_t OP_CB_B7();	uint8_t OP_CB_C7();	uint8_t OP_CB_D7();	uint8_t OP_CB_E7();	uint8_t OP_CB_F7();
	uint8_t OP_CB_88();	uint8_t OP_CB_98();	uint8_t OP_CB_A8();	uint8_t OP_CB_B8();	uint8_t OP_CB_C8();	uint8_t OP_CB_D8();	uint8_t OP_CB_E8();	uint8_t OP_CB_F8();
	uint8_t OP_CB_89();	uint8_t OP_CB_99();	uint8_t OP_CB_A9();	uint8_t OP_CB_B9();	uint8_t OP_CB_C9();	uint8_t OP_CB_D9();	uint8_t OP_CB_E9();	uint8_t OP_CB_F9();
	uint8_t OP_CB_8A();	uint8_t OP_CB_9A();	uint8_t OP_CB_AA();	uint8_t OP_CB_BA();	uint8_t OP_CB_CA();	uint8_t OP_CB_DA();	uint8_t OP_CB_EA();	uint8_t OP_CB_FA();
	uint8_t OP_CB_8B();	uint8_t OP_CB_9B();	uint8_t OP_CB_AB();	uint8_t OP_CB_BB();	uint8_t OP_CB_CB();	uint8_t OP_CB_DB();	uint8_t OP_CB_EB();	uint8_t OP_CB_FB();
	uint8_t OP_CB_8C();	uint8_t OP_CB_9C();	uint8_t OP_CB_AC();	uint8_t OP_CB_BC();	uint8_t OP_CB_CC();	uint8_t OP_CB_DC();	uint8_t OP_CB_EC();	uint8_t OP_CB_FC();
	uint8_t OP_CB_8D();	uint8_t OP_CB_9D();	uint8_t OP_CB_AD();	uint8_t OP_CB_BD();	uint8_t OP_CB_CD();	uint8_t OP_CB_DD();	uint8_t OP_CB_ED();	uint8_t OP_CB_FD();
	uint8_t OP_CB_8E();	uint8_t OP_CB_9E();	uint8_t OP_CB_AE();	uint8_t OP_CB_BE();	uint8_t OP_CB_CE();	uint8_t OP_CB_DE();	uint8_t OP_CB_EE();	uint8_t OP_CB_FE();
	uint8_t OP_CB_8F();	uint8_t OP_CB_9F();	uint8_t OP_CB_AF();	uint8_t OP_CB_BF();	uint8_t OP_CB_CF();	uint8_t OP_CB_DF();	uint8_t OP_CB_EF();	uint8_t OP_CB_FF();











};