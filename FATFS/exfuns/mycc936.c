#include "ff.h"   
#include "flash.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32开发板
//cc936.c修改后 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

WCHAR ff_convert (	/* Converted code, 0 means conversion error */
	WCHAR	src,	/* Character code to be converted */
	UINT	dir		/* 0: Unicode to OEMCP, 1: OEMCP to Unicode */
)
{
	WCHAR t[2];
	WCHAR c;
	u32 i, li, hi;
	u16 n;			 
	u32 gbk2uni_offset=0;		  
						  
	if (src < 0x80)c = src;//ASCII,直接不用转换.
	else 
	{
 		if(dir)	//GBK 2 UNICODE
		{
			gbk2uni_offset=ftinfo.ugbksize/2;	 
		}else	//UNICODE 2 GBK  
		{   
			gbk2uni_offset=0;	
		}    
		/* Unicode to OEMCP */
		hi=ftinfo.ugbksize/2;//对半开.
		hi =hi / 4 - 1;
		li = 0;
		for (n = 16; n; n--)
		{
			i = li + (hi - li) / 2;	
			SPI_Flash_Read((u8*)&t,ftinfo.ugbkaddr+i*4+gbk2uni_offset,4);//读出4个字节  
			if (src == t[0]) break;
			if (src > t[0])li = i;  
			else hi = i;    
		}
		c = n ? t[1] : 0;  	    
	}
	return c;
}		   

WCHAR ff_wtoupper (	/* Upper converted character */
	WCHAR chr		/* Input character */
)
{
	static const WCHAR tbl_lower[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0xA1, 0x00A2, 0x00A3, 0x00A5, 0x00AC, 0x00AF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0x0FF, 0x101, 0x103, 0x105, 0x107, 0x109, 0x10B, 0x10D, 0x10F, 0x111, 0x113, 0x115, 0x117, 0x119, 0x11B, 0x11D, 0x11F, 0x121, 0x123, 0x125, 0x127, 0x129, 0x12B, 0x12D, 0x12F, 0x131, 0x133, 0x135, 0x137, 0x13A, 0x13C, 0x13E, 0x140, 0x142, 0x144, 0x146, 0x148, 0x14B, 0x14D, 0x14F, 0x151, 0x153, 0x155, 0x157, 0x159, 0x15B, 0x15D, 0x15F, 0x161, 0x163, 0x165, 0x167, 0x169, 0x16B, 0x16D, 0x16F, 0x171, 0x173, 0x175, 0x177, 0x17A, 0x17C, 0x17E, 0x192, 0x3B1, 0x3B2, 0x3B3, 0x3B4, 0x3B5, 0x3B6, 0x3B7, 0x3B8, 0x3B9, 0x3BA, 0x3BB, 0x3BC, 0x3BD, 0x3BE, 0x3BF, 0x3C0, 0x3C1, 0x3C3, 0x3C4, 0x3C5, 0x3C6, 0x3C7, 0x3C8, 0x3C9, 0x3CA, 0x430, 0x431, 0x432, 0x433, 0x434, 0x435, 0x436, 0x437, 0x438, 0x439, 0x43A, 0x43B, 0x43C, 0x43D, 0x43E, 0x43F, 0x440, 0x441, 0x442, 0x443, 0x444, 0x445, 0x446, 0x447, 0x448, 0x449, 0x44A, 0x44B, 0x44C, 0x44D, 0x44E, 0x44F, 0x451, 0x452, 0x453, 0x454, 0x455, 0x456, 0x457, 0x458, 0x459, 0x45A, 0x45B, 0x45C, 0x45E, 0x45F, 0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 0x2176, 0x2177, 0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 0x217E, 0x217F, 0xFF41, 0xFF42, 0xFF43, 0xFF44, 0xFF45, 0xFF46, 0xFF47, 0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 0xFF4D, 0xFF4E, 0xFF4F, 0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 0xFF55, 0xFF56, 0xFF57, 0xFF58, 0xFF59, 0xFF5A, 0 };
	static const WCHAR tbl_upper[] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x21, 0xFFE0, 0xFFE1, 0xFFE5, 0xFFE2, 0xFFE3, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0x178, 0x100, 0x102, 0x104, 0x106, 0x108, 0x10A, 0x10C, 0x10E, 0x110, 0x112, 0x114, 0x116, 0x118, 0x11A, 0x11C, 0x11E, 0x120, 0x122, 0x124, 0x126, 0x128, 0x12A, 0x12C, 0x12E, 0x130, 0x132, 0x134, 0x136, 0x139, 0x13B, 0x13D, 0x13F, 0x141, 0x143, 0x145, 0x147, 0x14A, 0x14C, 0x14E, 0x150, 0x152, 0x154, 0x156, 0x158, 0x15A, 0x15C, 0x15E, 0x160, 0x162, 0x164, 0x166, 0x168, 0x16A, 0x16C, 0x16E, 0x170, 0x172, 0x174, 0x176, 0x179, 0x17B, 0x17D, 0x191, 0x391, 0x392, 0x393, 0x394, 0x395, 0x396, 0x397, 0x398, 0x399, 0x39A, 0x39B, 0x39C, 0x39D, 0x39E, 0x39F, 0x3A0, 0x3A1, 0x3A3, 0x3A4, 0x3A5, 0x3A6, 0x3A7, 0x3A8, 0x3A9, 0x3AA, 0x410, 0x411, 0x412, 0x413, 0x414, 0x415, 0x416, 0x417, 0x418, 0x419, 0x41A, 0x41B, 0x41C, 0x41D, 0x41E, 0x41F, 0x420, 0x421, 0x422, 0x423, 0x424, 0x425, 0x426, 0x427, 0x428, 0x429, 0x42A, 0x42B, 0x42C, 0x42D, 0x42E, 0x42F, 0x401, 0x402, 0x403, 0x404, 0x405, 0x406, 0x407, 0x408, 0x409, 0x40A, 0x40B, 0x40C, 0x40E, 0x40F, 0x2160, 0x2161, 0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 0xFF38, 0xFF39, 0xFF3A, 0 };
	int i;


	for (i = 0; tbl_lower[i] && chr != tbl_lower[i]; i++) ;

	return tbl_lower[i] ? tbl_upper[i] : chr;
}



