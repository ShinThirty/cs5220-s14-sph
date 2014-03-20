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
<<<<<<< HEAD
    /* BEGIN TASK */
=======
>>>>>>> db14f5421786a69bb670c1fe6f53de7d2e20e1e2
    int ix = (unsigned)(p->x[0]/h) & HASH_MASK;
    int iy = (unsigned)(p->x[1]/h) & HASH_MASK;
    int iz = (unsigned)(p->x[2]/h) & HASH_MASK;
    unsigned loc = 0;
    unsigned i = 0;
    
    // Traverse through all surrouding bins and add their locations into array
    // buckets
    for (int diz = -1; diz <= 1; ++diz)
<<<<<<< HEAD
         if (iz+diz >=0 && iz+diz < HASH_DIM)
            for (int diy = -1; diy <= 1; ++diy) 
                 if (iy+diy >=0 && iy+diy < HASH_DIM)
                    for (int dix = -1; dix <= 1; ++dix)
                        if (ix+dix >=0 && ix+dix < HASH_DIM) {                                                                            loc = zm_encode(ix+dix, iy+diy, iz+diz);
                           buckets[i++] = loc;                                                                                                           }
   
                                                                                                                    // Return the number of surrounding buckets
    return i;




    /* END TASK */
=======
        if (iz+diz >=0 && iz+diz < HASH_DIM)
            for (int diy = -1; diy <= 1; ++diy) 
                if (iy+diy >=0 && iy+diy < HASH_DIM)
                    for (int dix = -1; dix <= 1; ++dix)
                        if (ix+dix >=0 && ix+dix < HASH_DIM) {
                            loc = zm_encode(ix+dix, iy+diy, iz+diz);
                            buckets[i++] = loc;
                        }

    // Return the number of surrounding buckets
    return i;
>>>>>>> db14f5421786a69bb670c1fe6f53de7d2e20e1e2
}

void hash_particles(sim_state_t* s, float h)
{
<<<<<<< HEAD
    /* BEGIN TASK */
=======
>>>>>>> db14f5421786a69bb670c1fe6f53de7d2e20e1e2
    int n = s->n;
    particle_t* p = s->part;
    unsigned loc = 0;
    particle_t* pi;
    particle_t** hash = s->hash;
<<<<<<< HEAD
    memset(hash, 0, HASH_SIZE * sizeof(particle_t*));
    for (int i = 0; i < n; ++i)
     {
        pi = p+i;
        loc = particle_bucket(pi, h);
        // Add the particle into the hash table
        pi->next = hash[loc];
        hash[loc] = pi;
     }
    /* END TASK */
=======

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
>>>>>>> db14f5421786a69bb670c1fe6f53de7d2e20e1e2
}
