#include <stdio.h>
// _getch()関数を使用するための外部ライブラリ
#include <conio.h>
// system()関数を使用するための標準ライブラリ
#include <windows.h>
// exit()関数を使用するための外部ライブラリ
#include <stdlib.h>
#include <string.h>

void keyboard_input(int, int, int *);
void display_transition(int);

// 他ファイルで使用している関数のプロトタイプ宣言
#include "joint.h"

int main(void) {
    // 現在の選択画面を判別するための識別コード
    int currentStateNum = 0;

    // 文字コードをutf8に変更するシェルコマンド
    system("chcp 65001");

    // コマンドプロンプトのコマンド等の履歴をすべて消去するシェルコマンド
    system("cls");

    display_transition(currentStateNum);

    while(1) {
        // 入力したキーボードの文字を認識する関数で16進数で認識している。
        int getOnceNum = _getch();
        /*
        矢印キーが押された時に、一回目に矢印キー自体が押されたことを認識したあとに二回目でどの向きの矢印キーが押されたのかを
        識別するため二つの変数を用いて格納している。
        */
        int getTwiceNum = _getch();
        keyboard_input(getOnceNum, getTwiceNum, &currentStateNum);
    }

    return 0;
}

void keyboard_input(int getNumOnce, int getNumTwice, int *currentStateNum) {
    switch(getNumOnce) {
        // 矢印キーが押された場合
        case 0xe0:
            switch(getNumTwice) {
                // ↑キーが押された時
                case 0x48:
                    system("cls");
                    if(0<*currentStateNum && *currentStateNum<4) {
                        // ()をつけないと*演算子よりもインクリメントが優先され、アドレスをデクリメントすることになってしまうため、()を付ける。
                        (*currentStateNum)--;
                    }
                    display_transition(*currentStateNum);
                    break;
                // ↓キーが押された時
                case 0x50:
                    system("cls");
                    if(-1<*currentStateNum && *currentStateNum<3) {
                        (*currentStateNum)++;
                    }
                    display_transition(*currentStateNum);
                    break;
            }
            break;
        // Enterキーが押された時
        case 0xd:
            system("cls");
            switch(*currentStateNum) {
                case 1:
                    // 入力
                    input();
                    break;
                case 2:
                    // 検索
                    search();
                    break;
                case 3:
                    // メダルソート
                    break;
                case 4:
                    // 国名ソート
                    break;
            }
            break;
        // Escキーが押された時
        case 0x1b:
            system("cls");
            // コマンドプロンプトを強制終了する
            exit(0);
            break;
    }
}

void display_transition(int currentStateNum) {
    char *normalState[4] = {"  入力\n", "  検索\n", "  メダル総獲得順一覧\n", "  国名順一覧\n"};
    char *selectState[4];
    char allow[50] = "➤";
    strcat(allow, normalState[currentStateNum]);

    for(int i = 0; i < 4; i++) {
        selectState[i] = normalState[i];
        selectState[currentStateNum] = allow;
        printf("%s", selectState[i]);
    }
}