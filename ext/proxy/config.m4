dnl $Id$
dnl config.m4 for extension proxy

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(proxy, for proxy support,
dnl Make sure that the comment is aligned:
dnl [  --with-proxy             Include proxy support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(proxy, whether to enable proxy support,
dnl Make sure that the comment is aligned:
[  --enable-proxy           Enable proxy support])

if test "$PHP_PROXY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-proxy -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/proxy.h"  # you most likely want to change this
  dnl if test -r $PHP_PROXY/$SEARCH_FOR; then # path given as parameter
  dnl   PROXY_DIR=$PHP_PROXY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for proxy files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PROXY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PROXY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the proxy distribution])
  dnl fi

  dnl # --with-proxy -> add include path
  dnl PHP_ADD_INCLUDE($PROXY_DIR/include)

  dnl # --with-proxy -> check for lib and symbol presence
  dnl LIBNAME=proxy # you may want to change this
  dnl LIBSYMBOL=proxy # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PROXY_DIR/lib, PROXY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PROXYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong proxy lib version or lib not found])
  dnl ],[
  dnl   -L$PROXY_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PROXY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(proxy, proxy.c, $ext_shared)
fi
