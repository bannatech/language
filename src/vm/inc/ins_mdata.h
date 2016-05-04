#ifndef INS_MDATA_H
#define INS_MDATA_H

/* Macro used below.
 * It should be self-explainitory
 * i.e. encode( 3, 2, 1, 0 ) = 0b11100100
 *             11,10,01,00   = 0xE4
 */
#define encode(n, a0, a1, a2) \
	( n << 6 | a0 << 4 | a1 << 2 | a2 );

#define NAMELEN 2
#define ADDRLEN 2

#define A_BYTE 0
#define A_NAME 1
#define A_ADDR 2
#define A_DYNC 3

/* This definition is ran in `is.c`
 *
 *  INS_MDATA[ <opcode> ] <- encode( <number of arguements>, <type..3> )
 */
#define INS_MDATA_DEF()                                              \
/* NULL      */ INS_MDATA[0x00] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* SYNC      */ INS_MDATA[0x01] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
/* PRINT     */ INS_MDATA[0x02] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* DEBUG     */ INS_MDATA[0x03] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ARGB      */ INS_MDATA[0x0E] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* LIBC      */ INS_MDATA[0x0F] = encode(1, A_ADDR, A_BYTE, A_BYTE); \
                                                                     \
/* POP       */ INS_MDATA[0x10] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
/* ROT       */ INS_MDATA[0x11] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* DUP       */ INS_MDATA[0x12] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ROT_THREE */ INS_MDATA[0x13] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* DEC       */ INS_MDATA[0x20] = encode(3, A_BYTE, A_BYTE, A_NAME); \
/* LOV       */ INS_MDATA[0x21] = encode(2, A_BYTE, A_NAME, A_BYTE); \
/* STV       */ INS_MDATA[0x22] = encode(2, A_BYTE, A_NAME, A_BYTE); \
/* CTV       */ INS_MDATA[0x23] = encode(3, A_BYTE, A_NAME, A_DYNC); \
/* CTS       */ INS_MDATA[0x24] = encode(1, A_DYNC, A_BYTE, A_BYTE); \
                                                                     \
/* TYPEOF    */ INS_MDATA[0x30] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* CAST      */ INS_MDATA[0x31] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* ADD       */ INS_MDATA[0x40] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* SUB       */ INS_MDATA[0x41] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* MULT      */ INS_MDATA[0x42] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* DIV       */ INS_MDATA[0x43] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* POW       */ INS_MDATA[0x44] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* BRT       */ INS_MDATA[0x45] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* SIN       */ INS_MDATA[0x46] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* COS       */ INS_MDATA[0x47] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* TAN       */ INS_MDATA[0x48] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ISIN      */ INS_MDATA[0x49] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ICOS      */ INS_MDATA[0x4A] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ITAN      */ INS_MDATA[0x4B] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* MOD       */ INS_MDATA[0x4C] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* BOR       */ INS_MDATA[0x4D] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* BXOR      */ INS_MDATA[0x4E] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* BNAND     */ INS_MDATA[0x4F] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* GTHAN     */ INS_MDATA[0x50] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* LTHAN     */ INS_MDATA[0x51] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* G_THAN_EQ */ INS_MDATA[0x52] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* G_LHAN_EQ */ INS_MDATA[0x53] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* EQ        */ INS_MDATA[0x54] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* NE        */ INS_MDATA[0x55] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* NOT       */ INS_MDATA[0x56] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* OR        */ INS_MDATA[0x57] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* AND       */ INS_MDATA[0x58] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* STARTL    */ INS_MDATA[0x60] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* CLOOP     */ INS_MDATA[0x61] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* BREAK     */ INS_MDATA[0x6E] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ENDL      */ INS_MDATA[0x6F] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* GOTO      */ INS_MDATA[0x70] = encode(1, A_ADDR, A_BYTE, A_BYTE); \
/* JUMPF     */ INS_MDATA[0x71] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
/* IFDO      */ INS_MDATA[0x72] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* ELSE      */ INS_MDATA[0x73] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* DONE      */ INS_MDATA[0x7E] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* CALL      */ INS_MDATA[0x7F] = encode(2, A_BYTE, A_NAME, A_BYTE); \
                                                                     \
/* GETN      */ INS_MDATA[0x80] = encode(1, A_NAME, A_BYTE, A_BYTE); \
/* SETN      */ INS_MDATA[0x81] = encode(1, A_NAME, A_BYTE, A_BYTE); \
/* CALLM     */ INS_MDATA[0x82] = encode(1, A_NAME, A_BYTE, A_BYTE); \
/* INDEXO    */ INS_MDATA[0x83] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* MODO      */ INS_MDATA[0x84] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
                                                                     \
/* RETURN    */ INS_MDATA[0xF0] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* NEW       */ INS_MDATA[0xF1] = encode(2, A_BYTE, A_NAME, A_BYTE); \
/* ENDCLASS  */ INS_MDATA[0xF2] = encode(0, A_BYTE, A_BYTE, A_BYTE); \
/* DENS      */ INS_MDATA[0xFD] = encode(1, A_BYTE, A_BYTE, A_BYTE); \
/* DECLASS   */ INS_MDATA[0xFE] = encode(2, A_NAME, A_DYNC, A_BYTE); \
/* DEFUN     */ INS_MDATA[0xFF] = encode(3, A_NAME, A_BYTE, A_DYNC);


