#ifndef PACKAGE_H
#define PACKAGE_H

#include "object.h"

extern void ensure_package_initialized(void);
extern void ensure_package_initialized_2(void);

extern object package_slot_name(object package);
extern void set_package_slot_name(object package, object name);
extern object package_slot_nicknames(object package);
extern void set_package_slot_nicknames(object package, object name);
extern object cfun_packagep(object maybe_package);
extern object cfun_package_name(object maybe_package);
extern object cfun_find_symbol(object string, object package);
extern object cfun_intern(object string, object package);

extern object cfun_package_external_symbols(object package);
extern object cfun_package_internal_symbols(object package);
extern void package_add_external_symbol(object package, object symbol);
extern void package_add_internal_symbol(object package, object symbol);
extern void intern(object string, object package);

extern object class_package;

extern object package_common_lisp;
extern object package_common_lisp_user;

extern object package_keyword;

extern object current_package;

#endif
