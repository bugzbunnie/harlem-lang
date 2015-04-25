
#include "lexics.h"

struct node
{
    string type;
    string value;
    int n;
    node * child [10];
};

 #define _N  ->n
 #define _Ty ->type
 #define _V  ->value

void Print (node* dno, string* tablef, string* tablev, FILE* tree)
{
   fputs ("[", tree);
   int i = 0;
   if (dno _Ty == "3")
   {
      for (i = 0; i < 10; i++)
      {
        if (dno _V == tablev [i]) dno _V = i+'0';
      }
   }

   if (dno _Ty == "1")
   {
      for (i = 0; i < 10; i++)
      {
        if (dno _V == tablef [i]) dno _V = i+'0';
      }
   }

   fprintf (tree, "%s %s", dno _Ty.c_str(), dno _V.c_str());
   //int i = 0;

   for (i = 0; i < dno _N; i += 1)
   {
        Print (dno -> child [i], tablef, tablev, tree);

        //if (i != (dno _N - 1)) printf (":");
   }
   fprintf (tree, " NULL]");
}

node* CreateBranches (node* dno)
{
    int i = 0;
    for (i = 0; i < 10; i+= 1)
    {
        dno -> child [i] = new node();
    }
    return dno;
}

void Copy (node* dno, node* original)
{
    assert (dno);
    assert (original);
    dno _Ty = original _Ty;
    //printf ("started");
    dno _V  = original _V ;
    dno _N  = original _N ;

    //memcpy (dno -> child, original -> child, sizeof(original -> child));
    int i = 0;
    for (i = 0; i < 10; i+= 1)
    {
        if (original -> child [i])
        {
            dno -> child [i] = new node();
            assert (dno -> child [i]);
            Copy (dno -> child [i], original -> child [i]);
        }
    }
}
