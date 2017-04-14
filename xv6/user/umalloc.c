#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
  struct {
    union header *ptr;
    uint size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

static struct spinlock baselock;
static struct spinlock freeplock;

void
free(void *ap)
{
  if (freeplock.created != 1) {
	  spin_init(&freeplock);
  }

  Header *bp, *p;

  bp = (Header*)ap - 1;
  spin_lock(&freeplock);
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if(p + p->s.size == bp){
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;

  spin_unlock(&freeplock);
}

/* Don't think morecore needs locking since they're already
 * held by the time malloc calls it
 */
static Header*
morecore(uint nu)
{
  char *p;
  Header *hp;

  if(nu < 4096)
    nu = 4096;
  p = sbrk(nu * sizeof(Header));
  if(p == (char*)-1)
    return 0;
  hp = (Header*)p;
  hp->s.size = nu;
  free((void*)(hp + 1));
  return freep;
}

void*
malloc(uint nbytes)
{
  /* Malloc should be the process' first entry point into this code, so this seems
   * appropriate for initializing these global locks
   */

  if (baselock.created != 1) {
	  spin_init(&baselock);
  }

  if (freeplock.created != 1) {
	  spin_init(&freeplock);
  }

  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;

  spin_lock(&baselock);
  spin_lock(&freeplock);
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    if(p->s.size >= nunits){
      if(p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;

      spin_unlock(&freeplock);
      spin_unlock(&baselock);
      return (void*)(p + 1);
    }
    if(p == freep) {
      spin_unlock(&freeplock);
      if((p = morecore(nunits)) == 0) {
	spin_unlock(&baselock);
        return 0;
      }
    }
  }
}
