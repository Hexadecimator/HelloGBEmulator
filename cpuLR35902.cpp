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
		{"", &a::OP_80, ?},{"", &a::OP_81, ?},{"", &a::OP_82, ?},{"", &a::OP_83, ?},{"", &a::OP_84, ?},{"", &a::OP_85, ?},{"", &a::OP_86, ?},{"", &a::OP_87, ?},{"", &a::OP_88, ?},{"", &a::OP_89, ?},{"", &a::OP_8A, ?},{"", &a::OP_8B, ?},{"", &a::OP_8C, ?},{"", &a::OP_8D, ?},{"", &a::OP_8E, ?},{"", &a::OP_8F, ?},
		{"", &a::OP_90, ?},{"", &a::OP_91, ?},{"", &a::OP_92, ?},{"", &a::OP_93, ?},{"", &a::OP_94, ?},{"", &a::OP_95, ?},{"", &a::OP_96, ?},{"", &a::OP_97, ?},{"", &a::OP_98, ?},{"", &a::OP_99, ?},{"", &a::OP_9A, ?},{"", &a::OP_9B, ?},{"", &a::OP_9C, ?},{"", &a::OP_9D, ?},{"", &a::OP_9E, ?},{"", &a::OP_9F, ?},
		{"", &a::OP_A0, ?},{"", &a::OP_A1, ?},{"", &a::OP_A2, ?},{"", &a::OP_A3, ?},{"", &a::OP_A4, ?},{"", &a::OP_A5, ?},{"", &a::OP_A6, ?},{"", &a::OP_A7, ?},{"", &a::OP_A8, ?},{"", &a::OP_A9, ?},{"", &a::OP_AA, ?},{"", &a::OP_AB, ?},{"", &a::OP_AC, ?},{"", &a::OP_AD, ?},{"", &a::OP_AE, ?},{"", &a::OP_AF, ?},
		{"", &a::OP_B0, ?},{"", &a::OP_B1, ?},{"", &a::OP_B2, ?},{"", &a::OP_B3, ?},{"", &a::OP_B4, ?},{"", &a::OP_B5, ?},{"", &a::OP_B6, ?},{"", &a::OP_B7, ?},{"", &a::OP_B8, ?},{"", &a::OP_B9, ?},{"", &a::OP_BA, ?},{"", &a::OP_BB, ?},{"", &a::OP_BC, ?},{"", &a::OP_BD, ?},{"", &a::OP_BE, ?},{"", &a::OP_BF, ?},
		{"", &a::OP_C0, ?},{"", &a::OP_C1, ?},{"", &a::OP_C2, ?},{"", &a::OP_C3, ?},{"", &a::OP_C4, ?},{"", &a::OP_C5, ?},{"", &a::OP_C6, ?},{"", &a::OP_C7, ?},{"", &a::OP_C8, ?},{"", &a::OP_C9, ?},{"", &a::OP_CA, ?},{"", &a::OP_CB, ?},{"", &a::OP_CC, ?},{"", &a::OP_CD, ?},{"", &a::OP_CE, ?},{"", &a::OP_CF, ?},
		{"", &a::OP_D0, ?},{"", &a::OP_D1, ?},{"", &a::OP_D2, ?},{"", &a::OP_D3, ?},{"", &a::OP_D4, ?},{"", &a::OP_D5, ?},{"", &a::OP_D6, ?},{"", &a::OP_D7, ?},{"", &a::OP_D8, ?},{"", &a::OP_D9, ?},{"", &a::OP_DA, ?},{"", &a::OP_DB, ?},{"", &a::OP_DC, ?},{"", &a::OP_DD, ?},{"", &a::OP_DE, ?},{"", &a::OP_DF, ?},
		{"", &a::OP_E0, ?},{"", &a::OP_E1, ?},{"", &a::OP_E2, ?},{"", &a::OP_E3, ?},{"", &a::OP_E4, ?},{"", &a::OP_E5, ?},{"", &a::OP_E6, ?},{"", &a::OP_E7, ?},{"", &a::OP_E8, ?},{"", &a::OP_E9, ?},{"", &a::OP_EA, ?},{"", &a::OP_EB, ?},{"", &a::OP_EC, ?},{"", &a::OP_ED, ?},{"", &a::OP_EE, ?},{"", &a::OP_EF, ?},
		{"", &a::OP_F0, ?},{"", &a::OP_F1, ?},{"", &a::OP_F2, ?},{"", &a::OP_F3, ?},{"", &a::OP_F4, ?},{"", &a::OP_F5, ?},{"", &a::OP_F6, ?},{"", &a::OP_F7, ?},{"", &a::OP_F8, ?},{"", &a::OP_F9, ?},{"", &a::OP_FA, ?},{"", &a::OP_FB, ?},{"", &a::OP_FC, ?},{"", &a::OP_FD, ?},{"", &a::OP_FE, ?},{"", &a::OP_FF, ?}
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