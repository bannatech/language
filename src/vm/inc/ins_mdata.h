#ifndef INS_MDATA_H
#define INS_MDATA_H

/* Macro used below.
 * It should be self-explainitory
 * i.e. encode( 3, 2, 1, 0 ) = 0b11100100
 *             11,10,01,00   = 0xE4
 */
#define encode(n, a0, a1, a2) \
	( n << 6 | a0 << 4 | a1 << 2 | a2 );

#define A_NULL 0
#define A_BYTE 1
#define A_WORD 2
#define A_DYNC 3

/* This definition is ran in `is.c`
 *
 *  INS_MDATA[ <opcode> ] = encode( <number of arguements>, <type..3> )
 */
#define INS_MDATA_DEF()                                             \
/* NULL      */ INS_MDATA[0x00] = encode(0, A_NULL, A_NULL, A_NULL); \
/* SYNC      */ INS_MDATA[0x01] = encode(1, A_BYTE, A_NULL, A_NULL); \
/* ARGB      */ INS_MDATA[0x02] = encode(0, A_NULL, A_NULL, A_NULL); \
/* LIBC      */ INS_MDATA[0x0F] = encode(1, A_WORD, A_NULL, A_NULL); \
                                                                     \
/* POP       */ INS_MDATA[0x10] = encode(1, A_BYTE, A_NULL, A_NULL); \
/* ROT       */ INS_MDATA[0x11] = encode(0, A_NULL, A_NULL, A_NULL); \
/* DUP       */ INS_MDATA[0x12] = encode(0, A_NULL, A_NULL, A_NULL); \
/* ROT_THREE */ INS_MDATA[0x13] = encode(0, A_NULL, A_NULL, A_NULL); \
                                                                     \
/* DEC       */ INS_MDATA[0x20] = encode(3, A_BYTE, A_BYTE, A_WORD); \
/* LOV       */ INS_MDATA[0x21] = encode(2, A_BYTE, A_WORD, A_NULL); \
/* STV       */ INS_MDATA[0x22] = encode(2, A_BYTE, A_WORD, A_NULL); \
/* LOC       */ INS_MDATA[0x23] = encode(3, A_BYTE, A_WORD, A_DYNC); \
/* CTS       */ INS_MDATA[0x24] = encode(1, A_DYNC, A_NULL, A_NULL); \
                                                                     \
/* TYPEOF    */ INS_MDATA[0x30] = encode(0, A_NULL, A_NULL, A_NULL); \
/* CAST      */ INS_MDATA[0x31] = encode(1, A_BYTE, A_NULL, A_NULL); \
                                                                     \
/* ADD       */ INS_MDATA[0x40] = encode(0, A_NULL, A_NULL, A_NULL); \
/* SUB       */ INS_MDATA[0x41] = encode(0, A_NULL, A_NULL, A_NULL); \
/* MULT      */ INS_MDATA[0x42] = encode(0, A_NULL, A_NULL, A_NULL); \
/* DIV       */ INS_MDATA[0x43] = encode(0, A_NULL, A_NULL, A_NULL); \
/* POW       */ INS_MDATA[0x44] = encode(0, A_NULL, A_NULL, A_NULL); \
/* BRT       */ INS_MDATA[0x45] = encode(0, A_NULL, A_NULL, A_NULL); \
/* SIN       */ INS_MDATA[0x46] = encode(0, A_NULL, A_NULL, A_NULL); \
/* COS       */ INS_MDATA[0x47] = encode(0, A_NULL, A_NULL, A_NULL); \
/* TAN       */ INS_MDATA[0x48] = encode(0, A_NULL, A_NULL, A_NULL); \
/* ISIN      */ INS_MDATA[0x49] = encode(0, A_NULL, A_NULL, A_NULL); \
/* ICOS      */ INS_MDATA[0x4A] = encode(0, A_NULL, A_NULL, A_NULL); \
/* ITAN      */ INS_MDATA[0x4B] = encode(0, A_NULL, A_NULL, A_NULL); \
/* MOD       */ INS_MDATA[0x4C] = encode(0, A_NULL, A_NULL, A_NULL); \
/* OR        */ INS_MDATA[0x4D] = encode(0, A_NULL, A_NULL, A_NULL); \
/* XOR       */ INS_MDATA[0x4E] = encode(0, A_NULL, A_NULL, A_NULL); \
/* NAND      */ INS_MDATA[0x4F] = encode(0, A_NULL, A_NULL, A_NULL); \
                                                                     \
