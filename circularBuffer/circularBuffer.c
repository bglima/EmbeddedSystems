#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t *buffer;
    uint8_t size;
    uint8_t read;
    uint8_t write;
} CB;

uint8_t CBDataLength (CB *cb);
void CBSetMemory(CB *cb, uint8_t * memory);


#define createNewCB(name) CB name = {  {0}, 0, 0, 0 }

int main(int argc, const char* argv[] ) {
    uint8_t a[80];

    createNewCB(myBuffer);

    printf("Memory size of CB: %d\n", sizeof(myBuffer.buffer));
    
    CBSetMemory(&myBuffer, a);

    printf("Memory size of CB: %d\n", sizeof(myBuffer.buffer));

    return 0;


}

uint8_t CBDataLenght (CB *cb) {
    return ((cb->write - cb->read) & (cb->size - 1));
}

void CBSetMemory (CB *cb, uint8_t * memory) {
    cb->buffer = memory;
}
