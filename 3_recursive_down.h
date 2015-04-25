
#include "2_reader.h"

int m_count = 0;

void GetN     (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetMath  (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetVars  (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetA     (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetIO    (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetIf    (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetWhile (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetNode  (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetMain  (node* dno, FILE*  ASM, string* tablef, string* tablev);
void GetFuncs (node* dno, FILE*  ASM, string* tablef, string* tablev);


void GetN     (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    if (dno _Ty == "3") fprintf (ASM, "%s", tablev [atoi (dno _V .c_str())].c_str());
    else if (dno _Ty == "2") fprintf (ASM, "%s", dno _V .c_str());
}

void GetVars  (node* dno, FILE*  ASM, string* tablef, string* tablev)
{

    for (int i = 0; i < dno _N; i++)
    {
        fprintf (ASM, "%s = %s;\n"  , tablev [atoi(dno -> child [i]_V.c_str())].c_str(),
         dno -> child [i] -> child [0] _V.c_str());
    }
}

void GetMath  (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    if (dno _V == "2" && dno _Ty == "4")
    {
        fprintf  (ASM, "(");
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf  (ASM, " + ");
        GetMath (dno -> child [1], ASM, tablef, tablev);
        fprintf  (ASM, ")");
    }

    else if (dno _V == "3" && dno _Ty == "4")
    {
        fprintf  (ASM, "(");
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf  (ASM, " - ");
        GetMath (dno -> child [1], ASM, tablef, tablev);
        fprintf  (ASM, ")");
    }

    else if (dno _V == "4" && dno _Ty == "4")
    {
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf  (ASM, " * ");
        GetMath (dno -> child [1], ASM, tablef, tablev);
    }

    else if (dno _V == "5" && dno _Ty == "4")
    {
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf  (ASM, " / ");
        GetMath (dno -> child [1], ASM, tablef, tablev);
    }
    else GetN (dno, ASM, tablef, tablev);
}

void GetA     (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    fprintf   (ASM, "%s = ", tablev [atoi (dno -> child[0] _V.c_str())] .c_str());
    GetMath (dno -> child[1], ASM, tablef, tablev);
    fprintf (ASM, ";\n");
}

void GetIO    (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    if (dno _V == "1")
    {
        fprintf (ASM, "inda ");
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf (ASM, ";\n");
    }
    else if (dno _V == "2")
    {
        fprintf (ASM, "outta ");
        GetMath (dno -> child [0], ASM, tablef, tablev);
        fprintf (ASM, ";\n");
    }
}

void GetIf    (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    m_count ++;
    int tc = m_count;
    fprintf (ASM, "if (");
    GetMath (dno -> child [0] -> child [0] -> child [0], ASM, tablef, tablev);

    if      (dno -> child [0] -> child [0] _V == "7")  fprintf (ASM, " homie ", m_count);
    else if (dno -> child [0] -> child [0] _V == "8")  fprintf (ASM, " enemy ", m_count);
    else if (dno -> child [0] -> child [0] _V == "9")  fprintf (ASM, " whiter ", m_count);
    else if (dno -> child [0] -> child [0] _V == "10") fprintf (ASM, " blacker ", m_count);
    else if (dno -> child [0] -> child [0] _V == "11") fprintf (ASM, " blacka ", m_count);
    else if (dno -> child [0] -> child [0] _V == "12") fprintf (ASM, " whita ", m_count);

    GetMath (dno -> child [0] -> child [0] -> child [1], ASM, tablef, tablev);
    fprintf (ASM, ")\n");
    int i = 0;

    fprintf (ASM, "{\n");

    while (i < dno -> child [1] _N)
    {
        //Print (dno -> child [1] -> child [i]);
        GetNode (dno -> child [1] -> child [i], ASM, tablef, tablev);

        i++;
    }

    fprintf (ASM, "}\n", tc);
}

void GetWhile (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    m_count ++;
    int tc = m_count;
    fprintf (ASM, "while (");
    GetMath (dno -> child [0] -> child [0] -> child [0], ASM, tablef, tablev);

    if      (dno -> child [0] -> child [0] _V == "7")  fprintf (ASM, " homie ", m_count);
    else if (dno -> child [0] -> child [0] _V == "8")  fprintf (ASM, " enemy ", m_count);
    else if (dno -> child [0] -> child [0] _V == "9")  fprintf (ASM, " whiter ", m_count);
    else if (dno -> child [0] -> child [0] _V == "10") fprintf (ASM, " blacker ", m_count);
    else if (dno -> child [0] -> child [0] _V == "11") fprintf (ASM, " blacka ", m_count);
    else if (dno -> child [0] -> child [0] _V == "12") fprintf (ASM, " whita ", m_count);

    GetMath (dno -> child [0] -> child [0] -> child [1], ASM, tablef, tablev);
    fprintf (ASM, ")\n");
    int i = 0;

    fprintf (ASM, "{\n");

    while (i < dno -> child [1] _N)
    {
        //Print (dno -> child [1] -> child [i]);
        GetNode (dno -> child [1] -> child [i], ASM, tablef, tablev);

        i++;
    }

    fprintf (ASM, "}\n", tc);
}

void GetNode  (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    if (dno _V == "1" && dno _Ty == "4")
        GetA (dno, ASM, tablef, tablev);
    if ((dno _V == "1" || dno _V == "2") && dno _Ty == "7")
        GetIO (dno, ASM, tablef, tablev);
    if (dno _V == "1" && dno _Ty == "5")
        GetIf (dno, ASM, tablef, tablev);
    if (dno _V == "2" && dno _Ty == "5")
        GetWhile (dno, ASM, tablef, tablev);
    if (dno _Ty == "1")
    {
        int temp = atoi (dno _V .c_str());
        fprintf (ASM, "%s;\n", tablef [temp] .c_str());
    }
}

void GetMain  (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
    int i = 0;
    fprintf (ASM, "inda_hood\n{\n");
    while (i < dno _N)
    {
        GetNode (dno -> child [i], ASM, tablef, tablev);

        i++;
    }

    fprintf (ASM, "}");
}

void GetFuncs (node* dno, FILE*  ASM, string* tablef, string* tablev)
{
   int i = 1;
   for (i = 1; dno -> child [i] _Ty == "1"; i++)
   {
        fprintf (ASM, "%s\n{\n", tablef [i - 1] .c_str());
        GetNode (dno -> child [i] -> child [0], ASM, tablef, tablev);
        fprintf (ASM, "}\n");
   }

}
