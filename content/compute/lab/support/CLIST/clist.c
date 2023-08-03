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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "clist.h"

typedef struct
{
  int count;          /* Number of items in the list. */
  int alloc_size;     /* Allocated size in quantity of items */
  int lastSearchPos;  /* Position of last search - firstMatch or LastMatch */
  size_t item_size;   /* Size of each item in bytes. */
  void *items;        /* Pointer to the list */
} CList_priv_;  

int CList_Realloc_(CList *l, int n)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (n < p->count)
  {
    fprintf(stderr, "CList: ERROR! Can not realloc to '%i' size - count is '%i'\n", n, p->count);
    assert(n >= p->count);
    return 0;
  }

  if (n == 0 && p->alloc_size == 0)
    n = 2;

  void *ptr = realloc(p->items, p->item_size * n);
  if (ptr == NULL)
  {
    fprintf(stderr, "CList: ERROR! Can not reallocate memory!\n");
    return 0;
  }
  p->items = ptr;
  p->alloc_size = n;
  return 1;
}

void *CList_Add_(CList *l, void *o)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (p->count == p->alloc_size && 
        CList_Realloc_(l, p->alloc_size * 2) == 0)
    return NULL;
  
  char *data = (char*) p->items;
  data = data + p->count * p->item_size;
  memcpy(data, o, p->item_size);
  p->count++;
  return data;
}

void *CList_Insert_(CList *l, void *o, int n)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (n < 0 || n > p->count)
  {
    fprintf(stderr, "CList: ERROR! Insert position outside range - %d; n - %d.\n", 
                        p->count, n);
    assert(n >= 0 && n <= p->count);
    return NULL;
  }

  if (p->count == p->alloc_size && 
        CList_Realloc_(l, p->alloc_size * 2) == 0)
    return NULL;

  size_t step = p->item_size;
  char *data = (char*) p->items + n * step;
  memmove(data + step, data, (p->count - n) * step);
  memcpy(data, o, step);
  p->count++;
  return data;
}

void *CList_Replace_(CList *l, void *o, int n)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (n < 0 || n >= p->count)
  {
    fprintf(stderr, "CList: ERROR! Replace position outside range - %d; n - %d.\n", 
                        p->count, n);
    assert(n >= 0 && n < p->count);
    return NULL;
  }

  char *data = (char*) p->items;
  data = data + n * p->item_size;
  memcpy(data, o, p->item_size);
  return data;
}

void CList_Remove_(CList *l, int n)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (n < 0 || n >= p->count)
  {
    fprintf(stderr, "CList: ERROR! Remove position outside range - %d; n - %d.\n",
                        p->count, n);
    assert(n >= 0 && n < p->count);
    return;
  }

  size_t step = p->item_size;
  char *data = (char*)p->items + n * step;
  memmove(data, data + step, (p->count - n - 1) * step);
  p->count--;

  if (p->alloc_size > 3 * p->count && p->alloc_size >= 4) /* Dont hold much memory */
    CList_Realloc_(l, p->alloc_size / 2);
}

void *CList_At_(CList *l, int n)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  if (n < 0 || n >= p->count)
  {
    fprintf(stderr, "CList: ERROR! Get position outside range - %d; n - %d.\n", 
                      p->count, n);
    assert(n >= 0 && n < p->count);
    return NULL;
  }

  char *data = (char*) p->items;
  data = data + n * p->item_size;
  return data;
}

void *CList_firstMatch_(CList *l, const void *o, size_t shift, size_t size, int string)
{
  CList_priv_ *p = (CList_priv_*) l->priv;    
  char *data = (char*) p->items;
  size_t step = p->item_size;
  p->lastSearchPos = -1;  

  if (shift + size > p->item_size)
  {
    fprintf(stderr, "CList: ERROR! Wrong ranges for firstMatch - "
                "shift '%zu', size '%zu', item_size '%zu'\n", shift, size, p->item_size);
    assert(shift + size <= p->item_size);
    return NULL;    
  }

  if (shift == 0 && size == 0)
    size = p->item_size;

  size_t i = shift;
  size_t end = p->count * step;
  int index = 0;

  if (string)
  {
    for (; i < end; i += step, index++)
    {
      if (strncmp(data + i, o, size) == 0)
      {
        p->lastSearchPos = index;  
        return (data + i - shift);
      }
    }
  }
  else
  {
    for (; i < end; i += step, index++)
    {
      if (memcmp(data + i, o, size) == 0)
      {
        p->lastSearchPos = index;
        return (data + i - shift);
      }
    }
  }

  return NULL;
}

void *CList_lastMatch_(struct CList *l, const void *o, size_t shift, size_t size, int string)
{
  CList_priv_ *p = (CList_priv_*) l->priv;    
  char *data = (char*) p->items;
  size_t step = p->item_size;
  p->lastSearchPos = -1;

  if (shift + size > p->item_size)
  {
    fprintf(stderr, "CList: ERROR! Wrong ranges for lastMatch - "
                "shift '%zu', size '%zu', item_size '%zu'\n", shift, size, p->item_size);
     assert(shift + size <= p->item_size);
    return NULL;
  }

  if (shift == 0 && size == 0)
    size = p->item_size;

  int index = p->count - 1;
  long i = index * step + shift;
  if (string)
  {  
    for (; i >= 0; i -= step, index--)
    {
      if (strncmp(data + i, o, size) == 0)
      {
        p->lastSearchPos = index;
        return (data + i - shift);
      }
    }
  }  
  else
  {  
    for (; i >= 0; i -= step, index--)
    {
      if (memcmp(data + i, o, size) == 0)
      {
        p->lastSearchPos = index;
        return (data + i - shift);
      }
    }
  }

  return NULL;  
}

