# SonarQube

## Instalación de sonnarqube en maquina local Linux

```bash
docker pull sonarqube  # (tener docker instalado)
docker run -d --name sonarqube -p 9000:9000 sonarqube
docker ps  # (muestra si esta bien montada la imagen  de sonarqube)
ip a # (buscas tu ip inet ej : 192.168.100.5)
```
Luego verificas si en el puerto 9000 esta montado el sonar, para esto puede abrir tu navegador e ingresar como dirección:

```http
TUIPINET:9000
```
Usas el usuario y la contraseña `admin` y te hace poner una nueva contraseña de tu elección.

Guia: https://www.youtube.com/watch?v=SRnvLQYXchI

## Utilización de SonarQube atravez de SonarScanner

Debes indicarle a SonarScanner la URL de tu servidor de SonarQube. Abre el archivo de configuración del scanner (usualmente ubicado en /etc/sonar-scanner/sonar-scanner.properties en Linux) y agrega la línea:

Abre el archivo de configuración en /opt/sonar-scanner/conf/sonar-scanner.properties y añade la URL de tu servidor SonarQube:

sonar.host.url=http://TUIPINET:9000

## Ejecuta el análisis
Navega a la carpeta raíz de tu proyecto y ejecuta el siguiente comando, reemplazando [project_key] por un identificador único para tu proyecto y path_to_project por la ruta de tu proyecto si no estás ya en ella:

```bash
sonar-scanner \
  -Dsonar.projectKey=[project_key] \
  -Dsonar.sources=path_to_project \
  -Dsonar.login=[your_token]
```

Para el campo [your_token], genera un token de autenticación en SonarQube:

    Ve a My Account > Security en la interfaz de SonarQube.
    Crea un nuevo token y usa el valor generado en lugar de [your_token]
    
Después de ejecutar el comando, el proyecto debería aparecer en la interfaz de SonarQube en http://TUIPINET:9000
