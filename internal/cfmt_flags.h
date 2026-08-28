#ifndef CFMT_FLAGS_H
#define CFMT_FLAGS_H

extern unsigned char cfmt_flags;

#define is_(flag) (cfmt_flags & (flag))
#define set_(flag) (cfmt_flags |= (flag))
#define clr_(flag) (cfmt_flags &= ~(flag))


#define set_flags (cfmt_flags = 0xFF)
#define clr_flags (cfmt_flags = 0x00)


// Flag name:     Flag bit:
#define colored     0x01
#define styled      0x02
#define rgb_256     0x04
#define rgb_hex     0x08

#define formatting  0x40
#define parsing     0x80

#endif