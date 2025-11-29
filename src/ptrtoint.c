/* Dereference a pointer to an integer
Useful for dereferencing function calls.
*/

int ptrtoint(void *v) {
        int     *pi;

        if(!v)
                return 0;
        pi = (int*) v;

        return *pi;
}
