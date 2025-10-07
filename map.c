#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define ROWS 25
#define COLS 87

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

int main() {
#ifdef _WIN32
    // Enable ANSI escape sequences on Windows CMD/PowerShell
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    const char *ascii[] = {
        "+---------------------------------------------------------------------------------+",
        "| ENTER                                                                           |",
        "| HERE                                                                            |",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|                                                                            EXIT |",
        "|                                                                            HERE |",
        "|---------------------------------------------------------------------------------|"
    };

    int asciiRows = sizeof(ascii) / sizeof(ascii[0]);
    char map[ROWS][COLS + 1];

    // Copy ASCII map into 2D array
    for (int i = 0; i < asciiRows && i < ROWS; i++) {
        strncpy(map[i], ascii[i], COLS);
        map[i][COLS] = '\0';
    }

    // Example: mark some parking spots


    // Print map with colors
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c = map[i][j];
            if (c == '+' || c == '-' || c == '|') {
                printf(CYAN "%c" RESET, c);  // Border -> cyan
            } else if (c == 'I' && i < ROWS-3) {
                printf(GREEN "%c" RESET, c);
            } else {
                printf("%c", c);             // Normal text
            }
        }
        printf("\n");
    }

    return 0;
}


    /*int main() {
        char map[ROWS][COLS + 1];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                map[i][j] = ' ';
            }

        }


        const char *ascii[] = {
        "+-------------------------------------------------------------------------------+",
        "| ENTER                                                                         |",
        "| HERE                                                                          |",
        "|----1            ----8----            ---14----            ---20----      26---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----2            ----9----            ---15----            ---21----      27---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----3            ---10----            ---16----            ---22----      28---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----4            ---11----            ---17----            ---23----      29---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----5            ---12----            ---18----            ---24----      30---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----6            ---13----            ---19----            ---25----      31---|",
        "|                     |                    |                    |               |",
        "|                     |                    |                    |               |",
        "|----7            ----+----            ----+----            ----+----      -----|",
        "|                                                                          EXIT |",
        "|                                                                          HERE |",
        "|-------------------------------------------------------------------------------|"
        };

        int asciiRows = sizeof(ascii) / sizeof(ascii[0]);

        for (int i = 0; i < asciiRows; i++) {
            strncpy(map[i], ascii[i], COLS);
        }

        for (int i = 0; i < ROWS; i++) {
            printf("%s\n", map[i]);
        }

        return 0;
    }*/
