/* Fig. 5.24: main.c Card shuffling dealing program */ 
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;

void shuffle( int wDeck[][13] ); 

void show_cards(int wDeck[][13]); //Unit testing
void show_numbers(int wDeck[][13]);//second test
const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" }; 
const char *face[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
int testarr[60];

int main() { 
    
    srand(time(0)); 
    int deck[4][13] = {0}; 
    for (int i=0; i<100; i++){
        shuffle(deck); 
    
        show_cards(deck);
        show_numbers(deck);printf("\n");
        for (int j=1; j<=52; j++){
            
            printf("    ",testarr[j]);
        
        }
        printf("\n");
        
        for (int row = 0; row < 4; row++ ){
            for (int column = 0; column < 13; column++ ){
               deck[row][column]=0;
            }
        }
        
        
    }
    getchar();
    return 0; 
    }
    
    
    
void shuffle( int wDeck[][13] ) { 
    int row;
    int column;
    int card;
    for ( card = 1; card <= 52; card++ ) { 
        do { 
            row = rand() % 4; 
            column = rand() % 13; 
        } while( wDeck[row][column] != 0 ); 
    wDeck[ row ][ column ] = card; 
    }
}
    
void show_cards(int wDeck[][13]){
    int row;
    int column;
    int card;
    for ( card = 1; card <= 52; card++ ){
        row=column=0;
        while ( wDeck[row][column] != card){
            column++;
            if (column>12){
                column=0;
                row++;
            }
        }
        //printf("%s %s %d %d\n",face[column],suit[row],wDeck[row][column],card);
                
    }
}

void show_numbers(int wDeck[][13]){
    int row;
    int column;
    int card;
    for ( row = 0; row < 4; row++ ){
        for ( column = 0; column < 13; column++ ){
           printf("%3d",wDeck[row][column]);
           testarr[wDeck[row][column]]++;
           
        }
    }
}






