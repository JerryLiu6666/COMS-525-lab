#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int prize = rand() % 3;           // 0,1,2
    int notprize1 = (prize + 1) % 3;
    int notprize2 = (prize + 2) % 3;

    printf("\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf(" ** Monty Hall Simulator **\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("\n");

    int pick = -1;
    while (pick < 0 || pick > 2)
    {
        printf(" Pick a door (0, 1, or 2): ");
        if (scanf("%d", &pick) != 1) {
            printf(" Invalid input.\n");
            return 1;
        }
    }

    printf("\n You entered: %d\n", pick);

    int other, other_other;
    printf("\n Interesting choice ...\n");

    if (pick == prize)
    {
        int ss = rand() % 2;
        if (ss == 0)
        {
            other = notprize1;
            other_other = notprize2;
        }
        else
        {
            other = notprize2;
            other_other = notprize1;
        }
    }
    else
    {
        other_other = prize;
        if (pick == notprize1)
            other = notprize2;
        else
            other = notprize1;
    }

    printf("\n I can tell you for sure that the prize is not behind door: %d\n", other);

    int change = -1;
    while (change != 0 && change != 1)
    {
        printf("\n Stay with Door %d (press 0) or switch to Door %d (press 1): ", pick, other_other);
        if (scanf("%d", &change) != 1) {
            printf(" Invalid input.\n");
            return 1;
        }
    }

    int final_pick;
    if (change == 0)
    {
        final_pick = pick;
        printf("\n You stayed with Door %d\n", final_pick);
    }
    else
    {
        final_pick = other_other;
        printf("\n You switched to Door %d\n", final_pick);
    }

    if (final_pick == prize)
        printf("\n *** WINNER ***\n\n");
    else
        printf("\n --- LOSER ---\n\n");

    printf(" The prize was behind Door %d\n\n", prize);

    return 0;
}

