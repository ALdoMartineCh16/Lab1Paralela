import matplotlib.pyplot as plt

# Leer datos del archivo comparacion_tiempos.txt
tamanios = []
tiempos_clasico = []
tiempos_bloques = []

with open('comparacion_tiempos.txt', 'r') as archivo:
    for linea in archivo:
        size, tiempo_clasico, tiempo_bloques = map(int, linea.split())
        tamanios.append(size)
        tiempos_clasico.append(tiempo_clasico)
        tiempos_bloques.append(tiempo_bloques)

# Graficar los tiempos de ejecución
plt.plot(tamanios, tiempos_clasico, label='Clásico', marker='o')
plt.plot(tamanios, tiempos_bloques, label='Bloques', marker='s')
plt.title('Comparación de tiempos de ejecución: Clásico vs Bloques')
plt.xlabel('Tamaño de la matriz (NxN)')
plt.ylabel('Tiempo de ejecución (ms)')
plt.grid(True)
plt.legend()
plt.show()
