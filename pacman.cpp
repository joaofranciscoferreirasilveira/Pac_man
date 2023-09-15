#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>

#define height 15

using namespace std;
int keyCode = 0;
struct block{
    int X,Y;
    char S;
    };
block blocks[999] = {};
int quantBlock = 0;
int width;
/*
    | = │
    c = ┌
    C = ┐
    b = └
    ┘ = B
    ─ = -
    */
string _map[2][height]={
    {
    "c----------------C     c----------------C",
    "|P***************bC   cB***************P|",
    "|*c-*----**---C***b---B***c---**----*-C*|",
    "|*|***********|***********|***********|*|",
    "|****c--C**cC*|*---------*| cC**c--C****|",
    "b--C*|  |**||               ||**|  |*c--B",
    "---B*b--B**bB    c-   -C    bB**b--B*b---",
    "T                |  F  |                T",
    "---C***********  b-----B  ***********c---",
    "c--B*----------           ----------*b--C",
    "|***************************************|",
    "|*c--C*c---C*---*---W---*---*c---C*c--C*|",
    "|*b--B*b---B******  |  ******b---B*b--B*|",
    "|P***********c----C O c----C***********P|",
    "b------------B    b---B    b------------B"
    },
    {
    "c-----------------------------------------------------C",
    "|*****************************************************|",
    "|*---*c-------C*---------------*----- cC*----*-------*|",
    "|*****| c-----B*****************      ||**************|",
    "b---C*| |*******c-----C*c-----C c- -C ||*c-----C*c----B",
    "----B*| |*c---C*|c---C|*|c---C| | F | ||*|  c--B*b-----",
    "T    *| |*b-C |*||   ||*||   || S---s ||*|  |****    T",
    "----C*| b---B |*|b---B|*|b---B| b---B ||*|  b--C*c-----",
    "c---B*b-------B*b-----B*b-----B       bB*b-----B*b----C",
    "|*******************************--W--*****************|",
    "|*----*----------*|*-----------***|***---------*-----*|",
    "|*****************|*************|*O*|*****************|",
    "b-----------------w-------------w---w-----------------B",
    }

};
int fase = 0;
bool sair = 1;
COORD origin;
COORD pac;
int direcao = 1;
int direcaoEspera = 1;

COORD pCreateFant;
int quantFantasma = 0;
COORD fantasmas[4]={};
int directionFantasmas[4]={};

COORD pTeleport[2] = {};
int qPortr = 0;

COORD positionPontos[9999] = {};
int quanPositionPontos  = 0;
COORD positionPower[9999] = {};
int quanPositionPower  = 0;
bool inPower = 0;
int tempPower =0;
int pontos = 0;
bool ingame = 1;


//introdução
COORD gigaPac = {80,10};
int nubfan = 0;


int keyPressed(int key);
void trocaDeCor(int cor);
void gotoxy(int x,int y);
void createBlocks();
void drawMap();
void drawPac();
void deletPac();
void movPac();
void trocaDirecaoEspera();
void trocaDirecao();
void teleport();
void createFantasma();
void drawFantasma();
void deletFantasmas();
void movFantasmas();
void drawPontos();
void drawPower();
void coletarPontos();
void coletarPower();
void derota();
void vitoria();
void setFontSize(int FontSize);
void esconderCursor();
void configuracaoConsole();
void introducao();

int main(){
    configuracaoConsole();
    width = _map[fase][0].length();
    srand(time(NULL));
    //introdução
    introducao();
    //primeiro game
    createBlocks();
    trocaDeCor(1);
    drawMap();
    drawPac();
    drawPontos();
    drawPower();
    while(sair){
    while(ingame){
            //esconderCursor();
        teleport();
        if(kbhit()){
            trocaDirecaoEspera();
        }
        trocaDirecao();
        drawPontos();
        drawPower();
        movPac();
        derota();
        coletarPontos();
        coletarPower();
        movFantasmas();
        derota();
        vitoria();
        createFantasma();
        if(tempPower>0){
            tempPower--;
        }else{
            inPower = 0;
        }
        Sleep(100);
    }
    if(kbhit()){
        keyCode = getch();

        if(keyCode == 27){
                sair = 0;
                exit(0);
        }
        if(keyCode == 114){
            system("cls");
            width = _map[fase][0].length();
            ingame = 1;
            pontos = 0;
            quantFantasma = 0;
            quanPositionPontos = 0;
            quanPositionPower = 0;
            inPower = 0;
            quantBlock = 0;
            system("color 1");
            createBlocks();
            drawMap();
            drawPac();
            drawPontos();
        }
    }
    }

    trocaDeCor(0);
    gotoxy(0,height+1);
    return 0;
}

