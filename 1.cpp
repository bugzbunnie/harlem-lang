
#include "1_recursive_down.h"

char code  [1000];
token roll [100] ;

int main ()
{
    FILE* nigga = fopen ("code.txt", "r");

    fread (code, 1, filelength (fileno (nigga)), nigga);
    puts  (code                                       );

    PreAnalyze (code, roll);
    Analyze    (roll      );
    //PrintRoll  (roll      );
    printf ("\n=============\n\n");

    node* ruta   = new node();
    node* func   = new node();
    node* vars   = new node();
    node* main   = new node();
    int* current = new int ();

    *current = 0;

    func = GetF (roll, current);
    vars = GetI (roll, current);
    main = GetM (roll, current);
    ruta = MakeRoot (func, vars, main);
    string* tablef = new string[10];
    string* tablev = new string[10];

    FILE* tree = fopen ("ast.txt", "w");

    fputs ("1 8\n", tree);

    PrintTable (func, vars, tablef, tablev, tree);
    puts (tablef[0].c_str());
    Print (ruta, tablef, tablev, tree);

    fclose (nigga);
    fclose (tree) ;
    return 0;
}


