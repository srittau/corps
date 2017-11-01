dnl AM_PATH_CORPS([VERSION [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AC_DEFUN(AM_PATH_CORPS,[
dnl FIXME	AC_CHECK_LIB(corps, corps_core,,
dnl FIXME		AC_MSG_ERROR(You must install corps-core!),
dnl FIXME		$ORBIT_LIBS
dnl FIXME	)

  ifelse([$2], , :, [$2])
])


dnl AM_CORPS_CORBA([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN(AM_CORPS_CORBA,[
  corps_c_found="yes"
  CORPS_CORBA_CXXFLAGS=""
  CORPS_CORBA_LIBS=""

  if test "x$corps_c_found" = "xyes" ; then
    AM_PATH_CORPS(0.2.0,, corps_c_found="no")
  fi

  AC_LANG_CPLUSPLUS
  if test "x$corps_c_found" = "xyes" ; then
    AM_CORPS_OMNIORB(,, corps_c_found="no")
  fi
  if test "x$corps_c_found" = "xyes" ; then
    AM_CORPS_THREADS(,, corps_c_found="no")
  fi
  AC_LANG_C

  if test "x$corps_c_found" = "xyes" ; then
    CORPS_CORBA_CXXFLAGS="$OMNIORB_CXXFLAGS $THREAD_CFLAGS"
    CORPS_CORBA_LIBS="$OMNIORB_LIBS $THREAD_LIBS -lcorpscorba -lcorpstool"
    ifelse([$1], , :, [$1])
  else
    ifelse([$2], , :, [$2])
  fi

  AC_SUBST(CORPS_CORBA_CXXFLAGS)
  AC_SUBST(CORPS_CORBA_LIBS)
])


dnl AM_CORPS_FILE([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
AC_DEFUN(AM_CORPS_FILE,[
  corps_f_found="yes"
  CORPS_FILE_CXXFLAGS=""
  CORPS_FILE_LIBS=""

  if test "x$corps_f_found" = "xyes" ; then
    AM_PATH_XML(1.0.0,, corps_f_found="no")
  fi

  if test "x$corps_f_found" = "xyes" ; then
    CORPS_FILE_CXXFLAGS="$XML_CFLAGS"
    CORPS_FILE_LIBS="-lcorpstool $XML_LIBS"
    ifelse([$1], , :, [$1])
  else
    ifelse([$2], , :, [$2])
  fi

  AC_SUBST(CORPS_FILE_CXXFLAGS)
  AC_SUBST(CORPS_FILE_LIBS)
])


dnl AM_CORPS_OMNIORB([VERSION [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AC_DEFUN(AM_CORPS_OMNIORB, [
  corps_orb_found="yes"
  OMNIORB_LIBS=""
  OMNIORB_CXXFLAGS=""

  if test "x$corps_orb_found" = "xyes" ; then
    AC_PATH_PROGS(IDL_COMPILER,omniidl2, corps_orb_found="no")
  fi
  if test "x$corps_orb_found" = "xyes" ; then
    dnl FIXME: AC_CHECK_LIB(omniORB2,main,, corps_orb_found="no")
    true
  fi

  if test "x$corps_orb_found" = "xyes" ; then
    OMNIORB_LIBS="-lomniORB2 -ltcpwrapGK -lomniLC -lomnithread -lomniDynamic2"
    dnl FIXME:
    OMNIORB_CXXFLAGS="-D__x86__"
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
  fi

  AC_SUBST(OMNIORB_LIBS)
  AC_SUBST(OMNIORB_CXXFLAGS)
])


dnl AM_CORPS_THREADS([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
dnl FIXME
AC_DEFUN(AM_CORPS_THREADS, [
  THREAD_LIBS="-lpthread"
  THREAD_CFLAGS="-D_REENTRANT"
  AC_SUBST(THREAD_LIBS)
  AC_SUBST(THREAD_CFLAGS)

  ifelse([$1], , :, [$1])
])