/* GTHAN     */ INS_MDATA[0x50] = encode(0, A_NULL, A_NULL, A_NULL); \
/* LTHAN     */ INS_MDATA[0x51] = encode(0, A_NULL, A_NULL, A_NULL); \
/* EQ        */ INS_MDATA[0x52] = encode(0, A_NULL, A_NULL, A_NULL); \
/* NOT       */ INS_MDATA[0x53] = encode(0, A_NULL, A_NULL, A_NULL); \
                                                                     \
/* STARTL    */ INS_MDATA[0x60] = encode(0, A_NULL, A_NULL, A_NULL); \
/* CLOOP     */ INS_MDATA[0x61] = encode(0, A_NULL, A_NULL, A_NULL); \
/* BREAK     */ INS_MDATA[0x6E] = encode(0, A_NULL, A_NULL, A_NULL); \
/* DONE      */ INS_MDATA[0x6F] = encode(0, A_NULL, A_NULL, A_NULL); \
                                                                     \
/* GOTO      */ INS_MDATA[0x70] = encode(1, A_WORD, A_NULL, A_NULL); \
/* JUMPF     */ INS_MDATA[0x71] = encode(1, A_BYTE, A_NULL, A_NULL); \
/* CALL      */ INS_MDATA[0x7F] = encode(1, A_WORD, A_NULL, A_NULL); \
                                                                     \
/* PUSH      */ INS_MDATA[0x80] = encode(0, A_NULL, A_NULL, A_NULL); \
/* DEL       */ INS_MDATA[0x81] = encode(0, A_NULL, A_NULL, A_NULL); \
/* GET       */ INS_MDATA[0x82] = encode(0, A_NULL, A_NULL, A_NULL); \
/* GETP      */ INS_MDATA[0x83] = encode(1, A_WORD, A_NULL, A_NULL); \
/* CALLM     */ INS_MDATA[0x84] = encode(1, A_WORD, A_NULL, A_NULL); \
                                                                     \
/* RETURN    */ INS_MDATA[0xF0] = encode(0, A_NULL, A_NULL, A_NULL); \
/* NEW       */ INS_MDATA[0xF1] = encode(1, A_WORD, A_NULL, A_NULL); \
/* DECLASS   */ INS_MDATA[0xFE] = encode(2, A_WORD, A_DYNC, A_NULL); \
/* DEFUN     */ INS_MDATA[0xFF] = encode(3, A_WORD, A_BYTE, A_DYNC);

#define BTOI 0
#define WTOA 1
#define DTOL 2
#define DTOV 3

/* This definition is ran in `is.c`
 *
 *  INS_ADATA[ <opcode> ] = encode( <number of arguements>, <type..3> )
 */
#define INS_ADATA_DEF()                                        \
/* NULL      */ INS_ADATA[0x00] = encode(0, BTOI, BTOI, BTOI); \
/* SYNC      */ INS_ADATA[0x01] = encode(1, BTOI, BTOI, BTOI); \
/* ARGB      */ INS_ADATA[0x02] = encode(0, BTOI, BTOI, BTOI); \
/* LIBC      */ INS_ADATA[0x0F] = encode(1, WTOA, BTOI, BTOI); \
                                                               \
/* POP       */ INS_ADATA[0x10] = encode(1, BTOI, BTOI, BTOI); \
/* ROT       */ INS_ADATA[0x11] = encode(0, BTOI, BTOI, BTOI); \
/* DUP       */ INS_ADATA[0x12] = encode(0, BTOI, BTOI, BTOI); \
/* ROT_THREE */ INS_ADATA[0x13] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* DEC       */ INS_ADATA[0x20] = encode(3, BTOI, BTOI, WTOA); \
/* LOV       */ INS_ADATA[0x21] = encode(2, BTOI, WTOA, BTOI); \
/* STV       */ INS_ADATA[0x22] = encode(2, BTOI, WTOA, BTOI); \
/* LOC       */ INS_ADATA[0x23] = encode(3, BTOI, WTOA, BTOI); \
/* CTS       */ INS_ADATA[0x24] = encode(1, BTOI, BTOI, BTOI); \
                                                               \
