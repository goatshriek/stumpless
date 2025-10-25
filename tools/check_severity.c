#include <stdio.h>
#include <stumpless/severity.h>
#include <stumpless/error.h>

int main(void)
{
    int r;
    const struct stumpless_error *err;

    r = stumpless_get_severity_enum_from_buffer("war", 3);
    printf("war(3) -> %d\n", r);
    err = stumpless_get_error();
    if (err)
        printf("error id: %d\n", stumpless_get_error_id(err));

    r = stumpless_get_severity_enum_from_buffer("not", 3);
    printf("not(3) -> %d\n", r);
    err = stumpless_get_error();
    if (err)
        printf("error id: %d\n", stumpless_get_error_id(err));

    r = stumpless_get_severity_enum_from_buffer(NULL, 0);
    printf("NULL(0) -> %d\n", r);
    err = stumpless_get_error();
    if (err)
        printf("error id: %d\n", stumpless_get_error_id(err));

    return 0;
}
