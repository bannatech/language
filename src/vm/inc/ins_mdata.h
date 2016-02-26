#ifndef INS_MDATA_H
#define INS_MDATA_H

#define INS_MDATA_DEF()                                             \
/* NULL      */ INS_MDATA[0x00] = encode(0, A_NULL, A_NULL, A_NULL); \
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
/* DECLASS   */ INS_MDATA[0xFE] = encode(2, A_WORD, A_DYNC, A_NULL); \
/* DEFUN     */ INS_MDATA[0xFF] = encode(3, A_WORD, A_BYTE, A_DYNC);

#endif
