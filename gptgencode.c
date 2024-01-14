#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

// Define the Cell data type
typedef struct {
    float value;
    char* label;
} Cell;

// Maximum number of columns
#define MAX_COLUMNS 26

// Create a 2D array of Cells (MAX_COLUMNS columns x 12 rows)
Cell cells[12][MAX_COLUMNS];

// Function to initialize the cells
void initializeCells() {
    for (int row = 0; row < 12; ++row) {
        for (int col = 0; col < MAX_COLUMNS; ++col) {
            cells[row][col].value = -1;
            cells[row][col].label = NULL;
        }
    }
}

// Function to get the current terminal width
int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

// Function to display the table using ncurses
void displayTable(int currentRow, int currentCol, int displayedColumns) {
    clear();
    
    // Display the input field at the top left corner
    // mvprintw(0, 0, "Enter value: ");

    // Set colors for headers
    attron(COLOR_PAIR(1));


    // Display column headers
    for (int col = 0; col < displayedColumns; ++col) {
        int actualCol = col + (currentCol / displayedColumns) * displayedColumns;
        if(actualCol < MAX_COLUMNS)
            mvprintw(2, (10 * (col)) + 3, "     %c    ", 'A' + actualCol);
    }

    attroff(COLOR_PAIR(1));

    for (int row = 0; row < 12; ++row) {
        // Display row headers
        attron(COLOR_PAIR(1));
        mvprintw(3 + row, 0, "%3d", row + 1);
        attroff(COLOR_PAIR(1));

        for (int col = 0; col < displayedColumns; ++col) {
            int actualCol = col + (currentCol / displayedColumns) * displayedColumns;

            if(actualCol >= MAX_COLUMNS)
                break; 

            if (row == currentRow && actualCol == currentCol) {
                attron(COLOR_PAIR(2)); // Highlight the current cell
            } else {
                // Set color for individual cells based on the original terminal window color
                attron(COLOR_PAIR(3));
            }

            if (cells[row][actualCol].label != NULL) {
                int len = strlen(cells[row][actualCol].label);

                for(int l = 0; l < 10; l++) {
                    printw("%c", cells[row][actualCol].label[l]);
                }

                for(int spc = 0; spc < 10 - len; spc++) {
                    printw(" ");
                }

                // printw("%-.10s", cells[row][actualCol].label);
                // printw("%-10ld", strlen(cells[row][actualCol].label));
            } 
            else if(cells[row][actualCol].value != -1) {

                float val = cells[row][actualCol].value;

                char rep[10];

                sprintf(rep, "%.02f", val);

                int len = strlen(rep);

                for(int spc = 0; spc < 10 - len; spc++) {
                    printw(" ");
                }

                for(int l = 0; l < 10; l++) {
                    printw("%c", rep[l]);
                }

                

                // printw("%s", rep);
            } 
            else {
                printw("          "); // Blank space
            }

            if (row == currentRow && actualCol == currentCol) {
                attroff(COLOR_PAIR(2));
            } else {
                attroff(COLOR_PAIR(3));
            }
        }
        printw("\n");
    }

    refresh();

    move(0,0);
}

// Function to handle user input and update the cells
void handleUserInput() {
    int ch;
    int currentRow = 0;
    int currentCol = 0;
    char inputBuffer[20];

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_UP:
                currentRow = (currentRow - 1 >= 0) ? currentRow - 1 : 0;
                break;
            case KEY_DOWN:
                currentRow = (currentRow + 1 < 12) ? currentRow + 1 : 11;
                break;
            case KEY_LEFT:
                currentCol = (currentCol - 1 >= 0) ? currentCol - 1 : 0;
                break;
            case KEY_RIGHT:
                currentCol = (currentCol + 1 < MAX_COLUMNS) ? currentCol + 1 : MAX_COLUMNS - 1;
                break;
            case '\n': // Enter key
                echo();
                // mvprintw(0, 0, "                         "); // Clear the previous input
                // mvprintw(0, 0, "Enter value: ");
                scanw("%[^\n]", inputBuffer);
                noecho();

                // Update the current cell with the entered value
                if (strlen(inputBuffer) > 0) {         

                    cells[currentRow][currentCol].value = 0.0;
                    cells[currentRow][currentCol].label = NULL;           

                    // char str[] = strdup(inputBuffer);
                    char *endptr;

                    float result = strtof(inputBuffer, &endptr);

                    if (*endptr != '\0') {
                        // Conversion failed
                        printf("Conversion failed. Not a valid integer.\n");
                        cells[currentRow][currentCol].label = strdup(inputBuffer);

                    } else {
                        // Conversion successful
                        printf("Converted value: %.02f\n", result);
                        cells[currentRow][currentCol].value = result;

                    }   

                    // cells[currentRow][currentCol].value = 0.0;
                    // cells[currentRow][currentCol].label = strdup(c);
                } else {
                    cells[currentRow][currentCol].value = 0.0;
                    cells[currentRow][currentCol].label = NULL;
                }
                break;
            default:
                break;

        }

        // Recalculate the number of displayed columns based on the current terminal width
        int terminalWidth = getTerminalWidth();
        int displayedColumns = (terminalWidth - 1) / 10; // 10 characters per column
        displayedColumns = (displayedColumns > MAX_COLUMNS) ? MAX_COLUMNS : displayedColumns;

        displayTable(currentRow, currentCol, displayedColumns);
    }
}

int main() {
    initscr();      // Initialize the library
    cbreak();       // Disable line buffering
    noecho();       // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys

    start_color();  // Enable color support

    // Define color pairs
    init_pair(1, COLOR_WHITE, COLOR_GREEN); // Color for headers
    init_pair(2, COLOR_WHITE, COLOR_GREEN);  // Color for the current cell
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Color for individual cells based on the original terminal window color
    // use_default_colors();
    initializeCells();

    // Get the initial terminal width and set the initial number of displayed columns
    int terminalWidth = getTerminalWidth();
    int displayedColumns = (terminalWidth - 1) / 10; // 10 characters per column
    displayedColumns = (displayedColumns > MAX_COLUMNS) ? MAX_COLUMNS : displayedColumns;

    displayTable(0, 0, displayedColumns);
    handleUserInput();

    endwin();       // Cleanup and close the library
    return 0;
}
