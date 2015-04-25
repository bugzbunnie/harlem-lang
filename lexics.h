
#include "txlib.h"

struct token
{
    string value;
    string type;
};

const int ReservedAmount = 7;

static string reservedWords [ReservedAmount] = { "nigga", "clique", "outta", "inda",
                                  "yall", "in_da_hood", "gtfo"};

static char limiters[] = {'{','}',',', '.', '(', ')', '[', ']', ':', ';', '+', '-', '*', '/', '<', '>', '=', '!'};

void PrintRoll (token least [])
{
    int i = 0;
    for (i = 0; least [i].type != "end"; i ++)
    {
        puts (least [i].value .c_str());
        puts (least [i].type  .c_str());
        printf ("_____\n");
    }
}

void PreAnalyze (char text [], token bill[])
{
    int i = 0;
    int counter = -1;

    while (text [i] != '\0')
    {
        int check = i;
        if (text [i] != ' ' && text [i] != '\n' && text [i] != '	')
        {
            if (text [i] >= 'A' && text [i] <= 'z') counter ++;
            while (text [i] >= 'A' && text [i] <= 'z')
            {
              bill [counter] .value += text [i];
              bill [counter] .type   = "abc";
               i++;
            }


            if (text [i] >= '0' && text [i] <= '9') counter ++;
            while (text [i] >= '0' && text [i] <= '9')
            {
              bill [counter] .value += text [i];
              bill [counter] .type   = "num";
               i++;
            }

            int j = 0;
            for (j = 0; limiters [j] != '\0'; j++)
            {
                if (text[i] == limiters [j])
                {
                    counter ++;
                   bill [counter] .value += text [i];
                   bill [counter] .type   = "lim";
                    i++;
                }
            }
        }

        else i ++;
        if (check == i) {printf ("error\n"); break;}
    }
    bill [counter + 1] .type = "end";
 }

void Analyze (token bill [])
{
   int i = 0;

   for (i = 0; bill [i].value != ""; i ++)
    {
        if (bill [i] .type == "abc")
        {
            int j = 0;

            for (j = 0; j < ReservedAmount; j++)
            {
                if (bill [i] .value == reservedWords [j])
                {
                    bill [i] .type = "reserved";
                }
                else
                    bill [i] .type = "integer";
            }
        }
    }
}
