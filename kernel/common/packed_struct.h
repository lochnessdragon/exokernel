#ifndef _NO_PACK_H
#define _NO_PACK_H

#ifdef __GNUC__
#define packed_struct __attribute__((packed))
#else
#error This project doesn't support non-gcc compiler's!
#endif

#endif // _NO_PACK_H