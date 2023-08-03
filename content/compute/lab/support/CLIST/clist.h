/******************************************/
/*                                        */
/*        Alexander Agdgomlishvili        */
/*                                        */
/*         cdevelopment@mail.com          */
/*                                        */
/******************************************/


/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2020, Alexander Agdgomlishvili
 * cdevelopment@mail.com
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.

 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Github link: https://github.com/AlexanderAgd/CLIST */

#ifndef CLIST_H
#define CLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CList
{
  void * (* add)         (struct CList *l, void *o);            /* Add object to the end of a list */
  void * (* insert)      (struct CList *l, void *o, int n);     /* Insert object at position 'n' */
  void * (* replace)     (struct CList *l, void *o, int n);     /* Replace object at position 'n' */
  void   (* remove)      (struct CList *l, int n);              /* Remove object at position 'n' */
  void * (* at)          (struct CList *l, int n);              /* Get object at position 'n' */
  int    (* realloc)     (struct CList *l, int n);              /* Reallocate list to 'size' items */
  int    (* count)       (struct CList *l);                     /* Get list size in items */
  void * (* firstMatch)  (struct CList *l, const void *o, size_t shift, size_t size, int string);
                                                                /* Returns object with first match of string or byte compare */
  void * (* lastMatch)   (struct CList *l, const void *o, size_t shift, size_t size, int string);
                                                                /* Returns object with last match of string or byte compare */
  int    (* index)       (struct CList *l);                     /* Get index of previos search match */
  int    (* swap)        (struct CList *l, int a, int b);       /* Swap, replace two items with index a b */
  int    (* allocSize)   (struct CList *l);                     /* Get allocated size in items */
  size_t (* itemSize)    (struct CList *l);                     /* Get item size in bytes */
  void   (* print)       (struct CList *l, size_t shift, int n, const char *type);   /* Print list data */
  void   (* clear)       (struct CList *l);                     /* Clear list */
  void   (* free)        (struct CList *l);                     /* Destroy struct CList and all data */
  void  *priv;           /* NOT FOR USE, private data */
} CList;

CList *CList_init(size_t objSize); /* Set list object size in bytes */

/*  void *add(struct CList *l, void *o);
        Returns pointer to added object; Returns NULL if failed.

    void *insert(struct CList *l, void *o, int n);
        Returns pointer to inserted object; Returns NULL if failed.

    void *replace(struct CList *l, void *o, int n);
        Returns pointer to replaced object; Returns NULL if failed.

    void *at(struct CList *l, int n);
        Returns pointer to object at index n;

    int realloc(struct CList *l, int n);
        Return 1 when success. Returns 0 if failed.

    void *firstMatch(struct CList *l, const void *o, size_t shift, size_t size, int string);
        Returns pointer to list item when first match found. Straight scanning, from 0 to list end.
        Returns NULL if search failed.  

    void *lastMatch(struct CList *l, const void *o, size_t shift, size_t size, int string);
        Returns pointer to list item when first match found. Reverse scanning, from list end to 0.
        Returns NULL if search failed.

    int index(struct CList *l);
        Returns index of last search firstMatch or lastMatch. Returns -1 if search failed.
    
    void print(struct CList *l, size_t shift, int n, const char *type);
        Prints data of "int n" list items with offset "size_t shift" and type "const char *type".
        Supported types: char, short, int, long, uintptr_t, size_t, double, string.
        If type is NULL just pointers data will be printed. 
*/

#ifdef __cplusplus
}
#endif

#endif /* CLIST_H */
