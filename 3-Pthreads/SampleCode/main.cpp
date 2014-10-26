#include <pthread.h>
#include <iostream>

struct point {
    int x; int y;
};


void* func( void* ptr ) 
{
    point* p = ( point* )ptr;
    std::cout << p->x << " " << p->y << std::endl;
    pthread_exit( NULL );
}


int main() 
{
    point var;  
    var.x = 10; var.y = 20; 
    
    pthread_t thread;
    int ret = pthread_create( &thread, NULL, func, ( void* )( &var ) );
    
    pthread_join( thread, NULL );
    
    return 0;
}