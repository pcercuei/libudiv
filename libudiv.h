/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (C) 2023 Paul Cercueil <paul@crapouillou.net>
 */

#ifndef __LIBUDIV_H__
#define __LIBUDIV_H__

#ifdef _MSC_BUILD
#	define clz32(x)		_lzcnt_u32(x)
#else
#	define clz32(x)		__builtin_clz(x)
#endif

typedef struct {
    unsigned int p;
    unsigned int m;
} udiv_t;

udiv_t udiv_set_divider(unsigned int div)
{
    unsigned int p = 31 - clz32(div) + !!(div & (div - 1));
    unsigned int m = ((0x1ull << (32 + p)) + div - 1) / (unsigned long long)div;

    return (udiv_t){ .p = p, .m = m, };
}

unsigned int udiv_divide(unsigned int val, udiv_t udiv)
{
    unsigned int q = ((unsigned long long)udiv.m * val) >> 32;
    unsigned int t = ((val - q) >> 1) + q;

    return t >> (udiv.p - 1);
}

#endif /* __LIBUDIV_H__ */
