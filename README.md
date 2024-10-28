
Instalación en Linux

```bash
sudo gpg -k
sudo gpg --no-default-keyring --keyring /usr/share/keyrings/k6-archive-keyring.gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C5AD17C747E3415A3642D57D77C6C491D6AC1D69
echo "deb [signed-by=/usr/share/keyrings/k6-archive-keyring.gpg] https://dl.k6.io/deb stable main" | sudo tee /etc/apt/sources.list.d/k6.list
sudo apt-get update
sudo apt-get install k6
```

Opción 1 - Correr tests de carga manualmente con comandos

Para test local simple:

```bash
$ k6 new <nombre del archivo>.js --- Crea un script llamado <nombre del archivo>.js en el directorio actual
$ k6 run <nombre del archivo>.js --- Ejecuta el script
```

Para simular test de carga con mas de un usuario virtual y de cierta duracion, por consola:

```bash
$ k6 run --vus 10 --duration 30s <nombre del archivo>.js
```

![alt text](image.png)
![alt text](image-2.png)


Opción 2 - Correr test automaticos con la definicion del script.js

Para un testeo de 20 usuarios y de 15s:

```bash
import http from 'k6/http';
import { sleep } from 'k6';
export const options = {
  vus: 20,
  duration: '15s',
};
export default function () {
  http.get('http://test.k6.io');
  sleep(1);
}
```

Luego
```bash
$ k6 run <nombre del archivo>.js --- Ejecuta el script
```
![alt text](image-1.png)

Opcion 3 - Correr test automaticamente con subidas y bajadas de cantidad de usuarios conectados

```bash
import http from 'k6/http';
import { check, sleep } from 'k6';

export const options = {
  stages: [
    { duration: '10s', target: 5 },
    { duration: '20s', target: 30 },
    { duration: '10s', target: 8 },
  ],
};

export default function () {
  const res = http.get('https://httpbin.test.k6.io/');
  check(res, { 'status was 200': (r) => r.status == 200 });
  sleep(1);
}
```

Luego
```bash
$ k6 run <nombre del archivo>.js --- Ejecuta el script
```

![alt text](image-3.png)
