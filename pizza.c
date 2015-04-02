#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include "pizza.h"

int slicesAvailable = 0;

sem_t mutex;
sem_t order;


int main( int argc, const char* argv[] ) {
    sem_init( &mutex, 0, 1 );
    sem_init( &order, 0, 0 );

    int studentID[4];
    studentID[0] = 0;
    studentID[1] = 1;
    studentID[2] = 2;
    studentID[3] = 3;

    pthread_t studentOne;
    pthread_t studentTwo;
    pthread_t studentThree;
    pthread_t studentFour;
    pthread_create( &studentOne, NULL, (void *) &student, (void *) &studentID[0] );
    pthread_create( &studentTwo, NULL, (void *) &student, (void *) &studentID[1] );
    pthread_create( &studentThree, NULL, (void *) &student, (void *) &studentID[2] );
    pthread_create( &studentFour, NULL, (void *) &student, (void *) &studentID[3] );
    pthread_join( studentOne, NULL );
    pthread_join( studentTwo, NULL );
    pthread_join( studentThree, NULL );
    pthread_join( studentFour, NULL );


    pthread_t pizzaPlaceThread;
    pthread_create( &pizzaPlaceThread, NULL, (void *) &pizzaPlace, NULL );
    pthread_join( pizzaPlaceThread, NULL );

    sem_destroy( &mutex );
    sem_destroy( &order );

    printf("TEST");

    exit(0);

}

void pizzaPlace( void ) {
    while( true )
    {
        sem_wait( &order );
            sem_wait( &mutex );
                slicesAvailable = 8;
                printf("Pizza place received an order for 8 slices.");
            sem_post( &mutex );
    }
}

void student( void *studentID ) {
    int student = *((int *) studentID);
    while( true )
    {
        sem_wait( &mutex );
        if( slicesAvailable )
        {
            sem_post( &mutex );
            slicesAvailable--;
            eatAndCode( student , slicesAvailable+1);
        }
        else
        {
            int orderPlaced;
            sem_getvalue( &order, &orderPlaced );
            if( orderPlaced )
            {
                sem_post( &mutex );
                goofOff( student );
            }
            else
            {
                sem_post( &order );
                sem_post( &mutex );
                goofOff( student );
            }
        }
    }
}

void eatAndCode( int student, int slice ) {
    printf("student%d ate slice %d.\n", student, slice);
}

void goofOff( int student ) {
    printf("student%d is goofing off.\n", student);
}
