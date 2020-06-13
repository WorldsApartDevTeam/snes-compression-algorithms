/* C mimic of Alloc.h from lzma-SDK.
Reverse engineered from Igor Pavlov : 7zTypes.h, Alloc.h  */

#ifndef __ALLOC_H
#define __ALLOC_H

typedef struct ISzAlloc ISzAlloc;
typedef const ISzAlloc * ISzAllocPtr;
void *MyAlloc(size_t size); // Desired allocated size.
void MyFree(void *address); // Space available.

struct ISzAlloc
{
  void *(*Alloc)(ISzAllocPtr p, size_t size);
  void (*Free)(ISzAllocPtr p, void *address); // address can be 0
};

/*
The below probably isn't necessary and just for 7zip's syntax. Ignore for now.

#define MidAlloc(size) MyAlloc(size)
#define MidFree(address) MyFree(address)
#define BigAlloc(size) MyAlloc(size)
#define BigFree(address) MyFree(address)

*/

typedef struct
{
  ISzAlloc vt;
  ISzAllocPtr baseAlloc;
  unsigned numAlignBits; /* ((1 << numAlignBits) >= sizeof(void *)) */
  size_t offset;         /* (offset == (k * sizeof(void *)) && offset < (1 << numAlignBits) */
} CAlignOffsetAlloc;

void AlignOffsetAlloc_CreateVTable(CAlignOffsetAlloc *p);


#endif