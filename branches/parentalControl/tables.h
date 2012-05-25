/*********************** Information *************************\
| $HeadURL$
|
| Author: Jo2003
|
| Begin: 13.06.2010 / 14:50:35
|
| Last edited by: $Author$
|
| $Id$
\*************************************************************/
#ifndef __130610_TABLES_H
   #define __130610_TABLES_H

#define TAB_ASPECT \
"CREATE TABLE aspect ("\
      "cid integer PRIMARY KEY UNIQUE,"\
      "asp char(32),"\
      "crop char(32))"

#define TAB_SETTINGS \
"CREATE TABLE settings ("\
      "name char(32) PRIMARY KEY UNIQUE,"\
      "val text)"

#define TAB_TIMERREC \
"CREATE TABLE timerrec ("\
      "id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"\
      "cid integer NOT NULL,"\
      "timeshift  integer,"\
      "recstart unsigned int(10) NOT NULL,"\
      "recend unsigned int(10) NOT NULL,"\
      "name tiny text NOT NULL)"

#define TAB_SHORTCUTS \
"CREATE TABLE shortcuts ("\
      "target VARCHAR(50) NOT NULL,"\
      "slot VARCHAR(100) NOT NULL,"\
      "key_sequence VARCHAR(25) NULL DEFAULT NULL,"\
      "PRIMARY KEY (target, slot))"

#define TAB_VOD_FAV \
"CREATE TABLE vodFav ("\
      "vodid integer PRIMARY KEY NOT NULL UNIQUE,"\
      "descr tiny text NOT NULL)"

#endif // __130610_TABLES_H
/************************* History ***************************\
| $Log$
\*************************************************************/