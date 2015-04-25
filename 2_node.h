
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

void Print (node* dno)
{
   printf ("[");


   printf ("%s %s", dno _Ty.c_str(), dno _V.c_str());
   //int i = 0;

   for (int i = 0; i < dno _N; i += 1)
   {
        Print (dno -> child [i]);

        //if (i != (dno _N - 1)) printf (":");
   }
   printf (" NULL]");
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
