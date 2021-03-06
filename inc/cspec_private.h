/*
 *  cspec_private.h
 *
 * See copyright notice in cspec.h
 *
 */
#ifndef CSPEC_PRIVATE_H
#define CSPEC_PRIVATE_H

int  CSpec_StartDescribe(const char *descr);
void CSpec_EndDescribe();

int  CSpec_StartIt(const char *descr);
void CSpec_EndIt();

int CSpec_StartBefore();
void CSpec_EndBefore();

void CSpec_End();

int CSpec_StartContext(const char *descr);
void CSpec_EndContext();


void CSpec_Eval(const char*filename, int line_number, const char*assertion, int assertionResult);
void CSpec_Pending(const char* reason);

#define CSPEC_EVAL(x)       { CSpec_Eval(__FILE__, __LINE__, #x, (x)); }
#define CSPEC_PENDING(reason)   { CSpec_Pending(reason); }

typedef void ( *CSpecTmpFunction )();
void CSpec_set_before( CSpecTmpFunction fun );

#endif

