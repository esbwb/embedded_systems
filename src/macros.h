#ifndef _MACROS_H_
#define _MACROS_H_ 1

#define digit_to_int(c) (c-48)

/* This can be used to print defined symbols as compiler messages */
#define STRING_MSG2(x) #x
#define STRING_MSG(x) STRING_MSG2(x)

#define UNUSED(x) x __attribute__((unused))

#endif
