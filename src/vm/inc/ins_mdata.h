#ifndef INS_MDATA_H
#define INS_MDATA_H

#define INS_MDATA_DEF()                           \
INS_MDATA[1] = encode(0, A_NULL, A_NULL, A_NULL); \
INS_MDATA[2] = encode(1, A_BYTE, A_NULL, A_NULL); \
INS_MDATA[3] = encode(2, A_BYTE, A_WORD, A_NULL); \
INS_MDATA[4] = encode(1, A_DYNC, A_NULL, A_NULL);

#endif