/* TYPEOF    */ INS_ADATA[0x30] = encode(0, BTOI, BTOI, BTOI); \
/* CAST      */ INS_ADATA[0x31] = encode(1, BTOI, BTOI, BTOI); \
                                                               \
/* ADD       */ INS_ADATA[0x40] = encode(0, BTOI, BTOI, BTOI); \
/* SUB       */ INS_ADATA[0x41] = encode(0, BTOI, BTOI, BTOI); \
/* MULT      */ INS_ADATA[0x42] = encode(0, BTOI, BTOI, BTOI); \
/* DIV       */ INS_ADATA[0x43] = encode(0, BTOI, BTOI, BTOI); \
/* POW       */ INS_ADATA[0x44] = encode(0, BTOI, BTOI, BTOI); \
/* BRT       */ INS_ADATA[0x45] = encode(0, BTOI, BTOI, BTOI); \
/* SIN       */ INS_ADATA[0x46] = encode(0, BTOI, BTOI, BTOI); \
/* COS       */ INS_ADATA[0x47] = encode(0, BTOI, BTOI, BTOI); \
/* TAN       */ INS_ADATA[0x48] = encode(0, BTOI, BTOI, BTOI); \
/* ISIN      */ INS_ADATA[0x49] = encode(0, BTOI, BTOI, BTOI); \
/* ICOS      */ INS_ADATA[0x4A] = encode(0, BTOI, BTOI, BTOI); \
/* ITAN      */ INS_ADATA[0x4B] = encode(0, BTOI, BTOI, BTOI); \
/* MOD       */ INS_ADATA[0x4C] = encode(0, BTOI, BTOI, BTOI); \
/* OR        */ INS_ADATA[0x4D] = encode(0, BTOI, BTOI, BTOI); \
/* XOR       */ INS_ADATA[0x4E] = encode(0, BTOI, BTOI, BTOI); \
/* NAND      */ INS_ADATA[0x4F] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* GTHAN     */ INS_ADATA[0x50] = encode(0, BTOI, BTOI, BTOI); \
/* LTHAN     */ INS_ADATA[0x51] = encode(0, BTOI, BTOI, BTOI); \
/* EQ        */ INS_ADATA[0x52] = encode(0, BTOI, BTOI, BTOI); \
/* NOT       */ INS_ADATA[0x53] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* STARTL    */ INS_ADATA[0x60] = encode(0, BTOI, BTOI, BTOI); \
/* CLOOP     */ INS_ADATA[0x61] = encode(0, BTOI, BTOI, BTOI); \
/* BREAK     */ INS_ADATA[0x6E] = encode(0, BTOI, BTOI, BTOI); \
/* DONE      */ INS_ADATA[0x6F] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* GOTO      */ INS_ADATA[0x70] = encode(1, WTOA, BTOI, BTOI); \
/* JUMPF     */ INS_ADATA[0x71] = encode(1, BTOI, BTOI, BTOI); \
/* CALL      */ INS_ADATA[0x7F] = encode(1, WTOA, BTOI, BTOI); \
                                                               \
/* PUSH      */ INS_ADATA[0x80] = encode(0, BTOI, BTOI, BTOI); \
/* DEL       */ INS_ADATA[0x81] = encode(0, BTOI, BTOI, BTOI); \
/* GET       */ INS_ADATA[0x82] = encode(0, BTOI, BTOI, BTOI); \
/* GETP      */ INS_ADATA[0x83] = encode(1, WTOA, BTOI, BTOI); \
/* CALLM     */ INS_ADATA[0x84] = encode(1, WTOA, BTOI, BTOI); \
                                                               \
/* RETURN    */ INS_ADATA[0xF0] = encode(0, BTOI, BTOI, BTOI); \
/* NEW       */ INS_ADATA[0xF1] = encode(1, WTOA, BTOI, BTOI); \
/* DECLASS   */ INS_ADATA[0xFE] = encode(2, WTOA, BTOI, BTOI); \
/* DEFUN     */ INS_ADATA[0xFF] = encode(3, WTOA, BTOI, BTOI);

#endif
