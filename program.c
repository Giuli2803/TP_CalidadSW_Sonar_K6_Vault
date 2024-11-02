#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void cargar_variables_entorno(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("No se pudo abrir el archivo .env");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (key && value) {
            setenv(key, value, 1);  // 1 para sobrescribir si ya existe
        }
    }

    fclose(file);
}

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char *)userp)[strcspn((char *)contents, "\n")] = '\0';
    strcat(userp, contents);
    return size * nmemb;
}

int main() {
    cargar_variables_entorno(".env");  // Cargar el archivo .env

    const char *VAULT_ADDR = getenv("VAULT_ADDR");
    const char *SECRET_PATH = getenv("SECRET_PATH");
    const char *token = getenv("VAULT_TOKEN");

    fprintf(stderr, "VAULT_ADDR: %s\n", VAULT_ADDR);
    fprintf(stderr, "SECRET_PATH: %s\n", SECRET_PATH);
    fprintf(stderr, "VAULT_TOKEN: %s\n", token);

    if (!token) {
        fprintf(stderr, "Token de Vault no encontrado. Configura la variable de entorno VAULT_TOKEN.\n");
        return 1;
    }

    CURL *curl = curl_easy_init();
    if(curl) {
        char url[256];
        char response[4096] = "";
        struct curl_slist *headers = NULL;

        snprintf(url, sizeof(url), "%s/v1/%s", VAULT_ADDR, SECRET_PATH);
        headers = curl_slist_append(headers, "Content-Type: application/json");

        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "X-Vault-Token: %s", token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "Error al consultar Vault: %s\n", curl_easy_strerror(res));
        else
            printf("Respuesta de Vault: %s\n", response);

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return 0;
}
