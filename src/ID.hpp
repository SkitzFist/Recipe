#ifndef _ID
#define _ID

struct ID
{
    int id;
    ID(int _id){
        id = _id;
    }
};

static const int getNewId(){
    static int counter = 0;
    return counter++;
}


#endif