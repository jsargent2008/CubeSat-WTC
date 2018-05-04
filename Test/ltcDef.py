NC = -1
THERM = -2
TH_OP = -3
IO = -1
PDWN = -5

# #	 PIN, desc,		~voltage,	factor
ltc1 = [
	[0, 'V_Stack_4',	7.2,	0.33],
	[1, 'NC',			NC,		1.00],
	[2, 'TH-3-7+',		THERM,	1.00],
	[3, 'TH-3-7-',		THERM,	1.00],
	[4, 'TH-4-8+',		THERM,	1.00],
	[5, 'TH-4-8-',		THERM,	1.00],
	[6, 'V-Stack_3',	7.2,	0.33],
	[7, 'REF_Chrg',		IO,		0.50]
]

ltc2 = [
	[0, 'V_Stack_2',	7.2,	0.33],
	[1, 'NC',			NC,		1.00],
	[2, 'TH-2-6+',		THERM,	1.00],
	[3, 'TH-2-6-',		THERM,	1.00],
	[4, 'TH-1-5+',		THERM,	1.00],
	[5, 'TH-1-5-',		THERM,	1.00],
	[6, 'NC',			NC,		1.00],
	[7, 'V-Stack_1',	7.2,	0.33]
]

ltc3 = [
	[0, 'V_MPPT_XCtr',	6,		0.50],
	[1, 'V_MPPT_XZ-',	6,		0.50],
	[2, 'V_MPPT_Z+',	6,		0.50],
	[3, 'NTC_XCtr',		TH_OP,	0.50],
	[4, 'NTC_YZ-',		TH_OP,	0.50],
	[5, 'V_MPPT_YCtr',	6,		0.50],
	[6, 'V_MPPT_YZ+',	6,		0.50],
	[7, 'NTC_YCtr',		TH_OP,	0.50]
]

ltc4 = [
	[0, 'V_Pnl_Y-Ctr',	4.7,	0.50],
	[1, 'V_Pnl_Y-Z+',	4.7,	0.50],
	[2, 'V_Pnl_Y-Z-',	4.7,	0.50],
	[3, 'V_Pnl_X-Z-',	4.7,	0.50],
	[4, 'NTC_YZ+',		TH_OP,	0.50],
	[5, 'NTC_Drive',	5,		0.50],
	[6, 'V_Pnl_X-Z+',	4.7,	0.50],
	[7, 'V_Pnl_X-Ctr',	4.7,	0.50]
]

ltc5 = [
	[0, 'V_Pnl_X+Ctr',	4.7,	0.50],
	[1, 'V_Pnl_X+Z+',	4.7,	0.50],
	[2, 'V_Pnl_X+Z-',	4.7,	0.50],
	[3, 'V_Pnl_Z+',		4.7,	0.50],
	[4, 'V_Pnl_Y+Z-',	4.7,	0.50],
	[5, 'V_Pnl_Y+Z+',	4.7,	0.50],
	[6, 'V_Pnl_Y+Ctr',	4.7,	0.50],
	[7, 'Pull-down',	PDWN,	1.00]
]

ltc6 = [
	[0, 'NTC_XZ+',		TH_OP,	0.50],
	[1, 'NTC_XZ-',		TH_OP,	0.50],
	[2, 'NTC_Z+',		TH_OP,	0.50],
	[3, 'V_MPPT_XZ+',	6,		0.50],
	[4, 'V_MPPT_YZ-',	6,		0.50],
	[5, 'Pull-down',	PDWN,	1.00],
	[6, 'Pull-down',	PDWN,	1.00],
	[7, 'MPPT_Bus',		5.9,	0.50]
]

BatteryBoard = [ltc1, ltc2]
MPPT = [ltc3, ltc4, ltc5, ltc6]
ltcAll = [ltc1,ltc2,ltc3,ltc4,ltc5,ltc6]
