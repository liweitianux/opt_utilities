/*
                 __________                                      
    _____   __ __\______   \_____  _______  ______  ____ _______ 
   /     \ |  |  \|     ___/\__  \ \_  __ \/  ___/_/ __ \\_  __ \
  |  Y Y  \|  |  /|    |     / __ \_|  | \/\___ \ \  ___/ |  | \/
  |__|_|  /|____/ |____|    (____  /|__|  /____  > \___  >|__|   
        \/                       \/            \/      \/        
  Copyright (C) 2004-2006 Ingo Berg

  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/

// Folgender ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren 
// aus einer DLL vereinfachen. Alle Dateien in der DLL werden mit dem MUPARSERLIB_EXPORTS-Symbol
// kompiliert, das in der Befehlszeile definiert wurde. Das Symbol darf nicht für ein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, erkennen 
// MUPARSERLIB_API-Funktionen als aus einer DLL importiert, während die DLL mit diesem Makro
// definierte Symbole als exportiert ansieht.
#ifndef MU_PARSER_DLL_H
#define MU_PARSER_DLL_H

#ifdef MUPARSERLIB_EXPORTS
#define MU_PARSER_API __declspec(dllexport) 
#else
#define MU_PARSER_API __declspec(dllimport) 
#endif


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef void* parser_handle;
typedef double (*fun_type1)(double); 
typedef double (*fun_type2)(double, double); 
typedef double (*fun_type3)(double, double, double); 
typedef double (*fun_type4)(double, double, double, double); 
typedef double (*fun_type5)(double, double, double, double, double); 
typedef double (*multfun_type)(const double*, int);
typedef double (*strfun_type1)(const char*);
typedef double (*strfun_type2)(const char*, double);
typedef double (*strfun_type3)(const char*, double, double);
typedef void (*errhandler_type)();
typedef double* (*facfun_type)(const char*, void *);
typedef bool (*identfun_type)(const char*, int&, double&);

extern "C"
{

// Basic operations / initialization  
MU_PARSER_API parser_handle mupInit();
MU_PARSER_API void mupRelease(parser_handle a_hParser);
MU_PARSER_API const char* mupGetExpr(parser_handle a_hParser);
MU_PARSER_API void mupSetExpr(parser_handle a_hParser, const char *a_szExpr);
MU_PARSER_API void mupSetErrorHandler(errhandler_type a_pErrHandler);
MU_PARSER_API void mupSetVarFactory(parser_handle a_hParser, facfun_type a_pFactory, void *pUserData);

MU_PARSER_API double mupEval(parser_handle a_hParser);

// Defining callbacks / variables / constants
MU_PARSER_API void mupDefineFun1(parser_handle a_hParser, const char *a_szName, fun_type1 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineFun2(parser_handle a_hParser, const char *a_szName, fun_type2 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineFun3(parser_handle a_hParser, const char *a_szName, fun_type3 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineFun4(parser_handle a_hParser, const char *a_szName, fun_type4 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineFun5(parser_handle a_hParser, const char *a_szName, fun_type5 a_pFun, bool a_bAllowOpt = true);
// string functions
MU_PARSER_API void mupDefineStrFun1(parser_handle a_hParser, const char *a_szName, strfun_type1 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineStrFun2(parser_handle a_hParser, const char *a_szName, strfun_type2 a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineStrFun3(parser_handle a_hParser, const char *a_szName, strfun_type3 a_pFun, bool a_bAllowOpt = true);

MU_PARSER_API void mupDefineMultFun(parser_handle a_hParser, const char *a_szName, multfun_type a_pFun, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineOprt(parser_handle a_hParser, const char *a_szName, fun_type2 a_pFun, int a_iPri = 0, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineConst(parser_handle a_hParser, const char *a_szName, double a_fVal);
MU_PARSER_API void mupDefineStrConst(parser_handle a_hParser, const char *a_szName, const char *a_sVal);
MU_PARSER_API void mupDefineVar(parser_handle a_hParser, const char *a_szName, double *a_fVar);
MU_PARSER_API void mupDefinePostfixOprt(parser_handle a_hParser, const char *a_szName, fun_type1 a_pOprt, bool a_bAllowOpt = true);
MU_PARSER_API void mupDefineInfixOprt(parser_handle a_hParser, const char *a_szName, fun_type1 a_pOprt, bool a_bAllowOpt=true);

// Define character sets for identifiers
MU_PARSER_API void mupDefineNameChars(parser_handle a_hParser, const char *a_szCharset);
MU_PARSER_API void mupDefineOprtChars(parser_handle a_hParser, const char *a_szCharset);
MU_PARSER_API void mupDefineInfixOprtChars(parser_handle a_hParser, const char *a_szCharset);

// Remove all / single variables
MU_PARSER_API void mupRemoveVar(parser_handle a_hParser, const char *a_szName);
MU_PARSER_API void mupClearVar(parser_handle a_hParser);
MU_PARSER_API void mupClearConst(parser_handle a_hParser);
MU_PARSER_API void mupClearOprt(parser_handle a_hParser);

// Querying variables / expression variables / constants
MU_PARSER_API int mupGetExprVarNum(parser_handle a_hParser);
MU_PARSER_API int mupGetVarNum(parser_handle a_hParser);
MU_PARSER_API int mupGetConstNum(parser_handle a_hParser);
MU_PARSER_API void mupGetExprVar(parser_handle a_hParser, unsigned a_iVar, const char **a_pszName, double **a_pVar);
MU_PARSER_API void mupGetVar(parser_handle a_hParser, unsigned a_iVar, const char **a_pszName, double **a_pVar);
MU_PARSER_API void mupGetConst(parser_handle a_hParser, unsigned a_iVar, const char **a_pszName, double &a_pVar);

// Add value recognition callbacks
MU_PARSER_API void mupAddValIdent(parser_handle a_hParser, identfun_type);

// Error handling
MU_PARSER_API bool mupError();
MU_PARSER_API void mupErrorReset();
MU_PARSER_API const char* mupGetErrorMsg();
MU_PARSER_API int mupGetErrorCode();
MU_PARSER_API int mupGetErrorPos();
MU_PARSER_API const char* mupGetErrorToken();

} // extern "C"

#endif
