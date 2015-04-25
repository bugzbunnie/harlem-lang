
#include "2_node.h"

node* RecursiveReader (char AST[]);

node* Reader (token roll[], int* current)
{
    int tc = *current;
    node* dno = new node();
    tc ++;

    dno _Ty = roll [tc].value;

    tc += 1;
    dno _V  = roll [tc].value;
    tc ++;

    puts (dno _Ty .c_str());
    puts (dno _V .c_str());
    //getch();

    dno = CreateBranches (dno);

    *current = tc;

    for (int i = 0; roll [*current].value == "("; i ++)
    {
       dno -> child [i] = Reader (roll, current);
       *current += 1;
       dno _N ++;
    }
    *current += 1;

    return dno;
}

node* Preparation (char AST[], string* tablev, string* tablef)
{
    node* dno = new node();
    token roll [1000];

    for (int i = 0; AST [i] != '\0'; i++)
    {
        if (AST [i] == '[') AST [i] = '(';
        if (AST [i] == ']') AST [i] = ')';
    }

    PreAnalyze (AST, roll);
    Analyze    (roll     );
    PrintRoll  (roll     );

    int current = 0;

    current += 3;
    //string table [10][2];


        current ++;

        for (int i = 0; roll [current] .value != "VARS"; i ++)
        {
            tablef [i] = roll [current] .value;
            current ++;
        }


    current += 2;

    for (int i = 0; roll [current] .value != "("; i ++)
    {
        tablev [i] = roll [current] .value;
        current ++;
    }


    puts (roll [current] .value .c_str());

    dno = Reader (roll, &current);


    return dno;
}
