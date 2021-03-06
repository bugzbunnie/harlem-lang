
#include "node.h"

node* GetN (token roll [], int* current);
node* GetE (token roll [], int* current);
node* GetT (token roll [], int* current);
node* GetP (token roll [], int* current);
node* GetL (token roll [], int* current);
node* GetI (token roll [], int* current);
node* GetS (token roll [], int* current);
node* GetD (token roll [], int* current);
node* GetR (token roll [], int* current);


node* GetN (token roll [], int* current)
{
    node* dno = new node();
    if (roll [*current] .type == "num" || roll [*current] .type == "integer")
    {

        dno -> type  = roll [*current] .type ;
        dno -> value = roll [*current] .value;
        if (dno -> type == "num"    ) dno _Ty = "2";
        if (dno -> type == "integer") dno _Ty = "3";

        dno -> n     = 0                     ;

        //printf ("\n%s\n", roll [*current] .value .c_str());
    }
    return dno;
}

node* GetT (token roll [], int* current)
{
    node* dno  = new node();
    node* temp = new node();
    int tc = *current;

    dno = GetP (roll, current);
    tc += 1;

    if (!(dno -> child [0])) dno = CreateBranches (dno);


    while (roll [tc] .value == "*" || roll [tc] .value == "/")
    {
        string sym = roll [tc] .value;
        tc += 1;

        Copy (temp            , dno                 );
        Copy (dno -> child [0], temp                );
        Copy (dno -> child [1], GetP (roll, &tc));

        dno _Ty = "4";
        dno _V  = sym;
        if (dno _V == "*") dno _V = "4";
        else               dno _V = "5";
        dno _N  = 2  ;

        tc += 1;
    }

    *current = tc;
    return dno;
}

node* GetE (token roll [], int* current)
{
    node* dno  = new node();
    node* temp = new node();
    int tc = *current;

    dno = GetT (roll, &tc);

    if (!(dno -> child [0])) dno = CreateBranches (dno);


    while (roll [tc] .value == "+" || roll [tc] .value == "-")
    {
        string sym = roll [tc] .value;
        tc += 1;
        //Print (dno);
        Copy (temp            , dno             );
        Copy (dno -> child [0], temp            );
        Copy (dno -> child [1], GetT (roll, &tc));

        dno _Ty = "4";
        dno _V  = sym  ;
        if (dno _V == "+") dno _V = "2";
        else               dno _V = "3";
        dno _N  = 2    ;
        //tc += 1;
    }


    *current = tc;
    //Print (dno);
    return dno;
}

node* GetP (token roll [], int* current)
{

    node* dno = new node();
    if (roll [*current] .value == "(")
    {
        *current += 1;

        dno = GetE (roll, current);
        //*current += 1;
    }
    else
    {
        dno = GetN (roll, current);
    }

    return dno;
}

node* GetL (token roll [], int* current)
{
    node* dno  = new node();
    node* temp = new node();
    dno = CreateBranches (dno);

    dno = GetE (roll, current);
    //*current += 1;
    string s = roll [*current] .value;
    *current += 1;

    Copy (temp            , dno                 );
    Copy (dno -> child [0], temp                );
    Copy (dno -> child [1], GetE (roll, current));

    dno _Ty = "4";
    dno _V  = s  ;
    dno _N  = 2  ;

    if (dno _V == "homie") dno _V = "7";
    if (dno _V == "blacker") dno _V = "10";
    if (dno _V == "whiter") dno _V = "9";
    if (dno _V == "enemy") dno _V = "8";
    if (dno _V == "=") dno _V = "1";

    return dno;

}

node* GetI (token roll [], int* current)
{
    node* dno = new node();
    dno = CreateBranches (dno);
    int tc = *current;
    int i = 0;

    for (i = 0; roll [tc] .value == "nigga"; i ++)
    {
       tc += 1;
       dno -> child [i] = CreateBranches (dno -> child [i]);
       dno -> child [i] = GetN (roll, &tc);
       tc += 2;
       dno -> child [i] -> child [0] = GetN (roll, &tc);

       dno -> child [i] _N  = 1;
       //dno -> child [i] _Ty = "8";
       //dno -> child [i] _V  = "0";
       tc += 2;
       printf ("//%d//", tc);
    }

    dno _V  = "0";
    dno _Ty = "8";
    dno _N  = i;

    *current = tc;

    return dno;
}

node* GetD (token roll [], int* current)
{
    node* dno = new node();

    if (roll [*current] .value == "outta" || roll [*current] .value == "inda")
    {
        dno = CreateBranches (dno);
        dno _Ty = "7";
        if (roll [*current] .value == "outta") dno _V = "2";
        else                                   dno _V = "1";
        dno _N  = 1;

        *current += 1;

        dno -> child [0] = GetE (roll, current);

    }


    return dno;
}

