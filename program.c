#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* password = getenv("PASSWORD_OF_VAULT");
    const char* username = getenv("USERNAME_OF_VAULT");

    if (password) {
        printf("PASSWORD_OF_VAULT: %s\n", password);
    } else {
        printf("PASSWORD_OF_VAULT no está definida.\n");
    }

    if (username) {
        printf("USERNAME_OF_VAULT: %s\n", username);
    } else {
        printf("USERNAME_OF_VAULT no está definida.\n");
    }

    return 0;
}
