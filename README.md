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

## Instalación de SonarScanner

Puedes utilizar:
```bash
 sudo apt-get install sonar-scanner
```
Ó

```bash
 wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-5.0.1.3006-linux.zip
 unzip sonar-scanner-cli-5.0.1.3006-linux.zip
 sudo mv sonar-scanner-5.0.1.3006-linux /opt/sonar-scanner
 nano ~/.bashrc # Debes abrir y agregar en la ultima linea lo siguiente:
 export PATH=$PATH:/opt/sonar-scanner/bin # Liego de agregar Ctl+x Y luego Y para guardar
 source ~/.bashrc # Actualizo las variables del bash
```

Una vez realizados estos pasos deberias poder ejecutar sin problemas SonarScanner.

## Utilización de SonarQube atravez de SonarScanner

Debes indicarle a SonarScanner la URL de tu servidor de SonarQube. Abre el archivo de configuración del scanner (usualmente ubicado en /opt/sonar-scanner/sonar-scanner.properties en Linux) y agrega la línea:

Abre el archivo de configuración en /opt/sonar-scanner/conf/sonar-scanner.properties y añade la URL de tu servidor SonarQube:

```bash
nano /opt/sonar-scanner/conf/sonar-scanner.properties
# pegar lo siguiente : sonar.host.url=http://TUIPINET:9000
```

![sonar-scanner](<Images/image_1.png>)

## Crear un proyecto

Para crear un nuevo proyecto ingresamos a http://TUIPINET:9000 y elegimos **Create Project > Local Project** y le asignamos un nombre continuamos.

![Create project](<Images/image_5.png>)

Luego elegimos **Use the global setting** y creamos el proyecto.

Cabe aclarar que no es necesario crear el proyecto manualmente ya que este se creará automáticamente al ejecutar el análisis con sonar scanner, pero en el caso de querer instalar un plugin como se verá a continuación se requiere tener acceso a un proyecto existente.

## Instalar plugins

Sonnarqube permite analizar múltiples lenguajes en su versión gratuita (java, C#, javascript, html, etc), pero otros lenguajes solo se pueden analizar pagando la versión **Developer**, o instalar plugins.

Para instalar un plugin en un contenedor de sonarqube corriendo en docker se debe descargar el archivo .jar en la carpeta *$SONARQUBE_HOME/extensions/plugins/* del contenedor.

```bash
docker exec sonarqube bash -c 'wget <PLUGIN_JAR_URL> -P "$SONARQUBE_HOME"/extensions/plugins/'
```

por ejemplo para analizar un código en C o C++

```bash
docker exec sonarqube bash -c 'wget https://github.com/SonarOpenCommunity/sonar-cxx/releases/download/cxx-2.2.0-beta.6/sonar-cxx-plugin-2.2.0.946.jar -P "$SONARQUBE_HOME"/extensions/plugins/'
```

Una vez instalado el plugin deberíamos poder encontrarlo en la ventada de **Quality Profiles** dentro de sonarqube (Esto es en http://TUIPNET:9000).

Es posible que el plugin se instale con todas sus reglas desactivadas, para poder activarlas primero debemos crear una copia del perfil correspondiente al plugin, para lo que nos dirigimos a **Quality Profiles > Create** y elegimos la opción **Copy an existing quality profile** con el lenguaje que corresponda.

![quality profile](<Images/image_2.png>)

Ahora podemos seleccionar el nuevo perfil y activar reglas seleccionandolo en la lista de Quality Profiles y apretando en el boton **Activate More** donde podremos activar reglas manualmente o si querríamos activarlas todas seleccionamos **Bulk Change > Activate In** y eligiendo el perfil que acabamos de crear.

![Activate rules](<Images/image_3.png>)

Por último debemos seleccionar el nuevo perfil para el proyecto, para lo que vamos al proyecto en particular y en **Project Settings > Quality Profiles** elegimos **Add Language** y elegimos el lenguaje en particular con el perfil recién creado.

![Select profile](<Images/image_4.png>)

## Ejecuta el análisis
Navega a la carpeta raíz de tu proyecto y ejecuta el siguiente comando, reemplazando [project_key] por un identificador único para tu proyecto y path_to_project por la ruta de tu proyecto si no estás ya en ella:

```bash
sonar-scanner \
  -Dsonar.projectKey=[project_key] \
  -Dsonar.sources=path_to_project \
  -Dsonar.token=[your_token]
```

Para el campo [your_token], genera un token de autenticación en SonarQube:
Ve a My Account > Security en la interfaz de SonarQube.
Crea un nuevo token y usa el valor generado en lugar de [your_token].

Alternativamente podemos crear un archivo *sonar-project.properties* en el directorio de nuestro proyecto como el que se encuentra de como ejemplo en este mismo repositorio.

Después de ejecutar el comando, el proyecto debería aparecer en la interfaz de SonarQube en http://TUIPINET:9000

En la ventana principal del proyecto tendremos un resumen del estado actual del proyecto con el numero de *issues* clasificados en las categorías *Security, Reliability & Maintainability* Podemos seleccionar una categoría para ver los problemas relacionados a esa categoría, explorar la ventana **Issues** para ver todos los problemas existentes del proyecto o, si solo nos interesa observar un tipo de problema en particular, podemos desde la ventana **Rules** elegir la regla correspondiente al problema que buscamos y luego seleccionar el número que figura junto a **Issues** (Siempre que este sea mayor que 0)

![Rule selection](<Images/image_6.png>)
![Rule Issues list](<Images/image_7.png>)