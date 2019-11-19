#include "format.h"
#include <cassert>

int main(int argc, char const *argv[])
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    return 0;
}