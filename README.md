# Vault by Hashicorp

## Descargar Vault

Para descargar Vault se puede buscar la pagina oficial por internet darle al boton install, el cual te llevará al instructivo donde te explica como instalar Vault en diferentes Sistemas Operativos. Esto se encuentra disponible en el siguiente link:

https://developer.hashicorp.com/vault/install?product_intent=vault

## Utilizar Vault

HashiCorp Vault ofrece diferentes modos de operación, y cada uno tiene usos específicos que se adaptan a diferentes entornos y necesidades de seguridad:

- Modo Dev (vault server -dev): Para desarrollo local, no persistente, inseguro, pero rápido de configurar.
- Modo Standalone: Para producción en entornos pequeños, persistente, seguro.
- Modo HA (High Availability): Para alta disponibilidad en producción, redundancia con un clúster.
- Modo Performance Replication : Para grandes despliegues con necesidad de mejorar rendimiento y disponibilidad global.

En producción, el modo HA o Performance Replication es esencial para garantizar la seguridad y disponibilidad, mientras que el modo dev solo es adecuado para pruebas locales.

Luego de realizar la instalación si desea lanzar Vault localmente se puede utilizar el siguiente comando:

```bash
vault server -dev
```

Esto inicia vault y permite que se puedan realiza acciones sobre la misma desde otra terminal.
Para realizar esta acción las terminales deben conocer la variable de entorno `VAULT_ADDR`, podemos declararla localmente asi no hace falta que cada vez que abrimos una terminal la especificamos. Esto se realiza de la siguiente forma:

```bash
nano ~/.bashrc                              # Abrir y agregar en la ultima linea el contenido de la siguiente linea

export VAULT_ADDR='http://127.0.0.1:8200'   # Agregar esta linea luego guardar los cambios con Ctrl+X y luego Yes 'Y'

source ~/.bashrc                            # Actualizamos las variables de la terminal para obtener los cambios
```
Luego podemos desde cualquier terminal comunicarnos con Vault para realizar las siguentes acciones:

```bash
vault kv put secret/example username="giuliano" password="123"    # Declarar 2 secretos en la seccion Examples
vault kv put secret/example username="tomas" password="1234"      # Actualizar esos 2 secretos
vault kv put secret/example username="eli" password="12345"       

vault kv get secret/example                                       # Observar los secretos actuales

vault status                                                      # Estado del Vault en modo servidor 
```

## Ejecución del programa de Prueba

Las dependencias necesarias se pueden instalar con los siguientes comandos:

```bash
pip install hvac --break-system-packages
pip install python-dotenv --break-system-packages
```

Tambien se debe agregar un archivo `.env` el cual contenga las siguientes variables que solicita el programa:

```bash
VAULT_ADDR=http://127.0.0.1:8200            # Direccion de Vault
VAULT_TOKEN=rootToken    # Token de root (se obtiene al levantar el Vault)
```
El archivo `.env` debe estar definido en el directorio principal del proyecto para sui correcta identificación.

El programa realizado en python consiste en una ventana que realiza la petición de credenciales y realiza una consulta a la boveda para verificar si son correctas. Luego de eso avisa si es correcta o no. Se puede ejecutar de la siguiente forma:

```bash
python program.py
python3 program.py
```


