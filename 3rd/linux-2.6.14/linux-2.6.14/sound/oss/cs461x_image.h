/****************************************************************************
 * "CWCIMAGE.H"-- For CS46XX. Ver 1.04
 *      Copyright 1998-2001 (c) Cirrus Logic Corp.
 *      Version 1.04
 ****************************************************************************
 */
#ifndef __CS_IMAGE_H
#define __CS_IMAGE_H

#define CLEAR__COUNT     3
#define FILL__COUNT      4
#define BA1__DWORD_SIZE  13*1024+512

static struct
{
        unsigned BA1__DestByteOffset;
        unsigned BA1__SourceSize;
} ClrStat[CLEAR__COUNT] ={ {0x00000000, 0x00003000 },
                           {0x00010000, 0x00003800 },
                           {0x00020000, 0x00007000 } };

static u32 FillArray1[]={
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000163,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00200040,0x00008010,0x00000000,
0x00000000,0x80000001,0x00000001,0x00060000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00900080,0x00000173,0x00000000,
0x00000000,0x00000010,0x00800000,0x00900000,
0xf2c0000f,0x00000200,0x00000000,0x00010600,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000163,0x330300c2,
0x06000000,0x00000000,0x80008000,0x80008000,
0x3fc0000f,0x00000301,0x00010400,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00b00000,0x00d0806d,0x330480c3,
0x04800000,0x00000001,0x00800001,0x0000ffff,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x066a0600,0x06350070,0x0000929d,0x929d929d,
0x00000000,0x0000735a,0x00000600,0x00000000,
0x929d735a,0x00000000,0x00010000,0x735a735a,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x0000804f,0x000000c3,
0x05000000,0x00a00010,0x00000000,0x80008000,
0x00000000,0x00000000,0x00000700,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000080,0x00a00000,0x0000809a,0x000000c2,
0x07400000,0x00000000,0x80008000,0xffffffff,
0x00c80028,0x00005555,0x00000000,0x000107a0,
0x00c80028,0x000000c2,0x06800000,0x00000000,
0x06e00080,0x00300000,0x000080bb,0x000000c9,
0x07a00000,0x04000000,0x80008000,0xffffffff,
0x00c80028,0x00005555,0x00000000,0x00000780,
0x00c80028,0x000000c5,0xff800000,0x00000000,
0x00640080,0x00c00000,0x00008197,0x000000c9,
0x07800000,0x04000000,0x80008000,0xffffffff,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x0000805e,0x000000c1,
0x00000000,0x00800000,0x80008000,0x80008000,
0x00020000,0x0000ffff,0x00000000,0x00000000};

static u32 FillArray2[]={
0x929d0600,0x929d929d,0x929d929d,0x929d0000,
0x929d929d,0x929d929d,0x929d929d,0x929d929d,
0x929d929d,0x00100635,0x060b013f,0x00000004,
0x00000001,0x007a0002,0x00000000,0x066e0610,
0x0105929d,0x929d929d,0x929d929d,0x929d929d,
0x929d929d,0xa431ac75,0x0001735a,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0x735a0051,
0x00000000,0x929d929d,0x929d929d,0x929d929d,
0x929d929d,0x929d929d,0x929d929d,0x929d929d,
0x929d929d,0x929d929d,0x00000000,0x06400136,
0x0000270f,0x00010000,0x007a0000,0x00000000,
0x068e0645,0x0105929d,0x929d929d,0x929d929d,
0x929d929d,0x929d929d,0xa431ac75,0x0001735a,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0xa431ac75,0xa431ac75,0xa431ac75,0xa431ac75,
0x735a0100,0x00000000,0x00000000,0x00000000};

static u32 FillArray3[]={
0x00000000,0x00000000,0x00000000,0x00010004};

