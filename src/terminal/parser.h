/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     DOUBLE = 259,
     NAME = 260,
     STRING = 261,
     ENDCMD = 262,
     MODEL = 263,
     DATA = 264,
     IN = 265,
     TO = 266,
     INITS = 267,
     PARAMETERS = 268,
     COMPILE = 269,
     INITIALIZE = 270,
     ADAPT = 271,
     UPDATE = 272,
     BY = 273,
     MONITORS = 274,
     MONITOR = 275,
     TYPE = 276,
     SET = 277,
     CLEAR = 278,
     THIN = 279,
     CODA = 280,
     STEM = 281,
     EXIT = 282,
     NCHAINS = 283,
     CHAIN = 284,
     LOAD = 285,
     LIST = 286,
     STRUCTURE = 287,
     DIM = 288,
     NA = 289,
     R_NULL = 290,
     DIMNAMES = 291,
     ITER = 292,
     ARROW = 293,
     ENDDATA = 294,
     ASINTEGER = 295,
     DIRECTORY = 296,
     CD = 297,
     PWD = 298
   };
#endif
/* Tokens.  */
#define INT 258
#define DOUBLE 259
#define NAME 260
#define STRING 261
#define ENDCMD 262
#define MODEL 263
#define DATA 264
#define IN 265
#define TO 266
#define INITS 267
#define PARAMETERS 268
#define COMPILE 269
#define INITIALIZE 270
#define ADAPT 271
#define UPDATE 272
#define BY 273
#define MONITORS 274
#define MONITOR 275
#define TYPE 276
#define SET 277
#define CLEAR 278
#define THIN 279
#define CODA 280
#define STEM 281
#define EXIT 282
#define NCHAINS 283
#define CHAIN 284
#define LOAD 285
#define LIST 286
#define STRUCTURE 287
#define DIM 288
#define NA 289
#define R_NULL 290
#define DIMNAMES 291
#define ITER 292
#define ARROW 293
#define ENDDATA 294
#define ASINTEGER 295
#define DIRECTORY 296
#define CD 297
#define PWD 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 83 "parser.yy"
{
  int intval;
  double val;
  std::string *stringptr;
  ParseTree *ptree;
  std::vector<ParseTree*> *pvec;
  std::vector<double> *vec;
  std::vector<long> *ivec;
}
/* Line 1489 of yacc.c.  */
#line 145 "../../../JAGS/src/terminal/parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE zzlval;

