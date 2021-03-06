////////////////////////////////////////////////////////////
// emacs edit mode for this file is -*- C++ -*-
// $Id$
////////////////////////////////////////////////////////////
#ifndef INCL_REORDER_H
#define INCL_REORDER_H

#include <factory/factory.h>
#include <tmpl_inst.h>  // for typedef's

/*BEGINPUBLIC*/
// the next three give you a heuristically optimal reorderd list of the
// variables. For internal and external (e.g. Singular/Macaulay2) library use.
// This is really experimental!
// See the comments in reorder.cc.
// 
// this gives you a heuristically optimal ordering for the ring variables
// if you use the irreducible characteristic series.
Varlist  neworder( const CFList & PolyList );
// the same as neworder(...) only returning a list of CanonicalForm 's
// (i.e. the variables as CanonicalForms)
CFList   newordercf(const CFList & PolyList );
// the same as neworder(...) only returning a list of int 's (i.e. the levels)
IntList  neworderint(const CFList & PolyList );

// for library internal use only:
// next function reorders the variables in PS:
// a code segment to use:
// ...
// #include <tmpl_inst.h> // for typedef's
// CFList PS= <setup-your-list-of-CanonicalForms>;
// Varlist betterorder= neworder(PS);
// PS= reorder(betterorder,PS); // reorder variables in PS from oldorder 
//                                 to betterorder
// ListCFList Q= IrrCharSeries( PS );
// Q= reorder(betterorder,Q);   // revert ordering to oldorder
// 
CFList reorder( const Varlist & betterorder, const CFList & PS);
CFFList reorder( const Varlist & betterorder, const CFFList & PS);
ListCFList reorder(const Varlist & betterorder, const ListCFList & Q);
/*ENDPUBLIC*/

#endif /* INCL_REORDER_H */