void movGigafantasmas(char type){



        ifstream meuArquivo ("gost.txt");

        if (meuArquivo.is_open()) //Verifica que o arquivo foi aberto
        {
            string linha = "";
            int quantLine=0;
            while ( getline (meuArquivo,linha) ) //A condi��o de parada do while � quando ogetline encontra o EOF (End Of File)
            {
                gotoxy(gigaPac.X-15, gigaPac.Y+quantLine);
                if(type == 'd'){

                    cout << linha << '\n'; //Imprime a linha na tela
                }else{

                for(int i =0;i<linha.length();i++){
                    cout << " ";
                }
                }
                quantLine++;

            }
            meuArquivo.close(); //Fecha o arquivo
        }


}
void movGigapac(char type,int frame){
    string file  ;
    if(frame == 0){
          file  = ("pacmandraw.txt");
    }else if(frame == 1){
        file  = ("pacmandraw2.txt");
    }else{
         file  = ("pacmandraw3.txt");

    }


        ifstream meuArquivo (file);

        if (meuArquivo.is_open()) //Verifica que o arquivo foi aberto
        {
            string linha = "";
            int quantLine=0;
            while ( getline (meuArquivo,linha) ) //A condi��o de parada do while � quando ogetline encontra o EOF (End Of File)
            {
                gotoxy(gigaPac.X, gigaPac.Y+quantLine);
                if(type == 'd'){

                    cout << linha << '\n'; //Imprime a linha na tela
                }else{

                for(int i =0;i<linha.length();i++){
                    cout << " ";
                }
                }
                quantLine++;

            }
            meuArquivo.close(); //Fecha o arquivo
        }


}
void introducao(){
    gotoxy(45,2);
    trocaDeCor(14);
    cout<<"pac-man";
      gotoxy(42,4);
      cout<<"por Pedro Vitor";
int sentAniamtio = 1;
for(int i =0;i<60;i++){
movGigapac('o',nubfan);
movGigafantasmas('o');
gigaPac.X--;
trocaDeCor(14);
movGigapac('d',nubfan);
trocaDeCor(12);
movGigafantasmas('d');
if(kbhit()){
    getch();

    break;

}
Sleep(51);
if(sentAniamtio){
nubfan++;
}else{
nubfan --;
}
if(nubfan == 3){
    sentAniamtio = 0;
}
if(nubfan == 0){
    sentAniamtio = 1;
}
}
system("cls");
}
void trocaDirecao(){
    if(direcaoEspera != direcao){
            bool mov =  1;
        switch(direcaoEspera){
        case 0://up
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y+1&&pac.X == blocks[i].X){
                    mov = 0;
                }
            }
            if(mov){
               direcao = direcaoEspera;
            }
        break;
        case 1://down
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y-1&&pac.X == blocks[i].X){
                    mov = 0;
                }
            }
            if(mov){
                direcao = direcaoEspera;
            }
        break;
        case 2://right
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y&&pac.X == blocks[i].X-1){
                    mov = 0;
                }
            }
            if(mov){
                direcao = direcaoEspera;
            }
        break;
        case 3://left
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y&&pac.X == blocks[i].X+1){
                    mov = 0;
                }
            }
            if(mov){
                direcao = direcaoEspera;
            }
        break;


    }


    }

}
void configuracaoConsole(){
    system("title pacman");
    setFontSize(25);
    HWND console = GetConsoleWindow();
    ShowWindow(console ,SW_SHOWMAXIMIZED);
    esconderCursor();
    system("color 1");

}
void esconderCursor(){
CONSOLE_CURSOR_INFO info; //passando informação do cursor
    info.dwSize = 1; //tamanho 0-normal 100-totalmente preenchido
    info.bVisible = false; //mostrar ou não
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}
void vitoria(){
    if(pontos >= quanPositionPontos){
        ingame = 0;fase++;
        gotoxy(width/2-7,0);
        trocaDeCor(10);
        cout<<"vitoria parabens";
    }
}
void derota(){

    for(int f = 0;f<quantFantasma;f++){

            if(fantasmas[f].X == pac.X&& fantasmas[f].Y == pac.Y){
                if(!inPower){
                    ingame = 0;
                    system("cls");
                    system("cls");
                    trocaDeCor(12);
                    gotoxy((width/2)-4,0);
                    cout<<"game Over";
                    trocaDeCor(7);
                    gotoxy((width/2)-4,3);
                    cout<<"(r)reniciar";
                    trocaDeCor(14);
                    gotoxy((width/2)+20,0);
                    cout<<"PONTOS: "<<pontos;
                 }else{
                    fantasmas[f] = pCreateFant;
                }

            }

    }
}
void coletarPontos(){
    for(int i =0;i<quanPositionPontos;i++){
        if(positionPontos[i].X == pac.X && positionPontos[i].Y==pac.Y){
            positionPontos[i].X = width+2;
            pontos++;
            gotoxy(width+2,10);
            cout<<"pontos: "<<pontos;

        }
    }
}
void drawPontos(){
    for(int i =0;i<quanPositionPontos;i++){
        gotoxy(positionPontos[i].X,positionPontos[i].Y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        if(positionPontos[i].X<=width)
            cout<<'*';
    }
}
void coletarPower(){
    for(int i =0;i<quanPositionPower;i++){
        if(positionPower[i].X == pac.X && positionPower[i].Y==pac.Y){
            positionPower[i].X = width+2;
            inPower = 1;
            tempPower = 50;
        }
    }
}


void drawPower(){
    for(int i =0;i<quanPositionPower;i++){
        gotoxy(positionPower[i].X,positionPower[i].Y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        if(positionPower[i].X<=width)
            cout<<char(207);
    }
}

void movFantasmas(){
    deletFantasmas();
    for(int f = 0;f<quantFantasma;f++){
        bool mov = 1;

        for(int i  = 0;i<qPortr;i++){
            if(fantasmas[f].X==pTeleport[i].X&&fantasmas[f].Y==pTeleport[i].Y){

                fantasmas[f] = pTeleport[i==0?1:0];
                break;
            }
        }
        if(rand()%2 == 1){//vou trocar minha direção?
            if(rand()%3 == 1){//movimento randomico
                directionFantasmas[f]  =  rand()%4;
            }else{//movimento logico
                if(rand()%2 == 1){//qual eixo vou movimentar
                    if(pac.X>fantasmas[f].X){
                        directionFantasmas[f] = 2;
                    }
                    if(pac.X<fantasmas[f].X){
                        directionFantasmas[f] = 3;
                    }
                }else{
                    if(pac.Y>fantasmas[f].Y){
                        directionFantasmas[f] = 1;
                    }
                    if(pac.Y<fantasmas[f].Y){
                        directionFantasmas[f] = 0;
                    }
                }
            }
        }


        switch( directionFantasmas[f]){
            case 0://up
                for(int b = 0;b<quantBlock;b++){
                    if(fantasmas[f].Y == blocks[b].Y+1&&
                       fantasmas[f].X == blocks[b].X){
                        mov = 0;

                    }
                }
                if(mov == 1){
                        if(fantasmas[f].Y>0)
                fantasmas[f].Y--;
                }
            break;
            case 1://down
                for(int b = 0;b<quantBlock;b++){
                    if(fantasmas[f].Y == blocks[b].Y-1&&
                       fantasmas[f].X == blocks[b].X){
                        mov = 0;

                    }
                }
                if(mov == 1){
                    fantasmas[f].Y++;
                }
            break;
            case 2://right
                for(int b = 0;b<quantBlock;b++){
                    if(fantasmas[f].Y == blocks[b].Y&&
                       fantasmas[f].X == blocks[b].X-1){
                        mov = 0;

                    }
                }
                if(mov == 1){
                    if(fantasmas[f].X<width-1)
                        fantasmas[f].X++;
                }
            break;
            case 3://left
                for(int b = 0;b<quantBlock;b++){
                    if(fantasmas[f].Y == blocks[b].Y&&
                       fantasmas[f].X == blocks[b].X+1){
                        mov = 0;

                    }
                }
                if(mov == 1){
                    if(fantasmas[f].X>0)
                        fantasmas[f].X--;
                }
        }

    }
    drawFantasma();
}
void deletFantasmas(){
    for(int i = 0;i<quantFantasma;i++){
        gotoxy(fantasmas[i].X,fantasmas[i].Y);
        cout<<' ';
    }
}
void drawFantasma(){
    for(int i = 0;i<quantFantasma;i++){
        gotoxy(fantasmas[i].X,fantasmas[i].Y);
        if(!inPower){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12+i);
        }else{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
        }
        cout<<'@';
    }
}
void createFantasma(){
    if(rand()%10 == 0&&quantFantasma<4){
        fantasmas[quantFantasma] = pCreateFant;
        quantFantasma++;

    }
}
void teleport(){

    for(int i  = 0;i<qPortr;i++){
        if(pac.X==pTeleport[i].X&&pac.Y==pTeleport[i].Y){
                deletPac();
            pac = pTeleport[i==0?1:0];
                break;
        }
    }

}
void trocaDirecaoEspera(){
     keyCode = getch();
    //#define ARROW_UP 72
    //#define ARROW_DOWN 80
    //#define ARROW_LEFT 75
    //#define ARROW_RIGHT 77

    if(keyPressed(VK_UP)){
        direcaoEspera = 0;
    }else
    if(keyPressed(VK_DOWN)){
        direcaoEspera = 1;
    }else
    if(keyPressed(VK_RIGHT)){
        direcaoEspera = 2;
    }
    else
    if(keyPressed(VK_LEFT)){
        direcaoEspera = 3;
    }
    switch(keyCode){
    case 27:
        deletPac();
        pac = origin;
        drawPac();

        case 'w':
            direcaoEspera = 0;
        break;

        case 's':
            direcaoEspera = 1;
        break;

        case 'd':
            direcaoEspera = 2;
        break;

        case 'a':
            direcaoEspera = 3;
        break;
    }
}
void movPac(){
    deletPac();
    bool mov = 1;
    if(keyCode!=-32)
    switch(direcao){
        case 0://up
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y+1&&pac.X == blocks[i].X){
                    mov = 0;
                }
            }
            if(mov){
                pac.Y--;
            }
        break;
        case 1://down
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y-1&&pac.X == blocks[i].X){
                    mov = 0;
                }
            }
            if(mov){
                pac.Y++;
            }
        break;
        case 2://right
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y&&pac.X == blocks[i].X-1){
                    mov = 0;
                }
            }
            if(mov){
                pac.X++;
            }
        break;
        case 3://left
            for(int i = 0;i<quantBlock;i++){
                if(pac.Y == blocks[i].Y&&pac.X == blocks[i].X+1){
                    mov = 0;
                }
            }
            if(mov){
                pac.X--;
            }
        break;


    }
    drawPac();
}
void deletPac(){
    gotoxy(pac.X,pac.Y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<' ';
}
void drawPac(){
    gotoxy(pac.X,pac.Y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<'G';
}
void drawMap(){
    int tempSleep = 1;
    for(int i = 0;i<quantBlock;i++){
        gotoxy(blocks[i].X,blocks[i].Y);
        cout<<char(blocks[i].S);
        if(kbhit()){
            tempSleep = 0;
        }
        Sleep(tempSleep);
    }
}
void createBlocks(){
    for(int y = 0;y<height;y++){
        for(int x = 0;x<_map[fase][0].length();x++){
            block blo;
            switch(_map[fase][y][x]){
                case 'P':
                    positionPower[quanPositionPower].X = x;
                    positionPower[quanPositionPower].Y = y;
                    quanPositionPower++;
                break;
                case 's':
                    blo.X = x;
                    blo.Y = y;
                    blo.S = 180;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'S':
                    blo.X = x;
                    blo.Y = y;
                    blo.S = 195;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'W':
                     blo.X = x;
                    blo.Y = y;
                    blo.S = 194;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'w':
                     blo.X = x;
                    blo.Y = y;
                    blo.S = 193;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case '*':
                    positionPontos[quanPositionPontos].X = x;
                    positionPontos[quanPositionPontos].Y = y;
                    quanPositionPontos++;
                break;
                case 'O':
                   origin = (COORD){x,y};
                    pac=origin;
                break;
                case 'F':
                    pCreateFant.X = x;
                    pCreateFant.Y = y;
                break;
                case 'T':
                    pTeleport[qPortr].X = x;
                    pTeleport[qPortr].Y = y;
                    gotoxy(0,height+2+qPortr);

                    qPortr++;
                break;
                case '|':
                    blo.X = x;
                    blo.Y = y;
                    blo.S = 179;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                 case '-':
                    blo.X = x;
                    blo.Y = y;
                    blo.S = 196;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'c':

                    blo.X = x;
                    blo.Y = y;
                    blo.S = 218;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'C':

                    blo.X = x;
                    blo.Y = y;
                    blo.S = 191;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'b':

                    blo.X = x;
                    blo.Y = y;
                    blo.S = 192;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                case 'B':

                    blo.X = x;
                    blo.Y = y;
                    blo.S = 217;
                    blocks[quantBlock] =blo;
                    quantBlock++;
                break;
                default:


                break;
            }

        }
    }
}
void gotoxy(int x,int y){
    COORD position;
    position.X =x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);
}
void trocaDeCor(int cor){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cor);
}
void setFontSize(int FontSize){
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = FontSize; // leave X as zero
    info.FontWeight   = FW_NORMAL;
    wcscpy(info.FaceName, L" Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}



