#ifndef INPUT_H
#define INPUT_H

#define MAX_TESTCASES_BUNCH_SIZE 100

#define VECTOR_SIZE 8

#include <fstream>

struct testcase
{
	int rslen, haplen, *q, *i, *d, *c, *n_new;
	char *hap_alloc, *hap, *rs; //hap_alloc is the allocation, hap is offset for padding
   int index;
   double prob;
   void display()
   {
      printf("hap (len %d) = %s\n", haplen, hap);
      printf("rs (len %d) = %s\n", rslen, rs);
      printf("q = ");
      for (int z=0;z<rslen;z++) printf("%d  ", q[z]);
      printf("\n");
      printf("i = ");
      for (int z=0;z<rslen;z++) printf("%d  ", i[z]);
      printf("\n");
      printf("d = ");
      for (int z=0;z<rslen;z++) printf("%d  ", d[z]);
      printf("\n");
      printf("c = ");
      for (int z=0;z<rslen;z++) printf("%d  ", c[z]);
      printf("\n");
      printf("n_new = ");
      for (int z=0;z<rslen;z++) printf("%d  ", n_new[z]);
      printf("\n");
   }
   void free() 
   {
      //Free hap_alloc, not hap (which is a pointer within hap_alloc
      if (hap_alloc) delete [] hap_alloc;
      if (rs) delete [] rs;
      if (q) delete [] q;
      if (i) delete [] i;
      if (d) delete [] d;
      if (c) delete [] c;
      if (n_new) delete [] n_new;
      hap = rs = hap_alloc = NULL;
      q = i = c = d = n_new = NULL;
      rslen = haplen = 0;
   }
   testcase& operator=(const testcase& src)
   {
       rslen = src.rslen;
       haplen = src.haplen;
	    int sz = 1 + ((rslen + VECTOR_SIZE - 1) / VECTOR_SIZE) * VECTOR_SIZE;
       if (rslen > 0) 
       {
          q = new int[sz]();
          i = new int[sz]();
          c = new int[sz]();
          d = new int[sz]();
          n_new = new int[sz]();
       }
       if (src.hap) 
       {
          hap_alloc = new char[haplen + 2 * (sz-1) + 1]();
          hap = hap_alloc;
          hap += (sz-1);
          strncpy(hap, src.hap, src.haplen);
       } else {
          hap = hap_alloc = 0;
       }
       if (src.rs) 
       {
          rs = new char[sz]();
          strncpy(rs, src.rs, src.rslen);
       } else {
          rs = 0;
       }
       for (int z=0;z<rslen;z++) 
       {
           q[z] = src.q[z];
           i[z] = src.i[z];
           d[z] = src.d[z];
           c[z] = src.c[z];
           n_new[z] = src.n_new[z];
       }
       return *this;
   } 
   testcase() {
       hap = hap_alloc = rs = NULL;
       q = i = d = c = n_new = NULL;
       haplen = rslen = 0;
   }
   ~testcase() {
      free();
   }
};

int read_testcase(testcase *, std::istream&, bool=false);
int read_a_bunch_of_testcases(testcase *, int, std::fstream&);

#endif
