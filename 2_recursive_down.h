
#include "2_reader.h"

int m_count = 0;

void GetN     (node* dno, FILE*  ASM);
void GetMath  (node* dno, FILE*  ASM);
void GetVars  (node* dno, FILE*  ASM);
void GetA     (node* dno, FILE*  ASM);
void GetIO    (node* dno, FILE*  ASM);
void GetIf    (node* dno, FILE*  ASM);
void GetWhile (node* dno, FILE*  ASM);
void GetNode  (node* dno, FILE*  ASM);
void GetMain  (node* dno, FILE*  ASM);
void GetFuncs (node* dno, FILE*  ASM);


void GetN     (node* dno, FILE*  ASM)
{
    if (dno _Ty == "3") fprintf (ASM, "\npushr %c", atoi (dno _V .c_str()) + '0');
    else if (dno _Ty == "2") fprintf (ASM, "\npush %s", dno _V .c_str());
}

void GetVars  (node* dno, FILE*  ASM)
{

    for (int i = 0; i < dno _N; i++)
    {
        fprintf (ASM, "\npush %s"  , dno -> child [i] -> child [0] _V.c_str());
        fprintf (ASM, "\npop %c", atoi(dno -> child [i]_V.c_str()) + '0');
    }
}

void GetMath  (node* dno, FILE*  ASM)
{
    if (dno _V == "2" && dno _Ty == "4")
    {
        Print (dno);
        Print (dno -> child [0]);
        Print (dno -> child [1]);
        GetMath (dno -> child [0], ASM);
        GetMath (dno -> child [1], ASM);
        fprintf  (ASM, "\nadd");
    }

    else if (dno _V == "3" && dno _Ty == "4")
    {
        GetMath (dno -> child [1], ASM);
        GetMath (dno -> child [0], ASM);
        fprintf  (ASM, "\nsub");
    }

    else if (dno _V == "4" && dno _Ty == "4")
    {
        Print (dno);
        GetMath (dno -> child [0], ASM);
        GetMath (dno -> child [1], ASM);
        fprintf  (ASM, "\nmul");
    }

    else if (dno _V == "5" && dno _Ty == "4")
    {
        GetMath (dno -> child [1], ASM);
        GetMath (dno -> child [0], ASM);
        fprintf   (ASM, "\ndiv");
    }
    else GetN (dno, ASM);
}

void GetA     (node* dno, FILE*  ASM)
{
    GetMath (dno -> child[1], ASM);
    fprintf   (ASM, "\npop %c", atoi (dno -> child[0] _V.c_str()) + '0');
}

void GetIO    (node* dno, FILE*  ASM)
{
    if (dno _V == "1")
    {
       // GetMath (dno -> child [0], ASM);
        fprintf (ASM, "\nin %c", atoi (dno -> child[0] _V.c_str()) + '0');
    }
    else if (dno _V == "2")
    {
        GetMath (dno -> child [0], ASM);
        fprintf (ASM, "\nout");
    }
}

void GetIf    (node* dno, FILE*  ASM)
{
    m_count ++;
    int tc = m_count;
    GetMath (dno -> child [0] -> child [0] -> child [0], ASM);
    GetMath (dno -> child [0] -> child [0] -> child [1], ASM);

    //fprintf (ASM, "\ncmp");

    if      (dno -> child [0] -> child [0] _V == "7")  fprintf (ASM, "\njne :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "8")  fprintf (ASM, "\nje :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "9")  fprintf (ASM, "\njbe :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "10") fprintf (ASM, "\njae :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "11") fprintf (ASM, "\njb :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "12") fprintf (ASM, "\nja :%d", m_count);

    int i = 0;

   //fprintf (ASM, " %d ", dno -> child [0] _N);
   //Print (

    while (i < dno -> child [1] _N)
    {
        //Print (dno -> child [1] -> child [i]);
        GetNode (dno -> child [1] -> child [i], ASM);

        i++;
    }

    fprintf (ASM, "\n:%d", tc);
}

void GetWhile (node* dno, FILE*  ASM)
{
    m_count ++;
    int tc2 = m_count;
    m_count ++;
    int tc = m_count;
    //Print (dno);
    fprintf (ASM, "\n:%d", tc2);

    GetMath (dno -> child [0] -> child [0] -> child [0], ASM);
    GetMath (dno -> child [0] -> child [0] -> child [1], ASM);

    //fprintf (ASM, "\ncmp");

    if      (dno -> child [0] -> child [0] _V == "7")  fprintf (ASM, "\njne :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "8")  fprintf (ASM, "\nje :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "9")  fprintf (ASM, "\njbe :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "10") fprintf (ASM, "\njae :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "11") fprintf (ASM, "\njb :%d", m_count);
    else if (dno -> child [0] -> child [0] _V == "12") fprintf (ASM, "\nja :%d", m_count);

    int i = 0;

   //fprintf (ASM, " %d ", dno -> child [0] _N);
   //Print (

    while (i < dno -> child [1] _N)
    {
        //Print (dno -> child [1] -> child [i]);
        GetNode (dno -> child [1] -> child [i], ASM);

        i++;
    }
    fprintf (ASM, "\njmp :%d", tc2);
    fprintf (ASM, "\n:%d", tc);
}

void GetNode  (node* dno, FILE*  ASM)
{
    if (dno _V == "1" && dno _Ty == "4")
        GetA (dno, ASM);
    if ((dno _V == "1" || dno _V == "2") && dno _Ty == "7")
        GetIO (dno, ASM);
    if (dno _V == "1" && dno _Ty == "5")
        GetIf (dno, ASM);
    if (dno _V == "2" && dno _Ty == "5")
        GetWhile (dno, ASM);
    if (dno _Ty == "1")
    {
        int temp = atoi (dno _V .c_str());
        fprintf (ASM, "\ncall :%d", temp);
    }
}

void GetMain  (node* dno, FILE*  ASM)
{
    int i = 0;

    while (i < dno _N)
    {
        GetNode (dno -> child [i], ASM);

        i++;
    }

    fprintf (ASM, "\nend");
}

void GetFuncs (node* dno, FILE*  ASM)
{
   int i = 1;
   for (i = 1; dno -> child [i] _Ty == "1"; i++)
   {
        fprintf (ASM, "\n:%d", i - 1);
        m_count ++;
        GetNode (dno -> child [i] -> child [0], ASM);
        fprintf (ASM, "\nret");
   }
}