int CList_index_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  return p->lastSearchPos;
}

int CList_swap_(CList *l, int a, int b)
{
  CList_priv_ *p = (CList_priv_*) l->priv;

  if (a < 0 || a >= p->count || b < 0 || b >= p->count)
  {
    fprintf(stderr, "CList: ERROR! Swap position outside range - %i, %i; count - %d.\n", 
                      a, b, p->count);
    assert(a >= 0 && a < p->count && b >= 0 && b < p->count);
    return 0;
  }

  if (a == b) return 1; /* ? Good ? :D */

  char *data = (char*) p->items;
  size_t step = p->item_size;

  if (p->count == p->alloc_size && 
        CList_Realloc_(l, p->alloc_size + 1) == 0)
    return 0;

  memcpy(data + p->count * step, data + a * step, step);
  memcpy(data + a * step, data + b * step, step);
  memcpy(data + b * step, data + p->count * step, step);
  return 1;
}

int CList_Count_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  return p->count;
}

int CList_AllocSize_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  return p->alloc_size;
}

size_t CList_ItemSize_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  return p->item_size;
}

void CList_Clear_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  free(p->items);
  p->items = NULL;
  p->alloc_size = 0;
  p->count = 0;
}

void CList_Free_(CList *l)
{
  CList_priv_ *p = (CList_priv_*) l->priv;
  free(p->items);
  free(p);
  free(l);
  l = NULL;
}

void CList_print_(CList *l, size_t shift, int n, const char *type)
{
  CList_priv_ *p = (CList_priv_*) l->priv;

  if (shift >= p->item_size)
  {
    fprintf(stderr, "CList: ERROR! Wrong shift value for list print - "
                "shift '%zu', item_size '%zu'\n", shift, p->item_size);
     assert(shift < p->item_size);
    return;
  }

  printf("\nCList:  count = %i  item_size = %zu   alloc_size = %i   type = %s\n",
                      p->count, p->item_size, p->alloc_size, type);

  if (n > 0)
  {
    int tp = -1;
    if (type == NULL) tp = 0;  /* Print out pointers */
    else if (strcmp(type, "char") == 0) tp = 1;
    else if (strcmp(type, "short") == 0) tp = 2;
    else if (strcmp(type, "int") == 0) tp = 3;
    else if (strcmp(type, "long") == 0) tp = 4;
    else if (strcmp(type, "uintptr_t") == 0) tp = 5;
    else if (strcmp(type, "size_t") == 0) tp = 6;
    else if (strcmp(type, "double") == 0) tp = 7;
    else if (strcmp(type, "string") == 0) tp = 8;

    if (tp == -1)
    {  
      fprintf(stderr, "CList: Can not print - not supported type - %s\n\n", type);
      return;
    }  

    n = (n > p->count) ? p->count : n;
    char *data = (char*) p->items + shift;
    size_t step = p->item_size;
    int i = 0;
    for (; i < n; i++)
    {
      switch (tp)
      {
        case 0: printf("%p  ", data); break;
        case 1: printf("%c ", *(char*) data); break;
        case 2: printf("%hi  ", *(short*) data); break;
        case 3: printf("%i  ", *(int*) data); break;
        case 4: printf("%li  ", *(long*) data); break;
        case 5: printf("0x%lx  ", *(uintptr_t*) data); break;
        case 6: printf("%zu  ", *(size_t*) data); break;
        case 7: printf("%f  ", *(double*) data); break;
        case 8: printf("%s\n", data); break;
        default: return;
      }  

      data += step;
    }
    printf("\n\n");
  }
}

CList *CList_init(size_t objSize)
{
  CList *lst = malloc(sizeof(CList));
  CList_priv_ *p = malloc(sizeof(CList_priv_));
  if (!lst || !p)
  {
    fprintf(stderr, "CList: ERROR! Can not allocate CList!\n");
    return NULL;
  }
  p->count = 0;
  p->alloc_size = 0;
  p->lastSearchPos = -1;
  p->item_size = objSize;
  p->items = NULL;
  lst->add = &CList_Add_;
  lst->insert = &CList_Insert_;
  lst->replace = &CList_Replace_;
  lst->remove = &CList_Remove_;
  lst->at = &CList_At_;
  lst->realloc = &CList_Realloc_;
  lst->count = &CList_Count_;
  lst->firstMatch = &CList_firstMatch_;
  lst->lastMatch = &CList_lastMatch_;
  lst->index = &CList_index_;
  lst->swap = &CList_swap_;
  lst->allocSize = &CList_AllocSize_;
  lst->itemSize = &CList_ItemSize_;
  lst->print = &CList_print_;
  lst->clear = &CList_Clear_;
  lst->free = &CList_Free_;
  lst->priv = p;
  return lst;
}

