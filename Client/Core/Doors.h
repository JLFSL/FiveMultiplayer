#pragma once
class Doors
{
public:
	Doors() {};
	~Doors() {};

	void Pulse();

	const int MAXDOORS = 225;

	typedef struct
	{
		Hash modelInfoHash;	//doorType
		CVector3 coords;	//doorCords
		int doorState;		//doorState
		int doorHash;		//doorHash/Model
		float heading;		//doorOpenState
	} DoorsInfo;
};

inline Doors::DoorsInfo GetDoorInfo(int doorIndex)
{
	Doors::DoorsInfo doorInfo;
	switch (doorIndex)
	{
	case 0:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { 133.0f, -1711.0f, 29.0f };
		doorInfo.doorHash = 0x6b918ea1;
		break;
	case 1:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { -1287.857f, -1115.742f, 7.1401f };
		doorInfo.doorHash = 0x53a940ab;
		break;
	case 2:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { 1932.952f, 3725.154f, 32.9944f };
		doorInfo.doorHash = 0x86ef4558;
		break;
	case 3:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { 1207.873f, -470.063f, 66.358f };
		doorInfo.doorHash = 1796834809;
		break;

	case 4:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { -29.8692f, -148.1571f, 57.2265f };
		doorInfo.doorHash = 96153298;
		break;

	case 5:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bs_door");
		doorInfo.coords = { -280.7851f, 6232.782f, 31.8455f };
		doorInfo.doorHash = -281080954;
		break;

	case 6:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_hd_door_l");
		doorInfo.coords = { -824.0f, -187.0f, 38.0f };
		doorInfo.doorHash = 183249434;
		break;

	case 7:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_hd_door_r");
		doorInfo.coords = { -823.0f, -188.0f, 38.0f };
		doorInfo.doorHash = 758345384;
		break;

	case 8:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { 82.3186f, -1392.752f, 29.5261f };
		doorInfo.doorHash = -1069262641;
		break;

	case 9:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { 82.3186f, -1390.476f, 29.5261f };
		doorInfo.doorHash = 1968521986;
		break;

	case 10:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { 1686.983f, 4821.741f, 42.2131f };
		doorInfo.doorHash = -2143706301;
		break;

	case 11:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { 1687.282f, 4819.484f, 42.2131f };
		doorInfo.doorHash = -1403421822;
		break;

	case 12:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { 418.637f, -806.457f, 29.6396f };
		doorInfo.doorHash = -1950137670;
		break;

	case 13:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { 418.637f, -808.733f, 29.6396f };
		doorInfo.doorHash = 1226259807;
		break;

	case 14:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { -1096.661f, 2705.446f, 19.2578f };
		doorInfo.doorHash = 1090833557;
		break;

	case 15:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { -1094.965f, 2706.964f, 19.2578f };
		doorInfo.doorHash = 897332612;
		break;

	case 16:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { 1196.825f, 2703.221f, 38.3726f };
		doorInfo.doorHash = 1095946640;
		break;

	case 17:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { 1199.101f, 2703.221f, 38.3726f };
		doorInfo.doorHash = 801975945;
		break;

	case 18:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { -818.7642f, -1079.544f, 11.4781f };
		doorInfo.doorHash = -167996547;
		break;

	case 19:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { -816.7932f, -1078.406f, 11.4781f };
		doorInfo.doorHash = -1935818563;
		break;

	case 20:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01");
		doorInfo.coords = { -0.0564f, 6517.461f, 32.0278f };
		doorInfo.doorHash = 1891185217;
		break;

	case 21:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door01_r");
		doorInfo.coords = { -1.7253f, 6515.914f, 32.0278f };
		doorInfo.doorHash = 1236591681;
		break;

	case 22:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_clothmiddoor");
		doorInfo.coords = { -1201.435f, -776.8566f, 17.9918f };
		doorInfo.doorHash = 1980808685;
		break;

	case 23:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_clothmiddoor");
		doorInfo.coords = { 617.2458f, 2751.022f, 42.7578f };
		doorInfo.doorHash = 1352749757;
		break;

	case 24:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_clothmiddoor");
		doorInfo.coords = { 127.8201f, -211.8274f, 55.2275f };
		doorInfo.doorHash = -566554453;
		break;

	case 25:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_clothmiddoor");
		doorInfo.coords = { -3167.75f, 1055.536f, 21.5329f };
		doorInfo.doorHash = 1284749450;
		break;

	case 26:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -716.6754f, -155.42f, 37.6749f };
		doorInfo.doorHash = 261851994;
		break;

	case 27:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -715.6154f, -157.2561f, 37.6749f };
		doorInfo.doorHash = 217646625;
		break;

	case 28:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -157.0924f, -306.4413f, 39.994f };
		doorInfo.doorHash = 1801139578;
		break;

	case 29:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -156.4022f, -304.4366f, 39.994f };
		doorInfo.doorHash = -2123275866;
		break;

	case 30:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -1454.782f, -231.7927f, 50.0565f };
		doorInfo.doorHash = 1312689981;
		break;

	case 31:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ch_glassdoor");
		doorInfo.coords = { -1456.201f, -233.3682f, 50.0565f };
		doorInfo.doorHash = -595055661;
		break;

	case 32:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ta_door");
		doorInfo.coords = { 321.81f, 178.36f, 103.68f };
		doorInfo.doorHash = -265260897;
		break;

	case 33:
		doorInfo.modelInfoHash = -1212951353;
		doorInfo.coords = { 1859.89f, 3749.79f, 33.18f };
		doorInfo.doorHash = -1284867488;
		break;

	case 34:
		doorInfo.modelInfoHash = -1212951353;
		doorInfo.coords = { -289.1752f, 6199.112f, 31.637f };
		doorInfo.doorHash = 302307081;
		break;

	case 35:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ta_door");
		doorInfo.coords = { -1155.454f, -1424.008f, 5.0461f };
		doorInfo.doorHash = -681886015;
		break;

	case 36:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ta_door");
		doorInfo.coords = { 1321.286f, -1650.597f, 52.3663f };
		doorInfo.doorHash = -2086556500;
		break;

	case 37:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ta_door");
		doorInfo.coords = { -3167.789f, 1074.767f, 20.9209f };
		doorInfo.doorHash = -1496386696;
		break;

	case 38:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_mm_doorm_l");
		doorInfo.coords = { -817.0f, 179.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -2097039789;
		break;

	case 39:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_mm_doorm_r");
		doorInfo.coords = { -816.0f, 178.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -2127416656;
		break;

	case 40:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ld_garaged_01");
		doorInfo.coords = { -815.0f, 186.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -1986583853;
		doorInfo.heading = 6.5f;
		break;

	case 41:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bh1_48_backdoor_l");
		doorInfo.coords = { -797.0f, 177.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 776026812;
		break;

	case 42:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bh1_48_backdoor_r");
		doorInfo.coords = { -795.0f, 178.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 698422331;
		break;

	case 43:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bh1_48_backdoor_l");
		doorInfo.coords = { -793.0f, 181.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 535076355;
		break;

	case 44:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bh1_48_backdoor_r");
		doorInfo.coords = { -794.0f, 183.0f, 73.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 474675599;
		break;

	case 45:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bh1_48_gate_1");
		doorInfo.coords = { -849.0f, 179.0f, 70.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -1978427516;
		break;

	case 46:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_mm_windowwc");
		doorInfo.coords = { -802.7333f, 167.5041f, 77.5824f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -1700375831;
		break;

	case 47:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fa_frontdoor");
		doorInfo.coords = { -14.0f, -1441.0f, 31.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 613961892;
		break;

	case 48:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fh_frntdoor");
		doorInfo.coords = { -15.0f, -1427.0f, 31.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -272570634;
		break;

	case 49:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_sc1_21_g_door_01");
		doorInfo.coords = { -25.28f, -1431.06f, 30.84f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -1040675994;
		break;

	case 50:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fh_frontdoor");
		doorInfo.coords = { 7.52f, 539.53f, 176.18f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 1201219326;
		break;

	case 51:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_trevtraildr");
		doorInfo.coords = { 1973.0f, 3815.0f, 34.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = 1736361794;
		break;

	case 52:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_cs4_10_tr_gd_01");
		doorInfo.coords = { 1972.787f, 3824.554f, 32.5831f };
		doorInfo.doorHash = 1113956670;
		doorInfo.heading = 12.0f;
		break;

	case 53:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_trev_doorfront");
		doorInfo.coords = { -1150.0f, -1521.0f, 11.0f };
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 0);
		doorInfo.doorHash = -1361617046;
		break;
	case 54:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_com_ls_door_01");
		doorInfo.coords = { -1145.9f, -1991.14f, 14.18f };
		doorInfo.doorHash = -1871080926;
		doorInfo.heading = 25.0f;
		break;

	case 55:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_id2_11_gdoor");
		doorInfo.coords = { 723.12f, -1088.83f, 23.28f };
		doorInfo.doorHash = 1168079979;
		doorInfo.heading = 25.0f;
		break;

	case 56:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_com_ls_door_01");
		doorInfo.coords = { -356.09f, -134.77f, 40.01f };
		doorInfo.doorHash = 1206354175;
		doorInfo.heading = 25.0f;
		break;

	case 57:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_carmod3door");
		doorInfo.coords = { 108.8502f, 6617.876f, 32.673f };
		doorInfo.doorHash = -1038180727;
		doorInfo.heading = 25.0f;
		break;

	case 58:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_carmod3door");
		doorInfo.coords = { 114.3206f, 6623.226f, 32.7161f };
		doorInfo.doorHash = 1200466273;
		doorInfo.heading = 25.0f;
		break;

	case 59:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_carmod3door");
		doorInfo.coords = { 1182.305f, 2645.242f, 38.807f };
		doorInfo.doorHash = 1391004277;
		doorInfo.heading = 25.0f;
		break;

	case 60:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_carmod3door");
		doorInfo.coords = { 1174.654f, 2645.242f, 38.6826f };
		doorInfo.doorHash = -459199009;
		doorInfo.heading = 25.0f;
		break;

	case 61:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_janitor_frontdoor");
		doorInfo.coords = { -107.5401f, -9.0258f, 70.6696f };
		doorInfo.doorHash = -252283844;
		break;

	case 62:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door8");
		doorInfo.coords = { 717.0f, -975.0f, 25.0f };
		doorInfo.doorHash = -826072862;
		break;

	case 63:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door7");
		doorInfo.coords = { 719.0f, -975.0f, 25.0f };
		doorInfo.doorHash = 763780711;
		break;

	case 64:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door02");
		doorInfo.coords = { 709.9813f, -963.5311f, 30.5453f };
		doorInfo.doorHash = -874851305;
		break;

	case 65:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door03");
		doorInfo.coords = { 709.9894f, -960.6675f, 30.5453f };
		doorInfo.doorHash = -1480820165;
		break;

	case 66:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_store_door");
		doorInfo.coords = { 707.8046f, -962.4564f, 30.5453f };
		doorInfo.doorHash = 949391213;
		break;

	case 67:
		doorInfo.modelInfoHash = -1212951353;
		doorInfo.coords = { 1393.0f, 3599.0f, 35.0f };
		doorInfo.doorHash = 212192855;
		break;

	case 68:
		doorInfo.modelInfoHash = -1212951353;
		doorInfo.coords = { 1395.0f, 3600.0f, 35.0f };
		doorInfo.doorHash = -126474752;
		break;

	case 69:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door04");
		doorInfo.coords = { 1387.0f, 3614.0f, 39.0f };
		doorInfo.doorHash = 1765671336;
		break;

	case 70:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ron_door_01");
		doorInfo.coords = { 1083.547f, -1975.435f, 31.6222f };
		doorInfo.doorHash = 792295685;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 71:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ron_door_01");
		doorInfo.coords = { 1065.237f, -2006.079f, 32.2329f };
		doorInfo.doorHash = 563273144;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 72:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ron_door_01");
		doorInfo.coords = { 1085.307f, -2018.561f, 41.6289f };
		doorInfo.doorHash = -726993043;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 73:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bank4door02");
		doorInfo.coords = { -111.0f, 6464.0f, 32.0f };
		doorInfo.doorHash = 178228075;
		break;

	case 74:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bank4door01");
		doorInfo.coords = { -110.0f, 6462.0f, 32.0f };
		doorInfo.doorHash = 1852297978;
		break;

	case 75:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_lester_doorfront");
		doorInfo.coords = { 1274.0f, -1721.0f, 55.0f };
		doorInfo.doorHash = -565026078;
		break;

	case 76:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_lester_doorveranda");
		doorInfo.coords = { 1271.89f, -1707.57f, 53.79f };
		doorInfo.doorHash = 1646172266;
		break;

	case 77:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_lester_doorveranda");
		doorInfo.coords = { 1270.77f, -1708.1f, 53.75f };
		doorInfo.doorHash = 204467342;
		break;

	case 78:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_deviantfrontdoor");
		doorInfo.coords = { -127.5f, -1456.18f, 37.94f };
		doorInfo.doorHash = 2047070410;
		break;

	case 79:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_com_gar_door_01");
		doorInfo.coords = { 483.56f, -1316.08f, 32.18f };
		doorInfo.doorHash = 1417775309;
		break;

	case 80:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cs_door");
		doorInfo.coords = { 483.0f, -1312.0f, 29.0f };
		doorInfo.doorHash = -106474626;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 81:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_strip_door_01");
		doorInfo.coords = { 128.0f, -1299.0f, 29.0f };
		doorInfo.doorHash = 1840510598;
		break;

	case 82:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_magenta_door");
		doorInfo.coords = { 96.0f, -1285.0f, 29.0f };
		doorInfo.doorHash = 1382825971;
		break;

	case 83:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_motel_door_09");
		doorInfo.coords = { 549.0f, -1773.0f, 34.0f };
		doorInfo.doorHash = 232536303;
		break;

	case 84:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gangsafedoor");
		doorInfo.coords = { 974.0f, -1839.0f, 36.0f };
		doorInfo.doorHash = 1267246609;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 3);
		break;

	case 85:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gangsafedoor");
		doorInfo.coords = { 977.0f, -105.0f, 75.0f };
		doorInfo.doorHash = -1900237971;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 3);
		break;

	case 86:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_l");
		doorInfo.coords = { 1391.0f, 1163.0f, 114.0f };
		doorInfo.doorHash = 2077901353;
		break;

	case 87:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_r");
		doorInfo.coords = { 1391.0f, 1161.0f, 114.0f };
		doorInfo.doorHash = -2102079126;
		break;

	case 88:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_cs6_03_door_l");
		doorInfo.coords = { 1396.0f, 1143.0f, 115.0f };
		doorInfo.doorHash = -1905793212;
		break;

	case 89:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_cs6_03_door_r");
		doorInfo.coords = { 1396.0f, 1141.0f, 115.0f };
		doorInfo.doorHash = -1797032505;
		break;

	case 90:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_l");
		doorInfo.coords = { 1409.0f, 1146.0f, 114.0f };
		doorInfo.doorHash = -62235167;
		break;

	case 91:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_r");
		doorInfo.coords = { 1409.0f, 1148.0f, 114.0f };
		doorInfo.doorHash = -1727188163;
		break;

	case 92:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_l");
		doorInfo.coords = { 1408.0f, 1159.0f, 114.0f };
		doorInfo.doorHash = -562748873;
		break;

	case 93:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ra_door1_r");
		doorInfo.coords = { 1408.0f, 1161.0f, 114.0f };
		doorInfo.doorHash = 1976429759;
		break;

	case 94:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_gar_door_01");
		doorInfo.coords = { -1067.0f, -1666.0f, 5.0f };
		doorInfo.doorHash = 1341041543;
		break;

	case 95:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_gar_door_02");
		doorInfo.coords = { -1065.0f, -1669.0f, 5.0f };
		doorInfo.doorHash = -1631467220;
		break;

	case 96:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_map_door_01");
		doorInfo.coords = { -1104.66f, -1638.48f, 4.68f };
		doorInfo.doorHash = -1788473129;
		break;

	case 97:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fib_door1");
		doorInfo.coords = { -31.72f, -1101.85f, 26.57f };
		doorInfo.doorHash = -1831288286;
		break;

	case 98:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_tort_door");
		doorInfo.coords = { 134.4f, -2204.1f, 7.52f };
		doorInfo.doorHash = 963876966;
		break;

	case 99:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bl_shutter2");
		doorInfo.coords = { 3628.0f, 3747.0f, 28.0f };
		doorInfo.doorHash = 1773088812;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 100:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bl_shutter2");
		doorInfo.coords = { 3621.0f, 3752.0f, 28.0f };
		doorInfo.doorHash = -1332101528;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 101:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_rc_door3_l");
		doorInfo.coords = { -608.73f, -1610.32f, 27.16f };
		doorInfo.doorHash = -1811763714;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 102:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_rc_door3_r");
		doorInfo.coords = { -611.32f, -1610.09f, 27.16f };
		doorInfo.doorHash = 1608500665;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 103:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_rc_door3_l");
		doorInfo.coords = { -592.94f, -1631.58f, 27.16f };
		doorInfo.doorHash = -1456048340;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 104:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_rc_door3_r");
		doorInfo.coords = { -592.71f, -1628.99f, 27.16f };
		doorInfo.doorHash = 943854909;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 105:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ss_door04");
		doorInfo.coords = { 1991.0f, 3053.0f, 47.0f };
		doorInfo.doorHash = -89065356;
		break;

	case 106:
		doorInfo.modelInfoHash = 479144380;
		doorInfo.coords = { 1988.353f, 3054.411f, 47.3204f };
		doorInfo.doorHash = -925491840;
		break;

	case 107:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_epsilon_door_l");
		doorInfo.coords = { -700.17f, 47.31f, 44.3f };
		doorInfo.doorHash = 1999872275;
		break;

	case 108:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_epsilon_door_r");
		doorInfo.coords = { -697.94f, 48.35f, 44.3f };
		doorInfo.doorHash = 1999872275;
		break;

	case 109:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cm_door1");
		doorInfo.coords = { 241.3574f, 361.0488f, 105.8963f };
		doorInfo.doorHash = 1538555582;
		break;

	case 110:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch2_09c_garage_door");
		doorInfo.coords = { -689.11f, 506.97f, 110.64f };
		doorInfo.doorHash = -961994186;
		break;

	case 111:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_door_orangesolid");
		doorInfo.coords = { -1055.96f, -236.43f, 44.17f };
		doorInfo.doorHash = -1772472848;
		break;

	case 112:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_magenta_door");
		doorInfo.coords = { 29.0f, 3661.0f, 41.0f };
		doorInfo.doorHash = -46374650;
		break;

	case 113:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_cs4_05_tdoor");
		doorInfo.coords = { 32.0f, 3667.0f, 41.0f };
		doorInfo.doorHash = -358302761;
		break;

	case 114:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_housedoor1");
		doorInfo.coords = { 87.0f, -1959.0f, 21.0f };
		doorInfo.doorHash = -1237936041;
		break;

	case 115:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fh_frntdoor");
		doorInfo.coords = { 0.0f, -1823.0f, 30.0f };
		doorInfo.doorHash = 1487374207;
		break;

	case 116:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("p_cut_door_03");
		doorInfo.coords = { 23.34f, -1897.6f, 23.05f };
		doorInfo.doorHash = -199126299;
		break;

	case 117:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("p_cut_door_02");
		doorInfo.coords = { 524.2f, 3081.14f, 41.16f };
		doorInfo.doorHash = -897071863;
		break;

	case 118:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_po_door");
		doorInfo.coords = { -1910.58f, -576.01f, 19.25f };
		doorInfo.doorHash = -864465775;
		break;

	case 119:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ss1_10_door_l");
		doorInfo.coords = { -720.39f, 256.86f, 80.29f };
		doorInfo.doorHash = -208439480;
		break;

	case 120:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ss1_10_door_r");
		doorInfo.coords = { -718.42f, 257.79f, 80.29f };
		doorInfo.doorHash = -1001088805;
		break;

	case 121:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fibl_door02");
		doorInfo.coords = { 106.38f, -742.7f, 46.18f };
		doorInfo.doorHash = 756894459;
		break;

	case 122:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fibl_door01");
		doorInfo.coords = { 105.76f, -746.65f, 46.18f };
		doorInfo.doorHash = 476981677;
		break;

	case 123:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ct_door01");
		doorInfo.coords = { -2343.53f, 3265.37f, 32.96f };
		doorInfo.doorHash = 2081647379;
		break;

	case 124:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_ct_door01");
		doorInfo.coords = { -2342.23f, 3267.62f, 32.96f };
		doorInfo.doorHash = 2081647379;
		break;

	case 125:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("ap1_02_door_l");
		doorInfo.coords = { -1041.933f, -2748.167f, 22.0308f };
		doorInfo.doorHash = 169965357;
		break;

	case 126:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("ap1_02_door_r");
		doorInfo.coords = { -1044.841f, -2746.489f, 22.0308f };
		doorInfo.doorHash = 311232516;
		break;

	case 128:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fb_doorshortl");
		doorInfo.coords = { -1045.12f, -232.004f, 39.4379f };
		doorInfo.doorHash = -1563127729;
		break;

	case 129:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fb_doorshortr");
		doorInfo.coords = { -1046.516f, -229.3581f, 39.4379f };
		doorInfo.doorHash = 759145763;
		break;

	case 130:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fb_door01");
		doorInfo.coords = { -1083.62f, -260.4167f, 38.1867f };
		doorInfo.doorHash = -84399179;
		break;

	case 131:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_fb_door02");
		doorInfo.coords = { -1080.974f, -259.0204f, 38.1867f };
		doorInfo.doorHash = -461898059;
		break;

	case 127:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gtdoor");
		doorInfo.coords = { -1042.57f, -240.6f, 38.11f };
		doorInfo.doorHash = 1259065971;
		break;

	case 132:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_damdoor_01");
		doorInfo.coords = { 1385.258f, -2079.949f, 52.7638f };
		doorInfo.doorHash = -884051216;
		break;

	case 133:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor2");
		doorInfo.coords = { 1656.57f, 4849.66f, 42.35f };
		doorInfo.doorHash = 243782214;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 134:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor1");
		doorInfo.coords = { 1656.25f, 4852.24f, 42.35f };
		doorInfo.doorHash = 714115627;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 135:
		doorInfo.modelInfoHash = -1184516519;
		doorInfo.coords = { -1051.402f, -474.6847f, 36.6199f };
		doorInfo.doorHash = 1668106976;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 1);
		break;

	case 136:
		doorInfo.modelInfoHash = -1184516519;
		doorInfo.coords = { -1049.285f, -476.6376f, 36.7584f };
		doorInfo.doorHash = 1382347031;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 1);
		break;

	case 137:
		doorInfo.modelInfoHash = 1230099731;
		doorInfo.coords = { -1210.957f, -580.8765f, 27.2373f };
		doorInfo.doorHash = -966790948;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 1);
		break;

	case 138:
		doorInfo.modelInfoHash = 1230099731;
		doorInfo.coords = { -1212.445f, -578.4401f, 27.2373f };
		doorInfo.doorHash = -2068750132;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 1);
		break;

	case 139:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_roc_door4");
		doorInfo.coords = { -565.1712f, 276.6259f, 83.2863f };
		doorInfo.doorHash = -1716533184;
		break;

	case 140:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_roc_door4");
		doorInfo.coords = { -561.2863f, 293.5043f, 87.7771f };
		doorInfo.doorHash = 2146505927;
		break;

	case 141:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("p_jewel_door_l");
		doorInfo.coords = { -631.96f, -236.33f, 38.21f };
		doorInfo.doorHash = 1874948872;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 142:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("p_jewel_door_r1");
		doorInfo.coords = { -630.43f, -238.44f, 38.21f };
		doorInfo.doorHash = -1965020851;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 145:
		doorInfo.modelInfoHash = -1743257725;
		doorInfo.coords = { 231.62f, 216.23f, 106.4f };
		doorInfo.doorHash = 1951546856;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 146:
		doorInfo.modelInfoHash = -1743257725;
		doorInfo.coords = { 232.72f, 213.88f, 106.4f };
		doorInfo.doorHash = -431382051;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 143:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_j2_door");
		doorInfo.coords = { 258.32f, 203.84f, 106.43f };
		doorInfo.doorHash = -293975210;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 144:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_j2_door");
		doorInfo.coords = { 260.76f, 202.95f, 106.43f };
		doorInfo.doorHash = -785215289;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 148:
		doorInfo.modelInfoHash = -222270721;
		doorInfo.coords = { 256.31f, 220.66f, 106.43f };
		doorInfo.doorHash = -366143778;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 147:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bk_door");
		doorInfo.coords = { 266.36f, 217.57f, 110.43f };
		doorInfo.doorHash = 440819155;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 149:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_shrf2door");
		doorInfo.coords = { -442.66f, 6015.222f, 31.8663f };
		doorInfo.doorHash = -588495243;
		break;

	case 150:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_shrf2door");
		doorInfo.coords = { -444.4985f, 6017.06f, 31.8663f };
		doorInfo.doorHash = 1815504139;
		break;

	case 151:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_shrfdoor");
		doorInfo.coords = { 1855.685f, 3683.93f, 34.5928f };
		doorInfo.doorHash = 1344911780;
		break;

	case 152:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_l");
		doorInfo.coords = { -1223.35f, -172.41f, 39.98f };
		doorInfo.doorHash = -320891223;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 153:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_r");
		doorInfo.coords = { -1220.93f, -173.68f, 39.98f };
		doorInfo.doorHash = 1511747875;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 154:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_l");
		doorInfo.coords = { -1211.99f, -190.57f, 39.98f };
		doorInfo.doorHash = -1517722103;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 155:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_r");
		doorInfo.coords = { -1213.26f, -192.98f, 39.98f };
		doorInfo.doorHash = -1093199712;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 156:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_l");
		doorInfo.coords = { -1217.77f, -201.54f, 39.98f };
		doorInfo.doorHash = 1902048492;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 157:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_bhhotel_door_r");
		doorInfo.coords = { -1219.04f, -203.95f, 39.98f };
		doorInfo.doorHash = -444768985;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 158:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch3_04_door_01l");
		doorInfo.coords = { 2514.32f, -317.34f, 93.32f };
		doorInfo.doorHash = 404057594;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 159:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch3_04_door_01r");
		doorInfo.coords = { 2512.42f, -319.26f, 93.32f };
		doorInfo.doorHash = -1417472813;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 160:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch3_01_trlrdoor_l");
		doorInfo.coords = { 2333.23f, 2574.97f, 47.03f };
		doorInfo.doorHash = -1376084479;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 161:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch3_01_trlrdoor_r");
		doorInfo.coords = { 2329.65f, 2576.64f, 47.03f };
		doorInfo.doorHash = 457472151;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 162:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 16.1279f, -1114.605f, 29.9469f };
		doorInfo.doorHash = 1071759151;
		break;

	case 163:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 18.572f, -1115.495f, 29.9469f };
		doorInfo.doorHash = -2119023917;
		break;

	case 165:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 1698.176f, 3751.506f, 34.8553f };
		doorInfo.doorHash = -1488490473;
		break;

	case 166:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 1699.937f, 3753.42f, 34.8553f };
		doorInfo.doorHash = -511187813;
		break;

	case 167:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 244.7274f, -44.0791f, 70.91f };
		doorInfo.doorHash = -248569395;
		break;

	case 168:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 243.8379f, -46.5232f, 70.91f };
		doorInfo.doorHash = 989443413;
		break;

	case 169:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 845.3624f, -1024.539f, 28.3448f };
		doorInfo.doorHash = 2022251829;
		break;

	case 170:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 842.7684f, -1024.539f, 23.3448f };
		doorInfo.doorHash = 649820567;
		break;

	case 171:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { -326.1122f, 6075.27f, 31.6047f };
		doorInfo.doorHash = 537455378;
		break;

	case 172:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { -324.273f, 6077.109f, 31.6047f };
		doorInfo.doorHash = 1121431731;
		break;

	case 173:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { -665.2424f, -944.3256f, 21.9792f };
		doorInfo.doorHash = -1437380438;
		break;

	case 174:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { -662.6414f, -944.3256f, 21.9792f };
		doorInfo.doorHash = -946336965;
		break;

	case 175:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { -1313.826f, -389.1259f, 36.8457f };
		doorInfo.doorHash = 1893144650;
		break;

	case 176:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { -1314.465f, -391.6472f, 36.8457f };
		doorInfo.doorHash = 435841678;
		break;

	case 177:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { -1114.009f, 2689.77f, 18.7041f };
		doorInfo.doorHash = 948508314;
		break;

	case 178:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { -1112.071f, 2691.505f, 18.7041f };
		doorInfo.doorHash = -1796714665;
		break;

	case 179:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { -3164.845f, 1081.392f, 20.9887f };
		doorInfo.doorHash = -1155247245;
		break;

	case 180:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { -3163.812f, 1083.778f, 20.9887f };
		doorInfo.doorHash = 782482084;
		break;

	case 181:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 2570.905f, 303.3556f, 108.8848f };
		doorInfo.doorHash = -1194470801;
		break;

	case 182:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 2568.304f, 303.3556f, 108.8848f };
		doorInfo.doorHash = -2129698061;
		break;

	case 183:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door04");
		doorInfo.coords = { 813.1779f, -2148.27f, 29.7689f };
		doorInfo.doorHash = 1071759151;
		break;

	case 184:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door03");
		doorInfo.coords = { 810.5769f, -2148.27f, 29.7689f };
		doorInfo.doorHash = -2119023917;
		break;

	case 164:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door01");
		doorInfo.coords = { 6.8179f, -1098.209f, 29.9469f };
		doorInfo.doorHash = 1487704245;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 3);
		break;

	case 185:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_gc_door01");
		doorInfo.coords = { 827.5342f, -2160.493f, 29.7688f };
		doorInfo.doorHash = 1529812051;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 3);
		break;

	case 186:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_lrggate_01c_l");
		doorInfo.coords = { -1107.01f, 289.38f, 64.76f };
		doorInfo.doorHash = 904342475;
		break;

	case 187:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_lrggate_01c_r");
		doorInfo.coords = { -1101.62f, 290.36f, 64.76f };
		doorInfo.doorHash = -795418380;
		break;

	case 188:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_lrggate_01c_l");
		doorInfo.coords = { -1138.64f, 300.82f, 67.18f };
		doorInfo.doorHash = -1502457334;
		break;

	case 189:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_lrggate_01c_r");
		doorInfo.coords = { -1137.05f, 295.59f, 67.18f };
		doorInfo.doorHash = -1994188940;
		break;

	case 190:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bl_doorel_l");
		doorInfo.coords = { -2053.16f, 3239.49f, 30.5f };
		doorInfo.doorHash = -621770121;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 191:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_bl_doorel_r");
		doorInfo.coords = { -2054.39f, 3237.23f, 30.5f };
		doorInfo.doorHash = 1018580481;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 192:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_cbankcountdoor01");
		doorInfo.coords = { -108.91f, 6469.11f, 31.91f };
		doorInfo.doorHash = 421926217;
		break;

	case 193:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_fnclink_03gate5");
		doorInfo.coords = { -182.91f, 6168.37f, 32.14f };
		doorInfo.doorHash = -1331552374;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;
	case 196:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_csr_door_l");
		doorInfo.coords = { -59.89f, -1092.95f, 26.88f };
		doorInfo.doorHash = -293141277;
		break;

	case 197:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_csr_door_r");
		doorInfo.coords = { -60.55f, -1094.75f, 26.89f };
		doorInfo.doorHash = 506750037;
		break;

	case 194:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_csr_door_l");
		doorInfo.coords = { -39.13f, -1108.22f, 26.72f };
		doorInfo.doorHash = 1496005418;
		break;

	case 195:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_csr_door_r");
		doorInfo.coords = { -37.33f, -1108.87f, 26.72f };
		doorInfo.doorHash = -1863079210;
		break;

	case 198:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ron_door_01");
		doorInfo.coords = { 1943.73f, 3803.63f, 32.31f };
		doorInfo.doorHash = -2018911784;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 199:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor2");
		doorInfo.coords = { 316.39f, -276.49f, 54.52f };
		doorInfo.doorHash = -93934272;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 200:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor1");
		doorInfo.coords = { 313.96f, -275.6f, 54.52f };
		doorInfo.doorHash = 667682830;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 201:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor2");
		doorInfo.coords = { -2965.71f, 484.22f, 16.05f };
		doorInfo.doorHash = 1876735830;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 202:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor1");
		doorInfo.coords = { -2965.82f, 481.63f, 16.05f };
		doorInfo.doorHash = -2112857171;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 205:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_abbmaindoor");
		doorInfo.coords = { 962.1f, -2183.83f, 31.06f };
		doorInfo.doorHash = 2046930518;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 206:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_abbmaindoor2");
		doorInfo.coords = { 961.79f, -2187.08f, 31.06f };
		doorInfo.doorHash = 1208502884;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 207:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch3_04_door_02");
		doorInfo.coords = { 2508.43f, -336.63f, 115.76f };
		doorInfo.doorHash = 1986432421;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 208:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01l");
		doorInfo.coords = { -2255.19f, 322.26f, 184.93f };
		doorInfo.doorHash = -722798986;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 209:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01r");
		doorInfo.coords = { -2254.06f, 319.7f, 184.93f };
		doorInfo.doorHash = 204301578;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 210:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01l");
		doorInfo.coords = { -2301.13f, 336.91f, 184.93f };
		doorInfo.doorHash = -320140460;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 211:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01r");
		doorInfo.coords = { -2298.57f, 338.05f, 184.93f };
		doorInfo.doorHash = 65222916;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 212:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01l");
		doorInfo.coords = { -2222.32f, 305.86f, 184.93f };
		doorInfo.doorHash = -920027322;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 213:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01r");
		doorInfo.coords = { -2221.19f, 303.3f, 184.93f };
		doorInfo.doorHash = -58432001;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 214:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01l");
		doorInfo.coords = { -2280.6f, 265.43f, 184.93f };
		doorInfo.doorHash = -2007378629;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 215:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_ch1_07_door_01r");
		doorInfo.coords = { -2278.04f, 266.57f, 184.93f };
		doorInfo.doorHash = 418772613;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 216:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_gar_door_04");
		doorInfo.coords = { 778.31f, -1867.49f, 30.66f };
		doorInfo.doorHash = 1679064921;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 217:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_gate_tep_01_l");
		doorInfo.coords = { -721.35f, 91.01f, 56.68f };
		doorInfo.doorHash = 412198396;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 218:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_gate_tep_01_r");
		doorInfo.coords = { -728.84f, 88.64f, 56.68f };
		doorInfo.doorHash = -1053755588;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 219:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_artgallery_02_dr");
		doorInfo.coords = { -2287.62f, 363.9f, 174.93f };
		doorInfo.doorHash = -53446139;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 220:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_artgallery_02_dl");
		doorInfo.coords = { -2289.78f, 362.91f, 174.93f };
		doorInfo.doorHash = 1333960556;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 221:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_artgallery_02_dr");
		doorInfo.coords = { -2289.86f, 362.88f, 174.93f };
		doorInfo.doorHash = -41786493;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 222:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_artgallery_02_dl");
		doorInfo.coords = { -2292.01f, 361.89f, 174.93f };
		doorInfo.doorHash = 1750120734;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 223:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_fnclink_07gate1");
		doorInfo.coords = { 1803.94f, 3929.01f, 33.72f };
		doorInfo.doorHash = 1661506222;
		break;

	case 203:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor2");
		doorInfo.coords = { -348.81f, -47.26f, 49.39f };
		doorInfo.doorHash = -2116116146;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 204:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("v_ilev_genbankdoor1");
		doorInfo.coords = { -351.26f, -46.41f, 49.39f };
		doorInfo.doorHash = -74083138;
		GAMEPLAY::SET_BIT(&doorInfo.doorState, 2);
		break;

	case 224:
		doorInfo.modelInfoHash = GAMEPLAY::GET_HASH_KEY("prop_abat_slide");
		doorInfo.coords = { 962.9084f, -2105.814f, 34.6432f };
		doorInfo.doorHash = -1670085357;
		break;
	}
	return doorInfo;
}