static u32 FillArray4[]={
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00001705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00009705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00011705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00019705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00021705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00029705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00031705,0x00001400,0x000a411e,0x00001003,
0x00040730,0x00001002,0x000f619e,0x00001003,
0x00039705,0x00001400,0x000a411e,0x00001003,
0x000fe19e,0x00001003,0x0009c730,0x00001003,
0x0008e19c,0x00001003,0x000083c1,0x00093040,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00009705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00011705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00019705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00021705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00029705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00031705,0x00001400,0x000a211e,0x00001003,
0x00098730,0x00001002,0x000ee19e,0x00001003,
0x00039705,0x00001400,0x000a211e,0x00001003,
0x0000a730,0x00001008,0x000e2730,0x00001002,
0x0000a731,0x00001002,0x0000a731,0x00001002,
0x0000a731,0x00001002,0x0000a731,0x00001002,
0x0000a731,0x00001002,0x0000a731,0x00001002,
0x00000000,0x00000000,0x000f619c,0x00001003,
0x0007f801,0x000c0000,0x00000037,0x00001000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x000c0000,0x00000000,0x00000000,
0x0000373c,0x00001000,0x00000000,0x00000000,
0x000ee19c,0x00001003,0x0007f801,0x000c0000,
0x00000037,0x00001000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x0000273c,0x00001000,
0x00000033,0x00001000,0x000e679e,0x00001003,
0x00007705,0x00001400,0x000ac71e,0x00001003,
0x00087fc1,0x000c3be0,0x0007f801,0x000c0000,
0x00000037,0x00001000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x0000a730,0x00001003,
0x00000033,0x00001000,0x0007f801,0x000c0000,
0x00000037,0x00001000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x000c0000,
0x00000032,0x00001000,0x0000273d,0x00001000,
0x0004a730,0x00001003,0x00000f41,0x00097140,
0x0000a841,0x0009b240,0x0000a0c1,0x0009f040,
0x0001c641,0x00093540,0x0001cec1,0x0009b5c0,
0x00000000,0x00000000,0x0001bf05,0x0003fc40,
0x00002725,0x000aa400,0x00013705,0x00093a00,
0x0000002e,0x0009d6c0,0x00038630,0x00001004,
0x0004ef0a,0x000eb785,0x0003fc8a,0x00000000,
0x00000000,0x000c70e0,0x0007d182,0x0002c640,
0x00000630,0x00001004,0x000799b8,0x0002c6c0,
0x00031705,0x00092240,0x00039f05,0x000932c0,
0x0003520a,0x00000000,0x00040731,0x0000100b,
0x00010705,0x000b20c0,0x00000000,0x000eba44,
0x00032108,0x000c60c4,0x00065208,0x000c2917,
0x000406b0,0x00001007,0x00012f05,0x00036880,
0x0002818e,0x000c0000,0x0004410a,0x00000000,
0x00040630,0x00001007,0x00029705,0x000c0000,
0x00000000,0x00000000,0x00003fc1,0x0003fc40,
0x000037c1,0x00091b40,0x00003fc1,0x000911c0,
0x000037c1,0x000957c0,0x00003fc1,0x000951c0,
0x000037c1,0x00000000,0x00003fc1,0x000991c0,
0x000037c1,0x00000000,0x00003fc1,0x0009d1c0,
0x000037c1,0x00000000,0x0001ccc1,0x000915c0,
0x0001c441,0x0009d800,0x0009cdc1,0x00091240,
0x0001c541,0x00091d00,0x0009cfc1,0x00095240,
0x0001c741,0x00095c80,0x000e8ca9,0x00099240,
0x000e85ad,0x00095640,0x00069ca9,0x00099d80,
0x000e952d,0x00099640,0x000eaca9,0x0009d6c0,
0x000ea5ad,0x00091a40,0x0006bca9,0x0009de80,
0x000eb52d,0x00095a40,0x000ecca9,0x00099ac0,
0x000ec5ad,0x0009da40,0x000edca9,0x0009d300,
0x000a6e0a,0x00001000,0x000ed52d,0x00091e40,
0x000eeca9,0x00095ec0,0x000ee5ad,0x00099e40,
0x0006fca9,0x00002500,0x000fb208,0x000c59a0,
0x000ef52d,0x0009de40,0x00068ca9,0x000912c1,
0x000683ad,0x00095241,0x00020f05,0x000991c1,
0x00000000,0x00000000,0x00086f88,0x00001000,
0x0009cf81,0x000b5340,0x0009c701,0x000b92c0,
0x0009de81,0x000bd300,0x0009d601,0x000b1700,
0x0001fd81,0x000b9d80,0x0009f501,0x000b57c0,
0x000a0f81,0x000bd740,0x00020701,0x000b5c80,
0x000a1681,0x000b97c0,0x00021601,0x00002500,
0x000a0701,0x000b9b40,0x000a0f81,0x000b1bc0,
0x00021681,0x00002d00,0x00020f81,0x000bd800,
0x000a0701,0x000b5bc0,0x00021601,0x00003500,
0x000a0f81,0x000b5f40,0x000a0701,0x000bdbc0,
0x00021681,0x00003d00,0x00020f81,0x000b1d00,
0x000a0701,0x000b1fc0,0x00021601,0x00020500,
0x00020f81,0x000b1341,0x000a0701,0x000b9fc0,
0x00021681,0x00020d00,0x00020f81,0x000bde80,
0x000a0701,0x000bdfc0,0x00021601,0x00021500,
0x00020f81,0x000b9341,0x00020701,0x000b53c1,
0x00021681,0x00021d00,0x000a0f81,0x000d0380,
0x0000b601,0x000b15c0,0x00007b01,0x00000000,
0x00007b81,0x000bd1c0,0x00007b01,0x00000000,
0x00007b81,0x000b91c0,0x00007b01,0x000b57c0,
0x00007b81,0x000b51c0,0x00007b01,0x000b1b40,
0x00007b81,0x000b11c0,0x00087b01,0x000c3dc0,
0x0007e488,0x000d7e45,0x00000000,0x000d7a44,
0x0007e48a,0x00000000,0x00011f05,0x00084080,
0x00000000,0x00000000,0x00001705,0x000b3540,
0x00008a01,0x000bf040,0x00007081,0x000bb5c0,
0x00055488,0x00000000,0x0000d482,0x0003fc40,
0x0003fc88,0x00000000,0x0001e401,0x000b3a00,
0x0001ec81,0x000bd6c0,0x0004ef08,0x000eb784,
0x000c86b0,0x00001007,0x00008281,0x000bb240,
0x0000b801,0x000b7140,0x00007888,0x00000000,
0x0000073c,0x00001000,0x0007f188,0x000c0000,
0x00000000,0x00000000,0x00055288,0x000c555c,
0x0005528a,0x000c0000,0x0009fa88,0x000c5d00,
0x0000fa88,0x00000000,0x00000032,0x00001000,
0x0000073d,0x00001000,0x0007f188,0x000c0000,
0x00000000,0x00000000,0x0008c01c,0x00001003,
0x00002705,0x00001008,0x0008b201,0x000c1392,
0x0000ba01,0x00000000,0x00008731,0x00001400,
0x0004c108,0x000fe0c4,0x00057488,0x00000000,
0x000a6388,0x00001001,0x0008b334,0x000bc141,
0x0003020e,0x00000000,0x000886b0,0x00001008,
0x00003625,0x000c5dfa,0x000a638a,0x00001001,
0x0008020e,0x00001002,0x0008a6b0,0x00001008,
0x0007f301,0x00000000,0x00000000,0x00000000,
0x00002725,0x000a8c40,0x000000ae,0x00000000,
0x000d8630,0x00001008,0x00000000,0x000c74e0,
0x0007d182,0x0002d640,0x000a8630,0x00001008,
0x000799b8,0x0002d6c0,0x0000748a,0x000c3ec5,
0x0007420a,0x000c0000,0x00062208,0x000c4117,
0x00070630,0x00001009,0x00000000,0x000c0000,
0x0001022e,0x00000000,0x0003a630,0x00001009,
0x00000000,0x000c0000,0x00000036,0x00001000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x0002a730,0x00001008,0x0007f801,0x000c0000,
0x00000037,0x00001000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x0002a730,0x00001008,
0x00000033,0x00001000,0x0002a705,0x00001008,
0x00007a01,0x000c0000,0x000e6288,0x000d550a,
0x0006428a,0x00000000,0x00060730,0x0000100a,
0x00000000,0x000c0000,0x00000000,0x00000000,
0x0007aab0,0x00034880,0x00078fb0,0x0000100b,
0x00057488,0x00000000,0x00033b94,0x00081140,
0x000183ae,0x00000000,0x000786b0,0x0000100b,
0x00022f05,0x000c3545,0x0000eb8a,0x00000000,
0x00042731,0x00001003,0x0007aab0,0x00034880,
0x00048fb0,0x0000100a,0x00057488,0x00000000,
0x00033b94,0x00081140,0x000183ae,0x00000000,
0x000806b0,0x0000100b,0x00022f05,0x00000000,
0x00007401,0x00091140,0x00048f05,0x000951c0,
0x00042731,0x00001003,0x0000473d,0x00001000,
0x000f19b0,0x000bbc47,0x00080000,0x000bffc7,
0x000fe19e,0x00001003,0x00000000,0x00000000,
0x0008e19c,0x00001003,0x000083c1,0x00093040,
0x00000f41,0x00097140,0x0000a841,0x0009b240,
0x0000a0c1,0x0009f040,0x0001c641,0x00093540,
0x0001cec1,0x0009b5c0,0x00000000,0x000fdc44,
0x00055208,0x00000000,0x00010705,0x000a2880,
0x0000a23a,0x00093a00,0x0003fc8a,0x000df6c5,
0x0004ef0a,0x000c0000,0x00012f05,0x00036880,
0x00065308,0x000c2997,0x000d86b0,0x0000100a,
0x0004410a,0x000d40c7,0x00000000,0x00000000,
0x00080730,0x00001004,0x00056f0a,0x000ea105,
0x00000000,0x00000000,0x0000473d,0x00001000,
0x000f19b0,0x000bbc47,0x00080000,0x000bffc7,
0x0000273d,0x00001000,0x00000000,0x000eba44,
0x00048f05,0x0000f440,0x00007401,0x0000f7c0,
0x00000734,0x00001000,0x00010705,0x000a6880,
0x00006a88,0x000c75c4,0x00000000,0x000e5084,
0x00000000,0x000eba44,0x00087401,0x000e4782,
0x00000734,0x00001000,0x00010705,0x000a6880,
0x00006a88,0x000c75c4,0x0007c108,0x000c0000,
0x0007e721,0x000bed40,0x00005f25,0x000badc0,
0x0003ba97,0x000beb80,0x00065590,0x000b2e00,
0x00033217,0x00003ec0,0x00065590,0x000b8e40,
0x0003ed80,0x000491c0,0x00073fb0,0x00074c80,
0x000283a0,0x0000100c,0x000ee388,0x00042970,
0x00008301,0x00021ef2,0x000b8f14,0x0000000f,
0x000c4d8d,0x0000001b,0x000d6dc2,0x000e06c6,
0x000032ac,0x000c3916,0x0004edc2,0x00074c80,
0x00078898,0x00001000,0x00038894,0x00000032,
0x000c4d8d,0x00092e1b,0x000d6dc2,0x000e06c6,
0x0004edc2,0x000c1956,0x0000722c,0x00034a00,
0x00041705,0x0009ed40,0x00058730,0x00001400,
0x000d7488,0x000c3a00,0x00048f05,0x00000000};

static struct
{   u32 Offset;
    u32 Size;
    u32 *pFill;
} FillStat[FILL__COUNT] = {
                            {0x00000000, sizeof(FillArray1), FillArray1},
                            {0x00001800, sizeof(FillArray2), FillArray2},
                            {0x000137f0, sizeof(FillArray3), FillArray3},
                            {0x00020000, sizeof(FillArray4), FillArray4}
                          };


#endif
