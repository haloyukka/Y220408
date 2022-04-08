#include <stdio.h>
#include <windows.h>
void  main()
{
    while (1)                                 // 無限ループ
    {
        system("cls");                          // 画面消去
        printf("                     \n");
        printf("              ***    \n");
        printf("             *       \n");
        printf("    *********        \n");
        printf("      ******         \n");
        printf("       *  *          \n");
        printf("      *    *         \n");
        printf("_y_y_y*y_y_y*y_y_y_y_\n");
        Sleep(500);                             // 500ミリ秒止まる

        system("cls");                          // 画面消去
        printf("                     \n");
        printf("             ***     \n");
        printf("             *       \n");
        printf("    *********        \n");
        printf("      ******         \n");
        printf("        **           \n");
        printf("        **           \n");
        printf("y_y_y_y_**y_y_y_y_y_y\n");
        Sleep(500);                             // 500ミリ秒止まる
    }
}
