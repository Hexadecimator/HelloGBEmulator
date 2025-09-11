#include "headers/cpuLR35902.h"
#include "headers/Bus.h"


cpuLR35902::cpuLR35902()
{
	using a = cpuLR35902;
	lookup =
	{
		// TODO: Some cycles are in the form "12/8" or similar... figure this out. Probably handle this in the op code's function
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

	cb_lookup =
	{
		{"RLC B", &a::OP_CB_00, 8},{"RLC C", &a::OP_CB_01, 8},{"RLC D", &a::OP_CB_02, 8},{"RLC E", &a::OP_CB_03, 8},{"RLC H", &a::OP_CB_04, 8},{"RLC L", &a::OP_CB_05, 8},{"RLC (HL)", &a::OP_CB_06, 16},{"RLC A", &a::OP_CB_07, 8},{"RRC B", &a::OP_CB_08, 8},{"RRC C", &a::OP_CB_09, 8},{"RRC D", &a::OP_CB_0A, 8},{"RRC E", &a::OP_CB_0B, 8},{"RRC H", &a::OP_CB_0C, 8},{"RRC L", &a::OP_CB_0D, 8},{"RRC (HL)", &a::OP_CB_0E, 16},{"RRC A", &a::OP_CB_0F, 8},
		{"RL B", &a::OP_CB_10, 8},{"RL C", &a::OP_CB_11, 8},{"RL D", &a::OP_CB_12, 8},{"RL E", &a::OP_CB_13, 8},{"RL H", &a::OP_CB_14, 8},{"RL L", &a::OP_CB_15, 8},{"RL (HL)", &a::OP_CB_16, 16},{"RL A", &a::OP_CB_17, 8},{"RR B", &a::OP_CB_18, 8},{"RR C", &a::OP_CB_19, 8},{"RR D", &a::OP_CB_1A, 8},{"RR E", &a::OP_CB_1B, 8},{"RR H", &a::OP_CB_1C, 8},{"RR L", &a::OP_CB_1D, 8},{"RR (HL)", &a::OP_CB_1E, 16},{"RR A", &a::OP_CB_1F, 8},
		{"SLA B", &a::OP_CB_20, 8},{"SLA C", &a::OP_CB_21, 8},{"SLA D", &a::OP_CB_22, 8},{"SLA E", &a::OP_CB_23, 8},{"SLA H", &a::OP_CB_24, 8},{"SLA L", &a::OP_CB_25, 8},{"SLA (HL)", &a::OP_CB_26, 16},{"SLA A", &a::OP_CB_27, 8},{"SRA B", &a::OP_CB_28, 8},{"SRA C", &a::OP_CB_29, 8},{"SRA D", &a::OP_CB_2A, 8},{"SRA E", &a::OP_CB_2B, 8},{"SRA H", &a::OP_CB_2C, 8},{"SRA L", &a::OP_CB_2D, 8},{"SRA (HL)", &a::OP_CB_2E, 16},{"SRA A", &a::OP_CB_2F, 8},
		{"SWAP B", &a::OP_CB_30, 8},{"SWAP C", &a::OP_CB_31, 8},{"SWAP D", &a::OP_CB_32, 8},{"SWAP E", &a::OP_CB_33, 8},{"SWAP H", &a::OP_CB_34, 8},{"SWAP L", &a::OP_CB_35, 8},{"SWAP (HL)", &a::OP_CB_36, 16},{"SWAP A", &a::OP_CB_37, 8},{"SRL B", &a::OP_CB_38, 8},{"SRL C", &a::OP_CB_39, 8},{"SRL D", &a::OP_CB_3A, 8},{"SRL E", &a::OP_CB_3B, 8},{"SRL H", &a::OP_CB_3C, 8},{"SRL L", &a::OP_CB_3D, 8},{"SRL (HL)", &a::OP_CB_3E, 16},{"SRL A", &a::OP_CB_3F, 8},
		{"BIT 0,B", &a::OP_CB_40, 8},{"BIT 0,C", &a::OP_CB_41, 8},{"BIT 0,D", &a::OP_CB_42, 8},{"BIT 0,E", &a::OP_CB_43, 8},{"BIT 0,H", &a::OP_CB_44, 8},{"BIT 0,L", &a::OP_CB_45, 8},{"BIT 0,(HL)", &a::OP_CB_46, 16},{"BIT 0,A", &a::OP_CB_47, 8},{"BIT 1,B", &a::OP_CB_48, 8},{"BIT 1,C", &a::OP_CB_49, 8},{"BIT 1,D", &a::OP_CB_4A, 8},{"BIT 1,E", &a::OP_CB_4B, 8},{"BIT 1,H", &a::OP_CB_4C, 8},{"BIT 1,L", &a::OP_CB_4D, 8},{"BIT 1,(HL)", &a::OP_CB_4E, 16},{"BIT 1,A", &a::OP_CB_4F, 8},
		{"BIT 2,B", &a::OP_CB_50, 8},{"BIT 2,C", &a::OP_CB_51, 8},{"BIT 2,D", &a::OP_CB_52, 8},{"BIT 2,E", &a::OP_CB_53, 8},{"BIT 2,H", &a::OP_CB_54, 8},{"BIT 2,L", &a::OP_CB_55, 8},{"BIT 2,(HL)", &a::OP_CB_56, 16},{"BIT 2,A", &a::OP_CB_57, 8},{"BIT 3,B", &a::OP_CB_58, 8},{"BIT 3,C", &a::OP_CB_59, 8},{"BIT 3,D", &a::OP_CB_5A, 8},{"BIT 3,E", &a::OP_CB_5B, 8},{"BIT 3,H", &a::OP_CB_5C, 8},{"BIT 3,L", &a::OP_CB_5D, 8},{"BIT 3,(HL)", &a::OP_CB_5E, 16},{"BIT 3,A", &a::OP_CB_5F, 8},
		{"BIT 4,B", &a::OP_CB_60, 8},{"BIT 4,C", &a::OP_CB_61, 8},{"BIT 4,D", &a::OP_CB_62, 8},{"BIT 4,E", &a::OP_CB_63, 8},{"BIT 4,H", &a::OP_CB_64, 8},{"BIT 4,L", &a::OP_CB_65, 8},{"BIT 4,(HL)", &a::OP_CB_66, 16},{"BIT 4,A", &a::OP_CB_67, 8},{"BIT 5,B", &a::OP_CB_68, 8},{"BIT 5,C", &a::OP_CB_69, 8},{"BIT 5,D", &a::OP_CB_6A, 8},{"BIT 5,E", &a::OP_CB_6B, 8},{"BIT 5,H", &a::OP_CB_6C, 8},{"BIT 5,L", &a::OP_CB_6D, 8},{"BIT 5,(HL)", &a::OP_CB_6E, 16},{"BIT 5,A", &a::OP_CB_6F, 8},
		{"BIT 6,B", &a::OP_CB_70, 8},{"BIT 6,C", &a::OP_CB_71, 8},{"BIT 6,D", &a::OP_CB_72, 8},{"BIT 6,E", &a::OP_CB_73, 8},{"BIT 6,H", &a::OP_CB_74, 8},{"BIT 6,L", &a::OP_CB_75, 8},{"BIT 6,(HL)", &a::OP_CB_76, 16},{"BIT 6,A", &a::OP_CB_77, 8},{"BIT 7,B", &a::OP_CB_78, 8},{"BIT 7,C", &a::OP_CB_79, 8},{"BIT 7,D", &a::OP_CB_7A, 8},{"BIT 7,E", &a::OP_CB_7B, 8},{"BIT 7,H", &a::OP_CB_7C, 8},{"BIT 7,L", &a::OP_CB_7D, 8},{"BIT 7,(HL)", &a::OP_CB_7E, 16},{"BIT 7,A", &a::OP_CB_7F, 8},
		{"RES 0,B", &a::OP_CB_80, 8},{"RES 0,C", &a::OP_CB_81, 8},{"RES 0,D", &a::OP_CB_82, 8},{"RES 0,E", &a::OP_CB_83, 8},{"RES 0,H", &a::OP_CB_84, 8},{"RES 0,L", &a::OP_CB_85, 8},{"RES 0,(HL)", &a::OP_CB_86, 16},{"RES 0,A", &a::OP_CB_87, 8},{"RES 1,B", &a::OP_CB_88, 8},{"RES 1,C", &a::OP_CB_89, 8},{"RES 1,D", &a::OP_CB_8A, 8},{"RES 1,E", &a::OP_CB_8B, 8},{"RES 1,H", &a::OP_CB_8C, 8},{"RES 1,L", &a::OP_CB_8D, 8},{"RES 1,(HL)", &a::OP_CB_8E, 16},{"RES 1,A", &a::OP_CB_8F, 8},
		{"RES 2,B", &a::OP_CB_90, 8},{"RES 2,C", &a::OP_CB_91, 8},{"RES 2,D", &a::OP_CB_92, 8},{"RES 2,E", &a::OP_CB_93, 8},{"RES 2,H", &a::OP_CB_94, 8},{"RES 2,L", &a::OP_CB_95, 8},{"RES 2,(HL)", &a::OP_CB_96, 16},{"RES 2,A", &a::OP_CB_97, 8},{"RES 3,B", &a::OP_CB_98, 8},{"RES 3,C", &a::OP_CB_99, 8},{"RES 3,D", &a::OP_CB_9A, 8},{"RES 3,E", &a::OP_CB_9B, 8},{"RES 3,H", &a::OP_CB_9C, 8},{"RES 3,L", &a::OP_CB_9D, 8},{"RES 3,(HL)", &a::OP_CB_9E, 16},{"RES 3,A", &a::OP_CB_9F, 8},
		{"RES 4,B", &a::OP_CB_A0, 8},{"RES 4,C", &a::OP_CB_A1, 8},{"RES 4,D", &a::OP_CB_A2, 8},{"RES 4,E", &a::OP_CB_A3, 8},{"RES 4,H", &a::OP_CB_A4, 8},{"RES 4,L", &a::OP_CB_A5, 8},{"RES 4,(HL)", &a::OP_CB_A6, 16},{"RES 4,A", &a::OP_CB_A7, 8},{"RES 5,B", &a::OP_CB_A8, 8},{"RES 5,C", &a::OP_CB_A9, 8},{"RES 5,D", &a::OP_CB_AA, 8},{"RES 5,E", &a::OP_CB_AB, 8},{"RES 5,H", &a::OP_CB_AC, 8},{"RES 5,L", &a::OP_CB_AD, 8},{"RES 5,(HL)", &a::OP_CB_AE, 16},{"RES 5,A", &a::OP_CB_AF, 8},
		{"RES 6,B", &a::OP_CB_B0, 8},{"RES 6,C", &a::OP_CB_B1, 8},{"RES 6,D", &a::OP_CB_B2, 8},{"RES 6,E", &a::OP_CB_B3, 8},{"RES 6,H", &a::OP_CB_B4, 8},{"RES 6,L", &a::OP_CB_B5, 8},{"RES 6,(HL)", &a::OP_CB_B6, 16},{"RES 6,A", &a::OP_CB_B7, 8},{"RES 7,B", &a::OP_CB_B8, 8},{"RES 7,C", &a::OP_CB_B9, 8},{"RES 7,D", &a::OP_CB_BA, 8},{"RES 7,E", &a::OP_CB_BB, 8},{"RES 7,H", &a::OP_CB_BC, 8},{"RES 7,L", &a::OP_CB_BD, 8},{"RES 7,(HL)", &a::OP_CB_BE, 16},{"RES 7,A", &a::OP_CB_BF, 8},
		{"SET 0,B", &a::OP_CB_C0, 8},{"SET 0,C", &a::OP_CB_C1, 8},{"SET 0,D", &a::OP_CB_C2, 8},{"SET 0,E", &a::OP_CB_C3, 8},{"SET 0,H", &a::OP_CB_C4, 8},{"SET 0,L", &a::OP_CB_C5, 8},{"SET 0,(HL)", &a::OP_CB_C6, 16},{"SET 0,A", &a::OP_CB_C7, 8},{"SET 1,B", &a::OP_CB_C8, 8},{"SET 1,C", &a::OP_CB_C9, 8},{"SET 1,D", &a::OP_CB_CA, 8},{"SET 1,E", &a::OP_CB_CB, 8},{"SET 1,H", &a::OP_CB_CC, 8},{"SET 1,L", &a::OP_CB_CD, 8},{"SET 1,(HL)", &a::OP_CB_CE, 16},{"SET 1,A", &a::OP_CB_CF, 8},
		{"SET 2,B", &a::OP_CB_D0, 8},{"SET 2,C", &a::OP_CB_D1, 8},{"SET 2,D", &a::OP_CB_D2, 8},{"SET 2,E", &a::OP_CB_D3, 8},{"SET 2,H", &a::OP_CB_D4, 8},{"SET 2,L", &a::OP_CB_D5, 8},{"SET 2,(HL)", &a::OP_CB_D6, 16},{"SET 2,A", &a::OP_CB_D7, 8},{"SET 3,B", &a::OP_CB_D8, 8},{"SET 3,C", &a::OP_CB_D9, 8},{"SET 3,D", &a::OP_CB_DA, 8},{"SET 3,E", &a::OP_CB_DB, 8},{"SET 3,H", &a::OP_CB_DC, 8},{"SET 3,L", &a::OP_CB_DD, 8},{"SET 3,(HL)", &a::OP_CB_DE, 16},{"SET 3,A", &a::OP_CB_DF, 8},
		{"SET 4,B", &a::OP_CB_E0, 8},{"SET 4,C", &a::OP_CB_E1, 8},{"SET 4,D", &a::OP_CB_E2, 8},{"SET 4,E", &a::OP_CB_E3, 8},{"SET 4,H", &a::OP_CB_E4, 8},{"SET 4,L", &a::OP_CB_E5, 8},{"SET 4,(HL)", &a::OP_CB_E6, 16},{"SET 4,A", &a::OP_CB_E7, 8},{"SET 5,B", &a::OP_CB_E8, 8},{"SET 5,C", &a::OP_CB_E9, 8},{"SET 5,D", &a::OP_CB_EA, 8},{"SET 5,E", &a::OP_CB_EB, 8},{"SET 5,H", &a::OP_CB_EC, 8},{"SET 5,L", &a::OP_CB_ED, 8},{"SET 5,(HL)", &a::OP_CB_EE, 16},{"SET 5,A", &a::OP_CB_EF, 8},
		{"SET 6,B", &a::OP_CB_F0, 8},{"SET 6,C", &a::OP_CB_F1, 8},{"SET 6,D", &a::OP_CB_F2, 8},{"SET 6,E", &a::OP_CB_F3, 8},{"SET 6,H", &a::OP_CB_F4, 8},{"SET 6,L", &a::OP_CB_F5, 8},{"SET 6,(HL)", &a::OP_CB_F6, 16},{"SET 6,A", &a::OP_CB_F7, 8},{"SET 7,B", &a::OP_CB_F8, 8},{"SET 7,C", &a::OP_CB_F9, 8},{"SET 7,D", &a::OP_CB_FA, 8},{"SET 7,E", &a::OP_CB_FB, 8},{"SET 7,H", &a::OP_CB_FC, 8},{"SET 7,L", &a::OP_CB_FD, 8},{"SET 7,(HL)", &a::OP_CB_FE, 16},{"SET 7,A", &a::OP_CB_FF, 8}
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
	fetched = read(addr_abs);

	return fetched;
}



