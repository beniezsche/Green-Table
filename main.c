#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

int main() {	
    initscr();			/* Start curses mode 		  */
    printw("Hello World !!!");	/* Print Hello World		  */
    		/* Print it on to the real screen */
    // getch();		/* Wait for user input */

    noecho();

    int y = 0;
    int x = 0;

    while(true) {

        int in = getch();

        // printf("%d", in);

        switch(in) {
            case 'e':
                printw("e pressed");
                refresh();
                // endwin();
                break;
            case 'w':
                y--;
                move(y, x);
                break;
            case 's':
                y++;
                move(y, x);
                refresh();
                break;
            case 'a':
                x--;
                move(y, x);
                break;
            case 'd':
                x++;
                move(y, x);
                break;
            default:
                endwin();
                break;
        }

    }


    return 0;
}

// int main() {

//     printf("\033[2J");

//     // Print a message
//     printf("Welcome to Green Table!\n");

//     int r = 255;
//     int g = 255;
//     int b = 255;

//     int increment = 100;

//     // printf("\033[38;2;255;82;197;48;2;155;106;0mHello This is a pink text on brown bg \n");
//     printf("\n");

    

//     // int myNum = 7;

//     // for(int i = 0; i < myNum; i++) {
//     //     printf("\n");
//     //     for(int j = 0; j < myNum; j++) {
//     //         printf("  (%d, %d)  ", i, j);
//     //     }
//     // }

//     for(int j = 0; j < 10; j++) {
//         for(int i = 0; i <= 8; i++) {


//             if (j == 0 && i == 0) {
//                 printf("\033[0m");
//                 printf("            ");
//             }
//             else if (j == 0 && i == 1) {
//                 printf("\033[48;2;4;101;13m");
//                 printf("     (A)    ");
//             }
//             else if (j == 0 && i == 2) {
//                 printf("     (B)    ");
//             }
//             else if (j == 0 && i == 3) {
//                 printf("     (C)    ");
//             }
//             else if (j == 0 && i == 4) {
//                 printf("     (D)    ");
//             }
//             else if (j == 0 && i == 5) {
//                 printf("     (E)    ");
//             }
//             else if (j == 0 && i == 6) {
//                 printf("     (F)    ");
//             }
//             else if (j == 0 && i == 7) {
//                 printf("     (G)    ");
//             }
//             else if (j == 0 && i == 8) {
//                 printf("     (H)    ");
//                 printf("\033[0m");
//             }
//             else if(j == 0) {
//                 printf("\033[48;2;4;101;13m");
//                 printf("     (%d)    ", j);
//                 printf("\033[0m");
//             }
//             else if(i == 0) {
//                 printf("\033[48;2;4;101;13m");
//                 printf("     (%d)    ", j);
//                 printf("\033[0m");
//             }
//             else {
//                 printf("%12d",rand() % 20);
//             }

//         }
//         printf("\n");
//     }



//     printf("\n");  


//     return 0;

// }