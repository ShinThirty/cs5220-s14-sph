#include <string.h>

#include "zmorton.h"
#include "binhash.h"

/*@q
 * ====================================================================
 */

/*@T
 * \subsection{Spatial hashing implementation}
 * 
 * In the current implementation, we assume [[HASH_DIM]] is $2^b$,
 * so that computing a bitwise of an integer with [[HASH_DIM]] extracts
 * the $b$ lowest-order bits.  We could make [[HASH_DIM]] be something
 * other than a power of two, but we would then need to compute an integer
 * modulus or something of that sort.
 * 
 *@c*/

#define HASH_MASK (HASH_DIM-1)

unsigned particle_bucket(particle_t* p, float h)
{
    unsigned ix = p->x[0]/h;
    unsigned iy = p->x[1]/h;
    unsigned iz = p->x[2]/h;
    return zm_encode(ix & HASH_MASK, iy & HASH_MASK, iz & HASH_MASK);
}

unsigned particle_neighborhood(unsigned* buckets, particle_t* p, float h)
{
    unsigned ix = p->x[0]/h;
    unsigned iy = p->x[1]/h;
    unsigned iz = p->x[2]/h;
    unsigned loc = 0;
    int i = 0;
    
    // Traverse through all surrouding bins and add their locations into array
    // buckets
    for (int diz = -1; diz <= 1; ++diz)
        for (int diy = -1; diy <= 1; ++diy)
            for (int dix = -1; dix <= 1; ++dix)
            {
                loc = zm_encode((ix+dix) & HASH_MASK, (iy+diy) & HASH_MASK, 
                        (iz+diz) & HASH_MASK);
                buckets[i++] = loc;
            }

    // Return the number of surrounding buckets
    return i;
}

void hash_particles(sim_state_t* s, float h)
{
    int n = s->n;
    particle_t* p = s->part;
    unsigned loc = 0;
    particle_t* pi;
    particle_t** hash = s->hash;

    // Clear the contents in the hash table to avoid interference from the
    // last state
    memset(hash, 0, HASH_SIZE * sizeof(particle_t*));

    // Traverse all the particles and rearrange them in the hash table
    for (int i = 0; i < n; ++i)
    {
        pi = p+i;
        loc = particle_bucket(pi, h);

        // Add the particle into the hash table
        pi->next = hash[loc];
        hash[loc] = pi;
    }
}
