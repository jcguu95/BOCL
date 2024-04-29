#ifndef CONS_H
#define CONS_H

#include "object.h"

extern void ensure_cons_initialized(void);
extern object cfun_consp(object maybe_cons);
extern object cfun_cons(object car, object cdr);
extern object cfun_car(object cons);
extern object cfun_cdr(object cons);
extern object cfun_listp(object maybe_cons);
extern object cfun_length(object list);
extern object cfun_rplaca(object cons, object obj);
extern object cfun_rpldca(object cons, object obj);

/* extern object list1(object element); */
/* extern object list2(object element1, object element2); */
/* extern object list3(object element1, object element2, object element3); */
/* extern object list4(object element1, object element2, object element3, object element4); */
/* extern object list5(object element1, object element2, object element3, object element4, object element5); */
extern object cfun_list(object objects[], size_t size);

extern object class_cons;

#endif
