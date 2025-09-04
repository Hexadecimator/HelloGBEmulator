#include "cpuLR35902.h"
#include "Bus.h"

cpuLR35902::cpuLR35902()
{
	using a = cpuLR35902;
	lookup =
	{
		// TODO: Some cycles are in the form "12/8" or similar... figure this out. Probably handle this in the op code's function
		// only doing 1 row for now to figure things out
		{"NOP", &a::OP_00, 4},{"LD BC,d16", &a::OP_01, 12},{"LD (BC),A", &a::OP_02, 8},{"INC BC", &a::OP_03, 8},{"INC B", &a::OP_04, 4},{"DEC B", &a::OP_05, 4},{"LD B,d8", &a::OP_06, 8},{"RLCA", &a::OP_07, 4},{"LD (a16), SP", &a::OP_08, 20},{"ADD HL,BC", &a::OP_09, 8},{"LD A,(BC)", &a::OP_0A, 8},{"DEC BC", &a::OP_0B, 8},{"INC C", &a::OP_0C, 4},{"DEC C", &a::OP_0D, 4},{"LD C,d8", &a::OP_0E, 8},{"RRCA", &a::OP_0F, 4},
		{"STOP", &a::OP_10, 4},{"LD DE,d16", &a::OP_11, 12},{"LD (DE),A", &a::OP_12, 8},{"INC DE", &a::OP_13, 8},{"INC D", &a::OP_14, 4},{"DEC D", &a::OP_15, 4},{"LD D,d8", &a::OP_16, 8},{"RLA", &a::OP_17, 4},{"JR r8", &a::OP_18, 12},{"ADD HL,DE", &a::OP_19, 8},{"LD A,(DE)", &a::OP_1A, 8},{"DEC DE", &a::OP_1B, 8},{"INC E", &a::OP_1C, 4},{"DEC E", &a::OP_1D, 4},{"LD E,d8", &a::OP_1E, 8},{"RRA", &a::OP_1F, 4},
		{"JR NZ,r8", &a::OP_20, 12/8},{"LD HL,d16", &a::OP_21, 12},{"LD (HL+),A", &a::OP_22, 8},{"INC HL", &a::OP_23, 8},{"INC H", &a::OP_24, 4},{"DEC H", &a::OP_25, 4},{"LD H,d8", &a::OP_26, 8},{"DAA", &a::OP_27, 4},{"JR Z,r8", &a::OP_28, 12/8},{"ADD HL,HL", &a::OP_29, 8},{"LD A,(HL+)", &a::OP_2A, 8},{"DEC HL", &a::OP_2B, 8},{"INC L", &a::OP_2C, 4},{"DEC L", &a::OP_2D, 4},{"LD L,d8", &a::OP_2E, 8},{"CPL", &a::OP_2F, 4},
		{"JR NC,r8", &a::OP_30, 12/8},{"LD SP,d16", &a::OP_31, 16},{"LD (HL-),A", &a::OP_32, 8},{"INC SP", &a::OP_33, 8},{"INC (HL)", &a::OP_34, 12},{"DEC (HL)", &a::OP_35, 12},{"LD (HL),d8", &a::OP_36, 12},{"SCF", &a::OP_37, 4},{"JR C,r8", &a::OP_38, 12/8},{"ADD HL,SP", &a::OP_39, 8},{"LD A,(HL-)", &a::OP_3A, 8},{"DEC SP", &a::OP_3B, 8},{"INC A", &a::OP_3C, 4},{"DEC A", &a::OP_3D, 4},{"LD A,d8", &a::OP_3E, 8},{"CCF", &a::OP_3F, 4},
		{"LD B,B", &a::OP_40, 4},{"LD B,C", &a::OP_41, 4},{"LD B,D", &a::OP_42, 4},{"LD B,E", &a::OP_43, 4},{"LD B,H", &a::OP_44, 4},{"LD B,L", &a::OP_45, 4},{"LD B,(HL)", &a::OP_46, 8},{"LD B,A", &a::OP_47, 4},{"LD C,B", &a::OP_48, 4},{"LD C,C", &a::OP_49, 4},{"LD C,D", &a::OP_4A, 4},{"LD C,E", &a::OP_4B, 4},{"LD C,H", &a::OP_4C, 4},{"LD C,L", &a::OP_4D, 4},{"LD C,(HL)", &a::OP_4E, 8},{"LD C,A", &a::OP_4F, 4},
		{"LD D,B", &a::OP_50, 4},{"LD D,C", &a::OP_51, 4},{"LD D,D", &a::OP_52, 4},{"LD D,E", &a::OP_53, 4},{"LD D,H", &a::OP_54, 4},{"LD D,L", &a::OP_55, 4},{"LD D,(HL)", &a::OP_56, 8},{"LD D,A", &a::OP_57, 4},{"LD E,B", &a::OP_58, 4},{"LD E,C", &a::OP_59, 4},{"LD E,D", &a::OP_5A, 4},{"LD E,E", &a::OP_5B, 4},{"LD E,H", &a::OP_5C, 4},{"LD E,L", &a::OP_5D, 4},{"LD E,(HL)", &a::OP_5E, 4},{"LD E,A", &a::OP_5F, 4},
		{"LD H,B", &a::OP_60, 4},{"LD H,C", &a::OP_61, 4},{"LD H,D", &a::OP_62, 4},{"LD H,E", &a::OP_63, 4},{"LD H,H", &a::OP_64, 4},{"LD H,L", &a::OP_65, 4},{"LD H,(HL)", &a::OP_66, 8},{"LD H,A", &a::OP_67, 4},{"LD L,B", &a::OP_68, 4},{"LD L,C", &a::OP_69, 4},{"LD L,D", &a::OP_6A, 4},{"LD L,E", &a::OP_6B, 4},{"LD L,H", &a::OP_6C, 4},{"LD L,L", &a::OP_6D, 4},{"LD L,(HL)", &a::OP_6E, 8},{"LD L,A", &a::OP_6F, 4},
		{"LD (HL),B", &a::OP_70, 8},{"LD (HL),C", &a::OP_71, 8},{"LD (HL),D", &a::OP_72, 8},{"LD (HL),E", &a::OP_73, 8},{"LD (HL),H", &a::OP_74, 8},{"LD (HL),L", &a::OP_75, 8},{"HALT", &a::OP_76, 4},{"LD (HL),A", &a::OP_77, 8},{"LD A,B", &a::OP_78, 4},{"LD A,C", &a::OP_79, 4},{"LD A,D", &a::OP_7A, 4},{"LD A,E", &a::OP_7B, 4},{"LD A,H", &a::OP_7C, 4},{"LD A,L", &a::OP_7D, 4},{"LD A,(HL)", &a::OP_7E, 8},{"LD A,A", &a::OP_7F, 4},
		{"ADD A,B", &a::OP_80, 4},{"ADD A,C", &a::OP_81, 4},{"ADD A,D", &a::OP_82, 4},{"ADD A,E", &a::OP_83, 4},{"ADD A,H", &a::OP_84, 4},{"ADD A,L", &a::OP_85, 4},{"ADD A,(HL)", &a::OP_86, 8},{"ADD A,A", &a::OP_87, 4},{"ADC A,B", &a::OP_88, 4},{"ADC A,C", &a::OP_89, 4},{"ADC A,D", &a::OP_8A, 4},{"ADC A,E", &a::OP_8B, 4},{"ADC A,H", &a::OP_8C, 4},{"ADC A,L", &a::OP_8D, 4},{"ADC A,(HL)", &a::OP_8E, 8},{"ADC A,A", &a::OP_8F, 4},
		{"SUB B", &a::OP_90, 4},{"SUB C", &a::OP_91, 4},{"SUB D", &a::OP_92, 4},{"SUB E", &a::OP_93, 4},{"SUB H", &a::OP_94, 4},{"SUB L", &a::OP_95, 4},{"SUB (HL)", &a::OP_96, 8},{"SUB A", &a::OP_97, 4},{"SBC A,B", &a::OP_98, 4},{"SBC A,C", &a::OP_99, 4},{"SBC A,D", &a::OP_9A, 4},{"SBC A,E", &a::OP_9B, 4},{"SBC A,H", &a::OP_9C, 4},{"SBC A,L", &a::OP_9D, 4},{"SBC A,(HL)", &a::OP_9E, 8},{"SBC A,A", &a::OP_9F, 4},
		{"AND B", &a::OP_A0, 4},{"AND C", &a::OP_A1, 4},{"AND D", &a::OP_A2, 4},{"AND E", &a::OP_A3, 4},{"AND H", &a::OP_A4, 4},{"AND L", &a::OP_A5, 4},{"AND (HL)", &a::OP_A6, 8},{"AND A", &a::OP_A7, 4},{"XOR B", &a::OP_A8, 4},{"XOR C", &a::OP_A9, 4},{"XOR D", &a::OP_AA, 4},{"XOR E", &a::OP_AB, 4},{"XOR H", &a::OP_AC, 4},{"XOR L", &a::OP_AD, 4},{"XOR (HL)", &a::OP_AE, 8},{"XOR A", &a::OP_AF, 4},
		{"OR B", &a::OP_B0, 4},{"OR C", &a::OP_B1, 4},{"OR D", &a::OP_B2, 4},{"OR E", &a::OP_B3, 4},{"OR H", &a::OP_B4, 4},{"OR L", &a::OP_B5, 4},{"OR (HL)", &a::OP_B6, 8},{"OR A", &a::OP_B7, 4},{"CP B", &a::OP_B8, 4},{"CP C", &a::OP_B9, 4},{"CP D", &a::OP_BA, 4},{"CP E", &a::OP_BB, 4},{"CP H", &a::OP_BC, 4},{"CP L", &a::OP_BD, 4},{"CP (HL)", &a::OP_BE, 8},{"CP A", &a::OP_BF, 4},
		{"RET NZ", &a::OP_C0, 20/8},{"POP BC", &a::OP_C1, 12},{"JP NZ,a16", &a::OP_C2, 16/12},{"JP a16", &a::OP_C3, 16},{"CALL NZ,a16", &a::OP_C4, 24/12},{"PUSH BC", &a::OP_C5, 16},{"ADD A,d8", &a::OP_C6, 8},{"RST 00H", &a::OP_C7, 16},{"RET Z", &a::OP_C8, 20/8},{"RET", &a::OP_C9, 16},{"JP Z,a16", &a::OP_CA, 16/12},{"PREFIX CB", &a::OP_CB, 4},{"CALL Z,a16", &a::OP_CC, 24/12},{"CALL a16", &a::OP_CD, 24},{"ADC A,d8", &a::OP_CE, 8},{"RST 08H", &a::OP_CF, 16},
		{"RET NC", &a::OP_D0, 20/8},{"POP DE", &a::OP_D1, 12},{"JP NC,a16", &a::OP_D2, 16/12},{"???", &a::OP_D3, 1},{"CALL NC,a16", &a::OP_D4, 24/12},{"PUSH DE", &a::OP_D5, 16},{"SUB d8", &a::OP_D6, 8},{"RST 10H", &a::OP_D7, 16},{"RET C", &a::OP_D8, 20/8},{"RETI", &a::OP_D9, 16},{"JP C,a16", &a::OP_DA, 16/12},{"???", &a::OP_DB, 1},{"CALL C,a16", &a::OP_DC, 24/12},{"???", &a::OP_DD, 1},{"SBC A,d8", &a::OP_DE, 8},{"RST 18H", &a::OP_DF, 16},
		{"LDH (a8),A", &a::OP_E0, 12},{"POP HL", &a::OP_E1, 12},{"LD (C),A", &a::OP_E2, 8},{"???", &a::OP_E3, 1},{"???", &a::OP_E4, 1},{"PUSH HL", &a::OP_E5, 16},{"AND d8", &a::OP_E6, 8},{"RST 20H", &a::OP_E7, 16},{"ADD SP,r8", &a::OP_E8, 16},{"JP (HL)", &a::OP_E9, 4},{"LD (a16),A", &a::OP_EA, 16},{"???", &a::OP_EB, 1},{"???", &a::OP_EC, 1},{"???", &a::OP_ED, 1},{"XOR d8", &a::OP_EE, 8},{"RST 28H", &a::OP_EF, 16},
		{"LDH A,(a8)", &a::OP_F0, 12},{"POP AF", &a::OP_F1, 12},{"LD A,(C)", &a::OP_F2, 8},{"DI", &a::OP_F3, 4},{"???", &a::OP_F4, 1},{"PUSH AF", &a::OP_F5, 16},{"OR d8", &a::OP_F6, 8},{"RST 30H", &a::OP_F7, 16},{"LD HL,SP+r8", &a::OP_F8, 12},{"LD SP,HL", &a::OP_F9, 8},{"LD A,(a16)", &a::OP_FA, 16},{"EI", &a::OP_FB, 4},{"???", &a::OP_FC, 1},{"???", &a::OP_FD, 1},{"CP d8", &a::OP_FE, 8},{"RST 38H", &a::OP_FF, 16}
	};
}

cpuLR35902::~cpuLR35902()
{
}

uint8_t cpuLR35902::GetFlag(FLAGS35902 f)
{
	return ((status & f) > 0) ? 1 : 0;
}

void cpuLR35902::SetFlag(FLAGS35902 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

uint8_t cpuLR35902::fetch()
{
	// TODO: INCORPORATE THE DIFFERENT ADDRESSING MODES
	fetched = read(addr_abs);

	return fetched;
}

// NOP
uint8_t cpuLR35902::OP_00()
{
	// TODO: Game compatibility may necessitate handling different
	// NOP opcodes differently, thus the switch statement
	switch (opcode)
	{
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}