node* GetS (token roll [], int* current)
{
    node* dno  = new node();
    node* temp = new node();

    int tc = *current;

    dno = CreateBranches (dno      );
    dno = GetN           (roll, &tc);

    dno _Ty = "5";
    dno _N  = 2  ;

    if (dno _V == "if")    dno _V = "1";
    if (dno _V == "else")  dno _V = "3";
    if (dno _V == "while") dno _V = "2";

    dno -> child [0] = new node();
    dno -> child [1] = new node();

    tc +=2;
    printf ("lol");
    dno -> child [0] _Ty = "5";
    dno -> child [0] _V  = "4";
    dno -> child [0] _N  =  1 ;
    dno -> child [0] = CreateBranches (dno -> child [0]);
    dno -> child [0] -> child [0] = GetL (roll, &tc);

    tc +=1;

    dno -> child [1] = GetR (roll, &tc);
    dno -> child [1] _Ty = "5";
    dno -> child [1] _V  = "5";

    *current = tc;
    return dno;
}

node* GetR (token roll [], int* current)
{
    node* dno = new node();
    dno = CreateBranches (dno);
    //if (roll [tc] .value != "{") {printf ("ERROR"
    int tc = *current;
    tc ++;
    int i = 0;

    for (i = 0; roll [tc] .value != "}"; i++)
    {
        if (roll [tc] .value == "inda" || roll [tc] .value == "outta")
        {
            dno -> child [i] = GetD (roll, &tc);
        }
        else if (roll [tc] .value == "while" || roll [tc] .value == "if" || roll [tc] .value == "else")
        {
            dno -> child [i] = GetS (roll, &tc);
            //tc ++;
        }
        else if (roll [tc] .type == "integer" && roll [tc + 1] .value == "=")
        {
            dno -> child [i] = GetL (roll, &tc);
        }
        else if (roll [tc] .type == "integer")
        {
            dno -> child [i] = GetN (roll, &tc);
            dno -> child [i] _Ty = "1";
            tc ++;
        }
//printf ("made");
        tc ++;
    }

    dno _Ty = "node" ;
    dno _V  = "block";
    dno _N  = i ;

    *current = tc;

    return dno;
}

node* GetM (token roll [], int* current)
{
    node* dno = new node ();


    dno _N  =  1 ;

    dno = CreateBranches (dno);
    int tc = *current;
    tc ++;

    dno    = GetR (roll, &tc);
    dno _Ty = "6";
    dno _V  = "0";

    return dno;
}

node* GetF (token roll [], int* current)
{
    node* dno = new node();
    dno = CreateBranches (dno);
    int tc = *current;
    int i = 0;

    for (i = 0; roll [tc] .value == "clip"; i ++)
    {
        tc += 1;

        node* temp = new node();
        temp = GetN (roll, &tc);

        tc += 1;
        dno -> child [i] = GetR (roll, &tc);
        dno -> child [i] _Ty = "1";
        dno -> child [i] _V = temp _V;

        tc ++;


       //printf ("//%d//", tc);
    }

   // dno _V  = "0";
    dno _Ty = "1";
    dno _N  = i;

    *current = tc;

    return dno;
}

node* MakeRoot (node* funcs, node* vars, node* main)
{
    node* root = new node();
    root = CreateBranches (root);

    if (funcs _N == 0)
    {
        root _N = 2;

        root -> child[0] = vars;
        root -> child[1] = main;
    }

    else
    {

        root -> child[0] = vars ;

        int i = 0;
        for (i = 0; i < funcs _N; i++)
        {
          root -> child[i + 1] = funcs -> child[i];
        }

        root -> child[i + 1] = main ;

        root _N = i + 2;
    }

    root _V =  "0";
    root _Ty = "0";

    return root;
}

void PrintTable (node* funcs, node* vars, string* tablef, string* tablev, FILE* tree)
{
   int i = 0;

   fprintf (tree, "FUNCS %d\n", funcs _N);

   for (i = 0; i < funcs _N; i ++)
   {
        fputs (funcs -> child [i] _V.c_str(), tree);
        fprintf (tree, "\n");
        tablef[i] = funcs -> child [i] _V;
   }


   fprintf (tree, "VARS %d\n", vars _N);

   for (i = 0; i < vars _N; i ++)
   {
        fputs (vars -> child [i]_V.c_str(), tree);
        fprintf (tree, "\n");
        tablev [i] = vars -> child [i] _V;
   }
}


