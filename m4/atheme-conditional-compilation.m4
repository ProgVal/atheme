# SPDX-License-Identifier: ISC
# SPDX-URL: https://spdx.org/licenses/ISC.html
dnl
# Copyright (C) 2005-2009 Atheme Project (http://atheme.org/)
# Copyright (C) 2018-2019 Atheme Development Group (https://atheme.github.io/)
dnl
# -*- Atheme IRC Services -*-
# Atheme Build System Component

AC_DEFUN([ATHEME_COND_CONTRIB_SUBMODULE_ENABLE], [

    CONTRIB_COND_D="contrib"
    AC_SUBST([CONTRIB_COND_D])
])

AC_DEFUN([ATHEME_COND_ECDH_X25519_TOOL_ENABLE], [

    ECDH_X25519_TOOL_COND_D="ecdh-x25519-tool"
    AC_SUBST([ECDH_X25519_TOOL_COND_D])

    AC_DEFINE([HAVE_ANYLIB_ECDH_X25519], [1], [Define to 1 if any library can provide ECDH-X25519-CHALLENGE])
])

AC_DEFUN([ATHEME_COND_ECDSA_TOOLS_ENABLE], [

    ECDSA_TOOLS_COND_D="ecdsadecode ecdsakeygen ecdsasign"
    AC_SUBST([ECDSA_TOOLS_COND_D])
])

AC_DEFUN([ATHEME_COND_LIBMOWGLI_SUBMODULE_ENABLE], [

    LIBMOWGLI_COND_D="libmowgli-2"
    AC_SUBST([LIBMOWGLI_COND_D])
])

AC_DEFUN([ATHEME_COND_LEGACY_PWCRYPTO_ENABLE], [

    LEGACY_PWCRYPTO_COND_C="anope-enc-sha256.c base64.c ircservices.c"
    LEGACY_PWCRYPTO_COND_C="${LEGACY_PWCRYPTO_COND_C} crypt3-des.c crypt3-md5.c"
    LEGACY_PWCRYPTO_COND_C="${LEGACY_PWCRYPTO_COND_C} rawmd5.c rawsha1.c rawsha2-256.c rawsha2-512.c"
    AC_SUBST([LEGACY_PWCRYPTO_COND_C])
])

AC_DEFUN([ATHEME_COND_NLS_ENABLE], [

    PODIR_COND_D="po"
    AC_SUBST([PODIR_COND_D])
])

AC_DEFUN([ATHEME_COND_CRYPTO_BENCHMARK_ENABLE], [

    CRYPTO_BENCHMARK_COND_D="crypto-benchmark"
    AC_SUBST([CRYPTO_BENCHMARK_COND_D])
])

AC_DEFUN([ATHEME_COND_PERL_ENABLE], [

    PERL_COND_D="perl"
    AC_SUBST([PERL_COND_D])
])

AC_DEFUN([ATHEME_COND_QRCODE_ENABLE], [

    QRCODE_COND_C="qrcode.c"
    AC_SUBST([QRCODE_COND_C])
])
