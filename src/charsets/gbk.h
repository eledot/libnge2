/*
 * Copyright (C) 1999-2001, 2005, 2008 Free Software Foundation, Inc.
 * Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 * This file is under GPL or LGPL License.
 */

/*
 * GBK
 */

/*
 * GBK, as described in Ken Lunde's book, is an extension of GB 2312-1980
 * (shifted by adding 0x8080 to the range 0xA1A1..0xFEFE, as used in EUC-CN).
 * It adds the following ranges:
 *
 * (part of GBK/1)  0xA2A1-0xA2AA  Small Roman numerals
 * GBK/3   0x{81-A0}{40-7E,80-FE}  6080 new characters, all in Unicode
 * GBK/4   0x{AA-FE}{40-7E,80-A0}  8160 new characters, 8080 in Unicode
 * GBK/5   0x{A8-A9}{40-7E,80-A0}  166 new characters, 153 in Unicode
 *
 * Furthermore, all four tables I have looked at
 *   - the CP936 table by Microsoft, found on ftp.unicode.org in 1999,
 *   - the GBK table by Sun, investigated on a Solaris 2.7 machine,
 *   - the GBK tables by CWEX, found in the Big5+ package,
 *   - the GB18030 standard (second printing),
 * agree in the following extensions. (Ken Lunde must have overlooked these
 * differences between GB2312 and GBK. Also, the CWEX tables have additional
 * differences.)
 *
 * 1. Some characters in the GB2312 range are defined differently:
 *
 *     code    GB2312                         GBK
 *    0xA1A4   0x30FB # KATAKANA MIDDLE DOT   0x00B7 # MIDDLE DOT
 *    0xA1AA   0x2015 # HORIZONTAL BAR        0x2014 # EM DASH
 *
 * 2. 19 characters added in the range 0xA6E0-0xA6F5.
 *
 * 3. 4 characters added in the range 0xA8BB-0xA8C0.
 *
 * CP936 as of 1999 was identical to GBK. However, since 1999, Microsoft has
 * added new mappings to CP936...
 */

#include "charsets/gb2312.h"
#include "charsets/gbkext1.h"
#include "charsets/gbkext2.h"
#include "charsets/gbkext_inv.h"
#include "charsets/cp936ext.h"

inline static int
gbk_mbtowc (ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;

  if (c >= 0x81 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    if (c >= 0xa1 && c <= 0xf7) {
      unsigned char c2 = s[1];
      if (c == 0xa1) {
        if (c2 == 0xa4) {
          *pwc = 0x00b7;
          return 2;
        }
        if (c2 == 0xaa) {
          *pwc = 0x2014;
          return 2;
        }
      }
      if (c2 >= 0xa1 && c2 < 0xff) {
        unsigned char buf[2];
        int ret;
        buf[0] = c-0x80; buf[1] = c2-0x80;
        ret = gb2312_mbtowc(pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
        buf[0] = c; buf[1] = c2;
        ret = cp936ext_mbtowc(pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
      }
    }
    if (c >= 0x81 && c <= 0xa0)
      return gbkext1_mbtowc(pwc,s,2);
    if (c >= 0xa8 && c <= 0xfe)
      return gbkext2_mbtowc(pwc,s,2);
    if (c == 0xa2) {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 <= 0xaa) {
        *pwc = 0x2170+(c2-0xa1);
        return 2;
      }
    }
  }
  return RET_ILSEQ;
}

inline static int
gbk_wctomb (unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  if (wc != 0x30fb && wc != 0x2015) {
    ret = gb2312_wctomb(buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if (n < 2)
        return RET_TOOSMALL;
      r[0] = buf[0]+0x80;
      r[1] = buf[1]+0x80;
      return 2;
    }
  }
  ret = gbkext_inv_wctomb(buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }
  if (wc >= 0x2170 && wc <= 0x2179) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa2;
    r[1] = 0xa1 + (wc-0x2170);
    return 2;
  }
  ret = cp936ext_wctomb(buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }
  if (wc == 0x00b7) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa1;
    r[1] = 0xa4;
    return 2;
  }
  if (wc == 0x2014) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa1;
    r[1] = 0xaa;
    return 2;
  }

  return RET_ILUNI;
}
