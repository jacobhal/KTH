// sizeof(Data) = 12
struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
       //if (v[i] != 0)
            v[i] = new Data; // 12 bytes
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size]; // 5*8
    //foo(v, size);
    Data ** p = foo(v, size);
    delete [] p; // frigör pointer memory 5*8
}

/*
struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
       if (v[i] != 0)
            v[i] = new Data;
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    foo(v, size);
}
*/
