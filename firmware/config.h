#ifndef __config_h__
#define __config_h__

// int switch_map[] =
// {
// 	59,60,1,3,5,7,9,11,13,14,84,
// 	69, 70, 2, 4, 6, 8, 10, 12, 72, 80, 85
// };

#define NA 0
#define NO_KEY -1

int switch_map[] =
{
	// 1, 2, 0, 16, 18, 20, 22, 24,
	// 26, 27, 14, 11, 12, 15, 17, 19,
	// 21, 23, 25, 71, 81, 75, 3, 4,
	// 29, 31, 33, 35, 37, 39, 40, 28,
	// 57, 43, 30, 32, 34, 36, 38, 80,
	// 41, 56, 5, 6, 45, 46, 48, 50,
	// 51, 53, 82, 77, 7, 8, 44, 47,
	// 49, 63, 52, 54, 55, 70, 9, 10,
	// 58, 59, 62, 64, 67, 68, 69, 13,
	// 72, 73, 42, 60, 61, 76, 66, 79,
	// 74, 78

	// /*0*/ 1, /*1*/ 2, /*2*/ 0, /*3*/ 16, /*4*/ 18, /*5*/ 20, /*6*/ 22, /*7*/ 24,
	// /*8*/ 26, /*9*/ 27, /*10*/ 14, /*11*/ 11, /*12*/ 12, /*13*/ 15, /*14*/ 17, /*15*/ 19,
	// /*16*/ 21, /*17*/ 23, /*18*/ 25, /*19*/ 71, /*20*/ 81, /*21*/ 75, /*22*/ 3, /*23*/ 4,
	// /*24*/ 29, /*25*/ 31, /*26*/ 33, /*27*/ 35, /*28*/ 37, /*29*/ 39, /*30*/ 40, /*31*/ 28,
	// /*32*/ 57, /*33*/ 43, /*34*/ 30, /*35*/ 32, /*36*/ 34, /*37*/ 36, /*38*/ 38, /*39*/ 80,
	// /*40*/ 41, 41 56, /*42*/ 5, /*43*/ 6, /*44*/ 45, /*45*/ 46, /*46*/ 48, /*47*/ 50,
	// /*48*/ 51, /*49*/ 53, /*50*/ 82, /*51*/ 77, /*52*/ 7, /*53*/ 8, /*54*/ 44, /*55*/ 47,
	// /*56*/ 49, /*57*/ 63, /*58*/ 52, /*59*/ 54, /*60*/ 55, /*61*/ 70, /*62*/ 9, /*63*/ 10,
	// /*64*/ 58, /*65*/ 59, /*66*/ 62, /*67*/ 64, /*68*/ 67, /*69*/ 68, /*70*/ 69, /*71*/ 13,
	// /*72*/ 72, /*73*/ 73, /*74*/ 42, /*75*/ 60, /*76*/ 61, /*77*/ 76, /*78*/ 66, /*79*/ 79,
	// /*80*/ 74, /*81*/ 78

	/* 0:KEY_F1 */ 1, /* 1:KEY_F2 */ 2, /* 2:KEY_ESC */ 0, /* 3:KEY_2 */ 16, /* 4:KEY_4 */ 18, /* 5:KEY_6 */ 20, /* 6:KEY_8 */ 22, /* 7:KEY_0 */ 24,
	/* 8:KEY_EQUAL */ 26, /* 9:KEY_BACKSPACE */ 27, /* 10:KEY_SYSREQ */ 14, /* 11:KEY_NUM_LOCK */ 11, /* 12:KEY_SCROLL_LOCK */ 12, /* 13:KEY_1 */ 15, /* 14:KEY_3 */ 17, /* 15:KEY_5 */ 19,
	/* 16:KEY_7 */ 21, /* 17:KEY_9 */ 23, /* 18:KEY_MINUS */ 25, /* 19:KEY_UP */ 71, /* 20:KEY_DOWN */ 81, /* 21:KEY_FN */ 75, /* 22:KEY_F3 */ 3, /* 23:KEY_F4 */ 4,
	/* 24:KEY_TAB */ 29, /* 25:KEY_W */ 31, /* 26:KEY_R */ 33, /* 27:KEY_Y */ 35, /* 28:KEY_I */ 37, /* 29:KEY_P */ 39, /* 30:KEY_LEFT_BRACE */ 40, /* 31:KEY_HOME */ 28,
	/* 32:NA */ NO_KEY, /* 33:KEY_PAGE_DOWN */ 57, /* 34:KEY_PAGE_UP */ 43, /* 35:KEY_Q */ 30, /* 36:KEY_E */ 32, /* 37:KEY_T */ 34, /* 38:KEY_U */ 36, /* 39:KEY_O */ 38,
	/* 40:KEY_LEFT */ 80, /* 41:KEY_RIGHT_BRACE */ 41, /* 42:KEY_ENTER */ 56, /* 43:NA */ NO_KEY, /* 44:KEY_F5 */ 5, /* 45:KEY_F6 */ 6, /* 46:KEY_A */ 45, /* 47:KEY_S */ 46,
	/* 48:KEY_F */ 48, /* 49:KEY_H */ 50, /* 50:KEY_J */ 51, /* 51:KEY_L */ 53, /* 52:KEY_RIGHT */ 82, /* 53:KEY_TILDE */ 77, /* 54:NA */ NO_KEY, /* 55:KEY_F7 */ 7,
	/* 56:KEY_F8 */ 8, /* 57:KEY_LEFT_CTRL */ 44, /* 58:KEY_D */ 47, /* 59:KEY_G */ 49, /* 60:KEY_B */ 63, /* 61:KEY_K */ 52, /* 62:KEY_SEMICOLON */ 54, /* 63:KEY_QUOTE */ 55,
	/* 64:KEY_RIGHT_SHIFT */ 70, /* 65:NA */ NO_KEY, /* 66:KEY_F9 */ 9, /* 67:KEY_F10 */ 10, /* 68:KEY_LEFT_SHIFT */ 58, /* 69:KEY_Z */ 59, /* 70:KEY_V */ 62, /* 71:KEY_N */ 64,
	/* 72:KEY_COMMA */ 67, /* 73:KEY_PERIOD */ 68, /* 74:KEY_SLASH */ 69, /* 75:KEY_PRINTSCREEN */ 13, /* 76:NA */ NO_KEY, /* 77:KEY_END */ 72, /* 78:KEY_LEFT_ALT */ 73, /* 79:KEY_BACKSLASH */ 42,
	/* 80:KEY_X */ 60, /* 81:KEY_C */ 61, /* 82:KEY_SPACE */ 76, /* 83:KEY_M */ 66, /* 84:KEY_DELETE */ 79, /* 85:KEY_CAPS_LOCK */ 74, /* 86:KEY_INSERT */ 78, /* 87:NA */ NO_KEY
};

int key_map[] =
{
	KEY_ESC,		KEY_F1,			KEY_F2, KEY_F3,		KEY_F4,		KEY_F5,		KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_NUM_LOCK, KEY_SCROLL_LOCK, KEY_PRINTSCREEN, KEY_SYSREQ,
	KEY_1,			KEY_2,			KEY_3, 	KEY_4,		KEY_5,		KEY_6,		KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_HOME,
	KEY_TAB,		KEY_Q,			KEY_W, 	KEY_E,		KEY_R,		KEY_T,		KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_PAGE_UP,
	KEY_LEFTCONTROL, 	KEY_A,			KEY_S, 	KEY_D,		KEY_F,		KEY_G,		KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER, KEY_PAGE_DOWN,
	KEY_LEFTSHIFT, KEY_Z,			KEY_X, 	KEY_C,		KEY_V,		KEY_B,		KEY_N, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHTSHIFT, KEY_UP, KEY_END,
	KEY_LEFTALT, 	KEY_CAPS_LOCK,	NA,		KEY_SPACE, 	KEY_TILDE,	KEY_INSERT, KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT
};

#endif