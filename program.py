import os
import hvac
import tkinter as tk
from tkinter import messagebox
from dotenv import load_dotenv

# Función para obtener las credenciales desde Vault
def obtener_credenciales(client):
    try:
        # Verificar que la conexión es exitosa
        if client.is_authenticated():
            print("Autenticado con éxito en Vault.")
        
        # Obtener el secreto
        secret_path = "example"
        secret = client.secrets.kv.v2.read_secret_version(path=secret_path, raise_on_deleted_version=True)

        # Extraer las credenciales
        username = secret['data']['data']['username']
        password = secret['data']['data']['password']
        
        return username, password

    except hvac.exceptions.InvalidRequest as e:
        messagebox.showerror("Error", f"Error al obtener las credenciales: {str(e)}")
    except Exception as e:
        messagebox.showerror("Error", f"Ocurrió un error: {str(e)}")
        return None, None

# Función para verificar las credenciales ingresadas
def verificar_login(client, entry_usuario, entry_contrasena):
    username, password = obtener_credenciales(client)
    if username and password:  # Verificar que las credenciales fueron obtenidas correctamente
        if entry_usuario.get() == username and entry_contrasena.get() == password:
            messagebox.showinfo("Éxito", "Inicio de sesión exitoso.")
        else:
            messagebox.showerror("Error", "Usuario o contraseña incorrectos.")

# Función principal
def main():
    # Cargar variables de entorno desde el archivo .env
    load_dotenv()

    # Configurar la variable de entorno VAULT_ADDR
    os.environ['VAULT_ADDR'] = os.getenv('VAULT_ADDR')

    # Configuración de Vault
    client = hvac.Client(
        url=os.environ['VAULT_ADDR'],  # Dirección de Vault desde la variable de entorno
        token=os.getenv('VAULT_TOKEN')  # Token de Vault desde la variable de entorno
    )

    # Crear la ventana principal
    ventana = tk.Tk()
    ventana.geometry("400x300")
    ventana.title("Credenciales de Vault")

    # Etiquetas y entradas para el inicio de sesión
    tk.Label(ventana, text="Usuario:", font=("Arial", 14)).pack(pady=5)
    entry_usuario = tk.Entry(ventana, font=("Arial", 14))
    entry_usuario.pack(pady=5)

    tk.Label(ventana, text="Contraseña:", font=("Arial", 14)).pack(pady=5)
    entry_contrasena = tk.Entry(ventana, show='*', font=("Arial", 14))
    entry_contrasena.pack(pady=5)

    # Botón para verificar el inicio de sesión
    boton_login = tk.Button(ventana, text="Iniciar Sesión", font=("Arial", 14),
                            command=lambda: verificar_login(client, entry_usuario, entry_contrasena))
    boton_login.pack(pady=20)

    # Ejecutar el bucle principal de la ventana
    ventana.mainloop()

# Ejecutar el programa solo si este archivo es ejecutado directamente
if __name__ == "__main__":
    main()
