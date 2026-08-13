#ifndef FLAGS_H
#define FLAGS_H

extern unsigned char flags;

#define is_(flag) (flags & (flag))
#define set_(flag) (flags |= (flag))
#define clr_(flag) (flags &= ~(flag))


#define set_flags (flags = 0xFF)
#define clr_flags (flags = 0x00)


// Flag name:     Flag bit:
#define colored     0x01
#define styled      0x02
#define rgb_256     0x04
#define rgb_hex     0x08

#define formatting  0x40
#define parsing     0x80

#endif