#define BTOI 0 // Byte to Integer
#define BTOT 1 // Byte to Type
#define DTOL 2 // Dynamic to Byte List
#define DTOV 3 // Dynamic to Variable

/* This definition is ran in `is.c`
 *
 *  INS_ADATA[ <opcode> ] = encode( <number of arguements>, <type..3> )
 */
#define INS_ADATA_DEF()                                        \
/* NULL      */ INS_ADATA[0x00] = encode(0, BTOI, BTOI, BTOI); \
/* SYNC      */ INS_ADATA[0x01] = encode(1, BTOI, BTOI, BTOI); \
/* PRINT     */ INS_ADATA[0x02] = encode(0, BTOI, BTOI, BTOI); \
/* DEBUG     */ INS_ADATA[0x03] = encode(0, BTOI, BTOI, BTOI); \
/* ARGB      */ INS_ADATA[0x0E] = encode(0, BTOI, BTOI, BTOI); \
/* LIBC      */ INS_ADATA[0x0F] = encode(1, BTOI, BTOI, BTOI); \
                                                               \
/* POP       */ INS_ADATA[0x10] = encode(1, BTOI, BTOI, BTOI); \
/* ROT       */ INS_ADATA[0x11] = encode(0, BTOI, BTOI, BTOI); \
/* DUP       */ INS_ADATA[0x12] = encode(0, BTOI, BTOI, BTOI); \
/* ROT_THREE */ INS_ADATA[0x13] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* DEC       */ INS_ADATA[0x20] = encode(3, BTOI, BTOT, BTOI); \
/* LOV       */ INS_ADATA[0x21] = encode(2, BTOI, BTOI, BTOI); \
/* STV       */ INS_ADATA[0x22] = encode(2, BTOI, BTOI, BTOI); \
/* CTV       */ INS_ADATA[0x23] = encode(3, BTOI, BTOI, DTOV); \
/* CTS       */ INS_ADATA[0x24] = encode(1, DTOV, BTOI, BTOI); \
                                                               \
/* TYPEOF    */ INS_ADATA[0x30] = encode(0, BTOI, BTOI, BTOI); \
/* CAST      */ INS_ADATA[0x31] = encode(1, BTOT, BTOI, BTOI); \
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
/* G_THAN_EQ */ INS_ADATA[0x52] = encode(0, BTOI, BTOI, BTOI); \
/* G_LHAN_EQ */ INS_ADATA[0x53] = encode(0, BTOI, BTOI, BTOI); \
/* EQ        */ INS_ADATA[0x54] = encode(0, BTOI, BTOI, BTOI); \
/* NEQ       */ INS_ADATA[0x55] = encode(0, BTOI, BTOI, BTOI); \
/* NOT       */ INS_ADATA[0x56] = encode(0, BTOI, BTOI, BTOI); \
/* OR        */ INS_ADATA[0x57] = encode(0, BTOI, BTOI, BTOI); \
/* AND       */ INS_ADATA[0x58] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* STARTL    */ INS_ADATA[0x60] = encode(0, BTOI, BTOI, BTOI); \
/* CLOOP     */ INS_ADATA[0x61] = encode(0, BTOI, BTOI, BTOI); \
/* BREAK     */ INS_ADATA[0x6E] = encode(0, BTOI, BTOI, BTOI); \
/* ENDL      */ INS_ADATA[0x6F] = encode(0, BTOI, BTOI, BTOI); \
                                                               \
/* GOTO      */ INS_ADATA[0x70] = encode(1, BTOI, BTOI, BTOI); \
/* JUMPF     */ INS_ADATA[0x71] = encode(1, BTOI, BTOI, BTOI); \
/* IFDO      */ INS_ADATA[0x72] = encode(0, BTOI, BTOI, BTOI); \
/* ELSE      */ INS_ADATA[0x73] = encode(0, BTOI, BTOI, BTOI); \
/* DONE      */ INS_ADATA[0x7E] = encode(0, BTOI, BTOI, BTOI); \
/* CALL      */ INS_ADATA[0x7F] = encode(2, BTOI, BTOI, BTOI); \
                                                               \
/* GETN      */ INS_ADATA[0x80] = encode(1, BTOI, BTOI, BTOI); \
/* SETN      */ INS_ADATA[0x81] = encode(1, BTOI, BTOI, BTOI); \
/* CALLM     */ INS_ADATA[0x82] = encode(1, BTOI, BTOI, BTOI); \
/* INDEXO    */ INS_ADATA[0x83] = encode(0, BTOI, BTOI, BTOI); \
/* MODO      */ INS_ADATA[0x84] = encode(1, BTOI, BTOI, BTOI); \
                                                               \
/* RETURN    */ INS_ADATA[0xF0] = encode(0, BTOI, BTOI, BTOI); \
/* NEW       */ INS_ADATA[0xF1] = encode(2, BTOI, BTOI, BTOI); \
/* ENDCLASS  */ INS_MDATA[0xF2] = encode(0, BTOI, BTOI, BTOI); \
/* DENS      */ INS_ADATA[0xFD] = encode(1, BTOI, BTOI, BTOI); \
/* DECLASS   */ INS_ADATA[0xFE] = encode(2, BTOI, DTOL, BTOI); \
/* DEFUN     */ INS_ADATA[0xFF] = encode(3, BTOI, BTOT, DTOL);

#endif
