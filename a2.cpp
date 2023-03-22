#include <xapian.h>
#include <iostream>

int main() {
    char *dbname = "test";
    Xapian::WritableDatabase db(dbname, Xapian::DB_CREATE_OR_OPEN);
    std::cout << "Hello, World" << std::endl;
    return 0;
}
