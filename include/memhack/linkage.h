/*
 * This file defines macros that handle external linkage on all plattforms.
 */

#ifndef MH_LINKAGE_H
#define MH_LINKAGE_H

/*
 * Export/import function calls from/to dynamic link libraries based on whether
 * library ist build statically or dynamically is defined. MH_BUILD_STATIC for
 * static linkage, MH_BUILD_DYNAMIC for dynamic linkage. Omit both if you are
 * not building the library.
 */
#if !defined(DECLSPEC)

#if defined(MH_BUILD_STATIC) && defined(MH_BUILD_DYNAMIC)
#	error "Cannot build for static and dynamic linkage at the same time"
#endif

#if defined(_WIN32)
#	if defined(MH_BUILD_STATIC)
#		define DECLSPEC
#	elif defined(MH_BUILD_DYNAMIC)
#		define DECLSPEC __declspec(dllexport)
#	else
#		define DECLSPEC __declspec(dllimport)
#	endif
#else
#	define DECLSPEC
#endif

#endif

#endif